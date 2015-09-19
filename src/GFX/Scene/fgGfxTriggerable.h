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
 * File:   fgGfxTriggerable.h
 * Author: vigilant
 *
 * Created on September 19, 2015, 10:52 AM
 */

#ifndef FG_INC_GFX_TRIGGERABLE
    #define FG_INC_GFX_TRIGGERABLE
    #define FG_INC_GFX_TRIGGERABLE_BLOCK

    #include "fgGfxTraits.h"
    #include "fgBool.h"
    #include "fgVector.h"

namespace fg {
    namespace event {
        class CArgumentList;
    } // namespace event

    namespace gfx {

        class CSceneNode;
        class CSceneCallback;

        namespace traits {

            /**
             * 
             */
            class CTriggerable {
            public:
                typedef CTriggerable self_type;
                typedef CTriggerable type;

            public:
                static const SceneNode SELF_TRAIT = SceneNode::TRIGGERABLE;

            public:

                enum TriggerActivation {
                    ON_COLLISION_BEGIN = 0,
                    ON_COLLISION_END = 1
                };

                enum TriggerShape {
                    BOX,
                    SPHERE,
                    PLANE
                };

            protected:

                /**
                 *
                 */
                struct STriggerInfo {
                    /**
                     *
                     */
                    CSceneCallback* pCallback;
                    /**
                     *
                     */
                    TriggerActivation activation;
                    /**
                     *
                     */
                    STriggerInfo();
                    /**
                     *
                     * @param callback
                     * @param onActivate
                     */
                    STriggerInfo(CSceneCallback *callback, TriggerActivation activationType = ON_COLLISION_BEGIN);
                    /**
                     *
                     */
                    void Call(void);
                    /**
                     *
                     * @param argv
                     */
                    void Call(event::CArgumentList* argv);
                    /**
                     *
                     * @param pSystemData
                     */
                    void Call(void* pSystemData);
                    /**
                     *
                     * @param pNodeA
                     */
                    void Call(CSceneNode* pNodeA);
                    /**
                     *
                     * @param pNodeA
                     * @param pNodeB
                     */
                    void Call(CSceneNode* pNodeA, CSceneNode* pNodeB);
                }; // struct TriggerInfo

                ///
                typedef CVector<STriggerInfo> CallbacksVec;
                ///
                typedef CallbacksVec::iterator CallbacksVecItor;

                //--------------------------------------------------------------
            public:
                /**
                 *
                 */
                CTriggerable();
                /**
                 *
                 * @param orig
                 */
                CTriggerable(const CTriggerable& orig);
                /**
                 *
                 */
                virtual ~CTriggerable();

            public:
                /**
                 *
                 * @param pCallback
                 * @param activationType
                 */
                void addCallback(CSceneCallback *pCallback, TriggerActivation activationType);
                /**
                 *
                 * @param pCallback
                 */
                void removeCallback(CSceneCallback *pCallback);
                /**
                 *
                 * @param pCallback
                 */
                fgBool checkCallback(CSceneCallback *pCallback);
                /**
                 *
                 * @param activationType
                 */
                void trigger(TriggerActivation activationType,
                             CSceneNode* pNodeA,
                             CSceneNode* pNodeB = NULL);
                /**
                 *
                 * @return
                 */
                inline unsigned int getCallbacksCount(void) const {
                    return m_callbacks.size();
                }
                /**
                 *
                 * @return
                 */
                inline fgBool hasCallbacks(void) const {
                    return (fgBool)!!getCallbacksCount();
                }

            protected:
                /**
                 *
                 * @return
                 */
                CallbacksVec& getCallbacks(void) {
                    return m_callbacks;
                }
                /**
                 *
                 * @return
                 */
                CallbacksVec const& getCallbacks(void) const {
                    return m_callbacks;
                }
            private:
                ///
                CallbacksVec m_callbacks;
            }; // class CTriggerable

        } // namespace traits
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_TRIGGERABLE_BLOCK
#endif	/* FG_INC_GFX_TRIGGERABLE */
