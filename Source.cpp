#include <iostream>
#include <fstream>
#include "Chess.h"
using namespace std;

void readFile(ifstream& file, int& n, int& friendsCount, int& enemiesCount, Pos*& friends, Pos*& enemies, Pos& now, Pos& finish) {
	file >> n;
	file >> now.x; file >> now.y;
	file >> finish.x; file >> finish.y;
	file >> friendsCount;
	friends = new Pos[friendsCount];
	for (int i = 0; i < friendsCount; i++) {
		file >> friends[i].x;
		file >> friends[i].y;
	}
	file >> enemiesCount;
	enemies = new Pos[enemiesCount];
	for (int i = 0; i < enemiesCount; i++) {
		file >> enemies[i].x;
		file >> enemies[i].y;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");

	int n = 0; int friendsCount = 0; int enemiesCount = 0; Pos now; Pos finish;
	Pos* friends;
	Pos* enemies;
	ifstream file("file.txt");

	readFile(file, n, friendsCount, enemiesCount, friends, enemies, now, finish);
	Chess A(n, friendsCount, friends, enemiesCount, enemies);
	int count = A.Backtracking(now, finish);
	cout << count;
	return 0;
}