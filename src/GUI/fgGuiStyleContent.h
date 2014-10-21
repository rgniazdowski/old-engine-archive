/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_STYLE_CONTENT_H_
    #define _FG_GUI_STYLE_CONTENT_H_

    #include "fgBuildConfig.h"
    #include "fgTypes.h"

    #ifndef _FG_MATHLIB_H_
        #include "Math/fgMathLib.h"
    #endif

    #include "GFX/fgGFXColor.h"
    #include "GFX/fgGFXBoundingBox.h"

    #define FG_GUI_FLOAT_UNIT_INVALID       1280000.0f
    #define FG_GUI_FLOAT_UNIT_TEST_VALUE    1000000.0f
    #define FG_GUI_CHECK_FLOAT(value)   (value < FG_GUI_FLOAT_UNIT_TEST_VALUE)

/**
 *
 */
enum fgGuiUnitType {
    FG_GUI_PIXELS,
    FG_GUI_INCHES,
    FG_GUI_BLOCKS,
    FG_GUI_PERCENTS
};

/**
 *
 */
enum fgGuiBorderStyle {
    FG_GUI_BORDER_NONE,
    FG_GUI_BORDER_DOTTED,
    FG_GUI_BORDER_DASHED,
    FG_GUI_BORDER_SOLID
};

/**
 *
 */
enum fgGuiBorderWhich {
    FG_GUI_BORDER_LEFT = 0x0001,
    FG_GUI_BORDER_RIGHT = 0x0002,
    FG_GUI_BORDER_TOP = 0x0004,
    FG_GUI_BORDER_BOTTOM = 0x0008,
    FG_GUI_BORDER_ALL = FG_GUI_BORDER_LEFT | FG_GUI_BORDER_RIGHT | FG_GUI_BORDER_TOP | FG_GUI_BORDER_BOTTOM
};
FG_ENUM_FLAGS(fgGuiBorderWhich);

    #define FG_GUI_DEFAULT_BORDER_STYLE FG_GUI_BORDER_SOLID
    #define FG_GUI_DEFAULT_BORDER_COLOR	fgColor4f(1.0f, 1.0f, 1.0f, 1.0f)
    #define FG_GUI_DEFAULT_BORDER_WIDTH	2.0f

/**
 *
 */
struct fgGuiBorder {
    fgGuiBorderStyle style;
    fgColor4f color;
    float width;
    fgGuiBorder(const float _width = FG_GUI_DEFAULT_BORDER_WIDTH) :
    style(FG_GUI_DEFAULT_BORDER_STYLE),
    color(FG_GUI_DEFAULT_BORDER_COLOR),
    width(_width) { }
};

/**
 *
 */
enum fgGuiBackgroundStyle {
    FG_GUI_BACKGROUND_NONE,
    FG_GUI_BACKGROUND_NORMAL,
    FG_GUI_BACKGROUND_MAX,
    FG_GUI_BACKGROUND_TILED
};

/**
 *
 */
struct fgGuiBackground {
    fgGuiBackgroundStyle style;
    fgColor4f color;
    std::string texture;
    fgGuiBackground() :
    style(FG_GUI_BACKGROUND_MAX),
    color(0.4f, 0.4f, 0.4f, 0.8f), // Default predefs..
    texture() { }
};

    #define FG_GUI_DEFAULT_TEXT_SIZE	16.0f
    #define FG_GUI_DEFAULT_FONT		"DefaultFont"
    #define FG_GUI_DEFAULT_FG_COLOR	fgColor4f(0.9f, 0.9f, 0.9f, 1.0f)

/**
 *
 */
struct fgGuiForeground {
    float textSize;
    fgColor4f color;
    std::string font;
    fgGuiForeground() :
    textSize(FG_GUI_DEFAULT_TEXT_SIZE), // FIXME
    color(FG_GUI_DEFAULT_FG_COLOR),
    font(FG_GUI_DEFAULT_FONT) { }
};

    #define FG_GUI_DEFAULT_MARGIN 8.0f
    #define FG_GUI_DEFAULT_PADDING 8.0f

/**
 *
 */
struct fgGuiMargin {
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
    fgGuiMargin() :
    value(FG_GUI_DEFAULT_MARGIN),
    left(FG_GUI_DEFAULT_MARGIN),
    right(FG_GUI_DEFAULT_MARGIN),
    top(FG_GUI_DEFAULT_MARGIN),
    bottom(FG_GUI_DEFAULT_MARGIN) { }
};

/**
 *
 */
enum fgGuiMarginWhich {
    FG_GUI_MARGIN_LEFT = 0x0001,
    FG_GUI_MARGIN_RIGHT = 0x0002,
    FG_GUI_MARGIN_TOP = 0x0004,
    FG_GUI_MARGIN_BOTTOM = 0x0008,
    FG_GUI_MARGIN_ALL = FG_GUI_MARGIN_LEFT | FG_GUI_MARGIN_RIGHT | FG_GUI_MARGIN_TOP | FG_GUI_MARGIN_BOTTOM
};
FG_ENUM_FLAGS(fgGuiMarginWhich);

