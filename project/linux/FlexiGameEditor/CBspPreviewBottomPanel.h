#ifndef CBSPPREVIEWBOTTOMPANEL_H
    #define CBSPPREVIEWBOTTOMPANEL_H

//(*Headers(CBspPreviewBottomPanel)
    #include <wx/sizer.h>
    #include <wx/panel.h>
    #include <wx/gbsizer.h>
//*)

class CBspPreviewBottomPanel : public wxPanel {
public:

    CBspPreviewBottomPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    virtual ~CBspPreviewBottomPanel();

    //(*Declarations(CBspPreviewBottomPanel)
    //*)

protected:

    //(*Identifiers(CBspPreviewBottomPanel)
    //*)

private:

    //(*Handlers(CBspPreviewBottomPanel)
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
