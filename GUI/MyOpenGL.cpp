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


#include <wx/clipbrd.h> 
#include <wx/menu.h>
#include <wx/textfile.h>

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
    glEnable(GL_BLEND); //is not checked
    glEnable(GL_CULL_FACE); //is not checked
    glEnable(GL_DEPTH_TEST); //is not checked
    glEnable(GL_COLOR_MATERIAL); //To enable the colourful glusphere. Whithout this we are unable to change the color of surfaces
    
    //glEnable( GL_LINE_SMOOTH );
    //glEnable( GL_POLYGON_SMOOTH );
    //glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    //glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    
    glEnable(GL_LIGHT0); //is not checked
	glLightfv(GL_LIGHT0, GL_POSITION, (const GLfloat[]) {30,30,50.0f});
	glLightfv(GL_LIGHT0, GL_SPECULAR,  (const GLfloat[]) {1,1,1,1});
    
    glEnable(GL_LIGHT1); //is not checked
	glLightfv(GL_LIGHT1, GL_POSITION, (const GLfloat[]) {-70,-70,0.0f});
	glLightfv(GL_LIGHT1, GL_SPECULAR,  (const GLfloat[]) {0.5,0.5,0.5,1});
    
    glEnable(GL_LIGHT2); //is not checked
	glLightfv(GL_LIGHT2, GL_POSITION, (const GLfloat[]) {0,0,50.0f});
	glLightfv(GL_LIGHT2, GL_AMBIENT,  (const GLfloat[]) {0.25,0.25,0.25,0.25});
	//glLightfv(GL_LIGHT0, GL_DIFFUSE,  (const GLfloat[]) {1,1,1,1});
	//glLightfv(GL_LIGHT0, GL_SPECULAR, (const GLfloat[]) {1,1,1,1});

    
    glMaterialfv(GL_FRONT, GL_EMISSION,  (const GLfloat[]) {0,0,0,1} );
    glMaterialfv(GL_FRONT, GL_AMBIENT,  (const GLfloat[]) {1,1,1,1} );
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  (const GLfloat[]) {1,1,1,1} );
    glMaterialfv(GL_FRONT, GL_SPECULAR,  (const GLfloat[]) {1,1,1,1} );
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0f);
    
    
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

// initiate buffers
GLuint elementbuffer;
GLuint normalbuffer;
GLuint uvbuffer;
GLuint vertexbuffer;

// this variable will later be used to hold the number of indices
int size = 0;



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

void MyGLContext::Draw_Atom(float r, float x, float y, float z, GLubyte R, GLubyte G, GLubyte B, int Slices, int Stacks)
{
    glPushMatrix();
    glColor3ub(R, G, B);
    glTranslatef(x, y, z);
    //glScaled(0.5, 0.5, 0.5);
    gluSphere(quad,r , Slices , Stacks);
    //gluDisk(quad,1.0f,2.0f,50,3);
    glPopMatrix();
}

void MyGLContext::Draw_Bond(float x0, float y0, float z0, float x1, float y1, float z1, float radius, GLubyte R, GLubyte G, GLubyte B, int Slices, int Stacks)
{
    float pi180 = 3.14159265/180.0;
    float r = sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) + (z1-z0)*(z1-z0));
    float th = 0;
    if (r==0)
        th=0;
    else
        th = acos((z1-z0)/r) / pi180;
    float phi = atan2((y1-y0),(x1-x0)) / pi180;
    glPushMatrix();
    glColor3ub(R, G, B);
    glTranslatef(x0, y0, z0);
    glRotatef(phi, 0.0f, 0.0f, 1.0f);
    glRotatef(th, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad, radius, radius, r, Slices, Stacks);
    glPopMatrix();
}

//check it
//void cleanup() // call once when you exit program
//{
//  gluDeleteQuadric(qobj);
//}

