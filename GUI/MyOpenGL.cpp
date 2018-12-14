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

// this is a definition so can't be in a header
wxDEFINE_EVENT(MyOpenGL_EVT_SelectionChanged, wxCommandEvent);

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

int PlotBand(mglGraph *gr, int w, int h, Sec30* sec30, int MyID)
{
    bool isBandLoaded = false;
    if (sec30->ArraysOf0DInt[0] != 0) isBandLoaded = true;
    
    if (isBandLoaded)
    {
        int nKPoint = sec30->ArraysOf0DInt[1];
        int maxneig = sec30->ArraysOf0DInt[2];
        int mspin = sec30->ArraysOf0DInt[3];
        int DFTnMin = sec30->ArraysOf0DInt[4];
        int DFTnMax = sec30->ArraysOf0DInt[5];
        double ChemP = sec30->ArraysOf0DDouble[0];
        bool SelectMode = false;
        if (sec30->ArraysOf0DInt[6] != 0) SelectMode = true;
        
        mreal yMin, yMax, xMin, xMax;
        if (MyID == 0)
        {
            yMin = (mreal)sec30->ArraysOf0DDouble[1];
            yMax = (mreal)sec30->ArraysOf0DDouble[2];
            xMin = (mreal)sec30->ArraysOf0DDouble[5];
            xMax = (mreal)sec30->ArraysOf0DDouble[6];
        }
        else if (MyID == 1)
        {
            yMin = (mreal)sec30->ArraysOf0DDouble[3];
            yMax = (mreal)sec30->ArraysOf0DDouble[4];
            xMin = (mreal)sec30->ArraysOf0DDouble[7];
            xMax = (mreal)sec30->ArraysOf0DDouble[8];
        }
        //sec30->ArraysOf2DDouble[0] = Adouble1D();//double** FracKPoint;
        //sec30->ArraysOf2DDouble[1] = Adouble1D();//double** EigVal;
        
        if (DFTnMax < DFTnMin || DFTnMax<1 || DFTnMin<1 || DFTnMin>maxneig || DFTnMax>maxneig) return 0;
        
        int nCurve = DFTnMax - DFTnMin + 1;
        int nX = nKPoint;
        mglData Y(nX,nCurve);
        mglData C(nX,nCurve);
        mglData X(nX);
        
        for(long iX=0; iX<nX; iX++)
        {
            //mreal x = iX/(nX-1.0);
            X.a[iX] = (mreal)sec30->ArraysOf2DDouble[0][iX][6];//d_path
        }
            
        for(long iCurve=0; iCurve<nCurve; iCurve++)
        {
            for(long iX=0; iX<nX; iX++)
            {
                //mreal x = iX/(nX-1.0);
                Y.a[iCurve*nX + iX] = (mreal)(sec30->ArraysOf2DDouble[1][iX][iCurve + DFTnMin - 1] - ChemP);//Eigen Value - ChemP
            }
        }
        
        if (SelectMode)
        {
            for(long iCurve=0; iCurve<nCurve; iCurve++)
            {
                for(long iX=0; iX<nX; iX++)
                {
                    //mreal x = iX/(nX-1.0);
                    C.a[iCurve*nX + iX] = -0.5;
                    if ( iX > (int)(nX/3.0)) C.a[iCurve*nX + iX] = 0.5;
                }
            }
        }
        
        
        gr->NewFrame();          // start frame
        //gr->Adjust();
        //gr->Rasterize();
        //gr->SubPlot(1,1,0,"");
        if (SelectMode)
            gr->SubPlot(1,1,0,"#");
        else
            gr->SubPlot(1,1,0,"");
        //gr->SetSize((int)(w*1.5),(int)(h*1.5),true);
        //gr->Title("Beam and ray tracing","",-1.5);
        gr->SetFontSize(4);
        //gr->Label('x', "k",0);   //x Title
        //gr->Label('y', "E_k (eV)",0);   //y Title
        gr->SetRanges(X.a[0], X.a[nX-1], yMin, yMax);
        double val[]={X.a[0] + 0.00000001};
        wxString xlabel = sec30->ArraysOf1DString[0][0];
        gr->SetTicksVal('x', mglData(1,val), xlabel.c_str().AsChar());
        //gr->SetTicks('x',X.a[nX-1] + 1,-1);
        int nk = sec30->ArraysOf1DString[0].size();
        for (int ik=1; ik<nk-1; ik++)
        {
            mreal xpos = (mreal)sec30->ArraysOf1DDouble[0][ik];
            xlabel = sec30->ArraysOf1DString[0][ik];
            gr->AddTick('x', xpos, xlabel.c_str().AsChar());
        }
        mreal xpos2 = X.a[nX-1] - 0.00000001;
        xlabel = sec30->ArraysOf1DString[0][nk-1];
        gr->AddTick('x', xpos2, xlabel.c_str().AsChar());
        
        //gr->SetTicks(’x’,M_PI,0,0,"\\pi");
        //gr->AddTick(’x’,0.886,"x^*");
        //gr->Grid("xy","{xA9A9A9}|");
        gr->Box();                 //some plotting
        gr->Axis();                //draw axis
        //gr->Adjust();
        if (SelectMode)
            gr->Tens(X, Y, C, "-2");      // "b" is colour ??
        else    
            gr->Plot(X, Y, "{x6495ED}-2");      // "b" is colour ??
        //gr->Plot(X, Y, "{x800000}-2");      // "marron" is colour ??
        
        gr->Line(mglPoint(X.a[0],0.0), mglPoint(X.a[nX-1],0.0), "r2|");
        for (int ik=1; ik<nk-1; ik++)
        {
            mreal xpos = (mreal)sec30->ArraysOf1DDouble[0][ik];
            gr->Line(mglPoint(xpos, yMin), mglPoint(xpos, yMax), "H2");
        }
        
        gr->SetSize((int)(w*1.5),(int)(h*1.5),false);
        //float max = (float)w;
        //if (h>w) max = (float)h;
        //float w2d=w/max;
        //float h2d=h/max;
        //gr->Aspect(w2d,h2d);
        //gr->Adjust();
        //gr->Puts(mglPoint(0.7, -0.05), strstream.str().c_str());
        gr->EndFrame ();          // end frame
        //gr->WriteFrame ();        // save frame
        
        return 0;
    }
}

