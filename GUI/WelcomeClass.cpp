#include "WelcomeClass.h"

WelcomeClass::WelcomeClass(wxWindow* parent)
    : WelcomeClassBase(parent)
{
    Time=0;
    wxLog::SetLogLevel(0);
    
    this->SetMinSize(wxSize(650,285));
    this->SetSize(wxSize(650,285));
    wxStaticBitmap* myimage = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(this, wxSize(650,275)), 0 );
    //boxSizer1085->Add(welcomeimage, 1, wxEXPAND, WXC_FROM_DIP(5));
    //welcomeimage->SetMinSize(wxSize(650,275));
    myimage->SetBitmap(GetPng(welcome650325_png,welcome650325_png_size));
    myimage->Refresh(true);
}

WelcomeClass::~WelcomeClass()
{
}

wxBitmap WelcomeClass::GetPng(const void* data, size_t length)
{
    wxMemoryInputStream memIStream(data, length);
    wxImage image(memIStream, wxBITMAP_TYPE_PNG );
    wxBitmap bmp( image );
    return bmp;
}

void WelcomeClass::OnTick(wxTimerEvent& event)
{
    Time++;
    if(Time>WelcomeTime) this->Close();
}
