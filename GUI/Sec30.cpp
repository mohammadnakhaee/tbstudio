#include "Sec30.h"


// this is a definition so can't be in a header
wxDEFINE_EVENT(Sec30EVT_OnUpdated, wxCommandEvent);

/******************************************************************************/
BEGIN_EVENT_TABLE(Sec30,wxWindow)

END_EVENT_TABLE()
/******************************************************************************/

Sec30::Sec30(wxWindow* parent)
{
    SetParent(parent);
}

void Sec30::init()
{
    int nArraysOf0DDouble = 9;
    int nArraysOf0DInt = 10;
    int nArraysOf2DInt = 3;
    int nArraysOf1DDouble = 4;
    int nArraysOf1DString = 3;
    int nArraysOf2DDouble = 5;
    int nArraysOf3DDouble = 6;
    ArraysOf0DDouble.clear();
    ArraysOf0DInt.clear();
    ArraysOf2DInt.clear();
    ArraysOf1DDouble.clear();
    ArraysOf1DString.clear();
    ArraysOf2DDouble.clear();
    ArraysOf3DDouble.clear();
    for (int i=0; i<nArraysOf0DDouble; i++) ArraysOf0DDouble.push_back(0.0);
    for (int i=0; i<nArraysOf0DInt; i++) ArraysOf0DInt.push_back(0);
    for (int i=0; i<nArraysOf2DInt; i++) ArraysOf2DInt.push_back(Aint1D());
    for (int i=0; i<nArraysOf1DDouble; i++) ArraysOf1DDouble.push_back(Adouble0D());
    for (int i=0; i<nArraysOf1DString; i++) ArraysOf1DString.push_back(Astring0D());
    for (int i=0; i<nArraysOf2DDouble; i++) ArraysOf2DDouble.push_back(Adouble1D());
    for (int i=0; i<nArraysOf3DDouble; i++) ArraysOf3DDouble.push_back(Adouble2D());
    /////////////////////////////0D Int///////////////////////////////////////////////////////
    ArraysOf0DInt[0] = 0;//bool isBandLoaded;
    ArraysOf0DInt[1] = 0;//int nKPoint;
    ArraysOf0DInt[2] = 0;//int maxneig;
    ArraysOf0DInt[3] = 0;//int mspin;
    ArraysOf0DInt[4] = 0;//int DFTnBandMin;
    ArraysOf0DInt[5] = 0;//int DFTnBandMax;
    ArraysOf0DInt[6] = 0;//bool isSelectMode;
    ArraysOf0DInt[7] = 0;//bool isTBBand_i;
    ArraysOf0DInt[8] = 0;//bool isTBBand_f;
    ArraysOf0DInt[9] = 0;//bool notUsed
    
    /////////////////////////////2D Int///////////////////////////////////////////////////////
    ArraysOf2DInt[0] = Aint1D();//int** HamiltonianDimMap;
    ArraysOf2DInt[1] = Aint1D();//int** SKListInfo;
    ArraysOf2DInt[2] = Aint1D();//int** FitPoints;
    
    /////////////////////////////0D Double///////////////////////////////////////////////////////
    ArraysOf0DDouble[0] = 0.0;//double ChemP;
    ArraysOf0DDouble[1] = 0.0;//double DFTyMin2d0;
    ArraysOf0DDouble[2] = 0.0;//double DFTyMax2d0;
    ArraysOf0DDouble[3] = 0.0;//double DFTyMin2d;
    ArraysOf0DDouble[4] = 0.0;//double DFTyMax2d;
    ArraysOf0DDouble[5] = 0.0;//double DFTxMin2d0;
    ArraysOf0DDouble[6] = 0.0;//double DFTxMax2d0;
    ArraysOf0DDouble[7] = 0.0;//double DFTxMin2d;
    ArraysOf0DDouble[8] = 0.0;//double DFTxMax2d;
    
    /////////////////////////////1D Double///////////////////////////////////////////////////////
    ArraysOf1DDouble[0] = Adouble0D();//double* dkLabel;
    ArraysOf1DDouble[1] = Adouble0D();//double akDFT[3];
    ArraysOf1DDouble[2] = Adouble0D();//double bkDFT[3];
    ArraysOf1DDouble[3] = Adouble0D();//double ckDFT[3];
    
    /////////////////////////////1D String///////////////////////////////////////////////////////
    ArraysOf1DString[0] = Astring0D();//wxString* kLabel;
    ArraysOf1DString[1] = Astring0D();//wxString* HamiltonianMap;
    ArraysOf1DString[2] = Astring0D();//wxString* HamiltonianShellMap;
    
    /////////////////////////////2D Double///////////////////////////////////////////////////////
    ArraysOf2DDouble[0] = Adouble1D();//double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    ArraysOf2DDouble[1] = Adouble1D();//double** DFTEigVal;
    ArraysOf2DDouble[2] = Adouble1D();//double** iTBEigVal;
    ArraysOf2DDouble[3] = Adouble1D();//double** fTBEigVal;
    ArraysOf2DDouble[4] = Adouble1D();//double** DFTEigValWeight;
    
    /////////////////////////////3D Double///////////////////////////////////////////////////////
    ArraysOf3DDouble[0] = Adouble2D();//double*** Hi; Vi_{0,0,0}, Vi_{1,0,0}, Vi_{0,1,0}, Vi_{1,1,0}, Vi_{1,-1,0}
    ArraysOf3DDouble[1] = Adouble2D();//double*** Hf; Vf_{0,0,0}, Vf_{1,0,0}, Vf_{0,1,0}, Vf_{1,1,0}, Vf_{1,-1,0}
    ArraysOf3DDouble[2] = Adouble2D();//double*** Si; Si_{0,0,0}, Si_{1,0,0}, Si_{0,1,0}, Si_{1,1,0}, Si_{1,-1,0}
    ArraysOf3DDouble[3] = Adouble2D();//double*** Sf; Sf_{0,0,0}, Sf_{1,0,0}, Sf_{0,1,0}, Sf_{1,1,0}, Sf_{1,-1,0}
    ArraysOf3DDouble[4] = Adouble2D();//double*** SOCi; SOCi_Re, SOCi_Im
    ArraysOf3DDouble[5] = Adouble2D();//double*** SOCf; SOCf_Re, SOCf_Im
}

Sec30::~Sec30()
{
}

void Sec30::AddGroupBox(wxWindow *parent, wxString Caption, wxColour BGColor)
{
    wxPanel* p = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), wxTAB_TRAVERSAL);
    p->SetBackgroundColour(BGColor);
    parent->GetSizer()->Add(p, 0, wxALL|wxEXPAND, WXC_FROM_DIP(5));
    wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
    p->SetSizer(vsizer);
    wxStaticText* st = new wxStaticText(p, wxID_ANY, Caption, wxDefaultPosition, wxDLG_UNIT(p, wxSize(-1,-1)), 0);
    vsizer->Add(st, 0, wxLEFT, WXC_FROM_DIP(5));
    st->SetForegroundColour(*wxBLACK);
}

wxStaticText* Sec30::AddGroupBox(wxWindow *parent, wxString name, wxString Caption, wxColour BGColor)
{
    wxPanel* p = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), wxTAB_TRAVERSAL);
    p->SetBackgroundColour(BGColor);
    parent->GetSizer()->Add(p, 0, wxALL|wxEXPAND, WXC_FROM_DIP(5));
    wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
    p->SetSizer(vsizer);
    wxStaticText* st = new wxStaticText(p, wxID_ANY, Caption, wxDefaultPosition, wxDLG_UNIT(p, wxSize(-1,-1)), 0);
    vsizer->Add(st, 0, wxLEFT, WXC_FROM_DIP(5));
    st->SetName(name);
    st->SetForegroundColour(*wxBLACK);
    return st;
}

void Sec30::AddButton(wxWindow *parent, int ButtonCnt, wxString* Labels, wxObjectEventFunction* Funcs)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxEXPAND, WXC_FROM_DIP(5));
    for (int i=0; i < ButtonCnt; i++)
    {
        wxButton* btn = new wxButton(parent, wxID_ANY, Labels[i], wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
        btn->SetForegroundColour(*wxBLACK);
        MySizer->Add(btn, 1, wxALL|wxEXPAND, WXC_FROM_DIP(5));
        btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, Funcs[i], NULL, parent);
    }
}

void Sec30::AddButton(wxWindow *parent, int ButtonCnt, wxString* ButtonNames, wxString* Labels, wxObjectEventFunction* Funcs)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxEXPAND, WXC_FROM_DIP(5));
    for (int i=0; i < ButtonCnt; i++)
    {
        wxButton* btn = new wxButton(parent, wxID_ANY, Labels[i], wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
        btn->SetForegroundColour(*wxBLACK);
        MySizer->Add(btn, 1, wxALL|wxEXPAND, WXC_FROM_DIP(5));
        btn->SetName(ButtonNames[i]);
        btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, Funcs[i], NULL, parent);
    }
}

void Sec30::AddVarVector(wxWindow *parent, int VecCnt, wxString VariableName, wxString VariableType, wxString VecLabel, int LabelSize, int CtrlSize,bool EnableEvent, bool ReadOnly)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, VecLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
    st->SetForegroundColour(*wxBLACK);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator ivar = vars.end();
    
    for (int i=0; i < VecCnt; i++)
    {
        sec30TextCtrl* tc=new sec30TextCtrl(parent, wxID_ANY, VariableType, wxDefaultPosition, wxSize(CtrlSize,-1), ReadOnly);
        MySizer->Add(tc, 0, wxRIGHT, WXC_FROM_DIP(5));
        tc->SetMinSize(wxSize(CtrlSize,-1));
        
        wxString var = wxString::Format(wxT("%s[%d]"), VariableName, i);
        vars.insert(ivar,var);
        tc->SetName(var);
        //tc->SetColLabelValue(0,VariableType);
        if (VariableType != _("wxString")) tc->SetCellValue(0,0,_("0"));
        if (EnableEvent) tc->Connect(Sec30EVT_Grid_Updated, wxCommandEventHandler(Sec30::sec30TextCtrl_OnUpdated), NULL, this);
    }
    
    MySizer->Layout();
    parent->Layout();
}

void Sec30::AddVarVector(wxWindow *parent, int VecCnt, wxString VariableName, wxString VariableType)
{
    std::list<wxString>::iterator ivar = vars.end();
    
    for (int i=0; i < VecCnt; i++)
    {
        sec30TextCtrl* tc=new sec30TextCtrl(parent, wxID_ANY, VariableType, wxDefaultPosition, wxSize(0,0));
        tc->SetParent(parent);
        tc->Show(false);
        
        wxString var = wxString::Format(wxT("%s[%d]"), VariableName, i);
        vars.insert(ivar,var);
        tc->SetName(var);
        if (VariableType != _("wxString")) tc->SetCellValue(0,0,_("0"));
        //tc->Connect(Sec30EVT_Grid_Updated, wxCommandEventHandler(Sec30::sec30TextCtrl_OnUpdated), NULL, this);
    }
    parent->Layout();
}

myGrid* Sec30::AddGrid(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColNames, wxString* ColTypes, int* ColSizes, int* ColPrecision, int xCtrlSize, int yCtrlSize, bool EnableEvent)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    std::list<wxString>::iterator igrid = grids.end();
    
    myGrid* gc=new myGrid(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(xCtrlSize,yCtrlSize)),wxFULL_REPAINT_ON_RESIZE|wxHSCROLL|wxVSCROLL);
    MySizer->Add(gc, 0, wxRIGHT, WXC_FROM_DIP(5));
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
            gc->SetCellAlignment(j, i, wxALIGN_LEFT,wxALIGN_CENTRE);
    }
    
    for (int i=0; i< nRow; i++) gc->DisableRowResize(i);
    
    grids.insert(igrid,VariableName);
    
    wxColour c; //Also it is possible to determine the color in this way: wxColour c=*wxGREEN;
    c.Set(191,205,219,255);
    gc->SetLabelBackgroundColour(c);
    gc->SetColLabelSize(20);
    gc->SetRowLabelSize(35);
    gc->SetColMinimalAcceptableWidth(1);
    
    if (EnableEvent) gc->Connect(Sec30EVT_Grid_Updated, wxCommandEventHandler(Sec30::sec30TextCtrl_OnUpdated), NULL, this);
    
    //gc->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Sec30::TextCtrl_OnUpdated), NULL, this);
    //gc->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(StructureClass::OnCellChanged), NULL, this);
    //gc->Connect(MyGridPasteEvent, wxCommandEventHandler(StructureClass::OnGridPaste), NULL, this);

    MySizer->Layout();
    parent->Layout();
	return gc;
}

void Sec30::AddGrid(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColTypes, int* ColPrecision)
{
    std::list<wxString>::iterator igrid = grids.end();
    
    myGrid* gc=new myGrid(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(0,0)),0);
    gc->Show(false);
    gc->SetName(VariableName);
    gc->CreateGrid( nRow, nCol);
    for (int i=0; i< nCol; i++)
    {
        if (ColTypes[i]=="int")
            gc->SetColFormatNumber(i);
        else if (ColTypes[i]=="double")
            gc->SetColFormatFloat(i,-1,ColPrecision[i]);
    }
    grids.insert(igrid,VariableName);
    //gc->Connect(Sec30EVT_Grid_Updated, wxCommandEventHandler(Sec30::sec30TextCtrl_OnUpdated), NULL, this);
    parent->Layout();
}

void Sec30::AddRadioButton(wxWindow *parent, wxString VariableName, wxString Label)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    std::list<wxString>::iterator ivar = radios.end();
    
    wxRadioButton* ctr=new wxRadioButton(parent, wxID_ANY, Label, wxDefaultPosition, wxSize(-1,-1));
    //ctr->SetBackgroundColour(*wxGRAY);
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    
    wxString var = wxString::Format(wxT("%s[%d]"), VariableName, 0);
    radios.insert(ivar,var);
    ctr->SetName(var);
    ctr->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(Sec30::MyRadioSelected), NULL, this);
    
    MySizer->Layout();
    parent->Layout();
}

wxCheckBox* Sec30::AddCheckBox(wxWindow *parent, wxString VariableName, wxString Label)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    std::list<wxString>::iterator ichecks = checks.end();
    
    wxCheckBox* ctr=new wxCheckBox(parent, wxID_ANY, Label, wxDefaultPosition, wxSize(-1,-1));
    ctr->SetValue(false);
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    
    wxString var = wxString::Format(wxT("%s[%d]"), VariableName, 0);
    checks.insert(ichecks,var);
    ctr->SetName(var);
    ctr->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(Sec30::MyCheckBoxSelected), NULL, this);
    
    MySizer->Layout();
    parent->Layout();
    return ctr;
}

wxCheckTree* Sec30::AddTreeCtrl(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize, bool EnableEvent)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    std::list<wxString>::iterator itrees = trees.end();
    
    wxCheckTree* ctr=new wxCheckTree(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(xCtrlSize,yCtrlSize)),wxTR_DEFAULT_STYLE|wxFULL_REPAINT_ON_RESIZE|wxTR_EDIT_LABELS); //wxTR_HIDE_ROOT //wxNO_BORDER
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(xCtrlSize,yCtrlSize));
    trees.insert(itrees,VariableName);
    ctr->SetName(VariableName);
    
    wxColour c; //Also it is possible to determine the color in this way: wxColour c=*wxGREEN;
    c.Set(191,205,219,255);
    
    if (EnableEvent)
    {
        ctr->Connect(wxEVT_COMMAND_TREE_DELETE_ITEM, wxTreeEventHandler(Sec30::TreeCtrlDeleteItem), NULL, this);
        //ctr->Connect(wxEVT_CHECKTREE_CHOICE, wxCommandEventHandler(Sec30::TreeCtrlLeftClick), NULL, this);
        ctr->Connect(CHECKTREE_CheckChanged, wxCommandEventHandler(Sec30::TreeCtrlLeftClick), NULL, this);
    }
    ctr->ExpandAll();
    MySizer->Layout();
    parent->Layout();
    
    return ctr;
}

wxChoice* Sec30::AddChoiceCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, int LabelSize, int CtrlSize, bool EnableEvent)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, MyLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
    st->SetForegroundColour(*wxBLACK);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator ichoices = choices.end();
    
    wxArrayString empty;
    wxChoice* ctr=new wxChoice(parent, wxID_ANY, wxDefaultPosition, wxSize(CtrlSize,-1), empty, 0);
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(CtrlSize,-1));
    
    choices.insert(ichoices,VariableName);
    ctr->SetName(VariableName);
    
    if (EnableEvent) ctr->Connect(wxEVT_CHOICE, wxCommandEventHandler(Sec30::Choice_OnChanged), NULL, this);
    
    MySizer->Layout();
    parent->Layout();
    return ctr;
}

wxComboBox* Sec30::AddComboCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, int LabelSize, int CtrlSize, bool EnableEvent)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, MyLabel + wxT(":      "), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
    st->SetForegroundColour(*wxBLACK);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    st->SetName(_("LOf") + VariableName);
    
    std::list<wxString>::iterator icombos = combos.end();
    
    wxArrayString empty;
    wxComboBox* ctr=new wxComboBox(parent, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(CtrlSize,-1)), empty, 0);
    ctr->SetHint(wxT(""));
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(CtrlSize,-1));
    
    combos.insert(icombos,VariableName);
    ctr->SetName(VariableName);
    
    if (EnableEvent) ctr->Connect(wxEVT_COMBOBOX, wxCommandEventHandler(Sec30::ComboBox_OnChanged), NULL, this);
    
    MySizer->Layout();
    parent->Layout();
    return ctr;
}

wxColourPickerCtrl* Sec30::AddColorCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, wxColour color, int LabelSize, int CtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, MyLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
    st->SetForegroundColour(*wxBLACK);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator icolors = colors.end();
    
    wxColourPickerCtrl* ctr = new wxColourPickerCtrl(parent, wxID_ANY, color, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(CtrlSize,-1)), wxCLRP_DEFAULT_STYLE);
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(CtrlSize,-1));
    
    colors.insert(icolors,VariableName);
    ctr->SetName(VariableName);
    
    ctr->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(Sec30::PickerChangeColor), NULL, this);
    
    MySizer->Layout();
    parent->Layout();
    return ctr;
}
    
wxScrolledWindow* Sec30::AddScrolledPanel(wxWindow *parent, int xCtrlSize, int yCtrlSize, long style)
{
    wxScrolledWindow* ctr = new wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(xCtrlSize,yCtrlSize)), style);
    ctr->SetScrollRate(5, 5);
    parent->GetSizer()->Add(ctr, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(xCtrlSize,yCtrlSize));
    wxBoxSizer* MySizer = new wxBoxSizer(wxVERTICAL);
    ctr->SetSizer(MySizer,true);
    ctr->SetName(parent->GetName());
    
    parent->Layout();
    return ctr;
}

wxCheckListBox* Sec30::AddCheckListBox(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    std::list<wxString>::iterator ichecklists = checklists.end();
    
    wxArrayString listBoxArr;
    wxCheckListBox* ctr=new wxCheckListBox(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(xCtrlSize,yCtrlSize)),listBoxArr,wxLB_SINGLE); //wxTR_HIDE_ROOT
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(xCtrlSize,yCtrlSize));
    checklists.insert(ichecklists,VariableName);
    ctr->SetName(VariableName);
    return ctr;
}

wxListBox* Sec30::AddListBox(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    std::list<wxString>::iterator ilists = lists.end();
    
    wxArrayString listBoxArr;
    wxListBox* ctr=new wxListBox(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(xCtrlSize,yCtrlSize)),listBoxArr,wxLB_SINGLE); //wxTR_HIDE_ROOT
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(xCtrlSize,yCtrlSize));
    lists.insert(ilists,VariableName);
    ctr->SetName(VariableName);
    return ctr;
}

void Sec30::GetDim(wxString VariableName, int& nRow, int& nCol)
{
    myGrid* gridobj = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    nRow = gridobj->GetNumberRows();
    nCol = gridobj->GetNumberCols();
}

void Sec30::sec30TextCtrl_OnUpdated(wxCommandEvent& event)
{
    wxTextCtrl* tc= (wxTextCtrl*)event.GetEventObject();
    //wxString type = tc->GetHint();
    wxString name = tc->GetParent()->GetName();
    //wxString value = tc->GetValue();
    //logfile->AppendText(_("sec30:388 TextCtrl_OnUpdated")+wxString::Format(wxT(" %s"),name));
    SendUpdateEvent(name);
}

void Sec30::TreeCtrlDeleteItem(wxTreeEvent& event)
{
    wxCheckTree* tc= (wxCheckTree*)event.GetEventObject();
    wxString name = tc->GetParent()->GetName();
    //logfile->AppendText(_("sec30:398 TreeCtrlDeleteItem")+wxString::Format(wxT(" %s"),name));
    SendUpdateEvent(name);
}

void Sec30::TreeCtrlLeftClick(wxCommandEvent& event)
{
    wxCheckTree* tc= (wxCheckTree*)event.GetEventObject();
    wxString name = tc->GetParent()->GetName();
    //logfile->AppendText(_("sec30:406 TreeCtrlLeftClick"+wxString::Format(wxT(" %s"),name)));
    SendUpdateEvent(name);
}

void Sec30::Choice_OnChanged(wxCommandEvent& event)
{
    wxChoice* tc= (wxChoice*)event.GetEventObject();
    //wxString type = tc->GetHint();
    wxString name = tc->GetParent()->GetName();
    //wxString value = tc->GetValue();
    //logfile->AppendText(_("sec30:398 Choice_OnChanged")+wxString::Format(wxT(" %s"),name));
    SendUpdateEvent(name);
}

void Sec30::ComboBox_OnChanged(wxCommandEvent& event)
{
    wxComboBox* tc= (wxComboBox*)event.GetEventObject();
    //wxString type = tc->GetHint();
    wxString name = tc->GetParent()->GetName();
    //wxString value = tc->GetValue();
    //logfile->AppendText(_("sec30:424 ComboBox_OnChanged")+wxString::Format(wxT(" %s"),name));
    SendUpdateEvent(name);
}

void Sec30::PickerChangeColor(wxColourPickerEvent& event)
{
    wxColourPickerCtrl* tc= (wxColourPickerCtrl*)event.GetEventObject();
    wxString name = tc->GetParent()->GetName();
    //logfile->AppendText(_("sec30:433 PickerChangeColor")+wxString::Format(wxT(" %s"),name));
    SendUpdateEvent(name);
}

void Sec30::MyRadioSelected(wxCommandEvent& event)
{
    wxRadioButton* ctr= (wxRadioButton*)event.GetEventObject();
    wxString name = ctr->GetParent()->GetName();
    //logfile->AppendText(_("sec30:441 MyRadioSelected")+wxString::Format(wxT(" %s"),name));
    SendUpdateEvent(name);
}

void Sec30::MyCheckBoxSelected(wxCommandEvent& event)
{
    wxCheckBox* ctr= (wxCheckBox*)event.GetEventObject();
    wxString name = ctr->GetParent()->GetName();
    //logfile->AppendText(_("sec30:447 MyCheckBoxSelected")+wxString::Format(wxT(" %s"),name));
    SendUpdateEvent(name);
}

void Sec30::SendUpdateEvent(wxString info, int MyID)
{
    wxCommandEvent* event = new wxCommandEvent(Sec30EVT_OnUpdated);
    //event->SetEventObject(this);
    event->SetString(info);
    event->SetInt(MyID);
    //logfile->AppendText(_("sec30:454 SendUpdateEvent"));

    wxQueueEvent(this,event);
}

void Sec30::SetVar(wxString VariableName, double Value, bool FireEvent)
{
    wxString val = wxString::Format(wxT("%.8f"), Value);
    sec30TextCtrl* ctr = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    ctr->SetCellValue(0,0,val);
    if (FireEvent)
    {
        wxString name = ctr->GetParent()->GetName();
        SendUpdateEvent(name);
    }
}

void Sec30::SetVar(wxString VariableName, int Value, bool FireEvent)
{
    wxString val = wxString::Format(wxT("%d"), Value);
    sec30TextCtrl* ctr = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    ctr->SetCellValue(0,0,val);
    if (FireEvent)
    {
        wxString name = ctr->GetParent()->GetName();
        SendUpdateEvent(name);
    }
}

void Sec30::SetVar(wxString VariableName, bool Value, bool FireEvent)
{
    int b = 0;
    if (Value) b=1;
    wxString val = wxString::Format(wxT("%d"), b);
    sec30TextCtrl* ctr = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    ctr->SetCellValue(0,0,val);
    if (FireEvent)
    {
        wxString name = ctr->GetParent()->GetName();
        SendUpdateEvent(name);
    }
}

void Sec30::SetVar(wxString VariableName, wxString Value, bool FireEvent)
{
    sec30TextCtrl* ctr = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    ctr->SetCellValue(0,0,Value);
    if (FireEvent)
    {
        wxString name = ctr->GetParent()->GetName();
        SendUpdateEvent(name);
    }
}

bool Sec30::GetVar(wxString VariableName, double& Value)
{
    double d = 0.0;
    wxString val = ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->GetCellValue(0,0);
    bool output = val.ToDouble(&d);
    if (output) Value = d;
    return output;
}

bool Sec30::GetVar(wxString VariableName, int& Value)
{
    long l = 0;
    wxString val = ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->GetCellValue(0,0);
    bool output = val.ToLong(&l);
    if (output) Value = (int)l;
    return output;
}

bool Sec30::GetVar(wxString VariableName, bool& Value)
{
    int IntValue = 0;
    bool output = GetVar(VariableName, IntValue);
    if (output)
    {
        Value = true;
        if (IntValue == 0) Value = false;
    }
    return output;
}

bool Sec30::GetVar(wxString VariableName, wxString& Value)
{
    Value = ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->GetCellValue(0,0);
    return true;
}

void Sec30::SetVar(wxString VariableName, int iRow, int iCol, double Value, bool FireEvent)
{
    wxString val = wxString::Format(wxT("%.8f"), Value);
    sec30TextCtrl* ctr = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    ctr->SetCellValue(iRow, iCol, val);
    if (FireEvent)
    {
        wxString name = ctr->GetParent()->GetName();
        SendUpdateEvent(name);
    }
}

void Sec30::SetVar(wxString VariableName, int iRow, int iCol, int Value, bool FireEvent)
{
    wxString val = wxString::Format(wxT("%d"), Value);
    sec30TextCtrl* ctr = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    ctr->SetCellValue(iRow, iCol, val);
    if (FireEvent)
    {
        wxString name = ctr->GetParent()->GetName();
        SendUpdateEvent(name);
    }
}

void Sec30::SetVar(wxString VariableName, int iRow, int iCol, bool Value, bool FireEvent)
{
    int b = 0;
    if (Value) b=1;
    wxString val = wxString::Format(wxT("%d"), b);
    sec30TextCtrl* ctr = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    ctr->SetCellValue(iRow, iCol, val);
    if (FireEvent)
    {
        wxString name = ctr->GetParent()->GetName();
        SendUpdateEvent(name);
    }
}

