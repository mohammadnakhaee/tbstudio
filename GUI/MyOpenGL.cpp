///////////////////////////////////////////////////////////////////////////////
// Name:        cube.cpp
// Purpose:     wxGLCanvas demo program
// Author:      Julian Smart
// Modified by: Vadim Zeitlin to use new wxGLCanvas API (2007-04-09)
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include "MyOpenGL.h"
#include "main.h"
DECLARE_APP(MainApp)

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../../sample.xpm"
#endif

#include <mgl2/mgl.h>
#include <mgl2/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glut.h>

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// control ids
enum
{
    SpinTimer = wxID_HIGHEST + 1
};

// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------



static void CheckGLError()
{
    GLenum errLast = GL_NO_ERROR;

    for ( ;; )
    {
        GLenum err = glGetError();
        if ( err == GL_NO_ERROR )
            return;

        // normally the error is reset by the call to glGetError() but if
        // glGetError() itself returns an error, we risk looping forever here
        // so check that we get a different error than the last time
        if ( err == errLast )
        {
            wxLogError("OpenGL error state couldn't be reset.");
            return;
        }

        errLast = err;

        wxLogError("OpenGL error %d", err);
    }
}

void mgls_prepare2d(mglData *a, mglData *b=0, mglData *v=0)
{
  register long i,j,n=50,m=40,i0;
  if(a) a->Create(n,m);   if(b) b->Create(n,m);
  if(v) { v->Create(9); v->Fill(-1,1);  }
  mreal x,y;
  for(i=0;i<n;i++)  for(j=0;j<m;j++)
  {
    x = i/(n-1.); y = j/(m-1.); i0 = i+n*j;
    if(a) a->a[i0] = 0.6*sin(2*M_PI*x)*sin(3*M_PI*y)+0.4*cos(3*M_PI*x*y);
    if(b) b->a[i0] = 0.6*cos(2*M_PI*x)*cos(3*M_PI*y)+0.4*cos(3*M_PI*x*y);
  }
}

void mgls_prepare3d(mglData *a, mglData *b=0)
{
  register long i,j,k,n=61,m=50,l=40,i0;
  if(a) a->Create(n,m,l);   if(b) b->Create(n,m,l);
  mreal x,y,z;
  for(i=0;i<n;i++)  for(j=0;j<m;j++)  for(k=0;k<l;k++)
  {
    x=2*i/(n-1.)-1; y=2*j/(m-1.)-1; z=2*k/(l-1.)-1; i0 = i+n*(j+m*k);
    if(a) a->a[i0] = -2*(x*x + y*y + z*z*z*z - z*z - 0.1);
    if(b) b->a[i0] = 1-2*tanh((x+y)*(x+y));
  }
}

int sample7(mglGraph *gr, double w, double h)
{
  mglData c;  mgls_prepare3d(&c);
  gr->Title("Dens[XYZ] sample");  gr->Rotate(50,60);
  gr->Box();  gr->DensX(c.Sum("x"),0,-1);
  gr->DensY(c.Sum("y"),0,1);  gr->DensZ(c.Sum("z"),0,-1);
  return 0;
}

int sample5(mglGraph *gr, double w, double h)
{
  mglData a,a1(30,40,3);  mgls_prepare2d(&a);
  gr->Fill(a1,"0.6*sin(2*pi*x+pi*(z+1)/2)*sin(3*pi*y+pi*z) + 0.4*cos(3*pi*(x*y)+pi*(z+1)^2/2)");
  gr->SubPlot(2,2,0,""); gr->Title("Dens plot (default)");
  gr->Box();  gr->Dens(a);

  gr->SubPlot(2,2,1); gr->Title("3d variant");
  gr->Rotate(50,60);  gr->Box();  gr->Dens(a);

  gr->SubPlot(2,2,2,"");  gr->Title("'\\#' style; meshnum 10");
  gr->Box();  gr->Dens(a,"#","meshnum 10");

  gr->SubPlot(2,2,3); gr->Title("several slices");
  gr->Rotate(50,60);    gr->Box();  gr->Dens(a1);
  return 0;
}

