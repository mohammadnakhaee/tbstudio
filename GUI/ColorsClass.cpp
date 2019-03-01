#include "ColorsClass.h"

ColorsClass::ColorsClass(wxWindow* parent, Sec30* sec30var)
    : ColorsBaseClass(parent)
{
    //153,180,209
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetName(wxT("ColorsClass"));
    SetSize(wxSize(-1,500));
    //GetSizer()->Fit(this);
    wxScrolledWindow* mainscrl = sec30->AddScrolledPanel(this, 340,630);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(mainscrl, _("Atom Styles"),wxColour(wxT("rgb(153,180,209)")));
    wxScrolledWindow* atomcolorlist = sec30->AddScrolledPanel(mainscrl, 340,350);
    for (int i=1; i<=118; i++)
    {
        wxColour c = sec30->GetAtomColor(i);
        sec30->AddColorCtrl(atomcolorlist, _("AColor") + wxString::Format(wxT("%d"),i), wxString::Format(wxT("%d"),i) + _(")  ") + sec30->GetAtomLable(i) ,c,100,100);
    }
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(mainscrl, _("Bond Styles"),wxColour(wxT("rgb(153,180,209)")));
    wxScrolledWindow* bondcolorlist = sec30->AddScrolledPanel(mainscrl, 340,300);
    for (int i=1; i<=50; i++)
    {
        wxColour c = sec30->GetBondColor(i);
        sec30->AddColorCtrl(bondcolorlist, _("BColor") + wxString::Format(wxT("%d"),i), _("Bond ") + wxString::Format(wxT("%d"),i),c,100,100);
    }
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(mainscrl,_(""),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
}

ColorsClass::~ColorsClass()
{
}

void ColorsClass::OnClose(wxCloseEvent& event)
{
    event.Veto(true);
    this->Hide();
}
