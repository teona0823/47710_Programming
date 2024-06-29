#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

void print_center(char* text); // 가운데 정렬, 줄바꿈 없음
void print_centern(char* text); // 가운데 정렬, 줄바꿈 1회
void print_centernn(char* text); // 가운데 정렬, 줄바꿈 2회
void print_title(); // 제목 출력
void set_diff(); // 난이도 선택메뉴 출력
void print_menu(); // 메인메뉴 출력
void print_diff(); // 현재 난이도 출력
void int_to_char(char show[][3], int board[][3]); // 보드에서 1값을 'O' 표시, 2값을 'X' 표시
void print_board(char show[][3]); // 보드 출력
int check(int arr[], int n); // 중복 확인
void print_ai(); // AI 차례일때 출력
int minimax(int arr[][3], int depth, int aiturn); // minimax 알고리즘
int ai_turn(int arr[][3], int num[], int n); // AI 수 두기
int win(int arr[][3]); // 게임 끝났는지 확인 -> 끝났다면 이긴 사람 숫자 리턴, 아니면 0 리턴
void over(int n); // 게임 결과 출력

int vic = 0; // 승리 횟수
int def = 0; // 패배 횟수
int drw = 0; // 무승부 횟수
int diff; // 난이도 변수

/*
<용어 설명>
귀: 네 가장자리. 숫자로 1, 3, 7, 9.
변: 숫자로 2, 4, 6, 8.
중앙: 가운데. 숫자로 5.

<선공 필승법>
첫 수를 귀에 둔 상태에서 상대의 응수가 변일 때, 두 번째 수는 중앙에, 세 번째 수는 귀에 둔다.
첫 수를 귀에 둔 상태에서 상대의 응수가 이웃한 귀일 때, 두 번재 수는 첫 번째 수와 인접하지만 상대의 수와 인접하지 않은 변에 둔다.
첫 수를 귀에 둔 상태에서 상대의 응수가 마주보는 귀일 때, 두 번째 수는 귀에, 세 번째 수는 중앙에 둔다.
첫 수를 변에 둔 상태에서 상대의 응수가 이웃한 변일 때, 두 번째 수는 중앙에, 세 번째 수는 이웃한 귀에 둔다.
첫 수를 변에 둔 상태에서 상대의 응수가 인접하지 않은 귀일 때, 두 번째 수는 첫 번째 수와 인접하고 상대의 수와 이웃한 귀에 두고, 세 번째 수는 중앙에 둔다.
첫 수를 중앙에 둔 상태에서 상대의 응수가 변일 때, 두 번째 수는 귀에, 세 번째 수는 두 번째 수와 인접한 변에 두거나 상대의 공격을 막는다.

<후공 필승법>
상대가 첫 수를 변에 두고 나의 응수가 마주보는 변일 때, 상대가 무리하게 공격하려 하면 1/4의 확률로 이기고 3/4의 확률로 무승부가 된다.
*/

int main()
{
	int cmd;
	char command[10];
	char difficulty[10];
	int board[3][3] = { 0 };
	char show[3][3];
	char enter[10];
	int num[9] = { 0 };
	int cnt = 0;

	while (1)
	{
		set_diff();
		gets(difficulty);

		diff = atoi(difficulty);

		if ((strlen(difficulty) == 1) && (diff >= 1 && diff <= 3)) break;
		if (strcmp(difficulty, "0") == 0) exit(1);

		print_center("Please enter a number from 1, 2, or 3.");
		Sleep(1000);
		system("cls");
	}

	system("cls");
	
	while (1)
	{
		print_menu();
		gets(command);

		cmd = atoi(command);

		if ((strlen(command) == 1) && (cmd == 1 || cmd == 2)) break;
		if (strcmp(command, "0") == 0) exit(1);
		
		print_center("Please enter a number from 1 or 2.");
		Sleep(1000);
		system("cls");
	}

	system("cls");

	for (int i = 0; i < 10; i++)
	{
		print_title();

		int_to_char(board, show);
		print_board(show);

		if (win(board) == 0)
		{
			if ((i % 2 == cmd - 1) && i != 9)
			{
				printf("\n");
				print_center("Your Turn: ");
				gets(enter);

				int enter1 = atoi(enter);

				if (!(enter1 >= 1 && enter1 <= 9) || strlen(enter) != 1) // 1 ~ 9 외의 값 입력 시
				{
					printf("\n");
					print_center("Please enter a number in range 1 ~ 9.");
					Sleep(1000);
					i--;
					system("cls");
				}

				else if (!check(num, enter1)) // 중복되는 값 입력 시
				{
					printf("\n");
					print_center("Can't put here!");
					Sleep(1000);
					i--;
					system("cls");
				}

				else
				{
					int value_i = (enter1 - 1) / 3;
					int value_j = (enter1 - 1) % 3;

					board[value_i][value_j] = 1;

					num[cnt++] = enter1;
					system("cls");
				}
			}

			else if (i != 9)
			{
				printf("\n");
				print_ai();

				int enter2 = ai_turn(board, num, i);

				int value_i = (enter2 - 1) / 3;
				int value_j = (enter2 - 1) % 3;

				board[value_i][value_j] = 2;

				num[cnt++] = enter2;

				system("cls");
			}

			else
				over(0);
		}

		else
			over(win(board));
	}

	return 0;
}

