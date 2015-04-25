#include "CEditorResMgrPanel.h"

//(*InternalHeaders(CEditorResMgrPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CEditorResMgrPanel)
//*)

BEGIN_EVENT_TABLE(CEditorResMgrPanel,wxPanel)
	//(*EventTable(CEditorResMgrPanel)
	//*)
END_EVENT_TABLE()

CEditorResMgrPanel::CEditorResMgrPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CEditorResMgrPanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//*)
}

CEditorResMgrPanel::~CEditorResMgrPanel()
{
	//(*Destroy(CEditorResMgrPanel)
	//*)
}

