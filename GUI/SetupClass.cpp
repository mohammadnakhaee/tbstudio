#include "SetupClass.h"

/* Parameters */
#define N 4
#define NRHS 2
#define LDA N
#define LDB NRHS

SetupClass::SetupClass(wxWindow* parent, Sec30* sec30var, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    //SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetBackgroundColour(sec30->ThemeMenuColour);
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
    choicectr->Append(_("OpenMX Band-Structure"));
    choicectr->Append(_("Vasp XML Output"));
    choicectr->SetEditable(false);
    choicectr->SetBackgroundColour(*wxWHITE);
    choicectr->Select(0);
    wxString Labels1[2] = {_("Open File"), _("Reload")};
    wxObjectEventFunction Funcs1[2] = { wxCommandEventHandler(SetupClass::Btn_OpenFile_OnClick), wxCommandEventHandler(SetupClass::Btn_Reload_OnClick)};
    sec30->AddButton(this, 2, Labels1, Funcs1);
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
    sec30->AddGroupBox(this,_("DFT Band-Structure"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 2, _("DFTBandRange"), _("int"), _("DFT Bands Range"), 105, 100);
    sec30->AddVarVector(this, 1, _("nDFTBandRange"), _("int"), _("Number of Bands"), 105, 100, false, true);
    sec30->SetVar(_("DFTBandRange[0]"), 0, false);
    sec30->SetVar(_("DFTBandRange[1]"), 0, false);
    sec30->SetVar(_("nDFTBandRange[0]"), 0, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Fitting Customization"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 2, _("TBBandRange"), _("int"), _("TB Bands Range"), 105, 100, false, false);
    sec30->AddVarVector(this, 1, _("DFTFirst"), _("int"), _("DFT First Band"), 105, 100, false, false);
    sec30->SetVar(_("TBBandRange[0]"), 0, false);
    sec30->SetVar(_("TBBandRange[1]"), 0, false);
    sec30->SetVar(_("DFTFirst[0]"), 0, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Weight Function"),wxColour(wxT("rgb(153,180,209)")));
    wxString Labels11[2] = {_("Clear all"), _("Set all to one")};
    wxObjectEventFunction Funcs11[2] = { wxCommandEventHandler(SetupClass::Btn_SetZero_OnClick), wxCommandEventHandler(SetupClass::Btn_SetOne_OnClick)};
    sec30->AddButton(this, 2, Labels11, Funcs11);
    wxString Labels3[1] = {_("Brush")};
    wxObjectEventFunction Funcs3[1] = { wxCommandEventHandler(SetupClass::Btn_Select_OnClick)};
    sec30->AddButton(this, 1, Labels3, Funcs3);
    sec30->AddGroupBox(this,_("To increase the weight function, paint on bands."),sec30->ThemeMenuColour);
    sec30->AddGroupBox(this,_("To decrease, hold Ctrl or Alt key and paint."),sec30->ThemeMenuColour);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Fitting Algorithmic Parameters"),wxColour(wxT("rgb(153,180,209)")));
    wxComboBox* choicectrm = sec30->AddComboCtrl(this, _("OMethod"), _("Method"), 70, 200, true);
    choicectrm->Append(_("Nielsen's lambda"));
    choicectrm->Append(_("Levenberg-Marquardt"));
    choicectrm->Append(_("Quadratic"));
    choicectrm->SetEditable(false);
    choicectrm->SetBackgroundColour(*wxWHITE);
    choicectrm->Select(0);
    sec30->AddVarVector(this, 1, _("OPrnt"), _("int"), _("Figure Updating Step"), 170, 100, false, false);
    sec30->SetVar(_("OPrnt[0]"), 3, false);
    sec30->AddVarVector(this, 1, _("OMaxIter"), _("int"), _("Iteration Limit"), 170, 100, false, false);
    sec30->SetVar(_("OMaxIter[0]"), 50, false);
    sec30->AddVarVector(this, 1, _("Oeps1"), _("double"), _("Gradient Threshold"), 170, 100, false, false);
    sec30->SetVar(_("Oeps1[0]"), 0.0001, false);
    sec30->AddVarVector(this, 1, _("Oeps2"), _("double"), _("Parameters Threshold"), 170, 100, false, false);
    sec30->SetVar(_("Oeps2[0]"), 0.0001, false);
    sec30->AddVarVector(this, 1, _("Oeps3"), _("double"), _("Reduced Chi-squared"), 170, 100, false, false);
    sec30->SetVar(_("Oeps3[0]"), 0.001, false);
    sec30->AddVarVector(this, 1, _("Oeps4"), _("double"), _("L-M Acceptance"), 170, 100, false, false);
    sec30->SetVar(_("Oeps4[0]"), 0.001, false);
    sec30->AddVarVector(this, 1, _("OLam0"), _("double"), _("L-M Lambda0"), 170, 100, false, false);
    sec30->SetVar(_("OLam0[0]"), 0.0001, false);
    sec30->AddVarVector(this, 1, _("OLamUp"), _("double"), _("Increasing Lambda"), 170, 100, false, false);
    sec30->SetVar(_("OLamUp[0]"), 0.001, false);
    sec30->AddVarVector(this, 1, _("OLamDn"), _("double"), _("Decreasing Lambda"), 170, 100, false, false);
    sec30->SetVar(_("OLamDn[0]"), 0.0001, false);
    sec30->AddVarVector(this, 1, _("OMaxP"), _("double"), _("Parameters Maximum"), 170, 100, false, false);
    sec30->SetVar(_("OMaxP[0]"), 1000.0, false);
    sec30->AddVarVector(this, 1, _("OMinP"), _("double"), _("Parameters Minimum"), 170, 100, false, false);
    sec30->SetVar(_("OMinP[0]"), -1000.0, false);
    sec30->AddVarVector(this, 1, _("OMixing"), _("double"), _("Mixing"), 170, 100, false, false);
    sec30->SetVar(_("OMixing[0]"), 1.0, false);
    sec30->AddVarVector(this, 1, _("OReScale"), _("double"), _("Rescale Factor"), 170, 100, false, false);
    sec30->SetVar(_("OReScale[0]"), 1.0, false);
    /**********************************************************************************************************************************************/
    //sec30->AddGroupBox(this,_("k-Path"),wxColour(wxT("rgb(153,180,209)")));
    //wxString ColNames1[4] = { _("Parameter"), _("Initial Value"), _("Last Value")};
    //wxString ColTypes1[4] = { _("string"), _("double"), _("double")};
    //int ColSizes1[4] = {96, 100, 100};
    //int ColPrecision1[4] = { 0, 8, 8};
    //sec30->AddGrid(this, 0, 3, _("kpath"), ColNames1, ColTypes1, ColSizes1, ColPrecision1, 350, 400);
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
    
    bool isOK=false;
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        isOK = true;
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
    if (isOK)
    {
        ReloadBand();
        sec30->SendUpdateEvent(this->GetName());
    }
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
    
    sec30->DFTNomadEntryID = _("");
    
    wxComboBox* ctr =  sec30->GetComboObject(_("BandFileFormat"));
    int FileFormat = ctr->GetSelection();
    if (FileFormat < 0)
    {
        wxMessageBox(_("Please choose the file format."),_("Error"));
        return;
    }
    else
    {
        int maxneig, mspin, nKPoint;
        double ChemP;
        bool isBandLoaded;
        Adouble1D KPoints;
        Adouble1D EigVal;
        
        Adouble0D dkLabel;
        Astring0D kLabel;
        Aint0D bandSections;
        
        if (FileFormat==0)
            LoadOpenMXBand(file, isBandLoaded, maxneig, mspin, ChemP, nKPoint, KPoints, EigVal, dkLabel, kLabel, bandSections);
        else if (FileFormat==1)
            LoadVaspXMLOutput(file, isBandLoaded, maxneig, mspin, ChemP, nKPoint, KPoints, EigVal, dkLabel, kLabel, bandSections);
        
        if (isBandLoaded)
        {
            int nk0 = EigVal.size();
            int nband0 = EigVal[0].size();
            Adouble1D EigValWeights(nk0,std::vector<double>(nband0,1.0));
            
            sec30->isBandLoaded = true;
            sec30->nKPoint = nKPoint;
            sec30->maxneig = maxneig;
            sec30->mspin = mspin;
            sec30->isSelectMode = false;
            sec30->ChemP = ChemP;
            sec30->dkLabel = dkLabel;
            sec30->kLabel = kLabel;
            sec30->bandSections = bandSections;
            sec30->KPoints = KPoints;
            sec30->DFTEigVal = EigVal;
            sec30->DFTEigValWeight = EigValWeights;
    
            bool isMinOK, isMaxOK;
            IsRangeOK(maxneig, isMinOK, isMaxOK);
            if (!isMinOK)
            {
                sec30->SetVar(_("DFTBandRange[0]"), 1, false);
                sec30->DFTnBandMin = 1;//int DFTnBandMin;
            }
            if (!isMaxOK)
            {
                sec30->SetVar(_("DFTBandRange[1]"), maxneig, false);
                sec30->DFTnBandMax = maxneig;//int DFTnBandMax;
            }
            
            if (sec30->DFTyMin2d0 == sec30->DFTyMax2d0)
            {
                sec30->DFTyMin2d0 = -5;
                sec30->DFTyMax2d0 = 5;
                sec30->DFTyMin2d = -5;
                sec30->DFTyMax2d = 5;
            }
            
            int nkPoints = sec30->dkLabel.size();
            sec30->DFTxMin2d0 = 0.0;
            sec30->DFTxMax2d0 = sec30->dkLabel[nkPoints-1];
            sec30->DFTxMin2d = 0.0;
            sec30->DFTxMax2d = sec30->dkLabel[nkPoints-1];
        }
        else
        {
            sec30->isBandLoaded = false;
            sec30->nKPoint = 0;
            sec30->maxneig = 0;
            sec30->mspin = 0;
            sec30->isSelectMode = false;
            sec30->ChemP = 0.0;
            sec30->dkLabel = Adouble0D();
            sec30->kLabel = Astring0D();
            sec30->KPoints = Adouble1D();
            sec30->DFTEigVal = Adouble1D();
            sec30->DFTEigValWeight = Adouble1D();
            sec30->DFTyMin2d0 = 0.0;
            sec30->DFTyMax2d0 = 0.0;
            sec30->DFTyMin2d = 0.0;
            sec30->DFTyMax2d = 0.0;
            sec30->DFTxMin2d0 = 0.0;
            sec30->DFTxMax2d0 = 0.0;
            sec30->DFTxMin2d = 0.0;
            sec30->DFTxMax2d = 0.0;
        }
    }
    
    //else if (FileFormat==1)
        //LoadOpenMXUnfoldedBand(file);
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
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
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
    if (btnctr->GetForegroundColour() != *wxGREEN)
    {
        btnctr->SetForegroundColour(*wxGREEN);
        sec30->isSelectMode = true;
    }
    else
    {
        btnctr->SetForegroundColour(*wxBLACK);
        sec30->isSelectMode = false;
    }
    
    sec30->SendUpdateEvent(this->GetName(),0);
}

void SetupClass::Btn_Test_OnClick(wxCommandEvent& event)
{
    wxMessageBox(_("LapackE Example."),_("debug"));
    lapack_int n = N, nrhs = NRHS, lda = LDA, ldb = LDB, info;
        /* Local arrays */
        lapack_int ipiv[N];
        lapack_complex_double a[LDA*N] = {
           { 1.23, -5.50}, { 7.91, -5.38}, {-9.80, -4.86}, {-7.32,  7.57},
           {-2.14, -1.12}, {-9.92, -0.79}, {-9.18, -1.12}, { 1.37,  0.43},
           {-4.30, -7.10}, {-6.47,  2.52}, {-6.51, -2.67}, {-5.86,  7.38},
           { 1.27,  7.29}, { 8.90,  6.92}, {-8.82,  1.25}, { 5.41,  5.37}
        };
        lapack_complex_double b[LDB*N] = {
           { 8.33, -7.32}, {-6.11, -3.81},
           {-6.18, -4.80}, { 0.14, -7.71},
           {-5.71, -2.80}, { 1.41,  3.40},
           {-1.60,  3.08}, { 8.54, -4.05}
        };
        
        info = LAPACKE_zgesv(LAPACK_ROW_MAJOR, n, nrhs, a, lda, ipiv, b, ldb );
        
    wxMessageBox(wxString::Format("%d",info),_("debug"));
}

void SetupClass::LoadOpenMXBand(wxString file, bool &isBandLoaded, int &maxneig, int &mspin, double &ChemP, int &nKp, Adouble1D &KPoints, Adouble1D &EigVal, Adouble0D &dkLabel, Astring0D &kLabel, Aint0D &bandSections)
{
    double Hartree2eV = 27.2113961318;
    double BohrToAng = 1.88973;
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
        ChemP = ChemP * Hartree2eV;
        double rtv[3][3];
        fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf",
         &rtv[0][0], &rtv[0][1], &rtv[0][2],
         &rtv[1][0], &rtv[1][1], &rtv[1][2],
         &rtv[2][0], &rtv[2][1], &rtv[2][2]);
        
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++) rtv[i][j] = rtv[i][j] * BohrToAng;
            Adouble0D A1dvecs;
            A1dvecs.push_back(rtv[i][0]);
            A1dvecs.push_back(rtv[i][1]);
            A1dvecs.push_back(rtv[i][2]);
            if (i == 0) sec30->akDFT = A1dvecs;
            if (i == 1) sec30->bkDFT = A1dvecs;
            if (i == 2) sec30->ckDFT = A1dvecs;
        }
        
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
        bandSections.clear();
        int n1;
        double vk[3], vec[3], vk2[3], vec2[3], oldvec[3], eig;
        double d = 0.0;
        
        dkLabel.push_back(d);
        bandSections.push_back(nKp);
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
            bandSections.push_back(nKp);
        }
        if (kname2 == "G" || kname2 == "g" || kname2.Contains(_("\G")) || kname2.Contains(_("\g")) || kname2.Contains(_("gamma")) || kname2.Contains(_("Gamma"))) kname2 = _("\\Gamma");
        kLabel.push_back(kname2);
        
        bool spin1=false;
        bool spin2=false;
        if (mspin>0) //0 -> one spin      1-> two spins
        {
            wxMessageDialog dial1(NULL, 
              _("There are two datasets in your data file, spin-up and spin-down. Do you want to load both spins as an indivisible fitting dataset?"),
              wxT("Both spins?"), 
              wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
            
            if ( dial1.ShowModal() == wxID_NO )
            {
                wxMessageDialog dial(NULL, 
                  _("Which spin do you like to load?"),
                  wxT("Which spin?"), 
                  wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
                
                dial.SetYesNoLabels(wxT("spin-up"), wxT("spin-down"));
                
                spin1=true;
                if ( dial.ShowModal() == wxID_NO )
                {
                    spin1=false;
                    spin2=true;
                }
            }   
            else
            {
                spin1=true;
                spin2=true;
            }
        }
        else
            spin1=true;
        
        
        int PathCounter = 0;
        int ThisPathInd = 0;
        d = 0.0;
        Adouble2D kArr = Adouble2D();
        for(int i=0; i<nKp; i++)
        {
            Adouble1D sArr = Adouble1D();
            for(int ispin=0; ispin<mspin+1; ispin++)
            {
                fscanf(fp,"%d %lf %lf %lf\n", &n1,&vk[0],&vk[1],&vk[2]);
                
                if (ispin==0)
                {
                    sec30->vk_rtv(vk,rtv,vec);
                    if (i==0)
                    {
                        oldvec[0]=vec[0];
                        oldvec[1]=vec[1];
                        oldvec[2]=vec[2];
                    }
                    double deltakPath = sec30->norm(vec, oldvec);
                    if (PathCounter == n_perpath[ThisPathInd])
                    {
                        deltakPath = 0.000001;
                        PathCounter = 0;
                        ThisPathInd++;
                    }
                    PathCounter++;
                    d += deltakPath;
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
                }
                
                Adouble0D eArr = Adouble0D();
                for (int l=0;l<n1;l++)
                {
                    fscanf(fp,"%lf",&eig);
                    eig = eig * Hartree2eV;
                    eArr.push_back(eig);
                }
                sArr.push_back(eArr);
            }
            kArr.push_back(sArr);
        }
        
        if (spin1 && spin2)
        {
            int nk = kArr.size();
            for (int ik=0; ik<nk; ik++)
            {
                Adouble0D SortedkArr;
                for (int ie=0; ie<maxneig; ie++) SortedkArr.push_back(kArr[ik][0][ie]);
                for (int ie=0; ie<maxneig; ie++) SortedkArr.push_back(kArr[ik][1][ie]);
                std::sort(SortedkArr.begin(), SortedkArr.end());
                EigVal.push_back(SortedkArr);
            }
            maxneig=2*maxneig;
        }
        else
        {
            if (spin1)
            {
                int nk = kArr.size();
                for (int ik=0; ik<nk; ik++) EigVal.push_back(kArr[ik][0]);
            }
            else
            {
                int nk = kArr.size();
                for (int ik=0; ik<nk; ik++) EigVal.push_back(kArr[ik][1]);
            }
        }
        
        isBandLoaded = true;
    }
    catch (...) { }
}

