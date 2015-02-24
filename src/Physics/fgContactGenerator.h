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
 * Interface file for the contact resolution system.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */
/* 
 * File:   fgContactGenerator.h
 * Author: vigilant
 *
 * Created on February 5, 2015, 10:34 PM
 */

#ifndef FG_INC_CONTACT_GENERATOR
    #define FG_INC_CONTACT_GENERATOR
    #define FG_INC_CONTACT_GENERATOR_BLOCK

namespace fg {
    namespace physics {

        class CContact;

        /**
         * This is the basic polymorphic interface for contact generators
         * applying to rigid bodies.
         */
        class CContactGenerator {
        public:
            /**
             * Fills the given contact structure with the generated
             * contact. The contact pointer should point to the first
             * available contact in a contact array, where limit is the
             * maximum number of contacts in the array that can be written
             * to. The method returns the number of contacts that have
             * been written.
             */
            virtual unsigned addContact(CContact *contact, unsigned limit) const = 0;
        };

    } // namespace physics
} // namespace fg 

    #undef FG_INC_CONTACT_GENERATOR_BLOCK
#endif	/* FG_INC_CONTACT_GENERATOR */
