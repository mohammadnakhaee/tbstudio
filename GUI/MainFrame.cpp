#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <mgl2/mgl.h>
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
//#include <GL/glut.h>
//#include <WX/mdi.h>
#include <wx/msgdlg.h>
#include <WelcomeClass.h>
#include <wx/dir.h>
#include "Embeded.h"
#include "main.h"

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
    //wxColour MenueColour = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT);

#if defined(__APPLE__)
ThemeMenuColour.Set(93,111,142,255);
#else
ThemeMenuColour.Set(255,255,255,255);
#endif
    
    /*
    //1.5.0
    MySerialNumber = Sec30::GetSN(_("Limited"));
    IsLicensed = CheckLicense(LicenseOwner);
    //1.5.0
    */
    
    LeftPanel0->SetBackgroundColour(ThemeMenuColour);
    this->SetTitle(SoftwareName);
    this->Maximize(true);
    LoadIcons();
    RButtonMouse->ToggleButton(wxID_RETRY, true);//Rotate
    //tbmodel = new TBModel();
    //tbmodel->nAtoms = 4;
    
    sec30 = new Sec30(this);
    sec30->ThemeMenuColour = ThemeMenuColour;
    //sec30 = std::make_shared<Sec30>(this);
    
    sec30->Connect(Sec30EVT_OnUpdated, wxCommandEventHandler(MainFrame::sec30_OnUpdated), NULL, this);
    this->Connect(MyOpenGL_EVT_SelectionChanged, wxCommandEventHandler(MainFrame::myOpenGL_EVT_SelectionChanged), NULL, this);
    this->Connect(RegressionEVT_OnNewPlot, wxCommandEventHandler(MainFrame::regressionEVT_OnNewPlot), NULL, this);
    this->Connect(RegressionEVT_OnNewData, wxCommandEventHandler(MainFrame::regressionEVT_OnNewData), NULL, this);
    this->Connect(RegressionEVT_OnFinished, wxCommandEventHandler(MainFrame::regressionEVT_OnFinished), NULL, this);
    this->Connect(RegressionEVT_OnStarted, wxCommandEventHandler(MainFrame::regressionEVT_OnStarted), NULL, this);
    this->Connect(FigureClass_EVT_PlotFinished, wxCommandEventHandler(MainFrame::figureClass_EVT_PlotFinished), NULL, this);
    
    InitializeSec30Arrays();
    
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
	//aui_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_GRIPPER_SIZE, 80);
	wxColour c; //Also it is possible to determine the color in this way: wxColour c=*wxGREEN;
    //c.Set(150,0,0,255);
    c.Set(49,69,135,255);
    aui_mgr.GetArtProvider()->SetColour(wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR, c);
    c.Set(191,205,219,255);
	aui_mgr.GetArtProvider()->SetColour(wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR, c);
	  
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
    LeftPanel->SetBackgroundColour(ThemeMenuColour);
    
    
    LoadColorsForm();
    LoadUnitcellPanel();
    LoadStructurePanel();
    LoadOrbitalsPanel();
    LoadBondsPanel();
    LoadSKPanel();
    LoadSetupPanel();
    //LeftPanel->GetPage(0)->SetBackgroundColour(ThemeMenuColour);
    //////////////////////////////////////////////////////////////
    //Strange problem in run-time out side of the codelite. We should have selected one time the SK tab and it works fine.
    //It seems when we select the tab the objects will be opened.
    //LeftPanel->ChangeSelection(0);
    //LeftPanel->ChangeSelection(1);
    //LeftPanel->ChangeSelection(2);
    //LeftPanel->ChangeSelection(3);
    //LeftPanel->ChangeSelection(4);
    //LeftPanel->ChangeSelection(5);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //Set initial tabs
    MainRibbon->SetActivePage((size_t)0);
    LeftPanel->ChangeSelection(0);
    
    
    Init_Notebook();
    Init_graph3d();
    Init_graph2d0();
    Init_graph2d();
	
	
    regression = new Regression();
    nomadGUI = new NomadGUI(this, sec30, graph2d0, graph2d);
//    nomadGUI->Destroy();

    WelcomeClass* welcome = new WelcomeClass(NULL);
    welcome->CenterOnScreen();
    //welcome->CenterOnParent();
    welcome->ShowModal();
    
	
	
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
    
    if (IsLicensed)
    {
        logfile->AppendText(_("\nLicensed to ") + LicenseOwner +_("\n\n"));
        this->SetTitle(SoftwareName + _(" <") + LicenseOwner + _(">"));
    }
    
#if defined(__APPLE__)
//At the begining MainFrame does not raise in MacOS and this code does not work in Ubuntu (bad behaviuor in Layout)
    this->Iconize();
    this->Maximize();
    this->Raise();
#endif
}

MainFrame::~MainFrame()
{
    aui_mgr.UnInit();
    if (is_p) {delete [] p; is_p=false;}
    if (is_t) {delete [] t; is_t=false;}
    if (is_y_dat) {delete [] y_dat; is_y_dat=false;}
    if (is_weight) {delete [] weight; is_weight=false;}
    if (is_dp) {delete [] dp; is_dp=false;}
    if (is_cnst) {delete [] cnst; is_cnst=false;}
    //if (is_UpperSymMatrixHf) {delete [] UpperSymMatrixHf; is_UpperSymMatrixHf=false;}
    
    delete regression;
    //delete FittingThread;
    
    delete sec30;
    
    //if (SelectedAtoms) delete [] SelectedAtoms;
    delete graph3d;
    delete graph2d0;
    delete graph2d;
    delete unitcellPanel;
    delete structurePanel;
    delete orbitalsPanel;
    delete bondsPanel;
    delete setupPanel;
    delete skPanel;
    delete ColorsForm;
    delete RButtonMouse;
//    delete nomadGUI;
}


bool MainFrame::CheckLicense(wxString &UserName)
{
	/*
	//1.5.0
    bool isOK = false;
    wxString SNSeed1 = _("");
    if (!Sec30::GetSNFromLicenseFile(SNSeed1)) return isOK;
    if(!Sec30::IsSNSeed1MatchToThisPC(SNSeed1)) return isOK;
    wxString ID1 = Sec30::SN2ID(SNSeed1,1);
    UserName = ID1.AfterLast('|');
    return true;
	//1.5.0
	*/
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    ShowAbout();
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
    //if (unitcellPanel) unitcellPanel->Layout();
    //if(aui_mgr) aui_mgr.Update();
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
    //#include <mgl2/glut.h>
    //mglGLUT gr(sample0);
    //gr.Run();
}

void MainFrame::BtnMain_OnClick(wxRibbonButtonBarEvent& event)
{
    
}

void MainFrame::BtnTerminal_OnClick(wxRibbonButtonBarEvent& event)
{
    
}

void MainFrame::InitializeSec30Arrays()
{
    sec30->init();
}

void MainFrame::Init_Notebook()
{
	SKtables = new wxAuiNotebook(mainpanel, wxID_ANY,
                                    wxPoint(0, 0),
                                    wxSize(-1,-1),
                                    wxAUI_NB_CLOSE_BUTTON | wxAUI_NB_SCROLL_BUTTONS);
	
	wxColour c; //Also it is possible to determine the color in this way: wxColour c=*wxGREEN;
    c.Set(191,205,219,255);
	SKtables->GetArtProvider()->SetColour(c);
    //c.Set(151,0,0,255);
    c.Set(49,69,135,255);
	SKtables->GetArtProvider()->SetActiveColour(c);
    
	SKtables->Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler(MainFrame::SKtables_pageClose), NULL, this);
    SKtables->Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED, wxAuiNotebookEventHandler(MainFrame::SKtables_pageClosed), NULL, this);
	
	//SKtables->SetBackgroundColour(*wxWHITE);
	
    //SKtables->Freeze();
	//SKtables->Thaw();
	
	//SKtables = new wxAuiNotebook(mainpanel, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(mainpanel, wxSize(-1,-1)), wxBK_DEFAULT);
	//wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);
    //SKtables->SetSizer(mainsizer);
	
	aui_mgr.SetDockSizeConstraint(0.333333,0.75);
	aui_mgr.AddPane(SKtables, wxAuiPaneInfo().Gripper(false).Floatable(true).Dockable(true).Caption("Tables").CloseButton(false).MaximizeButton(true).MinimizeButton(true).BestSize(800,600).Dock().Top());
	aui_mgr.Update();

	wxString ColNames[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
	wxString ColTypes[3] = { _("string"), _("double"), _("double")};
	int ColSizes[3] = {130, 100, 100};
	int ColPrecision[3] = { 0, 8, 8};
	
	myGrid* gc = CreateGrid(SKtables, 0, 3, _(""), ColNames, ColTypes, ColSizes, ColPrecision, -1, -1, false);

	SKtables->AddPage(gc,_(""));
	SKtables->Update();
	SKtables->Refresh(true);
}

void MainFrame::Init_graph3d()
{
    graph3d = new GraphClass(mainpanel, 3, sec30, -1);
    for (int i=1; i<=50; i++) graph3d->BColorCtrl[i-1] = sec30->GetColorObject(_("BColor") + wxString::Format(wxT("%d"),i));
    //for (int i=1; i<=118; i++) graph3d->AColorCtrl[i-1] = sec30->GetColorObject(_("AColor") + wxString::Format(wxT("%d"),i));
    graph3d->CreateAtomicStructure(sec30, true);
    aui_mgr.SetDockSizeConstraint(0.333333,0.75);
    aui_mgr.AddPane(graph3d, wxAuiPaneInfo().Gripper(false).Floatable(true).Dockable(true).Caption("Structure").CloseButton(false).MaximizeButton(true).MinimizeButton(true).BestSize(800,600).Dock().Top());
    aui_mgr.Update();
}

void MainFrame::Init_graph2d0()
{
    graph2d0 = new GraphClass(mainpanel, 2, sec30, 0);
    graph2d0->sec30 = sec30;
    graph2d0->SetCursor(wxCursor(wxCURSOR_CROSS));
    aui_mgr.AddPane(graph2d0, wxAuiPaneInfo().Gripper(false).Floatable(true).Dockable(true).Caption("Initial Band-Structure").CloseButton(false).MaximizeButton(true).MinimizeButton(true).Dock().Right());
    aui_mgr.Update();
}

void MainFrame::Init_graph2d()
{
    graph2d = new GraphClass(mainpanel, 2, sec30, 1);
    graph2d->sec30 = sec30;
    graph2d->SetCursor(wxCursor(wxCURSOR_CROSS));
    aui_mgr.AddPane(graph2d, wxAuiPaneInfo().Gripper(false).Floatable(true).Dockable(true).Caption("Final Band-Structure").CloseButton(false).MaximizeButton(true).MinimizeButton(true).Dock().Right());
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
		this, _("Open TB model"), wxEmptyString, wxEmptyString, 
		_("TBM File (*.tbm)|*.tbm")
        ,wxFD_OPEN, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        sec30->LoadFromFile(dgPath, dgFileName);
        UpdateGraph2Ds();
		sec30->WorkingDIR = dgPath;
		sec30->WorkingFile = dgFileName;
		while (SKtables->GetPageCount() != 0)
		{
			SKtables->DeletePage(0);
		}
		
		wxString ColNames[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
		wxString ColTypes[3] = { _("string"), _("double"), _("double")};
		int ColSizes[3] = {130, 100, 100};
		int ColPrecision[3] = { 0, 8, 8};
		
		myGrid* gc = CreateGrid(SKtables, 0, 3, _(""), ColNames, ColTypes, ColSizes, ColPrecision, -1, -1, false);
		SKtables->AddPage(gc,_(""));
		SKtables->Update();
		SKtables->Refresh(true);
		
		this->SetTitle(SoftwareName + _(": ") + sec30->WorkingDIR + wxFileName::GetPathSeparator() + dgFileName);
		
		LoadSKTables();
	}
 
	OpenDialog->Destroy();
}

void MainFrame::BtnSave_OnClick(wxRibbonButtonBarEvent& event)
{
    if (sec30->WorkingDIR != wxEmptyString && sec30->WorkingFile != wxEmptyString)
	{
		sec30->SaveToFile(sec30->WorkingDIR, sec30->WorkingFile);
		wxMessageBox(wxT("Done!"));
	}
	else
	{
		SaveAs();
	}
}

void MainFrame::BtnSaveAs_OnClick(wxRibbonButtonBarEvent& event)
{
    SaveAs();
}

void MainFrame::BtnCloud_OnClick(wxRibbonButtonBarEvent& event)
{
    nomadGUI->ShowModal();
}

void MainFrame::SaveAs()
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Save as"), wxEmptyString, wxEmptyString, 
		_("TBM File (*.tbm)|*.tbm")
        ,wxFD_SAVE, wxDefaultPosition);
		
    OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
		
		wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("tbm"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
		dgFileName = BaseName + _(".tbm");
		
        sec30->SaveToFile(dgPath, dgFileName);
		sec30->WorkingDIR = dgPath;
		sec30->WorkingFile = dgFileName;
		this->SetTitle(SoftwareName + _(": ") + sec30->WorkingDIR + wxFileName::GetPathSeparator() + dgFileName);
		wxMessageBox(wxT("Done!"));
	}
 
	OpenDialog->Destroy();
}

void MainFrame::ClearGraph3D()
{
    graph3d->DiscardAtomicStructure();
    graph3d->myRefresh3d();
}

void MainFrame::ShowGraph3D()
{
    graph3d->CreateAtomicStructure(sec30, true);
    graph3d->myRefresh3d();
}

void MainFrame::UpdateGraph3D()
{
    graph3d->DiscardAtomicStructure();
    graph3d->CreateAtomicStructure(sec30);
    graph3d->myRefresh3d();
}

void MainFrame::UpdateGraph2D0()
{
    //graph2d0->Update2d0();
    graph2d0->myRefresh2d();
}

void MainFrame::UpdateGraph2D()
{
    //graph2d->Update2d();
    graph2d->myRefresh2d();
}

void MainFrame::UpdateGraph2Ds()
{
    UpdateGraph2D0();
    UpdateGraph2D();
}

/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
void MainFrame::sec30_OnUpdated(wxCommandEvent& event)
{
    wxString info = event.GetString();
    int redraw = event.GetInt();
    
    if (info == _("SKClass"))
    {
		int EventID = redraw;
		if (EventID == 3)
		{
			MakeACopyOfSKList();
		}
		else
		{
			int DoUpdateSKList = EventID;// 2 = update list
			EvaluateSKPanel(DoUpdateSKList);
		}
    }
    else if (info == _("SetupClass"))
    {
        int SetWeight= redraw;// 2=set all to zero     3=set all to one
        EvaluateSetupPanel(SetWeight);
    }
    
    if (info == _("UnitcellClass"))
    {
        if (redraw == 1) ClearGraph3D();
        EvaluateUnitcellPanel();
    }
    else if (info == _("StructureClass"))
    {
        if (redraw == 1) ClearGraph3D();
        EvaluateStructurePanel();
    }
    else if (info == _("OrbitalsClass"))
    {
        if (redraw == 1) ClearGraph3D();
        EvaluateOrbitalsPanel(redraw);
    }
    else if (info == _("AtomsSelected"))
    {
        if (redraw == 1) ClearGraph3D();
        EvaluateBondsPanel(redraw);
    }
    else if (info == _("BondsClass"))
    {
        if (redraw == 1) ClearGraph3D();
//        EvaluateBondsPanel(redraw);
        if (ValidateBondsPanel()) ShowGraph3D();
    }
    else if (info == _("ColorsClass"))
    {
        if (redraw == 1) ClearGraph3D();
        EvaluateColorsPanel();
    }
}
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
void MainFrame::myOpenGL_EVT_SelectionChanged(wxCommandEvent& event)
{
    int nList = graph3d->GetSelectedCount();
    if (nList == 0) {
        selectedAtomsIndex.clear();
        selectedAtomsPositions.clear();
    }
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
        sec30->SendUpdateEvent(wxT("AtomsSelected"), 0);
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
        bool isFound = false;
        int selectedIndex = -1;
        for(Aint0D::iterator it = std::begin(selectedAtomsIndex); it != std::end(selectedAtomsIndex); ++it) {
            selectedIndex++;
            if (*it == i) {
                isFound = true;
                break;
            }
        }
        
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
            
            Adouble0D pos;
            pos.push_back(x);
            pos.push_back(y);
            pos.push_back(z);
            
            if (!isFound) {
                selectedAtomsIndex.push_back(i);
                selectedAtomsPositions.push_back(pos);
            }
            
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
            if (isFound) {
                selectedAtomsIndex.erase(selectedAtomsIndex.begin() + selectedIndex);
                selectedAtomsPositions.erase(selectedAtomsPositions.begin() + selectedIndex);
            }
            
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
        
        wxString cellItem1 = wxString::Format(wxT("(0,0,0)-(%d,%d,%d)"), iMyess, jMyess, kMyess);
        wxTreeItemId lmnID1 = treectr->FindItemIn(rootID,cellItem1);
        
        wxString cellItem2 = wxString::Format(wxT("(0,0,0)-(%d,%d,%d)"), -iMyess, -jMyess, -kMyess);
        wxTreeItemId lmnID2 = treectr->FindItemIn(rootID,cellItem2);
        
        wxString cellItem;
        wxTreeItemId lmnID;
        bool isfound = false;
        if (lmnID1.IsOk())
        {
            isfound = true;
            cellItem = wxString::Format(wxT("(0,0,0)-(%d,%d,%d)"), iMyess, jMyess, kMyess);
            lmnID = treectr->FindItemIn(rootID,cellItem);
            ind000 = i1000;
            indlmn = i2000;
        }
        else if (lmnID2.IsOk())
        {
            isfound = true;
            cellItem = wxString::Format(wxT("(0,0,0)-(%d,%d,%d)"), -iMyess, -jMyess, -kMyess);
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
        
        Adouble0D pos1 = selectedAtomsPositions.at(0);
        Adouble0D pos2 = selectedAtomsPositions.at(1);
        double vec1[3] = {pos1.at(0), pos1.at(1), pos1.at(2)};
        double vec2[3] = {pos2.at(0), pos2.at(1), pos2.at(2)};
        double distance = sec30->norm(vec1, vec2);
        logfile->AppendText(wxString::Format(wxT("Distance: %.8f"), distance) + _("\n"));
    }
    
    if (nList == 3) {
        double PI=3.14159265359;
        Adouble0D pos1 = selectedAtomsPositions.at(0);
        Adouble0D pos2 = selectedAtomsPositions.at(1);
        Adouble0D pos3 = selectedAtomsPositions.at(2);
        double vec1[3] = {pos1.at(0) - pos2.at(0), pos1.at(1) - pos2.at(1), pos1.at(2) - pos2.at(2)};
        double vec2[3] = {pos3.at(0) - pos2.at(0), pos3.at(1) - pos2.at(1), pos3.at(2) - pos2.at(2)};
        double dot12 = sec30->dot(vec1, vec2);
        double norm1 = sec30->norm(vec1);
        double norm2 = sec30->norm(vec2);
        double angle = acos(dot12 / norm1 / norm2) / PI * 180.0;
        logfile->AppendText(wxString::Format(wxT("Angle: %.8f"), angle) + _("\n"));
    }
    
    gridctr->Refresh(true);
    sec30->SendUpdateEvent(wxT("AtomsSelected"), 0);
    delete [] Atoms;
}
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
void MainFrame::LoadUnitcellPanel()
{
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    scrolledwindow->SetBackgroundColour(ThemeMenuColour);
    LeftPanel->AddPage(scrolledwindow,"Unit Cell",true);
    LeftPanel->Update();
    
    unitcellPanel = new UnitcellClass(scrolledwindow,sec30);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxVERTICAL);
    panelSizer1->Add(unitcellPanel, 1, wxEXPAND);
    scrolledwindow->SetSizer(panelSizer1);
    
    scrolledwindow->FitInside();
    scrolledwindow->SetScrollRate(-1,15);
    unitcellPanel->graph3d = graph3d;
    unitcellPanel->logfile = logfile;
}

void MainFrame::LoadStructurePanel()
{
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    scrolledwindow->SetBackgroundColour(ThemeMenuColour);
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
    scrolledwindow->SetBackgroundColour(ThemeMenuColour);
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
    scrolledwindow->SetBackgroundColour(ThemeMenuColour);
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

void MainFrame::LoadSetupPanel()
{
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    scrolledwindow->SetBackgroundColour(ThemeMenuColour);
    LeftPanel->AddPage(scrolledwindow,"Setup",true);
    LeftPanel->Update();
    
    setupPanel = new SetupClass(scrolledwindow,sec30);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxVERTICAL);
    panelSizer1->Add(setupPanel, 1, wxEXPAND);
    scrolledwindow->SetSizer(panelSizer1);
    
    scrolledwindow->FitInside();
    scrolledwindow->SetScrollRate(-1,15);
    setupPanel->graph3d = graph3d;
}

void MainFrame::LoadSKPanel()
{
    wxScrolledWindow* scrolledwindow = new wxScrolledWindow(LeftPanel,wxID_ANY,wxDefaultPosition, wxSize(-1,-1));
    scrolledwindow->SetBackgroundColour(ThemeMenuColour);
    LeftPanel->AddPage(scrolledwindow,"SK",true);
    LeftPanel->Update();
    
    skPanel = new SKClass(scrolledwindow,sec30);
    
    wxBoxSizer* panelSizer1 = new wxBoxSizer(wxVERTICAL);
    panelSizer1->Add(skPanel, 1, wxEXPAND);
    scrolledwindow->SetSizer(panelSizer1);
    
    scrolledwindow->FitInside();
    scrolledwindow->SetScrollRate(-1,15);
    skPanel->graph3d = graph3d;
    skPanel->graph2d0 = graph2d0;
    skPanel->graph2d = graph2d;
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
    if (ValidateUnitCellPanel())
    {
        EvaluateStructurePanel();
    }
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

void MainFrame::EvaluateOrbitalsPanel(int redraw)
{
    if (ValidateOrbitalsPanel())
    {
        FillSetupPanel();
        if (redraw == 1) ShowGraph3D();
    }
}

void MainFrame::EvaluateBondsPanel(int redraw)
{
    if (ValidateBondsPanel())
    {
        wxButton* set_btnctr =  sec30->GetButtonObject(_("SetBondBtn"));
        wxButton* delete_btnctr =  sec30->GetButtonObject(_("DeleteBondBtn"));
        wxStaticText* bond_status =  sec30->GetStaticTextObject(_("BondStatus"));
        
//        wxButton* btnctr =  sec30->GetButtonObject(_("PickAtomBtn"));
//        if (btnctr->GetForegroundColour() == *wxRED)
//        {
//            
//        }
//        else
//            btnctr->SetForegroundColour(*wxBLACK);
        
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
            {
                set_btnctr->Enable(false);
                delete_btnctr->Enable(false);
                bond_status->SetLabel(_("TB model in Structure tab should be extended."));
                bond_status->SetForegroundColour(*wxRED);
            }
            
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
                
//                btnctr->SetForegroundColour(*wxGREEN);
                wxTreeItemId BondID = bondsPanel->GetTheBondID();
                if (BondID)
                {
                    bond_status->SetLabel(_("A bond has been selected."));
                    bond_status->SetForegroundColour(*wxBLUE);
                    set_btnctr->Enable(false);
                    delete_btnctr->Enable(true);
                } else {
                    bond_status->SetLabel(_("Selected atoms are valid."));
                    bond_status->SetForegroundColour(*wxBLUE);
                    set_btnctr->Enable(true);
                    delete_btnctr->Enable(false);
                }
            }
        }
        else
        {
            set_btnctr->Enable(false);
            delete_btnctr->Enable(false);
            bond_status->SetLabel(_("Select two atoms to create a bond."));
            bond_status->SetForegroundColour(*wxBLUE);
//            wxMessageBox(_("Please select the two atoms you are going to make a bond between them."),_("Error"));
        }
            
        if (redraw == 1) ShowGraph3D();
    }
}

void MainFrame::EvaluateSetupPanel(int SetWeight)
{
    if (SetWeight>1)
    {
        int nk = sec30->ArraysOf2DDouble[4].size();
        if (nk<1) return;
        int nbands = sec30->ArraysOf2DDouble[4][0].size();
        if (nbands<1) return;
        if (SetWeight==2)
        {
            Adouble1D EigValWeights(nk,std::vector<double>(nbands,0.0));
            sec30->ArraysOf2DDouble[4] = EigValWeights;
        }
        else if (SetWeight==3)
        {
            Adouble1D EigValWeights(nk,std::vector<double>(nbands,1.0));
            sec30->ArraysOf2DDouble[4] = EigValWeights;
        }
    }
    
    if (sec30->ArraysOf0DInt[6] == 0)
    {
        graph2d0->SetCursor(wxCursor(wxCURSOR_CROSS));
        graph2d->SetCursor(wxCursor(wxCURSOR_CROSS));
    }
    else
    {
        graph2d0->SetCursor(wxCursor(wxCURSOR_BULLSEYE));
        graph2d->SetCursor(wxCursor(wxCURSOR_BULLSEYE));
    }
    
    if (ValidateSetupPanel()) UpdateGraph2Ds();
}

