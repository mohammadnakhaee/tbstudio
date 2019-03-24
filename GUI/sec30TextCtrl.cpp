#include "sec30TextCtrl.h"
/******************************************************************************/
// this is a definition so can't be in a header
/******************************************************************************/
//wxDEFINE_EVENT(Sec30EVT_sec30TextCtrl_Updated, wxCommandEvent);
/******************************************************************************/
//BEGIN_EVENT_TABLE(sec30TextCtrl,myGrid)
    //EVT_GRID_CELL_CHANGED(sec30TextCtrl::OnCellChanged)
    //EVT_KEY_DOWN(sec30TextCtrl::myOnKeyDown)
//END_EVENT_TABLE()
/******************************************************************************/

sec30TextCtrl::~sec30TextCtrl()
{
}


void sec30TextCtrl::SendUpdateEvent()
{
    wxCommandEvent* event = new wxCommandEvent(Sec30EVT_sec30TextCtrl_Updated);
    event->SetEventObject(this);
    event->SetString("");
    wxQueueEvent(this,event);
}

void sec30TextCtrl::OnCellChanged(wxGridEvent &event)
{
    SendUpdateEvent();
}

void sec30TextCtrl::myOnKeyDown(wxKeyEvent &event)
{
    switch (event.GetKeyCode())
    {
        case WXK_TAB:
        case WXK_RETURN:
            SendUpdateEvent();
    }
}

