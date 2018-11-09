#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <mgl2/mgl.h>
#include <mgl2/glut.h>
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <WX/mdi.h>
#include <wx/msgdlg.h>


/*
#ifdef __WXMAC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef WIN32
#include <unistd.h> // FIXME: ¿This work/necessary in Windows?
                    //Not necessary, but if it was, it needs to be replaced by process.h AND io.h
#endif
*/

int Myi=0;
void orthogonalStart(void);
void orthogonalEnd(void);
int sample0(mglGraph *gr);
int sample2(mglGraph *gr);
void reshape(int w, int h);
void display();
void display2D();
GLuint LoadTexture();
void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
void render();
void displayMe(void);
GLuint texture = 0;
wxGLContext* m_context;
//wxClientDC* dc;
//wxGLCanvas* m_glCanvas17;


MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    BtnMouse->ToggleButton(wxID_RETRY, true);//Rotate
    //tbmodel = new TBModel();
    //tbmodel->nAtoms = 4;
    sec30=new Sec30(this);
    sec30->Connect(Sec30EVT_OnUpdated, wxCommandEventHandler(sec30_OnUpdated), NULL, this);
    this->Connect(MyOpenGL_EVT_SelectionChanged, wxCommandEventHandler(myOpenGL_EVT_SelectionChanged), NULL, this);
    
    /*
    CML::IOData* iod = static_cast<MainFrame*>(mainFrame)->iod;
    int SelectedCalcBoxIndex = iod->SelectedCalcBoxIndex;
    std::list<CML::CalcBox>::iterator cb=iod->CalcBoxs.begin();
    for (int i=0; i < SelectedCalcBoxIndex; i++) cb++;
    
    CML::Atom NewAtom;
    NewAtom.Kind=1;
    NewAtom.x=0;
    NewAtom.y=0;
    NewAtom.z=0;
    std::list<CML::Atom>::iterator atm=cb->UnitCell->Atoms.end();
    cb->UnitCell->Atoms.insert(atm,NewAtom);
    cb->UnitCell->nAtoms++;
    wxString str = wxString::Format(wxT("%02d: %s {%5.4f,%5.4f,%5.4f}"), cb->UnitCell->nAtoms,NewAtom.GetAtomLable(NewAtom.Kind),NewAtom.x,NewAtom.y,NewAtom.z);
    LBAtoms->Append(str);
    */
    
    /*
    std::list<double>::iterator x=tbmodel->XArray.end();
    tbmodel->XArray.insert(x,-0.5);
    tbmodel->XArray.insert(x,0.5);
    tbmodel->XArray.insert(x,0.5);
    tbmodel->XArray.insert(x,-0.5);
    std::list<double>::iterator y=tbmodel->YArray.end();
    tbmodel->YArray.insert(y,-0.5);
    tbmodel->YArray.insert(y,-0.5);
    tbmodel->YArray.insert(y,0.5);
    tbmodel->YArray.insert(y,0.5);
    std::list<double>::iterator z=tbmodel->ZArray.end();
    tbmodel->ZArray.insert(z,0.0);
    tbmodel->ZArray.insert(z,0.0);
    tbmodel->ZArray.insert(z,0.0);
    tbmodel->ZArray.insert(z,0.0);
    std::list<int>::iterator k=tbmodel->KindArray.end();
    tbmodel->KindArray.insert(k,-0.5);
    tbmodel->KindArray.insert(k,0.5);
    tbmodel->KindArray.insert(k,0.5);
    tbmodel->KindArray.insert(k,-0.5);
    */
    
    //Draw_Atom(0.5f, -0.5f, -0.5f, 0.0f, 255, 0, 0, 80, 60);
    //Draw_Atom(0.5f, -0.5f, 0.5f, 0.0f, 0, 255, 0, 80, 60);
    //Draw_Atom(0.5f, 0.5f, 0.5f, 0.0f, 0, 0, 255, 80, 60);
    //Draw_Atom(0.5f, 0.5f, -0.5f, 0.0f, 0, 125, 140, 80, 60);
    
    unsigned int AUI_Flags = wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_ALLOW_ACTIVE_PANE|
    wxAUI_MGR_TRANSPARENT_DRAG|wxAUI_MGR_TRANSPARENT_HINT|wxAUI_MGR_VENETIAN_BLINDS_HINT|
    wxAUI_MGR_RECTANGLE_HINT|wxAUI_MGR_HINT_FADE|wxAUI_MGR_NO_VENETIAN_BLINDS_FADE|
    wxAUI_MGR_LIVE_RESIZE;
    
    aui_mgr.SetFlags(AUI_Flags);
    aui_mgr.SetManagedWindow(mainpanel);
    aui_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE, 1);
    
    wxPanel* CenteralPanel= new wxPanel(mainpanel);
    //CenterPanel->SetBackgroundColour(* wxRED); //Google it to know why it does not work.
    aui_mgr.AddPane(CenteralPanel, wxCENTER);
    aui_mgr.Update();
    
    logfile = new wxTextCtrl(CenteralPanel, -1, _("ready ...\n"),
                                        wxDefaultPosition, wxSize(200,150),
                                        wxNO_BORDER | wxTE_MULTILINE);
    logfile->SetEditable(false);
    logfile->SetBackgroundColour(*wxBLACK);
    logfile->SetForegroundColour(*wxWHITE);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxHORIZONTAL);
    panelSizer1->Add(logfile, 1, wxEXPAND);
    CenteralPanel->SetSizer(panelSizer1);
    
    LoadColorsForm();
    LoadUnitcellPanel();
    LoadStructurePanel();
    LoadOrbitalsPanel();
    LoadBondsPanel();
    LoadProjectionPanel();
    
    MainRibbon->SetActivePage((size_t)0);
    LeftPanel->ChangeSelection(0);
    
    Init_graph3d();
    Init_graph2d0();
    Init_graph2d();
    
    /////////////////////////////////////////////////////////////////////////////////////
    ///////Just to call InsertPane to push old panes (graph2d0 and graph2d) aside////////
    wxPanel* dummy = new wxPanel(CenteralPanel);
    wxAuiPaneInfo inf = wxAuiPaneInfo().Dockable(true).CloseButton(true).Dock().Right();
    aui_mgr.InsertPane(dummy, inf, wxAUI_INSERT_DOCK);
    aui_mgr.ClosePane(aui_mgr.GetPane(dummy));
    aui_mgr.Update();
    /////////////////////////////////////////////////////////////////////////////////////
    
    //wxConfig::Get()->Write(CFG_AUI_PERSPECTIVE, aui_mgr.SavePerspective());
    //SetAppName(wxT("TBModel"));
    //SetVendorName(wxT("CMT Group, Antwerp University, Antwerpen, Belgium."));
    //const wxString perspective = _("layout2|name=0394df705cc5b7dc000000dc00000001;caption=;state=768;dir=5;layer=0;row=0;pos=0;prop=100000;bestw=20;besth=20;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=072d48e05cc5b7de000006ab00000002;caption=Structure;state=12584956;dir=1;layer=0;row=0;pos=0;prop=100000;bestw=800;besth=600;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=072dae405cc5b7de000007ba00000003;caption=Current Band-Structure;state=12584956;dir=2;layer=1;row=0;pos=0;prop=100000;bestw=525;besth=0;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=1426;floaty=329;floatw=541;floath=39|name=072dd1605cc5b7de000008ed00000004;caption=Initial Band-Structure;state=12601340;dir=2;layer=1;row=0;pos=1;prop=100000;bestw=525;besth=0;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=1041;floaty=477;floatw=541;floath=39|dock_size(5,0,0)=22|dock_size(1,0,0)=633|dock_size(2,1,0)=343|");
    //aui_mgr.LoadPerspective(perspective,false);
    
    EvaluateUnitcellPanel();
    // Create the TB Model Class which includes all information about the system
    
    
    //
    
    /*
    unsigned int ntb_Flags = wxAUI_NB_TAB_SPLIT|wxAUI_NB_CLOSE_ON_ACTIVE_TAB|wxAUI_NB_TOP|
    wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_WINDOWLIST_BUTTON|wxAUI_NB_MIDDLE_CLICK_CLOSE|wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_FIXED_WIDTH;
    aui_ntb = new wxAuiNotebook(LeftPanel,wxID_ANY,wxPoint(0,0),wxSize(100,100),ntb_Flags);
    // Set up the sizer for the panel
    wxBoxSizer* panelSizer2 = new wxBoxSizer(wxHORIZONTAL);
    panelSizer2->Add(aui_ntb, 1, wxEXPAND);
    LeftPanel->SetSizer(panelSizer2);
    */
    
    //ShowStartPage();
    
    //wxAuiPaneInfo inf = wxAuiPaneInfo().Dockable(true).TopDockable(true).BottomDockable(true).LeftDockable(true).RightDockable(true).Caption(wxT("Notbook")).BestSize(600,800).Dock();
    //aui_mgr.AddPane(SidePanel,inf);
    //m_ribbonButtonBar528->Connect(wxID_ANY, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrameBaseClass::b2), NULL, this);
    //wxGLAttributes m_glCanvas17Attr = wxGLAttributes().PlatformDefaults().Defaults();
    //m_glCanvas17Attr.PlatformDefaults().Defaults().EndList();
    //bool accepted = wxGLCanvas::IsDisplaySupported(m_glCanvas17Attr);
}

