#include "BondsClass.h"

/******************************************************************************/
BEGIN_EVENT_TABLE(BondsClass,wxPanel)
    EVT_MENU(wxID_DELETE,BondsClass::OnDelete)
END_EVENT_TABLE()
/******************************************************************************/

BondsClass::BondsClass(wxWindow* parent, Sec30* sec30var, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetName(wxT("BondsClass"));
    SetSize(wxDLG_UNIT(this, wxSize(-1,-1)));
    GetSizer()->Fit(this);
    /**********************************************************************************************************************************************/
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Essential Unit-Cell"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddCheckBox(this, _("WorkingViewmode"), _("Show the working unit cells"));
    wxListBox* esslistctr = sec30->AddListBox(this, _("EssentialUnitcellList"), 340, 120);
    esslistctr->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(BondsClass::EssList_OnSelected), NULL, this);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Connect Two Atoms"),wxColour(wxT("rgb(153,180,209)")));
    wxString Labels2[1] = {_("Pick the selected pair of atoms")};
    wxString Names2[1] = {_("PickAtomBtn")};
    wxObjectEventFunction Funcs2[1] = { wxCommandEventHandler(BondsClass::Btn_Pick_OnClick)};
    sec30->AddButton(this, 1, Names2, Labels2, Funcs2);
    sec30->AddGroupBox(this,_("Atom index and shell number in cell (0,0,0):"),wxColour(wxT("rgb(255,255,255)")));
    sec30->AddVarVector(this, 2, _("AtomIndex1"), _("int"), _("(i,n)"), 70, 50, false);
    sec30->AddGroupBox(this,_("Atom index and shell number in selected cell:"),wxColour(wxT("rgb(255,255,255)")));
    sec30->AddVarVector(this, 2, _("AtomIndex2"), _("int"), _("(j,m)"), 70, 50, false);
    sec30->SetVar(_("AtomIndex1[0]"),1,false);
    sec30->SetVar(_("AtomIndex1[1]"),1,false);
    sec30->SetVar(_("AtomIndex2[0]"),1,false);
    sec30->SetVar(_("AtomIndex2[1]"),1,false);
    wxComboBox* choicectr = sec30->AddComboCtrl(this, _("BondLabel"), _("Bond Label"), 70, 105, false);
    for (int i=1; i<=50; i++)
    {
        //wxImage img = wxImage(wxSize(10,10),true);
        //wxColour c = BondColour(i);
        //img.SetRGB(wxRect(0,0,10,10),c.Red(),c.Green(),c.Blue());
        //choicectr->Append(_("Bond ") + wxString::Format(wxT("%d"), i),img);
        choicectr->Append(_("Bond ") + wxString::Format(wxT("%d"), i));
    }
    choicectr->SetEditable(false);
    choicectr->SetBackgroundColour(*wxWHITE);
    choicectr->Select(0);
    wxString Labels1[1] = {_("Set Bond")};
    wxObjectEventFunction Funcs1[1] = { wxCommandEventHandler(BondsClass::Btn_Set_OnClick)};
    sec30->AddButton(this, 1, Labels1, Funcs1);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("List of Bonds in TB Model"),wxColour(wxT("rgb(153,180,209)")));
    wxCheckTree* treectr = sec30->AddTreeCtrl(this, _("Bonds"), 340, 500, true);
    treectr->AddRoot("TB Model");
    treectr->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(BondsClass::BondsTree_RightDown), NULL, this);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_(""),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
}
    
BondsClass::~BondsClass()
{
    //try{}
    //catch(std::exception& ex)
    //{wxMessageBox(ex.what());}
}

