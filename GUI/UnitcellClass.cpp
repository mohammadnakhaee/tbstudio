#include "UnitcellClass.h"

UnitcellClass::UnitcellClass(wxWindow* parent, Sec30* sec30var, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetName(wxT("UnitcellClass"));
    SetSize(wxDLG_UNIT(this, wxSize(-1,-1)));
    GetSizer()->Fit(this);
    /**********************************************************************************************************************************************/
    /*************Hidden Variables**************/
    sec30->AddVarVector(this, 1, _("AllSK"), _("string"));
    sec30->SetVar(_("AllSK[0]"),_("sss,sps,sds,pps,ppp,pds,pdp,dds,ddp,ddd"), false);//All SK parameters in this version of software //number of (s,p,d) = 3; if you are going to add more please note that you should add the name of orbitals in file OrbitalsClass.cpp in function Btn_AddShell_OnClick
    sec30->AddVarVector(this, 1, _("nAtoms"), _("int"));
    sec30->SetVar(_("nAtoms[0]"),0, false);
    sec30->AddVarVector(this, 1, _("nShells"), _("int"));
    sec30->SetVar(_("nShells[0]"),0, false);
    sec30->AddVarVector(this, 1, _("nShowingBonds"), _("int"));
    sec30->SetVar(_("nShowingBonds[0]"),0, false);
    wxString ColTypes1[3] = {_("double"), _("double"), _("double")};
    int ColPrecision1[3] = {8, 8, 8};
    sec30->AddGrid(this, 99, 3, _("XYZ_Coords"), ColTypes1, ColPrecision1);
    sec30->AddVarVector(this, 1, _("isDFTBand"), _("bool"));
    sec30->SetVar(_("isDFTBand[0]"),false, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Crystallographic Information File"),wxColour(wxT("rgb(153,180,209)")));
    wxString Labels1[2] = { _("Load"), _("Save")};
    wxObjectEventFunction Funcs1[2] = { wxCommandEventHandler(UnitcellClass::Btn_Load_OnClick), wxCommandEventHandler(UnitcellClass::Btn_Save_OnClick)};
    sec30->AddButton(this, 2, Labels1, Funcs1);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Optimized Unit Vectors"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 3, _("a0"), _("double"), _("a0"), 25, 100);
    sec30->AddVarVector(this, 3, _("b0"), _("double"), _("b0"), 25, 100);
    sec30->AddVarVector(this, 3, _("c0"), _("double"), _("c0"), 25, 100);
    sec30->SetVar(_("a0[0]"), 1.0, false);
    sec30->SetVar(_("a0[1]"),0.0, false);
    sec30->SetVar(_("a0[2]"),0.0, false);
    sec30->SetVar(_("b0[0]"),0.0, false);
    sec30->SetVar(_("b0[1]"),1.0, false);
    sec30->SetVar(_("b0[2]"),0.0, false);
    sec30->SetVar(_("c0[0]"),0.0, false);
    sec30->SetVar(_("c0[1]"),0.0, false);
    sec30->SetVar(_("c0[2]"),1.0, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Strain Coefficients"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 1, _("astrain"), _("double"), _("a"), 25, 100);
    sec30->AddVarVector(this, 1, _("bstrain"), _("double"), _("b"), 25, 100);
    sec30->AddVarVector(this, 1, _("cstrain"), _("double"), _("c"), 25, 100);
    sec30->SetVar(_("astrain[0]"),1.0, false);
    sec30->SetVar(_("bstrain[0]"),1.0, false);
    sec30->SetVar(_("cstrain[0]"),1.0, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Strained Unit Vectors"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 3, _("a"), _("double"), _("a"), 25, 100);
    sec30->AddVarVector(this, 3, _("b"), _("double"), _("b"), 25, 100);
    sec30->AddVarVector(this, 3, _("c"), _("double"), _("c"), 25, 100);
    sec30->SetVar(_("a[0]"), 1.0, false);
    sec30->SetVar(_("a[1]"),0.0, false);
    sec30->SetVar(_("a[2]"),0.0, false);
    sec30->SetVar(_("b[0]"),0.0, false);
    sec30->SetVar(_("b[1]"),1.0, false);
    sec30->SetVar(_("b[2]"),0.0, false);
    sec30->SetVar(_("c[0]"),0.0, false);
    sec30->SetVar(_("c[1]"),0.0, false);
    sec30->SetVar(_("c[2]"),1.0, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Atom Species and Fractional Coordinates"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames[4] = { _("Kind"), _("a"), _("b"), _("c")};
    wxString ColTypes[4] = { _("int"), _("double"), _("double"), _("double")};
    int ColSizes[4] = { 50, 82, 82, 82};
    int ColPrecision[4] = { 0, 8, 8, 8};
    sec30->AddGrid(this, 99, 4, _("KABC_Coords"), ColNames, ColTypes, ColSizes, ColPrecision, 350, 500);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_(""),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
}

UnitcellClass::~UnitcellClass()
{
    //try{}
    //catch(std::exception& ex)
    //{wxMessageBox(ex.what());}
}

void UnitcellClass::Btn_Load_OnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Import Structure"), wxEmptyString, wxEmptyString, 
		_("CIF File (*.cif)|*.cif"),
        wxFD_OPEN, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        //int dgFileKind = OpenDialog->GetFilterIndex();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString dgPath = OpenDialog->GetDirectory();
        wxString fl = dgPath + wxT("\\") + dgFileName;
        ImportFromCIF(dgPath, dgFileName);
	}
 
	OpenDialog->Destroy();
}

void UnitcellClass::Btn_Save_OnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Export Structure"), wxEmptyString, wxEmptyString, 
		_("CIF File (*.cif)|*.cif")
        ,wxFD_SAVE, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        int dgFileKind = OpenDialog->GetFilterIndex();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString dgPath = OpenDialog->GetDirectory();
        ExportToCIF(dgPath, dgFileName);
	}
 
	OpenDialog->Destroy();
}