void MainFrame::EvaluateSKPanel(int isUpdateSKList)
{
    if (isUpdateSKList == 2)
    {
        if (ValidateSKPanel()) ReArrangeSKList();
    }
    else
    {
        if (ValidateSKParametersList())
        {
            UpdateTBBand_if();
            UpdateGraph2Ds();
        }
		else
		{
			//logfile->AppendText(_("You have made some changes in the settings of your TB model. The fitting parameters in SK panel are not valid. Please update the independent parameters in the SK panel.\n"));
		}
    }
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
    double a0[3], b0[3], c0[3];
    double a[3], b[3], c[3];
    double astrain, bstrain, cstrain;
    double x, y, z;
    int kind;
    int nRow = 0;
    int nCol = 0;
    sec30->GetDim(_("KABC_Coords"), nRow, nCol);
    
    isValid = isValid && sec30->GetVar(_("a0[0]"), a0[0]);
    isValid = isValid && sec30->GetVar(_("a0[1]"), a0[1]);
    isValid = isValid && sec30->GetVar(_("a0[2]"), a0[2]);
    isValid = isValid && sec30->GetVar(_("b0[0]"), b0[0]);
    isValid = isValid && sec30->GetVar(_("b0[1]"), b0[1]);
    isValid = isValid && sec30->GetVar(_("b0[2]"), b0[2]);
    isValid = isValid && sec30->GetVar(_("c0[0]"), c0[0]);
    isValid = isValid && sec30->GetVar(_("c0[1]"), c0[1]);
    isValid = isValid && sec30->GetVar(_("c0[2]"), c0[2]);
    
    isValid = isValid && sec30->GetVar(_("astrain[0]"), astrain);
    isValid = isValid && sec30->GetVar(_("bstrain[0]"), bstrain);
    isValid = isValid && sec30->GetVar(_("cstrain[0]"), cstrain);
    for (int i0=0; i0<3; i0++)
    {
        a[i0]=a0[i0]*astrain;
        b[i0]=b0[i0]*bstrain;
        c[i0]=c0[i0]*cstrain;
    }
    
    if (isValid)
    {
        sec30->SetVar(_("a[0]"),a[0],false);
        sec30->SetVar(_("a[1]"),a[1],false);
        sec30->SetVar(_("a[2]"),a[2],false);
        sec30->SetVar(_("b[0]"),b[0],false);
        sec30->SetVar(_("b[1]"),b[1],false);
        sec30->SetVar(_("b[2]"),b[2],false);
        sec30->SetVar(_("c[0]"),c[0],false);
        sec30->SetVar(_("c[1]"),c[1],false);
        sec30->SetVar(_("c[2]"),c[2],false);
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
            
            wxString name = wxString::Format(wxT("AtomInd%d"),AtomCnt);
            wxStaticText* lab = sec30->GetComboLabelObject(name);
            wxString label = wxString::Format(wxT("Atom %d"),i+1);
            lab->SetLabel(label + _(" [") +sec30->GetAtomLable(kind)+ _("]:"));
            lab->GetParent()->Layout();
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

bool MainFrame::ValidateSetupPanel()
{
    bool isValid = true;
    int nMin, nMax;
    sec30->GetVar(_("DFTBandRange[0]"), nMin);
    sec30->GetVar(_("DFTBandRange[1]"), nMax);
    
    if (nMax >= nMin)
    {
        sec30->ArraysOf0DInt[4] = nMin;//int DFTnBandMin;
        sec30->ArraysOf0DInt[5] = nMax;//int DFTnBandMax;
        sec30->SetVar(_("nDFTBandRange[0]"), nMax - nMin + 1, false);
    }
    else
        isValid = false;
    return isValid;
}

bool MainFrame::ValidateSKPanel()
{
    sec30->isMainThread = true;
    //sec30->ArraysOf0DInt[9] = 0; //bool isFittingParametersValid = false;
    int ErrorIndex = 0;
    int WarningIndex = 0;
    bool isValid = true;
    int nOnSites=0;
    sec30->GetVar(_("nAtoms[0]"),nOnSites);
    if (nOnSites == 0)
    {
        ErrorIndex++;
        if (ErrorIndex==1){isValid = false;logfile->AppendText(_("\nError list:\n"));}
        logfile->AppendText(wxString::Format(wxT("Error %d: There is not any atom in your structure!\n"),ErrorIndex));
    }
    
    for (int i = 1; i<=nOnSites; i++)
    {
        wxString name = wxString::Format(wxT("AtomInd%d"),i);
        wxComboBox* comb = sec30->GetComboObject(name);
        wxStaticText* comblabel = sec30->GetComboLabelObject(name);
        wxString label = comb->GetStringSelection();
        if (label == _("Not set"))
        {
            ErrorIndex++;
            if (ErrorIndex==1) {isValid = false;logfile->AppendText(_("\nError list:\n"));}
            logfile->AppendText(wxString::Format(wxT("Error %d: "),ErrorIndex) + _("The projection for the ") + comblabel->GetLabel() + _(" has not yet been set.\n"));
        }
    }
    
    
    /*int b1a1, b1a2, b2a1, b2a2;
    sec30->GetVar(_("KABC_Coords"), iAtomIndex0, 0, b1a1);
    sec30->GetVar(_("KABC_Coords"), jAtomIndex0, 0, b1a2);
    sec30->GetVar(_("KABC_Coords"), iAtomIndex, 0, b2a1);
    sec30->GetVar(_("KABC_Coords"), jAtomIndex, 0, b2a2);
    wxString sb1a1, sb1a2, sb2a1, sb2a2;
    sb1a1 = sec30->GetAtomLable(b1a1);
    sb1a2 = sec30->GetAtomLable(b1a2);
    sb2a1 = sec30->GetAtomLable(b2a1);
    sb2a2 = sec30->GetAtomLable(b2a2);*/
                        
                        
    wxComboBox* bondtypes = sec30->GetComboObject(_("BondLabel"));
    wxCheckTree* bonds = sec30->GetTreeObject(_("Bonds"));
    wxCheckTree* orbs = sec30->GetTreeObject(_("Orbitals"));
    
    wxListBox* TBlistctr = sec30->GetListObject(_("AtomSpeciesList"));
    int TBnspec = TBlistctr->GetCount();
    wxTreeItemId orbsrootID = orbs->GetRootItem();
    
    for(int j=0; j<TBnspec; j++)
    {
        wxString TBAtomName = TBlistctr->GetString(j);
        wxTreeItemId orbsatomID = orbs->FindItemIn(orbsrootID,TBAtomName);
        //FixSoSoon
        orbs->SetItemState(orbsatomID, wxCheckTree::UNCHECKED);
        wxTreeItemIdValue cookie;
        wxTreeItemId nextChild = orbs->GetFirstChild(orbsatomID, cookie);
        while (nextChild.IsOk())
        {
            //FixSoSoon
            orbs->SetItemState(nextChild, wxCheckTree::UNCHECKED);
            nextChild = orbs->GetNextSibling(nextChild);
        }
    }
    
    int nBondType = bondtypes->GetCount();
    int nBonds = 0;
    for (int BondTypeIndex = 1; BondTypeIndex <= nBondType; BondTypeIndex++)
    {
        wxString bondinfotest = wxString::Format(wxT("Bond %d"), BondTypeIndex);
        wxTreeItemId rootID = bonds->GetRootItem();
        wxTreeItemId FirstID = bonds->ActiveAndContainsItemIn(rootID,bondinfotest);
        
        if (FirstID)
        {
            nBonds++;
            wxString BondInfo0 = bonds->GetItemText(FirstID);
            int iAtomIndex0,nShellIndex0,jAtomIndex0,mShellIndex0,bondtype0;
            sec30->GetBondInfo(BondInfo0, iAtomIndex0,nShellIndex0,jAtomIndex0,mShellIndex0,bondtype0);
            wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex0 + 1);
            wxComboBox* comb1 = sec30->GetComboObject(atom1);
            wxString TBAtom1 = comb1->GetStringSelection();
            int Dim1 = -1;
            bool IsShell;
            wxString Orbs1;
            if (TBAtom1 != _("Not set")) sec30->GetOrbitalInfo(orbs, TBAtom1, nShellIndex0, Orbs1, Dim1, IsShell);
            //if (!IsShell) logfile->AppendText(wxString::Format(wxT("Shell %d"),nShellIndex0) + _(" has not been defined for the TB atom ") + TBAtom1 + _(".\n"));
            wxString atom2 = wxString::Format(wxT("AtomInd%d"),jAtomIndex0 + 1);
            wxComboBox* comb2 = sec30->GetComboObject(atom2);
            wxString TBAtom2 = comb2->GetStringSelection();
            int Dim2 = -1;
            wxString Orbs2;
            if (TBAtom2 != _("Not set")) sec30->GetOrbitalInfo(orbs, TBAtom2, mShellIndex0, Orbs2, Dim2, IsShell);
            //if (!IsShell) logfile->AppendText(wxString::Format(wxT("Shell %d"),mShellIndex0) + _(" has not been defined for the TB atom ") + TBAtom2 + _(".\n"));
            
            std::stack<wxTreeItemId> items;
            if (bonds->GetRootItem().IsOk())
            {
                wxTreeItemId bond = bonds->GetRootItem();
                items.push(bond);
                wxString sbond = bonds->GetItemText(bond);
            }

            while (!items.empty())
            {
                wxTreeItemId next = items.top();
                items.pop();
                
                wxTreeItemIdValue cookie;
                wxTreeItemId nextChild = bonds->GetFirstChild(next, cookie);
                while (nextChild.IsOk())
                {
                    items.push(nextChild);
                    
                    wxString BondInfo = bonds->GetItemText(nextChild);
                    if (!BondInfo.StartsWith("("))
                    {
                        wxTreeItemId ParrentOfnextChild = bonds->GetItemParent(nextChild);
                        if (bonds->GetItemState(nextChild) >= wxCheckTree::CHECKED && bonds->GetItemState(ParrentOfnextChild) >= wxCheckTree::CHECKED)
                        {
                            int iAtomIndex,nShellIndex,jAtomIndex,mShellIndex,bondtype;
                            sec30->GetBondInfo(BondInfo, iAtomIndex,nShellIndex,jAtomIndex,mShellIndex,bondtype);
                            
                            if (bondtype == bondtype0)
                            {
                                wxString natom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
                                wxComboBox* ncomb1 = sec30->GetComboObject(natom1);
                                wxString nTBAtom1 = ncomb1->GetStringSelection();
                                int nDim1 = -1;
                                bool IsShell;
                                wxString nOrbs1;
                                if (nTBAtom1 != _("Not set")) sec30->GetOrbitalInfo(orbs, nTBAtom1, nShellIndex, nOrbs1, nDim1, IsShell);
                                if (!IsShell) logfile->AppendText(wxString::Format(wxT("Shell %d"),nShellIndex) + _(" has not been defined for the TB atom ") + nTBAtom1 + _(".\n"));
                                wxString natom2 = wxString::Format(wxT("AtomInd%d"), jAtomIndex + 1);
                                wxComboBox* ncomb2 = sec30->GetComboObject(natom2);
                                wxString nTBAtom2 = ncomb2->GetStringSelection();
                                int nDim2 = -1;
                                wxString nOrbs2;
                                if (nTBAtom2 != _("Not set")) sec30->GetOrbitalInfo(orbs, nTBAtom2, mShellIndex, nOrbs2, nDim2, IsShell);
                                if (!IsShell) logfile->AppendText(wxString::Format(wxT("Shell %d"),mShellIndex) + _(" has not been defined for the TB atom ") + nTBAtom2 + _(".\n"));
                                
                                
                                
                                if (nDim1 == 0 || nDim2 == 0)
                                {
                                    ErrorIndex++;
                                    if (ErrorIndex==1) {isValid = false;logfile->AppendText(_("\nError list:\n"));}
                                    logfile->AppendText(wxString::Format(wxT("Error %d: "),ErrorIndex) + _("The bond has an empty shell.\n"));
                                    logfile->AppendText(wxString::Format(wxT("          "),ErrorIndex) + _("Defined as ") + BondInfo + _(" between ") + nOrbs1 + _(" and ") + nOrbs2 + _("\n"));
                                }
                                else
                                {
                                    bool isConflict = false;
                                    if (TBAtom1 == nTBAtom1 && TBAtom2 == nTBAtom2)
                                    {
                                        if (!(nOrbs1 == Orbs1 && nOrbs2 == Orbs2)) isConflict = true;
                                    }
                                    else if (TBAtom1 == nTBAtom2 && TBAtom2 == nTBAtom1)
                                    {
                                        if (!(nOrbs1 == Orbs2 && nOrbs2 == Orbs1)) isConflict = true;
                                    }
                                    
                                    if (isConflict)
                                    {
                                        ErrorIndex++;
                                        if (ErrorIndex==1) {isValid = false; logfile->AppendText(_("\nError list:\n"));}
                                        logfile->AppendText(wxString::Format(wxT("Error %d: "),ErrorIndex) + _("There is a conflict between the defined bonds.\n"));
                                        logfile->AppendText(wxString::Format(wxT("          "),ErrorIndex) + _("First defined as ") + BondInfo0 + _(" between ") + Orbs1 + _(" and ") + Orbs2 + _("\n"));
                                        logfile->AppendText(wxString::Format(wxT("          "),ErrorIndex) + _("Here defined as ") + BondInfo + _(" between ") + nOrbs1 + _(" and ") + nOrbs2 + _("\n"));
                                    }
                                }
                                
                                if (!((TBAtom1 == nTBAtom1 && TBAtom2 == nTBAtom2) || (TBAtom1 == nTBAtom2 && TBAtom2 == nTBAtom1)))
                                {
                                    WarningIndex++;
                                    if (WarningIndex==1) {logfile->AppendText(_("\nWarning list:\n"));}
                                    logfile->AppendText(wxString::Format(wxT("Warning %d: "),WarningIndex) + bondinfotest + _(" has been defined for different pair of atoms. It may cause wrong results.\n"));
                                    logfile->AppendText(wxString::Format(wxT("            "),WarningIndex) + _("First defined as ") + BondInfo0 + _(" between ") + TBAtom1 + _(" and ") + TBAtom2 + _("\n"));
                                    logfile->AppendText(wxString::Format(wxT("            "),WarningIndex) + _("Here defined as ") + BondInfo + _(" between ") + nTBAtom1 + _(" and ") + nTBAtom2 + _("\n"));
                                }
                            }
                        }
                    }
                    nextChild = bonds->GetNextSibling(nextChild);
                }
            }
        }
        
    }
    
    if (nBonds == 0)
    {
        WarningIndex++;
        if (WarningIndex==1) {logfile->AppendText(_("\nWarning list:\n"));}
        logfile->AppendText(wxString::Format(wxT("Warning %d: "),ErrorIndex) + _("No bond was found in your bonds list. It will result in molecular levels.\n"));
    }
    
    if (isValid)
	{
        //sec30->ArraysOf0DInt[9] = 1; //bool isFittingParametersValid = true;
	}
    else
        logfile->AppendText(_("\nFix the errors and try again ...\n"));
    
    return isValid;
}

bool MainFrame::ValidateSKParametersList()
{
    bool isFittingParametersValid = true;

	bool AnyProblem = false;
	myGrid* osgc = sec30->GetGridObject(_("OS"));
	//myGrid* skgc = sec30->GetGridObject(_("SK"));
	myGrid* olgc = sec30->GetGridObject(_("OL"));
	int nos = osgc->GetNumberRows();
	//int nsk = skgc->GetNumberRows();
	int nol = olgc->GetNumberRows();
	
	int nHamiltonian = sec30->ArraysOf1DString[1].size();
	bool isSOC;
	sec30->GetCheckVar(_("SOC[0]"), isSOC);
	bool isOverlap;
	sec30->GetCheckVar(_("Overlap[0]"), isOverlap);
    
	if ((nol < 1 && isOverlap) || (nol > 0 && !isOverlap)) AnyProblem = true;
	
	if (!AnyProblem)
	{
		if(nos > 2)
		{
			wxString str = osgc->GetCellValue(nos - 2, 0);
			if ((!str.Contains(_("soc")) && isSOC) || (str.Contains(_("soc")) && !isSOC)) AnyProblem = true;
		}
		else
			AnyProblem = true;
	}
	
	if (AnyProblem)
	{
		//sec30->ArraysOf0DInt[9] = 0;//bool isFittingParametersValid = false;
		isFittingParametersValid = false;
	}

    return isFittingParametersValid;
}

bool MainFrame::ValidateColorsPanel()
{
    bool isValid = true;
    
    return isValid;
}
/****************************************************************************************************************************************************************/
void MainFrame::ReArrangeSKList()
{
    sec30->isMainThread = true;
    Aint0D SKListAddress;
    
    wxString AllSK;
    sec30->GetVar(_("AllSK[0]"), AllSK);
    
    myGrid* osgc = sec30->GetGridObject(_("OS"));
    int nRowsOS = osgc->GetNumberRows();
    if (nRowsOS!=0) osgc->DeleteRows(0,nRowsOS,true);
    
    myGrid* skgc = sec30->GetGridObject(_("SK"));
    int nRowsSK = skgc->GetNumberRows();
    if (nRowsSK!=0) skgc->DeleteRows(0,nRowsSK,true);
    
    myGrid* olgc = sec30->GetGridObject(_("OL"));
    int nRowsOL = olgc->GetNumberRows();
    if (nRowsOL!=0) olgc->DeleteRows(0,nRowsOL,true);
    
    bool isSOC;
    sec30->GetCheckVar(_("SOC[0]"), isSOC);
    
    bool isOverlap;
    sec30->GetCheckVar(_("Overlap[0]"), isOverlap);
    
    wxColour c, ctitle; //Also it is possible to determine the color in this way: wxColour c=*wxGREEN;
    c.Set(191,205,219,255);
    
    wxComboBox* comboctr = sec30->GetComboObject(_("BondLabel"));
    int nBondType = comboctr->GetCount();
    wxCheckTree* bonds = sec30->GetTreeObject(_("Bonds"));
    wxCheckTree* orbs = sec30->GetTreeObject(_("Orbitals"));
    Astring0D HamiltonianMap;
    Astring0D HamiltonianShellMap;
    Aint1D HamiltonianDimMap;
    GetHamiltonianMap(orbs, HamiltonianMap, HamiltonianShellMap, HamiltonianDimMap);
    sec30->ArraysOf1DString[1] = HamiltonianMap;
    sec30->ArraysOf1DString[2] = HamiltonianShellMap;
    sec30->ArraysOf2DInt[0] = HamiltonianDimMap;
    
    Aint1D SKIndexList;
    int TotalNumberOfParameters = 0;
    ///////////////////////////////////////////////////////////On-Sites////////////////////////////////////////////////////////////////////
    int TotalIndex = -1;
    wxTreeItemId orbsRoot = orbs->GetRootItem();
    wxTreeItemIdValue cookie00;
    wxTreeItemId TBAtomID = orbs->GetFirstChild(orbsRoot,cookie00);
    while (TBAtomID.IsOk())
    {
        if (orbs->GetItemState(TBAtomID) >= wxCheckTree::CHECKED)
        {
            wxString AtomLabel = orbs->GetItemText(TBAtomID);
            
            wxTreeItemIdValue cookie01;
            wxTreeItemId TBShellID = orbs->GetFirstChild(TBAtomID,cookie01);
            while (TBShellID.IsOk())
            {
                if (orbs->GetItemState(TBShellID) >= wxCheckTree::CHECKED)
                {
                    wxString ShellLabel = orbs->GetItemText(TBShellID);
                    TotalIndex++;
                    SKListAddress.push_back(TotalIndex);
                    osgc->InsertRows(TotalIndex, 1,true);
                    osgc->SetCellValue(TotalIndex, 0, AtomLabel + _(" (") + ShellLabel +_(")"));
                    osgc->SetReadOnly(TotalIndex, 0);
                    osgc->SetReadOnly(TotalIndex, 1);
                    osgc->SetReadOnly(TotalIndex, 2);
                    osgc->SetCellBackgroundColour(TotalIndex, 0, c);
                    osgc->SetCellBackgroundColour(TotalIndex, 1, c);
                    osgc->SetCellBackgroundColour(TotalIndex, 2, c);
                    
                    bool is_p = false;
                    bool is_d = false;
                    wxTreeItemIdValue cookie02;
                    wxTreeItemId TBOrbID = orbs->GetFirstChild(TBShellID,cookie02);
                    while (TBOrbID.IsOk())
                    {
                        if (orbs->GetItemState(TBOrbID) >= wxCheckTree::CHECKED)
                        {
                            wxString OnSiteLabel = orbs->GetItemText(TBOrbID);
                            TotalNumberOfParameters++;
                            TotalIndex++;
                            SKListAddress.push_back(TotalIndex);
                            osgc->InsertRows(TotalIndex, 1,true);
                            osgc->SetCellValue(TotalIndex, 0, OnSiteLabel);
                            osgc->SetReadOnly(TotalIndex, 0);
                            osgc->SetCellBackgroundColour(TotalIndex, 0, c);
                            osgc->SetCellValue(TotalIndex, 1, _("0"));
                            
                            Aint0D IndexInfo;
                            IndexInfo.push_back(1);
                            IndexInfo.push_back(TotalIndex);
                            SKIndexList.push_back(IndexInfo);
                            
                            if (!is_p)
                            {
                                if (OnSiteLabel[0] == 'p' || OnSiteLabel[1] == 'p') is_p = true;
                            }
                            
                            if (!is_d)
                            {
                                if (OnSiteLabel[0] == 'd' || OnSiteLabel[1] == 'd') is_d = true;
                            }
                        }
                        TBOrbID = orbs->GetNextSibling(TBOrbID);
                    }
                    
                    if (isSOC)
                    {
                        if (is_p)
                        {
                            TotalNumberOfParameters++;
                            TotalIndex++;
                            SKListAddress.push_back(TotalIndex);
                            osgc->InsertRows(TotalIndex, 1,true);
                            osgc->SetCellValue(TotalIndex, 0, _("p_{soc}"));
                            osgc->SetReadOnly(TotalIndex, 0);
                            osgc->SetCellBackgroundColour(TotalIndex, 0, c);
                            osgc->SetCellValue(TotalIndex, 1, _("0"));
                            
                            Aint0D IndexInfo;
                            IndexInfo.push_back(1);
                            IndexInfo.push_back(TotalIndex);
                            SKIndexList.push_back(IndexInfo);
                        }
                        
                        if (is_d)
                        {
                            TotalNumberOfParameters++;
                            TotalIndex++;
                            SKListAddress.push_back(TotalIndex);
                            osgc->InsertRows(TotalIndex, 1,true);
                            osgc->SetCellValue(TotalIndex, 0, _("d_{soc}"));
                            osgc->SetReadOnly(TotalIndex, 0);
                            osgc->SetCellBackgroundColour(TotalIndex, 0, c);
                            osgc->SetCellValue(TotalIndex, 1, _("0"));
                            
                            Aint0D IndexInfo;
                            IndexInfo.push_back(1);
                            IndexInfo.push_back(TotalIndex);
                            SKIndexList.push_back(IndexInfo);
                        }
                    }
                }
                TBShellID = orbs->GetNextSibling(TBShellID);
            }
        }
        TBAtomID = orbs->GetNextSibling(TBAtomID);
    }
    
    TotalIndex++;
    SKListAddress.push_back(TotalIndex);
    osgc->InsertRows(TotalIndex, 1,true);
    osgc->SetCellValue(TotalIndex, 0, _(""));
    osgc->SetReadOnly(TotalIndex, 0);
    osgc->SetReadOnly(TotalIndex, 1);
    osgc->SetReadOnly(TotalIndex, 2);
    osgc->SetCellBackgroundColour(TotalIndex, 0, c);
    osgc->SetCellBackgroundColour(TotalIndex, 1, c);
    osgc->SetCellBackgroundColour(TotalIndex, 2, c);
    
    ///////////////////////////////////////////////////////////Bonds////////////////////////////////////////////////////////////////////
    Aint0D OnlyBondsIndex;
    TotalIndex = -1;
    for (int BondTypeIndex = 1; BondTypeIndex <= nBondType; BondTypeIndex++)
    {
        wxString bondinfotest = wxString::Format(wxT("Bond %d"), BondTypeIndex);
        wxTreeItemId rootID = bonds->GetRootItem();
        wxTreeItemId FirstID = bonds->ContainsItemIn(rootID,bondinfotest);
        
        if (FirstID)
        {
            TotalIndex++;
            SKListAddress.push_back(TotalIndex);
            skgc->InsertRows(TotalIndex, 1,true);
            skgc->SetCellValue(TotalIndex, 0, bondinfotest);
            skgc->SetReadOnly(TotalIndex, 0);
            skgc->SetReadOnly(TotalIndex, 1);
            skgc->SetReadOnly(TotalIndex, 2);
            skgc->SetCellBackgroundColour(TotalIndex, 0, c);
            skgc->SetCellBackgroundColour(TotalIndex, 1, c);
            skgc->SetCellBackgroundColour(TotalIndex, 2, c);
            
            if (isOverlap)
            {
                olgc->InsertRows(TotalIndex, 1,true);
                olgc->SetCellValue(TotalIndex, 0, bondinfotest);
                olgc->SetReadOnly(TotalIndex, 0);
                olgc->SetReadOnly(TotalIndex, 1);
                olgc->SetReadOnly(TotalIndex, 2);
                olgc->SetCellBackgroundColour(TotalIndex, 0, c);
                olgc->SetCellBackgroundColour(TotalIndex, 1, c);
                olgc->SetCellBackgroundColour(TotalIndex, 2, c);
            }
            
            wxString BondInfo0 = bonds->GetItemText(FirstID);
            int iAtomIndex0,nShellIndex0,jAtomIndex0,mShellIndex0,bondtype0;
            sec30->GetBondInfo(BondInfo0, iAtomIndex0,nShellIndex0,jAtomIndex0,mShellIndex0,bondtype0);
            wxString atom1 = wxString::Format(wxT("AtomInd%d"), iAtomIndex0 + 1);
            wxComboBox* comb1 = sec30->GetComboObject(atom1);
            wxString TBAtom1 = comb1->GetStringSelection();
            int Dim1 = -1;
            bool IsShell;
            wxString Orbs1;
            if (TBAtom1 != _("Not set")) sec30->GetOrbitalInfo(orbs, TBAtom1, nShellIndex0, Orbs1, Dim1, IsShell);
            //if (!IsShell) logfile->AppendText(wxString::Format(wxT("Shell %d"),nShellIndex0) + _(" has not been defined for the TB atom ") + TBAtom1 + _(".\n"));
            wxString atom2 = wxString::Format(wxT("AtomInd%d"), jAtomIndex0 + 1);
            wxComboBox* comb2 = sec30->GetComboObject(atom2);
            wxString TBAtom2 = comb2->GetStringSelection();
            int Dim2 = -1;
            wxString Orbs2;
            if (TBAtom2 != _("Not set")) sec30->GetOrbitalInfo(orbs, TBAtom2, mShellIndex0, Orbs2, Dim2, IsShell);
            //if (!IsShell) logfile->AppendText(wxString::Format(wxT("Shell %d"),mShellIndex0) + _(" has not been defined for the TB atom ") + TBAtom2 + _(".\n"));
            
            wxString orbs1 = Orbs1.AfterFirst('(').BeforeLast(')');
            wxString orbs2 = Orbs2.AfterFirst('(').BeforeLast(')');
            orbs1.Replace(wxString(" "), wxString(""));
            orbs2.Replace(wxString(" "), wxString(""));
    
            wxStringTokenizer SKtokenizer(AllSK, ",");
            while ( SKtokenizer.HasMoreTokens() )
            {
                wxString sk = SKtokenizer.GetNextToken();
                //to check is there such a parameter in this bond or not
                if (IsBondContainsParameter(orbs1,orbs2,sk))
                {
                    TotalNumberOfParameters++;
                    TotalIndex++;
                    skgc->InsertRows(TotalIndex, 1,true);
                    skgc->SetCellValue(TotalIndex, 0, sk);
                    skgc->SetReadOnly(TotalIndex, 0);
                    skgc->SetCellBackgroundColour(TotalIndex, 0, c);
                    skgc->SetCellValue(TotalIndex, 1, _("0"));
                    
                    OnlyBondsIndex.push_back(TotalIndex);
                    
                    if (isOverlap)
                    {
                        TotalNumberOfParameters++;
                        olgc->InsertRows(TotalIndex, 1,true);
                        olgc->SetCellValue(TotalIndex, 0, sk);
                        olgc->SetReadOnly(TotalIndex, 0);
                        olgc->SetCellBackgroundColour(TotalIndex, 0, c);
                        olgc->SetCellValue(TotalIndex, 1, _("0"));
                    }
                }
            }
        }
    }
    
    for (int isk = 0; isk<OnlyBondsIndex.size(); isk++)
    {
        Aint0D IndexInfo;
        IndexInfo.push_back(2);
        IndexInfo.push_back(OnlyBondsIndex[isk]);
        SKIndexList.push_back(IndexInfo);
    }
    
    if (isOverlap)
    {
        for (int isk = 0; isk<OnlyBondsIndex.size(); isk++)
        {
            Aint0D IndexInfo;
            IndexInfo.push_back(3);
            IndexInfo.push_back(OnlyBondsIndex[isk]);
            SKIndexList.push_back(IndexInfo);
        }
    }
    
    sec30->ArraysOf2DInt[1] = SKIndexList;
    
    TotalIndex++;
    skgc->InsertRows(TotalIndex, 1,true);
    skgc->SetCellValue(TotalIndex, 0, _(""));
    skgc->SetReadOnly(TotalIndex, 0);
    skgc->SetReadOnly(TotalIndex, 1);
    skgc->SetReadOnly(TotalIndex, 2);
    skgc->SetCellBackgroundColour(TotalIndex, 0, c);
    skgc->SetCellBackgroundColour(TotalIndex, 1, c);
    skgc->SetCellBackgroundColour(TotalIndex, 2, c);
    
    if (isOverlap)
    {
        olgc->InsertRows(TotalIndex, 1,true);
        olgc->SetCellValue(TotalIndex, 0, _(""));
        olgc->SetReadOnly(TotalIndex, 0);
        olgc->SetReadOnly(TotalIndex, 1);
        olgc->SetReadOnly(TotalIndex, 2);
        olgc->SetCellBackgroundColour(TotalIndex, 0, c);
        olgc->SetCellBackgroundColour(TotalIndex, 1, c);
        olgc->SetCellBackgroundColour(TotalIndex, 2, c);
    }
    
    sec30->SetVar(_("nParameters[0]"), TotalNumberOfParameters, false);
    logfile->AppendText(_("\nThe SK parameters list has been updated ...\n"));
    logfile->AppendText(wxString::Format(wxT("The total number of parameters: %d\n"),TotalNumberOfParameters));
}

bool MainFrame::IsBondContainsParameter(wxString Orbs1, wxString Orbs2, wxString sk)
{
    bool isSK=false;
    
    //examples: sk="sss","sps","pps","ppp" or "sds" : so for "sds" sk[0]='s' sk[1]='d' sk[2]=s
    wxStringTokenizer tokenizer1(Orbs1, ",");
    while (tokenizer1.HasMoreTokens() && !isSK)
    {
        wxString o1 = tokenizer1.GetNextToken();
        
        wxStringTokenizer tokenizer2(Orbs2, ",");
        while (tokenizer2.HasMoreTokens() && !isSK)
        {
            wxString o2 = tokenizer2.GetNextToken();
            if ((sk[0] == o1[0] && sk[1] == o2[0]) || (sk[0] == o2[0] && sk[1] == o1[0]))
            {
                isSK = true;
            }
        }
    }
    return isSK;
}

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

void MainFrame::FillSetupPanel()
{
    //Clear All labels in Projection panel after the nAtoms. It will be set later as long as the lines are valid in unitcell panel
    int maxIndex=0;
    sec30->GetVar(_("nAtoms[0]"),maxIndex);
    for (int i = maxIndex + 1; i<=99; i++)
    {
        wxString name = wxString::Format(wxT("AtomInd%d"),i);
        wxStaticText* lab = sec30->GetComboLabelObject(name);
        wxString label = wxString::Format(wxT("Atom %d"),i);
        lab->SetLabel(label);
    }
    
    wxListBox* listctr = sec30->GetListObject(_("AtomSpeciesList"));
    int nspec = listctr->GetCount();
    
    for (int i = 1; i<=99; i++)
    {
        wxString name = wxString::Format(wxT("AtomInd%d"),i);
        wxComboBox* ctr = sec30->GetComboObject(name);
        int oldind = ctr->GetSelection();
        ctr->Clear();
        ctr->Append(_("Not set"));
        for(int j=0; j<nspec; j++) ctr->Append(listctr->GetString(j));
        if (oldind < nspec)
            ctr->SetSelection(oldind);
        else
            ctr->SetSelection(0);
    }
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
    {
        //ColorsForm->CenterOnScreen();
        ColorsForm->CenterOnParent();
        ColorsForm->Show(true);
    }
}

void MainFrame::BtnSelect_OnClick(wxRibbonButtonBarEvent& event)
{
    RButtonMouse->ToggleButton(wxID_FILE4, false);//BtnScale_OnClick
    RButtonMouse->ToggleButton(wxID_FILE2, false);//BtnMove_OnClick
    RButtonMouse->ToggleButton(wxID_FILE3, false);//BtnRotate_OnClick
    graph3d->SetLeftMouseMode(0);//Select
}

void MainFrame::BtnMove_OnClick(wxRibbonButtonBarEvent& event)
{
    RButtonMouse->ToggleButton(wxID_FILE1, false);//BtnSelect_OnClick
    RButtonMouse->ToggleButton(wxID_FILE3, false);//BtnRotate_OnClick
    RButtonMouse->ToggleButton(wxID_FILE4, false);//BtnScale_OnClick
    graph3d->SetLeftMouseMode(1);//Move
}
    
void MainFrame::BtnRotate_OnClick(wxRibbonButtonBarEvent& event)
{
    RButtonMouse->ToggleButton(wxID_FILE1, false);//BtnSelect_OnClick
    RButtonMouse->ToggleButton(wxID_FILE2, false);//BtnMove_OnClick
    RButtonMouse->ToggleButton(wxID_FILE4, false);//BtnScale_OnClick
    graph3d->SetLeftMouseMode(2);//Rotate
}

void MainFrame::BtnScale_OnClick(wxRibbonButtonBarEvent& event)
{
    RButtonMouse->ToggleButton(wxID_FILE1, false);//BtnSelect_OnClick
    RButtonMouse->ToggleButton(wxID_FILE2, false);//BtnMove_OnClick
    RButtonMouse->ToggleButton(wxID_FILE3, false);//BtnRotate_OnClick
    graph3d->SetLeftMouseMode(3);//Scale
}

void MainFrame::BtnX_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->SetCamDir(_("x"));
}

void MainFrame::BtnY_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->SetCamDir(_("y"));
}

void MainFrame::BtnZ_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->SetCamDir(_("z"));
}

void MainFrame::BtnA_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->SetCamDir(_("a"));
}

void MainFrame::BtnB_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->SetCamDir(_("b"));
}

void MainFrame::BtnC_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->SetCamDir(_("c"));
}

void MainFrame::BtnUp_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->RotateCam(_("u"));
}

void MainFrame::BtnDown_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->RotateCam(_("d"));
}

void MainFrame::BtnLeft_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->RotateCam(_("l"));
}

void MainFrame::BtnRight_OnClick(wxRibbonButtonBarEvent& event)
{
    graph3d->RotateCam(_("r"));
}

void MainFrame::BtnStart_OnClick(wxRibbonButtonBarEvent& event)
{
    if (!isFittingThreadBusy)
        StartRegression(false);
    else
        wxMessageBox(_("A procedure is running!"));
}

void MainFrame::BtnOnestep_OnClick(wxRibbonButtonBarEvent& event)
{
    if (!isFittingThreadBusy) StartRegression(true);
}

void MainFrame::BtnPause_OnClick(wxRibbonButtonBarEvent& event)
{
    
}

void MainFrame::BtnStop_OnClick(wxRibbonButtonBarEvent& event)
{
    if (!sec30->IsStopClicked)
    {
        sec30->IsStopClicked = true;
        logfile->AppendText(_("\nTerminating the regression process!\n"));
    }
}

void MainFrame::BtnCppCode_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("C++ Code (*.cpp)|*.cpp")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("cpp"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        GenerateCode(dgPath, BaseName, _("Cpp"), 1, false);
	}
    
	OpenDialog->Destroy();
}

void MainFrame::BtnCCode_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("C Code (*.c)|*.c")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("c"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        GenerateCode(dgPath, BaseName, _("C"), 1, false);
	}
    
	OpenDialog->Destroy();
}

void MainFrame::BtnFCode_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("Fortran Code (*.f90)|*.f90")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("f90"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        GenerateCode(dgPath, BaseName, _("Fortran90"), 1, false);
	}
    
	OpenDialog->Destroy();
}

void MainFrame::BtnMathematicaCode_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("Mathematica Notebook (*.nb)|*.nb")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("nb"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        GenerateCode(dgPath, BaseName, _("Mathematica"), 1, false);
	}
    
	OpenDialog->Destroy();
}

void MainFrame::BtnMatlabCode_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("Matlab Script File (*.m)|*.m")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("m"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        GenerateCode(dgPath, BaseName, _("Matlab"), 1, false);
	}
    
	OpenDialog->Destroy();
}

void MainFrame::BtnPythonCode_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("Python Script File (*.py)|*.py")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("py"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        GenerateCode(dgPath, BaseName, _("Python"), 1, false);
	}
    
	OpenDialog->Destroy();
}

void MainFrame::BtnPyBinding_OnClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("Python Script File (*.py)|*.py")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("py"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        GeneratePyBindingInput(dgPath, BaseName, 1);
	}
    
	OpenDialog->Destroy();
}

void MainFrame::BtnAbout_OnClick(wxRibbonButtonBarEvent& event)
{
    ShowAbout();
}

void MainFrame::ShowAbout()
{
    if (!IsLicensed)
    {
        //logfile->AppendText(_("\nThe free version of ") + SoftwareName + _(" has limitations in ") + FreeSoftwareLimitations + (". To eliminate all limitations you need a full featured license. To get a license you will need to supply the following serial number."));
        //logfile->AppendText(_("\n\nSerial Number:\n") + MySerialNumber +_("\n\n"));
    }
    else
    {
        
    }
    
    wxAboutDialogInfo info;
    wxIcon icn;
    icn.CopyFromBitmap(GetPng(icon256_png,icon256_png_size));
    info.SetIcon(icn);
    
    info.SetName(SoftwareName);
    info.SetVersion(wxString::Format(_("%d.%d.%d"), Ver_MAJOR, Ver_MINOR, Ver_RELEASE));
    info.SetDescription(_("A technical software application for constructing Tight-Binding Hamiltonian"));
    
    info.SetCopyright(_("GNU Lesser General Public License, 2019 Mohammad Nakhaee"));

    wxArrayString developers;
    developers.Add(_("This software was initiated and developed by Mohammad Nakhaee during his Ph.D. at\nPhysics department (CMT), Antwerp university, Antwerpen, Belgium.\nEmail: developer.support@tight-binding.com"));
    info.SetDevelopers(developers);
    
    
    wxAboutBox(info);
}

void MainFrame::BtnTutorials_OnClick(wxRibbonButtonBarEvent& event)
{
    wxLaunchDefaultBrowser(wxT("https://tight-binding.com/video-tutorials/"));
}

void MainFrame::BtnWebsite_OnClick(wxRibbonButtonBarEvent& event)
{
	wxLaunchDefaultBrowser(wxT("https://tight-binding.com/"));
    /*
	//1.5.0
	UpdateClass* update = new UpdateClass(this, MySerialNumber);
    update->CenterOnScreen();
    //welcome->CenterOnParent();
    update->ShowModal();
	//1.5.0
	*/
}

