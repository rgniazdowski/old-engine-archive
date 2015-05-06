/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_HARDWARE_STATE
    #define FG_INC_HARDWARE_STATE
    #define FG_INC_HARDWARE_STATE_BLOCK

    #define FG_ORIENTATION_PORTRAIT     0
    #define FG_ORIENTATION_LANDSCAPE    1

    #define FG_FRAMES_COUNT_LIMIT       20
    #define FG_FRAMES_LIMIT             FG_FRAMES_COUNT_LIMIT
    #define FG_MAX_FPS                  60.0
    #define FG_FPS_LIMIT                FG_MAX_FPS

    #define FG_DEVICE_ORIENTATION       FG_ORIENTATION_LANDSCAPE

namespace fg {

    enum class ScreenOrientation : unsigned char {
        PORTRAIT,
        LANDSCAPE,
        DEFAULT = ScreenOrientation::LANDSCAPE
    };

    /**
     * The class holds only SIMPLE states, i.e. it does not
     * hold GameLogic object. Reason: to avoid including EVERYTHING here.
     */
    class CHardwareState {
    public:
        typedef CHardwareState self_type;
        typedef CHardwareState type;

    public:
        /**
         * Default constructor for Hardware State object
         */
        CHardwareState();
        /**
         * Destructor for Hardware State object
         */
        virtual ~CHardwareState();

    public:
        /**
         * Inits DPI. Called from GL init code, when display is ready
         */
        void initDPI(void);

        /**
         *
         * @param ms
         */
        void deviceYield(int ms = 0);

        /**
         * Calculate current FPS
         * @return
         */
        float calculateFPS(void);
        /**
         * Returns FPS
         * @return
         */
        float getFPS(void) const {
            return m_fps;
        }
        /**
         * Returns screen height
         * @return
         */
        int getScreenHeight(void) const {
            return m_screenHeight;
        }
        /**
         * Returns screen width
         * @return
         */
        int getScreenWidth(void) const {
            return m_screenWidth;
        }
        /**
         * Returns display area
         * @return
         */
        int getDisplayArea(void) const {
            return m_dispArea;
        }
        /**
         * Returns screen DPI
         * @return
         */
        int getDPI(void) const {
            return m_dpi;
        }
        /**
         * Returns horizontal (X) screen DPI
         * @return
         */
        int getXDPI(void) const {
            int sum = m_screenWidth + m_screenHeight;
            return int(float(m_screenWidth) / sum * m_dpi);
        }
        /**
         * Returns vertical (Y) screen DPI
         * @return
         */
        int getYDPI(void) const {
            int sum = m_screenWidth + m_screenHeight;
            return int(float(m_screenHeight) / sum * m_dpi);
        }
        /**
         * Returns screen display coefficient
         * @return
         */
        float getDisplayCoefficient(void) const {
            return m_dpiAndAreaCoef;
        }
        /**
         * Convert inches to pixels (from screen DPI)
         * @param inches
         * @return
         */
        int inchesToPixels(float inches) {
            return (int)(m_dpi * inches);
        }
        /**
         * Convert millimeters to pixels
         * @param mm
         * @return
         */
        int millimeterToPixels(float mm) {
            return (int)(m_dpi * mm / 25.4f);
        }
        /**
         * Convert inches to pixels horizontally
         * @param inches
         * @return
         */
        int inchesToPixelsX(float inches) {
            return (int)(getXDPI() * inches);
        }
        /**
         * Convert millimeters to pixels horizontally
         * @param mm
         * @return
         */
        int millimeterToPixelsX(float mm) {
            return (int)(getXDPI() * mm / 25.4f);
        }
        /**
         * Convert inches to pixels vertically
         * @param inches
         * @return
         */
        int inchesToPixelsY(float inches) {
            return (int)(getYDPI() * inches);
        }
        /**
         * Convert millimeters to pixels vertically
         * @param mm
         * @return
         */
        int millimeterToPixelsY(float mm) {
            return (int)(getYDPI() * mm / 25.4f);
        }
        /**
         * Set screen dimensions
         * @param screenWidth
         * @param screenHeight
         */
        void setScreenDimensions(int screenWidth, int screenHeight) {
            if(FG_DEVICE_ORIENTATION == FG_ORIENTATION_LANDSCAPE) {
                if(screenWidth > screenHeight) {
                    m_screenWidth = screenWidth;
                    m_screenHeight = screenHeight;
                } else {
                    m_screenWidth = screenHeight;
                    m_screenHeight = screenWidth;
                }
            } else {
                if(screenWidth > screenHeight) {
                    m_screenWidth = screenHeight;
                    m_screenHeight = screenWidth;
                } else {
                    m_screenWidth = screenWidth;
                    m_screenHeight = screenHeight;
                }
            }
            m_dispArea = m_screenHeight * m_screenWidth;
        }

    private:
        // Screen height
        int m_screenHeight;
        // Screen width
        int m_screenWidth;
        // Display area (WxH)
        int m_dispArea;
        // Current FPS (frames per second)
        float m_fps;
        // DPI of the screen
        int m_dpi;
        // Coefficient DisplayArea / DPI
        float m_dpiAndAreaCoef;
    };

} // namespace fg

    #undef FG_INC_HARDWARE_STATE_BLOCK
#endif /* FG_INC_HARDWARE_STATE */
