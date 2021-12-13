#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "LinkedQueue.h"
using namespace std;

const int maze_size = 6;  //maze 크기 (가로값)
char maze[maze_size][maze_size];

bool fileStream() { //파일 read + 배열에 담기
	ifstream fin;
	fin.open("test.txt"); // 파일 open
	char c;
	int row = 0;
	int col = 0;	//maze배열의 row, col값 초기화
	while (true)
	{
		fin.get(c);
		if (fin.fail())
		{
			break;
		}
		if (c == '0' || c == '1' || c == 'x' || c == 'e') {	// 0은 열린부분, 1은 막힌부분, x는 출구, e는 입구
			{
				maze[row][col] = c;
				col++; if (col == maze_size) { col = 0; row++; } // 0이나 1값을 받을 때 마다 col 값을 증가시키고 다음 열로 넘어가야 하면 col값 증가
			}
		}
	}
	fin.close();
	return 0;
}

bool validLoc(int r, int c)
{
	if (r < 0 || c < 0 || r >= maze_size || c >= maze_size) return false;
	else return maze[r][c] == '0' || maze[r][c] == 'x';
}


void main() {
	fileStream();
	for (int i = 0; i < maze_size; i++) {
		for (int j = 0; j < maze_size; j++) {
			cout << maze[i][j];
		}
		printf("\n");
	}

	LinkedQueue queue;
	Node entry(1, 0);
	queue.enqueue(new Node(1, 0));

	while (!queue.isEmpty())
	{
		Node* here = queue.dequeue();

		int r = here->row;
		int c = here->col;
		printf("(%d, %d) ", r, c);

		if (maze[r][c] == 'x') {
			printf("미로 탐색 성공");
			return;
		}
		else {
			maze[r][c] = '.';
			if (validLoc(r - 1, c)) queue.enqueue(new Node(r - 1, c));
			if (validLoc(r + 1, c)) queue.enqueue(new Node(r + 1, c));
			if (validLoc(r, c - 1)) queue.enqueue(new Node(r, c - 1));
			if (validLoc(r, c + 1)) queue.enqueue(new Node(r, c + 1));
		}
	}
	printf("미로 탐색 실패");
}