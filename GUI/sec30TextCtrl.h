/******************************************************************************/
#ifndef SEC30TEXTCTRL_H
#define SEC30TEXTCTRL_H
/******************************************************************************/
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/event.h>
#include <mygrid.h>
/******************************************************************************/
#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIP
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif
/******************************************************************************/
// this is typically in a header: it just declares MY_EVENT event type
/******************************************************************************/
//wxDECLARE_EVENT(Sec30EVT_sec30TextCtrl_Updated, wxCommandEvent);
/******************************************************************************/

class  sec30TextCtrl : public myGrid
{
public:
	sec30TextCtrl(wxWindow *parent, wxWindowID id, wxString Type, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, const bool ReadOnly=false)
    :myGrid(parent, id, pos, size,0){
        //SetMinSize(size);
        //EnableGridLines(false);
        EnableEditing(true);
        CreateGrid( 1, 1);
        SetColSize(0, size.x-1);// in pixels
        SetColLabelSize(1);
        ShowScrollbars(wxSHOW_SB_NEVER,wxSHOW_SB_NEVER);
        if (Type=="wxString")
        {}
        else if (Type=="int")
            SetColFormatNumber(0);
        else if (Type=="double")
            SetColFormatFloat(0);
        else if (Type=="bool")
            SetColFormatBool(0);
        
        SetCellAlignment (0,0, wxALIGN_LEFT,wxALIGN_BOTTOM);
        //SetDefaultCellAlignment(wxALIGN_LEFT,wxALIGN_CENTRE);
        SetReadOnly(0,0,ReadOnly);
        
    };
    
    ~sec30TextCtrl();


   
private:
    //virtual void SendUpdateEvent();
    // virtual void OnCellChanged(wxGridEvent &event); You should not use This Function Name. It seems it is connected by default without DECLARE_EVENT_TABLE()
    //virtual void myOnKeyDown(wxKeyEvent &event);
       //DECLARE_EVENT_TABLE()
};
/******************************************************************************/
#endif