void MyGLContext::Draw_Lattice(int nColDArray, int* nDArray, double** DArray, int nColIArray, int* nIArray, int** IArray)
{
    /***********************************************************************************/
    /* The structure of data: (note that the number of atoms and bonds can be different)
     * DArray[0][:] DArray[1][:] DArray[2][:] DArray[3][:] DArray[4][:] DArray[5][:] DArray[6][:] DArray[7][:] DArray[8][:] DArray[9][:] DArray[10][:]  IArray[0][:]   IArray[1][:]   IArray[2][:]  IArray[3][:]   IArray[4][:]   IArray[5][:]
     *      x0          y0           z0           r0           x1bond0     y1bond0     z1bond0      x2bond0      y2bond0      z2bond0      rbond0         AtomRed0      AtomGreen0     AtomBlue0       BondRed0      BondGreen0    BondBlue0
     *      x1          y1           z1           r1           x1bond1     y1bond1     z1bond1      x2bond1      y2bond1      z2bond1      rbond1         AtomRed1      AtomGreen1     AtomBlue1       BondRed1      BondGreen1    BondBlue1
     *      x2          y2           z2           r2           x1bond2     y1bond2     z1bond2      x2bond2      y2bond2      z2bond2      rbond2         AtomRed2      AtomGreen2     AtomBlue2       BondRed2      BondGreen2    BondBlue2
     *                                                         x1bond3     y1bond3     z1bond3      x2bond3      y2bond3      z2bond3      rbond3                                                      BondRed3      BondGreen3    BondBlue3
     *                                                         x1bond4     y1bond4     z1bond4      x2bond4      y2bond4      z2bond4      rbond4                                                      BondRed4      BondGreen4    BondBlue4
     */
    /***********************************************************************************/
    for (int i=0; i<nDArray[0]; i++)
    {
        Draw_Atom((float)DArray[3][i], (float)DArray[0][i], (float)DArray[1][i], (float)DArray[2][i], (GLubyte)IArray[0][i], (GLubyte)IArray[1][i], (GLubyte)IArray[2][i], 60, 40);
    }
    
    for (int i=0; i<nDArray[4]; i++)
    {
        Draw_Bond((float)DArray[4][i], (float)DArray[5][i], (float)DArray[6][i],(float)DArray[7][i], (float)DArray[8][i], (float)DArray[9][i], (float)DArray[10][i], (GLubyte)IArray[3][i], (GLubyte)IArray[4][i], (GLubyte)IArray[5][i] ,23,2);
    }
    
}

void MyGLContext::Draw3D(int nColDArray, int* nDArray, double** DArray, int nColIArray, int* nIArray, int** IArray, float xMove, float yMove, float XCam, float YCam, float zoom, float zoomCam, float w, float h)
{
    glEnable(GL_LIGHTING);
    GLfloat ambient[] = { 0.065, 0.065, 0.065, 0.065 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    //glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluLookAt(0, 0, -1,  0, 0, 0, 1, 0, 0);
    //glFrustum(-1.0f, 1.0f, -0.5f, 0.5f, 1.0f, 10.0f);
    glOrtho(-w, w, -h, h, -50.0f, 50.0f);
    glTranslatef(XCam + xMove, YCam + yMove, 0.0f);
    float ztot = zoomCam + zoom;
    if (ztot <= 0.001) ztot = 0.001;
    glScaled(ztot, ztot, ztot);//Zoom
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -2.0f);
    //glRotatef(xangle, 1.0f, 0.0f, 0.0f);
    //glRotatef(yangle, 0.0f, 1.0f, 0.0f);
    //double theta = zangle*0.01745329252;
    //glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
    //glRotatef(xangle, (float)sin(theta), -(float)cos(theta), 0.0f);
    //glRotatef(zangle, 0.0f, 0.0f, 1.0f);
    
    
    //Polygons3D(); //It works, but we do not need it no longer
    //Glu Functions Begin
    quad = gluNewQuadric();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE or GL_FILL
    glLineWidth(1.0);
    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    Draw_Lattice(nColDArray, nDArray, DArray, nColIArray, nIArray, IArray);
    gluDeleteQuadric(quad);
    //Glu Functions End
    glFlush();  // Render now
    //glPopMatrix();
    CheckGLError();
}

// ----------------------------------------------------------------------------
// MyGLCanvas
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
    EVT_PAINT(MyGLCanvas::OnPaint)
    EVT_KEY_DOWN(MyGLCanvas::OnKeyDown)
    EVT_TIMER(SpinTimer, MyGLCanvas::OnSpinTimer)
    EVT_MOUSEWHEEL(MyGLCanvas::OnMouseWheel)
    EVT_LEFT_DOWN(MyGLCanvas::OnMouseLeftDown)
    EVT_LEFT_UP(MyGLCanvas::OnMouseLeftUp)
    EVT_MOTION(MyGLCanvas::OnMouseMove)
    EVT_RIGHT_DOWN(MyGLCanvas::OnMouseRightDown)
    EVT_RIGHT_UP(MyGLCanvas::OnMouseRightUp)
    EVT_MIDDLE_DOWN(MyGLCanvas::OnMouseMiddleDown)
    EVT_MIDDLE_UP(MyGLCanvas::OnMouseMiddleUp)
    EVT_MENU(wxID_COPY,MyGLCanvas::OnSaveRasterImage)
