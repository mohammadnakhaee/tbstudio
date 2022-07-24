#ifndef NOMAD_H
#define NOMAD_H
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <wx/msgdlg.h>
#include <thread>

#ifdef __WINDOWS__
#include <windows.h>
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#endif

// It just declares MY_EVENT event type
/******************************************************************************/
wxDECLARE_EVENT(NomadEVT_OnQueryStarted, wxCommandEvent);
wxDECLARE_EVENT(NomadEVT_OnQueryDataReceived, wxCommandEvent);
wxDECLARE_EVENT(NomadEVT_OnQueryErrorReceived, wxCommandEvent);
wxDECLARE_EVENT(NomadEVT_OnQueryFinished, wxCommandEvent);
/******************************************************************************/

class Nomad
{
public:
    Nomad(wxWindow* ParentRef);
    ~Nomad();
    
    wxWindow* Parent;
    wxString owner;
    std::vector<wxString> elements;
    std::vector<wxString> types;
    std::vector<wxString> spins;
    std::vector<wxString> gapTypes;
    int pagination;
    wxString sortBy;
    
    std::string exec(const char* cmd);
    wxString CreateCommand(wxString owner, std::vector<wxString> elements, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy);
    std::string query(wxString owner, std::vector<wxString> elements, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy);
    void queryProcess();
    void startQuery();
    void SendEventQueryStarted();
    void SendEventQueryDataReceived(wxString data);
    void SendEventQueryErrorReceived(wxString error);
    void SendEventQueryFinished();
    
#ifdef __WINDOWS__
    int runWindowsCmd(const char* cmd, std::string& outOutput);
    void my_cmd();
    void ErrorExit(PTSTR lpszFunction);
#endif
};

#endif // NOMAD_H
