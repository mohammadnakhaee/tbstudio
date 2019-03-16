#ifndef WELCOMECLASS_H
#define WELCOMECLASS_H
#include "wxcrafter.h"
#include "unistd.h"
#include <wx/mstream.h>
#include <welcome650325.h>
#include "wx/log.h"
class WelcomeClass : public WelcomeClassBase
{
public:
    int WelcomeTime = 10;//sec
    int Time = 0;//ses
    WelcomeClass(wxWindow* parent);
    virtual ~WelcomeClass();
    wxBitmap GetPng(const void* data, size_t length);
protected:
    virtual void OnTick(wxTimerEvent& event);
};
#endif // WELCOMECLASS_H