MainFrame::~MainFrame()
{
    aui_mgr.UnInit();
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetCopyright(_("My MainFrame"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Short description goes here"));
    ::wxAboutBox(info);
}


void MainFrame::BtnTest_OnClick(wxCommandEvent& event)
{

}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();
}

void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
	
    /*
     *  Inits the OpenGL viewport for drawing in 2D
     */
	
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glEnable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int w1 = 0;
int h1 = 0;
void reshape(int w, int h)
{
    w1 = w;
    h1 = h;
    glViewport(0, 0, w, h);
}


void orthogonalStart() 
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-w1/2, w1/2, -h1/2, h1/2);
    glMatrixMode(GL_MODELVIEW);
}

void orthogonalEnd()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClearColor (1.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable( GL_TEXTURE_2D );

    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //glutSwapBuffers();
}


GLuint LoadTexture()
{
    unsigned char data[] = { 255,0,0, 0,255,0, 0,0,255, 255,255,255 };

    glGenTextures( 1, &texture ); 
    glBindTexture( GL_TEXTURE_2D, texture ); 
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); 

    //even better quality, but this will do for now.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    //to the edge of our shape. 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0,GL_RGB, GL_UNSIGNED_BYTE, data);
    return texture; //return whether it was successful
}

int sample0(mglGraph *gr)
{
  mglData dat(300);
  Myi++;
    gr->NewFrame ();          // start frame
    gr->Box ();               // some plotting
    gr->Axis ();              // draw axis
    for (long j = 0; j < dat.nx; j++)
      dat.a[j] = sin (M_PI*j/dat.nx+M_PI*Myi);
    gr->Plot(dat, "r|3");      // "b" is colour ??
    gr->EndFrame ();          // end frame
    gr->WriteFrame ();        // save frame
    return 0;
}

/*
int sample2(mglGraph *gr)
{
  mglData dat (300);
  i++;
    gr->NewFrame ();          // start frame
    gr->Box ();               // some plotting
    gr->Axis ();              // draw axis
    for (long j = 0; j < dat.nx; j++)
      dat.a[j] = sin (M_PI*j/dat.nx+M_PI*0.05*i);
    gr->Plot(dat, "r-3");      // "b" is colour ??
    gr->EndFrame ();          // end frame
    gr->WriteFrame ();        // save frame
    return 0;
}
*/

