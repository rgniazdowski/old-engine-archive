/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
#include "CBspMaterialsEditDialog.h"

//(*InternalHeaders(CBspMaterialsEditDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CBspMaterialsEditDialog)
const long CBspMaterialsEditDialog::idMaterialsListBox = wxNewId();
const long CBspMaterialsEditDialog::idMaterialName = wxNewId();
const long CBspMaterialsEditDialog::idIORTextValue = wxNewId();
const long CBspMaterialsEditDialog::idIORSpinArrows = wxNewId();
const long CBspMaterialsEditDialog::idShininessSpin = wxNewId();
const long CBspMaterialsEditDialog::idDissolveSpin = wxNewId();
const long CBspMaterialsEditDialog::idColourPickerAmbient = wxNewId();
const long CBspMaterialsEditDialog::idColurPickerDiffuse = wxNewId();
const long CBspMaterialsEditDialog::idColourPickerSpecular = wxNewId();
const long CBspMaterialsEditDialog::idColourPickerTransmittance = wxNewId();
const long CBspMaterialsEditDialog::idColourPickerEmission = wxNewId();
const long CBspMaterialsEditDialog::idComboBoxAmbient = wxNewId();
const long CBspMaterialsEditDialog::idComboBoxDiffuse = wxNewId();
const long CBspMaterialsEditDialog::idComboBoxSpecular = wxNewId();
const long CBspMaterialsEditDialog::idComboBoxNormal = wxNewId();
const long CBspMaterialsEditDialog::idRadioBoxBlend = wxNewId();
const long CBspMaterialsEditDialog::idCheckBoxCullFaceFlag = wxNewId();
const long CBspMaterialsEditDialog::idCheckBoxDepthTestFlag = wxNewId();
const long CBspMaterialsEditDialog::idCheckBoxDepthWriteMaskFlag = wxNewId();
const long CBspMaterialsEditDialog::idCheckBoxTextureRepeatFlag = wxNewId();
const long CBspMaterialsEditDialog::idRadioBoxFrontFace = wxNewId();
const long CBspMaterialsEditDialog::idBurnSpin = wxNewId();
const long CBspMaterialsEditDialog::idButtonSave = wxNewId();
const long CBspMaterialsEditDialog::idButtonApply = wxNewId();
const long CBspMaterialsEditDialog::idButtonCancel = wxNewId();
const long CBspMaterialsEditDialog::idButtonNew = wxNewId();
const long CBspMaterialsEditDialog::idButtonDelete = wxNewId();
const long CBspMaterialsEditDialog::idButtonDuplicate = wxNewId();
const long CBspMaterialsEditDialog::idMaterialPropsPanel = wxNewId();
//*)

BEGIN_EVENT_TABLE(CBspMaterialsEditDialog,wxDialog)
	//(*EventTable(CBspMaterialsEditDialog)
	//*)
END_EVENT_TABLE()

