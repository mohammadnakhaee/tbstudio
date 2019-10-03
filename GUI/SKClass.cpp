#include "SKClass.h"

/******************************************************************************/
BEGIN_EVENT_TABLE(SKClass,wxPanel)
    //EVT_MENU(wxID_DELETE,SKClass::OnDelete)
END_EVENT_TABLE()
/******************************************************************************/

SKClass::SKClass(wxWindow* parent, Sec30* sec30var, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    sec30=sec30var;
    /**********************************************************************************************************************************************/
    wxBoxSizer* BaseSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(BaseSizer);
    SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    SetName(wxT("SKClass"));
    SetSize(wxDLG_UNIT(this, wxSize(-1,-1)));
    GetSizer()->Fit(this);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this, _("Setup the Parameter Vector"),wxColour(wxT("rgb(153,180,209)")));
    wxCheckBox* socCtrl = sec30->AddCheckBox(this, _("SOC"), _("Take SOC into Accounts"));
    //socCtrl->Enable(false);
    wxCheckBox* OvCtrl = sec30->AddCheckBox(this, _("Overlap"), _("Non-Orthogonal Basis"));
    //OvCtrl->Enable(false);
    wxString Labels1[1] = {_("Evaluate Independent Parameters")};
    wxObjectEventFunction Funcs1[1] = {wxCommandEventHandler(SKClass::Btn_Update_OnClick)};
    sec30->AddButton(this, 1, Labels1, Funcs1);
    /**********************************************************************************************************************************************/
    sec30->AddVarVector(this, 1, _("nParameters"), _("int"), _("Number of Parameters"), 180, 100, false, true);
    sec30->SetVar(_("nParameters[0]"), 0, false);
	/**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Tools"),wxColour(wxT("rgb(153,180,209)")));
    wxString Labels5[2] = {_("Save initial"), _("Save final")};
    wxObjectEventFunction Funcs5[2] = {wxCommandEventHandler(SKClass::Btn_ExportInit_OnClick), wxCommandEventHandler(SKClass::Btn_ExportFinal_OnClick)};
    sec30->AddButton(this, 2, Labels5, Funcs5);
	wxString Labels2[1] = {_("Use Last State as Initial Guess")};
    wxObjectEventFunction Funcs2[1] = { wxCommandEventHandler(SKClass::Btn_LastValues_OnClick)};
    sec30->AddButton(this, 1, Labels2, Funcs2);
	sec30->AddVarVector(this, 1, _("SKName"), _("wxString"), _("File Name"), 110, 120,false);
	wxString Labels3[1] = {_("Make a copy")};
    wxObjectEventFunction Funcs3[1] = { wxCommandEventHandler(SKClass::Btn_MakeACopy_OnClick)};
    sec30->AddButton(this, 1, Labels3, Funcs3);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("On-Site Energies"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
    wxString ColTypes[3] = { _("string"), _("double"), _("double")};
    int ColSizes[3] = {96, 100, 100};
    int ColPrecision[3] = { 0, 8, 8};
    sec30->AddGrid(this, 0, 3, _("OS"), ColNames, ColTypes, ColSizes, ColPrecision, 350, 400);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Slater-Koster Integrals"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames2[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
    wxString ColTypes2[3] = { _("string"), _("double"), _("double")};
    int ColSizes2[3] = {96, 100, 100};
    int ColPrecision2[3] = {0, 8, 8};
    sec30->AddGrid(this, 0, 3, _("SK"), ColNames2, ColTypes2, ColSizes2, ColPrecision2, 350, 400);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_("Overlap Integrals"),wxColour(wxT("rgb(153,180,209)")));
    wxString ColNames3[3] = { _("Parameter"), _("Initial Value"), _("Last Value")};
    wxString ColTypes3[3] = { _("string"), _("double"), _("double")};
    int ColSizes3[3] = {96, 100, 100};
    int ColPrecision3[3] = { 0, 8, 8};
    sec30->AddGrid(this, 0, 3, _("OL"), ColNames3, ColTypes3, ColSizes3, ColPrecision3, 350, 400);
    /**********************************************************************************************************************************************/
    sec30->AddGroupBox(this,_(""),wxColour(wxT("rgb(153,180,209)")));
    /**********************************************************************************************************************************************/
}

SKClass::~SKClass()
{
    //try{}
    //catch(std::exception& ex)
    //{wxMessageBox(ex.what());}
}