void MainFrame::m_glCanvas17_OnPaint(wxPaintEvent& )
{
    /*int w,h,x,y;
    GetClientSize(&w,&h); // size of the picture
    mglGraph gr(w,h);
    gr.Alpha(true); // draws something using MathGL
    gr.Light(true);
    sample(&gr);
    
    wxImage img(w,h,(unsigned char *)gr.GetRGB(),true);
    m_glCanvas17->GetSize(&x,&y); // gets a height of the toolbar if any
    wxString s = wxString::Format(wxT("%d"), (int)y);
    TextTest->SetLabel(s);
    
    //wxPaintDC((wxWindow*)m_glCanvas17); // only to be used in paint events. use wxClientDC to paint outside the paint event
    
    wxPaintDC dc((wxWindow*)m_glCanvas17); // and draws it
    dc.DrawBitmap(wxBitmap(img),0,0);*/
    
    
    
}

/*
void GLPane::prepareFor2DDrawing()
{
    glViewport(x, y, width, height); // decide which area of the frame will be painted
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height); // set up coordinate system
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void GLPane::prepareFor3DDrawing()
{
    
    glViewport(x, y, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Calculate The Aspect Ratio And Set The Clipping Volume
    if (height == 0) height = 1;
    gluPerspective(45, (float)width/(float)height, 0.1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
*/




    //int w,h,x,y;
    //GetClientSize(&w,&h); // size of the picture
    //mglGraph gr(w,h);
    //gr.Alpha(true); // draws something using MathGL
    //gr.Light(true);
    //sample(&gr);
    //wxImage img(w,h,(unsigned char *)gr.GetRGB(),true);
    

    //TextTest->SetLabel("hello");
    /*mglData dat(30,40); // data to for plotting
    for(long i=0;i<30;i++) for(long j=0;j<40;j++)
    dat.a[i+30*j] = 1/(1+(i-15)*(i-15)/225.+(j-20)*(j-20)/400.);
    mglGraph gr; // class for plot drawing
    gr.Rotate(50,60); // rotate axis
    gr.Light(true); // enable lighting
    gr.Surf(dat); // plot surface
    gr.Cont(dat,"y"); // plot yellow contour lines
    gr.Axis(); // draw axis*/
    
    //mglGraph* gr;
    //gr = new mglGraph();
    //gr->FPlot("sin(pi*x)");
    
    //mglGLUT ggr;
    //ggr.FPlot("sin(pi*x)");
    //ggr.Run();
    
    //mglGLUT gr(sample);
    
    
    //m_context = new wxGLContext(m_glCanvas17);
    //m_context->SetCurrent((const wxGLCanvas&)m_glCanvas17);
    //dc = new wxClientDC((wxWindow*)m_glCanvas17);
    
    
    /*m_glCanvas17->GetSize(&x,&y); // gets a height of the toolbar if any
    wxString s = wxString::Format(wxT("%d"), (int)y);
    TextTest->SetLabel(s);
    dc->DrawBitmap(wxBitmap(img),0,0);*/
    
void MainFrame::MainFrameBaseClass_Resize(wxSizeEvent& event)
{
    this->Layout();
    unitcellPanel->Layout();
    aui_mgr.Update();
}

void MainFrame::MainFrameBaseClass_Move(wxMoveEvent& event)
{
 
}

void MainFrame::test_OnClick(wxCommandEvent& event)
{

}




/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black and opaque
}
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display2D() {
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
 
   // Define shapes enclosed within a pair of glBegin and glEnd
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
      glVertex2f(-0.2f, 0.7f);
      glVertex2f(-0.8f, 0.7f);
 
      glColor3f(0.0f, 1.0f, 0.0f); // Green
      glVertex2f(-0.7f, -0.6f);
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
      glVertex2f(0.7f, 0.4f);
      glVertex2f(0.6f, 0.6f);
      glVertex2f(0.4f, 0.6f);
      glVertex2f(0.3f, 0.4f);
   glEnd();
 
   glFlush();  // Render now
}

void MainFrame::test2D_OnClick(wxCommandEvent& event)
{

    //return 0;
}

void MainFrame::Test3D_OnClick(wxCommandEvent& event)
{

}

void MainFrame::MathGL_test_OnClick(wxCommandEvent& event)
{

}

void MainFrame::RibbonAnalyzeGraph2D_OnClick(wxRibbonButtonBarEvent& event)
{
    
}

void MainFrame::RibbonAnalyzeGraph3D_OnClick(wxRibbonButtonBarEvent& event)
{
    
}

void MainFrame::Btn2D_OnClick(wxRibbonButtonBarEvent& event)
{
    
}


void MainFrame::b1(wxRibbonButtonBarEvent& event)
{
        
}
void MainFrame::b2(wxRibbonButtonBarEvent& event)
{

}
void MainFrame::d1(wxRibbonButtonBarEvent& event)
{
}
void MainFrame::d2(wxRibbonButtonBarEvent& event)
{
}
void MainFrame::b3(wxRibbonButtonBarEvent& event)
{
}
void MainFrame::b4(wxRibbonButtonBarEvent& event)
{
}
void MainFrame::bb1(wxKeyEvent& event)
{
    
}
void MainFrame::bb2(wxKeyEvent& event)
{

}

void MainFrame::B2D(wxRibbonButtonBarEvent& event)
{
    
}

void MainFrame::Btn3D_OnClick(wxRibbonButtonBarEvent& event)
{

}

void MainFrame::B3D(wxRibbonButtonBarEvent& event)
{
    char *myargv [1];
    int myargc=1;myargv [0]=strdup ("Myappname");
    glutInit(&myargc, myargv);          // Initialize GLUT
    glutCreateWindow("Vertex, Primitive & Color");  // Create window with the given title
    glutInitWindowSize(800, 400);   // Set the window's initial width & height
    glutInitWindowPosition(500, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display2D);       // Register callback handler for window re-paint event
    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the event-processing loop
}

