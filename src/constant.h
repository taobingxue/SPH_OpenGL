#ifndef CONSTANT_H
#define CONSTANT_H

const int PARTICLE_MAX = 1000;
const double PARTICLE_RADIUS = 0.45f;
const double GRID_LENGTH = 0.5f;
const double SMOOTHING_WIDTH = 1;
const double SMOOTHING_WIDTH2 = SMOOTHING_WIDTH * SMOOTHING_WIDTH;
const double SMOOTHING_WIDTH3 = SMOOTHING_WIDTH * SMOOTHING_WIDTH2;
const double mass = 1;
const int DELTA_TIME = 25;
const double g = -9.8f;

const double Pi = 3.1415926;
const float I[4] = {1, 1, 1, 1};
const float I01[4] = {0.1, 0.1, 0.1, 1};
const float I02[4] = {0.2, 0.2, 0.2, 1};
const float I08[4] = {0.8, 0.8, 0.8, 1};

const float color4_white[] = {1, 1, 1, 1};
const float color4_black[] = {0, 0, 0, 1};
const float color4_sphere[] = {0.5f, 0, 0, 1};

const double FRAME_LENGTH[3] = {9, 5, 10};
const double FRAME_BASE[3] = {0, -2, -20};
const double WALL_EDGE[12][3] = {
	{FRAME_BASE[0] - FRAME_LENGTH[0], FRAME_BASE[1]                  , FRAME_BASE[2] + FRAME_LENGTH[2]},
	{FRAME_BASE[0] + FRAME_LENGTH[0], FRAME_BASE[1]                  , FRAME_BASE[2] + FRAME_LENGTH[2]},
	{FRAME_BASE[0] - FRAME_LENGTH[0], FRAME_BASE[1]                  , FRAME_BASE[2] - FRAME_LENGTH[2]},
	{FRAME_BASE[0] + FRAME_LENGTH[0], FRAME_BASE[1]                  , FRAME_BASE[2] - FRAME_LENGTH[2]},	
	{FRAME_BASE[0] - FRAME_LENGTH[0], FRAME_BASE[1] - FRAME_LENGTH[1], FRAME_BASE[2]                  },
	{FRAME_BASE[0] + FRAME_LENGTH[0], FRAME_BASE[1] - FRAME_LENGTH[1], FRAME_BASE[2]                  },
	{FRAME_BASE[0] - FRAME_LENGTH[0], FRAME_BASE[1] + FRAME_LENGTH[1], FRAME_BASE[2]                  },
	{FRAME_BASE[0] + FRAME_LENGTH[0], FRAME_BASE[1] + FRAME_LENGTH[1], FRAME_BASE[2]                  },
	{FRAME_BASE[0]                  , FRAME_BASE[1] - FRAME_LENGTH[1], FRAME_BASE[2] + FRAME_LENGTH[2]},
	{FRAME_BASE[0]                  , FRAME_BASE[1] + FRAME_LENGTH[1], FRAME_BASE[2] + FRAME_LENGTH[2]},
	{FRAME_BASE[0]                  , FRAME_BASE[1] - FRAME_LENGTH[1], FRAME_BASE[2] - FRAME_LENGTH[2]},
	{FRAME_BASE[0]                  , FRAME_BASE[1] + FRAME_LENGTH[1], FRAME_BASE[2] - FRAME_LENGTH[2]}};
const double WALL_SCALE[12][3] = {
	{0.1, FRAME_LENGTH[1] * 2, 0.1}, {0.1, FRAME_LENGTH[1] * 2, 0.1}, {0.1, FRAME_LENGTH[1] * 2, 0.1}, {0.1, FRAME_LENGTH[1] * 2, 0.1},
	{0.1, 0.1, FRAME_LENGTH[2] * 2}, {0.1, 0.1, FRAME_LENGTH[2] * 2}, {0.1, 0.1, FRAME_LENGTH[2] * 2}, {0.1, 0.1, FRAME_LENGTH[2] * 2},
	{FRAME_LENGTH[0] * 2, 0.1, 0.1}, {FRAME_LENGTH[0] * 2, 0.1, 0.1}, {FRAME_LENGTH[0] * 2, 0.1, 0.1}, {FRAME_LENGTH[0] * 2, 0.1, 0.1}};

#endif
