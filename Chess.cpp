#include "Chess.h"

Chess::Chess(int n) {
	size = n;
	chessBoard = new int* [size];
	for (int i = 0; i < size; i++)
		chessBoard[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			chessBoard[i][j] = 0;
	// Создаём доску и заполняем её нулями
}

Chess::Chess(int n, int friendsCount, Pos* friends, int enemiesCount, Pos* enemies) : Chess(n) {
	// Создали доску и заполнили её нулями
	// Расставляем друзей (1)
	for (int i = 0; i < friendsCount; i++)
		chessBoard[friends[i].y][friends[i].x] = 1;
	// Расставляем врагов (-1)
	for (int i = 0; i < enemiesCount; i++)
		chessBoard[enemies[i].y][enemies[i].x] = -1;
}

Chess::~Chess() {
	for (int i = 0; i < size; i++)
		delete chessBoard[i];
	delete[]chessBoard;
}

void Chess::backtracking(Pos& now, Pos& finish, int& way, int& minWay, string& lastMotion, int**& chessBoard) {
	// Если на финише
	cout << "POSITION: " << now.x << " " << now.y << endl;
	cout << "WAY: " << way << endl;
	this->print();
	//if (now.x == 0 && now.y == 1 && way == 1)
	//	cout << " ";
	if (now == finish) {
		if (way < minWay)
			minWay = way;
	}
	else {// Движение вверх
		if (now.y != 0) { //Если вверху не конец поля
			if (chessBoard[now.y - 1][now.x] != 1) {// Если вверху не союзник
				int temp = chessBoard[now.y][now.x]; // Сохраним исходное значение матрицы в позиции
				chessBoard[now.y][now.x] = 1; // Пометим, что мы здесь были
				now.y -= 1; // Ход вверх
				string tlast = lastMotion;
				if (chessBoard[now.y][now.x] == -1 || lastMotion != "top" || lastMotion == "first") { // Если сверху противник ИЛИ последний ход был не вверх ИЛИ это первый ход
					lastMotion = "top";
					way++;
					backtracking(now, finish, way, minWay, lastMotion, chessBoard); // Итак, все условия выше, указывают, что фигура ходит в этом направлении НЕ повторно, следовательно шаг засчитывается
					way--;
				}
				else { // Иначе фигура на прошлом шаге уже ходила вверх и так как ладья может идти в одном направлении сколько угодно за ожин ход, ход мы не прибавляем
					lastMotion = "top";
					backtracking(now, finish, way, minWay, lastMotion, chessBoard);
				}
				lastMotion = tlast;
				now.y += 1; // Возвращаем исходное значение
				chessBoard[now.y][now.x] = temp; // Возвращаем исходное значение
			}
		} // Движение вправо
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
		} // Движение вниз
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
		} // Движение влево
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