void MainFrame::mgl_test(wxRibbonButtonBarEvent& event)
{
    mglGLUT gr(sample0);
    gr.Run();
}

void MainFrame::BtnMain_OnClick(wxRibbonButtonBarEvent& event)
{
    
}

void MainFrame::BtnTerminal_OnClick(wxRibbonButtonBarEvent& event)
{
    
}

void MainFrame::Init_graph3d()
{
    graph3d = new GraphClass(mainpanel,3);
    graph3d->CreateAtomicStructure(sec30);
    aui_mgr.SetDockSizeConstraint(0.333333,0.75);
    aui_mgr.AddPane(graph3d, wxAuiPaneInfo().Gripper(false).Floatable(true).Dockable(true).Caption("Structure").CloseButton(false).MaximizeButton(true).MinimizeButton(true).BestSize(800,600).Dock().Top());
    aui_mgr.Update();
}

void MainFrame::Init_graph2d0()
{
    graph2d0 = new GraphClass(mainpanel,2);
    aui_mgr.AddPane(graph2d0, wxAuiPaneInfo().Gripper(false).Floatable(true).Dockable(true).Caption("Initial Band-Structure").CloseButton(false).MaximizeButton(true).MinimizeButton(true).Dock().Right());
    aui_mgr.Update();
}

void MainFrame::Init_graph2d()
{
    graph2d = new GraphClass(mainpanel,2);
    aui_mgr.AddPane(graph2d, wxAuiPaneInfo().Gripper(false).Floatable(true).Dockable(true).Caption("Current Band-Structure").CloseButton(false).MaximizeButton(true).MinimizeButton(true).Dock().Right());
    aui_mgr.Update();
}

void MainFrame::BtnGrid_OnClick(wxRibbonButtonBarEvent& event)
{
    GridClass* grid = new GridClass(LeftPanel);
    //LeftPanel->AddPage()
    LeftPanel->AddPage(grid,"Data Grid",true);
    LeftPanel->Update();
    //wxSpinCtrlDbl s;
}

void MainFrame::BtnOpen_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Open project"), wxEmptyString, wxEmptyString, 
		_("TBM File (*.tbm)|*.tbm")
        ,wxFD_OPEN, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        sec30->LoadFromFile(dgPath, dgFileName);
	}
 
	OpenDialog->Destroy();
}

void MainFrame::BtnSave_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Save project"), wxEmptyString, wxEmptyString, 
		_("TBM File (*.tbm)|*.tbm")
        ,wxFD_SAVE, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        sec30->SaveToFile(dgPath, dgFileName);
	}
 
	OpenDialog->Destroy();
}

void MainFrame::ClearGraph3D()
{
    graph3d->DiscardAtomicStructure();
    graph3d->Refresh(false);
}

void MainFrame::ShowGraph3D()
{
    graph3d->CreateAtomicStructure(sec30);
    graph3d->Refresh(false);
}

void MainFrame::UpdateGraph3D()
{
    graph3d->DiscardAtomicStructure();
    graph3d->CreateAtomicStructure(sec30);
    graph3d->Refresh(false);
}

