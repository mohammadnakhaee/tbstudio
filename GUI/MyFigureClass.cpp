#include "MyFigureClass.h"
#include "main.h"
DECLARE_APP(MainApp)

//#ifndef wxHAS_IMAGES_IN_RESOURCES
//    #include "../../sample.xpm"
//#endif


wxBEGIN_EVENT_TABLE(MyFigure2d, wxPanel)
    EVT_PAINT(MyFigure2d::OnPaint)
    EVT_KEY_DOWN(MyFigure2d::OnKeyDown)
    EVT_MOUSEWHEEL(MyFigure2d::OnMouseWheel)
    EVT_LEFT_DOWN(MyFigure2d::OnMouseLeftDown)
    EVT_LEFT_UP(MyFigure2d::OnMouseLeftUp)
    EVT_MOTION(MyFigure2d::OnMouseMove)
    EVT_RIGHT_DOWN(MyFigure2d::OnMouseRightDown)
    EVT_RIGHT_UP(MyFigure2d::OnMouseRightUp)
    EVT_MIDDLE_DOWN(MyFigure2d::OnMouseMiddleDown)
    EVT_MIDDLE_UP(MyFigure2d::OnMouseMiddleUp)
    EVT_MENU(wxID_COPY,MyFigure2d::OnSaveRasterImage)
wxEND_EVENT_TABLE()

MyFigure2d::MyFigure2d(wxWindow *parent, Sec30* sec30Var, int MyID) : wxPanel(parent)
{
    ObjectID = MyID;
    sec30 = sec30Var;
}

void MyFigure2d::OnPaint(wxPaintEvent& WXUNUSED(event))
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
    
    int w,h;
    w=ClientSize.x;
    h=ClientSize.y;
    float max = (float)w;
    if (h>w) max = (float)h;
    float w3d=w/max;
    float h3d=h/max;
        
	//Plot using MathGL Library
	mglGraph gr;
	
	int ploterr = PlotBand(&gr, w, h, sec30, ObjectID);
	//int ploterr = 0;
	//sample(&gr, w, h);
	
	//bool CanIt = dc.CanDrawBitmap();
	
	//Convert to image and then to Bitmap
	if (ploterr==0)
	{
		wxImage img(w,h,(unsigned char *)gr.GetRGB(),true);
		//wxBitmap bmp(img);
		dc.DrawBitmap(img,0,0,false);
	}
	else
	{
		sample(&gr, w, h, ObjectID);
		wxImage img(w,h,(unsigned char *)gr.GetRGB(),true);
		//wxImage img(w,h,true);
		//wxRect rect(0,0,w,h);
		//img.SetRGB(rect,255,20,25);
		//wxBitmap bmp(img);
		dc.DrawBitmap(img,0,0,false);
	}
	
	/*
	if (canvasRefreshCnt<3)
	{
		canvasRefreshCnt++;
		this->Refresh(false);
	}
	else
	{
		canvasRefreshCnt=0;
	}
		*/
		
	//this->GetContext();
	
	//Print to dc
	//wxBitmap bmp2(wxT("C:\\GCloth.png"), wxBITMAP_TYPE_PNG);
	//dc.DrawBitmap(bmp2,0,0,false);
	//dc.DrawBitmap(bmp,0,0,false);
}

void MyFigure2d::GetDirection(int i0, int j0, int i, int j, float& x, float& y, float& Theta)
{
    x = -(float)(i - i0);
    y = (float)(j - j0);
    Theta = (float)sqrt(x*x + y*y);
}

