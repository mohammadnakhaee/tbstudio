#include "Nomad.h"

// this is a definition so can't be in a header
wxDEFINE_EVENT(NomadEVT_On_State_Idle, wxCommandEvent);
wxDEFINE_EVENT(NomadEVT_On_State_Completed, wxCommandEvent);
wxDEFINE_EVENT(NomadEVT_On_State_Failed, wxCommandEvent);
wxDEFINE_EVENT(NomadEVT_On_State_Cancelled, wxCommandEvent);
wxDEFINE_EVENT(NomadEVT_On_State_Active, wxCommandEvent);
wxDEFINE_EVENT(NomadEVT_On_State_Unauthorized, wxCommandEvent);

Nomad::Nomad(wxWindow* ParentRef)
{
    Parent = ParentRef;
    owner = wxString("visible");
    pagination = 5;
    page = 1;
    order = "asc";
    sortBy = "upload_create_time";
    

     // wxSocketBase::Initialize(); // we need to init socket in the main thread if we want to use wxHTTP in a separate thread
     
//    elements.push_back(wxString("C"));
//    types.push_back(wxString("2D"));
//    spins.push_back(wxString("false"));
//    gapTypes.push_back(wxString("indirect"));

}

Nomad::~Nomad()
{
}

//std::string Nomad::query(wxString owner, std::vector<wxString> elements, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy)
//{
//    wxString command = CreateCommand(owner, elements, types, spins, gapTypes, pagination, sortBy);
//    std::string out = Nomad::exec(command.c_str());
//    return out;
//}

void Nomad::query(wxString owner, std::vector<wxString> elements, bool exclusive_composition, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy)
{
    wxString Query = CreateQuery(owner, elements, exclusive_composition, types, spins, gapTypes, pagination, sortBy);

    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(
        Parent,
        "http://nomad-lab.eu/prod/v1/staging/api/v1/entries/query"
    );
    
    API_ID ID = API_ID::POST_entries_query;

    if ( !request.IsOk() ) {
        // This is not expected, but handle the error somehow.
    }
    
    request.SetData(Query, "application/json");

    request.SetMethod(wxT("POST"));
    // Bind state event
    Parent->Bind(wxEVT_WEBREQUEST_STATE, [this, ID](wxWebRequestEvent& evt) {
        switch (evt.GetState())
        {
            // Request completed
            case wxWebRequest::State_Completed:
            {
                wxString response = evt.GetResponse().AsString();
                bool isData = response.Contains(wxString("\"data\": ["));
                if (isData)
                {
                    this->SendEvent_On_State_Completed(response, ID);
                }
                else
                    this->SendEvent_On_State_Failed(response, ID);
        
                break;
            }

            case wxWebRequest::State_Idle:
            {
                this->SendEvent_On_State_Idle(ID);
                break;
            }

            case wxWebRequest::State_Unauthorized:
            {
                this->SendEvent_On_State_Unauthorized(ID);
                break;
            }

            case wxWebRequest::State_Active:
            {
                this->SendEvent_On_State_Active(ID);
                break;
            }

            case wxWebRequest::State_Cancelled:
            {
                this->SendEvent_On_State_Cancelled(ID);
                break;
            }

            case wxWebRequest::State_Failed:
            {
                this->SendEvent_On_State_Failed(evt.GetErrorDescription(), ID);
                break;
            }
        }
    });
     
    // Start the request
    request.Start();
}

void Nomad::startQuery()
{
    query(this->owner, this->elements, this->exclusive_composition, this->types, this->spins, this->gapTypes, this->pagination, this->sortBy);
}

