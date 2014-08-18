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

//
struct fgProfileSample
{
	fgBool isValid;				// whether this data is valid
	unsigned int numInstances;	// number of times profile begin called
	unsigned int numOpen;		// number of times opened w/o profile end
	std::string name;			// name of sample
	float startTime;			// the current open profile start time
	float accumulator;			// all samples this frame added together
	float childrenSampleTime;	// time taken by all children
	unsigned int numParents;	// number of profile parents

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
	profileStack m_profileStack;
	profileVec m_orderVec;
	profileMap m_sampleMap;
	historyMap m_sampleHistory;
	float m_startProfile;
	float m_endProfile;
public:
	fgProfiling();
	~fgProfiling();

	void init(void);
	void clear(void);

	fgBool begin(std::string& name);
	fgBool begin(const char* name);

	fgBool end(std::string& name);
	fgBool end(const char *name);

	void updateHistory(void);

	fgBool storeProfileHistory(std::string& name, float percent);
	fgBool getProfileHistory(std::string& name, float* average, float* minimum, float* maximum);
};

#endif /* _FG_PROFILING_H_ */
