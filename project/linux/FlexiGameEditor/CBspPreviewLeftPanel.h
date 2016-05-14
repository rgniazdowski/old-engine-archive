#ifndef CBSPPREVIEWLEFTPANEL_H
    #define CBSPPREVIEWLEFTPANEL_H

//(*Headers(CBspPreviewLeftPanel)
    #include <wx/panel.h>
//*)

class CBspPreviewLeftPanel : public wxPanel {
public:

    CBspPreviewLeftPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    virtual ~CBspPreviewLeftPanel();

    //(*Declarations(CBspPreviewLeftPanel)
    //*)

protected:

    //(*Identifiers(CBspPreviewLeftPanel)
    //*)

private:

    //(*Handlers(CBspPreviewLeftPanel)
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
