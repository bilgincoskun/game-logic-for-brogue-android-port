#ifndef _platform_h_
#define _platform_h_

#include "Rogue.h"

#define U_MIDDLE_DOT  0x00b7
#define U_FOUR_DOTS  0x2237
#define U_DIAMOND  0x25c7
#define U_FLIPPED_V  0x22CF
#define U_ARIES  0x2648
#define U_ESZETT  0x00df
#define U_ANKH  0x2640
#define U_MUSIC_NOTE  0x266A
#define U_CIRCLE  0x26AA
#define U_LIGHTNING_BOLT  0x03DF
#define U_FILLED_CIRCLE  0x25cf
#define U_NEUTER  0x26b2
#define U_U_ACUTE  0x00da
#define U_CURRENCY 0x00A4
#define U_UP_ARROW  0x2191
#define U_DOWN_ARROW  0x2193
#define U_LEFT_ARROW  0x2190
#define U_RIGHT_ARROW  0x2192
#define U_OMEGA  0x03A9
#define U_CIRCLE_BARS  0x29F2
#define U_FILLED_CIRCLE_BARS  0x29F3

struct brogueConsole {
	void (*gameLoop)();
	boolean (*pauseForMilliseconds)(short milliseconds);
	void (*nextKeyOrMouseEvent)(rogueEvent *returnEvent, boolean textInput, boolean colorsDance);
	void (*plotChar)(enum displayGlyph, short, short, short, short, short, short, short, short);
	void (*remap)(const char *, const char *);
	boolean (*modifierHeld)(int modifier);
	boolean (*setGraphicsEnabled)(boolean);
    void (*textInputStart)(void);
    void (*textInputStop)(void);
};

void loadKeymap();

#ifdef BROGUE_TCOD
extern struct brogueConsole tcodConsole;
#endif

#ifdef BROGUE_CURSES
extern struct brogueConsole cursesConsole;
#endif

extern struct brogueConsole currentConsole;
extern boolean serverMode;
extern boolean noMenu;

extern gameStatus gameStat;

#endif
