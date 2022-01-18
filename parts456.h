#pragma once

void PartsFourToSix()
{
	switch (state.verb)
	{
	case go:
	{
		if (state.tiedToBed)
			puts("But I'm tied to the bed!?");
		else if (!haveNoDirection)
		{
			if (youAreIn(bBedRoom) && state.direction == north && !state.hookerFucked)
				puts("\"Don't go there; do me first!\"");
			else if (youAreIn(cHallway) && state.direction == north && !state.marriedToGirl)
				puts("The door is locked shut.");
			else if (youAreIn(bBackRoom) && state.direction == up && state.TVChannel != 6)
			{
				if (state.TVChannel != 5)
				{
					if (state.money < 20 || !objectIsCarried(wallet))
						puts("The pimp says I can't go until I get $2000.");
					else if (state.hookerFucked)
						puts("\"Bruh, ain'tcha had enough for one night?\" the pimp asks.");
					else
					{
						puts("The pimp takes $2000 and gives me the okay.");
						state.paidPimp = true;
						state.money -= 20;
						state.yourPlace = bBedRoom;
					}
				}
				else
				{ 
					state.yourPlace = bBedRoom;
				}
			}
			else if (youAreIn(bBalcony) && state.direction == west && !state.ropeInUse)
				fallingDown();
			else
			{
				places newPlace = (places)state.path[state.yourPlace][state.direction];
				if (newPlace != nowhere)
					state.yourPlace = newPlace;
				else
					cantGoThatWay();
			}
		}
		else
			cantDoThat();
		break;
	}
	case hail:
	{
		if (state.noun != taxi)
			puts("Who are you kidding?");
		else if (!(youAreIn(bStreet) || youAreIn(cStreet) || youAreIn(dStreet)))
			puts("I'm not in the street.");
		else
		{
			writeLongMessage(36);

			char dest[128];
			putchar('>');
			getString(dest, 128);
			for (int i = 0; i < 4; i++)
				dest[i] = (char)toupper(dest[i]);
			dest[4] = 0;
			places newPlace = nowhere;
			if      (!strcmp(dest, "DISC")) newPlace = dStreet;
			else if (!strcmp(dest, "CASI")) newPlace = cStreet;
			else if (!strcmp(dest, "BAR" )) newPlace = bStreet;
			if (newPlace == nowhere || newPlace == state.yourPlace)
				puts("Huh? Hail another!");
			else if (objectIsCarried(wine))
			{
				wineInTaxi();
				state.yourPlace = newPlace;
				state.objectPlace[wine] = nowhere;
			}
			else
			{
				puts("We arrive and I get out.");
				state.yourPlace = newPlace;
			}
		}
		break;
	}
	case take: //get, grab
	{
		if (state.noun == inventory)
		{
			bool anythingCarried = false;
			for (int o = firstObject; o < lastObject; o++)
			{
				if (objectIsCarried((objects)o))
				{
					if (!anythingCarried)
						printf("I'm carrying the following:");
					anythingCarried = true;
					printf("\n > %s", objectNames[o]);
					if (o == wallet && state.money > 0)
						printf(" with $%d00", state.money);
				}
			}
			if (anythingCarried)
				puts("");
			else
				puts("I'm not carrying anything!");
		}
		else if (state.noun == off)
			puts("You're not a bird, silly.");
		else if (state.noun == all)
		{
			puts("You hog.");
			delay(300);
			for (int o = firstObject; o < lastObject; o++)
			{
				if (objectIsHere((objects)o))
				{
					printf("%s: ", objectNames[o]);
					if (state.objectsCarried >= maxCarried)
						puts("I'm carrying too much!");
					else if (objectCanBeTaken((objects)o))
					{
						if (youAreIn(dPharmacy) && (o == magazine || o == rubber))
						{
							puts("The clerk shouts \"Shoplifter!\" and guns me down.");
							purgatory();
						}
						else
						{
							state.objectPlace[o] = youHaveIt;
							state.objectsCarried++;
							if (o == water)
								state.pitcherFull = true;
							else if (o == pitcher && state.pitcherFull)
								state.objectPlace[water] = youHaveIt;
							puts("Taken.");
						}
					}
					else
						cantDoThat();
				}
			}
		}
		else if (objectIsCarried(state.noun))
			alreadyHaveIt();
		else if (!objectIsHere(state.noun))
			findMeOne();
		else if (state.objectsCarried >= maxCarried)
			puts("I'm carrying too much!");
		else if (!objectCanBeTaken(state.noun))
			cantDoThat();
		else if (youAreIn(dPharmacy) && (state.noun == magazine || state.noun == rubber))
		{
			puts("The clerk shouts \"Shoplifter!\" and guns me down.");
			purgatory();
		}
		else if (state.noun == water && !objectIsCarried(pitcher))
			puts("Get me a pitcher so I don't spill it.");
		else if (state.noun == candy && youAreIn(bBedRoom) && !state.hookerFucked)
			puts("The hooker calls out to you, \"Don't take it, do me first!\"");
		else if (state.noun == rope && state.ropeInUse)
			puts("It's tied to the balcony.");
		else
		{
			okay();
			state.objectPlace[state.noun] = youHaveIt;
			state.objectsCarried++;
			if (state.noun == water)
				state.pitcherFull = true;
			else if (state.noun == pitcher && state.pitcherFull)
				state.objectPlace[water] = youHaveIt;
		}
		break;
	}
	case drop: //leave, plant, give
	{
		if (state.noun == inventory || state.noun == taxi || state.noun == on || state.noun == off)
			huh();
		else if (state.noun == all)
		{
			bool anythingCarried = false;
			for (int o = firstObject; o < lastObject; o++)
			{
				if (objectIsCarried((objects)o))
				{
					anythingCarried = true;
					printf("%s: Dropped.\n", objectNames[o]);
					state.objectPlace[o] = state.yourPlace;
					state.objectsCarried--;
					//Bug in original: DROP ALL won't synchronize things like rubberWorn.
					if (o == pitcher && state.pitcherFull)
						state.objectPlace[water] = state.yourPlace;
					else if (o == rubber)
						state.rubberWorn = false;
					//Anything given *to* others, like Fawn's gifts, we don't actually *give* even if we typed "give".
				}
			}
			if (!anythingCarried)
				puts("I'm not carrying anything!");
		}
		else if (!objectIsCarried(state.noun))
			dontHaveIt();
		else
		{
			state.objectPlace[state.noun] = state.yourPlace;
			state.objectsCarried--;
			if (state.noun == pitcher && state.pitcherFull)
				state.objectPlace[water] = state.yourPlace;
			else if (state.noun == rubber)
				state.rubberWorn = false;
			else if (youAreIn(dDisco) && objectIsHere(girl) && (state.noun == candy || state.noun == flowers || state.noun == ring))
			{
				switch (state.noun)
				{
				case candy:
				{
					puts("She smiles and eats a couple.");
					state.candyGiven = true;
					//Bug in original: should remove candy from play, just like candy and ring?
					state.objectPlace[candy] = nowhere;
					break;
				}
				case flowers:
				{
					puts("She blushes profusely and puts them in her hair.");
					state.flowersGiven = true;
					state.objectPlace[flowers] = nowhere;
					break;
				}
				case ring:
				{
					puts("She blushes and puts it safely in her purse.");
					state.ringGiven = true;
					state.objectPlace[ring] = nowhere;
					break;
				}
				}
				if (state.candyGiven && state.flowersGiven && state.ringGiven)
				{
					puts("She says, \"Meet me at the marriage center!\"");
					state.objectPlace[girl] = cChapel;
				}
			}
			else if (objectIsHere(bum) && state.noun == wine)
			{
				if (state.objectPlace[knife] == nowhere)
				{
					bumTellsStory();
					state.objectPlace[knife] = state.yourPlace;
				}
				else
					puts("\"That stuff made me puke,\" the bum mutters. \"Git outta here.\"");
			}
			else if (objectIsHere(businessMan) && state.noun == whiskey && state.objectPlace[controlUnit] == nowhere)
			{
				puts("The guy gives me a TV remote control.");
				state.objectPlace[controlUnit] = state.yourPlace;
			}
			else if (objectIsHere(blonde) && state.noun == pills)
			{
				writeLongMessage(57);
				state.objectPlace[blonde] = nowhere;
				state.objectPlace[pills] = nowhere;
			}
			else if (state.noun == apple && youAreIn(pJacuzzi) && objectIsHere(girl))
			{
				writeLongMessage(50);
				state.appleGiven = true;
			}
			else
				okay();
		}
		break;
	}
	case look: //search, examine, read, watch
	{
		if (haveNoObject)
		{
			writeLongMessage(state.yourPlace);
			noImAt = true;
		}
		else if (state.noun == all)
			puts("That's too much! One item at a time, please.");
		else if (state.noun == inventory || state.noun == on || state.noun == off)
			huh();
		else if (!objectIsHere(state.noun) && !objectIsCarried(state.noun))
			findMeOne();
		else
		{
			switch (state.noun)
			{
			case desk:
			{
				if (state.drawerOpen)
					seeSomething(newspaper, NULL);
				else
					puts("Its drawer is shut.");
				break;
			}
			case washBasin:
			{
				seeSomething(ring, "Dead roaches...");
				break;
			}
			case graffiti:
			{
				lookAtGraffiti();
				break;
			}
			case mirror:
			{
				puts("There's some pervert staring back at me.");
				break;
			}
			case toilet:
			{
				puts("Doesn't seem to be cleaned in ages. It stinks!");
				break;
			}
			case businessMan:
			{
				puts("Looks like a whiskey-drinking kinda guy to me.");
				break;
			}
			case button:
			{
				puts("It says 'push'.");
				break;
			}
			case bartender:
			{
				puts("He's waiting for me to buy something.");
				break;
			}
			case pimp:
			{
				puts("He has a pin on his coat. \"Support your local pimp -- gimme $2000\".");
				break;
			}
			case hooker:
			{
				writeLongMessage(31);
				break;
			}
			case billboard:
			{
				writeLongMessage(63, false);
				break;
			}
			case TV:
			{
				//if (!objectIsCarried(controlUnit))
				//	puts("I'd need the remote control for that.");
				//else if (!state.hookerFucked)
				//	puts("The pimp says I can't watch TV.");
				//else
					watchTV();
				break;
			}
			case slotMachines:
			{
				puts("Playing these might be more fun...");
				break;
			}
			case ashtray:
			{
				seeSomething(passcard, NULL);
				break;
			}
			case blonde:
			{
				writeLongMessage(40);
				break;
			}
			case bum:
			{
				puts("\"Tell ya my story for a bottle o' wine,\" he grumbles.");
				break;
			}
			case peephole:
			{
				if (state.holePeeped)
					puts("All windows at the hotel across the road have their curtains shut.");
				else
				{
					writeLongMessage(55);
					state.holePeeped = true;
				}
				break;
			}
			case doorWest:
			{
				if (state.doorWestOpen)
					puts("The door is open.");
				else
				{
					puts("The sign on the door says:");
					puts("\"Entry by showing passcard - club members and their guests only\"");
				}
				break;
			}
			case waitress:
			{
				puts("She ignores you.");
				break;
			}
			case telephone:
			{
				if (youAreIn(dBooth))
					puts("\"For a good time, call 555-6969.\"");
				else
					seeNothingSpecial();
				break;
			}
			case closet:
			{
				if (state.closetOpen)
					seeSomething(doll, "It's open.");
				break;
			}
			case sink:
			{
				puts("Type \"water on\" or \"water off\" to operate.");
				break;
			}
			case elevator:
			{
				puts("Its doors are closed.");
				break;
			}
			case dealer:
			{
				puts("He's waiting for me to play.");
				break;
			}
			case cabinet:
			{
				if (state.stoolClimbed)
				{
					if (state.cabinetOpen)
						seeSomething(pitcher, "It's open.");
					else
						puts("It's closed.");
				}
				else
					seeNothingSpecial();
				break;
			}
			case bushes:
			{
				puts("These bushes look lushes.");
				break;
			}
			case tree:
			{
				seeSomething(apple, NULL);
				break;
			}
			case sign:
			{
				puts("\"Hail taxi here\"");
				break;
			}
			case girl:
			{
				if (youAreIn(pJacuzzi))
					writeLongMessage(35);
				else if (youAreIn(dDisco) || youAreIn(cChapel))
					writeLongMessage(34);
				else
					puts("She slaps me for staring.");
				break;
			}
			case newspaper:
			{
				if (objectIsCarried(newspaper))
					writeLongMessage(32);
				else
					dontHaveIt();
				break;
			}
			case garbage:
			{
				seeSomething(appleCore, NULL);
				break;
			}
			case flowers:
			{
				puts("They look beautiful!");
				break;
			}
			case appleCore:
			{
				seeSomething(seeds, NULL);
				break;
			}
			case pills:
			{
				puts("The label on the bottle says:");
				puts("\"Want to drive someone crazy with lust? Try this!\"");
				break;
			}
			case plant:
			{
				if (state.objectPlace[bushes] == nowhere)
				{
					puts("Hello? There's a group of bushes behind it!");
					state.objectPlace[bushes] = state.yourPlace;
				}
				else
					seeNothingSpecial();
				break;
			}
			case radio:
			{
				puts("Maybe I should listen?");
				break;
			}
			case magazine:
			{
				if (objectIsCarried(magazine))
					writeLongMessage(33);
				else
					dontHaveIt();
				break;
			}
			case rubber:
			{
				if (objectIsCarried(rubber))
					printf("It's %s, %s-flavored, %s, and %s.\n", state.rubberColor, state.rubberFlavor, state.rubberLubricated, state.rubberRibbed);
				else
					dontHaveIt();
				break;
			}
			case wallet:
			{
				if (state.money > 0)
					printf("It contains $%d00.\n", state.money);
				else
					puts("It's empty.");
				break;
			}
			case doll:
			{
				if (state.dollInflated)
					puts("It's inflated.");
				else
					puts("It's all rolled up in a little ball.");
				break;
			}
			case pitcher:
			{
				if (state.pitcherFull)
					puts("It's full of water.");
				else
					puts("It's empty.");
				break;
			}
			case rack:
			{
				if (objectIsHere(rack))
					seeSomething(magazine, NULL);
				else if (objectIsHere(hooker))
					puts("It's... something alright.");
				else if (objectIsHere(girl) || objectIsHere(blonde))
					puts("Lookin' goo-- *SLAP* Ow.");
				break;
			}
			case curtain:
			{
				puts("It's on the east wall.");
				break;
			}
			default:
			{
				seeNothingSpecial();
				break;
			}
			}
		}
		break;
	}
	case flush:
	{
		if (!objectIsHere(state.noun))
			findMeOne();
		else if (state.noun == toilet)
		{
			writeLongMessage(69); //tsk! Nice! -- Kawa
			purgatory();
		}
		else
			cantDoThat();
		break;
	}
	case open: //pull
	{
		if (!objectIsHere(state.noun))
		{
			findMeOne();
			break;
		}
		switch (state.noun)
		{
		case window:
		{
			puts("It won't budge.");
			break;
		}
		case desk:
		{
			_open(&state.drawerOpen);
			break;
		}
		case doorWest:
		{
			if (state.doorWestOpen)
				puts("It's already open.");
			else
			{
				puts("A voice asks, \"Passcard?\". I search my pockets and...");
				if (objectIsCarried(passcard))
				{
					puts("I have it! The door opens.");
					state.doorWestOpen = true;
					state.path[dEntrance][west] = dDisco;
				}
				else
					puts("I don't have it!");
			}
		}
		case curtain:
		{
			puts("It seems to be remotely controlled.");
			break;
		}
		case elevator:
		{
			puts("Push the button to open the elevator doors.");
			break;
		}
		case closet:
		{
			_open(&state.closetOpen);
			break;
		}
		case cabinet:
		{
			if (state.stoolClimbed)
				_open(&state.cabinetOpen);
			else
				puts("I can't reach it.");
		}
		default:
		{
			cantDoThat();
			break;
		}
		}
		break;
	}
	case inflate:
	{
		if (state.noun == doll)
		{
			if (objectIsCarried(doll))
			{
				if (state.dollInflated)
					puts("It's already inflated, dimwit.");
				else
				{
					okay();
					state.dollInflated = true;
				}
			}
			else if (objectIsHere(doll))
				puts("I can't if I'm not holding it close.");
			else
				findMeOne();
		}
		else
			puts("But the prime rate is already 257%%!");
		break;
	}
	case play:
	{
		if (!objectIsHere(state.noun))
			findMeOne();
		else if (state.noun == slotMachines)
		{
			if (objectIsHere(slotMachines))
			{
				if (state.money > 0 && objectIsCarried(wallet))
					playSlots(&state.money);
				else
					noMoney();
			}
			else
				puts("Okay, show me your slot...");
		}
		else if (state.noun == cards)
		{
			if (youAreIn(c21Room))
			{
				if (state.money > 0 && objectIsCarried(wallet))
					; //play21(&state.money);
				else
					noMoney();
			}
			else
				maybeLater();
		}
		else
			puts("Playful li'l bugger, eh?");
		break;
	}
	case press: //push
	{
		if (state.noun == button)
		{
			if (youAreIn(bBar))
			{
				puts("A voice from behind the curtain says \"What's the password?\"");
				putchar('>');
				char password[128] = { 0 };
				getString(password, 128);
				for (int i = 0; i < 6; i++)
					password[i] = (char)toupper(password[i]);
				password[6] = '\0';
				if (!strcmp(password, "BELLYB"))
				{
					puts("The curtain pulls back!");
					state.path[bBar][east] = bBackRoom;
				}
				else if (!strcmp(password, "AL SEN") || !strcmp(password, "KEN SE"))
					puts("\"Cute, bruh. Real cute, but wrong.\"");
				else
					puts("\"Wrong, bruh!\"");
			}
			else if (youAreIn(cHtDesk) || youAreIn(pFoyer))
			{
				if (objectIsHere(blonde))
					puts("The blonde calls out, \"You can't go there!\"");
				else
				{
					writeLongMessage(37);
					if (youAreIn(cHtDesk))
						state.yourPlace = pFoyer;
					else
						state.yourPlace = cHtDesk;
				}
			}
			else
				maybeLater();
		}
		else
			puts("Pushy chump, eh?");
		break;
	}
	case enter:
	{
		if (!objectIsHere(state.noun))
			findMeOne();
		else if (state.noun == bushes)
			state.yourPlace = pGarden;
		else if (state.noun == window)
		{
			if (state.windowBroken)
				state.yourPlace = bInRoom;
			else
				maybeLater();
		}
		else if (state.noun == doorWest)
		{
			if (state.doorWestOpen)
				state.yourPlace = dDisco;
			else
				puts("The door's closed.");
		}
		else if (state.noun == elevator)
			puts("Push the button to enter the elevator.");
		else
			cantDoThat();
		break;
	}
	case eat:
	{
		if (!objectIsHere(state.noun) && !objectIsCarried(state.noun))
			findMeOne();
		else if (state.noun == blonde || state.noun == waitress || state.noun == hooker || state.noun == girl)
		{
			writeLongMessage(38);
			purgatory();
		}
		else if (state.noun == mushroom)
		{
			writeLongMessage(64);
			state.yourPlace = (places)getRandom(3);
			delay(600);
			state.placeVisited[state.yourPlace] = false;
		}
		else if (state.noun == garbage || state.noun == appleCore)
			puts("Eccch no!");
		else if (state.noun == apple)
			puts("I'm not that hungry.");
		else if (state.noun == pills)
		{
			writeLongMessage(56);
			purgatory();
		}
		else
			puts("Tastes awful.");
		break;
	}
	case drink:
	{
		if (!objectIsCarried(state.noun))
		{
			dontHaveIt();
			break;
		}
		switch (state.noun)
		{
		case whiskey: puts("This stuff's rot-gut! I'd rather give it to someone else."); break;
		case beer: puts("Heheheheeey, this stuff's okay!"); break;
		case wine: puts("Sour grapes..."); break;
		case water: puts("Thanks!"); break;
		default: puts("...Huh? Get your head examined."); break;
		}
		if (state.noun == beer || state.noun == water)
		{
			state.objectPlace[state.noun] = nowhere;
			state.objectsCarried--;
		}
		break;
	}
	case buy: //order
	{
		if (state.money < 1 || !objectIsCarried(wallet))
		{
			noMoney();
			break;
		}
		switch (state.noun)
		{
		case whiskey:
		case beer:
		{
			if (!youAreIn(bBar))
				maybeLater();
			else
			{
				if (state.objectPlace[state.noun] != nowhere)
					puts("\"Sorry, all out.\"");
				else
				{
					puts("I give the bartender $100 and he places it on the bar.");
					state.money--;
					state.objectPlace[state.noun] = state.yourPlace;
				}
			}
			break;
		}
		case wine:
		{
			if (!youAreIn(dDisco))
				maybeLater();
			else
			{
				if (state.objectPlace[state.noun] != nowhere)
					puts("\"Sorry, all out.\"");
				else
				{
					puts("The waitress takes $100 and says she'll be back shortly.");
					delay(3000);
					puts("...gee, that's taking a while.");
					delay(2000);
					state.money--;
					state.objectPlace[state.noun] = state.yourPlace;
				}
			}
			break;
		}
		case rubber:
		case magazine:
		{
			if (!youAreIn(dPharmacy))
				maybeLater();
			else
			{
				if (objectIsHere(state.noun))
				{
					if (state.noun == rubber)
						buyRubber();
					else
						puts("The clerk takes $100 and gives me the magazine.");
					state.money--;
					state.objectPlace[state.noun] = youHaveIt;
				}
				else
					puts("\"Sorry, sold out.\"");
			}
			break;
		}
		case hooker:
		{
			if (objectIsHere(hooker))
			{
				if (state.paidPimp)
					puts("I already paid the pimp, numbnuts.");
				else
					puts("After all that trickery?");
			}
			else
				findMeOne();
			break;
		}
		default:
		{
			puts("Money can't buy everything.");
			break;
		}
		}
		break;
	}
	case climb:
	{
		if (state.noun == stool)
		{
			if (objectIsHere(stool))
			{
				okay();
				state.stoolClimbed = true;
			}
			else
				puts("It's not on the floor here.");
		}
		else if (objectIsHere(state.noun) || objectIsCarried(state.noun))
			cantDoThat();
		else
			findMeOne();
		break;
	}
	case _water:
	{
		if (state.noun == on || state.noun == off)
		{
			if (!objectIsHere(sink))
				puts("Gotta find a working sink.");
			else
			{
				state.waterOn = state.noun == on;
				if (state.waterOn)
				{
					puts("Water is running in the sink.");
					state.objectPlace[water] = state.yourPlace;
				}
				else if (!state.pitcherFull)
				{
					okay();
					state.objectPlace[water] = nowhere;
				}
			}
		}
		else if (!objectIsCarried(water))
			puts("I have no water.");
		else if (!objectIsHere(state.noun))
			findMeOne();
		else if (state.noun == seeds)
		{
			state.objectPlace[water] = nowhere;
			state.pitcherFull = true;
			if (youAreIn(pGarden))
			{
				puts("Somehow, a tree sprouts within seconds!");
				state.objectPlace[tree] = state.yourPlace;
				state.objectPlace[seeds] = nowhere;
			}
			else
				puts("The seeds need better soil to grow.");
		}
		else
		{
			puts("It pours into the ground.");
			state.objectPlace[water] = nowhere;
			state.pitcherFull = false;
		}
		break;
	}
	case fill:
	{
		if (state.noun != pitcher)
			cantDoThat();
		else if (!objectIsCarried(pitcher))
			puts("I don't have it.");
		else if (!objectIsHere(sink))
			puts("Gotta find a working sink.");
		else if (!state.waterOn)
			puts("The water isn't running.");
		else if (state.pitcherFull)
			puts("The pitcher is already full.");
		else
		{
			okay();
			state.pitcherFull = true;
		}
		break;
	}
	case pour:
	{
		if (state.noun != water)
			cantDoThat();
		else if (!objectIsCarried(pitcher))
			puts("I have nothing to pour it with.");
		else if (!state.pitcherFull)
			puts("The pitcher is empty.");
		else if (!youAreIn(pGarden) || !objectIsHere(seeds))
			puts("It pours into the ground.");
		else
		{
			puts("Somehow, a tree sprouts within seconds!");
			state.objectPlace[tree] = state.yourPlace;
			//Bug in original: WATER SEEDS removes seeds from play, but POUR WATER does not.
			state.objectPlace[seeds] = nowhere;
		}
		break;
	}
	case _listen:
	{
		if (!objectIsHere(state.noun) && !objectIsCarried(state.noun))
			findMeOne();
		else if (state.noun == radio)
		{
			if (objectIsCarried(radio))
			{
				if (state.radioListened)
					puts("Eugh, punk rock.");
				else
				{
					puts("An advertisement says \"call 555-0987 for all your liquor needs!\"");
					state.radioListened = true;
				}
			}
			else
				puts("I should take it so I can hold it up to my ear.");
		}
		else
			puts("Quiet as a mouse in heat.");
		break;
	}
	case close:
	{
		if (!objectIsHere(state.noun))
		{
			findMeOne();
			break;
		}
		switch (state.noun)
		{
		case desk:
		{
			_close(&state.drawerOpen);
			if (objectIsHere(newspaper))
				state.objectPlace[newspaper] = nowhere;
			break;
		}
		case closet:
		{
			_close(&state.closetOpen);
			if (objectIsHere(doll))
				state.objectPlace[doll] = nowhere;
			break;
		}
		case cabinet:
		{
			if (state.stoolClimbed)
			{
				_close(&state.cabinetOpen);
				if (objectIsHere(pitcher))
					state.objectPlace[pitcher] = nowhere;
			}
			else
				puts("I can't reach it.");
			break;
		}
		case doorWest:
		{
			_close(&state.doorWestOpen);
			state.path[dEntrance][west] = nowhere;
		}
		default:
		{
			cantDoThat();
			break;
		}
		}
		break;
	}
	case jump:
	{
		if (youAreIn(bBalcony) || youAreIn(bWindowLedge))
			fallingDown();
		else
			puts("Hup!");
		break;
	}
	case marry:
	{
		if (state.noun != girl)
			puts("No way, weirdo.");
		else if (!objectIsHere(girl))
			puts("There's no girl here.");
		else if (!youAreIn(cChapel))
			maybeLater();
		else if (state.money < 30 || !objectIsCarried(wallet))
		{
			if (state.money < 20)
				puts("The girl says, \"But you'll need $2000 for the honeymoon suite!\"\nThe preacher chimes in, \"I'll need $1000, too.\"");
			else
				puts("The preacher says, \"I'll need $1000 for that.\"");
		}
		else
		{
			writeLongMessage(66);
			state.money -= 30;
			state.objectPlace[girl] = cSuite;
			state.marriedToGirl = true;
			state.path[cHallway][south] = cSuite;
		}
		break;
	}
	case fuck: //seduce, rape, screw
	{
		if (!objectIsHere(state.noun) && !objectIsCarried(state.noun) && state.noun != you)
		{
			findMeOne();
			break;
		}
		switch (state.noun)
		{
		case hooker:
		{
			if (state.hookerFucked)
				puts("She doesn't look like she can take any more.");
			else
			{
				if (state.rubberWorn)
				{
					state.hookerFucked = true;
					state.score++;
					writeLongMessage(51);
				}
				else
				{
					puts("Oh no! She gave me the dreaded Atomic Clap!");
					purgatory();
				}
			}
			break;
		}
		case doll:
		{
			if (objectIsCarried(doll))
			{
				if (state.dollInflated)
				{
					writeLongMessage(52);
					state.objectPlace[doll] = nowhere;
					state.objectsCarried--;
				}
				else
					puts("Inflate it first, dummy.");
			}
			else
				puts("I can't unless I'm holding it close.");
			break;
		}
		case girl:
		{
			switch (state.yourPlace)
			{
			case cSuite:
			{
				if (state.wineOrdered)
				{
					writeLongMessage(54);
					state.girl2Fucked = true;
					state.score++;
					state.tiedToBed = true;
					state.objectPlace[girl] = pJacuzzi;
					state.objectPlace[rope] = state.yourPlace;
				}
				else
					puts("\"I'm nervous. Don't you have some wine?\"");
				break;
			}
			case pJacuzzi:
			{
				if (state.appleGiven)
				{
					state.score++;
					writeLongMessage(53);
					state.gameEnded = true;
				}
				else
					maybeLater();
				break;
			}
			default:
			{
				maybeLater();
				break;
			}
			}
			break;
		}
		case bartender:
		{
			//puts("He jumps over the bar and strikes me down!");
			//puts("(Now that's putting the 'ender' in 'bartender'!)");
			//purgatory();
			puts("\"Buddy, don't make me put the 'ender' in 'bartender'.\"");
			puts("... he got me there.");
			break;
		}
		case you:
		{
			puts("The whole point was to stop doing that!");
			break;
		}
		case waitress:
		{
			puts("She kicks me in the nads for trying.");
			puts("\"Wisen up, Buster!\"");
			break;
		}
		case blonde:
		{
			puts("\"Fuck off, I'm working!\"");
			break;
		}
		case pimp:
		{
			puts("\"Bruh, even if I'd let ya you couldn't afford me, foo'!\" he mocks.");
			break;
		}
		case bum:
		{
			puts("Let's not. I don't know where he's been!");
			break;
		}
		case businessMan:
		{
			puts("\"Don't make this weird.\"");
			break;
		}
		case off:
		{
			puts("Yeah? How 'bout *you* fuck off, asshole?");
			break;
		}
		default:
		{
			puts("Pervert.");
			break;
		}
		}
		break;
	}
	case wear: //use
	{
		if (!objectIsHere(state.noun) && !objectIsCarried(state.noun) && state.noun != you)
		{
			findMeOne();
			break;
		}
		switch (state.noun)
		{
		case rubber:
		{
			puts("It tickles!");
			state.rubberWorn = true;
			state.objectPlace[rubber] = youHaveIt;
			break;
		}
		case toilet:
		{
			puts("~I got the constipation bluuueees...~");
			puts("Ah, much better.");
			break;
		}
		case bed:
		{
			puts("Ah, sleep...");
			delay(1000);
			puts("No wait! I can't sleep yet, I gotta find me a girl!");
			break;
		}
		case rope:
		{
			if (objectIsCarried(rope))
			{
				if (youAreIn(bBalcony))
				{
					state.objectPlace[rope] = state.yourPlace;
					state.ropeInUse = true;
					puts("Okay, the safety rope is tied to the balcony.");
				}
				else
					maybeLater();
			}
			else
				dontHaveIt();
			break;
		}
		case passcard:
		{
			if (objectIsCarried(passcard))
			{
				if (youAreIn(dEntrance))
				{
					puts("I flash my passcard and the door opens.");
					state.path[dEntrance][west] = dDisco;
				}
				else
					maybeLater();
			}
			else
				dontHaveIt();
			break;
		}
		case knife:
		{
			puts("Let me see if I still have it...");
			delay(600);
			if (objectIsCarried(knife))
			{
				if (state.tiedToBed)
				{
					puts("Yeah, I do. And it works! Thanks!");
					state.tiedToBed = false;
				}
				else
				{
					puts("Samurai sex fiend, YEEEAAAH!");
					delay(600);
					puts("...I accidentally stabbed myself.");
					purgatory();
				}
			}
			else
				dontHaveIt();
			break;
		}
		default:
		{
			cantDoThat();
			break;
		}
		}
		break;
	}
	case answer:
	{
		if (!objectIsHere(state.noun))
			findMeOne();
		else if (state.noun != telephone)
			cantDoThat();
		else if (state.telephoneRinging)
		{
			printf("A girl says, \"Hi honey! This is %s. Dear, why\n", state.girlName);
			printf("don't you forget this game and %s with me?\n", state.girlDo);
			printf("After all, your %s has always turned me on.\n", state.yourPart);
			printf("So bring a %s and come play with my %s.\"\n", state.yourObject, state.girlPart);
			printf("She hangs up.");
			state.telephoneRinging = false;
			state.telephoneAnswered = true;
		}
		else
			puts("It's not ringing though?");
		break;
	}
	case call: //dial
	{
		if (youAreIn(pPntPch))
			puts("This only takes incoming calls.");
		//Bug in original: CALL 555-XXXX works everywhere *but* the penthouse foyer.
		else if (!objectIsHere(telephone))
			puts("I mean, I could talk to my hand...");
		else if (!strcmp(fullNoun, "6969") && !state.called5556969)
		{
			puts("A voice on the line says \"Hello. Please answer the questions with\none-word answers.\"");
			printf("\"What's your favorite girls name?\"  >"); getString(state.girlName,   32);
			printf("\"Name a nice part of her anatomy.\"  >"); getString(state.girlPart,   32);
			printf("\"What do you like to do with her?\"  >"); getString(state.girlDo,     32);
			printf("\"And the best part of your body?\"   >"); getString(state.yourPart,   32);
			printf("\"Finally, your favorite object?\"    >"); getString(state.yourObject, 32);
			puts("He hangs up.");
			state.called5556969 = true;
		}
		else if (!strcmp(fullNoun, "0439") && !state.called5550439)
		{
			writeLongMessage(67);
			state.called5550439 = true;
		}
		else if (!strcmp(fullNoun, "0987") && state.marriedToGirl && !state.called5550987)
		{
			writeLongMessage(68);
			state.wineOrdered = true;
			state.called5550987 = true;
			state.objectPlace[wine] = cSuite;
		}
		else
		{
			puts("Nobody answers.");
		}
		break;
	}
	case _break:
	{
		if (!objectIsHere(state.noun))
			findMeOne();
		else if (state.noun == window)
		{
			if (objectIsCarried(hammer))
			{
				puts("Using the hammer, I smash the window to pieces.");
				state.path[bWindowLedge][south] = bInRoom;
			}
			else
				puts("If I had something to break it with, sure!");
		}
		else
			cantDoThat();
		break;
	}
	case cut:
	{
		puts("Let me see if I still have that knife...");
		delay(600);
		if (objectIsCarried(knife))
		{
			if (state.noun == rope && state.tiedToBed)
			{
				puts("Yeah, I do. And it works! Thanks!");
				state.tiedToBed = false;
			}
			else
			{
				puts("Samurai sex fiend, YEEEAAAH!");
				delay(600);
				puts("...I accidentally stabbed myself.");
				purgatory();
			}
		}
		else
			dontHaveIt();
		break;
	}
	case dance:
	{
		for (int i = 0; i < 3; i++)
		{
			delay(500);
			puts("Woohoo!");
			delay(500);
			puts("Yeah, yeah, yeah~");
		}
		delay(1000);
		puts("\nYeah, I got the moves, dude!");
		break;
	}
	case kill:
	{
		//puts("Try using a knife.");
		puts("What, with my bare hands?");
		break;
	}
	case pay:
	{
		if (!objectIsHere(state.noun))
		{
			findMeOne();
			break;
		}
		switch (state.noun)
		{
		case pimp:
		{
			if (state.hookerFucked)
				puts("\"I don't need yo money, bruh.\"");
			else
				puts("He'll take the money when you go up.");
			break;
		}
		case hooker:
		{
			if (state.paidPimp)
				puts("You already paid the pimp, dum-dum.");
			else
				puts("After all that trickery?");
			break;
		}
		case blonde:
		case waitress:
		case girl:
		{
			puts("\"What do you take me for, some common skank!?\"");
			puts("She punches me right in the vulnerables...");
			purgatory();
			break;
		}
		case preacher:
		{
			puts("Bring a girl here to marry, he'll take the money then.");
			break;
		}
		case businessMan:
		{
			puts("He's too drunk to do business right now.");
			break;
		}
		case bartender:
		{
			puts("Buy something, he'll take the money then.");
			break;
		}
		case dealer:
		{
			puts("Why not play 21 instead? You'll lose anyway!");
			break;
		}
		default:
		{
			cantDoThat();
			break;
		}
		}
		break;
	}
	case smoke:
	{
		if (state.noun == plant)
		{
			puts("A cop comes running and guns me down!");
			purgatory();
		}
		else
			cantDoThat();
		break;
	}
	case show:
	{
		if (state.noun == passcard)
		{
			if (objectIsCarried(passcard))
			{
				if (youAreIn(dEntrance))
				{
					puts("I flash my passcard and the door opens.");
					state.path[dEntrance][west] = dDisco;
				}
				else
					maybeLater();
			}
			else
				dontHaveIt();
		}
		else
			cantDoThat();
		break;
	}
	case smell:
	{
		if (!objectIsHere(state.noun) && !objectIsCarried(state.noun))
		{
			findMeOne();
			break;
		}
		switch (state.noun)
		{
		case blonde: puts("Hmm. Nice!"); break;
		case hooker: puts("Okay, who's eating tuna fish?"); break;
		case toilet: puts("Augh, I'm gonna puke!"); break;
		case plant: puts("...Achoo! Hmm. Guess I'm allergic?"); break;
		case garbage: puts("Yeeeccch!"); break;
		case flowers: puts("Smells like perfume."); break;
		default: puts("Smells okay."); break;
		}
		break;
	}
	case help:
	{
		giveHelp();
		break;
	}
	case kiss:
	{
		puts("Don't do that, it gets me excited!");
		break;
	}
	case stab:
	{
		stabSomeone();
		break;
	}
	case quit:
	{
		state.gameEnded = true;
		break;
	}
	case showScore:
	{
		puts("Can't you see the bar on top of the screen?");
		break;
	}
	case save:
	{
		int slot = 0;
		puts("Save to which slot? (0-9)");
		while (true)
		{
			char resp = getKeySilent();
			if (resp >= '0' && resp <= '9')
			{
				slot = resp - '0';
				break;
			}
		}
		char fileName[24] = "SOFTP-#.SAV";
		fileName[6] = '0' + slot;
#ifdef HAVESAFE
		FILE *f = NULL;
		if (fopen_s(&f, fileName, "wb+"))
#else
		FILE *f = fopen(fileName, "wb+");
		if (f != 0)
#endif
		{
			printf("Couldn't open %s.\n", fileName);
			break;
		}
		fwrite(&state, sizeof(gameState), 1, f);
		fclose(f);
		printf("Saved game to %s.\n", fileName);
		break;
	}
	case restore: //load
	{
		int slot = 0;
		puts("Restore from which slot? (0-9)");
		while (true)
		{
			char resp = getKeySilent();
			if (resp >= '0' && resp <= '9')
			{
				slot = resp - '0';
				break;
			}
		}
		char fileName[24] = "SOFTP-#.SAV";
		fileName[6] = '0' + slot;
#ifdef HAVESAFE
		FILE *f = NULL;
		if (fopen_s(&f, fileName, "rb+"))
#else
		FILE *f = fopen(fileName, "rb+");
		if (f != 0)
#endif
		{
			printf("Couldn't open %s.\n", fileName);
			break;
		}
		fread(&state, sizeof(gameState), 1, f);
		fclose(f);
		printf("Loaded game from %s.\n", fileName);

		//force full description
		state.placeVisited[state.yourPlace] = false;
		break;
	}
	default:
	{
		cantDoThat();
		break;
	}
	}
}