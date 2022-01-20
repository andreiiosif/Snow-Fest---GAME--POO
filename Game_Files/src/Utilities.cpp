#include "../include/Utilities.h"

bool Utilities::rectangles_overlap(Vec2D A, Vec2D B, int h)
{
	Vec2D l1, r1, l2, r2;

	l1.x = A.x;
	l1.y = A.y;
	r1.x = A.x + h;
	r1.y = A.y - h;

	l2.x = B.x;
	l2.y = B.y;
	r2.x = B.x + h;
	r2.y = B.y - h;

	if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
		|| l2.y == r2.y) {
		// the line cannot have positive overlap
		return false;
	}

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	// If one rectangle is above other
	if (r1.y >= l2.y || r2.y >= l1.y)
		return false;

	return true;
}

bool Utilities::outOfGame(int x, int y)
{
	if (y < 0 || y > 600 - 50 || x < 0 || x > 800 - 50)
		return true;
	return false;
}

int Utilities::Load_Levels(uint8_t test[12][16], uint8_t level)
{
	char buff[100];
	strcpy_s(buff, strlen("data/bin/levels/level") + 1, "data/bin/levels/level");
	unsigned l = strlen(buff);
	buff[l] = level + 48;
	buff[l + 1] = '\0';
	strcat_s(buff, sizeof(buff), ".dat");

	std::ifstream rf(buff, std::ios::out | std::ios::binary);
	if (!rf) {
		std::cout << "\nERROR: Cannot open file!";
		return 1;
	}
	uint8_t buffer[12 * 16];
	rf.read((char*)&buffer, sizeof(buffer));

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			test[i][j] = buffer[i * 16 + j];
		}
	}

	rf.close();
	if (!rf.good()) {
		std::cout << "\nERROR: Error occurred at reading time!";
		return 1;
	}
	return 0;
}

int Utilities::Load_Game_Data(game_stats &gdata)
{
	std::ifstream rf("data/bin/game_data.dat", std::ios::out | std::ios::binary);
	if (!rf) {
		std::cout << "\nERROR: Cannot open file!";
		return 1;
	}
	rf.read((char*)&gdata, sizeof(gdata));
	rf.close();
	if (!rf.good()) {
		std::cout << "\nERROR: Error occurred at reading time!";
		return 1;
	}
	return 0;
}

int Utilities::Save_Game_Data(game_stats gdata)
{
	std::ofstream wf("data/bin/game_data.dat", std::ios::out | std::ios::binary);
	if (!wf) {
		std::cout << "\nERROR: Cannot open file!";
		return 1;
	}
	wf.write((char*)&gdata, sizeof(gdata));
	wf.close();
	if (!wf.good()) {
		std::cout << "\nERROR: Error occurred at writing time!";
		return 1;
	}
}

uint32_t Utilities::getDigits(uint32_t number)
{
	uint32_t sol = 0;
	if (number == 0) sol = 1;
	while (number)
	{
		sol++;
		number /= 10;
	}
	return sol;
}

char* Utilities::getSource(uint8_t digit)
{
	char* s = new char[30];
	switch (digit)
	{
	case 0:
		strcpy_s(s, strlen("data/png/BG/Numbers2/0.png") + 1, "data/png/BG/Numbers2/0.png");
		break;
	case 1:
		strcpy_s(s, strlen("data/png/BG/Numbers2/1.png") + 1, "data/png/BG/Numbers2/1.png");
		break;
	case 2:
		strcpy_s(s, strlen("data/png/BG/Numbers2/2.png") + 1, "data/png/BG/Numbers2/2.png");
		break;
	case 3:
		strcpy_s(s, strlen("data/png/BG/Numbers2/3.png") + 1, "data/png/BG/Numbers2/3.png");
		break;
	case 4:
		strcpy_s(s, strlen("data/png/BG/Numbers2/4.png") + 1, "data/png/BG/Numbers2/4.png");
		break;
	case 5:
		strcpy_s(s, strlen("data/png/BG/Numbers2/5.png") + 1, "data/png/BG/Numbers2/5.png");
		break;
	case 6:
		strcpy_s(s, strlen("data/png/BG/Numbers2/6.png") + 1, "data/png/BG/Numbers2/6.png");
		break;
	case 7:
		strcpy_s(s, strlen("data/png/BG/Numbers2/7.png") + 1, "data/png/BG/Numbers2/7.png");
		break;
	case 8:
		strcpy_s(s, strlen("data/png/BG/Numbers2/8.png") + 1, "data/png/BG/Numbers2/8.png");
		break;
	case 9:
		strcpy_s(s, strlen("data/png/BG/Numbers2/9.png") + 1, "data/png/BG/Numbers2/9.png");
		break;
	default:
		break;
	}
	return s;
}


template <typename T> T Max(T a, T b)
{
	return a > b ? a : b;
}