void MainFrame::LoadIcons()
{
    wxColour c1 = wxColour(wxT("rgb(133,160,190)"));
    //wxColour c2 = wxColour(wxT("rgb(13,98,124)"));
    wxColour c2 = wxColour(wxT("rgb(48,97,180)"));
    //MainRibbon->GetArtProvider()->SetColourScheme(c1, c2, c2);
    wxColour c3 = wxColour(wxT("rgb(93,111,142)"));
    MainRibbon->GetArtProvider()->SetColourScheme(c3, c2, c1);
    
    
    wxLog::SetLogLevel(0);
    
    wxIconBundle app_icons;
    {
        wxIcon icn;
        icn.CopyFromBitmap(GetPng(icon16_png,icon16_png_size));
        app_icons.AddIcon( icn );
    }
    {
        wxIcon icn;
        icn.CopyFromBitmap(GetPng(icon32_png,icon32_png_size));
        app_icons.AddIcon( icn );
    }
    {
        wxIcon icn;
        icn.CopyFromBitmap(GetPng(icon64_png,icon64_png_size));
        app_icons.AddIcon( icn );
    }
    {
        wxIcon icn;
        icn.CopyFromBitmap(GetPng(icon128_png,icon128_png_size));
        app_icons.AddIcon( icn );
    }
    {
        wxIcon icn;
        icn.CopyFromBitmap(GetPng(icon256_png,icon256_png_size));
        app_icons.AddIcon( icn );
    }
    SetIcons( app_icons );
    
    
    int myID;
    
    wxRibbonPage* RPageFile1 = new wxRibbonPage(MainRibbon, wxID_ANY, _("File"), wxNullBitmap, 0);
    wxRibbonPanel* RPanelProject = new wxRibbonPanel(RPageFile1, wxID_ANY, _("TB Model"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageFile1, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonButtonBar* RButtonBar1 = new wxRibbonButtonBar(RPanelProject, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelProject, wxSize(-1,-1)), 0);
    
    RButtonBar1->AddButton(wxID_OPEN, _("Open"), GetPng(open_png,open_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar1->Connect(wxID_OPEN, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnOpen_OnClick), NULL, this);
    
    RButtonBar1->AddButton(wxID_SAVE, _("Save"), GetPng(save_png,save_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar1->Connect(wxID_SAVE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnSave_OnClick), NULL, this);
    
    RButtonBar1->AddButton(wxID_SAVEAS, _("Save as"), GetPng(save_png,save_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar1->Connect(wxID_SAVEAS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnSaveAs_OnClick), NULL, this);
    
    RButtonBar1->AddButton(wxID_FIND, _("Cloud storage"), GetPng(cloud_png,cloud_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar1->Connect(wxID_FIND, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnCloud_OnClick), NULL, this);
    
    RButtonBar1->Realize();
    
    wxRibbonPage* RPageTools = new wxRibbonPage(MainRibbon, wxID_ANY, _("Tools"), wxNullBitmap, 0);
    wxRibbonPanel* RPanelStructure = new wxRibbonPanel(RPageTools, wxID_ANY, _("Structure"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageTools, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonButtonBar* RButtonBar2 = new wxRibbonButtonBar(RPanelStructure, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelStructure, wxSize(-1,-1)), 0);
    
    myID = wxID_SELECT_COLOR;
    RButtonBar2->AddButton(myID, _("Atoms and Bonds"), GetPng(colors_png,colors_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar2->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnStructureStyle_OnClick), NULL, this);
	
    RButtonBar2->Realize();
	
	
	
	
	
	
    
    wxRibbonPanel* RPanelMouse = new wxRibbonPanel(RPageTools, wxID_ANY, _("Mouse"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageTools, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    RButtonMouse = new wxRibbonButtonBar(RPanelMouse, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelMouse, wxSize(-1,-1)), 0);
    
    myID = wxID_FILE1;
    RButtonMouse->AddButton(myID, _("Select"), GetPng(select_png,select_png_size), _(""), wxRIBBON_BUTTON_TOGGLE);
    RButtonMouse->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnSelect_OnClick), NULL, this);
    
    myID = wxID_FILE2;
    RButtonMouse->AddButton(myID, _("Move"), GetPng(move_png,move_png_size), _(""), wxRIBBON_BUTTON_TOGGLE);
    RButtonMouse->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnMove_OnClick), NULL, this);
    
    myID = wxID_FILE3;
    RButtonMouse->AddButton(myID, _("Rotate"), GetPng(rotate_png,rotate_png_size), _(""), wxRIBBON_BUTTON_TOGGLE);
    RButtonMouse->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnRotate_OnClick), NULL, this);
    
    myID = wxID_FILE4;
    RButtonMouse->AddButton(myID, _("Zoom"), GetPng(zoom_png,zoom_png_size), _(""), wxRIBBON_BUTTON_TOGGLE);
    RButtonMouse->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnScale_OnClick), NULL, this);
    
    RButtonMouse->Realize();
    
    
    
    //wxRibbonPage* RPageView = new wxRibbonPage(MainRibbon, wxID_ANY, _("View"), wxNullBitmap, 0);
    wxRibbonPanel* RPanelCart = new wxRibbonPanel(RPageTools, wxID_ANY, _("Cartesian"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageTools, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonButtonBar* RButtonBar3 = new wxRibbonButtonBar(RPanelCart, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelCart, wxSize(-1,-1)), 0);
    
    myID = wxID_FILE1;
    RButtonBar3->AddButton(myID, _(""), GetPng(x_png,x_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar3->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnX_OnClick), NULL, this);
    
    myID = wxID_FILE2;
    RButtonBar3->AddButton(myID, _(""), GetPng(y_png,y_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar3->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnY_OnClick), NULL, this);
    
    myID = wxID_FILE3;
    RButtonBar3->AddButton(myID, _(""), GetPng(z_png,z_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar3->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnZ_OnClick), NULL, this);
    
    RButtonBar3->Realize();
    
    /*wxRibbonPanel* RPanelUnitcell = new wxRibbonPanel(RPageTools, wxID_ANY, _("Unit-cell"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageTools, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonButtonBar* RButtonBar4 = new wxRibbonButtonBar(RPanelUnitcell, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelUnitcell, wxSize(-1,-1)), 0);
    
    myID = wxID_FILE1;
    RButtonBar4->AddButton(myID, _(""), GetPng(a_png,a_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar4->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnA_OnClick), NULL, this);
    
    myID = wxID_FILE2;
    RButtonBar4->AddButton(myID, _(""), GetPng(b_png,b_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar4->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnB_OnClick), NULL, this);
    
    myID = wxID_FILE3;
    RButtonBar4->AddButton(myID, _(""), GetPng(c_png,c_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar4->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnC_OnClick), NULL, this);
    
    RButtonBar4->Realize();*/
    
    wxRibbonPanel* RPanelRotation = new wxRibbonPanel(RPageTools, wxID_ANY, _("Rotation"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageTools, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonButtonBar* RButtonBar5 = new wxRibbonButtonBar(RPanelRotation, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelRotation, wxSize(-1,-1)), 0);
    
    myID = wxID_FILE1;
    RButtonBar5->AddButton(myID, _(""), GetPng(up_png,up_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar5->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnUp_OnClick), NULL, this);
    
    myID = wxID_FILE2;
    RButtonBar5->AddButton(myID, _(""), GetPng(down_png,down_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar5->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnDown_OnClick), NULL, this);
    
    myID = wxID_FILE3;
    RButtonBar5->AddButton(myID, _(""), GetPng(left_png,left_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar5->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnLeft_OnClick), NULL, this);
    
    myID = wxID_FILE4;
    RButtonBar5->AddButton(myID, _(""), GetPng(right_png,right_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar5->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnRight_OnClick), NULL, this);
    
    RButtonBar5->Realize();
    
	RPanelStructure->Realize();
	
    wxRibbonPage* RPageCalculations = new wxRibbonPage(MainRibbon, wxID_ANY, _("Analyze"), wxNullBitmap, 0);
    wxRibbonPanel* RPanelFitting = new wxRibbonPanel(RPageCalculations, wxID_ANY, _("Fitting"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageCalculations, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonButtonBar* RButtonBar7 = new wxRibbonButtonBar(RPanelFitting, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelFitting, wxSize(-1,-1)), 0);
    
    myID = wxID_FILE1;
    RButtonBar7->AddButton(myID, _("Start"), GetPng(start_png,start_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar7->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnStart_OnClick), NULL, this);
    
    myID = wxID_FILE2;
    RButtonBar7->AddButton(myID, _("One Step"), GetPng(onestep_png,onestep_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar7->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnOnestep_OnClick), NULL, this);
    
    //myID = wxID_FILE3;
    //RButtonBar7->AddButton(myID, _("Pause"), GetPng(pause_png,pause_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    //RButtonBar7->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnPause_OnClick), NULL, this);
    
    myID = wxID_FILE4;
    RButtonBar7->AddButton(myID, _("Stop"), GetPng(stop_png,stop_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar7->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnStop_OnClick), NULL, this);
    
    RButtonBar7->Realize();

    wxRibbonPage* RPageWizard = new wxRibbonPage(MainRibbon, wxID_ANY, _("Wizard"), wxNullBitmap, 0);
    wxRibbonPanel* RPanelCodeGen = new wxRibbonPanel(RPageWizard, wxID_ANY, _("Code Generator"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageWizard, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonButtonBar* RButtonBarCG1 = new wxRibbonButtonBar(RPanelCodeGen, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelCodeGen, wxSize(-1,-1)), 0);
    
    myID = wxID_FILE1;
    RButtonBarCG1->AddButton(myID, _("C++"), GetPng(cppcode_png,cppcode_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBarCG1->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnCppCode_OnClick), NULL, this);
    
    myID = wxID_FILE2;
    RButtonBarCG1->AddButton(myID, _("C"), GetPng(ccode_png,ccode_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBarCG1->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnCCode_OnClick), NULL, this);
    
    myID = wxID_FILE3;
    RButtonBarCG1->AddButton(myID, _("Fortran"), GetPng(fcode_png,fcode_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBarCG1->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnFCode_OnClick), NULL, this);
    
    myID = wxID_FILE4;
    RButtonBarCG1->AddButton(myID, _("Mathematica"), GetPng(mathematicacode_png,mathematicacode_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBarCG1->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnMathematicaCode_OnClick), NULL, this);
    
    myID = wxID_FILE5;
    RButtonBarCG1->AddButton(myID, _("Matlab"), GetPng(matlabcode_png,matlabcode_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBarCG1->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnMatlabCode_OnClick), NULL, this);
    
    myID = wxID_FILE6;
    RButtonBarCG1->AddButton(myID, _("Python"), GetPng(pythoncode_png,pythoncode_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBarCG1->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnPythonCode_OnClick), NULL, this);
    
	myID = wxID_FILE7;
    RButtonBarCG1->AddButton(myID, _("PyBinding"), GetPng(pybinding_png,pybinding_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBarCG1->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnPyBinding_OnClick), NULL, this);
    
    RButtonBarCG1->Realize();
    
    wxRibbonPage* RPageHelp = new wxRibbonPage(MainRibbon, wxID_ANY, _("Help"), wxNullBitmap, 0);
    wxRibbonPanel* RPanelHelp = new wxRibbonPanel(RPageHelp, wxID_ANY, _("Help"), wxNullBitmap, wxDefaultPosition, wxDLG_UNIT(RPageHelp, wxSize(-1,-1)), wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonButtonBar* RButtonBar6 = new wxRibbonButtonBar(RPanelHelp, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(RPanelHelp, wxSize(-1,-1)), 0);
    
    myID = wxID_ABOUT;
    RButtonBar6->AddButton(myID, _("About"), GetPng(icon32_png,icon32_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar6->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnAbout_OnClick), NULL, this);
    
    myID = wxID_HELP;
    RButtonBar6->AddButton(myID, _("Tutorials"), GetPng(tutorials_png,tutorials_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar6->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnTutorials_OnClick), NULL, this);
    
    myID = wxID_HELP_SEARCH;
    RButtonBar6->AddButton(myID, _("Update"), GetPng(update_png,update_png_size), _(""), wxRIBBON_BUTTON_NORMAL);
    RButtonBar6->Connect(myID, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, wxRibbonButtonBarEventHandler(MainFrame::BtnWebsite_OnClick), NULL, this);
    
    RButtonBar6->Realize();
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    MainRibbon->SetActivePage(RPageFile1);
    MainRibbon->Realize();
}

wxBitmap MainFrame::GetPng(const void* data, size_t length)
{
    wxMemoryInputStream memIStream(data, length);
    wxImage image(memIStream, wxBITMAP_TYPE_PNG );
    wxBitmap bmp( image );
    return bmp;
}

void MainFrame::GetHamiltonianMap(wxCheckTree* orbs, Astring0D &HamiltonianMap, Astring0D &HamiltonianShellMap, Aint1D &HamiltonianDimMap)
{
    //Clear All labels in Projection panel after the nAtoms. It will be set later as long as the lines are valid in unitcell panel
    int nAtom=0;
    sec30->GetVar(_("nAtoms[0]"),nAtom);
    HamiltonianMap.clear();
    HamiltonianShellMap.clear();
    HamiltonianDimMap.clear();
    int LastIndex = 0;
    for (int iAtom = 0; iAtom<nAtom; iAtom++)
    {
        wxString TBatomObjectName = wxString::Format(wxT("AtomInd%d"),iAtom + 1);
        wxComboBox* comb = sec30->GetComboObject(TBatomObjectName);
        wxString TBAtom = comb->GetStringSelection();
        Aint0D HamiltonianDimMapItem; //The index of the shell in Hamiltonian
        AddShellAndOrbitalInfo(orbs, TBAtom, HamiltonianMap, HamiltonianShellMap, HamiltonianDimMapItem, LastIndex);
        HamiltonianDimMap.push_back(HamiltonianDimMapItem);
    }
}

void MainFrame::AddShellAndOrbitalInfo(wxCheckTree* orbsTree, wxString AtomName, Astring0D &HamiltonianMap, Astring0D &HamiltonianShellMap, Aint0D &HamiltonianDimMapItem, int &LastIndex)
{
    wxTreeItemId rootID = orbsTree->GetRootItem();
    wxString rootname = orbsTree->GetItemText(rootID);
    wxTreeItemId atomID = orbsTree->FindItemIn(rootID,AtomName);
    int ShellCount = orbsTree->GetChildrenCount(atomID,false);
    for (int ShellNumber = 1; ShellNumber <= ShellCount; ShellNumber++)
    {
        HamiltonianDimMapItem.push_back(LastIndex); //We count the number of active orbitals for all shells, but note that the value is valid only for the active shells. It will be the index of the Hamiltonian.
        wxString ShellName = wxString::Format(wxT("Shell %d"),ShellNumber);
        wxTreeItemId shellID = orbsTree->FindItemIn(atomID,ShellName);
        if (shellID.IsOk() && orbsTree->GetItemState(shellID) >= wxCheckTree::CHECKED)
        {
            int orbCnt = 0;
            wxTreeItemIdValue cookie;
            wxString ShellAdd = rootname + _("/") + AtomName + _("/") + ShellName;
            wxTreeItemId child = orbsTree->GetFirstChild(shellID, cookie);
            while( child.IsOk() )
            {
                if (orbsTree->GetItemState(child) >= wxCheckTree::CHECKED)
                {
                    orbCnt++;
                    wxString Add = ShellAdd + _("/") + orbsTree->GetItemText(child);
                    HamiltonianMap.push_back(Add);
                }
                child = orbsTree->GetNextChild(shellID, cookie);
            }
            
            if (orbCnt!=0)
            {
                HamiltonianShellMap.push_back(ShellAdd);
                LastIndex = LastIndex + orbCnt;
            }
        }
    }
}

void MainFrame::ReadSK()
{
    long bondtype;
    wxString val;
    myGrid* skctr = sec30->GetGridObject(_("SK"));
    int nRow = skctr->GetNumberRows();
    int Case = -1;
    for (int irow=0; irow<nRow;irow++)
    {
        val = skctr->GetCellValue(irow,0);
        if (val == _("On-Sites"))
        {
            Case = 0;
        }
        else if (val == _("SOC"))
        {
            Case = 1;
        }
        else if (val.StartsWith(_("Bond")))
        {
            Case = 2;
            val.Replace(_("Bond "), _(""));
            val.ToLong(&bondtype);
        }
        else if (val.StartsWith(_("Overlap")))
        {
            Case = 3;
            val.Replace(_("Overlap "), _(""));
            val.ToLong(&bondtype);
        }
        else
        {
            if (Case == 0)
            {
                
            }
            else if (Case == 1)
            {
                
            }
            else if (Case == 2)
            {
                
            }
            else if (Case == 3)
            {
                
            }
        }
    }
    
    if (Case == -1) {wxMessageBox(_("SK parameters were not set."),_("Error")); return;}
}

void MainFrame::TestEig()
{
    /* Locals */
    int n = 5, lda = 5, info;
    /* Local arrays */
    double w[5];
    double a[5*5] = {
        1.96, -6.49, -0.47, -7.20, -0.65,
        0.00,  3.80, -6.39,  1.50, -6.34,
        0.00,  0.00, 4.17, -1.51, 2.67,
        0.00,  0.00, 0.00,  5.70, 1.80,
        0.00,  0.00, 0.00,  0.00, -7.10
    };
    
    info = LAPACKE_dsyev( LAPACK_ROW_MAJOR, 'N', 'U', n, a, lda, w);
    
    /* Check for convergence */
    if( info > 0 ) {
        printf( "The algorithm failed to compute eigenvalues.\n" );
        exit( 1 );
    }
}

void MainFrame::TestZEig()
{
    /* Locals */
        lapack_int n = 4, lda = 4, info;
        /* Local arrays */
        double w[4];
        lapack_complex_double a[4*4] = {
           { 9.14,  0.00}, {-4.37,  9.22}, {-1.98,  1.72}, {-8.96,  9.50},
           { 0.00,  0.00}, {-3.35,  0.00}, { 2.25,  9.51}, { 2.57, -2.40},
           { 0.00,  0.00}, { 0.00,  0.00}, {-4.82,  0.00}, {-3.24, -2.04},
           { 0.00,  0.00}, { 0.00,  0.00}, { 0.00,  0.00}, { 8.44,  0.00}
        };
        /* Solve eigenproblem */
        info = LAPACKE_zheev( LAPACK_ROW_MAJOR, 'V', 'U', n, a, lda, w );
        /* Check for convergence */
        if( info > 0 ) {
                printf( "The algorithm failed to compute eigenvalues.\n" );
                exit( 1 );
        }
}

void MainFrame::UpdateTBBand_if()
{
    sec30->isMainThread = true;
    bool isBandLoaded;
    if (sec30->ArraysOf0DInt[0] != 0) isBandLoaded = true;
    if (!isBandLoaded) return;
    int nKPoint = sec30->ArraysOf0DInt[1];
    if (nKPoint < 1)  return;
    
    double a[3],b[3],c[3];
    sec30->GetVar(_("a[0]"), a[0]);
    sec30->GetVar(_("a[1]"), a[1]);
    sec30->GetVar(_("a[2]"), a[2]);
    sec30->GetVar(_("b[0]"), b[0]);
    sec30->GetVar(_("b[1]"), b[1]);
    sec30->GetVar(_("b[2]"), b[2]);
    sec30->GetVar(_("c[0]"), c[0]);
    sec30->GetVar(_("c[1]"), c[1]);
    sec30->GetVar(_("c[2]"), c[2]);
    
    double ak[3],bk[3],ck[3];
    sec30->VecToReciprocal(a, b, c, ak, bk, ck);
    
    int natoms = 0;
    sec30->GetVar(_("nAtoms[0]"),natoms);
    double** XYZCoords = new double*[natoms];
    for (int i=0; i<natoms; i++) XYZCoords[i] = new double[3];
    
    myGrid* xyzgc =  sec30->GetGridObject(_("XYZ_Coords"));
    wxString val;
    double x, y, z;
    for (int i0=0; i0<natoms; i0++)
    {
        val = xyzgc->GetCellValue(i0, 0);
        val.ToDouble(&x);
        val = xyzgc->GetCellValue(i0, 1);
        val.ToDouble(&y);
        val = xyzgc->GetCellValue(i0, 2);
        val.ToDouble(&z);
        XYZCoords[i0][0] = x;
        XYZCoords[i0][1] = y;
        XYZCoords[i0][2] = z;
    }
    
    Adouble2D Hi, Si, Hf, Sf, SOC_i, SOC_f;
    int nEssensialCells;
    int nHamiltonian;
    Aint1D EssCells;
    
    bool isSOC;
    sec30->GetCheckVar(_("SOC[0]"), isSOC);
    bool isOverlap;
    sec30->GetCheckVar(_("Overlap[0]"), isOverlap);
    
    bool isSpin = false;
    if (isSOC) isSpin = true;
    
    if(isOverlap)
        sec30->ConstructTBHamiltonian(a, b, c, XYZCoords, Hi, Hf, Si, Sf, nEssensialCells, nHamiltonian, EssCells, isSOC, SOC_i, SOC_f);
    else
        sec30->ConstructTBHamiltonian(a, b, c, XYZCoords, Hi, Hf, nEssensialCells, nHamiltonian, EssCells, isSOC, SOC_i, SOC_f);
        
    
    for (int i=0; i<natoms; i++) delete [] XYZCoords[i];
    if (natoms>0) delete [] XYZCoords;
    
    sec30->ArraysOf3DDouble[0] = Hi;
    sec30->ArraysOf3DDouble[1] = Hf;
    sec30->ArraysOf3DDouble[2] = Si;
    sec30->ArraysOf3DDouble[3] = Sf;
    if (isSOC)
    {
        sec30->ArraysOf3DDouble[4] = SOC_i;
        sec30->ArraysOf3DDouble[5] = SOC_f;
    }
    else
    {
        sec30->ArraysOf3DDouble[4] = Adouble2D();
        sec30->ArraysOf3DDouble[5] = Adouble2D();
    }
    
    if (nEssensialCells < 1) return;
    if (nHamiltonian < 1) return;
    
    //double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    Adouble1D KPoints = sec30->ArraysOf2DDouble[0];
    
    //////////////////////////////Allocate all arrays//////////////////////////////////
    int** lmnEssCells = new int*[nEssensialCells];
    double*** Mi = new double**[nEssensialCells];
    double*** Mf = new double**[nEssensialCells];
    double*** sMi;
    double*** sMf;
    if(isOverlap)
    {
        sMi = new double**[nEssensialCells];
        sMf = new double**[nEssensialCells];
    }
    
    for(int iECell = 0; iECell < nEssensialCells; iECell++)
    {
        lmnEssCells[iECell] = new int[3];
        Mi[iECell] = new double*[nHamiltonian];
        Mf[iECell] = new double*[nHamiltonian];
        for(int i = 0; i < nHamiltonian; i++)
        {
            Mi[iECell][i] = new double[nHamiltonian];
            Mf[iECell][i] = new double[nHamiltonian];
        }
    }
    
    if(isOverlap)
    {
        for(int iECell = 0; iECell < nEssensialCells; iECell++)
        {
            sMi[iECell] = new double*[nHamiltonian];
            sMf[iECell] = new double*[nHamiltonian];
            for(int i = 0; i < nHamiltonian; i++)
            {
                sMi[iECell][i] = new double[nHamiltonian];
                sMf[iECell][i] = new double[nHamiltonian];
            }
        }
    }
    //////////////////////////////Fill all arrays//////////////////////////////////
    for(int iECell = 0; iECell < nEssensialCells; iECell++)
    {
        for(int i = 0; i < 3; i++) lmnEssCells[iECell][i] = EssCells[iECell][i];
        for(int i = 0; i < nHamiltonian; i++)
            for(int j = 0; j < nHamiltonian; j++)
            {
                Mi[iECell][i][j] = Hi[iECell][i][j];
                Mf[iECell][i][j] = Hf[iECell][i][j];
            }
    }
    
    if(isOverlap)
    {
        for(int iECell = 0; iECell < nEssensialCells; iECell++)
        {
            for(int i = 0; i < nHamiltonian; i++)
                for(int j = 0; j < nHamiltonian; j++)
                {
                    sMi[iECell][i][j] = Si[iECell][i][j];
                    sMf[iECell][i][j] = Sf[iECell][i][j];
                }
        }
    }
    /////////////////////////Calculate the TB Band-structure////////////////////////
    lapack_complex_double* LowerSymMatrixHi;
    lapack_complex_double* LowerSymMatrixHf;
    lapack_complex_double* LowerSymMatrixSi;
    lapack_complex_double* LowerSymMatrixSf;
    double* eigHi;
    double* eigHf;
    
    int nHamiltonianTot;
    if (isSpin)
        nHamiltonianTot = 2*nHamiltonian;
    else
        nHamiltonianTot = nHamiltonian;
    
    int nH2 = nHamiltonianTot*nHamiltonianTot;
    eigHi = new double[nHamiltonianTot];
    eigHf = new double[nHamiltonianTot];
    
    Adouble1D iTBEigVal(nKPoint,std::vector<double>(nHamiltonianTot));
    Adouble1D fTBEigVal(nKPoint,std::vector<double>(nHamiltonianTot));
    
    lapack_complex_double lzerocomplex = {0.0, 0.0};
    
    int nOverlapMat = (nHamiltonianTot+nH2) + 1;
    if(isOverlap)
    {
        LowerSymMatrixHi = new lapack_complex_double[nOverlapMat];
        LowerSymMatrixHf = new lapack_complex_double[nOverlapMat];
        LowerSymMatrixSi = new lapack_complex_double[nOverlapMat];
        LowerSymMatrixSf = new lapack_complex_double[nOverlapMat];
        for(int i=0; i<nOverlapMat; i++)
        {
            LowerSymMatrixHi[i] = lzerocomplex;
            LowerSymMatrixHf[i] = lzerocomplex;
            LowerSymMatrixSi[i] = lzerocomplex;
            LowerSymMatrixSf[i] = lzerocomplex;
        }
    }
    else
    {
        LowerSymMatrixHi = new lapack_complex_double[nH2];
        LowerSymMatrixHf = new lapack_complex_double[nH2];
        for(int i=0; i<nH2; i++)
        {
            LowerSymMatrixHi[i] = lzerocomplex;
            LowerSymMatrixHf[i] = lzerocomplex;
        }
    }
    
    for (int ik=0; ik<nKPoint; ik++)
    {
        double frac[3] = {KPoints[ik][0], KPoints[ik][1], KPoints[ik][2]};
        double absol[3];
        sec30->FracToAbs(ak, bk, ck, frac, absol);
        double kx = absol[0];
        double ky = absol[1];
        double kz = absol[2];
        
        //kx = KPoints[ik][3];
        //ky = KPoints[ik][4];
        //kz = KPoints[ik][5];
        
        if (isSpin)
        {
            lapack_complex_double cmlx;
            if(isOverlap)
            {
                for(int i=0; i<nOverlapMat; i++)
                {
                    LowerSymMatrixHi[i] = lzerocomplex;
                    LowerSymMatrixSi[i] = lzerocomplex;
                }
                
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = 2*(iH - jH); // i1 = (2*iH) - (2*jH);
                        LowerSymMatrixHi[i1 * nHamiltonianTot + 2*iH] = sec30->GetHk(Mi, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixSi[i1 * nHamiltonianTot + 2*iH] = sec30->GetHk(sMi, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixHi[i1 * nHamiltonianTot + 2*iH + 1] = LowerSymMatrixHi[i1 * nHamiltonianTot + 2*iH];
                        LowerSymMatrixSi[i1 * nHamiltonianTot + 2*iH + 1] = LowerSymMatrixSi[i1 * nHamiltonianTot + 2*iH];
                    }
                }
                
                //Add SOC to Hk
                for(int iH=0; iH<nHamiltonianTot; iH++)
                {
                    eigHi[iH] = 0.0;
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = iH - jH;
                        cmlx = {SOC_i[0][iH][jH], SOC_i[1][iH][jH]}; // Real and Imaginary parts of SOC are [0] and [1]
                        LowerSymMatrixHi[i1 * nHamiltonianTot + iH] += cmlx;
                    }
                }
            }
            else
            {
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    for(int jH=0; jH<=iH; jH++)
                    {
                        LowerSymMatrixHi[2*iH * nHamiltonianTot + 2*jH] = sec30->GetHk(Mi, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixHi[2*iH * nHamiltonianTot + 2*jH + 1] = lzerocomplex;
                        LowerSymMatrixHi[(2*iH + 1) * nHamiltonianTot + 2*jH + 1] = LowerSymMatrixHi[2*iH * nHamiltonianTot + 2*jH];
                        LowerSymMatrixHi[(2*iH + 1) * nHamiltonianTot + 2*jH] = lzerocomplex;
                    }
                }

                //Add SOC to Hk
                for(int iH=0; iH<nHamiltonianTot; iH++)
                {
                    eigHi[iH] = 0.0;
                    for(int jH=0; jH<=iH; jH++)
                    {
                        cmlx = {SOC_i[0][iH][jH], SOC_i[1][iH][jH]}; // Real and Imaginary parts of SOC are [0] and [1]
                        LowerSymMatrixHi[iH * nHamiltonianTot + jH] += cmlx;
                    }
                }
            }
        }
        else
        {
            if(isOverlap)
            {
                for(int i=0; i<nOverlapMat; i++)
                {
                    LowerSymMatrixHi[i] = lzerocomplex;
                    LowerSymMatrixSi[i] = lzerocomplex;
                }
                
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    eigHi[iH] = 0.0;
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = iH - jH;
                        LowerSymMatrixHi[i1 * nHamiltonianTot + iH] = sec30->GetHk(Mi, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixSi[i1 * nHamiltonianTot + iH] = sec30->GetHk(sMi, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                    }
                }
            }
            else
            {
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    eigHi[iH] = 0.0;
                    for(int jH=0; jH<=iH; jH++)
                    {
                        LowerSymMatrixHi[iH * nHamiltonianTot + jH] = sec30->GetHk(Mi, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                    }
                }
            }
        }
        
        int checki;
        
        if(isOverlap)
            checki = sec30->SymEigenValues(LowerSymMatrixHi, LowerSymMatrixSi, nHamiltonianTot, eigHi);
        else
            checki = sec30->SymEigenValues(LowerSymMatrixHi, nHamiltonianTot, eigHi);
        
        for(int iH=0; iH<nHamiltonianTot; iH++) iTBEigVal[ik][iH] = eigHi[iH];
        
        if (isSpin)
        {
            lapack_complex_double cmlx;
            if(isOverlap)
            {
                for(int i=0; i<nOverlapMat; i++)
                {
                    LowerSymMatrixHf[i] = lzerocomplex;
                    LowerSymMatrixSf[i] = lzerocomplex;
                }
                
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = 2*(iH - jH); // i1 = (2*iH) - (2*jH);
                        LowerSymMatrixHf[i1 * nHamiltonianTot + 2*iH] = sec30->GetHk(Mf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixSf[i1 * nHamiltonianTot + 2*iH] = sec30->GetHk(sMf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixHf[i1 * nHamiltonianTot + 2*iH + 1] = LowerSymMatrixHf[i1 * nHamiltonianTot + 2*iH];
                        LowerSymMatrixSf[i1 * nHamiltonianTot + 2*iH + 1] = LowerSymMatrixSf[i1 * nHamiltonianTot + 2*iH];
                    }
                }
                
                //Add SOC to Hk
                for(int iH=0; iH<nHamiltonianTot; iH++)
                {
                    eigHf[iH] = 0.0;
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = iH - jH;
                        cmlx = {SOC_f[0][iH][jH], SOC_f[1][iH][jH]};// Real and Imaginary parts of SOC are [0] and [1]
                        LowerSymMatrixHf[i1 * nHamiltonianTot + iH] += cmlx;
                    }
                }
            }
            else
            {
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    for(int jH=0; jH<=iH; jH++)
                    {
                        LowerSymMatrixHf[2*iH * nHamiltonianTot + 2*jH] = sec30->GetHk(Mf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixHf[2*iH * nHamiltonianTot + 2*jH + 1] = lzerocomplex;
                        LowerSymMatrixHf[(2*iH + 1) * nHamiltonianTot + 2*jH + 1] = LowerSymMatrixHf[2*iH * nHamiltonianTot + 2*jH];
                        LowerSymMatrixHf[(2*iH + 1) * nHamiltonianTot + 2*jH] = lzerocomplex;
                    }
                }
                
                //Add SOC to Hk
                for(int iH=0; iH<nHamiltonianTot; iH++)
                {
                    eigHf[iH] = 0.0;
                    for(int jH=0; jH<=iH; jH++)
                    {
                        cmlx = {SOC_f[0][iH][jH], SOC_f[1][iH][jH]};// Real and Imaginary parts of SOC are [0] and [1]
                        LowerSymMatrixHf[iH * nHamiltonianTot + jH] += cmlx;
                    }
                }
            }
        }
        else
        {
            if(isOverlap)
            {
                for(int i=0; i<nOverlapMat; i++)
                {
                    LowerSymMatrixHf[i] = lzerocomplex;
                    LowerSymMatrixSf[i] = lzerocomplex;
                }
                
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    eigHf[iH] = 0.0;
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = iH - jH;
                        LowerSymMatrixHf[i1 * nHamiltonianTot + iH] = sec30->GetHk(Mf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixSf[i1 * nHamiltonianTot + iH] = sec30->GetHk(sMf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                    }
                }
            }
            else
            {
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    eigHf[iH] = 0.0;
                    for(int jH=0; jH<=iH; jH++)
                    {
                        LowerSymMatrixHf[iH * nHamiltonianTot + jH] = sec30->GetHk(Mf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                    }
                }
            }
        }
        
        int checkf;
        
        if(isOverlap)
            checkf = sec30->SymEigenValues(LowerSymMatrixHf, LowerSymMatrixSf, nHamiltonianTot, eigHf);
        else
            checkf = sec30->SymEigenValues(LowerSymMatrixHf, nHamiltonianTot, eigHf);
        
        for(int iH=0; iH<nHamiltonianTot; iH++) fTBEigVal[ik][iH] = eigHf[iH];
    }
    
    delete [] LowerSymMatrixHi;
    delete [] LowerSymMatrixHf;
    if(isOverlap)
    {
        delete [] LowerSymMatrixSi;
        delete [] LowerSymMatrixSf;
    }
    delete [] eigHi;
    delete [] eigHf;
    
    sec30->ArraysOf2DDouble[2] = iTBEigVal;
    sec30->ArraysOf2DDouble[3] = fTBEigVal;
    
    //////////////////////////////Deallocate all arrays//////////////////////////////////
    for(int iECell = 0; iECell < nEssensialCells; iECell++)
    {
        for(int i = 0; i < nHamiltonian; i++)
        {
            delete [] Mi[iECell][i];
            delete [] Mf[iECell][i];
        }
        delete [] Mi[iECell];
        delete [] Mf[iECell];
        
        if(isOverlap)
        {
            for(int i = 0; i < nHamiltonian; i++)
            {
                delete [] sMi[iECell][i];
                delete [] sMf[iECell][i];
            }
            delete [] sMi[iECell];
            delete [] sMf[iECell];
        }
        
        delete [] lmnEssCells[iECell];
    }
    
    if (nEssensialCells>0) delete [] Mi;
	if (nEssensialCells>0) delete [] Mf;
    
    if(isOverlap)
    {
        if (nEssensialCells>0) delete [] sMi;
        if (nEssensialCells>0) delete [] sMf;
    }
    
    if (nEssensialCells>0) delete [] lmnEssCells;
}

void MainFrame::StartRegression(bool isOneStep)
{
    sec30->isMainThread = true;
	wxCheckTree* orbs;
	wxListBox* TBlistctr;
	int TBnspec;
	wxTreeItemId orbsrootID;
	wxComboBox* ctrm;
	bool isAny_d_Orbital, isBandLoaded, isAllvalid, isMatchVector;
	int TotalNumberOfParameters, prnt, MaxIter, Update_Type, MethodSel, natoms, np,ny,nc;
    double epsilon_1, epsilon_2, epsilon_3, epsilon_4, lambda_0, lambda_UP_fac, lambda_DN_fac;
    double p_min, p_max, Mixing, RescaleFactor;
	int TBBandFirst, TBBandLast, DFTFirst, nKPoint, idftBand, nFitPoints, indx;
	lmOptions opts;
    Aint1D FitPoints;
	double a[3],b[3],c[3], akTB[3], bkTB[3], ckTB[3], akDFT[3], bkDFT[3], ckDFT[3];
	double thershold, x, y, z, ChemP, shift;
	myGrid* xyzgc;
	wxString val;
	bool isFittingParametersValid;
	
	try
	{
		//The order of these functions are very important, because ValidateSKPanel() make SK list Valid
		//if (!ValidateSKParametersList()) {wxMessageBox(_(""),_("Error"));return;}
		if ( (!ValidateSKPanel()) || (!ValidateSKParametersList()) ) {wxMessageBox(_("The constructed TB model is not passable. Please fix the errors reported in the terminal and try again. Maybe, You have made some changes in the settings of your TB model and now the fitting parameters in SK panel are not valid. Please update the independent parameters in the SK panel.\n\n SK Panel -> Evaluate Independent Parameters"),_("Error"));return;}
		
		orbs = sec30->GetTreeObject(_("Orbitals"));
		TBlistctr = sec30->GetListObject(_("AtomSpeciesList"));
		TBnspec = TBlistctr->GetCount();
		orbsrootID = orbs->GetRootItem();
		
		isAny_d_Orbital = false;
		for(int j=0; j<TBnspec; j++)
		{
			wxString TBAtomName = TBlistctr->GetString(j);
			wxTreeItemId orbsatomID = orbs->FindItemIn(orbsrootID,TBAtomName);
			wxTreeItemIdValue cookie;
			wxTreeItemId nextChild = orbs->GetFirstChild(orbsatomID, cookie);
			int shellNumber=0;
			while (nextChild.IsOk())
			{
				shellNumber++;
				wxString itemname = orbs->GetItemText(nextChild);
				wxString Orbs;
				int nOrbs;
				bool IsShell;
				sec30->GetOrbitalInfo(orbs, TBAtomName, shellNumber, Orbs, nOrbs, IsShell);
				if (Orbs.Contains(_("d_{")))
				{
					isAny_d_Orbital=true;
					break;
				}
				nextChild = orbs->GetNextSibling(nextChild);
			}
			if (isAny_d_Orbital) break;
		}
		
		if (isAny_d_Orbital)
		{
			//if (!IsLicensed) {wxMessageBox(_("In the case of fitting a TB model including d-orbitals you need to contact developer support. Please find the contact information in Help>About."),_("Error"));return;}
		}
		
		//Show the SK Tab
		LeftPanel->ChangeSelection(4);
		
		sec30->GetVar(_("nParameters[0]"), TotalNumberOfParameters);
		if (TotalNumberOfParameters<1) {wxMessageBox(_("First evaluate independent parameters."),_("Error"));return;}
		
		isBandLoaded = false;
		if (sec30->ArraysOf0DInt[0] != 0) isBandLoaded = true;
		if (!isBandLoaded) {wxMessageBox(_("DFT band-structure has not yet been loaded."),_("Error"));return;}

		ctrm =  sec30->GetComboObject(_("OMethod"));
		MethodSel = ctrm->GetSelection();
		if (MethodSel==0)
			Update_Type = 3;
		else if (MethodSel==1)
			Update_Type = 1;
		else if (MethodSel==2)
			Update_Type = 2;
		
		isAllvalid = true;
		isAllvalid = isAllvalid && sec30->GetVar(_("OPrnt[0]"), prnt);
		isAllvalid = isAllvalid && sec30->GetVar(_("OMaxIter[0]"), MaxIter);
		isAllvalid = isAllvalid && sec30->GetVar(_("Oeps1[0]"), epsilon_1);
		isAllvalid = isAllvalid && sec30->GetVar(_("Oeps2[0]"), epsilon_2);
		isAllvalid = isAllvalid && sec30->GetVar(_("Oeps3[0]"), epsilon_3);
		isAllvalid = isAllvalid && sec30->GetVar(_("Oeps4[0]"), epsilon_4);
		isAllvalid = isAllvalid && sec30->GetVar(_("OLam0[0]"), lambda_0);
		isAllvalid = isAllvalid && sec30->GetVar(_("OLamUp[0]"), lambda_UP_fac);
		isAllvalid = isAllvalid && sec30->GetVar(_("OLamDn[0]"), lambda_DN_fac);
		isAllvalid = isAllvalid && sec30->GetVar(_("OMaxP[0]"), p_max);
		isAllvalid = isAllvalid && sec30->GetVar(_("OMinP[0]"), p_min);
		isAllvalid = isAllvalid && sec30->GetVar(_("OMixing[0]"), Mixing);
		isAllvalid = isAllvalid && sec30->GetVar(_("OReScale[0]"), RescaleFactor);
		
		if (!isAllvalid) {wxMessageBox(_("Invalid value in Fitting Algorithmic Parameters."),_("Error"));return;}
		if (MaxIter<1) {wxMessageBox(_("Invalid value for Iteration Limit."),_("Error"));return;}
		if (prnt<1) {wxMessageBox(_("Invalid value for Figure Updating Step."),_("Error"));return;}
		if (prnt>MaxIter) {wxMessageBox(_("Figure Updating Step must be smaller than Iteration Limit."),_("Error"));return;}
		if (epsilon_1<0.000001) {wxMessageBox(_("Invalid value for Gradient Threshold. >0.000001"),_("Error"));return;}
		if (epsilon_2<0.000001) {wxMessageBox(_("Invalid value for Parameters Threshold. >0.000001"),_("Error"));return;}
		if (epsilon_3<0.000001) {wxMessageBox(_("Invalid value for Reduced Chi-squared Threshold. >0.000001"),_("Error"));return;}
		if (epsilon_4<0.000001) {wxMessageBox(_("Invalid value for L-M Acceptance. >0.000001"),_("Error"));return;}
		if (lambda_0<0.000001) {wxMessageBox(_("Invalid value for L-M Lambda0. >0.000001"),_("Error"));return;}
		if (lambda_UP_fac<0.000001) {wxMessageBox(_("Invalid value for Increasing Lambda. >0.000001"),_("Error"));return;}
		if (lambda_DN_fac<0.000001) {wxMessageBox(_("Invalid value for Decreasing Lambda. >0.000001"),_("Error"));return;}
		if (p_max<p_min) {wxMessageBox(_("Parameters Minimum Limit must be smaller than Parameters Maximum Limit."),_("Error"));return;}
		if (!(Mixing > 0 && Mixing <= 1.0)) {wxMessageBox(_("Invalid value for Mixing Factor. >0 and <=1.0"),_("Error"));return;}
		if (RescaleFactor<0.000001) {wxMessageBox(_("Invalid value for Rescale Factor. >0.000001"),_("Error"));return;}

		isAllvalid = isAllvalid && sec30->GetVar(_("TBBandRange[0]"), TBBandFirst);
		isAllvalid = isAllvalid && sec30->GetVar(_("TBBandRange[1]"), TBBandLast);
		isAllvalid = isAllvalid && sec30->GetVar(_("DFTFirst[0]"), DFTFirst);
		if (!isAllvalid) {wxMessageBox(_("Invalid value in Fitting Customization."),_("Error"));return;}
		if (TBBandFirst<1) {wxMessageBox(_("Invalid value(s) for TB Bands Range."),_("Error"));return;}
		if (TBBandLast<1) {wxMessageBox(_("Invalid value(s) for TB Bands Range."),_("Error"));return;}
		if (TBBandFirst>TBBandLast) {wxMessageBox(_("Invalid value(s) for TB Bands Range."),_("Error"));return;}
		if (DFTFirst<1) {wxMessageBox(_("Invalid value for DFT First Band."),_("Error"));return;}

		nKPoint = sec30->ArraysOf0DInt[1];
		if (nKPoint < 1) {wxMessageBox(_("Something went wrong with the number of k-points."),_("Error"));return;}
		
		opts.prnt = prnt;             // >1 intermediate results; >2 plots
		opts.MaxIter = MaxIter;          // maximum number of iterations
		opts.epsilon_1 = epsilon_1;        // convergence tolerance for gradient
		opts.epsilon_2 = epsilon_2;        // convergence tolerance for parameters
		opts.epsilon_3 = epsilon_3;        // convergence tolerance for Chi-square
		opts.epsilon_4 = epsilon_4;        // determines acceptance of a L-M step
		opts.lambda_0 = lambda_0;         // initial value of damping paramter, lambda
		opts.lambda_UP_fac = lambda_UP_fac;    // factor for increasing lambda
		opts.lambda_DN_fac = lambda_DN_fac;    // factor for decreasing lambda
		opts.Update_Type = Update_Type;      // 1: Levenberg-Marquardt lambda update
		
		idftBand = DFTFirst - 1;
		for (int iband=TBBandFirst; iband<=TBBandLast; iband++)
		{
			idftBand++;
			for (int ik = 0; ik<nKPoint; ik++)
			{
				Aint0D FitPoint;
				int iReplaceddftBand = ReplaceDFTBand(idftBand,ik);
				FitPoint.push_back(iband);
				FitPoint.push_back(iReplaceddftBand);
				FitPoint.push_back(ik);
				//FitPoint.push_back(WeightPercentages[idftBand][ik]);
				FitPoints.push_back(FitPoint);
			}
		}
		
		sec30->ArraysOf2DInt[2] = FitPoints;
		
		nFitPoints = FitPoints.size();
		if (nFitPoints < 1) {wxMessageBox(_("No reference data for regression procedure."),_("Error"));return;}
		if (nFitPoints < TotalNumberOfParameters) {wxMessageBox(_("Non sufficient reference data for regression procedure."),_("Error"));return;}
		
		sec30->GetVar(_("a[0]"), a[0]);
		sec30->GetVar(_("a[1]"), a[1]);
		sec30->GetVar(_("a[2]"), a[2]);
		sec30->GetVar(_("b[0]"), b[0]);
		sec30->GetVar(_("b[1]"), b[1]);
		sec30->GetVar(_("b[2]"), b[2]);
		sec30->GetVar(_("c[0]"), c[0]);
		sec30->GetVar(_("c[1]"), c[1]);
		sec30->GetVar(_("c[2]"), c[2]);
		
		sec30->VecToReciprocal(a, b, c, akTB, bkTB, ckTB);
		
		for(int i=0; i<3; i++) akDFT[i] = sec30->ArraysOf1DDouble[1][i];
		for(int i=0; i<3; i++) bkDFT[i] = sec30->ArraysOf1DDouble[2][i];
		for(int i=0; i<3; i++) ckDFT[i] = sec30->ArraysOf1DDouble[3][i];
		
		isMatchVector = true;
		thershold = 0.00001;
		isMatchVector = isMatchVector && sec30->isMatch(akTB[0], akDFT[0], thershold);
		isMatchVector = isMatchVector && sec30->isMatch(akTB[1], akDFT[1], thershold);
		isMatchVector = isMatchVector && sec30->isMatch(akTB[2], akDFT[2], thershold);
		isMatchVector = isMatchVector && sec30->isMatch(bkTB[0], bkDFT[0], thershold);
		isMatchVector = isMatchVector && sec30->isMatch(bkTB[1], bkDFT[1], thershold);
		isMatchVector = isMatchVector && sec30->isMatch(bkTB[2], bkDFT[2], thershold);
		isMatchVector = isMatchVector && sec30->isMatch(ckTB[0], ckDFT[0], thershold);
		isMatchVector = isMatchVector && sec30->isMatch(ckTB[1], ckDFT[1], thershold);
		isMatchVector = isMatchVector && sec30->isMatch(ckTB[2], ckDFT[2], thershold);
		if (!isMatchVector)
		{
			wxMessageDialog dial(NULL, 
			  wxString::Format(wxT("Mismatch detected between lattice vectors of TB model and DFT data!\nDFT reciprocal lattice vectors:\na* = (%.8f,%.8f,%.8f)\nb* = (%.8f,%.8f,%.8f)\nc* = (%.8f,%.8f,%.8f)\nTB Model reciprocal lattice vectors:\na* = (%.8f,%.8f,%.8f)\nb* = (%.8f,%.8f,%.8f)\nc* = (%.8f,%.8f,%.8f)\nAre you sure you want to continue?"), akDFT[0], akDFT[1], akDFT[2], bkDFT[0], bkDFT[1], bkDFT[2], ckDFT[0], ckDFT[1], ckDFT[2], akTB[0], akTB[1], akTB[2], bkTB[0], bkTB[1], bkTB[2], ckTB[0], ckTB[1], ckTB[2]),
			  wxT("Warning"), 
			  wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
			if ( dial.ShowModal() == wxID_NO ) return;
		}
		
		natoms = 0;
		sec30->GetVar(_("nAtoms[0]"),natoms);
		
		np = TotalNumberOfParameters;
		ny = nFitPoints;
		nc = 3*natoms + 9;
		
		if (is_p) {delete [] p; is_p=false;}
		if (is_t) {delete [] t; is_t=false;}
		if (is_y_dat) {delete [] y_dat; is_y_dat=false;}
		if (is_weight) {delete [] weight; is_weight=false;}
		if (is_dp) {delete [] dp; is_dp=false;}
		if (is_cnst) {delete [] cnst; is_cnst=false;}
		//if (is_UpperSymMatrixHf) {delete [] UpperSymMatrixHf; is_UpperSymMatrixHf=false;}
		
		p = new double[np]; is_p=true;
		t = new double[ny]; is_t=true;
		y_dat = new double[ny]; is_y_dat=true;
		weight = new double[ny]; is_weight=true;
		dp = new double[np]; is_dp=true;
		cnst = new double[nc]; is_cnst=true;
		
		cnst[0] = a[0];
		cnst[1] = a[1];
		cnst[2] = a[2];
		cnst[3] = b[0];
		cnst[4] = b[1];
		cnst[5] = b[2];
		cnst[6] = c[0];
		cnst[7] = c[1];
		cnst[8] = c[2];
		
		xyzgc =  sec30->GetGridObject(_("XYZ_Coords"));
		indx=9;
		for (int i0=0; i0<natoms; i0++)
		{
			val = xyzgc->GetCellValue(i0, 0);
			val.ToDouble(&x);
			val = xyzgc->GetCellValue(i0, 1);
			val.ToDouble(&y);
			val = xyzgc->GetCellValue(i0, 2);
			val.ToDouble(&z);
			cnst[indx++] = x;
			cnst[indx++] = y;
			cnst[indx++] = z;
		}
		
		ChemP = sec30->ArraysOf0DDouble[0];
		shift = 0.0;
		for (int iy=0; iy<ny; iy++)
		{
			//int tbband = FitPoints[iy][0];
			int dftband = FitPoints[iy][1];
			int ik = FitPoints[iy][2];
			t[iy] = iy * 0.05;
			shift = ShiftBand(dftband,ik);
			y_dat[iy] = sec30->ArraysOf2DDouble[1][ik][dftband - 1] - ChemP + shift;
			weight[iy] = sec30->ArraysOf2DDouble[4][ik][dftband - 1];
		}
		
		for (int ip=0; ip<np; ip++)
		{
			p[ip] = GetFitParameter(ip, 1);//Get initial values for parameters
			dp[ip] = -0.01;
		}
		
		sec30->IsStopClicked = false;
		
	}
    catch(std::exception& ex)
    {
		wxMessageBox("Error (St-101): Something went wrong ...");
	}
    ////////////////////////////////
    //int nH2=64;
    //UpperSymMatrixHf = new lapack_complex_double[nH2]; is_UpperSymMatrixHf=true;
    //for (int i=0; i<nH2; i++) UpperSymMatrixHf[i] = {0.0,0.0};
    ////////////////////////////////
    try
	{
		//Start(double* p, int np, double* t, double* y_dat, int ny, double* weight, double* dp, double p_min, double p_max, double* c, lmOptions opts)
		std::thread RegressionThread(&Regression::Start, regression, p, np, t, y_dat, ny, weight, dp, p_min, p_max, Mixing, cnst, opts, isOneStep, sec30, this);
		//RegressionThreadMap = RegressionThread.native_handle();
		if(RegressionThread.joinable())
		{
			//std::cout<<"Detaching Thread "<<std::endl;
			RegressionThread.detach();
		}
		//RegressionThread.detach();
		//RegressionThread.join();
		//pthread_cancel(RegressionThreadMap);
	}
    catch(std::exception& ex)
    {
		wxMessageBox("Error (St-102): Something went wrong ...");
	}
    ////////////////It works well///////////////////////
    //Regression fitting(sec30, this);                //
    //long long num=400000000;                        //
    //std::thread trd(&Regression::foo, &fitting, num); //
    //trd.detach();                                     //
    ////////////////////////////////////////////////////
    
    //A pointer also works but not reliable
    //FittingThread = new std::thread(&Fitting::foo, &fitting, num);
}

int MainFrame::ReplaceDFTBand(int idftband, int ik)
{
    int newband = idftband;
    
    
    return newband;
}

double MainFrame::ShiftBand(int idftband, int ik)
{
    double shift = 0.0;
    
    
    return shift;
}

double MainFrame::GetFitParameter(int ip, int icol)
{
    //ip is the index of the parameter in the arra p         p[ip]
    int GridInd = sec30->ArraysOf2DInt[1][ip][0];
    int irow = sec30->ArraysOf2DInt[1][ip][1];
    
    myGrid* gc;
    if (GridInd == 1)
        gc = sec30->GetGridObject(_("OS"));
    else if (GridInd == 2)
        gc = sec30->GetGridObject(_("SK"));
    else if (GridInd == 3)
        gc = sec30->GetGridObject(_("OL"));
    
    double d = 0.0;
    wxString val = gc->GetCellValue(irow, icol);
    bool output = val.ToDouble(&d);
    if (!output) return 0.0;
    return d;
}

void MainFrame::regressionEVT_OnNewPlot(wxCommandEvent& event)
{
    //wxMessageBox(wxT("I am in OnNewPlot event."));
    graph2d->myRefresh2d();
} 
void MainFrame::regressionEVT_OnNewData(wxCommandEvent& event)
{
    logfile->AppendText(event.GetString());
	logfile->ShowPosition(logfile->GetLastPosition());
    //10000sec30->isPrinting = false;
	//logfile->SetScrollPos(wxVERTICAL,logfile->GetScrollRange(wxVERTICAL));
}

void MainFrame::regressionEVT_OnFinished(wxCommandEvent& event)
{
	
    if (is_p) {delete [] p; is_p=false;}
    if (is_t) {delete [] t; is_t=false;}
    if (is_y_dat) {delete [] y_dat; is_y_dat=false;}
    if (is_weight) {delete [] weight; is_weight=false;}
    if (is_dp) {delete [] dp; is_dp=false;}
    if (is_cnst) {delete [] cnst; is_cnst=false;}
	//pthread_cancel(RegressionThreadMap);
    //if (is_UpperSymMatrixHf) {delete [] UpperSymMatrixHf; is_UpperSymMatrixHf=false;}
    isFittingThreadBusy = false;
    
    myGrid* osgc = sec30->GetGridObject(_("OS"));
	myGrid* skgc = sec30->GetGridObject(_("SK"));
	myGrid* olgc = sec30->GetGridObject(_("OL"));
    
    osgc->Refresh(true);
    skgc->Refresh(true);
    olgc->Refresh(true);
    
    UpdateTBBand_if();
    UpdateGraph2Ds();
    this->Refresh(false);
}

void MainFrame::regressionEVT_OnStarted(wxCommandEvent& event)
{
    isFittingThreadBusy = true;
	logfile->Clear();
}

void MainFrame::figureClass_EVT_PlotFinished(wxCommandEvent& event)
{
    sec30->isPlotting = false;
    /*if (sec30->isPlotting)
    {
        wxMessageBox(wxT("MainFrame: sec30->isPlotting = true"));
    }
    else
    {
        wxMessageBox(wxT("MainFrame: sec30->isPlotting = false"));
    }*/
}

void MainFrame::ExportMatrices(wxString filepath, wxString BaseName, int MyID_Initial0Final1)
{
    int nKPoint = sec30->ArraysOf0DInt[1];
    if (nKPoint < 1)  return;
    
    //double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    Adouble1D KPoints = sec30->ArraysOf2DDouble[0];
    
    FILE *fpk;
    wxString fname = filepath + wxFileName::GetPathSeparator() + BaseName + wxT("_kPath") + wxT(".dat");
    if ((fpk = fopen(fname,"w")) != NULL)
    {
        for (int ik=0; ik<nKPoint; ik++)
        {
            double ka = KPoints[ik][0];
            double kb = KPoints[ik][1];
            double kc = KPoints[ik][2];
            double dpath = KPoints[ik][6];
            fprintf(fpk, "%.8f\t%.8f\t%.8f\t%.8f\n", ka, kb, kc, dpath);
        }
        fclose(fpk);
    }
    
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    int Sind = 2;
    int SOCind = 4;
    if (ID == 1)
    {
        Hind = 1;
        Sind = 3;
        SOCind = 5;
    }
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) return;
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) return;
    
    wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
    int nCell = listctr->GetCount();
    
    for (int iCell=0; iCell<nCell; iCell++)
    {
        wxString WorkingCell = listctr->GetString(iCell);
        
        FILE *fp;
        wxString fname1 = filepath + wxFileName::GetPathSeparator() + BaseName + wxT("_H") + WorkingCell + wxT(".dat");
        if ((fp = fopen(fname1,"w")) != NULL)
        {
            for (int iH=0; iH<nH; iH++)
            {
                fprintf(fp, "%.8f", sec30->ArraysOf3DDouble[Hind][iCell][iH][0]);
                for (int jH=1; jH<nH; jH++) fprintf(fp, "\t%.8f", sec30->ArraysOf3DDouble[Hind][iCell][iH][jH]);
                fprintf(fp, "\n");
            }
            fclose(fp);
        }
    }
    
    int nEssS = sec30->ArraysOf3DDouble[Sind].size();
    if (nEssS > 0)
    {
        int nS = sec30->ArraysOf3DDouble[Sind][0].size();
        if (nS > 0)
        {
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                
                FILE *fp;
                wxString fname1 = filepath + wxFileName::GetPathSeparator() + BaseName + wxT("_S") + WorkingCell + wxT(".dat");
                if ((fp = fopen(fname1,"w")) != NULL)
                {
                    for (int iS=0; iS<nS; iS++)
                    {
                        fprintf(fp, "%.8f", sec30->ArraysOf3DDouble[Sind][iCell][iS][0]);
                        for (int jS=1; jS<nS; jS++)
                        {
                            fprintf(fp, "\t%.8f", sec30->ArraysOf3DDouble[Sind][iCell][iS][jS]);
                        }
                        fprintf(fp, "\n");
                    }
                    fclose(fp);
                }
            }
        }
    }
    
    
    int nSOCBuf = sec30->ArraysOf3DDouble[SOCind].size();
    if (nSOCBuf == 2)
    {
        int nSOCReal = sec30->ArraysOf3DDouble[SOCind][0].size();
        int nSOCImage = sec30->ArraysOf3DDouble[SOCind][1].size();
        if (nSOCReal > 1 && nSOCImage == nSOCReal) //We have spin. so at least should be 2
        {
            int nH_SOC = sec30->ArraysOf3DDouble[SOCind][0][0].size();
            if (nH_SOC > 1) //We have spin. so at least should be 2
            {
                FILE *fpsocre;
                wxString fnamesocre = filepath + wxFileName::GetPathSeparator() + BaseName + wxT("_SOC_Re.dat");
                if ((fpsocre = fopen(fnamesocre,"w")) != NULL)
                {
                    for (int iH=0; iH<nSOCReal; iH++)
                    {
                        fprintf(fpsocre, "%.8f", sec30->ArraysOf3DDouble[SOCind][0][iH][0]);
                        for (int jH=1; jH<nSOCReal; jH++)
                        {
                            fprintf(fpsocre, "\t%.8f", sec30->ArraysOf3DDouble[SOCind][0][iH][jH]);
                        }
                        fprintf(fpsocre, "\n");
                    }
                    fclose(fpsocre);
                }
                
                FILE *fpsocim;
                wxString fnamesocim = filepath + wxFileName::GetPathSeparator() + BaseName + wxT("_SOC_Im.dat");
                if ((fpsocim = fopen(fnamesocim,"w")) != NULL)
                {
                    for (int iH=0; iH<nSOCImage; iH++)
                    {
                        fprintf(fpsocim, "%.8f", sec30->ArraysOf3DDouble[SOCind][1][iH][0]);
                        for (int jH=1; jH<nSOCImage; jH++)
                        {
                            fprintf(fpsocim, "\t%.8f", sec30->ArraysOf3DDouble[SOCind][1][iH][jH]);
                        }
                        fprintf(fpsocim, "\n");
                    }
                    fclose(fpsocim);
                }
            }
        }
    }
    
}

