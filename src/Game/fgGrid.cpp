/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgGrid.cpp
 * Author: vigilant
 * 
 * Created on July 13, 2015, 12:27 PM
 */

#include <climits>
#include <malloc.h>

#include "fgGrid.h"
#include "Math/fgVectorOperations.h"

using namespace fg;

//------------------------------------------------------------------------------

game::CGrid::CGrid(Dimension dimension) :
m_size(),
m_capacity(),
m_maxSize(),
m_dimension(dimension),
m_data(NULL),
m_dummy() {
    if(m_dimension == Dimension::NONE)
        m_dimension = Dimension::TWO_DIMENSIONAL;
    setMaxSize(MAX_SIZE_TWO_DIMENSIONAL,
               MAX_SIZE_TWO_DIMENSIONAL,
               2,
               2);
}
//------------------------------------------------------------------------------

game::CGrid::CGrid(const CGrid& orig) { }
//------------------------------------------------------------------------------

game::CGrid::~CGrid() {
    release();
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::SCellHolder::left(fgBool rewind) {
    if(!this->pParent) {
        return NULL;
    }
    SCellHolder* pCell = NULL;
    unsigned short sizeX = 0;
    unsigned short x = this->pos.x;
    fgBool success = FG_TRUE;

    this->pParent->getSize(&sizeX);
    if(x) {
        x--;
    } else if(rewind) {
        x = sizeX - 1;
    } else {
        success = FG_FALSE;
    }
    if(success) {
        pCell = this->pParent->atPtr(x, this->pos.y, this->pos.z, this->pos.w);
    }
    return pCell;
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::SCellHolder::right(fgBool rewind) {
    if(!this->pParent) {
        return NULL;
    }
    SCellHolder* pCell = NULL;
    unsigned short sizeX = 0;
    unsigned short x = this->pos.x;
    fgBool success = FG_TRUE;

    this->pParent->getSize(&sizeX);
    if(x < sizeX - 1) {
        x++;
    } else if(rewind) {
        x = 0;
    } else {
        success = FG_FALSE;
    }
    if(success) {
        pCell = this->pParent->atPtr(x, this->pos.y, this->pos.z, this->pos.w);
    }
    return pCell;
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::SCellHolder::front(fgBool rewind) {
    if(!this->pParent) {
        return NULL;
    }
    SCellHolder* pCell = NULL;
    unsigned short sizeZ = 0;
    unsigned short z = this->pos.z;
    fgBool success = FG_TRUE;

    this->pParent->getSize(NULL, NULL, &sizeZ);
    if(z < sizeZ - 1) {
        z++;
    } else if(rewind) {
        z = 0;
    } else {
        success = FG_FALSE;
    }
    if(success) {
        pCell = this->pParent->atPtr(this->pos.x, this->pos.y, z, this->pos.w);
    }
    return pCell;
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::SCellHolder::back(fgBool rewind) {
    if(!this->pParent) {
        return NULL;
    }
    SCellHolder* pCell = NULL;
    unsigned short sizeZ = 0;
    unsigned short z = this->pos.z;
    fgBool success = FG_TRUE;

    this->pParent->getSize(NULL, NULL, &sizeZ);
    if(z) {
        z--;
    } else if(rewind) {
        z = sizeZ - 1;
    } else {
        success = FG_FALSE;
    }
    if(success) {
        pCell = this->pParent->atPtr(this->pos.x, this->pos.y, z, this->pos.w);
    }
    return pCell;
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::SCellHolder::up(fgBool rewind) {
    if(!this->pParent) {
        return NULL;
    }
    SCellHolder* pCell = NULL;
    unsigned short sizeY = 0;
    unsigned short y = this->pos.y;
    fgBool success = FG_TRUE;

    this->pParent->getSize(NULL, &sizeY);
    if(y < sizeY - 1) {
        y++;
    } else if(rewind) {
        y = 0;
    } else {
        success = FG_FALSE;
    }
    if(success) {
        pCell = this->pParent->atPtr(this->pos.x, y, this->pos.z, this->pos.w);
    }
    return pCell;
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::SCellHolder::down(fgBool rewind) {
    if(!this->pParent) {
        return NULL;
    }
    SCellHolder* pCell = NULL;
    unsigned short sizeY = 0;
    unsigned short y = this->pos.y;
    fgBool success = FG_TRUE;

    this->pParent->getSize(NULL, &sizeY);
    if(y) {
        y--;
    } else if(rewind) {
        y = sizeY - 1;
    } else {
        success = FG_FALSE;
    }
    if(success) {
        pCell = this->pParent->atPtr(this->pos.x, y, this->pos.z, this->pos.w);
    }
    return pCell;
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::SCellHolder::forward(fgBool rewind) {
    if(!this->pParent) {
        return NULL;
    }
    SCellHolder* pCell = NULL;
    unsigned short sizeW = 0;
    unsigned short w = this->pos.w;
    fgBool success = FG_TRUE;

    this->pParent->getSize(NULL, NULL, NULL, &sizeW);
    if(w < sizeW - 1) {
        w++;
    } else if(rewind) {
        w = 0;
    } else {
        success = FG_FALSE;
    }
    if(success) {
        pCell = this->pParent->atPtr(this->pos.x, this->pos.y, this->pos.z, w);
    }
    return pCell;
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::SCellHolder::backward(fgBool rewind) {
    if(!this->pParent) {
        return NULL;
    }
    SCellHolder* pCell = NULL;
    unsigned short sizeW = 0;
    unsigned short w = this->pos.w;
    fgBool success = FG_TRUE;

    this->pParent->getSize(NULL, NULL, NULL, &sizeW);
    if(this->pos.w >= sizeW)
        this->pos.w = sizeW - 1;
    if(w) {
        w--;
    } else if(rewind) {
        w = sizeW - 1;
    } else {
        success = FG_FALSE;
    }
    if(success) {
        pCell = this->pParent->atPtr(this->pos.x, this->pos.y, this->pos.z, w);
    }
    return pCell;
}
//------------------------------------------------------------------------------

void game::CGrid::clear(fgBool full) {
    if(!m_data)
        return;
    unsigned short ix, iy, iz, iw;
    for(iw = 0; iw < m_size.w; iw++) {
        for(iz = 0; iz < m_size.z; iz++) {
            for(iy = 0; iy < m_size.y; iy++) {
                for(ix = 0; ix < m_size.x; ix++) {
                    if(full) {
                        m_data[iw][iz][iy][ix].clear();
                    } else {
                        m_data[iw][iz][iy][ix].clear(ix, iy, iz, iw);
                        m_data[iw][iz][iy][ix].pParent = this;
                    }
                }
            }
        }
    }
}
//------------------------------------------------------------------------------

void game::CGrid::release(void) {
    clear(FG_TRUE);
    if(!m_data)
        return;
    unsigned short iy, iz, iw;
    for(iw = 0; iw < m_capacity.w; iw++) {
        for(iz = 0; iz < m_capacity.z; iz++) {
            for(iy = 0; iy < m_capacity.y; iy++) {
                if(m_data[iw][iz][iy])
                    free(m_data[iw][iz][iy]);
                m_data[iw][iz][iy] = NULL;
            }
            if(m_data[iw][iz])
                free(m_data[iw][iz]);
            m_data[iw][iz] = NULL;
        }

        if(m_data[iw])
            free(m_data[iw]);
        m_data[iw] = NULL;
    }
    if(m_data)
        free(m_data);
    m_data = NULL;
    m_size.zero();
    m_capacity.zero();
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder& game::CGrid::at(unsigned short x,
                                          unsigned short y,
                                          unsigned short z,
                                          unsigned short w) {
    if(!isValidAddress(x, y, z, w) || !m_data) {
        m_dummy.clear();
        m_dummy.pParent = NULL;
        return m_dummy;
    }
    return m_data[w][z][y][x];
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder const& game::CGrid::at(unsigned short x,
                                                unsigned short y,
                                                unsigned short z,
                                                unsigned short w) const {
    if(!isValidAddress(x, y, z, w) || !m_data) {
        //m_dummy.clear();
        //m_dummy.pParent = NULL;
        return m_dummy;
    }
    return m_data[w][z][y][x];
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* game::CGrid::atPtr(unsigned short x,
                                             unsigned short y,
                                             unsigned short z,
                                             unsigned short w) {
    if(!isValidAddress(x, y, z, w) || !m_data) {
        m_dummy.clear();
        m_dummy.pParent = NULL;
        return &m_dummy;
    }
    return &m_data[w][z][y][x];
}
//------------------------------------------------------------------------------

const game::CGrid::SCellHolder* game::CGrid::atPtr(unsigned short x,
                                                   unsigned short y,
                                                   unsigned short z,
                                                   unsigned short w) const {
    if(!isValidAddress(x, y, z, w) || !m_data) {
        //m_dummy.clear();
        //m_dummy.pParent = NULL;
        return &m_dummy;
    }
    return &m_data[w][z][y][x];
}
//------------------------------------------------------------------------------

void* game::CGrid::getCellData(unsigned short x,
                               unsigned short y,
                               unsigned short z,
                               unsigned short w) {
    if(!isValidAddress(x, y, z, w)) {
        return NULL;
    }
    return m_data[w][z][y][x].pData;
}
//------------------------------------------------------------------------------

fgBool game::CGrid::setCellData(void* pData,
                                unsigned short x,
                                unsigned short y,
                                unsigned short z,
                                unsigned short w) {
    if(!isValidAddress(x, y, z, w)) {
        return FG_FALSE;
    }
    m_data[w][z][y][x].pData = pData;
    m_data[w][z][y][x].pos.x = x;
    m_data[w][z][y][x].pos.y = y;
    m_data[w][z][y][x].pos.z = z;
    m_data[w][z][y][x].pos.w = w;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool game::CGrid::setCellValue(unsigned short value,
                                 unsigned short x,
                                 unsigned short y,
                                 unsigned short z,
                                 unsigned short w) {
    if(!isValidAddress(x, y, z, w)) {
        return FG_FALSE;
    }
    m_data[w][z][y][x].value = value;
    m_data[w][z][y][x].pos.x = x;
    m_data[w][z][y][x].pos.y = y;
    m_data[w][z][y][x].pos.z = z;
    m_data[w][z][y][x].pos.w = w;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void game::CGrid::resize(unsigned short x,
                         unsigned short y,
                         unsigned short z,
                         unsigned short w) {
    if(x == 0)
        x = 1;
    if(y == 0)
        y = 1;
    if(z == 0)
        z = 1;
    if(w == 0)
        w = 1;
    if(x > m_maxSize.x)
        x = m_maxSize.x;
    if(y > m_maxSize.y)
        y = m_maxSize.y;
    if(z > m_maxSize.z)
        z = m_maxSize.z;
    if(w > m_maxSize.w)
        w = m_maxSize.w;
    fgBool is_x_diff = (fgBool)!!(x != m_size.x);
    fgBool is_y_diff = (fgBool)!!(y != m_size.y);
    fgBool is_z_diff = (fgBool)!!(z != m_size.z);
    fgBool is_w_diff = (fgBool)!!(w != m_size.w);
    fgBool is_x_less = (fgBool)!!(x < m_size.x);
    fgBool is_y_less = (fgBool)!!(y < m_size.y);
    fgBool is_z_less = (fgBool)!!(z < m_size.z);
    fgBool is_w_less = (fgBool)!!(w < m_size.w);
    int beginW = 0, beginZ = 0, beginY = 0, beginX = 0;
    int newW = w, newZ = z, newY = y, newX = x;
    int oldW = m_size.w, oldZ = m_size.z, oldY = m_size.y, oldX = m_size.x;
    // if requested resize size is smaller than current
    // no reallocation will occur - memory will be preserved

    if(is_w_diff && !is_w_less && m_capacity.w < w) {
        // W dimension changed bigger
        // realloc W dimension
        m_data = (SCellHolder ****)realloc(m_data, w * sizeof (SCellHolder ***));
        for(unsigned short iw = m_size.w; iw < w; iw++)
            m_data[iw] = NULL;
    }

    if(!(is_z_diff && !is_z_less) && is_w_diff) {
        beginW = m_size.w;
        z = m_size.z;
    }
    m_size.w = w;
    int oldCapacityW = m_capacity.w;
    if(is_w_diff && !is_w_less)
        m_capacity.w = newW;
    int oldCapacityZ = m_capacity.z;
    int oldCapacityY = m_capacity.y;
    int oldCapacityX = m_capacity.x;
    if(is_z_diff && !is_z_less && m_capacity.z < newZ)
        m_capacity.z = newZ;
    if(is_y_diff && !is_y_less && m_capacity.y < newY)
        m_capacity.y = newY;
    if(is_x_diff && !is_x_less && m_capacity.x < newX)
        m_capacity.x = newX;
    if((is_z_diff && !is_z_less) || is_w_diff) {
        for(unsigned short iw = beginW; iw < m_size.w; iw++) {
            m_data[iw] = (SCellHolder ***)realloc(m_data[iw], m_capacity.z * sizeof (SCellHolder **));
            unsigned short iz = oldCapacityZ;
            if(is_w_diff && iw >= oldCapacityW)
                iz = 0;
            for(; iz < z; iz++)
                m_data[iw][iz] = NULL;
        }
    }

    if(!(is_y_diff && !is_y_less) && is_z_diff) {
        beginZ = m_size.z;
        y = m_size.y;
    }
    m_size.z = z;    
    if((is_y_diff && !is_y_less) || is_z_diff || is_w_diff) {
        for(unsigned short iw = 0; iw < m_size.w; iw++) {
            for(unsigned short iz = beginZ; iz < m_size.z; iz++) {
                m_data[iw][iz] = (SCellHolder **)realloc(m_data[iw][iz], m_capacity.y * sizeof (SCellHolder *));
                unsigned short iy = oldCapacityY;
                if((is_z_diff && iz >= oldCapacityZ) || (is_w_diff && iw >= oldCapacityW))
                    iy = 0;
                for(; iy < y; iy++)
                    m_data[iw][iz][iy] = NULL;
            }
        }
    }

    if(!(is_x_diff && !is_x_less) && is_y_diff) {
        beginY = m_size.y;
        x = m_size.x;
    }
    m_size.y = y;    
    if((is_x_diff && !is_x_less) || is_y_diff || is_z_diff || is_w_diff) {
        for(unsigned short iw = 0; iw < m_size.w; iw++) {
            for(unsigned short iz = 0; iz < m_size.z; iz++) {
                for(unsigned short iy = beginY; iy < m_size.y; iy++) {
                    
                    m_data[iw][iz][iy] = (SCellHolder *)realloc(m_data[iw][iz][iy], m_capacity.x * sizeof (SCellHolder));
                    unsigned short ix = m_size.x;
                    if((is_y_diff && iy >= oldY) ||
                       (is_z_diff && iz >= oldZ) ||
                       (is_w_diff && iw >= oldW))
                        ix = 0;
                    for(; ix < x; ix++) {
                        m_data[iw][iz][iy][ix].clear(ix, iy, iz, iw);
                        m_data[iw][iz][iy][ix].pParent = this;
                    }
                }
            }
        }
    }
    m_size.x = newX;
    m_size.y = newY;
    m_size.z = newZ;
    m_size.w = newW;
}
//------------------------------------------------------------------------------

void game::CGrid::reserve(unsigned short x,
                          unsigned short y,
                          unsigned short z,
                          unsigned short w) {
    if(x < m_size.x)
        x = m_size.x;
    if(y < m_size.y)
        y = m_size.y;
    if(z < m_size.z)
        z = m_size.z;
    if(w < m_size.w)
        w = m_size.w;

    int oldX = m_size.x, oldY = m_size.y, oldZ = m_size.z, oldW = m_size.w;

    if(x > m_size.x || y > m_size.y || z > m_size.z || w > m_size.w)
        resize(x, y, z, w);

    m_size.x = oldX;
    m_size.y = oldY;
    m_size.z = oldZ;
    m_size.w = oldW;
}
//------------------------------------------------------------------------------

void game::CGrid::setMaxSize(unsigned short x,
                             unsigned short y,
                             unsigned short z,
                             unsigned short w) {
    fixSize(x, y, z, w);
    m_maxSize.x = x;
    m_maxSize.y = y;
    m_maxSize.z = z;
    m_maxSize.w = w;
}
//------------------------------------------------------------------------------

void game::CGrid::getSize(unsigned short& x,
                          unsigned short& y,
                          unsigned short& z,
                          unsigned short& w) {
    x = m_size.x;
    y = m_size.y;
    z = m_size.z;
    w = m_size.w;
}
//------------------------------------------------------------------------------

void game::CGrid::getSize(unsigned short* x,
                          unsigned short* y,
                          unsigned short* z,
                          unsigned short* w) {
    if(x)
        *x = m_size.x;
    if(y) {
        *y = m_size.y;
    }
    if(z) {
        *z = m_size.z;
    }
    if(w) {
        *w = m_size.w;
        if(m_dimension != FOUR_DIMENSIONAL)
            *w = 1;
    }
}
//------------------------------------------------------------------------------

void game::CGrid::getCapacity(unsigned short& x,
                              unsigned short& y,
                              unsigned short& z,
                              unsigned short& w) {
    x = m_capacity.x;
    y = m_capacity.y;
    z = m_capacity.z;
    w = m_capacity.w;
}
//------------------------------------------------------------------------------

void game::CGrid::getCapacity(unsigned short* x,
                              unsigned short* y,
                              unsigned short* z,
                              unsigned short* w) {
    if(x)
        *x = m_capacity.x;
    if(y)
        *y = m_capacity.y;
    if(z)
        *z = m_capacity.z;
    if(w) {
        *w = m_capacity.w;
        if(m_dimension != FOUR_DIMENSIONAL)
            *w = 1;
    }
}
//------------------------------------------------------------------------------

void game::CGrid::getMaxSize(unsigned short& x,
                             unsigned short& y,
                             unsigned short& z,
                             unsigned short& w) {
    x = m_maxSize.x;
    y = m_maxSize.y;
    z = m_maxSize.z;
    if(m_dimension == FOUR_DIMENSIONAL)
        w = m_maxSize.w;
    else
        w = 1;
}
//------------------------------------------------------------------------------

void game::CGrid::getMaxSize(unsigned short* x,
                             unsigned short* y,
                             unsigned short* z,
                             unsigned short* w) {
    if(x)
        *x = m_maxSize.x;
    if(y)
        *y = m_maxSize.y;
    if(z)
        *z = m_maxSize.z;
    if(w) {
        *w = m_maxSize.w;
        if(m_dimension != FOUR_DIMENSIONAL)
            *w = 1;
    }
}
//------------------------------------------------------------------------------

fgBool game::CGrid::fixSize(unsigned short& x,
                            unsigned short& y,
                            unsigned short& z,
                            unsigned short& w,
                            Dimension dimension) {
    int combined = (int)x;
    if(y)
        combined *= (int)y;
    if(z)
        combined *= (int)z;
    if(w)
        combined *= (int)w;
    fgBool status = FG_FALSE;
    if(dimension == Dimension::NONE)
        dimension = Dimension::FOUR_DIMENSIONAL;

    if(dimension == Dimension::FOUR_DIMENSIONAL) {
        int max_four_d = MAX_SIZE_FOUR_DIMENSIONAL * MAX_SIZE_FOUR_DIMENSIONAL;
        max_four_d *= MAX_SIZE_FOUR_DIMENSIONAL;
        max_four_d *= MAX_SIZE_FOUR_DIMENSIONAL;
        if(combined > max_four_d) {
            x = MAX_SIZE_FOUR_DIMENSIONAL;
            y = MAX_SIZE_FOUR_DIMENSIONAL;
            z = MAX_SIZE_FOUR_DIMENSIONAL;
            w = MAX_SIZE_FOUR_DIMENSIONAL;
            status = FG_TRUE;
        }
    } else if(dimension == Dimension::THREE_DIMENSIONAL) {
        int max_three_d = MAX_SIZE_THREE_DIMENSIONAL;
        max_three_d *= MAX_SIZE_THREE_DIMENSIONAL;
        max_three_d *= MAX_SIZE_THREE_DIMENSIONAL;
        if(combined > max_three_d) {
            x = MAX_SIZE_THREE_DIMENSIONAL;
            y = MAX_SIZE_THREE_DIMENSIONAL;
            z = MAX_SIZE_THREE_DIMENSIONAL;
            status = FG_TRUE;
        } else if(w > 1) {
            x = (int)math::round(math::pow((double)combined, 1. / 3.));
            y = x;
            z = x;
            status = FG_TRUE;
        }
        w = 1;
    } else if(dimension == Dimension::TWO_DIMENSIONAL) {
        int max_two_d = MAX_SIZE_TWO_DIMENSIONAL * MAX_SIZE_TWO_DIMENSIONAL;
        if(combined > max_two_d) {
            x = MAX_SIZE_TWO_DIMENSIONAL;
            y = MAX_SIZE_TWO_DIMENSIONAL;
            status = FG_TRUE;
        } else if(z > 1 || w > 1) {
            x = (int)math::round(math::sqrt((float)combined));
            y = x;
            status = FG_TRUE;
        }
        z = 1;
        w = 1;
    } else if(dimension == Dimension::SINGLE_DIMENSIONAL) {
        if(combined >= MAX_SIZE_ONE_DIMENSIONAL)
            combined = MAX_SIZE_ONE_DIMENSIONAL;
        x = combined;
        y = 1;
        z = 1;
        w = 1;
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool game::CGrid::isValidAddress(unsigned short x,
                                   unsigned short y,
                                   unsigned short z,
                                   unsigned short w) const {
    fgBool status = FG_TRUE;
    status = (fgBool)(status && x < m_size.x);
    status = (fgBool)(status && y < m_size.y);
    status = (fgBool)(status && z < m_size.z);
    status = (fgBool)(status && w < m_size.w);
    return status;
}
//------------------------------------------------------------------------------

#if defined(DEBUG) || defined(FG_DEBUG)

void game::CGrid::dump(void) {
    if(!m_data)
        return;
    printf("fg::game::CGrid::dump(): size[%d][%d][%d][%d]\n", m_size.x,
           m_size.y,
           m_size.z,
           m_size.w);
    unsigned short ix, iy, iz, iw;
    for(iw = 0; iw < m_size.w; iw++) {
        printf("==== W[%d] ==== ==== ====\n", iw);
        for(iz = 0; iz < m_size.z; iz++) {
            printf("==== Z[%d] ==== ==== ====\n", iz);
            printf("    ");
            for(ix = 0; ix < m_size.x; ix++) {
                printf("%.3d ", ix);
            }
            printf("\n");
            for(iy = 0; iy < m_size.y; iy++) {

                printf("%.3d ", iy);
                for(ix = 0; ix < m_size.x; ix++) {
                    printf("%3d ", m_data[iw][iz][iy][ix].value);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
}
#endif
//------------------------------------------------------------------------------
