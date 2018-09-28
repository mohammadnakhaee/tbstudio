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
}

void Sec30::AddButton(wxWindow *parent, int ButtonCnt, wxString* Labels, wxObjectEventFunction* Funcs)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxEXPAND, WXC_FROM_DIP(5));
    for (int i=0; i < ButtonCnt; i++)
    {
        wxButton* btn = new wxButton(parent, wxID_ANY, Labels[i], wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
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
        MySizer->Add(btn, 1, wxALL|wxEXPAND, WXC_FROM_DIP(5));
        btn->SetName(ButtonNames[i]);
        btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, Funcs[i], NULL, parent);
    }
}

void Sec30::AddVarVector(wxWindow *parent, int VecCnt, wxString VariableName, wxString VariableType, wxString VecLabel, int LabelSize, int CtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, VecLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator ivar = vars.end();
    
    for (int i=0; i < VecCnt; i++)
    {
        sec30TextCtrl* tc=new sec30TextCtrl(parent, wxID_ANY, VariableType, wxDefaultPosition, wxSize(CtrlSize,-1));
        MySizer->Add(tc, 0, wxRIGHT, WXC_FROM_DIP(5));
        tc->SetMinSize(wxSize(CtrlSize,-1));
        
        wxString var = wxString::Format(wxT("%s[%d]"), VariableName, i);
        vars.insert(ivar,var);
        tc->SetName(var);
        //tc->SetColLabelValue(0,VariableType);
        if (VariableType != _("wxString")) tc->SetCellValue(0,0,_("0"));
        tc->Connect(Sec30EVT_Grid_Updated, wxCommandEventHandler(Sec30::sec30TextCtrl_OnUpdated), NULL, this);
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

void Sec30::AddGrid(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColNames, wxString* ColTypes, int* ColSizes, int* ColPrecision, int xCtrlSize, int yCtrlSize)
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
    c.Set(191,205,219,0);
    gc->SetLabelBackgroundColour(c);
    gc->SetColLabelSize(20);
    gc->SetRowLabelSize(35);
    gc->SetColMinimalAcceptableWidth(1);
    
    gc->Connect(Sec30EVT_Grid_Updated, wxCommandEventHandler(Sec30::sec30TextCtrl_OnUpdated), NULL, this);
    
    gc->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Sec30::TextCtrl_OnUpdated), NULL, this);
    gc->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(StructureClass::OnCellChanged), NULL, this);
    gc->Connect(MyGridPasteEvent, wxCommandEventHandler(StructureClass::OnGridPaste), NULL, this);

    MySizer->Layout();
    parent->Layout();
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
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    
    wxString var = wxString::Format(wxT("%s[%d]"), VariableName, 0);
    radios.insert(ivar,var);
    ctr->SetName(var);
    ctr->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(Sec30::MyRadioSelected), NULL, this);
    
    MySizer->Layout();
    parent->Layout();
}

void Sec30::AddCheckBox(wxWindow *parent, wxString VariableName, wxString Label)
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
}

wxCheckTree* Sec30::AddTreeCtrl(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize)
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
    c.Set(191,205,219,0);
    
    gc->Connect(Sec30EVT_Grid_Updated, wxCommandEventHandler(Sec30::sec30TextCtrl_OnUpdated), NULL, this);
    gc->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Sec30::TextCtrl_OnUpdated), NULL, this);
    gc->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(StructureClass::OnCellChanged), NULL, this);
    gc->Connect(MyGridPasteEvent, wxCommandEventHandler(StructureClass::OnGridPaste), NULL, this);
    
    
    wxTreeItemId id2=ctr->AppendItem(rootID,"2");
    ctr->tree_add(id1,"x",true,true);
    ctr->tree_add(id1,"y",true,true);
    ctr->tree_add(id2,"x",true,false);
    ctr->tree_add(id2,"y",true,true);
    
    ctr->ExpandAll();
    MySizer->Layout();
    parent->Layout();
    
    return ctr;
}

wxChoice* Sec30::AddChoiceCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, int LabelSize, int CtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, MyLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator ichoices = choices.end();
    
    wxArrayString empty;
    wxChoice* ctr=new wxChoice(parent, wxID_ANY, wxDefaultPosition, wxSize(CtrlSize,-1), empty, 0);
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(CtrlSize,-1));
    
    choices.insert(ichoices,VariableName);
    ctr->SetName(VariableName);
    
    MySizer->Layout();
    parent->Layout();
    return ctr;
}

wxComboBox* Sec30::AddComboCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, int LabelSize, int CtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, MyLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator icombos = combos.end();
    
    wxArrayString empty;
    wxComboBox* ctr=new wxComboBox(parent, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(CtrlSize,-1)), empty, 0);
    ctr->SetHint(wxT(""));
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(CtrlSize,-1));
    
    combos.insert(icombos,VariableName);
    ctr->SetName(VariableName);
    
    MySizer->Layout();
    parent->Layout();
    return ctr;
}