void MyFigure2d::OnKeyDown(wxKeyEvent& event)
{
    float angle = 5.0;

    switch ( event.GetKeyCode() )
    {
        case WXK_RIGHT:
            //Spin( 0.0, -angle , 0.0);
            break;

        case WXK_LEFT:
            //Spin( 0.0, angle  , 0.0);
            break;

        case WXK_DOWN:
            //Spin( -angle, 0.0  , 0.0);
            break;

        case WXK_UP:
            //Spin( angle, 0.0  , 0.0);
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

void MyFigure2d::OnMouseWheel(wxMouseEvent& event)
{
    bool scrldwn = event.GetWheelRotation() < 0;
    //float delta = 0.01*0.01f*event.GetWheelDelta(); //Constant delta
	bool isBandLoaded = false;
	if (sec30->ArraysOf0DInt[0] != 0)
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

    Refresh(false);
}

void MyFigure2d::OnMouseLeftDown(wxMouseEvent& event)
{
    //To get mouse position relative to top-left corner of display, add this in a mouse event handler:
    const wxPoint pt = wxGetMousePosition();
    mouseX0 = pt.x;
    mouseY0 = pt.y;
    isMouseLeftDown = true;
    isMouseRightDown = false;
    isMouseMiddleDown = false;
    const wxPoint cpt = event.GetPosition();
    ClientMouseX0 = cpt.x;
    ClientMouseY0 = cpt.y;
    
    //To get mouse position relative to top-left corner of current window or canvas, add this in a mouse event handler:
    //const wxPoint pt = wxGetMousePosition();
    //int mouseX = pt.x - this->GetScreenPosition().x;
    //int mouseY = pt.y - this->GetScreenPosition().y;
    
    if (sec30->ArraysOf0DInt[6] != 0) PaintMode = true;
}

void MyFigure2d::OnMouseLeftUp(wxMouseEvent& event)
{
    const wxPoint pt = wxGetMousePosition();
    mouseX = pt.x;
    mouseY = pt.y;
    isMouseLeftDown = false;
    if (sec30->ArraysOf0DInt[6] != 0) PaintMode = false;
}

void MyFigure2d::OnMouseMove(wxMouseEvent& event)
{
    SetFocus();
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
		if (sec30->ArraysOf0DInt[6] != 0 && PaintMode)
		{
			const wxSize ClientSize = GetClientSize();
			int w,h;
			w=ClientSize.x;
			h=ClientSize.y;
			
			if (event.CmdDown() || event.AltDown())
				SetWeight(ClientMouseX, ClientMouseY, w, h, -1.0);
			else
				SetWeight(ClientMouseX, ClientMouseY, w, h, 1.0);
		}
            
		isPaintCursur = true;
		Refresh(false);
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
		DoMove2d(l,m);
    }
}

void MyFigure2d::OnMouseRightUp(wxMouseEvent& event)
{
    const wxPoint pt = wxGetMousePosition();
    mouseX = pt.x;
    mouseY = pt.y;
    isMouseRightDown = false;
    if (mouseY==mouseY0 && mouseX==mouseX0)
    {
        wxMenu *pmenuPopUp = new wxMenu;
        wxMenuItem* pItem;
        pItem = new wxMenuItem(pmenuPopUp,wxID_COPY, wxT("Save as image"));
        pmenuPopUp->Append(pItem);
        PopupMenu(pmenuPopUp,event.GetPosition());
        delete pmenuPopUp;
    }
}

void MyFigure2d::OnMouseMiddleDown(wxMouseEvent& event)
{
    const wxPoint pt = wxGetMousePosition();
    mouseX0 = pt.x;
    mouseY0 = pt.y;
    isMouseMiddleDown = true;
    isMouseRightDown = false;
    isMouseLeftDown = false;
        if (ObjectID == 0)
        {
            OldyMin = sec30->ArraysOf0DDouble[1];
            OldyMax = sec30->ArraysOf0DDouble[2];
            OldxMin = sec30->ArraysOf0DDouble[5];
            OldxMax = sec30->ArraysOf0DDouble[6];
        }
        else if (ObjectID == 1)
        {
            OldyMin = sec30->ArraysOf0DDouble[3];
            OldyMax = sec30->ArraysOf0DDouble[4];
            OldxMin = sec30->ArraysOf0DDouble[7];
            OldxMax = sec30->ArraysOf0DDouble[8];
        }
}

void MyFigure2d::OnMouseMiddleUp(wxMouseEvent& event)
{
    isMouseMiddleDown = false;
}

void MyFigure2d::DoMove2d(float l, float m)
{
    const wxSize ClientSize = GetClientSize();
    int w,h;
    w=ClientSize.x;
    h=ClientSize.y;
    double dy = (OldyMax - OldyMin) / h * m;
    double dx = (OldxMax - OldxMin) / w * l;
    if (ObjectID == 0)
    {
        
        sec30->ArraysOf0DDouble[1] = OldyMin + dy;
        sec30->ArraysOf0DDouble[2] = OldyMax + dy;
        //sec30->ArraysOf0DDouble[5] = OldxMin + dx;
        //sec30->ArraysOf0DDouble[6] = OldxMax + dx;
    }
    else if (ObjectID == 1)
    {
        sec30->ArraysOf0DDouble[3] = OldyMin + dy;
        sec30->ArraysOf0DDouble[4] = OldyMax + dy;
        //sec30->ArraysOf0DDouble[7] = OldxMin + dx;
        //sec30->ArraysOf0DDouble[8] = OldxMax + dx;
    }
        
    Refresh(false);
}

void MyFigure2d::OnSaveRasterImage(wxCommandEvent &WXUNUSED(event))
{
    const wxSize ClientSize = GetClientSize();
    
    int width,height;
    width=ClientSize.x;
    height=ClientSize.y;
	
	wxFileDialog* OpenDialog = new wxFileDialog(
	this, _("Generate code"), wxEmptyString, wxEmptyString, 
	_("EPS files (*.eps)|*.eps|SVG files (*.svg)|*.svg|PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg|TGA files (*.tga)|*.tga|TEX files (*.tex)|*.tex")
	,wxFD_SAVE, wxDefaultPosition);
	
	OpenDialog->SetDirectory(sec30->WorkingDIR);
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		int findex = OpenDialog->GetFilterIndex();
		wxString mytype = _("");
		if (findex == 0)
			mytype = _("eps");
		else if (findex == 1)
			mytype = _("svg");
		else if (findex == 2)
			mytype = _("png");
		else if (findex == 3)
			mytype = _("jpg");
		else if (findex == 4)
			mytype = _("tga");
		else if (findex == 5)
			mytype = _("tex");
			
		wxString dgPath = OpenDialog->GetDirectory();
		wxString dgFileName = OpenDialog->GetFilename();
		wxString BaseName = _("");
		if (dgFileName.AfterLast('.') == mytype)
			BaseName = dgFileName.BeforeLast('.');
		else
			BaseName = dgFileName;
		wxString Thefile = dgPath + wxT("/") + BaseName + wxT(".") + mytype;
		
		mglGraph gr;
		int ploterr = PlotBand(&gr, width, height, sec30, ObjectID);
		if (findex == 0)
			gr.WriteEPS(Thefile);
		else if (findex == 1)
			gr.WriteSVG(Thefile);
		else if (findex == 2)
			gr.WritePNG(Thefile);
		else if (findex == 3)
			gr.WriteJPEG(Thefile);
		else if (findex == 4)
			gr.WriteTGA(Thefile);
		else if (findex == 5)
			gr.WriteTEX(Thefile);
	}
        
	OpenDialog->Destroy();
}