int sample6(mglGraph *gr, double w, double h)
{
gr->SubPlot(2,2,0); gr->Box();
gr->Puts(mglPoint(-1,1.1),"Just box",":L");
gr->InPlot(0.2,0.5,0.7,1,false); gr->Box();
gr->Puts(mglPoint(0,1.2),"InPlot example");
gr->SubPlot(2,2,1); gr->Title("Rotate only");
gr->Rotate(50,60); gr->Box();
gr->SubPlot(2,2,2); gr->Title("Rotate and Aspect");
gr->Rotate(50,60); gr->Aspect(1,1,2); gr->Box();
gr->SubPlot(2,2,3); gr->Title("Aspect in other direction");
gr->Rotate(50,60); gr->Aspect(1,2,2); gr->Box();
return 0;
}

int frameCnt=0;

int samplemulti(mglGraph *gr,double w, double h)
{
  gr->SubPlot(2,2,0); gr->Title("Axis origin, Grid"); gr->SetOrigin(0,0);
  gr->Axis(); gr->Grid(); gr->FPlot("x^3");

  gr->SubPlot(2,2,1); gr->Title("2 axis");
  gr->SetRanges(-1,1,-1,1); gr->SetOrigin(-1,-1,-1);  // first axis
  gr->Axis(); gr->Label('y',"axis 1",0);  gr->FPlot("sin(pi*x)");
  gr->SetRanges(0,1,0,1);   gr->SetOrigin(1,1,1);   // second axis
  gr->Axis(); gr->Label('y',"axis 2",0);  gr->FPlot("cos(pi*x)");

  gr->SubPlot(2,2,3); gr->Title("More axis");
  gr->SetOrigin(NAN,NAN); gr->SetRange('x',-1,1);
  gr->Axis(); gr->Label('x',"x",0); gr->Label('y',"y_1",0);
  gr->FPlot("x^2","k");
  gr->SetRanges(-1,1,-1,1); gr->SetOrigin(-1.3,-1); // second axis
  gr->Axis("y","r");  gr->Label('y',"#r{y_2}",0.2);
  gr->FPlot("x^3","r");

  gr->SubPlot(2,2,2); gr->Title("4 segments, inverted axis");
  gr->SetOrigin(0,0);
  gr->InPlot(0.5,1,0.5,1);  gr->SetRanges(0,10,0,2);  gr->Axis();
  gr->FPlot("sqrt(x/2)");   gr->Label('x',"W",1); gr->Label('y',"U",1);
  gr->InPlot(0,0.5,0.5,1);  gr->SetRanges(1,0,0,2); gr->Axis("x");
  gr->FPlot("sqrt(x)+x^3"); gr->Label('x',"\\tau",-1);
  gr->InPlot(0.5,1,0,0.5);  gr->SetRanges(0,10,4,0);  gr->Axis("y");
  gr->FPlot("x/4"); gr->Label('y',"L",-1);
  gr->InPlot(0,0.5,0,0.5);  gr->SetRanges(1,0,4,0); gr->FPlot("4*x^2");
  return 0;
}

int it=0;

int sample(mglGraph *gr,double w, double h)
{
    gr->SetSize(w,h,true);
    mglData dat (100);
    for (long j = 0; j < dat.nx; j++)
      dat.a[j] = sin (5.0*M_PI*(j)/dat.nx+it*0.5);
    
    gr->NewFrame ();          // start frame
    gr->SubPlot(1,1,0,"<_"); 
    gr->Aspect(1.0,1.0);
    
    
    gr->Title("Beam and ray tracing","",-1.5);
    gr->SetFontSize(4);
    gr->Box();                 //some plotting
    gr->Axis();                //draw axis
    gr->Label('x', "x",0);   //x Title
    gr->Label('y', "f(x) (Arb.)",0);   //y Title
    gr->Grid("xy","{xA9A9A9}|");
    
    gr->Plot(dat, "{x6495ED}-2");      // "b" is colour ??
    //gr->Puts(mglPoint(0.7, -0.05), strstream.str().c_str());
    //gr->EndFrame ();          // end frame
    //gr->WriteFrame ();        // save frame
    return 0;
}