void BondsClass::Btn_Set_OnClick(wxCommandEvent& event)
{
    int i000,sh000;
    int ilmn,shlmn;
    if (!sec30->GetVar(_("AtomIndex1[0]"),i000)) {wxMessageBox(_("The first atom index is empty. Please fill out this field and try again."),_("Error")); return;}
    if (!sec30->GetVar(_("AtomIndex1[1]"),sh000)) {wxMessageBox(_("The first shell index is empty. Please fill out this field and try again."),_("Error")); return;}
    if (!sec30->GetVar(_("AtomIndex2[0]"),ilmn)) {wxMessageBox(_("The second atom index is empty. Please fill out this field and try again."),_("Error")); return;}
    if (!sec30->GetVar(_("AtomIndex2[1]"),shlmn)) {wxMessageBox(_("The second shell index is empty. Please fill out this field and try again."),_("Error")); return;}
    if (i000 < 1 || ilmn < 1) {wxMessageBox(_("The atomic index must be greater than zero. i or j = 1,2,3, ... ."),_("Error")); return;}
    if (sh000 < 1 || shlmn < 1) {wxMessageBox(_("The shell index must be greater than zero. n or m = 1,2,3, ... ."),_("Error")); return;}
    int maxIndex=0;
    sec30->GetVar(_("nAtoms[0]"),maxIndex);
    if (i000 > maxIndex || ilmn > maxIndex) {wxMessageBox(_("You have ") + wxString::Format(wxT("%d"), maxIndex) + _(" atom(s) in your unit cell.") ,_("Error")); return;}
    
    wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
    if (listctr->GetCount() < 1) {wxMessageBox(_("There is a problem in your structure. Please check your inputs in the Unit Cell and the Structure Panels."),_("Error")); return;}
    int lmn = listctr->GetSelection();
    if (lmn < 0) {wxMessageBox(_("Please select the unit cell at which the second atom is located."),_("Error")); return;}
    wxString listucell = listctr->GetString(lmn);
    wxString ucell = _("(0,0,0)-") + listucell;
    
    wxComboBox* bondctr =  sec30->GetComboObject(_("BondLabel"));
    int btypind = bondctr->GetSelection();
    if (btypind < 0) {wxMessageBox(_("Please select the Bond Label."),_("Error")); return;}
    
    wxCheckTree* treectr = sec30->GetTreeObject(_("Bonds"));
    wxTreeItemId rootID = treectr->GetRootItem();
    wxTreeItemId lmnID = treectr->FindItemIn(rootID,ucell);
    
    if (!lmnID)
    {
        treectr->tree_add(rootID,ucell,true,true);
        lmnID = treectr->FindItemIn(rootID,ucell);
    }
    
    if( listucell.CompareTo(_("(0,0,0)")) == 0 )
    {
        if (i000 == ilmn) {wxMessageBox(_("Connection between ") + wxString::Format(wxT("%d"), i000) + _("th atom in cell(0,0,0) and ") + wxString::Format(wxT("%d"), ilmn) + _("th atom in cell") + listucell + _(" has no meaning."),_("Error")); return;}
        if (i000 > ilmn)
        {
            int dummy = i000;
            i000 = ilmn;
            ilmn = dummy;
            
            dummy = sh000;
            sh000 = shlmn;
            shlmn = dummy;
        }
    }
    
    wxString bondinfotest = _("[ (i,n)=") + wxString::Format(wxT("(%d,%d)"), i000, sh000) + _(" , (j,m)=") + wxString::Format(wxT("(%d,%d)"), ilmn, shlmn);
    wxTreeItemId testID = treectr->ContainsItemIn(lmnID,bondinfotest);
    if (testID)
        wxMessageBox(_("There is a bond defined between ") + wxString::Format(wxT("(%d,%d)"), i000, sh000) + _(" in cell(0,0,0) and ") + wxString::Format(wxT("(%d,%d)"), ilmn, shlmn) + _(" in cell") + listucell + _(" in your TB model."),_("Error"));
    else
    {
        wxString bondinfo = _("[ (i,n)=") + wxString::Format(wxT("(%d,%d)"), i000, sh000) + _(" , (j,m)=") + wxString::Format(wxT("(%d,%d)"), ilmn, shlmn) + _(" , ") + bondctr->GetString(btypind) + _(" ]");
        treectr->tree_add(lmnID,bondinfo,true,true);
    }
    treectr->Expand(rootID);
    treectr->Expand(lmnID);
    treectr->Update();
    treectr->Refresh(true);
    
    sec30->SendUpdateEvent(this->GetName());
    //wxCommandEvent* event0 = new wxCommandEvent(Sec30EVT_OnUpdated);
    //event0->SetString(this->GetName());
    //wxQueueEvent(this->GetParent(),event0);
}

void BondsClass::Btn_Pick_OnClick(wxCommandEvent& event)
{
    wxButton* btnctr = (wxButton*)event.GetEventObject();
    //wxButton* btnctr =  sec30->GetButtonObject(_("PickAtomBtn"));
    //btnctr->SetBackgroundColour(wxColour(wxT("rgb(209,153,180)")));
    if (btnctr->GetForegroundColour() == *wxBLACK)
        btnctr->SetForegroundColour(*wxRED);
    else
        btnctr->SetForegroundColour(*wxBLACK);
    
    sec30->SendUpdateEvent(this->GetName(),0);
}

/*
bool on_check_or_label(int flags)
{
    return flags&(wxTREE_HITTEST_ONITEMSTATEICON|wxTREE_HITTEST_ONITEMLABEL)?true:false;
}*/


void BondsClass::BondsTree_RightDown(wxMouseEvent& event)
{
    wxCheckTree* treectr = sec30->GetTreeObject(_("Bonds"));
    
    int flags;
    wxPoint clickpos = event.GetPosition();
    ClickedID = treectr->HitTest( clickpos, flags );
    if (ClickedID == treectr->GetRootItem()) return;
    
    wxMenu *pmenuPopUp = new wxMenu;
    wxMenuItem* pItem;
    
    pItem = new wxMenuItem(pmenuPopUp,wxID_DELETE, wxT("Delete"));
    pmenuPopUp->Append(pItem);
    
    wxPoint treepos = treectr->GetPosition();
    PopupMenu(pmenuPopUp, clickpos.x + treepos.x, clickpos.y + treepos.y);
    delete pmenuPopUp;
}

void BondsClass::OnDelete(wxCommandEvent &event)
{
    wxCheckTree* treectr = sec30->GetTreeObject(_("Bonds"));
    treectr->Delete(ClickedID);
    treectr->Update();
    treectr->Refresh(true);
}

void BondsClass::EssList_OnSelected(wxCommandEvent& event)
{
    bool WorkingViewmode;
    sec30->GetRadioVar(_("WorkingViewmode[0]"),WorkingViewmode);
    if (WorkingViewmode) sec30->SendUpdateEvent(this->GetName());
}
