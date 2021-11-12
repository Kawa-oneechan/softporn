#pragma once

void putw(const char* str)
{
	int l = (int)strlen(str);
	if (l < COLS)
	{
		puts(str);
		return;
	}
	char *s = (char*)str;
	char *space = strchr(s, ' ');
	int taken = 0;
	int newWidth = 0;
	while (l > 0)
	{
		char *s2 = s;
		newWidth = 0;
		while (s2 < space)
		{
			s2++;
			newWidth++;
		}
		if (taken + newWidth >= COLS - 1)
		{
			putchar('\n');
			taken = 0;
		}
		while (s <= space)
		{
			if (*s == '\n')
			{
				if (taken < COLS)
					putchar(' ');
			}
			else
				putchar(*s);
			s++;
			taken++;
			l--;
		}
		space = strchr(s, ' ');
		if (space == NULL)
			space = s + l;
	}
}

void giveHelp()
{
	clearScreen();
	writeLongMessage(70);
	////writeLongMessage(71);
	////writeLongMessage(72);
	getKey();
	clearScreen();
	printf("\n\n\n\n");
}

void lookAtGraffiti()
{
	if (COLS < 70)
	{
		putw("(You need at least 80 columns to display the graffiti. The password is \"bellybutton\". -- Kawa)");
		return;
	}
	clearScreen();
	writeLongMessage(59, false);
	////writeLongMessage(60);
	////writeLongMessage(61);
	////writeLongMessage(62);
	getKey();
	//clearScreen();
	//printf("\n\n\n\n");
}

void purgatory()
{
	delay(700);
	int door = 0;
loop:
	if (door == 0)
		writeLongMessage(65);
	else
		puts("I'm still here?\n");
	puts("Choose your door: 1, 2, or 3?");
ask:
	putchar('>');
	char k = getOneOf('1', '2', '3');
	int c = k - '0';
	if (c > 0 && c < 4)
	{
		door = (getRandom(3) + c) % 3;
		state.gameEnded = door == 1;
	}
	else
	{
		puts("Just 1, 2, or 3.");
		goto ask;
	}
	if (door == 2)
		goto loop;
	else if (door == 1)
	{
		puts("Guess I'll die.");
		delay(200);
	}
	else if (door == 0)
	{
		puts("\"Congratulations, you get another shot! See you soon!\"");
		delay(200);
	}
}

void bumTellsStory()
{
	puts("He looks at you and starts to speak.");
	delay(400);
	writeLongMessage(39);
	delay(300);
	int i;
	for (i = 0; i < 128; i++)
	{
		for (int j = 0; j < i; j++)
			putchar(' ');
		puts("Like I did!");
	}
	for (i = 0; i < 5; i++)
		puts("");
	delay(500);
	puts("He throws up and gives me back the bottle of wine.");
}

void watchTV()
{
watch:
	writeLongMessage(41 + state.TVChannel);
	printf("Change the channel? >");
	if (getOneOf('Y', 'N', 0) == 'Y')
	{
		puts("*click*");
		state.TVChannel = (state.TVChannel + 1) % 9;
		puts("...");
		goto watch;
	}
}

void wineInTaxi()
{
	writeLongMessage(58);
	delay(500);
	puts("What do I do!?");
	delay(1000);
	puts("The idiot cabbie backs over me and kills me!");
	purgatory();
}

extern bool objectIsCarried(objects object);
void stabSomeone()
{
	if (!objectIsCarried(knife))
	{
		puts("With what, rapier wit?");
		return;
	}
	puts("Okay ya warmonger.");
	delay(1000);
	printf("Parry!");
	delay(500);
	printf(" Thrust!");
	delay(1000);
	puts(" ...and I just got myself.");
	purgatory();
}

void fallingDown()
{
	puts("Aaaaaauuuuuugh!");
	delay(300);
	puts("*SPLAT!*");
	if (state.verb != jump)
	{
		delay(500);
		puts("\n... I should've used a safety rope.");
	}
	purgatory();
}

