/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_STYLE_CONTENT
    #define FG_INC_GUI_STYLE_CONTENT
    #define FG_INC_GUI_STYLE_CONTENT_BLOCK

    #include "fgBuildConfig.h"
    #include "fgTypes.h"

    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif

    #include "GFX/fgGfxColor.h"
    #include "GFX/fgGfxBoundingBox.h"

    #define FG_GUI_FLOAT_UNIT_INVALID       1280000.0f
    #define FG_GUI_CHECK_FLOAT(value)   (value < FG_GUI_FLOAT_UNIT_INVALID)

    #include "Util/fgConfigStruct.h"

    #define FG_GUI_DEFAULT_BORDER_STYLE SBorder::Style::SOLID
    #define FG_GUI_DEFAULT_BORDER_COLOR	Color4f(1.0f, 1.0f, 1.0f, 1.0f)
    #define FG_GUI_DEFAULT_BORDER_WIDTH	2.0f
    #define FG_GUI_DEFAULT_TEXT_SIZE	16.0f
    #define FG_GUI_DEFAULT_FONT		"StbCourier"
    #define FG_GUI_DEFAULT_FG_COLOR	Color4f(0.9f, 0.9f, 0.9f, 1.0f)
    #define FG_GUI_DEFAULT_MARGIN       8.0f
    #define FG_GUI_DEFAULT_PADDING      8.0f
    #define FG_GUI_DEFAULT_ALIGN	Align::CENTER
    #define FG_GUI_DEFAULT_VALIGN	Align::MIDDLE
    #define FG_GUI_DEFAULT_TEXT_ALIGN   (Align::CENTER | Align::MIDDLE)

    #define FG_GUI_DEFAULT_SIZE_STYLE   SSize::Style::INVALID_STYLE
    #define FG_GUI_DEFAULT_SIZE_X       FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_SIZE_Y       FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_SIZE_Z       FG_GUI_FLOAT_UNIT_INVALID

    #define FG_GUI_DEFAULT_POSITION_STYLE	SPosition::Style::STATICPOS
    #define FG_GUI_DEFAULT_POSITION_LEFT	FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_RIGTH	FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_TOP		FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_BOTTOM	FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_FRONT	FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_BACK	FG_GUI_FLOAT_UNIT_INVALID

namespace fg {
    namespace gui {

        /**
         *
         */
        enum class Unit : unsigned char {
            INVALID_UNIT,
            PIXELS,
            INCHES,
            BLOCKS,
            PERCENTS
        };

        /**
         *
         */
        struct SBorder {

            /**
             *
             */
            enum class Which : unsigned char {
                LEFT = 0x0001,
                RIGHT = 0x0002,
                TOP = 0x0004,
                BOTTOM = 0x0008,
                ALL = Which::LEFT | Which::RIGHT | Which::TOP | Which::BOTTOM
            };

            /**
             *
             */
            enum class Style : unsigned char {
                NONE,
                DOTTED,
                DASHED,
                SOLID
            };
            ///
            Style style;
            ///
            Color4f color;
            ///
            float width;
            /**
             * 
             * @param _width
             */
            SBorder(const float _width = FG_GUI_DEFAULT_BORDER_WIDTH) :
            style(FG_GUI_DEFAULT_BORDER_STYLE),
            color(FG_GUI_DEFAULT_BORDER_COLOR),
            width(_width) { }
            /**
             * 
             * @return 
             */
            operator Color4f() const {
                return color;
            }
            /**
             * 
             * @return 
             */
            operator SBorder::Style() const {
                return style;
            }
            /**
             * 
             * @return 
             */
            operator float() const {
                return width;
            }
        };

        /**
         *
         */
        struct SBackground {

            /**
             *
             */
            enum Style {
                NONE,
                NORMAL,
                MAX,
                TILED
            };
            ///
            Style style;
            ///
            std::string texture;
            ///
            Color4f color;
            /**
             * 
             */
            SBackground() :
            style(Style::MAX),
            texture(),
            color(0.4f, 0.4f, 0.4f, 0.8f) // Default
            { }
            /**
             * 
             * @return 
             */
            operator std::string() const {
                return texture;
            }
            /**
             * 
             * @return 
             */
            operator Color4f() const {
                return color;
            }
            /**
             * 
             * @return 
             */
            operator SBackground::Style() const {
                return style;
            }
        };