void MainFrame::GenerateCode(wxString filepath, wxString BaseName, wxString CodeType, int MyID_Initial0Final1, bool OnlyDatFiles)
{
    bool isBandLoaded;
    if (sec30->ArraysOf0DInt[0] != 0) isBandLoaded = true;
    if (!isBandLoaded) {wxMessageBox(_("Your DFT band is not loaded. We do not have any information about the k-path. Please load the DFT band and make sure you can see the TB band structure and try later."),_("Error"));return;}
    int nKPoint = sec30->ArraysOf0DInt[1];
    if (nKPoint < 1) {wxMessageBox(_("We do not have any information about the k-path. Please make sure you can see the band structure and try later."),_("Error"));return;}
    
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    if (ID == 1) Hind = 1;
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) {wxMessageBox(_("Your TB model is not completed. Please make sure you can see the band structure and try later."),_("Error"));return;}
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) {wxMessageBox(_("Your TB model is not completed. Please make sure you can see the band structure and try later."),_("Error"));return;}
    
    ExportMatrices(filepath, BaseName, MyID_Initial0Final1);
    if (OnlyDatFiles) return;
    if (CodeType == _("Cpp"))
        GenerateCppCode(filepath, BaseName, MyID_Initial0Final1);
    else if (CodeType == _("C"))
        GenerateCCode(filepath, BaseName, MyID_Initial0Final1);
    else if (CodeType == _("Fortran90"))
        GenerateFCode(filepath, BaseName, MyID_Initial0Final1);
    else if (CodeType == _("Mathematica"))
        GenerateMathematicaCode(filepath, BaseName, MyID_Initial0Final1);
    else if (CodeType == _("Matlab"))
        GenerateMatlabCode(filepath, BaseName, MyID_Initial0Final1);
    else if (CodeType == _("Python"))
        GeneratePythonCode(filepath, BaseName, MyID_Initial0Final1);
		
	wxMessageBox(wxT("Done!"));
}

