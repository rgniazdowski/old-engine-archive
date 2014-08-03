/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

// As for now I don't really see a point behind font manager. Can't remember what I thought about
// when I was creating this file... oops...
// Now I can't think of reason to have texture manager....

// such managers (below resource manager) could be used to get pointers in a faster way? or
// manage quality ?
// That makes actually sense - or not - dunno.
// QualityManager could be on top of this and such things like (font/texture manager) wont be necessary.

// Well now i know that font manager wont be necessary
// However Texture manager - yes. TexManager is used for triggering loading of data to RAM and then
// to VRAM (make gl texture) - those mechanism should be stored inside of the texture manager - not
// in texture resource definition - I think.

// Font is basically a texture - a 16x16 array in one image (ASCII font).

//////
////// TO DELETE
//////

#endif