void MyFigure2d::SaveImageFromData(wxImage image, wxString filepath, wxString OutputFileType)
{
    if (OutputFileType == _("png"))
        image.SaveFile(filepath, wxBITMAP_TYPE_PNG);
    else if (OutputFileType == _("bmp"))
        image.SaveFile(filepath, wxBITMAP_TYPE_BMP);
    else if (OutputFileType == _("jpg"))
        image.SaveFile(filepath, wxBITMAP_TYPE_JPEG);
}

void MyFigure2d::SetWeight(float x, float y, float w, float h, float coef)
{
    if (sec30->ArraysOf0DInt[0] == 0) return; //if (isBandLoaded = false) rturn;
    int nX = sec30->ArraysOf0DInt[1];
    int DFTnMin = sec30->ArraysOf0DInt[4];
    int DFTnMax = sec30->ArraysOf0DInt[5];
    
    double Xmax = sec30->ArraysOf2DDouble[0][nX-1][6];
    double X = Xmax*x/w;
    
    int iX = 0;
    for(long ix=0; ix<nX; ix++)
    {
        if ( sec30->ArraysOf2DDouble[0][ix][6] >= X)
        {
            iX=ix;
            break;
        }
    }
    
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
    
    double clickedY = y1 + (y2-y1)*(h - y)/h;
    double dy = (y2-y1)/60;
    for(int iband=DFTnMin; iband<=DFTnMax; iband++)
    {
        double y = sec30->ArraysOf2DDouble[1][iX][iband-1] - sec30->ArraysOf0DDouble[0]; //EIG - ChemP
        if(y > clickedY-dy && y < clickedY+dy)
        {
            int ix1 = iX-7;
            int ix2 = iX+7;
            if (ix1 < 0) ix1=0;
            if (ix2 > nX-1) ix2=nX-1;
            for(long ix=ix1; ix<=ix2; ix++)
            {
                sec30->ArraysOf2DDouble[4][ix][iband-1] += coef*0.1;
                if (sec30->ArraysOf2DDouble[4][ix][iband-1] < 0.0) sec30->ArraysOf2DDouble[4][ix][iband-1]=0.0;
                if (sec30->ArraysOf2DDouble[4][ix][iband-1] > 1.0) sec30->ArraysOf2DDouble[4][ix][iband-1]=1.0;
            }
        }
    }
    
    Refresh(true);
}