void MainFrame::GenerateCppCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1)
{
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    int Sind = 2;
    int SOCind = 4;
    if (ID == 1)
    {
        Hind = 1;
        Sind = 3;
        SOCind = 5;
    }
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) return;
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) return;
    
    bool isS = false;
    int nEssS = sec30->ArraysOf3DDouble[Sind].size();
    if (nEssS > 0) isS = true;
    
    bool isSOC = false;
    int nSOCBuf = sec30->ArraysOf3DDouble[SOCind].size();
    if (nSOCBuf > 1) isSOC = true;
    //int nk = sec30->ArraysOf2DDouble[0].size();//double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    //int nklabel = sec30->ArraysOf1DDouble[0].size();//double* dkLabel;
    
    FILE *fpk;
    wxString fname = BaseName + wxT(".cpp");
    wxString fpath =  filepath + wxFileName::GetPathSeparator() + fname;
    if ((fpk = fopen(fpath,"w")) != NULL)
    {
        fprintf(fpk,"//compile command: g++ %s\n",fname.c_str().AsChar());
        fprintf(fpk,"//headers\n");
        fprintf(fpk,"#include <stdlib.h>\n");
        fprintf(fpk,"#include <stdio.h>\n");
        fprintf(fpk,"#include <complex>\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"//Declaration\n");
        fprintf(fpk,"double dot(double a[3], double b[3]);\n");
        fprintf(fpk,"void cross(double a[3], double b[3], double (&c)[3]);\n");
        fprintf(fpk,"void VecToReciprocal(double a[3], double b[3], double c[3], double (&ak)[3], double (&bk)[3], double (&ck)[3]);\n");
        fprintf(fpk,"std::complex<double> Getk(double*** H, double kx, double ky, double kz, double a[3], double b[3], double c[3], int nCells, int Cells[][3], int iH, int jH);\n");
        fprintf(fpk,"std::complex<double> GetkFrac(double*** H, double ka, double kb, double kc, double as[3], double bs[3], double cs[3], double a[3], double b[3], double c[3], int nCells, int Cells[][3], int iH, int jH);\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"//Main program\n");
        fprintf(fpk,"int main() {\n");
        fprintf(fpk,"\t/* Parameters */\n");
        if (isSOC)
        {
            fprintf(fpk,"\tint nH0 = %d;\n", nH);
            fprintf(fpk,"\tint nH = 2*nH0;\n");
        }
        else
            fprintf(fpk,"\tint nH = %d;\n", nH);
            
        wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
        int nCell = listctr->GetCount();        

        fprintf(fpk,"\tint nCells = %d;\n", nCell);
        
        double a[3],b[3],c[3];
        sec30->GetVar(_("a[0]"), a[0]);
        sec30->GetVar(_("a[1]"), a[1]);
        sec30->GetVar(_("a[2]"), a[2]);
        sec30->GetVar(_("b[0]"), b[0]);
        sec30->GetVar(_("b[1]"), b[1]);
        sec30->GetVar(_("b[2]"), b[2]);
        sec30->GetVar(_("c[0]"), c[0]);
        sec30->GetVar(_("c[1]"), c[1]);
        sec30->GetVar(_("c[2]"), c[2]);
        
        fprintf(fpk,"\n\t/* Set the unitcell vectors */\n");
        fprintf(fpk,"\tdouble a[3] = {%.8f, %.8f, %.8f};\n", a[0], a[1], a[2]);
        fprintf(fpk,"\tdouble b[3] = {%.8f, %.8f, %.8f};\n", b[0], b[1], b[2]);
        fprintf(fpk,"\tdouble c[3] = {%.8f, %.8f, %.8f};\n", c[0], c[1], c[2]);
        
        fprintf(fpk,"\n\t/* Calculate the reciprocal space vectors */\n");
        fprintf(fpk,"\tdouble as[3],bs[3],cs[3];\n");
        fprintf(fpk,"\tVecToReciprocal(a, b, c, as, bs, cs);\n");
        fprintf(fpk,"\tprintf(\"Unitcell Vectors:\\n\");\n");
        fprintf(fpk,"\tprintf(\"a = (%%.3f, %%.3f, %%.3f)\\n\", a[0], a[1], a[2]);\n");
        fprintf(fpk,"\tprintf(\"b = (%%.3f, %%.3f, %%.3f)\\n\", b[0], b[1], b[2]);\n");
        fprintf(fpk,"\tprintf(\"c = (%%.3f, %%.3f, %%.3f)\\n\", c[0], c[1], c[2]);\n");
        fprintf(fpk,"\tprintf(\"\\nReciprocal Vectors:\\n\");\n");
        fprintf(fpk,"\tprintf(\"a* = (%%.3f, %%.3f, %%.3f)\\n\", as[0], as[1], as[2]);\n");
        fprintf(fpk,"\tprintf(\"b* = (%%.3f, %%.3f, %%.3f)\\n\", bs[0], bs[1], bs[2]);\n");
        fprintf(fpk,"\tprintf(\"c* = (%%.3f, %%.3f, %%.3f)\\n\", cs[0], cs[1], cs[2]);\n");
        
        fprintf(fpk,"\n\t/* Set the unitcell list */\n");
        fprintf(fpk,"\tint Cells[][3] = {\n");
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            if (iCell<nCell - 1)
                fprintf(fpk,"\t\t{%d, %d, %d},\n", lcell, mcell, ncell);
            else
                fprintf(fpk,"\t\t{%d, %d, %d}\n", lcell, mcell, ncell);
        }
        fprintf(fpk,"\t};\n");
        
        fprintf(fpk,"\n\t/* Allocate the h array */\n");
        fprintf(fpk,"\tdouble*** h = new double**[nCells];\n");
        fprintf(fpk,"\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
        fprintf(fpk,"\t{\n");
        fprintf(fpk,"\t\th[iCell] = new double*[nH];\n");
        fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++) h[iCell][i] = new double[nH];\n");
        fprintf(fpk,"\t}\n");
        
        if (isS)
        {
            fprintf(fpk,"\n\t/* Allocate the s array */\n");
            fprintf(fpk,"\tdouble*** s = new double**[nCells];\n");
            fprintf(fpk,"\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\ts[iCell] = new double*[nH];\n");
            fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++) s[iCell][i] = new double[nH];\n");
            fprintf(fpk,"\t}\n");
        }
        
        if (isSOC)
        {
            fprintf(fpk,"\n\t/* Allocate the Hsoc array */\n");
            fprintf(fpk,"\tstd::complex<double>** Hsoc = new std::complex<double>*[nH];\n");
            fprintf(fpk,"\tfor(int i = 0; i < nH; i++) Hsoc[i] = new std::complex<double>[nH];\n");
        }
        
        if (isSOC)
        {
            fprintf(fpk,"\n\t/* Load files */\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
            fprintf(fpk,"\tchar filename[100];\n");
            fprintf(fpk,"\tint it = 0;\n");
            fprintf(fpk,"\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tFILE *fp;\n");
            fprintf(fpk,"\t\tsprintf(filename, \"%s_H(%%d,%%d,%%d).dat\",Cells[iCell][0] ,Cells[iCell][1] ,Cells[iCell][2]);\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\t\tprintf(\"%%d) loading file: %%s\\n\", ++it, filename);\n");
            fprintf(fpk,"\t\tfp = fopen(filename,\"r\");\n");
            fprintf(fpk,"\t\tfor(int i = 0; i < nH0; i++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tfor(int j = 0; j < nH0; j++)\n");
            fprintf(fpk,"\t\t\t{\n");
            fprintf(fpk,"\t\t\t\tfscanf(fp, \"%%lf\", &h[iCell][2*i][2*j]);\n");
            fprintf(fpk,"\t\t\t\th[iCell][2*i + 1][2*j + 1] = h[iCell][2*i][2*j];\n");
            fprintf(fpk,"\t\t\t\th[iCell][2*i][2*j + 1] = 0.0;\n");
            fprintf(fpk,"\t\t\t\th[iCell][2*i + 1][2*j] = 0.0;\n");
            fprintf(fpk,"\t\t\t}\n");
            fprintf(fpk,"\t\t\tfscanf(fp,\"\\n\");\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tfclose(fp);\n");
            fprintf(fpk,"\t\t\n");
            fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tfor(int j = 0; j < nH; j++)\n");
            fprintf(fpk,"\t\t\t\tprintf(\"%%.3f \", h[iCell][i][j]);\n");
            fprintf(fpk,"\t\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
            
            if(isS)
            {
                fprintf(fpk,"\n\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
                fprintf(fpk,"\t{\n");
                fprintf(fpk,"\t\tFILE *fp;\n");
                fprintf(fpk,"\t\tsprintf(filename, \"%s_S(%%d,%%d,%%d).dat\",Cells[iCell][0] ,Cells[iCell][1] ,Cells[iCell][2]);\n",BaseName.c_str().AsChar());
                fprintf(fpk,"\t\tprintf(\"%%d) loading file: %%s\\n\", ++it, filename);\n");
                fprintf(fpk,"\t\tfp = fopen(filename,\"r\");\n");
                fprintf(fpk,"\t\tfor(int i = 0; i < nH0; i++)\n");
                fprintf(fpk,"\t\t{\n");
                fprintf(fpk,"\t\t\tfor(int j = 0; j < nH0; j++)\n");
                fprintf(fpk,"\t\t\t{\n");
                fprintf(fpk,"\t\t\t\tfscanf(fp, \"%%lf\", &s[iCell][2*i][2*j]);\n");
                fprintf(fpk,"\t\t\t\ts[iCell][2*i + 1][2*j + 1] = s[iCell][2*i][2*j];\n");
                fprintf(fpk,"\t\t\t\ts[iCell][2*i][2*j + 1] = 0.0;\n");
                fprintf(fpk,"\t\t\t\ts[iCell][2*i + 1][2*j] = 0.0;\n");
                fprintf(fpk,"\t\t\t}\n");
                fprintf(fpk,"\t\t\tfscanf(fp,\"\\n\");\n");
                fprintf(fpk,"\t\t}\n");
                fprintf(fpk,"\t\tfclose(fp);\n");
                fprintf(fpk,"\t\t\n");
                fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++)\n");
                fprintf(fpk,"\t\t{\n");
                fprintf(fpk,"\t\t\tfor(int j = 0; j < nH; j++)\n");
                fprintf(fpk,"\t\t\t\tprintf(\"%%.3f \", s[iCell][i][j]);\n");
                fprintf(fpk,"\t\t\tprintf(\"\\n\");\n");
                fprintf(fpk,"\t\t}\n");
                fprintf(fpk,"\t\tprintf(\"\\n\");\n");
                fprintf(fpk,"\t}\n");
            }
            
            fprintf(fpk,"\t\n");
            fprintf(fpk,"\tFILE *fpSOCRe;\n");
            fprintf(fpk,"\tFILE *fpSOCIm;\n");
            fprintf(fpk,"\tfpSOCRe = fopen(\"%s_SOC_Re.dat\",\"r\");\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\tfpSOCIm = fopen(\"%s_SOC_Im.dat\",\"r\");\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\tfor(int i = 0; i < nH; i++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int j = 0; j < nH; j++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tdouble re, im;\n");
            fprintf(fpk,"\t\t\tfscanf(fpSOCRe, \"%%lf\", &re);\n");
            fprintf(fpk,"\t\t\tfscanf(fpSOCIm, \"%%lf\", &im);\n");
            fprintf(fpk,"\t\t\tHsoc[i][j].real(re);\n");
            fprintf(fpk,"\t\t\tHsoc[i][j].imag(im);\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tfscanf(fpSOCRe,\"\\n\");\n");
            fprintf(fpk,"\t\tfscanf(fpSOCIm,\"\\n\");\n");
            fprintf(fpk,"\t}\n");
            fprintf(fpk,"\tfclose(fpSOCRe);\n");
            fprintf(fpk,"\tfclose(fpSOCIm);\n");
            
            fprintf(fpk,"\t\n");
            fprintf(fpk,"\tfor(int i = 0; i < nH; i++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int j = 0; j < nH; j++)\n");
            fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Hsoc[i][j].real(), Hsoc[i][j].imag());\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
        }
        else
        {
            fprintf(fpk,"\n\t/* Load files */\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
            fprintf(fpk,"\tchar filename[100];\n");
            fprintf(fpk,"\tint it = 0;\n");
            fprintf(fpk,"\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tFILE *fp;\n");
            fprintf(fpk,"\t\tsprintf(filename, \"%s_H(%%d,%%d,%%d).dat\",Cells[iCell][0] ,Cells[iCell][1] ,Cells[iCell][2]);\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\t\tprintf(\"%%d) loading file: %%s\\n\", ++it, filename);\n");
            fprintf(fpk,"\t\tfp = fopen(filename,\"r\");\n");
            fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tfor(int j = 0; j < nH; j++)\n");
            fprintf(fpk,"\t\t\t{\n");
            fprintf(fpk,"\t\t\t\tfscanf(fp, \"%%lf\", &h[iCell][i][j]);\n");
            fprintf(fpk,"\t\t\t\tprintf(\"%%.3f \", h[iCell][i][j]);\n");
            fprintf(fpk,"\t\t\t}\n");
            fprintf(fpk,"\t\t\tfscanf(fp,\"\\n\");\n");
            fprintf(fpk,"\t\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tfclose(fp);\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
            
            if(isS)
            {
                fprintf(fpk,"\n\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
                fprintf(fpk,"\t{\n");
                fprintf(fpk,"\t\tFILE *fp;\n");
                fprintf(fpk,"\t\tsprintf(filename, \"%s_S(%%d,%%d,%%d).dat\",Cells[iCell][0] ,Cells[iCell][1] ,Cells[iCell][2]);\n",BaseName.c_str().AsChar());
                fprintf(fpk,"\t\tprintf(\"%%d) loading file: %%s\\n\", ++it, filename);\n");
                fprintf(fpk,"\t\tfp = fopen(filename,\"r\");\n");
                fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++)\n");
                fprintf(fpk,"\t\t{\n");
                fprintf(fpk,"\t\t\tfor(int j = 0; j < nH; j++)\n");
                fprintf(fpk,"\t\t\t{\n");
                fprintf(fpk,"\t\t\t\tfscanf(fp, \"%%lf\", &s[iCell][i][j]);\n");
                fprintf(fpk,"\t\t\t\tprintf(\"%%.3f \", s[iCell][i][j]);\n");
                fprintf(fpk,"\t\t\t}\n");
                fprintf(fpk,"\t\t\tfscanf(fp,\"\\n\");\n");
                fprintf(fpk,"\t\t\tprintf(\"\\n\");\n");
                fprintf(fpk,"\t\t}\n");
                fprintf(fpk,"\t\tfclose(fp);\n");
                fprintf(fpk,"\t\tprintf(\"\\n\");\n");
                fprintf(fpk,"\t}\n");
            }
        }
        
        if (isS)
            fprintf(fpk,"\n\t/* Allocate Hamiltonian and overlap matrix */\n");
        else
            fprintf(fpk,"\n\t/* Allocate Hamiltonian matrix */\n");
        
        fprintf(fpk,"\tint nH2 = nH*nH;\n");
        fprintf(fpk,"\tstd::complex<double>* Hk = new std::complex<double>[nH2];\n");
        if (isS)
            fprintf(fpk,"\tstd::complex<double>* Sk = new std::complex<double>[nH2];\n");
        
        fprintf(fpk,"\n\t/* Calculate the Hamiltonian in a typical k=(kx, ky, kz) */\n");
        fprintf(fpk,"\tdouble kx, ky, kz;\n");
        fprintf(fpk,"\tkx=0.0; ky=0.0; kz=0.0;\n");
        fprintf(fpk,"\tprintf(\"Testing the function Getk. Hamiltonian matrix in an absolute k point k=(kx, ky, kz) = (%%.3f, %%.3f, %%.3f)\\n\", kx, ky ,kz);\n");
        fprintf(fpk,"\tfor(int i=0; i<nH; i++)\n");
        fprintf(fpk,"\t{\n");
        fprintf(fpk,"\t\tfor(int j=0; j<nH; j++)\n");
        fprintf(fpk,"\t\t{\n");
        if (isSOC)
            fprintf(fpk,"\t\t\tHk[i * nH + j] = Getk(h, kx, ky, kz, a, b, c, nCells, Cells, i, j) + Hsoc[i][j];\n");
        else
            fprintf(fpk,"\t\t\tHk[i * nH + j] = Getk(h, kx, ky, kz, a, b, c, nCells, Cells, i, j);\n");
        fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Hk[i * nH + j].real(), Hk[i * nH + j].imag());\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t\tprintf(\"\\n\");\n");
        fprintf(fpk,"\t}\n");
        
        if (isS)
        {
            fprintf(fpk,"\t\n");
            fprintf(fpk,"\t/* Calculate the overlap matrix in a typical k=(kx, ky, kz) */\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
            fprintf(fpk,"\tprintf(\"Testing the function Getk. Overlap matrix in an absolute k point k=(kx, ky, kz) = (%%.3f, %%.3f, %%.3f)\\n\", kx, ky ,kz);\n");
            fprintf(fpk,"\tfor(int i=0; i<nH; i++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int j=0; j<nH; j++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tSk[i * nH + j] = Getk(s, kx, ky, kz, a, b, c, nCells, Cells, i, j);\n");
            fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Sk[i * nH + j].real(), Sk[i * nH + j].imag());\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
        }
        
        fprintf(fpk,"\n\t/* Calculate the Hamiltonian in a typical fractional k point (ka, kb, kc) */\n");
        fprintf(fpk,"\tprintf(\"\\n\");\n");
        fprintf(fpk,"\tdouble ka, kb, kc;\n");
        fprintf(fpk,"\tka=0.0; kb=0.25; kc=0.0;\n");
        fprintf(fpk,"\tprintf(\"Testing the function GetkFrac. Hamiltonian matrix in a fractional k point (ka, kb, kc) = (%%.3f, %%.3f, %%.3f)\\n\", ka, kb ,kc);\n");
        fprintf(fpk,"\tfor(int i=0; i<nH; i++)\n");
        fprintf(fpk,"\t{\n");
        fprintf(fpk,"\t\tfor(int j=0; j<nH; j++)\n");
        fprintf(fpk,"\t\t{\n");
        if (isSOC)
            fprintf(fpk,"\t\t\tHk[i * nH + j] = GetkFrac(h, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, i, j) + Hsoc[i][j];\n");
        else
            fprintf(fpk,"\t\t\tHk[i * nH + j] = GetkFrac(h, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, i, j);\n");
        fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Hk[i * nH + j].real(), Hk[i * nH + j].imag());\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t\tprintf(\"\\n\");\n");
        fprintf(fpk,"\t}\n");
        
        if (isS)
        {
            fprintf(fpk,"\t\n");
            fprintf(fpk,"\t/* Calculate the overlap matrix in a typical fractional k point (ka, kb, kc) */\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
            fprintf(fpk,"\tprintf(\"Testing the function GetkFrac. Overlap matrix in a fractional k point (ka, kb, kc) = (%%.3f, %%.3f, %%.3f)\\n\", ka, kb ,kc);\n");
            fprintf(fpk,"\tfor(int i=0; i<nH; i++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int j=0; j<nH; j++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tSk[i * nH + j] = GetkFrac(s, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, i, j);\n");
            fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Sk[i * nH + j].real(), Sk[i * nH + j].imag());\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
        }
        
        fprintf(fpk,"\n\t/* Deallocate the h array */\n");
        fprintf(fpk,"\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
        fprintf(fpk,"\t{\n");
        fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++) delete[] h[iCell][i];\n");
        fprintf(fpk,"\t\tdelete[] h[iCell];\n");
        fprintf(fpk,"\t}\n");
        fprintf(fpk,"\tdelete[] h;\n");
        
        if (isS)
        {
            fprintf(fpk,"\n\t/* Deallocate the s array */\n");
            fprintf(fpk,"\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++) delete[] s[iCell][i];\n");
            fprintf(fpk,"\t\tdelete[] s[iCell];\n");
            fprintf(fpk,"\t}\n");
            fprintf(fpk,"\tdelete[] s;\n");
        }
        
        if (isSOC)
        {
            fprintf(fpk,"\n\t/* Deallocate the Hsoc array */\n");
            fprintf(fpk,"\tfor(int i = 0; i < nH; i++) delete[] Hsoc[i];\n");
            fprintf(fpk,"\tdelete[] Hsoc;\n");
        }
        
        fprintf(fpk,"\n\texit( 0 );\n");
        fprintf(fpk,"}\n");
        
        
        fprintf(fpk,"\n\t//Implementation\n");
        fprintf(fpk,"std::complex<double> GetkFrac(double*** H, double ka, double kb, double kc, double as[3], double bs[3], double cs[3], double a[3], double b[3], double c[3], int nCells, int Cells[][3], int iH, int jH)\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble k[3];\n");
        fprintf(fpk,"\tfor(int i=0; i<3; i++)\n");
        fprintf(fpk,"\tk[i] = ka*as[i] + kb*bs[i] + kc*cs[i];\n");
        fprintf(fpk,"\treturn Getk(H, k[0], k[1], k[2], a, b, c, nCells, Cells, iH, jH);\n");
        fprintf(fpk,"}\n\n");
        
        fprintf(fpk,"std::complex<double> Getk(double*** H, double kx, double ky, double kz, double a[3], double b[3], double c[3], int nCells, int Cells[][3], int iH, int jH)\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble K[3] = {kx, ky, kz};\n");
        fprintf(fpk,"\tdouble RealPart = 0.0;\n");
        fprintf(fpk,"\tdouble ImaginaryPart = 0.0;\n");
        fprintf(fpk,"\tdouble R[3];\n");
        fprintf(fpk,"\tdouble arg;\n");
        fprintf(fpk,"\tfor (int icell=0; icell < nCells; icell++)\n");
        fprintf(fpk,"\t{\n");
        fprintf(fpk,"\t\tif (Cells[icell][0] == 0 && Cells[icell][1] == 0 && Cells[icell][2] == 0)\n");
        fprintf(fpk,"\t\t{\n");
        fprintf(fpk,"\t\t\tRealPart += H[icell][iH][jH];\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t\telse\n");
        fprintf(fpk,"\t\t{\n");
        fprintf(fpk,"\t\t\tR[0] = Cells[icell][0] * a[0] + Cells[icell][1] * b[0] + Cells[icell][2] * c[0];\n");
        fprintf(fpk,"\t\t\tR[1] = Cells[icell][0] * a[1] + Cells[icell][1] * b[1] + Cells[icell][2] * c[1];\n");
        fprintf(fpk,"\t\t\tR[2] = Cells[icell][0] * a[2] + Cells[icell][1] * b[2] + Cells[icell][2] * c[2];\n");
        fprintf(fpk,"\t\t\targ = dot(K, R);\n");
        fprintf(fpk,"\t\t\tRealPart += (H[icell][iH][jH] + H[icell][jH][iH]) * cos(arg);  //V*Exp(-ikR) + VT*Exp(ikR)  //Re\n");
        fprintf(fpk,"\t\t\tImaginaryPart -= (H[icell][iH][jH] - H[icell][jH][iH]) * sin(arg); //V*Exp(-ikR) + VT*Exp(ikR)  //Im\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"\tstd::complex<double> out;\n");
        fprintf(fpk,"\tout.real(RealPart);\n");
        fprintf(fpk,"\tout.imag(ImaginaryPart);\n");
        fprintf(fpk,"\treturn out;\n");
        fprintf(fpk,"}\n\n");
        
        fprintf(fpk,"double dot(double a[3], double b[3])\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble r = 0.0;\n");
        fprintf(fpk,"\tfor (int i=0;i<3;i++) r += a[i]*b[i];\n");
        fprintf(fpk,"\treturn r;\n");
        fprintf(fpk,"}\n\n");
        
        fprintf(fpk,"void cross(double a[3], double b[3], double (&c)[3])\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tc[0] = a[1]*b[2]-a[2]*b[1];\n");
        fprintf(fpk,"\tc[1] = a[2]*b[0]-a[0]*b[2];\n");
        fprintf(fpk,"\tc[2] = a[0]*b[1]-a[1]*b[0];\n");
        fprintf(fpk,"}\n\n");
        
        fprintf(fpk,"void VecToReciprocal(double a[3], double b[3], double c[3], double (&ak)[3], double (&bk)[3], double (&ck)[3])\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble bc[3], ca[3], ab[3];\n");
        fprintf(fpk,"\tcross(b, c, bc);\n");
        fprintf(fpk,"\tcross(c, a, ca);\n");
        fprintf(fpk,"\tcross(a, b, ab);\n");
        fprintf(fpk,"\tdouble volume = dot(a, bc);\n");
        fprintf(fpk,"\tdouble volumek = 2.0*3.14159265359 / volume;\n");
        fprintf(fpk,"\tfor(int i=0; i<3; i++) ak[i] = volumek*bc[i];\n");
        fprintf(fpk,"\tfor(int i=0; i<3; i++) bk[i] = volumek*ca[i];\n");
        fprintf(fpk,"\tfor(int i=0; i<3; i++) ck[i] = volumek*ab[i];\n");
        fprintf(fpk,"}\n\n");
        
        fclose(fpk);
    }
}

void MainFrame::GenerateCCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1)
{
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    int Sind = 2;
    int SOCind = 4;
    if (ID == 1)
    {
        Hind = 1;
        Sind = 3;
        SOCind = 5;
    }
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) return;
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) return;
    
    bool isS = false;
    int nEssS = sec30->ArraysOf3DDouble[Sind].size();
    if (nEssS > 0) isS = true;
    
    bool isSOC = false;
    int nSOCBuf = sec30->ArraysOf3DDouble[SOCind].size();
    if (nSOCBuf > 1) isSOC = true;
    
    //int nk = sec30->ArraysOf2DDouble[0].size();//double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    //int nklabel = sec30->ArraysOf1DDouble[0].size();//double* dkLabel;
    
    FILE *fpk;
    wxString fname = BaseName + wxT(".c");
    wxString fpath =  filepath + wxFileName::GetPathSeparator() + fname;
    if ((fpk = fopen(fpath,"w")) != NULL)
    {
        fprintf(fpk,"//compile command: gcc %s -lm\n",fname.c_str().AsChar());
        fprintf(fpk,"//headers\n");
        fprintf(fpk,"#include <stdlib.h>\n");
        fprintf(fpk,"#include <stdio.h>\n");
        fprintf(fpk,"#include \"math.h\"\n");
        fprintf(fpk,"\n");
        
        fprintf(fpk,"/* Definition of complex structure */\n");
        fprintf(fpk,"/*In the case of using lapack for solving eigen value problems\n");
        fprintf(fpk,"or matrix inversion one should use lapack_make_complex_double(double re, double im) or\n");
        fprintf(fpk,"lapack_make_complex_float(float re, float im). These functions (actually macros) are\n");
        fprintf(fpk,"available in lapacke.h and compensate absent complex support in C compiler.*/\n");
        fprintf(fpk,"typedef struct {double real;double imag;} complex;\n");
        
        fprintf(fpk,"\n//Declaration\n");
        fprintf(fpk,"double ***alloc3d(size_t xlen, size_t ylen, size_t zlen);\n");
        fprintf(fpk,"void free3d(double ***data, size_t xlen, size_t ylen);\n");
        fprintf(fpk,"double dot(double a[3], double b[3]);\n");
        fprintf(fpk,"void cross(double a[3], double b[3], double c[3]);\n");
        fprintf(fpk,"void VecToReciprocal(double a[3], double b[3], double c[3], double ak[3], double bk[3], double ck[3]);\n");
        fprintf(fpk,"complex Getk(double*** H, double kx, double ky, double kz, double a[3], double b[3], double c[3], int nCells, int Cells[][3], int iH, int jH);\n");
        fprintf(fpk,"complex GetkFrac(double*** H, double ka, double kb, double kc, double as[3], double bs[3], double cs[3], double a[3], double b[3], double c[3], int nCells, int Cells[][3], int iH, int jH);\n");
        
        fprintf(fpk,"\n//Main program\n");
        fprintf(fpk,"int main() {\n");
        fprintf(fpk,"\t/* Parameters */\n");
        if (isSOC)
        {
            fprintf(fpk,"\tint nH0 = %d;\n", nH);
            fprintf(fpk,"\tint nH = 2*nH0;\n");
        }
        else
            fprintf(fpk,"\tint nH = %d;\n", nH);
        
        wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
        int nCell = listctr->GetCount();
        
        fprintf(fpk,"\tint nCells = %d;\n", nCell);
        fprintf(fpk,"\t\n");
        
        double a[3],b[3],c[3];
        sec30->GetVar(_("a[0]"), a[0]);
        sec30->GetVar(_("a[1]"), a[1]);
        sec30->GetVar(_("a[2]"), a[2]);
        sec30->GetVar(_("b[0]"), b[0]);
        sec30->GetVar(_("b[1]"), b[1]);
        sec30->GetVar(_("b[2]"), b[2]);
        sec30->GetVar(_("c[0]"), c[0]);
        sec30->GetVar(_("c[1]"), c[1]);
        sec30->GetVar(_("c[2]"), c[2]);
        
        fprintf(fpk,"\t/* Set the unitcell vectors */\n");
        fprintf(fpk,"\tdouble a[3] = {%.8f, %.8f, %.8f};\n", a[0], a[1], a[2]);
        fprintf(fpk,"\tdouble b[3] = {%.8f, %.8f, %.8f};\n", b[0], b[1], b[2]);
        fprintf(fpk,"\tdouble c[3] = {%.8f, %.8f, %.8f};\n", c[0], c[1], c[2]);
        
        fprintf(fpk,"\n\t/* Calculate the reciprocal space vectors */\n");
        fprintf(fpk,"\tdouble as[3],bs[3],cs[3];\n");
        fprintf(fpk,"\tVecToReciprocal(a, b, c, as, bs, cs);\n");
        fprintf(fpk,"\tprintf(\"Unitcell Vectors:\\n\");\n");
        fprintf(fpk,"\tprintf(\"a = (%%.3f, %%.3f, %%.3f)\\n\", a[0], a[1], a[2]);\n");
        fprintf(fpk,"\tprintf(\"b = (%%.3f, %%.3f, %%.3f)\\n\", b[0], b[1], b[2]);\n");
        fprintf(fpk,"\tprintf(\"c = (%%.3f, %%.3f, %%.3f)\\n\", c[0], c[1], c[2]);\n");
        fprintf(fpk,"\tprintf(\"\\nReciprocal Vectors:\\n\");\n");
        fprintf(fpk,"\tprintf(\"a* = (%%.3f, %%.3f, %%.3f)\\n\", as[0], as[1], as[2]);\n");
        fprintf(fpk,"\tprintf(\"b* = (%%.3f, %%.3f, %%.3f)\\n\", bs[0], bs[1], bs[2]);\n");
        fprintf(fpk,"\tprintf(\"c* = (%%.3f, %%.3f, %%.3f)\\n\", cs[0], cs[1], cs[2]);\n");
        
        fprintf(fpk,"\n\t/* Set the unitcell list */\n");
        fprintf(fpk,"\tint Cells[][3] = {\n");
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            if (iCell<nCell - 1)
                fprintf(fpk,"\t\t{%d, %d, %d},\n", lcell, mcell, ncell);
            else
                fprintf(fpk,"\t\t{%d, %d, %d}\n", lcell, mcell, ncell);
        }
        fprintf(fpk,"\t};\n");
        
        if(isSOC)
        {
            if(isS)
                fprintf(fpk,"\n\t/* Allocate h, s and Hsoc arrays */\n");
            else
                fprintf(fpk,"\n\t/* Allocate h and Hsoc arrays */\n");
        }
        else
        {
            if(isS)
                fprintf(fpk,"\n\t/* Allocate h and s arrays */\n");
            else
                fprintf(fpk,"\n\t/* Allocate the h array */\n");
        }
        fprintf(fpk,"\tdouble*** h = alloc3d(nCells, nH, nH);\n");
        if(isS) fprintf(fpk,"\tdouble*** s = alloc3d(nCells, nH, nH);\n");
        if(isSOC) fprintf(fpk,"\tdouble*** Hsoc = alloc3d(2, nH, nH);\n");
        fprintf(fpk,"\t\n");
        
        if (isSOC)
        {
            fprintf(fpk,"\n\t/* Load files */\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
            fprintf(fpk,"\tchar filename[100];\n");
            fprintf(fpk,"\tint it = 0;\n");
            fprintf(fpk,"\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tFILE *fp;\n");
            fprintf(fpk,"\t\tsprintf(filename, \"%s_H(%%d,%%d,%%d).dat\",Cells[iCell][0] ,Cells[iCell][1] ,Cells[iCell][2]);\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\t\tprintf(\"%%d) loading file: %%s\\n\", ++it, filename);\n");
            fprintf(fpk,"\t\tfp = fopen(filename,\"r\");\n");
            fprintf(fpk,"\t\tfor(int i = 0; i < nH0; i++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tfor(int j = 0; j < nH0; j++)\n");
            fprintf(fpk,"\t\t\t{\n");
            fprintf(fpk,"\t\t\t\tfscanf(fp, \"%%lf\", &h[iCell][2*i][2*j]);\n");
            fprintf(fpk,"\t\t\t\th[iCell][2*i + 1][2*j + 1] = h[iCell][2*i][2*j];\n");
            fprintf(fpk,"\t\t\t\th[iCell][2*i][2*j + 1] = 0.0;\n");
            fprintf(fpk,"\t\t\t\th[iCell][2*i + 1][2*j] = 0.0;\n");
            fprintf(fpk,"\t\t\t}\n");
            fprintf(fpk,"\t\t\tfscanf(fp,\"\\n\");\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tfclose(fp);\n");
            fprintf(fpk,"\t\t\n");
            fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tfor(int j = 0; j < nH; j++)\n");
            fprintf(fpk,"\t\t\t\tprintf(\"%%.3f \", h[iCell][i][j]);\n");
            fprintf(fpk,"\t\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
            
            if(isS)
            {
                fprintf(fpk,"\n\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
                fprintf(fpk,"\t{\n");
                fprintf(fpk,"\t\tFILE *fp;\n");
                fprintf(fpk,"\t\tsprintf(filename, \"%s_S(%%d,%%d,%%d).dat\",Cells[iCell][0] ,Cells[iCell][1] ,Cells[iCell][2]);\n",BaseName.c_str().AsChar());
                fprintf(fpk,"\t\tprintf(\"%%d) loading file: %%s\\n\", ++it, filename);\n");
                fprintf(fpk,"\t\tfp = fopen(filename,\"r\");\n");
                fprintf(fpk,"\t\tfor(int i = 0; i < nH0; i++)\n");
                fprintf(fpk,"\t\t{\n");
                fprintf(fpk,"\t\t\tfor(int j = 0; j < nH0; j++)\n");
                fprintf(fpk,"\t\t\t{\n");
                fprintf(fpk,"\t\t\t\tfscanf(fp, \"%%lf\", &s[iCell][2*i][2*j]);\n");
                fprintf(fpk,"\t\t\t\ts[iCell][2*i + 1][2*j + 1] = s[iCell][2*i][2*j];\n");
                fprintf(fpk,"\t\t\t\ts[iCell][2*i][2*j + 1] = 0.0;\n");
                fprintf(fpk,"\t\t\t\ts[iCell][2*i + 1][2*j] = 0.0;\n");
                fprintf(fpk,"\t\t\t}\n");
                fprintf(fpk,"\t\t\tfscanf(fp,\"\\n\");\n");
                fprintf(fpk,"\t\t}\n");
                fprintf(fpk,"\t\tfclose(fp);\n");
                fprintf(fpk,"\t\t\n");
                fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++)\n");
                fprintf(fpk,"\t\t{\n");
                fprintf(fpk,"\t\t\tfor(int j = 0; j < nH; j++)\n");
                fprintf(fpk,"\t\t\t\tprintf(\"%%.3f \", s[iCell][i][j]);\n");
                fprintf(fpk,"\t\t\tprintf(\"\\n\");\n");
                fprintf(fpk,"\t\t}\n");
                fprintf(fpk,"\t\tprintf(\"\\n\");\n");
                fprintf(fpk,"\t}\n");
            }
            
            fprintf(fpk,"\t\n");
            fprintf(fpk,"\tFILE *fpSOCRe;\n");
            fprintf(fpk,"\tFILE *fpSOCIm;\n");
            fprintf(fpk,"\tfpSOCRe = fopen(\"%s_SOC_Re.dat\",\"r\");\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\tfpSOCIm = fopen(\"%s_SOC_Im.dat\",\"r\");\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\tfor(int i = 0; i < nH; i++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int j = 0; j < nH; j++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tfscanf(fpSOCRe, \"%%lf\", &Hsoc[0][i][j]);\n");
            fprintf(fpk,"\t\t\tfscanf(fpSOCIm, \"%%lf\", &Hsoc[1][i][j]);\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tfscanf(fpSOCRe,\"\\n\");\n");
            fprintf(fpk,"\t\tfscanf(fpSOCIm,\"\\n\");\n");
            fprintf(fpk,"\t}\n");
            fprintf(fpk,"\tfclose(fpSOCRe);\n");
            fprintf(fpk,"\tfclose(fpSOCIm);\n");
            
            fprintf(fpk,"\t\n");
            fprintf(fpk,"\tfor(int i = 0; i < nH; i++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int j = 0; j < nH; j++)\n");
            fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Hsoc[0][i][j], Hsoc[1][i][j]);\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
        }
        else
        {
            fprintf(fpk,"\n\t/* Load files */\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
            fprintf(fpk,"\tchar filename[100];\n");
            fprintf(fpk,"\tint it = 0;\n");
            fprintf(fpk,"\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tFILE *fp;\n");
            fprintf(fpk,"\t\tsprintf(filename, \"%s_H(%%d,%%d,%%d).dat\",Cells[iCell][0] ,Cells[iCell][1] ,Cells[iCell][2]);\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\t\tprintf(\"%%d) loading file: %%s\\n\", ++it, filename);\n");
            fprintf(fpk,"\t\tfp = fopen(filename,\"r\");\n");
            fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tfor(int j = 0; j < nH; j++)\n");
            fprintf(fpk,"\t\t\t{\n");
            fprintf(fpk,"\t\t\t\tfscanf(fp, \"%%lf\", &h[iCell][i][j]);\n");
            fprintf(fpk,"\t\t\t\tprintf(\"%%.3f \", h[iCell][i][j]);\n");
            fprintf(fpk,"\t\t\t}\n");
            fprintf(fpk,"\t\t\tfscanf(fp,\"\\n\");\n");
            fprintf(fpk,"\t\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tfclose(fp);\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
            
            if(isS)
            {
                fprintf(fpk,"\n\tfor(int iCell = 0; iCell < nCells; iCell++)\n");
                fprintf(fpk,"\t{\n");
                fprintf(fpk,"\t\tFILE *fp;\n");
                fprintf(fpk,"\t\tsprintf(filename, \"%s_S(%%d,%%d,%%d).dat\",Cells[iCell][0] ,Cells[iCell][1] ,Cells[iCell][2]);\n",BaseName.c_str().AsChar());
                fprintf(fpk,"\t\tprintf(\"%%d) loading file: %%s\\n\", ++it, filename);\n");
                fprintf(fpk,"\t\tfp = fopen(filename,\"r\");\n");
                fprintf(fpk,"\t\tfor(int i = 0; i < nH; i++)\n");
                fprintf(fpk,"\t\t{\n");
                fprintf(fpk,"\t\t\tfor(int j = 0; j < nH; j++)\n");
                fprintf(fpk,"\t\t\t{\n");
                fprintf(fpk,"\t\t\t\tfscanf(fp, \"%%lf\", &s[iCell][i][j]);\n");
                fprintf(fpk,"\t\t\t\tprintf(\"%%.3f \", s[iCell][i][j]);\n");
                fprintf(fpk,"\t\t\t}\n");
                fprintf(fpk,"\t\t\tfscanf(fp,\"\\n\");\n");
                fprintf(fpk,"\t\t\tprintf(\"\\n\");\n");
                fprintf(fpk,"\t\t}\n");
                fprintf(fpk,"\t\tfclose(fp);\n");
                fprintf(fpk,"\t\tprintf(\"\\n\");\n");
                fprintf(fpk,"\t}\n");
            }
        }
        
        if(isS)
            fprintf(fpk,"\n\t/* Allocate Hamiltonian and overlap matrix */\n");
        else
            fprintf(fpk,"\n\t/* Allocate Hamiltonian matrix */\n");
        fprintf(fpk,"\tprintf(\"\\n\");\n");
        fprintf(fpk,"\tint nH2 = nH*nH;\n");
        fprintf(fpk,"\tcomplex* Hk = (complex*)malloc(nH2 * sizeof(complex));\n");
        if(isS) fprintf(fpk,"\tcomplex* Sk = (complex*)malloc(nH2 * sizeof(complex));\n");
        
        fprintf(fpk,"\t\n");
        fprintf(fpk,"\t/* Calculate the Hamiltonian in a typical k=(kx, ky, kz) */\n");
        fprintf(fpk,"\tdouble kx, ky, kz;\n");
        fprintf(fpk,"\tkx=0.0; ky=0.0; kz=0.0;\n");
        fprintf(fpk,"\tprintf(\"Testing the function Getk. Hamiltonian matrix in an absolute k point k=(kx, ky, kz) = (%%.3f, %%.3f, %%.3f)\\n\", kx, ky ,kz);\n");
        fprintf(fpk,"\tfor(int i=0; i<nH; i++)\n");
        fprintf(fpk,"\t{\n");
        fprintf(fpk,"\t\tfor(int j=0; j<nH; j++)\n");
        fprintf(fpk,"\t\t{\n");
        fprintf(fpk,"\t\t\tHk[i * nH + j] = Getk(h, kx, ky, kz, a, b, c, nCells, Cells, i, j);\n");
        if (isSOC)
        {
            fprintf(fpk,"\t\t\tHk[i * nH + j].real = Hk[i * nH + j].real + Hsoc[0][i][j];\n");
            fprintf(fpk,"\t\t\tHk[i * nH + j].imag = Hk[i * nH + j].imag + Hsoc[1][i][j];\n");
        }
        fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Hk[i * nH + j].real, Hk[i * nH + j].imag);\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t\tprintf(\"\\n\");\n");
        fprintf(fpk,"\t}\n");
        
        if(isS)
        {
            fprintf(fpk,"\t\n");
            fprintf(fpk,"\t/* Calculate the overlap matrix in a typical k=(kx, ky, kz) */\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
            fprintf(fpk,"\tprintf(\"Testing the function Getk. Overlap matrix in an absolute k point k=(kx, ky, kz) = (%%.3f, %%.3f, %%.3f)\\n\", kx, ky ,kz);\n");
            fprintf(fpk,"\tfor(int i=0; i<nH; i++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int j=0; j<nH; j++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tSk[i * nH + j] = Getk(s, kx, ky, kz, a, b, c, nCells, Cells, i, j);\n");
            fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Sk[i * nH + j].real, Sk[i * nH + j].imag);\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
        }
        
        fprintf(fpk,"\n\t/* Calculate the Hamiltonian in a typical fractional k point (ka, kb, kc) */\n");
        fprintf(fpk,"\tprintf(\"\\n\");\n");
        fprintf(fpk,"\tdouble ka, kb, kc;\n");
        fprintf(fpk,"\tka=0.0; kb=0.25; kc=0.0;\n");
        fprintf(fpk,"\tprintf(\"Testing the function GetkFrac. Hamiltonian matrix in a fractional k point (ka, kb, kc) = (%%.3f, %%.3f, %%.3f)\\n\", ka, kb ,kc);\n");
        fprintf(fpk,"\tfor(int i=0; i<nH; i++)\n");
        fprintf(fpk,"\t{\n");
        fprintf(fpk,"\t\tfor(int j=0; j<nH; j++)\n");
        fprintf(fpk,"\t\t{\n");
        fprintf(fpk,"\t\t\tHk[i * nH + j] = GetkFrac(h, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, i, j);\n");
        if (isSOC)
        {
            fprintf(fpk,"\t\t\tHk[i * nH + j].real = Hk[i * nH + j].real + Hsoc[0][i][j];\n");
            fprintf(fpk,"\t\t\tHk[i * nH + j].imag = Hk[i * nH + j].imag + Hsoc[1][i][j];\n");
        }
        fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Hk[i * nH + j].real, Hk[i * nH + j].imag);\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t\tprintf(\"\\n\");\n");
        fprintf(fpk,"\t}\n");
        
        if(isS)
        {
            fprintf(fpk,"\t\n");
            fprintf(fpk,"\t/* Calculate the overlap matrix in a typical fractional k point (ka, kb, kc) */\n");
            fprintf(fpk,"\tprintf(\"\\n\");\n");
            fprintf(fpk,"\tprintf(\"Testing the function GetkFrac. Overlap matrix in a fractional k point (ka, kb, kc) = (%%.3f, %%.3f, %%.3f)\\n\", ka, kb ,kc);\n");
            fprintf(fpk,"\tfor(int i=0; i<nH; i++)\n");
            fprintf(fpk,"\t{\n");
            fprintf(fpk,"\t\tfor(int j=0; j<nH; j++)\n");
            fprintf(fpk,"\t\t{\n");
            fprintf(fpk,"\t\t\tSk[i * nH + j] = GetkFrac(s, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, i, j);\n");
            fprintf(fpk,"\t\t\tprintf(\"(%%.3f, %%.3f)\", Sk[i * nH + j].real, Sk[i * nH + j].imag);\n");
            fprintf(fpk,"\t\t}\n");
            fprintf(fpk,"\t\tprintf(\"\\n\");\n");
            fprintf(fpk,"\t}\n");
        }
        
        if(isSOC)
        {
            if(isS)
                fprintf(fpk,"\n\t/* Deallocate h, s and Hsoc arrays */\n");
            else
                fprintf(fpk,"\n\t/* Deallocate h and Hsoc arrays */\n");
        }
        else
        {
            if(isS)
                fprintf(fpk,"\n\t/* Deallocate h and s arrays */\n");
            else
                fprintf(fpk,"\n\t/* Deallocate the h array */\n");
        }
        fprintf(fpk,"\tfree3d(h, nCells, nH);\n");
        if(isS) fprintf(fpk,"\tfree3d(s, nCells, nH);\n");
        if (isSOC) fprintf(fpk,"\tfree3d(Hsoc, 2, nH);\n");
        fprintf(fpk,"\texit( 0 );\n");
        fprintf(fpk,"}\n");
        
        
        fprintf(fpk,"\n//Implementation\n");
        fprintf(fpk,"complex GetkFrac(double*** H, double ka, double kb, double kc, double as[3], double bs[3], double cs[3], double a[3], double b[3], double c[3], int nCells, int Cells[][3], int iH, int jH)\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble k[3];\n");
        fprintf(fpk,"\tfor(int i=0; i<3; i++)\n");
        fprintf(fpk,"\t\tk[i] = ka*as[i] + kb*bs[i] + kc*cs[i];\n");
        fprintf(fpk,"\treturn Getk(H, k[0], k[1], k[2], a, b, c, nCells, Cells, iH, jH);\n");
        fprintf(fpk,"}\n");
        
        fprintf(fpk,"\n");
        fprintf(fpk,"complex Getk(double*** H, double kx, double ky, double kz, double a[3], double b[3], double c[3], int nCells, int Cells[][3], int iH, int jH)\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble K[3] = {kx, ky, kz};\n");
        fprintf(fpk,"\tdouble RealPart = 0.0;\n");
        fprintf(fpk,"\tdouble ImaginaryPart = 0.0;\n");
        fprintf(fpk,"\tdouble R[3];\n");
        fprintf(fpk,"\tdouble arg;\n");
        fprintf(fpk,"\tfor (int icell=0; icell < nCells; icell++)\n");
        fprintf(fpk,"\t{\n");
        fprintf(fpk,"\t\tif (Cells[icell][0] == 0 && Cells[icell][1] == 0 && Cells[icell][2] == 0)\n");
        fprintf(fpk,"\t\t{\n");
        fprintf(fpk,"\t\t\tRealPart += H[icell][iH][jH];\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t\telse\n");
        fprintf(fpk,"\t\t{\n");
        fprintf(fpk,"\t\t\tR[0] = Cells[icell][0] * a[0] + Cells[icell][1] * b[0] + Cells[icell][2] * c[0];\n");
        fprintf(fpk,"\t\t\tR[1] = Cells[icell][0] * a[1] + Cells[icell][1] * b[1] + Cells[icell][2] * c[1];\n");
        fprintf(fpk,"\t\t\tR[2] = Cells[icell][0] * a[2] + Cells[icell][1] * b[2] + Cells[icell][2] * c[2];\n");
        fprintf(fpk,"\t\t\targ = dot(K, R);\n");
        fprintf(fpk,"\t\t\tRealPart += (H[icell][iH][jH] + H[icell][jH][iH]) * cos(arg);  //V*Exp(-ikR) + VT*Exp(ikR)  //Re\n");
        fprintf(fpk,"\t\t\tImaginaryPart -= (H[icell][iH][jH] - H[icell][jH][iH]) * sin(arg); //V*Exp(-ikR) + VT*Exp(ikR)  //Im\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t}\n");
        fprintf(fpk,"\t\n");
        fprintf(fpk,"\tcomplex out;\n");
        fprintf(fpk,"\tout.real = RealPart;\n");
        fprintf(fpk,"\tout.imag = ImaginaryPart;\n");
        fprintf(fpk,"\treturn out;\n");
        fprintf(fpk,"}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"double dot(double a[3], double b[3])\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble r = 0.0;\n");
        fprintf(fpk,"\tfor (int i=0;i<3;i++) r += a[i]*b[i];\n");
        fprintf(fpk,"\treturn r;\n");
        fprintf(fpk,"}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"void cross(double a[3], double b[3], double c[3])\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tc[0] = a[1]*b[2]-a[2]*b[1];\n");
        fprintf(fpk,"\tc[1] = a[2]*b[0]-a[0]*b[2];\n");
        fprintf(fpk,"\tc[2] = a[0]*b[1]-a[1]*b[0];\n");
        fprintf(fpk,"}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"void VecToReciprocal(double a[3], double b[3], double c[3], double ak[3], double bk[3], double ck[3])\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble bc[3], ca[3], ab[3];\n");
        fprintf(fpk,"\tcross(b, c, bc);\n");
        fprintf(fpk,"\tcross(c, a, ca);\n");
        fprintf(fpk,"\tcross(a, b, ab);\n");
        fprintf(fpk,"\tdouble volume = dot(a, bc);\n");
        fprintf(fpk,"\tdouble volumek = 2.0*3.14159265359 / volume;\n");
        fprintf(fpk,"\tfor(int i=0; i<3; i++) ak[i] = volumek*bc[i];\n");
        fprintf(fpk,"\tfor(int i=0; i<3; i++) bk[i] = volumek*ca[i];\n");
        fprintf(fpk,"\tfor(int i=0; i<3; i++) ck[i] = volumek*ab[i];\n");
        fprintf(fpk,"}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"double ***alloc3d(size_t xlen, size_t ylen, size_t zlen)\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tdouble ***p;\n");
        fprintf(fpk,"\tsize_t i, j;\n");
        fprintf(fpk,"\tif ((p = malloc(xlen * sizeof *p)) == NULL) {\n");
        //fprintf(fpk,"\t\tperror(\"malloc 1\");\n");
        fprintf(fpk,"\t\treturn NULL;\n");
        fprintf(fpk,"\t}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"\tfor (i=0; i < xlen; ++i)\n");
        fprintf(fpk,"\t\tp[i] = NULL;\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"\tfor (i=0; i < xlen; ++i)\n");
        fprintf(fpk,"\t\tif ((p[i] = malloc(ylen * sizeof *p[i])) == NULL) {\n");
        //fprintf(fpk,"\t\t\tperror(\"malloc 2\");\n");
        fprintf(fpk,"\t\t\tfree3d(p, xlen, ylen);\n");
        fprintf(fpk,"\t\t\treturn NULL;\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"\tfor (i=0; i < xlen; ++i)\n");
        fprintf(fpk,"\t\tfor (j=0; j < ylen; ++j)\n");
        fprintf(fpk,"\t\t\tp[i][j] = NULL;\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"\tfor (i=0; i < xlen; ++i)\n");
        fprintf(fpk,"\t\tfor (j=0; j < ylen; ++j)\n");
        fprintf(fpk,"\t\t\tif ((p[i][j] = malloc(zlen * sizeof *p[i][j])) == NULL) {\n");
        //fprintf(fpk,"\t\t\t\tperror(\"malloc 3\");\n");
        fprintf(fpk,"\t\t\t\tfree3d(p, xlen, ylen);\n");
        fprintf(fpk,"\t\t\t\treturn NULL;\n");
        fprintf(fpk,"\t\t\t}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"\treturn p;\n");
        fprintf(fpk,"}\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"void free3d(double ***data, size_t xlen, size_t ylen)\n");
        fprintf(fpk,"{\n");
        fprintf(fpk,"\tsize_t i, j;\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"\tfor (i=0; i < xlen; ++i) {\n");
        fprintf(fpk,"\t\tif (data[i] != NULL) {\n");
        fprintf(fpk,"\t\t\tfor (j=0; j < ylen; ++j)\n");
        fprintf(fpk,"\t\t\t\tfree(data[i][j]);\n");
        fprintf(fpk,"\t\t\tfree(data[i]);\n");
        fprintf(fpk,"\t\t}\n");
        fprintf(fpk,"\t}\n");
        fprintf(fpk,"\tfree(data);\n");
        fprintf(fpk,"}\n\n");
        
        fclose(fpk);
    }

}

void MainFrame::GenerateFCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1)
{
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    int Sind = 2;
    int SOCind = 4;
    if (ID == 1)
    {
        Hind = 1;
        Sind = 3;
        SOCind = 5;
    }
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) return;
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) return;
    
    bool isS = false;
    int nEssS = sec30->ArraysOf3DDouble[Sind].size();
    if (nEssS > 0) isS = true;
    
    bool isSOC = false;
    int nSOCBuf = sec30->ArraysOf3DDouble[SOCind].size();
    if (nSOCBuf > 1) isSOC = true;
    
    //int nk = sec30->ArraysOf2DDouble[0].size();//double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    //int nklabel = sec30->ArraysOf1DDouble[0].size();//double* dkLabel;
    
    FILE *fpk;
    wxString fname = BaseName + wxT(".f90");
    wxString fpath =  filepath + wxFileName::GetPathSeparator() + fname;
    if ((fpk = fopen(fpath,"w")) != NULL)
    {
        fprintf(fpk,"!compile command: gfortran %s\n",fname.c_str().AsChar());
        fprintf(fpk,"!Main program\n");
        fprintf(fpk,"program main\n");
        fprintf(fpk,"\tuse, intrinsic :: iso_fortran_env\n");
        fprintf(fpk,"\timplicit none\n");
        fprintf(fpk,"\t!Parameters\n");
        
        wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
        int nCell = listctr->GetCount();    
        
        if(isSOC)
            fprintf(fpk,"\tinteger, parameter:: nH0 = %d, nCells = %d\n", nH, nCell);
        else
            fprintf(fpk,"\tinteger, parameter:: nH = %d, nCells = %d\n", nH, nCell);
        
        if(isSOC)
            fprintf(fpk,"\tinteger :: it, i, j, iCell, nH\n");
        else
            fprintf(fpk,"\tinteger :: it, i, j, iCell\n");
        
        fprintf(fpk,"\tinteger, allocatable :: Cells(:,:)\n");
        
        if(isSOC)
            fprintf(fpk,"\treal(8) :: a(3), b(3), c(3), as(3), bs(3), cs(3), kx, ky, kz, ka, kb, kc, resoc(1:2*nH0), imsoc(1:2*nH0)\n");
        else
            fprintf(fpk,"\treal(8) :: a(3), b(3), c(3), as(3), bs(3), cs(3), kx, ky, kz, ka, kb, kc\n");
        
        if (isS)
            fprintf(fpk,"\treal(8), allocatable :: h(:,:,:), s(:,:,:)\n");
        else
            fprintf(fpk,"\treal(8), allocatable :: h(:,:,:)\n");
        
        fprintf(fpk,"\tcomplex(16) :: Getk, GetkFrac\n");
        
        if(isSOC)
        {
            if (isS)
                fprintf(fpk,"\tcomplex(16), allocatable:: Hk(:,:), Sk(:,:), Hsoc(:,:)\n");
            else
                fprintf(fpk,"\tcomplex(16), allocatable:: Hk(:,:), Hsoc(:,:)\n");
        }
        else
        {
            if (isS)
                fprintf(fpk,"\tcomplex(16), allocatable:: Hk(:,:), Sk(:,:)\n");
            else
                fprintf(fpk,"\tcomplex(16), allocatable:: Hk(:,:)\n");            
        }
        
        fprintf(fpk,"\tcharacter(100) filename\n");
        fprintf(fpk,"\t\n");
        
        if (isSOC)
        {
            fprintf(fpk,"\t!The total size of the Hamiltonian\n");
            fprintf(fpk,"\tnH = 2*nH0\n");
            fprintf(fpk,"\t\n");
        }
        
        double a[3],b[3],c[3];
        sec30->GetVar(_("a[0]"), a[0]);
        sec30->GetVar(_("a[1]"), a[1]);
        sec30->GetVar(_("a[2]"), a[2]);
        sec30->GetVar(_("b[0]"), b[0]);
        sec30->GetVar(_("b[1]"), b[1]);
        sec30->GetVar(_("b[2]"), b[2]);
        sec30->GetVar(_("c[0]"), c[0]);
        sec30->GetVar(_("c[1]"), c[1]);
        sec30->GetVar(_("c[2]"), c[2]);
        
        fprintf(fpk,"\t!Set the unitcell vectors\n");
        fprintf(fpk,"\ta = (/%.8f, %.8f, %.8f/)\n", a[0], a[1], a[2]);
        fprintf(fpk,"\tb = (/%.8f, %.8f, %.8f/)\n", b[0], b[1], b[2]);
        fprintf(fpk,"\tc = (/%.8f, %.8f, %.8f/)\n", c[0], c[1], c[2]);
        fprintf(fpk,"\t\n");
        fprintf(fpk,"\t!Calculate the reciprocal space vectors\n");
        fprintf(fpk,"\tcall VecToReciprocal(a, b, c, as, bs, cs)\n");
        fprintf(fpk,"\twrite(*,*) \"unitcell vectors:\"\n");
        fprintf(fpk,"\twrite(*,*) \"a =\", a\n");
        fprintf(fpk,"\twrite(*,*) \"b =\", b\n");
        fprintf(fpk,"\twrite(*,*) \"c =\", c\n");
        fprintf(fpk,"\twrite(*,*) \"\"\n");
        fprintf(fpk,"\twrite(*,*) \"reciprocal vectors:\"\n");
        fprintf(fpk,"\twrite(*,*) \"a* =\", as\n");
        fprintf(fpk,"\twrite(*,*) \"b* =\", bs\n");
        fprintf(fpk,"\twrite(*,*) \"c* =\", cs\n");
        fprintf(fpk,"\t\n");
        fprintf(fpk,"\t!Set the unitcell list\n");
        fprintf(fpk,"\tallocate(Cells(1:nCells, 1:3))\n");
        
        fprintf(fpk,"\tCells = reshape((/&\n");
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            if (iCell<nCell - 1)
                fprintf(fpk,"\t\t& %d, %d, %d, &\n", lcell, mcell, ncell);
            else
                fprintf(fpk,"\t\t& %d, %d, %d &\n", lcell, mcell, ncell);
        }
        fprintf(fpk,"\t\t&/), (/nCells, 3/), order = (/ 2, 1 /))\n");
        
        fprintf(fpk,"\t\n");
        if(isSOC)
        {
            if(isS)
                fprintf(fpk,"\n\t!Allocate h, s and Hsoc arrays\n");
            else
                fprintf(fpk,"\n\t!Allocate h and Hsoc arrays\n");
        }
        else
        {
            if(isS)
                fprintf(fpk,"\n\t!Allocate h and s arrays\n");
            else
                fprintf(fpk,"\n\t!Allocate the h array\n");
        }
        
        fprintf(fpk,"\tallocate(h(1:nCells, 1:nH, 1:nH))\n");
        if (isS)
            fprintf(fpk,"\tallocate(s(1:nCells, 1:nH, 1:nH))\n");
        if (isSOC)
            fprintf(fpk,"\tallocate(Hsoc(1:nH, 1:nH))\n");
        fprintf(fpk,"\t\n");
        
        if(isSOC)
        {
            fprintf(fpk,"\t!Load files\n");
            fprintf(fpk,"2001 format (8(F6.3))\n");
            fprintf(fpk,"\twrite(*,*) ""\n");
            fprintf(fpk,"\tit = 0\n");
            fprintf(fpk,"\tdo iCell = 1,nCells\n");
            fprintf(fpk,"\t\twrite(filename,\'(\"%s_H(\", I0, \",\", I0, \",\", I0, \").dat\")\') Cells(iCell,1) ,Cells(iCell,2) ,Cells(iCell,3)\n", BaseName.c_str().AsChar());
            fprintf(fpk,"\t\tit=it+1\n");
            fprintf(fpk,"\t\twrite(*, \'(I0, \") loading file: \", A)\') it, filename\n");
            fprintf(fpk,"\t\topen(unit=100, file=filename, action=\'read\')\n");
            fprintf(fpk,"\t\tdo i=1,nH0\n");
            fprintf(fpk,"\t\t\tRead(100,*)(h(iCell, 2*i - 1, 2*j - 1) , j=1,nH0)\n");
            fprintf(fpk,"\t\t\tdo j=1,nH0\n");
            fprintf(fpk,"\t\t\t\th(iCell, 2*i, 2*j)=h(iCell, 2*i-1, 2*j-1)\n");
            fprintf(fpk,"\t\t\t\th(iCell, 2*i - 1, 2*j)=0.0d0\n");
            fprintf(fpk,"\t\t\t\th(iCell, 2*i, 2*j - 1)=0.0d0\n");
            fprintf(fpk,"\t\t\tend do\n");
            fprintf(fpk,"\t\tend do\n");
            fprintf(fpk,"\t\tclose(100)\n");
            fprintf(fpk,"\t\tdo i=1,nH\n");
            fprintf(fpk,"\t\t\twrite(*,2001) (h(iCell, i, j) , j=1,nH)\n");
            fprintf(fpk,"\t\tend do\n");
            fprintf(fpk,"\t\twrite(*,*) \"\"\n");
            fprintf(fpk,"\tend do\n");
            fprintf(fpk,"\t\n");
            
            if (isS)
            {
                fprintf(fpk,"\tdo iCell = 1,nCells\n");
                fprintf(fpk,"\t\twrite(filename,\'(\"%s_S(\", I0, \",\", I0, \",\", I0, \").dat\")\') Cells(iCell,1) ,Cells(iCell,2) ,Cells(iCell,3)\n", BaseName.c_str().AsChar());
                fprintf(fpk,"\t\tit=it+1\n");
                fprintf(fpk,"\t\twrite(*, \'(I0, \") loading file: \", A)\') it, filename\n");
                fprintf(fpk,"\t\topen(unit=100, file=filename, action=\'read\')\n");
                fprintf(fpk,"\t\tdo i=1,nH0\n");
                fprintf(fpk,"\t\t\tRead(100,*)(s(iCell, 2*i - 1, 2*j - 1) , j=1,nH0)\n");
                fprintf(fpk,"\t\t\tdo j=1,nH0\n");
                fprintf(fpk,"\t\t\t\ts(iCell, 2*i, 2*j)=s(iCell, 2*i-1, 2*j-1)\n");
                fprintf(fpk,"\t\t\t\ts(iCell, 2*i - 1, 2*j)=0.0d0\n");
                fprintf(fpk,"\t\t\t\ts(iCell, 2*i, 2*j - 1)=0.0d0\n");
                fprintf(fpk,"\t\t\tend do\n");
                fprintf(fpk,"\t\tend do\n");
                fprintf(fpk,"\t\tclose(100)\n");
                fprintf(fpk,"\t\tdo i=1,nH\n");
                fprintf(fpk,"\t\t\twrite(*,2001) (s(iCell, i, j) , j=1,nH)\n");
                fprintf(fpk,"\t\tend do\n");
                fprintf(fpk,"\t\twrite(*,*) \"\"\n");
                fprintf(fpk,"\tend do\n");
                fprintf(fpk,"\t\n");
            }
            
            fprintf(fpk,"\twrite(*,*) \"\"\n");
            fprintf(fpk,"\twrite(*,*) \"Loading real and imaginary parts of SOC Hamiltonian from files\"\n");
            fprintf(fpk,"\topen(unit=100, file=\"%s_SOC_Re.dat\", action=\'read\')\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\topen(unit=101, file=\"%s_SOC_Im.dat\", action=\'read\')\n",BaseName.c_str().AsChar());
            fprintf(fpk,"\tdo i=1,nH\n");
            fprintf(fpk,"\t\tRead(100,*) resoc\n");
            fprintf(fpk,"\t\tRead(101,*) imsoc\n");
            fprintf(fpk,"\t\tdo j=1,nH\n");
            fprintf(fpk,"\t\t\tHsoc(i,j) = CMPLX(resoc(j), imsoc(j))\n");
            fprintf(fpk,"\t\tend do\n");
            fprintf(fpk,"\tend do\n");
            fprintf(fpk,"\tclose(100)\n");
            fprintf(fpk,"\tclose(101)\n");
            fprintf(fpk,"\t\n");
        }
        else
        {
            fprintf(fpk,"\t!Load files\n");
            fprintf(fpk,"2001 format (8(F6.3))\n");
            fprintf(fpk,"\twrite(*,*) ""\n");
            fprintf(fpk,"\tit = 0\n");
            fprintf(fpk,"\tdo iCell = 1,nCells\n");
            fprintf(fpk,"\t\twrite(filename,\'(\"%s_H(\", I0, \",\", I0, \",\", I0, \").dat\")\') Cells(iCell,1) ,Cells(iCell,2) ,Cells(iCell,3)\n", BaseName.c_str().AsChar());
            fprintf(fpk,"\t\tit=it+1\n");
            fprintf(fpk,"\t\twrite(*, \'(I0, \") loading file: \", A)\') it, filename\n");
            fprintf(fpk,"\t\topen(unit=100, file=filename, action=\'read\')\n");
            fprintf(fpk,"\t\tdo i=1,nH\n");
            fprintf(fpk,"\t\t\tRead(100,*)(h(iCell, i, j) , j=1,nH)\n");
            fprintf(fpk,"\t\t\twrite(*,2001) (h(iCell, i, j) , j=1,nH)\n");
            fprintf(fpk,"\t\tend do\n");
            fprintf(fpk,"\t\tclose(100)\n");
            fprintf(fpk,"\t\twrite(*,*) \"\"\n");
            fprintf(fpk,"\tend do\n");
            fprintf(fpk,"\t\n");
            
            if (isS)
            {
                fprintf(fpk,"\tdo iCell = 1,nCells\n");
                fprintf(fpk,"\t\twrite(filename,\'(\"%s_S(\", I0, \",\", I0, \",\", I0, \").dat\")\') Cells(iCell,1) ,Cells(iCell,2) ,Cells(iCell,3)\n", BaseName.c_str().AsChar());
                fprintf(fpk,"\t\tit=it+1\n");
                fprintf(fpk,"\t\twrite(*, \'(I0, \") loading file: \", A)\') it, filename\n");
                fprintf(fpk,"\t\topen(unit=100, file=filename, action=\'read\')\n");
                fprintf(fpk,"\t\tdo i=1,nH\n");
                fprintf(fpk,"\t\t\tRead(100,*)(s(iCell, i, j) , j=1,nH)\n");
                fprintf(fpk,"\t\t\twrite(*,2001) (s(iCell, i, j) , j=1,nH)\n");
                fprintf(fpk,"\t\tend do\n");
                fprintf(fpk,"\t\tclose(100)\n");
                fprintf(fpk,"\t\twrite(*,*) \"\"\n");
                fprintf(fpk,"\tend do\n");
                fprintf(fpk,"\t\n");
            }
        }
        
        fprintf(fpk,"\n2002 format (8(\"(\",F8.2,\",\",F8.2,\")\"))\n");
        
        if(isSOC)
        {
            fprintf(fpk,"\tdo i=1,nH\n");
            fprintf(fpk,"\t\twrite(*,2002) (Hsoc(i, j) , j=1,nH)\n");
            fprintf(fpk,"\tend do\n");
            fprintf(fpk,"\twrite(*,*) \"\"\n");
            fprintf(fpk,"\t\n");
        }
        
        fprintf(fpk,"\t!Allocate Hk array\n");
        fprintf(fpk,"\tallocate(Hk(1:nH,1:nH))\n");
        if (isS)
            fprintf(fpk,"\tallocate(Sk(1:nH,1:nH))\n");
        fprintf(fpk,"\t\n");
        
        fprintf(fpk,"\n\t!Calculate the Hamiltonian in a typical k=(kx, ky, kz)\n");
        fprintf(fpk,"\tkx=0.0\n");
        fprintf(fpk,"\tky=0.0\n");
        fprintf(fpk,"\tkz=0.0\n");
        fprintf(fpk,"\twrite(*,*) \"Testing the function Getk. Hamiltonian matrix in an absolute k point\"\n");
        fprintf(fpk,"\twrite(*,*) \"k=(kx, ky, kz) = \", kx, ky ,kz\n");
        fprintf(fpk,"\tdo i=1,nH\n");
        fprintf(fpk,"\t\tdo j=1,nH\n");
        if (isSOC)
            fprintf(fpk,"\t\t\tHk(i,j) = Getk(h, kx, ky, kz, a, b, c, nCells, Cells, nH, i, j) + Hsoc(i,j)\n");
        else
            fprintf(fpk,"\t\t\tHk(i,j) = Getk(h, kx, ky, kz, a, b, c, nCells, Cells, nH, i, j)\n");
        fprintf(fpk,"\t\tend do\n");
        fprintf(fpk,"\t\twrite(*,2002) (Hk(i,j) , j=1,nH)\n");
        fprintf(fpk,"\tend do\n");
        fprintf(fpk,"\twrite(*,*) \"\"\n");
        fprintf(fpk,"\t");
        
        if (isS)
        {
            fprintf(fpk,"\n\t!Calculate the overlap matrix in a typical k=(kx, ky, kz)\n");
            fprintf(fpk,"\twrite(*,*) \"Testing the function Getk. Overlap matrix in an absolute k point\"\n");
            fprintf(fpk,"\twrite(*,*) \"k=(kx, ky, kz) = \", kx, ky ,kz\n");
            fprintf(fpk,"\tdo i=1,nH\n");
            fprintf(fpk,"\t\tdo j=1,nH\n");
            fprintf(fpk,"\t\t\tSk(i,j) = Getk(s, kx, ky, kz, a, b, c, nCells, Cells, nH, i, j)\n");
            fprintf(fpk,"\t\tend do\n");
            fprintf(fpk,"\t\twrite(*,2002) (Sk(i,j) , j=1,nH)\n");
            fprintf(fpk,"\tend do\n");
            fprintf(fpk,"\twrite(*,*) \"\"\n");
            fprintf(fpk,"\t");
        }
        
        fprintf(fpk,"\n\t!Calculate the Hamiltonian in a typical fractional k point (ka, kb, kc)\n");
        fprintf(fpk,"\tka=0.0\n");
        fprintf(fpk,"\tkb=0.25\n");
        fprintf(fpk,"\tkc=0.0\n");
        fprintf(fpk,"\twrite(*,*) \"Testing the function GetkFrac. Hamiltonian matrix in a fractional k point\"\n");
        fprintf(fpk,"\twrite(*,*) \"(ka, kb, kc) = \", ka, kb ,kc\n");
        fprintf(fpk,"\tdo i=1,nH\n");
        fprintf(fpk,"\t\tdo j=1,nH\n");
        if (isSOC)
            fprintf(fpk,"\t\t\tHk(i,j) = GetkFrac(h, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, nH, i, j) + Hsoc(i,j)\n");
        else
            fprintf(fpk,"\t\t\tHk(i,j) = GetkFrac(h, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, nH, i, j)\n");
        fprintf(fpk,"\t\tend do\n");
        fprintf(fpk,"\t\twrite(*,2002) (Hk(i,j) , j=1,nH)\n");
        fprintf(fpk,"\tend do\n");
        
        if (isS)
        {
            fprintf(fpk,"\twrite(*,*) \"\"\n");
            fprintf(fpk,"\n\t!Calculate the overlap matrix in a typical fractional k point (ka, kb, kc)\n");
            fprintf(fpk,"\twrite(*,*) \"Testing the function GetkFrac. Overlap matrix in a fractional k point\"\n");
            fprintf(fpk,"\twrite(*,*) \"(ka, kb, kc) = \", ka, kb ,kc\n");
            fprintf(fpk,"\tdo i=1,nH\n");
            fprintf(fpk,"\t\tdo j=1,nH\n");
            fprintf(fpk,"\t\t\tSk(i,j) = GetkFrac(s, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, nH, i, j)\n");
            fprintf(fpk,"\t\tend do\n");
            fprintf(fpk,"\t\twrite(*,2002) (Sk(i,j) , j=1,nH)\n");
            fprintf(fpk,"\tend do\n");
        }
        
        fprintf(fpk,"\t\n");
        fprintf(fpk,"\tdeallocate(Hk)\n");
        if (isS) fprintf(fpk,"\tdeallocate(Sk)\n");
        fprintf(fpk,"\tdeallocate(Cells)\n");
        fprintf(fpk,"\tdeallocate(h)\n");
        if (isS) fprintf(fpk,"\tdeallocate(s)\n");
        if (isSOC) fprintf(fpk,"\tdeallocate(Hsoc)\n");
        fprintf(fpk,"\t\n");
        fprintf(fpk,"end program main\n");
        fprintf(fpk,"\n");
        
        fprintf(fpk,"!Definitions\n");
        fprintf(fpk,"function GetkFrac(H, ka, kb, kc, as, bs, cs, a, b, c, nCells, Cells, nH, iH, jH)\n");
        fprintf(fpk,"\timplicit none\n");
        fprintf(fpk,"\tinteger :: nCells, nH\n");
        fprintf(fpk,"\tinteger :: i, iH, jH, Cells(nCells,3)\n");
        fprintf(fpk,"\treal(8) :: k(3), a(3), b(3), c(3), ka, kb, kc, as(3), bs(3), cs(3), H(nCells,nH,nH)\n");
        fprintf(fpk,"\tcomplex(16) :: Getk, GetkFrac\n");
        fprintf(fpk,"\tdo i=1,3\n");
        fprintf(fpk,"\t\tk(i) = ka*as(i) + kb*bs(i) + kc*cs(i)\n");
        fprintf(fpk,"\tend do\n");
        fprintf(fpk,"\tGetkFrac = Getk(H, k(1), k(2), k(3), a, b, c, nCells, Cells, nH, iH, jH)\n");
        fprintf(fpk,"end function\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"function Getk(H, kx, ky, kz, a, b, c, nCells, Cells, nH, iH, jH)\n");
        fprintf(fpk,"\timplicit none\n");
        fprintf(fpk,"\tinteger :: nCells, nH\n");
        fprintf(fpk,"\tinteger :: iH, jH, icell, Cells(nCells,3)\n");
        fprintf(fpk,"\treal(8) :: K(3), R(3), a(3), b(3), c(3), kx, ky, kz, H(nCells,nH,nH), dot\n");
        fprintf(fpk,"\tcomplex(16) :: i, Getk\n");
        fprintf(fpk,"\ti = (0.0d0, 1.0d0)\n");
        fprintf(fpk,"\tK(1) = kx\n");
        fprintf(fpk,"\tK(2) = ky\n");
        fprintf(fpk,"\tK(3) = kz\n");
        fprintf(fpk,"\t\n");
        fprintf(fpk,"\tGetk=(0.0d0, 0.0d0)\n");
        fprintf(fpk,"\tdo icell=1,nCells\n");
        fprintf(fpk,"\t\tif (Cells(icell,1) == 0 .and. Cells(icell,2) == 0 .and. Cells(icell,3) == 0) then\n");
        fprintf(fpk,"\t\t\tGetk = Getk + H(icell,iH,jH)\n");
        fprintf(fpk,"\t\telse\n");
        fprintf(fpk,"\t\t\tR(1) = Cells(icell,1) * a(1) + Cells(icell,2) * b(1) + Cells(icell,3) * c(1)\n");
        fprintf(fpk,"\t\t\tR(2) = Cells(icell,1) * a(2) + Cells(icell,2) * b(2) + Cells(icell,3) * c(2)\n");
        fprintf(fpk,"\t\t\tR(3) = Cells(icell,1) * a(3) + Cells(icell,2) * b(3) + Cells(icell,3) * c(3)\n");
        fprintf(fpk,"\t\t\tGetk = Getk + H(icell,iH,jH) * exp(-i*dot(K, R)) + H(icell,jH,iH) * exp(i*dot(K, R))  !V*Exp(-ikR) + VT*Exp(ikR)\n");
        fprintf(fpk,"\t\tend if\n");
        fprintf(fpk,"\tend do\n");
        fprintf(fpk,"end function\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"function dot(a, b)\n");
        fprintf(fpk,"\timplicit none\n");
        fprintf(fpk,"\tinteger :: i\n");
        fprintf(fpk,"\treal(8) :: a(3), b(3)\n");
        fprintf(fpk,"\treal(8) :: dot\n");
        fprintf(fpk,"\tdot = 0.0d0\n");
        fprintf(fpk,"\tdo i=1,3\n");
        fprintf(fpk,"\t\tdot = dot + a(i)*b(i)\n");
        fprintf(fpk,"\tend do\n");
        fprintf(fpk,"end function\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"subroutine cross(a, b, c)\n");
        fprintf(fpk,"\timplicit none\n");
        fprintf(fpk,"\treal(8) :: a(3), b(3), c(3)\n");
        fprintf(fpk,"\tc(1) = a(2)*b(3)-a(3)*b(2)\n");
        fprintf(fpk,"\tc(2) = a(3)*b(1)-a(1)*b(3)\n");
        fprintf(fpk,"\tc(3) = a(1)*b(2)-a(2)*b(1)\n");
        fprintf(fpk,"end subroutine\n");
        fprintf(fpk,"\n");
        fprintf(fpk,"subroutine VecToReciprocal(a, b, c, ak, bk, ck)\n");
        fprintf(fpk,"\timplicit none\n");
        fprintf(fpk,"\tinteger :: i\n");
        fprintf(fpk,"\treal(8) :: Pi, a(3), b(3), c(3), ak(3), bk(3), ck(3), bc(3), ca(3), ab(3), volume, volumek, dot\n");
        fprintf(fpk,"\tPi = dacos(-1.0d0)\n");
        fprintf(fpk,"\tcall cross(b, c, bc)\n");
        fprintf(fpk,"\tcall cross(c, a, ca)\n");
        fprintf(fpk,"\tcall cross(a, b, ab)\n");
        fprintf(fpk,"\tvolume = dot(a, bc)\n");
        fprintf(fpk,"\tvolumek = 2.0*Pi / volume\n");
        fprintf(fpk,"\tdo i=1,3\n");
        fprintf(fpk,"\t\tak(i) = volumek*bc(i)\n");
        fprintf(fpk,"\t\tbk(i) = volumek*ca(i)\n");
        fprintf(fpk,"\t\tck(i) = volumek*ab(i)\n");
        fprintf(fpk,"\tenddo\n");
        fprintf(fpk,"end subroutine\n");
        fprintf(fpk,"\n");
        
        fclose(fpk);
    }
}

void MainFrame::GenerateMathematicaCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1)
{
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    int Sind = 2;
    int SOCind = 4;
    if (ID == 1)
    {
        Hind = 1;
        Sind = 3;
        SOCind = 5;
    }
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) return;
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) return;
    
    bool isS = false;
    int nEssS = sec30->ArraysOf3DDouble[Sind].size();
    if (nEssS > 0) isS = true;
    
    bool isSOC = false;
    int nSOCBuf = sec30->ArraysOf3DDouble[SOCind].size();
    if (nSOCBuf > 1) isSOC = true;
    
    int nk = sec30->ArraysOf2DDouble[0].size();//double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    int nklabel = sec30->ArraysOf1DDouble[0].size();//double* dkLabel;
    
    FILE *fpk;
    wxString fname = filepath + wxFileName::GetPathSeparator() + BaseName + wxT(".nb");
    if ((fpk = fopen(fname,"w")) != NULL)
    {
        fprintf(fpk,"(*Define the parameters*)\n");
        if(isSOC)
        {
            fprintf(fpk,"nH0 = %d;\n", nH);
            fprintf(fpk,"nH = 2*nH0;\n", nH);
        }
        else
            fprintf(fpk,"nH = %d;\n", nH);
        fprintf(fpk,"nk = %d;\n", nk);
        fprintf(fpk,"labels = {");
        for (int iklabel=0; iklabel<nklabel; iklabel++)
        {
            //sec30->ArraysOf1DDouble[0]//double* dkLabel;
            //sec30->ArraysOf1DString[0]//wxString* kLabel;
            if (iklabel>0) fprintf(fpk,",");
            wxString mylabel = sec30->ArraysOf1DString[0][iklabel];
            if (mylabel == _("\\Gamma")) mylabel = _("G");
            fprintf(fpk,"{{%.3f, 0.0}, \"%s\"}", sec30->ArraysOf1DDouble[0][iklabel], mylabel.c_str().AsChar());
        }
        fprintf(fpk,"};\n");
        fprintf(fpk,"nlabels = Length[labels];\n\n");
        
        fprintf(fpk,"(*Set the directory*)\n");
        fprintf(fpk,"SetDirectory[NotebookDirectory[]];\n");
        fprintf(fpk,"Directory[];\n\n");
        
        fprintf(fpk,"(*Load Hamiltonian from the files*)\n");
        wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
        int nCell = listctr->GetCount();        
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            wxString fname1 = wxT("./") + BaseName + wxT("_H") + WorkingCell + wxT(".dat");
            fprintf(fpk,"h[%d, %d, %d] = Import[\"%s\"];\n", lcell, mcell, ncell, fname1.c_str().AsChar());
        }
        
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            if (!(lcell==0 && mcell==0 && ncell == 0))
                fprintf(fpk,"h[%d, %d, %d] = ConjugateTranspose[h[%d, %d, %d]];\n", -lcell, -mcell, -ncell, lcell, mcell, ncell);
        }
        
        if (isS)
        {
            fprintf(fpk,"\n");
            fprintf(fpk,"(*Load overlap matrices from the files*)\n");    
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                wxString fname1 = wxT("./") + BaseName + wxT("_S") + WorkingCell + wxT(".dat");
                fprintf(fpk,"s[%d, %d, %d] = Import[\"%s\"];\n", lcell, mcell, ncell, fname1.c_str().AsChar());
            }
            
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                if (!(lcell==0 && mcell==0 && ncell == 0))
                    fprintf(fpk,"s[%d, %d, %d] = ConjugateTranspose[s[%d, %d, %d]];\n", -lcell, -mcell, -ncell, lcell, mcell, ncell);
            }
        }
        
        if(isSOC)
        {
            fprintf(fpk,"\nSOCRe = Import[\"./%s_SOC_Re.dat\"];\n",BaseName.c_str().AsChar());
            fprintf(fpk,"SOCIm = Import[\"./%s_SOC_Im.dat\"];\n",BaseName.c_str().AsChar());
            fprintf(fpk,"Hsoc = SOCRe + I*SOCIm;\n");
            
            fprintf(fpk,"\n(*Evaluate H*I_{2x2}*)\n");
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                if (!(lcell==0 && mcell==0 && ncell == 0))
                {
                    fprintf(fpk,"h[%d, %d, %d] = KroneckerProduct[h[%d, %d, %d],{{1, 0}, {0, 1}}];\n", lcell, mcell, ncell, lcell, mcell, ncell);
                    fprintf(fpk,"h[%d, %d, %d] = KroneckerProduct[h[%d, %d, %d],{{1, 0}, {0, 1}}];\n", -lcell, -mcell, -ncell, -lcell, -mcell, -ncell);
                }
                else
                    fprintf(fpk,"h[%d, %d, %d] = KroneckerProduct[h[%d, %d, %d],{{1, 0}, {0, 1}}];\n", lcell, mcell, ncell, lcell, mcell, ncell);
            }
            
            if (isS)
            {
                fprintf(fpk,"\n(*Evaluate S*I_{2x2}*)\n");
                for (int iCell=0; iCell<nCell; iCell++)
                {
                    wxString WorkingCell = listctr->GetString(iCell);
                    int lcell,mcell,ncell;
                    sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                    if (!(lcell==0 && mcell==0 && ncell == 0))
                    {
                        fprintf(fpk,"s[%d, %d, %d] = KroneckerProduct[s[%d, %d, %d],{{1, 0}, {0, 1}}];\n", lcell, mcell, ncell, lcell, mcell, ncell);
                        fprintf(fpk,"s[%d, %d, %d] = KroneckerProduct[s[%d, %d, %d],{{1, 0}, {0, 1}}];\n", -lcell, -mcell, -ncell, -lcell, -mcell, -ncell);
                    }
                    else
                        fprintf(fpk,"s[%d, %d, %d] = KroneckerProduct[s[%d, %d, %d],{{1, 0}, {0, 1}}];\n", lcell, mcell, ncell, lcell, mcell, ncell);
                }
            }
            
            fprintf(fpk,"\n(*Add SOC to the total Hamiltonian: HTot = H*I_{2x2} + Hsoc*)\n");
            fprintf(fpk,"h[%d, %d, %d] = h[%d, %d, %d] + Hsoc;\n", 0, 0, 0, 0, 0, 0);
        }
        
        fprintf(fpk,"\n");
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            fprintf(fpk,"MatrixForm[h[%d, %d, %d]]\n", lcell, mcell, ncell);
        }
        
        if (isS)
        {
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                fprintf(fpk,"MatrixForm[s[%d, %d, %d]]\n", lcell, mcell, ncell);
            }
        }
        
        fprintf(fpk,"\n(*Load k-points from the file*)\n");
        fprintf(fpk,"kPath = Import[\"./%s_kPath.dat\"];\n", BaseName.c_str().AsChar());
        
        double a[3],b[3],c[3];
        sec30->GetVar(_("a[0]"), a[0]);
        sec30->GetVar(_("a[1]"), a[1]);
        sec30->GetVar(_("a[2]"), a[2]);
        sec30->GetVar(_("b[0]"), b[0]);
        sec30->GetVar(_("b[1]"), b[1]);
        sec30->GetVar(_("b[2]"), b[2]);
        sec30->GetVar(_("c[0]"), c[0]);
        sec30->GetVar(_("c[1]"), c[1]);
        sec30->GetVar(_("c[2]"), c[2]);
        
        fprintf(fpk,"\n(*Set the unitcell vectors*)\n");
        fprintf(fpk,"a={%.8f, %.8f, %.8f};\n", a[0], a[1], a[2]);
        fprintf(fpk,"b={%.8f, %.8f, %.8f};\n", b[0], b[1], b[2]);
        fprintf(fpk,"c={%.8f, %.8f, %.8f};\n", c[0], c[1], c[2]);
        
        fprintf(fpk,"\n(*Calculate the reciprocal space vectors*)\n");
        fprintf(fpk,"vol = a.Cross[b, c];\n");
        fprintf(fpk,"as = 2*Pi*Cross[b, c]/vol;\n");
        fprintf(fpk,"bs = 2*Pi*Cross[c, a]/vol;\n");
        fprintf(fpk,"cs = 2*Pi*Cross[a, b]/vol;\n");
        
        int TBl,TBm,TBn;
        sec30->GetVar(_("TBl[0]"), TBl);
        sec30->GetVar(_("TBm[0]"), TBm);
        sec30->GetVar(_("TBn[0]"), TBn);
        if (isS)
            fprintf(fpk,"\n(*Calculate the TB Hamiltonian and overlap matrices in reciprocal space*)\n");
        else
            fprintf(fpk,"\n(*Calculate the TB Hamiltonian in reciprocal space*)\n");
        fprintf(fpk,"HkFunc = Sum[h[l, m, n]*Exp[-I*((ka*as + kb*bs + kc*cs).(l*a + m*b + n*c))], {l, %d, %d}, {m, %d, %d}, {n, %d, %d}];\n", -TBl, TBl, -TBm, TBm, -TBn, TBn);
        if (isS)
            fprintf(fpk,"SkFunc = Sum[s[l, m, n]*Exp[-I*((ka*as + kb*bs + kc*cs).(l*a + m*b + n*c))], {l, %d, %d}, {m, %d, %d}, {n, %d, %d}];\n", -TBl, TBl, -TBm, TBm, -TBn, TBn);
        
        if (isS)
            fprintf(fpk,"\n(*Define H and S functions as TB Hamiltonian and overlap matrix*)\n");
        else
            fprintf(fpk,"\n(*Define H function as TB Hamiltonian*)\n");
        fprintf(fpk,"H[{ka_, kb_, kc_}] := Evaluate[HkFunc];\n");
        if (isS)
            fprintf(fpk,"S[{ka_, kb_, kc_}] := Evaluate[SkFunc];\n");
        
        fprintf(fpk,"\n(*Band-Structure Calculation*)\n");
        fprintf(fpk,"Print[\"The number of bands is \" <> ToString[nH]];\n");
        fprintf(fpk,"nbands = nH;\n");
        fprintf(fpk,"bands = Table[{0.0, 0.0}, {nbands}, {nk}];\n");
        fprintf(fpk,"dpath = 0.0;\n");
        fprintf(fpk,"Do[\n");
        fprintf(fpk,"  {ka0, kb0, kc0, dpath} = kPath[[ik]];\n");
        if (isS)
            fprintf(fpk,"  eig = Eigenvalues[{H[{ka0, kb0, kc0}], S[{ka0, kb0, kc0}]}];\n");
        else
            fprintf(fpk,"  eig = Eigenvalues[H[{ka0, kb0, kc0}]];\n");
        fprintf(fpk,"  eig = Re[eig];(*The imaginary part is practically zero.*)\n");
        fprintf(fpk,"  eig = Sort[eig];\n");
        fprintf(fpk,"  Do[\n");
        fprintf(fpk,"   bands[[iband, ik, 1]] = dpath;\n");
        fprintf(fpk,"   bands[[iband, ik, 2]] = eig[[iband]];\n");
        fprintf(fpk,"   , {iband, 1, nbands}];\n");
        fprintf(fpk,"  , {ik, 1, nk}];\n");
        fprintf(fpk,"dmax = dpath;\n");
        
        fprintf(fpk,"\n(*Plot the band-structure*)\n");
        fprintf(fpk,"Show[\n");
        fprintf(fpk," ListLinePlot[bands, PlotRange -> {{0, dmax}, All}, PlotStyle -> RGBColor[0.65, 0, 0], Frame -> True, Axes -> False],\n");
        fprintf(fpk," Graphics[{Directive[Thick, Dashed, Red], Line[{{0, 0}, {dmax, 0}}]}],\n");
        fprintf(fpk," ListPlot[Table[Callout[labels[[i, 1]], labels[[i, 2]], Background -> Transparent], {i, nlabels}], PlotRange -> {{0, dmax}, All}]\n");
        fprintf(fpk,"]\n");
        fclose(fpk);
    }
}