void playSlots(int* money)
{
	const char slot[5] = { '!', '#', '*', '$', '^' };
	const int slotFigs = 5;
	int x1, x2, x3;
	bool cheat = false;
	char answer = 'Y';
	puts("This will cost $100 each time.");
	do
	{
		printf("You have $%d00. Would you like to play?\n>", *money);
		answer = getOneOf('Y','N','K');
		if (answer == 'K')
		{
			cheat = !cheat;
			answer = 'Y';
		}
		if (answer == 'Y')
		{
			int cx, cy;
			getPos(&cx, &cy);
			for (int i = 0; i < 30; i++)
			{
				x1 = getRandom(slotFigs);
				x2 = getRandom(slotFigs);
				x3 = getRandom(slotFigs);
				if (cheat) x3 = x2 = x1;
				delay(100);
				setPos(cx, cy);
				printf("%c %c %c", slot[x1], slot[x2], slot[x3]);
			}
			puts("");
			if (x1 == x2 && x2 == x3)
			{
				puts("Triples! You win $1500!");
				*money += 15;
			}
			else if (x1 == x2 || x2 == x3 || x1 == x3)
			{
				puts("A pair! You win $300!");
				*money += 3;
			}
			else
			{
				puts("You lose.");
				*money -= 1;
			}
		}
	} while (*money > 0 && answer != 'N');
	puts("");
	if (*money < 1)
	{
		puts("I'm broke! That means death!");
		purgatory();
	}
}

const char* const cardNames[] =
{
	"an Ace", "a 2", "a 3", "a 4", "a 5", "a 6", "a 7",
	"an 8", "a 9", "a 10", "a Jack", "a Queen", "a King"
};

void dealCard(int* y, int* z, int* ac, char** card)
{
	*z = getRandom(13) + 1;
	*y = 0;
	*ac = 0;
	*card = (char*)cardNames[*z - 1];
	if (*z > 10) *z = 10;
	if (*z == 1) *z = 11;
	if (*z == 0) *y = 1;
	if (*z == 11) *ac = 1;
}

void check(int* mi, int* md, int* ad, int* a, int* money, int* dollars, bool* gameOver)
{
	if (*md > 21 && *ad > 0)
	{
		*ad -= 1;
		*md -= 10;
	}
	delay(200);
	printf("The dealer has %d.\n", *md);
	if (*md < 17)
		*a = 6;
	else if (*md > 21 || *mi > *md)
	{
		delay(200);
		puts("You win!");
		*money += *dollars;
		*gameOver = true;
	}
	else if (*mi < *md)
	{
		delay(200);
		puts("You lose!");
		*money -= *dollars;
		*gameOver = true;
	}
	else if (*mi == *md)
	{
		delay(200);
		puts("Tie!");
		*gameOver = true;
	}
}

void checkHit(int* mi, int* md, int* yd, int* ym, int* ad, int* am, int* a, int* money, int* dollars, bool* gameOver)
{
	if (*mi > 21 && *am > 0)
	{
		*am -= 1;
		*mi -= 10;
	}
	delay(200);
	printf("Your total is %d.\n", *mi);
	if (*mi > 21)
	{
		delay(200);
		puts("Busted!");
		*money -= *dollars;
		*gameOver = true;
	}
	else if (*ym == 2 && (*mi == 21))
	{
		delay(200);
		puts("You got a ***BLACKJACK***");
		*money += *dollars + *dollars;
		*gameOver = true;
	}
	else if (*yd == 2 && (*md == 21))
	{
		delay(200);
		puts("The dealer has a ***BLACKJACK***");
		*money += *dollars - *dollars;
		*gameOver = true;
	}
	else
	{
		delay(200);
		printf("Would you like a hit?\n>");
		char answer = getOneOf('Y','N',0);
		if (answer == 'N')
			check(mi, md, ad, a, money, dollars, gameOver);
	}
}

