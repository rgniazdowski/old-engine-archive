/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_PROFILING_H_
#define _FG_PROFILING_H_

#include "fgCommon.h"
#include <stack>
#include <hash_map>

#define FG_MAX_PROFILE_SAMPLES 10

/*
 * Struct for profile sample. Holds various info: name, time started,
 * accumulated values
 */
struct fgProfileSample
{
	fgBool isValid;				// Whether this data is valid
	unsigned int numInstances;	// Number of times profile begin called
	unsigned int numOpen;		// Number of times opened w/o profile end
	std::string name;			// Name of sample
	float startTime;			// The current open profile start time
	float accumulator;			// All samples this frame added together
	float childrenSampleTime;	// Time taken by all children
	unsigned int numParents;	// Number of profile parents

	fgProfileSample() : isValid(FG_FALSE), numInstances(0),
		numOpen(0), startTime(-1.0f), accumulator(0.0f), 
		childrenSampleTime(-1.0f), numParents(0) {
	}
};

//
struct fgProfileSampleHistory
{
	fgBool isValid;		// whether the data is valid
	std::string name;	// name of sample
	float average;		// average time per frame (percentage)
	float minimum;		// minimum time per frame %
	float maximum;		// maximum time per frame %

	fgProfileSampleHistory() : isValid(FG_FALSE), average(0.0f),
		minimum(0.0f), maximum(0.0f) {
	}
};

#ifndef FG_HASH_STD_STRING_TEMPLATE_DEFINED_
#define FG_HASH_STD_STRING_TEMPLATE_DEFINED_

namespace std
{
	template<> struct hash<std::string>
	{
		size_t operator()(const std::string& x) const
		{
			return hash<const char*>()(x.c_str());
		}
	};
};

#endif /* FG_HASH_STD_STRING_TEMPLATE_DEFINED_ */

/*
 *
 */
class fgProfiling
{

protected:
	struct profileEqualTo
	{
		bool operator()(const char* s1, const char* s2) const
		{
			return strcmp(s1, s2) == 0;
		}

		bool operator()(const std::string& s1, const std::string& s2) const
		{
			return s1.compare(s2) == 0;
		}
	};
protected:
	typedef std::stack<fgProfileSample *> profileStack;
	typedef std::string hashKey;
	typedef std::hash<std::string> hashFunc;
	typedef std::hash_map <std::string, fgProfileSample *, hashFunc, profileEqualTo> profileMap;
	typedef profileMap::iterator profileMapItor;
	typedef std::hash_map <std::string, fgProfileSampleHistory *, hashFunc, profileEqualTo> historyMap;
	typedef historyMap::iterator historyMapItor;
	typedef fgArrayVector<fgProfileSample *> profileVec;
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
	~fgProfiling();

	// Initialize the profiling
	void initialize(void);
	// Clear all data, reset
	void clear(void);

	// Open given profile (begin calculations)
	fgBool begin(std::string& name);
	// Open given profile (begin calculations)
	fgBool begin(const char* name);

	// End given profile (stop)
	fgBool end(std::string& name);
	// End given profile (stop)
	fgBool end(const char *name);

	// Update the history, count average values
	void updateHistory(void);

	// Store the current profile in history
	fgBool storeProfileHistory(std::string& name, float percent);
	// Get profile informatione from history
	fgBool getProfileHistory(std::string& name, float* average, float* minimum, float* maximum);
};

#endif /* _FG_PROFILING_H_ */
