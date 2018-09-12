#include "Sec30.h"

Sec30::Sec30()
{
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

void Sec30::AddDoubleVec(wxWindow *parent, int VecCnt, wxString VariableName, wxString VecLabel, int LabelSize, int CtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* st = new wxStaticText(parent, wxID_ANY, VecLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator ivar = double_vars.end();
    std::list<double>::iterator ival = double_vals.end();
    
    for (int i=0; i < VecCnt; i++)
    {
        wxTextCtrl* tc=new wxTextCtrl(parent, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(CtrlSize,-1)), 0);
        MySizer->Add(tc, 0, wxRIGHT, WXC_FROM_DIP(5));
        tc->SetMinSize(wxSize(CtrlSize,-1));
        
        wxString var = wxString::Format(wxT("%s[%d]"), VariableName, i);
        double_vars.insert(ivar,var);
        double_vals.insert(ival,0.0);
        
        //Bind the TextBox and its Variable
        tc->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Sec30::TextCtrl_OnUpdated), NULL, this);
        tc->Connect(wxEVT_CHAR, wxKeyEventHandler(Sec30::TextCtrl_OnChar), NULL, this);
        tc->SetName(var);
        tc->SetHint(wxT("double"));
    }
    
    MySizer->Layout();
    parent->Layout();
}

void Sec30::AddDouble2dArray(wxWindow *parent, int nRow, int nCol, wxString VariableName, wxString* ColNames, wxString* ColTypes, int* ColSizes, int* ColPrecision, int xCtrlSize, int yCtrlSize)
{
    wxBoxSizer* MySizer = new wxBoxSizer(wxHORIZONTAL);
    parent->GetSizer()->Add(MySizer, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, WXC_FROM_DIP(5));
    
    //wxStaticText* st = new wxStaticText(parent, wxID_ANY, VecLabel + wxT(":"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    //MySizer->Add(st, 0, wxLEFT|wxRIGHT|wxTOP, WXC_FROM_DIP(5));
    //st->SetMinSize(wxSize(LabelSize,-1));
    
    std::list<wxString>::iterator ivar = double2dArray_vars.end();
    std::list<   std::vector<std::vector<wxString>>   > ::iterator ival = double2dArray_vals.end();
    
    myGrid* gc=new myGrid(parent, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(xCtrlSize,yCtrlSize)));
    MySizer->Add(gc, 0, wxRIGHT, WXC_FROM_DIP(5));
    gc->EnableEditing(true);
    gc->SetMinSize(wxSize(xCtrlSize,yCtrlSize));
    gc->SetName(VariableName);
    
    gc->CreateGrid( nRow, nCol);
    for (int i=0; i< nCol; i++)
    {
        gc->SetColLabelValue(i,ColNames[i]);
        gc->SetColSize(i, ColSizes[i] );// in pixels
        if (ColTypes[i]=="int")
            gc->SetColFormatNumber(i);
        else if (ColTypes[i]=="double")
            gc->SetColFormatFloat(i,ColSizes[i],ColPrecision[i]);
    }
    
    double2dArray_vars.insert(ivar,VariableName);
    std::vector<std::vector<wxString>> empty;
    double2dArray_vals.insert(ival,empty);
    
    wxColour c; //*wxGREEN
    c.Set(191,205,219,0);
    gc->SetLabelBackgroundColour(c);
    gc->SetColLabelSize(20);
    gc->SetRowLabelSize(35);
    gc->SetColMinimalAcceptableWidth(1);

    //gc->SetColLabelSize(1);
    //gc->SetRowLabelSize(1);
    //gc->EnableCellEditControl(false);
    
    //Bind the TextBox and its Variable
    //gc->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Sec30::TextCtrl_OnUpdated), NULL, this);
    //gc->Connect(wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(StructureClass::OnCellChanged), NULL, this);
    //gc->Connect(MyGridPasteEvent, wxCommandEventHandler(StructureClass::OnGridPaste), NULL, this);
    
    
    
    
    
    MySizer->Layout();
    parent->Layout();
}

void Sec30::TextCtrl_OnUpdated(wxCommandEvent& event)
{
    wxTextCtrl* tc= (wxTextCtrl*)event.GetEventObject();
    wxString type = tc->GetHint();
    wxString name = tc->GetName();
    wxString value = tc->GetValue();
    SetData(type, name, value);
    //if (isValid(label,value)) 
}

void Sec30::SetVar(wxWindow *parent, wxString VariableName, double Value)
{
    wxString val = wxString::Format(wxT("%1f"), Value);
    ((wxTextCtrl*)FindWindowByName(VariableName,parent))->SetValue(val);
}

void Sec30::SetVar(wxWindow *parent, wxString VariableName, int Value)
{
    wxString val = wxString::Format(wxT("%d"), Value);
    ((wxTextCtrl*)FindWindowByName(VariableName,parent))->SetValue(val);
}

