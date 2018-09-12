/******************************************************************************/
#ifndef SEC30TEXTCTRL_H
#define SEC30TEXTCTRL_H
/******************************************************************************/
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/event.h>

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
wxDECLARE_EVENT(sec30TextCtrl_Updated, wxCommandEvent);

class  sec30TextCtrl : public wxTextCtrl
{
public:
	sec30TextCtrl(wxWindow *parent, wxWindowID id, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr)
    :wxTextCtrl(parent, id, value, pos, size, style, validator, name) {};

    ~sec30TextCtrl();
    virtual void SendDataThroughEvent();
    virtual void myUpdated(wxCommandEvent &WXUNUSED(event));
    virtual void myENTER(wxCommandEvent &WXUNUSED(event));

   
private:
       DECLARE_EVENT_TABLE()
};
/******************************************************************************/
#endif