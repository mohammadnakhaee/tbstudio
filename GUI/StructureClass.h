#ifndef STRUCTURECLASS_H
#define STRUCTURECLASS_H
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
class StructureClass : public wxPanel
{
public:
    Sec30* sec30;
    GraphClass* graph3d;

    StructureClass(wxWindow* parent, Sec30* sec30var, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL|wxBORDER_STATIC);
    virtual ~StructureClass();
    
protected:
    virtual void Btn_Export_XYZ_OnClick(wxCommandEvent& event);
    virtual void Btn_Import_XYZ_OnClick(wxCommandEvent& event);
};
#endif // STRUCTURECLASS_H

