#ifndef WELCOMECLASS_H
#define WELCOMECLASS_H
#include "wxcrafter.h"
#include "unistd.h"
#include <wx/mstream.h>
#include "wx/log.h"
#include <wx/statbmp.h>
#include "Sec30.h"
class WelcomeClass : public WelcomeClassBase
{
public:
    int WelcomeTime = 12;//sec
    int Time = 0;//ses
    WelcomeClass(wxWindow* parent);
    virtual ~WelcomeClass();
    wxBitmap GetPng(const void* data, size_t length);
protected:
    virtual void OnTick(wxTimerEvent& event);
};
#endif // WELCOMECLASS_H
