#include "sec30TextCtrl.h"

// this is a definition so can't be in a header
wxDEFINE_EVENT(sec30TextCtrl_Updated, wxCommandEvent);

/******************************************************************************/
BEGIN_EVENT_TABLE(sec30TextCtrl,wxTextCtrl)
    //wxEVT_COMMAND_TEXT_UPDATED(sec30TextCtrl::myUpdated)
    //wxEVT_COMMAND_TEXT_ENTER(sec30TextCtrl::myENTER)
END_EVENT_TABLE()
/******************************************************************************/

sec30TextCtrl::~sec30TextCtrl()
{
}

void sec30TextCtrl::SendDataThroughEvent()
{
    wxCommandEvent* myevent = new wxCommandEvent(sec30TextCtrl_Updated);
    //myevent->m_clientData = 1;
    wxQueueEvent(this,myevent);
}

void sec30TextCtrl::myUpdated(wxCommandEvent &WXUNUSED(event))
{
    SendDataThroughEvent();
}

void sec30TextCtrl::myENTER(wxCommandEvent &WXUNUSED(event))
{
    SendDataThroughEvent();
}