int sample(mglGraph *gr,double w, double h)
{
    gr->SetSize(w,h,true);
    mglData y(100);
    mglData x(100);
    for (long j = 0; j < x.nx; j++)
    {
        x.a[j] = (5.0*M_PI*(j)/x.nx+it*0.5);
        y.a[j] = sin(5.0*M_PI*(j)/y.nx+it*0.5);
    }
    
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
    
    gr->Plot(x, y, "{x6495ED}-2");      // "b" is colour ??
    
    //gr->Puts(mglPoint(0.7, -0.05), strstream.str().c_str());
    //gr->EndFrame ();          // end frame
    //gr->WriteFrame ();        // save frame
    return 0;
}

int sampleOK(mglGraph *gr,double w, double h)
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
        
    //int w,h,x,y;
    //w=1600;
    //h=400;
    ////GetClientSize(&w,&h); // size of the picture
    //mglGraph gr(w,h);
    //gr.Alpha(true); // draws something using MathGL
    //gr.Light(true);
    //sample(&gr,(double)w,(double)h);
    ////wxImage img(w,h,(unsigned char *)gr.GetRGB(),true);
    ////return img;
    //    
    //    //const wxImage img(DrawDice(256, i + 1));
    //    
    //    //const wxImage img(w,h,(unsigned char *)gr.GetRGB(),true);
    //    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.GetWidth(), img.GetHeight(),
    //    //             0, GL_RGB, GL_UNSIGNED_BYTE, img.GetData());
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gr.GetWidth(), gr.GetHeight(),
    //                 0, GL_RGB, GL_UNSIGNED_BYTE, gr.GetRGB());
    //                 
    //                 //(unsigned char *)
    ////}

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

