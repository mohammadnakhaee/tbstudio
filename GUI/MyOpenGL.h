/////////////////////////////////////////////////////////////////////////////
// Name:        cube.h
// Purpose:     wxGLCanvas demo program
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_CUBE_H_
#define _WX_CUBE_H_

#include "wx/glcanvas.h"
#include <wx/timer.h>
#include <mgl2/mgl.h>
#include <mgl2/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <math.h>
#include <exception>

// the rendering context used by all GL canvases
class MyGLContext : public wxGLContext
{
public:
    MyGLContext(wxGLCanvas *canvas, int DimVar);
    int Dim;
    void Polygons2D();
    void Polygons3D();
    void Draw_Atom(float r, float x, float y, float z, GLubyte R, GLubyte G, GLubyte B, int Slices, int Stacks);
    void Draw_Bond(float x0, float y0, float z0, float x1, float y1, float z1, float radius, GLubyte R, GLubyte G, GLubyte B, int Slices, int Stacks);
    void Draw_Lattice(int nColDArray, int* nDArray, double** DArray, int nColIArray, int* nIArray, int** IArray);
    void background();
    void Draw2D();
    void Draw3D(int nColDArray, int* nDArray, double** DArray, int nColIArray, int* nIArray, int** IArray, float xMove, float yMove, float XCam, float YCam, float zoom, float zoomCam, float w, float h);
private:
    // textures for the cube faces
    GLuint m_textures[1];
    GLUquadric *quad;
};

class MyGLCanvas : public wxGLCanvas
{
public:
    int Dim;
    float Zoom=0.5;
    float XMove=0.0;
    float YMove=0.0;
    
    float XCam=0.0;
    float YCam=0.0;
    float ZoomCam=0.0;
    
    int NumberOfDoubleArrays=0;
    int* nDoubleArray;
    double** DoubleArray;

    int NumberOfIntArrays=0;
    int* nIntArray;
    int** IntArray;
    
    MyGLCanvas(wxWindow *parent, int DimVar, int *attribList = NULL);
    void CreateDoubleArray(int NumberOfArraysVar, int* nArray);
    void DiscardDoubleArrays();
    void CreateIntArray(int NumberOfArraysVar, int* nArray);
    void DiscardIntArrays();
    void LoadToCanvas();
    void Reload();
    
private:
    float TheLastXAngle = 0;
    float TheLastYAngle = 0;
    float TheLastZAngle = 0;
    
    int mouseX0 = 0;
    int mouseY0 = 0;
    int mouseX = 0;
    int mouseY = 0;
    bool isMouseLeftDown = false;
    bool isMouseRightDown = false;
    bool isMouseMiddleDown = false;
    bool isMoveMode = false;
    bool isRotationMode = true;
    bool isZoomMode = false;
    double** DoubleArray0;
    double** DoubleArray1;
            
    wxTimer m_spinTimer;
    bool m_useStereo;
    bool m_stereoWarningAlreadyDisplayed;


    void OnPaint(wxPaintEvent& event);
    void Spin(float xSpin, float ySpin, float zSpin);
    void Animate(void);
    void OnKeyDown(wxKeyEvent& event);
    void OnSpinTimer(wxTimerEvent& WXUNUSED(event));
    void OnMouseWheel(wxMouseEvent& event);
    void OnMouseLeftDown(wxMouseEvent& event);
    void OnMouseLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseRightDown(wxMouseEvent& event);
    void OnMouseRightUp(wxMouseEvent& event);
    void OnMouseMiddleDown(wxMouseEvent& event);
    void OnMouseMiddleUp(wxMouseEvent& event);
    void OnSaveRasterImage(wxCommandEvent &WXUNUSED(event));
    
    void CreateDoubleArray1();
    void DiscardDoubleArrays1();
    void DoMove(float l, float m);
    void DoRotate(float l, float m, float Theta);
    void DoZoom(float l);
    void GetDirection(int i0, int j0, int i, int j, float& x, float& y, float& z);
    
    wxDECLARE_EVENT_TABLE();
    
private:
    int currentRenderDimension = 0;
};

enum
{
    NEW_STEREO_WINDOW = wxID_HIGHEST + 1
};

#endif // _WX_CUBE_H_