void Nomad::getEntry(wxString entry_id)
{
    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(
        Parent,
        wxString::Format(wxT("http://nomad-lab.eu/prod/v1/staging/api/v1/entries/%s/archive"), entry_id)
    );
    API_ID ID = API_ID::GET_entries_entry;
    
    if ( !request.IsOk() ) {
        // This is not expected, but handle the error somehow.
    }
    
//    request.SetData(Query, "application/json");

    request.SetMethod(wxT("GET"));
    // Bind state event
    Parent->Bind(wxEVT_WEBREQUEST_STATE, [this, ID](wxWebRequestEvent& evt) {
        switch (evt.GetState())
        {
            // Request completed
            case wxWebRequest::State_Completed:
            {
                wxString response = evt.GetResponse().AsString();
                bool isData = response.Contains(wxString("\"band_structure_electronic\": {"));
                if (isData)
                {
                    this->SendEvent_On_State_Completed(response, ID);
                }
                else
                    this->SendEvent_On_State_Failed(response, ID);
        
                break;
            }

            case wxWebRequest::State_Idle:
            {
                this->SendEvent_On_State_Idle(ID);
                break;
            }

            case wxWebRequest::State_Unauthorized:
            {
                this->SendEvent_On_State_Unauthorized(ID);
                break;
            }

            case wxWebRequest::State_Active:
            {
                this->SendEvent_On_State_Active(ID);
                break;
            }

            case wxWebRequest::State_Cancelled:
            {
                this->SendEvent_On_State_Cancelled(ID);
                break;
            }

            case wxWebRequest::State_Failed:
            {
                this->SendEvent_On_State_Failed(evt.GetErrorDescription(), ID);
                break;
            }
        }
    });
     
    // Start the request
    request.Start();
}

void Nomad::getUploads(wxString query)
{
    wxString apiurl;
    if (query == wxT(""))
        apiurl = wxT("http://nomad-lab.eu/prod/v1/staging/api/v1/uploads?page_size=100000&order_by=upload_create_time&order=desc");
    else
        apiurl = wxString::Format(wxT("http://nomad-lab.eu/prod/v1/staging/api/v1/uploads?page_size=100000&order_by=upload_create_time&order=desc&%s"), query);

    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(
        Parent,
        apiurl
    );
    API_ID ID = API_ID::GET_uploads;
    
    if ( !request.IsOk() ) {
        // This is not expected, but handle the error somehow.
    }
    
//    request.SetData(Query, "application/json");

    request.SetMethod(wxT("GET"));
    wxString authKey = wxT("Authorization");
//    wxString authVal = wxT("Bearer eyJhbGciOiJSUzI1NiIsInR5cCIgOiAiSldUIiwia2lkIiA6ICJmb1hmZnM5QlFQWHduLU54Yk5PYlExOFhnZnlKU1FNRkl6ZFVnWjhrZzdVIn0.eyJqdGkiOiI2YWNmM2Y4Yi0xYzBlLTQ1MzItOGJlNy1mMDczZTc0N2ZlZjAiLCJleHAiOjE2NzAwNzMzNTcsIm5iZiI6MCwiaWF0IjoxNjY5OTg2OTU3LCJpc3MiOiJodHRwczovL25vbWFkLWxhYi5ldS9mYWlyZGkva2V5Y2xvYWsvYXV0aC9yZWFsbXMvZmFpcmRpX25vbWFkX3Byb2QiLCJzdWIiOiIzNGFlYzE4OS1jYjRhLTRkMTctOGQ5Mi1iMDk3YThmMDU3ZTQiLCJ0eXAiOiJCZWFyZXIiLCJhenAiOiJub21hZF9wdWJsaWMiLCJub25jZSI6ImIyZDMzMGU1LTRhYTctNGY0Zi1iZjE1LTE5OGVlODgyZmIwMyIsImF1dGhfdGltZSI6MTY2OTk4NTI3Nywic2Vzc2lvbl9zdGF0ZSI6IjEyNGQ5ZGI0LTE1MTgtNGNkOS05YjJiLWM0OWRlOTQ3MjA1ZiIsImFjciI6IjAiLCJzY29wZSI6Im9wZW5pZCBwcm9maWxlIGVtYWlsIiwiZW1haWxfdmVyaWZpZWQiOnRydWUsIm5hbWUiOiJNb2hhbW1hZCBOYWtoYWVlIiwicHJlZmVycmVkX3VzZXJuYW1lIjoibW5ha2hhZWUiLCJnaXZlbl9uYW1lIjoiTW9oYW1tYWQiLCJmYW1pbHlfbmFtZSI6Ik5ha2hhZWUiLCJlbWFpbCI6Im1vaGFtbWFkLm5ha2hhZWUuMUBnbWFpbC5jb20ifQ.GELyoIG8O8ZQQHoJ0X61wm_tS80KT88rWN3GH3efPCKb-5p9m23-BzOBhPUY3Pty9J4Fsw1RaSYeL62UEeMIwQIYrgSlaV797ygw1RwoacGnh3GfoNNqoi8qR7yoN-HeQyWrD_TjLB5kr1xo5vxBpE9tfcFa7UC7NB494iWLGKM2db3tOF3ppYv5tW9HgsgwB2M-R9SX4TE6JaBZg402YoBBJZjUcOYeqLqyeNr2ebg55HjpgJbQ3_6CQLx_A7cv-Tt_zaiakZfLoapUYg43Kl-frXx6RheyCloYeMi1ck_kW1-aqxcbdk-UgOJTzSv_wMx3QidpGY61V1-EfaguCA");
    wxString authVal = wxString::Format(wxT("Bearer %s"), access_token);
    request.SetHeader(authKey, authVal);

    // Bind state event
    Parent->Bind(wxEVT_WEBREQUEST_STATE, [this, ID](wxWebRequestEvent& evt) {
        switch (evt.GetState())
        {
            // Request completed
            case wxWebRequest::State_Completed:
            {
                wxString response = evt.GetResponse().AsString();
                bool isData = response.Contains(wxString("\"data\": ["));
                if (isData)
                {
                    this->SendEvent_On_State_Completed(response, ID);
                }
                else
                    this->SendEvent_On_State_Failed(response, ID);
        
                break;
            }

            case wxWebRequest::State_Idle:
            {
                this->SendEvent_On_State_Idle(ID);
                break;
            }

            case wxWebRequest::State_Unauthorized:
            {
                this->SendEvent_On_State_Unauthorized(ID);
                break;
            }

            case wxWebRequest::State_Active:
            {
                this->SendEvent_On_State_Active(ID);
                break;
            }

            case wxWebRequest::State_Cancelled:
            {
                this->SendEvent_On_State_Cancelled(ID);
                break;
            }

            case wxWebRequest::State_Failed:
            {
                this->SendEvent_On_State_Failed(evt.GetErrorDescription(), ID);
                break;
            }
        }
    });
     
    // Start the request
    request.Start();
}

