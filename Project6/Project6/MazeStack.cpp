#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "LinkedStack.h"
#include<vector> 
using namespace std;


int r_size = 0;
int c_size = 0;

int R_size() {			//�� ����
	ifstream fin;
	fin.open("test.txt"); // ���� open
	char c;
	int count = -1;
	while (true)
	{
		fin.get(c);
		if (fin.fail())
		{
			break;
		}
		if (c == '{') {	 // '{' ���� -1�� ���
			{
				count++;
			}
		}
	}
	return count;
	fin.close();
}

int C_size() {		//�� ����
	ifstream fin;
	fin.open("test.txt"); // ���� open
	char c;
	int count = 0;
	while (true)
	{

		fin.get(c);
		if (fin.fail())
		{
			break;
		}
		if (c == '0' || c == '1' || c == 'x' || c == 'e') {	// ��ü �������� �� ���� ����� ���
			{
				count++;
			}
		}
	}
	return count;
	fin.close();
}

bool validLoc(int r, int c, int maze[][])
{
	if (r < 0 || c < 0 || r >= r_size || c >= c_size) return false;
	else return maze[r][c] == '0' || maze[r][c] == 'x';
}


void main() {
	r_size = R_size(); //�� ����
	c_size = C_size() / r_size; // �� ����
	vector< vector<int>> maze(r_size, vector<int>(c_size, 0));

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
				col++; if (col == c_size) { col = 0; row++; } // 0�̳� 1���� ���� �� ���� col ���� ������Ű�� ���� ���� �Ѿ�� �ϸ� col�� ����
			}
		}
	}
	fin.close();


	for (int i = 0; i < r_size; i++) {
		for (int j = 0; j < c_size; j++) {
			cout << (char)maze[i][j];
		}
		printf("\n");
	}

	LinkedStack stack;
	Node entry(1, 0);
	stack.push(new Node(1, 0));

	while (!stack.isEmpty())
	{
		Node* here = stack.top;
		stack.pop();

		int r = here->row;
		int c = here->col;
		printf("(%d, %d) ", r, c);

		if (maze[r][c] == 'x') {
			printf("�̷� Ž�� ����");
			return;
		}
		else {
			maze[r][c] = '.';
			if (validLoc(r - 1, c, maze[r][c])) stack.push(new Node(r - 1, c));
			if (validLoc(r + 1, c, maze[r][c])) stack.push(new Node(r + 1, c));
			if (validLoc(r, c - 1, maze[r][c])) stack.push(new Node(r, c - 1));
			if (validLoc(r, c + 1, maze[r][c])) stack.push(new Node(r, c + 1));
		}
	}
	printf("�̷� Ž�� ����");
}