#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "pathfinder.h"

using namespace std;
using namespace sf;

int pathfinder::sort(float& big, float& small, int size, Vector2i & epoint) {
	//vector<int>::iterator dig;

	/*if (distance <= small) {
		small = distance;
		output = 0;
		dig = rank.begin() + output;
		rank.insert(dig, area_size);
	}
	else if (distance >= big) {
		big = distance;
		output = -1;
		rank.push_back(area_size);
	}
	else {
		output = floor((distance - small) / (big - small) * (size - 1));
		dig = rank.begin() + output;
		rank.insert(dig, area_size);
	}*/
	bool change = false;
	//float distance = sqrt(pow((int)area[area_size].r - epoint.x, 2) + pow((int)area[area_size].g - epoint.y, 2));
	float distance = abs((int)area[area_size].r - epoint.x) + abs((int)area[area_size].g - epoint.y);
	for (vector<int>::iterator it = rank.begin(); it != rank.end(); ++it) {
		//float tdis = sqrt(pow(area[*it].r - epoint.x, 2) + pow(area[*it].g - epoint.y, 2));
		float tdis = abs(area[*it].r - epoint.x) + abs(area[*it].g - epoint.y);
		if (distance + area[area_size].b < tdis + area[*it].b) {
			rank.insert(it, area_size);
			change = true;
			break;
		}
	}
	if (change == false) {
		rank.push_back(area_size);
	}

	return 0;
}