int sample1(mglGraph *gr, double w, double h)
{
        gr->SetSize(w,h,true);
    //gr.Alpha(true); // draws something using MathGL
    //gr.Light(true);
mglData a,re(128),im(128);
gr->Fill(re,"exp(-48*(x+0.7)^2)");
a = gr->PDE("p^2+q^2-x-1+i*0.5*(z+x)*(z>-x)", re, im, 0.01, 30);
a.Transpose("yxz");
gr->SubPlot(1,1,0,"<_"); gr->Title("PDE solver");
gr->Aspect(w,h);
gr->SetRange('c',0,1); gr->Dens(a,"wyrRk");
gr->Axis(); gr->Label('x', "\\i x"); gr->Label('y', "\\i z");
gr->FPlot("-x", "k|");
gr->Puts(mglPoint(0, 0.85), "absorption: (x+z)/2 for x+z>0");
gr->Puts(mglPoint(0,1.1),"Equation: ik_0\\partial_zu + \\Delta u + x\\cdot u");
return 0;
}

int sample9(mglGraph *gr, double w, double h)
{
            gr->SetSize(w,h,true);
    frameCnt++;
    char str[128];
    std::stringstream strstream;
    strstream << frameCnt;
mglData r, xx, yy, a, im(128), re(128);
const char *ham = "p^2+q^2-x-1+i*0.5*(y+x)*(y>-x)";
r = mglRay(ham, mglPoint(-0.7, -1), mglPoint(0, 0.5), 0.02, 2);
gr->SubPlot(1,1,0,"<_"); gr->Title("Beam and ray tracing");
gr->Aspect(w/w,h/w);
gr->Plot(r.SubData(0), r.SubData(1), "k");
gr->Axis(); gr->Label('x', " x"); gr->Label('y', "\\i z");
// now start beam tracing
gr->Fill(re,"exp(-48*x^2)");
a = mglQO2d(ham, re, im, r, xx, yy, 1, 30);
gr->SetRange('c',0, 1);
gr->Dens(xx, yy, a, "wyrRk");
gr->FPlot("-x", "k|");
gr->Puts(mglPoint(0, 0.85), "absorption: (x+y)/2 for x+y>0");
gr->Puts(mglPoint(0.7, -0.05), strstream.str().c_str());
return 0;
}

// function to draw the texture for cube faces
static wxImage DrawDice(int size, unsigned num)
{
    /*
    wxASSERT_MSG( num >= 1 && num <= 6, "invalid dice index" );

    const int dot = size/16;        // radius of a single dot
    const int gap = 5*size/32;      // gap between dots

    wxBitmap bmp(size, size);
    wxMemoryDC dc;
    dc.SelectObject(bmp);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    dc.SetBrush(*wxBLACK_BRUSH);

    // the upper left and lower right points
    if ( num != 1 )
    {
        dc.DrawCircle(gap + dot, gap + dot, dot);
        dc.DrawCircle(size - gap - dot, size - gap - dot, dot);
    }

    // draw the central point for odd dices
    if ( num % 2 )
    {
        dc.DrawCircle(size/2, size/2, dot);
    }

    // the upper right and lower left points
    if ( num > 3 )
    {
        dc.DrawCircle(size - gap - dot, gap + dot, dot);
        dc.DrawCircle(gap + dot, size - gap - dot, dot);
    }

    // finally those 2 are only for the last dice
    if ( num == 6 )
    {
        dc.DrawCircle(gap + dot, size/2, dot);
        dc.DrawCircle(size - gap - dot, size/2, dot);
    }

    dc.SelectObject(wxNullBitmap);
*/

    /*
    std::stringstream pngfile;
    pngfile << "C:/Users/mohammad/Documents/Codelite/pecsjunc/GUI/fig.png";
    wxBitmap Bitmap;
    Bitmap.LoadFile(pngfile.str().c_str(),wxBITMAP_TYPE_PNG); 
    return Bitmap.ConvertToImage();
    */
}

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// MyGLContext
// ----------------------------------------------------------------------------

