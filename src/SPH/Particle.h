#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include <vector>
#include "../includes/vector3D.h"
#include "../includes/constant.h"

using namespace std;

class Particle {
    public:
        Particle();
        Particle(const Vector3D &_position, const Vector3D &_velocity);

        // count different parameters based on its neighbors and distance to the neighbors
        void countDensity(const vector<Particle> &neighbour, const vector<double> &r);
        void countPressure(const vector<Particle> &neighbour, const vector<double> &r);
        void countForce(const vector<Particle> &neighbour, const vector<double> &r);
        void countViscosity(const vector<Particle> &neighbour, const vector<double> &r);
        void countColorfield(const vector<Particle> &neighbour, const vector<double> &r);
        void countVelocity(const Vector3D &base_move);

        // move to new position
        void move();
        // check the position, reflect and damp the velocity based on the boundary
        void check(const Vector3D &bound);

        // kernal functions
        double KernelPoly(const Particle &_particle, double r) const;
        double KernalPolyLap(const Particle &_particle, double r) const;
        Vector3D KernalPolyGrad(const Particle &_particle, double r) const;
        Vector3D KernalSpik(const Particle &_particle, double r) const;
        double KernalVisc(const Particle &_particle, double r) const;

        // Gets
        Vector3D countMid(const Vector3D &_pos) const {
            return (position + _pos) * 0.5f;
        }
        Vector3D getPosition() const {
            return position;
        }
        Vector3D getVelocity() const {
            return velocity;
        }
        double getPressure() const {
            return pressure;
        }

    private:
        // parameters for one particle
        Vector3D position, velocity, viscosity, tenssion, force;
        double density, pressure;
};

#endif
