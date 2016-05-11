#include "SPH.h"

using namespace std;

void SPH::move() {
	int l = particle_list.size();
	// get the list of neighbors that is close enough for each particle with the distance
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
	
	// count density
	i = 0;
	for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++it0, ++i) {
		(*it0).countDensity(neighbour_list[i], dis_list[i]);
	}
	
	// count pressure
	i = 0;
	for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++it0, ++i) {
		(*it0).countPressure(neighbour_list[i], dis_list[i]);
	}
	
	// count different force
	i = 0;
	for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++it0, ++i) {
		(*it0).countForce(neighbour_list[i], dis_list[i]);
		(*it0).countViscosity(neighbour_list[i], dis_list[i]);
		(*it0).countColorfield(neighbour_list[i], dis_list[i]);
	}
	
	// count final velocity and move
	for (auto it0 = particle_list.begin(); it0 != particle_list.end(); ++it0) {
		(*it0).countVelocity(base_move);
		(*it0).check(bound);
		(*it0).move();
	}
	
	// reset container movement
	base_move = Vector3D(0.0f, 0.0f, 0.0f);
}
