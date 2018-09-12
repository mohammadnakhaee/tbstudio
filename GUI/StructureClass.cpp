#include "StructureClass.h"

StructureClass::StructureClass(wxWindow* parent, Sec30* sec30var)
    : StructureBaseClass(parent)
{
    //tbmodel=tbmodelvar;
    sec30=sec30var;
    CreateAtomsGrid();
    
    
    ctr_a0->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->a[0]));
    ctr_a1->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->a[1]));
    ctr_a2->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->a[2]));
    ctr_b0->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->b[0]));
    ctr_b1->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->b[1]));
    ctr_b2->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->b[2]));
    ctr_c0->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->c[0]));
    ctr_c1->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->c[1]));
    ctr_c2->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->c[2]));
    ctr_a_strain->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->a_strain));
    ctr_b_strain->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->b_strain));
    ctr_c_strain->ChangeValue(wxString::Format(wxT("%lf"), (double)tbmodel->c_strain));
    
    
    sec30->AddGroupBox(this,_("Crystallographic Information File"),wxColour(wxT("rgb(153,180,209)")));
    
    sec30->AddGroupBox(this,_("Unit Vectors"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddDoubleVec(this, 3, _("a"), _("a"), 25, 100);
    sec30->AddDoubleVec(this, 3, _("b"), _("b"), 25, 100);
    sec30->AddDoubleVec(this, 3, _("c"), _("c"), 25, 100);
    sec30->SetVar(this,_("a[0]"),1.0);
    sec30->SetVar(this,_("a[1]"),0.0);
    sec30->SetVar(this,_("a[2]"),0.0);
    sec30->SetVar(this,_("b[0]"),0.0);
    sec30->SetVar(this,_("b[1]"),1.0);
    sec30->SetVar(this,_("b[2]"),0.0);
    sec30->SetVar(this,_("c[0]"),0.0);
    sec30->SetVar(this,_("c[1]"),0.0);
    sec30->SetVar(this,_("c[2]"),1.0);
    
    sec30->AddGroupBox(this,_("Strain Coefficients"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddDoubleVec(this, 1, _("astrain"), _("a"), 25, 100);
    sec30->AddDoubleVec(this, 1, _("bstrain"), _("b"), 25, 100);
    sec30->AddDoubleVec(this, 1, _("cstrain"), _("c"), 25, 100);
    sec30->SetVar(this,_("astrain[0]"),1.0);
    sec30->SetVar(this,_("bstrain[0]"),1.0);
    sec30->SetVar(this,_("cstrain[0]"),1.0);
    
    sec30->AddGroupBox(this,_("Atom species and Fractional Coordinates"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames[4] = { _("Kind"), _("a"), _("b"), _("c")};
    wxString ColTypes[4] = { _("int"), _("double"), _("double"), _("double")};
    int ColSizes[4] = { 50, 75, 75, 75};
    int ColPrecision[4] = { 0, 8, 8, 8};
    sec30->AddDouble2dArray(this, 999, 4, _("atomgrids"), ColNames, ColTypes, ColSizes, ColPrecision, 340, 300);
    
    sec30->AddGroupBox(this,_("Import and Export XYZ Coordinates in Angstrom"),wxColour(wxT("rgb(153,180,209)")));

}

StructureClass::~StructureClass()
{
}

void StructureClass::CreateAtomsGrid(void)
{
    /*AtomsGrid = new myGrid( gridpanel,wxID_ANY,wxDefaultPosition,gridpanel->GetSize());
    AtomsGrid->EnableEditing(true);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gridpanel, 1, wxEXPAND);
    AtomsGrid->SetSizer(mainSizer);

    AtomsGrid->CreateGrid( 999, 4);
    AtomsGrid->SetColLabelValue(0,wxString("Kind"));
    AtomsGrid->SetColLabelValue(1,wxString("a"));
    AtomsGrid->SetColLabelValue(2,wxString("b"));
    AtomsGrid->SetColLabelValue(3,wxString("c"));
    AtomsGrid->SetColSize( 0, 65 );// in pixels
    AtomsGrid->SetColSize( 1, 65 );
    AtomsGrid->SetColSize( 2, 65 );
    AtomsGrid->SetColSize( 3, 65 );
    
    AtomsGrid->SetColMinimalAcceptableWidth(1);
    //*wxGREEN
    wxColour c;
    c.Set(191,205,219,0);
    AtomsGrid->SetLabelBackgroundColour(c);
    AtomsGrid->SetColLabelSize(20);
    AtomsGrid->SetRowLabelSize(35);
    
    AtomsGrid->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(StructureClass::OnCellChanged), NULL, this);
    AtomsGrid->Connect(MyGridPasteEvent, wxCommandEventHandler(StructureClass::OnGridPaste), NULL, this);
     */
}

int StructureClass::ValidateAtoms(void)
{
    /*tbmodel->XArray.clear();
    tbmodel->YArray.clear();
    tbmodel->ZArray.clear();
    tbmodel->KindArray.clear();
    int AtomCnt=0;
    double A,B,C;
    double x,y,z;
    long int kind;
    int nRow = AtomsGrid->GetNumberRows();
    int i=-1;
    bool isValid=true;
    std::list<double>::iterator ia = tbmodel->AArray.end();
    std::list<double>::iterator ib = tbmodel->BArray.end();
    std::list<double>::iterator ic = tbmodel->CArray.end();
    std::list<double>::iterator ix = tbmodel->XArray.end();
    std::list<double>::iterator iy = tbmodel->YArray.end();
    std::list<double>::iterator iz = tbmodel->ZArray.end();
    std::list<int>::iterator ik = tbmodel->KindArray.end();
            
    while (i<nRow && isValid)
    {
        i++;
        bool isLineValid = AtomsGrid->GetCellValue(i,0).ToLong(&kind);
        isLineValid = isLineValid && AtomsGrid->GetCellValue(i,1).ToDouble(&A);
        isLineValid = isLineValid && AtomsGrid->GetCellValue(i,2).ToDouble(&B);
        isLineValid = isLineValid && AtomsGrid->GetCellValue(i,3).ToDouble(&C);
        if (isLineValid)
        {
            AtomCnt++;
            tbmodel->AArray.insert(ix,A);
            tbmodel->BArray.insert(iy,B);
            tbmodel->CArray.insert(iz,C);
            x = A * tbmodel->a[0] + B * tbmodel->b[0] + C * tbmodel->c[0];
            y = A * tbmodel->a[1] + B * tbmodel->b[1] + C * tbmodel->c[1];
            z = A * tbmodel->a[2] + B * tbmodel->b[2] + C * tbmodel->c[2];
            tbmodel->XArray.insert(ix,x);
            tbmodel->YArray.insert(iy,y);
            tbmodel->ZArray.insert(iz,z);
            tbmodel->KindArray.insert(ik,kind);
        }
        else
            isValid=false;
    }
    
    return AtomCnt;
     */
     
    //To learn
    //AtomsGrid->SetCellTextColour(3, 3, *wxGREEN);
    //AtomsGrid->SetCellBackgroundColour(3, 3, *wxLIGHT_GREY);
}


void StructureClass::OnCellChanged(wxGridEvent& event)
{
    ValidateForm();
}

void StructureClass::OnGridPaste(wxCommandEvent& event)
{
    ValidateForm();
}

void StructureClass::ValidateForm()
{
    //int nAtoms = ValidateAtoms();
    //tbmodel->nAtoms = nAtoms;
    //graph3d->DiscardAtomicStructure();
    //graph3d->CreateAtomicStructure(tbmodel);
    //graph3d->Refresh(false);
}

void StructureClass::Btn_Load_OnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Import Structure"), wxEmptyString, wxEmptyString, 
		_("CIF File (*.cif)|*.cif")
        ,wxFD_OPEN, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        //int dgFileKind = OpenDialog->GetFilterIndex();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString dgPath = OpenDialog->GetDirectory();
        
        wxString fl = dgPath + wxT("/") + dgFileName;
        
	}
 
	OpenDialog->Destroy();
}

void StructureClass::Btn_Save_OnClick(wxCommandEvent& event)
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

void StructureClass::Btn_Import_XYZ_OnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Import XYZ File"), wxEmptyString, wxEmptyString, 
		_("XYZ File (*.xyz)|*.xyz")
        ,wxFD_OPEN, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        //int dgFileKind = OpenDialog->GetFilterIndex();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString dgPath = OpenDialog->GetDirectory();
        
        wxString fl = dgPath + wxT("/") + dgFileName;
        
	}
 
	OpenDialog->Destroy();
}

void StructureClass::Btn_Export_XYZ_OnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Export XYZ File"), wxEmptyString, wxEmptyString, 
		_("XYZ File (*.xyz)|*.xyz")
        ,wxFD_SAVE, wxDefaultPosition);
    
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        //int dgFileKind = OpenDialog->GetFilterIndex();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString dgPath = OpenDialog->GetDirectory();
        ExportToXYZ(dgPath, dgFileName);
	}
 
	OpenDialog->Destroy();
}