void play21(int* money)
{
	bool answerOkay = false;
	int dollars;
	char dollarString[64];
	char *card;
	char answer = 'Y';
	do
	{
		do
		{
			answerOkay = false;
			printf("You have $%d00. How many would you like to bet?\n>", *money);
			getString(dollarString, 64);
			dollars = atoi(dollarString);
			char *endBit = NULL;
			if (strlen(dollarString) > 2)
				endBit = dollarString + strlen(dollarString) - 2;
			if (dollars <= 0)
				puts("Huh?");
			else if (endBit == NULL || (endBit[0] != '0' || endBit[1] != '0'))
				puts("$100 increments only, please.");
			else if (dollars / 100 > *money)
				puts("You don't have that much.");
			else
				answerOkay = true;
		} while (!answerOkay);
		dollars /= 100;

		int mi = 0;
		int md = 0;
		int yd = 0;
		int ym = 0;
		int ad = 0;
		int am = 0;
		int a = 1;
		int y = 0;
		int z = 0;
		int ac;
		bool gameOver = false;
		do
		{
			dealCard(&y, &z, &ac, &card);
			delay(200);
			switch (a)
			{
			case 1:
			case 3:
			{
				mi += z;
				printf("You're dealt %s.\n", card);
				ym += y;
				am += ac;
				a++;
				break;
			}
			case 2:
			{
				md += z;
				printf("The dealer gets a card down.\n");
				yd += y;
				ad += ac;
				a++;
				break;
			}
			case 4:
			{
				md += z;
				printf("The dealer gets %s.\n", card);
				a = 5;
				ad += ac;
				yd += y;
				checkHit(&mi, &md, &yd, &ym, &ad, &am, &a, money, &dollars, &gameOver);
				break;
			}
			case 5:
			{
				mi += z;
				printf("You get %s.\n", card);
				am += ac;
				checkHit(&mi, &md, &yd, &ym, &ad, &am, &a, money, &dollars, &gameOver);
				break;
			}
			case 6:
			{
				md += z;
				printf("The dealer gets %s.\n", card);
				ad += ac;
				check(&mi, &md, &ad, &a, money, &dollars, &gameOver);
				break;
			}
			}
		} while (!gameOver);
		if (*money < 1)
		{
			puts("You're outta money! So long~");
			purgatory();
		}
		else
		{
			puts("Play again?");
			putchar('>');
			answer = getOneOf('Y', 'N', 0);
		}
	} while (answer == 'Y' && *money > 0);
}

void buyRubber()
{
	strcpy(state.rubberLubricated, "non-lubricated");
	strcpy(state.rubberRibbed, "smooth");
	puts("The man leans over the counter and whispers, \"What color, maaan?\"");
	putchar('>');
	getString(state.rubberColor, 32);
	int i;
	for (i = 0; i < 32; i++)
		state.rubberColor[i] = (char)tolower(state.rubberColor[i]);
	puts("\"And what flavor?\"");
	putchar('>');
	getString(state.rubberFlavor, 32);
	for (i = 0; i < 32; i++)
		state.rubberFlavor[i] = (char)tolower(state.rubberFlavor[i]);
	puts("\"Lubricated?\"");
	putchar('>');
	char yesNo = getOneOf('Y', 'N', 0);
	if (yesNo == 'Y')
		strcpy(state.rubberLubricated, "lubricated");
	puts("\"...Ribbed?\"");
	putchar('>');
	yesNo = getOneOf('Y', 'N', 0);
	if (yesNo == 'Y')
		strcpy(state.rubberRibbed, "ribbed");
	delay(1000);
	printf("Suddenly the clerk yells out, \"Hey everybody! This guy just bought\na %s, %s-flavored, %s, %s rubber!\"\n", state.rubberColor, state.rubberFlavor, state.rubberLubricated, state.rubberRibbed);
	delay(1000);
	puts("\"WHAT A PERVERT!\"");
}

void okay()
{
	puts("Okay.");
}

void _open(bool* objectOpen)
{
	if (*objectOpen)
		puts("It's already open.");
	else
	{
		okay();
		*objectOpen = true;
	}
}

void _close(bool* objectOpen)
{
	if (!*objectOpen)
		puts("It's already closed.");
	else
	{
		okay();
		*objectOpen = false;
	}
}
