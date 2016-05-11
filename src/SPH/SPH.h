#ifndef SPH_H
#define SPH_H

#include <list>
#include "../includes/constant.h"
#include "../includes/vector3D.h"
#include "Particle.h"

using namespace std;

class SPH {
    public:
        SPH() {}
        SPH(const double _bound[]): particle_list(0), bound(_bound), base_move(0.0f, 0.0f, 0.0f) {}

        // add a new particle to the SPH system
        void add(Particle _particle) {
            particle_list.push_back(_particle);
        }

        // remove the oldest particle
        void remove() {
            if (!particle_list.empty()) particle_list.pop_front();
        }

        // set the recent container movement
        void setBase(const Vector3D &base_vec) {
            base_move = base_vec;
        }

        // get the size of the SPH
        int size() {
            return particle_list.size();
        }

        // get the particle list
        list<Particle> getList() const {
            return particle_list;
        }

        // simulate for one step
        void move();

    private:
        // list of particles
        list<Particle> particle_list;
        // boundary for the container
        Vector3D bound;
        // recent movement of the container
        Vector3D base_move;
};

#endif