void Nomad::getRefreshToken(wxString username, wxString password)
{
    wxString url = keycloakBase + keycloakURL;
    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(
        Parent,
        url
    );
    API_ID ID = API_ID::POST_keycloak_RefreshToken;
    
    if ( !request.IsOk() ) {
        // This is not expected, but handle the error somehow.
    }

    wxString Query = wxString::Format(wxString("username=%s&grant_type=%s&password=%s&client_id=%s"), username, wxT("password"), password, keycloak_client_id);
    request.SetData(Query, "application/x-www-form-urlencoded");

    request.SetMethod(wxT("POST"));
    
    request.SetHeader(wxT("cache-control"), wxT("no-cache"));

    // Bind state event
    Parent->Bind(wxEVT_WEBREQUEST_STATE, [this, ID](wxWebRequestEvent& evt) {
        switch (evt.GetState())
        {
            // Request completed
            case wxWebRequest::State_Completed:
            {
                wxString response = evt.GetResponse().AsString();
                bool isData = response.Contains(wxString("\"access_token\":"));
                if (isData)
                    this->SendEvent_On_State_Completed(response, ID);
                else
                    this->SendEvent_On_State_Failed(response, ID);
                    
                break;
            }

            case wxWebRequest::State_Idle:
            {
                this->SendEvent_On_State_Idle(ID);
                break;
            }

            case wxWebRequest::State_Unauthorized:
            {
                this->SendEvent_On_State_Unauthorized(ID);
                break;
            }

            case wxWebRequest::State_Active:
            {
                this->SendEvent_On_State_Active(ID);
                break;
            }

            case wxWebRequest::State_Cancelled:
            {
                this->SendEvent_On_State_Cancelled(ID);
                break;
            }

            case wxWebRequest::State_Failed:
            {
                wxString error = evt.GetErrorDescription();
                if (!error.Contains(_("Initializing authentication challenge failed with error"))) {
                    this->SendEvent_On_State_Failed(error, ID);
                }
                break;
            }
        }
    });
     
    // Start the request
    request.Start();
}

