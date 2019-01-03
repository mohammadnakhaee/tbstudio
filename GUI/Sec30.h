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
#include <wx/mstream.h>
#include <iostream>
#include <fstream>
#include "mygrid.h"
#include <sec30TextCtrl.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include "checktree.h"
#include <wx/checklst.h>
#include <wx/choice.h>
#include <wx/bmpcbox.h>
#include <wx/clrpicker.h>
#include <wx/tokenzr.h>
#include <sstream>
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

class CheckTreeItemData : public wxTreeItemData
{
public:
    int Index;
};

class Sec30  : public wxWindow
{
public:
    Sec30(wxWindow* parent);
    ~Sec30();
    
    std::list<wxString> vars;
    std::list<wxString> grids;
    std::list<wxString> radios;
    std::list<wxString> checks;
    std::list<wxString> trees;
    std::list<wxString> checklists;
    std::list<wxString> lists;
    std::list<wxString> choices;
    std::list<wxString> combos;
    std::list<wxString> colors;
    
    void AddGroupBox(wxWindow *parent, wxString Caption, wxColour BGColor);
    void AddButton(wxWindow *parent, int ButtonCnt, wxString* Labels, wxObjectEventFunction* Funcs);
    void AddButton(wxWindow *parent, int ButtonCnt, wxString* ButtonNames, wxString* Labels, wxObjectEventFunction* Funcs);
    void AddVarVector(wxWindow *parent, int VecCnt, wxString VariableName, wxString VariableType, wxString VecLabel, int LabelSize, int CtrlSize, bool EnableEvent = true, bool ReadOnly = false);
    void AddVarVector(wxWindow *parent, int VecCnt, wxString VariableName, wxString VariableType);
    void AddGrid(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColNames, wxString* ColTypes, int* ColSizes, int* ColPrecision, int xCtrlSize, int yCtrlSize, bool EnableEvent=true);
    void AddGrid(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColTypes, int* ColPrecision);
    void AddRadioButton(wxWindow *parent, wxString VariableName, wxString Label);
    void AddCheckBox(wxWindow *parent, wxString VariableName, wxString Label);
    wxCheckTree* AddTreeCtrl(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize, bool EnableEvent);
    wxChoice* AddChoiceCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, int LabelSize, int CtrlSize, bool EnableEvent);
    wxComboBox* AddComboCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, int LabelSize, int CtrlSize, bool EnableEvent);
    wxColourPickerCtrl* AddColorCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, wxColour color, int LabelSize, int CtrlSize);
    wxScrolledWindow* AddScrolledPanel(wxWindow *parent, int xCtrlSize, int yCtrlSize, long style = wxSIMPLE_BORDER|wxHSCROLL|wxVSCROLL);
    wxCheckListBox* AddCheckListBox(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize);
    wxListBox* AddListBox(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize);
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
    void SetRadioVar(wxString VariableName, bool Value, bool FireEvent);
    void GetRadioVar(wxString VariableName, bool& Value);
    void SetCheckVar(wxString VariableName, bool Value, bool FireEvent);
    void GetCheckVar(wxString VariableName, bool& Value);
    wxButton* GetButtonObject(wxString VariableName);
    wxCheckTree* GetTreeObject(wxString VariableName);
    wxCheckListBox* GetCheckListObject(wxString VariableName);
    wxListBox* GetListObject(wxString VariableName);
    wxChoice* GetChoiceObject(wxString VariableName);
    wxComboBox* GetComboObject(wxString VariableName);
    wxStaticText* GetComboLabelObject(wxString VariableName);
    wxColourPickerCtrl* GetColorObject(wxString VariableName);
    myGrid* GetGridObject(wxString VariableName);
    sec30TextCtrl* GetTextCtrlObject(wxString VariableName);
    
    void SaveToFile(wxString filepath, wxString filename);
    void LoadFromFile(wxString filepath, wxString filename);
    void SendUpdateEvent(wxString info, int MyID = 1);
    wxString GetAtomLable(int kind);
    int GetAtomLable(wxString Lable);
    wxColor GetAtomColor(int kind);
    wxColor GetBondColor(int kind);
    void GetUnitcellInfo(const wxString& unitcelltextvar, int& l, int& m, int& n);
    void GetBondInfo(const wxString& bondtextvar, int& i, int& n, int& j, int& m, int& bondtype);
    void GetBondSK(int bondtype, Adouble0D &BondSK);
    void GetOrbitalInfo(wxCheckTree* orbsTree, wxString AtomName, int ShellNumber, wxString &Orbs, int &nOrbs, bool &IsShell);
    void GetOrbQuantumNumbers(const wxString& OrbitalName, int& l, int& m);
    wxString CreateFilePath(wxString Path,wxString FileName);
    double norm(double a[3]);
    double norm(double a[3], double b[3]);
    void vk_rtv(double vk[3], double rtv[3][3], double v[3]);
    void GetDirectionalCosines(double x1, double y1, double z1, double x2, double y2, double z2, double &l, double &m, double &n);
    double Hopspd(Adouble0D BondSK, double l, double m, double n, wxString o1, wxString o2);
    double Hopspd(double sss, double sps, double sds, double pps, double ppp, double pds, double pdp, double dds, double ddp, double ddd, double l, double m, double n, wxString o1, wxString o2);
private:
    virtual void sec30TextCtrl_OnUpdated(wxCommandEvent &event);
    virtual void TreeCtrlDeleteItem(wxTreeEvent& event);
    virtual void TreeCtrlLeftClick(wxCommandEvent& event);    
    virtual void Choice_OnChanged(wxCommandEvent& event);
    virtual void ComboBox_OnChanged(wxCommandEvent& event);
    virtual void PickerChangeColor(wxColourPickerEvent& event);
    virtual void MyRadioSelected(wxCommandEvent& event);
    virtual void MyCheckBoxSelected(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif // SEC30_H