void StructureClass::ExportToCIF(wxString filepath, wxString filename)
{
  double PI=3.14159265359;
  int i,Gc_AN,itmp;
  double tmp[4],Cxyz[4],Cell_Gxyz[4],tv[4][4],rtv[4][4];
  double lena,lenb,lenc,t1;
  double alpha,beta,gamma;
  double CellV,Cell_Volume;
  FILE *fp;
  
  //tv[1][1] = tbmodel->a[0]; tv[1][2] = tbmodel->a[1]; tv[1][3] = tbmodel->a[2];
  //tv[2][1] = tbmodel->b[0]; tv[2][2] = tbmodel->b[1]; tv[2][3] = tbmodel->b[2];
  //tv[3][1] = tbmodel->c[0]; tv[3][2] = tbmodel->c[1]; tv[3][3] = tbmodel->c[2];
  
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
  /*  
    for (Gc_AN=1; Gc_AN<=tbmodel->nAtoms; Gc_AN++){

      //The zero is taken as the origin of the unit cell

      Cxyz[1] = *ix++;
      Cxyz[2] = *iy++;
      Cxyz[3] = *iz++;
      int kind=*ik++;
      
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
      
      fprintf(fp,"A%-6d%-3s%10.5f%10.5f%10.5f%10.5f  Uiso   1.00\n", Gc_AN, (const char*)GetAtomLable(kind).mb_str(), Cell_Gxyz[1], Cell_Gxyz[2], Cell_Gxyz[3], 0.0);
    }
*/
    fclose(fp);
  }
}


