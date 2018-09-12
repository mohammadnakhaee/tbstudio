#ifndef SEC30_H
#define SEC30_H

#include <list>
#include <vector>
#include <wx/window.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <sstream>
#include <wx/panel.h>
#include <iostream>
#include <fstream>
#include "mygrid.h"
#include <wx/spinctrl.h>

#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIPclTabCtrl
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif

class Sec30  : public wxWindow
{
public:
    Sec30();
    ~Sec30();
    
    std::list<wxString> double_vars;
    std::list<double> double_vals;
    
    std::list<wxString> int_vars;
    std::list<int> int_vals;
    
    std::list<wxString> bool_vars;
    std::list<bool> bool_vals;
    
    std::list<wxString> float_vars;
    std::list<float> float_vals;
    
    std::list<wxString> char_vars;
    std::list<char> char_vals;
    
    std::list<wxString> wxString_vars;
    std::list<wxString> wxString_vals;
    
    std::list<wxString> double2dArray_vars;
    std::list<   std::vector<std::vector<wxString>>   > double2dArray_vals;
    
    void AddGroupBox(wxWindow *parent, wxString Caption, wxColour BGColor);
    void AddDoubleVec(wxWindow *parent, int VecCnt, wxString VariableName, wxString VecLabel, int LabelSize, int CtrlSize);
    void AddDouble2dArray(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColNames, wxString* ColTypes, int* ColSizes, int* ColPrecision, int xCtrlSize, int yCtrlSize);
    void SetVar(wxWindow *parent, wxString VariableName, double Value);
    void SetVar(wxWindow *parent, wxString VariableName, int Value);
    void SetVar(wxWindow *parent, wxString VariableName, wxString Value);
    void SetVar(wxString FileName);
    void SaveToFile(wxString filepath, wxString filename);
    void LoadFromFile(wxString filepath, wxString filename);
    
private:
    bool SetData(wxString Type, wxString VariableName, wxString Value);
    void GetData(wxString VariableName, double &Value);
    virtual void TextCtrl_OnUpdated(wxCommandEvent &event);
    virtual void TextCtrl_OnChar(wxKeyEvent& event);
};

#endif // SEC30_H