void print_center(char* text) // 가운데 정렬, 줄바꿈 없음
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int len = strlen(text);

	int padding = (width - len) / 2;

	for (int i = 0; i < padding; i++)
		printf(" ");

	printf("%s", text);
}

void print_centern(char* text) // 가운데 정렬, 줄바꿈 1회
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int len = strlen(text);

	int padding = (width - len) / 2;

	for (int i = 0; i < padding; i++)
		printf(" ");

	printf("%s\n", text);
}

void print_centernn(char* text) // 가운데 정렬, 줄바꿈 2회
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int len = strlen(text);

	int padding = (width - len) / 2;

	for (int i = 0; i < padding; i++)
		printf(" ");

	printf("%s\n\n", text);
}

void print_title() // 제목 출력
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	printf("\n");
	print_centernn("### Tic - Tac - Toe ###");
	print_centernn("Game by. Bomin Moon, 20232759");
	print_centernn("Player 1 [O]: Human, Player 2 [X]: Computer");
	print_centernn("Ver. 3.61 (Final)");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int j = 0; j < (width - 29) / 2; j++)
		printf(" ");

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("%d ", vic);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("Victory / ");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("%d ", def);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("Defeat / ");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("%d ", drw);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("Draw\n\n");
}

void set_diff() // 난이도 선택메뉴 출력
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	print_title();

	print_centernn("Select Difficulty:");

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	print_centern("1. Easy");
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	print_centern("2. Normal");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	print_centern("3. Hard");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	print_centernn("0. Exit Game");

	print_center("Enter Command: ");
}

void print_menu() // 메인메뉴 출력
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	print_title();

	print_diff();

	print_centernn("Play First? or Second?");

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
	print_centern("1. Play First");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	print_centern("2. Play Second");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	print_centernn("0. Exit Game");

	print_center("Enter Command: ");
}

void print_diff() // 현재 난이도 출력
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	for (int j = 0; j < (width - 17) / 2; j++)
		printf(" ");
	printf("Difficulty: ");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (diff)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("Easy\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		break;

	case 2:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("Normal\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		break;

	default:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("Hard\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		break;
	}
}

void int_to_char(int board[][3], char show[][3]) // 보드에서 1값을 'O' 표시, 2값을 'X' 표시
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (board[i][j])
			{
			case 1:
				show[i][j] = 'O';
				break;
			case 2:
				show[i][j] = 'X';
				break;
			default:
				show[i][j] = ' ';
				break;
			}
		}
	}
}

void print_board(char show[][3]) // 보드 출력
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	print_diff();

	for (int i = 0; i < 7; i++)
	{
		if (i % 2 == 0)
			print_centern("+---+---+---+");
		else
		{
			for (int j = 0; j < (width - 13) / 2; j++)
				printf(" ");
			switch (diff)
			{
			case 1:
				for (int k = 0; k < 3; k++)
				{
					printf("|");
					if (show[i / 2][k] == 'X')
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					printf(" %c ", show[i / 2][k]);
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				printf("|\n");

				break;

			case 2:
				for (int k = 0; k < 3; k++)
				{
					printf("|");
					if (show[i / 2][k] == 'X')
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf(" %c ", show[i / 2][k]);
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				printf("|\n");

				break;

			default:
				for (int k = 0; k < 3; k++)
				{
					printf("|");
					if (show[i / 2][k] == 'X')
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" %c ", show[i / 2][k]);
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				printf("|\n");

				break;
			}
		}
	}
}

int check(int arr[], int n) // 중복 확인
{
	for (int i = 0; i < 9; i++)
	{
		if (arr[i] == n)
			return 0;
	}

	return 1;
}

void print_ai() // AI 차례일때 출력
{
	printf("\n");
	print_center("AI Calculating...");
	Sleep(1000);
}

int minimax(int arr[][3], int depth, int aiturn)
{
	if (aiturn)
	{
		int best = -1000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (arr[i][j] == 0)
				{
					arr[i][j] = 2;
					best = best > minimax(arr, depth + 1, 0) ? best : minimax(arr, depth + 1, 0);
					arr[i][j] = 0;
				}
			}
		}
		return best;
	}
}