MyGLContext::MyGLContext(wxGLCanvas *canvas, int DimVar)
             : wxGLContext(canvas)
{
    Dim=DimVar;
    SetCurrent(*canvas);
    glGenTextures(WXSIZEOF(m_textures), m_textures);
    
    //Shared between 2D and 3D OpenGL
    glEnable(GL_TEXTURE_2D); //Essential
    glEnable(GL_NORMALIZE);  //Faster
    glEnable(GL_LIGHT0); //is not checked
    glEnable(GL_BLEND); //is not checked
    glEnable(GL_CULL_FACE); //is not checked
    glEnable(GL_DEPTH_TEST); //is not checked
    
    //for ( unsigned i = 0; i < WXSIZEOF(m_textures); i++ )
    //{
        glBindTexture(GL_TEXTURE_2D, m_textures[0]);

        GLfloat fLargest;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
    
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST is fast but low quality textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
        
    int w,h,x,y;
    w=1600;
    h=400;
    //GetClientSize(&w,&h); // size of the picture
    mglGraph gr(w,h);
    gr.Alpha(true); // draws something using MathGL
    gr.Light(true);
    sample(&gr,(double)w,(double)h);
    //wxImage img(w,h,(unsigned char *)gr.GetRGB(),true);
    //return img;
        
        //const wxImage img(DrawDice(256, i + 1));
        
        //const wxImage img(w,h,(unsigned char *)gr.GetRGB(),true);
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.GetWidth(), img.GetHeight(),
        //             0, GL_RGB, GL_UNSIGNED_BYTE, img.GetData());
                     
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gr.GetWidth(), gr.GetHeight(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, gr.GetRGB());
                     
                     //(unsigned char *)
    //}

    
    //
    
    CheckGLError();
}