void SKClass::Btn_Update_OnClick(wxCommandEvent& event)
{
    sec30->SendUpdateEvent(this->GetName(),2);
}

void SKClass::Btn_LastValues_OnClick(wxCommandEvent& event)
{
    sec30->CopyLastSKToInitialSK();
    sec30->SendUpdateEvent(this->GetName());
}

void SKClass::Btn_ExportInit_OnClick(wxCommandEvent& event)
{
	wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("Text File (*.txt)|*.txt")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("txt"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        ExportSKToTXT(dgPath, BaseName, 1); // 1 means first row
	}
    
	OpenDialog->Destroy();
}

void SKClass::Btn_ExportFinal_OnClick(wxCommandEvent& event)
{
	wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Generate code"), wxEmptyString, wxEmptyString, 
		_("Text File (*.txt)|*.txt")
        ,wxFD_SAVE, wxDefaultPosition);
    
	OpenDialog->SetDirectory(sec30->WorkingDIR);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
        wxString dgPath = OpenDialog->GetDirectory();
        wxString dgFileName = OpenDialog->GetFilename();
        wxString BaseName = _("");
        if (dgFileName.AfterLast('.') == _("txt"))
            BaseName = dgFileName.BeforeLast('.');
        else
            BaseName = dgFileName;
        
        ExportSKToTXT(dgPath, BaseName, 2); // 1 means second row
	}
    
	OpenDialog->Destroy();
}

void SKClass::Btn_MakeACopy_OnClick(wxCommandEvent& event)
{
    sec30->SendUpdateEvent(this->GetName(),3);
}

void SKClass::ExportSKToTXT(wxString filepath, wxString BaseName, int InitOrFinalSK)
{
	int ind = InitOrFinalSK;
    FILE *fpk;
    wxString fname = filepath + wxT("/") + BaseName + wxT(".txt");
    if ((fpk = fopen(fname,"w")) != NULL)
    {
		fprintf(fpk,"On-Site energies\n");
		myGrid* osgc = sec30->GetGridObject(_("OS"));
		int nRowsOS = osgc->GetNumberRows();
		for (int i=0; i<nRowsOS; i++)
		{
			double d = 0.0;
			wxString var = osgc->GetCellValue(i, 0);
			wxString val = osgc->GetCellValue(i, ind);
			bool output = val.ToDouble(&d);
			if (!output) d = 0.0;
			if ( var == _(""))
				fprintf(fpk,"\n");
			else if (var.Contains(wxT("Shell")))
				fprintf(fpk,"%s\n", var.c_str().AsChar());
			else
				fprintf(fpk,"%s\t%.6f\n", var.c_str().AsChar(), d);
		}
		
		fprintf(fpk,"\n");
		fprintf(fpk,"Slater-Koster parameters for Hamiltonian\n");
		
		myGrid* skgc = sec30->GetGridObject(_("SK"));
		int nRowsSK = skgc->GetNumberRows();
		for (int i=0; i<nRowsSK; i++)
		{
			double d = 0.0;
			wxString var = skgc->GetCellValue(i, 0);
			wxString val = skgc->GetCellValue(i, ind);
			bool output = val.ToDouble(&d);
			if (!output) d = 0.0;
			if ( var == _(""))
				fprintf(fpk,"\n");
			else if (var.Contains(wxT("Bond")))
				fprintf(fpk,"%s\n", var.c_str().AsChar());
			else
				fprintf(fpk,"%s\t%.6f\n", var.c_str().AsChar(), d);
				
		}
		
		fprintf(fpk,"\n");
		fprintf(fpk,"Slater-Koster parameters for overlap matrix\n");
		
		myGrid* olgc = sec30->GetGridObject(_("OL"));
		int nRowsOL = olgc->GetNumberRows();
		for (int i=0; i<nRowsOL; i++)
		{
			double d = 0.0;
			wxString var = olgc->GetCellValue(i, 0);
			wxString val = olgc->GetCellValue(i, ind);
			bool output = val.ToDouble(&d);
			if (!output) d = 0.0;
			if ( var == _(""))
				fprintf(fpk,"\n");
			else if (var.Contains(wxT("Bond")))
				fprintf(fpk,"%s\n", var.c_str().AsChar());
			else
				fprintf(fpk,"%s\t%.6f\n", var.c_str().AsChar(), d);
		}
		
        fclose(fpk);
    }
}