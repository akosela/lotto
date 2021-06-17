/* Lotto game.
   Copyright (C) 2021 Andy Kosela <akosela@andykosela.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301 USA.  */ 
   
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CASH	40
#define MAX	49.0
#define RAND	1 + (int)(MAX * random() / (RAND_MAX + 1.0))

int game(int *, int *);
int generate(int *);
int intro(int *);
int play(int *, int *);

int generate(int *lotto)
{
	int i, j, number;

	for(i = 0; i < 6; i++)
		lotto[i] = 0;

	for(i = 0; i < 6; i++) {
		number = RAND;
		lotto[i] = number;

		/* Eliminate duplicates */
		for(j = 0; j < i; j++) {
			if (number == lotto[j]) {
				number = RAND;
				lotto[j] = number;
			}
		}
	}
	printf("\n");
}

int game(int *lotto, int *p_budget)
{
	int a, i, j, win;
	unsigned int hit[6], win2[6];
	win = 0;

	for(i = 0; i < 6; i++)
		win2[i] = 0;

	printf("Choose six numbers between 1 and 49:\n");
	(*p_budget)--;
	for(i = 0; i < 6; i++) {
		scanf("%d", &hit[i]);
		while (hit[i] < 1 || hit[i] > 49) {
			printf("Number out of range\n");
			scanf("%d", &hit[i]);
		}

		for(j = 0; j < i; j++) {
			while (hit[i] == hit[j]) {
				printf("Duplicate number selected\n");
				scanf("%d", &hit[i]);
				while (hit[i] < 1 || hit[i] > 49) {
					printf("Number out of range\n");
					scanf("%d", &hit[i]);
				}
			}
		}
		
		/* Check winning numbers */
		for(j = 0; j < 6; j++) {
			if (lotto[j] == hit[i]) {
				win2[j] = lotto[j];
				win++;
			}
		}
	}

	printf("\n");

	/* Sort and print lotto numbers */
	printf("Winning numbers: ");
	for(i = 0; i < 6; i++) {
		/* Sort in ascending order */
		for(j = i + 1; j < 6; j++) {
			if (win2[i] > win2[j]) {
				a = win2[i];
				win2[i] = win2[j];
				win2[j] = a;
			}
			if (lotto[i] > lotto[j]) {
				a = lotto[i];
				lotto[i] = lotto[j];
				lotto[j] = a;
			}
		}
		printf("%d ", lotto[i]);
	}
	printf("\n");
	for(i = 0; i < 6; i++) {
		if (win2[i] > 0)
			printf("%d ", win2[i]);
	}
	printf("\n");

	switch (win) {
	case 0:
		break;
	case 1:
		printf("One number!\n");
		break;
	case 2:
		printf("Two numbers!\n");
		break;
	case 3:
		printf("Three numbers!\n");
		printf("You won: $10\n");
		*p_budget += 10;
		break;
	case 4:
		printf("Four numbers!\n");
		printf("You won: $100\n");
		*p_budget += 100;
		break;
	case 5:
		printf("Five numbers!\n");
		printf("You won: $1000\n");
		*p_budget += 1000;
		break;
	case 6:
		printf("JACKPOT!\n");
		printf("You won: $1000000\n");
		*p_budget += 1000000;
		break;
	}
}

int play(int *lotto, int *p_budget)
{
	unsigned int seed = time(NULL);
	srandom(seed);
	generate(lotto);
	game(lotto, p_budget);
}

int intro(int *p_budget)
{
	printf("Welcome to the game of LOTTO.\n");
	printf("Your initial budget is $%d.\n", *p_budget);
	printf("One game costs $1.\n");
}

int main()
{
	int lotto[6], a, i, j, budget;
	char c;
	int *p_budget;

	/* Initial budget */
	budget = CASH;
	p_budget = &budget;

	intro(p_budget);
	play(lotto, p_budget);

	/* Main game loop */
	while (1) {
		if (budget == 0) {
			printf("You don't have any more money!\n");
			break;
		}
		printf("\nYou have: $%d\n", *p_budget);
		printf("Do you want to play one more time? [y] ");
		c = getchar();
		c = getchar();
		if (c == 'y' || c == 'Y' || c == '\n') {
			play(lotto, p_budget);
		} else {
			break;
		}
	}

	printf("End of game.\n");
	return 0;
}
