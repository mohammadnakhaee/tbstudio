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
wxDECLARE_EVENT(MyGridPasteEvent, wxCommandEvent);

class  myGrid : public wxGrid
{
public:
       myGrid(wxWindow *parent, wxWindowID id = wxID_ANY,
          const wxPoint& pos = wxDefaultPosition,
          const wxSize& size = wxDefaultSize)
      : wxGrid(parent,id,pos,size,wxFULL_REPAINT_ON_RESIZE|wxHSCROLL|wxVSCROLL) {};
      
        virtual void Copy(bool cut);
        virtual void Paste();
        virtual void Refresh(wxKeyCode KeyCode, bool isShift);
        virtual void OnCopy(wxCommandEvent &WXUNUSED(event));
        virtual void OnCut(wxCommandEvent &WXUNUSED(event));
        virtual void OnPaste(wxCommandEvent &WXUNUSED(event));
        virtual void OnRightMouseDown(wxGridEvent &event);
        virtual void OnCellChanged(wxGridEvent &event);
        virtual void myOnKeyDown(wxKeyEvent &event);

private:
       DECLARE_EVENT_TABLE()
};
/******************************************************************************/
#endif