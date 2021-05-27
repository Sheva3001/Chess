#pragma once
#include <iostream>
using namespace std;

struct Pos {
	int x = 0;
	int y = 0;
	bool operator == (const Pos& obj) const {
		return this->x == obj.x && this->y == obj.y;
	}
	bool operator != (const Pos& obj) const {
		return this->x != obj.x || this->y != obj.y;
	}
};

class Chess {
	int size;
	int** chessBoard;
public:
	Chess(int n);
	Chess(int n, int friendsCount, Pos* friends, int enemiesCount, Pos* enemies);
	~Chess();
	void backtracking(Pos& now, Pos& finish, int& way, int& minWay, string& lastMotion, int**& chessBoard);
	int Backtracking(Pos now, Pos finish);
	void print();
};