void MainFrame::GenerateMatlabCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1)
{
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    int Sind = 2;
    int SOCind = 4;
    if (ID == 1)
    {
        Hind = 1;
        Sind = 3;
        SOCind = 5;
    }
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) return;
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) return;
    
    bool isS = false;
    int nEssS = sec30->ArraysOf3DDouble[Sind].size();
    if (nEssS > 0) isS = true;
    
    bool isSOC = false;
    int nSOCBuf = sec30->ArraysOf3DDouble[SOCind].size();
    if (nSOCBuf > 1) isSOC = true;
    
    int nk = sec30->ArraysOf2DDouble[0].size();//double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    int nklabel = sec30->ArraysOf1DDouble[0].size();//double* dkLabel;
    
    FILE *fpk;
    wxString fname = filepath + wxFileName::GetPathSeparator() + BaseName + wxT(".m");
    if ((fpk = fopen(fname,"w")) != NULL)
    {
        fprintf(fpk,"%%Clear global parameters\n");
        fprintf(fpk,"clear all\n");
        fprintf(fpk,"clc\n");
        
        fprintf(fpk,"\n%%Global parameters\n");
        fprintf(fpk,"global nH lMax mMax nMax l0 m0 n0 a b c as bs cs\n");
        
        fprintf(fpk,"\n%%Define the parameters\n");
        if (isSOC)
            fprintf(fpk,"nH = %d;\n", 2*nH);
        else
            fprintf(fpk,"nH = %d;\n", nH);
        fprintf(fpk,"nk = %d;\n", nk);
        fprintf(fpk,"labels = {");
        for (int iklabel=0; iklabel<nklabel; iklabel++)
        {
            //sec30->ArraysOf1DDouble[0]//double* dkLabel;
            //sec30->ArraysOf1DString[0]//wxString* kLabel;
            if (iklabel>0) fprintf(fpk,",");
            wxString mylabel = sec30->ArraysOf1DString[0][iklabel];
            if (mylabel == _("\\Gamma")) mylabel = _("G");
            fprintf(fpk,"{%.3f, \'%s\'}", sec30->ArraysOf1DDouble[0][iklabel], mylabel.c_str().AsChar());
        }
        fprintf(fpk,"};\n");
        fprintf(fpk,"nlabels = length(labels);\n");
        
        int TBl,TBm,TBn;
        sec30->GetVar(_("TBl[0]"), TBl);
        sec30->GetVar(_("TBm[0]"), TBm);
        sec30->GetVar(_("TBn[0]"), TBn);
        
        fprintf(fpk,"\n%%The dimensions of the TB model\n");
        fprintf(fpk,"lMax = %d;\n", TBl);
        fprintf(fpk,"mMax = %d;\n", TBm);
        fprintf(fpk,"nMax = %d;\n", TBn);
        
        fprintf(fpk,"\n%%We need to shift the indices, because Matlab does not accept negative index\n");
        fprintf(fpk,"l0 = lMax+1; %%It will be added to the all i indices\n");
        fprintf(fpk,"m0 = mMax+1; %%It will be added to the all j indices\n");
        fprintf(fpk,"n0 = nMax+1; %%It will be added to the all k indices\n");
        
        if (isS)
            fprintf(fpk,"\n%%Load Hamiltonian and overlap matrix from the files\n");
        else
            fprintf(fpk,"\n%%Load Hamiltonian from the files\n");
        fprintf(fpk,"h=cell(1,1);\n");
        if (isS) fprintf(fpk,"s=cell(1,1);\n");
        wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
        int nCell = listctr->GetCount();        
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            wxString fname1 = wxT("./") + BaseName + wxT("_H") + WorkingCell + wxT(".dat");
            fprintf(fpk,"h{l0 + %d, m0 + %d, n0 + %d} = load(\'%s\');\n", lcell, mcell, ncell, fname1.c_str().AsChar());
        }
        
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            if (!(lcell==0 && mcell==0 && ncell == 0))
                fprintf(fpk,"h{l0 + %d, m0 + %d, n0 + %d} = h{l0 + %d, m0 + %d, n0 + %d}\';\n", -lcell, -mcell, -ncell, lcell, mcell, ncell);
        }
        
        if (isS)
        {
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                wxString fname1 = wxT("./") + BaseName + wxT("_S") + WorkingCell + wxT(".dat");
                fprintf(fpk,"s{l0 + %d, m0 + %d, n0 + %d} = load(\'%s\');\n", lcell, mcell, ncell, fname1.c_str().AsChar());
            }
            
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                if (!(lcell==0 && mcell==0 && ncell == 0))
                    fprintf(fpk,"s{l0 + %d, m0 + %d, n0 + %d} = s{l0 + %d, m0 + %d, n0 + %d}\';\n", -lcell, -mcell, -ncell, lcell, mcell, ncell);
            }
        }
        
        if (isSOC)
        {
            fprintf(fpk,"\n%%Load real and imaginary parts of Hsoc from the files\n");
            wxString fnamere = wxT("./") + BaseName + wxT("_SOC_Re.dat");
            fprintf(fpk,"ReSOC = load(\'%s\');\n", fnamere.c_str().AsChar());
            wxString fnameim = wxT("./") + BaseName + wxT("_SOC_Im.dat");
            fprintf(fpk,"ImSOC = load(\'%s\');\n", fnameim.c_str().AsChar());
            fprintf(fpk,"Hsoc = ReSOC + 1i * ImSOC;\n");
            
            fprintf(fpk,"\n%%Evaluate H*I_{2x2}\n");
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                if (!(lcell==0 && mcell==0 && ncell == 0))
                {
                    fprintf(fpk,"h{l0 + %d, m0 + %d, n0 + %d} = kron(h{l0 + %d, m0 + %d, n0 + %d},[1 0;0 1]);\n", lcell, mcell, ncell, lcell, mcell, ncell);
                    fprintf(fpk,"h{l0 + %d, m0 + %d, n0 + %d} = kron(h{l0 + %d, m0 + %d, n0 + %d},[1 0;0 1]);\n", -lcell, -mcell, -ncell, -lcell, -mcell, -ncell);
                }
                else
                    fprintf(fpk,"h{l0 + %d, m0 + %d, n0 + %d} = kron(h{l0 + %d, m0 + %d, n0 + %d},[1 0;0 1]);\n", lcell, mcell, ncell, lcell, mcell, ncell);
            }
            
            if (isS)
            {
                fprintf(fpk,"\n%%Evaluate S*I_{2x2}\n");
                for (int iCell=0; iCell<nCell; iCell++)
                {
                    wxString WorkingCell = listctr->GetString(iCell);
                    int lcell,mcell,ncell;
                    sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                    if (!(lcell==0 && mcell==0 && ncell == 0))
                    {
                        fprintf(fpk,"s{l0 + %d, m0 + %d, n0 + %d} = kron(s{l0 + %d, m0 + %d, n0 + %d},[1 0;0 1]);\n", lcell, mcell, ncell, lcell, mcell, ncell);
                        fprintf(fpk,"s{l0 + %d, m0 + %d, n0 + %d} = kron(s{l0 + %d, m0 + %d, n0 + %d},[1 0;0 1]);\n", -lcell, -mcell, -ncell, -lcell, -mcell, -ncell);
                    }
                    else
                        fprintf(fpk,"s{l0 + %d, m0 + %d, n0 + %d} = kron(s{l0 + %d, m0 + %d, n0 + %d},[1 0;0 1]);\n", lcell, mcell, ncell, lcell, mcell, ncell);
                }
            }
            
            fprintf(fpk,"\n%%Add SOC to the total Hamiltonian: HTot = H*I_{2x2} + Hsoc\n");
            fprintf(fpk,"h{l0 + %d, m0 + %d, n0 + %d} = h{l0 + %d, m0 + %d, n0 + %d} + Hsoc;\n", 0, 0, 0, 0, 0, 0);
        }
        
        fprintf(fpk,"\n%%Load k-points from the file\n");
        fprintf(fpk,"kPath = load(\'./%s_kPath.dat\');\n", BaseName.c_str().AsChar());
        
        double a[3],b[3],c[3];
        sec30->GetVar(_("a[0]"), a[0]);
        sec30->GetVar(_("a[1]"), a[1]);
        sec30->GetVar(_("a[2]"), a[2]);
        sec30->GetVar(_("b[0]"), b[0]);
        sec30->GetVar(_("b[1]"), b[1]);
        sec30->GetVar(_("b[2]"), b[2]);
        sec30->GetVar(_("c[0]"), c[0]);
        sec30->GetVar(_("c[1]"), c[1]);
        sec30->GetVar(_("c[2]"), c[2]);
        
        fprintf(fpk,"\n%%Set the unitcell vectors\n");
        fprintf(fpk,"a=[%.8f, %.8f, %.8f];\n", a[0], a[1], a[2]);
        fprintf(fpk,"b=[%.8f, %.8f, %.8f];\n", b[0], b[1], b[2]);
        fprintf(fpk,"c=[%.8f, %.8f, %.8f];\n", c[0], c[1], c[2]);
        
        fprintf(fpk,"\n%%Calculate the reciprocal space vectors\n");
        fprintf(fpk,"vol = a*cross(b, c)\';\n");
        fprintf(fpk,"as = 2*pi*cross(b, c)/vol;\n");
        fprintf(fpk,"bs = 2*pi*cross(c, a)/vol;\n");
        fprintf(fpk,"cs = 2*pi*cross(a, b)/vol;\n");
        
        fprintf(fpk,"\n%%Band-Structure Calculation\n");
        fprintf(fpk,"nbands = nH;\n");
        fprintf(fpk,"disp(['The number of bands is ' mat2str(nbands)]);\n");
        fprintf(fpk,"bands = zeros(nbands, nk, 2);\n");
        fprintf(fpk,"dpath = 0.0;\n");
        
        fprintf(fpk,"for ik=1:nk\n");
        fprintf(fpk,"\tka = kPath(ik,1);\n");
        fprintf(fpk,"\tkb = kPath(ik,2);\n");
        fprintf(fpk,"\tkc = kPath(ik,3);\n");
        fprintf(fpk,"\tdpath = kPath(ik,4);\n");
        fprintf(fpk,"\thk = Getk(h, ka, kb, kc);\n");
        if (isS) fprintf(fpk,"\tsk = Getk(s, ka, kb, kc);\n");
        if (isS)
            fprintf(fpk,"\tEIG = eig(hk,sk);\n");
        else
            fprintf(fpk,"\tEIG = eig(hk);\n");
        fprintf(fpk,"\tEIG = real(EIG); %%The imaginary part is practically zero.\n");
        fprintf(fpk,"\tEIG = sort(EIG);\n");
        fprintf(fpk,"\tfor iband=1:nbands\n");
        fprintf(fpk,"\t\tbands(iband,ik,1) = dpath;\n");
        fprintf(fpk,"\t\tbands(iband,ik,2) = EIG(iband);\n");
        fprintf(fpk,"\tend\n");
        fprintf(fpk,"end\n");
        
        fprintf(fpk,"\n%%Plot the band-structure\n");
        fprintf(fpk,"dmax = dpath;\n");
        fprintf(fpk,"close all\n");
        fprintf(fpk,"figure(1)\n");
        fprintf(fpk,"for iband=1:nbands\n");
        fprintf(fpk,"\tplot(bands(iband,:,1),bands(iband,:,2),'-r')\n");
        fprintf(fpk,"\thold on\n");
        fprintf(fpk,"end\n\n");
        fprintf(fpk,"xlim([0 dmax])\n");
        fprintf(fpk,"yrange=ylim();\n");
        fprintf(fpk,"for i=1:nlabels\n");
        fprintf(fpk,"\tline([labels{i}{1},labels{i}{1}],[yrange(1),yrange(2)]);\n");
        fprintf(fpk,"end\n");
        fclose(fpk);
    }
    
    FILE *fpk2;
    wxString fname2 = filepath + wxT("/Getk.m");
    if ((fpk2 = fopen(fname2,"w")) != NULL)
    {
        fprintf(fpk2,"function Mk = Getk(Mr, ka, kb, kc)\n");
        fprintf(fpk2,"global nH lMax mMax nMax l0 m0 n0 a b c as bs cs\n");
        fprintf(fpk2,"Mk = zeros(nH, nH);\n\n");
        fprintf(fpk2,"for i=1:nH\n");
        fprintf(fpk2,"\tfor j=1:nH\n");
        fprintf(fpk2,"\t\tMk(i,j) = 0.0;\n");
        fprintf(fpk2,"\t\tfor l=-lMax:lMax\n");
        fprintf(fpk2,"\t\t\tfor m=-mMax:mMax\n");
        fprintf(fpk2,"\t\t\t\tfor n=-nMax:nMax\n");
        fprintf(fpk2,"\t\t\t\t\tMij = Mr{l0 + l, m0 + m, n0 + n}(i,j);\n");
        fprintf(fpk2,"\t\t\t\t\tMk(i,j) = Mk(i,j) + Mij*exp(-1i*(ka*as + kb*bs + kc*cs)*(l*a\' + m*b\' + n*c\'));\n");
        fprintf(fpk2,"\t\t\t\tend\n");
        fprintf(fpk2,"\t\t\tend\n");
        fprintf(fpk2,"\t\tend\n");
        fprintf(fpk2,"\tend\n");
        fprintf(fpk2,"end\n");
        fclose(fpk2);
    }
}

