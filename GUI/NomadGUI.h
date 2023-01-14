#ifndef NOMADGUI_H
#define NOMADGUI_H
#include "wxcrafter.h"
#include <wx/tglbtn.h>
#include <Nomad.h>
#include <wx/mstream.h>
#include "tinyjson.hpp"
#include <wx/listctrl.h>
#include "GraphClass.h"
#include "LoginClass.h"
#include <wx/clipbrd.h>

using namespace tiny;
//using namespace rapidjson;

class NomadGUI : public NomadGUIBase
{
public:
    Nomad* nomad;
    Sec30* sec30;
    GraphClass* main_graph2d0;
    GraphClass* main_graph2d;
    Sec30* remote_sec30;
    int shownPage = 2;
    int previousMainPage = -1;
    
    wxString owner = wxString("visible");
    bool exclusive_composition = false;
    std::vector<wxString> elements;
    std::vector<wxString> types;
    std::vector<wxString> spins;
    std::vector<wxString> gapTypes;
    wxString AuthorPrefix = wxT("");
    wxString structural_type = wxT("");
    
    int pagination = 200;
    int page = 1;
    bool loadingEntry = false;
    
    Aint0D species_indices;
    Adouble1D fractional_site_positions;
    double a[3],b[3],c[3];
    
    NomadGUI(wxWindow* parent, Sec30* main_sec30, GraphClass* _main_graph2d0, GraphClass* _main_graph2d);
    
    wxListView* entryList;
    
    GraphClass* graph2d;
//    LoginClass* loginClass;
    
    virtual ~NomadGUI();
    
    void nomadEVT_On_State_Idle(wxCommandEvent& event);
    void nomadEVT_On_State_Completed(wxCommandEvent& event);
    void nomadEVT_On_State_Failed(wxCommandEvent& event);
    void nomadEVT_On_State_Cancelled(wxCommandEvent& event);
    void nomadEVT_On_State_Active(wxCommandEvent& event);
    void nomadEVT_On_State_Unauthorized(wxCommandEvent& event);

    void SearchOnClick(wxCommandEvent& event);
    void BackOnClick(wxCommandEvent& event);
    void addElement(wxGridSizer* periodicTableGridSizer, wxString number, wxString weight, wxString name, wxString abv, wxString Group, wxString ElectronConfig);
    void addUploadRow(wxString uploadID, wxString uploadInfo);
    void addEmpty(int n, wxGridSizer* periodicTableGridSizer);
    void initSearchPanel();
    void setPage(int pageNumber);
    void InitializeSec30Arrays();
    void CopyToTBStudio();
    void loadEntriesPage(int pageNumber);
    void PreviousPageOnClick(wxCommandEvent& event);
    void NextPageOnClick(wxCommandEvent& event);
    void OnSortChanged(wxCommandEvent &event);
    void setLoadingEntryState(bool state);
    
protected:
    virtual void btnMyProjects_OnClick(wxCommandEvent& event);
    virtual void btnExplore_OnClick(wxCommandEvent& event);
    virtual void UserNamePrefix_OnUpdated(wxCommandEvent& event);
    virtual void LoadEntry_In_TBStudio_OnClick(wxCommandEvent& event);
    virtual void EntryID_OnEnter(wxCommandEvent& event);
    virtual void testlistctrl_On_Item_Activated(wxListEvent& event);
    virtual void testlistctrl_On_Item_RightClick(wxListEvent& event);
    virtual void testlistctrl_On_Item_Selected(wxListEvent& event);
    virtual void bulk_onChanged(wxCommandEvent& event);
    virtual void dim_1d_onChanged(wxCommandEvent& event);
    virtual void dim_2d_onChanged(wxCommandEvent& event);
    virtual void direct_onChanged(wxCommandEvent& event);
    virtual void exclusively_composition_onChanged(wxCommandEvent& event);
    virtual void indirect_onChanged(wxCommandEvent& event);
    virtual void not_spin_onChanged(wxCommandEvent& event);
    virtual void spin_onChanged(wxCommandEvent& event);
    virtual void surface_onChanged(wxCommandEvent& event);
    virtual void addInfo(wxString label, wxString value, wxString clipboardValue = wxT(""));
    virtual void addSpacer();
    virtual void CopyTextToClipboard(wxCommandEvent& event);
    int getIndex(std::vector<wxString>& List, wxString item);
    void add(std::vector<wxString>& List, wxString item);
    void remove(std::vector<wxString>& List, wxString item);
    bool includes(std::vector<wxString>& List, wxString item);
    void onElementToggle(wxCommandEvent& event);
    void openUpload_onClick(wxCommandEvent& event);
    wxBitmap GetPng(const void* data, size_t length);
};
#endif // NOMADGUI_H