wxEND_EVENT_TABLE()

MyGLCanvas::MyGLCanvas(wxWindow *parent, int DimVar, int *attribList)
    // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
    // flag should always be set, because even making the canvas smaller should
    // be followed by a paint event that updates the entire canvas with new
    // viewport settings.
    : wxGLCanvas(parent, wxID_ANY, attribList,
                 wxDefaultPosition, wxDefaultSize,
                 wxFULL_REPAINT_ON_RESIZE),
      TheLastXAngle(0.0),
      TheLastYAngle(0.0),
      TheLastZAngle(0.0),
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
    
    
    int w,h;
    w=ClientSize.x;
    h=ClientSize.y;
    float max = (float)w;
    if (h>w) max = (float)h;
    float w3d=w/max;
    float h3d=h/max;
    
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
        
        if (Dim==3)
            context.Draw3D(NumberOfDoubleArrays, nDoubleArray, DoubleArray1,
                            NumberOfIntArrays, nIntArray, IntArray,
                            XMove, YMove, XCam, YCam, Zoom, ZoomCam, w3d,h3d);
        else
            context.Draw2D();
            
        CheckGLError();
        glDrawBuffer( GL_BACK_RIGHT );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-0.53f, 0.47f, -0.5f, 0.5f, 1.0f, 3.0f);
        
        if (Dim==3)
            context.Draw3D(NumberOfDoubleArrays, nDoubleArray, DoubleArray1,
                            NumberOfIntArrays, nIntArray, IntArray,
                            XMove, YMove, XCam, YCam, Zoom, ZoomCam, w3d,h3d);
        else
            context.Draw2D();
            
        CheckGLError();
    }
    else
    {
        if (Dim==3)
            context.Draw3D(NumberOfDoubleArrays, nDoubleArray, DoubleArray1,
                            NumberOfIntArrays, nIntArray, IntArray,
                            XMove, YMove, XCam, YCam, Zoom, ZoomCam, w3d,h3d);
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

void MyGLCanvas::Spin(float xSpin, float ySpin, float zSpin)
{
    TheLastXAngle += xSpin;
    TheLastYAngle += ySpin;
    TheLastZAngle += zSpin;
    
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
            Spin( 0.0, -angle , 0.0);
            break;

        case WXK_LEFT:
            Spin( 0.0, angle  , 0.0);
            break;

        case WXK_DOWN:
            Spin( -angle, 0.0  , 0.0);
            break;

        case WXK_UP:
            Spin( angle, 0.0  , 0.0);
            break;

        case WXK_SPACE:
            if ( m_spinTimer.IsRunning() )
                m_spinTimer.Stop();
            else
                m_spinTimer.Start( 20 );
            break;

        default:
            event.Skip();
            return;
    }
}

void MyGLCanvas::OnMouseWheel(wxMouseEvent& event)
{
    bool scrldwn = event.GetWheelRotation() < 0;
    float delta = 0.005*0.01f*event.GetWheelDelta();
    //scrldwn=scrldwn;
    //int d = event.GetWheelDelta();
    if (scrldwn)
        ZoomCam = ZoomCam + delta;
    else
        ZoomCam = ZoomCam - delta;
    if (ZoomCam <=0.001) ZoomCam=0.001;
    
    Refresh(false);
}

void MyGLCanvas::OnSpinTimer(wxTimerEvent& WXUNUSED(event))
{
    if (Dim == 3)
        Spin(1.0, 0.0 , 0.0);
    else
        Animate();
    
}

void MyGLCanvas::OnMouseLeftDown(wxMouseEvent& event)
{
    //To get mouse position relative to top-left corner of display, add this in a mouse event handler:
    const wxPoint pt = wxGetMousePosition();
    mouseX0 = pt.x;
    mouseY0 = pt.y;
    isMouseLeftDown = true;
    isMouseRightDown = false;
    isMouseMiddleDown = false;
    //To get mouse position relative to top-left corner of current window or canvas, add this in a mouse event handler:
    //const wxPoint pt = wxGetMousePosition();
    //int mouseX = pt.x - this->GetScreenPosition().x;
    //int mouseY = pt.y - this->GetScreenPosition().y;
}

void MyGLCanvas::OnMouseLeftUp(wxMouseEvent& event)
{
    isMouseLeftDown = false;
    Reload();
}

