#ifndef UNITCELLCLASS_H
#define UNITCELLCLASS_H
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
class UnitcellClass : public wxPanel
{
public:
    Sec30* sec30;
    GraphClass* graph3d;

    UnitcellClass(wxWindow* parent, Sec30* sec30var, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL|wxBORDER_STATIC);
    virtual ~UnitcellClass();
    
protected:
    virtual void Btn_Load_OnClick(wxCommandEvent& event);
    virtual void Btn_Save_OnClick(wxCommandEvent& event);
    void ExportToCIF(wxString filepath, wxString filename);
    void ImportFromCIF(wxString filepath, wxString filename);
    void GetValueFromLine(wxString str, double &val);
    void GetValueFromLine(wxString str, int &val);
};
#endif // UNITCELLCLASS_H