void Sec30::SetVar(wxWindow *parent, wxString VariableName, wxString Value)
{
    ((wxTextCtrl*)FindWindowByName(VariableName,parent))->SetValue(Value);
}

bool Sec30::SetData(wxString Type, wxString VariableName, wxString Value)
{
    bool isvalid = false;
    std::list<wxString>::iterator ivar = double_vars.begin();
    if (Type == wxT("double"))
    {
        double val;
        isvalid = Value.ToDouble(&val);
        std::list<double>::iterator ival = double_vals.begin();
        for (int i=0; i<double_vars.size(); i++)
        {
            if (VariableName == *ivar++)
            {
                *ival = val;
                return isvalid;
            }
            ival++;
        }
        
        throw "Invalid variable name.";
    }
    else if (Type == wxT("int"))
    {
        long i;
        //isvalid = value.ToLong(&i);
    }
    
    
}

void Sec30::GetData(wxString VariableName, double &Value)
{
    
}

void Sec30::SaveToFile(wxString filepath, wxString filename)
{
    wxString fname1 = filepath + wxT("/") + filename;
    std::ofstream out(fname1, std::ios::out | std::ios::binary);
    
    if (out.is_open())
    {
        int n = 0;
        std::list<wxString>::iterator is;
        std::list<double>::iterator id;
        std::list<int>::iterator ii;
        std::list<bool>::iterator ib;
        std::list<float>::iterator ifl;
        std::list<char>::iterator ic;
        
        ///////////////////////////////////////////////////////////////
        n = double_vars.size();
        out.write((char *) &n, sizeof n);
        
        for(is=double_vars.begin(); is!= double_vars.end(); is++)
        {
            size_t len = (*is).size();
            out.write((char *)&len, sizeof len);
            out.write((*is).c_str(), len);
        }
        
        for(id=double_vals.begin(); id!= double_vals.end(); id++)
            out.write((char *)&*id, sizeof *id);
        ///////////////////////////////////////////////////////////////
        n = int_vars.size();
        out.write((char *) &n, sizeof n);
        
        for(is=int_vars.begin(); is!= int_vars.end(); is++)
        {
            size_t len = (*is).size();
            out.write((char *)&len, sizeof len);
            out.write((*is).c_str(), len);
        }
        
        for(ii=int_vals.begin(); ii!= int_vals.end(); ii++)
            out.write((char *)&*ii, sizeof *ii);
        ///////////////////////////////////////////////////////////////
        n = bool_vars.size();
        out.write((char *) &n, sizeof n);
        
        for(is=bool_vars.begin(); is!= bool_vars.end(); is++)
        {
            size_t len = (*is).size();
            out.write((char *)&len, sizeof len);
            out.write((*is).c_str(), len);
        }
        
        for(ib=bool_vals.begin(); ib!= bool_vals.end(); ib++)
            out.write((char *)&*ib, sizeof *ib);
        ///////////////////////////////////////////////////////////////
        n = float_vars.size();
        out.write((char *) &n, sizeof n);
        
        for(is=float_vars.begin(); is!= float_vars.end(); is++)
        {
            size_t len = (*is).size();
            out.write((char *)&len, sizeof len);
            out.write((*is).c_str(), len);
        }
        
        for(ifl=float_vals.begin(); ifl!= float_vals.end(); ifl++)
            out.write((char *)&*ifl, sizeof *ifl);
        ///////////////////////////////////////////////////////////////
        n = char_vars.size();
        out.write((char *) &n, sizeof n);
        
        for(is=char_vars.begin(); is!= char_vars.end(); is++)
        {
            size_t len = (*is).size();
            out.write((char *)&len, sizeof len);
            out.write((*is).c_str(), len);
        }
        
        for(ic=char_vals.begin(); ic!= char_vals.end(); ic++)
            out.write((char *)&*ic, sizeof *ic);
        ///////////////////////////////////////////////////////////////
        n = wxString_vars.size();
        out.write((char *) &n, sizeof n);
        
        for(is=wxString_vars.begin(); is!= wxString_vars.end(); is++)
        {
            size_t len = (*is).size();
            out.write((char *)&len, sizeof len);
            out.write((*is).c_str(), len);
        }
        
        for(is=wxString_vals.begin(); is!= wxString_vals.end(); is++)
        {
            size_t len = (*is).size();
            out.write((char *)&len, sizeof len);
            out.write((*is).c_str(), len);
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
        size_t ns = 0;
        double d=0.0;
        int i=0;
        bool b=false;
        float f=0.0f;
        char c='c';
        
        std::list<wxString>::iterator is;
        std::list<double>::iterator id;
        std::list<int>::iterator ii;
        std::list<bool>::iterator ib;
        std::list<float>::iterator ifl;
        std::list<char>::iterator ic;
        
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        is = double_vars.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&ns), sizeof ns);
            char* buf = new char[ns];
            infile.read(buf, ns);
            double_vars.insert(is,wxString(buf));
        }
        
        id = double_vals.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&d), sizeof d);
            double_vals.insert(id,d);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        is = int_vars.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&ns), sizeof ns);
            char* buf = new char[ns];
            infile.read(buf, ns);
            int_vars.insert(is,wxString(buf));
        }
        
        ii = int_vals.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&i), sizeof i);
            int_vals.insert(ii,i);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        is = bool_vars.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&ns), sizeof ns);
            char* buf = new char[ns];
            infile.read(buf, ns);
            bool_vars.insert(is,wxString(buf));
        }
        
        ib = bool_vals.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&b), sizeof b);
            bool_vals.insert(ib,b);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        is = float_vars.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&ns), sizeof ns);
            char* buf = new char[ns];
            infile.read(buf, ns);
            float_vars.insert(is,wxString(buf));
        }
        
        ifl = float_vals.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&f), sizeof f);
            float_vals.insert(ifl,f);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        is = char_vars.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&ns), sizeof ns);
            char* buf = new char[ns];
            infile.read(buf, ns);
            char_vars.insert(is,wxString(buf));
        }
        
        ic = char_vals.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&c), sizeof c);
            char_vals.insert(ic,c);
        }
        ///////////////////////////////////////////////////////////////
        infile.read(reinterpret_cast<char *>(&n), sizeof n);
        
        is = wxString_vars.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&ns), sizeof ns);
            char* buf = new char[ns];
            infile.read(buf, ns);
            wxString_vars.insert(is,wxString(buf));
        }
        
        is = wxString_vals.end();
        for(int it=0; it != n; it++)
        {
            infile.read(reinterpret_cast<char *>(&ns), sizeof ns);
            char* buf = new char[ns];
            infile.read(buf, ns);
            wxString_vals.insert(is,wxString(buf));
        }
        ///////////////////////////////////////////////////////////////
        
        infile.close();
    }

}