void MyGLContext::Draw2D(int w, int h, Sec30* sec30, int MyID)
{
    PlotFigToTexture(w, h, sec30, MyID);
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

void MyGLContext::PlotFigToTexture(int w, int h, Sec30* sec30, int MyID)
{
    //GetClientSize(&w,&h); // size of the picture
    mglGraph gr;
    PlotBand(&gr, w, h, sec30, MyID);
    //sample(&gr, w, h);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gr.GetWidth(), gr.GetHeight(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, gr.GetRGB());
}

void MyGLContext::DrawSelectionFrame(float x1, float y1, float x2, float y2)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(x1, y1, 50.0f);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(x2, y1, 50.0f);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(x2, y2, 50.0f);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(x1, y2, 50.0f);
   glEnd();
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
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

void MyGLContext::Draw_UnitCellBox(float a[3], float b[3], float c[3], float i, float j, float k, GLubyte R, GLubyte G, GLubyte B)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glPushMatrix();
    glColor3ub(R, G, B);
    
    glBegin(GL_QUADS);
    float x0, y0, z0;
    
    x0 = i*a[0] + j*b[0] + k*c[0];
    y0 = i*a[1] + j*b[1] + k*c[1];
    z0 = i*a[2] + j*b[2] + k*c[2];
    
    glVertex3f(x0,y0,z0);
    glVertex3f(x0 + a[0], y0 + a[1], z0 + a[2]);
    glVertex3f(x0 + a[0] + b[0],y0 + a[1] + b[1],z0 + a[2] + b[2]);
    glVertex3f(x0 + b[0],y0 + b[1],z0 + b[2]);
    
    glVertex3f(x0 + b[0],y0 + b[1],z0 + b[2]);
    glVertex3f(x0 + a[0] + b[0],y0 + a[1] + b[1],z0 + a[2] + b[2]);
    glVertex3f(x0 + a[0], y0 + a[1], z0 + a[2]);
    glVertex3f(x0,y0,z0);
    
    glVertex3f(x0,y0,z0);
    glVertex3f(x0 + a[0], y0 + a[1], z0 + a[2]);
    glVertex3f(x0 + a[0] + c[0],y0 + a[1] + c[1],z0 + a[2] + c[2]);
    glVertex3f(x0 + c[0],y0 + c[1],z0 + c[2]);
    
    glVertex3f(x0 + c[0],y0 + c[1],z0 + c[2]);
    glVertex3f(x0 + a[0] + c[0],y0 + a[1] + c[1],z0 + a[2] + c[2]);
    glVertex3f(x0 + a[0], y0 + a[1], z0 + a[2]);
    glVertex3f(x0,y0,z0);
    
    glVertex3f(x0,y0,z0);
    glVertex3f(x0 + b[0], y0 + b[1], z0 + b[2]);
    glVertex3f(x0 + b[0] + c[0],y0 + b[1] + c[1],z0 + b[2] + c[2]);
    glVertex3f(x0 + c[0],y0 + c[1],z0 + c[2]);
    
    glVertex3f(x0 + c[0],y0 + c[1],z0 + c[2]);
    glVertex3f(x0 + b[0] + c[0],y0 + b[1] + c[1],z0 + b[2] + c[2]);
    glVertex3f(x0 + b[0], y0 + b[1], z0 + b[2]);
    glVertex3f(x0,y0,z0);
    
    
    x0 = (i+1)*a[0] + (j+1)*b[0] + (k+1)*c[0];
    y0 = (i+1)*a[1] + (j+1)*b[1] + (k+1)*c[1];
    z0 = (i+1)*a[2] + (j+1)*b[2] + (k+1)*c[2];
    
    glVertex3f(x0,y0,z0);
    glVertex3f(x0 - a[0], y0 - a[1], z0 - a[2]);
    glVertex3f(x0 - a[0] - b[0],y0 - a[1] - b[1],z0 - a[2] - b[2]);
    glVertex3f(x0 - b[0],y0 - b[1],z0 - b[2]);
    
    glVertex3f(x0 - b[0],y0 - b[1],z0 - b[2]);
    glVertex3f(x0 - a[0] - b[0],y0 - a[1] - b[1],z0 - a[2] - b[2]);
    glVertex3f(x0 - a[0], y0 - a[1], z0 - a[2]);
    glVertex3f(x0,y0,z0);
    
    glVertex3f(x0,y0,z0);
    glVertex3f(x0 - a[0], y0 - a[1], z0 - a[2]);
    glVertex3f(x0 - a[0] - c[0],y0 - a[1] - c[1],z0 - a[2] - c[2]);
    glVertex3f(x0 - c[0],y0 - c[1],z0 - c[2]);
    
    glVertex3f(x0 - c[0],y0 - c[1],z0 - c[2]);
    glVertex3f(x0 - a[0] - c[0],y0 - a[1] - c[1],z0 - a[2] - c[2]);
    glVertex3f(x0 - a[0], y0 - a[1], z0 - a[2]);
    glVertex3f(x0,y0,z0);
    
    glVertex3f(x0,y0,z0);
    glVertex3f(x0 - b[0], y0 - b[1], z0 - b[2]);
    glVertex3f(x0 - b[0] - c[0],y0 - b[1] - c[1],z0 - b[2] - c[2]);
    glVertex3f(x0 - c[0],y0 - c[1],z0 - c[2]);
    
    glVertex3f(x0 - c[0],y0 - c[1],z0 - c[2]);
    glVertex3f(x0 - b[0] - c[0],y0 - b[1] - c[1],z0 - b[2] - c[2]);
    glVertex3f(x0 - b[0], y0 - b[1], z0 - b[2]);
    glVertex3f(x0,y0,z0);
    
    glEnd();
    
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
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

void MyGLContext::Draw_Vector(float x0, float y0, float z0, float x1, float y1, float z1, float radius, GLubyte R, GLubyte G, GLubyte B, int Slices, int Stacks)
{
    float ConeHeight = 0.15f;
    float pi180 = 3.14159265/180.0;
    float r = sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) + (z1-z0)*(z1-z0));
    float th = 0;
    if (r<=0)
        th=0;
    else
        th = acos((z1-z0)/r) / pi180;
    float phi = atan2((y1-y0),(x1-x0)) / pi180;
    glPushMatrix();
    glColor3ub(R, G, B);
    glTranslatef(x0, y0, z0);
    glRotatef(phi, 0.0f, 0.0f, 1.0f);
    glRotatef(th, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad, radius, radius, r - ConeHeight, Slices, Stacks);
    glPopMatrix();
    
    glPushMatrix();
    glColor3ub(R, G, B);
    glTranslatef(x1 / r * (r-ConeHeight), y1 / r * (r-ConeHeight), z1 / r * (r-ConeHeight));
    glRotatef(phi, 0.0f, 0.0f, 1.0f);
    glRotatef(th, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad, 0.0f, 2.3f*radius, 0.000001f, Slices, Stacks);
    glPopMatrix();
    
    glPushMatrix();
    glColor3ub(R, G, B);
    glTranslatef(x1 / r * (r-ConeHeight), y1 / r * (r-ConeHeight), z1 / r * (r-ConeHeight));
    glRotatef(phi, 0.0f, 0.0f, 1.0f);
    glRotatef(th, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad, 2.3f*radius, 0.0f, ConeHeight, Slices, Stacks);
    glPopMatrix();
}

//check it
//void cleanup() // call once when you exit program
//{
//  gluDeleteQuadric(qobj);
//}

