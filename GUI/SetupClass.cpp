#include "SetupClass.h"

SetupClass::SetupClass(wxWindow* parent, Sec30* sec30var, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetName(wxT("SetupClass"));
    SetSize(wxDLG_UNIT(this, wxSize(-1,-1)));
    GetSizer()->Fit(this);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("DFT Band-Structure"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 1, _("DFTPath"), _("string"), _("File DIR"), 60, 270,false,false);
    sec30->SetVar(_("DFTPath[0]"), _(""), false);
    sec30->AddVarVector(this, 1, _("DFTFile"), _("string"), _("File Name"), 60, 270,false,false);
    sec30->SetVar(_("DFTFile[0]"), _(""), false);
    wxComboBox* choicectr = sec30->AddComboCtrl(this, _("BandFileFormat"), _("Format"), 60, 270, false);

    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("DFT Orbital-Weighted Profile"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 1, _("DFTPathU"), _("string"), _("File DIR"), 60, 270,false,false);
    sec30->SetVar(_("DFTPathU[0]"), _(""), false);
    sec30->AddVarVector(this, 1, _("DFTFileU"), _("string"), _("File Name"), 60, 270,false,false);
    sec30->SetVar(_("DFTFileU[0]"), _(""), false);
    wxComboBox* choicectr2 = sec30->AddComboCtrl(this, _("BandFileFormatU"), _("Format"), 60, 270, false);
    choicectr2->Append(_("OpenMX Unfolded Band-Structure"));
    choicectr2->Append(_("Vasp XML Output"));
    choicectr2->SetEditable(false);
    choicectr2->SetBackgroundColour(*wxWHITE);
    choicectr2->Select(-1);
    wxString Labels2[2] = {_("Open File"), _("Reload")};
    wxObjectEventFunction Funcs2[2] = { wxCommandEventHandler(SetupClass::Btn_OpenFileU_OnClick), wxCommandEventHandler(SetupClass::Btn_ReloadU_OnClick)};
    sec30->AddButton(this, 2, Labels2, Funcs2);
    /**********************************************************************************************************************************************/
    wxObjectEventFunction Funcs3[1] = { wxCommandEventHandler(SetupClass::Btn_Select_OnClick)};
    sec30->AddButton(this, 1, Labels3, Funcs3);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_(""),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
}
    
SetupClass::~SetupClass()
{
    //try{}
    //catch(std::exception& ex)
    //{wxMessageBox(ex.what());}
}

void SetupClass::Btn_OpenFile_OnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
                                this, _("Open File"), wxEmptyString, wxEmptyString, 
                                _("OpenMX Band-Structure (*.Band)|*.Band|Vasp XML Output (*.xml)|*.xml"),
                                wxFD_OPEN, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        int dgFileKind = OpenDialog->GetFilterIndex();
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        sec30->SetVar(_("DFTPath[0]"), dgPath, false);
        sec30->SetVar(_("DFTFile[0]"), dgFileName, false);
        wxComboBox* ctr = sec30->GetComboObject(_("BandFileFormat"));
        ctr->Select(dgFileKind);
        //wxString fl = dgPath + wxT("\\") + dgFileName;
	}
 
	OpenDialog->Destroy();
    ReloadBand();
    sec30->SendUpdateEvent(this->GetName());
}

void SetupClass::Btn_Reload_OnClick(wxCommandEvent& event)
{
    ReloadBand();
    sec30->SendUpdateEvent(this->GetName());
}

