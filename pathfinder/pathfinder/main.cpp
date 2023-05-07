#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include "pathfinder.h"
#include <filesystem>
#include <fstream>
#include <sstream>

using namespace std;
using namespace sf;
namespace fs = filesystem;

Event event;

const int WIDTH = 20;
const int HEIGHT = 20;

int area[HEIGHT][WIDTH];

pathfinder path;

int main()
{
	RenderWindow window(sf::VideoMode(WIDTH*25, HEIGHT*25), "path", Style::Close);
	window.setFramerateLimit(60);
	Clock clock;
	Vector2i position = sf::Mouse::getPosition(window);

	Vector2i spoint, epoint;
	spoint = Vector2i(1, 1);
	epoint = Vector2i(18, 18);
	vector<Vector2i> maze;

	RectangleShape spot[HEIGHT+1][WIDTH+1];
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			spot[y][x].setSize(Vector2f(25,25));
			spot[y][x].setPosition(x * 25, y * 25);
			spot[y][x].setFillColor(Color(0, 0, 0));
		}
	}

	clock.restart();
	vector<Vector2i> dir = path.find(spoint, epoint, maze, WIDTH, HEIGHT);
	cout << clock.getElapsedTime().asMilliseconds() << endl;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		position = sf::Mouse::getPosition(window);

		if (position.x/25 >= 0 && position.x/25 < WIDTH && position.y/25 >= 0 && position.y/25 < HEIGHT) {
			if (Mouse::isButtonPressed(Mouse::Left) && window.hasFocus()) {
				bool chidk = true;
				for (int i = 0; i < maze.size(); ++i) {
					if (maze[i].x == position.x / 25 && maze[i].y == position.y / 25) {
						chidk = false;
					}
				}
				if (chidk) {
					maze.push_back(position / 25);
				}
				clock.restart();
				dir = path.find(spoint, epoint, maze, WIDTH, HEIGHT);
				cout << clock.getElapsedTime().asMicroseconds() << endl;
			}
			else if (Mouse::isButtonPressed(Mouse::Right) && window.hasFocus()) {
				for (int i = 0; i < maze.size(); ++i) {
					if (maze[i].x == position.x / 25 && maze[i].y == position.y / 25) {
						maze.erase(maze.begin() + i);
						i = 0;
					}
				}
				clock.restart();
				dir = path.find(spoint, epoint, maze, WIDTH, HEIGHT);
				cout << clock.getElapsedTime().asMicroseconds() << endl;
			}
		}

		for (int i = 0; i <= path.area_size; ++i) {
			if (path.area[i].a) {
				spot[path.area[i].g][path.area[i].r].setFillColor(Color(0, 255, 0));
			}
			else {
				spot[path.area[i].g][path.area[i].r].setFillColor(Color(0, 0, path.area[i].b * 10));
			}
			window.draw(spot[path.area[i].g][path.area[i].r]);
		}
		for (vector<Vector2i>::iterator it = dir.begin(); it != dir.end(); ++it) {
			spot[it->y][it->x].setFillColor(Color(255, 0, 0));
			window.draw(spot[it->y][it->x]);
		}
		for (int i = 0; i < maze.size(); ++i) {
			spot[maze[i].y][maze[i].x].setFillColor(Color::White);
			window.draw(spot[maze[i].y][maze[i].x]);
		}
		window.display();
		window.clear();
	}

	return 0;
}