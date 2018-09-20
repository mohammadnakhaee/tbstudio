#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include <wx/aui/aui.h>
#include "GraphClass.h"
#include "GridClass.h"
#include "StructureClass.h"

class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
    
    GraphClass* graph3d;
    GraphClass* graph2d0;
    GraphClass* graph2d;
    StructureClass* structurePanel;
    //TBModel* tbmodel;
    Sec30* sec30;
    
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
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
    virtual void Init_graph3d();
    virtual void Init_graph2d0();
    virtual void Init_graph2d();
    virtual void LoadStructurePanel();
    virtual void UpdateGraph3d();
    virtual void ValidateStructure();
    virtual int ValidateAtoms();
    
private:
    wxTextCtrl* logfile;
    wxAuiManager aui_mgr;
    wxAuiNotebook* aui_ntb;
    
    virtual void sec30_OnUpdated(wxCommandEvent& event);
};
#endif // MAINFRAME_H