void MainFrame::GeneratePythonCode(wxString filepath, wxString BaseName, int MyID_Initial0Final1)
{
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    int Sind = 2;
    int SOCind = 4;
    if (ID == 1)
    {
        Hind = 1;
        Sind = 3;
        SOCind = 5;
    }
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) return;
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) return;
    
    bool isS = false;
    int nEssS = sec30->ArraysOf3DDouble[Sind].size();
    if (nEssS > 0) isS = true;
    
    bool isSOC = false;
    int nSOCBuf = sec30->ArraysOf3DDouble[SOCind].size();
    if (nSOCBuf > 1) isSOC = true;
    
    int nk = sec30->ArraysOf2DDouble[0].size();//double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    int nklabel = sec30->ArraysOf1DDouble[0].size();//double* dkLabel;
    
    FILE *fpk;
    wxString fname = filepath + wxFileName::GetPathSeparator() + BaseName + wxT(".py");
    if ((fpk = fopen(fname,"w")) != NULL)
    {
        fprintf(fpk,"#Import libraries\n");
        fprintf(fpk,"import numpy as np\n");
        fprintf(fpk,"from scipy import linalg as LA\n");
        fprintf(fpk,"import matplotlib.pyplot as plt\n");
        
        fprintf(fpk,"\n#Function definition for Hamiltonian\n");
        fprintf(fpk,"def Getk(Mr, ka, kb, kc):\n");
        fprintf(fpk,"   mk = np.array([[0.0 + 0.0*1j for j in range(nH)] for i in range(nH)])\n");
        fprintf(fpk,"   for i in range(nH):\n");
        fprintf(fpk,"      for j in range(nH):\n");
        fprintf(fpk,"         mk[i][j] = 0.0 + 0.0*1j\n");
        fprintf(fpk,"         for l in range(-lMax, lMax + 1):\n");
        fprintf(fpk,"            for m in range(-mMax, mMax + 1):\n");
        fprintf(fpk,"               for n in range(-nMax, nMax + 1):\n");
        fprintf(fpk,"                  mij = Mr[l0 + l][m0 + m][n0 + n][i][j]\n");
        fprintf(fpk,"                  kvec = ka*astar + kb*bstar + kc*cstar\n");
        fprintf(fpk,"                  Rvec = l*a + m*b + n*c\n");
        fprintf(fpk,"                  mk[i][j] = mk[i][j] + mij*np.exp(-1j*np.dot(kvec,Rvec))\n");
        fprintf(fpk,"   return mk\n");
        
        fprintf(fpk,"\n#Define the parameters\n");
        fprintf(fpk,"pi = np.arccos(-1.0)\n");
        fprintf(fpk,"nH = %d\n", nH);
        fprintf(fpk,"nk = %d\n", nk);
        fprintf(fpk,"xlabels = [");
        for (int iklabel=0; iklabel<nklabel; iklabel++)
        {
            //sec30->ArraysOf1DDouble[0]//double* dkLabel;
            //sec30->ArraysOf1DString[0]//wxString* kLabel;
            if (iklabel>0) fprintf(fpk,",");
            fprintf(fpk,"%.3f", sec30->ArraysOf1DDouble[0][iklabel]);
        }
        fprintf(fpk,"]\n");
        fprintf(fpk,"labels = [");
        for (int iklabel=0; iklabel<nklabel; iklabel++)
        {
            //sec30->ArraysOf1DDouble[0]//double* dkLabel;
            //sec30->ArraysOf1DString[0]//wxString* kLabel;
            if (iklabel>0) fprintf(fpk,",");
            wxString mylabel = sec30->ArraysOf1DString[0][iklabel];
            if (mylabel == _("\\Gamma")) mylabel = _("G");
            fprintf(fpk,"\"%s\"", mylabel.c_str().AsChar());
        }
        fprintf(fpk,"]\n");
        fprintf(fpk,"nlabels = len(labels)\n");
        
        int TBl,TBm,TBn;
        sec30->GetVar(_("TBl[0]"), TBl);
        sec30->GetVar(_("TBm[0]"), TBm);
        sec30->GetVar(_("TBn[0]"), TBn);
        
        fprintf(fpk,"\n#The dimensions of the TB model\n");
        fprintf(fpk,"lMax = %d\n", TBl);
        fprintf(fpk,"mMax = %d\n", TBm);
        fprintf(fpk,"nMax = %d\n", TBn);
        
        fprintf(fpk,"\n#We need to shift the indices, because Python does not accept negative index\n");
        fprintf(fpk,"l0 = lMax #It will be added to the all i indices\n");
        fprintf(fpk,"m0 = mMax #It will be added to the all j indices\n");
        fprintf(fpk,"n0 = nMax #It will be added to the all k indices\n");
        
        if (isS)
            fprintf(fpk,"\n#Load Hamiltonian and overlap matrix from the files\n");
        else
            fprintf(fpk,"\n#Load Hamiltonian from the files\n");
        wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
        int nCell = listctr->GetCount();
        fprintf(fpk,"h = [[[0 for k in range(2*nMax+1)] for j in range(2*mMax + 1)] for i in range(2*lMax+1)]\n");
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            wxString fname1 = wxT("./") + BaseName + wxT("_H") + WorkingCell + wxT(".dat");
            fprintf(fpk,"h[l0 + %d][m0 + %d][n0 + %d] = np.loadtxt(\'%s\', usecols=range(nH))\n", lcell, mcell, ncell, fname1.c_str().AsChar());
        }
        
        for (int iCell=0; iCell<nCell; iCell++)
        {
            wxString WorkingCell = listctr->GetString(iCell);
            int lcell,mcell,ncell;
            sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
            if (!(lcell==0 && mcell==0 && ncell == 0))
                fprintf(fpk,"h[l0 + %d][m0 + %d][n0 + %d] = h[l0 + %d][m0 + %d][n0 + %d].conj().T\n", -lcell, -mcell, -ncell, lcell, mcell, ncell);
        }
        
        if (isS)
        {
            fprintf(fpk,"s = [[[0 for k in range(2*nMax+1)] for j in range(2*mMax + 1)] for i in range(2*lMax+1)]\n");
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                wxString fname1 = wxT("./") + BaseName + wxT("_S") + WorkingCell + wxT(".dat");
                fprintf(fpk,"s[l0 + %d][m0 + %d][n0 + %d] = np.loadtxt(\'%s\', usecols=range(nH))\n", lcell, mcell, ncell, fname1.c_str().AsChar());
            }
            
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                if (!(lcell==0 && mcell==0 && ncell == 0))
                    fprintf(fpk,"s[l0 + %d][m0 + %d][n0 + %d] = s[l0 + %d][m0 + %d][n0 + %d].conj().T\n", -lcell, -mcell, -ncell, lcell, mcell, ncell);
            }
        }
        
        if(isSOC)
        {
            fprintf(fpk,"\n#Taking spin into accounts\n");
            fprintf(fpk,"nH = 2*nH\n");
            fprintf(fpk,"SOCRe = np.loadtxt('./%s_SOC_Re.dat', usecols=range(nH))\n",BaseName.c_str().AsChar());
            fprintf(fpk,"SOCIm = np.loadtxt('./%s_SOC_Im.dat', usecols=range(nH))\n",BaseName.c_str().AsChar());
            fprintf(fpk,"Hsoc = SOCRe + 1j * SOCIm\n");
            
            fprintf(fpk,"\n#Evaluate H*I_{2x2}\n");
            for (int iCell=0; iCell<nCell; iCell++)
            {
                wxString WorkingCell = listctr->GetString(iCell);
                int lcell,mcell,ncell;
                sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                if (!(lcell==0 && mcell==0 && ncell == 0))
                {
                    fprintf(fpk,"h[l0 + %d][m0 + %d][n0 + %d] = np.kron(h[l0 + %d][m0 + %d][n0 + %d], np.identity(2))\n", lcell, mcell, ncell, lcell, mcell, ncell);
                    fprintf(fpk,"h[l0 + %d][m0 + %d][n0 + %d] = np.kron(h[l0 + %d][m0 + %d][n0 + %d], np.identity(2))\n", -lcell, -mcell, -ncell, -lcell, -mcell, -ncell);
                }
                else
                    fprintf(fpk,"h[l0 + %d][m0 + %d][n0 + %d] = np.kron(h[l0 + %d][m0 + %d][n0 + %d], np.identity(2))\n", lcell, mcell, ncell, lcell, mcell, ncell);
            }
            
            if (isS)
            {
                fprintf(fpk,"\n#Evaluate S*I_{2x2}\n");
                for (int iCell=0; iCell<nCell; iCell++)
                {
                    wxString WorkingCell = listctr->GetString(iCell);
                    int lcell,mcell,ncell;
                    sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
                    if (!(lcell==0 && mcell==0 && ncell == 0))
                    {
                        fprintf(fpk,"s[l0 + %d][m0 + %d][n0 + %d] = np.kron(s[l0 + %d][m0 + %d][n0 + %d], np.identity(2))\n", lcell, mcell, ncell, lcell, mcell, ncell);
                        fprintf(fpk,"s[l0 + %d][m0 + %d][n0 + %d] = np.kron(s[l0 + %d][m0 + %d][n0 + %d], np.identity(2))\n", -lcell, -mcell, -ncell, -lcell, -mcell, -ncell);
                    }
                    else
                        fprintf(fpk,"s[l0 + %d][m0 + %d][n0 + %d] = np.kron(s[l0 + %d][m0 + %d][n0 + %d], np.identity(2))\n", lcell, mcell, ncell, lcell, mcell, ncell);
                }
            }
            
            fprintf(fpk,"\n#Add SOC to the total Hamiltonian: HTot = H*I_{2x2} + Hsoc\n");
            fprintf(fpk,"h[l0 + %d][m0 + %d][n0 + %d] = h[l0 + %d][m0 + %d][n0 + %d] + Hsoc\n", 0, 0, 0, 0, 0, 0);
        }
        
        fprintf(fpk,"\n#Load k-points from the file\n");
        fprintf(fpk,"kPath = np.loadtxt(\'./%s_kPath.dat\', usecols=range(4))\n", BaseName.c_str().AsChar());
        
        double a[3],b[3],c[3];
        sec30->GetVar(_("a[0]"), a[0]);
        sec30->GetVar(_("a[1]"), a[1]);
        sec30->GetVar(_("a[2]"), a[2]);
        sec30->GetVar(_("b[0]"), b[0]);
        sec30->GetVar(_("b[1]"), b[1]);
        sec30->GetVar(_("b[2]"), b[2]);
        sec30->GetVar(_("c[0]"), c[0]);
        sec30->GetVar(_("c[1]"), c[1]);
        sec30->GetVar(_("c[2]"), c[2]);
        
        fprintf(fpk,"\n#Set the unitcell vectors\n");
        fprintf(fpk,"a = np.array([%.8f, %.8f, %.8f])\n", a[0], a[1], a[2]);
        fprintf(fpk,"b = np.array([%.8f, %.8f, %.8f])\n", b[0], b[1], b[2]);
        fprintf(fpk,"c = np.array([%.8f, %.8f, %.8f])\n", c[0], c[1], c[2]);
        
        fprintf(fpk,"\n#Calculate the reciprocal space vectors\n");
        fprintf(fpk,"vol = np.dot(a, np.cross(b, c))\n");
        fprintf(fpk,"astar = 2*pi*np.cross(b, c)/vol\n");
        fprintf(fpk,"bstar = 2*pi*np.cross(c, a)/vol\n");
        fprintf(fpk,"cstar = 2*pi*np.cross(a, b)/vol\n");
        
        fprintf(fpk,"\n#Band-Structure Calculation\n");
        fprintf(fpk,"print('The number of bands is ' + str(nH))\n");
        fprintf(fpk,"nbands = nH\n");
        fprintf(fpk,"X = [0.0 for j in range(nk)]\n");
        fprintf(fpk,"bands = [[0.0 for j in range(nk)] for i in range(nbands)]\n");
        fprintf(fpk,"dpath = 0.0\n");
        
        fprintf(fpk,"for ik in range(nk):\n");
        fprintf(fpk,"   ka = kPath[ik][0]\n");
        fprintf(fpk,"   kb = kPath[ik][1]\n");
        fprintf(fpk,"   kc = kPath[ik][2]\n");
        fprintf(fpk,"   dpath = kPath[ik][3]\n");
        fprintf(fpk,"   hk = Getk(h, ka, kb, kc)\n");
        if (isS) fprintf(fpk,"   sk = Getk(s, ka, kb, kc)\n");
        if (isS)
            fprintf(fpk,"   EIG, VEC = LA.eig(hk, sk)\n");
        else
            fprintf(fpk,"   EIG, VEC = LA.eig(hk)\n");
        fprintf(fpk,"   EIG = np.real(EIG)	#The imaginary part is practically zero.\n");
        fprintf(fpk,"   EIG = np.sort(EIG)\n");
        fprintf(fpk,"   for iband in range(nbands):\n");
        fprintf(fpk,"      X[ik] = dpath\n");
        fprintf(fpk,"      bands[iband][ik] = EIG[iband]\n\n");
        
        fprintf(fpk,"dmax = dpath\n");
        
        fprintf(fpk,"\n#Plot the band-structure\n");
        fprintf(fpk,"for i in range(nbands):\n");
        fprintf(fpk,"   plt.plot(X, bands[i][:], 'r-')\n\n");
        fprintf(fpk,"for i in range(nlabels):\n");
        fprintf(fpk,"   plt.axvline(x=xlabels[i])\n\n");
        fprintf(fpk,"plt.xlim(0.0, dmax)\n");
        fprintf(fpk,"plt.xticks(xlabels, labels)\n");
        fprintf(fpk,"plt.show()\n");
        fclose(fpk);
    }
}