int MyFigure2d::PlotBand(mglGraph *gr, int w, int h, Sec30* sec30, int MyID)
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
        //sec30->ArraysOf2DDouble[1] = Adouble1D();//double** DFTEigVal;
        //sec30->ArraysOf2DDouble[4] = Adouble1D();//double** DFTEigValWeight;
        
        if (DFTnMax < DFTnMin || DFTnMax<1 || DFTnMin<1 || DFTnMin>maxneig || DFTnMax>maxneig) return 1;
        
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
                    C.a[iCurve*nX + iX] = (mreal)(sec30->ArraysOf2DDouble[4][iX][iCurve + DFTnMin - 1]*2.0-1.0);//Showing fitting weight as a color. The values are between x=[0:1] but the colors are c=[-1,1], so c=2*x-1
                    /*if ( iX > (int)(0.0*nX/9.0) && iX <= (int)(1.0*nX/9.0)) C.a[iCurve*nX + iX] = -1.0;
                    if ( iX > (int)(1.0*nX/9.0) && iX <= (int)(2.0*nX/9.0)) C.a[iCurve*nX + iX] = -0.75;
                    if ( iX > (int)(2.0*nX/9.0) && iX <= (int)(3.0*nX/9.0)) C.a[iCurve*nX + iX] = -0.5;
                    if ( iX > (int)(3.0*nX/9.0) && iX <= (int)(4.0*nX/9.0)) C.a[iCurve*nX + iX] = -0.25;
                    if ( iX > (int)(4.0*nX/9.0) && iX <= (int)(5.0*nX/9.0)) C.a[iCurve*nX + iX] = 0.0;
                    if ( iX > (int)(5.0*nX/9.0) && iX <= (int)(6.0*nX/9.0)) C.a[iCurve*nX + iX] = 0.25;
                    if ( iX > (int)(6.0*nX/9.0) && iX <= (int)(7.0*nX/9.0)) C.a[iCurve*nX + iX] = 0.5;
                    if ( iX > (int)(7.0*nX/9.0) && iX <= (int)(8.0*nX/9.0)) C.a[iCurve*nX + iX] = 0.75;
                    if ( iX > (int)(8.0*nX/9.0) && iX <= (int)(9.0*nX/9.0)) C.a[iCurve*nX + iX] = 1.0;*/
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
        {
            gr->Plot(X, Y, "{x6495ED}-2");      // "b" is colour ??
        }
        
        if (MyID == 0 && !SelectMode)
        {
            int isData = sec30->ArraysOf2DDouble[2].size();
            if (isData != 0)
            {
                int niTBHam = sec30->ArraysOf2DDouble[2][0].size();
                mglData Y2(nX,niTBHam); //Tight-binding size
                for(long iCurve=0; iCurve<niTBHam; iCurve++)
                {
                    for(long iX=0; iX<nX; iX++)
                    {
                        //mreal x = iX/(nX-1.0);
                        Y2.a[iCurve*nX + iX] = (mreal)(sec30->ArraysOf2DDouble[2][iX][iCurve]);//Eigen Value - ChemP
                    }
                }
                gr->Plot(X, Y2, "{x800000}-2");      // maroon
            }
        }
        
        if (MyID == 1 && !SelectMode)
        {
            int isData = sec30->ArraysOf2DDouble[3].size();
            if (isData != 0)
            {
                int nfTBHam = sec30->ArraysOf2DDouble[3][0].size();
                mglData Y2(nX,nfTBHam); //Tight-binding size
                for(long iCurve=0; iCurve<nfTBHam; iCurve++)
                {
                    for(long iX=0; iX<nX; iX++)
                    {
                        //mreal x = iX/(nX-1.0);
                        Y2.a[iCurve*nX + iX] = (mreal)(sec30->ArraysOf2DDouble[3][iX][iCurve]);//Eigen Value - ChemP
                    }
                }
                gr->Plot(X, Y2, "{x800000}-2");      // maroon
            }
        }
        //gr->Plot(X, Y, "{x800000}-2");      // maroon
        
        if (yMax * yMin <= 0) gr->Line(mglPoint(X.a[0],0.0), mglPoint(X.a[nX-1],0.0), "r2=");
        
        for (int ik=1; ik<nk-1; ik++)
        {
            mreal xpos = (mreal)sec30->ArraysOf1DDouble[0][ik];
            gr->Line(mglPoint(xpos, yMin), mglPoint(xpos, yMax), "H2");
        }
        
        gr->SetSize((int)(w),(int)(h),false);
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
    else
        return 1;
}