void MyGLContext::Polygons3D()
{
    // draw six faces of a cube of size 1 centered at (0, 0, 0)
    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glBegin(GL_QUADS);
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glTexCoord2f(0, 0); glVertex3f( 0.5f, 0.5f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f(-0.5f,-0.5f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f( 0.5f,-0.5f, 0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glBegin(GL_QUADS);
        glNormal3f( 0.0f, 0.0f,-1.0f);
        glTexCoord2f(0, 0); glVertex3f(-0.5f,-0.5f,-0.5f);
        glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f,-0.5f);
        glTexCoord2f(1, 1); glVertex3f( 0.5f, 0.5f,-0.5f);
        glTexCoord2f(0, 1); glVertex3f( 0.5f,-0.5f,-0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glBegin(GL_QUADS);
        glNormal3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f( 0.5f, 0.5f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f( 0.5f, 0.5f,-0.5f);
        glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f,-0.5f);
        glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glBegin(GL_QUADS);
        glNormal3f( 0.0f,-1.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(-0.5f,-0.5f,-0.5f);
        glTexCoord2f(1, 0); glVertex3f( 0.5f,-0.5f,-0.5f);
        glTexCoord2f(1, 1); glVertex3f( 0.5f,-0.5f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(-0.5f,-0.5f, 0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glBegin(GL_QUADS);
        glNormal3f( 1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f( 0.5f, 0.5f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f( 0.5f,-0.5f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f( 0.5f,-0.5f,-0.5f);
        glTexCoord2f(0, 1); glVertex3f( 0.5f, 0.5f,-0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(-0.5f,-0.5f,-0.5f);
        glTexCoord2f(1, 0); glVertex3f(-0.5f,-0.5f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f,-0.5f);
    glEnd();

}

void MyGLContext::background()
{
    glColor3f(1.0f, 1.0f, 1.0f); // Red
    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glBegin( GL_QUADS );
    glTexCoord2d(0.0,1.0); glVertex2d(-1.0,-1.0);
    glTexCoord2d(1.0,1.0); glVertex2d(+1.0,-1.0);
    glTexCoord2d(1.0,0.0); glVertex2d(+1.0,+1.0);
    glTexCoord2d(0.0,0.0); glVertex2d(-1.0,+1.0);
    glEnd();
}

void MyGLContext::Polygons2D()
{
    /*
    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
      glVertex2f(-0.2f, 0.7f);
      glVertex2f(-0.8f, 0.7f);
      
      glColor3f(0.0f, 1.0f, 0.0f); // Green
      glVertex2f(-30.7f, -0.6f);
      glVertex2f(-0.1f, -0.6f);
      glVertex2f(-0.1f,  0.0f);
      glVertex2f(-0.7f,  0.0f);
 
      glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
      glVertex2f(-0.9f, -0.7f);
      glColor3f(1.0f, 1.0f, 1.0f); // White
      glVertex2f(-0.5f, -0.7f);
      glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
      glVertex2f(-0.5f, -0.3f);
      glColor3f(1.0f, 1.0f, 1.0f); // White
      glVertex2f(-0.9f, -0.3f);
   glEnd();
 
   glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f(0.1f, -0.6f);
      glVertex2f(0.7f, -0.6f);
      glVertex2f(0.4f, -0.1f);
 
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(0.3f, -0.4f);
      glColor3f(0.0f, 1.0f, 0.0f); // Green
      glVertex2f(0.9f, -0.4f);
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f(0.6f, -0.9f);
   glEnd();
 
   glBegin(GL_POLYGON);            // These vertices form a closed polygon
      glColor3f(1.0f, 1.0f, 0.0f); // Yellow
      glVertex2f(0.4f, 0.2f);
      glVertex2f(0.6f, 0.2f);
      glVertex2f(0.97f, 0.4f);
      glVertex2f(0.6f, 0.6f);
      glVertex2f(0.4f, 0.6f);
      glVertex2f(0.3f, 0.4f);
   glEnd();
    */
}

void MyGLContext::Draw2D()
{
    glDisable(GL_LIGHTING);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable( GL_TEXTURE_2D );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    background();
    Polygons2D();
    glFlush();  // Render now
    glPopMatrix();
    CheckGLError();
}

void MyGLContext::Draw3D(float xangle, float yangle)
{
    glEnable(GL_LIGHTING);
    GLfloat ambient[] = { 0.65, 0.65, 0.65, 0.65 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -2.0f);
    glRotatef(xangle, 1.0f, 0.0f, 0.0f);
    glRotatef(yangle, 0.0f, 1.0f, 0.0f);
    Polygons3D();
    glFlush();  // Render now
    glPopMatrix();
    CheckGLError();
}

// ----------------------------------------------------------------------------
// MyGLCanvas
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
    EVT_PAINT(MyGLCanvas::OnPaint)
    EVT_KEY_DOWN(MyGLCanvas::OnKeyDown)
    EVT_TIMER(SpinTimer, MyGLCanvas::OnSpinTimer)
wxEND_EVENT_TABLE()

MyGLCanvas::MyGLCanvas(wxWindow *parent, int DimVar, int *attribList)
    // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
    // flag should always be set, because even making the canvas smaller should
    // be followed by a paint event that updates the entire canvas with new
    // viewport settings.
    : wxGLCanvas(parent, wxID_ANY, attribList,
                 wxDefaultPosition, wxDefaultSize,
                 wxFULL_REPAINT_ON_RESIZE),
      m_xangle(0.0),
      m_yangle(0.0),
      m_spinTimer(this,SpinTimer),
      m_useStereo(false),
      m_stereoWarningAlreadyDisplayed(false)
{
    Dim = DimVar;
    if ( attribList )
    {
        int i = 0;
        while ( attribList[i] != 0 )
        {
            if ( attribList[i] == WX_GL_STEREO )
                m_useStereo = true;
            ++i;
        }
    }
}

void MyGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    // This is required even though dc is not used otherwise.
    wxPaintDC dc(this);

    // Set the OpenGL viewport according to the client size of this canvas.
    // This is done here rather than in a wxSizeEvent handler because our
    // OpenGL rendering context (and thus viewport setting) is used with
    // multiple canvases: If we updated the viewport in the wxSizeEvent
    // handler, changing the size of one canvas causes a viewport setting that
    // is wrong when next another canvas is repainted.
    const wxSize ClientSize = GetClientSize();
                     
    MyGLContext& context = wxGetApp().GetContext(this, Dim, m_useStereo);

    glViewport(0,0,ClientSize.x, ClientSize.y); // decide which area of the frame will be painted
    //gluOrtho2D(0, ClientSize.x, 0, ClientSize.y);
    
    // Render the graphics and swap the buffers.
    GLboolean quadStereoSupported;
    glGetBooleanv( GL_STEREO, &quadStereoSupported);
    
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluOrtho2D(0, ClientSize.x, 0, ClientSize.y); // set up coordinate system
    //glMatrixMode(GL_MODELVIEW);
    //canvas.DrawRotatedCube(m_xangle, m_yangle);
    

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black and opaque
    
    
    int w,h,x,y;
    w=ClientSize.x;
    h=ClientSize.y;
    //GetClientSize(&w,&h); // size of the picture
    mglGraph gr;
    sample(&gr,(double)w,(double)h);
    
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gr.GetWidth(), gr.GetHeight(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, gr.GetRGB());
    
    if ( quadStereoSupported )
    {
        glDrawBuffer( GL_BACK_LEFT );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-0.47f, 0.53f, -0.5f, 0.5f, 1.0f, 3.0f);
        
        if (Dim>2)
            context.Draw3D(m_xangle, m_yangle);
        else
            context.Draw2D();
            
        CheckGLError();
        glDrawBuffer( GL_BACK_RIGHT );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-0.53f, 0.47f, -0.5f, 0.5f, 1.0f, 3.0f);
        
        if (Dim>2)
            context.Draw3D(m_xangle, m_yangle);
        else
            context.Draw2D();
            
        CheckGLError();
    }
    else
    {
        if (Dim>2)
            context.Draw3D(m_xangle, m_yangle);
        else
            context.Draw2D();
        if ( m_useStereo && !m_stereoWarningAlreadyDisplayed )
        {
            m_stereoWarningAlreadyDisplayed = true;
            wxLogError("Stereo not supported by the graphics card.");
        }
    }
    
    SwapBuffers();
    
    
    //glFinish(); // necessary
}

void MyGLCanvas::Spin(float xSpin, float ySpin)
{
    m_xangle += xSpin;
    m_yangle += ySpin;

    Refresh(false);
}

void MyGLCanvas::Animate(void)
{
    it++;
    Refresh(false);
}

void MyGLCanvas::OnKeyDown(wxKeyEvent& event)
{
    float angle = 5.0;

    switch ( event.GetKeyCode() )
    {
        case WXK_RIGHT:
            Spin( 0.0, -angle );
            break;

        case WXK_LEFT:
            Spin( 0.0, angle );
            break;

        case WXK_DOWN:
            Spin( -angle, 0.0 );
            break;

        case WXK_UP:
            Spin( angle, 0.0 );
            break;

        case WXK_SPACE:
            if ( m_spinTimer.IsRunning() )
                m_spinTimer.Stop();
            else
                m_spinTimer.Start( 100 );
            break;

        default:
            event.Skip();
            return;
    }
}

void MyGLCanvas::OnSpinTimer(wxTimerEvent& WXUNUSED(event))
{
    if (Dim == 3)
        Spin(0.0, 4.0);
    else
        Animate();
    
}
