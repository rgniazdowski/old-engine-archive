#ifndef CEDITOREVENTMGRPANEL_H
#define CEDITOREVENTMGRPANEL_H

//(*Headers(CEditorEventMgrPanel)
#include <wx/panel.h>
//*)

class CEditorEventMgrPanel: public wxPanel
{
	public:

		CEditorEventMgrPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CEditorEventMgrPanel();

		//(*Declarations(CEditorEventMgrPanel)
		//*)

	protected:

		//(*Identifiers(CEditorEventMgrPanel)
		//*)

	private:

		//(*Handlers(CEditorEventMgrPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
