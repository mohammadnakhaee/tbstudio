#ifndef MAINFRAME_H
#define MAINFRAME_H

/**********************************************************************************/
#include "wxcrafter.h"
#include <wx/aui/aui.h>
#include <math.h>
#include "GraphClass.h"
#include "GridClass.h"
#include "UnitcellClass.h"
#include "StructureClass.h"
#include "OrbitalsClass.h"
#include "BondsClass.h"
#include "SetupClass.h"
#include "SKClass.h"
#include "ColorsClass.h"
#include "unistd.h"
#include "Embeded.h"
#include <wx/ribbon/bar.h>
#include <wx/ribbon/art.h>
#include <wx/ribbon/page.h>
#include <wx/ribbon/panel.h>
#include <wx/ribbon/buttonbar.h>
#include <thread>
#include <Regression.h>
#include "UpdateClass.h"
//#include <memory>
/**********************************************************************************/



class MainFrame : public MainFrameBaseClass
{
public:
    wxString MySerialNumber = _("");
    wxString SoftwareName = _("TBStudio");
    wxString FreeSoftwareLimitations = _("fitting a TB model including d-orbitals");
    int Ver_MAJOR = 1;
    int Ver_MINOR = 4;
    int Ver_RELEASE = 0;
    
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
    
    //int* SelectedAtoms;
    GraphClass* graph3d;
    GraphClass* graph2d0;
    GraphClass* graph2d;
    UnitcellClass* unitcellPanel;
    StructureClass* structurePanel;
    OrbitalsClass* orbitalsPanel;
    BondsClass* bondsPanel;
    SetupClass* setupPanel;
    SKClass* skPanel;
    ColorsClass* ColorsForm;
    
    bool IsLicensed = false;
    wxString LicenseOwner = _("");
    
    Sec30* sec30;
    //std::shared_ptr<Sec30> sec30;
    double* p;
    double* t;
    double* y_dat;
    double* weight;
    double* dp;
    double* cnst;
    lapack_complex_double* UpperSymMatrixHf;
    
    bool is_p = false;
    bool is_t = false;
    bool is_y_dat = false;
    bool is_weight = false;
    bool is_dp = false;
    bool is_cnst = false;
    bool is_UpperSymMatrixHf = false;
    
    Regression* regression;
    //std::thread* FittingThread;
    bool isFittingThreadBusy = false;
    