void Sec30::TextCtrl_OnChar(wxKeyEvent& event)
{
    wxTextCtrl* tc= (wxTextCtrl*)event.GetEventObject();
    wxString oldvalue=tc->GetValue();
    event.Skip(false);
    
    switch (event.GetKeyCode())
    {
        case '0':
        case WXK_NUMPAD0:
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case WXK_NUMPAD1:
        case WXK_NUMPAD2:
        case WXK_NUMPAD3:
        case WXK_NUMPAD4:
        case WXK_NUMPAD5:
        case WXK_NUMPAD6:
        case WXK_NUMPAD7:
        case WXK_NUMPAD8:
        case WXK_NUMPAD9:
        case WXK_DELETE:    
        case WXK_RIGHT:
        case WXK_LEFT:        
        case WXK_BACK:
        case WXK_TAB: 
        case WXK_NUMPAD_END:
        case WXK_NUMPAD_BEGIN:
        case WXK_HOME:
        case WXK_END:
        case WXK_RETURN:
        case WXK_NUMPAD_DECIMAL:
        case '.':
        case ',':
        case WXK_NUMPAD_SUBTRACT:
        case '-':
            event.Skip();
    }
    
    /*
    switch (event.GetKeyCode())
    {
        case '0':
        case WXK_NUMPAD0:  
            //if (!((tc->GetDouble()==0)&&(oldvalue.Find('.')==-1)))
                event.Skip();
            break;
        
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case WXK_NUMPAD1:
        case WXK_NUMPAD2:
        case WXK_NUMPAD3:
        case WXK_NUMPAD4:
        case WXK_NUMPAD5:
        case WXK_NUMPAD6:
        case WXK_NUMPAD7:
        case WXK_NUMPAD8:
        case WXK_NUMPAD9:
            //if(GetDouble()==0) Clear();
            
        case WXK_DELETE:    
        case WXK_RIGHT:
        case WXK_LEFT:        
        case WXK_BACK:
        case WXK_TAB: 
        case WXK_NUMPAD_END:
        case WXK_NUMPAD_BEGIN:
        case WXK_HOME:
        case WXK_END:
        case WXK_RETURN:
            //event.Skip();  
            break;
        
        case WXK_NUMPAD_DECIMAL:
        case '.':
        case ',':
            //if (!(tc->GetHint() == _("int")))
            //    if (oldvalue.Find('.')==-1) //keine doppelten Punkte zulassen
            //        WriteText(".");  
            break;
        
        case WXK_NUMPAD_SUBTRACT:
        case '-':
                event.Skip();
            break;
            
        default:
            break;
    }
     */
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