        /**
         *
         */
        struct SForeground {
            ///
            Unit unit;
            ///
            float textSize;
            ///
            std::string font;
            ///
            Color4f color;
            /**
             * 
             */
            SForeground() :
            unit(Unit::PIXELS),
            textSize(FG_GUI_DEFAULT_TEXT_SIZE),
            font(FG_GUI_DEFAULT_FONT),
            color(FG_GUI_DEFAULT_FG_COLOR) { }
        };

        /**
         *
         */
        struct SMargin {

            /**
             *
             */
            enum class Which : unsigned char {
                LEFT = 0x0001,
                RIGHT = 0x0002,
                TOP = 0x0004,
                BOTTOM = 0x0008,
                ALL = Which::LEFT | Which::RIGHT | Which::TOP | Which::BOTTOM
            };
            ///
            float value;
            ///
            float left;
            ///
            float right;
            ///
            float top;
            ///
            float bottom;
            /**
             * 
             */
            SMargin() :
            value(FG_GUI_DEFAULT_MARGIN),
            left(FG_GUI_DEFAULT_MARGIN),
            right(FG_GUI_DEFAULT_MARGIN),
            top(FG_GUI_DEFAULT_MARGIN),
            bottom(FG_GUI_DEFAULT_MARGIN) { }
            /**
             * 
             * @return 
             */
            operator float() const {
                return value;
            }
        };

        /**
         *
         */
        struct SPadding {

            /**
             *
             */
            enum class Which : unsigned char {
                LEFT = 0x0001,
                RIGHT = 0x0002,
                TOP = 0x0004,
                BOTTOM = 0x0008,
                ALL = Which::LEFT | Which::RIGHT | Which::TOP | Which::BOTTOM
            };
            ///
            float value;
            ///
            float left;
            ///
            float right;
            ///
            float top;
            ///
            float bottom;
            /**
             * 
             */
            SPadding() :
            value(FG_GUI_DEFAULT_MARGIN),
            left(FG_GUI_DEFAULT_MARGIN),
            right(FG_GUI_DEFAULT_MARGIN),
            top(FG_GUI_DEFAULT_MARGIN),
            bottom(FG_GUI_DEFAULT_MARGIN) { }
            /**
             * 
             * @return 
             */
            operator float() const {
                return value;
            }
        };

        /**
         * 
         */
        struct SBorderGroup {
            ///
            SBorder all;
            ///
            SBorder left;
            ///
            SBorder right;
            ///
            SBorder top;
            ///
            SBorder bottom;
            /**
             * 
             */
            SBorderGroup() :
            all(FG_GUI_DEFAULT_BORDER_WIDTH),
            left(FG_GUI_DEFAULT_BORDER_WIDTH),
            right(FG_GUI_DEFAULT_BORDER_WIDTH),
            top(FG_GUI_DEFAULT_BORDER_WIDTH),
            bottom(FG_GUI_DEFAULT_BORDER_WIDTH) { }

            // maybe some functions ?
        };

        /**
         *
         */
        enum class Align : unsigned char {
            NONE = 0x0000,
            LEFT = 0x0001,
            RIGHT = 0x0002,
            CENTER = 0x0004,
            MIDDLE = 0x0008,
            TOP = 0x0020,
            BOTTOM = 0x0040
        };

        /**
         *
         */
        struct SPosition {