    wxRibbonButtonBar* RButtonMouse;
    
    
    void ShowAbout();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
    bool CheckLicense(wxString &UserName);
    virtual void BtnMove_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnRotate_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnScale_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnSelect_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnStructureStyle_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnX_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnY_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnZ_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnA_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnB_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnC_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnUp_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnDown_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnLeft_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnRight_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnStart_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnOnestep_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnPause_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnStop_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnCppCode_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnCCode_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnFCode_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnMathematicaCode_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnMatlabCode_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnPythonCode_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnAbout_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnTutorials_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnWebsite_OnClick(wxRibbonButtonBarEvent& event);
    virtual void OnchoisSelected(wxCommandEvent& event);
    virtual void BtnOpen_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnSave_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnGrid_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnMain_OnClick(wxRibbonButtonBarEvent& event);
    virtual void BtnTerminal_OnClick(wxRibbonButtonBarEvent& event);
    virtual void mgl_test(wxRibbonButtonBarEvent& event);
    virtual void B2D(wxRibbonButtonBarEvent& event);
    virtual void B3D(wxRibbonButtonBarEvent& event);
    virtual void bb1(wxKeyEvent& event);
    virtual void bb2(wxKeyEvent& event);
    virtual void b3(wxRibbonButtonBarEvent& event);
    virtual void b4(wxRibbonButtonBarEvent& event);
    virtual void d1(wxRibbonButtonBarEvent& event);
    virtual void d2(wxRibbonButtonBarEvent& event);
    virtual void b1(wxRibbonButtonBarEvent& event);
    virtual void b2(wxRibbonButtonBarEvent& event);
    virtual void Btn3D_OnClick(wxRibbonButtonBarEvent& event);
    virtual void Btn2D_OnClick(wxRibbonButtonBarEvent& event);
    virtual void RibbonAnalyzeGraph2D_OnClick(wxRibbonButtonBarEvent& event);
    virtual void RibbonAnalyzeGraph3D_OnClick(wxRibbonButtonBarEvent& event);
    virtual void MathGL_test_OnClick(wxCommandEvent& event);
    virtual void Test3D_OnClick(wxCommandEvent& event);
    virtual void test2D_OnClick(wxCommandEvent& event);
    virtual void test_OnClick(wxCommandEvent& event);
    virtual void MainFrameBaseClass_Move(wxMoveEvent& event);
    virtual void MainFrameBaseClass_Resize(wxSizeEvent& event);
    virtual void m_glCanvas17_OnPaint(wxPaintEvent& event);
    virtual void BtnTest_OnClick(wxCommandEvent& event);
    virtual void GetHamiltonianMap(wxCheckTree* orbs, Astring0D &HamiltonianMap, Astring0D &HamiltonianShellMap, Aint1D &HamiltonianDimMap);
    virtual void AddShellAndOrbitalInfo(wxCheckTree* orbsTree, wxString AtomName, Astring0D &HamiltonianMap, Astring0D &HamiltonianShellMap, Aint0D &HamiltonianDimMapItem, int &LastIndex);
    virtual void ReadSK();
    virtual void Init_graph3d();
    virtual void Init_graph2d0();
    virtual void Init_graph2d();
    virtual void ClearGraph3D();
    virtual void ShowGraph3D();
    virtual void UpdateGraph3D();
    virtual void UpdateGraph2D0();
    virtual void UpdateGraph2D();
    virtual void UpdateGraph2Ds();
    /****************************************/
    virtual void LoadUnitcellPanel();
    virtual void EvaluateUnitcellPanel();
    virtual bool ValidateUnitCellPanel();
    /****************************************/
    virtual void LoadStructurePanel();
    virtual void EvaluateStructurePanel();
    virtual bool ValidateStructurePanel();
    /****************************************/
    virtual void LoadOrbitalsPanel();
    virtual void EvaluateOrbitalsPanel(int redraw);
    virtual bool ValidateOrbitalsPanel();
    /****************************************/
    virtual void LoadBondsPanel();
    virtual void EvaluateBondsPanel(int redraw);
    virtual bool ValidateBondsPanel();
    virtual void FillBondsPanel();
    /****************************************/
    virtual void LoadSetupPanel();
    virtual void EvaluateSetupPanel(int SetWeight);
    virtual bool ValidateSetupPanel();
    virtual void FillSetupPanel();
    /****************************************/
    virtual void LoadSKPanel();
    virtual void EvaluateSKPanel(int isUpdateSKList);
    virtual bool ValidateSKPanel();
    virtual bool ValidateSKParametersList();
    /****************************************/
    virtual void LoadColorsForm();
    virtual void EvaluateColorsPanel();
    virtual bool ValidateColorsPanel();
    /****************************************/
    int GetBonds(int* bonds);
    void ReArrangeSKList();
    bool IsBondContainsParameter(wxString Orbs1, wxString Orbs2, wxString sk);
    void TestEig();
    void TestZEig();
    void InitializeSec30Arrays();
    void UpdateTBBand_if();
    void StartRegression(bool isOneStep);
    int ReplaceDFTBand(int iband, int ik);
    double ShiftBand(int iband, int ik);
    double GetFitParameter(int ip, int icol);
    void ExportMatrices(wxString filepath, wxString BaseName, int MyID_Initial0Final1);
    void GenerateCode(wxString filepath, wxString BaseName, wxString Type, int MyID_Initial0Final1, bool OnlyDatFiles);
    void GenerateCppCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1);
    void GenerateCCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1);
    void GenerateFCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1);
    void GenerateMathematicaCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1);
    void GenerateMatlabCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1);
    void GeneratePythonCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1);
    
private:
    wxTextCtrl* logfile;
    wxAuiManager aui_mgr;
    wxAuiNotebook* aui_ntb;
    std::list<int> EssentialListi;
    std::list<int> EssentialListj;
    std::list<int> EssentialListk;
    bool isItNew(int i,int j,int k);
    virtual void sec30_OnUpdated(wxCommandEvent& event);
    virtual void myOpenGL_EVT_SelectionChanged(wxCommandEvent& event);
    virtual void regressionEVT_OnNewData(wxCommandEvent& event);
    virtual void regressionEVT_OnFinished(wxCommandEvent& event);
    virtual void regressionEVT_OnStarted(wxCommandEvent& event);
    virtual void LoadIcons();
    virtual wxBitmap GetPng(const void* data, size_t length);
};
#endif // MAINFRAME_H
