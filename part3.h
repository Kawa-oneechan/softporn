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

extern void parse(char*);
extern int results[];
bool agiParse(char* str)
{
	for (unsigned int i = 0; i < strlen(str); i++)
		str[i] = (char)tolower(str[i]);

	if (strlen(str) == 1)
	{
		switch (str[0])
		{
		case 'i': strcpy(str, "take inventory"); break;
		case 'n': strcpy(str, "north"); break;
		case 's': strcpy(str, "s"); break;
		case 'e': strcpy(str, "east"); break;
		case 'w': strcpy(str, "west"); break;
		case 'u': strcpy(str, "up"); break;
		case 'd': strcpy(str, "down"); break;
		}
	}

	parse(str);

	if (results[0] == -1)
	{
		puts("I didn't catch that.");
		return false;
	}

	if (results[0] == 2) //taek
	{
		puts("Learn to spell, numbnut!");
		return false;
	}
	else if (results[1] == 3) //lady
	{
		puts("That's no lady, that's my sister!");
		return false;
	}

	if (results[0] == 264)
	{
		//take inventory
		results[0] = 302;
		results[1] = 264;
	}
	else if (results[0] >= 100 && results[0] <= 199)
	{
		//go _____
		results[1] = results[0];
		results[0] = 300;
	}

	haveNoVerb = true;
	haveNoObject = true;
	haveNoDirection = true;

	if (results[0] >= 300 && results[0] <= 399)
	{
		haveNoVerb = false;
		state.verb = (verbs)(results[0] - 300);
	}
	if (results[1] >= 200 && results[1] <= 299)
	{
		haveNoObject = false;
		state.noun = (objects)(results[1] - 200);
	}
	if (haveNoObject && results[1] >= 100 && results[1] <= 199)
	{
		haveNoDirection = false;
		state.direction = (directions)(results[1] - 100);
	}

	haveVerbOnly = !haveNoVerb && (haveNoObject && haveNoDirection);
	return true;
}

void readAndParseCommand()
{
	bool commandOK = false;
	places prevPlace = (places)-1;
	char score[40];
	sprintf(score, "Score: %d/3", state.score);

	do
	{
		do
		{
			if (state.yourPlace != prevPlace)
				lookAround();
			prevPlace = state.yourPlace;

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
		commandOK = agiParse(command);

	} while (!commandOK);
}