void MyGLCanvas::OnMouseMove(wxMouseEvent& event)
{
    if (isMouseLeftDown)
    {
        const wxPoint pt = wxGetMousePosition();
        mouseX = pt.x;
        mouseY = pt.y;
        float l=0;
        float m=0;
        float value=0;
        GetDirection(mouseX0, mouseY0, mouseX, mouseY, l, m, value);
        
        if (isMoveMode)
            DoMove(l,m);
        else if (isRotationMode)
            DoRotate(l,m,(float)(0.01*value));
        else if (isZoomMode)
            DoZoom(0.0005*(m-l));
    }
    else if (isMouseRightDown)
    {
        const wxPoint pt = wxGetMousePosition();
        mouseX = pt.x;
        mouseY = pt.y;
        float l=0;
        float m=0;
        float value=0;
        GetDirection(mouseX0, mouseY0, mouseX, mouseY, l, m, value);
        DoZoom(0.0005*(m-l));
    }
    else if (isMouseMiddleDown)
    {
        const wxPoint pt = wxGetMousePosition();
        mouseX = pt.x;
        mouseY = pt.y;
        float l=0;
        float m=0;
        float value=0;
        GetDirection(mouseX0, mouseY0, mouseX, mouseY, l, m, value);
        DoMove(l,m);
    }
}

void MyGLCanvas::OnMouseRightDown(wxMouseEvent& event)
{
    const wxPoint pt = wxGetMousePosition();
    mouseX0 = pt.x;
    mouseY0 = pt.y;
    isMouseRightDown = true;
    isMouseLeftDown = false;
    isMouseMiddleDown = false;
}

void MyGLCanvas::OnMouseRightUp(wxMouseEvent& event)
{
    const wxPoint pt = wxGetMousePosition();
    mouseX = pt.x;
    mouseY = pt.y;
    isMouseRightDown = false;
    if (mouseY==mouseY0 && mouseX==mouseX0)
    {
        wxMenu *pmenuPopUp = new wxMenu;
        wxMenuItem* pItem;
        pItem = new wxMenuItem(pmenuPopUp,wxID_COPY, wxT("Save Raster Image"));
        pmenuPopUp->Append(pItem);
        PopupMenu(pmenuPopUp,event.GetPosition());
        delete pmenuPopUp;
    }
    else
        Reload();
}

void MyGLCanvas::OnMouseMiddleDown(wxMouseEvent& event)
{
    const wxPoint pt = wxGetMousePosition();
    mouseX0 = pt.x;
    mouseY0 = pt.y;
    isMouseMiddleDown = true;
    isMouseRightDown = false;
    isMouseLeftDown = false;
}

void MyGLCanvas::OnMouseMiddleUp(wxMouseEvent& event)
{
    isMouseMiddleDown = false;
    Reload();
}

void MyGLCanvas::OnSaveRasterImage(wxCommandEvent &WXUNUSED(event))
{
    
}

void MyGLCanvas::DoMove(float l, float m)
{
    const wxSize ClientSize = GetClientSize();
    int w,h;
    w=ClientSize.x;
    h=ClientSize.y;
    float max = (float)w;
    if (h>w) max = (float)h;
    float w3d=w/max;
    float h3d=h/max;
    
    if (l!=0) XMove = -2.0*l*w3d/w;
    if (m!=0) YMove = -2.0*m*h3d/h;
    Refresh(false);
}

void MyGLCanvas::DoRotate(float l, float m, float Theta)
{
    if (l==0 && m==0) return;
    double r2 = l*l + m*m;
    double r = sqrt(r2);
    double sr = sin(Theta)/r;
    double c = cos(Theta);
    double cr2 = c/r2;
    double sr2 = sr/r;
    for (int i=0; i<nDoubleArray[0]; i++)
    {
        double a = (m*DoubleArray0[0][i] - l*DoubleArray0[1][i])/r2;
        double b = l*DoubleArray0[0][i] + m*DoubleArray0[1][i];
        double bc = b*cr2;
        double zs = DoubleArray0[2][i]*sr2;
        DoubleArray1[0][i] = m*a + l*bc - l*r*zs;
        DoubleArray1[1][i] = -l*a + m*bc - m*r*zs;
        DoubleArray1[2][i] = DoubleArray0[2][i]*c + b*sr;
    }
    
    for (int i=0; i<nDoubleArray[4]; i++)
    {
        double a = (m*DoubleArray0[4][i] - l*DoubleArray0[5][i])/r2;
        double b = l*DoubleArray0[4][i] + m*DoubleArray0[5][i];
        double bc = b*cr2;
        double zs = DoubleArray0[6][i]*sr2;
        DoubleArray1[4][i] = m*a + l*bc - l*r*zs;
        DoubleArray1[5][i] = -l*a + m*bc - m*r*zs;
        DoubleArray1[6][i] = DoubleArray0[6][i]*c + b*sr;
    }
    
    
    for (int i=0; i<nDoubleArray[7]; i++)
    {
        double a = (m*DoubleArray0[7][i] - l*DoubleArray0[8][i])/r2;
        double b = l*DoubleArray0[7][i] + m*DoubleArray0[8][i];
        double bc = b*cr2;
        double zs = DoubleArray0[9][i]*sr2;
        DoubleArray1[7][i] = m*a + l*bc - l*r*zs;
        DoubleArray1[8][i] = -l*a + m*bc - m*r*zs;
        DoubleArray1[9][i] = DoubleArray0[9][i]*c + b*sr;
    }
    
    Refresh(false);
}

