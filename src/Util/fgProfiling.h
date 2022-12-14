/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_PROFILING
    #define FG_INC_PROFILING
    #define FG_INC_PROFILING_BLOCK

    #include "fgCommon.h"
    #include <stack>

    #define FG_MAX_PROFILE_SAMPLES 16

    #if 1
        #include <unordered_map>
    #endif

namespace fg {
    namespace profile {

        /**
         * Structure for profile sample. Holds various info: name, time started,
         * accumulated values
         */
        struct SSample {
            /// Whether this data is valid
            fgBool isValid;
            /// Number of times profile begin called
            unsigned int numInstances;
            /// Number of times opened w/o profile end
            unsigned int numOpen;
            /// Name of sample
            std::string name;
            /// The current open profile start time
            float startTime;
            /// All samples this frame added together
            float accumulator;
            /// Time taken by all children
            float childrenSampleTime;
            /// Number of profile parents
            unsigned int numParents;
            /**
             * 
             */
            SSample() : isValid(FG_FALSE), numInstances(0),
            numOpen(0), name("\0"), startTime(-1.0f), accumulator(0.0f),
            childrenSampleTime(-1.0f), numParents(0) { }
        }; // struct SSample

        /**
         *
         */
        struct SSampleHistory {
            /// Whether the data is valid
            fgBool isValid;
            /// Name of sample
            std::string name;
            /// Average time per frame (percentage)
            float average;
            /// Minimum time per frame %
            float minimum;
            /// Maximum time per frame %
            float maximum;
            /**
             * 
             */
            SSampleHistory() : isValid(FG_FALSE), name("\0"), average(0.0f),
            minimum(0.0f), maximum(0.0f) { }
        }; // struct SSampleHistory

        /**
         *
         */
        class CProfiling {
    
        protected:
            ///
            typedef std::stack<SSample *> ProfileStack;
            ///
            typedef std::string HashKey;
    #if 1
            ///
            typedef std::unordered_map <HashKey, SSample *> ProfileMap;
            ///
            typedef std::unordered_map <HashKey, SSampleHistory *> HistoryMap;
    #endif
            ///
            typedef std::pair<std::string, SSample *> ProfileMapPair;
            ///
            typedef std::pair<std::string, SSampleHistory *> HistoryMapPair;
            ///
            typedef ProfileMap::iterator ProfileMapItor;
            ///
            typedef HistoryMap::iterator HistoryMapItor;
            ///
            typedef fg::CVector<SSample *> ProfileVec;
            ///
            typedef ProfileVec::iterator ProfileVecItor;

        private:
            /// Stack holding currently open samples (active) in order
            ProfileStack m_profileStack;
            /// Stack holding all profiles in order in which they were added
            ProfileVec m_orderVec;
            /// Map for binding string id (name) to profile info structure
            ProfileMap m_sampleMap;
            /// Map holding history records (for average values)
            HistoryMap m_sampleHistory;
            /// When the profiling started (frame)
            float m_startProfile;
            /// When the profiling ended
            float m_endProfile;

        public:
            /**
             * Base constructor for Profiling object
             */
            CProfiling();
            /**
             * Destructor for Profiling object
             */
            virtual ~CProfiling();

            /**
             * Initialize the profiling
             */
            void initialize(void);
            /**
             * Clear all data, reset
             */
            void clear(void);

            /**
             * Open given profile (begin calculations)
             * @param name
             * @return 
             */
            fgBool begin(const std::string& name);
            /**
             * Open given profile (begin calculations)
             * @param name
             * @return 
             */
            fgBool begin(const char* name);

            /**
             * End given profile (stop)
             * @param name
             * @return 
             */
            fgBool end(const std::string& name);
            /**
             * End given profile (stop)
             * @param name
             * @return 
             */
            fgBool end(const char *name);

            /**
             * Update the history, count average values
             */
            void updateHistory(void);

            /**
             * 
             */
            void dumpToDefaultFile(void);

            /**
             * Store the current profile in history
             * @param name
             * @param percent
             * @return 
             */
            fgBool storeProfileHistory(const std::string& name, float percent);
            /**
             * Get profile information from history
             * @param name
             * @param average
             * @param minimum
             * @param maximum
             * @return 
             */
            fgBool getProfileHistory(const std::string& name,
                                     float* average,
                                     float* minimum,
                                     float* maximum);
        }; // class CProfiling

    } // namespace profile
} // namespace fg

namespace fg {
    namespace profile {

    #if defined(FG_DEBUG)
        ///
        extern CProfiling *g_debugProfiling;
    #endif
    } // namespace profile
} // namespace fg

    #undef FG_INC_PROFILING_BLOCK
#endif /* FG_INC_PROFILING */
