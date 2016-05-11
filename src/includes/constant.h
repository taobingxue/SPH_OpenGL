#ifndef CONSTANT_H
#define CONSTANT_H

#pragma once

const int PARTICLE_MAX = 1000;
const double PARTICLE_RADIUS = 0.045f;
const double GRID_LENGTH = 0.08f;
const double SMOOTHING_WIDTH = 0.04f;
const double SMOOTHING_WIDTH2 = SMOOTHING_WIDTH * SMOOTHING_WIDTH;
const double SMOOTHING_WIDTH3 = SMOOTHING_WIDTH * SMOOTHING_WIDTH2;
const double mass = 0.02f;
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

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const double FRAME_LENGTH[3] = {0.8, 0.8, 0.8};
const double FRAME_BASE_INIT[3] = {0, -0.25f, -2.3};
const double WALL_EDGE[12][3] = {
	{ - FRAME_LENGTH[0], 0                ,   FRAME_LENGTH[2]},
	{   FRAME_LENGTH[0], 0                ,   FRAME_LENGTH[2]},
	{ - FRAME_LENGTH[0], 0                , - FRAME_LENGTH[2]},
	{   FRAME_LENGTH[0], 0                , - FRAME_LENGTH[2]},	
	{ - FRAME_LENGTH[0], - FRAME_LENGTH[1], 0                },
	{   FRAME_LENGTH[0], - FRAME_LENGTH[1], 0                },
	{ - FRAME_LENGTH[0],   FRAME_LENGTH[1], 0                },
	{   FRAME_LENGTH[0],   FRAME_LENGTH[1], 0                },
	{   0              , - FRAME_LENGTH[1],   FRAME_LENGTH[2]},
	{   0              ,   FRAME_LENGTH[1],   FRAME_LENGTH[2]},
	{   0              , - FRAME_LENGTH[1], - FRAME_LENGTH[2]},
	{   0              ,   FRAME_LENGTH[1], - FRAME_LENGTH[2]}};
const double WALL_SCALE[12][3] = {
	{0.01, FRAME_LENGTH[1] * 2, 0.01}, {0.01, FRAME_LENGTH[1] * 2, 0.01}, {0.01, FRAME_LENGTH[1] * 2, 0.01}, {0.01, FRAME_LENGTH[1] * 2, 0.01},
	{0.01, 0.01, FRAME_LENGTH[2] * 2}, {0.01, 0.01, FRAME_LENGTH[2] * 2}, {0.01, 0.01, FRAME_LENGTH[2] * 2}, {0.01, 0.01, FRAME_LENGTH[2] * 2},
	{FRAME_LENGTH[0] * 2, 0.01, 0.01}, {FRAME_LENGTH[0] * 2, 0.01, 0.01}, {FRAME_LENGTH[0] * 2, 0.01, 0.01}, {FRAME_LENGTH[0] * 2, 0.01, 0.01}};

#endif
