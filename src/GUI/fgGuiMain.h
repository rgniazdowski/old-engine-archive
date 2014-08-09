/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_GUI_MAIN_H_
#define _FG_GUI_MAIN_H_

#include "fgGuiWidget.h"
#include "fgGuiMenu.h"

// #FIXME #TODO #P4 - this needs so much fixing and refactoring that I dont
// even know where to start... whole GUI, FONT & drawing is fubar...

#define MENU_GAME_STAGE 0
#define MENU_MAIN 1
#define MENU_NEW_GAME 2
#define MENU_OPTIONS 3
#define MENU_HIGHSCORES 4
#define MENU_HELP 5
#define MENU_ESCAPE 6
#define MENU_NONE 7

#define NUM_OBJ_COLORS 15

// For Gui::selection, and multiple other selection-situations
#ifndef NO_SELECTION
#define NO_SELECTION (-1)
#endif



class GuiMain {
private:

public:
	GuiMain();
	~GuiMain();

	void initMenuElements(void);
	void draw(void);
	void getSignals(void);
	void onMenuChange(void);
	
};

#endif /* _FG_GUI_MAIN_H_ */