/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
void MainFrame::sec30_OnUpdated(wxCommandEvent& event)
{
    int redraw = event.GetInt();
    if (redraw == 1) ClearGraph3D();
    wxString info = event.GetString();
    if (info == _("UnitcellClass"))
        EvaluateUnitcellPanel();
    else if (info == _("StructureClass"))
        EvaluateStructurePanel();
    else if (info == _("OrbitalsClass"))
        EvaluateOrbitalsPanel();
    else if (info == _("BondsClass"))
        EvaluateBondsPanel(redraw);
    else if (info == _("ProjectionClass"))
        EvaluateProjectionPanel(redraw);
    else if (info == _("ColorsClass"))
        EvaluateColorsPanel();
}
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
void MainFrame::myOpenGL_EVT_SelectionChanged(wxCommandEvent& event)
{
    int nList = graph3d->GetSelectedCount();
    int nShowingAtoms = graph3d->GetShowingAtomsCount();
    
    myGrid* gridctr = sec30->GetGridObject(_("KABC_Coords"));
    if (nList < 1)
    {
        int nRow = 0;
        int nCol = 0;
        sec30->GetDim(_("KABC_Coords"), nRow, nCol);
        for (int i=0; i != nShowingAtoms;i++)
            for (int j=0; j != nCol;j++)
                gridctr->SetCellBackgroundColour(i, j, *wxWHITE);
        gridctr->Refresh(true);
        return;
    }
    
    logfile->AppendText(_("\nNumber of selected atoms : ") + wxString::Format(wxT("%d"), nList) + _("\n"));
    int* Atoms = new int[nShowingAtoms];
    graph3d->GetAtoms_Selection(Atoms);
    wxColour c; //Also it is possible to determine the color in this way: wxColour c=*wxGREEN;
    c.Set(170,60,100,0);
    int icell1,jcell1,kcell1,icell2,jcell2,kcell2,i1000,i2000;
    int first = true;
    for (int i=0; i != nShowingAtoms;i++)
    {
        if (Atoms[i] == 1)
        {
            float x=graph3d->glc->DoubleArray[0][i];
            float y=graph3d->glc->DoubleArray[1][i];
            float z=graph3d->glc->DoubleArray[2][i];
            int icell=graph3d->glc->IntArray[11][i];
            int jcell=graph3d->glc->IntArray[12][i];
            int kcell=graph3d->glc->IntArray[13][i];
            int indexcell000=graph3d->glc->IntArray[14][i];
            int kind=graph3d->glc->IntArray[15][i];
            
            logfile->AppendText(wxString::Format(wxT("%s\tIndex: %d\tCell: (%d,%d,%d)\tr = (%.6f,%.6f,%.6f)\n"), sec30->GetAtomLable(kind), indexcell000 + 1, icell, jcell, kcell, x, y, z));
            
            for (int j=0; j != 4;j++)
            {
                gridctr->SetCellBackgroundColour(indexcell000, j, c);
            }
            
            if (nList == 2)
            {
                if (first)
                {
                    first = false;
                    icell1 = icell;
                    jcell1 = jcell;
                    kcell1 = kcell;
                    i1000 = indexcell000;
                }
                else
                {
                    icell2 = icell;
                    jcell2 = jcell;
                    kcell2 = kcell;
                    i2000 = indexcell000;
                }
            }
        }
        else
        {
            for (int j=0; j != 4;j++)
            {
                gridctr->SetCellBackgroundColour(i, j, *wxWHITE);
            }
        }
    }
    
    if (nList == 2)
    {
        int iMyess = icell2 - icell1;
        int jMyess = jcell2 - jcell1;
        int kMyess = kcell2 - kcell1;
        int ind000,indlmn;
        wxCheckTree* treectr = sec30->GetTreeObject(_("Bonds"));
        wxTreeItemId rootID = treectr->GetRootItem();
        
        wxString cellItem1 = wxString::Format(wxT("cell(0,0,0)-cell(%d,%d,%d)"), iMyess, jMyess, kMyess);
        wxTreeItemId lmnID1 = treectr->FindItemIn(rootID,cellItem1);
        
        wxString cellItem2 = wxString::Format(wxT("cell(0,0,0)-cell(%d,%d,%d)"), -iMyess, -jMyess, -kMyess);
        wxTreeItemId lmnID2 = treectr->FindItemIn(rootID,cellItem2);
        
        wxString cellItem;
        wxTreeItemId lmnID;
        bool isfound = false;
        if (lmnID1.IsOk())
        {
            isfound = true;
            cellItem = wxString::Format(wxT("cell(0,0,0)-cell(%d,%d,%d)"), iMyess, jMyess, kMyess);
            lmnID = treectr->FindItemIn(rootID,cellItem);
            ind000 = i1000;
            indlmn = i2000;
        }
        else if (lmnID2.IsOk())
        {
            isfound = true;
            cellItem = wxString::Format(wxT("cell(0,0,0)-cell(%d,%d,%d)"), -iMyess, -jMyess, -kMyess);
            lmnID = treectr->FindItemIn(rootID,cellItem);
            ind000 = i2000;
            indlmn = i1000;
        }
        
        if (isfound)
        {
            wxTreeItemIdValue cookie;
            wxTreeItemId bond = treectr->GetFirstChild(lmnID, cookie);
            
            bool firstbond = true;
            while (bond.IsOk())
            {
                wxString BondInfo = treectr->GetItemText(bond);
                int iAtomIndex,nShellIndex,jAtomIndex,mShellIndex,bondtype;
                graph3d->GetBondInfo(BondInfo, iAtomIndex,nShellIndex,jAtomIndex,mShellIndex,bondtype);
                
                if (iMyess == 0 && jMyess == 0 && kMyess == 0)
                {
                    if (ind000 > indlmn)
                    {
                        int dummy = ind000;
                        ind000 = indlmn;
                        indlmn = dummy;
                    }
                }
                
                if (iAtomIndex == ind000 && jAtomIndex == indlmn)
                {
                    if (firstbond)
                    {
                        logfile->AppendText(_("The tight-binding bonds defined between the atoms:\n"));
                        firstbond = false;
                    }
                    wxString bondinfo = _("[ (i,n)=") + wxString::Format(wxT("(%d,%d)"), iAtomIndex + 1, nShellIndex) + _(" , (j,m)=") + wxString::Format(wxT("(%d,%d)"), jAtomIndex + 1, mShellIndex) + _(" , ") + wxString::Format(wxT("Bond %d"), bondtype) + _(" ]");
                    logfile->AppendText(bondinfo + _("\n"));
                }
                
                bond = treectr->GetNextSibling(bond);
            }
        }
    }
    
    gridctr->Refresh(true);
    delete [] Atoms;
}
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
void MainFrame::LoadUnitcellPanel()
{
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    LeftPanel->AddPage(scrolledwindow,"Unit Cell",true);
    LeftPanel->Update();
    
    unitcellPanel = new UnitcellClass(scrolledwindow,sec30);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxVERTICAL);
    panelSizer1->Add(unitcellPanel, 1, wxEXPAND);
    scrolledwindow->SetSizer(panelSizer1);
    
    scrolledwindow->FitInside();
    scrolledwindow->SetScrollRate(-1,15);
    unitcellPanel->graph3d = graph3d;
}

void MainFrame::LoadStructurePanel()
{
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    LeftPanel->AddPage(scrolledwindow,"Structure",true);
    LeftPanel->Update();
    
    structurePanel = new StructureClass(scrolledwindow,sec30);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxVERTICAL);
    panelSizer1->Add(structurePanel, 1, wxEXPAND);
    scrolledwindow->SetSizer(panelSizer1);
    
    scrolledwindow->FitInside();
    scrolledwindow->SetScrollRate(-1,15);
    structurePanel->graph3d = graph3d;
}

void MainFrame::LoadOrbitalsPanel()
{
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    LeftPanel->AddPage(scrolledwindow,"Orbitals",true);
    LeftPanel->Update();
    
    orbitalsPanel = new OrbitalsClass(scrolledwindow,sec30);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxVERTICAL);
    panelSizer1->Add(orbitalsPanel, 1, wxEXPAND);
    scrolledwindow->SetSizer(panelSizer1);
    
    scrolledwindow->FitInside();
    scrolledwindow->SetScrollRate(-1,15);
    orbitalsPanel->graph3d = graph3d;
}

