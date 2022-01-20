#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <fstream> 
#include <iostream>
#include <string>

struct game_stats
{
	uint32_t played_time;
	uint32_t total_score;
	uint32_t best_score;
	uint8_t level;
};

struct Vec2D
{
	int x, y;
};

class Utilities
{
public:
	static bool outOfGame(int x, int y);
	static bool rectangles_overlap(Vec2D A, Vec2D B, int h);
	static int Load_Levels(uint8_t test[12][16], uint8_t level);
	static int Load_Game_Data(game_stats &gdata);
	static int Save_Game_Data(game_stats gdata);
	static uint32_t getDigits(uint32_t number);
	static char* getSource(uint8_t digit);
};

template <typename T> T Max(T a, T b);

template uint32_t Max(uint32_t, uint32_t);
template int Max(int, int);