wxColourPickerCtrl* Sec30::AddColorCtrl(wxWindow *parent, wxString VariableName, wxString MyLabel, wxColour color, int LabelSize, int CtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, MyLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(parent, wxSize(-1,-1)), 0);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator icolors = colors.end();
    
    wxColourPickerCtrl* ctr = new wxColourPickerCtrl(parent, wxID_ANY, color, wxDefaultPosition, wxDLG_UNIT(parent, wxSize(CtrlSize,-1)), wxCLRP_DEFAULT_STYLE);
    MySizer->Add(ctr, 0, wxRIGHT, WXC_FROM_DIP(5));
    ctr->SetMinSize(wxSize(CtrlSize,-1));
    
    colors.insert(icolors,VariableName);
    ctr->SetName(VariableName);
    
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
    
    parent->Layout();
    return ctr;
}

void Sec30::AddCheckListBox(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize)
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
}

void Sec30::AddListBox(wxWindow *parent, wxString VariableName, int xCtrlSize, int yCtrlSize)
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
    SendUpdateEvent(name);
}

void Sec30::MyRadioSelected(wxCommandEvent& event)
{
    wxRadioButton* ctr= (wxRadioButton*)event.GetEventObject();
    wxString name = ctr->GetParent()->GetName();
    SendUpdateEvent(name);
}

void Sec30::MyCheckBoxSelected(wxCommandEvent& event)
{
    wxCheckBox* ctr= (wxCheckBox*)event.GetEventObject();
    wxString name = ctr->GetParent()->GetName();
    SendUpdateEvent(name);
}

void Sec30::SendUpdateEvent(wxString info)
{
    wxCommandEvent* event = new wxCommandEvent(Sec30EVT_OnUpdated);
    //event->SetEventObject(this);
    event->SetString(info);
    wxQueueEvent(this,event);
}

void Sec30::SetVar(wxString VariableName, double Value, bool FireEvent)
{
    wxString val = wxString::Format(wxT("%1f"), Value);
    ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->SetCellValue(0,0,val);
    if (FireEvent) SendUpdateEvent(VariableName);
}

void Sec30::SetVar(wxString VariableName, int Value, bool FireEvent)
{
    wxString val = wxString::Format(wxT("%d"), Value);
    ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->SetCellValue(0,0,val);
    if (FireEvent) SendUpdateEvent(VariableName);
}

void Sec30::SetVar(wxString VariableName, bool Value, bool FireEvent)
{
    int b = 0;
    if (Value) b=1;
    wxString val = wxString::Format(wxT("%d"), b);
    ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->SetCellValue(0,0,val);
    if (FireEvent) SendUpdateEvent(VariableName);
}

void Sec30::SetVar(wxString VariableName, wxString Value, bool FireEvent)
{
    ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->SetCellValue(0,0,Value);
    if (FireEvent) SendUpdateEvent(VariableName);
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
    wxString val = wxString::Format(wxT("%1f"), Value);
    ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->SetCellValue(iRow, iCol, val);
    if (FireEvent) SendUpdateEvent(VariableName);
}

void Sec30::SetVar(wxString VariableName, int iRow, int iCol, int Value, bool FireEvent)
{
    wxString val = wxString::Format(wxT("%d"), Value);
    ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->SetCellValue(iRow, iCol, val);
    if (FireEvent) SendUpdateEvent(VariableName);
}

void Sec30::SetVar(wxString VariableName, int iRow, int iCol, bool Value, bool FireEvent)
{
    int b = 0;
    if (Value) b=1;
    wxString val = wxString::Format(wxT("%d"), b);
    ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->SetCellValue(iRow, iCol, val);
    if (FireEvent) SendUpdateEvent(VariableName);
}

void Sec30::SetVar(wxString VariableName, int iRow, int iCol, wxString Value, bool FireEvent)
{
    ((sec30TextCtrl*)FindWindowByName(VariableName,GetParent()))->SetCellValue(iRow, iCol, Value);
    if (FireEvent) SendUpdateEvent(VariableName);
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

wxColourPickerCtrl* Sec30::GetColorObject(wxString VariableName)
{
    wxColourPickerCtrl* ctr= (wxColourPickerCtrl*)FindWindowByName(VariableName,GetParent());
    return ctr;
}

void Sec30::SaveToFile(wxString filepath, wxString filename)
{
    wxString fname1 = filepath + wxT("/") + filename;
    std::ofstream out(fname1, std::ios::out | std::ios::binary);
    
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
            
            int nRow=0;
            int nCol=0;
            GetDim(VariableName, nRow, nCol);
            for (int irow=0; irow<nRow;irow++)
                for (int icol=0; icol<nCol; icol++)
                {
                    GetVar(VariableName, irow, icol, val);
                    len = val.size();
                    out.write((char *)&len, sizeof len);
                    out.write(val.c_str(), len);
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
        
        out.close();
    }

}
    
void Sec30::LoadFromFile(wxString filepath, wxString filename)
{
    wxString fname1 = filepath + wxT("/") + filename;
    std::ifstream infile(fname1, std::ios::in | std::ios::binary);
    
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

            int nRow=0;
            int nCol=0;
            GetDim(VariableName, nRow, nCol);
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
                ctr->tree_add(parID, itemname, mystate, mychecked);
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
        infile.close();
    }

}


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
