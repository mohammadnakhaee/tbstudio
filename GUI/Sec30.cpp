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
        tc->SetCellValue(0,0,_("0"));
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
        tc->SetCellValue(0,0,_("0"));
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
    wxString name = tc->GetName();
    //wxString value = tc->GetValue();
    
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