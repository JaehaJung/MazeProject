#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "LinkedStack.h"
#include<vector> 
using namespace std;


int r_size = 0;
int c_size = 0;

int R_size() {			//열 개수
	ifstream fin;
	fin.open("test.txt"); // 파일 open
	char c;
	int count = -1;
	while (true)
	{
		fin.get(c);
		if (fin.fail())
		{
			break;
		}
		if (c == '{') {	 // '{' 개수 -1로 계산
			{
				count++;
			}
		}
	}
	return count;
	fin.close();
}

int C_size() {		//행 개수
	ifstream fin;
	fin.open("test.txt"); // 파일 open
	char c;
	int count = 0;
	while (true)
	{

		fin.get(c);
		if (fin.fail())
		{
			break;
		}
		if (c == '0' || c == '1' || c == 'x' || c == 'e') {	// 전체 개수에서 열 개수 나누어서 계산
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
	r_size = R_size(); //행 개수
	c_size = C_size() / r_size; // 열 개수
	vector< vector<int>> maze(r_size, vector<int>(c_size, 0));

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
				col++; if (col == c_size) { col = 0; row++; } // 0이나 1값을 받을 때 마다 col 값을 증가시키고 다음 열로 넘어가야 하면 col값 증가
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
			printf("미로 탐색 성공");
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
	printf("미로 탐색 실패");
}