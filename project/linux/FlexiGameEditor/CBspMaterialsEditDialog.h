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

    #include "fgBool.h"
    #include "fgVector.h"
    #include "GFX/fgGfxMaterial.h"

namespace fg {
    namespace gfx {
        struct SMaterial;
        class CShaderManager;
    }
    namespace resource {
        class CResourceManager;
    }
}

//(*Headers(CBspMaterialsEditDialog)
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/spinbutt.h>
#include <wx/button.h>
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
    typedef CBspMaterialsEditDialog self_type;
    typedef CBspMaterialsEditDialog type;

    typedef fg::CVector<fg::gfx::SMaterial> MaterialsVec;
    typedef MaterialsVec::iterator MaterialsVecItor;
    typedef MaterialsVec::const_iterator MaterialsVecConstItor;
public:

    static const char* const DEFAULT_SHADER_TEXT;
    static const char* const NO_TEXTURE_TEXT;

    /**
     *
     * @param parent
     * @param id
     * @param pos
     * @param size
     */
    CBspMaterialsEditDialog(wxWindow* parent,
                            wxWindowID id = wxID_ANY,
                            const wxPoint& pos = wxDefaultPosition,
                            const wxSize& size = wxDefaultSize);
    /**
     *
     */
    virtual ~CBspMaterialsEditDialog();

    //--------------------------------------------------------------------------

    /**
     *
     */
    void refreshInternals(void);

    /**
     *
     * @param force
     * @return
     */
    bool Close(bool force = false);

    /**
     * Show the edit dialog
     * @param show
     * @return
     */
    virtual bool Show(bool show = true);
    /**
     *
     * @return
     */
    virtual int ShowModal();
    /**
     *
     * @param retCode
     */
    virtual void EndModal(int retCode);

    //--------------------------------------------------------------------------

    /**
     *
     * @param materialName
     * @return
     */
    int getMaterialListIndex(const wxString& materialName);
    /**
     *
     * @param materialName
     * @return
     */
    int getMaterialListIndex(const std::string& materialName);
    /**
     *
     * @param materialName
     * @return
     */
    int getMaterialListIndex(const char* materialName);
    /**
     * 
     * @param pMaterial
     * @return
     */
    int getMaterialListIndex(fg::gfx::SMaterial* pMaterial);

    //--------------------------------------------------------------------------

    /**
     *
     * @param materialName
     * @return
     */
    int getMaterialVecIndex(const wxString& materialName);
    /**
     *
     * @param materialName
     * @return
     */
    int getMaterialVecIndex(const std::string& materialName);
    /**
     *
     * @param materialName
     * @return
     */
    int getMaterialVecIndex(const char* materialName);
    /**
     *
     * @param selectionIndex
     * @return
     */
    int getMaterialVecIndex(int selectionIndex);

    //--------------------------------------------------------------------------

    /**
     *
     * @param materialName
     * @return
     */
    fg::gfx::SMaterial* getMaterial(const wxString& materialName);
    /**
     *
     * @param materialName
     * @return
     */
    fg::gfx::SMaterial* getMaterial(const std::string& materialName);
    /**
     *
     * @param materialName
     * @return
     */
    fg::gfx::SMaterial* getMaterial(const char* materialName);
    /**
     *
     * @param selectionIndex
     * @return
     */
    fg::gfx::SMaterial* getMaterial(int selectionIndex);

    //--------------------------------------------------------------------------

    /**
     * Duplicates the given material, adds it to the list with new name and sets
     * as currently selected (on list)
     * @param pMaterial
     * @return
     */
    fgBool duplicateMaterial(fg::gfx::SMaterial* pMaterial);
    /**
     * Deletes the given material from the list (GUI and internal)
     * @param pMaterial
     * @return
     */
    fgBool deleteMaterial(fg::gfx::SMaterial* pMaterial);

    //fgBool duplicateMaterial(const std::string& materialName);
    //fgBool deleteMaterial(const std::string& materialName);

    /**
     *
     * @param selectionIndex
     * @return
     */
    fgBool duplicateMaterial(int selectionIndex);
    /**
     *
     * @param selectionIndex
     * @return
     */
    fgBool deleteMaterial(int selectionIndex);

    /**
     *
     * @return
     */
    fgBool refreshMaterialsList(void);

    /**
     * 
     */
    void resolveDuplicates(void);

    /**
     * Checks whether or not the options were changed and not saved
     * @return
     */
    fgBool didOptionsChange(void);
    /**
     * Refreshes all widgets to current values (based on the list selection)
     * @return
     */
    fgBool refreshOptions(void);

    /**
     *
     * @return
     */
    fgBool saveOptions(void);

    //--------------------------------------------------------------------------

    /**
     * Validates the all the options (textures, shaders, etc)
     * @return
     */
    fgBool validateOptions(void);

    /**
     * Validates whether or not the current combo box value is valid
     * This should not exactly use the ResourceManager request feature because
     * the request creates and allocates memory when the resource is valid
     * @param pComboBox
     * @return
     */
    fgBool validateTextureComboBox(wxComboBox* pComboBox);
    /**
     * Validates whether or not the current combo box value is valid
     * This should not exactly use the ShaderManager request feature because
     * the request creates and allocates memory when the resource is valid
     * @param pComboBox
     * @return
     */
    fgBool validateShaderComboBox(wxComboBox* pComboBox);

    /**
     * Clears and inserts new valid choices for the texture combo box
     * @param pComboBox
     * @return
     */
    fgBool populateTextureComboBox(wxComboBox* pComboBox);
    /**
     * Clears and inserts new valid choices for the shader combo box
     * @param pComboBox
     * @return
     */
    fgBool populateShaderComboBox(wxComboBox* pComboBox);

    //--------------------------------------------------------------------------
    /**
     * 
     * @param pShaderMgr
     */
    void setShaderManager(fg::gfx::CShaderManager* pShaderMgr) {
        m_pShaderMgr = pShaderMgr;
    }
    /**
     *
     * @param pResourceMgr
     */
    void setResourceManager(fg::resource::CResourceManager* pResourceMgr) {
        m_pResourceMgr = pResourceMgr;
    }
    /**
     *
     * @param pMaterials
     */
    void setMaterialsVector(MaterialsVec* pMaterials) {
        m_pMaterials = pMaterials;
    }

    //--------------------------------------------------------------------------
