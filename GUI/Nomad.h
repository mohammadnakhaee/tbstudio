#ifndef NOMAD_H
#define NOMAD_H
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <wx/msgdlg.h>
#include <thread>
#include <wx/app.h>
#include <wx/sstream.h>
#include <wx/protocol/http.h>
#include <wx/webrequest.h>
#include <wx/arrstr.h>

#ifdef __WINDOWS__
#include <windows.h>
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#endif

// It just declares MY_EVENT event type
/******************************************************************************/
wxDECLARE_EVENT(NomadEVT_On_State_Idle, wxCommandEvent);
wxDECLARE_EVENT(NomadEVT_On_State_Completed, wxCommandEvent);
wxDECLARE_EVENT(NomadEVT_On_State_Failed, wxCommandEvent);
wxDECLARE_EVENT(NomadEVT_On_State_Cancelled, wxCommandEvent);
wxDECLARE_EVENT(NomadEVT_On_State_Active, wxCommandEvent);
wxDECLARE_EVENT(NomadEVT_On_State_Unauthorized, wxCommandEvent);
/******************************************************************************/

enum API_ID
{
    POST_entries_query,
    GET_entries_entry,
    GET_uploads,
    POST_keycloak_RefreshToken,
    POST_keycloak_UpdateToken
};

class Nomad
{
public:
    Nomad(wxWindow* ParentRef);
    ~Nomad();
    
    wxString keycloakBase = wxT("https://nomad-lab.eu/fairdi/keycloak/auth/");
    
    // Nomad test
//    wxString keycloakURL = wxT("realms/fairdi_nomad_test/protocol/openid-connect/token");
//    wxString keycloak_client_id = wxT("nomad_gui_dev");

    // Nomad public
    wxString keycloakURL = wxT("realms/fairdi_nomad_prod/protocol/openid-connect/token");
    wxString keycloak_client_id = wxT("nomad_public");
    
    wxString access_token = wxT("");
    wxWindow* Parent;
    wxString owner;
    std::vector<wxString> elements;
    bool exclusive_composition = false;
    std::vector<wxString> types;
    std::vector<wxString> spins;
    std::vector<wxString> gapTypes;
    wxString AuthorPrefix = wxT("");
    
    int pagination;
    int page;
    wxString sortBy;
    wxString order;
    
    std::string exec(const char* cmd);
    wxString CreateCommand(wxString owner, std::vector<wxString> elements, bool exclusive_composition, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy);
    wxString CreateQuery(wxString owner, std::vector<wxString> elements, bool exclusive_composition, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy);
    void query(wxString owner, std::vector<wxString> elements, bool exclusive_composition, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy);
    void startQuery();
    void getEntry(wxString entry_id);
    void getUploads(wxString query = wxT(""));
    void getRefreshToken(wxString username, wxString password);
    void updateToken(wxString refresh_token);
    void SendEvent_On_State_Idle(API_ID ID);
    void SendEvent_On_State_Completed(wxString data, API_ID ID);
    void SendEvent_On_State_Failed(wxString error, API_ID ID);
    void SendEvent_On_State_Cancelled(API_ID ID);
    void SendEvent_On_State_Active(API_ID ID);
    void SendEvent_On_State_Unauthorized(API_ID ID);

#ifdef __WINDOWS__
    int runWindowsCmd(const char* cmd, std::string& outOutput);
    void my_cmd();
    void ErrorExit(PTSTR lpszFunction);
#endif
};

#endif // NOMAD_H
