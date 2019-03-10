#include "SKClass.h"

/******************************************************************************/
BEGIN_EVENT_TABLE(SKClass,wxPanel)
    //EVT_MENU(wxID_DELETE,SKClass::OnDelete)
END_EVENT_TABLE()
/******************************************************************************/

SKClass::SKClass(wxWindow* parent, Sec30* sec30var, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetName(wxT("SKClass"));
    SetSize(wxDLG_UNIT(this, wxSize(-1,-1)));
    GetSizer()->Fit(this);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this, _("Setup the Parameter Vector"),wxColour(wxT("rgb(153,180,209)")));
    wxCheckBox* socCtrl = sec30->AddCheckBox(this, _("SOC"), _("Take SOC into Accounts"));
    socCtrl->Enable(false);
    wxCheckBox* OvCtrl = sec30->AddCheckBox(this, _("Overlap"), _("Non-Orthogonal Basis"));
    OvCtrl->Enable(false);
    wxString Labels1[1] = {_("Evaluate Independent Parameters")};
    wxObjectEventFunction Funcs1[1] = {wxCommandEventHandler(SKClass::Btn_Update_OnClick)};
    sec30->AddButton(this, 1, Labels1, Funcs1);
    /**********************************************************************************************************************************************/
    sec30->AddVarVector(this, 1, _("nParameters"), _("int"), _("Number of Parameters"), 140, 100, false, true);
    sec30->SetVar(_("nParameters[0]"), 0, false);
    wxString Labels2[1] = {_("Use Last State as Initial Guess")};
    wxObjectEventFunction Funcs2[1] = { wxCommandEventHandler(SKClass::Btn_LastValues_OnClick)};
    sec30->AddButton(this, 1, Labels2, Funcs2);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("On-Site Energies"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
    wxString ColTypes[3] = { _("string"), _("double"), _("double")};
    int ColSizes[3] = {96, 100, 100};
    int ColPrecision[3] = { 0, 8, 8};
    sec30->AddGrid(this, 0, 3, _("OS"), ColNames, ColTypes, ColSizes, ColPrecision, 350, 400);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Slater-Koster Integrals"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames2[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
    wxString ColTypes2[3] = { _("string"), _("double"), _("double")};
    int ColSizes2[3] = {96, 100, 100};
    int ColPrecision2[3] = { 0, 8, 8};
    sec30->AddGrid(this, 0, 3, _("SK"), ColNames2, ColTypes2, ColSizes2, ColPrecision2, 350, 400);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Overlap Integrals"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames3[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
    wxString ColTypes3[3] = { _("string"), _("double"), _("double")};
    int ColSizes3[3] = {96, 100, 100};
    int ColPrecision3[3] = { 0, 8, 8};
    sec30->AddGrid(this, 0, 3, _("OL"), ColNames3, ColTypes3, ColSizes3, ColPrecision3, 350, 400);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Tools"),wxColour(wxT("rgb(153,180,209)")));
    wxString Labels5[2] = {_("Export Data"), _("Import Data")};
    wxObjectEventFunction Funcs5[2] = {wxCommandEventHandler(SKClass::Btn_ExportData_OnClick), wxCommandEventHandler(SKClass::Btn_ImportData_OnClick)};
    sec30->AddButton(this, 2, Labels5, Funcs5);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_(""),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
}

SKClass::~SKClass()
{
    //try{}
    //catch(std::exception& ex)
    //{wxMessageBox(ex.what());}
}

void SKClass::Btn_Update_OnClick(wxCommandEvent& event)
{
    sec30->SendUpdateEvent(this->GetName(),2);
}

void SKClass::Btn_LastValues_OnClick(wxCommandEvent& event)
{
    sec30->CopyLastSKToInitialSK();
    sec30->SendUpdateEvent(this->GetName());
}

void SKClass::Btn_ExportData_OnClick(wxCommandEvent& event)
{
    
}

void SKClass::Btn_ImportData_OnClick(wxCommandEvent& event)
{
    
}