void MainFrame::LoadBondsPanel()
{
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    LeftPanel->AddPage(scrolledwindow,"Bonds",true);
    LeftPanel->Update();
    
    bondsPanel = new BondsClass(scrolledwindow,sec30);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxVERTICAL);
    panelSizer1->Add(bondsPanel, 1, wxEXPAND);
    scrolledwindow->SetSizer(panelSizer1);
    
    scrolledwindow->FitInside();
    scrolledwindow->SetScrollRate(-1,15);
    bondsPanel->graph3d = graph3d;
}

void MainFrame::LoadProjectionPanel()
{
    /*
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    LeftPanel->AddPage(scrolledwindow,"Projection",true);
    LeftPanel->Update();
    
    projectionPanel = new ProjectionClass(scrolledwindow,sec30);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxVERTICAL);
    panelSizer1->Add(projectionPanel, 1, wxEXPAND);
    scrolledwindow->SetSizer(panelSizer1);
    
    scrolledwindow->FitInside();
    scrolledwindow->SetScrollRate(-1,15);
    projectionPanel->graph3d = graph3d;
     */
}

void MainFrame::LoadColorsForm()
{
    ColorsForm = new ColorsClass(this, sec30);
}
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
void MainFrame::EvaluateUnitcellPanel()
{
    wxListBox* eunitcellsctr = sec30->GetListObject( _("EssentialUnitcellList"));
    eunitcellsctr->Clear();
    if (ValidateUnitCellPanel()) EvaluateStructurePanel();
}

void MainFrame::EvaluateStructurePanel()
{
    wxListBox* eunitcellsctr = sec30->GetListObject( _("EssentialUnitcellList"));
    eunitcellsctr->Clear();
    if (ValidateStructurePanel())
    {
        FillBondsPanel();
        EvaluateBondsPanel(1);
    }
}

void MainFrame::EvaluateOrbitalsPanel()
{
    if (ValidateOrbitalsPanel()) ShowGraph3D();
}

void MainFrame::EvaluateBondsPanel(int redraw)
{
    if (ValidateBondsPanel())
    {
        wxButton* btnctr =  sec30->GetButtonObject(_("PickAtomBtn"));
        if (btnctr->GetForegroundColour() == *wxRED)
        {
            int n = graph3d->GetSelectedCount();
            if (n == 2)
            {
                int nShowingAtoms = graph3d->GetShowingAtomsCount();
                int* Atoms = new int[nShowingAtoms];
                graph3d->GetAtoms_Selection(Atoms);
                int icell1,jcell1,kcell1,icell2,jcell2,kcell2,i1000,i2000;
                int first = true;
                for (int i=0; i != nShowingAtoms;i++)
                {
                    if (Atoms[i] == 1)
                    {
                        int icell=graph3d->glc->IntArray[11][i];
                        int jcell=graph3d->glc->IntArray[12][i];
                        int kcell=graph3d->glc->IntArray[13][i];
                        int indexcell000=graph3d->glc->IntArray[14][i];
                
                        if (first)
                        {
                            first = false;
                            icell1 = icell;
                            jcell1 = jcell;
                            kcell1 = kcell;
                            i1000 = indexcell000;
                        }
                        else
                        {
                            icell2 = icell;
                            jcell2 = jcell;
                            kcell2 = kcell;
                            i2000 = indexcell000;
                        }
                    }
                }
                
                delete [] Atoms;
                int iMyess = icell2 - icell1;
                int jMyess = jcell2 - jcell1;
                int kMyess = kcell2 - kcell1;
                int ind000,indlmn;
                bool plusFound=false;
                bool minusFound=false;
                int plusEssInd = -1;
                int minusEssInd = -1;
                wxListBox* esslistctr= sec30->GetListObject(_("EssentialUnitcellList"));
                int nesslist = esslistctr->GetCount();
                int EssInd = -1;
                
                wxString cellItem1 = wxString::Format(wxT("(%d,%d,%d)"), iMyess, jMyess, kMyess);
                for (int ii=0; ii!=nesslist; ii++)
                {
                    plusEssInd++;
                    wxString item = esslistctr->GetString(ii);
                    if(item.CompareTo(cellItem1) == 0 ) {plusFound = true; break;}
                }
                
                wxString cellItem2 = wxString::Format(wxT("(%d,%d,%d)"), -iMyess, -jMyess, -kMyess);
                for (int ii=0; ii!=nesslist; ii++)
                {
                    minusEssInd++;
                    wxString item = esslistctr->GetString(ii);
                    if(item.CompareTo(cellItem2) == 0 ) {minusFound = true; break;}
                }
                
                wxString cellItem;
                wxTreeItemId lmnID;
                if (plusFound)
                {
                    ind000 = i1000;
                    indlmn = i2000;
                    EssInd = plusEssInd;
                }
                else if (minusFound)
                {
                    ind000 = i2000;
                    indlmn = i1000;
                    EssInd = minusEssInd;
                }
                else
                    wxMessageBox(_("You can not set a bond between these atoms. You should extend the\nNearest-Neighbor Unit-Cell of the TB model in Structure tab."),_("Error"));
                
                if (plusFound & minusFound)
                {
                    if (ind000 > indlmn)
                    {
                        int dummy = ind000;
                        ind000 = indlmn;
                        indlmn = dummy;
                    }
                }
                
                if (plusFound || minusFound)
                {
                    esslistctr->SetSelection(EssInd);
                    sec30->SetVar(_("AtomIndex1[0]"), ind000 + 1, false);
                    sec30->SetVar(_("AtomIndex2[0]"), indlmn + 1, false);
                    
                    sec30TextCtrl* ctr1= sec30->GetTextCtrlObject(_("AtomIndex1[0]"));
                    sec30TextCtrl* ctr2= sec30->GetTextCtrlObject(_("AtomIndex2[0]"));
                    
                    btnctr->SetForegroundColour(*wxGREEN);
                }
            }
            else
                wxMessageBox(_("Please select the two atoms you are going to make a bond between them."),_("Error"));
        }
        else
            btnctr->SetForegroundColour(*wxBLACK);
        
        if (redraw == 1) ShowGraph3D();
    }
}