void MyGLCanvas::DoZoom(float l)
{
    if (l!=0) Zoom = -l;
    Refresh(false);
}

void MyGLCanvas::GetDirection(int i0, int j0, int i, int j, float& x, float& y, float& Theta)
{
    x = -(float)(i - i0);
    y = (float)(j - j0);
    Theta = (float)sqrt(x*x + y*y);
}

void MyGLCanvas::CreateDoubleArray(int NumberOfArraysVar, int* nArray)
{
    NumberOfDoubleArrays=NumberOfArraysVar;
    nDoubleArray = new int[NumberOfDoubleArrays];
	DoubleArray = new double*[NumberOfDoubleArrays];
	for(int i = 0; i < NumberOfDoubleArrays; i++)
    {
        nDoubleArray[i]=nArray[i];
        DoubleArray[i] = new double[nDoubleArray[i]];
    }
    CreateDoubleArray1();
}

void MyGLCanvas::DiscardDoubleArrays()
{
    for(int i = 0; i < NumberOfDoubleArrays; i++)
    {
        if (nDoubleArray[i] > 0) delete [] DoubleArray[i];
    }
	if (NumberOfDoubleArrays>0) delete [] DoubleArray;
    DiscardDoubleArrays1();
}

void MyGLCanvas::CreateIntArray(int NumberOfArraysVar, int* nArray)
{
    NumberOfIntArrays=NumberOfArraysVar;
    nIntArray = new int[NumberOfIntArrays];
	IntArray = new int*[NumberOfIntArrays];
	for(int i = 0; i < NumberOfIntArrays; i++)
    {
        nIntArray[i]=nArray[i];
        IntArray[i] = new int[nIntArray[i]];
    }
}

void MyGLCanvas::DiscardIntArrays()
{
    for(int i = 0; i < NumberOfIntArrays; i++)
    {
        if (nIntArray[i] > 0)
        {
            delete [] IntArray[i];
            nIntArray[i] = 0;
        }
    }
	if (NumberOfIntArrays>0) delete [] IntArray;
    NumberOfIntArrays = 0;
}


void MyGLCanvas::CreateDoubleArray1()
{
	DoubleArray0 = new double*[NumberOfDoubleArrays];
    DoubleArray1 = new double*[NumberOfDoubleArrays];
	for(int i = 0; i < NumberOfDoubleArrays; i++)
    {
        DoubleArray0[i] = new double[nDoubleArray[i]];
        DoubleArray1[i] = new double[nDoubleArray[i]];
    }
}

void MyGLCanvas::DiscardDoubleArrays1()
{
    for(int i = 0; i < NumberOfDoubleArrays; i++)
    {
        if (nDoubleArray[i] > 0)
        {
            delete [] DoubleArray0[i];
            delete [] DoubleArray1[i];
            nDoubleArray[i]=0;
        }
    }
	if (NumberOfDoubleArrays>0) delete [] DoubleArray0;
    if (NumberOfDoubleArrays>0) delete [] DoubleArray1;
    NumberOfDoubleArrays=0;
}

void MyGLCanvas::LoadToCanvas()
{
    for (int i=0; i<NumberOfDoubleArrays; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray1[i][j] = DoubleArray[i][j];
    Reload();
}

void MyGLCanvas::Reload()
{
    XCam += XMove;
    YCam += YMove;
    ZoomCam += Zoom;
    if (ZoomCam <=0.001) ZoomCam=0.001;
    XMove = 0;
    YMove = 0;
    Zoom = 0;
    for (int i=0; i<NumberOfDoubleArrays; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray0[i][j] = DoubleArray1[i][j];
}