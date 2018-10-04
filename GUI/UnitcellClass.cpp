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
    sec30->AddVarVector(this, 1, _("nAtoms"), _("int"));
    sec30->SetVar(_("nAtoms[0]"),0, false);
    sec30->AddVarVector(this, 1, _("nShowingAtoms"), _("int"));
    sec30->SetVar(_("nShowingAtoms[0]"),0, false);
    sec30->AddVarVector(this, 1, _("nShells"), _("int"));
    sec30->SetVar(_("nShells[0]"),0, false);
    sec30->AddVarVector(this, 1, _("nShowingBonds"), _("int"));
    sec30->SetVar(_("nShowingBonds[0]"),0, false);
    wxString ColTypes2[3] = {_("double"), _("double"), _("double")};
    int ColPrecision2[3] = {8, 8, 8};
    sec30->AddGrid(this, 99, 3, _("XYZ_Coords"), ColTypes2, ColPrecision2);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Crystallographic Information File"),wxColour(wxT("rgb(153,180,209)")));
    wxString Labels1[2] = { _("Load"), _("Save")};
    wxObjectEventFunction Funcs1[2] = { wxCommandEventHandler(UnitcellClass::Btn_Load_OnClick), wxCommandEventHandler(UnitcellClass::Btn_Save_OnClick)};
    sec30->AddButton(this, 2, Labels1, Funcs1);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Unit Vectors"),wxColour(wxT("rgb(153,180,209)")));
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
    sec30->AddGroupBox(this,_("Strain Coefficients"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddVarVector(this, 1, _("astrain"), _("double"), _("a"), 25, 100);
    sec30->AddVarVector(this, 1, _("bstrain"), _("double"), _("b"), 25, 100);
    sec30->AddVarVector(this, 1, _("cstrain"), _("double"), _("c"), 25, 100);
    sec30->SetVar(_("astrain[0]"),1.0, false);
    sec30->SetVar(_("bstrain[0]"),1.0, false);
    sec30->SetVar(_("cstrain[0]"),1.0, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Atom species and Fractional Coordinates"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames[4] = { _("Kind"), _("a"), _("b"), _("c")};
    wxString ColTypes[4] = { _("int"), _("double"), _("double"), _("double")};
    int ColSizes[4] = { 50, 75, 75, 75};
    int ColPrecision[4] = { 0, 8, 8, 8};
    sec30->AddGrid(this, 99, 4, _("KABC_Coords"), ColNames, ColTypes, ColSizes, ColPrecision, 340, 300);
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
        
        wxString fl = dgPath + wxT("/") + dgFileName;
        
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


