#ifndef SEC30_H
#define SEC30_H

/******************************************************************************/
#include <list>
#include <vector>
#include <wx/window.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <sstream>
#include <wx/panel.h>
#include <wx/button.h>
#include <iostream>
#include <fstream>
#include "mygrid.h"
#include <sec30TextCtrl.h>
/******************************************************************************/

/******************************************************************************/
#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIPclTabCtrl
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif
/******************************************************************************/

// It just declares MY_EVENT event type
/******************************************************************************/
wxDECLARE_EVENT(Sec30EVT_OnUpdated, wxCommandEvent);
/******************************************************************************/

class Sec30  : public wxWindow
{
public:
    Sec30(wxWindow* parent);
    ~Sec30();

    std::list<wxString> vars;
    
    std::list<wxString> grids;
    
    void AddGroupBox(wxWindow *parent, wxString Caption, wxColour BGColor);
    void AddButton(wxWindow *parent, int ButtonCnt, wxString* Labels, wxObjectEventFunction* Funcs);
    void AddButton(wxWindow *parent, int ButtonCnt, wxString* ButtonNames, wxString* Labels, wxObjectEventFunction* Funcs);
    void AddVarVector(wxWindow *parent, int VecCnt, wxString VariableName, wxString VariableType, wxString VecLabel, int LabelSize, int CtrlSize);
    void AddVarVector(wxWindow *parent, int VecCnt, wxString VariableName, wxString VariableType);
    void AddGrid(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColNames, wxString* ColTypes, int* ColSizes, int* ColPrecision, int xCtrlSize, int yCtrlSize);
    void AddGrid(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColTypes, int* ColPrecision);
    void GetDim(wxString VariableName, int& nRow, int& nCol);
    void SetVar(wxString VariableName, double Value, bool FireEvent);
    void SetVar(wxString VariableName, int Value, bool FireEvent);
    void SetVar(wxString VariableName, bool Value, bool FireEvent);
    void SetVar(wxString VariableName, wxString Value, bool FireEvent);
    bool GetVar(wxString VariableName, double& Value);
    bool GetVar(wxString VariableName, int& Value);
    bool GetVar(wxString VariableName, bool& Value);
    bool GetVar(wxString VariableName, wxString& Value);
    void SetVar(wxString VariableName, int iRow, int iCol, double Value, bool FireEvent);
    void SetVar(wxString VariableName, int iRow, int iCol, int Value, bool FireEvent);
    void SetVar(wxString VariableName, int iRow, int iCol, bool Value, bool FireEvent);
    void SetVar(wxString VariableName, int iRow, int iCol, wxString Value, bool FireEvent);
    bool GetVar(wxString VariableName, int iRow, int iCol, double& Value);
    bool GetVar(wxString VariableName, int iRow, int iCol, int& Value);
    bool GetVar(wxString VariableName, int iRow, int iCol, bool& Value);
    bool GetVar(wxString VariableName, int iRow, int iCol, wxString& Value);
    
    
    void SaveToFile(wxString filepath, wxString filename);
    void LoadFromFile(wxString filepath, wxString filename);
private:
    void SendUpdateEvent(wxString info);
    virtual void sec30TextCtrl_OnUpdated(wxCommandEvent &event);
    DECLARE_EVENT_TABLE()
};

#endif // SEC30_H
