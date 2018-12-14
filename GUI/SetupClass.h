#ifndef SETUPCLASS_H
#define SETUPCLASS_H
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
class SetupClass : public wxPanel
{
public:
    Sec30* sec30;
    GraphClass* graph3d;
    
    SetupClass(wxWindow* parent, Sec30* sec30var, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL|wxBORDER_STATIC);
    virtual ~SetupClass();

protected:
    void ReloadBand();
    void IsRangeOK(int nBandMax, bool &IsMinOK, bool &IsMaxOK);
    void Btn_OpenFile_OnClick(wxCommandEvent& event);
    void Btn_Reload_OnClick(wxCommandEvent& event);
    void Btn_Select_OnClick(wxCommandEvent& event);
    void LoadOpenMXBand(wxString file, bool &isBandLoaded, int &maxneig, int &mspin, double &ChemP, int &nKp, Adouble1D &KPoints, Adouble1D &EigVal, Adouble0D &dkLabel, Astring0D &kLabel);
    void LoadOpenMXUnfoldedBand(wxString file);
};
#endif // BONDSCLASS_H
