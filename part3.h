#pragma once

void cantGoThatWay()
{
	puts("I can't go that way.");
}

void cantDoThat()
{
	const char* const responses[] =
	{
		"Huh?",
		"Umm... huh?",
		"You're nuts.",
		"You can't be serious.",
		"Not freakin' likely."
		"I don't know how.",
		"An interesting idea.",
		"I can't do that."
	};
	puts(responses[getRandom(7)]);
}

void huh()
{
	puts("Huh?");
}

void dontKnowThatWord()
{
	puts("I don't think I know that word.");
}

void findMeOne()
{
	const char* const responses[] =
	{
		"Find me one.",
		"I don't see one here.",
		"Can't find it here.",
		"You'd have to find it first."
	};
	puts(responses[getRandom(4)]);
}

void dontHaveIt()
{
	puts("I don't have it.");
}

void alreadyHaveIt()
{
	puts("I already have it.");
}

void seeNothingSpecial()
{
	puts("I see nothing special.");
}

void seeSomething(objects object, const char* message)
{
	if (state.objectPlace[object] == nowhere)
	{
		puts("Oh! I see something!");
		state.objectPlace[object] = state.yourPlace;
	}
	else if (message == NULL)
		seeNothingSpecial();
	else
		puts(message);
}

void maybeLater()
{
	puts("Maybe not just yet.");
}

void noMoney()
{
	puts("Sorry, no money.");
}

bool objectIsHere(objects object)
{
	return state.objectPlace[object] == state.yourPlace;
}

bool objectIsCarried(objects object)
{
	return state.objectPlace[object] == youHaveIt;
}

bool objectCanBeTaken(objects object)
{
	const objects them[] = {
		newspaper, ring, whiskey, beer, hammer, garbage, flowers,
		appleCore, seeds, candy, pills, plant, passcard, radio, knife,
		magazine, rubber, wine, wallet, doll, apple, pitcher, stool,
		rope, rack, mushroom, controlUnit, water
	};
	for (int i = 0; i < 28; i++)
		if (them[i] == object)
			return true;
	return false;
}

bool placeIsPublic(places place)
{
	const places there[] = {
		bStreet, cStreet, cCasino, c21Room, cLobby, cHtDesk, dStreet, dEntrance
	};
	for (int i = 0; i < 8; i++)
		if (there[i] == place)
			return true;
	return false;
}

bool youAreIn(places place)
{
	return state.yourPlace == place;
}

void initNewGame()
{
	clearScreen();

	//putw("Hello there! I'm Kawa and I welcome you to Fact Hunt-- I mean, to Softporn Adventure! If all went well, this line should've been automatically word-wrapped at \"adventure\".");

	puts("\n\n\n\n\n\n\n\n\n\n");
	writeHeader(0, NULL, NULL);

	setColor(BOLDCOLOR);
	puts("Welcome to SOFTPORN ADVENTURE!\n");
	setColor(REGULARCOLOR);
	puts("Do you need instructions?");
	putchar('>');
	char yesNo = getOneOf('Y', 'N', 0);
	if (yesNo == 'Y')
		giveHelp();
	else
		puts("");

	memset((void*)&state, 0, sizeof(gameState));

	int i;
	for (i = 0; i < 69; i++)
		state.objectPlace[i] = origObjectPlace[i];
	for (i = 0; i < 32; i++)
	{
		state.placeVisited[i] = false;
		for (int j = 0; j < 6; j++)
			state.path[i][j] = origPath[i][j];
	}

	state.yourPlace = bBar;
	state.money = 10; //$1000
}

void lookAround()
{
	char status[80];
	sprintf(status, "Score: %d/3", state.score);
	writeHeader(0, placeHeaders[state.yourPlace], status);
	if (!noImAt)
	{
		setColor(BOLDCOLOR);
		printf("\n>> %s\n", placeHeaders[state.yourPlace]);
		setColor(REGULARCOLOR);
		if (!state.placeVisited[state.yourPlace])
		{
			writeLongMessage(state.yourPlace + 1);
			puts("");
		}
	}
	if (youAreIn(pPntPch) && state.called5550439)
	{
		if (!state.telephoneAnswered && getRandom(4) == 2)
			state.telephoneRinging = true;
		if (state.telephoneRinging)
			puts("The telephone rings.");
		puts("");
	}

	int statusLine = 1;
	{
		strcpy(status, "Things here: ");
		int ct = 0;
		int i;
		for (i = 0; i < 70; i++)
		{
			if (objectIsHere((objects)i))
			{
				if (ct)
					strcat(status, ", ");
				ct++;
				if (strlen(status) + strlen(objectNames[i]) > COLS - 1)
				{
					writeHeader(statusLine, status, NULL);
					strcpy(status, "             ");
					statusLine++;
				}
				strcat(status, objectNames[i]);
			}
		}
		if (ct == 0)
			strcat(status, "Nothing interesting.");
		writeHeader(statusLine, status, NULL);
		statusLine++;

		strcpy(status, "Exits: ");
		ct = 0;
		for (i = 0; i < 6; i++)
		{
			if (state.path[state.yourPlace][i] != nowhere)
				ct++;
		}
		int exits = ct;
		if (exits == 0)
			strcat(status, "By magic!");
		else
		{
			for (int i = 0; i < 6; i++)
			{
				if (state.path[state.yourPlace][i] != nowhere)
				{
					if (ct < exits)
					{
						if (ct > 1)
							strcat(status, ", ");
						else if (exits > 1)
							strcat(status, " and ");
					}
					ct--;
					strcat(status, directionNames[i]);
				}
			}
		}
		writeHeader(statusLine, status, NULL);
	}
	state.placeVisited[state.yourPlace] = true;
	noImAt = false;
}

