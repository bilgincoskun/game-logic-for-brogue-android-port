#ifdef BROGUE_CURSES
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "term.h"
#include <sys/timeb.h>
#include <stdint.h>
#include <signal.h>
#include "platform.h"

extern playerCharacter rogue;

static void gameLoop() {
	signal(SIGINT, SIG_DFL); // keep SDL from overriding the default ^C handler when it's linked

	if (!Term.start()) {
		return;
	}
	Term.title("Brogue " BROGUE_VERSION_STRING);
	Term.resize(COLS, ROWS);

	rogueMain();

	Term.end();
}

unsigned int glyphToUnicode(enum displayGlyph glyph) {
    if (glyph < 128) return glyph;

    switch (glyph) {
        case G_UP_ARROW: return U_UP_ARROW;
        case G_DOWN_ARROW: return U_DOWN_ARROW;
        case G_POTION: return '!';
        case G_GRASS: return '"';
        case G_WALL: return '#';
        case G_EASY: return '&';
        case G_OPEN_DOOR: return '\'';
        case G_GOLD: return '*';
        case G_CLOSED_DOOR: return '+';
        case G_RUBBLE: return ',';
        case G_KEY: return '-';
        case G_BOG: return '~';
        case G_CHAIN_TOP_LEFT:
        case G_CHAIN_BOTTOM_RIGHT:
            return '\\';
        case G_CHAIN_TOP_RIGHT:
        case G_CHAIN_BOTTOM_LEFT:
            return '/';
        case G_CHAIN_TOP:
        case G_CHAIN_BOTTOM:
            return '|';
        case G_CHAIN_LEFT:
        case G_CHAIN_RIGHT:
            return '-';
        case G_FOOD: return ';';
        case G_UP_STAIRS: return '<';
        case G_VENT: return '=';
        case G_DOWN_STAIRS: return '>';
        case G_PLAYER: return '@';
        case G_BOG_MONSTER: return 'B';
        case G_CENTAUR: return 'C';
        case G_DRAGON: return 'D';
        case G_FLAMEDANCER: return 'F';
        case G_GOLEM: return 'G';
        case G_TENTACLE_HORROR: return 'H';
        case G_IFRIT: return 'I';
        case G_JELLY: return 'J';
        case G_KRAKEN: return 'K';
        case G_LICH: return 'L';
        case G_NAGA: return 'N';
        case G_OGRE: return 'O';
        case G_PHANTOM: return 'P';
        case G_REVENANT: return 'R';
        case G_SALAMANDER: return 'S';
        case G_TROLL: return 'T';
        case G_UNDERWORM: return 'U';
        case G_VAMPIRE: return 'V';
        case G_WRAITH: return 'W';
        case G_ZOMBIE: return 'Z';
        case G_ARMOR: return '[';
        case G_STAFF: return '/';
        case G_WEB: return ':';
        case G_MOUND: return 'a';
        case G_BLOAT: return 'b';
        case G_CENTIPEDE: return 'c';
        case G_DAR_BLADEMASTER: return 'd';
        case G_EEL: return 'e';
        case G_FURY: return 'f';
        case G_GOBLIN: return 'g';
        case G_IMP: return 'i';
        case G_JACKAL: return 'j';
        case G_KOBOLD: return 'k';
        case G_MONKEY: return 'm';
        case G_PIXIE: return 'p';
        case G_RAT: return 'r';
        case G_SPIDER: return 's';
        case G_TOAD: return 't';
        case G_BAT: return 'v';
        case G_WISP: return 'w';
        case G_PHOENIX: return 'P';
        case G_ALTAR: return '|';
        case G_LIQUID: return '~';
        case G_FLOOR: return U_MIDDLE_DOT;
        case G_CHASM: return U_FOUR_DOTS;
        case G_TRAP: return U_DIAMOND;
        case G_FIRE: return U_FLIPPED_V;
        case G_FOLIAGE: return U_ARIES;
        case G_AMULET: return U_ANKH;
        case G_SCROLL: return U_MUSIC_NOTE;
        case G_RING: return U_CIRCLE;
        case G_WEAPON: return U_UP_ARROW;
        case G_GEM: return U_FILLED_CIRCLE;
        case G_TOTEM: return U_NEUTER;
        case G_GOOD_MAGIC: return U_FILLED_CIRCLE_BARS;
        case G_BAD_MAGIC: return U_CIRCLE_BARS;
        case G_DOORWAY: return U_OMEGA;
        case G_CHARM: return U_LIGHTNING_BOLT;
        case G_WALL_TOP: return '#';
        case G_DAR_PRIESTESS: return 'd';
        case G_DAR_BATTLEMAGE: return 'd';
        case G_GOBLIN_MAGIC: return 'g';
        case G_GOBLIN_CHIEFTAN: return 'g';
        case G_OGRE_MAGIC: return 'O';
        case G_GUARDIAN: return U_ESZETT;
        case G_WINGED_GUARDIAN: return U_ESZETT;
        case G_EGG: return U_FILLED_CIRCLE;
        case G_WARDEN: return 'Y';
        case G_DEWAR: return '&';
        case G_ANCIENT_SPIRIT: return 'M';
        case G_LEVER: return '/';
        case G_LEVER_PULLED: return '\\';
        case G_BLOODWORT_STALK: return U_ARIES;
        case G_FLOOR_ALT: return U_MIDDLE_DOT;
        case G_UNICORN: return U_U_ACUTE;
        case G_TURRET: return U_FILLED_CIRCLE;
        case G_WAND: return '~';
        case G_GRANITE: return '#';
        case G_CARPET: return U_MIDDLE_DOT;
        case G_CLOSED_IRON_DOOR: return '+';
        case G_OPEN_IRON_DOOR: return '\'';
        case G_TORCH: return '#';
        case G_CRYSTAL: return '#';
        case G_PORTCULLIS: return '#';
        case G_BARRICADE: return '#';
        case G_STATUE: return U_ESZETT;
        case G_CRACKED_STATUE: return U_ESZETT;
        case G_CLOSED_CAGE: return '#';
        case G_OPEN_CAGE: return '|';
        case G_PEDESTAL: return '|';
        case G_CLOSED_COFFIN: return '-';
        case G_OPEN_COFFIN: return '-';
        case G_MAGIC_GLYPH: return U_FOUR_DOTS;
        case G_BRIDGE: return '=';
        case G_BONES: return ',';
        case G_ELECTRIC_CRYSTAL: return U_CURRENCY;
        case G_ASHES: return '\'';
        case G_BEDROLL: return '=';
        case G_BLOODWORT_POD: return '*';

        default:
            brogueAssert(false);
            return '?';
    }
}



