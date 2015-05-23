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

#include "GFX/Shaders/fgGfxShaderManager.h"
#include "GFX/Shaders/fgGfxShaderProgram.h"
#include "Resource/fgResourceManager.h"
#include "Resource/fgResource.h"

#include "fgLog.h"

//(*InternalHeaders(CBspMaterialsEditDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//------------------------------------------------------------------------------
//(*IdInit(CBspMaterialsEditDialog)
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
const long CBspMaterialsEditDialog::idComboBoxShader = wxNewId();
const long CBspMaterialsEditDialog::idButtonSave = wxNewId();
const long CBspMaterialsEditDialog::idButtonApply = wxNewId();
const long CBspMaterialsEditDialog::idButtonCancel = wxNewId();
const long CBspMaterialsEditDialog::idButtonNew = wxNewId();
const long CBspMaterialsEditDialog::idButtonDelete = wxNewId();
const long CBspMaterialsEditDialog::idButtonDuplicate = wxNewId();
const long CBspMaterialsEditDialog::idMaterialsListBox = wxNewId();
//*)
//------------------------------------------------------------------------------

BEGIN_EVENT_TABLE(CBspMaterialsEditDialog,wxDialog)
	//(*EventTable(CBspMaterialsEditDialog)
	//*)
END_EVENT_TABLE()

//------------------------------------------------------------------------------

const char* const CBspMaterialsEditDialog::DEFAULT_SHADER_TEXT = "-- Default shader --";
const char* const CBspMaterialsEditDialog::NO_TEXTURE_TEXT = "-- No texture --";

//------------------------------------------------------------------------------

