/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiConsole.h"
#include "fgStatus.h"

/*
 *
 */
fgGuiConsole::fgGuiConsole() :
base_type(),
m_numConsoleRecords(0) {
    fgGuiConsole::setDefaults();
}

/*
 *
 */
fgGuiConsole::~fgGuiConsole() { }

/*
 *
 */
void fgGuiConsole::setDefaults(void) {
    m_type = FG_GUI_CONSOLE;
    m_typeName = FG_GUI_CONSOLE_NAME;
    m_typeTraits = FG_GUI_CONSOLE | FG_GUI_TEXT_AREA | FG_GUI_SCROLL_AREA | FG_GUI_CONTAINER | FG_GUI_WIDGET;
    m_sliderSwitch = SLIDER_VERTICAL;
}

/*
 *
 */
fgBoundingBox3Df fgGuiConsole::updateBounds(void) {
    return base_type::updateBounds();
}

/*
 *
 */
void fgGuiConsole::refresh(void) {
    base_type::refresh();
}

/**
 * 
 * @param guiLayer
 */
void fgGuiConsole::display(fgGuiDrawer* guiLayer) {
    base_type::display(guiLayer);
}

/**
 * 
 * @param statusVec
 */
void fgGuiConsole::updateFromStatusVec(const fgVector<fgStatus *> &statusVec) {
   if(statusVec.empty())
       return;
   
   unsigned int n = statusVec.size(), diff = 0;
   diff = abs(n - m_numConsoleRecords);
   
   if(n == m_numConsoleRecords)
       return;
   
   if(n > m_numConsoleRecords) {
       for(unsigned int i=m_numConsoleRecords;i<n;i++) {
           fgStatus *status = statusVec[i];
           if(!status)
               continue;
           if(status->hasMessage()) {
               this->pushText(status->message->data);
           }
       }
       m_vSlider->setCurrentValue(m_vSlider->getMaxValue(), m_vSlider->getMaxValue());
       m_numConsoleRecords = m_textData.size();
   } else {
       // n < m_numConsoleRecords
       for(int i=0;i<diff;i++) {
           m_textData.pop_back();
       }
       m_numConsoleRecords = n;
   }
}
