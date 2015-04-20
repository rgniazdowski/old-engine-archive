/*
    Game Programming Gems: Vol 6, General Programming
    Gem:    BSP Techniques
    Author: Octavian Marius Chincisan
 */
#include "fgGfxBspTypes.h"

//CLR ZBLACK(0, 0, 0);
//CLR ZLIGHTGRAY(192, 192, 192);
//CLR ZGREY(128, 128, 128);
//CLR ZMEDIUMGRAY(128, 128, 128);
//CLR ZRED(255, 0, 0);
//CLR ZGREEN(0, 255, 0);
//CLR ZYELLOW(255, 255, 0);
//CLR ZBLUE(0, 0, 255);
//CLR ZWHITE(255, 255, 255);
//CLR ZCYAN(0, 255, 255);
//CLR ZREDLIGHT(255, 119, 119);
//CLR ZBLUELIGHT(119, 119, 255);
//CLR ZGREENLIGHT(119, 255, 119);

fg::Vector3f VX(1.0, 0.0, 0.0);
fg::Vector3f VZ(0.0, 0.0, 1.0);
fg::Vector3f VY(0.0, 1.0, 0.0);
fg::Vector3f V0(0.0, 0.0, 0.0);
fg::Vector3f V1(1.0, 1.0, 1.0);

//RGBA CLR_WHITE = {192, 192, 192, 255};
//RGBA CLR_GREY = {128, 64, 128, 255};
//RGBA CLR_PORTALS1 = {0, 0, 255, 100};
//RGBA CLR_PORTALS = {0, 255, 0, 100};
//RGBA CLR_PORTALSLINE = {255, 255, 0, 255};
/*
V3 AABoundingBox3Df::_norms[8] = {V3(-Cosr(PIPE4), -Cosr(PIPE4), -Cosr(PIPE4)),
                                  V3(Cosr(PIPE4), Cosr(PIPE4), Cosr(PIPE4)),
                                  V3(Cosr(PIPE4), -Cosr(PIPE4), -Cosr(PIPE4)),
                                  V3(-Cosr(PIPE4), Cosr(PIPE4), Cosr(PIPE4)),
                                  V3(Cosr(PIPE4), Cosr(PIPE4), -Cosr(PIPE4)),
                                  V3(-Cosr(PIPE4), -Cosr(PIPE4), Cosr(PIPE4)),
                                  V3(-Cosr(PIPE4), Cosr(PIPE4), -Cosr(PIPE4)),
                                  V3(Cosr(PIPE4), -Cosr(PIPE4), Cosr(PIPE4))};
 */