void Sec30::SetVar(wxString VariableName, int iRow, int iCol, wxString Value, bool FireEvent)
{
    sec30TextCtrl* ctr = (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    ctr->SetCellValue(iRow, iCol, Value);
    if (FireEvent)
    {
        wxString name = ctr->GetParent()->GetName();
        SendUpdateEvent(name);
    }
}

bool Sec30::GetVar(wxString VariableName, int iRow, int iCol, double& Value)
{
    double d = 0.0;
    wxString val = ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->GetCellValue(iRow, iCol);
    bool output = val.ToDouble(&d);
    if (output) Value = d;
    return output;
}

bool Sec30::GetVar(wxString VariableName, int iRow, int iCol, int& Value)
{
    long l = 0;
    wxString val = ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->GetCellValue(iRow, iCol);
    bool output = val.ToLong(&l);
    if (output) Value = (int)l;
    return output;
}

bool Sec30::GetVar(wxString VariableName, int iRow, int iCol, bool& Value)
{
    int IntValue = 0;
    bool output = GetVar(VariableName, iRow, iCol, IntValue);
    if (output)
    {
        Value = true;
        if (IntValue == 0) Value = false;
    }
    return output;
}

bool Sec30::GetVar(wxString VariableName, int iRow, int iCol, wxString& Value)
{
    Value = ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->GetCellValue(iRow, iCol);
    return true;
}

void Sec30::SetRadioVar(wxString VariableName, bool Value, bool FireEvent)
{
    ((wxRadioButton*)FindWindowByName(VariableName,GetParent()))->SetValue(Value);
    if (FireEvent) SendUpdateEvent(VariableName);
}

void Sec30::GetRadioVar(wxString VariableName, bool& Value)
{
    Value = ((wxRadioButton*)FindWindowByName(VariableName,GetParent()))->GetValue();
}

void Sec30::SetCheckVar(wxString VariableName, bool Value, bool FireEvent)
{
    ((wxCheckBox*)FindWindowByName(VariableName,GetParent()))->SetValue(Value);
    if (FireEvent) SendUpdateEvent(VariableName);
}

void Sec30::GetCheckVar(wxString VariableName, bool& Value)
{
    Value = ((wxCheckBox*)FindWindowByName(VariableName,GetParent()))->GetValue();
}

wxButton* Sec30::GetButtonObject(wxString VariableName)
{
    wxButton* ctr= (wxButton*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

wxCheckBox* Sec30::GetCheckObject(wxString VariableName)
{
    wxCheckBox* ctr= (wxCheckBox*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

wxCheckTree* Sec30::GetTreeObject(wxString VariableName)
{
    wxCheckTree* ctr= (wxCheckTree*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

wxCheckListBox* Sec30::GetCheckListObject(wxString VariableName)
{
    wxCheckListBox* ctr= (wxCheckListBox*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

wxListBox* Sec30::GetListObject(wxString VariableName)
{
    wxListBox* ctr= (wxListBox*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

wxChoice* Sec30::GetChoiceObject(wxString VariableName)
{
    wxChoice* ctr= (wxChoice*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

wxComboBox* Sec30::GetComboObject(wxString VariableName)
{
    wxComboBox* ctr= (wxComboBox*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

wxStaticText* Sec30::GetComboLabelObject(wxString VariableName)
{
    wxStaticText* ctr= (wxStaticText*)FindWindowByName(_("LOf") + VariableName,GetParent());
    return ctr;
}

wxStaticText* Sec30::GetStaticTextObject(wxString VariableName)
{
    wxStaticText* ctr= (wxStaticText*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

wxColourPickerCtrl* Sec30::GetColorObject(wxString VariableName)
{
    wxColourPickerCtrl* ctr= (wxColourPickerCtrl*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

myGrid* Sec30::GetGridObject(wxString VariableName)
{
    myGrid* ctr= (myGrid*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

sec30TextCtrl* Sec30::GetTextCtrlObject(wxString VariableName)
{
    sec30TextCtrl* ctr= (sec30TextCtrl*)FindWindowByName(VariableName,GetParent());
    return ctr;
}
 
void Sec30::SaveToFile(wxString filepath, wxString filename)
{
    wxString fname1 = filepath + wxFileName::GetPathSeparator() + filename;
    std::ofstream out(fname1.ToStdString(), std::ios::out | std::ios::binary);
    
    if (out.is_open())
    {
        int n = 0;
        std::list<wxString>::iterator is;
        wxString VariableName;
        wxString val;
        
        ///////////////////////////////////////////////////////////////
        n = vars.size();
        out.write((char *) &n, sizeof n);
        
        for(is=vars.begin(); is!= vars.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            GetVar(VariableName, val);
            len = val.size();
            out.write((char *)&len, sizeof len);
            out.write(val.c_str(), len);
        }
        ///////////////////////////////////////////////////////////////
        n = grids.size();
        out.write((char *) &n, sizeof n);
        
        for(is=grids.begin(); is!= grids.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            myGrid* gc = GetGridObject(VariableName);
            int nRow = gc->GetNumberRows();
            int nCol = gc->GetNumberCols();
            out.write((char *) &nRow, sizeof nRow);
            out.write((char *) &nCol, sizeof nCol);
            
            for (int irow=0; irow<nRow;irow++)
                for (int icol=0; icol<nCol; icol++)
                {
                    GetVar(VariableName, irow, icol, val);
                    len = val.size();
                    out.write((char *)&len, sizeof len);
                    out.write(val.c_str(), len);
                    bool isreadonly = gc->IsReadOnly(irow, icol);
                    out.write((char *)&isreadonly, sizeof isreadonly);
                }
        }
        ///////////////////////////////////////////////////////////////
        n = radios.size();
        out.write((char *) &n, sizeof n);
        
        bool boolval;
        for(is=radios.begin(); is!= radios.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            GetRadioVar(VariableName, boolval);
            out.write((char *)&boolval, sizeof boolval);
        }
        ///////////////////////////////////////////////////////////////
        n = checks.size();
        out.write((char *) &n, sizeof n);
        
        for(is=checks.begin(); is!= checks.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            GetCheckVar(VariableName, boolval);
            out.write((char *)&boolval, sizeof boolval);
        }
        ///////////////////////////////////////////////////////////////
        n = trees.size();
        out.write((char *) &n, sizeof n);
        
        for(is=trees.begin(); is!= trees.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            wxCheckTree* ctr = ((wxCheckTree*)FindWindowByName(VariableName,GetParent()));
            int nItems = ctr->GetItemCount();
            out.write((char *) &nItems, sizeof nItems);
            
            wxString itemname;
            wxString diritemname;
            int itemstate;
            //int itemData;
            
            std::stack<wxTreeItemId> items;
            wxTreeItemId rootID = ctr->GetRootItem();
            if (rootID.IsOk())
            {
                items.push(rootID);
                itemname = ctr->GetItemText(rootID);
                len = itemname.size();
                out.write((char *)&len, sizeof len);
                out.write(itemname.c_str(), len);
                
                itemstate = ctr->GetItemState(rootID);
                out.write((char *) &itemstate, sizeof itemstate);
                
                //CheckTreeItemData* data = (CheckTreeItemData*)ctr->GetItemData(rootID);
                //itemData = data->Index;
                //out.write((char *) &itemData, sizeof itemData);
            }
            
            while (!items.empty())
            {
                wxTreeItemId next = items.top();
                items.pop();
                
                wxTreeItemIdValue cookie;
                wxTreeItemId nextChild = ctr->GetFirstChild(next, cookie);
                while (nextChild.IsOk())
                {
                    items.push(nextChild);
                    //parentitemname = ctr->GetItemText(ctr->GetItemParent(nextChild));
                    diritemname = ctr->MyDIR(rootID, nextChild);
                    len = diritemname.size();
                    out.write((char *)&len, sizeof len);
                    out.write(diritemname.c_str(), len);
                    
                    itemname = ctr->GetItemText(nextChild);
                    len = itemname.size();
                    out.write((char *)&len, sizeof len);
                    out.write(itemname.c_str(), len);
                    
                    itemstate = ctr->GetItemState(nextChild);
                    out.write((char *) &itemstate, sizeof itemstate);
                    
                    //CheckTreeItemData* data = (CheckTreeItemData*)ctr->GetItemData(nextChild);
                    //itemData = data->Index;
                    //out.write((char *) &itemData, sizeof itemData);
                
                    nextChild = ctr->GetNextSibling(nextChild);
                }
            }
        }
        ///////////////////////////////////////////////////////////////
        n = checklists.size();
        out.write((char *) &n, sizeof n);
        
        for(is=checklists.begin(); is!= checklists.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            wxCheckListBox* ctr = ((wxCheckListBox*)FindWindowByName(VariableName,GetParent()));
            int nItems = ctr->GetCount();
            out.write((char *) &nItems, sizeof nItems);
            
            for (int i=0; i<nItems; i++)
            {
                wxString itemname= ctr->GetString(i);
                len = itemname.size();
                out.write((char *)&len, sizeof len);
                out.write(itemname.c_str(), len);
                
                boolval = ctr->IsChecked(i);
                out.write((char *)&boolval, sizeof boolval);
            }
        }
        ///////////////////////////////////////////////////////////////
        n = lists.size();
        out.write((char *) &n, sizeof n);
        
        for(is=lists.begin(); is!= lists.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            wxListBox* ctr = ((wxListBox*)FindWindowByName(VariableName,GetParent()));
            int nItems = ctr->GetCount();
            out.write((char *) &nItems, sizeof nItems);
            
            for (int i=0; i<nItems; i++)
            {
                wxString itemname= ctr->GetString(i);
                len = itemname.size();
                out.write((char *)&len, sizeof len);
                out.write(itemname.c_str(), len);
            }
        }
        ///////////////////////////////////////////////////////////////
        n = choices.size();
        out.write((char *) &n, sizeof n);
        
        for(is=choices.begin(); is!= choices.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            wxChoice* ctr = ((wxChoice*)FindWindowByName(VariableName,GetParent()));
            int nItems = ctr->GetCount();
            out.write((char *) &nItems, sizeof nItems);
            
            for (int i=0; i<nItems; i++)
            {
                wxString itemname= ctr->GetString(i);
                len = itemname.size();
                out.write((char *)&len, sizeof len);
                out.write(itemname.c_str(), len);
            }
            int nselect = ctr->GetSelection();
            out.write((char *) &nselect, sizeof nselect);
        }
        ///////////////////////////////////////////////////////////////
        n = combos.size();
        out.write((char *) &n, sizeof n);
        
        for(is=combos.begin(); is!= combos.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            wxStaticText* LabelCtr = GetComboLabelObject(VariableName);
            wxString LabelString = LabelCtr->GetLabel();
            size_t len2 = LabelString.size();
            out.write((char *)&len2, sizeof len2);
            out.write(LabelString.c_str(), len2);
            
            wxComboBox* ctr = ((wxComboBox*)FindWindowByName(VariableName,GetParent()));
            int nItems = ctr->GetCount();
            out.write((char *) &nItems, sizeof nItems);
            
            for (int i=0; i<nItems; i++)
            {
                wxString itemname= ctr->GetString(i);
                len = itemname.size();
                out.write((char *)&len, sizeof len);
                out.write(itemname.c_str(), len);
            }
            int nselect = ctr->GetSelection();
            out.write((char *) &nselect, sizeof nselect);
        }
        ///////////////////////////////////////////////////////////////
        n = colors.size();
        out.write((char *) &n, sizeof n);
        
        for(is=colors.begin(); is!= colors.end(); is++)
        {
            VariableName = *is;
            size_t len = VariableName.size();
            out.write((char *)&len, sizeof len);
            out.write(VariableName.c_str(), len);
            
            wxColourPickerCtrl* ctr = ((wxColourPickerCtrl*)FindWindowByName(VariableName,GetParent()));
            wxColour c = ctr->GetColour();
            int r = c.Red();
            int g = c.Green();
            int b = c.Blue();
            int a = c.Alpha();
            out.write((char *) &r, sizeof r);
            out.write((char *) &g, sizeof g);
            out.write((char *) &b, sizeof b);
            out.write((char *) &a, sizeof a);
        }
        ///////////////////////////////////////////////////////////////
        n = ArraysOf0DInt.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int intvar = ArraysOf0DInt[i1];
            out.write((char *) &intvar, sizeof intvar);
        }
        
        n = ArraysOf1DInt.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf1DInt[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                int intvar = ArraysOf1DInt[i1][i2];
                out.write((char *) &intvar, sizeof intvar);
            }
        }
        
        n = ArraysOf2DInt.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf2DInt[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                int n3 = ArraysOf2DInt[i1][i2].size();
                out.write((char *) &n3, sizeof n3);
                for(int i3=0; i3!=n3; i3++)
                {
                    int intvar = ArraysOf2DInt[i1][i2][i3];
                    out.write((char *) &intvar, sizeof intvar);
                }
            }
        }
        
        n = ArraysOf3DInt.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf3DInt[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                int n3 = ArraysOf3DInt[i1][i2].size();
                out.write((char *) &n3, sizeof n3);
                for(int i3=0; i3!=n3; i3++)
                {
                    int n4 = ArraysOf3DInt[i1][i2][i3].size();
                    out.write((char *) &n4, sizeof n4);
                    for(int i4=0; i4!=n4; i4++)
                    {
                        int intvar = ArraysOf3DInt[i1][i2][i3][i4];
                        out.write((char *) &intvar, sizeof intvar);
                    }
                }
            }
        }
        ///////////////////////////////////////////////////////////////
        n = ArraysOf0DDouble.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            double dvar = ArraysOf0DDouble[i1];
            out.write((char *) &dvar, sizeof dvar);
        }
        
        n = ArraysOf1DDouble.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf1DDouble[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                double dvar = ArraysOf1DDouble[i1][i2];
                out.write((char *) &dvar, sizeof dvar);
            }
        }
        
        n = ArraysOf2DDouble.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf2DDouble[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                int n3 = ArraysOf2DDouble[i1][i2].size();
                out.write((char *) &n3, sizeof n3);
                for(int i3=0; i3!=n3; i3++)
                {
                    double dvar = ArraysOf2DDouble[i1][i2][i3];
                    out.write((char *) &dvar, sizeof dvar);
                }
            }
        }
        
        n = ArraysOf3DDouble.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf3DDouble[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                int n3 = ArraysOf3DDouble[i1][i2].size();
                out.write((char *) &n3, sizeof n3);
                for(int i3=0; i3!=n3; i3++)
                {
                    int n4 = ArraysOf3DDouble[i1][i2][i3].size();
                    out.write((char *) &n4, sizeof n4);
                    for(int i4=0; i4!=n4; i4++)
                    {
                        double dvar = ArraysOf3DDouble[i1][i2][i3][i4];
                        out.write((char *) &dvar, sizeof dvar);
                    }
                }
            }
        }
        ///////////////////////////////////////////////////////////////
        n = ArraysOf0DString.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            wxString var = ArraysOf0DString[i1];
            size_t len = var.size();
            out.write((char *)&len, sizeof len);
            out.write(var.c_str(), len);
        }
        
        n = ArraysOf1DString.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf1DString[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                wxString var = ArraysOf1DString[i1][i2];
                size_t len = var.size();
                out.write((char *)&len, sizeof len);
                out.write(var.c_str(), len);
            }
        }
        
        n = ArraysOf2DString.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf2DString[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                int n3 = ArraysOf2DString[i1][i2].size();
                out.write((char *) &n3, sizeof n3);
                for(int i3=0; i3!=n3; i3++)
                {
                    wxString var = ArraysOf2DString[i1][i2][i3];
                    size_t len = var.size();
                    out.write((char *)&len, sizeof len);
                    out.write(var.c_str(), len);
                }
            }
        }
        
        n = ArraysOf3DString.size();
        out.write((char *) &n, sizeof n);
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2 = ArraysOf3DString[i1].size();
            out.write((char *) &n2, sizeof n2);
            for(int i2=0; i2!=n2; i2++)
            {
                int n3 = ArraysOf3DString[i1][i2].size();
                out.write((char *) &n3, sizeof n3);
                for(int i3=0; i3!=n3; i3++)
                {
                    int n4 = ArraysOf3DString[i1][i2][i3].size();
                    out.write((char *) &n4, sizeof n4);
                    for(int i4=0; i4!=n4; i4++)
                    {
                        wxString var = ArraysOf2DString[i1][i2][i3][i4];
                        size_t len = var.size();
                        out.write((char *)&len, sizeof len);
                        out.write(var.c_str(), len);
                    }
                }
            }
        }
        ///////////////////////////////////////////////////////////////
        
        out.close();
    }

}
    
void Sec30::LoadFromFile(wxString filepath, wxString filename)
{
    wxString fname1 = filepath + wxFileName::GetPathSeparator() + filename;
    std::ifstream infile(fname1.ToStdString(), std::ios::in | std::ios::binary);
    
    if (infile.is_open())
    {
        int n = 0;
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            size_t ns2=0;
            infile.read(reinterpret_cast<char *>(&ns2), sizeof ns2);
            char* ValBuf = new char[ns2];
            for (int i = 0; i < ns2; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                ValBuf[i] = ch;
            }
            wxString Val=wxString(ValBuf,ns2);
            
            SetVar(VariableName, Val, false);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            myGrid* gc = GetGridObject(VariableName);
            int n0 = gc->GetNumberRows();
            if (n0>0) gc->DeleteRows(0,n0,true);
            
            int nRow=0;
            int nCol=0;
            infile.read(reinterpret_cast<char *>(&nRow), sizeof nRow);
            infile.read(reinterpret_cast<char *>(&nCol), sizeof nCol);
            wxColour c; //Also it is possible to determine the color in this way: wxColour c=*wxGREEN;
            c.Set(191,205,219,255);
            gc->InsertRows(0, nRow,false);
            
            for (int irow=0; irow<nRow;irow++)
                for (int icol=0; icol<nCol; icol++)
                {
                    size_t ns2=0;
                    infile.read(reinterpret_cast<char *>(&ns2), sizeof ns2);
                    char* ValBuf = new char[ns2];
                    for (int i = 0; i < ns2; i++)
                    {
                        char ch;
                        infile.read(&ch, sizeof ch);
                        ValBuf[i] = ch;
                    }
                    wxString Val=wxString(ValBuf,ns2);
                    
                    
                    bool isreadonly;
                    infile.read(reinterpret_cast<char *>(&isreadonly), sizeof isreadonly);
                    gc->SetReadOnly(irow, icol, isreadonly);
                    if (isreadonly)
                        gc->SetCellBackgroundColour(irow, icol, c);
                    else
                        gc->SetCellBackgroundColour(irow, icol, *wxWHITE);
                        
                    SetVar(VariableName, irow, icol, Val, false);
                }
            
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            bool boolval;
            infile.read(reinterpret_cast<char *>(&boolval), sizeof boolval);
            SetRadioVar(VariableName, boolval, false);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            bool boolval;
            infile.read(reinterpret_cast<char *>(&boolval), sizeof boolval);
            SetCheckVar(VariableName, boolval, false);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            wxCheckTree* ctr = ((wxCheckTree*)FindWindowByName(VariableName,GetParent()));
            ctr->DeleteAllItems();
            
            int nItems = 0;
            infile.read(reinterpret_cast<char *>(&nItems), sizeof nItems);
            
            wxString itemname;
            wxString diritemname;
            int itemstate;
            //int itemData;
            wxTreeItemId rootID;
            
            if (nItems>0)
            {
                ns1=0;
                infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                char* itemnameBuf = new char[ns1];
                for (int i = 0; i < ns1; i++)
                {
                    char ch;
                    infile.read(&ch, sizeof ch);
                    itemnameBuf[i] = ch;
                }
                itemname = wxString(itemnameBuf,ns1);
                rootID=ctr->AddRoot(itemname);
                
                infile.read(reinterpret_cast<char *>(&itemstate), sizeof itemstate);
                ctr->SetItemState(rootID,itemstate);
                
                //infile.read(reinterpret_cast<char *>(&itemData), sizeof itemData);
                //CheckTreeItemData data;
                //data.Index = itemData;
                //ctr->SetItemData(rootID, &data);
            }
            
            for (int ii=1; ii<nItems; ii++)
            {
                ns1=0;
                infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                char* itemnameBuf1 = new char[ns1];
                for (int i = 0; i < ns1; i++)
                {
                    char ch;
                    infile.read(&ch, sizeof ch);
                    itemnameBuf1[i] = ch;
                }
                diritemname = wxString(itemnameBuf1,ns1);
                
                ns1=0;
                infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                char* itemnameBuf2 = new char[ns1];
                for (int i = 0; i < ns1; i++)
                {
                    char ch;
                    infile.read(&ch, sizeof ch);
                    itemnameBuf2[i] = ch;
                }
                itemname = wxString(itemnameBuf2,ns1);
                
                infile.read(reinterpret_cast<char *>(&itemstate), sizeof itemstate);
                //Check for the same names
                wxTreeItemId parID = ctr->FindItemViaDIR(diritemname);
                bool mystate=true;
                bool mychecked=true;
                if (itemstate < 0) mystate = false;
                if (itemstate == 0) mychecked = false;
                wxTreeItemId TheNewOneID = ctr->tree_add(parID, itemname, mystate, mychecked);
                
                //infile.read(reinterpret_cast<char *>(&itemData), sizeof itemData);
                //CheckTreeItemData data;
                //data.Index = itemData;
                //ctr->SetItemData(TheNewOneID, &data);
            }
            ctr->Expand(rootID);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            wxCheckListBox* ctr = ((wxCheckListBox*)FindWindowByName(VariableName,GetParent()));
            ctr->Clear();
            
            int nItems = 0;
            infile.read(reinterpret_cast<char *>(&nItems), sizeof nItems);

            wxString itemname;
            bool itemstate;
            for (int ii=0; ii<nItems; ii++)
            {
                ns1=0;
                infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                char* itemnameBuf = new char[ns1];
                for (int i = 0; i < ns1; i++)
                {
                    char ch;
                    infile.read(&ch, sizeof ch);
                    itemnameBuf[i] = ch;
                }
                itemname = wxString(itemnameBuf,ns1);
                
                infile.read(reinterpret_cast<char *>(&itemstate), sizeof itemstate);
                
                ctr->Append(itemname);
                ctr->Check(ii,itemstate);
            }
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            wxListBox* ctr = ((wxListBox*)FindWindowByName(VariableName,GetParent()));
            ctr->Clear();
            
            int nItems = 0;
            infile.read(reinterpret_cast<char *>(&nItems), sizeof nItems);
            
            wxString itemname;
            for (int ii=0; ii<nItems; ii++)
            {
                ns1=0;
                infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                char* itemnameBuf = new char[ns1];
                for (int i = 0; i < ns1; i++)
                {
                    char ch;
                    infile.read(&ch, sizeof ch);
                    itemnameBuf[i] = ch;
                }
                itemname = wxString(itemnameBuf,ns1);
                
                ctr->Append(itemname);
            }
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            wxChoice* ctr = ((wxChoice*)FindWindowByName(VariableName,GetParent()));
            ctr->Clear();
            
            int nItems = 0;
            infile.read(reinterpret_cast<char *>(&nItems), sizeof nItems);
            
            wxString itemname;
            for (int ii=0; ii<nItems; ii++)
            {
                ns1=0;
                infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                char* itemnameBuf = new char[ns1];
                for (int i = 0; i < ns1; i++)
                {
                    char ch;
                    infile.read(&ch, sizeof ch);
                    itemnameBuf[i] = ch;
                }
                itemname = wxString(itemnameBuf,ns1);
                
                ctr->Append(itemname);
            }
            int nselect=0;
            infile.read(reinterpret_cast<char *>(&nselect), sizeof nselect);
            ctr->Select(nselect);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            size_t ns2=0;
            infile.read(reinterpret_cast<char *>(&ns2), sizeof ns2);
            char* LabelNameBuf = new char[ns2];
            for (int i = 0; i < ns2; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                LabelNameBuf[i] = ch;
            }
            wxString LabelName = wxString(LabelNameBuf,ns2);
            
            wxStaticText* labelctr = GetComboLabelObject(VariableName);
            labelctr->SetLabel(LabelName);
            
            wxComboBox* ctr = ((wxComboBox*)FindWindowByName(VariableName,GetParent()));
            ctr->Clear();
            
            int nItems = 0;
            infile.read(reinterpret_cast<char *>(&nItems), sizeof nItems);
            
            wxString itemname;
            for (int ii=0; ii<nItems; ii++)
            {
                ns1=0;
                infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                char* itemnameBuf = new char[ns1];
                for (int i = 0; i < ns1; i++)
                {
                    char ch;
                    infile.read(&ch, sizeof ch);
                    itemnameBuf[i] = ch;
                }
                itemname = wxString(itemnameBuf,ns1);
                
                ctr->Append(itemname);
            }
            int nselect=0;
            infile.read(reinterpret_cast<char *>(&nselect), sizeof nselect);
            ctr->Select(nselect);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        for(int it=0; it != n; it++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* VariableNameBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                VariableNameBuf[i] = ch;
            }
            wxString VariableName = wxString(VariableNameBuf,ns1);
            
            wxColourPickerCtrl* ctr = ((wxColourPickerCtrl*)FindWindowByName(VariableName,GetParent()));
            int r,g,b,a;
            infile.read(reinterpret_cast<char *>(&r), sizeof r);
            infile.read(reinterpret_cast<char *>(&g), sizeof g);
            infile.read(reinterpret_cast<char *>(&b), sizeof b);
            infile.read(reinterpret_cast<char *>(&a), sizeof a);
            wxColour c;
            c.Set(r, g, b, a);
            ctr->SetColour(c);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf0DInt.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int intvar;
            infile.read(reinterpret_cast<char *>(&intvar), sizeof intvar);
            ArraysOf0DInt.push_back(intvar);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf1DInt.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Aint0D aint0D;
            for(int i2=0; i2!=n2; i2++)
            {
                int intvar;
                infile.read(reinterpret_cast<char *>(&intvar), sizeof intvar);
                aint0D.push_back(intvar);
            }
            ArraysOf1DInt.push_back(aint0D);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf2DInt.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Aint1D aint1D;
            for(int i2=0; i2!=n2; i2++)
            {
                int n3;
                infile.read(reinterpret_cast<char *>(&n3), sizeof n3);
                Aint0D aint0D;
                for(int i3=0; i3!=n3; i3++)
                {
                    int intvar;
                    infile.read(reinterpret_cast<char *>(&intvar), sizeof intvar);
                    aint0D.push_back(intvar);
                }
                aint1D.push_back(aint0D);
            }
            ArraysOf2DInt.push_back(aint1D);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf3DInt.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Aint2D aint2D;
            for(int i2=0; i2!=n2; i2++)
            {
                int n3;
                infile.read(reinterpret_cast<char *>(&n3), sizeof n3);
                Aint1D aint1D;
                for(int i3=0; i3!=n3; i3++)
                {
                    int n4;
                    infile.read(reinterpret_cast<char *>(&n4), sizeof n4);
                    Aint0D aint0D;
                    for(int i4=0; i4!=n4; i4++)
                    {
                        int intvar;
                        infile.read(reinterpret_cast<char *>(&intvar), sizeof intvar);
                        aint0D.push_back(intvar);
                    }
                    aint1D.push_back(aint0D);
                }
                aint2D.push_back(aint1D);
            }
            ArraysOf3DInt.push_back(aint2D);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf0DDouble.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            double dvar;
            infile.read(reinterpret_cast<char *>(&dvar), sizeof dvar);
            ArraysOf0DDouble.push_back(dvar);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf1DDouble.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Adouble0D adouble0D;
            for(int i2=0; i2!=n2; i2++)
            {
                double dvar;
                infile.read(reinterpret_cast<char *>(&dvar), sizeof dvar);
                adouble0D.push_back(dvar);
            }
            ArraysOf1DDouble.push_back(adouble0D);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf2DDouble.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Adouble1D adouble1D;
            for(int i2=0; i2!=n2; i2++)
            {
                int n3;
                infile.read(reinterpret_cast<char *>(&n3), sizeof n3);
                Adouble0D adouble0D;
                for(int i3=0; i3!=n3; i3++)
                {
                    double dvar;
                    infile.read(reinterpret_cast<char *>(&dvar), sizeof dvar);
                    adouble0D.push_back(dvar);
                }
                adouble1D.push_back(adouble0D);
            }
            ArraysOf2DDouble.push_back(adouble1D);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf3DDouble.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Adouble2D adouble2D;
            for(int i2=0; i2!=n2; i2++)
            {
                int n3;
                infile.read(reinterpret_cast<char *>(&n3), sizeof n3);
                Adouble1D adouble1D;
                for(int i3=0; i3!=n3; i3++)
                {
                    int n4;
                    infile.read(reinterpret_cast<char *>(&n4), sizeof n4);
                    Adouble0D adouble0D;
                    for(int i4=0; i4!=n4; i4++)
                    {
                        double dvar;
                        infile.read(reinterpret_cast<char *>(&dvar), sizeof dvar);
                        adouble0D.push_back(dvar);
                    }
                    adouble1D.push_back(adouble0D);
                }
                adouble2D.push_back(adouble1D);
            }
            ArraysOf3DDouble.push_back(adouble2D);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf0DString.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            size_t ns1=0;
            infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
            char* StrBuf = new char[ns1];
            for (int i = 0; i < ns1; i++)
            {
                char ch;
                infile.read(&ch, sizeof ch);
                StrBuf[i] = ch;
            }
            wxString var = wxString(StrBuf,ns1);
            ArraysOf0DString.push_back(var);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf1DString.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Astring0D astring0D;
            for(int i2=0; i2!=n2; i2++)
            {
                size_t ns1=0;
                infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                char* StrBuf = new char[ns1];
                for (int i = 0; i < ns1; i++)
                {
                    char ch;
                    infile.read(&ch, sizeof ch);
                    StrBuf[i] = ch;
                }
                wxString var = wxString(StrBuf,ns1);
                astring0D.push_back(var);
            }
            ArraysOf1DString.push_back(astring0D);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf2DString.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Astring1D astring1D;
            for(int i2=0; i2!=n2; i2++)
            {
                int n3;
                infile.read(reinterpret_cast<char *>(&n3), sizeof n3);
                Astring0D astring0D;
                for(int i3=0; i3!=n3; i3++)
                {
                    size_t ns1=0;
                    infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                    char* StrBuf = new char[ns1];
                    for (int i = 0; i < ns1; i++)
                    {
                        char ch;
                        infile.read(&ch, sizeof ch);
                        StrBuf[i] = ch;
                    }
                    wxString var = wxString(StrBuf,ns1);
                    astring0D.push_back(var);
                }
                astring1D.push_back(astring0D);
            }
            ArraysOf2DString.push_back(astring1D);
        }
        
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        ArraysOf3DString.clear();
        
        for(int i1=0; i1!=n; i1++)
        {
            int n2;
            infile.read(reinterpret_cast<char *>(&n2), sizeof n2);
            Astring2D astring2D;
            for(int i2=0; i2!=n2; i2++)
            {
                int n3;
                infile.read(reinterpret_cast<char *>(&n3), sizeof n3);
                Astring1D astring1D;
                for(int i3=0; i3!=n3; i3++)
                {
                    int n4;
                    infile.read(reinterpret_cast<char *>(&n4), sizeof n4);
                    Astring0D astring0D;
                    for(int i4=0; i4!=n4; i4++)
                    {
                        size_t ns1=0;
                        infile.read(reinterpret_cast<char *>(&ns1), sizeof ns1);
                        char* StrBuf = new char[ns1];
                        for (int i = 0; i < ns1; i++)
                        {
                            char ch;
                            infile.read(&ch, sizeof ch);
                            StrBuf[i] = ch;
                        }
                        wxString var = wxString(StrBuf,ns1);
                        astring0D.push_back(var);
                    }
                    astring1D.push_back(astring0D);
                }
                astring2D.push_back(astring1D);
            }
            ArraysOf3DString.push_back(astring2D);
        }
        ///////////////////////////////////////////////////////////////
        
        infile.close();
    }

}

wxString Sec30::GetAtomLable(int kind)
{
    wxString Lable;
    Lable=wxT("H");
    switch (kind)
    {
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

int Sec30::GetAtomLable(wxString Lable)
{
    if(Lable.Contains(wxT("He"))) return 2;
    else if(Lable.Contains(wxT("Li"))) return 3;
    else if(Lable.Contains(wxT("Be"))) return 4;
    else if(Lable.Contains(wxT("B"))) return 5;
    else if(Lable.Contains(wxT("C"))) return 6;
    else if(Lable.Contains(wxT("N"))) return 7;
    else if(Lable.Contains(wxT("O"))) return 8;
    else if(Lable.Contains(wxT("F"))) return 9;
    else if(Lable.Contains(wxT("Ne"))) return 10;
    else if(Lable.Contains(wxT("Na"))) return 11;
    else if(Lable.Contains(wxT("Mg"))) return 12;
    else if(Lable.Contains(wxT("Al"))) return 13;
    else if(Lable.Contains(wxT("Si"))) return 14;
    else if(Lable.Contains(wxT("P"))) return 15;
    else if(Lable.Contains(wxT("S"))) return 16;
    else if(Lable.Contains(wxT("Cl"))) return 17;
    else if(Lable.Contains(wxT("Ar"))) return 18;
    else if(Lable.Contains(wxT("K"))) return 19;
    else if(Lable.Contains(wxT("Ca"))) return 20;
    else if(Lable.Contains(wxT("Sc"))) return 21;
    else if(Lable.Contains(wxT("Ti"))) return 22;
    else if(Lable.Contains(wxT("V"))) return 23;
    else if(Lable.Contains(wxT("Cr"))) return 24;
    else if(Lable.Contains(wxT("Mn"))) return 25;
    else if(Lable.Contains(wxT("Fe"))) return 26;
    else if(Lable.Contains(wxT("Co"))) return 27;
    else if(Lable.Contains(wxT("Ni"))) return 28;
    else if(Lable.Contains(wxT("Cu"))) return 29;
    else if(Lable.Contains(wxT("Zn"))) return 30;
    else if(Lable.Contains(wxT("Ga"))) return 31;
    else if(Lable.Contains(wxT("Ge"))) return 32;
    else if(Lable.Contains(wxT("As"))) return 33;
    else if(Lable.Contains(wxT("Se"))) return 34;
    else if(Lable.Contains(wxT("Br"))) return 35;
    else if(Lable.Contains(wxT("Kr"))) return 36;
    else if(Lable.Contains(wxT("Rb"))) return 37;
    else if(Lable.Contains(wxT("Sr"))) return 38;
    else if(Lable.Contains(wxT("Y"))) return 39;
    else if(Lable.Contains(wxT("Zr"))) return 40;
    else if(Lable.Contains(wxT("Nb"))) return 41;
    else if(Lable.Contains(wxT("Mo"))) return 42;
    else if(Lable.Contains(wxT("Tc"))) return 43;
    else if(Lable.Contains(wxT("Ru"))) return 44;
    else if(Lable.Contains(wxT("Rh"))) return 45;
    else if(Lable.Contains(wxT("Pd"))) return 46;
    else if(Lable.Contains(wxT("Ag"))) return 47;
    else if(Lable.Contains(wxT("Cd"))) return 48;
    else if(Lable.Contains(wxT("In"))) return 49;
    else if(Lable.Contains(wxT("Sn"))) return 50;
    else if(Lable.Contains(wxT("Sb"))) return 51;
    else if(Lable.Contains(wxT("Te"))) return 52;
    else if(Lable.Contains(wxT("I"))) return 53;
    else if(Lable.Contains(wxT("Xe"))) return 54;
    else if(Lable.Contains(wxT("Cs"))) return 55;
    else if(Lable.Contains(wxT("Ba"))) return 56;
    else if(Lable.Contains(wxT("La"))) return 57;
    else if(Lable.Contains(wxT("Ce"))) return 58;
    else if(Lable.Contains(wxT("Pr"))) return 59;
    else if(Lable.Contains(wxT("Nd"))) return 60;
    else if(Lable.Contains(wxT("Pm"))) return 61;
    else if(Lable.Contains(wxT("Sm"))) return 62;
    else if(Lable.Contains(wxT("Eu"))) return 63;
    else if(Lable.Contains(wxT("Gd"))) return 64;
    else if(Lable.Contains(wxT("Tb"))) return 65;
    else if(Lable.Contains(wxT("Dy"))) return 66;
    else if(Lable.Contains(wxT("Ho"))) return 67;
    else if(Lable.Contains(wxT("Er"))) return 68;
    else if(Lable.Contains(wxT("Tm"))) return 69;
    else if(Lable.Contains(wxT("Yb"))) return 70;
    else if(Lable.Contains(wxT("Lu"))) return 71;
    else if(Lable.Contains(wxT("Hf"))) return 72;
    else if(Lable.Contains(wxT("Ta"))) return 73;
    else if(Lable.Contains(wxT("W"))) return 74;
    else if(Lable.Contains(wxT("Re"))) return 75;
    else if(Lable.Contains(wxT("Os"))) return 76;
    else if(Lable.Contains(wxT("Ir"))) return 77;
    else if(Lable.Contains(wxT("Pt"))) return 78;
    else if(Lable.Contains(wxT("Au"))) return 79;
    else if(Lable.Contains(wxT("Hg"))) return 80;
    else if(Lable.Contains(wxT("Tl"))) return 81;
    else if(Lable.Contains(wxT("Pb"))) return 82;
    else if(Lable.Contains(wxT("Bi"))) return 83;
    else if(Lable.Contains(wxT("Po"))) return 84;
    else if(Lable.Contains(wxT("At"))) return 85;
    else if(Lable.Contains(wxT("Rn"))) return 86;
    else if(Lable.Contains(wxT("Fr"))) return 87;
    else if(Lable.Contains(wxT("Ra"))) return 88;
    else if(Lable.Contains(wxT("Ac"))) return 89;
    else if(Lable.Contains(wxT("Th"))) return 90;
    else if(Lable.Contains(wxT("Pa"))) return 91;
    else if(Lable.Contains(wxT("U"))) return 92;
    else if(Lable.Contains(wxT("Np"))) return 93;
    else if(Lable.Contains(wxT("Pu"))) return 94;
    else if(Lable.Contains(wxT("Am"))) return 95;
    else if(Lable.Contains(wxT("Cm"))) return 96;
    else if(Lable.Contains(wxT("Bk"))) return 97;
    else if(Lable.Contains(wxT("Cf"))) return 98;
    else if(Lable.Contains(wxT("Es"))) return 99;
    else if(Lable.Contains(wxT("Fm"))) return 100;
    else if(Lable.Contains(wxT("Md"))) return 101;
    else if(Lable.Contains(wxT("No"))) return 102;
    else if(Lable.Contains(wxT("Lr"))) return 103;
    else if(Lable.Contains(wxT("Rf"))) return 104;
    else if(Lable.Contains(wxT("Db"))) return 105;
    else if(Lable.Contains(wxT("Sg"))) return 106;
    else if(Lable.Contains(wxT("Bh"))) return 107;
    else if(Lable.Contains(wxT("Hs"))) return 108;
    else if(Lable.Contains(wxT("Mt"))) return 109;
    else if(Lable.Contains(wxT("Ds"))) return 110;
    else if(Lable.Contains(wxT("Rg"))) return 111;
    else if(Lable.Contains(wxT("Cn"))) return 112;
    else if(Lable.Contains(wxT("Uut"))) return 113;
    else if(Lable.Contains(wxT("Fl"))) return 114;
    else if(Lable.Contains(wxT("Uup"))) return 115;
    else if(Lable.Contains(wxT("Lv"))) return 116;
    else if(Lable.Contains(wxT("Uus"))) return 117;
    else if(Lable.Contains(wxT("Uuo"))) return 118;
    
    return 1;
}

wxColor Sec30::GetAtomColor(int kind)
{
    wxColor c;
    c.Set(200, 200, 200, 255);
    switch (kind)
    {
    case 2: c.Set(100, 0, 0, 255); break;
    case 3: c.Set(100, 50, 0, 255); break;
    case 4: c.Set(100, 0, 50, 255); break;
    case 5: c.Set(100, 50, 50, 255); break;
    case 6: c.Set(0, 100, 0, 255); break;
    case 7: c.Set(50, 100, 0, 255); break;
    case 8: c.Set(0, 100, 50, 255); break;
    case 9: c.Set(50, 100, 50, 255); break;
    case 10: c.Set(0, 0, 100, 255); break;
    case 11: c.Set(50, 0, 100, 255); break;
    case 12: c.Set(0, 50, 100, 255); break;
    case 13: c.Set(50, 50, 100, 255); break;
    case 14: c.Set(150, 0, 0, 255); break;
    case 15: c.Set(150, 50, 0, 255); break;
    case 16: c.Set(150, 0, 50, 255); break;
    case 17: c.Set(150, 50, 50, 255); break;
    case 18: c.Set(0, 150, 0, 255); break;
    case 19: c.Set(50, 150, 0, 255); break;
    case 20: c.Set(0, 150, 50, 255); break;
    case 21: c.Set(50, 150, 50, 255); break;
    case 22: c.Set(0, 0, 150, 255); break;
    case 23: c.Set(50, 0, 150, 255); break;
    case 24: c.Set(0, 50, 150, 255); break;
    case 25: c.Set(50, 50, 150, 255); break;
    case 26: c.Set(170, 0, 0, 255); break;
    case 27: c.Set(170, 80, 0, 255); break;
    case 28: c.Set(170, 0, 80, 255); break;
    case 29: c.Set(170, 80, 80, 255); break;
    case 30: c.Set(0, 170, 0, 255); break;
    case 31: c.Set(80, 170, 0, 255); break;
    case 32: c.Set(0, 170, 80, 255); break;
    case 33: c.Set(80, 170, 80, 255); break;
    case 34: c.Set(0, 0, 170, 255); break;
    case 35: c.Set(80, 0, 170, 255); break;
    case 36: c.Set(0, 80, 170, 255); break;
    case 37: c.Set(80, 80, 170, 255); break;
    case 38: c.Set(20, 250, 250, 255); break;
    case 39: c.Set(20, 170, 170, 255); break;
    case 40: c.Set(20, 250, 170, 255); break;
    case 41: c.Set(20, 170, 250, 255); break;
    case 42: c.Set(250, 20, 250, 255); break;
    case 43: c.Set(170, 20, 170, 255); break;
    case 44: c.Set(250, 20, 170, 255); break;
    case 45: c.Set(170, 20, 250, 255); break;
    case 46: c.Set(250, 250, 20, 255); break;
    case 47: c.Set(170, 170, 20, 255); break;
    case 48: c.Set(170, 250, 20, 255); break;
    case 49: c.Set(250, 170, 20, 255); break;
    case 50: c.Set(120, 0, 0, 255); break;
    case 51: c.Set(120, 30, 0, 255); break;
    case 52: c.Set(120, 0, 30, 255); break;
    case 53: c.Set(120, 30, 30, 255); break;
    case 54: c.Set(0, 120, 0, 255); break;
    case 55: c.Set(30, 120, 0, 255); break;
    case 56: c.Set(0, 120, 30, 255); break;
    case 57: c.Set(30, 120, 30, 255); break;
    case 58: c.Set(0, 0, 120, 255); break;
    case 59: c.Set(30, 0, 120, 255); break;
    case 60: c.Set(0, 30, 120, 255); break;
    case 61: c.Set(30, 30, 120, 255); break;
    case 62: c.Set(210, 0, 0, 255); break;
    case 63: c.Set(210, 60, 0, 255); break;
    case 64: c.Set(210, 0, 60, 255); break;
    case 65: c.Set(210, 60, 60, 255); break;
    case 66: c.Set(0, 210, 0, 255); break;
    case 67: c.Set(60, 210, 0, 255); break;
    case 68: c.Set(0, 210, 60, 255); break;
    case 69: c.Set(60, 210, 60, 255); break;
    case 70: c.Set(0, 0, 210, 255); break;
    case 71: c.Set(60, 0, 210, 255); break;
    case 72: c.Set(0, 60, 210, 255); break;
    case 73: c.Set(60, 60, 210, 255); break;
    case 74: c.Set(120, 0, 0, 255); break;
    case 75: c.Set(120, 70, 0, 255); break;
    case 76: c.Set(120, 0, 70, 255); break;
    case 77: c.Set(120, 70, 70, 255); break;
    case 78: c.Set(0, 120, 0, 255); break;
    case 79: c.Set(70, 120, 0, 255); break;
    case 80: c.Set(0, 120, 70, 255); break;
    case 81: c.Set(70, 120, 70, 255); break;
    case 82: c.Set(0, 0, 120, 255); break;
    case 83: c.Set(70, 0, 120, 255); break;
    case 84: c.Set(0, 70, 120, 255); break;
    case 85: c.Set(70, 70, 120, 255); break;
    case 86: c.Set(250, 0, 0, 255); break;
    case 87: c.Set(250, 100, 0, 255); break;
    case 88: c.Set(250, 0, 100, 255); break;
    case 89: c.Set(250, 100, 100, 255); break;
    case 90: c.Set(0, 250, 0, 255); break;
    case 91: c.Set(100, 250, 0, 255); break;
    case 92: c.Set(0, 250, 100, 255); break;
    case 93: c.Set(100, 250, 100, 255); break;
    case 94: c.Set(0, 0, 250, 255); break;
    case 95: c.Set(100, 0, 250, 255); break;
    case 96: c.Set(0, 100, 250, 255); break;
    case 97: c.Set(100, 100, 250, 255); break;
    case 98: c.Set(50, 100, 100, 255); break;
    case 99: c.Set(50, 100, 200, 255); break;
    case 100: c.Set(50, 200, 100, 255); break;
    case 101: c.Set(50, 200, 200, 255); break;
    case 102: c.Set(100, 50, 100, 255); break;
    case 103: c.Set(100, 50, 200, 255); break;
    case 104: c.Set(200, 50, 100, 255); break;
    case 105: c.Set(200, 50, 200, 255); break;
    case 106: c.Set(100, 100, 50, 255); break;
    case 107: c.Set(100, 200, 50, 255); break;
    case 108: c.Set(200, 100, 50, 255); break;
    case 109: c.Set(200, 200, 50, 255); break;
    case 110: c.Set(100, 100, 100, 255); break;
    case 111: c.Set(150, 150, 150, 255); break;
    case 112: c.Set(200, 200, 200, 255); break;
    case 113: c.Set(70, 80, 110, 255); break;
    case 114: c.Set(110, 80, 70, 255); break;
    case 115: c.Set(80, 110, 70, 255); break;
    case 116: c.Set(70, 110, 80, 255); break;
    case 117: c.Set(110, 70, 80, 255); break;
    case 118: c.Set(80, 70, 110, 255); break;
    }
    return c;
}

wxColor Sec30::GetBondColor(int kind)
{
    wxColor c;
    c.Set(210, 0, 60, 255);
    switch (kind)
    {
    case 2: c.Set(0, 220, 0, 255); break;
    case 3: c.Set(150, 170, 0, 255); break;
    case 4: c.Set(150, 170, 150, 255); break;
    case 5: c.Set(0, 170, 0, 255); break;
    case 6: c.Set(140, 90, 0, 255); break;
    case 7: c.Set(0, 170, 150, 255); break;
    case 8: c.Set(110, 0, 90, 255); break;
    case 9: c.Set(200, 90, 90, 255); break;
    case 10: c.Set(0, 0, 170, 255); break;
    case 11: c.Set(150, 0, 170, 255); break;
    case 12: c.Set(0, 150, 170, 255); break;
    case 13: c.Set(150, 150, 170, 255); break;
    case 14: c.Set(220, 0, 0, 255); break;
    case 15: c.Set(220, 150, 0, 255); break;
    case 16: c.Set(220, 0, 150, 255); break;
    case 17: c.Set(220, 150, 150, 255); break;
    case 18: c.Set(140, 0, 0, 255); break;
    case 19: c.Set(150, 220, 0, 255); break;
    case 20: c.Set(0, 220, 150, 255); break;
    case 21: c.Set(150, 220, 150, 255); break;
    case 22: c.Set(0, 0, 220, 255); break;
    case 23: c.Set(50, 0, 220, 255); break;
    case 24: c.Set(0, 50, 220, 255); break;
    case 25: c.Set(50, 50, 220, 255); break;
    case 26: c.Set(170, 0, 0, 255); break;
    case 27: c.Set(170, 80, 0, 255); break;
    case 28: c.Set(170, 0, 80, 255); break;
    case 29: c.Set(170, 80, 80, 255); break;
    case 30: c.Set(0, 170, 0, 255); break;
    case 31: c.Set(80, 170, 0, 255); break;
    case 32: c.Set(0, 170, 80, 255); break;
    case 33: c.Set(80, 170, 80, 255); break;
    case 34: c.Set(0, 0, 170, 255); break;
    case 35: c.Set(80, 0, 170, 255); break;
    case 36: c.Set(0, 80, 170, 255); break;
    case 37: c.Set(80, 80, 170, 255); break;
    case 38: c.Set(20, 250, 250, 255); break;
    case 39: c.Set(20, 170, 170, 255); break;
    case 40: c.Set(20, 250, 170, 255); break;
    case 41: c.Set(20, 170, 250, 255); break;
    case 42: c.Set(250, 20, 250, 255); break;
    case 43: c.Set(170, 20, 170, 255); break;
    case 44: c.Set(250, 20, 170, 255); break;
    case 45: c.Set(170, 20, 250, 255); break;
    case 46: c.Set(250, 250, 20, 255); break;
    case 47: c.Set(170, 170, 20, 255); break;
    case 48: c.Set(170, 250, 20, 255); break;
    case 49: c.Set(250, 170, 20, 255); break;
    case 50: c.Set(120, 0, 0, 255); break;
    }
    return c;
}

void Sec30::GetBondInfo(const wxString& bondtextvar, int& i, int& n, int& j, int& m, int& bondtype)
{
    wxString bondtext = bondtextvar;
    bondtext.Replace(wxString(" "), wxString(""));
    bondtext.Replace(wxString("["), wxString(""));
    bondtext.Replace(wxString("]"), wxString(""));
    bondtext.Replace(wxString("("), wxString(""));
    bondtext.Replace(wxString(")"), wxString(""));
    bondtext.Replace(wxString("Bond"), wxString(""));
    bondtext.Replace(wxString("="), wxString(","));
    
    wxStringTokenizer tokenizer(bondtext, ",");
    tokenizer.GetNextToken();
    tokenizer.GetNextToken();
    long i0,n0,j0,m0,b0;
    tokenizer.GetNextToken().ToLong(&i0);
    tokenizer.GetNextToken().ToLong(&n0);
    tokenizer.GetNextToken();
    tokenizer.GetNextToken();
    tokenizer.GetNextToken().ToLong(&j0);
    tokenizer.GetNextToken().ToLong(&m0);
    tokenizer.GetNextToken().ToLong(&b0);
    i=i0-1;
    n=n0;
    j=j0-1;
    m=m0;
    bondtype=b0;
}

void Sec30::GetOrbitalInfo(wxCheckTree* orbsTree, wxString AtomName, int ShellNumber, wxString &Orbs, int &nOrbs, bool &IsShell)
{
    wxTreeItemId rootID = orbsTree->GetRootItem();
    wxTreeItemId atomID = orbsTree->FindItemIn(rootID,AtomName);
    //FixSoSoon
    if (atomID.IsOk() && (isMainThread || isPlotting)) orbsTree->SetItemState(atomID, wxCheckTree::CHECKED);
    wxString ShellName = wxString::Format(wxT("Shell %d"),ShellNumber);
    wxTreeItemId shellID = orbsTree->FindItemIn(atomID,ShellName);
    nOrbs=0;
    Orbs=_("(");
    IsShell = false;
    if (shellID.IsOk())
    {
        IsShell = true;
        //FixSoSoon
        if (isMainThread || isPlotting) orbsTree->SetItemState(shellID, wxCheckTree::CHECKED);
        wxTreeItemIdValue cookie;
        wxTreeItemId child = orbsTree->GetFirstChild(shellID, cookie);
        while( child.IsOk() )
        {
            if (orbsTree->GetItemState(child) >= wxCheckTree::CHECKED)
            {
                nOrbs++;
                if (nOrbs != 1) Orbs = Orbs + _(", ");
                Orbs = Orbs + orbsTree->GetItemText(child);
            }
            child = orbsTree->GetNextChild(shellID, cookie);
        }
    }
    
    Orbs = Orbs + _(")");
}

void Sec30::GetOrbQuantumNumbers(const wxString& OrbitalName, int& l, int& m)  // Unused 
{
    if (OrbitalName.StartsWith("s"))
    {
        l = 0;
        m = 0;
    }
    else if (OrbitalName.StartsWith("p"))
    {
        l = 1;
        if (OrbitalName.Contains("{y}"))
            m = -1;
        else if (OrbitalName.Contains("{z}"))
            m = 0;
        else if (OrbitalName.Contains("{x}"))
            m = 1;
    }
    else if (OrbitalName.StartsWith("d"))
    {
        l=2;
        if (OrbitalName.Contains("{xy}"))
            m = -2;
        else if (OrbitalName.Contains("{yz}"))
            m = -1;
        else if (OrbitalName.Contains("{3z^2-r^2}"))
            m = 0;
        else if (OrbitalName.Contains("{xz}"))
            m = 1;
        else if (OrbitalName.Contains("{x^2-y^2}"))
            m = 2;
    }
    else if (OrbitalName.StartsWith("f"))
    {
        l=3;
        if (OrbitalName.Contains("{y(3x^2-y^2)}"))
            m = -3;
        else if (OrbitalName.Contains("{xyz}"))
            m = -2;
        else if (OrbitalName.Contains("{y(5z^2-r^2)}"))
            m = -1;
        else if (OrbitalName.Contains("{z(5z^2-3r^2)}"))
            m = 0;
        else if (OrbitalName.Contains("{x(5z^2-r^2)}"))
            m = 1;
        else if (OrbitalName.Contains("{z(x^2-y^2)}"))
            m = 2;
        else if (OrbitalName.Contains("{x(x^2-3y^2)}"))
            m = 3;
    }
    else if (OrbitalName.StartsWith("g"))
    {
        l=4;
        if (OrbitalName.Contains("{xy(x^2-y^2)}"))
            m = -4;
        else if (OrbitalName.Contains("{yz(3x^2-y^2)}"))
            m = -3;
        else if (OrbitalName.Contains("{xy(7z^2-r^2)}"))
            m = -2;
        else if (OrbitalName.Contains("{yz(7z^2-3r^2)}"))
            m = -1;
        else if (OrbitalName.Contains("{35z^4-30z^2r^2+3r^4}"))
            m = 0;
        else if (OrbitalName.Contains("{xz(7z^2-3r^2)}"))
            m = 1;
        else if (OrbitalName.Contains("{(x^2-y^2)(7z^2-r^2)}"))
            m = 2;
        else if (OrbitalName.Contains("{xz(x^2-3y^2)}"))
            m = 3;
        else if (OrbitalName.Contains("{x^2(x^2-3y^2)-y^2(3x^2-y^2)}"))
            m = 4;
    }
}

wxString Sec30::CreateFilePath(wxString Path,wxString FileName)
{
    wxString file = Path + wxFileName::GetPathSeparator() + FileName;
    return file;
}

double Sec30::norm(double a[3])
{
    double r;
    r = 0.0;
    for (int i=0;i<3;i++)
    {
        r += a[i]*a[i];
    }
    return sqrt(r);  
}

double Sec30::norm(double a[3], double b[3])
{
    double r,v[3];
    r = 0.0;
    for (int i=0;i<3;i++)
    {
        v[i] = b[i]-a[i];
        r += v[i]*v[i];
    }
    return sqrt(r);
}

double Sec30::dot(double a[3], double b[3])
{
    double r = 0.0;
    for (int i=0;i<3;i++) r += a[i]*b[i];
    return r;
}

void Sec30::cross(double a[3], double b[3], double (&c)[3])
{
    c[0] = a[1]*b[2]-a[2]*b[1];
    c[1] = a[2]*b[0]-a[0]*b[2];
    c[2] = a[0]*b[1]-a[1]*b[0];
}

void Sec30::VecToReciprocal(double a[3], double b[3], double c[3], double (&ak)[3], double (&bk)[3], double (&ck)[3])
{
    double bc[3], ca[3], ab[3];
    cross(b, c, bc);
    cross(c, a, ca);
    cross(a, b, ab);
    double volume = dot(a, bc);
    double volumek = 2.0*3.14159265359 / volume;
    for(int i=0; i<3; i++) ak[i] = volumek*bc[i];
    for(int i=0; i<3; i++) bk[i] = volumek*ca[i];
    for(int i=0; i<3; i++) ck[i] = volumek*ab[i];
}

void Sec30::FracToAbs(double a[3], double b[3], double c[3], double frac[3], double (&absol)[3])
{
    absol[0] = frac[0] * a[0] + frac[1] * b[0] + frac[2] * c[0];
    absol[1] = frac[0] * a[1] + frac[1] * b[1] + frac[2] * c[1];
    absol[2] = frac[0] * a[2] + frac[1] * b[2] + frac[2] * c[2];
}

void Sec30::AbsToFrac(double a[3], double b[3], double c[3], double absol[3], double (&frac)[3])
{
    double vol = a[2]*b[1]*c[0] - a[1]*b[2]*c[0] - a[2]*b[0]*c[1] + a[0]*b[2]*c[1] + a[1]*b[0]*c[2] - a[0]*b[1]*c[2];
    if (isMatch(vol, 0.0, 1.0e-4)) {
        frac[0] = 0.0;
        frac[1] = 0.0;
        frac[2] = 0.0;
        return;
    }
    frac[0] = -(-(absol[2]*b[1]*c[0]) + absol[1]*b[2]*c[0] + absol[2]*b[0]*c[1] - absol[0]*b[2]*c[1] - absol[1]*b[0]*c[2] + absol[0]*b[1]*c[2]) / vol;
    frac[1] = -(-(a[2]*absol[1]*c[0]) + a[1]*absol[2]*c[0] + a[2]*absol[0]*c[1] - a[0]*absol[2]*c[1] - a[1]*absol[0]*c[2] + a[0]*absol[1]*c[2]) / vol;
    frac[2] = (-(a[2]*absol[1]*b[0]) + a[1]*absol[2]*b[0] + a[2]*absol[0]*b[1] - a[0]*absol[2]*b[1] - a[1]*absol[0]*b[2] + a[0]*absol[1]*b[2]) / vol;
}

void Sec30::vk_rtv(double vk[3], double rtv[3][3], double v[3])
{
   /* vk[1:3], rtv[1:3][1:3] */
  int i,j;
  for (i=0;i<3;i++) {
    v[i]=0.0;
    for (j=0;j<3;j++) {
       v[i] = v[i] + vk[j]*rtv[j][i] ;
    }
  }
}

void Sec30::GetDirectionalCosines(double x1, double y1, double z1, double x2, double y2, double z2, double &l, double &m, double &n)
{
    double R[3];
    R[0] = x2 - x1;
    R[1] = y2 - y1;
    R[2] = z2 - z1;
    
    double d = norm(R);
    if (d <= 0.0000001)
    {
        l = 0;
        m = 0;
        n = 0;
    }
    else
    {
        l = R[0]/d;
        m = R[1]/d;
        n = R[2]/d;
    }
}

double Sec30::Hopspd(Adouble0D BondSK, double l, double m, double n, wxString o1, wxString o2)
{
    double out = Hopspd(BondSK[0], BondSK[1], BondSK[2], BondSK[3], BondSK[4], BondSK[5], BondSK[6], BondSK[7], BondSK[8], BondSK[9], BondSK[10], BondSK[11], BondSK[12], BondSK[13], BondSK[14], BondSK[15], l, m, n, o1, o2);
    //double out = Hopspd(BondSK[0], BondSK[1], BondSK[2], BondSK[3], BondSK[4], BondSK[5], BondSK[6], BondSK[7], BondSK[8], BondSK[9], l, m, n, o1, o2);
    return out;
}

double Sec30::Hopspd(double sss, double sps, double sds, double pps, double ppp,
            double pds, double pdp, double dds, double ddp, double ddd,
            double l, double m, double n, wxString o1, wxString o2)
{
    double out = 0.0;
    
    wxString element = o1 + _(":") + o2;
    double nn=n;
    if (nn>0.9999)
    {
        nn=0.9999;
    }
    else if (nn<-0.9999)
    {
        nn=-0.9999;
    }
    
    if (element == _("s:s")) out = sss;
    else if (element == _("s:p_y")) out = sps*m;
    else if (element == _("p_y:s")) out = (-sps)*m;
    else if (element == _("s:p_z")) out = sps*nn;
    else if (element == _("p_z:s")) out = (-sps)*nn;
    else if (element == _("s:p_x")) out = sps*l;
    else if (element == _("p_x:s")) out = (-sps)*l;
    else if (element == _("s:d_{xy}")) out = ((sqrt(3)*sds)*l)*m;
    else if (element == _("d_{xy}:s")) out = ((sqrt(3)*sds)*l)*m;
    else if (element == _("s:d_{yz}")) out = ((sqrt(3)*sds)*m)*nn;
    else if (element == _("d_{yz}:s")) out = ((sqrt(3)*sds)*m)*nn;
    else if (element == _("s:d_{3z^2-r^2}")) out = (sds/2)*(-1 + 3*nn*nn);
    else if (element == _("d_{3z^2-r^2}:s")) out = (sds/2)*(-1 + 3*nn*nn);
    else if (element == _("s:d_{xz}")) out = ((sqrt(3)*sds)*l)*nn;
    else if (element == _("d_{xz}:s")) out = ((sqrt(3)*sds)*l)*nn;
    else if (element == _("s:d_{x^2-y^2}")) out = ((-sqrt(3)/2)*sds)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:s")) out = ((-sqrt(3)/2)*sds)*(-1 + 2*m*m + nn*nn);
    else if (element == _("p_y:p_y")) out = ppp - ppp*m*m + pps*m*m;
    else if (element == _("p_y:p_z")) out = ((-ppp + pps)*m)*nn;
    else if (element == _("p_z:p_y")) out = ((-ppp + pps)*m)*nn;
    else if (element == _("p_y:p_x")) out = ((-ppp + pps)*l)*m;
    else if (element == _("p_x:p_y")) out = ((-ppp + pps)*l)*m;
    else if (element == _("p_y:d_{xy}")) out = l*(pdp - (2*pdp)*m*m + (sqrt(3)*pds)*m*m);
    else if (element == _("d_{xy}:p_y")) out = (-l)*(pdp - (2*pdp)*m*m + (sqrt(3)*pds)*m*m);
    else if (element == _("p_y:d_{yz}")) out = (pdp - (2*pdp)*m*m + (sqrt(3)*pds)*m*m)*nn;
    else if (element == _("d_{yz}:p_y")) out = (-(pdp - (2*pdp)*m*m + (sqrt(3)*pds)*m*m))*nn;
    else if (element == _("p_y:d_{3z^2-r^2}")) out = (-m/2)*(pds + ((2*sqrt(3))*pdp)*nn*nn - (3*pds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:p_y")) out = (m/2)*(pds + ((2*sqrt(3))*pdp)*nn*nn - (3*pds)*nn*nn);
    else if (element == _("p_y:d_{xz}")) out = (((-2*pdp + sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("d_{xz}:p_y")) out = (((2*pdp - sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("p_y:d_{x^2-y^2}")) out = (pdp*m)*(-2 + 2*m*m + nn*nn) + (((-sqrt(3)/2)*pds)*m)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:p_y")) out = ((-pdp)*m)*(-2 + 2*m*m + nn*nn) + (((sqrt(3)/2)*pds)*m)*(-1 + 2*m*m + nn*nn);
    else if (element == _("p_z:p_z")) out = ppp - ppp*nn*nn + pps*nn*nn;
    else if (element == _("p_z:p_x")) out = ((-ppp + pps)*l)*nn;
    else if (element == _("p_x:p_z")) out = ((-ppp + pps)*l)*nn;
    else if (element == _("p_z:d_{xy}")) out = (((-2*pdp + sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("d_{xy}:p_z")) out = (((2*pdp - sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("p_z:d_{yz}")) out = m*(pdp - (2*pdp)*nn*nn + (sqrt(3)*pds)*nn*nn);
    else if (element == _("d_{yz}:p_z")) out = (-m)*(pdp - (2*pdp)*nn*nn + (sqrt(3)*pds)*nn*nn);
    else if (element == _("p_z:d_{3z^2-r^2}")) out = ((pds/2)*nn)*(-1 + 3*nn*nn) + (sqrt(3)*pdp)*(nn - pow(nn,3.0));
    else if (element == _("d_{3z^2-r^2}:p_z")) out = ((sqrt(3)*pdp)*nn)*(-1 + nn*nn) + (pds/2)*(nn - 3*pow(nn,3.0));
    else if (element == _("p_z:d_{xz}")) out = l*(pdp - (2*pdp)*nn*nn + (sqrt(3)*pds)*nn*nn);
    else if (element == _("d_{xz}:p_z")) out = (-l)*(pdp - (2*pdp)*nn*nn + (sqrt(3)*pds)*nn*nn);
    else if (element == _("p_z:d_{x^2-y^2}")) out = (((2*pdp - sqrt(3)*pds)/2)*nn)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:p_z")) out = ((-(2*pdp - sqrt(3)*pds)/2)*nn)*(-1 + 2*m*m + nn*nn);
    else if (element == _("p_x:p_x")) out = (-pps)*(-1 + m*m + nn*nn) + ppp*(m*m + nn*nn);
    else if (element == _("p_x:d_{xy}")) out = m*(((-sqrt(3))*pds)*(-1 + m*m + nn*nn) + pdp*(-1 + 2*m*m + 2*nn*nn));
    else if (element == _("d_{xy}:p_x")) out = ((sqrt(3)*pds)*m)*(-1 + m*m + nn*nn) + pdp*(m - 2*pow(m,3.0) - (2*m)*nn*nn);
    else if (element == _("p_x:d_{yz}")) out = (((-2*pdp + sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("d_{yz}:p_x")) out = (((2*pdp - sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("p_x:d_{3z^2-r^2}")) out = (-l/2)*(pds + ((2*sqrt(3))*pdp)*nn*nn - (3*pds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:p_x")) out = (l/2)*(pds + ((2*sqrt(3))*pdp)*nn*nn - (3*pds)*nn*nn);
    else if (element == _("p_x:d_{xz}")) out = nn*(pdp + (2*pdp)*(-1 + m*m + nn*nn) - (sqrt(3)*pds)*(-1 + m*m + nn*nn));
    else if (element == _("d_{xz}:p_x")) out = (-nn)*(pdp + (2*pdp)*(-1 + m*m + nn*nn) - (sqrt(3)*pds)*(-1 + m*m + nn*nn));
    else if (element == _("p_x:d_{x^2-y^2}")) out = (((-sqrt(3)/2)*pds)*l)*(-1 + 2*m*m + nn*nn) + (pdp*l)*(2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:p_x")) out = (((sqrt(3)/2)*pds)*l)*(-1 + 2*m*m + nn*nn) - (pdp*l)*(2*m*m + nn*nn);
    else if (element == _("d_{xy}:d_{xy}")) out = ddp - ddp*nn*nn + ((4*ddp)*m*m)*(-1 + m*m + nn*nn) - ((3*dds)*m*m)*(-1 + m*m + nn*nn) - (ddd*(-1 + m*m))*(m*m + nn*nn);
    else if (element == _("d_{xy}:d_{yz}")) out = (l*(-ddd + ddp + (ddd - 4*ddp + 3*dds)*m*m))*nn;
    else if (element == _("d_{yz}:d_{xy}")) out = (l*(-ddd + ddp + (ddd - 4*ddp + 3*dds)*m*m))*nn;
    else if (element == _("d_{xy}:d_{3z^2-r^2}")) out = (((sqrt(3)/2)*l)*m)*(ddd - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:d_{xy}")) out = (((sqrt(3)/2)*l)*m)*(ddd - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{xy}:d_{xz}")) out = ((-m)*nn)*(ddp*(3 - 4*m*m - 4*nn*nn) + (3*dds)*(-1 + m*m + nn*nn) + ddd*(m*m + nn*nn));
    else if (element == _("d_{xz}:d_{xy}")) out = ((-m)*nn)*(ddp*(3 - 4*m*m - 4*nn*nn) + (3*dds)*(-1 + m*m + nn*nn) + ddd*(m*m + nn*nn));
    else if (element == _("d_{xy}:d_{x^2-y^2}")) out = (((-(ddd - 4*ddp + 3*dds)/2)*l)*m)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:d_{xy}")) out = (((-(ddd - 4*ddp + 3*dds)/2)*l)*m)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{yz}:d_{yz}")) out = ddp*m*m + (ddp - (4*ddp)*m*m + (3*dds)*m*m)*nn*nn + (ddd*(-1 + m*m))*(-1 + nn*nn);
    else if (element == _("d_{yz}:d_{3z^2-r^2}")) out = (((sqrt(3)/2)*m)*nn)*(-ddd + 2*ddp - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:d_{yz}")) out = (((sqrt(3)/2)*m)*nn)*(-ddd + 2*ddp - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{yz}:d_{xz}")) out = (l*m)*(-ddd + ddp + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{xz}:d_{yz}")) out = (l*m)*(-ddd + ddp + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{yz}:d_{x^2-y^2}")) out = ((m/2)*nn)*((-3*dds)*(-1 + 2*m*m + nn*nn) + ddp*(-6 + 8*m*m + 4*nn*nn) + (ddd/(-1 + nn*nn))*(-4 + l*l + 3*m*m + (4 + l*l - m*m)*nn*nn));
    else if (element == _("d_{x^2-y^2}:d_{yz}")) out = ((m/2)*nn)*((-3*dds)*(-1 + 2*m*m + nn*nn) + ddp*(-6 + 8*m*m + 4*nn*nn) + (ddd/(-1 + nn*nn))*(-4 + l*l + 3*m*m + (4 + l*l - m*m)*nn*nn));
    else if (element == _("d_{3z^2-r^2}:d_{3z^2-r^2}")) out = (3*ddd + dds - (6*(ddd - 2*ddp + dds))*nn*nn + (3*(ddd - 4*ddp + 3*dds))*pow(nn,4.0))/4;
    else if (element == _("d_{3z^2-r^2}:d_{xz}")) out = (((sqrt(3)/2)*l)*nn)*(-ddd + 2*ddp - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{xz}:d_{3z^2-r^2}")) out = (((sqrt(3)/2)*l)*nn)*(-ddd + 2*ddp - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:d_{x^2-y^2}")) out = ((-sqrt(3)/4)*(-1 + 2*m*m + nn*nn))* (ddd - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{x^2-y^2}:d_{3z^2-r^2}")) out = ((-sqrt(3)/4)*(-1 + 2*m*m + nn*nn))* (ddd - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{xz}:d_{xz}")) out = ddp + ddd*m*m - ddp*m*m - ((ddd - 4*ddp + 3*dds)*(-1 + m*m))*nn*nn - (ddd - 4*ddp + 3*dds)*pow(nn,4.0);
    else if (element == _("d_{xz}:d_{x^2-y^2}")) out = ((-l/2)*nn)*(2*ddp - 3*dds - (4*ddp - 3*dds)*(2*m*m + nn*nn) + ddd*(1 + 2*m*m + nn*nn));
    else if (element == _("d_{x^2-y^2}:d_{xz}")) out = ((-l/2)*nn)*(2*ddp - 3*dds - (4*ddp - 3*dds)*(2*m*m + nn*nn) + ddd*(1 + 2*m*m + nn*nn));
    else if (element == _("d_{x^2-y^2}:d_{x^2-y^2}")) out = (4*ddp)*m*m + ddd*pow(m,4.0) + ddp*nn*nn + (ddd*m*m)*(-1 + nn*nn) + (ddd/4)*pow(1 + nn*nn,2.0) + ((3*dds)/4)*pow(-1 + 2*m*m + nn*nn,2.0) - ddp*pow(2*m*m + nn*nn,2.0);

    return out;
}


double Sec30::Hopspd(double sss, double sps, double sds, double pps, double ppp,
            double pds, double pdp, double dds, double ddp, double ddd,
            double sfs, double pfs, double pfp, double dfs, double dfp, double dfd,
            double l, double m, double n, wxString o1, wxString o2)
{
    double out = 0.0;
    
    wxString element = o1 + _(":") + o2;
    double nn=n;
    if (nn>0.9999)
    {
        nn=0.9999;
    }
    else if (nn<-0.9999)
    {
        nn=-0.9999;
    }
    
    if (element == _("s:s")) out = sss;
    else if (element == _("s:p_y")) out = sps*m;
    else if (element == _("p_y:s")) out = (-sps)*m;
    else if (element == _("s:p_z")) out = sps*nn;
    else if (element == _("p_z:s")) out = (-sps)*nn;
    else if (element == _("s:p_x")) out = sps*l;
    else if (element == _("p_x:s")) out = (-sps)*l;
    else if (element == _("s:d_{xy}")) out = ((sqrt(3)*sds)*l)*m;
    else if (element == _("d_{xy}:s")) out = ((sqrt(3)*sds)*l)*m;
    else if (element == _("s:d_{yz}")) out = ((sqrt(3)*sds)*m)*nn;
    else if (element == _("d_{yz}:s")) out = ((sqrt(3)*sds)*m)*nn;
    else if (element == _("s:d_{3z^2-r^2}")) out = (sds/2)*(-1 + 3*nn*nn);
    else if (element == _("d_{3z^2-r^2}:s")) out = (sds/2)*(-1 + 3*nn*nn);
    else if (element == _("s:d_{xz}")) out = ((sqrt(3)*sds)*l)*nn;
    else if (element == _("d_{xz}:s")) out = ((sqrt(3)*sds)*l)*nn;
    else if (element == _("s:d_{x^2-y^2}")) out = ((-sqrt(3)/2)*sds)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:s")) out = ((-sqrt(3)/2)*sds)*(-1 + 2*m*m + nn*nn);
    else if (element == _("p_y:p_y")) out = ppp - ppp*m*m + pps*m*m;
    else if (element == _("p_y:p_z")) out = ((-ppp + pps)*m)*nn;
    else if (element == _("p_z:p_y")) out = ((-ppp + pps)*m)*nn;
    else if (element == _("p_y:p_x")) out = ((-ppp + pps)*l)*m;
    else if (element == _("p_x:p_y")) out = ((-ppp + pps)*l)*m;
    else if (element == _("p_y:d_{xy}")) out = l*(pdp - (2*pdp)*m*m + (sqrt(3)*pds)*m*m);
    else if (element == _("d_{xy}:p_y")) out = (-l)*(pdp - (2*pdp)*m*m + (sqrt(3)*pds)*m*m);
    else if (element == _("p_y:d_{yz}")) out = (pdp - (2*pdp)*m*m + (sqrt(3)*pds)*m*m)*nn;
    else if (element == _("d_{yz}:p_y")) out = (-(pdp - (2*pdp)*m*m + (sqrt(3)*pds)*m*m))*nn;
    else if (element == _("p_y:d_{3z^2-r^2}")) out = (-m/2)*(pds + ((2*sqrt(3))*pdp)*nn*nn - (3*pds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:p_y")) out = (m/2)*(pds + ((2*sqrt(3))*pdp)*nn*nn - (3*pds)*nn*nn);
    else if (element == _("p_y:d_{xz}")) out = (((-2*pdp + sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("d_{xz}:p_y")) out = (((2*pdp - sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("p_y:d_{x^2-y^2}")) out = (pdp*m)*(-2 + 2*m*m + nn*nn) + (((-sqrt(3)/2)*pds)*m)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:p_y")) out = ((-pdp)*m)*(-2 + 2*m*m + nn*nn) + (((sqrt(3)/2)*pds)*m)*(-1 + 2*m*m + nn*nn);
    else if (element == _("p_z:p_z")) out = ppp - ppp*nn*nn + pps*nn*nn;
    else if (element == _("p_z:p_x")) out = ((-ppp + pps)*l)*nn;
    else if (element == _("p_x:p_z")) out = ((-ppp + pps)*l)*nn;
    else if (element == _("p_z:d_{xy}")) out = (((-2*pdp + sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("d_{xy}:p_z")) out = (((2*pdp - sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("p_z:d_{yz}")) out = m*(pdp - (2*pdp)*nn*nn + (sqrt(3)*pds)*nn*nn);
    else if (element == _("d_{yz}:p_z")) out = (-m)*(pdp - (2*pdp)*nn*nn + (sqrt(3)*pds)*nn*nn);
    else if (element == _("p_z:d_{3z^2-r^2}")) out = ((pds/2)*nn)*(-1 + 3*nn*nn) + (sqrt(3)*pdp)*(nn - pow(nn,3.0));
    else if (element == _("d_{3z^2-r^2}:p_z")) out = ((sqrt(3)*pdp)*nn)*(-1 + nn*nn) + (pds/2)*(nn - 3*pow(nn,3.0));
    else if (element == _("p_z:d_{xz}")) out = l*(pdp - (2*pdp)*nn*nn + (sqrt(3)*pds)*nn*nn);
    else if (element == _("d_{xz}:p_z")) out = (-l)*(pdp - (2*pdp)*nn*nn + (sqrt(3)*pds)*nn*nn);
    else if (element == _("p_z:d_{x^2-y^2}")) out = (((2*pdp - sqrt(3)*pds)/2)*nn)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:p_z")) out = ((-(2*pdp - sqrt(3)*pds)/2)*nn)*(-1 + 2*m*m + nn*nn);
    else if (element == _("p_x:p_x")) out = (-pps)*(-1 + m*m + nn*nn) + ppp*(m*m + nn*nn);
    else if (element == _("p_x:d_{xy}")) out = m*(((-sqrt(3))*pds)*(-1 + m*m + nn*nn) + pdp*(-1 + 2*m*m + 2*nn*nn));
    else if (element == _("d_{xy}:p_x")) out = ((sqrt(3)*pds)*m)*(-1 + m*m + nn*nn) + pdp*(m - 2*pow(m,3.0) - (2*m)*nn*nn);
    else if (element == _("p_x:d_{yz}")) out = (((-2*pdp + sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("d_{yz}:p_x")) out = (((2*pdp - sqrt(3)*pds)*l)*m)*nn;
    else if (element == _("p_x:d_{3z^2-r^2}")) out = (-1./2)*(pds + ((2*sqrt(3))*pdp)*nn*nn - (3*pds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:p_x")) out = (1./2)*(pds + ((2*sqrt(3))*pdp)*nn*nn - (3*pds)*nn*nn);
    else if (element == _("p_x:d_{xz}")) out = nn*(pdp + (2*pdp)*(-1 + m*m + nn*nn) - (sqrt(3)*pds)*(-1 + m*m + nn*nn));
    else if (element == _("d_{xz}:p_x")) out = (-nn)*(pdp + (2*pdp)*(-1 + m*m + nn*nn) - (sqrt(3)*pds)*(-1 + m*m + nn*nn));
    else if (element == _("p_x:d_{x^2-y^2}")) out = (((-sqrt(3)/2)*pds)*l)*(-1 + 2*m*m + nn*nn) + (pdp*l)*(2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:p_x")) out = (((sqrt(3)/2)*pds)*l)*(-1 + 2*m*m + nn*nn) - (pdp*l)*(2*m*m + nn*nn);
    else if (element == _("d_{xy}:d_{xy}")) out = ddp - ddp*nn*nn + ((4*ddp)*m*m)*(-1 + m*m + nn*nn) - ((3*dds)*m*m)*(-1 + m*m + nn*nn) - (ddd*(-1 + m*m))*(m*m + nn*nn);
    else if (element == _("d_{xy}:d_{yz}")) out = (l*(-ddd + ddp + (ddd - 4*ddp + 3*dds)*m*m))*nn;
    else if (element == _("d_{yz}:d_{xy}")) out = (l*(-ddd + ddp + (ddd - 4*ddp + 3*dds)*m*m))*nn;
    else if (element == _("d_{xy}:d_{3z^2-r^2}")) out = (((sqrt(3)/2)*l)*m)*(ddd - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:d_{xy}")) out = (((sqrt(3)/2)*l)*m)*(ddd - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{xy}:d_{xz}")) out = ((-m)*nn)*(ddp*(3 - 4*m*m - 4*nn*nn) + (3*dds)*(-1 + m*m + nn*nn) + ddd*(m*m + nn*nn));
    else if (element == _("d_{xz}:d_{xy}")) out = ((-m)*nn)*(ddp*(3 - 4*m*m - 4*nn*nn) + (3*dds)*(-1 + m*m + nn*nn) + ddd*(m*m + nn*nn));
    else if (element == _("d_{xy}:d_{x^2-y^2}")) out = (((-(ddd - 4*ddp + 3*dds)/2)*l)*m)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{x^2-y^2}:d_{xy}")) out = (((-(ddd - 4*ddp + 3*dds)/2)*l)*m)*(-1 + 2*m*m + nn*nn);
    else if (element == _("d_{yz}:d_{yz}")) out = ddp*m*m + (ddp - (4*ddp)*m*m + (3*dds)*m*m)*nn*nn + (ddd*(-1 + m*m))*(-1 + nn*nn);
    else if (element == _("d_{yz}:d_{3z^2-r^2}")) out = (((sqrt(3)/2)*m)*nn)*(-ddd + 2*ddp - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:d_{yz}")) out = (((sqrt(3)/2)*m)*nn)*(-ddd + 2*ddp - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{yz}:d_{xz}")) out = (l*m)*(-ddd + ddp + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{xz}:d_{yz}")) out = (l*m)*(-ddd + ddp + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{yz}:d_{x^2-y^2}")) out = ((m/2)*nn)*((-3*dds)*(-1 + 2*m*m + nn*nn) + ddp*(-6 + 8*m*m + 4*nn*nn) + (ddd/(-1 + nn*nn))*(-4 + l*l + 3*m*m + (4 + l*l - m*m)*nn*nn));
    else if (element == _("d_{x^2-y^2}:d_{yz}")) out = ((m/2)*nn)*((-3*dds)*(-1 + 2*m*m + nn*nn) + ddp*(-6 + 8*m*m + 4*nn*nn) + (ddd/(-1 + nn*nn))*(-4 + l*l + 3*m*m + (4 + l*l - m*m)*nn*nn));
    else if (element == _("d_{3z^2-r^2}:d_{3z^2-r^2}")) out = (3*ddd + dds - (6*(ddd - 2*ddp + dds))*nn*nn + (3*(ddd - 4*ddp + 3*dds))*pow(nn,4.0))/4;
    else if (element == _("d_{3z^2-r^2}:d_{xz}")) out = (((sqrt(3)/2)*l)*nn)*(-ddd + 2*ddp - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{xz}:d_{3z^2-r^2}")) out = (((sqrt(3)/2)*l)*nn)*(-ddd + 2*ddp - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{3z^2-r^2}:d_{x^2-y^2}")) out = ((-sqrt(3)/4)*(-1 + 2*m*m + nn*nn))* (ddd - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{x^2-y^2}:d_{3z^2-r^2}")) out = ((-sqrt(3)/4)*(-1 + 2*m*m + nn*nn))* (ddd - dds + (ddd - 4*ddp + 3*dds)*nn*nn);
    else if (element == _("d_{xz}:d_{xz}")) out = ddp + ddd*m*m - ddp*m*m - ((ddd - 4*ddp + 3*dds)*(-1 + m*m))*nn*nn - (ddd - 4*ddp + 3*dds)*pow(nn,4.0);
    else if (element == _("d_{xz}:d_{x^2-y^2}")) out = ((-l/2)*nn)*(2*ddp - 3*dds - (4*ddp - 3*dds)*(2*m*m + nn*nn) + ddd*(1 + 2*m*m + nn*nn));
    else if (element == _("d_{x^2-y^2}:d_{xz}")) out = ((-l/2)*nn)*(2*ddp - 3*dds - (4*ddp - 3*dds)*(2*m*m + nn*nn) + ddd*(1 + 2*m*m + nn*nn));
    else if (element == _("d_{x^2-y^2}:d_{x^2-y^2}")) out = (4*ddp)*m*m + ddd*pow(m,4.0) + ddp*nn*nn + (ddd*m*m)*(-1 + nn*nn) + (ddd/4)*pow(1 + nn*nn,2.0) + ((3*dds)/4)*pow(-1 + 2*m*m + nn*nn,2.0) - ddp*pow(2*m*m + nn*nn,2.0);

    // s-f
    else if (element == _("s:f_{y(3x^2-y^2)}")) out = sqrt(15./2)/2*m*(3*l*l-m*m)*sfs;
    else if (element == _("f_{y(3x^2-y^2)}:s")) out = -sqrt(15./2)/2*m*(3*l*l-m*m)*sfs;
    else if (element == _("s:f_{xyz}")) out = sqrt(15)*l*m*n*sfs;
    else if (element == _("f_{xyz}:s")) out = -sqrt(15)*l*m*n*sfs;
    else if (element == _("s:f_{y(5z^2-r^2)}")) out = sqrt(3./2)/2*m*(5*n*n-1)*sfs;
    else if (element == _("f_{y(5z^2-r^2)}:s")) out = -sqrt(3./2)/2*m*(5*n*n-1)*sfs;
    else if (element == _("s:f_{z(5z^2-3r^2)}")) out = (5*n*n-3)*n/2*sfs;
    else if (element == _("f_{z(5z^2-3r^2)}:s")) out = -(5*n*n-3)*n/2*sfs;
    else if (element == _("s:f_{x(5z^2-r^2)}")) out = sqrt(3./2)/2*l*(5*n*n-1)*sfs;
    else if (element == _("f_{x(5z^2-r^2)}:s")) out = -sqrt(3./2)/2*l*(5*n*n-1)*sfs;
    else if (element == _("s:f_{z(x^2-y^2)}")) out = sqrt(15)/2*n*(l*l-m*m)*sfs;
    else if (element == _("f_{z(x^2-y^2)}:s")) out = -sqrt(15)/2*n*(l*l-m*m)*sfs;
    else if (element == _("s:f_{x(x^2-3y^2)}")) out = sqrt(15./2)/2*l*(l*l-3*m*m)*sfs;
    else if (element == _("f_{x(x^2-3y^2)}:s")) out = -sqrt(15./2)/2*l*(l*l-3*m*m)*sfs;
    // p_y-f
    else if (element == _("p_y:f_{y(3x^2-y^2)}")) out = sqrt(5./8)*m*m*(3*l*l-m*m)*pfs-sqrt(15)/4*(m*m*(3*l*l-m*m)+m*m-l*l)*pfp;    //6
    else if (element == _("f_{y(3x^2-y^2)}:p_y")) out = sqrt(5./8)*m*m*(3*l*l-m*m)*pfs-sqrt(15)/4*(m*m*(3*l*l-m*m)+m*m-l*l)*pfp;
    else if (element == _("p_y:f_{xyz}")) out = sqrt(15)*l*m*m*n*pfs-sqrt(5./2)*l*n*(3*m*m-1)*pfp; //4
    else if (element == _("f_{xyz}:p_y")) out = sqrt(15)*l*m*m*n*pfs-sqrt(5./2)*l*n*(3*m*m-1)*pfp;
    else if (element == _("p_y:f_{y(5z^2-r^2)}")) out = sqrt(3./8)*m*m*(5*n*n-1)*pfs-0.25*((5*n*n-1)*(3*m*m-1)+2*m*m)*pfp; //2
    else if (element == _("f_{y(5z^2-r^2)}:p_y")) out = sqrt(3./8)*m*m*(5*n*n-1)*pfs-0.25*((5*n*n-1)*(3*m*m-1)+2*m*m)*pfp;
    else if (element == _("p_y:f_{z(5z^2-3r^2)}")) out = m*n/2*(5*n*n-3)*pfs-sqrt(3./8)*m*n*(5*n*n-1)*pfp;  //0
    else if (element == _("f_{z(5z^2-3r^2)}:p_y")) out = m*n/2*(5*n*n-3)*pfs-sqrt(3./8)*m*n*(5*n*n-1)*pfp;
    else if (element == _("p_y:f_{x(5z^2-r^2)}")) out = sqrt(3./8)*l*m*(5*n*n-1)*pfs-l*m/4*(15*n*n-1)*pfp;//1
    else if (element == _("f_{x(5z^2-r^2)}:p_y")) out = sqrt(3./8)*l*m*(5*n*n-1)*pfs-l*m/4*(15*n*n-1)*pfp;
    else if (element == _("p_y:f_{z(x^2-y^2)}")) out = sqrt(15)/2*m*n*(l*l-m*m)*pfs-sqrt(5./8)*m*n*(3*(l*l-m*m)+2)*pfp;   //3
    else if (element == _("f_{z(x^2-y^2)}:p_y")) out = sqrt(15)/2*m*n*(l*l-m*m)*pfs-sqrt(5./8)*m*n*(3*(l*l-m*m)+2)*pfp;
    else if (element == _("p_y:f_{x(x^2-3y^2)}")) out = sqrt(5./8)*m*l*(l*l-3*m*m)*pfs-sqrt(15)/4*l*m*(l*l-3*m*m+2)*pfp;//5
    else if (element == _("f_{x(x^2-3y^2)}:p_y")) out = sqrt(5./8)*m*l*(l*l-3*m*m)*pfs-sqrt(15)/4*l*m*(l*l-3*m*m+2)*pfp;
    // p_z-f
    else if (element == _("p_z:f_{y(3x^2-y^2)}")) out = sqrt(5./8)*m*n*(3*l*l-m*m)*pfs-sqrt(15)/4*m*n*(3*l*l-m*m)*pfp;   //6
    else if (element == _("f_{y(3x^2-y^2)}:p_z")) out = sqrt(5./8)*m*n*(3*l*l-m*m)*pfs-sqrt(15)/4*m*n*(3*l*l-m*m)*pfp;
    else if (element == _("p_z:f_{xyz}")) out = sqrt(15)*l*m*n*n*pfs-sqrt(5./2)*l*m*(3*n*n-1)*pfp;  //4
    else if (element == _("f_{xyz}:p_y")) out = sqrt(15)*l*m*n*n*pfs-sqrt(5./2)*l*m*(3*n*n-1)*pfp;
    else if (element == _("p_z:f_{y(5z^2-r^2)}")) out = sqrt(3./8)*m*n*(5*n*n-1)*pfs-m*n/4*(15*n*n-11)*pfp; //2
    else if (element == _("f_{y(5z^2-r^2)}:p_z")) out = sqrt(3./8)*m*n*(5*n*n-1)*pfs-m*n/4*(15*n*n-11)*pfp;
    else if (element == _("p_z:f_{z(5z^2-3r^2)}")) out = n*n/2*(5*n*n-3)*pfs-sqrt(3./8)*(5*n*n-1)*(n*n-1)*pfp; //0
    else if (element == _("f_{z(5z^2-3r^2)}:p_z")) out = n*n/2*(5*n*n-3)*pfs-sqrt(3./8)*(5*n*n-1)*(n*n-1)*pfp;
    else if (element == _("p_z:f_{x(5z^2-r^2)}")) out = sqrt(3./8)*l*n*(5*n*n-1)*pfs-l*n/4*(15*n*n-11)*pfp;  //1
    else if (element == _("f_{x(5z^2-r^2)}:p_z")) out = sqrt(3./8)*l*n*(5*n*n-1)*pfs-l*n/4*(15*n*n-11)*pfp; 
    else if (element == _("p_z:f_{z(x^2-y^2)}")) out = sqrt(15)/2*n*n*(l*l-m*m)*pfs-sqrt(5./8)*(3*n*n-1)*(l*l-m*m)*pfp;   //3
    else if (element == _("f_{z(x^2-y^2)}:p_z")) out = sqrt(15)/2*n*n*(l*l-m*m)*pfs-sqrt(5./8)*(3*n*n-1)*(l*l-m*m)*pfp;
    else if (element == _("p_z:f_{x(x^2-3y^2)}")) out = sqrt(5./8)*l*n*(l*l-3*m*m)*pfs-sqrt(15)/4*l*n*(l*l-3*m*m)*pfp;  //5
    else if (element == _("f_{x(x^2-3y^2)}:p_z")) out = sqrt(5./8)*l*n*(l*l-3*m*m)*pfs-sqrt(15)/4*l*n*(l*l-3*m*m)*pfp;


    // p_x-f
    else if (element == _("p_x:f_{y(3x^2-y^2)}")) out = sqrt(5./8)*l*m*(3*l*l-m*m)*pfs-sqrt(15)/4*l*m*(3*l*l-m*m-2)*pfp; //6
    else if (element == _("f_{y(3x^2-y^2)}:p_x")) out = sqrt(5./8)*l*m*(3*l*l-m*m)*pfs-sqrt(15)/4*l*m*(3*l*l-m*m-2)*pfp;
    else if (element == _("p_x:f_{xyz}")) out = sqrt(15)*l*l*m*n*pfs-sqrt(5./2)*m*n*(3*l*l-1)*pfp;//4
    else if (element == _("f_{xyz}:p_x")) out = sqrt(15)*l*l*m*n*pfs-sqrt(5./2)*m*n*(3*l*l-1)*pfp;
    else if (element == _("p_x:f_{y(5z^2-r^2)}")) out = sqrt(3./8)*l*m*(5*n*n-1)*pfs-l*m/4*(15*n*n-1)*pfp;//2
    else if (element == _("f_{y(5z^2-r^2)}:p_x")) out = sqrt(3./8)*l*m*(5*n*n-1)*pfs-l*m/4*(15*n*n-1)*pfp;
    else if (element == _("p_x:f_{z(5z^2-3r^2)}")) out = l*n/2*(5*n*n-3)*pfs-sqrt(3./8)*l*n*(5*n*n-1)*pfp;  //0
    else if (element == _("f_{z(5z^2-3r^2)}:p_x")) out = l*n/2*(5*n*n-3)*pfs-sqrt(3./8)*l*n*(5*n*n-1)*pfp;
    else if (element == _("p_x:f_{x(5z^2-r^2)}")) out = sqrt(3./8)*l*l*(5*n*n-1)*pfs-0.25*((5*n*n-1)*(3*l*l-1)+2*l*l)*pfp;  //1
    else if (element == _("f_{x(5z^2-r^2)}:p_x")) out = sqrt(3./8)*l*l*(5*n*n-1)*pfs-0.25*((5*n*n-1)*(3*l*l-1)+2*l*l)*pfp;
    else if (element == _("p_x:f_{z(x^2-y^2)}")) out = sqrt(15)/2*l*n*(l*l-m*m)*pfs-sqrt(5./8)*l*n*(3*(l*l-m*m)-2)*pfp;  //3
    else if (element == _("f_{z(x^2-y^2)}:p_x")) out = sqrt(15)/2*l*n*(l*l-m*m)*pfs-sqrt(5./8)*l*n*(3*(l*l-m*m)-2)*pfp;
    else if (element == _("p_x:f_{x(x^2-3y^2)}")) out = sqrt(5./8)*l*l*(l*l-3*m*m)*pfs-sqrt(15)/4*(l*l*(l*l-3*m*m)+m*m-l*l)*pfp; //5
    else if (element == _("f_{x(x^2-3y^2)}:p_x")) out = sqrt(5./8)*l*l*(l*l-3*m*m)*pfs-sqrt(15)/4*(l*l*(l*l-3*m*m)+m*m-l*l)*pfp;

    // dxy - f  4
    else if (element == _("d_{xy}:f_{y(3x^2-y^2)}")) out = sqrt(15)/8*l*m*m*(3*l*l-m*m)*dfs-sqrt(15)/4*l*(2*m*m*(3*l*l-m*m)+n*n-1)*dfp+sqrt(3./8)*l*(m*m*(3*l*l-m*m)-2*n*n)*dfd; //6
    else if (element == _("f_{y(3x^2-y^2)}:d_{xy}")) out = -sqrt(15)/8*l*m*m*(3*l*l-m*m)*dfs+sqrt(15)/4*l*(2*m*m*(3*l*l-m*m)+n*n-1)*dfp-sqrt(3./8)*l*(m*m*(3*l*l-m*m)-2*n*n)*dfd;
    else if (element == _("d_{xy}:f_{xyz}")) out = sqrt(45)*l*l*m*m*n*dfs-sqrt(5./2)*n*(6*l*l*m*m+n*n-1)*dfp+n*(3*l*l*m*m+2*n*n-1)*dfd;  //4
    else if (element == _("f_{xyz}:d_{xy}")) out = -sqrt(45)*l*l*m*m*n*dfs+sqrt(5./2)*n*(6*l*l*m*m+n*n-1)*dfp-n*(3*l*l*m*m+2*n*n-1)*dfd;
    else if (element == _("d_{xy}:f_{y(5z^2-r^2)}")) out = 3/sqrt(8)*l*m*m*(5*n*n-1)*dfs-l/4*((6*m*m-1)*(5*n*n-1)+4*m*m)*dfp+sqrt(5./8)*l*(m*m*(3*n*n+1)-2*n*n)*dfd; //2
    else if (element == _("f_{y(5z^2-r^2)}:d_{xy}")) out = -(3/sqrt(8)*l*m*m*(5*n*n-1)*dfs-l/4*((6*m*m-1)*(5*n*n-1)+4*m*m)*dfp+sqrt(5./8)*l*(m*m*(3*n*n+1)-2*n*n)*dfd);
    else if (element == _("d_{xy}:f_{z(5z^2-3r^2)}")) out = sqrt(3)/2*l*m*n*(5*n*n-3)*dfs-sqrt(3./2)*l*m*n*(5*n*n-1)*dfs+sqrt(15)/2*l*m*n*(n*n+1)*dfd;  //0
    else if (element == _("f_{z(5z^2-3r^2)}:d_{xy}")) out = -( sqrt(3)/2*l*m*n*(5*n*n-3)*dfs-sqrt(3./2)*l*m*n*(5*n*n-1)*dfs+sqrt(15)/2*l*m*n*(n*n+1)*dfd );
    else if (element == _("d_{xy}:f_{x(5z^2-r^2)}")) out = 3/sqrt(8)*l*l*m*(5*n*n-1)*dfs-m/4*((6*l*l-1)*(5*n*n-1)+4*l*l)*dfp+sqrt(5./8)*m*(l*l*(3*n*n+1)-2*n*n)*dfd; //1
    else if (element == _("f_{x(5z^2-r^2)}:d_{xy}")) out = -(3/sqrt(8)*l*l*m*(5*n*n-1)*dfs-m/4*((6*l*l-1)*(5*n*n-1)+4*l*l)*dfp+sqrt(5./8)*m*(l*l*(3*n*n+1)-2*n*n)*dfd);
    else if (element == _("d_{xy}:f_{z(x^2-y^2)}")) out = sqrt(45)/2*l*m*n*(l*l-m*m)*dfs-sqrt(45)/2*l*m*n*(l*l-m*m)*dfp+3./2*l*m*n*(l*l-m*m)*dfd;   //3
    else if (element == _("f_{z(x^2-y^2)}:d_{xy}")) out = -(sqrt(45)/2*l*m*n*(l*l-m*m)*dfs-sqrt(45)/2*l*m*n*(l*l-m*m)*dfp+3./2*l*m*n*(l*l-m*m)*dfd);
    else if (element == _("d_{xy}:f_{x(x^2-3y^2)}")) out = sqrt(15./8)*l*l*m*(l*l-3*m*m)*dfs-sqrt(15)/4*m*(2*l*l*(l*l-3*m*m)-n*n+1)*dfp+sqrt(3./8)*m*(l*l*(l*l-3*m*m)-2*n*n)*dfd;  //5
    else if (element == _("f_{x(x^2-3y^2)}:d_{xy}")) out = -(sqrt(15./8)*l*l*m*(l*l-3*m*m)*dfs-sqrt(15)/4*m*(2*l*l*(l*l-3*m*m)-n*n+1)*dfp+sqrt(3./8)*m*(l*l*(l*l-3*m*m)-2*n*n)*dfd);

    // dyz - f  2
    else if (element == _("d_{yz}:f_{y(3x^2-y^2)}")) out = sqrt(15./8)*m*m*n*(3*l*l-m*m)*dfs-sqrt(15)/4*n*(2*m*m*(3*l*l-m*m)-l*l+m*m)*dfp+sqrt(3/8)*n*(m*m*(3*l*l-m*m)-2*l*l+2*m*m)*dfd; //6
    else if (element == _("f_{y(3x^2-y^2)}:d_{yz}")) out = -(sqrt(15./8)*m*m*n*(3*l*l-m*m)*dfs-sqrt(15)/4*n*(2*m*m*(3*l*l-m*m)-l*l+m*m)*dfp+sqrt(3/8)*n*(m*m*(3*l*l-m*m)-2*l*l+2*m*m)*dfd);
    else if (element == _("d_{yz}:f_{xyz}")) out = sqrt(45)*l*m*m*n*n*dfs-sqrt(5./2)*l*(6*m*m*n*n+l*l-1)*dfp+l*(3*m*m*n*n+2*l*l-1)*dfd;  //4
    else if (element == _("f_{xyz}:d_{yz}")) out = -(sqrt(45)*l*m*m*n*n*dfs-sqrt(5./2)*l*(6*m*m*n*n+l*l-1)*dfp+l*(3*m*m*n*n+2*l*l-1)*dfd);
    else if (element == _("d_{yz}:f_{y(5z^2-r^2)}")) out = 3/sqrt(8)*m*m*n*(5*n*n-1)*dfs-n/4*(m*m*(30*n*n-11)-4*n*n+l*l)*dfp+sqrt(5./8)*n*(n*n-1)*(3*m*m-2)*dfd; //2
    else if (element == _("f_{y(5z^2-r^2)}:d_{yz}")) out = -(3/sqrt(8)*m*m*n*(5*n*n-1)*dfs-n/4*(m*m*(30*n*n-11)-4*n*n+l*l)*dfp+sqrt(5./8)*n*(n*n-1)*(3*m*m-2)*dfd);
    else if (element == _("d_{yz}:f_{z(5z^2-3r^2)}")) out = sqrt(3)/2*m*n*n*(5*n*n-3)*dfs-sqrt(3./8)*m*(5*n*n-1)*(2*n*n-1)*dfp+sqrt(15)/2*m*n*n*(n*n-1)*dfd;//0
    else if (element == _("f_{z(5z^2-3r^2)}:d_{yz}")) out = -(sqrt(3)/2*m*n*n*(5*n*n-3)*dfs-sqrt(3./8)*m*(5*n*n-1)*(2*n*n-1)*dfp+sqrt(15)/2*m*n*n*(n*n-1)*dfd);
    else if (element == _("d_{yz}:f_{x(5z^2-r^2)}")) out = 3/sqrt(8)*l*m*n*(5*n*n-1)*dfs-3*l*m*n/2*(5*n*n-2)*dfp+sqrt(45)/8*l*m*n*(n*n-1)*dfd; //1
    else if (element == _("f_{x(5z^2-r^2)}:d_{yz}")) out = -(3/sqrt(8)*l*m*n*(5*n*n-1)*dfs-3*l*m*n/2*(5*n*n-2)*dfp+sqrt(45)/8*l*m*n*(n*n-1)*dfd);
    else if (element == _("d_{yz}:f_{z(x^2-y^2)}")) out = sqrt(45)/2*m*n*n*(l*l-m*m)*dfs-sqrt(5./8)*m*((6*n*n-1)*(l*l-m*m)+2*n*n)*dfp+m/2*(3*n*n*(l*l-m*m)-4*l*l+2*n*n)*dfd; //3
    else if (element == _("f_{z(x^2-y^2)}:d_{yz}")) out = -(sqrt(45)/2*m*n*n*(l*l-m*m)*dfs-sqrt(5./8)*m*((6*n*n-1)*(l*l-m*m)+2*n*n)*dfp+m/2*(3*n*n*(l*l-m*m)-4*l*l+2*n*n)*dfd);
    else if (element == _("d_{yz}:f_{x(x^2-3y^2)}")) out = sqrt(15./8)*l*m*n*(l*l-3*m*m)*dfs-sqrt(15)/2*l*m*n*(l*l-3*m*m+1)*dfp+sqrt(3./8)*l*m*n*(l*l-3*m*m+4)*dfd; //5
    else if (element == _("f_{x(x^2-3y^2)}:d_{yz}")) out = -(sqrt(15./8)*l*m*n*(l*l-3*m*m)*dfs-sqrt(15)/2*l*m*n*(l*l-3*m*m+1)*dfp+sqrt(3./8)*l*m*n*(l*l-3*m*m+4)*dfd);

    // d 3z2-r2 - f  0
    else if (element == _("d_{3z^2-r^2}:f_{y(3x^2-y^2)}")) out = sqrt(5./32)*m*(3*n*n-1)*(3*l*l-m*m)*dfs-sqrt(45)/4*m*n*n*(3*l*l-m*m)*dfp+3/sqrt(32)*m*(n*n+1)*(3*l*l-m*m)*dfd; //6
    else if (element == _("f_{y(3x^2-y^2)}:d_{3z^2-r^2}")) out = -(sqrt(5./32)*m*(3*n*n-1)*(3*l*l-m*m)*dfs-sqrt(45)/4*m*n*n*(3*l*l-m*m)*dfp+3/sqrt(32)*m*(n*n+1)*(3*l*l-m*m)*dfd);
    else if (element == _("d_{3z^2-r^2}:f_{xyz}")) out = sqrt(15)/2*l*m*n*(3*n*n-l)*dfs-sqrt(15./2)*l*m*n*(3*n*n-1)*dfp+sqrt(3)/2*l*m*n*(3*n*n-1)*dfd;   //4
    else if (element == _("f_{xyz}:d_{3z^2-r^2}")) out = -(sqrt(15)/2*l*m*n*(3*n*n-l)*dfs-sqrt(15./2)*l*m*n*(3*n*n-1)*dfp+sqrt(3)/2*l*m*n*(3*n*n-1)*dfd);
    else if (element == _("d_{3z^2-r^2}:f_{y(5z^2-r^2)}")) out = sqrt(3./32)*m*(3*n*n-1)*(5*n*n-1)*dfs-sqrt(3)/4*m*n*n*(15*n*n-11)*dfp+sqrt(15./32)*m*(n*n-1)*(3*n*n-1)*dfd;  //2
    else if (element == _("f_{y(5z^2-r^2)}:d_{3z^2-r^2}")) out = -(sqrt(3./32)*m*(3*n*n-1)*(5*n*n-1)*dfs-sqrt(3)/4*m*n*n*(15*n*n-11)*dfp+sqrt(15./32)*m*(n*n-1)*(3*n*n-1)*dfd);
    else if (element == _("d_{3z^2-r^2}:f_{z(5z^2-3r^2)}")) out = n/4*(3*n*n-1)*(5*n*n-3)*dfs-3/sqrt(8)*n*(5*n*n-1)*(n*n-1)*dfp+sqrt(45)/4*n*(n*n-1)*(n*n-1)*dfd;  //0
    else if (element == _("f_{z(5z^2-3r^2)}:d_{3z^2-r^2}")) out = -(n/4*(3*n*n-1)*(5*n*n-3)*dfs-3/sqrt(8)*n*(5*n*n-1)*(n*n-1)*dfp+sqrt(45)/4*n*(n*n-1)*(n*n-1)*dfd);
    else if (element == _("d_{3z^2-r^2}:f_{x(5z^2-r^2)}")) out = sqrt(3./32)*l*(3*n*n-1)*(5*n*n-1)*dfs-sqrt(3)/4*l*n*n*(15*n*n-11)*dfp+sqrt(15./32)*l*(n*n-1)*(3*n*n-1)*dfd;   //1
    else if (element == _("f_{x(5z^2-r^2)}:d_{3z^2-r^2}")) out = -(sqrt(3./32)*l*(3*n*n-1)*(5*n*n-1)*dfs-sqrt(3)/4*l*n*n*(15*n*n-11)*dfp+sqrt(15./32)*l*(n*n-1)*(3*n*n-1)*dfd);
    else if (element == _("d_{3z^2-r^2}:f_{z(x^2-y^2)}")) out = sqrt(15)/4*n*(3*n*n-1)*(l*l-m*m)*dfs-sqrt(15./8)*n*(3*n*n-1)*(l*l-m*m)*dfp+sqrt(3)/4*n*(3*n*n-1)*(l*l-m*m)*dfd; //3
    else if (element == _("f_{z(x^2-y^2)}:d_{3z^2-r^2}")) out = -(sqrt(15)/4*n*(3*n*n-1)*(l*l-m*m)*dfs-sqrt(15./8)*n*(3*n*n-1)*(l*l-m*m)*dfp+sqrt(3)/4*n*(3*n*n-1)*(l*l-m*m)*dfd);
    else if (element == _("d_{3z^2-r^2}:f_{x(x^2-3y^2)}")) out = sqrt(5./32)*l*(3*n*n-1)*(l*l-3*m*m)*dfs-sqrt(45)/4*l*n*n*(l*l-3*m*m)*dfp+3/sqrt(32)*l*(n*n+1)*(l*l-3*m*m)*dfd; //5
    else if (element == _("f_{x(x^2-3y^2)}:d_{3z^2-r^2}")) out = -(sqrt(5./32)*l*(3*n*n-1)*(l*l-3*m*m)*dfs-sqrt(45)/4*l*n*n*(l*l-3*m*m)*dfp+3/sqrt(32)*l*(n*n+1)*(l*l-3*m*m)*dfd);

    // dxz - f  1
    else if (element == _("d_{xz}:f_{y(3x^2-y^2)}")) out = sqrt(15./8)*l*m*n*(3*l*l-m*m)*dfs-sqrt(15)/2*l*m*n*(3*l*l-m*m-1)*dfp+sqrt(3/8)*l*m*n*(3*l*l-m*m-4)*dfd; //6
    else if (element == _("f_{y(3x^2-y^2)}:d_{xz}")) out = -(sqrt(15./8)*l*m*n*(3*l*l-m*m)*dfs-sqrt(15)/2*l*m*n*(3*l*l-m*m-1)*dfp+sqrt(3/8)*l*m*n*(3*l*l-m*m-4)*dfd);
    else if (element == _("d_{xz}:f_{xyz}")) out = sqrt(45)*l*l*m*n*n*dfs-sqrt(5./2)*m*(6*l*l*n*n+m*m-1)*dfp+m*(3*l*l*n*n+2*m*m-1)*dfd;   //4
    else if (element == _("f_{xyz}:d_{xz}")) out = -(sqrt(45)*l*l*m*n*n*dfs-sqrt(5./2)*m*(6*l*l*n*n+m*m-1)*dfp+m*(3*l*l*n*n+2*m*m-1)*dfd);
    else if (element == _("d_{xz}:f_{y(5z^2-r^2)}")) out = 3/sqrt(8)*l*m*n*(5*n*n-1)*dfs-3*l*m*n/2*(5*n*n-2)*dfp+sqrt(45./8)*l*m*n*(n*n-1)*dfd; //2
    else if (element == _("f_{y(5z^2-r^2)}:d_{xz}")) out = -(3/sqrt(8)*l*m*n*(5*n*n-1)*dfs-3*l*m*n/2*(5*n*n-2)*dfp+sqrt(45./8)*l*m*n*(n*n-1)*dfd);
    else if (element == _("d_{xz}:f_{z(5z^2-3r^2)}")) out = sqrt(3)/2*l*n*n*(5*n*n-3)*dfs-sqrt(3./8)*l*(5*n*n-1)*(2*n*n-1)*dfp+sqrt(15)/2*l*n*n*(n*n-1)*dfd;  //0
    else if (element == _("f_{z(5z^2-3r^2)}:d_{xz}")) out = -(sqrt(3)/2*l*n*n*(5*n*n-3)*dfs-sqrt(3./8)*l*(5*n*n-1)*(2*n*n-1)*dfp+sqrt(15)/2*l*n*n*(n*n-1)*dfd);
    else if (element == _("d_{xz}:f_{x(5z^2-r^2)}")) out = 3/sqrt(8)*l*l*n*(5*n*n-1)*dfs-n/4*(l*l*(30*n*n-11)-4*n*n+m*m)*dfp+sqrt(5./8)*n*(n*n-1)*(3*l*l-2)*dfd;  //1
    else if (element == _("f_{x(5z^2-r^2)}:d_{xz}")) out = -(3/sqrt(8)*l*l*n*(5*n*n-1)*dfs-n/4*(l*l*(30*n*n-11)-4*n*n+m*m)*dfp+sqrt(5./8)*n*(n*n-1)*(3*l*l-2)*dfd);
    else if (element == _("d_{xz}:f_{z(x^2-y^2)}")) out = sqrt(45)/2*l*n*n*(l*l-m*m)*dfs-sqrt(5./8)*l*((6*n*n-1)*(l*l-m*m)-2*n*n)*dfp+l/2*(3*n*n*(l*l-m*m)+4*m*m-2*n*n)*dfd; //3
    else if (element == _("f_{z(x^2-y^2)}:d_{xz}")) out = -(sqrt(45)/2*l*n*n*(l*l-m*m)*dfs-sqrt(5./8)*l*((6*n*n-1)*(l*l-m*m)-2*n*n)*dfp+l/2*(3*n*n*(l*l-m*m)+4*m*m-2*n*n)*dfd);
    else if (element == _("d_{xz}:f_{x(x^2-3y^2)}")) out = sqrt(15./8)*l*l*n*(l*l-3*m*m)*dfs-sqrt(15)/4*n*(2*l*l*(l*l-3*m*m)-l*l+m*m)*dfp+sqrt(3./8)*n*(l*l*(l*l-3*m*m)-2*l*l+2*m*m)*dfd;//5
    else if (element == _("f_{x(x^2-3y^2)}:d_{xz}")) out = -(sqrt(15./8)*l*l*n*(l*l-3*m*m)*dfs-sqrt(15)/4*n*(2*l*l*(l*l-3*m*m)-l*l+m*m)*dfp+sqrt(3./8)*n*(l*l*(l*l-3*m*m)-2*l*l+2*m*m)*dfd);

    // d x2-y2 - f  3
    else if (element == _("d_{x^2-y^2}:f_{y(3x^2-y^2)}")) out = sqrt(15./32)*m*(l*l-m*m)*(3*l*l-m*m)*dfs-sqrt(15)/4*m*((l*l-m*m)*(3*l*l-m*m)+n*n-1)*dfp+sqrt(3./32)*m*((l*l-m*m)*(3*l*l-m*m)+4*n*n)*dfd; //6
    else if (element == _("f_{y(3x^2-y^2)}:d_{x^2-y^2}")) out = -(sqrt(15./32)*m*(l*l-m*m)*(3*l*l-m*m)*dfs-sqrt(15)/4*m*((l*l-m*m)*(3*l*l-m*m)+n*n-1)*dfp+sqrt(3./32)*m*((l*l-m*m)*(3*l*l-m*m)+4*n*n)*dfd);
    else if (element == _("d_{x^2-y^2}:f_{xyz}")) out = sqrt(45)/2*l*m*n*(l*l-m*m)*dfs-sqrt(45)/2*l*m*n*(l*l-m*m)*dfp+3/2*l*m*n*(l*l-m*m)*dfd;  //4
    else if (element == _("f_{xyz}:d_{x^2-y^2}")) out = -(sqrt(45)/2*l*m*n*(l*l-m*m)*dfs-sqrt(45)/2*l*m*n*(l*l-m*m)*dfp+3/2*l*m*n*(l*l-m*m)*dfd);
    else if (element == _("d_{x^2-y^2}:f_{y(5z^2-r^2)}")) out = 3/sqrt(32)*m*(l*l-m*m)*(5*n*n-1)*dfs-m/4*(15*n*n*(l*l-m*m)+4*n*n-2*l*l)*dfp+sqrt(5./32)*m*((l*l-m*m)*(3*n*n+1)+4*n*n)*dfd;  //2
    else if (element == _("f_{y(5z^2-r^2)}:d_{x^2-y^2}")) out = -(3/sqrt(32)*m*(l*l-m*m)*(5*n*n-1)*dfs-m/4*(15*n*n*(l*l-m*m)+4*n*n-2*l*l)*dfp+sqrt(5./32)*m*((l*l-m*m)*(3*n*n+1)+4*n*n)*dfd);
    else if (element == _("p_y:f_{z(5z^2-3r^2)}")) out = sqrt(3)/4*n*(5*n*n-3)*(l*l-m*m)*dfs-sqrt(3./8)*n*(5*n*n-1)*(l*l-m*m)*dfs+sqrt(15)/4*n*(n*n+1)*(l*l-m*m)*dfd;  //0
    else if (element == _("f_{z(5z^2-3r^2)}:d_{x^2-y^2}")) out = -(sqrt(3)/4*n*(5*n*n-3)*(l*l-m*m)*dfs-sqrt(3./8)*n*(5*n*n-1)*(l*l-m*m)*dfs+sqrt(15)/4*n*(n*n+1)*(l*l-m*m)*dfd);
    else if (element == _("d_{x^2-y^2}:f_{x(5z^2-r^2)}")) out = 3/sqrt(32)*l*(5*n*n-1)*(l*l-m*m)*dfs-l/4*(15*n*n*(l*l-m*m)+2*m*m-4*n*n)*dfp+sqrt(5./32)*l*((l*l-m*m)*(3*n*n+1)-4*n*n)*dfd;   //1
    else if (element == _("f_{x(5z^2-r^2)}:d_{x^2-y^2}")) out = -(3/sqrt(32)*l*(5*n*n-1)*(l*l-m*m)*dfs-l/4*(15*n*n*(l*l-m*m)+2*m*m-4*n*n)*dfp+sqrt(5./32)*l*((l*l-m*m)*(3*n*n+1)-4*n*n)*dfd);
    else if (element == _("d_{x^2-y^2}:f_{z(x^2-y^2)}")) out = sqrt(45)/4*n*(l*l-m*m)*(l*l-m*m)*dfs-sqrt(5./8)*n*(3*(l*l-m*m)*(l*l-m*m)+2*n*n-2)*dfp+n/4*(3*(l*l-m*m)*(l*l-m*m)+8*n*n-4)*dfd; //3
    else if (element == _("f_{z(x^2-y^2)}:d_{x^2-y^2}")) out = -(sqrt(45)/4*n*(l*l-m*m)*(l*l-m*m)*dfs-sqrt(5./8)*n*(3*(l*l-m*m)*(l*l-m*m)+2*n*n-2)*dfp+n/4*(3*(l*l-m*m)*(l*l-m*m)+8*n*n-4)*dfd);
    else if (element == _("d_{x^2-y^2}:f_{x(x^2-3y^2)}")) out = sqrt(15./32)*l*(l*l-m*m)*(l*l-3*m*m)*dfs-sqrt(15)/4*l*((l*l-m*m)*(l*l-3*m*m)-n*n+1)*dfp+sqrt(3./32)*l*((l*l-m*m)*(l*l-3*m*m)+4*n*n)*dfd;  //5
    else if (element == _("f_{x(x^2-3y^2)}:d_{x^2-y^2}")) out = -(sqrt(15./32)*l*(l*l-m*m)*(l*l-3*m*m)*dfs-sqrt(15)/4*l*((l*l-m*m)*(l*l-3*m*m)-n*n+1)*dfp+sqrt(3./32)*l*((l*l-m*m)*(l*l-3*m*m)+4*n*n)*dfd);

    return out;
}

void Sec30::ConstructTBHamiltonian(double a[3], double b[3], double c[3], double** XYZCoords, Adouble2D &Hi, Adouble2D &Hf, int &nEssensialCells, int &nHamiltonian, Aint1D &EssCells, bool isSOC, Adouble2D &SOC_i, Adouble2D &SOC_f)
{
    wxListBox* listctr = this->GetListObject(_("EssentialUnitcellList"));
    int nCell = listctr->GetCount();
    nEssensialCells = nCell;
    
    myGrid* OnSiteCtr = this->GetGridObject(_("OS"));
    myGrid* SKCtr = this->GetGridObject(_("SK"));
    myGrid* OverlapCtr = this->GetGridObject(_("OL"));
    
    int nUnitcellAtoms = 0;
    this->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    wxCheckTree* orbs = this->GetTreeObject(_("Orbitals"));
    Astring0D HamiltonianMap = this->ArraysOf1DString[1];
    nHamiltonian = HamiltonianMap.size();
    Aint1D HamiltonianDimMap = this->ArraysOf2DInt[0];
    wxCheckTree* bonds = this->GetTreeObject(_("Bonds"));
    wxTreeItemId rootID = bonds->GetRootItem();
    EssCells.clear();
    for (int iCell=0; iCell<nCell; iCell++)
    {
        Aint0D lmnOfCell;
        wxString WorkingCell = listctr->GetString(iCell);
        wxString ucell = _("(0,0,0)-") + WorkingCell;
        int lcell,mcell,ncell;
        GetCellInfo(WorkingCell, lcell, mcell, ncell);
        lmnOfCell.push_back(lcell);
        lmnOfCell.push_back(mcell);
        lmnOfCell.push_back(ncell);
        EssCells.push_back(lmnOfCell);
        wxTreeItemId CellID = bonds->FindItemIn(rootID, ucell);
        Adouble1D hi(nHamiltonian,std::vector<double>(nHamiltonian));
        Adouble1D hf(nHamiltonian,std::vector<double>(nHamiltonian));
        if (isSOC)
        {
            SOC_i = Adouble2D(2, Adouble1D(2*nHamiltonian, Adouble0D(2*nHamiltonian, 0.0 ) ) );
            SOC_f = Adouble2D(2, Adouble1D(2*nHamiltonian, Adouble0D(2*nHamiltonian, 0.0 ) ) );
        }
        if (CellID.IsOk())
        {
            if (bonds->GetItemState(CellID) >= wxCheckTree::CHECKED) GetCouplingMatrix(SKCtr, OverlapCtr, bonds, orbs, a, b, c, XYZCoords, HamiltonianDimMap, CellID, WorkingCell, hi, hf);
        }
        
        if (WorkingCell == _("(0,0,0)"))
        {
            AddOnSiteMatrix(OnSiteCtr, orbs, HamiltonianDimMap, hi, hf, isSOC, SOC_i, SOC_f);
        }
        
        Hi.push_back(hi);
        Hf.push_back(hf);
    }
}

void Sec30::ConstructTBHamiltonian(double a[3], double b[3], double c[3], double** XYZCoords, Adouble2D &Hi, Adouble2D &Hf, Adouble2D &Si, Adouble2D &Sf, int &nEssensialCells, int &nHamiltonian, Aint1D &EssCells, bool isSOC, Adouble2D &SOC_i, Adouble2D &SOC_f)
{
    wxListBox* listctr = this->GetListObject(_("EssentialUnitcellList"));
    int nCell = listctr->GetCount();
    nEssensialCells = nCell;
    
    myGrid* OnSiteCtr = this->GetGridObject(_("OS"));
    myGrid* SKCtr = this->GetGridObject(_("SK"));
    myGrid* OverlapCtr = this->GetGridObject(_("OL"));
    
    int nUnitcellAtoms = 0;
    this->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    wxCheckTree* orbs = this->GetTreeObject(_("Orbitals"));
    Astring0D HamiltonianMap = this->ArraysOf1DString[1];
    nHamiltonian = HamiltonianMap.size();
    Aint1D HamiltonianDimMap = this->ArraysOf2DInt[0];
    wxCheckTree* bonds = this->GetTreeObject(_("Bonds"));
    wxTreeItemId rootID = bonds->GetRootItem();
    EssCells.clear();
    for (int iCell=0; iCell<nCell; iCell++)
    {
        Aint0D lmnOfCell;
        wxString WorkingCell = listctr->GetString(iCell);
        wxString ucell = _("(0,0,0)-") + WorkingCell;
        int lcell,mcell,ncell;
        GetCellInfo(WorkingCell, lcell, mcell, ncell);
        lmnOfCell.push_back(lcell);
        lmnOfCell.push_back(mcell);
        lmnOfCell.push_back(ncell);
        EssCells.push_back(lmnOfCell);
        wxTreeItemId CellID = bonds->FindItemIn(rootID, ucell);
        Adouble1D hi(nHamiltonian,std::vector<double>(nHamiltonian));
        Adouble1D hf(nHamiltonian,std::vector<double>(nHamiltonian));
        Adouble1D si(nHamiltonian,std::vector<double>(nHamiltonian));
        Adouble1D sf(nHamiltonian,std::vector<double>(nHamiltonian));
        if (isSOC)
        {
            SOC_i = Adouble2D(2, Adouble1D(2*nHamiltonian, Adouble0D(2*nHamiltonian, 0.0 ) ) );
            SOC_f = Adouble2D(2, Adouble1D(2*nHamiltonian, Adouble0D(2*nHamiltonian, 0.0 ) ) );
        }
        if (CellID.IsOk())
        {
            if (bonds->GetItemState(CellID) >= wxCheckTree::CHECKED) GetCouplingMatrix(SKCtr, OverlapCtr, bonds, orbs, a, b, c, XYZCoords, HamiltonianDimMap, CellID, WorkingCell, hi, hf, si, sf);
        }
        
        if (WorkingCell == _("(0,0,0)"))
        {
            AddOnSiteMatrix(OnSiteCtr, orbs, HamiltonianDimMap, hi, hf, si, sf, isSOC, SOC_i, SOC_f);
        }
        
        Hi.push_back(hi);
        Hf.push_back(hf);
        Si.push_back(si);
        Sf.push_back(sf);
    }
}

void Sec30::ConstructTBHamiltonianF(double a[3], double b[3], double c[3], double** XYZCoords, Adouble2D &Hf, int &nEssensialCells, int &nHamiltonian, Aint1D &EssCells, bool isSOC, Adouble2D &SOC_f)
{
    wxListBox* listctr = this->GetListObject(_("EssentialUnitcellList"));
    int nCell = listctr->GetCount();
    nEssensialCells = nCell;
    
    myGrid* OnSiteCtr = this->GetGridObject(_("OS"));
    myGrid* SKCtr = this->GetGridObject(_("SK"));
    myGrid* OverlapCtr = this->GetGridObject(_("OL"));
    
    int nUnitcellAtoms = 0;
    this->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    wxCheckTree* orbs = this->GetTreeObject(_("Orbitals"));
    Astring0D HamiltonianMap = this->ArraysOf1DString[1];
    nHamiltonian = HamiltonianMap.size();
    Aint1D HamiltonianDimMap = this->ArraysOf2DInt[0];
    wxCheckTree* bonds = this->GetTreeObject(_("Bonds"));
    wxTreeItemId rootID = bonds->GetRootItem();
    EssCells.clear();
    for (int iCell=0; iCell<nCell; iCell++)
    {
        Aint0D lmnOfCell;
        wxString WorkingCell = listctr->GetString(iCell);
        wxString ucell = _("(0,0,0)-") + WorkingCell;
        int lcell,mcell,ncell;
        GetCellInfo(WorkingCell, lcell, mcell, ncell);
        lmnOfCell.push_back(lcell);
        lmnOfCell.push_back(mcell);
        lmnOfCell.push_back(ncell);
        EssCells.push_back(lmnOfCell);
        wxTreeItemId CellID = bonds->FindItemIn(rootID, ucell);
        Adouble1D hf(nHamiltonian,std::vector<double>(nHamiltonian));
        if (isSOC) SOC_f = Adouble2D(2, Adouble1D(2*nHamiltonian, Adouble0D(2*nHamiltonian, 0.0 ) ) );
        if (CellID.IsOk())
        {
            if (bonds->GetItemState(CellID) >= wxCheckTree::CHECKED) GetCouplingMatrixF(SKCtr, OverlapCtr, bonds, orbs, a, b, c, XYZCoords, HamiltonianDimMap, CellID, WorkingCell, hf);
        }
        
        if (WorkingCell == _("(0,0,0)"))
        {
            AddOnSiteMatrixF(OnSiteCtr, orbs, HamiltonianDimMap, hf, isSOC, SOC_f);
        }
        
        Hf.push_back(hf);
    }
}

void Sec30::ConstructTBHamiltonianF(double a[3], double b[3], double c[3], double** XYZCoords, Adouble2D &Hf, Adouble2D &Sf, int &nEssensialCells, int &nHamiltonian, Aint1D &EssCells, bool isSOC, Adouble2D &SOC_f)
{
    wxListBox* listctr = this->GetListObject(_("EssentialUnitcellList"));
    int nCell = listctr->GetCount();
    nEssensialCells = nCell;
    
    myGrid* OnSiteCtr = this->GetGridObject(_("OS"));
    myGrid* SKCtr = this->GetGridObject(_("SK"));
    myGrid* OverlapCtr = this->GetGridObject(_("OL"));
    
    int nUnitcellAtoms = 0;
    this->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    wxCheckTree* orbs = this->GetTreeObject(_("Orbitals"));
    Astring0D HamiltonianMap = this->ArraysOf1DString[1];
    nHamiltonian = HamiltonianMap.size();
    Aint1D HamiltonianDimMap = this->ArraysOf2DInt[0];
    wxCheckTree* bonds = this->GetTreeObject(_("Bonds"));
    wxTreeItemId rootID = bonds->GetRootItem();
    EssCells.clear();
    for (int iCell=0; iCell<nCell; iCell++)
    {
        Aint0D lmnOfCell;
        wxString WorkingCell = listctr->GetString(iCell);
        wxString ucell = _("(0,0,0)-") + WorkingCell;
        int lcell,mcell,ncell;
        GetCellInfo(WorkingCell, lcell, mcell, ncell);
        lmnOfCell.push_back(lcell);
        lmnOfCell.push_back(mcell);
        lmnOfCell.push_back(ncell);
        EssCells.push_back(lmnOfCell);
        wxTreeItemId CellID = bonds->FindItemIn(rootID, ucell);
        Adouble1D hf(nHamiltonian,std::vector<double>(nHamiltonian));
        Adouble1D sf(nHamiltonian,std::vector<double>(nHamiltonian));
        if (isSOC) SOC_f = Adouble2D(2, Adouble1D(2*nHamiltonian, Adouble0D(2*nHamiltonian, 0.0 ) ) );
        if (CellID.IsOk())
        {
            if (bonds->GetItemState(CellID) >= wxCheckTree::CHECKED) GetCouplingMatrixF(SKCtr, OverlapCtr, bonds, orbs, a, b, c, XYZCoords, HamiltonianDimMap, CellID, WorkingCell, hf, sf);
        }
        
        if (WorkingCell == _("(0,0,0)"))
        {
            AddOnSiteMatrixF(OnSiteCtr, orbs, HamiltonianDimMap, hf, sf, isSOC, SOC_f);
        }
        
        Hf.push_back(hf);
        Sf.push_back(sf);
    }
}

void Sec30::GetCouplingMatrix(myGrid* SKCtr, myGrid* OverlapCtr, wxCheckTree* BondTree, wxCheckTree* orbs, double a[3], double b[3], double c[3], double** XYZCoords, Aint1D HamiltonianDimMap, wxTreeItemId CellID, wxString WorkingCell, Adouble1D &hi, Adouble1D &hf)
{
    if (!CellID.IsOk())
    {
        wxMessageBox(_("Fatal error occurred in thread REG01. Error code: GCMF001"),_("Error"));
        //Allocate h for zeros
        return;
    }
    
    int icell,jcell,kcell;
    GetCellInfo(WorkingCell, icell, jcell, kcell);
    
    double CellX = icell*a[0] + jcell*b[0] + kcell*c[0];
    double CellY = icell*a[1] + jcell*b[1] + kcell*c[1];
    double CellZ = icell*a[2] + jcell*b[2] + kcell*c[2];
            
    wxTreeItemId rootID = orbs->GetRootItem();
    wxString rootname = orbs->GetItemText(rootID);    
    
    wxTreeItemIdValue cookie;
	wxTreeItemId item = BondTree->GetFirstChild(CellID, cookie);
	while(item.IsOk())
	{
		wxString BondInfo = BondTree->GetItemText(item);
        //////////////////////////////////////////////
        if (BondTree->GetItemState(item) >= wxCheckTree::CHECKED)
        {
            int iAtomIndex,nShellIndex,jAtomIndex,mShellIndex,bondtype;
            this->GetBondInfo(BondInfo, iAtomIndex, nShellIndex, jAtomIndex, mShellIndex, bondtype);
            wxString BondStr = wxString::Format(wxT("Bond %d"), bondtype);
            
            Adouble0D iBondSK, fBondSK;
            GetBondSK(SKCtr, BondStr, iBondSK, fBondSK);
            
            int Dim1 = -1;
            int Dim2 = -1;
            bool IsShell1, IsShell2;
            wxString Orbs1, Orbs2;
            
            wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
            wxComboBox* comb1 = this->GetComboObject(atom1);
            wxString TBAtom1 = comb1->GetStringSelection();
            this->GetOrbitalInfo(orbs, TBAtom1, nShellIndex, Orbs1, Dim1, IsShell1);
            
            wxString atom2 = wxString::Format(wxT("AtomInd%d"),jAtomIndex + 1);
            wxComboBox* comb2 = this->GetComboObject(atom2);
            wxString TBAtom2 = comb2->GetStringSelection();
            this->GetOrbitalInfo(orbs, TBAtom2, mShellIndex, Orbs2, Dim2, IsShell2);

            double x2 = XYZCoords[jAtomIndex][0] + CellX;
            double y2 = XYZCoords[jAtomIndex][1] + CellY;
            double z2 = XYZCoords[jAtomIndex][2] + CellZ;
            double l, m, n;
            this->GetDirectionalCosines(XYZCoords[iAtomIndex][0], XYZCoords[iAtomIndex][1], XYZCoords[iAtomIndex][2], x2, y2, z2, l, m, n);
            
            double** iHopMat = new double*[Dim1];
            double** fHopMat = new double*[Dim1];
            for(int ii = 0; ii < Dim1; ii++)
            {
                iHopMat[ii] = new double[Dim2];
                fHopMat[ii] = new double[Dim2];
            }
            
            double** iHopMatT = new double*[Dim2];
            double** fHopMatT = new double*[Dim2];
            for(int ii = 0; ii < Dim2; ii++)
            {
                iHopMatT[ii] = new double[Dim1];
                fHopMatT[ii] = new double[Dim1];
            }
            
            Orbs1.Replace(_(" "),_(""));
            Orbs1.Replace(_("("),_(""), false);  // only remove the first (
            //Orbs1.Replace(_(")"),_(""));
            Orbs1.RemoveLast();                 // only remove the last )
            Orbs2.Replace(_(" "),_(""));
            Orbs2.Replace(_("("),_(""), false);  
            //Orbs2.Replace(_(")"),_(""));
            Orbs2.RemoveLast();
            int i=-1;
            wxStringTokenizer tokenizer1(Orbs1, ",");
            while (tokenizer1.HasMoreTokens())
            {
                i++;
                wxString o1 = tokenizer1.GetNextToken();
                
                int j=-1;
                wxStringTokenizer tokenizer2(Orbs2, ",");
                while (tokenizer2.HasMoreTokens())
                {
                    j++;
                    wxString o2 = tokenizer2.GetNextToken();
                    iHopMat[i][j] = this->Hopspd(iBondSK, l, m, n, o1, o2);
                    fHopMat[i][j] = this->Hopspd(fBondSK, l, m, n, o1, o2);
                    iHopMatT[j][i] = iHopMat[i][j];
                    fHopMatT[j][i] = fHopMat[i][j];
                }
            }
            
            int i0Ham = HamiltonianDimMap[iAtomIndex][nShellIndex - 1];
            int j0Ham = HamiltonianDimMap[jAtomIndex][mShellIndex - 1];
            
            if (icell==0 && jcell==0 && kcell==0)
            {
                for(int ii=0; ii<Dim1; ii++)
                    for(int jj=0; jj<Dim2; jj++)
                    {
                        int ih = i0Ham + ii;
                        int jh = j0Ham + jj;
                        hi[ih][jh] = iHopMat[ii][jj];
                        hf[ih][jh] = fHopMat[ii][jj];
                        hi[jh][ih] = iHopMatT[jj][ii];
                        hf[jh][ih] = fHopMatT[jj][ii];
                    }
            }
            else
            {
                for(int ii=0; ii<Dim1; ii++)
                    for(int jj=0; jj<Dim2; jj++)
                    {
                        int ih = i0Ham + ii;
                        int jh = j0Ham + jj;
                        hi[ih][jh] = iHopMat[ii][jj];
                        hf[ih][jh] = fHopMat[ii][jj];
                    }
            }
            
            for(int ii = 0; ii < Dim1; ii++)
            {
                if (Dim2 > 0)
                {
                    delete [] iHopMat[ii];
                    delete [] fHopMat[ii];
                }   
            }
            
            for(int ii = 0; ii < Dim2; ii++)
            {
                if (Dim1 > 0)
                {
                    delete [] iHopMatT[ii];
                    delete [] fHopMatT[ii];
                }   
            }
            
            if (Dim1>0)
            {
                delete [] iHopMat;
                delete [] fHopMat;
            }
            
            if (Dim2>0)
            {
                delete [] iHopMatT;
                delete [] fHopMatT;
            }
        }
        //////////////////////////////////////////////
		item = BondTree->GetNextChild(CellID, cookie);
	}
}

void Sec30::GetCouplingMatrix(myGrid* SKCtr, myGrid* OverlapCtr, wxCheckTree* BondTree, wxCheckTree* orbs, double a[3], double b[3], double c[3], double** XYZCoords, Aint1D HamiltonianDimMap, wxTreeItemId CellID, wxString WorkingCell, Adouble1D &hi, Adouble1D &hf, Adouble1D &si, Adouble1D &sf)
{
    if (!CellID.IsOk())
    {
        wxMessageBox(_("Fatal error occurred in thread REG01. Error code: GCMF001"),_("Error"));
        //Allocate h for zeros
        return;
    }
    
    int icell,jcell,kcell;
    GetCellInfo(WorkingCell, icell, jcell, kcell);
    
    double CellX = icell*a[0] + jcell*b[0] + kcell*c[0];
    double CellY = icell*a[1] + jcell*b[1] + kcell*c[1];
    double CellZ = icell*a[2] + jcell*b[2] + kcell*c[2];
            
    wxTreeItemId rootID = orbs->GetRootItem();
    wxString rootname = orbs->GetItemText(rootID);    
    
    wxTreeItemIdValue cookie;
	wxTreeItemId item = BondTree->GetFirstChild(CellID, cookie);
	while(item.IsOk())
	{
		wxString BondInfo = BondTree->GetItemText(item);
        //////////////////////////////////////////////
        if (BondTree->GetItemState(item) >= wxCheckTree::CHECKED)
        {
            int iAtomIndex,nShellIndex,jAtomIndex,mShellIndex,bondtype;
            this->GetBondInfo(BondInfo, iAtomIndex, nShellIndex, jAtomIndex, mShellIndex, bondtype);
            wxString BondStr = wxString::Format(wxT("Bond %d"), bondtype);
            
            Adouble0D iBondSK, fBondSK;
            GetBondSK(SKCtr, BondStr, iBondSK, fBondSK);
            
            Adouble0D iBondSK_s, fBondSK_s;
            GetBondSK(OverlapCtr, BondStr, iBondSK_s, fBondSK_s);
            
            int Dim1 = -1;
            int Dim2 = -1;
            bool IsShell1, IsShell2;
            wxString Orbs1, Orbs2;
            
            wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
            wxComboBox* comb1 = this->GetComboObject(atom1);
            wxString TBAtom1 = comb1->GetStringSelection();
            this->GetOrbitalInfo(orbs, TBAtom1, nShellIndex, Orbs1, Dim1, IsShell1);
            
            wxString atom2 = wxString::Format(wxT("AtomInd%d"),jAtomIndex + 1);
            wxComboBox* comb2 = this->GetComboObject(atom2);
            wxString TBAtom2 = comb2->GetStringSelection();
            this->GetOrbitalInfo(orbs, TBAtom2, mShellIndex, Orbs2, Dim2, IsShell2);

            double x2 = XYZCoords[jAtomIndex][0] + CellX;
            double y2 = XYZCoords[jAtomIndex][1] + CellY;
            double z2 = XYZCoords[jAtomIndex][2] + CellZ;
            double l, m, n;
            this->GetDirectionalCosines(XYZCoords[iAtomIndex][0], XYZCoords[iAtomIndex][1], XYZCoords[iAtomIndex][2], x2, y2, z2, l, m, n);
            
            double** iHopMat = new double*[Dim1];
            double** fHopMat = new double*[Dim1];
            double** iSMat = new double*[Dim1];
            double** fSMat = new double*[Dim1];
            for(int ii = 0; ii < Dim1; ii++)
            {
                iHopMat[ii] = new double[Dim2];
                fHopMat[ii] = new double[Dim2];
                iSMat[ii] = new double[Dim2];
                fSMat[ii] = new double[Dim2];
            }
            
            double** iHopMatT = new double*[Dim2];
            double** fHopMatT = new double*[Dim2];
            double** iSMatT = new double*[Dim2];
            double** fSMatT = new double*[Dim2];
            for(int ii = 0; ii < Dim2; ii++)
            {
                iHopMatT[ii] = new double[Dim1];
                fHopMatT[ii] = new double[Dim1];
                iSMatT[ii] = new double[Dim1];
                fSMatT[ii] = new double[Dim1];
            }
            
            Orbs1.Replace(_(" "),_(""));
            Orbs1.Replace(_("("),_(""), false);
            //Orbs1.Replace(_(")"),_(""));
            Orbs1.RemoveLast(); 
            Orbs2.Replace(_(" "),_(""));
            Orbs2.Replace(_("("),_(""), false);
            //Orbs2.Replace(_(")"),_(""));
            Orbs2.RemoveLast(); 
            int i=-1;
            wxStringTokenizer tokenizer1(Orbs1, ",");
            while (tokenizer1.HasMoreTokens())
            {
                i++;
                wxString o1 = tokenizer1.GetNextToken();
                
                int j=-1;
                wxStringTokenizer tokenizer2(Orbs2, ",");
                while (tokenizer2.HasMoreTokens())
                {
                    j++;
                    wxString o2 = tokenizer2.GetNextToken();
                    iHopMat[i][j] = this->Hopspd(iBondSK, l, m, n, o1, o2);
                    fHopMat[i][j] = this->Hopspd(fBondSK, l, m, n, o1, o2);
                    iHopMatT[j][i] = iHopMat[i][j];
                    fHopMatT[j][i] = fHopMat[i][j];
                    
                    iSMat[i][j] = this->Hopspd(iBondSK_s, l, m, n, o1, o2);
                    fSMat[i][j] = this->Hopspd(fBondSK_s, l, m, n, o1, o2);
                    iSMatT[j][i] = iSMat[i][j];
                    fSMatT[j][i] = fSMat[i][j];
                }
            }
            
            int i0Ham = HamiltonianDimMap[iAtomIndex][nShellIndex - 1];
            int j0Ham = HamiltonianDimMap[jAtomIndex][mShellIndex - 1];
            
            if (icell==0 && jcell==0 && kcell==0)
            {
                for(int ii=0; ii<Dim1; ii++)
                    for(int jj=0; jj<Dim2; jj++)
                    {
                        int ih = i0Ham + ii;
                        int jh = j0Ham + jj;
                        hi[ih][jh] = iHopMat[ii][jj];
                        hf[ih][jh] = fHopMat[ii][jj];
                        hi[jh][ih] = iHopMatT[jj][ii];
                        hf[jh][ih] = fHopMatT[jj][ii];
                        
                        si[ih][jh] = iSMat[ii][jj];
                        sf[ih][jh] = fSMat[ii][jj];
                        si[jh][ih] = iSMatT[jj][ii];
                        sf[jh][ih] = fSMatT[jj][ii];
                    }
            }
            else
            {
                for(int ii=0; ii<Dim1; ii++)
                    for(int jj=0; jj<Dim2; jj++)
                    {
                        int ih = i0Ham + ii;
                        int jh = j0Ham + jj;
                        hi[ih][jh] = iHopMat[ii][jj];
                        hf[ih][jh] = fHopMat[ii][jj];
                        
                        si[ih][jh] = iSMat[ii][jj];
                        sf[ih][jh] = fSMat[ii][jj];
                    }
            }
            
            for(int ii = 0; ii < Dim1; ii++)
            {
                if (Dim2 > 0)
                {
                    delete [] iHopMat[ii];
                    delete [] fHopMat[ii];
                    delete [] iSMat[ii];
                    delete [] fSMat[ii];
                }   
            }
            
            for(int ii = 0; ii < Dim2; ii++)
            {
                if (Dim1 > 0)
                {
                    delete [] iHopMatT[ii];
                    delete [] fHopMatT[ii];
                    delete [] iSMatT[ii];
                    delete [] fSMatT[ii];
                }   
            }
            
            if (Dim1>0)
            {
                delete [] iHopMat;
                delete [] fHopMat;
                delete [] iSMat;
                delete [] fSMat;
            }
            
            if (Dim2>0)
            {
                delete [] iHopMatT;
                delete [] fHopMatT;
                delete [] iSMatT;
                delete [] fSMatT;
            }
        }
        //////////////////////////////////////////////
		item = BondTree->GetNextChild(CellID, cookie);
	}
}

void Sec30::GetCouplingMatrixF(myGrid* SKCtr, myGrid* OverlapCtr, wxCheckTree* BondTree, wxCheckTree* orbs, double a[3], double b[3], double c[3], double** XYZCoords, Aint1D HamiltonianDimMap, wxTreeItemId CellID, wxString WorkingCell, Adouble1D &hf)
{
    if (!CellID.IsOk())
    {
        wxMessageBox(_("Sec30 kernel: Fatal error occurred in thread REG01. Error code: GCMF002"),_("Error"));
        //Allocate h for zeros
        return;
    }
    
    int icell,jcell,kcell;
    GetCellInfo(WorkingCell, icell, jcell, kcell);
    
    double CellX = icell*a[0] + jcell*b[0] + kcell*c[0];
    double CellY = icell*a[1] + jcell*b[1] + kcell*c[1];
    double CellZ = icell*a[2] + jcell*b[2] + kcell*c[2];
    
    wxTreeItemId rootID = orbs->GetRootItem();
    wxString rootname = orbs->GetItemText(rootID);    
    
    wxTreeItemIdValue cookie;
	wxTreeItemId item = BondTree->GetFirstChild(CellID, cookie);
	while(item.IsOk())
	{
		wxString BondInfo = BondTree->GetItemText(item);
        //////////////////////////////////////////////
        if (BondTree->GetItemState(item) >= wxCheckTree::CHECKED)
        {
            int iAtomIndex,nShellIndex,jAtomIndex,mShellIndex,bondtype;
            this->GetBondInfo(BondInfo, iAtomIndex, nShellIndex, jAtomIndex, mShellIndex, bondtype);
            wxString BondStr = wxString::Format(wxT("Bond %d"), bondtype);
            
            Adouble0D iBondSK, fBondSK;
            GetBondSKF(SKCtr, SKBuffer, BondStr, iBondSK, fBondSK);
            
            //wxString report = _("");
            //for (int ip=0; ip<4; ip++) report = report + wxString::Format(wxT("%.8f,"),fBondSK[ip]);
            //wxMessageBox(report,_("debug"));
            
            int Dim1 = -1;
            int Dim2 = -1;
            bool IsShell1, IsShell2;
            wxString Orbs1, Orbs2;
            
            wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
            wxComboBox* comb1 = this->GetComboObject(atom1);
            wxString TBAtom1 = comb1->GetStringSelection();
            this->GetOrbitalInfo(orbs, TBAtom1, nShellIndex, Orbs1, Dim1, IsShell1);
            
            wxString atom2 = wxString::Format(wxT("AtomInd%d"),jAtomIndex + 1);
            wxComboBox* comb2 = this->GetComboObject(atom2);
            wxString TBAtom2 = comb2->GetStringSelection();
            this->GetOrbitalInfo(orbs, TBAtom2, mShellIndex, Orbs2, Dim2, IsShell2);

            double x2 = XYZCoords[jAtomIndex][0] + CellX;
            double y2 = XYZCoords[jAtomIndex][1] + CellY;
            double z2 = XYZCoords[jAtomIndex][2] + CellZ;
            double l, m, n;
            this->GetDirectionalCosines(XYZCoords[iAtomIndex][0], XYZCoords[iAtomIndex][1], XYZCoords[iAtomIndex][2], x2, y2, z2, l, m, n);
            
            double** fHopMat = new double*[Dim1];
            for(int ii = 0; ii < Dim1; ii++) fHopMat[ii] = new double[Dim2];
            
            double** fHopMatT = new double*[Dim2];
            for(int ii = 0; ii < Dim2; ii++) fHopMatT[ii] = new double[Dim1];
            
            Orbs1.Replace(_(" "),_(""));
            Orbs1.Replace(_("("),_(""), false);
            //Orbs1.Replace(_(")"),_(""));
            Orbs1.RemoveLast(); 
            Orbs2.Replace(_(" "),_(""));
            Orbs2.Replace(_("("),_(""), false);
            //Orbs2.Replace(_(")"),_(""));
            Orbs2.RemoveLast(); 
            int i=-1;
            wxStringTokenizer tokenizer1(Orbs1, ",");
            while (tokenizer1.HasMoreTokens())
            {
                i++;
                wxString o1 = tokenizer1.GetNextToken();
                
                int j=-1;
                wxStringTokenizer tokenizer2(Orbs2, ",");
                while (tokenizer2.HasMoreTokens())
                {
                    j++;
                    wxString o2 = tokenizer2.GetNextToken();
                    fHopMat[i][j] = this->Hopspd(fBondSK, l, m, n, o1, o2);
                    fHopMatT[j][i] = fHopMat[i][j];
                }
            }
            
            int i0Ham = HamiltonianDimMap[iAtomIndex][nShellIndex - 1];
            int j0Ham = HamiltonianDimMap[jAtomIndex][mShellIndex - 1];
            
            if (icell==0 && jcell==0 && kcell==0)
            {
                for(int ii=0; ii<Dim1; ii++)
                    for(int jj=0; jj<Dim2; jj++)
                    {
                        int ih = i0Ham + ii;
                        int jh = j0Ham + jj;
                        hf[ih][jh] = fHopMat[ii][jj];
                        hf[jh][ih] = fHopMatT[jj][ii];
                    }
            }
            else
            {
                for(int ii=0; ii<Dim1; ii++)
                    for(int jj=0; jj<Dim2; jj++)
                    {
                        int ih = i0Ham + ii;
                        int jh = j0Ham + jj;
                        hf[ih][jh] = fHopMat[ii][jj];
                    }
            }
            
            for(int ii = 0; ii < Dim1; ii++)
            {
                if (Dim2 > 0) delete [] fHopMat[ii];
            }
            
            for(int ii = 0; ii < Dim2; ii++)
            {
                if (Dim1 > 0) delete [] fHopMatT[ii];
            }
            
            if (Dim1>0) delete [] fHopMat;
            
            if (Dim2>0) delete [] fHopMatT;
        }
        //////////////////////////////////////////////
		item = BondTree->GetNextChild(CellID, cookie);
	}
}

void Sec30::GetCouplingMatrixF(myGrid* SKCtr, myGrid* OverlapCtr, wxCheckTree* BondTree, wxCheckTree* orbs, double a[3], double b[3], double c[3], double** XYZCoords, Aint1D HamiltonianDimMap, wxTreeItemId CellID, wxString WorkingCell, Adouble1D &hf, Adouble1D &sf)
{
    if (!CellID.IsOk())
    {
        wxMessageBox(_("Fatal error occurred in thread REG01. Error code: GCMF002"),_("Error"));
        //Allocate h for zeros
        return;
    }
    
    int icell,jcell,kcell;
    GetCellInfo(WorkingCell, icell, jcell, kcell);
    
    double CellX = icell*a[0] + jcell*b[0] + kcell*c[0];
    double CellY = icell*a[1] + jcell*b[1] + kcell*c[1];
    double CellZ = icell*a[2] + jcell*b[2] + kcell*c[2];
    
    wxTreeItemId rootID = orbs->GetRootItem();
    wxString rootname = orbs->GetItemText(rootID);    
    
    wxTreeItemIdValue cookie;
	wxTreeItemId item = BondTree->GetFirstChild(CellID, cookie);
	while(item.IsOk())
	{
		wxString BondInfo = BondTree->GetItemText(item);
        //////////////////////////////////////////////
        if (BondTree->GetItemState(item) >= wxCheckTree::CHECKED)
        {
            int iAtomIndex,nShellIndex,jAtomIndex,mShellIndex,bondtype;
            this->GetBondInfo(BondInfo, iAtomIndex, nShellIndex, jAtomIndex, mShellIndex, bondtype);
            wxString BondStr = wxString::Format(wxT("Bond %d"), bondtype);
            
            Adouble0D iBondSK, fBondSK;
            GetBondSKF(SKCtr, SKBuffer, BondStr, iBondSK, fBondSK);
            
            Adouble0D iBondSK_s, fBondSK_s;
            GetBondSKF(OverlapCtr, OLBuffer, BondStr, iBondSK_s, fBondSK_s);
            
            //wxString report = _("");
            //for (int ip=0; ip<4; ip++) report = report + wxString::Format(wxT("%.8f,"),fBondSK[ip]);
            //wxMessageBox(report,_("debug"));
            
            int Dim1 = -1;
            int Dim2 = -1;
            bool IsShell1, IsShell2;
            wxString Orbs1, Orbs2;
            
            wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
            wxComboBox* comb1 = this->GetComboObject(atom1);
            wxString TBAtom1 = comb1->GetStringSelection();
            this->GetOrbitalInfo(orbs, TBAtom1, nShellIndex, Orbs1, Dim1, IsShell1);
            
            wxString atom2 = wxString::Format(wxT("AtomInd%d"),jAtomIndex + 1);
            wxComboBox* comb2 = this->GetComboObject(atom2);
            wxString TBAtom2 = comb2->GetStringSelection();
            this->GetOrbitalInfo(orbs, TBAtom2, mShellIndex, Orbs2, Dim2, IsShell2);

            double x2 = XYZCoords[jAtomIndex][0] + CellX;
            double y2 = XYZCoords[jAtomIndex][1] + CellY;
            double z2 = XYZCoords[jAtomIndex][2] + CellZ;
            double l, m, n;
            this->GetDirectionalCosines(XYZCoords[iAtomIndex][0], XYZCoords[iAtomIndex][1], XYZCoords[iAtomIndex][2], x2, y2, z2, l, m, n);
            
            double** fHopMat = new double*[Dim1];
            double** fSMat = new double*[Dim1];
            for(int ii = 0; ii < Dim1; ii++)
            {
                fHopMat[ii] = new double[Dim2];
                fSMat[ii] = new double[Dim2];
            }
            
            double** fHopMatT = new double*[Dim2];
            double** fSMatT = new double*[Dim2];
            for(int ii = 0; ii < Dim2; ii++)
            {
                fHopMatT[ii] = new double[Dim1];
                fSMatT[ii] = new double[Dim1];
            }
            
            Orbs1.Replace(_(" "),_(""));
            Orbs1.Replace(_("("),_(""), false);
            //Orbs1.Replace(_(")"),_(""));
            Orbs1.RemoveLast(); 
            Orbs2.Replace(_(" "),_(""));
            Orbs2.Replace(_("("),_(""), false);
            //Orbs2.Replace(_(")"),_(""));
            Orbs2.RemoveLast(); 
            int i=-1;
            wxStringTokenizer tokenizer1(Orbs1, ",");
            while (tokenizer1.HasMoreTokens())
            {
                i++;
                wxString o1 = tokenizer1.GetNextToken();
                
                int j=-1;
                wxStringTokenizer tokenizer2(Orbs2, ",");
                while (tokenizer2.HasMoreTokens())
                {
                    j++;
                    wxString o2 = tokenizer2.GetNextToken();
                    fHopMat[i][j] = this->Hopspd(fBondSK, l, m, n, o1, o2);
                    fHopMatT[j][i] = fHopMat[i][j];
                    
                    fSMat[i][j] = this->Hopspd(fBondSK_s, l, m, n, o1, o2);
                    fSMatT[j][i] = fSMat[i][j];
                }
            }
            
            int i0Ham = HamiltonianDimMap[iAtomIndex][nShellIndex - 1];
            int j0Ham = HamiltonianDimMap[jAtomIndex][mShellIndex - 1];
            
            if (icell==0 && jcell==0 && kcell==0)
            {
                for(int ii=0; ii<Dim1; ii++)
                    for(int jj=0; jj<Dim2; jj++)
                    {
                        int ih = i0Ham + ii;
                        int jh = j0Ham + jj;
                        hf[ih][jh] = fHopMat[ii][jj];
                        hf[jh][ih] = fHopMatT[jj][ii];
                        
                        sf[ih][jh] = fSMat[ii][jj];
                        sf[jh][ih] = fSMatT[jj][ii];
                    }
            }
            else
            {
                for(int ii=0; ii<Dim1; ii++)
                    for(int jj=0; jj<Dim2; jj++)
                    {
                        int ih = i0Ham + ii;
                        int jh = j0Ham + jj;
                        hf[ih][jh] = fHopMat[ii][jj];
                        sf[ih][jh] = fSMat[ii][jj];
                    }
            }
            
            for(int ii = 0; ii < Dim1; ii++)
            {
                if (Dim2 > 0)
                {
                    delete [] fHopMat[ii];
                    delete [] fSMat[ii];
                }
            }
            
            for(int ii = 0; ii < Dim2; ii++)
            {
                if (Dim1 > 0)
                {
                    delete [] fHopMatT[ii];
                    delete [] fSMatT[ii];
                }
            }
            
            if (Dim1>0)
            {
                delete [] fHopMat;
                delete [] fSMat;
            }
            
            if (Dim2>0)
            {
                delete [] fHopMatT;
                delete [] fSMatT;
            }
        }
        //////////////////////////////////////////////
		item = BondTree->GetNextChild(CellID, cookie);
	}
}

void Sec30::AddOnSiteMatrix(myGrid* OnSiteCtr, wxCheckTree* orbs, Aint1D HamiltonianDimMap, Adouble1D &hi, Adouble1D &hf, bool isSOC, Adouble2D &SOC_i, Adouble2D &SOC_f)
{
    wxTreeItemId rootID = orbs->GetRootItem();
    wxString rootname = orbs->GetItemText(rootID);
    
    int nUnitcellAtoms = 0;
    this->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    for (int iAtomIndex=0; iAtomIndex<nUnitcellAtoms; iAtomIndex++)
    {
        int Dim1 = -1;
        bool IsShell1;
        wxString Orbs1;
        
        wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
        wxComboBox* comb1 = this->GetComboObject(atom1);
        wxString TBAtom1 = comb1->GetStringSelection();
        
        wxTreeItemId AtomID = orbs->ActiveAndContainsItemIn(rootID ,TBAtom1);
        int nShell = orbs->GetChildrenCount(AtomID,false);
        
        for (int iShell=1; iShell<=nShell; iShell++)
        {
            wxString ShellName = wxString::Format(wxT("Shell %d"),iShell);
            wxTreeItemId shellID = orbs->FindItemIn(AtomID,ShellName);
            
            if (shellID.IsOk() && orbs->GetItemState(shellID) >= wxCheckTree::CHECKED)
            {
                this->GetOrbitalInfo(orbs, TBAtom1, iShell, Orbs1, Dim1, IsShell1);
                wxString Label = TBAtom1  + _(" (") + ShellName + _(")");
                
                int i0Ham = HamiltonianDimMap[iAtomIndex][iShell - 1];
                
                Adouble0D iOnSiteSK, fOnSiteSK;
                double i_p_soc, i_d_soc, f_p_soc, f_d_soc, i_f_soc, f_f_soc;
                Aint0D Orbital_Patern = Aint0D();
                GetOnSiteSK(OnSiteCtr, Label, iOnSiteSK, fOnSiteSK, i_p_soc, i_d_soc, i_f_soc, f_p_soc, f_d_soc, f_f_soc, Orbital_Patern);
                
                for(int ii=0; ii<Dim1; ii++)
                {
                    int ih = i0Ham + ii;
                    hi[ih][ih] = iOnSiteSK[ii];
                    hf[ih][ih] = fOnSiteSK[ii];
                }
                
                ///////////////Add SOC////////////////////////////////////////
                if (isSOC)
                {
                    int nMSpin = 2*Dim1;
                    double** iReSOC = new double*[nMSpin];
                    double** iImSOC = new double*[nMSpin];
                    double** fReSOC = new double*[nMSpin];
                    double** fImSOC = new double*[nMSpin];
                    for (int i=0; i<nMSpin; i++)
                    {
                        iReSOC[i] = new double[nMSpin];
                        iImSOC[i] = new double[nMSpin];
                        fReSOC[i] = new double[nMSpin];
                        fImSOC[i] = new double[nMSpin];
                    }
                    
                    GetSOC(i_p_soc, i_d_soc, i_f_soc, Orbital_Patern, iReSOC, iImSOC);
                    GetSOC(f_p_soc, f_d_soc, f_f_soc, Orbital_Patern, fReSOC, fImSOC);
                    
                    for(int ii=0; ii<nMSpin; ii++)
                    {
                        int ih = 2*i0Ham + ii;
                        for(int jj=0; jj<nMSpin; jj++)
                        {
                            int jh = 2*i0Ham + jj;
                            SOC_i[0][ih][jh] = iReSOC[ii][jj]; //SOC_i[0] is Real part
                            SOC_i[1][ih][jh] = iImSOC[ii][jj]; //SOC_i[1] is Imaginary part
                            SOC_f[0][ih][jh] = fReSOC[ii][jj]; //SOC_f[0] is Real part
                            SOC_f[1][ih][jh] = fImSOC[ii][jj]; //SOC_f[1] is Imaginary part
                        }
                    }
                    
                    for (int i=0; i<nMSpin; i++)
                    {
                        delete [] iReSOC[i];
                        delete [] iImSOC[i];
                        delete [] fReSOC[i];
                        delete [] fImSOC[i];
                    }
                    if (nMSpin>0)
                    {
                        delete [] iReSOC;
                        delete [] iImSOC;
                        delete [] fReSOC;
                        delete [] fImSOC;
                    }
                }
                ///////////////////////////////////////////////////////////////
                
            }
        }
    }
}

void Sec30::AddOnSiteMatrix(myGrid* OnSiteCtr, wxCheckTree* orbs, Aint1D HamiltonianDimMap, Adouble1D &hi, Adouble1D &hf, Adouble1D &si, Adouble1D &sf, bool isSOC, Adouble2D &SOC_i, Adouble2D &SOC_f)
{
    wxTreeItemId rootID = orbs->GetRootItem();
    wxString rootname = orbs->GetItemText(rootID);
    
    int nUnitcellAtoms = 0;
    this->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    for (int iAtomIndex=0; iAtomIndex<nUnitcellAtoms; iAtomIndex++)
    {
        int Dim1 = -1;
        bool IsShell1;
        wxString Orbs1;
        
        wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
        wxComboBox* comb1 = this->GetComboObject(atom1);
        wxString TBAtom1 = comb1->GetStringSelection();
        
        wxTreeItemId AtomID = orbs->ActiveAndContainsItemIn(rootID ,TBAtom1);
        int nShell = orbs->GetChildrenCount(AtomID,false);
        
        for (int iShell=1; iShell<=nShell; iShell++)
        {
            wxString ShellName = wxString::Format(wxT("Shell %d"),iShell);
            wxTreeItemId shellID = orbs->FindItemIn(AtomID,ShellName);
            
            if (shellID.IsOk() && orbs->GetItemState(shellID) >= wxCheckTree::CHECKED)
            {
                this->GetOrbitalInfo(orbs, TBAtom1, iShell, Orbs1, Dim1, IsShell1);
                wxString Label = TBAtom1  + _(" (") + ShellName + _(")");

                int i0Ham = HamiltonianDimMap[iAtomIndex][iShell - 1];
                
                Adouble0D iOnSiteSK, fOnSiteSK;
                double i_p_soc, i_d_soc, f_p_soc, f_d_soc, i_f_soc, f_f_soc;
                Aint0D Orbital_Patern = Aint0D();
                GetOnSiteSK(OnSiteCtr, Label, iOnSiteSK, fOnSiteSK, i_p_soc, i_d_soc, i_f_soc, f_p_soc, f_d_soc, f_f_soc, Orbital_Patern);
                
                for(int ii=0; ii<Dim1; ii++)
                {
                    int ih = i0Ham + ii;
                    hi[ih][ih] = iOnSiteSK[ii];
                    hf[ih][ih] = fOnSiteSK[ii];
                    
                    si[ih][ih] = 1.0;
                    sf[ih][ih] = 1.0;
                }
                
                ///////////////Add SOC////////////////////////////////////////
                if (isSOC)
                {
                    int nMSpin = 2*Dim1;
                    double** iReSOC = new double*[nMSpin];
                    double** iImSOC = new double*[nMSpin];
                    double** fReSOC = new double*[nMSpin];
                    double** fImSOC = new double*[nMSpin];
                    for (int i=0; i<2*Dim1; i++)
                    {
                        iReSOC[i] = new double[nMSpin];
                        iImSOC[i] = new double[nMSpin];
                        fReSOC[i] = new double[nMSpin];
                        fImSOC[i] = new double[nMSpin];
                    }
                    
                    GetSOC(i_p_soc, i_d_soc, i_f_soc, Orbital_Patern, iReSOC, iImSOC);
                    GetSOC(f_p_soc, f_d_soc, f_f_soc, Orbital_Patern, fReSOC, fImSOC);
                    for(int ii=0; ii<nMSpin; ii++)
                    {
                        int ih = 2*i0Ham + ii;
                        for(int jj=0; jj<nMSpin; jj++)
                        {
                            int jh = 2*i0Ham + jj;
                            SOC_i[0][ih][jh] = iReSOC[ii][jj]; //SOC_i[0] is Real part
                            SOC_i[1][ih][jh] = iImSOC[ii][jj]; //SOC_i[1] is Imaginary part
                            SOC_f[0][ih][jh] = fReSOC[ii][jj]; //SOC_f[0] is Real part
                            SOC_f[1][ih][jh] = fImSOC[ii][jj]; //SOC_f[1] is Imaginary part
                        }
                    }
                    
                    for (int i=0; i<nMSpin; i++)
                    {
                        delete [] iReSOC[i];
                        delete [] iImSOC[i];
                        delete [] fReSOC[i];
                        delete [] fImSOC[i];
                    }
                    if (nMSpin>0)
                    {
                        delete [] iReSOC;
                        delete [] iImSOC;
                        delete [] fReSOC;
                        delete [] fImSOC;
                    }
                }
                ///////////////////////////////////////////////////////////////
                
            }
        }
    }
}

void Sec30::AddOnSiteMatrixF(myGrid* OnSiteCtr, wxCheckTree* orbs, Aint1D HamiltonianDimMap, Adouble1D &hf, bool isSOC, Adouble2D &SOC_f)
{
    wxTreeItemId rootID = orbs->GetRootItem();
    wxString rootname = orbs->GetItemText(rootID);
    
    int nUnitcellAtoms = 0;
    this->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    for (int iAtomIndex=0; iAtomIndex<nUnitcellAtoms; iAtomIndex++)
    {
        int Dim1 = -1;
        bool IsShell1;
        wxString Orbs1;
        
        wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
        wxComboBox* comb1 = this->GetComboObject(atom1);
        wxString TBAtom1 = comb1->GetStringSelection();
        
        wxTreeItemId AtomID = orbs->ActiveAndContainsItemIn(rootID ,TBAtom1);
        int nShell = orbs->GetChildrenCount(AtomID,false);
        
        for (int iShell=1; iShell<=nShell; iShell++)
        {
            wxString ShellName = wxString::Format(wxT("Shell %d"),iShell);
            wxTreeItemId shellID = orbs->FindItemIn(AtomID,ShellName);
            
            if (shellID.IsOk() && orbs->GetItemState(shellID) >= wxCheckTree::CHECKED)
            {
                this->GetOrbitalInfo(orbs, TBAtom1, iShell, Orbs1, Dim1, IsShell1);
                wxString Label = TBAtom1  + _(" (") + ShellName + _(")");

                int i0Ham = HamiltonianDimMap[iAtomIndex][iShell - 1];
                
                Adouble0D iOnSiteSK, fOnSiteSK;
                double f_p_soc, f_d_soc, f_f_soc;
                Aint0D Orbital_Patern = Aint0D();
                GetOnSiteSKF(OnSiteCtr, OSBuffer, Label, iOnSiteSK, fOnSiteSK, f_p_soc, f_d_soc, f_f_soc, Orbital_Patern);
                
                for(int ii=0; ii<Dim1; ii++)
                {
                    int ih = i0Ham + ii;
                    hf[ih][ih] = fOnSiteSK[ii];
                }
                
                ///////////////Add SOC////////////////////////////////////////
                if (isSOC)
                {
                    int nMSpin = 2*Dim1;
                    double** fReSOC = new double*[nMSpin];
                    double** fImSOC = new double*[nMSpin];
                    for (int i=0; i<2*Dim1; i++)
                    {
                        fReSOC[i] = new double[nMSpin];
                        fImSOC[i] = new double[nMSpin];
                    }
                    
                    GetSOC(f_p_soc, f_d_soc, f_f_soc, Orbital_Patern, fReSOC, fImSOC);
                    
                    for(int ii=0; ii<nMSpin; ii++)
                    {
                        int ih = 2*i0Ham + ii;
                        for(int jj=0; jj<nMSpin; jj++)
                        {
                            int jh = 2*i0Ham + jj;
                            SOC_f[0][ih][jh] = fReSOC[ii][jj]; //SOC_f[0] is Real part
                            SOC_f[1][ih][jh] = fImSOC[ii][jj]; //SOC_f[1] is Imaginary part
                        }
                    }
                    
                    for (int i=0; i<nMSpin; i++)
                    {
                        delete [] fReSOC[i];
                        delete [] fImSOC[i];
                    }
                    if (nMSpin>0)
                    {
                        delete [] fReSOC;
                        delete [] fImSOC;
                    }
                }
                ///////////////////////////////////////////////////////////////
            }
        }
    }
}

void Sec30::AddOnSiteMatrixF(myGrid* OnSiteCtr, wxCheckTree* orbs, Aint1D HamiltonianDimMap, Adouble1D &hf, Adouble1D &sf, bool isSOC, Adouble2D &SOC_f)
{
    wxTreeItemId rootID = orbs->GetRootItem();
    wxString rootname = orbs->GetItemText(rootID);
    
    int nUnitcellAtoms = 0;
    this->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    for (int iAtomIndex=0; iAtomIndex<nUnitcellAtoms; iAtomIndex++)
    {
        int Dim1 = -1;
        bool IsShell1;
        wxString Orbs1;
        
        wxString atom1 = wxString::Format(wxT("AtomInd%d"),iAtomIndex + 1);
        wxComboBox* comb1 = this->GetComboObject(atom1);
        wxString TBAtom1 = comb1->GetStringSelection();
        
        wxTreeItemId AtomID = orbs->ActiveAndContainsItemIn(rootID ,TBAtom1);
        int nShell = orbs->GetChildrenCount(AtomID,false);
        
        for (int iShell=1; iShell<=nShell; iShell++)
        {
            wxString ShellName = wxString::Format(wxT("Shell %d"),iShell);
            wxTreeItemId shellID = orbs->FindItemIn(AtomID,ShellName);
            
            if (shellID.IsOk() && orbs->GetItemState(shellID) >= wxCheckTree::CHECKED)
            {
                this->GetOrbitalInfo(orbs, TBAtom1, iShell, Orbs1, Dim1, IsShell1);
                wxString Label = TBAtom1  + _(" (") + ShellName + _(")");

                int i0Ham = HamiltonianDimMap[iAtomIndex][iShell - 1];
                
                Adouble0D iOnSiteSK, fOnSiteSK;
                double f_p_soc, f_d_soc, f_f_soc;
                Aint0D Orbital_Patern = Aint0D();
                GetOnSiteSKF(OnSiteCtr, OSBuffer, Label, iOnSiteSK, fOnSiteSK, f_p_soc, f_d_soc, f_f_soc, Orbital_Patern);
                
                for(int ii=0; ii<Dim1; ii++)
                {
                    int ih = i0Ham + ii;
                    hf[ih][ih] = fOnSiteSK[ii];
                    
                    sf[ih][ih] = 1.0;
                }
                
                ///////////////Add SOC////////////////////////////////////////
                if (isSOC)
                {
                    int nMSpin = 2*Dim1;
                    double** fReSOC = new double*[nMSpin];
                    double** fImSOC = new double*[nMSpin];
                    for (int i=0; i<2*Dim1; i++)
                    {
                        fReSOC[i] = new double[nMSpin];
                        fImSOC[i] = new double[nMSpin];
                    }
                    
                    GetSOC(f_p_soc, f_d_soc, f_f_soc, Orbital_Patern, fReSOC, fImSOC);
                    
                    for(int ii=0; ii<nMSpin; ii++)
                    {
                        int ih = 2*i0Ham + ii;
                        for(int jj=0; jj<nMSpin; jj++)
                        {
                            int jh = 2*i0Ham + jj;
                            SOC_f[0][ih][jh] = fReSOC[ii][jj]; //SOC_f[0] is Real part
                            SOC_f[1][ih][jh] = fImSOC[ii][jj]; //SOC_f[1] is Imaginary part
                        }
                    }
                    
                    for (int i=0; i<nMSpin; i++)
                    {
                        delete [] fReSOC[i];
                        delete [] fImSOC[i];
                    }
                    if (nMSpin>0)
                    {
                        delete [] fReSOC;
                        delete [] fImSOC;
                    }
                }
                ///////////////////////////////////////////////////////////////
                
            }
        }
    }
}

void Sec30::GetCellInfo(wxString cellStr, int &icell, int &jcell, int &kcell)
{
    wxString str = cellStr;
    str.Replace(wxString("("), wxString(""));
    str.Replace(wxString(")"), wxString(""));
    
    wxStringTokenizer tokenizer(str, ",");
    long i0,j0,k0;
    tokenizer.GetNextToken().ToLong(&i0);
    tokenizer.GetNextToken().ToLong(&j0);
    tokenizer.GetNextToken().ToLong(&k0);
    icell=i0;
    jcell=j0;
    kcell=k0;
}

void Sec30::GetBondSK(myGrid* GridCtrl, wxString Label, Adouble0D &iBondSK, Adouble0D &fBondSK)
{
    wxString title, istr, fstr;
    double ival, fval;
    int nRow = GridCtrl->GetNumberRows();
    iBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    fBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    bool found = false;
    for (int irow=0; irow<nRow;irow++)
    {
        title = GridCtrl->GetCellValue(irow, 0);
        if (!found)
        {
            if (title == Label) found = true;
        }
        else
        {
            //if (GridCtrl->GetCellBackgroundColour(irow, 1) != *wxWHITE) return;
            if (GridCtrl->IsReadOnly(irow, 1)) return;
            istr = GridCtrl->GetCellValue(irow, 1);
            fstr = GridCtrl->GetCellValue(irow, 2);
            bool isOki = istr.ToDouble(&ival);
            bool isOkf = fstr.ToDouble(&fval);
            SetBondSKElement(title, isOki, iBondSK, ival, isOkf, fBondSK, fval);
        }
    }
}

void Sec30::GetBondSKF(myGrid* GridCtrl, double* GridBuffer, wxString Label, Adouble0D &iBondSK, Adouble0D &fBondSK)
{
    wxString title, fstr;
    double fval;
    int nRow = GridCtrl->GetNumberRows();
    iBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    fBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    bool found = false;
    for (int irow=0; irow<nRow;irow++)
    {
        title = GridCtrl->GetCellValue(irow, 0);
        if (!found)
        {
            if (title == Label) found = true;
        }
        else
        {
            //if (GridCtrl->GetCellBackgroundColour(irow, 1) != *wxWHITE) return;
            if (GridCtrl->IsReadOnly(irow, 1)) return;
            //istr = GridCtrl->GetCellValue(irow, 1);
            //fstr = GridCtrl->GetCellValue(irow, 2);
            //bool isOki = istr.ToDouble(&ival);
            //bool isOkf = fstr.ToDouble(&fval);
            fval = GridBuffer[irow];
            SetBondSKElement(title, false, iBondSK, 0.0, true, fBondSK, fval);
        }
    }
}

void Sec30::GetOnSiteSK(myGrid* GridCtrl, wxString Label, Adouble0D &iBondSK, Adouble0D &fBondSK, double &i_p_soc, double &i_d_soc, double &f_p_soc, double &f_d_soc, Aint0D &Orbital_Patern)
{
    wxString title, istr, fstr;
    double ival, fval;
    int nRow = GridCtrl->GetNumberRows();
    iBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    fBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    i_p_soc=0.0;
    f_p_soc=0.0;
    i_d_soc=0.0;
    f_d_soc=0.0;
    Orbital_Patern.clear();
    bool found = false;
    int ind=0;
    for (int irow=0; irow<nRow;irow++)
    {
        title = GridCtrl->GetCellValue(irow, 0);
        if (!found)
        {
            if (title == Label) found = true;
            ind=0;
        }
        else
        {
            //if (GridCtrl->GetCellBackgroundColour(irow, 1) != *wxWHITE) return;
            if (GridCtrl->IsReadOnly(irow, 1)) return;
            istr = GridCtrl->GetCellValue(irow, 1);
            fstr = GridCtrl->GetCellValue(irow, 2);
            bool isOki = istr.ToDouble(&ival);
            bool isOkf = fstr.ToDouble(&fval);
            if (title == _("p_{soc}"))
            {
                if (isOki)
                    i_p_soc = ival;
                else
                    i_p_soc = 0.0;
                
                if (isOkf)
                    f_p_soc = fval;
                else
                    f_p_soc = 0.0;
            }
            else if (title == _("d_{soc}"))
            {
                if (isOki)
                    i_d_soc = ival;
                else
                    i_d_soc = 0.0;
                
                if (isOkf)
                    f_d_soc = fval;
                else
                    f_d_soc = 0.0;
            }    
            else
            {
                int OrbitalIndex = SetOnSiteSKElement(ind++, title, isOki, iBondSK, ival, isOkf, fBondSK, fval);
                Orbital_Patern.push_back(OrbitalIndex);
            }
        }
    }
}

void Sec30::GetOnSiteSK(myGrid* GridCtrl, wxString Label, Adouble0D &iBondSK, Adouble0D &fBondSK, double &i_p_soc, double &i_d_soc, double &i_f_soc, double &f_p_soc, double &f_d_soc, double &f_f_soc, Aint0D &Orbital_Patern)
{
    wxString title, istr, fstr;
    double ival, fval;
    int nRow = GridCtrl->GetNumberRows();
    iBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    fBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    i_p_soc=0.0;
    f_p_soc=0.0;
    i_d_soc=0.0;
    f_d_soc=0.0;
    i_f_soc=0.0;
    f_f_soc=0.0;
    Orbital_Patern.clear();
    bool found = false;
    int ind=0;
    for (int irow=0; irow<nRow;irow++)
    {
        title = GridCtrl->GetCellValue(irow, 0);
        if (!found)
        {
            if (title == Label) found = true;
            ind=0;
        }
        else
        {
            //if (GridCtrl->GetCellBackgroundColour(irow, 1) != *wxWHITE) return;
            if (GridCtrl->IsReadOnly(irow, 1)) return;
            istr = GridCtrl->GetCellValue(irow, 1);
            fstr = GridCtrl->GetCellValue(irow, 2);
            bool isOki = istr.ToDouble(&ival);
            bool isOkf = fstr.ToDouble(&fval);
            if (title == _("p_{soc}"))
            {
                if (isOki)
                    i_p_soc = ival;
                else
                    i_p_soc = 0.0;
                
                if (isOkf)
                    f_p_soc = fval;
                else
                    f_p_soc = 0.0;
            }
            else if (title == _("d_{soc}"))
            {
                if (isOki)
                    i_d_soc = ival;
                else
                    i_d_soc = 0.0;
                
                if (isOkf)
                    f_d_soc = fval;
                else
                    f_d_soc = 0.0;
            }
            else if (title == _("f_{soc}"))
            {
                if (isOki)
                    i_f_soc = ival;
                else
                    i_f_soc = 0.0;
                
                if (isOkf)
                    f_f_soc = fval;
                else
                    f_f_soc = 0.0;
            }   
            else
            {
                int OrbitalIndex = SetOnSiteSKElement(ind++, title, isOki, iBondSK, ival, isOkf, fBondSK, fval);
                Orbital_Patern.push_back(OrbitalIndex);
            }
        }
    }
}

void Sec30::GetOnSiteSKF(myGrid* GridCtrl, double* GridBuffer, wxString Label, Adouble0D &iBondSK, Adouble0D &fBondSK, double &f_p_soc, double &f_d_soc, Aint0D &Orbital_Patern)
{
    wxString title, fstr;
    double fval;
    int nRow = GridCtrl->GetNumberRows();
    iBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    fBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    f_p_soc=0.0;
    f_d_soc=0.0;
    Orbital_Patern.clear();
    bool found = false;
    int ind=0;
    for (int irow=0; irow<nRow;irow++)
    {
        title = GridCtrl->GetCellValue(irow, 0);
        if (!found)
        {
            if (title == Label) found = true;
            ind=0;
        }
        else
        {
            //if (GridCtrl->GetCellBackgroundColour(irow, 1) != *wxWHITE) return;
            if (GridCtrl->IsReadOnly(irow, 1)) return;
            //istr = GridCtrl->GetCellValue(irow, 1);
            //fstr = GridCtrl->GetCellValue(irow, 2);
            //bool isOki = istr.ToDouble(&ival);
            //bool isOkf = fstr.ToDouble(&fval);
            fval = GridBuffer[irow];
            if (title == _("p_{soc}"))
                f_p_soc = fval;
            else if (title == _("d_{soc}"))
                f_d_soc = fval;
            else
            {
                int OrbitalIndex = SetOnSiteSKElement(ind++, title, false, iBondSK, 0.0, true, fBondSK, fval);
                Orbital_Patern.push_back(OrbitalIndex);
            }
        }
    }
}

void Sec30::GetOnSiteSKF(myGrid* GridCtrl, double* GridBuffer, wxString Label, Adouble0D &iBondSK, Adouble0D &fBondSK, double &f_p_soc, double &f_d_soc, double &f_f_soc, Aint0D &Orbital_Patern)
{
    wxString title, fstr;
    double fval;
    int nRow = GridCtrl->GetNumberRows();
    iBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    fBondSK = std::vector<double>(40,0.0);//{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    f_p_soc=0.0;
    f_d_soc=0.0;
    f_f_soc=0.0;
    Orbital_Patern.clear();
    bool found = false;
    int ind=0;
    for (int irow=0; irow<nRow;irow++)
    {
        title = GridCtrl->GetCellValue(irow, 0);
        if (!found)
        {
            if (title == Label) found = true;
            ind=0;
        }
        else
        {
            //if (GridCtrl->GetCellBackgroundColour(irow, 1) != *wxWHITE) return;
            if (GridCtrl->IsReadOnly(irow, 1)) return;
            //istr = GridCtrl->GetCellValue(irow, 1);
            //fstr = GridCtrl->GetCellValue(irow, 2);
            //bool isOki = istr.ToDouble(&ival);
            //bool isOkf = fstr.ToDouble(&fval);
            fval = GridBuffer[irow];
            if (title == _("p_{soc}"))
                f_p_soc = fval;
            else if (title == _("d_{soc}"))
                f_d_soc = fval;
            else if (title == _("f_{soc}"))
                f_f_soc = fval;
            else
            {
                int OrbitalIndex = SetOnSiteSKElement(ind++, title, false, iBondSK, 0.0, true, fBondSK, fval);
                Orbital_Patern.push_back(OrbitalIndex);
            }
        }
    }
}

void Sec30::GetSOC(double p_soc, double d_soc, Aint0D Orbital_Patern, double** ReSOC, double** ImSOC)
{
    // s+p+d  2+6+10
    double resoc[18][18] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0, 0, 
                              0, 0, 0}, {0, 0, 0, 0, 0, 0, -0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0}, {0, 0, 0, 0, 0, -0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 
                              0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0, 0, -0.5, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 
                              0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5,
                               0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, -0.5, 0, 0, 0, 0,
                               0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0.86602540378443864676372317075294, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0, -0.86602540378443864676372317075294, 0, 0, 0}, {0,
                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0, -0.86602540378443864676372317075294, 0, 0, 0, 0.5}, {0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0, 0, 0, 0.86602540378443864676372317075294, 0, 0, 
                              0, -0.5, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.5, 0, 
                              0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0, 0}};
     
    double imsoc[18][18] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 
                              0.5, -0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0.5, 0, 0,
                               0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, -0.5, 0, 0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, -0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0}, {0, 0, 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0, 0, 0}, {0, 0, 0, -0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, -1.0, 0}, {0,
                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0, 1.0}, {0, 0, 0, 
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0.86602540378443864676372317075294, -0.5, 0, 0, 0.5}, {0, 0, 0, 0, 
                              0, 0, 0, 0, 0, 0, 0, 0, 0.86602540378443864676372317075294, 0, 0, 
                              0.5, 0.5, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                              0, -0.86602540378443864676372317075294, 0, 0, 0, 0, 0, 0}, {0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, -0.86602540378443864676372317075294, 0, 0, 0, 
                              0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, -0.5, 0.5, 0, 0, 0, 0, 0, 
                              0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, -0.5, 0, 0, -0.5, 0, 0, 0, 0, 0, 
                              0}, {0, 0, 0, 0, 0, 0, 0, 0, 1.0, 0, 0, -0.5, 0, 0, 0, 0, 0, 0}, {0,
                               0, 0, 0, 0, 0, 0, 0, 0, -1.0, -0.5, 0, 0, 0, 0, 0, 0, 0}};
    
    const int np_real = 4;
    const int nd_real = 12;
    const int np_imag = 8;
    const int nd_imag = 20;
    int p_realNonZero[np_real][2] = {{4, 7},{5, 6},{6, 5},{7, 4}};
    int d_realNonZero[nd_real][2] = {{8, 11},{9, 10},{10, 9},{11, 8},{12, 15},{13, 14},{14, 13},{14, 17},{15, 12},{15, 16},{16, 15},{17, 14}};
    int p_imagNonZero[np_imag][2] = {{2, 5},{2, 6},{3, 4},{3, 7},{4, 3},{5, 2},{6, 2},{7, 3}};
    int d_imagNonZero[nd_imag][2] = {{8, 15},{8, 16},{9, 14},{9, 17},{10, 13},{10, 14},{10, 17},{11, 12},{11, 15},{11, 16},{12, 11},{13, 10},{14, 9},{14, 10},{15, 8},{15, 11},{16, 8},{16, 11},{17, 9},{17, 10}};
    
    for(int ind=0; ind<np_real; ind++)
    {
        int i = p_realNonZero[ind][0];
        int j = p_realNonZero[ind][1];
        resoc[i][j] = p_soc*resoc[i][j];
    }
    
    for(int ind=0; ind<nd_real; ind++)
    {
        int i = d_realNonZero[ind][0];
        int j = d_realNonZero[ind][1];
        resoc[i][j] = d_soc*resoc[i][j];
    }
    
    for(int ind=0; ind<np_imag; ind++)
    {
        int i = p_imagNonZero[ind][0];
        int j = p_imagNonZero[ind][1];
        imsoc[i][j] = p_soc*imsoc[i][j];
    }
    
    for(int ind=0; ind<nd_imag; ind++)
    {
        int i = d_imagNonZero[ind][0];
        int j = d_imagNonZero[ind][1];
        imsoc[i][j] = d_soc*imsoc[i][j];
    }
    
    int nM = Orbital_Patern.size();
    int nM2 = 2*nM;
    int* SpinOrbital_Patern = new int[nM2];
    int ind0 = 0;
    for (int i=0; i<nM; i++)
    {
        int i_up = 2*Orbital_Patern[i];
        int i_dn = 2*Orbital_Patern[i] + 1;
        SpinOrbital_Patern[ind0++] = i_up;
        SpinOrbital_Patern[ind0++] = i_dn;
    }
    
    for(int iM=0; iM<nM2; iM++)
    {
        int i = SpinOrbital_Patern[iM];
        for(int jM=0; jM<nM2; jM++)
        {
            int j = SpinOrbital_Patern[jM];
            ReSOC[iM][jM] = resoc[i][j];
            ImSOC[iM][jM] = imsoc[i][j];
        }
    }
    
    delete [] SpinOrbital_Patern;
}


// extend the matrix to include f shell
void Sec30::GetSOC(double p_soc, double d_soc, double f_soc, Aint0D Orbital_Patern, double** ReSOC, double** ImSOC)
{
    // s+p+d+f  2+6+10+14=32
    double resoc[32][32] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.86602540,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.86602540,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0.86602540,0,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,-0.86602540,0,0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.50000000,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.50000000,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.00000000,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.00000000,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.22474487,0.50000000,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.22474487,0,0,-0.50000000,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.22474487,0,0,0,-1.22474487,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.22474487,0,0,0,1.22474487,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.50000000,0,0,1.22474487,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.50000000,-1.22474487,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.00000000,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.00000000,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.50000000,0,0,0,0,0,0,0,0,0,0,0,0,}};
     
    double imsoc[32][32] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0.50000000,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0.50000000,0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.50000000,-1.00000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.50000000,0,0,1.00000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0.86602540,-0.50000000,0,0,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0.86602540,0,0,0.50000000,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,-0.86602540,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,-0.86602540,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,-0.50000000,0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,-0.50000000,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,1.00000000,0,0,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,-1.00000000,-0.50000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.61237244,0,0,0,0,0,0,0,-0.61237244,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.61237244,0,0,0,0,0,0,0,-0.61237244,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.61237244,0,0,0,0.79056942,0,0,0,-0.79056942,0,0,0,0.61237244,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.61237244,0,0,0,-0.79056942,0,0,0,-0.79056942,0,0,0,0.61237244,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.79056942,0,0,0,0,0,0,0,0.79056942,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.79056942,0,0,0,0,0,0,0,0.79056942,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.79056942,0,0,0,0,0,0,0,0.79056942,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.79056942,0,0,0,0,0,0,0,-0.79056942,0,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.61237244,0,0,0,-0.79056942,0,0,0,0.79056942,0,0,0,0.61237244,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.61237244,0,0,0,-0.79056942,0,0,0,-0.79056942,0,0,0,-0.61237244,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.61237244,0,0,0,0,0,0,0,0.61237244,0,0,},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.61237244,0,0,0,0,0,0,0,-0.61237244,0,0,0,}};
    
    const int np_real = 4;
    const int nd_real = 12;
    const int np_imag = 8;
    const int nd_imag = 20;
    const int nf_real = 20;
    const int nf_imag = 32;
    int p_realNonZero[np_real][2] = {{4, 7},{5, 6},{6, 5},{7, 4}};
    int d_realNonZero[nd_real][2] = {{8, 11},{9, 10},{10, 9},{11, 8},{12, 15},{13, 14},{14, 13},{14, 17},{15, 12},{15, 16},{16, 15},{17, 14}};
    int p_imagNonZero[np_imag][2] = {{2, 5},{2, 6},{3, 4},{3, 7},{4, 3},{5, 2},{6, 2},{7, 3}};
    int d_imagNonZero[nd_imag][2] = {{8, 15},{8, 16},{9, 14},{9, 17},{10, 13},{10, 14},{10, 17},{11, 12},{11, 15},{11, 16},{12, 11},{13, 10},{14, 9},{14, 10},{15, 8},{15, 11},{16, 8},{16, 11},{17, 9},{17, 10}};
    int f_realNonZero[nf_real][2] = {{18, 30},{19, 31},{20, 28},{21, 29},{22, 25},{22, 26},{23, 24},{23, 27},{24, 23},{24, 27},{25, 22},{25, 26},{26, 22},{26, 25},{27, 23},{27, 24},{28, 20},{29, 21},{30, 18},{31, 19}};
    int f_imagNonZero[nf_imag][2] = {{18, 21},{18, 29},{19, 20},{19, 28},{20, 19},{20, 23},{20, 27},{20, 31},{21, 18},{21, 22},{21, 26},{21, 30},{22, 21},{22, 29},{23, 20},{23, 28},{26, 21},{26, 29},{27, 20},{27, 28},{28, 19},{28, 23},{28, 27},{28, 31},{29, 18},{29, 22},{29, 26},{29, 30},{30, 21},{30, 29},{31, 20},{31, 28}};
    for(int ind=0; ind<np_real; ind++)
    {
        int i = p_realNonZero[ind][0];
        int j = p_realNonZero[ind][1];
        resoc[i][j] = p_soc*resoc[i][j];
    }
    
    for(int ind=0; ind<nd_real; ind++)
    {
        int i = d_realNonZero[ind][0];
        int j = d_realNonZero[ind][1];
        resoc[i][j] = d_soc*resoc[i][j];
    }

    for(int ind=0; ind<nf_real; ind++)
    {
        int i = f_realNonZero[ind][0];
        int j = f_realNonZero[ind][1];
        resoc[i][j] = f_soc*resoc[i][j];
    }
    
    for(int ind=0; ind<np_imag; ind++)
    {
        int i = p_imagNonZero[ind][0];
        int j = p_imagNonZero[ind][1];
        imsoc[i][j] = p_soc*imsoc[i][j];
    }
    
    for(int ind=0; ind<nd_imag; ind++)
    {
        int i = d_imagNonZero[ind][0];
        int j = d_imagNonZero[ind][1];
        imsoc[i][j] = d_soc*imsoc[i][j];
    }

    for(int ind=0; ind<nf_imag; ind++)
    {
        int i = f_imagNonZero[ind][0];
        int j = f_imagNonZero[ind][1];
        imsoc[i][j] = f_soc*imsoc[i][j];
    }
    
    int nM = Orbital_Patern.size();
    int nM2 = 2*nM;
    int* SpinOrbital_Patern = new int[nM2];
    int ind0 = 0;
    for (int i=0; i<nM; i++)
    {
        int i_up = 2*Orbital_Patern[i];
        int i_dn = 2*Orbital_Patern[i] + 1;
        SpinOrbital_Patern[ind0++] = i_up;
        SpinOrbital_Patern[ind0++] = i_dn;
    }
    
    for(int iM=0; iM<nM2; iM++)
    {
        int i = SpinOrbital_Patern[iM];
        for(int jM=0; jM<nM2; jM++)
        {
            int j = SpinOrbital_Patern[jM];
            ReSOC[iM][jM] = resoc[i][j];
            ImSOC[iM][jM] = imsoc[i][j];
        }
    }
    
    delete [] SpinOrbital_Patern;
}


int Sec30::SetOnSiteSKElement(int ind, wxString skName, bool isOki, Adouble0D &iBondSK, double ival, bool isOkf, Adouble0D &fBondSK, double fval)
{
    int ind0 = GetOnSiteSKInd(skName);
    if (isOki) iBondSK[ind] = ival;
    if (isOkf) fBondSK[ind] = fval;
    return ind0;
}

int Sec30::GetOnSiteSKInd(wxString skName)
{
    if (skName == _("s"))
        return 0;
    else if (skName == _("p_y"))
        return 1;
    else if (skName == _("p_z"))
        return 2;
    else if (skName == _("p_x"))
        return 3;
    else if (skName == _("d_{xy}"))
        return 4;
    else if (skName == _("d_{yz}"))
        return 5;
    else if (skName == _("d_{3z^2-r^2}"))
        return 6;
    else if (skName == _("d_{xz}"))
        return 7;
    else if (skName == _("d_{x^2-y^2}"))
        return 8;
    else if (skName == _("f_{y(3x^2-y^2)}"))
        return 9;
    else if (skName == _("f_{xyz}"))
        return 10;
    else if (skName == _("f_{y(5z^2-r^2)}"))
        return 11;
    else if (skName == _("f_{z(5z^2-3r^2)}"))
        return 12;
    else if (skName == _("f_{x(5z^2-r^2)}"))
        return 13;
    else if (skName == _("f_{z(x^2-y^2)}"))
        return 14;
    else if (skName == _("f_{x(x^2-3y^2)}"))
        return 15;

    
    return -1;
}


void Sec30::SetBondSKElement(wxString skName, bool isOki, Adouble0D &iBondSK, double ival, bool isOkf, Adouble0D &fBondSK, double fval)
{
    int ind = GetSKInd(skName);
    if (isOki) iBondSK[ind] = ival;
    if (isOkf) fBondSK[ind] = fval;
}


// must agree with definition in UnitcellClass.cpp
int Sec30::GetSKInd(wxString skName)
{
    if (skName == _("sss"))
        return 0;
    else if (skName == _("sps"))
        return 1;
    else if (skName == _("sds"))
        return 2;
    else if (skName == _("pps"))
        return 3;
    else if (skName == _("ppp"))
        return 4;
    else if (skName == _("pds"))
        return 5;
    else if (skName == _("pdp"))
        return 6;
    else if (skName == _("dds"))
        return 7;
    else if (skName == _("ddp"))
        return 8;
    else if (skName == _("ddd"))
        return 9;
    else if (skName == _("sfs"))
        return 10;
    else if (skName == _("pfs"))
        return 11;
    else if (skName == _("pfp"))
        return 12;
    else if (skName == _("dfs"))
        return 13;
    else if (skName == _("dfp"))
        return 14;
    else if (skName == _("dfd"))
        return 15;
    else if (skName == _("ffs"))
        return 16;
    else if (skName == _("ffp"))
        return 17;
    else if (skName == _("ffd"))
        return 18;
    else if (skName == _("fff"))
        return 19;
    
    return -1;
}



int Sec30::GetAtomIndexFromHamiltonianIndex(Aint1D HamiltonianDimMap, int iH)
{
	int nAtoms = HamiltonianDimMap.size();
	for (int iAtomIndex=0; iAtomIndex< nAtoms; iAtomIndex++)
	{
		Aint0D shells = HamiltonianDimMap[iAtomIndex];
		int nshells = shells.size();
		for (int ishells=0; ishells< nshells; ishells++)
		{
			int iHTest = shells[ishells];
			if (iHTest > iH) return iAtomIndex-1;
		}
	}
	return 0;
}

lapack_complex_double Sec30::GetHk(double*** H, double kx, double ky, double kz, double a[3], double b[3], double c[3], int nEssensialCells, int** lmnEssCells, int iH, int jH)
{
    double K[3] = {kx, ky, kz};
    double RealPart = 0.0;
    double ImaginaryPart = 0.0;
    double R[3];
    double arg;
    for (int icell=0; icell < nEssensialCells; icell++)
    {
        if (lmnEssCells[icell][0] == 0 && lmnEssCells[icell][1] == 0 && lmnEssCells[icell][2] == 0)
        {
            RealPart += H[icell][iH][jH];
        }
        else
        {
            R[0] = lmnEssCells[icell][0] * a[0] + lmnEssCells[icell][1] * b[0] + lmnEssCells[icell][2] * c[0];
            R[1] = lmnEssCells[icell][0] * a[1] + lmnEssCells[icell][1] * b[1] + lmnEssCells[icell][2] * c[1];
            R[2] = lmnEssCells[icell][0] * a[2] + lmnEssCells[icell][1] * b[2] + lmnEssCells[icell][2] * c[2];
            arg = this->dot(K, R);
            RealPart += (H[icell][iH][jH] + H[icell][jH][iH]) * cos(arg);  //V*Exp(-ikR) + VT*Exp(ikR)  //Re
            ImaginaryPart -= (H[icell][iH][jH] - H[icell][jH][iH]) * sin(arg); //V*Exp(-ikR) + VT*Exp(ikR)  //Im
        }
    }
    
    lapack_complex_double out;
    out = {RealPart, ImaginaryPart};
    return out;
}

int Sec30::SymEigenValues(lapack_complex_double* LowerSymMatrix, lapack_int N, double* &eig)
{
    //return LAPACKE_dsyev(LAPACK_ROW_MAJOR, 'N', 'U', N, UpperSymMatrix, N, eig);
    
    //lapack_int LAPACKE_zheev( int matrix_layout, char jobz, char uplo, lapack_int n,
    //                      lapack_complex_double* a, lapack_int lda, double* w );
    return LAPACKE_zheev(LAPACK_ROW_MAJOR, 'N', 'L', N, LowerSymMatrix, N, eig);
}

int Sec30::SymEigenValues(lapack_complex_double* LowerSymMatrixA, lapack_complex_double* LowerSymMatrixB, lapack_int N, double* &eig)
{
    //lapack_int LAPACKE_zhbgv( int matrix_layout, char jobz, char uplo, lapack_int n,
    //                      lapack_int ka, lapack_int kb,
    //                      lapack_complex_double* ab, lapack_int ldab,
    //                      lapack_complex_double* bb, lapack_int ldbb, double* w,
    //                      lapack_complex_double* z, lapack_int ldz );
    
    lapack_int nab = N+1;
    lapack_int nz = N;
    lapack_complex_double z[1];
    z[0] = {0.0, 0.0};
    int info = LAPACKE_zhbgv(LAPACK_ROW_MAJOR, 'N', 'L', N,
                         N, N,
                         LowerSymMatrixA, nab,
                         LowerSymMatrixB, nab,
                         eig,
                         z, nz);
    /*
        lapack_int n = 3, lda = 3, info;
        lapack_int na = n+1;
        lapack_int nb = n+1;
        lapack_int nc = 1;
        
        double w[3];
        lapack_complex_double a[4*4] = {
           { 9.14,  0.00}, {-4.37,  9.22}, {-1.98,  1.72}, {-8.96,  9.50},
           { 0.00,  0.00}, {-3.35,  0.00}, { 2.25,  9.51}, { 2.57, -2.40},
           { 0.00,  0.00}, { 0.00,  0.00}, {-4.82,  0.00}, {-3.24, -2.04},
           { 0.00,  0.00}, { 0.00,  0.00}, { 0.00,  0.00}, { 8.44,  0.00}
        };
        lapack_complex_double b[4*4] = {
           { 1.1,  0.00}, {1.0,  0.00}, {1.0,  0}, {1.0, 0},
           { 1.2,  0.00}, {1.0,  0.00}, { 1.1,  0}, {1.4, 0},
           { 1.1,  0.00}, { 0.5,  0.00}, {1.0,  0.00}, {1., 0},
           { 1.20,  0.00}, { 0.4,  0.00}, { 1.0,  0.00}, { 1.0,  0.00}
        };
        lapack_complex_double c[1] = {
           { 0.0,  0.00}
        };
        //info = LAPACKE_zhbgv( LAPACK_ROW_MAJOR, 'N', 'U', n, a, lda, w );
        info = LAPACKE_zhbgv(LAPACK_ROW_MAJOR, 'N', 'U', n,
                         n, n,
                         a, na,
                         b, nb,
                         w,
                         c, nc);
         
        wxMessageBox(wxString::Format(_("%d"),info));
    */
    return info;
}

bool Sec30::isMatch(double x, double y, double Thereshold)
{
    if (fabs(x-y) < Thereshold)
        return true;
    else
        return false;
}

void Sec30::CopyLastSKToInitialSK()
{
    myGrid* osgc = this->GetGridObject(_("OS"));
    int nRowsOS = osgc->GetNumberRows();
    for (int i=0; i<nRowsOS; i++)
    {
        wxString val = osgc->GetCellValue(i, 2);
        osgc->SetCellValue(i, 1, val);
    }
    
    myGrid* skgc = this->GetGridObject(_("SK"));
    int nRowsSK = skgc->GetNumberRows();
    for (int i=0; i<nRowsSK; i++)
    {
        wxString val = skgc->GetCellValue(i, 2);
        skgc->SetCellValue(i, 1, val);
    }
    
    myGrid* olgc = this->GetGridObject(_("OL"));
    int nRowsOL = olgc->GetNumberRows();
    for (int i=0; i<nRowsOL; i++)
    {
        wxString val = olgc->GetCellValue(i, 2);
        olgc->SetCellValue(i, 1, val);
    }
    
}

bool Sec30::IsSKPanelFilled()
{
	bool isFilled = false;
    myGrid* osgc = this->GetGridObject(_("OS"));
    int nRowsOS = osgc->GetNumberRows();
    for (int i=0; i<nRowsOS; i++)
    {
        
		double d1 = 0.0;
		double d2 = 0.0;
		wxString val1 = osgc->GetCellValue(i, 1);
		wxString val2 = osgc->GetCellValue(i, 3);
		bool output1 = val1.ToDouble(&d1);
		bool output2 = val2.ToDouble(&d2);
		if (!output1) d1 = 0.0;
		if (!output2) d2 = 0.0;
		if ((d1 != 0.0) || (d2 != 0.0)) return true;
    }
    
    myGrid* skgc = this->GetGridObject(_("SK"));
    int nRowsSK = skgc->GetNumberRows();
    for (int i=0; i<nRowsSK; i++)
    {
		double d1 = 0.0;
		double d2 = 0.0;
		wxString val1 = skgc->GetCellValue(i, 1);
		wxString val2 = skgc->GetCellValue(i, 3);
		bool output1 = val1.ToDouble(&d1);
		bool output2 = val2.ToDouble(&d2);
		if (!output1) d1 = 0.0;
		if (!output2) d2 = 0.0;
		if ((d1 != 0.0) || (d2 != 0.0)) return true;
    }
    
    myGrid* olgc = this->GetGridObject(_("OL"));
    int nRowsOL = olgc->GetNumberRows();
    for (int i=0; i<nRowsOL; i++)
    {
		double d1 = 0.0;
		double d2 = 0.0;
		wxString val1 = olgc->GetCellValue(i, 1);
		wxString val2 = olgc->GetCellValue(i, 3);
		bool output1 = val1.ToDouble(&d1);
		bool output2 = val2.ToDouble(&d2);
		if (!output1) d1 = 0.0;
		if (!output2) d2 = 0.0;
		if ((d1 != 0.0) || (d2 != 0.0)) return true;
    }
}

wxBitmap Sec30::GetPng(const void* data, size_t length)
{
    wxMemoryInputStream memIStream(data, length);
    wxImage image(memIStream, wxBITMAP_TYPE_PNG );
    wxBitmap bmp( image );
    return bmp;
}

/*
//1.5.0
wxString Sec30::GetSN(wxString UserName)
{
    wxString m_MACAddress = wxMACAddressUtility::GetMACAddress();
    u16 mac1;
    u16 mac2;
    wxFingerPrint::getMacHash(mac1, mac2);
	u16 VolumeHash = wxFingerPrint::getVolumeHash();
	u16 CpuHash = wxFingerPrint::getCpuHash();
	const char* MachineName = wxFingerPrint::getMachineName();
    
    wxString macadd = wxString::Format(_("%s"), m_MACAddress);
    wxString machash1 = wxString::Format(_("%d"), mac1);
    wxString machash2 = wxString::Format(_("%d"), mac2);
    wxString machname = wxString::Format(_("%s"), MachineName);
    //wxString volhash = wxString::Format(_("%d"), VolumeHash);
    wxString cpuhash = wxString::Format(_("%d"), CpuHash);
    
    wxString BaseSN = cpuhash + _(":") + machash1 + _(":") + machash2;
    wxString MacAddr = macadd + _("|") + machname + _("|") + UserName;
    
    wxString TheID = BaseSN + _(":") + MacAddr;
    
    wxString SerialNumber = ID2SN(TheID, 0);
    return SerialNumber;
}

wxString Sec30::ID2SN(wxString IDstr, int seed)
{
    wxString part1 = IDstr.BeforeFirst('|');
    wxString part23 = IDstr.AfterFirst('|');
    
    wxString BaseSN = part1.BeforeLast(':');
    wxString macadd = part1.AfterLast(':');
    wxString MacAddr = macadd + _("|") + part23;
    
    std::string SN1;
    std::string SN2;
    wxFingerPrint::smear(BaseSN.c_str().AsChar(), MacAddr.c_str().AsChar(), SN1, SN2, seed);
    
    int nSN1 = SN1.length();
    int nSN2 = SN2.length();
    char* SN1Char = new char[nSN1];
    char* SN2Char = new char[nSN2];
    strcpy(SN1Char, SN1.c_str());
    strcpy(SN2Char, SN2.c_str());
    
    int nSN = nSN1 + nSN2;
    char* Serial = new char[nSN + 2];
    int cnt = 0;
    Serial[cnt++] = (char)nSN1;
    Serial[cnt++] = (char)nSN2;
    
    int KeyKey = 0;
    for(int i=0; i<nSN1; i++)
    {
        Serial[cnt++] = SN1Char[i];
        KeyKey += SN1Char[i];
    }
    for(int i=0; i<nSN2; i++)
    {
        Serial[cnt++] = SN2Char[i];
        KeyKey -= SN2Char[i];
    }
    
    if (KeyKey < 0) KeyKey = -KeyKey;
    KeyKey += 5 + 3*seed;
    
    wxString SerialNumber = _("");
    SerialNumber += wxString::Format(_("1:%d:%d"),Serial[0] + 223,Serial[1] + 387);
    for(int i=2; i<nSN + 2; i++)
        SerialNumber += wxString::Format(_(":%d"),Serial[i] + 143 + i);
    SerialNumber += wxString::Format(_(":4520:%d"),KeyKey);
    return SerialNumber;
}

bool Sec30::SaveLicenseToFolder(wxString SNSeed1)
{
    FILE *fpk;
    wxString fname = wxT("./license.dat");
    bool isOK = false;
    if ((fpk = fopen(fname,"w")) != NULL)
    {
        fprintf(fpk,"%s", SNSeed1.c_str().AsChar());
        fclose(fpk);
        isOK = true;
    }
    return isOK;
}

bool Sec30::GetSNFromLicenseFile(wxString &SNSeed1)
{
    FILE *fpk;
    wxString fname = wxT("./license.dat");
    bool isOK = false;
    if ((fpk = fopen(fname,"r")) == NULL) return isOK;
    fclose(fpk);
    std::ifstream infile(fname);
    std::string line;
    std::getline(infile, line);
    SNSeed1 = wxString(line);
    isOK = true;
    return isOK;
}

bool Sec30::IsSNSeed1MatchToThisPC(wxString SN1)
{
    wxString SN0 = Sec30::GetSN(_("Limited"));
    wxString ID0 = Sec30::SN2ID(SN0, 0);
    wxString ID1 = Sec30::SN2ID(SN1, 1);
    wxString IDBase0 = ID0.BeforeFirst('|');
    wxString IDBase1 = ID1.BeforeFirst('|');
    if (IDBase0 == IDBase1)
        return true;
    else
        return false;
}

wxString Sec30::SN2ID(wxString SerialNumber, int seed)
{
    wxString NullID = _("Invalid Serial Number!");
    wxStringTokenizer tokenizer(SerialNumber, ":");
    std::vector<int> code;
    while ( tokenizer.HasMoreTokens() )
    {
        wxString tk = tokenizer.GetNextToken();
        long l = 0;
        bool output = tk.ToLong(&l);
        if (!output) return NullID;
        int ch = (int)l;
        code.push_back(ch);
    }
    
    int nParts = code.size();
    if (code[0] != 1) return NullID;
    if (code[nParts - 2] != 4520) return NullID;
    
    int nSN1, nSN2;
    nSN1 = (int)code[1] - 223;
    nSN2 = (int)code[2] - 387;
    
    if (nSN1 + nSN2 + 5 != nParts) return NullID;
    
    char* SN1 = new char[nSN1];
    char* SN2 = new char[nSN2];
    
    int KeyKey = 0;
    int nSN = nSN1 + nSN2;
    for(int i=2; i<nSN + 2; i++)
    {
        int j = i - 2;
        char chcode = (char)(code[i + 1] - 143 - i);
        if (j < nSN1)
        {
            SN1[j] = chcode;
            KeyKey += chcode;
        }
        else
        {
            SN2[j - nSN1] = chcode;
            KeyKey -= chcode;
        }
    }
    
    if (KeyKey < 0) KeyKey = -KeyKey;
    KeyKey += 5 + 3*seed;
    
    if (code[nParts - 1] != KeyKey) return NullID;
    
    wxString sSN1 = wxString(SN1, nSN1);
    wxString sSN2 = wxString(SN2, nSN2);
    
    std::string RecBaseSN;
    std::string RecMacAddr;
    wxFingerPrint::unsmear(sSN1.c_str().AsChar(), sSN2.c_str().AsChar(), RecBaseSN, RecMacAddr, seed);
    wxString ID = wxString(RecBaseSN) + _(":") + wxString(RecMacAddr);
    return ID;
}
//1.5.0
*/

/*
void Sec30::SetVecValue(wxWindow *parent, wxString VariableName, double* Array, int nArray)
{
    for (int i=0; i<nArray; i++)
    {
        wxString var = wxString::Format(wxT("%s%d"), VariableName, i);
        wxString val = wxString::Format(wxT("%1f"),Array[i]);
        ((wxTextCtrl*)FindWindowByName(var,parent))->SetValue(val);
    }
}
*/