void MyGLContext::Draw_Lattice(int nColDArray, int* nDArray, double** DArray, int nColIArray, int* nIArray, int** IArray, double Coordinate[3][3])
{
    if (nColDArray == 0) return;
    /***********************************************************************************/
    /* The structure of data: (note that the number of atoms and bonds can be different)
     * DArray[0][:] DArray[1][:] DArray[2][:] DArray[3][:] DArray[4][:] DArray[5][:] DArray[6][:] DArray[7][:] DArray[8][:] DArray[9][:] DArray[10][:] DArray[11][:] DArray[12][:] DArray[13][:] IArray[0][:]   IArray[1][:]   IArray[2][:]  IArray[3][:]   IArray[4][:]  IArray[5][:]  IArray[6][:] IArray[7][:] IArray[8][:]       IArray[9][:]         IArray[10][:]   IArray[11][:]   IArray[12][:]   IArray[13][:]     IArray[14][:]
     *      x0          y0           z0           r0           x1bond0     y1bond0     z1bond0      x2bond0      y2bond0      z2bond0      rbond0          a0             a1            a2        AtomRed0      AtomGreen0     AtomBlue0       BondRed0      BondGreen0    BondBlue0     unitcell0i    unitcell0j  unitcell0k        xyzCoord=0,1          isSelected0        i0              j0               k0          index0InCell000
     *      x1          y1           z1           r1           x1bond1     y1bond1     z1bond1      x2bond1      y2bond1      z2bond1      rbond1          b0             b1            b2        AtomRed1      AtomGreen1     AtomBlue1       BondRed1      BondGreen1    BondBlue1     unitcell1i    unitcell1j  unitcell1k        abcCoord=0,1          isSelected1        i1              j1               k1          index1InCell000
     *      x2          y2           z2           r2           x1bond2     y1bond2     z1bond2      x2bond2      y2bond2      z2bond2      rbond2          c0             c1            c2        AtomRed2      AtomGreen2     AtomBlue2       BondRed2      BondGreen2    BondBlue2     unitcell2i    unitcell2j  unitcell2k      UnitCellMode=0,1,2                         i2              j2               k2          index2InCell000
     *                                                         x1bond3     y1bond3     z1bond3      x2bond3      y2bond3      z2bond3      rbond3                                                                                              BondRed3      BondGreen3    BondBlue3     unitcell3i    unitcell3j  unitcell3k      SelectionFrame=0,1
     *                                                         x1bond4     y1bond4     z1bond4      x2bond4      y2bond4      z2bond4      rbond4                                                                                              BondRed4      BondGreen4    BondBlue4
     */
    /***********************************************************************************/
    float a[3],b[3],c[3];
    a[0] = (float)DArray[11][0];
    a[1] = (float)DArray[12][0];
    a[2] = (float)DArray[13][0];
    b[0] = (float)DArray[11][1];
    b[1] = (float)DArray[12][1];
    b[2] = (float)DArray[13][1];
    c[0] = (float)DArray[11][2];
    c[1] = (float)DArray[12][2];
    c[2] = (float)DArray[13][2];
    
    int xyzCoord = IArray[9][0];
    int abcCoord = IArray[9][1];
    int UnitCellMode = IArray[9][2];
    int SelectionFrame = IArray[9][3];
    
    if (SelectionFrame==1)
    {
        DrawSelectionFrame((float)DArray[14][0], (float)DArray[14][1], (float)DArray[14][2], (float)DArray[14][3]);
    }
    
    GLfloat selectambient[] = { 20.0, 0.0, 0.0, 0.565 };
    GLfloat normalambient[] = { 0.065, 0.065, 0.065, 0.065 };
    for (int i=0; i<nDArray[0]; i++)
    {
        GLubyte Red = 200;
        GLubyte Green = 100;
        GLubyte Blue = 100;
        if (IArray[10][i]==0)
        {
            Red = (GLubyte)IArray[0][i];
            Green = (GLubyte)IArray[1][i];
            Blue = (GLubyte)IArray[2][i];
        }
        else
        {
            glLightfv(GL_LIGHT0, GL_AMBIENT, selectambient);
        }
        Draw_Atom((float)DArray[3][i], (float)DArray[0][i], (float)DArray[1][i], (float)DArray[2][i], Red, Green, Blue, 60, 40);
        glLightfv(GL_LIGHT0, GL_AMBIENT, normalambient);
    }
    
    for (int i=0; i<nDArray[4]; i++)
    {
        if (IArray[3][i] >= 0) //&& IArray[4][i] >= 0 && IArray[5][i] >= 0)
        {
            Draw_Bond((float)DArray[4][i], (float)DArray[5][i], (float)DArray[6][i],(float)DArray[7][i], (float)DArray[8][i], (float)DArray[9][i], (float)DArray[10][i], (GLubyte)IArray[3][i], (GLubyte)IArray[4][i], (GLubyte)IArray[5][i] ,23,2);
        }
    }
    
    //try{}
    //catch(std::exception& ex)
    //{wxMessageBox(ex.what());}

    if (xyzCoord != 0)
    {
        Draw_Vector(0.0f, 0.0f, 0.0f, (float)Coordinate[0][0], (float)Coordinate[0][1], (float)Coordinate[0][2], 0.018f, (GLubyte)255, (GLubyte)0, (GLubyte)0 ,23,2);
        Draw_Vector(0.0f, 0.0f, 0.0f, (float)Coordinate[1][0], (float)Coordinate[1][1], (float)Coordinate[1][2], 0.018f, (GLubyte)0, (GLubyte)255, (GLubyte)0 ,23,2);
        Draw_Vector(0.0f, 0.0f, 0.0f, (float)Coordinate[2][0], (float)Coordinate[2][1], (float)Coordinate[2][2], 0.018f, (GLubyte)0, (GLubyte)0, (GLubyte)255 ,23,2);
    }
    
    if (abcCoord != 0)
    {
        Draw_Vector(0.0f, 0.0f, 0.0f, a[0], a[1], a[2], 0.012f, (GLubyte)175, (GLubyte)50, (GLubyte)50 ,23,2);
        Draw_Vector(0.0f, 0.0f, 0.0f, b[0], b[1], b[2], 0.012f, (GLubyte)50, (GLubyte)175, (GLubyte)50 ,23,2);
        Draw_Vector(0.0f, 0.0f, 0.0f, c[0], c[1], c[2], 0.012f, (GLubyte)50, (GLubyte)50, (GLubyte)175 ,23,2);
    }
    
    if (xyzCoord != 0 || abcCoord != 0) Draw_Atom(0.036f, 0.0f, 0.0f, 0.0f, (GLubyte)0, (GLubyte)0, (GLubyte)0, 30, 20);

    if (UnitCellMode != 0)
    {
        if (UnitCellMode == 1)
        {
            for (int i=0; i<nIArray[6]; i++)
            {
                Draw_UnitCellBox(a, b, c, 0, 0, 0, (GLubyte)0, (GLubyte)0, (GLubyte)0);
            }

        }
        else
        {
            for (int i=0; i<nIArray[6]; i++)
            {
                int icell = IArray[6][i];
                int jcell = IArray[7][i];
                int kcell = IArray[8][i];
                Draw_UnitCellBox(a, b, c, icell, jcell, kcell, (GLubyte)0, (GLubyte)0, (GLubyte)0);
            }
        }
    }
    

}

