#include "Particle.h"

const double KERNAL_POLY_CONSTANT = 4.921875;
const double KERNAL_POLY_GRAD_CONSTANT = -9.4000888;
const double KERNAL_POLY_LAP_CONSTANT = 9.4000888;
const double KERNAL_SPIK_GRAD_CONSTANT = -14.323944878;
const double KERNAL_VISC_LAPLACIAN_CONSTANT = 14.323944878;

using namespace std;

Particle::Particle(): position(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f) {}
Particle::Particle(const Vector3D &_position, const Vector3D &_velocity): position(_position), velocity(_velocity) {}

void Particle::countDensity(const vector<Particle> &neighbour, const vector<double> &r) {
    density = mass * KERNAL_POLY_CONSTANT / pow(SMOOTHING_WIDTH, 3);
    int l = neighbour.size();
    for (int i = 0; i < l; ++i) {
        density += KernelPoly(neighbour[i], r[i]) * mass;
    }
}

void Particle::countPressure(const vector<Particle> &neighbour, const vector<double> &r) {
    // pressure =  1000 * (density - 12);
    pressure = pow(density / 1000.0, 7) - 1;
}

void Particle::countForce(const vector<Particle> &neighbour, const vector<double> &r) {
    force = Vector3D(0, 0, 0);
    int l = neighbour.size();		
    for (int i = 0; i < l; ++i) {
        force += mass * 0.5 / density * KernalSpik(neighbour[i], r[i]) * (pressure + neighbour[i].getPressure());
    }
}

void Particle::countViscosity(const vector<Particle> &neighbour, const vector<double> &r) {
    viscosity = Vector3D(0.0f, 0.0f, 0.0f);
    int l = neighbour.size();		
    for (int i = 0; i < l; ++i) {
        viscosity += mass / density * (neighbour[i].getVelocity() - velocity) * KernalVisc(neighbour[i], r[i]) * 3e-4;
    }
}

void Particle::countColorfield(const vector<Particle> &neighbour, const vector<double> &r) {
    Vector3D color_grad(0.0f, 0.0f, 0.0f);
    double color_lap = 0;
    int l = neighbour.size();		
    for (int i = 0; i < l; ++i) {
        color_grad += mass / density * KernalPolyGrad(neighbour[i], r[i]);
        color_lap += mass / density * KernalPolyLap(neighbour[i], r[i]);
    }
    if (color_grad.norm() > 1e-6) tenssion = - color_lap * color_grad.unit() * 1e-4;
    else tenssion = Vector3D(0.0f, 0.0f, 0.0f);
}

void Particle::countVelocity(const Vector3D &base_move) {
    Vector3D acce = (force + viscosity + tenssion) / density;
    acce[1] += g;
    velocity += acce * DELTA_TIME / 1000 + base_move / DELTA_TIME * 200;	
}

void Particle::move() {
    //printf("force: %lf, %lf, %lf\n", force[0], force[1], force[2]);
    //printf("viscosity: %lf, %lf, %lf\n", viscosity[0], viscosity[1], viscosity[2]);
    //printf("tenssion: %lf, %lf, %lf\n", tenssion[0], tenssion[1], tenssion[2]);
    //printf("velocity0: %lf, %lf, %lf\n", velocity[0], velocity[1], velocity[2]);		
    position += velocity * DELTA_TIME / 1000;
    //printf("position: %lf, %lf, %lf\n", position[0], position[1], position[2]);
    //printf("density: %lf\n", density);
    //printf("pressure: %lf\n", pressure);
}
void Particle::check(const Vector3D &bound) {
    for (int i = 0; i < 3; ++i) {
        if (abs(position[i]) > bound[i] - 1e-6) {
            position[i] = bound[i] * (position[i] / abs(position[i])) * 2 - position[i];
            velocity[i] *= -0.5f;
        }
        /*
           if (abs(position[i]) > bound[i] - 1e-4 && velocity[i] * position[i] > 0) {
           velocity[i] *= -0.5f;
           }*/
    }
}

double Particle::KernelPoly(const Particle &_particle, double r) const {
    return KERNAL_POLY_CONSTANT / pow(SMOOTHING_WIDTH, 9) * pow(SMOOTHING_WIDTH2 - r * r, 3);
}

double Particle::KernalPolyLap(const Particle &_particle, double r) const {
    return KERNAL_POLY_LAP_CONSTANT / pow(SMOOTHING_WIDTH, 9) * (SMOOTHING_WIDTH2 - r * r) * (7.0f * r * r - 3.0f * SMOOTHING_WIDTH2);
}

Vector3D Particle::KernalPolyGrad(const Particle &_particle, double r) const {
    return KERNAL_POLY_GRAD_CONSTANT / pow(SMOOTHING_WIDTH, 9) * pow(SMOOTHING_WIDTH2 - r * r, 2) * (_particle.getPosition() - position);
}

Vector3D Particle::KernalSpik(const Particle &_particle, double r) const {
    return KERNAL_SPIK_GRAD_CONSTANT / pow(SMOOTHING_WIDTH, 6) * pow(SMOOTHING_WIDTH - r, 2) * (_particle.getPosition() - position);
}

double Particle::KernalVisc(const Particle &_particle, double r) const {
    return KERNAL_VISC_LAPLACIAN_CONSTANT / pow(SMOOTHING_WIDTH, 6) * (SMOOTHING_WIDTH - r);		
}