CBspMaterialsEditDialog::CBspMaterialsEditDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CBspMaterialsEditDialog)
	wxGridBagSizer* GridBagSizerGeneral;
	wxStaticText* StaticText13;
	wxStaticText* StaticText14;
	wxStaticText* StaticText15;
	wxBoxSizer* BoxSizer3;
	wxGridBagSizer* GridBagSizerOptionsAll;
	wxGridBagSizer* GridBagSizerOther;
	wxStaticBoxSizer* SBSizerColors;
	wxBoxSizer* BoxSizer2;
	wxStaticText* StaticText1;
	wxStaticText* StaticText10;
	wxGridBagSizer* GridBagSizerColors;
	wxStaticText* StaticText3;
	wxStaticText* StaticText8;
	wxStaticText* StaticText12;
	wxStaticBoxSizer* SBSizerMainOptions;
	wxStaticText* StaticText7;
	wxStaticText* StaticText4;
	wxBoxSizer* BoxSizer1;
	wxStaticText* StaticText5;
	wxStaticText* StaticText2;
	wxStaticText* StaticText6;
	wxStaticBoxSizer* SBSizerFlags;
	wxStaticText* StaticText9;
	wxStaticBoxSizer* SBSizerTextures;
	wxStaticText* StaticText11;
	wxGridBagSizer* GridBagSizerTextures;

	Create(parent, wxID_ANY, _("BSP Materials"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxWANTS_CHARS|wxFULL_REPAINT_ON_RESIZE, _T("wxID_ANY"));
	SetFocus();
	GridBagSizerOptionsAll = new wxGridBagSizer(0, 0);
	SBSizerMainOptions = new wxStaticBoxSizer(wxHORIZONTAL, this, _("General options"));
	GridBagSizerGeneral = new wxGridBagSizer(0, 0);
	StaticText1 = new wxStaticText(this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("wxID_ANY"));
	GridBagSizerGeneral->Add(StaticText1, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MaterialNameTextCtrl = new wxTextCtrl(this, idMaterialName, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idMaterialName"));
	MaterialNameTextCtrl->SetMaxLength(128);
	GridBagSizerGeneral->Add(MaterialNameTextCtrl, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, wxID_ANY, _("IOR:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	StaticText2->SetToolTip(_("Index of refraction, valid values are from 1.0 to 10.0"));
	StaticText2->SetHelpText(_("Index of refraction, valid values are from 1.0 to 10.0"));
	GridBagSizerGeneral->Add(StaticText2, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	IORTextCtrl = new wxTextCtrl(this, idIORTextValue, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idIORTextValue"));
	IORTextCtrl->SetMaxLength(4);
	BoxSizer1->Add(IORTextCtrl, 6, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	IORSpinButton = new wxSpinButton(this, idIORSpinArrows, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL, _T("idIORSpinArrows"));
	IORSpinButton->SetRange(0, 100);
	BoxSizer1->Add(IORSpinButton, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	GridBagSizerGeneral->Add(BoxSizer1, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText3 = new wxStaticText(this, wxID_ANY, _("Shininess:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerGeneral->Add(StaticText3, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ShininessSpinCtrl = new wxSpinCtrl(this, idShininessSpin, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("idShininessSpin"));
	ShininessSpinCtrl->SetValue(_T("0"));
	GridBagSizerGeneral->Add(ShininessSpinCtrl, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, wxID_ANY, _("Dissolve:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerGeneral->Add(StaticText4, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	DissolveSpinCtrl = new wxSpinCtrl(this, idDissolveSpin, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("idDissolveSpin"));
	DissolveSpinCtrl->SetValue(_T("0"));
	GridBagSizerGeneral->Add(DissolveSpinCtrl, wxGBPosition(3, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBSizerMainOptions->Add(GridBagSizerGeneral, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	GridBagSizerOptionsAll->Add(SBSizerMainOptions, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SBSizerColors = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Colors"));
	GridBagSizerColors = new wxGridBagSizer(0, 0);
	StaticText5 = new wxStaticText(this, wxID_ANY, _("Ambient:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerColors->Add(StaticText5, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ColourPickerAmbient = new wxColourPickerCtrl(this, idColourPickerAmbient, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColourPickerAmbient"));
	GridBagSizerColors->Add(ColourPickerAmbient, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, wxID_ANY, _("Diffuse:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerColors->Add(StaticText6, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ColourPickerDiffuse = new wxColourPickerCtrl(this, idColurPickerDiffuse, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColurPickerDiffuse"));
	GridBagSizerColors->Add(ColourPickerDiffuse, wxGBPosition(0, 3), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, wxID_ANY, _("Specular:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerColors->Add(StaticText7, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ColourPickerSpecular = new wxColourPickerCtrl(this, idColourPickerSpecular, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColourPickerSpecular"));
	GridBagSizerColors->Add(ColourPickerSpecular, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, wxID_ANY, _("Transmittance:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerColors->Add(StaticText8, wxGBPosition(1, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ColourPickerTransmittance = new wxColourPickerCtrl(this, idColourPickerTransmittance, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColourPickerTransmittance"));
	GridBagSizerColors->Add(ColourPickerTransmittance, wxGBPosition(1, 3), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, wxID_ANY, _("Emission:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerColors->Add(StaticText9, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ColourPickerEmission = new wxColourPickerCtrl(this, idColourPickerEmission, wxColour(0,0,0), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idColourPickerEmission"));
	GridBagSizerColors->Add(ColourPickerEmission, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBSizerColors->Add(GridBagSizerColors, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	GridBagSizerOptionsAll->Add(SBSizerColors, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SBSizerTextures = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Textures"));
	GridBagSizerTextures = new wxGridBagSizer(0, 0);
	StaticText10 = new wxStaticText(this, wxID_ANY, _("Ambient:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerTextures->Add(StaticText10, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ComboBoxAmbient = new wxComboBox(this, idComboBoxAmbient, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxAmbient"));
	GridBagSizerTextures->Add(ComboBoxAmbient, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, wxID_ANY, _("Diffuse:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerTextures->Add(StaticText11, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ComboBoxDiffuse = new wxComboBox(this, idComboBoxDiffuse, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxDiffuse"));
	GridBagSizerTextures->Add(ComboBoxDiffuse, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, wxID_ANY, _("Specular:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerTextures->Add(StaticText12, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ComboBoxSpecular = new wxComboBox(this, idComboBoxSpecular, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxSpecular"));
	GridBagSizerTextures->Add(ComboBoxSpecular, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, wxID_ANY, _("Normal:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerTextures->Add(StaticText13, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	ComboBoxNormal = new wxComboBox(this, idComboBoxNormal, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxNormal"));
	GridBagSizerTextures->Add(ComboBoxNormal, wxGBPosition(3, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBSizerTextures->Add(GridBagSizerTextures, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	GridBagSizerOptionsAll->Add(SBSizerTextures, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	SBSizerFlags = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Other"));
	GridBagSizerOther = new wxGridBagSizer(0, 0);
	wxString __wxRadioBoxChoices_1[3] =
	{
		_("None"),
		_("Additive"),
		_("Transparency")
	};
	RadioBoxBlend = new wxRadioBox(this, idRadioBoxBlend, _("Blend"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_1, 3, 0, wxDefaultValidator, _T("idRadioBoxBlend"));
	GridBagSizerOther->Add(RadioBoxBlend, wxGBPosition(0, 2), wxGBSpan(2, 1), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxCullFace = new wxCheckBox(this, idCheckBoxCullFaceFlag, _("Cull face"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxCullFaceFlag"));
	CheckBoxCullFace->SetValue(false);
	GridBagSizerOther->Add(CheckBoxCullFace, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxDepthTest = new wxCheckBox(this, idCheckBoxDepthTestFlag, _("Depth test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxDepthTestFlag"));
	CheckBoxDepthTest->SetValue(false);
	GridBagSizerOther->Add(CheckBoxDepthTest, wxGBPosition(2, 2), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxDepthWriteMask = new wxCheckBox(this, idCheckBoxDepthWriteMaskFlag, _("Depth write mask"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxDepthWriteMaskFlag"));
	CheckBoxDepthWriteMask->SetValue(false);
	GridBagSizerOther->Add(CheckBoxDepthWriteMask, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxTextureRepeat = new wxCheckBox(this, idCheckBoxTextureRepeatFlag, _("Texture repeat"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxTextureRepeatFlag"));
	CheckBoxTextureRepeat->SetValue(false);
	GridBagSizerOther->Add(CheckBoxTextureRepeat, wxGBPosition(3, 2), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Counterclockwise"),
		_("Clockwise")
	};
	RadioBoxFrontFace = new wxRadioBox(this, idRadioBoxFrontFace, _("Front face"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, 0, wxDefaultValidator, _T("idRadioBoxFrontFace"));
	GridBagSizerOther->Add(RadioBoxFrontFace, wxGBPosition(1, 0), wxGBSpan(1, 2), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, wxID_ANY, _("Burn:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerOther->Add(StaticText15, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BurnSpinCtrl = new wxSpinCtrl(this, idBurnSpin, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("idBurnSpin"));
	BurnSpinCtrl->SetValue(_T("0"));
	GridBagSizerOther->Add(BurnSpinCtrl, wxGBPosition(3, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(this, wxID_ANY, _("Shader:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	GridBagSizerOther->Add(StaticText14, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ComboBoxShader = new wxComboBox(this, idComboBoxShader, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idComboBoxShader"));
	GridBagSizerOther->Add(ComboBoxShader, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SBSizerFlags->Add(GridBagSizerOther, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	GridBagSizerOptionsAll->Add(SBSizerFlags, wxGBPosition(1, 2), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	ButtonSave = new wxButton(this, idButtonSave, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonSave"));
	BoxSizer2->Add(ButtonSave, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonApply = new wxButton(this, idButtonApply, _("Apply"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonApply"));
	ButtonApply->SetDefault();
	BoxSizer2->Add(ButtonApply, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonCancel = new wxButton(this, idButtonCancel, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonCancel"));
	BoxSizer2->Add(ButtonCancel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizerOptionsAll->Add(BoxSizer2, wxGBPosition(2, 2), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	ButtonNew = new wxButton(this, idButtonNew, _("New"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonNew"));
	BoxSizer3->Add(ButtonNew, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonDelete = new wxButton(this, idButtonDelete, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonDelete"));
	BoxSizer3->Add(ButtonDelete, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonDuplicate = new wxButton(this, idButtonDuplicate, _("Duplicate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonDuplicate"));
	BoxSizer3->Add(ButtonDuplicate, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizerOptionsAll->Add(BoxSizer3, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MaterialsListBox = new wxListBox(this, idMaterialsListBox, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idMaterialsListBox"));
	GridBagSizerOptionsAll->Add(MaterialsListBox, wxGBPosition(0, 0), wxGBSpan(3, 1), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(GridBagSizerOptionsAll);
	GridBagSizerOptionsAll->Fit(this);
	GridBagSizerOptionsAll->SetSizeHints(this);
	Center();

	Connect(idMaterialName,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnMaterialNameTextCtrlText);
	Connect(idMaterialName,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnMaterialNameTextCtrlText);
	Connect(idIORTextValue,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnIORTextCtrlText);
	Connect(idIORTextValue,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnIORTextCtrlText);
	Connect(idIORTextValue,wxEVT_COMMAND_TEXT_MAXLEN,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnIORTextCtrlText);
	Connect(idIORSpinArrows,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnIORSpinButtonChange);
	Connect(idIORSpinArrows,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnIORSpinButtonChange);
	Connect(idIORSpinArrows,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnIORSpinButtonChange);
	Connect(idColourPickerAmbient,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idColurPickerDiffuse,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idColourPickerSpecular,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idColourPickerTransmittance,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idColourPickerEmission,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnColourPickerColourChanged);
	Connect(idComboBoxAmbient,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureSelected);
	Connect(idComboBoxAmbient,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated);
	Connect(idComboBoxAmbient,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated);
	Connect(idComboBoxDiffuse,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureSelected);
	Connect(idComboBoxDiffuse,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated);
	Connect(idComboBoxDiffuse,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated);
	Connect(idComboBoxSpecular,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureSelected);
	Connect(idComboBoxSpecular,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated);
	Connect(idComboBoxSpecular,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated);
	Connect(idComboBoxNormal,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureSelected);
	Connect(idComboBoxNormal,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated);
	Connect(idComboBoxNormal,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated);
	Connect(idRadioBoxBlend,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnRadioBoxBlendSelect);
	Connect(idCheckBoxCullFaceFlag,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnCheckBoxStdClick);
	Connect(idCheckBoxDepthTestFlag,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnCheckBoxStdClick);
	Connect(idCheckBoxDepthWriteMaskFlag,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnCheckBoxStdClick);
	Connect(idCheckBoxTextureRepeatFlag,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnCheckBoxStdClick);
	Connect(idRadioBoxFrontFace,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnRadioBoxFrontFaceSelect);
	Connect(idComboBoxShader,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxShaderSelected);
	Connect(idComboBoxShader,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxShaderTextUpdated);
	Connect(idComboBoxShader,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnComboBoxShaderTextUpdated);
	Connect(idButtonSave,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonApply,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonNew,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonDelete,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idButtonDuplicate,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnButtonStdClick);
	Connect(idMaterialsListBox,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&CBspMaterialsEditDialog::OnMaterialsListBoxSelect);
	//*)

        GridBagSizerGeneral->AddGrowableCol(1);
        GridBagSizerTextures->AddGrowableCol(1);
        GridBagSizerOptionsAll->AddGrowableCol(2);
        this->SetAutoLayout(true);
        
        m_pShaderMgr = NULL;
        m_pResourceMgr = NULL;
        m_pMaterials = NULL;
}
//------------------------------------------------------------------------------

CBspMaterialsEditDialog::~CBspMaterialsEditDialog() {
    //(*Destroy(CBspMaterialsEditDialog)
    //*)
    FG_LOG_DEBUG("WX: Materials Edit Dialog destroyed...");
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::refreshInternals(void) {
    if(m_pShaderMgr) {
        m_shaderNames.clear();
        m_pShaderMgr->getShaderNames(m_shaderNames);
    }
    if(m_pResourceMgr) {
        m_textureNames.clear();
        fg::resource::ResourceType resTypes[] = {fg::resource::TEXTURE};
        m_pResourceMgr->getResourceNames(m_textureNames, fg::resource::TEXTURE);
    }    
}
//------------------------------------------------------------------------------
bool CBspMaterialsEditDialog::Close(bool force) {
    FG_LOG_DEBUG("WX: Materials Edit Dialog Close function...");
    // FIXME ?
    return this->Destroy();
}
//------------------------------------------------------------------------------

bool CBspMaterialsEditDialog::Show(bool show) {
    if(show) {
        refreshMaterialsList();        
        MaterialsListBox->SetSelection(0, true); // this does not throw any event
        
    }
    bool returnValue =  base_type::Show(show);
    if(show) {
        refreshOptions();
        this->DoLayoutAdaptation();
    }
    return returnValue;
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

int CBspMaterialsEditDialog::getMaterialListIndex(const wxString& materialName) { 
    if(materialName.IsEmpty() || !MaterialsListBox ||MaterialsListBox->IsEmpty())
        return -1;
    int listIndex = -1;
    const unsigned int n = MaterialsListBox->GetCount();
    for(unsigned int i = 0; i < n; i++) {
        wxString itemStr = MaterialsListBox->GetString(i);
        if(itemStr.compare(materialName)) {
            listIndex = i;
            break;
        }
    }
    return listIndex;
}
//------------------------------------------------------------------------------

int CBspMaterialsEditDialog::getMaterialListIndex(const std::string& materialName) {
    if(materialName.empty() || !MaterialsListBox ||MaterialsListBox->IsEmpty())
        return -1;
    int listIndex = -1;
    const unsigned int n = MaterialsListBox->GetCount();
    for(unsigned int i = 0; i < n; i++) {
        wxString itemStr = MaterialsListBox->GetString(i);
        if(itemStr.compare(materialName.c_str())) {
            listIndex = i;
            break;
        }
    }
    return listIndex;
}
//------------------------------------------------------------------------------

int CBspMaterialsEditDialog::getMaterialListIndex(const char* materialName) {
    if(!materialName || !MaterialsListBox ||MaterialsListBox->IsEmpty())
        return -1;
    if(!materialName[0])
        return -1;
    int listIndex = -1;
    const unsigned int n = MaterialsListBox->GetCount();
    for(unsigned int i = 0; i < n; i++) {
        wxString itemStr = MaterialsListBox->GetString(i);
        if(itemStr.compare(materialName)) {
            listIndex = i;
            break;
        }
    }
    return listIndex;
}
//------------------------------------------------------------------------------

int CBspMaterialsEditDialog::getMaterialListIndex(fg::gfx::SMaterial* pMaterial) {
    if(!pMaterial)
        return -1;
    int listIndex = -1;
    const unsigned int n = MaterialsListBox->GetCount();
    for(unsigned int i = 0; i < n; i++) {
        void *userData = MaterialsListBox->GetClientData(i);
        fg::gfx::SMaterial* pClientDataMaterial = (fg::gfx::SMaterial *)userData;
        wxString itemStr = MaterialsListBox->GetString(i);
        if(itemStr.compare(pMaterial->name.c_str()) && pMaterial == pClientDataMaterial) {
            listIndex = i;
            break;
        }
    }
    return listIndex;
}
//------------------------------------------------------------------------------

int CBspMaterialsEditDialog::getMaterialVecIndex(const wxString& materialName) {
    if(materialName.IsEmpty() || !m_pMaterials)
        return -1;
    int vecIndex = -1;
    MaterialsVec& materials = *m_pMaterials;
    const unsigned int n = materials.size();
    for(unsigned int i = 0; i < n; i ++) {
        fg::gfx::SMaterial& material = materials[i];
        if(materialName.compare(material.name.c_str()) == 0) {
            vecIndex = i;
            break;
        }
    }
    return vecIndex;
}
//------------------------------------------------------------------------------

int CBspMaterialsEditDialog::getMaterialVecIndex(const std::string& materialName) {
    if(materialName.empty() || !m_pMaterials)
        return -1;
    int vecIndex = -1;
    MaterialsVec& materials = *m_pMaterials;
    const unsigned int n = materials.size();
    for(unsigned int i = 0; i < n; i ++) {
        fg::gfx::SMaterial& material = materials[i];
        if(materialName.compare(material.name.c_str()) == 0) {
            vecIndex = i;
            break;
        }
    }
    return vecIndex;
}
//------------------------------------------------------------------------------

int CBspMaterialsEditDialog::getMaterialVecIndex(const char* materialName) {
    if(!materialName || !m_pMaterials)
        return -1;
    if(!materialName[0])
        return -1;
    int vecIndex = -1;
    MaterialsVec& materials = *m_pMaterials;
    const unsigned int n = materials.size();
    for(unsigned int i = 0; i < n; i ++) {
        fg::gfx::SMaterial& material = materials[i];
        if(material.name.compare(materialName) == 0) {
            vecIndex = i;
            break;
        }
    }
    return vecIndex;
}
//------------------------------------------------------------------------------

int CBspMaterialsEditDialog::getMaterialVecIndex(int selectionIndex) {
    if(selectionIndex < 0 || !MaterialsListBox )
        return -1;
    int vecIndex = -1;
    wxString materialName = MaterialsListBox->GetStringSelection();
    vecIndex = getMaterialVecIndex(materialName);
    return vecIndex;
}
//------------------------------------------------------------------------------

fg::gfx::SMaterial* CBspMaterialsEditDialog::getMaterial(const wxString& materialName) { 
    if(materialName.IsEmpty() || !m_pMaterials)
        return NULL;
    fg::gfx::SMaterial* pMaterial = NULL;
    int vecIndex = getMaterialVecIndex(materialName);
    if(vecIndex < 0)
        return NULL;
    MaterialsVec& materials = *m_pMaterials;
    pMaterial = &(materials[vecIndex]);
    return pMaterial;
}
//------------------------------------------------------------------------------

fg::gfx::SMaterial* CBspMaterialsEditDialog::getMaterial(const std::string& materialName) {
    if(materialName.empty() || !m_pMaterials)
        return NULL;
    fg::gfx::SMaterial* pMaterial = NULL;
    int vecIndex = getMaterialVecIndex(materialName);
    if(vecIndex < 0)
        return NULL;
    MaterialsVec& materials = *m_pMaterials;
    pMaterial = &(materials[vecIndex]);
    return pMaterial;
}
//------------------------------------------------------------------------------

fg::gfx::SMaterial* CBspMaterialsEditDialog::getMaterial(const char* materialName) { 
    if(!materialName || !m_pMaterials)
        return NULL;
    if(!materialName[0])
        return NULL;
    fg::gfx::SMaterial* pMaterial = NULL;
    int vecIndex = getMaterialVecIndex(materialName);
    if(vecIndex < 0)
        return NULL;
    MaterialsVec& materials = *m_pMaterials;
    pMaterial = &(materials[vecIndex]);
    return pMaterial;
}
//------------------------------------------------------------------------------

fg::gfx::SMaterial* CBspMaterialsEditDialog::getMaterial(int selectionIndex) {
    if(selectionIndex < 0 || !MaterialsListBox || !m_pMaterials)
        return NULL;
    fg::gfx::SMaterial* pMaterial = NULL;
    int vecIndex = -1;
    void* clientData = MaterialsListBox->GetClientData(selectionIndex);
    if(!clientData) {
        wxString materialName = MaterialsListBox->GetString(selectionIndex);
        vecIndex = getMaterialVecIndex(materialName);
        if(vecIndex < 0)
            return NULL;
        MaterialsVec& materials = *m_pMaterials;
        pMaterial = &(materials[vecIndex]);
    } else {
        pMaterial = (fg::gfx::SMaterial*)clientData;
    }
    return pMaterial;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::duplicateMaterial(fg::gfx::SMaterial* pMaterial) {
    if(!pMaterial)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::deleteMaterial(fg::gfx::SMaterial* pMaterial) {
    if(!pMaterial)
        return FG_FALSE;
    if(pMaterial->name.empty())
        return FG_FALSE;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::duplicateMaterial(int selectionIndex) {
    if(selectionIndex < 0)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::deleteMaterial(int selectionIndex) {
    if(selectionIndex < 0)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::refreshMaterialsList(void) {
    if(!m_pResourceMgr || !m_pShaderMgr || !m_pMaterials)
        return FG_FALSE;
    MaterialsListBox->Clear();
    MaterialsListBox->Enable(false);
    MaterialsListBox->Freeze();
    MaterialsVec & materials = *m_pMaterials;
    const unsigned int n = materials.size();
    for(unsigned int i = 0; i < n; i++) {
        fg::gfx::SMaterial& material = materials[i];
        MaterialsListBox->Append(_(material.name.c_str()), (void*)&material);
    }
    if(!n) {
        // The list is empty
        materials.push_back(fg::gfx::SMaterial());
        materials[0].name = "DefaultMaterial";
        MaterialsListBox->Append(_(materials[0].name.c_str()), (void*)&materials[0]);
    }

    MaterialsListBox->Thaw();
    MaterialsListBox->Enable(true);    
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::resolveDuplicates(void) {
    
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::didOptionsChange(void) {

    // options did not change - can refresh - no data lost
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::refreshOptions(void) {
    if(!IsVisible() || !IsShown() || !IsShownOnScreen()) {
        return FG_FALSE;
    }
    int selection = MaterialsListBox->GetSelection();
    if(selection < 0)
        return FG_FALSE;

    fg::gfx::SMaterial* pMaterial = getMaterial(selection);
    if(!pMaterial)
        return FG_FALSE;

    populateShaderComboBox(ComboBoxShader);
    populateTextureComboBox(ComboBoxAmbient);
    populateTextureComboBox(ComboBoxDiffuse);
    populateTextureComboBox(ComboBoxSpecular);
    populateTextureComboBox(ComboBoxNormal);

    MaterialNameTextCtrl->ChangeValue(_(pMaterial->name.c_str()));
    //IORTextCtrl->ChangeValue(wxEmptyString);
    // 0 - 1000
    float shininess = pMaterial->shininess;
    ShininessSpinCtrl->SetValue((int)shininess);
    DissolveSpinCtrl->SetValue((int)(100.0f * pMaterial->dissolve));
    BurnSpinCtrl->SetValue((int)(100.0f * pMaterial->burn));
    wxColour colour;
    unsigned char r,g,b,a;
    r = (unsigned char)(255.0f * pMaterial->ambient.r);
    g = (unsigned char)(255.0f * pMaterial->ambient.g);
    b = (unsigned char)(255.0f * pMaterial->ambient.b);
    a = (unsigned char)(255.0f * pMaterial->ambient.a);
    colour.Set(r,g,b,a);
    ColourPickerAmbient->SetColour(colour);
    r = (unsigned char)(255.0f * pMaterial->diffuse.r);
    g = (unsigned char)(255.0f * pMaterial->diffuse.g);
    b = (unsigned char)(255.0f * pMaterial->diffuse.b);
    a = (unsigned char)(255.0f * pMaterial->diffuse.a);
    colour.Set(r,g,b,a);
    ColourPickerDiffuse->SetColour(colour);
    r = (unsigned char)(255.0f * pMaterial->specular.r);
    g = (unsigned char)(255.0f * pMaterial->specular.g);
    b = (unsigned char)(255.0f * pMaterial->specular.b);
    a = (unsigned char)(255.0f * pMaterial->specular.a);
    colour.Set(r,g,b,a);
    ColourPickerSpecular->SetColour(colour);
    r = (unsigned char)(255.0f * pMaterial->transmittance.r);
    g = (unsigned char)(255.0f * pMaterial->transmittance.g);
    b = (unsigned char)(255.0f * pMaterial->transmittance.b);
    a = (unsigned char)(255.0f * pMaterial->transmittance.a);
    colour.Set(r,g,b,a);
    ColourPickerTransmittance->SetColour(colour);
    r = (unsigned char)(255.0f * pMaterial->emission.r);
    g = (unsigned char)(255.0f * pMaterial->emission.g);
    b = (unsigned char)(255.0f * pMaterial->emission.b);
    a = (unsigned char)(255.0f * pMaterial->emission.a);
    colour.Set(r,g,b,a);
    ColourPickerEmission->SetColour(colour);

    if(pMaterial->ambientTexName.empty()) {
        ComboBoxAmbient->ChangeValue(_(NO_TEXTURE_TEXT));
    } else {
        ComboBoxAmbient->ChangeValue(pMaterial->ambientTexName);
    }
    if(pMaterial->diffuseTexName.empty()) {
        ComboBoxDiffuse->ChangeValue(_(NO_TEXTURE_TEXT));
    } else {
        ComboBoxDiffuse->ChangeValue(pMaterial->diffuseTexName);
    }
    if(pMaterial->specularTexName.empty()) {
        ComboBoxSpecular->ChangeValue(_(NO_TEXTURE_TEXT));
    } else {
        ComboBoxSpecular->ChangeValue(pMaterial->specularTexName);
    }
    if(pMaterial->normalTexName.empty()) {
        ComboBoxNormal->ChangeValue(_(NO_TEXTURE_TEXT));
    } else {
        ComboBoxNormal->ChangeValue(pMaterial->normalTexName);
    }

    //wxString blendString = RadioBoxBlend->GetStringSelection();
    //int blendSelection = RadioBoxBlend->GetSelection();
    fg::gfx::BlendMode blendMode = pMaterial->blendMode;
    if(blendMode == fg::gfx::BLEND_OFF)
        RadioBoxBlend->SetSelection(0);
    else if(blendMode == fg::gfx::BLEND_ADDITIVE)
        RadioBoxBlend->SetSelection(1);
    else
        RadioBoxBlend->SetSelection(2);

    CheckBoxCullFace->SetValue((bool)pMaterial->isCullFace());
    CheckBoxDepthTest->SetValue((bool)pMaterial->isDepthTest());
    CheckBoxDepthWriteMask->SetValue((bool)pMaterial->isDepthWriteMask());
    CheckBoxTextureRepeat->SetValue((bool)pMaterial->isTextureRepeat());

    if(pMaterial->isFrontFaceCCW())
        RadioBoxFrontFace->SetSelection(0);
    else if(pMaterial->isFrontFaceCW())
        RadioBoxFrontFace->SetSelection(1);

    if(pMaterial->shaderName.empty()) {
        ComboBoxShader->ChangeValue(_(DEFAULT_SHADER_TEXT));
    } else {
        ComboBoxShader->ChangeValue(pMaterial->shaderName);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::saveOptions(void) {
     if(!IsVisible() || !IsShown() || !IsShownOnScreen()) {
        return FG_FALSE;
    }
    int selection = MaterialsListBox->GetSelection();
    if(selection < 0)
        return FG_FALSE;

    fg::gfx::SMaterial* pMaterial = getMaterial(selection);
    if(!pMaterial)
        return FG_FALSE;

    pMaterial->setCullFace((fgBool)CheckBoxCullFace->GetValue());
    pMaterial->setDepthTest((fgBool)CheckBoxDepthTest->GetValue());
    pMaterial->setDepthWriteMask((fgBool)CheckBoxDepthWriteMask->GetValue());
    pMaterial->setTextureRepeat((fgBool)CheckBoxTextureRepeat->GetValue());

    if(RadioBoxFrontFace->GetSelection() == 0)
        pMaterial->setFrontFace(fg::gfx::FrontFace::FACE_CCW);
    else
        pMaterial->setFrontFace(fg::gfx::FrontFace::FACE_CW);

    if(RadioBoxBlend->GetSelection() == 0)
        pMaterial->blendMode = fg::gfx::BLEND_OFF;
    else if(RadioBoxBlend->GetSelection() == 1)
        pMaterial->blendMode = fg::gfx::BLEND_ADDITIVE;
    else
        pMaterial->blendMode = fg::gfx::BLEND_TRANSPARENCY;

    pMaterial->shaderName.clear();
    wxString shaderName = ComboBoxShader->GetValue();
    if(shaderName.compare(DEFAULT_SHADER_TEXT) != 0)
        pMaterial->shaderName.append(shaderName.c_str().AsChar());

    pMaterial->ambientTexName.clear();
    wxString textureName = ComboBoxAmbient->GetValue();
    if(textureName.compare(NO_TEXTURE_TEXT) != 0)
        pMaterial->ambientTexName.append(textureName.c_str().AsChar());
    
    pMaterial->diffuseTexName.clear();
    textureName = ComboBoxDiffuse->GetValue();
    if(textureName.compare(NO_TEXTURE_TEXT) != 0)
        pMaterial->diffuseTexName.append(textureName.c_str().AsChar());
    
    pMaterial->specularTexName.clear();
    textureName = ComboBoxSpecular->GetValue();
    if(textureName.compare(NO_TEXTURE_TEXT) != 0)
        pMaterial->specularTexName.append(textureName.c_str().AsChar());
    
    pMaterial->normalTexName.clear();
    textureName = ComboBoxNormal->GetValue();
    if(textureName.compare(NO_TEXTURE_TEXT) != 0)
        pMaterial->normalTexName.append(textureName.c_str().AsChar());

    wxColour colour = ColourPickerAmbient->GetColour();
    fg::Color4f *fgColor = &(pMaterial->ambient);
    fgColor->r = ((float)colour.Red())/255.0f;
    fgColor->g = ((float)colour.Green())/255.0f;
    fgColor->b = ((float)colour.Blue())/255.0f;
    fgColor->a = ((float)colour.Alpha())/255.0f;

    colour = ColourPickerDiffuse->GetColour();
    fgColor = &(pMaterial->diffuse);
    fgColor->r = ((float)colour.Red())/255.0f;
    fgColor->g = ((float)colour.Green())/255.0f;
    fgColor->b = ((float)colour.Blue())/255.0f;
    fgColor->a = ((float)colour.Alpha())/255.0f;

    colour = ColourPickerSpecular->GetColour();
    fgColor = &(pMaterial->specular);
    fgColor->r = ((float)colour.Red())/255.0f;
    fgColor->g = ((float)colour.Green())/255.0f;
    fgColor->b = ((float)colour.Blue())/255.0f;
    fgColor->a = ((float)colour.Alpha())/255.0f;

    colour = ColourPickerTransmittance->GetColour();
    fgColor = &(pMaterial->transmittance);
    fgColor->r = ((float)colour.Red())/255.0f;
    fgColor->g = ((float)colour.Green())/255.0f;
    fgColor->b = ((float)colour.Blue())/255.0f;
    fgColor->a = ((float)colour.Alpha())/255.0f;

    colour = ColourPickerEmission->GetColour();
    fgColor = &(pMaterial->emission);
    fgColor->r = ((float)colour.Red())/255.0f;
    fgColor->g = ((float)colour.Green())/255.0f;
    fgColor->b = ((float)colour.Blue())/255.0f;
    fgColor->a = ((float)colour.Alpha())/255.0f;
    
    //MaterialNameTextCtrl->ChangeValue(_(pMaterial->name.c_str()));
    //IORTextCtrl->ChangeValue(wxEmptyString);
    // 0 - 1000
    //float shininess = pMaterial->shininess;
    //ShininessSpinCtrl->SetValue((int)shininess);
    //DissolveSpinCtrl->SetValue((int)(100.0f * pMaterial->dissolve));
    //BurnSpinCtrl->SetValue((int)(100.0f * pMaterial->burn));

    pMaterial->name.clear();
    wxString materialName = MaterialNameTextCtrl->GetValue();
    if(materialName.IsEmpty()) {
        pMaterial->name = "Generic material name\0";
    } else {
        pMaterial->name.append(materialName.c_str().AsChar());
    }
    MaterialsListBox->SetString(selection, _(pMaterial->name.c_str()));

    pMaterial->shininess = (float)ShininessSpinCtrl->GetValue();
    pMaterial->dissolve = ((float)DissolveSpinCtrl->GetValue())/100.0f;
    pMaterial->burn = ((float)BurnSpinCtrl->GetValue())/100.0f;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::validateOptions(void) {
    if(!IsVisible() || !IsShown() || !IsShownOnScreen()) {
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::validateTextureComboBox(wxComboBox* pComboBox) {
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::validateShaderComboBox(wxComboBox* pComboBox) {
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::populateTextureComboBox(wxComboBox* pComboBox) {
    if(!pComboBox)
        return FG_FALSE;    
    pComboBox->Clear();
    const unsigned int n = m_textureNames.size();
    pComboBox->Append(_(NO_TEXTURE_TEXT));
    for(unsigned int i = 0; i < n; i++) {
        wxString itemStr = m_textureNames[i].c_str();
        pComboBox->Append(itemStr);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CBspMaterialsEditDialog::populateShaderComboBox(wxComboBox* pComboBox) {
    if(!pComboBox)
        return FG_FALSE;
    pComboBox->Clear();
    const unsigned int n = m_shaderNames.size();
    pComboBox->Append(_(DEFAULT_SHADER_TEXT));
    for(unsigned int i = 0; i < n; i++) {
        wxString itemStr = m_shaderNames[i].c_str();
        pComboBox->Append(itemStr);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnRadioBoxBlendSelect(wxCommandEvent& event) {
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnComboBoxTextureSelected(wxCommandEvent& event) {
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnColourPickerColourChanged(wxColourPickerEvent& event) {
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnRadioBoxFrontFaceSelect(wxCommandEvent& event) {
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnMaterialsListBoxSelect(wxCommandEvent& event) {
    if(event.GetEventType() != wxEVT_LISTBOX) {
        event.Skip();
        return;
    }
    if(didOptionsChange()) {
        // The options did change so need to veto; ask to save changes, message box...
    }
    // refresh the options widgets so they will reflect the values of the newly
    // selected material
    refreshOptions();
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnButtonStdClick(wxCommandEvent& event) {
    const int id = event.GetId();
    if(!m_pMaterials)
        return;
    MaterialsVec& materials = *m_pMaterials;
    unsigned int n = materials.size();
    if(id == idButtonNew) {
        fgBool canChange = FG_TRUE; // fix me
        if(didOptionsChange()) {

        }
        // Create new material
        materials.push_back(fg::gfx::SMaterial());
        materials[n].name = "New material";
        refreshMaterialsList();
        MaterialsListBox->DeselectAll();
        MaterialsListBox->SetSelection(n, true);
        refreshOptions();
    } else if(id == idButtonDelete) {
            
    } else if(id == idButtonDuplicate) {
            
    } else if(id == idButtonSave) {
        if(validateOptions()) {
            saveOptions();
        }
        this->Show(false);
    } else if(id == idButtonApply) {
        if(validateOptions()) {
            saveOptions();
        }
    } else if(id == idButtonCancel) {
        // question?
        this->Show(false);
    }
            
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnCheckBoxStdClick(wxCommandEvent& event) {
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnComboBoxTextureTextUpdated(wxCommandEvent& event) {
    // events: EVT_TEXT/ENTER
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnComboBoxShaderSelected(wxCommandEvent& event) {
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnComboBoxShaderTextUpdated(wxCommandEvent& event) {
    // events: EVT_TEXT/ENTER
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnMaterialNameTextCtrlText(wxCommandEvent& event) {
    // events: EVT_TEXT/ENTER
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnIORSpinButtonChange(wxSpinEvent& event) {
    // events: EVT_SPIN/UP/DOWN
}
//------------------------------------------------------------------------------

void CBspMaterialsEditDialog::OnIORTextCtrlText(wxCommandEvent& event) {
    // events: EVT_TEXT/ENTER + EVT_TEXT_MAXLEN
}
//------------------------------------------------------------------------------
