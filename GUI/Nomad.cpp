#include "Nomad.h"

// this is a definition so can't be in a header
wxDEFINE_EVENT(NomadEVT_OnQueryStarted, wxCommandEvent);
wxDEFINE_EVENT(NomadEVT_OnQueryDataReceived, wxCommandEvent);
wxDEFINE_EVENT(NomadEVT_OnQueryErrorReceived, wxCommandEvent);
wxDEFINE_EVENT(NomadEVT_OnQueryFinished, wxCommandEvent);

Nomad::Nomad(wxWindow* ParentRef)
{
    Parent = ParentRef;
    owner = wxString("visible");
    pagination = 5;
    sortBy = "upload_create_time";

//    elements.push_back(wxString("C"));
//    types.push_back(wxString("2D"));
//    spins.push_back(wxString("false"));
//    gapTypes.push_back(wxString("indirect"));

}

Nomad::~Nomad()
{
}

std::string Nomad::query(wxString owner, std::vector<wxString> elements, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy)
{
    wxString command = CreateCommand(owner, elements, types, spins, gapTypes, pagination, sortBy);
    std::string out = Nomad::exec(command.c_str());
    return out;
}

void Nomad::queryProcess()
{
    SendEventQueryStarted();
    std::string out = query(this->owner, this->elements, this->types, this->spins, this->gapTypes, this->pagination, this->sortBy);
    wxString data = wxString(out);
    bool isData = data.Contains(wxString("\"data\": ["));
    if (isData)
        SendEventQueryDataReceived(data);
    else
        SendEventQueryErrorReceived(data);
    SendEventQueryFinished();
}

void Nomad::startQuery()
{
    try
	{
		std::thread NomadThread(&Nomad::queryProcess, this);
		if(NomadThread.joinable())
		{
			NomadThread.detach();
		}
	}
    catch(std::exception& ex)
    {
		wxMessageBox("Error nt001: Unable to start NOMAD ...");
	}
}

void Nomad::SendEventQueryStarted()
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_OnQueryStarted);
    wxQueueEvent(Parent, event);
}

void Nomad::SendEventQueryDataReceived(wxString data)
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_OnQueryDataReceived);
    event->SetString(data);
    wxQueueEvent(Parent, event);
}

void Nomad::SendEventQueryErrorReceived(wxString error)
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_OnQueryErrorReceived);
    event->SetString(error);
    wxQueueEvent(Parent, event);
}

void Nomad::SendEventQueryFinished()
{
    wxCommandEvent* event = new wxCommandEvent(NomadEVT_OnQueryFinished);
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

wxString Nomad::CreateCommand(wxString owner, std::vector<wxString> elements, std::vector<wxString> types, std::vector<wxString> spins, std::vector<wxString> gapTypes, int pagination, wxString sortBy)
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
        \\\"order_by\\\": \\\"%s\\\"         \
      }           \
    }\""), pagination, sortBy);

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
