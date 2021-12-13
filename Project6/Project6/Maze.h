#include <iostream>
#include <fstream>
#include <string> 
#include "LinkedQueue.h"
#include "LinkedStack.h"
using namespace std;

class Maze {
	int r_size;
	int c_size;
	int r;
	int c;
	int num1, num2, sr[50], sc[50], qr[100], qc[100];
	char** maze;
	//int* sr, * sc, * qr, * qc;
public:
	Maze() { r_size = 0; c_size = 0; r = 0; c = 0; }
	~Maze() { }
	void R_size() {			//열 개수
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
		r_size = count;
		fin.close();
	}

	void C_size() {		//행 개수
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
		c_size = count / r_size;
		fin.close();
	}

	bool validLoc(int r, int c)
	{
		if (r < 0 || c < 0 || r >= r_size || c >= c_size) return false;
		else return maze[r][c] == '0' || maze[r][c] == 'x';
	}

	void init()
	{
		maze = new char* [r_size];
		for (int i = 0; i < r_size; i++) {
			maze[i] = new char[c_size];
		}
	}

	void reset()
	{
		if (maze != NULL)
		{
			for (int i = 0; i < r_size; i++)
				delete[]maze[i];
			delete[]maze;
		}
	}

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
					col++; if (col == c_size) { col = 0; row++; } // 0이나 1값을 받을 때 마다 col 값을 증가시키고 다음 열로 넘어가야 하면 col값 증가
				}
			}
		}
		fin.close();
		return 0;
	}

	void search()
	{
		int ch;
		fileStream();
		show();
		Node* entry = new Node(r, c);
		while (true)
		{
			printf("\n1. Stack, 2. Queue, 3. Quit >> ");
			scanf_s("%d", &ch);
			fileStream();
			if (ch == 1)
			{
				num1 = 0;
				LinkedStack stack;
				stack.push(entry);
				while (!stack.isEmpty())
				{
					Node* here = stack.top;
					stack.pop();

					r = here->row;
					c = here->col;
					here->print();

					sr[num1] = r;
					sc[num1] = c;
					num1++;

					if (maze[r][c] == 'x') {
						break;
					}
					else {
						maze[r][c] = '.';
						if (validLoc(r - 1, c)) stack.push(new Node(r - 1, c));
						if (validLoc(r + 1, c)) stack.push(new Node(r + 1, c));
						if (validLoc(r, c - 1)) stack.push(new Node(r, c - 1));
						if (validLoc(r, c + 1)) stack.push(new Node(r, c + 1));
						show();
					}
				}
				if (maze[r][c] == 'x') {
					printf("\n미로 탐색 성공\n");
					path(1);
				}
				else {
					printf("\n미로 탐색 실패\n");
					path(1);
				}
			}
			else if (ch == 2)
			{
				num2 = 0;
				LinkedQueue queue;
				queue.enqueue(entry);

				while (!queue.isEmpty())
				{
					Node* here = queue.dequeue();

					r = here->row;
					c = here->col;
					here->print();

					qr[num2] = r;
					qc[num2] = c;
					num2++;

					if (maze[r][c] == 'x') {
						break;
					}
					else {
						maze[r][c] = '.';
						if (validLoc(r - 1, c)) queue.enqueue(new Node(r - 1, c));
						if (validLoc(r + 1, c)) queue.enqueue(new Node(r + 1, c));
						if (validLoc(r, c - 1)) queue.enqueue(new Node(r, c - 1));
						if (validLoc(r, c + 1)) queue.enqueue(new Node(r, c + 1));
						show();
					}
				}
				if (maze[r][c] == 'x') {
					printf("\n미로 탐색 성공\n");
					path(2);
				}
				else {
					printf("\n미로 탐색 실패\n");
					path(2);
				}
			}
			else
			{
				path(3);
				reset();
				break;
			}
		}
	}

	void show()
	{
		printf("\n");
		for (int i = 0; i < r_size; i++) {
			for (int j = 0; j < c_size; j++) {
				if (maze[i][j] == 'e')
				{
					r = i;
					c = j;
				}
				if (maze[i][j] == '0')
					cout << "  ";
				else if (maze[i][j] == '1')
					cout << "■";
				else if (maze[i][j] == 'x')
					cout << "★";
				else if (maze[i][j] == 'e')
					cout << "☆";
				else
					cout << "ο";
			}
			printf("\n");
		}
		printf("\n");
	}

	void path(int n)
	{
		if (n == 1) {
			printf("Stack [ %d번 ] ", num1);
			for (int i = 0; i < num1; i++)
				printf("(%d, %d) ", sr[i], sc[i]);
		}
		else if (n == 2) {
			printf("Queue [ %d번 ] ", num2);
			for (int i = 0; i < num2; i++)
				printf("(%d, %d) ", qr[i], qc[i]);
		}
		else {
			printf("Stack [ %d번 ] ", num1);
			for (int i = 0; i < num1; i++)
				printf("(%d, %d) ", sr[i], sc[i]);
			printf("\n\nQueue [ %d번 ] ", num2);
			for (int i = 0; i < num2; i++)
				printf("(%d, %d) ", qr[i], qc[i]);
		}
		printf("\n");
	}
};