void StructureClass::ExportToXYZ(wxString filepath, wxString filename)
{
  double PI=3.14159215;
  int i,j,Gc_AN,k,itmp;
  double tmp[4],Cxyz[4],Cell_Gxyz[4],tv[4][4],rtv[4][4];
  double lena,lenb,lenc,t1;
  double alpha,beta,gamma;
  double CellV,Cell_Volume;
  
  FILE *fp;
  
  //tv[1][1] = tbmodel->a[0]; tv[1][2] = tbmodel->a[1]; tv[1][3] = tbmodel->a[2];
  //tv[2][1] = tbmodel->a[0]; tv[2][2] = tbmodel->a[1]; tv[2][3] = tbmodel->a[2];
  //tv[3][1] = tbmodel->a[0]; tv[3][2] = tbmodel->a[1]; tv[3][3] = tbmodel->a[2];
  
  /********************************************
              making of a XYZ file
  *********************************************/

  wxString fname1 = filepath + wxT("/") + filename;
  if ((fp = fopen(fname1,"w")) != NULL){
/*
    fprintf(fp,"%d\n\n",tbmodel->nAtoms);

    std::list<double>::iterator ix = tbmodel->XArray.begin();
    std::list<double>::iterator iy = tbmodel->YArray.begin();
    std::list<double>::iterator iz = tbmodel->ZArray.begin();
    std::list<int>::iterator ik = tbmodel->KindArray.begin();
    
    for (Gc_AN=1; Gc_AN<=tbmodel->nAtoms; Gc_AN++)
    {
      //To use wxString in printf use one of them: GetAtomLable(kind).mb_str().data() or (const char*)GetAtomLable(kind).mb_str(),
      fprintf(fp,"%4s  %18.14f %18.14f %18.14f\n",(const char*)GetAtomLable(*ik++).mb_str(),*ix++,*iy++,*iz++);
    }
*/
    fclose(fp);
  }

}