void Nomad::updateToken(wxString refresh_token)
{
    wxString url = keycloakBase + keycloakURL;
    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(
        Parent,
        url
    );
    API_ID ID = API_ID::POST_keycloak_UpdateToken;
    
    if ( !request.IsOk() ) {
        // This is not expected, but handle the error somehow.
    }

    wxString Query = wxString::Format(wxString("refresh_token=%s&grant_type=%s&client_id=%s"), refresh_token, wxT("refresh_token"), keycloak_client_id);
    request.SetData(Query, "application/x-www-form-urlencoded");

    request.SetMethod(wxT("POST"));
    
    request.SetHeader(wxT("cache-control"), wxT("no-cache"));

    // Bind state event
    Parent->Bind(wxEVT_WEBREQUEST_STATE, [this, ID](wxWebRequestEvent& evt) {
        switch (evt.GetState())
        {
            // Request completed
            case wxWebRequest::State_Completed:
            {
                wxString response = evt.GetResponse().AsString();
                bool isData = response.Contains(wxString("\"access_token\":"));
                if (isData)
                    this->SendEvent_On_State_Completed(response, ID);
                else
                    this->SendEvent_On_State_Failed(response, ID);
                    
                break;
            }

            case wxWebRequest::State_Idle:
            {
                this->SendEvent_On_State_Idle(ID);
                break;
            }

            case wxWebRequest::State_Unauthorized:
            {
                this->SendEvent_On_State_Unauthorized(ID);
                break;
            }

            case wxWebRequest::State_Active:
            {
                this->SendEvent_On_State_Active(ID);
                break;
            }

            case wxWebRequest::State_Cancelled:
            {
                this->SendEvent_On_State_Cancelled(ID);
                break;
            }

            case wxWebRequest::State_Failed:
            {
                wxString error = evt.GetErrorDescription();
                if (!error.Contains(_("Initializing authentication challenge failed with error"))) {
                    this->SendEvent_On_State_Failed(error, ID);
                }
                break;
            }
        }
    });
     
    // Start the request
    request.Start();
}


void Nomad::SendEvent_On_State_Idle(API_ID ID)
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_On_State_Idle);
    event->SetInt(ID);
    wxQueueEvent(Parent, event);
}

void Nomad::SendEvent_On_State_Cancelled(API_ID ID)
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_On_State_Cancelled);
    event->SetInt(ID);
    wxQueueEvent(Parent, event);
}

void Nomad::SendEvent_On_State_Active(API_ID ID)
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_On_State_Active);
    event->SetInt(ID);
    wxQueueEvent(Parent, event);
}

void Nomad::SendEvent_On_State_Unauthorized(API_ID ID)
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_On_State_Unauthorized);
    event->SetInt(ID);
    wxQueueEvent(Parent, event);
}

void Nomad::SendEvent_On_State_Completed(wxString data, API_ID ID)
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_On_State_Completed);
    event->SetString(data);
    event->SetInt(ID);
    wxQueueEvent(Parent, event);
}

void Nomad::SendEvent_On_State_Failed(wxString error, API_ID ID)
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_On_State_Failed);
    event->SetString(error);
    event->SetInt(ID);
    wxQueueEvent(Parent, event);
}

std::string Nomad::exec(const char* cmd) {
#ifdef __WINDOWS__
    std::string output;
//    runWindowsCmd("cmd /c dir", output);
    runWindowsCmd(cmd, output);
    return output;
#else
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("Could not fetch data from NOMAD!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        result = "err";
        throw;
    }
    pclose(pipe);
    return result;
#endif
}