void UnitcellClass::ExportToCIF(wxString filepath, wxString filename)
{
    double PI=3.14159265359;
    int i,Gc_AN,itmp;
    double tmp[4],Cxyz[4],Cell_Gxyz[4],tv[4][4],rtv[4][4];
    double astrain, bstrain, cstrain;
    double lena,lenb,lenc,t1;
    double alpha,beta,gamma;
    double CellV,Cell_Volume;
    FILE *fp;
      
    bool isValid = true;
    isValid = isValid && sec30->GetVar(_("a[0]"),tv[1][1]); isValid = isValid && sec30->GetVar(_("a[1]"),tv[1][2]); isValid = isValid && sec30->GetVar(_("a[2]"),tv[1][3]);
    isValid = isValid && sec30->GetVar(_("b[0]"),tv[2][1]); isValid = isValid && sec30->GetVar(_("b[1]"),tv[2][2]); isValid = isValid && sec30->GetVar(_("b[2]"),tv[2][3]);
    isValid = isValid && sec30->GetVar(_("c[0]"),tv[3][1]); isValid = isValid && sec30->GetVar(_("c[1]"),tv[3][2]); isValid = isValid && sec30->GetVar(_("c[2]"),tv[3][3]);
    
    isValid = isValid && sec30->GetVar(_("astrain[0]"), astrain);
    isValid = isValid && sec30->GetVar(_("bstrain[0]"), bstrain);
    isValid = isValid && sec30->GetVar(_("cstrain[0]"), cstrain);
    
    if (!isValid) wxMessageBox(_("Unable to create cif file. Please check the inputs."));
    for (int i0=1; i0<=3; i0++)
    {
        tv[1][i0]=tv[1][i0]*astrain;
        tv[2][i0]=tv[2][i0]*bstrain;
        tv[3][i0]=tv[3][i0]*cstrain;
    }
    
  /********************************************
              making of a CIF file
  *********************************************/
  
  //sprintf(fname1,"%s%s.cif",filepath,filename);
  wxString fname1 = filepath + wxT("/") + filename;
  
  Cross_Product(tv[2],tv[3],tmp);
  CellV = Dot_Product(tv[1],tmp); 
  Cell_Volume = fabs(CellV);

  lena = sqrt(fabs(Dot_Product(tv[1],tv[1]))); 
  lenb = sqrt(fabs(Dot_Product(tv[2],tv[2]))); 
  lenc = sqrt(fabs(Dot_Product(tv[3],tv[3]))); 

  Cross_Product(tv[2],tv[3],tmp);
  rtv[1][1] = 2.0*PI*tmp[1]/CellV;
  rtv[1][2] = 2.0*PI*tmp[2]/CellV;
  rtv[1][3] = 2.0*PI*tmp[3]/CellV;
  
  Cross_Product(tv[3],tv[1],tmp);
  rtv[2][1] = 2.0*PI*tmp[1]/CellV;
  rtv[2][2] = 2.0*PI*tmp[2]/CellV;
  rtv[2][3] = 2.0*PI*tmp[3]/CellV;
  
  Cross_Product(tv[1],tv[2],tmp);
  rtv[3][1] = 2.0*PI*tmp[1]/CellV;
  rtv[3][2] = 2.0*PI*tmp[2]/CellV;
  rtv[3][3] = 2.0*PI*tmp[3]/CellV;

  //alpha: angle between b and c in Deg

  t1 = Dot_Product(tv[2],tv[3]);
  if (fabs(t1)<1.0e-14) 
    alpha = 90.0;
  else 
    alpha = acos(t1/(lenb*lenc))/PI*180.0;

  // beta: angle between c and a in Deg

  t1 = Dot_Product(tv[3],tv[1]);
  if (fabs(t1)<1.0e-14) 
    beta = 90.0;
  else 
    beta = acos(t1/(lenc*lena))/PI*180.0;

  // gamma: angle between a and b in Deg

  t1 = Dot_Product(tv[1],tv[2]);
  if (fabs(t1)<1.0e-14) 
    gamma = 90.0;
  else 
    gamma = acos(t1/(lena*lenb))/PI*180.0;

  if ((fp = fopen(fname1,"w")) != NULL){

    fprintf(fp,"data_%s\n",(const char*)filename.mb_str());
    fprintf(fp,"_audit_creation_date              2007-10-11\n");
    fprintf(fp,"_audit_creation_method            'Materials Studio'\n");

    fprintf(fp,"_symmetry_space_group_name_H-M    'P1'\n");
    fprintf(fp,"_symmetry_Int_Tables_number       1\n");
    fprintf(fp,"_symmetry_cell_setting            triclinic\n");

    fprintf(fp,"loop_\n");
    fprintf(fp,"_symmetry_equiv_pos_as_xyz\n");
    fprintf(fp,"  x,y,z\n");

    fprintf(fp,"_cell_length_a%26.4f\n",lena);
    fprintf(fp,"_cell_length_b%26.4f\n",lenb);
    fprintf(fp,"_cell_length_c%26.4f\n",lenc);

    fprintf(fp,"_cell_angle_alpha%24.4f\n",alpha);
    fprintf(fp,"_cell_angle_beta %24.4f\n",beta);
    fprintf(fp,"_cell_angle_gamma%24.4f\n",gamma);

    fprintf(fp,"loop_\n");
    fprintf(fp,"_atom_site_label\n");
    fprintf(fp,"_atom_site_type_symbol\n");
    fprintf(fp,"_atom_site_fract_x\n");
    fprintf(fp,"_atom_site_fract_y\n");
    fprintf(fp,"_atom_site_fract_z\n");
    fprintf(fp,"_atom_site_Uiso_or_equiv\n");
    fprintf(fp,"_atom_site_adp_type\n");
    fprintf(fp,"_atom_site_occupancy\n");
    
    //std::list<double>::iterator ix = tbmodel->XArray.begin();
    //std::list<double>::iterator iy = tbmodel->YArray.begin();
    //std::list<double>::iterator iz = tbmodel->ZArray.begin();
    //std::list<int>::iterator ik = tbmodel->KindArray.begin();
    int nAtoms=0;
    sec30->GetVar(_("nAtoms[0]"),nAtoms);
    for (Gc_AN=1; Gc_AN<=nAtoms; Gc_AN++){

      //The zero is taken as the origin of the unit cell
      int kind=0;
      sec30->GetVar(_("KABC_Coords"),Gc_AN-1,0,kind);
      sec30->GetVar(_("KABC_Coords"),Gc_AN-1,1,Cxyz[1]);
      sec30->GetVar(_("KABC_Coords"),Gc_AN-1,2,Cxyz[2]);
      sec30->GetVar(_("KABC_Coords"),Gc_AN-1,3,Cxyz[3]);
      
      Cell_Gxyz[1] = Dot_Product(Cxyz,rtv[1])*0.5/PI;
      Cell_Gxyz[2] = Dot_Product(Cxyz,rtv[2])*0.5/PI;
      Cell_Gxyz[3] = Dot_Product(Cxyz,rtv[3])*0.5/PI;

      // The fractional coordinates should be within 0 to 1
    for (i=1; i<=3; i++)
    {
          itmp = (int)Cell_Gxyz[i]; 
          if (1.0<Cell_Gxyz[i])
          {
              Cell_Gxyz[i] = fabs(Cell_Gxyz[i] - (double)itmp);
          }
          else if (Cell_Gxyz[i]<-1.0e-13)
          {
              Cell_Gxyz[i] = fabs(Cell_Gxyz[i] + (double)(abs(itmp)+1));
          }
    }
      
      fprintf(fp,"A%-6d%-3s%10.5f%10.5f%10.5f%10.5f  Uiso   1.00\n", Gc_AN, (const char*)sec30->GetAtomLable(kind).mb_str(), Cell_Gxyz[1], Cell_Gxyz[2], Cell_Gxyz[3], 0.0);
    }

    fclose(fp);
  }
}


