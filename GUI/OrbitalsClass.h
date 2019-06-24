#ifndef ORBITALSCLASS_H
#define ORBITALSCLASS_H
/**************************************************************************************/
#include "wxcrafter.h"
#include <sstream>
#include "GraphClass.h"
#include <wx/filedlg.h>
#include <MyMatrix.h>
#include <string.h>
#include <exception>
#include <wx/msgdlg.h>
#include <Sec30.h>
/**************************************************************************************/
class OrbitalsClass : public wxPanel
{
public:
    Sec30* sec30;
    GraphClass* graph3d;

    OrbitalsClass(wxWindow* parent, Sec30* sec30var, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxBORDER_STATIC);
    virtual ~OrbitalsClass();
    
protected:
    void Btn_AddAtom_OnClick(wxCommandEvent& event);
    void Btn_RemoveAtom_OnClick(wxCommandEvent& event);
    void Btn_AddShell_OnClick(wxCommandEvent& event);
    void Btn_RemoveShell_OnClick(wxCommandEvent& event);
};

#endif // ORBITALSCLASS_H