wxString Nomad::CreateCommand(wxString owner, std::vector<wxString> elements, bool exclusive_composition, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy)
{
    wxString ownerCMD = wxString::Format(wxString("\\\"owner\\\": \\\"%s\\\""), owner);
    
    wxString onlyWithBandStructure = wxString("\\\"results.properties.available_properties:all\\\": [\\\"band_structure_electronic\\\"]");
    
    int i = 0;
    wxString elementsCMD = wxString("\\\"results.material.elements:all\\\": [");
    for(std::vector<wxString>::iterator it = std::begin(elements); it != std::end(elements); ++it) {
        i++;
        elementsCMD = elementsCMD + wxString::Format(wxString("\\\"%s\\\""), *it);
        if (i != elements.size())
            elementsCMD = elementsCMD + wxString(", ");
        else
            elementsCMD = elementsCMD + wxString("]");
    }

    i = 0;
    wxString typesCMD = wxString("\\\"results.material.structural_type:any\\\": [");
    for(std::vector<wxString>::iterator it = std::begin(types); it != std::end(types); ++it) {
        i++;
        typesCMD = typesCMD + wxString::Format(wxString("\\\"%s\\\""), *it);
        if (i != types.size())
            typesCMD = typesCMD + wxString(", ");
        else
            typesCMD = typesCMD + wxString("]");
    }
    
    i = 0;
    wxString spinsCMD = wxString("\\\"results.properties.electronic.band_structure_electronic\\\": {\\\"spin_polarized:any\\\": [");
    for(std::vector<wxString>::iterator it = std::begin(spins); it != std::end(spins); ++it) {
        i++;
        spinsCMD = spinsCMD + wxString::Format(wxString("\\\"%s\\\""), *it);
        if (i != spins.size())
            spinsCMD = spinsCMD + wxString(", ");
        else
            spinsCMD = spinsCMD + wxString("]}");
    }
    
    i = 0;
    wxString gapTypesCMD = wxString("\\\"results.properties.electronic.band_structure_electronic.band_gap\\\": {\\\"type:any\\\": [");
    for(std::vector<wxString>::iterator it = std::begin(gapTypes); it != std::end(gapTypes); ++it) {
        i++;
        gapTypesCMD = gapTypesCMD + wxString::Format(wxString("\\\"%s\\\""), *it);
        if (i != gapTypes.size())
            gapTypesCMD = gapTypesCMD + wxString(", ");
        else
            gapTypesCMD = gapTypesCMD + wxString("]}");
    }

    wxString command = wxString::Format(wxString("curl -s -S -X POST https://nomad-lab.eu/prod/v1/staging/api/v1/entries/query -H \"accept: application/json\" -H \"Content-Type: application/json\" -d \"{   \
            %s, \\\"query\\\": {"), ownerCMD);
    if (elements.size() > 0) command = command + elementsCMD + wxString(", ");
    if (types.size() > 0) command = command + typesCMD + wxString(", ");
    if (spins.size() > 0) command = command + spinsCMD + wxString(", ");
    if (gapTypes.size() > 0) command = command + gapTypesCMD + wxString(", ");
    command = command + onlyWithBandStructure;
    wxString paginationCMD = wxString::Format(wxString("},         \
    \\\"pagination\\\": {         \
        \\\"page_size\\\": %d,         \
        \\\"page\\\": %d,         \
        \\\"order\\\": %s,         \
        \\\"order_by\\\": \\\"%s\\\"         \
      }           \
    }\""), pagination, page, order, sortBy);

    command = command + paginationCMD;
    return command;
    
    //OK query
    //wxString command = wxString::Format(wxString("curl -s -S -X POST https://nomad-lab.eu/prod/v1/staging/api/v1/entries/query -H \"accept: application/json\" -H \"Content-Type: application/json\" -d \"{   \
//  \\\"owner\\\": \\\"visible\\\",         \
//    \\\"query\\\": {         \
//        \\\"results.material.elements:all\\\": [\\\"C\\\", \\\"B\\\"],         \
//        \\\"results.material.structural_type:any\\\": [\\\"2D\\\"],         \
//        \\\"results.properties.available_properties:all\\\": [\\\"band_structure_electronic\\\"],         \
//        \\\"results.properties.electronic.band_structure_electronic\\\": {\\\"spin_polarized:any\\\": [\\\"true\\\"]},         \
//        \\\"results.properties.electronic.band_structure_electronic.band_gap\\\": {\\\"type:any\\\": [\\\"direct\\\"]}         \
//      },         \
//    \\\"pagination\\\": {         \
//        \\\"page_size\\\": %d,         \
//        \\\"order_by\\\": \\\"upload_create_time\\\"         \
//      }           \
//}\""), 2);
}


