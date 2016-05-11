#ifndef MARCHINGCUBE_H
#define MARCHINGCUBE_H

#include <list>
#include "../includes/constant.h"
#include "lookup_list.h"
#include "../SPH/Particle.h"
#include "../includes/vector3D.h"

using namespace std;

class MarchingCube {
    public:
        MarchingCube() {}
        MarchingCube(const double _bound[], double _l, list<Particle> *_particles);
        ~MarchingCube();

        // count the mesh
        void count(vector<Vector3D> &vertexs, vector<int> &tri_index);

    private:
        // return the closeset particle if there is a particle contain this vertex, otherwise NULL
        Particle* check(Vector3D v) const;

        // if one in one not, return the one in, otherwise, return NULL
        Particle* diff(Particle* a, Particle* b) const;

        // return the intersect point one the edge
        Vector3D* countInter(const Vector3D &v, const Vector3D &u, Particle* tmp) const;

    private:
        // position and size of the container
        Vector3D base, bound;
        // edge length of the cube
        double l;
        // number of edges on each coordinate
        int total_edge[3];
        // total number of vertex and edge
        int sum_v, sum_e;

        // list of particles
        list<Particle> *particles;

        /*	list of all edges for cubes
            point to the cut point if intersect with the mesh, otherwise NULL
            edge are numbered by related vetex towards z, y, x
         */
        vector<Vector3D*> intersections;
        // related index offset for twelve edges in a cube
        vector<int> offset_edge;
        // related index offset for two edge that is one step different on each coordinate
        int dx, dy, dz;
        // map edge to index of final mesh vertex
        vector<int> mapping;

        // list of all vertexs for cubes, point to the closest particle if it is inside, otherwise NULL
        vector<Particle*> inside;
        // related index offset for eight vertex in a cube
        vector<int> offset;

};

#endif