void MainFrame::GeneratePyBindingInput(wxString filepath, wxString BaseName, int MyID_Initial0Final1)
{
    sec30->isMainThread = true;
    int ID = MyID_Initial0Final1;
    int Hind = 0;
    int Sind = 2;
    int SOCind = 4;
    if (ID == 1)
    {
        Hind = 1;
        Sind = 3;
        SOCind = 5;
    }
    
    int nEss = sec30->ArraysOf3DDouble[Hind].size();
    if (nEss < 1) return;
    
    int nH = sec30->ArraysOf3DDouble[Hind][0].size();
    if (nH < 1) return;
    
    bool isS = false;
    int nEssS = sec30->ArraysOf3DDouble[Sind].size();
    if (nEssS > 0) isS = true;
    
    bool isSOC = false;
    int nSOCBuf = sec30->ArraysOf3DDouble[SOCind].size();
    if (nSOCBuf > 1) isSOC = true;
    
    int nk = sec30->ArraysOf2DDouble[0].size();//double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    int nklabel = sec30->ArraysOf1DDouble[0].size();//double* dkLabel;
    
    FILE *fpk;
    wxString fname = filepath + wxFileName::GetPathSeparator() + BaseName + wxT(".py");
    if ((fpk = fopen(fname,"w")) != NULL)
    {
        fprintf(fpk,"#Import libraries\n");
        fprintf(fpk,"import pybinding as pb\n");
		fprintf(fpk,"import matplotlib.pyplot as plt\n");
        fprintf(fpk,"import numpy as np\n");
		fprintf(fpk,"from math import pi\n");
		
        int TBl,TBm,TBn;
        sec30->GetVar(_("TBl[0]"), TBl);
        sec30->GetVar(_("TBm[0]"), TBm);
        sec30->GetVar(_("TBn[0]"), TBn);
		
		double a[3],b[3],c[3];
        sec30->GetVar(_("a[0]"), a[0]);
        sec30->GetVar(_("a[1]"), a[1]);
        sec30->GetVar(_("a[2]"), a[2]);
        sec30->GetVar(_("b[0]"), b[0]);
        sec30->GetVar(_("b[1]"), b[1]);
        sec30->GetVar(_("b[2]"), b[2]);
        sec30->GetVar(_("c[0]"), c[0]);
        sec30->GetVar(_("c[1]"), c[1]);
        sec30->GetVar(_("c[2]"), c[2]);
		
		int nUnitcellAtoms = 0;
		sec30->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
		bool isSOC;
		sec30->GetCheckVar(_("SOC[0]"), isSOC);
		bool isOverlap;
		sec30->GetCheckVar(_("Overlap[0]"), isOverlap);
		wxCheckTree* orbs = sec30->GetTreeObject(_("Orbitals"));
		Astring0D HamiltonianMap = sec30->ArraysOf1DString[1];
		int nHamiltonian = HamiltonianMap.size();
		Aint1D HamiltonianDimMap = sec30->ArraysOf2DInt[0];
		Aint0D HamiltonianDimMapItem; //The index of the shell in Hamiltonian
		wxTreeItemId orbsrootID = orbs->GetRootItem();
		
		int kind[nUnitcellAtoms];
		double XArray[nUnitcellAtoms];
		double YArray[nUnitcellAtoms];
		double ZArray[nUnitcellAtoms];
		
		for (int i0=0; i0<nUnitcellAtoms; i0++)
		{
			//double fraca, fracb, fracc;
			sec30->GetVar(_("KABC_Coords"), i0, 0, kind[i0]);
			//sec30->GetVar(_("KABC_Coords"), i0, 1, fraca);
			//sec30->GetVar(_("KABC_Coords"), i0, 2, fracb);
			//sec30->GetVar(_("KABC_Coords"), i0, 3, fracc);
			sec30->GetVar(_("XYZ_Coords"), i0, 0, XArray[i0]);
			sec30->GetVar(_("XYZ_Coords"), i0, 1, YArray[i0]);
			sec30->GetVar(_("XYZ_Coords"), i0, 2, ZArray[i0]);
		}
		
		Astring0D onsitesCodelines = Astring0D();
		
		int iH0=0;
		for (int iAtomIndex=0; iAtomIndex<nUnitcellAtoms; iAtomIndex++)
		{
			int Dim1 = -1;
			bool IsShell1;
			wxString Orbs1;
			
			wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
			wxComboBox* comb1 = sec30->GetComboObject(atom1);
			wxString TBAtom1 = comb1->GetStringSelection();
			
			wxTreeItemId AtomID = orbs->ActiveAndContainsItemIn(orbsrootID ,TBAtom1);
			int nShell = orbs->GetChildrenCount(AtomID,false);
			
			for (int iShell=1; iShell<=nShell; iShell++)
			{
				wxString ShellName = wxString::Format(wxT("Shell %d"),iShell);
				wxTreeItemId shellID = orbs->FindItemIn(AtomID,ShellName);
				
				if (shellID.IsOk() && orbs->GetItemState(shellID) >= wxCheckTree::CHECKED)
				{
					sec30->GetOrbitalInfo(orbs, TBAtom1, iShell, Orbs1, Dim1, IsShell1);
					wxString Label = TBAtom1  + _(" (") + ShellName + _(")");

					Orbs1.Replace(_(" "),_(""));
					Orbs1.Replace(_("("),_(""));
					Orbs1.Replace(_(")"),_(""));
					wxStringTokenizer tokenizer1(Orbs1, ",");
					while (tokenizer1.HasMoreTokens())
					{
						wxString o1 = tokenizer1.GetNextToken();
						wxString orbitallabel = wxString::Format(wxT("o%d:"),iH0+1) + sec30->GetAtomLable(kind[iAtomIndex]) + wxString::Format(wxT(":%d:"),iShell) + o1;
						onsitesCodelines.push_back(wxString::Format(wxT("        (\'%s\', [%.8f, %.8f, %.8f], onsite_energy[%d])"), orbitallabel, XArray[iAtomIndex], YArray[iAtomIndex], ZArray[iAtomIndex], iH0));
						iH0++;
					}
				}
			}
		}
		
		wxListBox* listctr = sec30->GetListObject(_("EssentialUnitcellList"));
		
		Adouble0D onsitesList = Adouble0D();
		Astring0D hoppingCodelines = Astring0D();
		int nCell = listctr->GetCount();
		for (int iCell=0; iCell<nCell; iCell++)
		{
			bool isMainCell = false;
			wxString WorkingCell = listctr->GetString(iCell);
			if (WorkingCell == _("(0,0,0)"))
			{
				hoppingCodelines.push_back(wxString::Format(wxT("\n        #inside the main cell")));
				isMainCell = true;
			}
			else
				hoppingCodelines.push_back(wxString::Format(wxT("\n        #between main cell and the cell %s"), WorkingCell));
			
			int lcell,mcell,ncell;
			sec30->GetCellInfo(WorkingCell, lcell, mcell, ncell);
			for (int iH=0; iH<nH; iH++)
			{
				for (int jH=0; jH<nH; jH++)
				{
					double t = sec30->ArraysOf3DDouble[Hind][iCell][iH][jH];
                    if (isMainCell && iH==jH)
                    {
                        onsitesList.push_back(t);
                    }
					else if (isMainCell && iH > jH)
					{
						//ignore
					}
                    else
                    {
                        if (fabs(t) > 0.00001)
                        {
							Astring0D HamiltonianMap = sec30->ArraysOf1DString[1];
							wxString path1 = HamiltonianMap[iH];
							wxString path2 = HamiltonianMap[jH];
							path1.Replace(_("TB-Model Atom Species/"),_(""));
							path1.Replace(_("Shell "),_(""));
							path2.Replace(_("TB-Model Atom Species/"),_(""));
							path2.Replace(_("Shell "),_(""));
							wxStringTokenizer tokenizer1(path1, "/");
							wxStringTokenizer tokenizer2(path2, "/");
							wxString TBatom1 = tokenizer1.GetNextToken();
							wxString TBatom2 = tokenizer2.GetNextToken();
							wxString shell1 = tokenizer1.GetNextToken();
							wxString shell2 = tokenizer2.GetNextToken();
							wxString orbital1 = tokenizer1.GetNextToken();
							wxString orbital2 = tokenizer2.GetNextToken();
							int iAtomIndex = sec30->GetAtomIndexFromHamiltonianIndex(HamiltonianDimMap, iH);
							int jAtomIndex = sec30->GetAtomIndexFromHamiltonianIndex(HamiltonianDimMap, jH);
							wxString orbitallabel1 = wxString::Format(wxT("o%d:"),iH+1) + sec30->GetAtomLable(kind[iAtomIndex]) + wxT(":") + shell1 + wxT(":") + orbital1;
							wxString orbitallabel2 = wxString::Format(wxT("o%d:"),jH+1) + sec30->GetAtomLable(kind[jAtomIndex]) + wxT(":") + shell2 + wxT(":") + orbital2;
							hoppingCodelines.push_back(wxString::Format(wxT("        ([%d, %d, %d], \'%s\', \'%s\', %.8f)"), lcell, mcell, ncell, orbitallabel1, orbitallabel2, t));
						}
					}
				}
			}
		}
		
		fprintf(fpk,"\n# create a lattice in format of pyBinding\n");
		fprintf(fpk,"def GetLattice(");
		
		int nhlines1 = onsitesList.size();
		fprintf(fpk,"onsite_energy=[");
		for (int il=0; il<nhlines1; il++)
		{
			wxString mycode = onsitesCodelines[il];
			if (il != nhlines1 - 1)
				fprintf(fpk,"%.8f,", onsitesList[il]);
			else
				fprintf(fpk,"%.8f", onsitesList[il]);
		}
		fprintf(fpk,"]");
		
		fprintf(fpk,"):\n");
		fprintf(fpk,"    lat = pb.Lattice(\n");
		fprintf(fpk,"        a1 = [%.8f, %.8f, %.8f],\n" , a[0], a[1], a[2]);
		fprintf(fpk,"        a2 = [%.8f, %.8f, %.8f],\n" , b[0], b[1], b[2]);
		fprintf(fpk,"        a3 = [%.8f, %.8f, %.8f]\n"  , c[0], c[1], c[2]);
		fprintf(fpk,"    )\n");

		fprintf(fpk,"\n");
		fprintf(fpk,"    lat.add_sublattices(\n");
		fprintf(fpk,"        #name and positions\n");
		for (int il=0; il<nhlines1; il++)
		{
			wxString mycode = onsitesCodelines[il];
			if (il != nhlines1 - 1)
				fprintf(fpk,"%s,\n", mycode.c_str().AsChar());
			else
				fprintf(fpk,"%s\n", mycode.c_str().AsChar());
		}
		fprintf(fpk,"    )\n");
		fprintf(fpk,"\n");
		
		int nhlines2 = hoppingCodelines.size();
		fprintf(fpk,"    lat.add_hoppings(\n");
		for (int il=0; il<nhlines2; il++)
		{
			wxString mycode = hoppingCodelines[il];
			if (mycode.Contains(_("#")))
				fprintf(fpk,"%s\n", mycode.c_str().AsChar());
			else
			{
				if (il != nhlines2 - 1)
					fprintf(fpk,"%s,\n", mycode.c_str().AsChar());
				else
					fprintf(fpk,"%s\n", mycode.c_str().AsChar());
			}
		}
		fprintf(fpk,"    )\n");
		fprintf(fpk,"\n");
        fprintf(fpk,"    return lat\n");
		
		
		fprintf(fpk,"\n");
		fprintf(fpk,"def make_k_path(k1, k2, step=0.01, **kwargs):\n");
		fprintf(fpk,"    #either choose num_steps or step\n");
		fprintf(fpk,"    num_steps = 1\n");
		fprintf(fpk,"    if 'num_steps' in kwargs:\n");
		fprintf(fpk,"        num_steps = kwargs['num_steps']\n");
		fprintf(fpk,"    else:\n");
		fprintf(fpk,"        num_steps = int(np.linalg.norm(k2 - k1) // step)\n");
		fprintf(fpk,"\n");
		fprintf(fpk,"    #k_path.shape == num_steps, k_space_dimensions\n");
		fprintf(fpk,"    k_path = np.array([np.linspace(s, e, num_steps, endpoint=False)\n");
		fprintf(fpk,"                       for s, e in zip(k1, k2)]).T\n");
		fprintf(fpk,"    return k_path\n");
		fprintf(fpk,"\n\n");
		fprintf(fpk,"#setup lattice with on-site potential terms\n");
		fprintf(fpk,"lat = GetLattice()\n");
		fprintf(fpk,"plt.figure()\n");
		fprintf(fpk,"plt.subplot(121)\n");
		fprintf(fpk,"plt.title('Lattice: xy')\n");
		fprintf(fpk,"lat.plot()\n");
		fprintf(fpk,"\n");
		fprintf(fpk,"plt.subplot(122)\n");
		fprintf(fpk,"plt.title('Lattice: yz')\n");
		fprintf(fpk,"lat.plot(axes='yz')\n");
		fprintf(fpk,"plt.show()\n");
		fprintf(fpk,"\n");
		fprintf(fpk,"#create a periodic model, which generates the Hamiltonian from the lattice\n");
		fprintf(fpk,"model = pb.Model(lat, pb.translational_symmetry())\n");
		fprintf(fpk,"\n");
		fprintf(fpk,"#take corners of the BZ\n");
		fprintf(fpk,"b1, b2, b3 = model.lattice.reciprocal_vectors()\n");
		fprintf(fpk,"#Example of significant points (here, user should define the path as a function of b1, b2 and b3)\n");
		fprintf(fpk,"P1 = b1[0:2] / 2.0\n");
		fprintf(fpk,"Gamma = np.array([0, 0])\n");
		fprintf(fpk,"P2 = b2[0:2] / 2.0\n");
		fprintf(fpk,"\n");
		fprintf(fpk,"#make a path between each of the two points\n");
		fprintf(fpk,"kp1 = make_k_path(P1, Gamma, num_steps=50)\n");
		fprintf(fpk,"kp2 = make_k_path(Gamma, P2, num_steps=50)\n");
		fprintf(fpk,"kp3 = make_k_path(P2, P1, num_steps=50)\n");
		fprintf(fpk,"\n");
		fprintf(fpk,"#define indexes\n");
		fprintf(fpk,"point_indices = [0, kp1.shape[0] - 1, kp1.shape[0] + kp2.shape[0] - 1, kp1.shape[0] + kp2.shape[0] + kp3.shape[0] - 1]\n");
		fprintf(fpk,"full_kpath = pb.results.Path(np.vstack((kp1, kp2, kp3)), point_indices=point_indices)\n");
		fprintf(fpk,"\n");
		fprintf(fpk,"bands_list = []\n");
		fprintf(fpk,"for k in full_kpath:\n");
		fprintf(fpk,"    model.set_wave_vector(k)\n");
		fprintf(fpk,"    solver = pb.solver.lapack(model)\n");
		fprintf(fpk,"    bands_list.append(solver.eigenvalues)\n");
		fprintf(fpk,"\n");
		fprintf(fpk,"bands = pb.results.Bands(full_kpath, np.vstack(bands_list))\n");
		fprintf(fpk,"bands.plot(point_labels=['P1', r'$\Gamma$',  'P2', 'P1'])\n");
		fprintf(fpk,"plt.show()\n");
		fprintf(fpk,"\n");
		
        fclose(fpk);
		wxMessageBox(wxT("Done!"));
    }
}

void MainFrame::MakeACopyOfSKList()
{
	if (sec30->WorkingDIR == wxEmptyString) {wxMessageBox(wxT("Error: Your project has not yet been saved. First, save your TB model in a separate folder.")); return;}
	wxString filename;
	sec30->GetVar(_("SKName[0]"),filename);
	if (filename == _("")) {wxMessageBox(_("File name is empty. Please fill out this field and try again."),_("Error")); return;}
	
	wxString filepath = sec30->WorkingDIR + wxFileName::GetPathSeparator() + filename + wxT(".sktab");
	if (wxFileExists(filepath)) {wxMessageBox(_("There is a tab with this name. Please choose another name."),_("Error")); return;}
	
	int numberOfRows = ExportSKToFile(filepath);
	
	CreateATabFromFile(filepath, filename, numberOfRows);
}

myGrid* MainFrame::CreateGrid(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColNames, wxString* ColTypes, int* ColSizes, int* ColPrecision, int xCtrlSize, int yCtrlSize, bool EnableEvent)
{
    //wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    //parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    myGrid* gc=new myGrid(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(xCtrlSize,yCtrlSize)),wxFULL_REPAINT_ON_RESIZE|wxHSCROLL|wxVSCROLL);
    //MySizer->Add(gc, 0, wxRIGHT, WXC_FROM_DIP(5));
    gc->EnableEditing(true);
    gc->SetMinSize(wxSize(xCtrlSize,yCtrlSize));
    
    gc->SetName(VariableName);
    
    //gc->SetDefaultCellAlignment(wxALIGN_LEFT,wxALIGN_CENTRE); //Does not work
    
    gc->CreateGrid( nRow, nCol);
	
    for (int i=0; i< nCol; i++)
    {
        gc->SetColLabelValue(i,ColNames[i]);
        gc->SetColSize(i, ColSizes[i] );// in pixels
        gc->DisableColResize(i);
        if (ColTypes[i]=="int")
            gc->SetColFormatNumber(i);
        else if (ColTypes[i]=="double")
            gc->SetColFormatFloat(i,-1,ColPrecision[i]);
            
        for (int j=0; j< nRow; j++)
		{
            gc->SetCellAlignment(j, i, wxALIGN_LEFT,wxALIGN_CENTRE);
			//gc->SetReadOnly(j,i,true);
		}
    }
    
    for (int i=0; i< nRow; i++) gc->DisableRowResize(i);
    
    wxColour c; //Also it is possible to determine the color in this way: wxColour c=*wxGREEN;
    c.Set(191,205,219,255);
    gc->SetLabelBackgroundColour(c);
    gc->SetColLabelSize(20);
    gc->SetRowLabelSize(35);
    gc->SetColMinimalAcceptableWidth(1);
    
    //MySizer->Layout();
    parent->Layout();
	return gc;
}

int MainFrame::ExportSKToFile(wxString filepath)
{
    FILE *fpk;
    if ((fpk = fopen(filepath,"w")) != NULL)
    {
		fprintf(fpk,"On-Site\n");
		myGrid* osgc = sec30->GetGridObject(_("OS"));
		int nRowsOS = osgc->GetNumberRows();
		for (int i=0; i<nRowsOS; i++)
		{
			double d1 = 0.0;
			double d2 = 0.0;
			wxString var = osgc->GetCellValue(i, 0);
			wxString val1 = osgc->GetCellValue(i, 1);
			wxString val2 = osgc->GetCellValue(i, 2);
			bool output1 = val1.ToDouble(&d1);
			bool output2 = val2.ToDouble(&d2);
			if (!output1) d1 = 0.0;
			if (!output2) d2 = 0.0;
			if ( var == _(""))
				fprintf(fpk,"\n");
			else if (var.Contains(wxT("Shell")))
				fprintf(fpk,"%s\n", var.c_str().AsChar());
			else
				fprintf(fpk,"%s\t%.8f\t%.8f\n", var.c_str().AsChar(), d1, d2);
		}
		
		fprintf(fpk,"Hamiltonian\n");
		
		myGrid* skgc = sec30->GetGridObject(_("SK"));
		int nRowsSK = skgc->GetNumberRows();
		for (int i=0; i<nRowsSK; i++)
		{
			double d1 = 0.0;
			double d2 = 0.0;
			wxString var = skgc->GetCellValue(i, 0);
			wxString val1 = skgc->GetCellValue(i, 1);
			wxString val2 = skgc->GetCellValue(i, 2);
			bool output1 = val1.ToDouble(&d1);
			bool output2 = val2.ToDouble(&d2);
			if (!output1) d1 = 0.0;
			if (!output2) d2 = 0.0;
			if ( var == _(""))
				fprintf(fpk,"\n");
			else if (var.Contains(wxT("Bond")))
				fprintf(fpk,"%s\n", var.c_str().AsChar());
			else
				fprintf(fpk,"%s\t%.8f\t%.8f\n", var.c_str().AsChar(), d1, d2);
		}
		
		fprintf(fpk,"Overlap\n");
		
		myGrid* olgc = sec30->GetGridObject(_("OL"));
		int nRowsOL = olgc->GetNumberRows();
		for (int i=0; i<nRowsOL; i++)
		{
			double d1 = 0.0;
			double d2 = 0.0;
			wxString var = olgc->GetCellValue(i, 0);
			wxString val1 = olgc->GetCellValue(i, 1);
			wxString val2 = olgc->GetCellValue(i, 2);
			bool output1 = val1.ToDouble(&d1);
			bool output2 = val2.ToDouble(&d2);
			if (!output1) d1 = 0.0;
			if (!output2) d2 = 0.0;
			if ( var == _(""))
				fprintf(fpk,"\n");
			else if (var.Contains(wxT("Bond")))
				fprintf(fpk,"%s\n", var.c_str().AsChar());
			else
				fprintf(fpk,"%s\t%.8f\t%.8f\n", var.c_str().AsChar(), d1, d2);
		}
		
        fclose(fpk);
		
		return nRowsOS + nRowsSK + nRowsOL;
    }
	return 0;
}

void MainFrame::CreateATabFromFile(wxString filepath, wxString tabname, int nLines)
{
	wxString ColNames[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
	wxString ColTypes[3] = { _("string"), _("double"), _("double")};
	int ColSizes[3] = {130, 100, 100};
	int ColPrecision[3] = { 0, 8, 8};
	
	myGrid* gc = CreateGrid(SKtables, nLines + 3, 3, _(""), ColNames, ColTypes, ColSizes, ColPrecision, -1, -1, false);

	LoadSKFileToTable(filepath, gc);
	
	SKtables->AddPage(gc,tabname);
	SKtables->Update();
	SKtables->Refresh(true);
	
	wxString firstone = SKtables->GetPageText(0);
	if (firstone == _("")) SKtables->DeletePage(0);
}

void MainFrame::LoadSKFileToTable(wxString filepath, myGrid* grid)
{
	grid->ClearGrid();
	std::ifstream infile(filepath.ToStdString());
	std::string l;
	int iRow = -1;
	while (std::getline(infile, l))
	{
		iRow++;
		wxString line = wxString(l);
		if ( line.Contains(wxT("On-Site")) ||
			 line.Contains(wxT("Hamiltonian")) ||
			 line.Contains(wxT("Overlap")) ||
			 line.Contains(wxT("Shell")) ||
			 line.Contains(wxT("Bond")))
		{
			grid->SetCellValue(iRow, 0, line);
		}
		else
		{
			std::istringstream iss(l);
			std::string sk = "";
			std::string iniVal = "";
			std::string finVal = "";
			iss >> sk >> iniVal >> finVal;
			grid->SetCellValue(iRow, 0, sk);
			grid->SetCellValue(iRow, 1, iniVal);
			grid->SetCellValue(iRow, 2, finVal);
		}
	}
}

int MainFrame::GetTheNumberOfLines(wxString filepath)
{
	std::ifstream infile(filepath.ToStdString());
	std::string l;
	int iRow = 0;
	while (std::getline(infile, l))
	{
		iRow++;
	}
	
	return iRow;
}

void MainFrame::LoadSKTables()
{
	wxDir dir(sec30->WorkingDIR);
	if ( !dir.IsOpened() )
	{
		// deal with the error here - wxDir would already log an error message
		// explaining the exact reason of the failure
		wxMessageBox(wxT("Unable to open the containing folder to load SK list."));
		return;
	}
	
	//puts("Enumerating object files in current directory:");
	wxString filename;
	bool cont = dir.GetFirst(&filename);
	while ( cont )
	{
		wxString filepath = sec30->WorkingDIR + wxFileName::GetPathSeparator() + filename;
		if (filename.AfterLast('.') == _("sktab"))
		{
			int nlines = GetTheNumberOfLines(filepath);
			CreateATabFromFile(filepath, filename.BeforeLast('.'), nlines);
		}
		cont = dir.GetNext(&filename);
	}
}

void MainFrame::SKtables_pageClose(wxAuiNotebookEvent& event)
{
	int ind = SKtables->GetSelection();
	wxString fname = SKtables->GetPageText(ind);
	wxString filepath = sec30->WorkingDIR + wxFileName::GetPathSeparator() + fname + wxT(".sktab");
	if (wxFileExists(filepath))
	{
		wxRemoveFile(filepath);
	}
}

void MainFrame::SKtables_pageClosed(wxAuiNotebookEvent& event)
{
	if (SKtables->GetPageCount() == 0)
	{
		wxString ColNames[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
		wxString ColTypes[3] = { _("string"), _("double"), _("double")};
		int ColSizes[3] = {130, 100, 100};
		int ColPrecision[3] = { 0, 8, 8};
		
		myGrid* gc = CreateGrid(SKtables, 0, 3, _(""), ColNames, ColTypes, ColSizes, ColPrecision, -1, -1, false);

		SKtables->AddPage(gc,_(""));
		SKtables->Update();
		SKtables->Refresh(true);
	}
}

void MainFrame::MainFrameClose(wxCloseEvent& event)
{
    this->Destroy();
    wxGetApp().ExitMainLoop();
}
