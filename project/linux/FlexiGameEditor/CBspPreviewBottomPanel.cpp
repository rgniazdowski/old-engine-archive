#include "CBspPreviewBottomPanel.h"

//(*InternalHeaders(CBspPreviewBottomPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CBspPreviewBottomPanel)
//*)

BEGIN_EVENT_TABLE(CBspPreviewBottomPanel,wxPanel)
	//(*EventTable(CBspPreviewBottomPanel)
	//*)
END_EVENT_TABLE()

CBspPreviewBottomPanel::CBspPreviewBottomPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CBspPreviewBottomPanel)
	wxStaticBoxSizer* StaticBoxSizerGroundGrid;
	wxStaticBoxSizer* StaticBoxSizerSelection;
	wxStaticBoxSizer* StaticBoxSizerMaterials;
	wxStaticBoxSizer* StaticBoxSizerInfoStats;
	wxGridBagSizer* GridBagSizerMaterials;
	wxGridBagSizer* GridBagSizerGroundGrid;
	wxGridBagSizer* GridBagSizerSelection;
	wxStaticBoxSizer* StaticBoxSizerDrawing;
	wxGridBagSizer* GridBagSizerMainAll;
	wxGridBagSizer* GridBagSizerDrawing;
	wxGridBagSizer* GridBagSizerInfoStats;
	wxGridBagSizer* GridBagSizerBspEdit;
	wxStaticBoxSizer* StaticBoxSizerBspEdit;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	GridBagSizerMainAll = new wxGridBagSizer(0, 0);
	StaticBoxSizerGroundGrid = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Ground grid"));
	GridBagSizerGroundGrid = new wxGridBagSizer(0, 0);
	StaticBoxSizerGroundGrid->Add(GridBagSizerGroundGrid, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizerMainAll->Add(StaticBoxSizerGroundGrid, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerMaterials = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Materials"));
	GridBagSizerMaterials = new wxGridBagSizer(0, 0);
	StaticBoxSizerMaterials->Add(GridBagSizerMaterials, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizerMainAll->Add(StaticBoxSizerMaterials, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerInfoStats = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Info"));
	GridBagSizerInfoStats = new wxGridBagSizer(0, 0);
	StaticBoxSizerInfoStats->Add(GridBagSizerInfoStats, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizerMainAll->Add(StaticBoxSizerInfoStats, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerBspEdit = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Tree status"));
	GridBagSizerBspEdit = new wxGridBagSizer(0, 0);
	StaticBoxSizerBspEdit->Add(GridBagSizerBspEdit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizerMainAll->Add(StaticBoxSizerBspEdit, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerDrawing = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Drawing"));
	GridBagSizerDrawing = new wxGridBagSizer(0, 0);
	StaticBoxSizerDrawing->Add(GridBagSizerDrawing, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizerMainAll->Add(StaticBoxSizerDrawing, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerSelection = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Selection"));
	GridBagSizerSelection = new wxGridBagSizer(0, 0);
	StaticBoxSizerSelection->Add(GridBagSizerSelection, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizerMainAll->Add(StaticBoxSizerSelection, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(GridBagSizerMainAll);
	GridBagSizerMainAll->Fit(this);
	GridBagSizerMainAll->SetSizeHints(this);
	//*)
}

CBspPreviewBottomPanel::~CBspPreviewBottomPanel()
{
	//(*Destroy(CBspPreviewBottomPanel)
	//*)
}

