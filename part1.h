#pragma once

enum directions
{
	north, south, east, west, up, down, noDirection
};

enum objects
{
	desk, washBasin, graffiti, mirror, toilet,
	businessMan, button, bartender, pimp, hooker,
	billboard, preacher, TV, slotMachines, cards,
	ashtray, blonde, bed, bum, peephole,
	doorWest, waitress, table, telephone, closet,
	sink, elevator, dealer, cabinet, bushes,
	tree, window, sign, girl, newspaper,
	ring, whiskey, beer, hammer, garbage,
	flowers, appleCore, seeds, candy, pills,
	plant, passcard, radio, knife, magazine,
	rubber, wine, wallet, doll, apple,
	pitcher, stool, rope, rack, mushroom,
	controlUnit, curtain, water,
	taxi, inventory, all, on, off,
	you, noObject
};

enum places
{
	//Bar
	bHallway, bBathroom, bBar, bStreet, bBackRoom,
	bGarbageDump, bInRoom, bWindowLedge, bBedRoom, bBalcony,
	//Casino
	cStreet, cChapel, cCasino, c21Room, cLobby,
	cSuite, cHallway, cBalcony, cHtDesk,
	//Disco
	dBooth, dDisco, dStreet, dEntrance, dPharmacy,
	//Penthouse
	pFoyer, pJacuzzi, pKitchen, pGarden, pLiving,
	pPntPch,
	//Elsewhere
	youHaveIt, nowhere
};

enum verbs
{
	go, hail, take, drop, look, flush, open, inflate, play,
	press, enter, eat, drink, buy, climb, _water, fill, pour,
	_listen, close, jump,
	marry, fuck, wear, answer, call, _break, cut, dance,
	kill, pay, smoke, show, smell, help, kiss, stab, say, quit,
	showScore, save, restore, noVerb
};

const int maxCarried = 7;
const directions firstDirection = north;
const directions lastDirection = down;
const objects firstObject = desk;
const objects lastObject = noObject;
const places firstPlace = bHallway;
const places lastPlace = nowhere;
const verbs firstVerb = go;
const verbs lastVerb = noVerb;

//type path_array = array[places,first_direction..last_direction] of places;

const char* const directionNames[] =
{
	"North", "South", "East", "West", "Up", "Down", "No direction"
};

const char* const objectNames[] =
{
	"a desk",
	"a washbasin",
	"graffiti",
	"a mirror",
	"a toilet",
	"a businessman",
	"a button",
	"the bartender",
	"a big dude",
	"a funky hooker",
	"a billboard",
	"a preacher",
	"a TV",
	"slot machines",
	"cards",
	"an ashtray",
	"a voluptous blonde",
	"a bed",
	"a bum",
	"a peep hole",
	"a door to the west",
	"a waitress",
	"a table",
	"a telephone",
	"a closet",
	"a sink",
	"an elevator",
	"a dealer",
	"a cabinet",
	"bushes",
	"a tree",
	"a window",
	"a sign",
	"a girl",
	"a newspaper",
	"a wedding ring",
	"a shot of whiskey",
	"a beer",
	"a hammer",
	"garbage",
	"flowers",
	"an apple core",
	"seeds",
	"candy",
	"pills",
	"a plant",
	"a passcard",
	"a radio",
	"a pocket knife",
	"adventureboy magazine",
	"a rubber",
	"a bottle of wine",
	"a wallet",
	"an inflatable doll",
	"an apple",
	"a pitcher",
	"a stool",
	"a rope",
	"a display rack",
	"a mushroom",
	"a remote control unit",
	"a curtain",
	"water",
	"a taxi",
	"inventory",
	"all",
	"on",
	"off",
	"yourself",
	"no object"
};

