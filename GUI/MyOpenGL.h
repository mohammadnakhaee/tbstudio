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

// the rendering context used by all GL canvases
class MyGLContext : public wxGLContext
{
public:
    MyGLContext(wxGLCanvas *canvas, int DimVar);
    int Dim;
    void Polygons2D();
    void Polygons3D();
    void background();
    void Draw2D();
    void Draw3D(float xangle, float yangle);
private:
    // textures for the cube faces
    GLuint m_textures[1];
};

class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(wxWindow *parent, int DimVar, int *attribList = NULL);
    int Dim;
    
private:
    void OnPaint(wxPaintEvent& event);
    void Spin(float xSpin, float ySpin);
    void Animate(void);
    void OnKeyDown(wxKeyEvent& event);
    void OnSpinTimer(wxTimerEvent& WXUNUSED(event));
    
    // angles of rotation around x- and y- axis
    float m_xangle,
          m_yangle;

    wxTimer m_spinTimer;
    bool m_useStereo,
         m_stereoWarningAlreadyDisplayed;

    wxDECLARE_EVENT_TABLE();
    

private:
    int currentRenderDimension = 0;
};

enum
{
    NEW_STEREO_WINDOW = wxID_HIGHEST + 1
};

#endif // _WX_CUBE_H_