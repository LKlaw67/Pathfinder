#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;


class pathfinder
{
public:
	//int WIDTH = 20;
	//int HEIGHT = 20;

	//Color area[128][128];
	Color* area; //(x, y, step, bool node)
	int area_size;
	vector<int> rank;

	int sort(float & big, float & small, int size, Vector2i & epoint);

	vector<Vector2i> find(Vector2i& spoint, Vector2i& epoint, vector<Vector2i>& maze, int WIDTH, int HEIGHT);
};