/**
 * 
 */
struct fgGuiBorderInfo {
    ///
    fgGuiBorder all;
    ///
    fgGuiBorder left;
    ///
    fgGuiBorder right;
    ///
    fgGuiBorder top;
    ///
    fgGuiBorder bottom;
    /**
     * 
     */
    fgGuiBorderInfo() :
    all(FG_GUI_DEFAULT_BORDER_WIDTH),
    left(FG_GUI_DEFAULT_BORDER_WIDTH),
    right(FG_GUI_DEFAULT_BORDER_WIDTH),
    top(FG_GUI_DEFAULT_BORDER_WIDTH),
    bottom(FG_GUI_DEFAULT_BORDER_WIDTH) { }
};

typedef fgGuiMargin fgGuiPadding;

/**
 *
 */
enum fgGuiPaddingWhich {
    FG_GUI_PADDING_LEFT = 0x0001,
    FG_GUI_PADDING_RIGHT = 0x0002,
    FG_GUI_PADDING_TOP = 0x0004,
    FG_GUI_PADDING_BOTTOM = 0x0008,
    FG_GUI_PADDING_ALL = FG_GUI_PADDING_LEFT | FG_GUI_PADDING_RIGHT | FG_GUI_PADDING_TOP | FG_GUI_PADDING_BOTTOM
};
FG_ENUM_FLAGS(fgGuiPaddingWhich);

/**
 *
 */
enum fgGuiAlign {
    FG_GUI_ALIGN_NONE = 0x0000,
    FG_GUI_ALIGN_LEFT = 0x0001,
    FG_GUI_ALIGN_RIGHT = 0x0002,
    FG_GUI_ALIGN_CENTER = 0x0004,
    FG_GUI_ALIGN_MIDDLE = 0x0008,
    FG_GUI_ALIGN_TOP = 0x0020,
    FG_GUI_ALIGN_BOTTOM = 0x0040
};
FG_ENUM_FLAGS(fgGuiAlign);

    #define FG_GUI_DEFAULT_ALIGN	FG_GUI_ALIGN_CENTER
    #define FG_GUI_DEFAULT_VALIGN	FG_GUI_ALIGN_MIDDLE
    #define FG_GUI_DEFAULT_TEXT_ALIGN (FG_GUI_ALIGN_CENTER | FG_GUI_ALIGN_MIDDLE)

/**
 *
 */
enum fgGuiPositionStyle {
    FG_GUI_POS_STATIC,
    FG_GUI_POS_FIXED,
    FG_GUI_POS_RELATIVE,
    FG_GUI_POS_ABSOLUTE
};

    #define FG_GUI_DEFAULT_POSITION_STYLE	FG_GUI_POS_STATIC
    #define FG_GUI_DEFAULT_POSITION_LEFT	FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_RIGTH	FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_TOP		FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_BOTTOM	FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_FRONT	FG_GUI_FLOAT_UNIT_INVALID
    #define FG_GUI_DEFAULT_POSITION_BACK	FG_GUI_FLOAT_UNIT_INVALID

/**
 *
 */
struct fgGuiPosition {
    ///
    fgGuiPositionStyle style;
    ///
    fgGuiUnitType unit;
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
    fgGuiPosition() :
    style(FG_GUI_DEFAULT_POSITION_STYLE),
    unit(FG_GUI_PIXELS),
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
};

/**
 *
 */
enum fgGuiSizeStyle {
    FG_GUI_SIZE_PIXELS = FG_GUI_PIXELS,
    FG_GUI_SIZE_INCHES = FG_GUI_INCHES,
    FG_GUI_SIZE_BLOCKS = FG_GUI_BLOCKS,
    FG_GUI_SIZE_PERCENTS = FG_GUI_PERCENTS,
    FG_GUI_SIZE_MAX,
    FG_GUI_SIZE_MIN

};

    #define FG_GUI_DEFAULT_SIZE_STYLE   FG_GUI_SIZE_PERCENTS
    #define FG_GUI_DEFAULT_SIZE_X       10.0f
    #define FG_GUI_DEFAULT_SIZE_Y       5.0f
    #define FG_GUI_DEFAULT_SIZE_Z       1.0f

/**
 *
 */
struct fgGuiSize {
    ///
    fgGuiSizeStyle style;

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
    fgGuiSize() :
    style(FG_GUI_DEFAULT_SIZE_STYLE),
    x(FG_GUI_DEFAULT_SIZE_X),
    y(FG_GUI_DEFAULT_SIZE_Y),
    z(FG_GUI_DEFAULT_SIZE_Z) { }
};

    #include "Util/fgConfigStruct.h"

/*
 *
 */
class fgGuiStyleContent {
    friend class fgGuiStyle;
private:
    ///
    std::string m_shader;
    ///
    std::string m_effect;
    ///
    fgGuiSize m_size;
    ///
    fgGuiBackground m_bg;
    ///
    fgGuiForeground m_fg;
    ///
    fgGuiMargin m_margin;
    ///
    fgGuiPadding m_padding;
    ///
    fgGuiBorderInfo m_border;
    ///
    fgGuiPosition m_position;
    ///
    fgGuiAlign m_align;
    ///
    fgGuiAlign m_valign;
    ///
    fgGuiAlign m_textAlign;

public:
    //
    fgGuiStyleContent();
    //
    virtual ~fgGuiStyleContent();

