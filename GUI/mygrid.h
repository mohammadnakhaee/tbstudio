//mygrid.h
/******************************************************************************/
#ifndef MYGRID_H
#define MYGRID_H 
/******************************************************************************/
#include <wx/grid.h>
#include <wx/clipbrd.h> 
#include <wx/menu.h>
#include <wx/textfile.h>
/******************************************************************************/
// this is typically in a header: it just declares MY_EVENT event type
/******************************************************************************/
wxDECLARE_EVENT(Sec30EVT_Grid_Updated, wxCommandEvent);
/******************************************************************************/

class  myGrid : public wxGrid
{
public:
     myGrid(wxWindow *parent, wxWindowID id = wxID_ANY,
          const wxPoint& pos = wxDefaultPosition,
          const wxSize& size = wxDefaultSize,
          long style = wxSUNKEN_BORDER|wxCLIP_CHILDREN|wxWANTS_CHARS)
    :wxGrid(parent,id,pos,size,style){};

        
private:
        void SendUpdateEvent();
        void UpdateGrid();
        void NavigateToNextInput(bool GoDown);
        virtual void Copy(bool OnlyDelete, bool cut);
        virtual void Paste();
        virtual void StartTyping(wxString keyString);
        virtual void OnCopy(wxCommandEvent &WXUNUSED(event));
        virtual void OnCut(wxCommandEvent &WXUNUSED(event));
        virtual void OnDelete(wxCommandEvent &WXUNUSED(event));
        virtual void OnPaste(wxCommandEvent &WXUNUSED(event));
        virtual void OnRightMouseDown(wxGridEvent &event);
        virtual void OnCellChanged(wxGridEvent &event);
        virtual void myOnKeyDown(wxKeyEvent &event);
        DECLARE_EVENT_TABLE()
};
/******************************************************************************/
#endif