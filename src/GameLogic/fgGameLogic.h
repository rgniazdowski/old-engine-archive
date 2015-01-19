/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GAME_LOGIC
    #define FG_INC_GAME_LOGIC
    #define FG_INC_GAME_LOGIC_BLOCK

    #include "Event/fgEventDefinitions.h" // #FIXME



    #include "fgManagerBase.h"
    #include <queue>

    #define FG_MANAGER_LOGIC        0x0001000

namespace fg {
    namespace game {

        /// Event thrown when game just started (once)
        const event::EventType GAME_STARTED = (event::LAST_STANDARD_EVENT_CODE + 1);
        /// Event is thrown once when the game changes state to PAUSED
        const event::EventType GAME_PAUSED = (event::LAST_STANDARD_EVENT_CODE + 2);
        /// Event is thrown once when the game changes state to STOPPED
        const event::EventType GAME_STOPPED = (event::LAST_STANDARD_EVENT_CODE + 3);

        /// Event is thrown once when the game is starting loading stage/level/data
        const event::EventType GAME_LOADING = (event::LAST_STANDARD_EVENT_CODE + 4);
        /// Event is thrown once when the game is beginning to restart
        const event::EventType GAME_RESTARTING = (event::LAST_STANDARD_EVENT_CODE + 5);

        /// Event thrown on game finish (stage/level/whole)
        const event::EventType GAME_FINISHED = (event::LAST_STANDARD_EVENT_CODE + 6);
        /// Event is thrown once when the game is waiting for external input
        const event::EventType GAME_WAITING = (event::LAST_STANDARD_EVENT_CODE + 7);
        /// Event is thrown when the game connects successfully to the server
        const event::EventType GAME_CONNECTED = (event::LAST_STANDARD_EVENT_CODE + 8);
        /// Event is thrown when the game disconnects from the server
        const event::EventType GAME_DISCONNECTED = (event::LAST_STANDARD_EVENT_CODE + 9);


        const event::EventType LAST_GAME_EVENT_CODE = (event::LAST_STANDARD_EVENT_CODE + 9);

        /**
         *
         */
        class Logic : public fg::base::CManager {
        public:
            typedef fg::base::CManager base_type;
            ///
            typedef float score_type;

        public:

            enum class Status : unsigned char {
                /// Invalid game status - this cannot appear in normal gameplay.
                /// If so, it means unknown error 
                GAME_INVALID,
                /// Unknown game state - undefined - in most cases it will be
                /// treated the same as STOPPED
                GAME_UNKNOWN,
                /// Game is active, normal gameplay
                GAME_ACTIVE,
                /// Game is paused, in most cases this displays pause menu
                GAME_PAUSED,
                /// Game is not active/stopped - not even loading, normal nongame menu
                GAME_STOPPED,

                /// Game is loading - loading, populating assets
                GAME_LOADING,
                /// Game is restarting - releasing any required data, then loading again
                GAME_RESTARTING,
                /// Game is stopping - releasing any required data, later back to nongame menu
                GAME_STOPPING,

                /// Game is finishing - some midlevel presentation on level ending, showing
                /// game status, highscores etc, 
                GAME_FINISHING,
                /// Game is finished, very similar to the FINISHING status, however this state
                /// is when level is unloaded (required data released)
                GAME_FINISHED,

                /// Game is connecting to the server
                GAME_CONNECTING,
                /// Game is waiting for some external input (any kind)
                GAME_WAITING,
                /// Game disconnect from the server - any kind of reason
                /// This game state is for a very short period (in most cases max 1 frame)
                GAME_DISCONNECTED
            };
        public:
            /**
             * 
             */
            Logic(fg::base::CManager *pEventMgr);
            /**
             * 
             * @param orig
             */
            Logic(const Logic &orig);
            /**
             * 
             */
            virtual ~Logic();

        protected:
            /**
             * 
             * @param eventType
             * @return 
             */
            fgBool throwGameEvent(const event::EventType eventType);
            /**
             * 
             */
            virtual void clear(void);

        public:
            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void);
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void);