CBspMaterialsEditDialog::CBspMaterialsEditDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CBspMaterialsEditDialog)
	wxBoxSizer* BoxSizerV1;
	wxGridSizer* GridSizer1;
	wxStaticText* StaticText13;
	wxStaticText* StaticText14;
	wxGridBagSizer* PanelGridBagSizer;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizerH1;
	wxGridSizer* GridSizer3;
	wxGridSizer* GridSizer2;
	wxStaticBoxSizer* SBSizerColors;
	wxBoxSizer* BoxSizer2;
	wxStaticText* StaticText1;
	wxStaticText* StaticText10;
	wxStaticText* StaticText3;
	wxStaticText* StaticText8;
	wxStaticText* StaticText12;
	wxStaticBoxSizer* SBSizerMainOptions;
	wxStaticText* StaticText7;
	wxStaticText* StaticText4;
	wxBoxSizer* BoxSizer1;
	wxStaticText* StaticText5;
	wxStaticText* StaticText2;
	wxGridBagSizer* GridBagSizer1;
	wxStaticText* StaticText6;
	wxStaticBoxSizer* SBSizerFlags;
	wxStaticText* StaticText9;
	wxStaticBoxSizer* SBSizerTextures;
	wxStaticText* StaticText11;

	Create(parent, wxID_ANY, _("Materials"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxWANTS_CHARS, _T("wxID_ANY"));
	SetMinSize(wxSize(256,96));
	SetFocus();
	BoxSizerV1 = new wxBoxSizer(wxVERTICAL);
	BoxSizerH1 = new wxBoxSizer(wxHORIZONTAL);
	MaterialsListBox = new wxListBox(this, idMaterialsListBox, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idMaterialsListBox"));
	BoxSizerH1->Add(MaterialsListBox, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MaterialPropsPanel = new wxPanel(this, idMaterialPropsPanel, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("idMaterialPropsPanel"));
	PanelGridBagSizer = new wxGridBagSizer(0, 0);
	SBSizerMainOptions = new wxStaticBoxSizer(wxHORIZONTAL, MaterialPropsPanel, _("General options"));
	GridSizer1 = new wxGridSizer(2, 2, 0, 0);
	StaticText1 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("wxID_ANY"));
	GridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MaterialNameTextCtrl = new wxTextCtrl(MaterialPropsPanel, idMaterialName, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idMaterialName"));
	GridSizer1->Add(MaterialNameTextCtrl, 2, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("IOR:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	StaticText2->SetToolTip(_("Index of refraction, valid values are from 1.0 to 10.0"));
	StaticText2->SetHelpText(_("Index of refraction, valid values are from 1.0 to 10.0"));
	GridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	IORTextCtrl = new wxTextCtrl(MaterialPropsPanel, idIORTextValue, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idIORTextValue"));
	BoxSizer1->Add(IORTextCtrl, 6, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	IORSpinButton = new wxSpinButton(MaterialPropsPanel, idIORSpinArrows, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("idIORSpinArrows"));
	IORSpinButton->SetRange(0, 100);
	BoxSizer1->Add(IORSpinButton, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	GridSizer1->Add(BoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText3 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Shininess:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ShininessSpinCtrl = new wxSpinCtrl(MaterialPropsPanel, idShininessSpin, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("idShininessSpin"));
	ShininessSpinCtrl->SetValue(_T("0"));
	GridSizer1->Add(ShininessSpinCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Dissolve:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	DissolveSpinCtrl = new wxSpinCtrl(MaterialPropsPanel, idDissolveSpin, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("idDissolveSpin"));
	DissolveSpinCtrl->SetValue(_T("0"));
	GridSizer1->Add(DissolveSpinCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBSizerMainOptions->Add(GridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	PanelGridBagSizer->Add(SBSizerMainOptions, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SBSizerColors = new wxStaticBoxSizer(wxHORIZONTAL, MaterialPropsPanel, _("Colors"));
	GridSizer2 = new wxGridSizer(3, 4, 0, 0);
	StaticText5 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Ambient:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ColourPickerAmbient = new wxColourPickerCtrl(MaterialPropsPanel, idColourPickerAmbient, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColourPickerAmbient"));
	GridSizer2->Add(ColourPickerAmbient, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Diffuse:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer2->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ColourPickerDiffuse = new wxColourPickerCtrl(MaterialPropsPanel, idColurPickerDiffuse, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColurPickerDiffuse"));
	GridSizer2->Add(ColourPickerDiffuse, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Specular:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer2->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ColourPickerSpecular = new wxColourPickerCtrl(MaterialPropsPanel, idColourPickerSpecular, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColourPickerSpecular"));
	GridSizer2->Add(ColourPickerSpecular, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Transmittance:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer2->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ColourPickerTransmittance = new wxColourPickerCtrl(MaterialPropsPanel, idColourPickerTransmittance, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColourPickerTransmittance"));
	GridSizer2->Add(ColourPickerTransmittance, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Emission:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer2->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ColourPickerEmission = new wxColourPickerCtrl(MaterialPropsPanel, idColourPickerEmission, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColourPickerEmission"));
	GridSizer2->Add(ColourPickerEmission, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBSizerColors->Add(GridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	PanelGridBagSizer->Add(SBSizerColors, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SBSizerTextures = new wxStaticBoxSizer(wxHORIZONTAL, MaterialPropsPanel, _("Textures"));
	GridSizer3 = new wxGridSizer(4, 2, 0, 0);
	StaticText10 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Ambient:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer3->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ComboBoxAmbient = new wxComboBox(MaterialPropsPanel, idComboBoxAmbient, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxAmbient"));
	GridSizer3->Add(ComboBoxAmbient, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Diffuse:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer3->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ComboBoxDiffuse = new wxComboBox(MaterialPropsPanel, idComboBoxDiffuse, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxDiffuse"));
	GridSizer3->Add(ComboBoxDiffuse, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Specular:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer3->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ComboBoxSpecular = new wxComboBox(MaterialPropsPanel, idComboBoxSpecular, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxSpecular"));
	GridSizer3->Add(ComboBoxSpecular, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Normal:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridSizer3->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ComboBoxNormal = new wxComboBox(MaterialPropsPanel, idComboBoxNormal, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxNormal"));
	GridSizer3->Add(ComboBoxNormal, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBSizerTextures->Add(GridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	PanelGridBagSizer->Add(SBSizerTextures, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SBSizerFlags = new wxStaticBoxSizer(wxHORIZONTAL, MaterialPropsPanel, _("Other"));
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	GridBagSizer1->AddGrowableCol(2);
	wxString __wxRadioBoxChoices_1[3] =
	{
		_("None"),
		_("Additive"),
		_("Transparency")
	};
	RadioBoxBlend = new wxRadioBox(MaterialPropsPanel, idRadioBoxBlend, _("Blend"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("idRadioBoxBlend"));
	GridBagSizer1->Add(RadioBoxBlend, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxCullFace = new wxCheckBox(MaterialPropsPanel, idCheckBoxCullFaceFlag, _("Cull face"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxCullFaceFlag"));
	CheckBoxCullFace->SetValue(false);
	GridBagSizer1->Add(CheckBoxCullFace, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxDepthTest = new wxCheckBox(MaterialPropsPanel, idCheckBoxDepthTestFlag, _("Depth test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxDepthTestFlag"));
	CheckBoxDepthTest->SetValue(false);
	GridBagSizer1->Add(CheckBoxDepthTest, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxDepthWriteMask = new wxCheckBox(MaterialPropsPanel, idCheckBoxDepthWriteMaskFlag, _("Depth write mask"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxDepthWriteMaskFlag"));
	CheckBoxDepthWriteMask->SetValue(false);
	GridBagSizer1->Add(CheckBoxDepthWriteMask, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxTextureRepeat = new wxCheckBox(MaterialPropsPanel, idCheckBoxTextureRepeatFlag, _("Texture repeat"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxTextureRepeatFlag"));
	CheckBoxTextureRepeat->SetValue(false);
	GridBagSizer1->Add(CheckBoxTextureRepeat, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Counterclockwise"),
		_("Clockwise")
	};
	RadioBoxFrontFace = new wxRadioBox(MaterialPropsPanel, idRadioBoxFrontFace, _("Front face"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, 0, wxDefaultValidator, _T("idRadioBoxFrontFace"));
	GridBagSizer1->Add(RadioBoxFrontFace, wxGBPosition(3, 0), wxGBSpan(1, 3), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(MaterialPropsPanel, wxID_ANY, _("Burn:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizer1->Add(StaticText14, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BurnSpinCtrl = new wxSpinCtrl(MaterialPropsPanel, idBurnSpin, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("idBurnSpin"));
	BurnSpinCtrl->SetValue(_T("0"));
	GridBagSizer1->Add(BurnSpinCtrl, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBSizerFlags->Add(GridBagSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	PanelGridBagSizer->Add(SBSizerFlags, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	ButtonSave = new wxButton(MaterialPropsPanel, idButtonSave, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonSave"));
	BoxSizer2->Add(ButtonSave, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonApply = new wxButton(MaterialPropsPanel, idButtonApply, _("Apply"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonApply"));
	ButtonApply->SetDefault();
	BoxSizer2->Add(ButtonApply, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonCancel = new wxButton(MaterialPropsPanel, idButtonCancel, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonCancel"));
	BoxSizer2->Add(ButtonCancel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PanelGridBagSizer->Add(BoxSizer2, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	ButtonNew = new wxButton(MaterialPropsPanel, idButtonNew, _("New"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonNew"));
	BoxSizer3->Add(ButtonNew, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonDelete = new wxButton(MaterialPropsPanel, idButtonDelete, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonDelete"));
	BoxSizer3->Add(ButtonDelete, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonDuplicate = new wxButton(MaterialPropsPanel, idButtonDuplicate, _("Duplicate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonDuplicate"));
	BoxSizer3->Add(ButtonDuplicate, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PanelGridBagSizer->Add(BoxSizer3, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MaterialPropsPanel->SetSizer(PanelGridBagSizer);
	PanelGridBagSizer->Fit(MaterialPropsPanel);
	PanelGridBagSizer->SetSizeHints(MaterialPropsPanel);
	BoxSizerH1->Add(MaterialPropsPanel, 4, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizerV1->Add(BoxSizerH1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SetSizer(BoxSizerV1);
	BoxSizerV1->Fit(this);
	BoxSizerV1->SetSizeHints(this);
	Center();

	Connect(idMaterialsListBox,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnMaterialsListBoxSelect);
	Connect(idColourPickerAmbient,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idColurPickerDiffuse,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idColourPickerSpecular,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idColourPickerTransmittance,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idColourPickerEmission,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idComboBoxAmbient,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxAmbientSelected);
	Connect(idComboBoxDiffuse,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxDiffuseSelected);
	Connect(idComboBoxSpecular,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxSpecularSelected);
	Connect(idComboBoxNormal,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxNormalSelected);
	Connect(idRadioBoxBlend,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnRadioBoxBlendSelect);
	Connect(idRadioBoxFrontFace,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnRadioBoxFrontFaceSelect);
	Connect(idButtonSave,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonApply,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonNew,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonDelete,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonDuplicate,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	//*)
}
//------------------------------------------------------------------------------

CBspMaterialsEditDialog::~CBspMaterialsEditDialog() {
    //(*Destroy(CBspMaterialsEditDialog)
    //*)
}
//------------------------------------------------------------------------------

bool CBspMaterialsEditDialog::Close(bool force) {
    // FIXME ?
    return this->Destroy();
}
//------------------------------------------------------------------------------

bool CBspMaterialsEditDialog::Show(bool show) {
    return base_type::Show(show);
}
//------------------------------------------------------------------------------

int CBspMaterialsEditDialog::ShowModal() {
    return base_type::ShowModal();
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::EndModal(int retCode) {
    base_type::EndDialog(retCode);
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnRadioBoxBlendSelect(wxCommandEvent& event)
{
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnComboBoxAmbientSelected(wxCommandEvent& event)
{
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnComboBoxDiffuseSelected(wxCommandEvent& event)
{
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnComboBoxSpecularSelected(wxCommandEvent& event)
{
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnComboBoxNormalSelected(wxCommandEvent& event)
{
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnColourPickerColourChanged(wxColourPickerEvent& event)
{
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnRadioBoxFrontFaceSelect(wxCommandEvent& event)
{
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnMaterialsListBoxSelect(wxCommandEvent& event)
{
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnButtonStdClick(wxCommandEvent& event)
{
}
//------------------------------------------------------------------------------
