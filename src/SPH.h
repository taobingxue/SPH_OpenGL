#ifndef SPH_H
#define SPH_H

#include <list>
#include "constant.h"
#include "vector3D.h"
#include "Particle.h"

using namespace std;

class SPH {
public:
	SPH() {}
	SPH(const double _bound[]): particle_list(0), bound(_bound) {}
	void add(Particle _particle) {
		particle_list.push_back(_particle);
	}
	void remove() {
		if (!particle_list.empty()) particle_list.pop_front();
	}
	void move() {
		int l = particle_list.size();
		
		vector<vector<Particle> > neighbour_list(l, vector<Particle>(0));
		vector<vector<double> > dis_list(l, vector<double>(0));
		int i = 0, j;
		for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++i) {
			Particle p0 = *it0;
			j = i + 1;
			for (auto it1 = ++it0; it1 != particle_list.end(); ++it1, ++j) {
				Particle p1 = *it1;
				double r = (p0.getPosition() - p1.getPosition()).norm();
				if (r < SMOOTHING_WIDTH) {
					neighbour_list[i].push_back(p1);
					dis_list[i].push_back(r);
					neighbour_list[j].push_back(p0);
					dis_list[j].push_back(r);
				}
			}
		}
		i = 0;
		for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++it0, ++i) {
			(*it0).countDensity(neighbour_list[i], dis_list[i]);
		}
		i = 0;
		for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++it0, ++i) {
			(*it0).countPressure(neighbour_list[i], dis_list[i]);
		}
		i = 0;
		for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++it0, ++i) {
			(*it0).countForce(neighbour_list[i], dis_list[i]);
			(*it0).countViscosity(neighbour_list[i], dis_list[i]);
			(*it0).countColorfield(neighbour_list[i], dis_list[i]);
		}
		for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++it0) {
			(*it0).move();
			(*it0).check(bound);
		}
	}
	int size() {
		return particle_list.size();
	}
	list<Particle> getList() const {
		return particle_list;
	}
	
private:
	list<Particle> particle_list;
	Vector3D bound;
};

#endif