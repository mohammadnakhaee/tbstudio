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

void Sec30::AddVarVector(wxWindow *parent, int VecCnt, wxString VariableName, wxString VariableType, wxString VecLabel, int LabelSize, int CtrlSize,bool EnableEvent)
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
    
    //gc->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Sec30::TextCtrl_OnUpdated), NULL, this);
    //gc->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(StructureClass::OnCellChanged), NULL, this);
    //gc->Connect(MyGridPasteEvent, wxCommandEventHandler(StructureClass::OnGridPaste), NULL, this);

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
    c.Set(191,205,219,0);
    
    if (EnableEvent) ctr->Connect(wxEVT_COMMAND_TREE_DELETE_ITEM, wxTreeEventHandler(Sec30::TreeCtrlDeleteItem), NULL, this);
    
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
    SendUpdateEvent(name);
}

void Sec30::TreeCtrlDeleteItem(wxTreeEvent& event)
{
    wxCheckTree* tc= (wxCheckTree*)event.GetEventObject();
    wxString name = tc->GetParent()->GetName();
    SendUpdateEvent(name);
}

void Sec30::Choice_OnChanged(wxCommandEvent& event)
{
    wxChoice* tc= (wxChoice*)event.GetEventObject();
    //wxString type = tc->GetHint();
    wxString name = tc->GetParent()->GetName();
    //wxString value = tc->GetValue();
    SendUpdateEvent(name);
}

void Sec30::ComboBox_OnChanged(wxCommandEvent& event)
{
    wxComboBox* tc= (wxComboBox*)event.GetEventObject();
    //wxString type = tc->GetHint();
    wxString name = tc->GetParent()->GetName();
    //wxString value = tc->GetValue();
    SendUpdateEvent(name);
}

void Sec30::PickerChangeColor(wxColourPickerEvent& event)
{
    wxColourPickerCtrl* tc= (wxColourPickerCtrl*)event.GetEventObject();
    wxString name = tc->GetParent()->GetName();
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

void Sec30::SendUpdateEvent(wxString info, int MyID)
{
    wxCommandEvent* event = new wxCommandEvent(Sec30EVT_OnUpdated);
    //event->SetEventObject(this);
    event->SetString(info);
    event->SetInt(MyID);
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

wxButton* Sec30::GetButtonObject(wxString VariableName)
{
    wxButton* ctr= (wxButton*)FindWindowByName(VariableName,GetParent());
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