void MyGLContext::Draw3D(int nColDArray, int* nDArray, double** DArray, int nColIArray, int* nIArray, int** IArray, double Coordinate[3][3], float xMove, float yMove, float XCam, float YCam, float zoom, float zoomCam, float w, float h)
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
    glScaled(ztot*2, ztot*2, ztot*2);//Zoom
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
    /*****************************************************/
    /***********For opacity of Selection Frame************/
    //glEnable(GL_BLEND);
    //glBlendEquation(GL_FUNC_ADD);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glShadeModel(GL_FLAT);
    
    //glEnable(GL_ALPHA_TEST);
    //glAlphaFunc(GL_GREATER,0.5f); // read the doc and tweak to eliminate thin green borders
    //glAlphaFunc(GL_ALWAYS,0.5f);
    //glDepthMask(GL_TRUE);
    /*****************************************************/
    //glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    Draw_Lattice(nColDArray, nDArray, DArray, nColIArray, nIArray, IArray, Coordinate);
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

MyGLCanvas::MyGLCanvas(wxWindow *parent, int DimVar, Sec30* sec30Var, int MyID, int *attribList)
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
    ObjectID = MyID;
    Dim = DimVar;
    sec30 = sec30Var;
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
    
    Coordinate0[0][0] = 1.0;
    Coordinate0[0][1] = 0.0;
    Coordinate0[0][2] = 0.0;
    Coordinate0[1][0] = 0.0;
    Coordinate0[1][1] = 1.0;
    Coordinate0[1][2] = 0.0;
    Coordinate0[2][0] = 0.0;
    Coordinate0[2][1] = 0.0;
    Coordinate0[2][2] = 1.0;
    
    Coordinate1[0][0] = 1.0;
    Coordinate1[0][1] = 0.0;
    Coordinate1[0][2] = 0.0;
    Coordinate1[1][0] = 0.0;
    Coordinate1[1][1] = 1.0;
    Coordinate1[1][2] = 0.0;
    Coordinate1[2][0] = 0.0;
    Coordinate1[2][1] = 0.0;
    Coordinate1[2][2] = 1.0;
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
    
    if ( quadStereoSupported )
    {
        glDrawBuffer( GL_BACK_LEFT );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-0.47f, 0.53f, -0.5f, 0.5f, 1.0f, 3.0f);
        
        if (Dim==3)
            context.Draw3D(NumberOfDoubleArrays, nDoubleArray, DoubleArray1,
                            NumberOfIntArrays, nIntArray, IntArray, Coordinate1,
                            XMove, YMove, XCam, YCam, Zoom, ZoomCam, w3d,h3d);
        else
            context.Draw2D(w, h, sec30, ObjectID);
            
        CheckGLError();
        glDrawBuffer( GL_BACK_RIGHT );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-0.53f, 0.47f, -0.5f, 0.5f, 1.0f, 3.0f);
        
        if (Dim==3)
            context.Draw3D(NumberOfDoubleArrays, nDoubleArray, DoubleArray1,
                            NumberOfIntArrays, nIntArray, IntArray, Coordinate1,
                            XMove, YMove, XCam, YCam, Zoom, ZoomCam, w3d,h3d);
        else
            context.Draw2D(w, h, sec30, ObjectID);
            
        CheckGLError();
    }
    else
    {
        if (Dim==3)
            context.Draw3D(NumberOfDoubleArrays, nDoubleArray, DoubleArray1,
                            NumberOfIntArrays, nIntArray, IntArray, Coordinate1,
                            XMove, YMove, XCam, YCam, Zoom, ZoomCam, w3d,h3d);
        else
            context.Draw2D(w, h, sec30, ObjectID);
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
    //float delta = 0.01*0.01f*event.GetWheelDelta(); //Constant delta
    if (Dim==3)
    {
        float delta = (ZoomCam*0.1)*0.01f*event.GetWheelDelta(); //Zoom dependent delta (It seems better)
        if (scrldwn)
            ZoomCam = ZoomCam + delta;
        else
            ZoomCam = ZoomCam - delta;
        if (ZoomCam <=0.001) ZoomCam=0.001;
    }
    else if(Dim==2)
    {
        bool isBandLoaded = false;
        if (sec30->ArraysOf0DInt[0] != 0) isBandLoaded = true;
        {
            double y1, y2;
            if (ObjectID == 0)
            {
                y1 = sec30->ArraysOf0DDouble[1];
                y2 = sec30->ArraysOf0DDouble[2];
            }
            else if (ObjectID == 1)
            {
                y1 = sec30->ArraysOf0DDouble[3];
                y2 = sec30->ArraysOf0DDouble[4];
            }
            
            double y0 = (y2 + y1) / 2.0;
            double r = (y2 - y1) / 2.0;
            float delta = (r*0.1)*0.01f*event.GetWheelDelta(); //Zoom dependent delta (It seems better)
            if (scrldwn)
                r = r + delta;
            else
                r = r - delta;
            if (r <=0.002) r=0.002;
            
            if (ObjectID == 0)
            {
                sec30->ArraysOf0DDouble[1] = y0 - r;
                sec30->ArraysOf0DDouble[2] = y0 + r;
            }
            else if (ObjectID == 1)
            {
                sec30->ArraysOf0DDouble[3] = y0 - r;
                sec30->ArraysOf0DDouble[4] = y0 + r;
            }
        }
    }
    
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
    if (Dim == 3)
    {
        ShowSelectionFrame = false;
        IntArray[9][3] = 0; //SelectionFrame=false
    }
    const wxPoint cpt = event.GetPosition();
    ClientMouseX0 = cpt.x;
    ClientMouseY0 = cpt.y;
    //To get mouse position relative to top-left corner of current window or canvas, add this in a mouse event handler:
    //const wxPoint pt = wxGetMousePosition();
    //int mouseX = pt.x - this->GetScreenPosition().x;
    //int mouseY = pt.y - this->GetScreenPosition().y;
}

