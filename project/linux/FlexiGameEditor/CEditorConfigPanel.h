#ifndef CEDITORCONFIGPANEL_H
#define CEDITORCONFIGPANEL_H

//(*Headers(CEditorConfigPanel)
#include <wx/panel.h>
//*)

class CEditorConfigPanel: public wxPanel
{
	public:

		CEditorConfigPanel(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~CEditorConfigPanel();

		//(*Declarations(CEditorConfigPanel)
		//*)

	protected:

		//(*Identifiers(CEditorConfigPanel)
		//*)

	private:

		//(*Handlers(CEditorConfigPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
