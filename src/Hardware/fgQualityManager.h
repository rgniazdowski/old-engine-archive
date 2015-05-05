/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_QUALITY_MANAGER
    #define FG_INC_QUALITY_MANAGER
    #define FG_INC_QUALITY_MANAGER_BLOCK

    #include "fgQualityTypes.h"
    #include "fgManagerBase.h"

    #include <map>
    #include <string>

    #define FG_QUALITY_DEFAULT      Quality::MEDIUM

    #define FG_MANAGER_QUALITY      0x00002000

namespace fg {

    /**
     * Currently quality manager is used solely for simple quality check
     * It uses screen resolution to determine if device is powerful enough
     * This is kinda slick - however it is bound to errors and works (?) only
     * for mobile platforms
     *
     * QualityManager is for determining what quality is currently available
     * It should manage it by screen resolution which is a good hint regarding
     * the power of the device as higher resolutions are on more powerful devices
     * also QM can determine quality by the device ID and generation
     * QM cant hold any information about the textures and other
     *
     * This is bound to change in the future
     * Let's call this version v0.1
     */
    class CQualityManager : public fg::base::CManager {
    public:
        typedef CQualityManager self_type;
        typedef CQualityManager type;
        typedef fg::base::CManager base_type;

    private:
        typedef std::map<int, Quality> AreaQMap;
        typedef AreaQMap::iterator AreaQMapItor;

        /// Temporary map for storing display area sizes and corresponding quality
        /// This will work only for mobile platforms (iOS especially)
        /// Here the power of the given device is determined by max screen resolution
        /// This can apply only to phones/tablets. On PC platforms there will be needed
        /// some deeper checking / benchmarking...
        std::map<int, Quality> m_displayAreaQuality;
        /// Hardware quality - this is determined by display area (mobile platforms)
        Quality m_hardwareQuality;
        /// Forced quality - quality can be forced
        Quality m_forcedQuality;
        /// Selected quality (this quality is reported outside)
        Quality m_selectedQuality;
        ///
        int m_currentDispArea;

    public:
        /**
         * Default constructor for Quality Manager object
         */
        CQualityManager(const int dispArea = -1);
        /**
         * Default destructor for Quality Manager object
         */
        virtual ~CQualityManager();

    protected:
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
         * Determine quality via screen resolution (this is bound to change in the future)
         */
        void determineQuality(void);
        /**
         *
         * @param dispArea
         */
        void setDisplayArea(const int dispArea) {
            m_currentDispArea = dispArea;
        }
        /**
         *
         * @param w
         * @param h
         */
        void setDisplayArea(const int w, const int h) {
            m_currentDispArea = w * h;
        }
        /**
         * Set value for forced quality (set quality up front)
         * @param forceQuality
         */
        void setForcedQuality(Quality forceQuality) {
            m_forcedQuality = forceQuality;
            m_selectedQuality = m_forcedQuality;
        }
        /**
         * Set currently selected quality to determined via hardware (screen resolution)
         */
        void setHardwareQuality(void) {
            m_selectedQuality = m_hardwareQuality;
        }
        /**
         * Return true if currently set quality is hardware
         * @return
         */
        fgBool isHardwareQuality(void) const {
            return (fgBool)(m_hardwareQuality == m_selectedQuality);
        }
        /**
         * Get currently selected quality
         * @return
         */
        Quality getQuality(void) const {
            return m_selectedQuality;
        }
        /**
         * Get value for hardware quality
         * @return
         */
        Quality getHardwareQuality(void) const {
            return m_hardwareQuality;
        }
    };
} // namespace fg

    #undef FG_INC_QUALITY_MANAGER_BLOCK
#endif /* FG_INC_QUALITY_MANAGER */