        public:
            /**
             * 
             * @param pEventMgr
             */
            void setEventManager(fg::base::CManager *pEventMgr) {
                m_pEventMgr = pEventMgr;
            }
            /**
             * 
             * @return 
             */
            inline fg::base::CManager *getEventManager(void) const {
                return m_pEventMgr;
            }
            /**
             * 
             * @return 
             */
            inline Status getStatus(void) const {
                return m_status;
            }
            /**
             * 
             * @return 
             */
            inline unsigned int getCurrentStageID(void) const {
                return m_currentStageID;
            }
            /**
             * 
             * @return 
             */
            inline std::string const &getCurrentStageName(void) const {
                return m_currentStageName;
            }
            /**
             * 
             * @return 
             */
            inline const char *getCurrentStageNameStr(void) const {
                return m_currentStageName.c_str();
            }
            /**
             * 
             * @return 
             */
            inline score_type getGlobalScore(void) const {
                return m_score;
            }
            /**
             * 
             * @return 
             */
            inline score_type getStageScore(void) const {
                return m_stageScore; // Maybe stage score hold in different structure (stage related data?)
            }
            /**
             * 
             * @param scoreDiff
             */
            inline void increaseStageScore(const score_type scoreDiff) {
                m_stageScore += scoreDiff;
            }
            /**
             * 
             */
            inline void resetStageScore(void) {
                m_stageScore = 0;
            }
            /**
             * 
             * @return 
             */
            inline std::string const & getPlayerName(void) const {
                return m_playerName;
            }
            /**
             * 
             * @return 
             */
            inline const char *getPlayerNameStr(void) const {
                return m_playerName.c_str();
            }
            /**
             * 
             * @param playerName
             */
            inline void setPlayerName(const char *playerName) {
                if(playerName)
                    m_playerName = playerName;
            }
            /**
             * 
             * @param playerName
             */
            inline void setPlayerName(const std::string &playerName) {
                m_playerName = playerName;
            }

        public:

            /**
             * 
             */
            void startGameDefault(void);
            /**
             * 
             * @param stageID
             */
            void startGame(const unsigned int stageID = 0);
            /**
             * 
             * @param stageName
             */
            void startGame(const std::string& stageName);
            /**
             * 
             * @param stageName
             */
            void startGame(const char *stageName);

            /**
             * 
             */
            void stopGame(void);
            /**
             * 
             */
            void pauseGame(void);
            /**
             * 
             */
            void restartGame(void);

        public:
            /**
             * 
             * @return 
             */
            fgBool isActive(void) const {
                return (fgBool)(m_status == Status::GAME_ACTIVE);
            }
            /**
             * 
             * @return 
             */
            fgBool isPaused(void) const {
                return (fgBool)(m_status == Status::GAME_PAUSED);
            }
            /**
             * 
             * @return 
             */
            fgBool isStopped(void) const {
                return (fgBool)(m_status == Status::GAME_STOPPED);
            }
            /**
             * 
             * @return 
             */
            fgBool isLoading(void) const {
                return (fgBool)(m_status == Status::GAME_LOADING);
            }
            /**
             * 
             * @return 
             */
            fgBool isRestarting(void) const {
                return (fgBool)(m_status == Status::GAME_RESTARTING);
            }
            /**
             * 
             * @return 
             */
            fgBool isStopping(void) const {
                return (fgBool)(m_status == Status::GAME_STOPPING);
            }
            /**
             * 
             * @return 
             */
            fgBool isFinishing(void) const {
                return (fgBool)(m_status == Status::GAME_FINISHING);
            }
            /**
             * 
             * @return 
             */
            fgBool isFinished(void) const {
                return (fgBool)(m_status == Status::GAME_FINISHED);
            }
            /**
             * 
             * @return 
             */
            fgBool isConnecting(void) const {
                return (fgBool)(m_status == Status::GAME_CONNECTING);
            }
            /**
             * 
             * @return 
             */
            fgBool isWaiting(void) const {
                return (fgBool)(m_status == Status::GAME_WAITING);
            }
            /**
             * 
             * @return 
             */
            fgBool isDisconnected(void) const {
                return (fgBool)(m_status == Status::GAME_DISCONNECTED);
            }

        public:
            /**
             * 
             */
            void update(void);

        protected:
            ///
            typedef std::queue<Status> StatusQueue;

        private:
            /// External pointer to the event manager
            fg::base::CManager *m_pEventMgr;
            ///
            Status m_status;
            ///
            StatusQueue m_statusQueue;
            /// Some stage/level abstract ID
            unsigned int m_currentStageID;
            /// Stage name
            std::string m_currentStageName;
            /// Current global score
            score_type m_score;
            /// Current stage score
            score_type m_stageScore;
            /// Player ID/Name/Nickname
            std::string m_playerName;
        };
    };
};

    #undef FG_INC_GAME_LOGIC_BLOCK
#endif /* FG_INC_GAME_LOGIC */