void SetupClass::ReloadBand()
{
    wxString path,fname;
    sec30->GetVar(_("DFTPath[0]"), path);
    sec30->GetVar(_("DFTFile[0]"), fname);
    wxString file = sec30->CreateFilePath(path,fname);
    
    wxComboBox* ctr =  sec30->GetComboObject(_("BandFileFormat"));
    int FileFormat = ctr->GetSelection();
    if (FileFormat < 0)
    {
        wxMessageBox(_("Please choose the file format."),_("Error"));
        return;
    }
    else if (FileFormat==0)
    {
        int maxneig, mspin, nKPoint;
        double ChemP;
        bool isBandLoaded;
        Adouble1D KPoints;
        Adouble1D EigVal;
        Adouble0D dkLabel;
        Astring0D kLabel;
        LoadOpenMXBand(file, isBandLoaded, maxneig, mspin, ChemP, nKPoint, KPoints, EigVal, dkLabel, kLabel);
        
        if (isBandLoaded)
        {
            sec30->ArraysOf0DInt[0] = 1;
            sec30->ArraysOf0DInt[1] = nKPoint;
            sec30->ArraysOf0DInt[2] = maxneig;
            sec30->ArraysOf0DInt[3] = mspin;
            sec30->ArraysOf0DInt[6] = 0;
            sec30->ArraysOf0DDouble[0] = ChemP;
            sec30->ArraysOf1DDouble[0] = dkLabel;
            sec30->ArraysOf1DString[0] = kLabel;
            sec30->ArraysOf2DDouble[0] = KPoints;
            sec30->ArraysOf2DDouble[1] = EigVal;
    
            bool isMinOK, isMaxOK;
            IsRangeOK(maxneig, isMinOK, isMaxOK);
            if (!isMinOK)
            {
                sec30->SetVar(_("DFTBandRange[0]"), 1, false);
                sec30->ArraysOf0DInt[4] = 1;//int DFTnBandMin;
            }
            if (!isMaxOK)
            {
                sec30->SetVar(_("DFTBandRange[1]"), maxneig, false);
                sec30->ArraysOf0DInt[5] = maxneig;//int DFTnBandMax;
            }
            
            if (sec30->ArraysOf0DDouble[1] == sec30->ArraysOf0DDouble[2])
            {
                sec30->ArraysOf0DDouble[1] = -5;
                sec30->ArraysOf0DDouble[2] = 5;
                sec30->ArraysOf0DDouble[3] = -5;
                sec30->ArraysOf0DDouble[4] = 5;
            }
            
            int nkPoints = sec30->ArraysOf1DDouble[0].size();
            sec30->ArraysOf0DDouble[5] = 0.0;
            sec30->ArraysOf0DDouble[6] = sec30->ArraysOf1DDouble[0][nkPoints-1];
            sec30->ArraysOf0DDouble[7] = 0.0;
            sec30->ArraysOf0DDouble[8] = sec30->ArraysOf1DDouble[0][nkPoints-1];
        }
        else
        {
            sec30->ArraysOf0DInt[0] = 0;
            sec30->ArraysOf0DInt[1] = 0;
            sec30->ArraysOf0DInt[2] = 0;
            sec30->ArraysOf0DInt[3] = 0;
            sec30->ArraysOf0DInt[6] = 0;
            sec30->ArraysOf0DDouble[0] = 0.0;
            sec30->ArraysOf1DDouble[0] = Adouble0D();
            sec30->ArraysOf1DString[0] = Astring0D();
            sec30->ArraysOf2DDouble[0] = Adouble1D();
            sec30->ArraysOf2DDouble[1] = Adouble1D();
            sec30->ArraysOf0DDouble[1] = 0.0;
            sec30->ArraysOf0DDouble[2] = 0.0;
            sec30->ArraysOf0DDouble[3] = 0.0;
            sec30->ArraysOf0DDouble[4] = 0.0;
            sec30->ArraysOf0DDouble[5] = 0.0;
            sec30->ArraysOf0DDouble[6] = 0.0;
            sec30->ArraysOf0DDouble[7] = 0.0;
            sec30->ArraysOf0DDouble[8] = 0.0;
        }
    }
    else if (FileFormat==1)
        LoadOpenMXUnfoldedBand(file);
}

void SetupClass::IsRangeOK(int nBandMax, bool &IsMinOK, bool &IsMaxOK)
{
    int nMin, nMax;
    sec30->GetVar(_("DFTBandRange[0]"), nMin);
    sec30->GetVar(_("DFTBandRange[1]"), nMax);
    
    IsMinOK = true;
    IsMaxOK = true;
    
    if (nMax<nMin) {IsMinOK=false;IsMaxOK=false;}
    if (nMax>nBandMax) IsMaxOK=false;
    if (nMin<1) IsMinOK=false;
    if (nMax<1) IsMaxOK=false;
    if (nMin > nBandMax) IsMinOK=false;
}

void SetupClass::Btn_OpenFileU_OnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
                                this, _("Open File"), wxEmptyString, wxEmptyString, 
                                _("OpenMX Unfolded Band-Structure (*.unfold_orb)|*.unfold_orb|Vasp XML Output (*.xml)|*.xml"),
                                wxFD_OPEN, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        int dgFileKind = OpenDialog->GetFilterIndex();
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        sec30->SetVar(_("DFTPathU[0]"), dgPath, false);
        sec30->SetVar(_("DFTFileU[0]"), dgFileName, false);
        wxComboBox* ctr = sec30->GetComboObject(_("BandFileFormatU"));
        ctr->Select(dgFileKind);
        //wxString fl = dgPath + wxT("\\") + dgFileName;
	}
 
	OpenDialog->Destroy();
}

void SetupClass::Btn_ReloadU_OnClick(wxCommandEvent& event)
{
    
}