const places origObjectPlace[] =
{
	bHallway, //desk
	bBathroom, //washbasin
	bBathroom, //graffiti
	bBathroom, //mirror
	bBathroom, //toilet
	bHallway, //businessman
	cHtDesk, //button, also in pFoyer
	bBar, //bartender
	bBackRoom, //big dude
	bBedRoom, //funky hooker
	bBalcony, //billboard
	cChapel, //preacher
	bBackRoom, //TV
	cCasino, //slot machines
	c21Room, //cards
	cHallway, //ashtray
	cHtDesk, //voluptuous blonde
	cSuite, //bed
	dStreet, //bum
	cBalcony, //peephole
	dEntrance, //door to the west
	dDisco, //waitress
	dDisco, //table
	dBooth, //telephone
	pLiving, //closet
	pKitchen, //sink
	cHtDesk, //elevator, also in pFoyer
	c21Room, //dealer
	pKitchen, //cabinet
	nowhere, //bushes, behind plant
	nowhere, //tree, grown in garden
	bWindowLedge, //window
	bStreet, //sign, also in cStreet and dStreet
	dDisco, //girl, also in cChapel, cSuite, and pJacuzzi
	nowhere, //newspaper, seen in drawer in bHallway
	nowhere, //wedding ring, seen in washbasin in bBathroom
	nowhere, //shot of whiskey, bought in bBar
	nowhere, //beer, bought in bBar
	pGarden, //hammer
	bGarbageDump, //garbage
	bHallway, //flowers
	nowhere, //apple core, found in garbage
	nowhere, //apple seeds, found in core
	bBedRoom, //candy
	bInRoom, //pills
	cLobby, //plant
	nowhere, //passcard, found in ashtray in cHallway
	cBalcony, //radio
	nowhere, //pocket knife, given by bum in dStreet
	nowhere, //magazine, found in rack in dPharmacy
	dPharmacy, //a rubber
	nowhere, //bottle of wine, bought in disco, ordered by phone
	youHaveIt, //wallet
	nowhere, //inflatable doll, in closet in pLiving
	nowhere, //apple, on tree grown in pGarden
	nowhere, //pitcher, in cabinet in pKitchen
	pGarden, //stool
	nowhere, //rope, girl ties you with it
	dPharmacy, //display rack
	pGarden, //mushroom
	nowhere, //remote control unit, given by businessman
	bBar, //curtain
	nowhere, //water, can get it by "water on"
	nowhere, //taxi, used in "hail taxi"
	nowhere, //inventory, used in "take inventory"
	nowhere, //all, used in "take all" and "drop all"
	nowhere, //on, used in "water on"
	nowhere, //off, used in "water off"
	nowhere, //you
	nowhere, //no object
};

const char* const verbNames[] =
{
	"GO",   "HAIL", "TAKE", "DROP", "LOOK",
	"FLUS", "OPEN", "INFL", "PLAY", "PRES",
	"ENTE", "EAT",  "DRIN", "BUY",  "CLIM",
	"WATE", "FILL", "POUR", "LIST", "CLOS",
	"JUMP", "MARR", "FUCK", "WEAR", "ANSW",
	"CALL", "BREA", "CUT",  "DANC", "KILL",
	"PAY",  "SMOK", "SHOW", "SMEL", "HELP",
	"KISS", "STAB", "SAY",  "QUIT",
	"SCOR", "SAVE", "REST", ""
};

const char* const objNames[] =
{
	"DESK", "WASH", "GRAF", "MIRR", "TOIL",
	"BUSI", "BUTT", "BART", "DUDE", "HOOK",
	"BILL", "PREA", "TV",   "SLOT", "CARD",
	"ASHT", "VOLU", "BED",  "BUM",  "HOLE",
	"DOOR", "WAIT", "TABL", "TELE", "CLOS",
	"SINK", "ELEV", "DEAL", "CABI", "BUSH",
	"TREE", "WIND", "SIGN", "GIRL", "NEWS",
	"RING", "WHIS", "BEER", "HAMM", "GARB",
	"FLOW", "CORE", "SEED", "CAND", "PILL",
	"PLAN", "PASS", "RADI", "KNIF", "MAGA",
	"RUBB", "WINE", "WALL", "DOLL", "APPL",
	"PITC", "STOO", "ROPE", "RACK", "MUSH",
	"CONT", "CURT", "WATE",
	"TAXI", "INVE", "ALL",  "ON",   "OFF",
	"YOU",  ""
};