void MainFrame::EvaluateProjectionPanel(int redraw)
{
    if (ValidateProjectionPanel()) ShowGraph3D();
}

void MainFrame::EvaluateColorsPanel()
{
    if (ValidateColorsPanel()) ShowGraph3D();
}
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
bool MainFrame::ValidateUnitCellPanel()
{
    bool isValid = true;
    int AtomCnt = 0;
    double A, B, C;
    double a[3], b[3], c[3];
    double astrain, bstrain, cstrain;
    double x, y, z;
    int kind;
    int nRow = 0;
    int nCol = 0;
    sec30->GetDim(_("KABC_Coords"), nRow, nCol);
    
    isValid = isValid && sec30->GetVar(_("a[0]"), a[0]);
    isValid = isValid && sec30->GetVar(_("a[1]"), a[1]);
    isValid = isValid && sec30->GetVar(_("a[2]"), a[2]);
    isValid = isValid && sec30->GetVar(_("b[0]"), b[0]);
    isValid = isValid && sec30->GetVar(_("b[1]"), b[1]);
    isValid = isValid && sec30->GetVar(_("b[2]"), b[2]);
    isValid = isValid && sec30->GetVar(_("c[0]"), c[0]);
    isValid = isValid && sec30->GetVar(_("c[1]"), c[1]);
    isValid = isValid && sec30->GetVar(_("c[2]"), c[2]);
    
    isValid = isValid && sec30->GetVar(_("astrain[0]"), astrain);
    isValid = isValid && sec30->GetVar(_("bstrain[0]"), bstrain);
    isValid = isValid && sec30->GetVar(_("cstrain[0]"), cstrain);
    for (int i0=0; i0<3; i0++)
    {
        a[i0]=a[i0]*astrain;
        b[i0]=b[i0]*bstrain;
        c[i0]=c[i0]*cstrain;
    }
    
    int i=-1;
    bool isLineValid=true;
    while (i<nRow && isLineValid)
    {
        i++;
        isLineValid = sec30->GetVar(_("KABC_Coords"), i, 0, kind);
        isLineValid = isLineValid && sec30->GetVar(_("KABC_Coords"), i, 1, A);
        isLineValid = isLineValid && sec30->GetVar(_("KABC_Coords"), i, 2, B);
        isLineValid = isLineValid && sec30->GetVar(_("KABC_Coords"), i, 3, C);
        
        if (isLineValid)
        {
            AtomCnt++;
            x = A * a[0] + B * b[0] + C * c[0];
            y = A * a[1] + B * b[1] + C * c[1];
            z = A * a[2] + B * b[2] + C * c[2];
            sec30->SetVar(_("XYZ_Coords"), i, 0, x, false);
            sec30->SetVar(_("XYZ_Coords"), i, 1, y, false);
            sec30->SetVar(_("XYZ_Coords"), i, 2, z, false);
        }
    }
    
    sec30->SetVar(_("nAtoms[0]"),AtomCnt,false);
    
    myGrid* gridctr = sec30->GetGridObject(_("KABC_Coords"));
    for (int i=0; i != nRow;i++)
        for (int j=0; j != nCol;j++)
            gridctr->SetCellBackgroundColour(i, j, *wxWHITE);
    gridctr->Refresh(true);
    
    return isValid;
     
    //To learn
    //AtomsGrid->SetCellTextColour(3, 3, *wxGREEN);
    //AtomsGrid->SetCellBackgroundColour(3, 3, *wxLIGHT_GREY);
}

bool MainFrame::ValidateStructurePanel()
{
    bool isValid = true;
    bool CustomViewmode,TBViewmode,TBEssentialViewmode;
    sec30->GetRadioVar(_("CustomViewmode[0]"),CustomViewmode);
    sec30->GetRadioVar(_("TBViewmode[0]"),TBViewmode);
    sec30->GetRadioVar(_("TBEssentialViewmode[0]"),TBEssentialViewmode);

    int ma[2],mb[2],mc[2],TBl,TBm,TBn;
    isValid = isValid && sec30->GetVar(_("ma[0]"), ma[0]);
    isValid = isValid && sec30->GetVar(_("ma[1]"), ma[1]);
    isValid = isValid && sec30->GetVar(_("mb[0]"), mb[0]);
    isValid = isValid && sec30->GetVar(_("mb[1]"), mb[1]);
    isValid = isValid && sec30->GetVar(_("mc[0]"), mc[0]);
    isValid = isValid && sec30->GetVar(_("mc[1]"), mc[1]);
    isValid = isValid && sec30->GetVar(_("TBl[0]"), TBl);
    isValid = isValid && sec30->GetVar(_("TBm[0]"), TBm);
    isValid = isValid && sec30->GetVar(_("TBn[0]"), TBn);

    return isValid;
}

bool MainFrame::ValidateOrbitalsPanel()
{
    bool isValid = true;
    
    wxCheckTree* treectr = sec30->GetTreeObject(_("Orbitals"));
    
    int cnt=0;
	std::stack<wxTreeItemId> items;
	if (treectr->GetRootItem().IsOk())
    {
		items.push(treectr->GetRootItem());
    }

	while (!items.empty())
	{
		wxTreeItemId next = items.top();
		items.pop();
        
		wxTreeItemIdValue cookie;
		wxTreeItemId nextChild = treectr->GetFirstChild(next, cookie);
		while (nextChild.IsOk())
		{
			items.push(nextChild);
            wxString itemtext = treectr->GetItemText(nextChild);
            if (itemtext.Contains(_("Shell"))) cnt++;
			nextChild = treectr->GetNextSibling(nextChild);
		}
	}
    
    sec30->SetVar(_("nShells[0]"),cnt, false);
    
    
    return isValid;
}