private:
    ///
    fg::gfx::CShaderManager* m_pShaderMgr;
    ///
    fg::resource::CResourceManager* m_pResourceMgr;
    ///
    fg::CStringVector m_textureNames;
    ///
    fg::CStringVector m_shaderNames;

    /// Pointer to the external material list - in most cases: the internal list
    /// of gfx::CBspTree
    MaterialsVec *m_pMaterials;

    //--------------------------------------------------------------------------

protected:

    //(*Identifiers(CBspMaterialsEditDialog)
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
    static const long idComboBoxShader;
    static const long idButtonSave;
    static const long idButtonApply;
    static const long idButtonCancel;
    static const long idButtonNew;
    static const long idButtonDelete;
    static const long idButtonDuplicate;
    static const long idMaterialsListBox;
    //*)

    //--------------------------------------------------------------------------
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
    wxComboBox* ComboBoxShader;
    wxComboBox* ComboBoxNormal;
    wxButton* ButtonDuplicate;
    wxColourPickerCtrl* ColourPickerTransmittance;
    wxCheckBox* CheckBoxDepthWriteMask;
    wxSpinCtrl* ShininessSpinCtrl;
    wxButton* ButtonSave;
    wxSpinButton* IORSpinButton;
    //*)

    //--------------------------------------------------------------------------
private:

    //(*Handlers(CBspMaterialsEditDialog)
    void OnRadioBoxBlendSelect(wxCommandEvent& event);
    void OnComboBoxTextureSelected(wxCommandEvent& event);
    void OnColourPickerColourChanged(wxColourPickerEvent& event);
    void OnRadioBoxFrontFaceSelect(wxCommandEvent& event);
    void OnMaterialsListBoxSelect(wxCommandEvent& event);
    void OnButtonStdClick(wxCommandEvent& event);
    void OnCheckBoxStdClick(wxCommandEvent& event);
    void OnComboBoxTextureTextUpdated(wxCommandEvent& event);
    void OnComboBoxShaderSelected(wxCommandEvent& event);
    void OnComboBoxShaderTextUpdated(wxCommandEvent& event);
    void OnMaterialNameTextCtrlText(wxCommandEvent& event);
    void OnIORSpinButtonChange(wxSpinEvent& event);
    void OnIORTextCtrlText(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
}; // class CBspMaterialsEditDialog

    #undef FG_INC_BSP_MATERIALS_EDIT_DIALOG_BLOCK
#endif /* FG_INC_BSP_MATERIALS_EDIT_DIALOG */