int ai_turn(int arr[][3], int num[], int n) // AI 수 두기
{
	int result;
	srand(time(NULL));

	if (diff >= 2) // 난이도가 Noraml 또는 Hard인 경우에만 해당. (공격 & 방어)
	{
		for (int i = 2; i >= 1; i--)
		{
			for (int j = 0; j < 3; j++)
			{
				if (arr[j][0] == i && arr[j][1] == i && arr[j][2] == 0)
					return j * 3 + 3;
				if (arr[j][0] == i && arr[j][2] == i && arr[j][1] == 0)
					return j * 3 + 2;
				if (arr[j][1] == i && arr[j][2] == i && arr[j][0] == 0)
					return j * 3 + 1;

				if (arr[0][j] == i && arr[1][j] == i && arr[2][j] == 0)
					return 7 + j;
				if (arr[0][j] == i && arr[2][j] == i && arr[1][j] == 0)
					return 4 + j;
				if (arr[1][j] == i && arr[2][j] == i && arr[0][j] == 0)
					return 1 + j;

				if (arr[0][0] == i && arr[1][1] == i && arr[2][2] == 0)
					return 9;
				if (arr[0][0] == i && arr[2][2] == i && arr[1][1] == 0)
					return 5;
				if (arr[1][1] == i && arr[2][2] == i && arr[0][0] == 0)
					return 1;

				if (arr[0][2] == i && arr[1][1] == i && arr[2][0] == 0)
					return 7;
				if (arr[0][2] == i && arr[2][0] == i && arr[1][1] == 0)
					return 5;
				if (arr[1][1] == i && arr[2][0] == i && arr[0][2] == 0)
					return 3;
			}
		}
	}

	if (diff == 3) // 난이도가 Hard인 경우에만 해당. (필승법과 minimax 알고리즘 사용)
	{
		if (n == 0) // 첫 수를 귀에 두기.
		{
			do
				result = rand() % 5 + 1;
			while (result == 3);

			return 2 * result - 1;
		}

		if ((n == 1 || n == 2)) // 상대의 첫 수에 따라
		{
			if (arr[1][1] == 0) // 상대가 첫 수를 중앙이 아닌 곳에 두었으면 다음 수를 중앙에,
				return 5;
			else // 상대가 중앙에 두었으면 다음 수를 귀에 두기.
			{
				do
					result = rand() % 5 + 1;
				while (!check(num, 2 * result - 1));

				return 2 * result - 1;
			}
		}

		int value = -1000;
		int best = -1;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (arr[i][j] == 0)
				{
					arr[i][j] = 2;
					int move = minimax(arr, 0, 0);
					arr[i][j] = 0;

					if (move > value)
					{
						best = i * 3 + j + 1;
						value = move;
					}
				}
			}
		}

		return best;
	}

	do // 위의 if문 중 만족하는 조건이 없다면 기존 수와 겹치지 않는 곳 중 하나에 랜덤하게 둔다.
		result = rand() % 9 + 1;
	while (!check(num, result));

	return result;
}

int win(int arr[][3]) // 게임 끝났는지 확인 -> 끝났다면 이긴 쪽 숫자 리턴, 아니면 0 리턴
{
	for (int i = 1; i <= 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (arr[j][0] == i && arr[j][1] == i && arr[j][2] == i)
				return i;
			if (arr[0][j] == i && arr[1][j] == i && arr[2][j] == i)
				return i;
		}

		if (arr[0][0] == i && arr[1][1] == i && arr[2][2] == i)
			return i;
		if (arr[0][2] == i && arr[1][1] == i && arr[2][0] == i)
			return i;
	}

	return 0;
}

void over(int n) // 게임 종료화면 출력
{
	printf("\n");
	print_centernn("!! GAME OVER !!");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (n)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		print_center("VICTORY!");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		vic++;
		break;

	case 2:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		print_center("DEFEAT!");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		def++;
		break;

	default:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		print_center("DRAW!");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		drw++;
		break;
	}

	Sleep(3000);
	system("cls");
	main();
}