const char* const glueWords[] =
{
	"A",  "AN", "THE",  "THIS", "THAT",
	"AT", "TO", "FROM", "WITH"
};

const char* const dirNames[] =
{
	"NORT", "SOUT", "EAST", "WEST",
	"UP", "DOWN", ""
};

const char* const placeNames[] =
{
	"I'm in a Hallway",
	"I'm in a Bathroom",
	"I'm in a Sleazy Bar",
	"I'm on a Street outside the Bar",
	"I'm in the Backroom",
	"I'm in a Filthy Dumpster",
	"I'm inside the room I broke into!",
	"I'm on a Window Ledge",
	"I'm in a Hooker's Bedroom",
	"I'm on a Hooker's Balcony",
	"I'm on a Downtown Street",
	"I'm in a Quickie Marriage Center",
	"I'm in the Main Casino Room",
	"I'm in the '21' Room",
	"I'm in the Lobby of the Hotel",
	"I'm in the Honeymoon Suite",
	"I'm in the Hotel Hallway",
	"I'm on the Honeymooner's Balcony",
	"I'm at the Hotel Desk",
	"I'm in a Telephone Booth",
	"I'm in the Disco",
	"I'm on a Residential Street",
	"I'm in the Disco's Entrance",
	"I'm in the Pharmacy",
	"I'm in the Penthouse Foyer",
	"I'm in the Jacuzzi",
	"I'm in the Kitchen",
	"I'm in the Garden",
	"I'm in the Living Room",
	"I'm on the Penthouse Porch",
	"Nowhere",
	"Carried by You"
};

const char* const placeHeaders[] =
{
	"Hallway",
	"Bathroom",
	"Sleazy Bar",
	"Street outside the Bar",
	"Backroom",
	"Filthy Dumpster",
	"Room I broke into!",
	"Window Ledge",
	"Hooker's Bedroom",
	"Hooker's Balcony",
	"Downtown Street",
	"Quickie Marriage Center",
	"Main Casino Room",
	"'21' Room",
	"Lobby of the Hotel",
	"Honeymoon Suite",
	"Hotel Hallway",
	"Honeymooner's Balcony",
	"Hotel Desk",
	"Telephone Booth",
	"Disco",
	"Residential Street",
	"Disco's Entrance",
	"Pharmacy",
	"Penthouse Foyer",
	"Jacuzzi",
	"Kitchen",
	"Garden",
	"Living Room",
	"Penthouse Porch",
	"Nowhere",
	"Carried by You"
};

