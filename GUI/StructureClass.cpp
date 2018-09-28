#include "StructureClass.h"

StructureClass::StructureClass(wxWindow* parent, Sec30* sec30var, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetName(wxT("StructureClass"));
    SetSize(wxDLG_UNIT(this, wxSize(-1,-1)));
    GetSizer()->Fit(this);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Display Ranges"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddRadioButton(this, _("CustomViewmode"), _("Show Custom Lattice"));
    sec30->SetRadioVar(_("CustomViewmode[0]"),true,false);
    sec30->AddVarVector(this, 2, _("ma"), _("int"), _("a range"), 70, 100);
    sec30->AddVarVector(this, 2, _("mb"), _("int"), _("b range"), 70, 100);
    sec30->AddVarVector(this, 2, _("mc"), _("int"), _("c range"), 70, 100);
    sec30->SetVar(_("ma[0]"), 0, false);
    sec30->SetVar(_("ma[1]"), 0, false);
    sec30->SetVar(_("mb[0]"), 0, false);
    sec30->SetVar(_("mb[1]"), 0, false);
    sec30->SetVar(_("mc[0]"), 0, false);
    sec30->SetVar(_("mc[1]"), 0, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("TB model Ranges (Nearest-Neighbor Unit-Cells)"),wxColour(wxT("rgb(153,180,209)")));
    sec30->AddRadioButton(this, _("TBViewmode"), _("Show TB Model"));
    sec30->AddRadioButton(this, _("TBEssentialViewmode"), _("Show TB Model Essential Unit Cells"));
    sec30->SetRadioVar(_("TBViewmode[0]"),false,false);
    sec30->SetRadioVar(_("TBEssentialViewmode[0]"),false,false);
    sec30->AddVarVector(this, 1, _("TBl"), _("int"), _("a direction"), 100, 100);
    sec30->AddVarVector(this, 1, _("TBm"), _("int"), _("b direction"), 100, 100);
    sec30->AddVarVector(this, 1, _("TBn"), _("int"), _("c direction"), 100, 100);
    sec30->SetVar(_("TBl[0]"), 1, false);
    sec30->SetVar(_("TBm[0]"), 1, false);
    sec30->SetVar(_("TBn[0]"), 0, false);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Import and Export XYZ Coordinates in Angstrom"),wxColour(wxT("rgb(153,180,209)")));
    wxString Labels2[2] = { _("Import"), _("Export")};
    wxObjectEventFunction Funcs2[2] = { wxCommandEventHandler(StructureClass::Btn_Import_XYZ_OnClick), wxCommandEventHandler(StructureClass::Btn_Export_XYZ_OnClick)};
    sec30->AddButton(this, 2, Labels2, Funcs2);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_(""),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
    sec30->AddVarVector(this, 1, _("nShowingAtoms"), _("int"));
    sec30->SetVar(_("nShowingAtoms[0]"),0, false);
    /**********************************************************************************************************************************************/
}
    
StructureClass::~StructureClass()
{
    //try{}
    //catch(std::exception& ex)
    //{wxMessageBox(ex.what());}
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