//mygrid.cpp
#include "mygrid.h"

// this is a definition so can't be in a header
wxDEFINE_EVENT(Sec30EVT_Grid_Updated, wxCommandEvent);

/******************************************************************************/
BEGIN_EVENT_TABLE(myGrid,wxGrid)
    EVT_MENU(wxID_COPY,myGrid::OnCopy)
    EVT_MENU(wxID_CUT,myGrid::OnCut)
    EVT_MENU(wxID_PASTE,myGrid::OnPaste)
    EVT_MENU(wxID_DELETE,myGrid::OnDelete)
    EVT_GRID_CELL_RIGHT_CLICK(myGrid::OnRightMouseDown)
    EVT_GRID_CELL_CHANGED(myGrid::OnCellChanged)
    //EVT_GRID_CELL_CHANGE(myGrid::OnCellCursorChange)
    EVT_KEY_DOWN(myGrid::myOnKeyDown)
END_EVENT_TABLE()
/******************************************************************************/

void myGrid::SendUpdateEvent()
{
    wxCommandEvent* event = new wxCommandEvent(Sec30EVT_Grid_Updated);
    event->SetEventObject(this);
    //event->SetString("nothing");
    wxQueueEvent(this,event);
}

void myGrid::OnCopy(wxCommandEvent &event)
{
    Copy(false, false);
}

void myGrid::OnCut(wxCommandEvent &event)
{
    Copy(false, true);
    UpdateGrid();
}

void myGrid::OnDelete(wxCommandEvent &event)
{
    Copy(true, true);
    UpdateGrid();
}

void myGrid::Copy(bool OnlyDelete, bool cut)
{
    const wxChar* NEWLINE_CHAR = wxTextFile::GetEOL();
    
    wxString copy_data;
    bool something_in_this_line;

    copy_data.Clear();
    
    //int Col0 = GetCursorColumn();
    //int Row0 = GetCursorRow();
    int Col0 = GetGridCursorCol();
    int Row0 = GetGridCursorRow();
        
    for (int i=0; i<GetNumberRows();i++)
    {
        something_in_this_line = false;    
        for (int j=0; j<wxGrid::GetNumberCols(); j++)
        {  
            if (IsInSelection(i,j) || (i==Row0 && j==Col0))
            { 
                if (something_in_this_line == false)
                {  
                    if (copy_data.IsEmpty() == false) 
                    {   
                        copy_data.Append(NEWLINE_CHAR);  
                    }
                    something_in_this_line = true;
                } 
                else
                {                                
                    copy_data.Append(wxT("\t"));  
                }
                
                if (!IsReadOnly(i, j))
                {
                    copy_data = copy_data + GetCellValue(i,j);
                    if (cut || OnlyDelete) SetCellValue(i,j,wxString(""));
                }
            }
        }
    }
    
    if (OnlyDelete) return;
    if (wxTheClipboard->Open())
    {
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData( new wxTextDataObject(copy_data.c_str()) );
        wxTheClipboard->Close();
    }
    //wxOpenClipboard();
    //wxEmptyClipboard();
    //wxSetClipboardData(wxDF_TEXT,copy_data.c_str(),0,0);
    //wxCloseClipboard();
}
/******************************************************************************/
void myGrid::OnPaste(wxCommandEvent &event)
{
    Paste();
    UpdateGrid();
}

