/*
 * =====================================================================================
 *
 *       Filename:  mysl.c
 *
 *    Description:  Some modifications to sl program
 *
 *        Version:  1.1
 *        Created:  Wednesday 30 May 2012 07:22:42  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mehta Sanket Satish, mehtasankets@gmail.com
 *
 * =====================================================================================
 */


#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "mysl.h"

int ACCIDENT  = 0;
int LOGO      = 0;
int FLY       = 0;
int STRING	  = 0;
int COUNTER	  = 0;
int count	  = 2;
char my_string[512];

int my_mvaddstr(int y, int x, char *str)
{
	for ( ; x < 0; ++x, ++str)
		if (*str == '\0')  return ERR;
	for ( ; *str != '\0'; ++str, ++x)
		if (mvaddch(y, x, *str) == ERR)  return ERR;
	return OK;
}

void option(char *str)
{
	extern int ACCIDENT, FLY, LONG;

	while (*str != '\0') {
		switch (*str++) {
			case 'a': ACCIDENT = 1; break;
			case 'F': FLY      = 1; break;
			case 'l': LOGO     = 1; break;
			case 's': STRING   = 2; break;
			case 'c': COUNTER  = 2; break;
			default:                break;
		}
	}
}

void main(int argc, char *argv[])
{
	int x, i;

	for (i = 1; i < argc; ++i) {
		if (*argv[i] == '-') {
			option(argv[i] + 1);
		}
		else if(STRING == 2)
		{
			STRING = 1;
			sprintf(my_string, "%s ", argv[i]);
		}
		else if(COUNTER == 2)
		{
			COUNTER = 1;
			count = atoi(argv[i]);
		}
	}
	if(STRING != 1)
	{
		sprintf(my_string, "SANKET ");
	}	
	initscr();
	signal(SIGINT, SIG_IGN);
	noecho();
	leaveok(stdscr, TRUE);
	scrollok(stdscr, FALSE);
	my_mvaddstr(0, 0, my_string);

	for (x = COLS - 1; ; --x) {
		if (LOGO == 0) {
			if (add_D51(x) == ERR) break;
		} else {
			if (add_sl(x) == ERR) break;
		}
		refresh();
		usleep(50000);
	}
	mvcur(0, COLS - 1, LINES - 1, 0);
	endwin();
}


int add_sl(int x)
{
	static char *sl[LOGOPATTERNS][LOGOHIGHT + 1]
		= {{LOGO1, LOGO2, LOGO3, LOGO4, LWHL11, LWHL12, DELLN},
			{LOGO1, LOGO2, LOGO3, LOGO4, LWHL21, LWHL22, DELLN},
			{LOGO1, LOGO2, LOGO3, LOGO4, LWHL31, LWHL32, DELLN},
			{LOGO1, LOGO2, LOGO3, LOGO4, LWHL41, LWHL42, DELLN},
			{LOGO1, LOGO2, LOGO3, LOGO4, LWHL51, LWHL52, DELLN},
			{LOGO1, LOGO2, LOGO3, LOGO4, LWHL61, LWHL62, DELLN}};

	static char *coal[LOGOHIGHT + 1]
		= {LCOAL1, LCOAL2, LCOAL3, LCOAL4, LCOAL5, LCOAL6, DELLN};

	static char *car[LOGOHIGHT + 1]
		= {LCAR1, LCAR2, LCAR3, LCAR4, LCAR5, LCAR6, DELLN};

	int i, y, py1 = 0, py2 = 0, py3 = 0;

	if (x < - LOGOLENGTH)  return ERR;
	y = LINES / 2 - 3;

	if (FLY == 1) {
		y = (x / 6) + LINES - (COLS / 6) - LOGOHIGHT;
		py1 = 2;  py2 = 4;  py3 = 6;
	}
	for (i = 0; i <= LOGOHIGHT; ++i) {
		my_mvaddstr(y + i, x, sl[(LOGOLENGTH + x) / 3 % LOGOPATTERNS][i]);
		my_mvaddstr(y + i + py1, x + 21, coal[i]);
		my_mvaddstr(y + i + py2, x + 42, car[i]);
		my_mvaddstr(y + i + py3, x + 63, car[i]);
	}
	if (ACCIDENT == 1) {
		add_man(y + 1, x + 14);
		add_man(y + 1 + py2, x + 45);  add_man(y + 1 + py2, x + 53);
		add_man(y + 1 + py3, x + 66);  add_man(y + 1 + py3, x + 74);
	}
	add_smoke(y - 1, x + LOGOFUNNEL);
	return OK;
}


add_D51(int x)
{
	char temp[2048];
	static char *d51[D51PATTERNS][D51HIGHT + 1]
		= {{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7,
			D51WHL11, D51WHL12, D51WHL13, D51DEL},
			{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7,
				D51WHL21, D51WHL22, D51WHL23, D51DEL},
			{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7,
				D51WHL31, D51WHL32, D51WHL33, D51DEL},
			{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7,
				D51WHL41, D51WHL42, D51WHL43, D51DEL},
			{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7,
				D51WHL51, D51WHL52, D51WHL53, D51DEL},
			{D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51STR6, D51STR7,
				D51WHL61, D51WHL62, D51WHL63, D51DEL}};
	static char *coal[D51HIGHT + 1]
		= {COAL01, COAL02, COAL03, COAL04, COAL05,
			COAL06, COAL07, COAL08, COAL09, COAL10, COALDEL};

	int y, i, dy = 0;

	if (x < - D51LENGTH)  return ERR;
	y = LINES / 2 - 5;

	if (FLY == 1) {
		y = (x / 7) + LINES - (COLS / 7) - D51HIGHT;
		dy = 1;
	}

	for (i = 0; i <= D51HIGHT; ++i) {
		my_mvaddstr(y + i, x, d51[(D51LENGTH + x) % D51PATTERNS][i]);		
		int cnt=count;
		strcpy(temp, "");
		while(cnt--)
		{
			strcat(temp, coal[i]);
		}
		my_mvaddstr(y + i + dy, x + 53, temp);
	}
	if (ACCIDENT == 1) {
		add_man(y + 2, x + 43);
		add_man(y + 2, x + 47);
	}
	add_smoke(y - 1, x + D51FUNNEL);
	return OK;
}


