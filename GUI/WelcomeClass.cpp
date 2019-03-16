#include "WelcomeClass.h"

WelcomeClass::WelcomeClass(wxWindow* parent)
    : WelcomeClassBase(parent)
{
    Time=0;
    wxLog::SetLogLevel(0);
    welcomeimage->SetBitmap(GetPng(welcome650325_png,welcome650325_png_size));
    welcomeimage->Refresh(true);
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
