/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_BSP_MATERIALS_EDIT_DIALOG
    #define FG_INC_BSP_MATERIALS_EDIT_DIALOG
    #define FG_INC_BSP_MATERIALS_EDIT_DIALOG_BLOCK

//(*Headers(CBspMaterialsEditDialog)
    #include <wx/spinctrl.h>
    #include <wx/combobox.h>
    #include <wx/checkbox.h>
    #include <wx/dialog.h>
    #include <wx/sizer.h>
    #include <wx/spinbutt.h>
    #include <wx/button.h>
    #include <wx/panel.h>
    #include <wx/gbsizer.h>
    #include <wx/stattext.h>
    #include <wx/clrpicker.h>
    #include <wx/textctrl.h>
    #include <wx/radiobox.h>
    #include <wx/listbox.h>
//*)
/**
 *
 */
class CBspMaterialsEditDialog : public wxDialog {
public:
    typedef wxDialog base_type;
public:

    /**
     *
     * @param parent
     * @param id
     * @param pos
     * @param size
     */
    CBspMaterialsEditDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    /**
     *
     */
    virtual ~CBspMaterialsEditDialog();

    /**
     *
     * @param force
     * @return
     */
    bool Close(bool force = false);

    virtual bool Show(bool show = true);
    virtual int ShowModal();
    virtual void EndModal(int retCode);

protected:

    //(*Identifiers(CBspMaterialsEditDialog)
    static const long idMaterialsListBox;
    static const long idMaterialName;
    static const long idIORTextValue;
    static const long idIORSpinArrows;
    static const long idShininessSpin;
    static const long idDissolveSpin;
    static const long idColourPickerAmbient;
    static const long idColurPickerDiffuse;
    static const long idColourPickerSpecular;
    static const long idColourPickerTransmittance;
    static const long idColourPickerEmission;
    static const long idComboBoxAmbient;
    static const long idComboBoxDiffuse;
    static const long idComboBoxSpecular;
    static const long idComboBoxNormal;
    static const long idRadioBoxBlend;
    static const long idCheckBoxCullFaceFlag;
    static const long idCheckBoxDepthTestFlag;
    static const long idCheckBoxDepthWriteMaskFlag;
    static const long idCheckBoxTextureRepeatFlag;
    static const long idRadioBoxFrontFace;
    static const long idBurnSpin;
    static const long idButtonSave;
    static const long idButtonApply;
    static const long idButtonCancel;
    static const long idButtonNew;
    static const long idButtonDelete;
    static const long idButtonDuplicate;
    static const long idMaterialPropsPanel;
    //*)

private:
    //(*Declarations(CBspMaterialsEditDialog)
    wxCheckBox* CheckBoxDepthTest;
    wxCheckBox* CheckBoxTextureRepeat;
    wxColourPickerCtrl* ColourPickerAmbient;
    wxListBox* MaterialsListBox;
    wxRadioBox* RadioBoxFrontFace;
    wxSpinCtrl* BurnSpinCtrl;
    wxButton* ButtonNew;
    wxButton* ButtonApply;
    wxTextCtrl* IORTextCtrl;
    wxButton* ButtonDelete;
    wxTextCtrl* MaterialNameTextCtrl;
    wxComboBox* ComboBoxDiffuse;
    wxColourPickerCtrl* ColourPickerEmission;
    wxButton* ButtonCancel;
    wxComboBox* ComboBoxAmbient;
    wxSpinCtrl* DissolveSpinCtrl;
    wxRadioBox* RadioBoxBlend;
    wxColourPickerCtrl* ColourPickerDiffuse;
    wxComboBox* ComboBoxSpecular;
    wxColourPickerCtrl* ColourPickerSpecular;
    wxCheckBox* CheckBoxCullFace;
    wxComboBox* ComboBoxNormal;
    wxButton* ButtonDuplicate;
    wxColourPickerCtrl* ColourPickerTransmittance;
    wxPanel* MaterialPropsPanel;
    wxCheckBox* CheckBoxDepthWriteMask;
    wxSpinCtrl* ShininessSpinCtrl;
    wxButton* ButtonSave;
    wxSpinButton* IORSpinButton;
    //*)

private:

    //(*Handlers(CBspMaterialsEditDialog)
    void OnRadioBoxBlendSelect(wxCommandEvent& event);
    void OnComboBoxAmbientSelected(wxCommandEvent& event);
    void OnComboBoxDiffuseSelected(wxCommandEvent& event);
    void OnComboBoxSpecularSelected(wxCommandEvent& event);
    void OnComboBoxNormalSelected(wxCommandEvent& event);
    void OnColourPickerColourChanged(wxColourPickerEvent& event);
    void OnRadioBoxFrontFaceSelect(wxCommandEvent& event);
    void OnMaterialsListBoxSelect(wxCommandEvent& event);
    void OnButtonStdClick(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
}; // class CBspMaterialsEditDialog 

    #undef FG_INC_BSP_MATERIALS_EDIT_DIALOG_BLOCK
#endif /* FG_INC_BSP_MATERIALS_EDIT_DIALOG */