int add_man(int y, int x)
{
	static char *man[2][2] = {{"", "(O)"}, {"Help!", "\\O/"}};
	int i;

	for (i = 0; i < 2; ++i) {
		my_mvaddstr(y + i, x, man[(LOGOLENGTH + x) / 12 % 2][i]);
	}
}

char *fill_smoke(char *my_string, int len)
{
	char *temp = (char *)malloc(1024 * sizeof(char));
	strncpy(temp, my_string, len);
	return temp;
}

int add_smoke(int y, int x)
#define SMOKEPTNS	16
{	
	static struct smokes {
		int y, x;
		int ptrn, kind;
	} S[1000];
	static int sum = 0;
	int len = strlen(my_string);
	char temp[128], temp1[128];
	char Spaces[128] = "            ";
	static char *Smoke[2][SMOKEPTNS]
		= {{"(   )", "(    )", "(    )", "(   )", "(  )",
			"(  )" , "( )"   , "( )"   , "()"   , "()"  ,
			"A"    , "A"     , "A"     , "A"    , "A"   ,
			" "                                          },
			{   "AAAAA", "AAAAAA", "AAAAAA", "AAAAA", "AAAA",
				"AAAA" , "AAA"   , "AAA"   , "AA"   , "AA"  ,
				"A"    , "A"     , "A"     , "A"    , "A"   ,
				" "                                          }};
	static char *Eraser[SMOKEPTNS]
		=  {"      ", "       ", "       ", "      ", "     ",
			"     " , "    "   , "    "   , "   "   , "   "  ,
			"  "    , "  "     , "  "     , "  "    , "  "   ,
			" "                                          };
	static int dy[SMOKEPTNS] = { 2,  1, 1, 1, 0, 0, 0, 0, 0, 0,
		0,  0, 0, 0, 0, 0             };
	static int dx[SMOKEPTNS] = {-2, -1, 0, 1, 1, 1, 1, 1, 2, 2,
		2,  2, 2, 3, 3, 3             };
	int i;

	Smoke[0][10] = fill_smoke(my_string, 1);
	Smoke[0][11] = fill_smoke(my_string, 1);
	Smoke[0][12] = fill_smoke(my_string, 1);
	Smoke[0][13] = fill_smoke(my_string, 1);
	Smoke[0][14] = fill_smoke(my_string, 1);

	if(len < 3)
		len = 4;

	Smoke[1][0]  = fill_smoke(my_string, len-2);
	Smoke[1][1]  = fill_smoke(my_string, len);
	Smoke[1][2]  = fill_smoke(my_string, len);
	Smoke[1][3]  = fill_smoke(my_string, len-1);
	Smoke[1][4]  = fill_smoke(my_string, len-2);

	Smoke[1][5]  = fill_smoke(my_string, len-3);
	Smoke[1][6]  = fill_smoke(my_string, 3);
	Smoke[1][7]  = fill_smoke(my_string, 3);
	Smoke[1][8]  = fill_smoke(my_string, 2);
	Smoke[1][9]  = fill_smoke(my_string, 2);

	Smoke[1][10] = fill_smoke(my_string, 1);
	Smoke[1][11] = fill_smoke(my_string, 1);
	Smoke[1][12] = fill_smoke(my_string, 1);
	Smoke[1][13] = fill_smoke(my_string, 1);
	Smoke[1][14] = fill_smoke(my_string, 1);

	if(len < 6)
		len = 7;

	Eraser[0]  = fill_smoke(Spaces, len-2);
	Eraser[1]  = fill_smoke(Spaces, len);
	Eraser[2]  = fill_smoke(Spaces, len);
	Eraser[3]  = fill_smoke(Spaces, len-1);
	Eraser[4]  = fill_smoke(Spaces, len-2);

	Eraser[5]  = fill_smoke(Spaces, len-3);
	Eraser[6]  = fill_smoke(Spaces, 3);
	Eraser[7]  = fill_smoke(Spaces, 3);
	Eraser[8]  = fill_smoke(Spaces, 2);
	Eraser[9]  = fill_smoke(Spaces, 2);

	Eraser[10] = fill_smoke(Spaces, 1);
	Eraser[11] = fill_smoke(Spaces, 1);
	Eraser[12] = fill_smoke(Spaces, 1);
	Eraser[13] = fill_smoke(Spaces, 1);
	Eraser[14] = fill_smoke(Spaces, 1);

	if (x % 4 == 0) {
		for (i = 0; i < sum; ++i) {
			my_mvaddstr(S[i].y, S[i].x, Eraser[S[i].ptrn]);
			S[i].y    -= dy[S[i].ptrn];
			S[i].x    += dx[S[i].ptrn];
			S[i].ptrn += (S[i].ptrn < SMOKEPTNS - 1) ? 1 : 0;
			my_mvaddstr(S[i].y, S[i].x, Smoke[S[i].kind][S[i].ptrn]);
		}
		my_mvaddstr(y, x, Smoke[sum % 2][0]);
		S[sum].y = y;    S[sum].x = x;
		S[sum].ptrn = 0; S[sum].kind = sum % 2;
		sum ++;
	}
}