static char glyphToAscii(enum displayGlyph glyph) {
    unsigned int ch;

    switch (glyph) {
        case G_UP_ARROW: return '^';
        case G_DOWN_ARROW: return 'v';
        case G_FLOOR: return '.';
        case G_CHASM: return ':';
        case G_TRAP: return '%';
        case G_FIRE: return '^';
        case G_FOLIAGE: return '&';
        case G_AMULET: return ',';
        case G_SCROLL: return '?';
        case G_RING: return '=';
        case G_WEAPON: return '(';
        case G_GEM: return '+';
        case G_TOTEM: return '0'; // zero
        case G_GOOD_MAGIC: return '$';
        case G_BAD_MAGIC: return '+';
        case G_DOORWAY: return '<';
        case G_CHARM: return '7';
        case G_GUARDIAN: return '5';
        case G_WINGED_GUARDIAN: return '5';
        case G_EGG: return 'o';
        case G_BLOODWORT_STALK: return '&';
        case G_FLOOR_ALT: return '.';
        case G_UNICORN: return 'U';
        case G_TURRET: return '*';
        case G_CARPET: return '.';
        case G_STATUE: return '5';
        case G_CRACKED_STATUE: return '5';
        case G_MAGIC_GLYPH: return ':';
        case G_ELECTRIC_CRYSTAL: return '$';

        default:
            ch = glyphToUnicode(glyph);
            brogueAssert(ch < 0x80); // assert ascii
            return ch;
    }
}

static void curses_plotChar(enum displayGlyph ch,
			  short xLoc, short yLoc,
			  short foreRed, short foreGreen, short foreBlue,
			  short backRed, short backGreen, short backBlue) {
	
	fcolor fore;
	fcolor back;
	
	fore.r = (float) foreRed / 100;
	fore.g = (float) foreGreen / 100;
	fore.b = (float) foreBlue / 100;
	back.r = (float) backRed / 100;
	back.g = (float) backGreen / 100;
	back.b = (float) backBlue / 100;

    ch = glyphToAscii(ch);
	if (ch < ' ' || ch > 127) ch = ' ';
	Term.put(xLoc, yLoc, ch, &fore, &back);
}


struct mapsymbol {
	int in_c, out_c;
	struct mapsymbol *next;
};

static struct mapsymbol *keymap = NULL;

static int rewriteKey(int key, boolean text) {
	if (text) return key;

	struct mapsymbol *s = keymap;
	while (s != NULL) {
		if (s->in_c == key) {
			return s->out_c;
		}

		s = s->next;
	}
	return key;
}