void SetupClass::LoadOpenMXUnfoldedBand(wxString file)
{
    
}

void SetupClass::LoadVaspXMLOutput(wxString file, bool &isBandLoaded, int &maxneig, int &mspin, double &ChemP, int &nKp, Adouble1D &KPoints, Adouble1D &EigVal, Adouble0D &dkLabel, Astring0D &kLabel, Aint0D &bandSections)
{
    isBandLoaded = false;
    try
    {
        rapidxml::file<> xmlFile(file); // Default template is char
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());
        
        rapidxml::xml_node<>* modeling_node = doc.first_node("modeling");
        if (!modeling_node) return;
        rapidxml::xml_node<>* structure_node = modeling_node->first_node("structure");
        if (!structure_node) return;
        rapidxml::xml_node<>* crystal_node = structure_node->first_node("crystal");
        if (!crystal_node) return;
        rapidxml::xml_node<>* rec_basis_node;
        for (rapidxml::xml_node<> * nd = crystal_node->first_node("varray"); nd; nd = nd->next_sibling("varray"))
        {
            if (_(nd->first_attribute("name")->value()) == _("rec_basis"))
            {
                rec_basis_node = nd;
                break;
            }
        }
        
        double rtv[3][3];
        rapidxml::xml_node<>* v_node = rec_basis_node->first_node("v");
        if (!v_node) return;
        sscanf(v_node->value(), "%lf %lf %lf", &rtv[0][0], &rtv[0][1], &rtv[0][2]);
        
        v_node = v_node->next_sibling("v");
        if (!v_node) return;
        sscanf(v_node->value(), "%lf %lf %lf", &rtv[1][0], &rtv[1][1], &rtv[1][2]);
        
        v_node = v_node->next_sibling("v");
        if (!v_node) return;
        sscanf(v_node->value(), "%lf %lf %lf", &rtv[2][0], &rtv[2][1], &rtv[2][2]);
        
        //wxMessageBox(wxString::Format(_("%.8f, %.8f, %.8f, %.8f, %.8f, %.8f, %.8f, %.8f, %.8f"),   rtv[0][0], rtv[0][1], rtv[0][2],   rtv[1][0], rtv[1][1], rtv[1][2],   rtv[2][0], rtv[2][1], rtv[2][2]   ));
        
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++) rtv[i][j] = 2.0*3.1415926535897932384626*rtv[i][j];// Vasp does not have a 2pi factor in its calculations
            Adouble0D A1dvecs;
            A1dvecs.push_back(rtv[i][0]);
            A1dvecs.push_back(rtv[i][1]);
            A1dvecs.push_back(rtv[i][2]);
            if (i == 0) sec30->akDFT = A1dvecs;
            if (i == 1) sec30->bkDFT = A1dvecs;
            if (i == 2) sec30->ckDFT = A1dvecs;
        }
        
        rapidxml::xml_node<>* kpoint = modeling_node->first_node("kpoints");
        if (!kpoint) return;
        
        rapidxml::xml_node<>* listgenerated = kpoint->first_node("generation");
        if (!listgenerated) return;
        
        rapidxml::xml_node<>* divisions = listgenerated->first_node("i");
        if (!divisions) return;
        int ndiv;
        sscanf(divisions->value(), "%d", &ndiv);
        
        double ka, kb, kc;
        Adouble1D Bufkpaths;
        for (rapidxml::xml_node<> * nd = listgenerated->first_node("v"); nd; nd = nd->next_sibling("v"))
        {
            Adouble0D kvec0;
            sscanf(nd->value(), "%lf %lf %lf", &ka, &kb, &kc);
            kvec0.push_back(ka);
            kvec0.push_back(kb);
            kvec0.push_back(kc);
            Bufkpaths.push_back(kvec0);
        }
        
        int nkpath = Bufkpaths.size() - 1;
        int* n_perpath = new int[nkpath];
        for (int i=0; i<nkpath; i++) n_perpath[i] = ndiv;
        
        //double k1,k2,k3,k4,k5,k6;
        wxString kname1, kname2;
        char* c1 = new char[20];
        char* c2 = new char[20];
        
        nKp = 0;
        Adouble0D A1d;
        dkLabel.clear();
        kLabel.clear();
        KPoints.clear();
        EigVal.clear();
        bandSections.clear();
        int n1;
        double vk[3], vec[3], vk2[3], vec2[3], oldvec[3], eig;
        double d = 0.0;
        
        dkLabel.push_back(d);
        bandSections.push_back(nKp);
        for (int i=0;i<nkpath;i++)
        {
            //fscanf(fp,"%d %lf %lf %lf  %lf %lf %lf  %s %s",&n_perpath[i],&k1, &k2, &k3,&k4, &k5, &k6, c1, c2);
            kname1 = wxString(_(" "));
            kname2 = wxString(_(" "));
            vk[0] = Bufkpaths[i][0]; vk[1] = Bufkpaths[i][1]; vk[2] = Bufkpaths[i][2];
            vk2[0] = Bufkpaths[i+1][0]; vk2[1] = Bufkpaths[i+1][1]; vk2[2] = Bufkpaths[i+1][2];
            sec30->vk_rtv(vk,rtv,vec);
            sec30->vk_rtv(vk2,rtv,vec2);
            d += sec30->norm(vec, vec2);
            nKp = nKp + n_perpath[i];
            dkLabel.push_back(d);
            if (kname1 == "G" || kname1 == "g" || kname1.Contains(_("\G")) || kname1.Contains(_("\g")) || kname1.Contains(_("gamma")) || kname1.Contains(_("Gamma"))) kname1 = _("\\Gamma");
            kLabel.push_back(kname1);
            bandSections.push_back(nKp);
        }
        if (kname2 == "G" || kname2 == "g" || kname2.Contains(_("\G")) || kname2.Contains(_("\g")) || kname2.Contains(_("gamma")) || kname2.Contains(_("Gamma"))) kname2 = _("\\Gamma");
        kLabel.push_back(kname2);
        
        rapidxml::xml_node<>* kpointlist = kpoint->first_node("varray");
        if (!kpointlist) return;
        
        int PathCounter = 0;
        int ThisPathInd = 0;
        d = 0.0;
        bool isFirst = true;
        for (rapidxml::xml_node<>* nd = kpointlist->first_node("v"); nd; nd = nd->next_sibling("v"))   //for(int i=0; i<nKp; i++)
        {
            sscanf(nd->value(), "%lf %lf %lf", &vk[0], &vk[1], &vk[2]);
            
            sec30->vk_rtv(vk,rtv,vec);
            if (isFirst)
            {
                oldvec[0]=vec[0];
                oldvec[1]=vec[1];
                oldvec[2]=vec[2];
                isFirst = false;
            }
            double deltakPath = sec30->norm(vec, oldvec);
            if (PathCounter == n_perpath[ThisPathInd])
            {
                deltakPath = 0.000001;
                PathCounter = 0;
                ThisPathInd++;
            }
            PathCounter++;
            d += deltakPath;
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
        }
        
        //reading the number of bands
        rapidxml::xml_node<>* parameters = modeling_node->first_node("parameters");
        if (!parameters) return;
        
        rapidxml::xml_node<>* electronic;
        for (rapidxml::xml_node<> * nd = parameters->first_node("separator"); nd; nd = nd->next_sibling("separator"))
        {
            if (_(nd->first_attribute("name")->value()) == _("electronic"))
            {
                electronic = nd;
                break;
            }
        }
        
        for (rapidxml::xml_node<> * nd = electronic->first_node("i"); nd; nd = nd->next_sibling("i"))
        {
            if (_(nd->first_attribute("name")->value()) == _("NBANDS"))
            {
                sscanf(nd->value(), "%d", &maxneig);
                break;
            }
        }
        
        //Loading Eigenvalues
        rapidxml::xml_node<>* calculation = modeling_node->first_node("calculation");
        if (!calculation) return;
        rapidxml::xml_node<>* eigenvalues = calculation->first_node("eigenvalues");
        if (!eigenvalues) return;
        rapidxml::xml_node<>* eigenvaluesarray = eigenvalues->first_node("array");
        if (!eigenvaluesarray) return;
        rapidxml::xml_node<>* spin_list = eigenvaluesarray->first_node("set");
        if (!spin_list) return;
        
        mspin=0;
        for (rapidxml::xml_node<>* nd = spin_list->first_node("set"); nd; nd = nd->next_sibling("set")) mspin++;
        if (mspin == 0) return;
        
        //reading EigenValues and storing them in a vector
        Adouble2D sArr = Adouble2D();
        for (rapidxml::xml_node<>* spinnode = spin_list->first_node("set"); spinnode; spinnode = spinnode->next_sibling("set"))
        {
            Adouble1D kArr = Adouble1D();
            for (rapidxml::xml_node<>* knode = spinnode->first_node("set"); knode; knode = knode->next_sibling("set"))
            {
                Adouble0D eArr = Adouble0D();
                for (rapidxml::xml_node<>* eignode = knode->first_node("r"); eignode; eignode = eignode->next_sibling("r"))
                {
                    double energy, dummy;
                    sscanf(eignode->value(), "%lf %lf", &energy, &dummy);
                    eArr.push_back(energy);
                }
                kArr.push_back(eArr);
            }
            sArr.push_back(kArr);
        }
        
        bool spin1=false;
        bool spin2=false;
        if (mspin>1)
        {
            wxMessageDialog dial1(NULL, 
              _("There are two datasets in your xml file, spin-up and spin-down. Do you want to load both spins as an indivisible fitting dataset?"),
              wxT("Both spins?"), 
              wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
            
            if ( dial1.ShowModal() == wxID_NO )
            {
                wxMessageDialog dial(NULL, 
                  _("Which spin do you like to load?"),
                  wxT("Which spin?"), 
                  wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
                
                dial.SetYesNoLabels(wxT("spin-up"), wxT("spin-down"));
                
                spin1=true;
                if ( dial.ShowModal() == wxID_NO )
                {
                    spin1=false;
                    spin2=true;
                }
            }   
            else
            {
                spin1=true;
                spin2=true;
            }
        }
        else
            spin1=true;
        
        if (spin1 && spin2)
        {
            int nk = sArr[0].size();
            for (int ik=0; ik<nk; ik++)
            {
                Adouble0D SortedkArr;
                for (int ie=0; ie<maxneig; ie++) SortedkArr.push_back(sArr[0][ik][ie]);
                for (int ie=0; ie<maxneig; ie++) SortedkArr.push_back(sArr[1][ik][ie]);
                std::sort(SortedkArr.begin(), SortedkArr.end());
                EigVal.push_back(SortedkArr);
            }
            maxneig=2*maxneig;
        }
        else
        {
            if (spin1)
            {
                int nk = sArr[0].size();
                for (int ik=0; ik<nk; ik++) EigVal.push_back(sArr[0][ik]);
            }
            else
            {
                int nk = sArr[1].size();
                for (int ik=0; ik<nk; ik++) EigVal.push_back(sArr[1][ik]);
            }
        }
        
        rapidxml::xml_node<>* dos_node = calculation->first_node("dos");
        if (!dos_node) return;
        rapidxml::xml_node<>* EFermi_node = dos_node->first_node("i");
        if (!EFermi_node) return;
        
        sscanf(EFermi_node->value(), "%lf", &ChemP);
        
        isBandLoaded = true;
    }
    catch (...) { }
}

void SetupClass::Btn_SetZero_OnClick(wxCommandEvent& event)
{
    sec30->SendUpdateEvent(this->GetName(),2);
}

void SetupClass::Btn_SetOne_OnClick(wxCommandEvent& event)
{
    sec30->SendUpdateEvent(this->GetName(),3);
}
