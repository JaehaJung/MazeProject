#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "LinkedQueue.h"
using namespace std;

const int maze_size = 6;  //maze ũ�� (���ΰ�)
char maze[maze_size][maze_size];

bool fileStream() { //���� read + �迭�� ���
	ifstream fin;
	fin.open("test.txt"); // ���� open
	char c;
	int row = 0;
	int col = 0;	//maze�迭�� row, col�� �ʱ�ȭ
	while (true)
	{
		fin.get(c);
		if (fin.fail())
		{
			break;
		}
		if (c == '0' || c == '1' || c == 'x' || c == 'e') {	// 0�� �����κ�, 1�� �����κ�, x�� �ⱸ, e�� �Ա�
			{
				maze[row][col] = c;
				col++; if (col == maze_size) { col = 0; row++; } // 0�̳� 1���� ���� �� ���� col ���� ������Ű�� ���� ���� �Ѿ�� �ϸ� col�� ����
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
			printf("�̷� Ž�� ����");
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
	printf("�̷� Ž�� ����");
}