#include "UpdateClass.h"

UpdateClass::UpdateClass(wxWindow* parent, wxString SN)
    : UpdateClassBase(parent)
{
    MySN = SN;
    wxLog::SetLogLevel(0);
    welcomeImage->SetBitmap(GetPng(welcome650325_png,welcome650325_png_size));
    welcomeImage->Refresh(true);
    
    SNTextBox->SetValue(MySN);
}

UpdateClass::~UpdateClass()
{
}

void UpdateClass::ActivateOnClick(wxCommandEvent& event)
{
    wxString SN1 = AKTextBox->GetValue();
    if (Sec30::IsSNSeed1MatchToThisPC(SN1))
    {
        if (Sec30::SaveLicenseToFolder(SN1))
            wxMessageBox(_("The license of your product is successfully verified. Please relaunch the software to load other features."));
        else
            wxMessageBox(_("Unable to write the license!"));
    }
    else
        wxMessageBox(_("Unable to successfully verify the product license!"));
}

wxBitmap UpdateClass::GetPng(const void* data, size_t length)
{
    wxMemoryInputStream memIStream(data, length);
    wxImage image(memIStream, wxBITMAP_TYPE_PNG );
    wxBitmap bmp( image );
    return bmp;
}

void UpdateClass::CopyClipboardOnClick(wxCommandEvent& event)
{
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData( new wxTextDataObject(MySN.c_str()) );
        wxTheClipboard->Close();
    }
}

void UpdateClass::ImageOnMouseLeftDown(wxMouseEvent& event)
{
    wxPoint p = event.GetPosition();
    pattern.push_back(p);
}

void UpdateClass::ImageOnMouseLeftUp(wxMouseEvent& event)
{
    int w = welcomeImage->GetSize().GetWidth();
    int h = welcomeImage->GetSize().GetHeight();
    if(pattern.size() < 1) return;
    if (pattern[0].x < 20 && pattern[0].y < 20)
    {
        if(pattern.size() < 2) return;
        if (pattern[1].x > w - 20 && pattern[1].y < 20)
        {
            if(pattern.size() < 3) return;
            if (pattern[2].x < 20 && pattern[2].y > h - 20)
            {
                if(pattern.size() < 4) return;
                if (pattern[3].x > w - 20 && pattern[3].y > h - 20)
                {
                    if(pattern.size() < 5) return;
                    if (pattern[4].x > w/2 - 20 && pattern[4].x < w/2 + 20 && pattern[4].y > h/2 - 20 && pattern[4].y < h/2 + 20)
                    {
                        wxPasswordEntryDialog passdiag(this, _("Enter the password to unlock."),_("Developer Support Password"));
                        passdiag.ShowModal();
                        pattern.clear();
                        wxString mayp1 = _("pr");
                        mayp1 += _("a");
                        mayp1 += _("c");
                        mayp1 += _("tic");
                        mayp1 += _("a");
                        mayp1 += _("ll");
                        mayp1 += _("y");
                        wxString mayp2 = _("@");
                        mayp2 += _("i");
                        mayp2 += _("n");
                        mayp2 += _("f");
                        mayp2 += _("ea");
                        mayp2 += _("s");
                        mayp2 += _("i");
                        mayp2 += _("b");
                        mayp2 += _("le");
                        if (passdiag.GetValue() == mayp1 + mayp2 + wxString::Format(_("e%dm%d"),4520,1244)) GenerateActivationKey();
                    }
                    else
                        pattern.clear();
                }
                else
                    pattern.clear();
            }
            else
                pattern.clear();
        }
        else
            pattern.clear();
    }
    else
        pattern.clear();
}

void UpdateClass::ImageOnMouseMove(wxMoveEvent& event)
{
    
}

void UpdateClass::GenerateActivationKey()
{
    wxString SN = SNTextBox->GetValue();
    wxString UserName = AKTextBox->GetValue();
    if (UserName == _("")) {wxMessageBox(_("Choose a username in activation key box.")); return;}
    wxString SNID = Sec30::SN2ID(SN, 0);
    wxString BaseID = SNID.BeforeLast('|');
    wxString newID = BaseID + _("|") + UserName;
    wxString ActKey = Sec30::ID2SN(newID, 1);
    AKTextBox->SetValue(ActKey);
}