            /**
             *
             */
            enum class Style : unsigned char {
                STATICPOS,
                FIXED,
                RELATIVE,
                ABSOLUTE
            };
            ///
            Style style;
            ///
            Unit unit;
            ///
            float left;
            ///
            float right;
            ///
            float top;
            ///
            float bottom;
            ///
            float front;
            ///
            float back;
            /**
             * 
             */
            SPosition() :
            style(FG_GUI_DEFAULT_POSITION_STYLE),
            unit(Unit::PIXELS),
            left(FG_GUI_DEFAULT_POSITION_LEFT),
            right(FG_GUI_DEFAULT_POSITION_RIGTH),
            top(FG_GUI_DEFAULT_POSITION_TOP),
            bottom(FG_GUI_DEFAULT_POSITION_BOTTOM),
            front(FG_GUI_DEFAULT_POSITION_FRONT),
            back(FG_GUI_DEFAULT_POSITION_BACK) {
                left = FG_GUI_FLOAT_UNIT_INVALID;
                right = left;
                top = left;
                bottom = left;
                front = left;
                back = left;
            }
            /**
             * 
             * @param pos
             */
            void set(const Vector3f& pos) {
                if(this->style != SPosition::Style::STATICPOS) {
                    if(pos.x <= 0.0f)
                        this->left = math::abs(pos.x);
                    else
                        this->right = pos.x;
                    if(pos.y <= 0.0f)
                        this->top = math::abs(pos.y);
                    else
                        this->bottom = pos.y;
                    if(pos.z <= 0.0f)
                        this->front = math::abs(pos.z);
                    else
                        this->back = pos.z;
                }
            }
            /**
             * 
             * @param pos
             */
            void set(const Vector2f& pos) {
                if(this->style != SPosition::Style::STATICPOS) {
                    if(pos.x <= 0.0f)
                        this->left = math::abs(pos.x);
                    else
                        this->right = pos.x;
                    if(pos.y <= 0.0f)
                        this->top = math::abs(pos.y);
                    else
                        this->bottom = pos.y;
                }
            }
        };

        /**
         *
         */
        struct SSize {

            /**
             *
             */
            enum class Style : unsigned char {
                INVALID_STYLE = Unit::INVALID_UNIT,
                PIXELS = Unit::PIXELS,
                INCHES = Unit::INCHES,
                BLOCKS = Unit::BLOCKS,
                PERCENTS = Unit::PERCENTS,
                MAX,
                MIN
            };
            ///
            Style style;

            union {
                float w;
                float x;
            };

            union {
                float h;
                float y;
            };

            union {
                float d;
                float z;
            };
            /**
             * 
             */
            SSize() :
            style(FG_GUI_DEFAULT_SIZE_STYLE),
            x(FG_GUI_DEFAULT_SIZE_X),
            y(FG_GUI_DEFAULT_SIZE_Y),
            z(FG_GUI_DEFAULT_SIZE_Z) { }
            /**
             * 
             * @param size
             */
            void set(const Vector3f& size) {
                this->x = size.x;
                this->y = size.y;
                this->z = size.z;
            }
            /**
             * 
             * @param _x
             * @param _y
             * @param _z
             */
            void set(float _x, float _y, float _z) {
                this->x = _x;
                this->y = _y;
                this->z = _z;
            }
            /**
             * 
             * @param _x
             * @param _y
             */
            void set(float _x, float _y) {
                this->x = _x;
                this->y = _y;
            }
        };
    };
};

FG_ENUM_FLAGS(fg::gui::SBorder::Which);
FG_ENUM_FLAGS(fg::gui::SMargin::Which);
FG_ENUM_FLAGS(fg::gui::SPadding::Which);
FG_ENUM_FLAGS(fg::gui::Align);

////////////////////////////////////////////////////////////////////////////////

namespace fg {
    namespace gui {

        class CStyle;

        /*
         *
         */
        class CStyleContent {
            friend class fg::gui::CStyle;

        public:
            ///
            typedef CStyleContent self_type;
            ///
            typedef CStyleContent type;
            ///
            typedef CStyleContent& self_ref;

        public:
            /**
             * 
             */
            CStyleContent();
            /**
             * 
             */
            virtual ~CStyleContent();

            /**
             *
             * @param style
             */
            void copyFrom(const CStyleContent& style);

            ////////////////////////////////////////////////////////////////////

