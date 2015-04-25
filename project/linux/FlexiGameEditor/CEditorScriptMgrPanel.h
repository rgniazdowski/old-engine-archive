#ifndef CEDITORSCRIPTMGRPANEL_H
#define CEDITORSCRIPTMGRPANEL_H

//(*Headers(CEditorScriptMgrPanel)
#include <wx/panel.h>
//*)

class CEditorScriptMgrPanel: public wxPanel
{
	public:

		CEditorScriptMgrPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CEditorScriptMgrPanel();

		//(*Declarations(CEditorScriptMgrPanel)
		//*)

	protected:

		//(*Identifiers(CEditorScriptMgrPanel)
		//*)

	private:

		//(*Handlers(CEditorScriptMgrPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
