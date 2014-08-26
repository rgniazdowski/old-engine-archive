/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXMaterial.h"

/* #TODO P4 - stworzenie klasy Material w glownym podsystemie GFX - wazne: tablice wierzcholkow, 
 * kolorow/uv itp sa grupowane wedlug uzytego materialu
 *
 * zalozenie jest takie ze grupowanie w ten sposob pozwala przyspieszyc rendering - jesli mamy np.
 * 10 obiektow po 1000+ wierzcholkow to nie ma sensu 10 razy wywolywac i przekazywac listy wierzcholkow
 * do OpenGL - mozna stworzyc jedna tablice i przekazac ja tylko raz 
 * * - teoretycznie ma to przyspieszyc dzialanie i prawdopodobnie tak jest - jednak zostawiam to na pozniej
 *
 * * Jak to zaimplementowac pozniej? W jakis sposob material musi miec odnosnik do obiektow ktore go uzywaja
 * * lub vice versa - po zaladowaniu wszystkich obiektow sa one merge'owane w grupy (wg uzytego Materialu) i
 * * duze tablice danych (vert,tris,uv,norm,color)
 * *
 * * To ma sens przy scenach z duza iloscia obiektow - zostawiam na pozniej - P4
 */

using namespace FG_GFX;