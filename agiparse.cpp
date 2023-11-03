#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#include "metrics.h"

int results[8];
char *dict = NULL;
int dictSize = 0;

void loadDict()
{
	FILE *f = NULL;
#ifdef HAVESAFE
	if (fopen_s(&f, "words.tok", "rb+"))
	{
		printf("Couldn't open dictionary.\n");
		return;
	}
#else
	f = fopen("words.tok", "rb+");
#endif
	if (f == NULL)
	{
		printf("Couldn't open dictionary.\n");
		return;
	}
	fseek(f, 1, SEEK_END);
	dictSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	dict = (char*)malloc(dictSize);
	if (dict == NULL)
	{
		printf("Couldn't allocate dictionary.\n");
		return;
	}
	fread(dict, dictSize, 1, f);
	fclose(f);
}

void parse(char* input)
{
	if (dict == NULL)
		loadDict();

	for (int i = 0; i < 8; i++)
		results[i] = -1;
	int numRes = 0;

	int cursor = 0;
	int inputLen = (int)strlen(input);
	while (cursor < inputLen)
	{
		if (isblank(input[cursor]) || ispunct(input[cursor]))
			cursor++;
		auto foundLen = 1;
		auto firstCh = input[cursor];
		auto here = input + cursor;
		auto id = -1; //unknown word;
		if ((firstCh >= 'a' && firstCh <= 'z'))
		{
			if ((cursor + 1 < inputLen) && (cursor >= inputLen || input[cursor + 1] == ' '))
			{
				//current word is one letter?
				if (firstCh == 'a' || firstCh == 'i')
					id = 0; //ignore
			}
		}

		int i = ((firstCh - 'a') * 2);
		int a = (unsigned char)dict[i++];
		int b = (unsigned char)dict[i++];
		i = (a << 8) | b;
		if (i == 0)
		{
			numRes = 0;
			return;
		}
		int words = dict[i];
		char thisWord[64] = { firstCh, 0 };

		while (thisWord[0] == firstCh && i < dictSize)
		{
			char prefixLen = dict[i++];
			char *prefixedWord = thisWord + prefixLen;
			char c = 0;
			do
			{
				c = dict[i++];
				if (i >= dictSize)
				{
					//give up
					results[numRes++] = -1;
					return;
				}
				*prefixedWord++ = (char)((c ^ 0x7F) & 0x7F);
			} while (((c & 0x80) != 0x80));
			if (thisWord[0] != firstCh)
			{
				numRes = 0;
				results[0] = -1;
				cursor += (int)strlen(thisWord);
				break;
			}
			*prefixedWord = 0;
			int a = (unsigned char)dict[i++];
			int b = (unsigned char)dict[i++];
			id = (a << 8) | b;
		
			int wordLen = (int)strlen(thisWord);
			if (!strncmp(here, thisWord, wordLen))
			{
				results[numRes++] = id;
				cursor += wordLen + 1;
				break;
			}
		}
	}

//	for (int i = 0; i < numRes; i++)
//		printf("%d %d\n", i, results[i]);
}
