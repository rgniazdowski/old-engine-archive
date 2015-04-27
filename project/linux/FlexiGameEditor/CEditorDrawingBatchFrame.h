/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_EDITOR_DRAWING_BATCH_FRAME
    #define FG_INC_EDITOR_DRAWING_BATCH_FRAME
    #define FG_INC_EDITOR_DRAWING_BATCH_FRAME_BLOCK

//(*Headers(CEditorDrawingBatchFrame)
    #include <wx/frame.h>
//*)

/**
 *
 */
class CEditorDrawingBatchFrame : public wxFrame {
public:
    typedef CEditorDrawingBatchFrame self_type;
    typedef CEditorDrawingBatchFrame type;
    typedef wxFrame base_type;

public:
    /**
     *
     * @param parent
     * @param id
     * @param pos
     * @param size
     */
    CEditorDrawingBatchFrame(wxWindow* parent,
                             wxWindowID id = wxID_ANY,
                             const wxPoint& pos = wxDefaultPosition,
                             const wxSize& size = wxDefaultSize);
    /**
     *
     */
    virtual ~CEditorDrawingBatchFrame();

    //(*Declarations(CEditorDrawingBatchFrame)
    //*)

protected:

    //(*Identifiers(CEditorDrawingBatchFrame)
    //*)

private:

    //(*Handlers(CEditorDrawingBatchFrame)
    //*)

    DECLARE_EVENT_TABLE()
};

    #undef FG_INC_EDITOR_DRAWING_BATCH_FRAME_BLOCK
#endif /* FG_INC_EDITOR_DRAWING_BATCH_FRAME */
