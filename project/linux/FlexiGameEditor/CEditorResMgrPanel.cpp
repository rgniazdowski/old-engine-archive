/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "CEditorResMgrPanel.h"

#include "fgEngineMain.h"
#include "Resource/fgResourceManager.h"

#include <wx/msgdlg.h>
#include <wx/stattext.h>

//(*InternalHeaders(CEditorResMgrPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CEditorResMgrPanel)
const long CEditorResMgrPanel::ID_RESOURCELISTVIEW = wxNewId();
const long CEditorResMgrPanel::ID_REFRESHLIST_BUTTON = wxNewId();
const long CEditorResMgrPanel::ID_PAGE1 = wxNewId();
const long CEditorResMgrPanel::ID_PAGE2 = wxNewId();
const long CEditorResMgrPanel::ID_PAGE3 = wxNewId();
const long CEditorResMgrPanel::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CEditorResMgrPanel, wxPanel)
//(*EventTable(CEditorResMgrPanel)
//*)
END_EVENT_TABLE()
//------------------------------------------------------------------------------

CEditorResMgrPanel::CEditorResMgrPanel(wxWindow* parent,
                                       wxWindowID id,
                                       const wxPoint& pos,
                                       const wxSize& size) {
    ////////////////////////////////////////////////////////////////////////////
    //(*Initialize(CEditorResMgrPanel)
    wxBoxSizer* BoxSizerMainV;
    wxGridBagSizer* GridBagSizer1;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
    BoxSizerMainV = new wxBoxSizer(wxVERTICAL);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Page1 = new wxPanel(Notebook1, ID_PAGE1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PAGE1"));
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    GridBagSizer1->AddGrowableCol(0);
    GridBagSizer1->AddGrowableRow(0);
    ResourceListView = new wxListView(Page1, ID_RESOURCELISTVIEW, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_RESOURCELISTVIEW"));
    GridBagSizer1->Add(ResourceListView, wxGBPosition(0, 0), wxGBSpan(1, 5), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    RefreshButton = new wxButton(Page1, ID_REFRESHLIST_BUTTON, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REFRESHLIST_BUTTON"));
    GridBagSizer1->Add(RefreshButton, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
    Page1->SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(Page1);
    GridBagSizer1->SetSizeHints(Page1);
    Page2 = new wxPanel(Notebook1, ID_PAGE2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PAGE2"));
    Page3 = new wxPanel(Notebook1, ID_PAGE3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PAGE3"));
    Notebook1->AddPage(Page1, _("Resource list"), true);
    Notebook1->AddPage(Page2, _("Resource preview"), false);
    Notebook1->AddPage(Page3, _("Status"), false);
    BoxSizerMainV->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    SetSizer(BoxSizerMainV);
    BoxSizerMainV->Fit(this);
    BoxSizerMainV->SetSizeHints(this);

    Connect(ID_RESOURCELISTVIEW,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&CEditorResMgrPanel::OnResourceListViewItemAction);
    Connect(ID_REFRESHLIST_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CEditorResMgrPanel::OnResListRefreshButtonClick);
    //*)
    ////////////////////////////////////////////////////////////////////////////

    wxListItem col;
    //col.SetBackgroundColour(wxTheColourDatabase->Find(wxT("DARK GREY")));
    // First column - type name
    col.SetId(0);
    col.SetText(_("Type"));
    col.SetWidth(120);
    ResourceListView->InsertColumn(0, col);

    // Second column - name tag
    col.SetId(1);
    col.SetText(_("Name"));
    col.SetWidth(150);
    ResourceListView->InsertColumn(1, col);

    // Third column is disposed?
    col.SetId(2);
    col.SetText(_("Is loaded?"));
    col.SetWidth(100);
    ResourceListView->InsertColumn(2, col);

    // Fourth column size
    col.SetId(3);
    col.SetText(_("Size (KiB)"));
    col.SetWidth(80);
    ResourceListView->InsertColumn(3, col);

    // Fifth column handle
    col.SetId(4);
    col.SetText(_("Handle"));
    col.SetWidth(160);
    ResourceListView->InsertColumn(4, col);
}
//------------------------------------------------------------------------------

CEditorResMgrPanel::~CEditorResMgrPanel() {
    //(*Destroy(CEditorResMgrPanel)
    //*)
}
//------------------------------------------------------------------------------

fgBool CEditorResMgrPanel::refreshResourceList(void) {
    if(!m_engineMain) {
        return FG_FALSE;
    }
    fg::resource::CResourceManager *pResMgr = m_engineMain->getResourceManager();
    if(!pResMgr) {
        return FG_FALSE;
    }
    //    if(!pResMgr->getRefDataVector().size()) {
    //        return FG_FALSE;
    //    }
    if(!ResourceListView->DeleteAllItems()) {
        return FG_FALSE;
    }
    char str[128];
    int n = 0;
    pResMgr->goToBegin();
    do {
        fg::resource::CResource* pResource = pResMgr->getCurrentResource();
        if(!pResource) {
            continue;
        }
        if(!pResMgr->isValid()) {
            break;
        }
        wxListItem listItem;
        if(n % 2 == 1)
            listItem.SetBackgroundColour(*wxLIGHT_GREY);
        //else
        //    //listItem.SetBackgroundColour(wxTheColourDatabase->Find(wxT("GREY")));
        listItem.SetId(n);
        listItem.SetText(pResource->getNameStr());
        ResourceListView->InsertItem(listItem);
        // Resource type name
        ResourceListView->SetItem(n, 0, fg::resource::getResourceTypeName(pResource->getResourceType()));
        // Resource name
        ResourceListView->SetItem(n, 1, pResource->getNameStr());
        // Disposal status (loaded?)
        if(pResource->isDisposed()) {
            sprintf(str, "Disposed");
        } else {
            sprintf(str, "Loaded");
        }
        ResourceListView->SetItem(n, 2, str);
        // Size
        sprintf(str, "%.2f", (float)pResource->getSize() / 1024.0f);
        ResourceListView->SetItem(n, 3, str);

        // Handle
        pResource->getResourceType();
        sprintf(str, "idx: %d mgx: %d", pResource->getHandle().getIndex(), pResource->getHandle().getMagic());
        ResourceListView->SetItem(n, 4, str);
        n++;
    } while(pResMgr->goToNext());

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CEditorResMgrPanel::OnResListRefreshButtonClick(wxCommandEvent& event) {
    refreshResourceList();
}
//------------------------------------------------------------------------------

void CEditorResMgrPanel::OnResourceListViewItemAction(wxListEvent& event)
{
    wxEventType type = event.GetEventType();
    if(type == wxEVT_LIST_ITEM_ACTIVATED) {
        // Display some detailed window description
        // special small frame? CEditorResInfoFrame
        long idx = ResourceListView->GetFocusedItem();
        if(idx < 0)
            return;
        // 0 - type, 1 - name tag
        //ResourceListView->GetItemText(idx, 0).c_str().AsChar();
        //ResourceListView->GetItemText(idx, 1).c_str().AsChar();
    } else if(type == wxEVT_LIST_ITEM_SELECTED) {

    } else if(type == wxEVT_LIST_ITEM_RIGHT_CLICK) {
        // context menu?
    }
}
//------------------------------------------------------------------------------