void myGrid::Paste()
{
    wxString copy_data;
    wxString cur_field;
    wxString cur_line;
    

    if (wxTheClipboard->Open())
    {
        if (wxTheClipboard->IsSupported( wxDF_TEXT ))
        {
            wxTextDataObject data;
            wxTheClipboard->GetData( data );
            //wxMessageBox( data.GetText() );
            copy_data = data.GetText();
        }
        wxTheClipboard->Close();
    }

    //wxOpenClipboard();          
    //copy_data = (char *)wxGetClipboardData(wxDF_TEXT);
    //wxCloseClipboard();

    int i = GetGridCursorRow();
    int j = GetGridCursorCol();
    int k = j;
    
    while(!copy_data.IsEmpty()) 
    {
        cur_line = copy_data.BeforeFirst('\n');
        cur_line.Replace(wxString("\t"), wxString(" "));
        for (int it=0;it<10;it++)
        {
            cur_line.Replace(wxString("    "), wxString(" "));
            cur_line.Replace(wxString("   "), wxString(" "));
            cur_line.Replace(wxString("  "), wxString(" "));
        }
        
        cur_line.Replace(wxString(", "), wxString(" "));
        cur_line.Replace(wxString(" ,"), wxString(" "));
        cur_line.Replace(wxString(","), wxString(" "));
        
        while(!cur_line.IsEmpty())
        {
            cur_field = cur_line.BeforeFirst(' ');
            if (!IsReadOnly(i, j)) SetCellValue(i,j,cur_field);
            j++; 
            cur_line  = cur_line.AfterFirst (' ');
        } 
        i++;
        j=k;
        copy_data = copy_data.AfterFirst('\n');
    }
    
    //UpdateGrid();
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //wxCommandEvent event(MyGridPasteEvent); // No specific id
    //event.SetString("This is the data");
    //wxPostEvent(this, event); // to ourselves
    //wxQueueEvent(this,new wxCommandEvent(MyGridPasteEvent));
    //event.SetEventObject(this);
    //ProcessWindowEvent(event);
    //wxPostEvent(pBar, event); // or to a different instance or class
    ///////////////////////////////////////////////////////////////////////////////////////////////////
}
/******************************************************************************/
void myGrid::OnRightMouseDown(wxGridEvent &event)
{
    wxMenu *pmenuPopUp = new wxMenu;
    wxMenuItem* pItem;
    
    pItem = new wxMenuItem(pmenuPopUp,wxID_COPY, wxT("Copy"));
    pmenuPopUp->Append(pItem);
    
    pItem = new wxMenuItem(pmenuPopUp,wxID_CUT, wxT("Cut"));
    pmenuPopUp->Append(pItem);
    
    pItem = new wxMenuItem(pmenuPopUp,wxID_PASTE, wxT("Paste"));
    pmenuPopUp->Append(pItem);
    
    pItem = new wxMenuItem(pmenuPopUp,wxID_DELETE, wxT("Delete"));
    pmenuPopUp->Append(pItem);
    
    if(!CanEnableCellControl()) 
        pItem->Enable(false);   
           
    PopupMenu(pmenuPopUp,event.GetPosition());
    delete pmenuPopUp;
}
/******************************************************************************/
void myGrid::OnCellChanged(wxGridEvent &event)
{
    UpdateGrid();
}

void myGrid::UpdateGrid()
{
    Update();
    SendUpdateEvent();
}