void MyGLCanvas::OnMouseLeftUp(wxMouseEvent& event)
{
    const wxPoint pt = wxGetMousePosition();
    mouseX = pt.x;
    mouseY = pt.y;
    isMouseLeftDown = false;
    if (Dim == 3)
    {
        if (mouseY==mouseY0 && mouseX==mouseX0)
        {
            const wxSize ClientSize = GetClientSize();
            int w,h;
            w=ClientSize.x;
            h=ClientSize.y;
            float max = (float)w;
            if (h>w) max = (float)h;
            float w3d=w/max;
            float h3d=h/max;
            const wxPoint pt0 = event.GetPosition();
            float x = (float)(w3d*pt0.x/w - w3d/2.0f);
            float y = -(float)(h3d*pt0.y/h - h3d/2.0f);
            int AtomIndex[1];
            AtomIndex[0] = RayTraceGetAtomIndex(x, y);
            if (AtomIndex[0] != -1)
            {
                if (event.CmdDown())
                    AddToSelectionList(1, AtomIndex, false, false);
                else if (event.AltDown())
                    AddToSelectionList(1, AtomIndex, false, true);
                else
                    AddToSelectionList(1, AtomIndex, true, false);
            }
            else
                AddToSelectionList(0, AtomIndex, true, true);
            //wxMessageBox(_("Atom index : ") + wxString::Format(wxT("(%d,%d)"), i000, sh000) + _(" in cell(0,0,0) and ") + wxString::Format(wxT("(%d,%d)"), ilmn, shlmn) + _(" in cell") + listucell + _(" in your TB model."),_("Error"));
            //wxMessageBox(_("Atom index : ") + wxString::Format(wxT("%d"), AtomIndex[0]),_("Info"));
        }
        else if (ShowSelectionFrame)
        {
            ShowSelectionFrame = false;
            IntArray[9][3] = 0; //SelectionFrame=false
            
            int* AtomIndex;
            int nSelected = 0;
            FrameGetAtomIndex(nSelected, AtomIndex);
            
            if (nSelected != 0)
            {
                if (event.CmdDown())
                    AddToSelectionList(nSelected, AtomIndex, false, false);
                else if (event.AltDown())
                    AddToSelectionList(nSelected, AtomIndex, false, true);
                else
                    AddToSelectionList(nSelected, AtomIndex, true, false);
                
                delete [] AtomIndex;
            }
            else
                AddToSelectionList(nSelected, AtomIndex, true, true);
        }
        else
            Reload();
    }
    else //if (Dim == 2)
    {
        
    }
}

