#ifndef MYFIGURECLASS_H
#define MYFIGURECLASS_H

#include <math.h>
#include <exception>
#include "Sec30.h"
#include <wx/clipbrd.h> 
#include <wx/menu.h>
#include <wx/textfile.h>
#include <mgl2/mgl.h>
#include <mgl2/glut.h>

class MyFigure2d : public wxPanel
{
public:
    //int canvasRefreshCnt=0;
    Sec30* sec30;
    bool isSelectMode = false;
    bool isMoveMode = false;
    bool isRotationMode = true;
    bool isZoomMode = false;
    int nSelection = 0;
    
    int ObjectID = -1;
    
    float Zoom=0.25;
    float XMove=0.0;
    float YMove=0.0;
    
    float XCam=0.0;
    float YCam=0.0;
    float ZoomCam=0.0;
    
    bool ShowSelectionFrame = false;
    float SelectionFramX1 = 0.0f;
    float SelectionFramY1 = 0.0f;
    float SelectionFramX2 = 0.0f;
    float SelectionFramY2 = 0.0f;
    
    bool isPaintCursur = false;
    
    int NumberOfDoubleArrays=0;
    int* nDoubleArray;
    double** DoubleArray;

    int NumberOfIntArrays=0;
    int* nIntArray;
    int** IntArray;
    
	MyFigure2d(wxWindow *parent, Sec30* sec30Var, int MyID);
    
private:
    float TheLastXAngle = 0;
    float TheLastYAngle = 0;
    float TheLastZAngle = 0;
    
    int mouseX0 = 0;
    int mouseY0 = 0;
    int ClientMouseX0 = 0;
    int ClientMouseY0 = 0;
    int mouseX = 0;
    int mouseY = 0;
    int ClientMouseX = 0;
    int ClientMouseY = 0;
    bool isMouseLeftDown = false;
    bool isMouseRightDown = false;
    bool isMouseMiddleDown = false;
    double** DoubleArray0;
    double** DoubleArray1;
    double Coordinate0[3][3];
    double Coordinate1[3][3];
    
    wxTimer m_spinTimer;
    bool m_useStereo;
    bool m_stereoWarningAlreadyDisplayed;

    double OldxMin, OldxMax, OldyMin, OldyMax;
    
    bool PaintMode = false;
    
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnMouseWheel(wxMouseEvent& event);
    void OnMouseLeftDown(wxMouseEvent& event);
    void OnMouseLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseRightDown(wxMouseEvent& event);
    void OnMouseRightUp(wxMouseEvent& event);
    void OnMouseMiddleDown(wxMouseEvent& event);
    void OnMouseMiddleUp(wxMouseEvent& event);
    void OnSaveRasterImage(wxCommandEvent &WXUNUSED(event));
    void SaveImageFromData(wxImage image, wxString filepath, wxString OutputFileType);
    int PlotBand(mglGraph *gr, int w, int h, Sec30* sec30, int MyID);
	int sample(mglGraph *gr,double w, double h, int ObjectID);
    void SetWeight(float x, float y, float w, float h, float coef);
    void GetDirection(int i0, int j0, int i, int j, float& x, float& y, float& Theta);
	void DoMove2d(float l, float m);
	
    wxDECLARE_EVENT_TABLE();
    
private:
    int currentRenderDimension = 0;
};

#endif