void UnitcellClass::ImportFromCIF(wxString filepath, wxString filename)
{
    /********************************************
                reading a CIF file
    *********************************************/
    wxString fname1 = filepath + wxT("/") + filename;
    std::ifstream infile(fname1);
    std::string line;
    bool cell_length_a = false;
    bool cell_length_b = false;
    bool cell_length_c = false;
    bool cell_angle_alpha = false;
    bool cell_angle_beta = false;
    bool cell_angle_gamma = false;
    bool ArgList = false;
    bool CoordinatesList = false;
    std::vector<wxString> args;
    std::vector<int> k;
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    
    double a0, b0, c0, alpha, beta, gamma;
    int ind = 0;
    while (std::getline(infile, line))
    {
        ind++;
        wxString l = wxString(line);
        double dval;
        int ival;
        if (!cell_length_a)
        {
            if(l.Contains(_("_cell_length_a")))
            {
                GetValueFromLine(l, dval);
                a0 = dval;
                cell_length_a = true;
            }
        }
        else if (!cell_length_b)
        {
            if(l.Contains(_("_cell_length_b")))
            {
                GetValueFromLine(l, dval);
                b0 = dval;
                cell_length_b = true;
            }
        }
        else if (!cell_length_c)
        {
            if(l.Contains(_("_cell_length_c")))
            {
                GetValueFromLine(l, dval);
                c0 = dval;
                cell_length_c = true;
            }
        }
        else if (!cell_angle_alpha)
        {
            if(l.Contains(_("_cell_angle_alpha")))
            {
                GetValueFromLine(l, dval);
                alpha = dval;
                cell_angle_alpha = true;
            }
        }
        else if (!cell_angle_beta)
        {
            if(l.Contains(_("_cell_angle_beta")))
            {
                GetValueFromLine(l, dval);
                beta = dval;
                cell_angle_beta = true;
            }
        }
        else if (!cell_angle_gamma)
        {
            if(l.Contains(_("_cell_angle_gamma")))
            {
                GetValueFromLine(l, dval);
                gamma = dval;
                cell_angle_gamma = true;
            }
        }
        else if (!ArgList && !CoordinatesList)
        {
            if(l.Contains(_("_atom_site_"))) ArgList = true;
        }
        
        if (ArgList)
        {
            args.push_back(l);
            if(!l.Contains(_("_atom_site_")))
            {
                CoordinatesList = true;
                ArgList = false;
            }
        }
        
        if (CoordinatesList)
        {
            int narg = args.size();
            wxString frmt = _("");
            std::istringstream iss(l.c_str().AsChar());
            for(int i=0; i<narg; i++)
            {
                std::string arg;
                iss >> arg;
                
                if( args[i].Contains(_("_atom_site_type_symbol")))
                {
                    int myKind = sec30->GetAtomLable(wxString(arg));
                    k.push_back(myKind);
                }
                else if( args[i].Contains(_("_atom_site_fract_x")))
                {
                    double val;
                    wxString sarg(arg);
                    sscanf(sarg.c_str(),"%lf",&val);
                    a.push_back(val);
                }
                else if( args[i].Contains(_("_atom_site_fract_y")))
                {
                    double val;
                    wxString sarg(arg);
                    sscanf(sarg.c_str(),"%lf",&val);
                    b.push_back(val);
                }
                else if( args[i].Contains(_("_atom_site_fract_z")))
                {
                    double val;
                    wxString sarg(arg);
                    sscanf(sarg.c_str(),"%lf",&val);
                    c.push_back(val);
                }
            }
            
            int nk = k.size();
            int na = a.size();
            int nb = b.size();
            int nc = c.size();
            
            if (nk!=0 && na!=0 && nb!=0 && nc!=0 && na==nk && cell_length_a && cell_length_b && cell_length_c && cell_angle_alpha && cell_angle_beta && cell_angle_gamma)
            {
                double PI=3.14159265359;
                double ax = a0;
                double bx = b0*cos(gamma/180.0*PI);
                double by = sqrt(b0*b0 - bx*bx);
                double cx = c0*cos(beta/180.0*PI);
                double cy = (a0*b0*cos(alpha/180.0*PI) - bx*c0*cos(beta/180.0*PI))/by;
                double cz = sqrt(by*by*c0*c0 - a0*a0*b0*b0*cos(alpha)*cos(alpha) + 2*a0*b0*bx*c0*cos(alpha)*cos(beta) - bx*bx*c0*c0*cos(beta)*cos(beta) - by*by*c0*c0*cos(beta)*cos(beta))/by;
                
                sec30->SetVar(_("a0[0]"), ax, false);
                sec30->SetVar(_("a0[1]"),0.0, false);
                sec30->SetVar(_("a0[2]"),0.0, false);
                sec30->SetVar(_("b0[0]"),bx, false);
                sec30->SetVar(_("b0[1]"),by, false);
                sec30->SetVar(_("b0[2]"),0.0, false);
                sec30->SetVar(_("c0[0]"),cx, false);
                sec30->SetVar(_("c0[1]"),cy, false);
                sec30->SetVar(_("c0[2]"),cz, false);
                
                for(int ik = 0; ik<nk; ik++)
                {
                    sec30->SetVar(_("KABC_Coords"), ik, 0, k[ik], false);
                    sec30->SetVar(_("KABC_Coords"), ik, 1, a[ik], false);
                    sec30->SetVar(_("KABC_Coords"), ik, 2, b[ik], false);
                    sec30->SetVar(_("KABC_Coords"), ik, 3, c[ik], false);
                }
                sec30->SetVar(_("nAtoms[0]"), nk, false);
                
                sec30->SetVar(_("astrain[0]"),1.0, false);
                sec30->SetVar(_("bstrain[0]"),1.0, false);
                sec30->SetVar(_("cstrain[0]"),1.0, true);
            }
            else
            {
                wxMessageBox(_("Unable to open the file."),_("Error"));
                return;
            }
        }
    }
}

void UnitcellClass::GetValueFromLine(wxString str, double &val)
{
    std::istringstream iss(str.c_str().AsChar());
    std::string dummy;
    iss >> dummy >> val;
}

void UnitcellClass::GetValueFromLine(wxString str, int &val)
{
    std::istringstream iss(str.c_str().AsChar());
    std::string dummy;
    iss >> dummy >> val;
}
