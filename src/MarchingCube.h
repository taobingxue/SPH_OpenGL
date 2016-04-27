#ifndef MARCHINGCUBE_H
#define MARCHINGCUBE_H

#include "constant.h"
#include "vector3D.h"

using namespace std;

/*
 * cube vetex order
 *  -
 *  + x
 *  + x + z
 *  + z
 *  + y
 *  + y + x
 *  + y + x + z
 *  + y + z
 */

class MarchingCube {
public:
	MarchingCube() {}
	MarchingCube(const double _bound[], double _l, list<Vector3D> *_particles):
		bound(_bound), l(_l),
		sum_v((1 + (int)_bound[0] / _l) * (1 + (int)_bound[1] / _l) * (1 + (int)_bound[2] / _l)),
		sum_e((1 + (int)_bound[0] / _l) * (1 + (int)_bound[1] / _l) * (1 + (int)_bound[2] / _l) * 3),
		particles(_particles),
		intersections(sum_e, null),
		inside(sum_v, null),
		vertexs(0), mapping(0), tri_index(0) {
			for (int i = 0; i < 3; ++i) {
				total_edge[i] = (int)_bound[i] / _l;
			}
			len = bound / l;
			
			dx = (total_edge[2] + 1) * (total_edge[1] + 1);
			dy = total_edge[2] + 1;
			dz = 1;
			
			offset = vector<int>(8);
			offset[0] = 0;			offset[1] = dx;
			offset[2] = dx + dz;	offset[3] = dz;
			offset[4] = dy;			offset[5] = dy + dx;
			offset[6] = dx + dy +dz;offset[7] = dy + dz;
			
			offset_edge = vector<int>(12);
			offset[0] = 0;
			offset[1] = dx * 3 + 2;
			offset[2] = dz * 3;
			offset[3] = 2;
			offset[4] = dy * 3;
			offset[5] = (dy + dx) * 3 + 2;
			offset[6] = (dy + dz) * 3;
			offset[7] = dy * 3 + 2;
			offset[8] = 1;
			offset[9] = dx * 3 + 1;
			offset[10] = (dx + dz) * 3 + 1;
			offset[11] = dz * 3 + 1;
	}
	
	void count() {
		// count inside
		int p = 0;
		for (int i = 0; i <= total_edge[0]; ++i) {
			for (int j = 0; j <= total_edge[1]; ++j) {
				for (int k = 0; k <= total_edge[2]; ++k, ++p) {
					Vector3D vetex(i * len[0], j * len[1], k * len[2]);
					inside[p] = check(vetex);
				}
			}
		}
		
		// cout intersection
		p = 0; Particle *tmp = null;
		for (int i = 0; i <= total_edge[0]; ++i) {
			for (int j = 0; j <= total_edge[1]; ++j) {
				for (int k = 0; k <= total_edge[2]; ++k, p += 3) {
					Vector3D v0(i * len[0], j * len[1], k * len[2]);
					Vector3D v1(i * len[0] + len[0], j * len[1], k * len[2]);
					Vector3D v2(i * len[0], j * len[1] + len[1], k * len[2]);
					Vector3D v3(i * len[0], j * len[1], k * len[2] + len[2]);
					
					if (tmp = diff(inside[p / 3], inside[p / 3 + dz])) {
						intersection[p + 2] = countInter(v0, v3, tmp);
					}
					if (tmp = diff(inside[p / 3], inside[p / 3 + dy])) {
						intersection[p + 1] = countInter(v0, v2, tmp);
					}
					if (tmp = diff(inside[p / 3], inside[p / 3 + dx])) {
						intersection[p] = countInter(v0, v1, tmp);
					}
				}
			}
		}
		
		// intersection mapping
		for (int i = 0; i < sum_e; ++i) {
			if (intersection[i]) {
				mapping.push_back(vertexs.size());
				vertexs.push_back(intersection[i]->getPosition());
			}
		}
		
		// lookup
		p = 0;
		for (int i = 0; i < total_edge[0]; ++i) {
			for (int j = 0; j < total_edge[1]; ++j) {
				for (int k = 0; k < total_edge[2]; ++k, ++p) {
					// count status
					int status = 0;
					for (int sta_i = 0, tw = 1; sta_i < 8; ++sta_i, tw = tw << 1) {
						status |= inside[p + offset[sta_i]] ? tw : 0;
					}
					if (status == 0 || status == 255) continue;
					
					// count triangle
					for (int tri_p = 0; tri_p < 16 && TRI_TABLE[status][tri_p] >= 0; ++tri_p) {
						tri_index.push_back(mapping[offset_edge[TRI_TABLE[status][tri_p]] + p * 3]);
					}
				}
				p += dz;
			}
			p += dy;
		}
	}
private:
	Particle* check(Vector3D v) {
		double min_dis2 = GRID_LENGTH * GRID_LENGTH + 0.1;
		Particle* result = null;
		for (auto particle: *particles) {
			double dis2 = (particle.getPosition() - v).norm2();
			if (dis < min_dis2) {
				min_dis2 = dis;
				result = &particle;
			}
		}
		if (min_dis2 < PARTICLE_RADIUS * PARTICLE_RADIUS) return result;
		return null;
	}
	Particle* diff(Particle* a, Particle* b) {
		if (a == null && b != null) return b;
		if (a != null && b == null) return a;
		return null;
	}

	Vector3D bound, len;
	double l;
	int total_edge[3];
	int sum;
	int dx, dy, dz;
	
	list<Particle> *particles;
	vector<int> offset;
	vector<int> offset_edge;
	// edge are numbered by related vetex towards z, y, x
	vector<Vector3D*> intersections;
	vector<Particle*> inside;
	
	vector<Vector3D> vertexs;
	vector<int> mapping;
	vector<int> tri_index;
}

#endif