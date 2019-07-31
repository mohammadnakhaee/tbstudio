#include "ChooseClass.h"

ChooseClass::ChooseClass(wxWindow* parent, int ndatasets, wxString filetype)
    : ChooseClassBase(parent)
{
    this->SetMinSize(wxSize(-1,-1));
    this->SetSize(wxSize(-1,-1));
    fileType->SetLabel(_("File type: ") + filetype);
    nDatasets->SetLabel(wxString::Format(_("The number of datasets in your file: %d") , ndatasets));
    //Select the datasets you are going to load them.
    //Note: The data will be combined as an indivisible fitting dataset.
    for (int i=1; i<=ndatasets; i++)
    {
        wxString dataname = wxString::Format(_("Spin %d") , i);
        wxCheckBox* ctr = new wxCheckBox(this, wxID_ANY, dataname, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
        ctr->SetName(wxString::Format(_("ss%d") , i));
        if (i==1)
            ctr->SetValue(true);
        else
            ctr->SetValue(false);
        ListTitle->GetContainingSizer()->Add(ctr, 0, wxALL, WXC_FROM_DIP(5));
    }
    this->Layout();
    this->Refresh();
}

ChooseClass::~ChooseClass()
{
}

void ChooseClass::Cancel_OnClick(wxCommandEvent& event)
{
}
void ChooseClass::OK_OnCLick(wxCommandEvent& event)
{
}