/*
procedure take_inventory;
(*=====================*)
var objcount  : integer;
    obj       : objects;

begin
  with game_position do
    begin
      writeln;
      writeln( 'I''m carrying: ');
      objcount := 0;
      for obj := first_object to last_object do
        begin
          if is_carried(obj) then
            begin
              objcount := objcount + 1;
              writeln(object_name[obj]);
            end;
        end;
      if objcount=0 then writeln('Nothing') else writeln;
    end;

end;  { take_inventory }
*/

bool verbIsStandalone(verbs verb)
{
	const verbs verbs[] =
	{
		look, jump, dance, help, quit, showScore, save, restore
	};
	for (int i = 0; i < 8; i++)
		if (verbs[i] == verb)
			return true;
	return false;
}

bool verbIsSpecial(verbs verb)
{
	const verbs verbs[] =
	{
		take /*inven*/, hail /*taxi*/, call /*number*/, play /*slot/21*/, buy, save, restore
	};
	for (int i = 0; i < 7; i++)
		if (verbs[i] == verb)
			return true;
	return false;
}

char* trimWhiteSpace(char* str)
{
	char *end;

	int startSpaces = 0;
	unsigned int i;
	for (i = 0; i < strlen(str); i++)
	{
		if (isspace(str[i]))
			startSpaces++;
		else
			break;
	}

	strcpy(str, str + startSpaces);

	if (*str == 0)
		return str;

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;

	end[1] = '\0';

	for (i = 1; i < strlen(str); i++)
	{
		while (isspace(str[i]) && isspace(str[i - 1]))
		{
			strcpy(str + i, str + i + 1);
			//for (int j = i; j < strlen(str); j++)
			//	str[i] = str[i + 1];
		}
	}

	return str;
}

void expandAbbreviations(char* str)
{
	for (unsigned int i = 0; i < strlen(str); i++)
		str[i] = (char)toupper(str[i]);

	if (!strcmp(str, "INVE"))
		strcpy(str, "I");
	if (strlen(str) == 1)
	{
		switch (str[0])
		{
		case 'I': strcpy(str, "TAKE INVE"); break;
		case 'N': strcpy(str, "GO NORT"); break;
		case 'S': strcpy(str, "GO SOUT"); break;
		case 'E': strcpy(str, "GO EAST"); break;
		case 'W': strcpy(str, "GO WEST"); break;
		case 'U': strcpy(str, "GO UP"); break;
		case 'D': strcpy(str, "GO DOWN"); break;
		case 'L': strcpy(str, "LOOK"); break;
		}
	}
}