bool MainFrame::ValidateBondsPanel()
{
    bool isValid = true;
    bool WorkingViewmode;
    sec30->GetRadioVar(_("WorkingViewmode[0]"),WorkingViewmode);
    return isValid;
}

bool MainFrame::ValidateProjectionPanel()
{
    bool isValid = true;

    return isValid;
}

bool MainFrame::ValidateColorsPanel()
{
    bool isValid = true;
    
    return isValid;
}
/****************************************************************************************************************************************************************/
void MainFrame::OnchoisSelected(wxCommandEvent& event)
{
}

bool MainFrame::isItNew(int i,int j,int k)
{
    std::list<int>::iterator ii;
    std::list<int>::iterator ij;
    std::list<int>::iterator ik;
    bool isOK = true;
    
    ii=EssentialListi.begin();
    ij=EssentialListj.begin();
    ik=EssentialListk.begin();
    for (int s=0; s!=EssentialListi.size(); s++)
    {
        if ((*ii == -i && *ij == -j && *ik == -k)) {isOK = false; break;}
        ii++;ij++;ik++;
    }
    
    if (isOK)
    {
        EssentialListi.insert(ii,i);
        EssentialListi.insert(ij,j);
        EssentialListi.insert(ik,k);
    }
    return isOK;
}

void MainFrame::FillBondsPanel()
{
    int TBl,TBm,TBn;
    sec30->GetVar(_("TBl[0]"), TBl);
    sec30->GetVar(_("TBm[0]"), TBm);
    sec30->GetVar(_("TBn[0]"), TBn);
    
    wxListBox* eunitcellsctr = sec30->GetListObject( _("EssentialUnitcellList"));
    EssentialListi.clear();
    EssentialListj.clear();
    EssentialListk.clear();
    int lmin,lmax,mmin,mmax,nmin,nmax;
    lmin = -TBl; lmax = TBl;
    mmin = -TBm; mmax = TBm;
    nmin = -TBn; nmax = TBn;
    if (lmin>lmax) {int dummy = lmax; lmax = lmin; lmin = dummy;}
    if (mmin>mmax) {int dummy = mmax; mmax = mmin; mmin = dummy;}
    if (nmin>nmax) {int dummy = nmax; nmax = nmin; nmin = dummy;}
    for (int i=lmax; i>=lmin; i--)
        for (int j=mmax; j>=mmin; j--)
            for (int k=nmax; k>=nmin; k--)
            {
                if (isItNew(i,j,k))
                {
                    wxString item = _("(") + wxString::Format(wxT("%d"), i) + _(",") + wxString::Format(wxT("%d"), j) + _(",") + wxString::Format(wxT("%d"), k) + _(")");
                    eunitcellsctr->Append(item);
                }
            }
}

void MainFrame::FillProjectionPanel()
{
    
}

int MainFrame::GetBonds(int* bonds)
{
    wxCheckTree* bondstreectr = sec30->GetTreeObject(_("Bonds"));
    
    int cnt=0;
	std::stack<wxTreeItemId> items;
	if (bondstreectr->GetRootItem().IsOk())
    {
		items.push(bondstreectr->GetRootItem());
        
        
        cnt++;
    }

	while (!items.empty())
	{
		wxTreeItemId next = items.top();
		items.pop();
        
		wxTreeItemIdValue cookie;
		wxTreeItemId nextChild = bondstreectr->GetFirstChild(next, cookie);
		while (nextChild.IsOk())
		{
			items.push(nextChild);
            
            
            cnt++;
			nextChild = bondstreectr->GetNextSibling(nextChild);
		}
	}

	return cnt;
}

void MainFrame::BtnStructureStyle_OnClick(wxRibbonButtonBarEvent& event)
{
    if (ColorsForm->IsShown())
        ColorsForm->Hide();
    else
        ColorsForm->Show(true);
}

void MainFrame::BtnSelect_OnClick(wxRibbonButtonBarEvent& event)
{
    BtnMouse->ToggleButton(wxID_SEPARATOR, false);//BtnScale_OnClick
    BtnMouse->ToggleButton(wxID_MORE, false);//BtnMove_OnClick
    BtnMouse->ToggleButton(wxID_RETRY, false);//BtnRotate_OnClick
    graph3d->SetLeftMouseMode(0);//Select
}

void MainFrame::BtnMove_OnClick(wxRibbonButtonBarEvent& event)
{
    BtnMouse->ToggleButton(wxID_SELECT_COLOR, false);//BtnSelect_OnClick
    BtnMouse->ToggleButton(wxID_RETRY, false);//BtnRotate_OnClick
    BtnMouse->ToggleButton(wxID_SEPARATOR, false);//BtnScale_OnClick
    graph3d->SetLeftMouseMode(1);//Move
}
    
void MainFrame::BtnRotate_OnClick(wxRibbonButtonBarEvent& event)
{
    BtnMouse->ToggleButton(wxID_SELECT_COLOR, false);//BtnSelect_OnClick
    BtnMouse->ToggleButton(wxID_MORE, false);//BtnMove_OnClick
    BtnMouse->ToggleButton(wxID_SEPARATOR, false);//BtnScale_OnClick
    graph3d->SetLeftMouseMode(2);//Rotate
}

void MainFrame::BtnScale_OnClick(wxRibbonButtonBarEvent& event)
{
    BtnMouse->ToggleButton(wxID_SELECT_COLOR, false);//BtnSelect_OnClick
    BtnMouse->ToggleButton(wxID_MORE, false);//BtnMove_OnClick
    BtnMouse->ToggleButton(wxID_RETRY, false);//BtnRotate_OnClick
    graph3d->SetLeftMouseMode(3);//Scale
}