wxString StructureClass::GetAtomLable(int kind)
{
    wxString Lable;
    switch (kind)
    {
    case 1: Lable=wxT("H"); break;
    case 2: Lable=wxT("He"); break;
    case 3: Lable=wxT("Li"); break;
    case 4: Lable=wxT("Be"); break;
    case 5: Lable=wxT("B"); break;
    case 6: Lable=wxT("C"); break;
    case 7: Lable=wxT("N"); break;
    case 8: Lable=wxT("O"); break;
    case 9: Lable=wxT("F"); break;
    case 10: Lable=wxT("Ne"); break;
    case 11: Lable=wxT("Na"); break;
    case 12: Lable=wxT("Mg"); break;
    case 13: Lable=wxT("Al"); break;
    case 14: Lable=wxT("Si"); break;
    case 15: Lable=wxT("P"); break;
    case 16: Lable=wxT("S"); break;
    case 17: Lable=wxT("Cl"); break;
    case 18: Lable=wxT("Ar"); break;
    case 19: Lable=wxT("K"); break;
    case 20: Lable=wxT("Ca"); break;
    case 21: Lable=wxT("Sc"); break;
    case 22: Lable=wxT("Ti"); break;
    case 23: Lable=wxT("V"); break;
    case 24: Lable=wxT("Cr"); break;
    case 25: Lable=wxT("Mn"); break;
    case 26: Lable=wxT("Fe"); break;
    case 27: Lable=wxT("Co"); break;
    case 28: Lable=wxT("Ni"); break;
    case 29: Lable=wxT("Cu"); break;
    case 30: Lable=wxT("Zn"); break;
    case 31: Lable=wxT("Ga"); break;
    case 32: Lable=wxT("Ge"); break;
    case 33: Lable=wxT("As"); break;
    case 34: Lable=wxT("Se"); break;
    case 35: Lable=wxT("Br"); break;
    case 36: Lable=wxT("Kr"); break;
    case 37: Lable=wxT("Rb"); break;
    case 38: Lable=wxT("Sr"); break;
    case 39: Lable=wxT("Y"); break;
    case 40: Lable=wxT("Zr"); break;
    case 41: Lable=wxT("Nb"); break;
    case 42: Lable=wxT("Mo"); break;
    case 43: Lable=wxT("Tc"); break;
    case 44: Lable=wxT("Ru"); break;
    case 45: Lable=wxT("Rh"); break;
    case 46: Lable=wxT("Pd"); break;
    case 47: Lable=wxT("Ag"); break;
    case 48: Lable=wxT("Cd"); break;
    case 49: Lable=wxT("In"); break;
    case 50: Lable=wxT("Sn"); break;
    case 51: Lable=wxT("Sb"); break;
    case 52: Lable=wxT("Te"); break;
    case 53: Lable=wxT("I"); break;
    case 54: Lable=wxT("Xe"); break;
    case 55: Lable=wxT("Cs"); break;
    case 56: Lable=wxT("Ba"); break;
    case 57: Lable=wxT("La"); break;
    case 58: Lable=wxT("Ce"); break;
    case 59: Lable=wxT("Pr"); break;
    case 60: Lable=wxT("Nd"); break;
    case 61: Lable=wxT("Pm"); break;
    case 62: Lable=wxT("Sm"); break;
    case 63: Lable=wxT("Eu"); break;
    case 64: Lable=wxT("Gd"); break;
    case 65: Lable=wxT("Tb"); break;
    case 66: Lable=wxT("Dy"); break;
    case 67: Lable=wxT("Ho"); break;
    case 68: Lable=wxT("Er"); break;
    case 69: Lable=wxT("Tm"); break;
    case 70: Lable=wxT("Yb"); break;
    case 71: Lable=wxT("Lu"); break;
    case 72: Lable=wxT("Hf"); break;
    case 73: Lable=wxT("Ta"); break;
    case 74: Lable=wxT("W"); break;
    case 75: Lable=wxT("Re"); break;
    case 76: Lable=wxT("Os"); break;
    case 77: Lable=wxT("Ir"); break;
    case 78: Lable=wxT("Pt"); break;
    case 79: Lable=wxT("Au"); break;
    case 80: Lable=wxT("Hg"); break;
    case 81: Lable=wxT("Tl"); break;
    case 82: Lable=wxT("Pb"); break;
    case 83: Lable=wxT("Bi"); break;
    case 84: Lable=wxT("Po"); break;
    case 85: Lable=wxT("At"); break;
    case 86: Lable=wxT("Rn"); break;
    case 87: Lable=wxT("Fr"); break;
    case 88: Lable=wxT("Ra"); break;
    case 89: Lable=wxT("Ac"); break;
    case 90: Lable=wxT("Th"); break;
    case 91: Lable=wxT("Pa"); break;
    case 92: Lable=wxT("U"); break;
    case 93: Lable=wxT("Np"); break;
    case 94: Lable=wxT("Pu"); break;
    case 95: Lable=wxT("Am"); break;
    case 96: Lable=wxT("Cm"); break;
    case 97: Lable=wxT("Bk"); break;
    case 98: Lable=wxT("Cf"); break;
    case 99: Lable=wxT("Es"); break;
    case 100: Lable=wxT("Fm"); break;
    case 101: Lable=wxT("Md"); break;
    case 102: Lable=wxT("No"); break;
    case 103: Lable=wxT("Lr"); break;
    case 104: Lable=wxT("Rf"); break;
    case 105: Lable=wxT("Db"); break;
    case 106: Lable=wxT("Sg"); break;
    case 107: Lable=wxT("Bh"); break;
    case 108: Lable=wxT("Hs"); break;
    case 109: Lable=wxT("Mt"); break;
    case 110: Lable=wxT("Ds"); break;
    case 111: Lable=wxT("Rg"); break;
    case 112: Lable=wxT("Cn"); break;
    case 113: Lable=wxT("Uut"); break;
    case 114: Lable=wxT("Fl"); break;
    case 115: Lable=wxT("Uup"); break;
    case 116: Lable=wxT("Lv"); break;
    case 117: Lable=wxT("Uus"); break;
    case 118: Lable=wxT("Uuo"); break;
    }
    return Lable;
}

void StructureClass::ValidateTextCtrl(wxTextCtrl c, double &value)
{

}

void StructureClass::ctr_a0_OnUpdated(wxCommandEvent& event)
{
    /*double x;
    if (ctr_a0->GetValue().ToDouble(&x))
        tbmodel->a[0] = s;
    else
        ctr_a0->SetValue(tbmodel->a[0].ToStr());*/
}

void StructureClass::ctr_a1_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_a2_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_a_strain_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_b0_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_b1_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_b2_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_b_strain_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_c0_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_c1_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_c2_OnUpdated(wxCommandEvent& event)
{
}

void StructureClass::ctr_c_strain_OnUpdated(wxCommandEvent& event)
{
}
void StructureClass::ctr_a0_OnEnter(wxCommandEvent& event)
{
}
void StructureClass::OnChar(wxKeyEvent& event)
{
}
