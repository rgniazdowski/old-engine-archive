/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgProfiling.h"
#include "fgTime.h"
#include "fgRegularFile.h"

using namespace fg;

//------------------------------------------------------------------------------

#if defined(FG_DEBUG)
///
profile::CProfiling *profile::g_debugProfiling = NULL;
#endif
//------------------------------------------------------------------------------

profile::CProfiling::CProfiling() : m_startProfile(-1.0f), m_endProfile(-1.0f) { }
//------------------------------------------------------------------------------

profile::CProfiling::~CProfiling() {
    clear();
}
//------------------------------------------------------------------------------

void profile::CProfiling::initialize(void) {
    m_startProfile = timesys::exact();
}
//------------------------------------------------------------------------------

void profile::CProfiling::clear(void) {
    while(!m_profileStack.empty())
        m_profileStack.pop();
    m_sampleMap.clear();
    m_sampleHistory.clear();
    m_orderVec.clear_optimised();
    m_startProfile = 0.0f;
    m_endProfile = 0.0f;
}
//------------------------------------------------------------------------------

fgBool profile::CProfiling::begin(const std::string& name) {
    if(name.empty())
        return FG_FALSE;
    ProfileMapPair query_pair;
    query_pair.first = name;
    query_pair.second = NULL;
    std::pair<ProfileMapItor, bool> result = m_sampleMap.insert(query_pair);
    ProfileMapItor &it = result.first;
    SSample *sample = it->second;
    //if(!sample)
    //    return FG_FALSE;
    if(result.second == false && sample && sample->isValid) {
        //delete query_pair.second;
        //query_pair.second = NULL;
        // Existed
        if(sample->numOpen) {
            // max 1 open at once
            return FG_FALSE;
        }
        sample->numOpen++;
        sample->numInstances++;
        sample->startTime = timesys::exact();
        //sample->isValid = FG_TRUE;
    } else {
        // New insertion
        if(m_sampleMap.size() > FG_MAX_PROFILE_SAMPLES) {
            if(result.second) {
                //delete query_pair.second;
                //query_pair.second = NULL;
                //it->second = NULL; // ?
            }
            m_sampleMap.erase(it);
            return FG_FALSE;
        }
        if(!sample)
            it->second = new SSample();
        sample = it->second;

        sample->isValid = FG_TRUE;
        sample->numOpen = 1;
        sample->numInstances = 1;
        sample->accumulator = 0.0f;
        sample->startTime = timesys::exact();
        sample->childrenSampleTime = 0.0f;
        sample->name = name;
        if(result.second)
            m_orderVec.push_back(sample);
    }

    if(sample)
        m_profileStack.push(sample);

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool profile::CProfiling::begin(const char* name) {
    if(!name)
        return FG_FALSE;
    std::string strName = std::string(name);
    return begin(strName);
}
//------------------------------------------------------------------------------

fgBool profile::CProfiling::end(const std::string& name) {
    if(name.empty())
        return FG_FALSE;

    ProfileMapItor it = m_sampleMap.find(name);
    if(it == m_sampleMap.end())
        return FG_FALSE;
    SSample *sample = it->second;
    if(!sample)
        return FG_FALSE;
    if(!sample->isValid || !sample->numOpen)
        return FG_FALSE;
    sample->numOpen--;
    float endTime = timesys::exact();
    m_profileStack.pop();
    sample->numParents = m_profileStack.size();
    if(sample->numParents) {
        SSample *parent = m_profileStack.top();
        if(parent->isValid)
            parent->childrenSampleTime += endTime - sample->startTime;
    }
    sample->accumulator += endTime - sample->startTime;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool profile::CProfiling::end(const char* name) {
    if(!name)
        return FG_FALSE;
    std::string strName;
    strName.append(name);
    return end(strName);
}
//------------------------------------------------------------------------------

void profile::CProfiling::updateHistory(void) {
    m_endProfile = timesys::exact();

    ProfileVecItor begin = m_orderVec.begin(), end = m_orderVec.end(), it;
    for(it = begin; it != end; it++) {
        SSample *sample = (*it);
        if(!sample->isValid)
            continue;
        sample->isValid = FG_FALSE;
        float sampleTime, percentTime, aveTime, minTime, maxTime;
        sampleTime = sample->accumulator - sample->childrenSampleTime;
        percentTime = (sampleTime / (m_endProfile - m_startProfile))*100.0f;
        aveTime = minTime = maxTime = percentTime;
        storeProfileHistory(sample->name, percentTime);
    }
    m_startProfile = timesys::exact();
}
//------------------------------------------------------------------------------

void profile::CProfiling::dumpToDefaultFile(void) {
    ProfileVecItor begin = m_orderVec.begin(), end = m_orderVec.end(), it;
    fg::util::CRegularFile file;
    file.open("defaultProfile.log", fg::util::CRegularFile::Mode::WRITE);
    long timestamp = timesys::seconds();
    struct tm *ti;
    ti = localtime(&timestamp);

    file.print("\n%02d/%02d/%02d %02d:%02d:%02d: Profiles Dump\n",
               ti->tm_mday,
               ti->tm_mon + 1,
               ti->tm_year - 100,
               ti->tm_hour,
               ti->tm_min,
               ti->tm_sec);
    file.print("  Ave :   Min :   Max :   # : Profile Name\n");
    file.print("--------------------------------------------\n");
    for(it = begin; it != end; it++) {
        SSample *sample = (*it);
        //if(!sample->isValid)
        //    continue;
        unsigned int indent = 0;
        float aveTime, minTime, maxTime;
        char line[256], name[256], indentedName[256];
        char ave[16], min[16], max[16], num[16];
        this->getProfileHistory(sample->name, &aveTime, &minTime, &maxTime);
        //Format the data
        sprintf(ave, "%3.1f", aveTime);
        sprintf(min, "%3.1f", minTime);
        sprintf(max, "%3.1f", maxTime);
        sprintf(num, "%3d", sample->numInstances);

        strcpy(indentedName, sample->name.c_str());
        for(indent = 0; indent < sample->numParents; indent++) {
            sprintf(name, "   %s", indentedName);
            strcpy(indentedName, name);
        }

        sprintf(line, "%5s : %5s : %5s : %3s : %s\n", ave, min, max, num, indentedName);
        file.print(line);

    }
    file.close();
}
//------------------------------------------------------------------------------

fgBool profile::CProfiling::storeProfileHistory(const std::string& name, float percent) {
    if(name.empty())
        return FG_FALSE;
    float oldRatio;
    float newRatio = 0.8f * timesys::elapsed();
    if(newRatio > 1.0f) {
        newRatio = 1.0f;
    }
    oldRatio = 1.0f - newRatio;
    std::pair<std::string, SSampleHistory *> query_pair;
    query_pair.first = name;
    query_pair.second = NULL;
    std::pair<HistoryMapItor, bool> result = m_sampleHistory.insert(query_pair);
    HistoryMapItor it = result.first;
    SSampleHistory *sample = it->second;
    //if(!sample)
    //    return FG_FALSE;
    if(result.second == false && sample) {
        // Sample existed #FIXME -- too much allocs
        //delete query_pair.second;
        //query_pair.second = NULL;
        //sample = it->second;
        // Existed
        sample->average = sample->average * oldRatio + (percent * newRatio);
        if(percent < sample->minimum) {
            sample->minimum = percent;
        } else {
            sample->minimum = sample->minimum * oldRatio + (percent * newRatio);
        }
        if(sample->minimum < 0.0f)
            sample->minimum = 0.0f;
        if(percent > sample->maximum) {
            sample->maximum = percent;
        } else {
            sample->maximum = sample->maximum * oldRatio + (percent * newRatio);
        }
    } else {
        // New insertion
        if(m_sampleHistory.size() > FG_MAX_PROFILE_SAMPLES) {
            //delete it->second;
            //it->second = NULL;
            m_sampleHistory.erase(it);
            return FG_FALSE;
        }
        if(!sample)
            it->second = new SSampleHistory();
        sample = it->second;
        sample->isValid = FG_TRUE;
        sample->name = name;
        sample->average = sample->minimum = sample->maximum = percent;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool profile::CProfiling::getProfileHistory(const std::string& name,
                                              float* average,
                                              float* minimum,
                                              float *maximum) {
    if(name.empty())
        return FG_FALSE;
    HistoryMapItor it = m_sampleHistory.find(name);
    if(it == m_sampleHistory.end())
        return FG_FALSE;
    SSampleHistory *entry = it->second;
    if(!entry)
        return FG_FALSE;
    if(average)
        *average = entry->average;
    if(minimum)
        *minimum = entry->minimum;
    if(maximum)
        *maximum = entry->maximum;
    return FG_TRUE;
}
//------------------------------------------------------------------------------
