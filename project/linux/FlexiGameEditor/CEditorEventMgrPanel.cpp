#include "CEditorEventMgrPanel.h"

//(*InternalHeaders(CEditorEventMgrPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CEditorEventMgrPanel)
//*)

BEGIN_EVENT_TABLE(CEditorEventMgrPanel,wxPanel)
	//(*EventTable(CEditorEventMgrPanel)
	//*)
END_EVENT_TABLE()

CEditorEventMgrPanel::CEditorEventMgrPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CEditorEventMgrPanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//*)
}

CEditorEventMgrPanel::~CEditorEventMgrPanel()
{
	//(*Destroy(CEditorEventMgrPanel)
	//*)
}