            /**
             * Initializes the style content from ini style parameters
             * @param params    Style parameters from given section, taken directly from ini
             * @param merge     If true the styles will be merged, if false - overwritten
             * @return
             */
            fgBool initializeFromConfig(util::config::ParameterVec &params,
                                        fgBool merge = FG_FALSE);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param align
             * @param pos
             * @param size
             * @param boundPos
             * @param boundSize
             * @param isInside
             */
            void applyPosAlign(const Align align, Vector3f& pos, const Vector3f& size, const Vector3f& boundPos, const Vector3f& boundSize, const fgBool isInside = FG_TRUE);
            /**
             * 
             * @param align
             * @param pos
             * @param size
             * @param boundPos
             * @param boundSize
             * @param isInside
             */
            void applyPosAlign(const Align align, Vector2f& pos, const Vector2f& size, const Vector2f& boundPos, const Vector2f& boundSize, const fgBool isInside = FG_TRUE);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param value
             * @return 
             */
            static Color4f parseColor(const char *value);
            /**
             * 
             * @param value
             * @return 
             */
            static SBorder parseBorder(const char *value);
            /**
             * 
             * @param value
             * @return 
             */
            static SBorder::Style parseBorderStyle(const char *value);
            /**
             * 
             * @param value
             * @return 
             */
            static SPosition::Style parsePositionStyle(const char *value);
            /**
             * 
             * @param value
             * @return 
             */
            static Align parseAlign(const char *value);
            /**
             * 
             * @param value
             * @return 
             */
            static SBackground::Style parseBackgroundStyle(const char *value);
            /**
             * Parses the length stored as string
             * @param value     Input length to parsed stored as C-like string
             * @param type      Type of the unit, can be percents, inches, blocks or pixels
             * @return          Floating point value of the parsed length
             */
            static float parseLength(const char *value, Unit &unit);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @return 
             */
            SBackground& getBackground(void);
            /**
             * 
             * @return 
             */
            SForeground& getForeground(void);
            /**
             * 
             * @return 
             */
            SMargin& getMargin(void);
            /**
             * 
             * @return 
             */
            SPadding& getPadding(void);
            /**
             * 
             * @return 
             */
            SBorderGroup& getBorder(void);
            /**
             * 
             * @return 
             */
            SPosition& getPosition(void);
            /**
             * 
             * @return 
             */
            Align getAlign(void) const;
            /**
             * 
             * @return 
             */
            Align getVAlign(void) const;
            /**
             * 
             * @return 
             */
            Align getTextAlign(void) const;
            /**
             * 
             * @return 
             */
            SSize& getSize(void);
            /**
             * 
             * @return 
             */
            std::string& getShader(void);
            /**
             * 
             * @return 
             */
            const char *getShaderStr(void) const;
            /**
             * 
             * @return 
             */
            std::string& getEffect(void);
            /**
             * 
             * @return 
             */
            const char *getEffectStr(void) const;

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param style
             * @return 
             */
            self_ref setBackground(const SBackground::Style style);
            /**
             * 
             * @param color
             * @return 
             */
            self_ref setBackground(const Color4f& color);
            /**
             * 
             * @param texture
             * @return 
             */
            self_ref setBackground(const std::string& texture);
            /**
             * 
             * @param texture
             * @return 
             */
            self_ref setBackground(const char *texture);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param textSize
             * @return 
             */
            self_ref setForeground(const float textSize);
            /**
             * 
             * @param color
             * @return 
             */
            self_ref setForeground(const Color4f& color);
            /**
             * 
             * @param font
             * @return 
             */
            self_ref setForeground(const std::string& font);
            /**
             * 
             * @param font
             * @return 
             */
            self_ref setForeground(const char *font);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param size
             * @return 
             */
            self_ref setMargin(const float size);
            /**
             * 
             * @param which
             * @param size
             * @return 
             */
            self_ref setMargin(const SMargin::Which which, const float size);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param size
             * @return 
             */
            self_ref setPadding(const float size);
            /**
             * 
             * @param which
             * @param size
             * @return 
             */
            self_ref setPadding(const SPadding::Which which, const float size);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param style
             * @return 
             */
            self_ref setBorder(const SBorder::Style style);
            /**
             * 
             * @param color
             * @return 
             */
            self_ref setBorder(const Color4f& color);
            /**
             * 
             * @param width
             * @return 
             */
            self_ref setBorder(const float width);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param which
             * @param style
             * @return 
             */
            self_ref setBorder(const SBorder::Which which, const SBorder::Style style);
            /**
             * 
             * @param which
             * @param color
             * @return 
             */
            self_ref setBorder(const SBorder::Which which, const Color4f& color);
            /**
             * 
             * @param which
             * @param width
             * @return 
             */
            self_ref setBorder(const SBorder::Which which, const float width);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param style
             * @return 
             */
            self_ref setPosition(const SPosition::Style style);
            /**
             * 
             * @param style
             * @param modPos
             * @return 
             */
            self_ref setPosition(const SPosition::Style style, const Vector2f& modPos);
            /**
             * 
             * @param modPos
             * @return 
             */
            self_ref setPosition(const Vector2f& modPos);
            /**
             * 
             * @param style
             * @param modPos
             * @return 
             */
            self_ref setPosition(const SPosition::Style style, const Vector3f& modPos);
            /**
             * 
             * @param modPos
             * @return 
             */
            self_ref setPosition(const Vector3f& modPos);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param align
             * @return 
             */
            self_ref setAlign(const Align align);
            /**
             * 
             * @param vAlign
             * @return 
             */
            self_ref setVAlign(const Align vAlign);
            /**
             * 
             * @param textAlign
             * @return 
             */
            self_ref setTextAlign(const Align textAlign);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param style
             * @return 
             */
            self_ref setSize(const SSize::Style style);
            /**
             * 
             * @param style
             * @param x
             * @param y
             * @return 
             */
            self_ref setSize(const SSize::Style style, const float x, const float y);
            /**
             * 
             * @param style
             * @param size
             * @return 
             */
            self_ref setSize(const SSize::Style style, const Vector2f& size);
            /**
             * 
             * @param style
             * @param x
             * @param y
             * @param z
             * @return 
             */
            self_ref setSize(const SSize::Style style, const float x, const float y, const float z);
            /**
             * 
             * @param style
             * @param size
             * @return 
             */
            self_ref setSize(const SSize::Style style, const Vector3f& size);
            /**
             * 
             * @param x
             * @param y
             * @return 
             */
            self_ref setSize(const float x, const float y);
            /**
             * 
             * @param size
             * @return 
             */
            self_ref setSize(const Vector2f& size);
            /**
             * 
             * @param x
             * @param y
             * @param z
             * @return 
             */
            self_ref setSize(const float x, const float y, const float z);
            /**
             * 
             * @param size
             * @return 
             */
            self_ref setSize(const Vector3f& size);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param shader
             * @return 
             */
            self_ref setShader(const std::string& shader);
            /**
             * 
             * @param shader
             * @return 
             */
            self_ref setShader(const char *shader);

            /**
             * 
             * @param effect
             * @return 
             */
            self_ref setEffect(const std::string& effect);
            /**
             * 
             * @param effect
             * @return 
             */
            self_ref setEffect(const char *effect);

        private:
            /// Used shader - name
            std::string m_shader;
            /// Used effect - name
            std::string m_effect;
            /// Size modifier
            SSize m_size;
            /// Style of the background (image, modifier)
            SBackground m_bg;
            /// Foreground info & style
            SForeground m_fg;
            /// Margins information
            SMargin m_margin;
            /// Padding information
            SPadding m_padding;
            /// Border information
            SBorderGroup m_border;
            /// Position modifier
            SPosition m_position;
            /// Horizontal align
            Align m_align;
            /// Vertical align
            Align m_valign;
            /// Align of the text
            Align m_textAlign;
        };
    };
};

    #undef FG_INC_GUI_STYLE_CONTENT_BLOCK
#endif /* FG_INC_GUI_STYLE_CONTENT */
