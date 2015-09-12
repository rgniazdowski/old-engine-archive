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
 * File:   fgGFXSceneNodeTrigger.h
 * Author: vigilant
 *
 * Created on February 18, 2015, 10:34 PM
 */

#ifndef FG_INC_GFX_SCENE_NODE_TRIGGER
    #define FG_INC_GFX_SCENE_NODE_TRIGGER
    #define FG_INC_GFX_SCENE_NODE_TRIGGER_BLOCK

    #ifndef FG_INC_GFX_SCENE_NODE
        #include "fgGfxSceneNode.h"
    #endif

    #include "fgGfxSceneCallback.h"

namespace fg {
    namespace gfx {

        class CSceneCallback;
        class CSceneManager;

        /**
         *
         */
        class CSceneNodeTrigger : public CSceneNode {
            friend CSceneManager;
        public:
            ///
            typedef CSceneNode base_type;
            ///
            typedef CSceneNodeTrigger self_type;
            ///
            typedef CSceneNodeTrigger type;

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
            struct TriggerInfo {
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
                TriggerInfo() : pCallback(NULL), activation(ON_COLLISION_BEGIN) { }
                /**
                 * 
                 * @param callback
                 * @param onActivate
                 */
                TriggerInfo(CSceneCallback *callback, TriggerActivation activationType = ON_COLLISION_BEGIN) :
                pCallback(callback), activation(activationType) { }
                /**
                 * 
                 */
                inline void Call(void) {
                    if(pCallback) pCallback->Call();
                }
                /**
                 * 
                 * @param argv
                 */
                inline void Call(event::CArgumentList* argv) {
                    if(pCallback) pCallback->Call(argv);
                }
                /**
                 * 
                 * @param pSystemData
                 */
                inline void Call(void* pSystemData) {
                    if(pCallback) pCallback->Call(pSystemData);
                }
                /**
                 * 
                 * @param pNodeA
                 */
                inline void Call(CSceneNode* pNodeA) {
                    if(pCallback) pCallback->Call(pNodeA);
                }
                /**
                 * 
                 * @param pNodeA
                 * @param pNodeB
                 */
                inline void Call(CSceneNode* pNodeA, CSceneNode* pNodeB) {
                    if(pCallback) pCallback->Call(pNodeA, pNodeB);
                }
            };

            ///
            typedef CVector<TriggerInfo> CallbacksVec;
            ///
            typedef CallbacksVec::iterator CallbacksVecItor;

        public:
            /**
             * 
             */
            CSceneNodeTrigger();
            /**
             * 
             * @param orig
             */
            CSceneNodeTrigger(const CSceneNodeTrigger& orig);
            /**
             * 
             */
            virtual ~CSceneNodeTrigger();

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param bodyType
             */
            virtual void setCollisionBodyType(const physics::CCollisionBody::BodyType bodyType);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param position
             */
            virtual void setPosition(const Vec3f& position);
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            virtual void setPosition(float x, float y, float z);
            /**
             * 
             * @param translation
             */
            virtual void translate(const Vec3f& translation);

            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            virtual void translate(float x, float y, float z);

            using base_type::setScale;

            /**
             * 
             * @param scale
             */
            virtual void setScale(const Vector3f& scale);

            //------------------------------------------------------------------
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
            void trigger(TriggerActivation activationType, CSceneNode* pNodeB = NULL);
            /**
             * 
             * @return 
             */
            inline unsigned int numCallbacks(void) const {
                return m_callbacks.size();
            }
            /**
             * 
             * @return 
             */
            inline fgBool hasCallbacks(void) const {
                return (fgBool)!!numCallbacks();
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
        }; // class CSceneNodeTrigger

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_NODE_TRIGGER_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_TRIGGER */
