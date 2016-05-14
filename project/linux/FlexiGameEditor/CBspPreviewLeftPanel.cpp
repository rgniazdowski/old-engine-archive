#include "CBspPreviewLeftPanel.h"

//(*InternalHeaders(CBspPreviewLeftPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CBspPreviewLeftPanel)
//*)

BEGIN_EVENT_TABLE(CBspPreviewLeftPanel,wxPanel)
	//(*EventTable(CBspPreviewLeftPanel)
	//*)
END_EVENT_TABLE()

CBspPreviewLeftPanel::CBspPreviewLeftPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CBspPreviewLeftPanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//*)
}

CBspPreviewLeftPanel::~CBspPreviewLeftPanel()
{
	//(*Destroy(CBspPreviewLeftPanel)
	//*)
}

