#include "ProjectionClass.h"

ProjectionClass::ProjectionClass(wxWindow* parent, Sec30* sec30var, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetName(wxT("ProjectionClass"));
    SetSize(wxDLG_UNIT(this, wxSize(-1,-1)));
    GetSizer()->Fit(this);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Unit-Cell Atoms Projection"),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
    for (int i=1; i<=99; i++)
    {
        wxString label = wxString::Format(wxT("Atom %d"),i);
        wxString name = wxString::Format(wxT("AtomInd%d"),i);
        //wxString Label = sec30->GetAtomLable(i);
        wxComboBox* choicectr = sec30->AddComboCtrl(this, name, label, 80, 110, true);
        choicectr->Append(_("Not set"));
        choicectr->SetEditable(false);
        choicectr->SetBackgroundColour(*wxWHITE);
        choicectr->Select(0);
    }
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_(""),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
}
    
ProjectionClass::~ProjectionClass()
{
    //try{}
    //catch(std::exception& ex)
    //{wxMessageBox(ex.what());}
}