wxString Nomad::CreateQuery(wxString owner, std::vector<wxString> elements, bool exclusive_composition, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy)
{
    wxString ownerCMD = wxString::Format(wxString("\"owner\": \"%s\""), owner);
    
    wxString onlyWithBandStructure = wxString("\"results.properties.available_properties:all\": [\"band_structure_electronic\"]");
    
    int i = 0;
    wxString elementsCMD;
    if (exclusive_composition) {
        elementsCMD = wxString("\"results.material.elements_exclusive\": \"");
        wxSortedArrayString sortedElements;
        
        for(std::vector<wxString>::iterator it = std::begin(elements); it != std::end(elements); ++it) sortedElements.Add(*it);
        sortedElements.Sort();
        
        for(int iElement = 0; iElement < sortedElements.Count(); iElement++) {
            elementsCMD = elementsCMD + sortedElements[iElement];
            if (iElement != sortedElements.Count() - 1)
                elementsCMD = elementsCMD + wxString(" ");
            else
                elementsCMD = elementsCMD + wxString("\"");
        }
    } else {
        elementsCMD = wxString("\"results.material.elements:all\": [");
        for(std::vector<wxString>::iterator it = std::begin(elements); it != std::end(elements); ++it) {
            i++;
            elementsCMD = elementsCMD + wxString::Format(wxString("\"%s\""), *it);
            if (i != elements.size())
                elementsCMD = elementsCMD + wxString(", ");
            else
                elementsCMD = elementsCMD + wxString("]");
        }   
    }
    
    i = 0;
    wxString typesCMD = wxString("\"results.material.structural_type:any\": [");
    for(std::vector<wxString>::iterator it = std::begin(types); it != std::end(types); ++it) {
        i++;
        typesCMD = typesCMD + wxString::Format(wxString("\"%s\""), *it);
        if (i != types.size())
            typesCMD = typesCMD + wxString(", ");
        else
            typesCMD = typesCMD + wxString("]");
    }
    
    wxString mainAuthorCMD = wxString::Format(wxString("\"main_author.name\": \"%s\""), AuthorPrefix);
    
    i = 0;
    wxString spinsCMD = wxString("\"results.properties.electronic.band_structure_electronic\": {\"spin_polarized:any\": [");
    for(std::vector<wxString>::iterator it = std::begin(spins); it != std::end(spins); ++it) {
        i++;
        spinsCMD = spinsCMD + wxString::Format(wxString("\"%s\""), *it);
        if (i != spins.size())
            spinsCMD = spinsCMD + wxString(", ");
        else
            spinsCMD = spinsCMD + wxString("]}");
    }
    
    i = 0;
    wxString gapTypesCMD = wxString("\"results.properties.electronic.band_structure_electronic.band_gap\": {\"type:any\": [");
    for(std::vector<wxString>::iterator it = std::begin(gapTypes); it != std::end(gapTypes); ++it) {
        i++;
        gapTypesCMD = gapTypesCMD + wxString::Format(wxString("\"%s\""), *it);
        if (i != gapTypes.size())
            gapTypesCMD = gapTypesCMD + wxString(", ");
        else
            gapTypesCMD = gapTypesCMD + wxString("]}");
    }

    wxString paginationCMD = wxString::Format(wxString("\"pagination\": {         \
            \"page_size\": %d,         \
            \"page\": %d,         \
            \"order\": \"%s\",         \
            \"order_by\": \"%s\"         \
          }"), pagination, page, order, sortBy);

    wxString requiredCMD = wxString("\"required\": {         \
        \"include\": [        \
          \"entry_id\",          \
          \"mainfile\",          \
          \"upload_id\",          \
          \"authors\",          \
          \"upload_create_time\",          \
          \"last_processing_time\",          \
          \"published\",          \
          \"main_author\",          \
          \"entry_create_time\",          \
          \"nomad_version\",          \
          \"results.method.simulation.dft.xc_functional_type\",          \
          \"results.method.simulation.program_name\",          \
          \"results.material.structural_type\",          \
          \"results.material.chemical_formula_anonymous\",          \
          \"results.material.chemical_formula_descriptive\",          \
          \"results.material.chemical_formula_hill\",          \
          \"results.material.chemical_formula_reduced\",          \
          \"results.method.method_name\"          \
            ]         \
          }");
    wxString command = wxString::Format(wxString("{   \
            %s, \"query\": {"), ownerCMD);
    if (elements.size() > 0) command = command + elementsCMD + wxString(", ");
    if (types.size() > 0) command = command + typesCMD + wxString(", ");
    if (spins.size() > 0) command = command + spinsCMD + wxString(", ");
    if (gapTypes.size() > 0) command = command + gapTypesCMD + wxString(", ");
    if (AuthorPrefix != wxT("")) command = command + mainAuthorCMD + wxString(", ");
    command = command + onlyWithBandStructure + wxString("},");
    command = command + paginationCMD + wxString(",");
    command = command + requiredCMD;
    command = command + wxString("}");
    return command;
    
    
// response structure:
//    {
//  "owner": "public",
//  "query": {
//    "name": "results.material.elements",
//    "value": {
//      "all": [
//        "C"
//      ]
//    }
//  },
//  "pagination": {
//    "page_size": 5,
//    "order_by": "upload_create_time",
//    "order": "asc",
//    "total": 1
//  },
//  "required": {
//    "include": [
//      "entry_id",
//      "mainfile",
//      "upload_id",
//      "authors",
//      "upload_create_time",
//      "last_processing_time",
//      "published",
//      "main_author",
//      "entry_create_time",
//      "nomad_version",
//      "results.method.simulation.dft.xc_functional_type",
//      "results.method.simulation.program_name",
//      "results.material.structural_type",
//      "results.material.chemical_formula_anonymous",
//      "results.material.chemical_formula_descriptive",
//      "results.material.chemical_formula_hill",
//      "results.material.chemical_formula_reduced",
//      "results.method.method_name"
//    ]
//  },
//  "data": [
//    {
//      "last_processing_time": "2022-05-17T11:25:27.381000",
//      "upload_create_time": "2022-05-17T11:24:37.623000",
//      "upload_id": "w9u8tUCDTBWhcE2yJTIKwQ",
//      "mainfile": "INFO.OUT",
//      "main_author": {
//        "user_id": "521be22f-503c-402d-be48-00615be8d739",
//        "name": "Lauri Himanen"
//      },
//      "entry_create_time": "2022-05-17T11:25:27.266000",
//      "published": true,
//      "results": {
//        "material": {
//          "chemical_formula_anonymous": "A6B4",
//          "structural_type": "1D",
//          "chemical_formula_reduced": "C6H4",
//          "chemical_formula_descriptive": "C6H4",
//          "chemical_formula_hill": "C6H4"
//        },
//        "method": {
//          "method_name": "DFT",
//          "simulation": {
//            "dft": {
//              "xc_functional_type": "GGA"
//            },
//            "program_name": "exciting"
//          }
//        }
//      },
//      "entry_id": "XRrvT8xgm9VOh4yq5Yrk5Otd2mfV",
//      "nomad_version": "1.0.8",
//      "authors": [
//        {
//          "user_id": "521be22f-503c-402d-be48-00615be8d739",
//          "name": "Lauri Himanen"
//        },
//        {
//          "user_id": "c6e033bc-b1db-42f1-b28d-d9236c570684",
//          "name": "Jari Järvi"
//        }
//      ]
//    }
//  ]
//}

}