    //
    fgBool initializeFromConfig(fgCfgTypes::parameterVec &params, fgBool merge = FG_FALSE);

    //
    void applyPosAlign(const fgGuiAlign align, fgVector3f& pos, const fgVector3f& size, const fgVector3f& boundSize);
    //
    void applyPosAlign(const fgGuiAlign align, fgVector2f& pos, const fgVector2f& size, const fgVector2f& boundSize);

    //
    static fgColor4f parseColor(const char *value);
    //
    static fgGuiBorder parseBorder(const char *value);
    //
    static fgGuiBorderStyle parseBorderStyle(const char *value);
    //
    static fgGuiPositionStyle parsePositionStyle(const char *value);
    //
    static fgGuiAlign parseAlign(const char *value);
    //
    static fgGuiBackgroundStyle parseBackgroundStyle(const char *value);
    //
    static float parseLength(const char *value, fgGuiUnitType &type);

    //
    fgGuiBackground& getBackground(void);
    //
    fgGuiForeground& getForeground(void);
    //
    fgGuiMargin& getMargin(void);
    //
    fgGuiPadding& getPadding(void);
    //
    fgGuiBorderInfo& getBorder(void);
    //
    fgGuiPosition& getPosition(void);
    //
    fgGuiAlign getAlign(void) const;
    //
    fgGuiAlign getVAlign(void) const;
    //
    fgGuiAlign getTextAlign(void) const;
    //
    fgGuiSize& getSize(void);
    //
    std::string& getShader(void);
    //
    std::string& getEffect(void);

    //
    fgGuiStyleContent& setBackground(const fgGuiBackgroundStyle style);
    //
    fgGuiStyleContent& setBackground(const fgColor4f& color);
    //
    fgGuiStyleContent& setBackground(const std::string& texture);

    //
    fgGuiStyleContent& setForeground(const float textSize);
    //
    fgGuiStyleContent& setForeground(const fgColor4f& color);
    //
    fgGuiStyleContent& setForeground(const std::string& font);

    //
    fgGuiStyleContent& setMargin(const float size);
    //
    fgGuiStyleContent& setMargin(const fgGuiMarginWhich which, const float size);

    //
    fgGuiStyleContent& setPadding(const float size);
    //
    fgGuiStyleContent& setPadding(const fgGuiPaddingWhich which, const float size);

    //
    fgGuiStyleContent& setBorder(const fgGuiBorderStyle style);
    //
    fgGuiStyleContent& setBorder(const fgColor4f& color);
    //
    fgGuiStyleContent& setBorder(const float width);

    //
    fgGuiStyleContent& setBorder(const fgGuiBorderWhich which, const fgGuiBorderStyle style);
    //
    fgGuiStyleContent& setBorder(const fgGuiBorderWhich which, const fgColor4f& color);
    //
    fgGuiStyleContent& setBorder(const fgGuiBorderWhich which, const float width);

    //
    fgGuiStyleContent& setPosition(const fgGuiPositionStyle style);
    //
    fgGuiStyleContent& setPosition(const fgGuiPositionStyle style, const fgVector2f& modPos);
    //
    fgGuiStyleContent& setPosition(const fgVector2f& modPos);
    //
    fgGuiStyleContent& setPosition(const fgGuiPositionStyle style, const fgVector3f& modPos);
    //
    fgGuiStyleContent& setPosition(const fgVector3f& modPos);

    //
    fgGuiStyleContent& setAlign(const fgGuiAlign align);
    //
    fgGuiStyleContent& setVAlign(const fgGuiAlign vAlign);
    //
    fgGuiStyleContent& setTextAlign(const fgGuiAlign textAlign);

    //
    fgGuiStyleContent& setSize(const fgGuiSizeStyle style);
    //
    fgGuiStyleContent& setSize(const fgGuiSizeStyle style, const float x, const float y);
    //
    fgGuiStyleContent& setSize(const fgGuiSizeStyle style, const fgVector2f& size);
    //
    fgGuiStyleContent& setSize(const fgGuiSizeStyle style, const float x, const float y, const float z);
    //
    fgGuiStyleContent& setSize(const fgGuiSizeStyle style, const fgVector3f& size);
    //
    fgGuiStyleContent& setSize(const float x, const float y);
    //
    fgGuiStyleContent& setSize(const fgVector2f& size);
    //
    fgGuiStyleContent& setSize(const float x, const float y, const float z);
    //
    fgGuiStyleContent& setSize(const fgVector3f& size);

    //
    fgGuiStyleContent& setShader(const std::string& shader);
    //
    fgGuiStyleContent& setEffect(const std::string& effect);

};

#endif /* _FG_GUI_STYLE_CONTENT_H_ */