void splitUpInVerbAndNoun(char* str)
{
	strcpy(parserVerb, "    ");
	strcpy(parserNoun, "    ");
	strcpy(fullVerb, "");
	strcpy(fullNoun, "");

	char firstWord[24] = { 0 };
	char secondWord[24] = { 0 };
	char thisWord[24] = { 0 };
	char *space;
	char *space2;
	int i;

	strcpy(firstWord, str);
findGlue:
	space = strchr(str, ' ');
	if (space != NULL)
	{
		*space = '\0';
		strcpy(secondWord, space + 1); //secondWord = space + 1;
		if (secondWord[0] == '5' && secondWord[1] == '5' && secondWord[2] == '5')
			strcpy(secondWord, secondWord + 4);
	}
	else
		goto doneGlue;
	//char thisWord[5] = { secondWord[0], secondWord[1], secondWord[2], secondWord[3], 0 };
	thisWord[0] = secondWord[0];
	thisWord[1] = secondWord[1];
	thisWord[2] = secondWord[2];
	thisWord[3] = secondWord[3];
	thisWord[0] = 0;
	space2 = strchr(thisWord, ' ');
	if (space2 != NULL)
		*space2 = '\0';
	for (i = 0; i < 9; i++)
	{
		if (!strcmp(thisWord, glueWords[i]))
		{
			space = strchr(secondWord, ' ');
			if (space != NULL)
			{
				*space = '\0';
				strcpy(secondWord, space + 1); //secondWord = space + 1;
			}
			goto findGlue;
		}
	}
doneGlue:
	if (secondWord[0] != 0)
	{
		space = strchr(secondWord, ' ');
		if (space != NULL)
			*space = '\0';
	}

	space = strchr(firstWord, ' ');
	if (space != NULL)
		*space = '\0';

	//we should now have a noun and maybe a verb, now to identify them.

	haveNoVerb = true;
	haveNoObject = true;
	haveNoDirection = true;

	strcpy(fullVerb, firstWord);

	if (strlen(firstWord) > 4)
		firstWord[4] = '\0';

	strcpy(parserVerb, firstWord);

	if      (!strcmp(firstWord, "GET" )) strcpy(firstWord, "TAKE");
	else if (!strcmp(firstWord, "GRAB")) strcpy(firstWord, "TAKE");
	else if (!strcmp(firstWord, "LEAV")) strcpy(firstWord, "DROP");
	else if (!strcmp(firstWord, "PLAN")) strcpy(firstWord, "DROP");
	else if (!strcmp(firstWord, "GIVE")) strcpy(firstWord, "DROP");
	else if (!strcmp(firstWord, "SEAR")) strcpy(firstWord, "LOOK");
	else if (!strcmp(firstWord, "EXAM")) strcpy(firstWord, "LOOK");
	else if (!strcmp(firstWord, "READ")) strcpy(firstWord, "LOOK");
	else if (!strcmp(firstWord, "WATC")) strcpy(firstWord, "LOOK");
	else if (!strcmp(firstWord, "PULL")) strcpy(firstWord, "OPEN");
	else if (!strcmp(firstWord, "PUSH")) strcpy(firstWord, "PRES");
	else if (!strcmp(firstWord, "ORDE")) strcpy(firstWord, "BUY" );
	else if (!strcmp(firstWord, "SEDU")) strcpy(firstWord, "FUCK");
	else if (!strcmp(firstWord, "RAPE")) strcpy(firstWord, "FUCK");
	else if (!strcmp(firstWord, "SCRE")) strcpy(firstWord, "FUCK");
	else if (!strcmp(firstWord, "USE" )) strcpy(firstWord, "WEAR");
	else if (!strcmp(firstWord, "DIAL")) strcpy(firstWord, "CALL");
	else if (!strcmp(firstWord, "SMAS")) strcpy(firstWord, "BREA");
	else if (!strcmp(firstWord, "LOAD")) strcpy(firstWord, "REST");
	else if (!strcmp(firstWord, "STOP")) strcpy(firstWord, "QUIT");
	else if (!strcmp(firstWord, "BYE" )) strcpy(firstWord, "QUIT");

	for (i = 0; i < 48; i++)
	{
		if (!strcmp(firstWord, verbNames[i]))
		{
			state.verb = (verbs)i;
			haveNoVerb = false;
			break;
		}
	}

	haveVerbOnly = !haveNoVerb && secondWord[0] == 0;

	if (secondWord[0] != 0)
	{
		strcpy(fullNoun, secondWord);

		if (strlen(secondWord) > 4)
			secondWord[4] = '\0';

		strcpy(parserNoun, secondWord);

		for (int i = 0; i < 70; i++)
		{
			if (!strcmp(secondWord, objNames[i]))
			{
				state.noun = (objects)i;
				haveNoObject = false;
				break;
			}
		}

		if (haveNoObject)
			for (int i = 0; i < 6; i++)
			{
				if (!strcmp(secondWord, dirNames[i]))
				{
					state.direction = (directions)i;
					haveNoDirection = false;
					break;
				}
			}
	}
}

extern void parse(char* str);

void readAndParseCommand()
{
	bool commandOK = false;
	char score[40];
	sprintf(score, "Score: %d/3", state.score);

	do
	{
		do
		{
			lookAround();

			do
			{
				writeHeader(0, placeHeaders[state.yourPlace], score);
				putchar('>');
				getString(lineFromKbd, 256);
				if (strlen(lineFromKbd) == 0)
					puts("Beg your pardon?");
			} while (strlen(lineFromKbd) == 0);

			for (unsigned int i = 0; i < strlen(lineFromKbd); i++)
			{
				if (ispunct(lineFromKbd[i]))
					lineFromKbd[i] = ' ';
				trimWhiteSpace(lineFromKbd);
			}
		} while (strlen(lineFromKbd) == 0);

		char command[256];
		strcpy(command, lineFromKbd);
		expandAbbreviations(command);
		splitUpInVerbAndNoun(command);

		commandOK = strlen(parserVerb) > 0;

		if (!strcmp(parserNoun, "LADY"))
		{
			puts("That's no lady, that's my sister!");
			commandOK = false;
		}
		//else if say
		else if (!strcmp(parserVerb, "TKAE") || !strcmp(parserVerb, "TAEK"))
		{
			puts("Learn to spell, numbnut!");
			commandOK = false;
		}

	} while (!commandOK);
}
