#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include <vector>
#include "vector3D.h"
#include "constant.h"

const double KERNAL_POLY_CONSTANT = 4.921875;
const double KERNAL_POLY_GRAD_CONSTANT = 9.4000888;
const double KERNAL_POLY_LAP_CONSTANT = 9.4000888;
const double KERNAL_SPIK_GRAD_CONSTANT = -14.323944878;
const double KERNAL_VISC_LAPLACIAN_CONSTANT = 14.323944878;

using namespace std;

class Particle {
public:
	Particle(): position(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f) {}
	Particle(const Vector3D &_position, const Vector3D &_velocity): position(_position), velocity(_velocity) {}
	
	void countDensity(const vector<Particle> &neighbour, const vector<double> &r) {
		density = 1;
		int l = neighbour.size();
		for (int i = 0; i < l; ++i) {
			density += KernelPoly(neighbour[i], r[i]) * mass;
		}
	}
	void countPressure(const vector<Particle> &neighbour, const vector<double> &r) {
		pressure =  0.5 * (density - 1.2f);
	}
	void countForce(const vector<Particle> &neighbour, const vector<double> &r) {
		force = Vector3D(0, g, 0);
		
		int l = neighbour.size();		
		for (int i = 0; i < l; ++i) {
			force += mass * 0.5 / density * KernalSpik(neighbour[i], r[i]) * (pressure + neighbour[i].getPressure());
		}
	}
	void countViscosity(const vector<Particle> &neighbour, const vector<double> &r) {
		viscosity = Vector3D(0.0f, 0.0f, 0.0f);
		int l = neighbour.size();		
		for (int i = 0; i < l; ++i) {
			viscosity += 0.1f * mass / density * (neighbour[i].getVelocity() - velocity) * KernalVisc(neighbour[i], r[i]);
		}
	}
	void countColorfield(const vector<Particle> &neighbour, const vector<double> &r) {
		Vector3D color_grad(0.0f, 0.0f, 0.0f);
		double color_lap = 0;
		int l = neighbour.size();		
		for (int i = 0; i < l; ++i) {
			color_grad += mass / density * KernalPolyGrad(neighbour[i], r[i]);
			color_lap += mass / density * KernalPolyLap(neighbour[i], r[i]);
		}
		if (color_grad.norm() > 1e-6) color_grad = - color_lap * color_grad.unit();
		else color_grad = Vector3D(0.0f, 0.0f, 0.0f);
	}
	void move() {
//		printf("force: %lf, %lf, %lf\n", force[0], force[1], force[2]);
		//printf("viscosity: %lf, %lf, %lf\n", viscosity[0], viscosity[1], viscosity[2]);
		//printf("tenssion: %lf, %lf, %lf\n", tenssion[0], tenssion[1], tenssion[2]);
		Vector3D acce = (force + viscosity + tenssion) / density;
		velocity += acce * DELTA_TIME / 1000;
		//printf("velocity0: %lf, %lf, %lf\n", velocity[0], velocity[1], velocity[2]);		
		position += velocity * DELTA_TIME / 1000;
		//printf("position: %lf, %lf, %lf\n", position[0], position[1], position[2]);
		//printf("density: %lf\n", density);
		//printf("pressure: %lf\n", pressure);
	}
	void check(const Vector3D &bound) {
		for (int i = 0; i < 3; ++i) {
			if (abs(position[i]) > bound[i] / 2) {
				velocity[i] *= -1;
			}
		}
		//printf("velocity1: %lf, %lf, %lf\n\n", velocity[0], velocity[1], velocity[2]);		
	}

    double KernelPoly(const Particle &_particle, double r) const {
        return KERNAL_POLY_CONSTANT / pow(SMOOTHING_WIDTH, 9) * pow(SMOOTHING_WIDTH2 - r * r, 3);
    }
	double KernalPolyLap(const Particle &_particle, double r) const {
		return KERNAL_POLY_LAP_CONSTANT / pow(SMOOTHING_WIDTH, 9) * (SMOOTHING_WIDTH2 - r * r) * (7.0f * r * r - 3.0f * SMOOTHING_WIDTH2);
	}
	Vector3D KernalPolyGrad(const Particle &_particle, double r) const {
		return -KERNAL_POLY_GRAD_CONSTANT / pow(SMOOTHING_WIDTH, 9) * pow(SMOOTHING_WIDTH2 - r * r, 2) * _particle.getPosition();
	}
    Vector3D KernalSpik(const Particle &_particle, double r) const {
        return KERNAL_SPIK_GRAD_CONSTANT / pow(SMOOTHING_WIDTH, 6) * pow(SMOOTHING_WIDTH - r, 2) * _particle.getPosition();
    }
	double KernalVisc(const Particle &_particle, double r) const {
        return KERNAL_VISC_LAPLACIAN_CONSTANT / pow(SMOOTHING_WIDTH, 6) * (SMOOTHING_WIDTH - r);		
	}

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
	Vector3D position, velocity, viscosity, tenssion, force;
	double density, pressure;
};

#endif
