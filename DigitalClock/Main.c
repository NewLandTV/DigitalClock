#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#pragma warning(disable:4996)

// 0 ~ 9까지 출력할 정보
char* digits[10][5][4] =
{
	{
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "■", "■", "■" }
	},
	{
		{ "  ", "  ", "  ", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "  ", "  ", "  ", "■" }
	},
	{
		{ "■", "■", "■", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "  " },
		{ "■", "■", "■", "■" }
	},
	{
		{ "■", "■", "■", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "■", "■", "■", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "■", "■", "■", "■" }
	},
	{
		{ "■", "  ", "  ", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "■", "■", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "  ", "  ", "  ", "■" }
	},
	{
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "  " },
		{ "■", "■", "■", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "■", "■", "■", "■" }
	},
	{
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "  " },
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "■", "■", "■" }
	},
	{
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "  ", "  ", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "  ", "  ", "  ", "■" }
	},
	{
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "■", "■", "■" }
	},
	{
		{ "■", "■", "■", "■" },
		{ "■", "  ", "  ", "■" },
		{ "■", "■", "■", "■" },
		{ "  ", "  ", "  ", "■" },
		{ "■", "■", "■", "■" }
	},
};

// 시 분 초를 출력할 x좌표
int sx[6] =
{
	0,
	10,
	24,
	34,
	48,
	58
};

char* colons[5] =
{
	"  ", "●", "  ", "●", "  "
};

char* colons2[5] =
{
	"  ", "○", "  ", "○", "  "
};

// 콜론을 출력할 x좌표
int sx2[6] =
{
	20,
	44
};

void gotoxy(int x, int y)
{
	COORD pos =
	{
		x,
		y
	};

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// dn자리에 정수 n을 출력하는 함수
void DrawNum(int dn, int n)
{
	int x, y;

	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 4; x++)
		{
			gotoxy(sx[dn] + x * 2, y);
			printf("%s", digits[n][y][x]);
		}

		printf("\n");
	}
}

// 콜론을 출력하는 함수. n이 0이면 시와 분사이, 1이면 분과 초사이
void DrawColon(int n, int off)
{
	int y = 0;

	for (y = 0; y < 5; y++)
	{
		gotoxy(sx2[n], y);

		if (off == 0)
		{
			printf("%s\n", colons2[y]);
		}
		else
		{
			printf("%s\n", colons[y]);
		}
	}
}

// 시간을 출력하는 함수
void DrawTime(int h, int m, int s)
{
	DrawNum(0, h / 10);
	DrawNum(1, h % 10);
	DrawNum(2, m / 10);
	DrawNum(3, m % 10);
	DrawNum(4, s / 10);
	DrawNum(5, s % 10);
}

// 콜론 출력 업데이트
void UpdateColon(int s)
{
	DrawColon(0, s % 2);
	DrawColon(1, s % 2);
}

int main(void)
{
	time_t now, before;

	struct tm nt;

	now = before = time(0);

	localtime_s(&nt, &now);
	UpdateColon(nt.tm_sec);
	DrawTime(nt.tm_hour, nt.tm_min, nt.tm_sec);

	while (kbhit() == 0)
	{
		now = time(0);

		if (now != before)
		{
			before = now;

			localtime_s(&nt, &now);
			UpdateColon(nt.tm_sec);
			DrawTime(nt.tm_hour, nt.tm_min, nt.tm_sec);
		}
	}

	return 0;
}