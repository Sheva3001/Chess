#include "Chess.h"

Chess::Chess(int n) {
	size = n;
	chessBoard = new int* [size];
	for (int i = 0; i < size; i++)
		chessBoard[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			chessBoard[i][j] = 0;
	// ������ ����� � ��������� � ������
}

Chess::Chess(int n, int friendsCount, Pos* friends, int enemiesCount, Pos* enemies) : Chess(n) {
	// ������� ����� � ��������� � ������
	// ����������� ������ (1)
	for (int i = 0; i < friendsCount; i++)
		chessBoard[friends[i].y][friends[i].x] = 1;
	// ����������� ������ (-1)
	for (int i = 0; i < enemiesCount; i++)
		chessBoard[enemies[i].y][enemies[i].x] = -1;
}

Chess::~Chess() {
	for (int i = 0; i < size; i++)
		delete chessBoard[i];
	delete[]chessBoard;
}

void Chess::backtracking(Pos& now, Pos& finish, int& way, int& minWay, string& lastMotion, int**& chessBoard) {
	// ���� �� ������
	cout << "POSITION: " << now.x << " " << now.y << endl;
	cout << "WAY: " << way << endl;
	this->print();
	//if (now.x == 0 && now.y == 1 && way == 1)
	//	cout << " ";
	if (now == finish) {
		if (way < minWay)
			minWay = way;
	}
	else {// �������� �����
		if (now.y != 0) { //���� ������ �� ����� ����
			if (chessBoard[now.y - 1][now.x] != 1) {// ���� ������ �� �������
				int temp = chessBoard[now.y][now.x]; // �������� �������� �������� ������� � �������
				chessBoard[now.y][now.x] = 1; // �������, ��� �� ����� ����
				now.y -= 1; // ��� �����
				string tlast = lastMotion;
				if (chessBoard[now.y][now.x] == -1 || lastMotion != "top" || lastMotion == "first") { // ���� ������ ��������� ��� ��������� ��� ��� �� ����� ��� ��� ������ ���
					lastMotion = "top";
					way++;
					backtracking(now, finish, way, minWay, lastMotion, chessBoard); // ����, ��� ������� ����, ���������, ��� ������ ����� � ���� ����������� �� ��������, ������������� ��� �������������
					way--;
				}
				else { // ����� ������ �� ������� ���� ��� ������ ����� � ��� ��� ����� ����� ���� � ����� ����������� ������� ������ �� ���� ���, ��� �� �� ����������
					lastMotion = "top";
					backtracking(now, finish, way, minWay, lastMotion, chessBoard);
				}
				lastMotion = tlast;
				now.y += 1; // ���������� �������� ��������
				chessBoard[now.y][now.x] = temp; // ���������� �������� ��������
			}
		} // �������� ������
		if (now.x != size - 1) {
			if (chessBoard[now.y][now.x + 1] != 1) {
				int temp = chessBoard[now.y][now.x];
				chessBoard[now.y][now.x] = 1;
				now.x += 1;
				string tlast = lastMotion;
				if (chessBoard[now.y][now.x] == -1 || lastMotion != "right" || lastMotion == "first") {
					lastMotion = "right";
					way++;
					backtracking(now, finish, way, minWay, lastMotion, chessBoard);
					way--;
				}
				else {
					lastMotion = "right";
					backtracking(now, finish, way, minWay, lastMotion, chessBoard);
				}
				lastMotion = tlast;
				now.x -= 1;
				chessBoard[now.y][now.x] = temp;
			}
		} // �������� ����
		if (now.y != size - 1) {
			if (chessBoard[now.y + 1][now.x] != 1) {
				int temp = chessBoard[now.y][now.x];
				chessBoard[now.y][now.x] = 1;
				now.y += 1;
				string tlast = lastMotion;
				if (chessBoard[now.y][now.x] == -1 || lastMotion != "down" || lastMotion == "first") {
					lastMotion = "down";
					way++;
					backtracking(now, finish, way, minWay, lastMotion, chessBoard);
					way--;
				}
				else {
					lastMotion = "down";
					backtracking(now, finish, way, minWay, lastMotion, chessBoard);
				}
				lastMotion = tlast;
				now.y -= 1;
				chessBoard[now.y][now.x] = temp;
			}
		} // �������� �����
		if (now.x != 0) {
			if (chessBoard[now.y][now.x - 1] != 1) {
				int temp = chessBoard[now.y][now.x];
				chessBoard[now.y][now.x] = 1;
				now.x -= 1;
				string tlast = lastMotion;
				if (chessBoard[now.y][now.x] == -1 || lastMotion != "left" || lastMotion == "first") {
					lastMotion = "left";
					way++;
					backtracking(now, finish, way, minWay, lastMotion, chessBoard);
					way--;
				}
				else {
					lastMotion = "left";
					backtracking(now, finish, way, minWay, lastMotion, chessBoard);
				}
				lastMotion = tlast;
				now.x += 1;
				chessBoard[now.y][now.x] = temp;
			}
		}
	}
}

int Chess::Backtracking(Pos now, Pos finish) {
	int way = 0; int minWay = 1000000; string lastMotion = "first";
	backtracking(now, finish, way, minWay, lastMotion, chessBoard);
	return minWay;
}

void Chess::print() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cout << chessBoard[i][j];
		cout << endl;
	}
}
