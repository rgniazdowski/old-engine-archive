#include "CEditorScriptMgrPanel.h"

//(*InternalHeaders(CEditorScriptMgrPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CEditorScriptMgrPanel)
//*)

BEGIN_EVENT_TABLE(CEditorScriptMgrPanel,wxPanel)
	//(*EventTable(CEditorScriptMgrPanel)
	//*)
END_EVENT_TABLE()

CEditorScriptMgrPanel::CEditorScriptMgrPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CEditorScriptMgrPanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//*)
}

CEditorScriptMgrPanel::~CEditorScriptMgrPanel()
{
	//(*Destroy(CEditorScriptMgrPanel)
	//*)
}

