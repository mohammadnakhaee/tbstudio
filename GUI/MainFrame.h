#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include <wx/aui/aui.h>

class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
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
    virtual void ShowStartPage();
    virtual void NewTerminal();
    
private:
    wxPanel* CenterPanel;
    wxAuiManager aui_mgr;
    wxAuiNotebook* aui_ntb;
};
#endif // MAINFRAME_H