void SetupClass::Btn_Select_OnClick(wxCommandEvent& event)
{
    wxButton* btnctr = (wxButton*)event.GetEventObject();
    //wxButton* btnctr =  sec30->GetButtonObject(_("PickAtomBtn"));
    //btnctr->SetBackgroundColour(wxColour(wxT("rgb(209,153,180)")));
    if (btnctr->GetForegroundColour() == *wxBLACK)
    {
        btnctr->SetForegroundColour(*wxGREEN);
        sec30->ArraysOf0DInt[6] = 1;
    }
    else
    {
        btnctr->SetForegroundColour(*wxBLACK);
        sec30->ArraysOf0DInt[6] = 0;
    }
    
    sec30->SendUpdateEvent(this->GetName(),0);
}

void SetupClass::LoadOpenMXBand(wxString file, bool &isBandLoaded, int &maxneig, int &mspin, double &ChemP, int &nKp, Adouble1D &KPoints, Adouble1D &EigVal, Adouble0D &dkLabel, Astring0D &kLabel)
{
    isBandLoaded = false;
    try
    {
        FILE *fp;
        if ( (fp=fopen(file,"r")) == 0 )
        {
            wxMessageBox(_("Unable to open the file."),_("Error"));
            return;
        }
        
        fscanf(fp,"%d %d  %lf", &maxneig,&mspin,&ChemP);//read maxneig,mspin,ChemP
        double rtv[3][3];
        fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",
         &rtv[0][0], &rtv[0][1], &rtv[0][2],
         &rtv[1][0], &rtv[1][1], &rtv[1][2],
         &rtv[2][0], &rtv[2][1], &rtv[2][2]);
         
        int nkpath;
        fscanf(fp,"%d",&nkpath);//read nkpath
        
        int* n_perpath = new int[nkpath];
        double k1,k2,k3,k4,k5,k6;
        
        wxString kname1, kname2;
        char* c1 = new char[20];
        char* c2 = new char[20];
        
        nKp = 0;
        Adouble0D A1d;
        dkLabel.clear();
        kLabel.clear();
        KPoints.clear();
        EigVal.clear();
        int n1;
        double vk[3], vec[3], vk2[3], vec2[3], oldvec[3], eig;
        double d = 0.0;
        
        dkLabel.push_back(d);
        for (int i=0;i<nkpath;i++)
        {
            fscanf(fp,"%d %lf %lf %lf  %lf %lf %lf  %s %s",&n_perpath[i],&k1, &k2, &k3,&k4, &k5, &k6, c1, c2);
            kname1 = wxString(c1, wxConvUTF8);
            kname2 = wxString(c2, wxConvUTF8);
            vk[0] = k1; vk[1] = k2; vk[2] = k3;
            vk2[0] = k4; vk2[1] = k5; vk2[2] = k6;
            sec30->vk_rtv(vk,rtv,vec);
            sec30->vk_rtv(vk2,rtv,vec2);
            d += sec30->norm(vec, vec2);
            nKp = nKp + n_perpath[i];
            dkLabel.push_back(d);
            if (kname1 == "G" || kname1 == "g" || kname1.Contains(_("\G")) || kname1.Contains(_("\g")) || kname1.Contains(_("gamma")) || kname1.Contains(_("Gamma"))) kname1 = _("\\Gamma");
            kLabel.push_back(kname1);
        }
        if (kname2 == "G" || kname2 == "g" || kname2.Contains(_("\G")) || kname2.Contains(_("\g")) || kname2.Contains(_("gamma")) || kname2.Contains(_("Gamma"))) kname2 = _("\\Gamma");
        kLabel.push_back(kname2);
        
        d = 0.0;
        for(int i=0; i<nKp; i++)
        {
            fscanf(fp,"%d %lf %lf %lf\n", &n1,&vk[0],&vk[1],&vk[2]);
            
            sec30->vk_rtv(vk,rtv,vec);
            if (i==0)
            {
                oldvec[0]=vec[0];
                oldvec[1]=vec[1];
                oldvec[2]=vec[2];
            }
            d += sec30->norm(vec, oldvec);
            oldvec[0]=vec[0];
            oldvec[1]=vec[1];
            oldvec[2]=vec[2];
            
            A1d.clear();
            for(int j=0; j<3; j++)
            {
                double val = vk[j];
                A1d.push_back(val);
            }
            
            for(int j=0; j<3; j++)
            {
                double val = vec[j];
                A1d.push_back(val);
            }
            
            A1d.push_back(d);
            
            KPoints.push_back(A1d);
            
            A1d.clear();
            for (int l=0;l<n1;l++)
            {
                fscanf(fp,"%lf",&eig);
                A1d.push_back(eig);
            }
            EigVal.push_back(A1d);
        }
        isBandLoaded = true;
    }
    catch (...) { }
}

void SetupClass::LoadOpenMXUnfoldedBand(wxString file)
{
    
}
