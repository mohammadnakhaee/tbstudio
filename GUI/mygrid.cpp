//mygrid.cpp
#include "mygrid.h"

// this is a definition so can't be in a header
wxDEFINE_EVENT(MyGridPasteEvent, wxCommandEvent);

/******************************************************************************/
BEGIN_EVENT_TABLE(myGrid,wxGrid)
    EVT_MENU(wxID_COPY,myGrid::OnCopy)
    EVT_MENU(wxID_CUT,myGrid::OnCut)
    EVT_MENU(wxID_PASTE,myGrid::OnPaste)
    EVT_GRID_CELL_RIGHT_CLICK(myGrid::OnRightMouseDown)
    EVT_GRID_CELL_CHANGED(myGrid::OnCellChanged)
    EVT_KEY_DOWN(myGrid::myOnKeyDown)
END_EVENT_TABLE()
/******************************************************************************/


void myGrid::OnCopy(wxCommandEvent &event)
{
    Copy(false);
}

void myGrid::OnCut(wxCommandEvent &event)
{
    Copy(true);
}

void myGrid::Copy(bool cut)
{
    const wxChar* NEWLINE_CHAR = wxTextFile::GetEOL();
    
    wxString copy_data;
    bool something_in_this_line;

    copy_data.Clear();
    
    for (int i=0; i<GetNumberRows();i++)
    {
        something_in_this_line = false;    
        for (int j=0; j<wxGrid::GetNumberCols(); j++)
        {  
            if (IsInSelection(i,j))
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
                copy_data = copy_data + GetCellValue(i,j);
                if (cut) SetCellValue(i,j,wxString(""));
            }
        }
    }

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
            SetCellValue(i,j,cur_field);
            j++; 
            cur_line  = cur_line.AfterFirst (' ');
        } 
        i++;
        j=k;
        copy_data = copy_data.AfterFirst('\n');
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //wxCommandEvent event(MyGridPasteEvent); // No specific id
    //event.SetString("This is the data");
    //wxPostEvent(this, event); // to ourselves
    wxQueueEvent(this,new wxCommandEvent(MyGridPasteEvent));
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
    
    if(!CanEnableCellControl()) 
        pItem->Enable(false);   
           
    PopupMenu(pmenuPopUp,event.GetPosition());
    delete pmenuPopUp;
}
/******************************************************************************/
void myGrid::OnCellChanged(wxGridEvent &event)
{
    Update();
}

void myGrid::Refresh(wxKeyCode KeyCode, bool isShift)
{
    
}

/******************************************************************************/
void myGrid::myOnKeyDown(wxKeyEvent &event)
{
    int key = event.GetKeyCode();
    bool isShift = wxGetKeyState(WXK_CONTROL_C);
    if (wxGetKeyState(WXK_CONTROL_C) || (wxGetKeyState(WXK_CONTROL) && key==67) || (wxGetKeyState(WXK_COMMAND) && key==67)) //Ctrl+C
        Copy(false);
    if (wxGetKeyState(WXK_CONTROL_X) || (wxGetKeyState(WXK_CONTROL) && key==88) || (wxGetKeyState(WXK_COMMAND) && key==88)) //Ctrl+C
    {
        Copy(true);
        Update();
    }
    else if (wxGetKeyState(WXK_CONTROL_V) || (wxGetKeyState(WXK_CONTROL) && key==86) || (wxGetKeyState(WXK_COMMAND) && key==86) || (wxGetKeyState(WXK_SHIFT) && wxGetKeyState(WXK_INSERT))) //Ctrl+V || Ctrl+Insert
    {
        Paste();
        Update();
    }
    else if (wxGetKeyState(WXK_UP))
        Refresh(WXK_UP,isShift);
    else if (wxGetKeyState(WXK_DOWN))
        Refresh(WXK_DOWN,isShift);
    else if (wxGetKeyState(WXK_RIGHT))
        Refresh(WXK_RIGHT,isShift);
    else if (wxGetKeyState(WXK_LEFT))
        Refresh(WXK_LEFT,isShift);
    else if (wxGetKeyState(WXK_EXECUTE))
        Update();
}
/******************************************************************************/