int MyFigure2d::sample(mglGraph *gr,double w, double h, int ObjectID)
{
    gr->SetSize(w,h,true);
    mglData y(2);
    mglData x(2);
	
	x.a[0]=-10.0;
	y.a[0]=-10.0;
	x.a[1]=-10.0;
	y.a[1]=-10.0;
    /*for (long j = 0; j < x.nx; j++)
    {
        x.a[j] = (5.0*M_PI*(j)/x.nx+it*0.5);
        y.a[j] = sin(5.0*M_PI*(j)/y.nx+it*0.5);
    }*/
    
    gr->NewFrame ();          // start frame
    gr->SubPlot(1,1,0,"<_"); 
    gr->Aspect(1.0,1.0);
    
    if (ObjectID==0)
		gr->Title("Initial Band-Structure","",-1.5);
	else
		gr->Title("Final Band-Structure","",-1.5);
    gr->SetFontSize(4);
    gr->Box();                 //some plotting
    gr->Axis();                //draw axis
    gr->Label('x', "",0);   //x Title
    gr->Label('y', "Energy(k) (eV)",0);   //y Title
    gr->Grid("xy","{xA9A9A9}|");
    
    gr->Plot(x, y, "{x6495ED}-2");      // "b" is colour ??
    
    //gr->Puts(mglPoint(0.7, -0.05), strstream.str().c_str());
    //gr->EndFrame ();          // end frame
    //gr->WriteFrame ();        // save frame
    return 0;
}
