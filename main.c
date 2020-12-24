#include <stdio.h>
#include <stdlib.h> 
#include <Windows.h>
#include <conio.h>
#include <time.h>

typedef struct _POS
{
	int x, y;
}POS;

void gotoxy(int x, int y)
{
	COORD Pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_Map(void)			// printf 로 Map draw 
{
	int i = 0;
	printf("□□□□□□□□□□□□□□□□□□□□");
	for (i = 1; i < 20; i++)
	{
		gotoxy(0, i);
		printf("□");
		gotoxy(19, i);
		printf("□");
	}

	printf("\n");
	printf("□□□□□□□□□□□□□□□□□□□□");
}

void _get_Dir(int *dir)			// keyboard hit 감지하여 Call by ref. 로 방향 받기 구현  
{								// W A S D 로 동작  
	int val = 0;
	if (_kbhit())
	{
		val = _getch();
		switch (val)
		{
		case 'w':
			if (*dir == 3) {
				break;
			}
			*dir = 1;
			break;
		case 'W':
			if (*dir == 3) {
				break;
			}
			*dir = 1;
			break;

		case 'a':
			if (*dir == 4) {
				break;
			}
			*dir = 2;
			break;
		case 'A':
			if (*dir == 4) {
				break;
			}
			*dir = 2;
			break;

		case 's':
			if (*dir == 1) {
				break;
			}
			*dir = 3;
			break;
		case 'S':
			if (*dir == 1) {
				break;
			}
			*dir = 3;
			break;

		case 'd':
			if (*dir == 2) {
				break;
			}
			*dir = 4;
			break;
		case 'D':
			if (*dir == 2) {
				break;
			}
			*dir = 4;
			break;
		}
	}
}

void _draw_Straightness(POS *head, int dir) // struct pointer을 받아와 내부에서 -> 연산하여 Call by ref. 구현
{
	gotoxy(head->x, head->y);

	switch (dir)
	{
	case 1:
		head->y -= 1;
		printf("△");
		break;

	case 2:
		head->x -= 1;
		printf("◁");
		break;

	case 3:
		head->y += 1;
		printf("▽");
		break;

	case 4:
		head->x += 1;
		printf("▷");
		break;
	}
}

void _draw_Tail(POS *head, int len)
{
	static j = 0;
	static POS tail[800];
	int i = 0, k = 0;

	tail[j].x = head->x;
	tail[j].y = head->y;

	j++;

	for (i = (j - len); i < j; i++)
	{
		gotoxy(tail[i - 1].x, tail[i - 1].y);
		printf("⊙");
	}
}

void check_Wall(POS *head)			//  Wall 좌표 부딪히면 over  
{
	int i = 0;

	if ((0 == head->x) || (head->x >= 19) || (head->y == 0) || (head->y >= 20))
	{
		system("cls");
		printf("the end");
		Sleep("3000");
	}
}

void _respawn_Food(POS *prand)
{
	srand(time(NULL));

	prand->x = (rand() % 18) + 1;
	prand->y = (rand() % 18) + 1;
}

int main()
{
	POS phead, prand;			// declare start POS 

	phead.x = 10;
	phead.y = 10;

	prand.x = 15;
	prand.y = 15;

	int dir = 1, len = 3, i, j = 0;

	while (1)
	{
		draw_Map();
		check_Wall(&phead);			// tail collision part should be added

		_get_Dir(&dir);

		_draw_Straightness(&phead, dir);

		_draw_Tail(&phead, len);

		if ((phead.x == prand.x) && (phead.y == prand.y))
		{
			len++;
			_respawn_Food(&prand);
		}

		gotoxy(prand.x, prand.y);
		printf("*");

		Sleep(100);

		system("cls");

		gotoxy(100, 100);
	}

	return 0;
}
