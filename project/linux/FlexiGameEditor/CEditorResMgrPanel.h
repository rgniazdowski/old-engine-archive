#ifndef CEDITORRESMGRPANEL_H
#define CEDITORRESMGRPANEL_H

//(*Headers(CEditorResMgrPanel)
#include <wx/panel.h>
//*)

class CEditorResMgrPanel: public wxPanel
{
	public:

		CEditorResMgrPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CEditorResMgrPanel();

		//(*Declarations(CEditorResMgrPanel)
		//*)

	protected:

		//(*Identifiers(CEditorResMgrPanel)
		//*)

	private:

		//(*Handlers(CEditorResMgrPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