const places origPath[][6] =
{
	//north south east west up down
	//BAR
	{ bBathroom, nowhere, bBar, nowhere, nowhere, nowhere }, //bHallway
	{ nowhere, bHallway, nowhere, nowhere, nowhere, nowhere }, //bBathroom
	{ bStreet, nowhere, nowhere, bHallway, nowhere, nowhere }, //bBar
	{ nowhere, bBar, nowhere, nowhere, nowhere, nowhere }, //bStreet
	{ nowhere, nowhere, nowhere, bBar, bBedRoom, nowhere }, //bBackRoom
	{ nowhere, nowhere, nowhere, bStreet, nowhere, nowhere }, //bGarbageDump
	{ bWindowLedge, nowhere, nowhere, nowhere, nowhere, nowhere }, //bInRoom
	{ nowhere, nowhere, bBalcony, nowhere, nowhere, nowhere }, //bWindowLedge
	{ bBalcony, nowhere, nowhere, nowhere, nowhere, bBackRoom }, //bBedroom
	{ nowhere, bBedRoom, nowhere, bWindowLedge, nowhere, bGarbageDump }, //bBalcony
	//CASINO
	{ cChapel, nowhere, cCasino, nowhere, nowhere, nowhere }, //cStreet
	{ nowhere, cStreet, nowhere, nowhere, nowhere, nowhere }, //cChapel
	{ c21Room, nowhere, cLobby, cStreet, nowhere, nowhere }, //cCasino
	{ nowhere, cCasino, nowhere, nowhere, nowhere, nowhere }, //c21Room
	{ nowhere, nowhere, nowhere, cCasino, cHtDesk, nowhere }, //cLobby
	{ cHallway, nowhere, cBalcony, nowhere, nowhere, nowhere }, //cSuite
	{ nowhere, nowhere, cHtDesk, nowhere, nowhere, nowhere }, //cHallway
	{ nowhere, nowhere, nowhere, cSuite, nowhere, nowhere }, //cBalcony
	{ nowhere, nowhere, nowhere, cHallway, nowhere, cLobby }, //cHtDesk
	//DISCO
	{ dDisco, nowhere, nowhere, nowhere, nowhere, nowhere }, //dBooth
	{ nowhere, dBooth, dEntrance, nowhere, nowhere, nowhere }, //dDisco
	{ dEntrance, nowhere, dPharmacy, nowhere, nowhere, nowhere }, //dStreet
	{ nowhere, dStreet, nowhere, nowhere, nowhere, nowhere }, //dEntrance
	{ nowhere, nowhere, nowhere, dStreet, nowhere, nowhere }, //dPharmacy
	//PENTHOUSE
	{ nowhere, nowhere, pKitchen, nowhere, pLiving, nowhere }, //pFoyer
	{ nowhere, nowhere, nowhere, nowhere, pPntPch, nowhere }, //pJacuzzi
	{ nowhere, nowhere, nowhere, pFoyer, nowhere, nowhere }, //pKitchen
	{ nowhere, nowhere, nowhere, nowhere, nowhere, nowhere }, //pGarden
	{ pPntPch, nowhere, nowhere, nowhere, nowhere, pFoyer }, //pLiving
	{ nowhere, pLiving, nowhere, nowhere, nowhere, pJacuzzi }, //pPntPch
	//ELSEWHERE
	{ nowhere, nowhere, nowhere, nowhere, nowhere, nowhere }, //youHaveIt
	{ nowhere, nowhere, nowhere, nowhere, nowhere, nowhere }, //nowhere
};

typedef struct gameState
{
	places objectPlace[69];
	bool placeVisited[32];
	places path[32][6];
	places yourPlace;

	objects noun;
	verbs verb;
	directions direction;

	bool gameEnded;

	int objectsCarried, money, score, TVChannel;
	
	bool ropeInUse, windowBroken, toiletFlushed, called5550987,
		called5556969, called5550439, rubberWorn, hookerFucked,
		doorWestOpen, radioListened, wineOrdered, telephoneRinging,
		telephoneAnswered, holePeeped, girl2Fucked, tiedToBed,
		drawerOpen, closetOpen, cabinetOpen, dollInflated,
		stoolClimbed, waterOn, pitcherFull, seedsPlanted,
		seedsWatered, appleGiven, candyGiven, flowersGiven,
		ringGiven, marriedToGirl, paidPimp;
	char girlName[32], girlPart[32], girlDo[32];
	char yourPart[32], yourObject[32];
	char rubberColor[32], rubberFlavor[32], rubberLubricated[32], rubberRibbed[32];
} gameState;

gameState state;
char lineFromKbd[256];
char parserVerb[8], parserNoun[8];
char fullVerb[64], fullNoun[64];
bool haveVerbOnly, haveNoVerb, haveNoObject, haveNoDirection;

bool noImAt = false;