/******************************************************************************/
void myGrid::myOnKeyDown(wxKeyEvent &event)
{
    int key = event.GetKeyCode();
    bool isShift = wxGetKeyState(WXK_SHIFT);
    if (wxGetKeyState(WXK_CONTROL_C) || (wxGetKeyState(WXK_CONTROL) && key==67) || (wxGetKeyState(WXK_COMMAND) && key==67)) //Ctrl+C
        Copy(false, false);
    if (wxGetKeyState(WXK_CONTROL_X) || (wxGetKeyState(WXK_CONTROL) && key==88) || (wxGetKeyState(WXK_COMMAND) && key==88)) //Ctrl+C
    {
        Copy(false, true);
        UpdateGrid();
    }
    else if (wxGetKeyState(WXK_CONTROL_V) || (wxGetKeyState(WXK_CONTROL) && key==86) || (wxGetKeyState(WXK_COMMAND) && key==86) || (wxGetKeyState(WXK_SHIFT) && wxGetKeyState(WXK_INSERT))) //Ctrl+V || Ctrl+Insert
    {
        Paste();
        UpdateGrid();
    }
    else if (wxGetKeyState(WXK_DELETE)) //Delete
    {
        Copy(true, true);
        UpdateGrid();
    }
    else if (wxGetKeyState(WXK_UP))
        MoveCursorUp(isShift);
    else if (wxGetKeyState(WXK_DOWN))
        MoveCursorDown(isShift);
    else if (wxGetKeyState(WXK_RIGHT))
        MoveCursorRight(isShift);
    else if (wxGetKeyState(WXK_LEFT))
        MoveCursorLeft(isShift);
    else if (key==WXK_TAB || key==WXK_NUMPAD_TAB)
        NavigateToNextInput(false);
    else if (key==WXK_RETURN || key==WXK_NUMPAD_ENTER)
    {
        if (IsCellEditControlEnabled())
            NavigateToNextInput(true);
        else
            EnableCellEditControl();
    }
    else
    {
        switch (key)
        {
            case 45: StartTyping(_("-")); break;
            case 46: StartTyping(_(".")); break;
            case 48: StartTyping(_("0")); break;
            case 49: StartTyping(_("1")); break;
            case 50: StartTyping(_("2")); break;
            case 51: StartTyping(_("3")); break;
            case 52: StartTyping(_("4")); break;
            case 53: StartTyping(_("5")); break;
            case 54: StartTyping(_("6")); break;
            case 55: StartTyping(_("7")); break;
            case 56: StartTyping(_("8")); break;
            case 57: StartTyping(_("9")); break;
            case 61: EnableCellEditControl(); break; // =
            case WXK_F2: EnableCellEditControl(); break; // F2
            case WXK_NUMPAD_SUBTRACT: StartTyping(_("-")); break;
            case WXK_NUMPAD_DECIMAL: StartTyping(_(".")); break;
            case WXK_NUMPAD0: StartTyping(_("0")); break;
            case WXK_NUMPAD1: StartTyping(_("1")); break;
            case WXK_NUMPAD2: StartTyping(_("2")); break;
            case WXK_NUMPAD3: StartTyping(_("3")); break;
            case WXK_NUMPAD4: StartTyping(_("4")); break;
            case WXK_NUMPAD5: StartTyping(_("5")); break;
            case WXK_NUMPAD6: StartTyping(_("6")); break;
            case WXK_NUMPAD7: StartTyping(_("7")); break;
            case WXK_NUMPAD8: StartTyping(_("8")); break;
            case WXK_NUMPAD9: StartTyping(_("9")); break;
            case WXK_SPACE: EnableCellEditControl(); break;
            case WXK_NUMPAD_SPACE: EnableCellEditControl(); break;
            case WXK_NUMPAD_EQUAL: EnableCellEditControl(); break;
            case WXK_NUMPAD_F2: EnableCellEditControl(); break; // F2
        }
    }
}

/******************************************************************************/
void myGrid::NavigateToNextInput(bool GoDown)
{
    int nrow = GetNumberRows();
    int ncol = GetNumberCols();
    int irow = GetGridCursorRow();
    int icol = GetGridCursorCol();    
    if (icol == ncol - 1 && irow == nrow - 1)
    {
        Navigate();
    }
    else
    {
        if (GoDown)
            MoveCursorDown(false);
        else
        {
            icol++;
            if (icol == ncol)
            {
                icol = 0;
                irow++;
            }
            SetGridCursor(irow,icol);
            //DisableCellEditControl();
            //EnableCellEditControl();
            //ShowCellEditControl();
        }
    }
}

void myGrid::StartTyping(wxString keyString)
{
    int irow = GetGridCursorRow();
    int icol = GetGridCursorCol();
    if (!IsCellEditControlEnabled())
    {
        EnableCellEditControl();
        //SetCellValue(irow, icol, keyString);
        //this->GetCellEditor(irow, icol)->SetParameters(keyString);
    }
}


