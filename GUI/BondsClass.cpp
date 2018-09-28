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
    sec30->AddGroupBox(this,_("Essential Unit-Cell"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddCheckBox(this, _("WorkingViewmode"), _("Show the working unit cells"));
    sec30->AddListBox(this, _("EssentialUnitcellList"), 340, 120);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Connect Two Atoms"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 1, _("AtomIndex1"), _("int"), _("i : Atom Index in Cell (0,0,0)"), 180, 100);
    sec30->AddVarVector(this, 1, _("AtomIndex2"), _("int"), _("j : Atom Index in Selected Cell"), 180, 100);
    sec30->SetVar(_("AtomIndex1[0]"),1,false);
    sec30->SetVar(_("AtomIndex2[0]"),1,false);
    wxComboBox* choicectr = sec30->AddComboCtrl(this, _("AtomLabel"), _("Bond Label"), 180, 100);
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
    wxCheckTree* treectr = sec30->AddTreeCtrl(this, _("Bonds"), 340, 500);
    wxTreeItemId rootID=treectr->AddRoot("TB Model");
    treectr->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(BondsClass::BondsTree_RightDown), NULL, this);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Bond Styles"),wxColour(wxT("rgb(153,180,209)")));
    wxScrolledWindow* colorlist = sec30->AddScrolledPanel(this, 340, 200);
    for (int i=1; i<=50; i++)
    {
        wxColour c;
        if (i==1)
            c.Set(200,0,60,255);
        else
            c.Set(30,30,200,255);
        sec30->AddColorCtrl(colorlist, _("Color") + wxString::Format(wxT("%d"),i), _("Bond ") + wxString::Format(wxT("%d"),i),c,100,100);
    }
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
    int i000;
    int ilmn;
    if (!sec30->GetVar(_("AtomIndex1[0]"),i000)) {wxMessageBox(_("The first index is empty. Please fill out this field and try again."),_("Error")); return;}
    if (!sec30->GetVar(_("AtomIndex2[0]"),ilmn)) {wxMessageBox(_("The second index is empty. Please fill out this field and try again."),_("Error")); return;}
    if (i000 < 1 || ilmn < 1) {wxMessageBox(_("The atomic index must be greater than zero. i or j = 1,2,3, ... ."),_("Error")); return;}
    int maxIndex=0;
    sec30->GetVar(_("nAtoms[0]"),maxIndex);
    if (i000 > maxIndex || ilmn > maxIndex) {wxMessageBox(_("You have ") + wxString::Format(wxT("%d"), maxIndex) + _(" atom(s) in your unit cell.") ,_("Error")); return;}
    
    wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
    if (listctr->GetCount() < 1) {wxMessageBox(_("There is a problem in your structure. Please check your inputs in Unit Cell and Structure Panels."),_("Error")); return;}
    int lmn = listctr->GetSelection();
    if (lmn < 0) {wxMessageBox(_("Please select the unit cell at which the second atom is located."),_("Error")); return;}
    wxString listucell = listctr->GetString(lmn);
    wxString ucell = _("cell(0,0,0)-cell") + listucell;
    
    wxComboBox* bondctr =  sec30->GetComboObject(_("AtomLabel"));
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
        }
    }
    
    wxString bondinfotest = _("[ i=") + wxString::Format(wxT("%d"), i000) + _(" , j=") + wxString::Format(wxT("%d"), ilmn);
    wxTreeItemId testID = treectr->ContainsItemIn(lmnID,bondinfotest);
    if (testID)
        wxMessageBox(_("There is a bond defined between ") + wxString::Format(wxT("%d"), i000) + _("th atom in cell(0,0,0) and ") + wxString::Format(wxT("%d"), ilmn) + _("th atom in cell") + listucell + _(" in your TB model."),_("Error"));
    else
    {
        wxString bondinfo = _("[ i=") + wxString::Format(wxT("%d"), i000) + _(" , j=") + wxString::Format(wxT("%d"), ilmn) + _(" , ") + bondctr->GetString(btypind) + _(" ]");
        treectr->tree_add(lmnID,bondinfo,true,true);
    }
    treectr->Expand(rootID);
    treectr->Expand(lmnID);
    treectr->Update();
    treectr->Refresh(true);
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