#ifdef __WINDOWS__
int Nomad::runWindowsCmd(const char* cmd, std::string& outOutput) {

    HANDLE g_hChildStd_OUT_Rd = NULL;
    HANDLE g_hChildStd_OUT_Wr = NULL;
    HANDLE g_hChildStd_ERR_Rd = NULL;
    HANDLE g_hChildStd_ERR_Wr = NULL;

    SECURITY_ATTRIBUTES sa;
    // Set the bInheritHandle flag so pipe handles are inherited.
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    if (!CreatePipe(&g_hChildStd_ERR_Rd, &g_hChildStd_ERR_Wr, &sa, 0))     { return 1; } // Create a pipe for the child process's STDERR.
    if (!SetHandleInformation(g_hChildStd_ERR_Rd, HANDLE_FLAG_INHERIT, 0)) { return 1; } // Ensure the read handle to the pipe for STDERR is not inherited.
    if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &sa, 0))     { return 1; } // Create a pipe for the child process's STDOUT.
    if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0)) { return 1; } // Ensure the read handle to the pipe for STDOUT is not inherited

    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    bool bSuccess = FALSE;

    // Set up members of the PROCESS_INFORMATION structure.
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

    // Set up members of the STARTUPINFO structure.
    // This structure specifies the STDERR and STDOUT handles for redirection.
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO); 
   siStartInfo.hStdError = g_hChildStd_OUT_Wr;
   siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
   siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

