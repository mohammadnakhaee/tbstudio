#ifndef SKCLASS_H
#define SKCLASS_H
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
class SKClass : public wxPanel
{
public:
    Sec30* sec30;
    GraphClass* graph3d;
    GraphClass* graph2d0;
    GraphClass* graph2d;
    
    SKClass(wxWindow* parent, Sec30* sec30var, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL|wxBORDER_STATIC);
    virtual ~SKClass();

protected:
    void Btn_Update_OnClick(wxCommandEvent& event);
    void Btn_LastValues_OnClick(wxCommandEvent& event);
    void Btn_ExportInit_OnClick(wxCommandEvent& event);
	void Btn_ExportFinal_OnClick(wxCommandEvent& event);
    void Btn_MakeACopy_OnClick(wxCommandEvent& event);
	void ExportSKToTXT(wxString filepath, wxString BaseName, int InitOrFinalSK);
    DECLARE_EVENT_TABLE()
};
#endif // BONDSCLASS_H


