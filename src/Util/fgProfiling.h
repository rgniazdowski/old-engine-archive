/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_PROFILING
    #define FG_INC_PROFILING

    #include "fgCommon.h"
    #include <stack>

    #define FG_MAX_PROFILE_SAMPLES 16

/*
 * Struct for profile sample. Holds various info: name, time started,
 * accumulated values
 */
struct fgProfileSample {
    fgBool isValid; // Whether this data is valid
    unsigned int numInstances; // Number of times profile begin called
    unsigned int numOpen; // Number of times opened w/o profile end
    std::string name; // Name of sample
    float startTime; // The current open profile start time
    float accumulator; // All samples this frame added together
    float childrenSampleTime; // Time taken by all children
    unsigned int numParents; // Number of profile parents
    fgProfileSample() : isValid(FG_FALSE), numInstances(0),
    numOpen(0), name("\0"), startTime(-1.0f), accumulator(0.0f),
    childrenSampleTime(-1.0f), numParents(0) { 
    }
};


struct fgProfileSampleHistory {
    fgBool isValid; // whether the data is valid
    std::string name; // name of sample
    float average; // average time per frame (percentage)
    float minimum; // minimum time per frame %
    float maximum; // maximum time per frame %
    fgProfileSampleHistory() : isValid(FG_FALSE), name("\0"), average(0.0f),
    minimum(0.0f), maximum(0.0f) { }
};

    #ifdef FG_USING_MARMALADE
        #include <hash_map>
        #include <map>

        #ifndef FG_HASH_STD_STRING_TEMPLATE_DEFINED_
            #define FG_HASH_STD_STRING_TEMPLATE_DEFINED_

namespace std {

    template<> struct hash<std::string> {
        size_t operator ()(const std::string& x) const {
            return hash<const char*>()(x.c_str());
        }
    };
};

        #endif // FG_HASH_STD_STRING_TEMPLATE_DEFINED_ 
    #else
        #include <unordered_map>
    #endif // FG_USING_MARMALADE

/*
 *
 */
class fgProfiling {
    #ifdef FG_USING_MARMALADE
protected:

    struct profileEqualTo {
        bool operator ()(const char* s1, const char* s2) const {
            return strcmp(s1, s2) == 0;
        }
        bool operator ()(const std::string& s1, const std::string& s2) const {
            return s1.compare(s2) == 0;
        }
    };
    struct profileLessTo {
        bool operator ()(const char* s1, const char* s2) const {
            return strcmp(s1, s2) == -1;
        }
        bool operator ()(const std::string& s1, const std::string& s2) const {
            return s1.compare(s2) == -1;
        }
    };
    #endif // FG_USING_MARMALADE
protected:
    ///
    typedef std::stack<fgProfileSample *> profileStack;
    ///
    typedef std::string hashKey;
    #ifdef FG_USING_MARMALADE
    ///
    typedef std::hash<std::string> hashFunc;
    //typedef std::hash_map<hashKey, fgProfileSample *, hashFunc, profileEqualTo> profileMap;   // #FIXME #WTF
    //typedef std::hash_map<hashKey, fgProfileSampleHistory *, hashFunc, profileEqualTo> historyMap; // #FIXME #WTF
    ///
    typedef std::map<hashKey, fgProfileSample *, profileLessTo> profileMap;
    ///
    typedef std::map<hashKey, fgProfileSampleHistory *, profileLessTo> historyMap;
    #else
    ///
    typedef std::unordered_map <hashKey, fgProfileSample *> profileMap;
    ///
    typedef std::unordered_map <hashKey, fgProfileSampleHistory *> historyMap;
    #endif
    ///
    typedef std::pair<std::string, fgProfileSample *> profileMapPair;
    ///
    typedef std::pair<std::string, fgProfileSampleHistory *> historyMapPair;
    ///
    typedef profileMap::iterator profileMapItor;
    ///
    typedef historyMap::iterator historyMapItor;
    ///
    typedef fg::CVector<fgProfileSample *> profileVec;
    ///
    typedef profileVec::iterator profileVecItor;
    
private:
    // Stack holding currently open samples (active) in order
    profileStack m_profileStack;
    // Stack holding all profiles in order in which they were added
    profileVec m_orderVec;
    // Map for binding string id (name) to profile info structure
    profileMap m_sampleMap;
    // Map holding history records (for average values)
    historyMap m_sampleHistory;
    // When the profiling started (frame)
    float m_startProfile;
    // When the profiling ended
    float m_endProfile;
public:
    // Base constructor for Profiling object
    fgProfiling();
    // Base destructor for Profiling object
    virtual ~fgProfiling();

    // Initialize the profiling
    void initialize(void);
    // Clear all data, reset
    void clear(void);

    // Open given profile (begin calculations)
    fgBool begin(const std::string& name);
    // Open given profile (begin calculations)
    fgBool begin(const char* name);

    // End given profile (stop)
    fgBool end(const std::string& name);
    // End given profile (stop)
    fgBool end(const char *name);

    // Update the history, count average values
    void updateHistory(void);
    
    void dumpToDefaultFile(void);

    // Store the current profile in history
    fgBool storeProfileHistory(const std::string& name, float percent);
    // Get profile information from history
    fgBool getProfileHistory(const std::string& name,
                             float* average,
                             float* minimum,
                             float* maximum);
};

    #if defined(FG_DEBUG)
extern fgProfiling *g_debugProfiling;
    #endif

#endif /* FG_INC_PROFILING */