void MyGLCanvas::OnMouseMove(wxMouseEvent& event)
{
    if (isMouseLeftDown)
    {
        const wxPoint pt = wxGetMousePosition();
        mouseX = pt.x;
        mouseY = pt.y;
        const wxPoint cpt = event.GetPosition();
        ClientMouseX = cpt.x;
        ClientMouseY = cpt.y;
        float l=0;
        float m=0;
        float value=0;
        GetDirection(mouseX0, mouseY0, mouseX, mouseY, l, m, value);
        if (Dim == 3)
        {
            ShowSelectionFrame = false;
            IntArray[9][3] = 0; //SelectionFrame=false
            if (isSelectMode)
                DoSelect(ClientMouseX0, ClientMouseY0, ClientMouseX, ClientMouseY);
            if (isMoveMode)
                DoMove(l,m);
            else if (isRotationMode)
                DoRotate(l,m,(float)(0.01*value));
            else if (isZoomMode)
                DoZoom(0.0005*(m-l));
        }
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
        if (Dim == 3) DoZoom(0.0005*(m-l));
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
        if (Dim==3) DoMove(l,m);
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
    if (Dim == 3)
    {
        ShowSelectionFrame = false;
        IntArray[9][3] = 0; //SelectionFrame=false
    }
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
    if (Dim == 3)
    {
        ShowSelectionFrame = false;
        IntArray[9][3] = 0; //SelectionFrame=false
    }
}

void MyGLCanvas::OnMouseMiddleUp(wxMouseEvent& event)
{
    isMouseMiddleDown = false;
    Reload();
}

void MyGLCanvas::OnSaveRasterImage(wxCommandEvent &WXUNUSED(event))
{
    
}

void MyGLCanvas::DoSelect(float x1, float y1, float x2, float y2)
{
    const wxSize ClientSize = GetClientSize();
    int w,h;
    w=ClientSize.x;
    h=ClientSize.y;
    float max = (float)w;
    if (h>w) max = (float)h;
    float w3d=w/max;
    float h3d=h/max;
    
    ShowSelectionFrame = true;
    IntArray[9][3] = 1; //SelectionFrame=true
    
    SelectionFramX1 = (x1*w3d/w - w3d/2.0f  - XCam/2.0)/ZoomCam;
    SelectionFramY1 = -(y1*h3d/h - h3d/2.0f + YCam/2.0)/ZoomCam;
    SelectionFramX2 = (x2*w3d/w - w3d/2.0f  - XCam/2.0)/ZoomCam;
    SelectionFramY2 = -(y2*h3d/h - h3d/2.0f + YCam/2.0)/ZoomCam;
    
    DoubleArray1[14][0] = fmin(SelectionFramX1,SelectionFramX2);
    DoubleArray1[14][1] = fmin(SelectionFramY1,SelectionFramY2);
    DoubleArray1[14][2] = fmax(SelectionFramX1,SelectionFramX2);
    DoubleArray1[14][3] = fmax(SelectionFramY1,SelectionFramY2);
    
    Refresh(true);
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
    
    double a,b,bc,zs;
    for (int i=0; i<3; i++)
    {
        a = (m*Coordinate0[i][0] - l*Coordinate0[i][1])/r2;
        b = l*Coordinate0[i][0] + m*Coordinate0[i][1];
        bc = b*cr2;
        zs = Coordinate0[i][2]*sr2;
        Coordinate1[i][0] = m*a + l*bc - l*r*zs;
        Coordinate1[i][1] = -l*a + m*bc - m*r*zs;
        Coordinate1[i][2] = Coordinate0[i][2]*c + b*sr;
    }
    
    for (int i=0; i<nDoubleArray[0]; i++)
    {
        a = (m*DoubleArray0[0][i] - l*DoubleArray0[1][i])/r2;
        b = l*DoubleArray0[0][i] + m*DoubleArray0[1][i];
        bc = b*cr2;
        zs = DoubleArray0[2][i]*sr2;
        DoubleArray1[0][i] = m*a + l*bc - l*r*zs;
        DoubleArray1[1][i] = -l*a + m*bc - m*r*zs;
        DoubleArray1[2][i] = DoubleArray0[2][i]*c + b*sr;
    }
    
    for (int i=0; i<nDoubleArray[4]; i++)
    {
        a = (m*DoubleArray0[4][i] - l*DoubleArray0[5][i])/r2;
        b = l*DoubleArray0[4][i] + m*DoubleArray0[5][i];
        bc = b*cr2;
        zs = DoubleArray0[6][i]*sr2;
        DoubleArray1[4][i] = m*a + l*bc - l*r*zs;
        DoubleArray1[5][i] = -l*a + m*bc - m*r*zs;
        DoubleArray1[6][i] = DoubleArray0[6][i]*c + b*sr;
    }
    
    for (int i=0; i<nDoubleArray[7]; i++)
    {
        a = (m*DoubleArray0[7][i] - l*DoubleArray0[8][i])/r2;
        b = l*DoubleArray0[7][i] + m*DoubleArray0[8][i];
        bc = b*cr2;
        zs = DoubleArray0[9][i]*sr2;
        DoubleArray1[7][i] = m*a + l*bc - l*r*zs;
        DoubleArray1[8][i] = -l*a + m*bc - m*r*zs;
        DoubleArray1[9][i] = DoubleArray0[9][i]*c + b*sr;
    }
    
    for (int i=0; i<nDoubleArray[11]; i++)
    {
        a = (m*DoubleArray0[11][i] - l*DoubleArray0[12][i])/r2;
        b = l*DoubleArray0[11][i] + m*DoubleArray0[12][i];
        bc = b*cr2;
        zs = DoubleArray0[13][i]*sr2;
        DoubleArray1[11][i] = m*a + l*bc - l*r*zs;
        DoubleArray1[12][i] = -l*a + m*bc - m*r*zs;
        DoubleArray1[13][i] = DoubleArray0[13][i]*c + b*sr;
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
        int nn = nIntArray[i];
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

void MyGLCanvas::RotationMatrix(double Theta, double lmn[3][3])
{
    double l = Coordinate0[2][0];
    double m = Coordinate0[2][1];
    double n = Coordinate0[2][2];
    if (n >=0.0 && n<0.0000001)
    {
        n=0.0000001;
    }
    if (n <0.0 && n>-0.0000001)
    {
        n=-0.0000001;
    }
    if (n>0.9999999)
    {
        l=0.0000001;
        m=0.0000001;
        n=0.9999999;
    }
    if (n<-0.9999999)
    {
        l=0.0000001;
        m=0.0000001;
        n=-0.9999999;
    }
    double lmnnorm = sqrt(l*l + m*m + n*n);
    l = l/lmnnorm;
    m = m/lmnnorm;
    n = n/lmnnorm;
    lmn[0][0] = (n*(m*cos(Theta) + l*n*sin(Theta)))/(sqrt(n*n)*sqrt(1.0 - n*n));
    lmn[1][0] = (n*(-(l*cos(Theta)) + m*n*sin(Theta)))/(sqrt(n*n)*sqrt(1.0 - n*n));
    lmn[2][0] = -((n*sqrt(1.0 - n*n)*sin(Theta))/sqrt(n*n));
    lmn[0][1] = (sqrt(n*n)*(l*n*cos(Theta) - m*sin(Theta)))/(n*sqrt(1 - n*n));
    lmn[1][1] = (sqrt(n*n)*(m*n*cos(Theta) + l*sin(Theta)))/(n*sqrt(1 - n*n));
    lmn[2][1] = -((n*sqrt(1 - n*n)*cos(Theta))/sqrt(n*n));
    lmn[0][2] = l;
    lmn[1][2] = m;
    lmn[2][2] = n;
}

void MyGLCanvas::LoadToCanvas()
{
    double Theta = 0.0;
    double lmn[3][3] = {0,0,0,0,0,0,0,0,0};
    RotationMatrix(Theta, lmn);
    double X1[3] = {lmn[0][0],lmn[1][0],lmn[2][0]};
    double CosTheta = Coordinate0[0][0]*X1[0] + Coordinate0[0][1]*X1[1] + Coordinate0[0][2]*X1[2];
    double direct[3] = {-Coordinate0[0][1]*X1[2] + X1[1]*Coordinate0[0][2], Coordinate0[0][0]*X1[2] - X1[0]*Coordinate0[0][2], -Coordinate0[0][0]*X1[1] + X1[0]*Coordinate0[0][1]};
    double CosTheta2 = Coordinate0[2][0]*direct[0] + Coordinate0[2][1]*direct[1] + Coordinate0[2][2]*direct[2];
    if (CosTheta2 > 0)
        Theta = acos(CosTheta);
    else
        Theta = -acos(CosTheta);
    RotationMatrix(Theta, lmn);
    
    for (int i=0; i<=2; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray1[i][j] = lmn[i][0] * DoubleArray[0][j] + lmn[i][1] * DoubleArray[1][j] + lmn[i][2] * DoubleArray[2][j];
            
    for (int i=3; i<=3; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray1[i][j] = DoubleArray[i][j];
    
    for (int i=4; i<=6; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray1[i][j] = lmn[i - 4][0] * DoubleArray[4][j] + lmn[i - 4][1] * DoubleArray[5][j] + lmn[i - 4][2] * DoubleArray[6][j];
    
    for (int i=7; i<=9; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray1[i][j] = lmn[i - 7][0] * DoubleArray[7][j] + lmn[i - 7][1] * DoubleArray[8][j] + lmn[i - 7][2] * DoubleArray[9][j];
    
    for (int i=10; i<=10; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray1[i][j] = DoubleArray[i][j];
            
    for (int i=11; i<=13; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray1[i][j] = lmn[i - 11][0] * DoubleArray[11][j] + lmn[i - 11][1] * DoubleArray[12][j] + lmn[i - 11][2] * DoubleArray[13][j];  
    
    for (int i=14; i<NumberOfDoubleArrays; i++)
        for (int j=0; j<nDoubleArray[i]; j++)
            DoubleArray1[i][j] = DoubleArray[i][j];
    
    Reload();
}

void MyGLCanvas::Reload()
{
    if (Dim==3)
    {
        XCam += XMove;
        YCam += YMove;
        ZoomCam += Zoom;
        if (ZoomCam <=0.001) ZoomCam=0.001;
        XMove = 0;
        YMove = 0;
        Zoom = 0;
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                Coordinate0[i][j] = Coordinate1[i][j];
        
        for (int i=0; i<NumberOfDoubleArrays; i++)
            for (int j=0; j<nDoubleArray[i]; j++)
                DoubleArray0[i][j] = DoubleArray1[i][j];
    }
}

int MyGLCanvas::RayTraceGetAtomIndex(float x, float y)
{
    std::list<int> InRayTrace;
    std::list<int>::iterator it;
    int AtomIndex = -1;
    for (int i=0; i<nDoubleArray[0]; i++)
    {
        float xi = (float)DoubleArray0[0][i];
        float yi = (float)DoubleArray0[1][i];
        float ri = (float)DoubleArray0[3][i];
        if ((x-xi*ZoomCam-XCam/2.0)*(x-xi*ZoomCam-XCam/2.0) + (y-yi*ZoomCam-YCam/2.0)*(y-yi*ZoomCam-YCam/2.0) < ri*ri*ZoomCam*ZoomCam)
        {
            //it = InRayTrace.end();
            InRayTrace.push_back(i);
        }
    }
    
    int nlist = InRayTrace.size();
    if (nlist > 0)
    {
        it = InRayTrace.begin();
        double zmax = DoubleArray0[2][*it];
        AtomIndex = *it;
        for (int i = 1; i < nlist; i++)
        {
            *it++;
            if (DoubleArray0[2][*it] > zmax)
            {
                zmax = DoubleArray0[2][*it];
                AtomIndex = *it;
            }
        }
    }
    
    return AtomIndex;
}

void MyGLCanvas::FrameGetAtomIndex(int &nList, int* &List)
{
    float x1 = (float)DoubleArray1[14][0];
    float y1 = (float)DoubleArray1[14][1];
    float x2 = (float)DoubleArray1[14][2];
    float y2 = (float)DoubleArray1[14][3];
    float X1 = x1*ZoomCam+XCam/2.0;
    float Y1 = y1*ZoomCam+YCam/2.0;
    float X2 = x2*ZoomCam+XCam/2.0;
    float Y2 = y2*ZoomCam+YCam/2.0;
    
    std::list<int> SelectedList;
    for (int i=0; i<nDoubleArray[0]; i++)
    {
        float xi = (float)DoubleArray0[0][i];
        float yi = (float)DoubleArray0[1][i];
        float ri = (float)DoubleArray0[3][i];
        
        float X = xi*ZoomCam+XCam/2.0;
        float Y = yi*ZoomCam+YCam/2.0;
        float rad = ri*ZoomCam;
        if ( X > X1 - rad && X < X2 + rad && Y > Y1 - rad && Y < Y2 + rad)
        {
            SelectedList.push_back(i);
        }
    }
    
    nList = SelectedList.size();
    
    if (nList>0)
    {
        List = new int[nList];
        std::list<int>::iterator it;
        int i=-1;
        for(it = SelectedList.begin(); it!=SelectedList.end(); it++)
        {
            i++;
            List[i] = *it;
        }
    }
}

void MyGLCanvas::AddToSelectionList(int nNew, int* indexes, bool ClearList, bool RemoveIndexes)
{
    if (ClearList)
    {
        for (int i=0; i != nIntArray[10];i++)
            IntArray[10][i]=0;
    }
    
    for(int i=0; i<nNew; i++)
    {
        if (RemoveIndexes)
            IntArray[10][indexes[i]] = 0;
        else
            IntArray[10][indexes[i]] = 1;
    }
    
    nSelection=0;
    for (int i=0; i != nIntArray[10];i++)
        if (IntArray[10][i] == 1) nSelection++;
    
    wxCommandEvent* event = new wxCommandEvent(MyOpenGL_EVT_SelectionChanged);
    wxQueueEvent(this->GetParent()->GetParent(),event);
    
    Refresh(true);
}