vector<Vector2i> pathfinder::find(Vector2i & epoint, Vector2i & spoint, vector<Vector2i>& mazes, int WIDTH, int HEIGHT)
{
	vector<Vector2i> output;
	float big, small;
	Vector2i* maze = mazes.data();
	int maze_size = mazes.size();

	rank.clear();
	delete[] area;
	area = new Color[WIDTH * HEIGHT];

	area_size = 0;
	area[area_size] = Color(spoint.x, spoint.y, 0, true);
	rank.push_back(0);

	//while ((int)area.back().r != epoint.x && (int)area.back().g != epoint.y) {
	while (true) {

		int it = rank[0];
		//cout << area.size() << " " << it << endl;
		//cout << area.max_size() << endl;

		bool check[8] = { true, true, true, true, true, true, true, true };
		for (int a = 0; a < maze_size; ++a) {
			if ((maze[a].x == (int)area[it].r && maze[a].y == (int)area[it].g - 1) || (int)area[it].g - 1 < 0) {//up
				check[0] = false;
				check[4] = false;
				check[5] = false;
			}
			if ((maze[a].x == (int)area[it].r - 1 && maze[a].y == (int)area[it].g - 1) || (int)area[it].r - 1 < 0) {//up left
				check[4] = false;
			}
			if ((maze[a].x == (int)area[it].r + 1 && maze[a].y == (int)area[it].g - 1) || (int)area[it].r + 1 >= WIDTH) {//up right
				check[5] = false;
			}
			if ((maze[a].x == (int)area[it].r && maze[a].y == (int)area[it].g + 1) || (int)area[it].g + 1 >= HEIGHT) {//down
				check[1] = false;
				check[6] = false;
				check[7] = false;
			}
			if ((maze[a].x == (int)area[it].r - 1 && maze[a].y == (int)area[it].g + 1) || (int)area[it].r - 1 < 0) {//down left
				check[6] = false;
			}
			if ((maze[a].x == (int)area[it].r + 1 && maze[a].y == (int)area[it].g + 1) || (int)area[it].r + 1 >= WIDTH) {//down right
				check[7] = false;
			}
			if ((maze[a].x == (int)area[it].r - 1 && maze[a].y == (int)area[it].g) || (int)area[it].r - 1 < 0) {//left
				check[2] = false;
				check[4] = false;
				check[6] = false;
			}
			if ((maze[a].x == (int)area[it].r + 1 && maze[a].y == (int)area[it].g) || (int)area[it].r + 1 >= WIDTH) {//right
				check[3] = false;
				check[5] = false;
				check[7] = false;
			}
		}
		for (int a = 0; a <= area_size; ++a) {
			if ((int)area[a].r == (int)area[it].r && (int)area[a].g == (int)area[it].g - 1) {//up
				check[0] = false;
			}
			if ((int)area[a].r == (int)area[it].r - 1 && (int)area[a].g == (int)area[it].g - 1) {//up left
				check[4] = false;
			}
			if ((int)area[a].r == (int)area[it].r + 1 && (int)area[a].g == (int)area[it].g - 1) {//up right
				check[5] = false;
			}
			if ((int)area[a].r == (int)area[it].r && (int)area[a].g == (int)area[it].g + 1) {//down
				check[1] = false;
			}
			if ((int)area[a].r == (int)area[it].r - 1 && (int)area[a].g == (int)area[it].g + 1) {//down left
				check[6] = false;
			}
			if ((int)area[a].r == (int)area[it].r + 1 && (int)area[a].g == (int)area[it].g + 1) {//down right
				check[7] = false;
			}
			if ((int)area[a].r == (int)area[it].r - 1 && (int)area[a].g == (int)area[it].g) {//left
				check[2] = false;
			}
			if ((int)area[a].r == (int)area[it].r + 1 && (int)area[a].g == (int)area[it].g) {//right
				check[3] = false;
			}
		}
		area[it].a = false;
		rank.erase(rank.begin());

		if (check[0]) {
			area_size++;
			area[area_size] = Color((int)area[it].r, (int)area[it].g - 1, (int)area[it].b + 1, true);
			sort(big, small, rank.size(), epoint);
		}
		if (check[1]) {
			area_size++;
			area[area_size] = Color((int)area[it].r, (int)area[it].g + 1, (int)area[it].b + 1, true);
			sort(big, small, rank.size(), epoint);
		}
		if (check[2]) {
			area_size++;
			area[area_size] = Color((int)area[it].r - 1, (int)area[it].g, (int)area[it].b + 1, true);
			sort(big, small, rank.size(), epoint);
		}
		if (check[3]) {
			area_size++;
			area[area_size] = Color((int)area[it].r + 1, (int)area[it].g, (int)area[it].b + 1, true);
			sort(big, small, rank.size(), epoint);
		}

		if (check[4]) {
			area_size++;
			area[area_size] = Color((int)area[it].r - 1, (int)area[it].g - 1, (int)area[it].b + 1, true);
			sort(big, small, rank.size(), epoint);
		}
		if (check[5]) {
			area_size++;
			area[area_size] = Color((int)area[it].r + 1, (int)area[it].g - 1, (int)area[it].b + 1, true);
			sort(big, small, rank.size(), epoint);
		}
		if (check[6]) {
			area_size++;
			area[area_size] = Color((int)area[it].r - 1, (int)area[it].g + 1, (int)area[it].b + 1, true);
			sort(big, small, rank.size(), epoint);
		}
		if (check[7]) {
			area_size++;
			area[area_size] = Color((int)area[it].r + 1, (int)area[it].g + 1, (int)area[it].b + 1, true);
			sort(big, small, rank.size(), epoint);
		}
		//cout << (int)area[rank.front()].r << " " << (int)area[rank.front()].g << endl;

		if (rank.empty()) {
			break;
		} else if ((int)area[rank.front()].r == epoint.x && (int)area[rank.front()].g == epoint.y) {
			break;
		}
	}
	//cout << (int)area[rank.front()].r << " " << (int)area[rank.front()].g << endl;

	int x, y, pick = 0;
	int distance, conc;
	Vector2i failsafe[2], prev = Vector2i(-1, -1);

	output.push_back(epoint);
	//distance = sqrt(pow(output.back().x - spoint.x, 2) + pow(output.back().y - spoint.y, 2));
	distance = abs(output.back().x - spoint.x) + abs(output.back().y - spoint.y);
	conc = area[rank.front()].b;
	x = epoint.x;
	y = epoint.y;
	while (output.back() != spoint) {
		for (int i = 0; i <= area_size; ++i) {
			//cout << (int)area[i].b <<" "<< (int)area[i].r <<" "<< (int)area[i].g << endl;
			if (prev.x != area[i].r || prev.y != area[i].g) {
				if ((area[i].r == x - 1 && area[i].g == y) || (area[i].r == x + 1 && area[i].g == y) || (area[i].r == x && area[i].g == y - 1) || (area[i].r == x && area[i].g == y + 1)) {
					//distance = sqrt(pow(area[i].r - spoint.x, 2) + pow(area[i].g - spoint.y, 2));
					distance = abs(area[i].r - spoint.x) + abs(area[i].g - spoint.y);
					if (area[i].b <= conc) {
						conc = area[i].b;
						pick = i;
						//cout << (int)area[i].r << " " << (int)area[i].g << endl;
					}
				}
			}
		}
		prev = Vector2i(x, y);
		output.push_back(Vector2i((int)area[pick].r, (int)area[pick].g));
		x = output.back().x;
		y = output.back().y;


		if (output.back() == failsafe[0]) {
			break;
		}
		failsafe[0] = failsafe[1];
		failsafe[1] = output.back();
	}

	return output;
}

