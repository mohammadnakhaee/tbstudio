#ifndef STRUCTURECLASS_H
#define STRUCTURECLASS_H
#include "wxcrafter.h"
#include <sstream>
//#include <TBModel.h>
#include "mygrid.h"
#include "GraphClass.h"
#include <wx/filedlg.h>
#include <MyMatrix.h>
#include <string.h>
#include <sec30TextCtrl.h>
#include <Sec30.h>

class StructureClass : public StructureBaseClass
{
public:
    //myGrid* AtomsGrid;
    //TBModel* tbmodel;
    Sec30* sec30;
    GraphClass* graph3d;
    
    StructureClass(wxWindow* parent, Sec30* sec30var);
    virtual ~StructureClass();
    virtual void CreateAtomsGrid(void);
    int ValidateAtoms(void);
    void ValidateForm();
    void ExportToCIF(wxString filepath, wxString filename);
    void ExportToXYZ(wxString filepath, wxString filename);
    wxString GetAtomLable(int kind);
    void ValidateTextCtrl(wxTextCtrl c, double &value);
    
protected:
    virtual void OnChar(wxKeyEvent& event);
    virtual void ctr_a0_OnEnter(wxCommandEvent& event);
    virtual void ctr_a0_OnUpdated(wxCommandEvent& event);
    virtual void ctr_a1_OnUpdated(wxCommandEvent& event);
    virtual void ctr_a2_OnUpdated(wxCommandEvent& event);
    virtual void ctr_a_strain_OnUpdated(wxCommandEvent& event);
    virtual void ctr_b0_OnUpdated(wxCommandEvent& event);
    virtual void ctr_b1_OnUpdated(wxCommandEvent& event);
    virtual void ctr_b2_OnUpdated(wxCommandEvent& event);
    virtual void ctr_b_strain_OnUpdated(wxCommandEvent& event);
    virtual void ctr_c0_OnUpdated(wxCommandEvent& event);
    virtual void ctr_c1_OnUpdated(wxCommandEvent& event);
    virtual void ctr_c2_OnUpdated(wxCommandEvent& event);
    virtual void ctr_c_strain_OnUpdated(wxCommandEvent& event);
    virtual void Btn_Export_XYZ_OnClick(wxCommandEvent& event);

};
#endif // STRUCTURECLASS_H