//    char arg[] = "curl -I https://www.keycdn.com"; //OK works
    // Convert char string to required LPWSTR string
    wchar_t text[1000];
    mbstowcs(text, cmd, strlen(cmd) + 1);
    LPWSTR command = text;
    // Create the child process.
    bSuccess = CreateProcess(
        NULL,             // program name
        command,       // command line
        NULL,             // process security attributes
        NULL,             // primary thread security attributes
        TRUE,             // handles are inherited
        CREATE_NO_WINDOW, // creation flags (this is what hides the window)
        NULL,             // use parent's environment
        NULL,             // use parent's current directory
        &siStartInfo,     // STARTUPINFO pointer
        &piProcInfo       // receives PROCESS_INFORMATION
    );

   // If an error occurs, exit the application. 
   if ( ! bSuccess ) {
    wxMessageBox(wxString("Could not start NOMAD process!"));
    ErrorExit(TEXT("CreateProcess"));
    CloseHandle(piProcInfo.hProcess);
      CloseHandle(piProcInfo.hThread);
      
      // Close handles to the stdin and stdout pipes no longer needed by the child process.
      // If they are not explicitly closed, there is no way to recognize that the child process has ended.
      CloseHandle(g_hChildStd_ERR_Wr);
      CloseHandle(g_hChildStd_OUT_Wr);
      CloseHandle(g_hChildStd_ERR_Rd);
      CloseHandle(g_hChildStd_OUT_Rd);
      return 0;
   }
   else 
   {
//           wxMessageBox(wxString("NOMAD process started!"));
//    ErrorExit(TEXT("CreateProcess"));
      CloseHandle(piProcInfo.hProcess);
      CloseHandle(piProcInfo.hThread);
      
      // Close handles to the stdin and stdout pipes no longer needed by the child process.
      // If they are not explicitly closed, there is no way to recognize that the child process has ended.
      CloseHandle(g_hChildStd_ERR_Wr);
      CloseHandle(g_hChildStd_OUT_Wr);
   }
   

    
    // read output
    #define BUFSIZE 4096
    DWORD dwRead;
    CHAR chBuf[BUFSIZE];
    for (;;) { // read stdout
        bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
        if(!bSuccess || dwRead == 0) {
            break;
        }
        std::string s(chBuf, dwRead);
        outOutput += s;
    }
    dwRead = 0;
    for (;;) { // read stderr
        bSuccess = ReadFile(g_hChildStd_ERR_Rd, chBuf, BUFSIZE, &dwRead, NULL);
        if(!bSuccess || dwRead == 0) {
            break;
        }
        std::string s(chBuf, dwRead);
        outOutput += s;
    }


    
    CloseHandle(g_hChildStd_ERR_Rd);
    CloseHandle(g_hChildStd_OUT_Rd);
    // The remaining open handles are cleaned up when this process terminates.
    // To avoid resource leaks in a larger application,
    // close handles explicitly.
    return 0;
}


void Nomad::my_cmd()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // CMD command here
    char arg[] = "matlab";
    // Convert char string to required LPWSTR string
    wchar_t text[500];
    mbstowcs(text, arg, strlen(arg) + 1);
    LPWSTR command = text;
    // Run process
    CreateProcess (NULL, command, NULL, NULL, 0, 
    CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
}

void Nomad::ErrorExit(PTSTR lpszFunction) 
// Format a readable error message, display a message box, 
// and exit from the application.
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf);
    wxMessageBox(wxString((LPCTSTR)lpDisplayBuf));
    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}


#endif