#define PAUSE_BETWEEN_EVENT_POLLING		34//17

static uint32_t getTime() {
	struct timeb time;
	ftime(&time);
	return 1000 * time.time + time.millitm;
}

static boolean curses_pauseForMilliseconds(short milliseconds) {
	Term.refresh();
	Term.wait(milliseconds);
	
	// hasKey returns true if we have a mouse event, too.
	return Term.hasKey();
}

static void curses_nextKeyOrMouseEvent(rogueEvent *returnEvent, boolean textInput, boolean colorsDance) {
	int key;
	// TCOD_mouse_t mouse;
	uint32_t theTime, waitTime;
	// short x, y;
	
	Term.refresh();

	if (noMenu && rogue.nextGame == NG_NOTHING) rogue.nextGame = NG_NEW_GAME;
	
	for (;;) {
		theTime = getTime(); //TCOD_sys_elapsed_milli();
		
		/*if (TCOD_console_is_window_closed()) {
			rogue.gameHasEnded = true; // causes the game loop to terminate quickly
			returnEvent->eventType = KEYSTROKE;
			returnEvent->param1 = ACKNOWLEDGE_KEY;
			return;
		}*/
		
		if (colorsDance) {
			shuffleTerrainColors(3, true);
			commitDraws();
		}	
		
		
		key = Term.getkey();
		if (key == TERM_MOUSE) {
			if (Term.mouse.x > 0 && Term.mouse.y > 0 && Term.mouse.x < COLS && Term.mouse.y < ROWS) {
				returnEvent->param1 = Term.mouse.x;
				returnEvent->param2 = Term.mouse.y;
				returnEvent->eventType = KEYSTROKE;
				if (Term.mouse.justReleased) returnEvent->eventType = MOUSE_UP;
				if (Term.mouse.justPressed) returnEvent->eventType = MOUSE_DOWN;
				if (Term.mouse.justMoved) returnEvent->eventType = MOUSE_ENTERED_CELL;
				returnEvent->controlKey = Term.mouse.control;
				returnEvent->shiftKey = Term.mouse.shift;
				if (returnEvent->eventType != KEYSTROKE) return;
			}
		} else if (key != TERM_NONE) {
			key = rewriteKey(key, textInput);

			returnEvent->eventType = KEYSTROKE;
			returnEvent->controlKey = 0; //(key.rctrl || key.lctrl);
			returnEvent->shiftKey = 0; //key.shift;
			returnEvent->param1 = key;

			if (key == Term.keys.backspace || key == Term.keys.del) returnEvent->param1 = DELETE_KEY;
			else if (key == Term.keys.up) returnEvent->param1 = UP_ARROW;
			else if (key == Term.keys.down) returnEvent->param1 = DOWN_ARROW;
			else if (key == Term.keys.left) returnEvent->param1 = LEFT_ARROW;
			else if (key == Term.keys.right) returnEvent->param1 = RIGHT_ARROW;
			else if (key == Term.keys.quit) {
				rogue.gameHasEnded = true;
				rogue.nextGame = NG_QUIT; // causes the menu to drop out immediately
			} 
			else if ((key >= 'A' && key <= 'Z')) {
				returnEvent->shiftKey = 1;
				// returnEvent->param1 += 'a' - 'A';
			}
			// we could try to catch control keys, where possible, but we'll catch keys we mustn't
			/* else if ((key >= 'A'-'@' && key <= 'Z'-'@')) {
				returnEvent->controlKey = 1;
				returnEvent->param1 += 'a' - ('A'-'@');
			} */

			return;
		}

		waitTime = PAUSE_BETWEEN_EVENT_POLLING + theTime - getTime();
		
		if (waitTime > 0 && waitTime <= PAUSE_BETWEEN_EVENT_POLLING) {
			curses_pauseForMilliseconds(waitTime);
		}
	}
}

static void curses_remap(const char *input_name, const char *output_name) {
	struct mapsymbol *sym = malloc(sizeof(*sym));
	
	if (sym == NULL) return; // out of memory?  seriously?
	
	sym->in_c = Term.keycodeByName(input_name);
	sym->out_c = Term.keycodeByName(output_name);
	
	sym->next = keymap;
	keymap = sym;
}

static boolean modifier_held(int modifier) {
	return 0;
}

struct brogueConsole cursesConsole = {
	gameLoop,
	curses_pauseForMilliseconds,
	curses_nextKeyOrMouseEvent,
	curses_plotChar,
	curses_remap,
	modifier_held
};
#endif

