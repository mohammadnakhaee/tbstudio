#include "NomadGUI.h"
#include "Embeded.h"
#define CONFIGURU_IMPLEMENTATION 1
#include <configuru.hpp>

configuru::Config resolveRef(configuru::Config object, wxString path);
void ImportFromNomad(configuru::Config data, bool &isBandLoaded, int &nAtoms, int &maxneig, int &mspin, double &ChemP, int &nKp, Adouble1D &lattice_vectors, Adouble1D &cartesian_site_positions, Aint0D &dimension_types, Astring0D &species_at_sites, Astring0D &kLabel, Adouble1D &fractional_KPoints, Adouble1D &energies_spin0, Adouble1D &energies_spin1, Aint0D &n_perpath, wxString &chemical_formula_reduced, wxString &chemical_formula_anonymous, wxString &program_name, wxString &method_name, wxString &entry_id, wxString &upload_id, wxString &parser_name, wxString &structural_type);

bool s = true;
NomadGUI::NomadGUI(wxWindow* parent, Sec30* main_sec30, GraphClass* _main_graph2d0, GraphClass* _main_graph2d)
    : NomadGUIBase(parent)
{
    sec30 = main_sec30;
    main_graph2d0 = _main_graph2d0;
    main_graph2d = _main_graph2d;
    nomad = new Nomad(this);
    remote_sec30 = new Sec30(this);
    InitializeSec30Arrays();
    
    this->Connect(NomadEVT_On_State_Idle, wxCommandEventHandler(NomadGUI::nomadEVT_On_State_Idle), NULL, this);
    this->Connect(NomadEVT_On_State_Completed, wxCommandEventHandler(NomadGUI::nomadEVT_On_State_Completed), NULL, this);
    this->Connect(NomadEVT_On_State_Failed, wxCommandEventHandler(NomadGUI::nomadEVT_On_State_Failed), NULL, this);
    this->Connect(NomadEVT_On_State_Cancelled, wxCommandEventHandler(NomadGUI::nomadEVT_On_State_Cancelled), NULL, this);
    this->Connect(NomadEVT_On_State_Active, wxCommandEventHandler(NomadGUI::nomadEVT_On_State_Active), NULL, this);
    this->Connect(NomadEVT_On_State_Unauthorized, wxCommandEventHandler(NomadGUI::nomadEVT_On_State_Unauthorized), NULL, this);
    
    initSearchPanel();

    btnSearch->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NomadGUI::SearchOnClick), NULL, this);
    ctlBack->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NomadGUI::BackOnClick), NULL, this);
    
    ctlLeftPage->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NomadGUI::PreviousPageOnClick), NULL, this);
    ctlRightPage->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NomadGUI::NextPageOnClick), NULL, this);
    
    EntryID->SetHint(wxT("NOMAD entry_id"));
    EntryID->SetDescriptiveText(wxT(""));
    EntryID->Bind(wxEVT_SEARCH, &NomadGUI::EntryID_OnEnter, this);
    
    UserNamePrefix->SetHint(wxT("NOMAD main_author"));
    UserNamePrefix->SetDescriptiveText(wxT(""));
    
    ctrl_nomad_user->SetHint(wxT("NOMAD user name or Email"));
    ctrl_nomad_user->SetDescriptiveText(wxT(""));
    
    ctrl_nomad_pass->SetHint(wxT("NOMAD password"));
    ctrl_nomad_pass->SetDescriptiveText(wxT(""));
    
    setPage(shownPage);
//    loginClass = new LoginClass(this);
    
//    nomad->getRefreshToken(wxT("test"), wxT("password"));
    nomad->getRefreshToken(wxT("mohammad.nakhaee.1@gmail.com"), wxT("E4520m1244"));

    ctlSortBy->Append(wxT("Create time (ascending)"));   //"upload_create_time"
    ctlSortBy->Append(wxT("Create time (descending)"));  //"upload_create_time"
    ctlSortBy->Append(wxT("Program name (ascending)"));  //"results.method.simulation.program_name"
    ctlSortBy->Append(wxT("Program name (descending)")); //"results.method.simulation.program_name"
    ctlSortBy->Append(wxT("Author name (ascending)"));   //main_author.name
    ctlSortBy->Append(wxT("Author name (descending)"));  //main_author.name
    
    ctlSortBy->Select(0);
    ctlSortBy->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(NomadGUI::OnSortChanged), NULL, this);
    
//    nomad->elements.push_back(wxString("C"));
////    nomad->types.push_back(wxString("2D"));
//    nomad->spins.push_back(wxString("false"));
//    nomad->gapTypes.push_back(wxString("indirect"));
//    nomad->startQuery();
    
    this->SetSize(wxSize(1200, 800));
    searchPanel->Layout();
    this->SetSize(wxSize(1200, 800));
    
    entryList = new wxListView(leftPanel, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(leftPanel, wxSize(-1,-1)), wxLC_REPORT);
    
    entryList->InsertColumn(0, _("index"));
    entryList->InsertColumn(1, _("Formula"));
    entryList->InsertColumn(2, _("Type"));
    entryList->InsertColumn(3, _("Program"));
    entryList->InsertColumn(4, _("Method"));
    entryList->InsertColumn(5, _("Author"));
    
    entryList->Connect(wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(NomadGUI::testlistctrl_On_Item_Selected), NULL, this);
    entryList->Connect(wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler(NomadGUI::testlistctrl_On_Item_RightClick), NULL, this);
    entryList->Connect(wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler(NomadGUI::testlistctrl_On_Item_Activated), NULL, this);
    
    wxBoxSizer* leftPanelSizer = (wxBoxSizer*)leftPanel->GetSizer();
    leftPanelSizer->Add(entryList, 1, wxEXPAND, WXC_FROM_DIP(5));
    leftPanel->Layout();
    
    graph2d = new GraphClass(entryVisual, 2, remote_sec30, 0);
    graph2d->sec30 = remote_sec30;
    graph2d->SetCursor(wxCursor(wxCURSOR_CROSS));
    
    wxBoxSizer* entryVisualSizer = (wxBoxSizer*)entryVisual->GetSizer();
    entryVisualSizer->Add(graph2d, 1, wxEXPAND, WXC_FROM_DIP(5));
    entryVisual->Layout();
    
    

    
//    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
//    Document d;
//    d.Parse(json);
    
//    int a = d["stars"].GetInt();

//const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
//            configuru::Config cfg = configuru::parse_string(json, configuru::JSON, "string");
//            
//            if (cfg.has_key("project")) {
//                std::string beta = (std::string)cfg["project"];
//                wxMessageBox(wxString(beta));
//            }
}

NomadGUI::~NomadGUI()
{
    delete nomad;
    delete remote_sec30;
    delete graph2d;
//    delete loginClass;
}


void NomadGUI::InitializeSec30Arrays()
{
    remote_sec30->init();
}

void NomadGUI::CopyToTBStudio()
{
    if (fractional_site_positions.size() > 99) {
        wxMessageBox(wxT("The number of atoms in unitcell is too large!"));
        return;
    }

    sec30->init();

    sec30->ArraysOf0DInt[0] = remote_sec30->ArraysOf0DInt[0];
    sec30->ArraysOf0DInt[1] = remote_sec30->ArraysOf0DInt[1];
    sec30->ArraysOf0DInt[2] = remote_sec30->ArraysOf0DInt[2];
    sec30->ArraysOf0DInt[3] = remote_sec30->ArraysOf0DInt[3];
    sec30->ArraysOf0DInt[6] = remote_sec30->ArraysOf0DInt[6];
    sec30->ArraysOf0DDouble[0] = remote_sec30->ArraysOf0DDouble[0];
    
    sec30->ArraysOf1DDouble[0] = remote_sec30->ArraysOf1DDouble[0];
    sec30->ArraysOf1DDouble[1] = remote_sec30->ArraysOf1DDouble[1];
    sec30->ArraysOf1DDouble[2] = remote_sec30->ArraysOf1DDouble[2];
    sec30->ArraysOf1DDouble[3] = remote_sec30->ArraysOf1DDouble[3];
    
    sec30->ArraysOf1DString[0] = remote_sec30->ArraysOf1DString[0];
    sec30->ArraysOf2DDouble[0] = remote_sec30->ArraysOf2DDouble[0];
    sec30->ArraysOf2DDouble[1] = remote_sec30->ArraysOf2DDouble[1];
    sec30->ArraysOf2DDouble[4] = remote_sec30->ArraysOf2DDouble[4];
    
    sec30->ArraysOf0DInt[4] = remote_sec30->ArraysOf0DInt[4];
    sec30->ArraysOf0DInt[5] = remote_sec30->ArraysOf0DInt[5];
    
    sec30->ArraysOf0DDouble[1] = remote_sec30->ArraysOf0DDouble[1];
    sec30->ArraysOf0DDouble[2] = remote_sec30->ArraysOf0DDouble[2];
    sec30->ArraysOf0DDouble[3] = remote_sec30->ArraysOf0DDouble[3];
    sec30->ArraysOf0DDouble[4] = remote_sec30->ArraysOf0DDouble[4];
    
    sec30->ArraysOf0DDouble[5] = remote_sec30->ArraysOf0DDouble[5];
    sec30->ArraysOf0DDouble[6] = remote_sec30->ArraysOf0DDouble[6];
    sec30->ArraysOf0DDouble[7] = remote_sec30->ArraysOf0DDouble[7];
    sec30->ArraysOf0DDouble[8] = remote_sec30->ArraysOf0DDouble[8];
    
    myGrid* kabc = sec30->GetGridObject(_("KABC_Coords"));
    
    for(int atin=0; atin < 99; atin++) {
        kabc->SetCellValue(atin, 0, wxT(""));
        kabc->SetCellValue(atin, 1, wxT(""));
        kabc->SetCellValue(atin, 2, wxT(""));
        kabc->SetCellValue(atin, 3, wxT(""));
    }
    
    int atomIndex = -1;
    for(Adouble1D::iterator it = std::begin(fractional_site_positions); it != std::end(fractional_site_positions); ++it) {
        atomIndex++;
        double frac[3] = {(*it).at(0), (*it).at(1), (*it).at(2)};
        int atomKind = species_indices.at(atomIndex);
        wxString ddd = wxString::Format(wxT("%f"), frac[0]);
        kabc->SetCellValue(atomIndex, 0, wxString::Format(wxT("%d"), atomKind));
        kabc->SetCellValue(atomIndex, 1, wxString::Format(wxT("%f"), frac[0]));
        kabc->SetCellValue(atomIndex, 2, wxString::Format(wxT("%f"), frac[1]));
        kabc->SetCellValue(atomIndex, 3, wxString::Format(wxT("%f"), frac[2]));
    }
    
    if (structural_type == wxT("bulk")) {
        sec30->SetVar(_("TBl[0]"), 1, false);
        sec30->SetVar(_("TBm[0]"), 1, false);
        sec30->SetVar(_("TBn[0]"), 1, false);
    } else if (structural_type == wxT("2D") || structural_type == wxT("surface")) {
        sec30->SetVar(_("TBl[0]"), 1, false);
        sec30->SetVar(_("TBm[0]"), 1, false);
        sec30->SetVar(_("TBn[0]"), 0, false);
    } else if (structural_type == wxT("1D")) {
        sec30->SetVar(_("TBl[0]"), 1, false);
        sec30->SetVar(_("TBm[0]"), 0, false);
        sec30->SetVar(_("TBn[0]"), 0, false);
    }
    sec30->SetCheckVar(_("TBViewmode[0]"), true, false);

    sec30->SetVar(_("a0[0]"), a[0], false);
    sec30->SetVar(_("a0[1]"), a[1], false);
    sec30->SetVar(_("a0[2]"), a[2], false);
    sec30->SetVar(_("b0[0]"), b[0], false);
    sec30->SetVar(_("b0[1]"), b[1], false);
    sec30->SetVar(_("b0[2]"), b[2], false);
    sec30->SetVar(_("c0[0]"), c[0], false);
    sec30->SetVar(_("c0[1]"), c[1], false);
    sec30->SetVar(_("c0[2]"), c[2], true);
    
    main_graph2d0->myRefresh2d();
    main_graph2d->myRefresh2d();
}

void NomadGUI::loadEntriesPage(int pageNumber)
{
    wxString sortBy;
    wxString order;
    int selected = ctlSortBy->GetSelection();
    if (selected == 0) {
        sortBy = "upload_create_time";
        order = "asc";
    } else if (selected == 1) {
        sortBy = "upload_create_time";
        order = "desc";
    } else if (selected == 2) {
        sortBy = "results.method.simulation.program_name";
        order = "asc";
    } else if (selected == 3) {
        sortBy = "results.method.simulation.program_name";
        order = "desc";
    } else if (selected == 4) {
        sortBy = "main_author.name";
        order = "asc";
    } else if (selected == 5) {
        sortBy = "main_author.name";
        order = "desc";
    }
    
    nomad->owner = owner;
    nomad->elements = elements;
    nomad->exclusive_composition = exclusive_composition;
    nomad->types = types;
    nomad->spins = spins;
    nomad->AuthorPrefix = AuthorPrefix;
    nomad->gapTypes = gapTypes;
    nomad->pagination = pagination;
    nomad->page = pageNumber;
    nomad->sortBy = sortBy;
    nomad->order = order;
    nomad->startQuery();
}


void NomadGUI::SearchOnClick(wxCommandEvent& event)
{
    page = 1;
    loadEntriesPage(page);
}

void NomadGUI::NextPageOnClick(wxCommandEvent& event)
{
    page = page + 1;
    loadEntriesPage(page);
}

void NomadGUI::PreviousPageOnClick(wxCommandEvent& event)
{
    if (page == 1) return;
    page = page - 1;
    loadEntriesPage(page);
}

void NomadGUI::OnSortChanged(wxCommandEvent &event)
{
    loadEntriesPage(page);
}

void NomadGUI::BackOnClick(wxCommandEvent& event)
{
    setPage(previousMainPage);
}

void NomadGUI::addElement(wxGridSizer* periodicTableGridSizer, wxString number, wxString weight, wxString name, wxString abv, wxString Group, wxString ElectronConfig)
{
    wxToggleButton* elementButton = new wxToggleButton(periodicTable, wxID_ANY, _(abv), wxDefaultPosition, wxDLG_UNIT(periodicTable, wxSize(30,30)), 0);
    wxString toolTip = wxString::Format(wxString("Name: %s\n"), name);
    toolTip = toolTip + wxString::Format(wxString("Atomic number: %s\n"), number);
    toolTip = toolTip + wxString::Format(wxString("Atomic weight: %s (u)\n"), weight);
    toolTip = toolTip + wxString::Format(wxString("Electron config: %s"), ElectronConfig);
    elementButton->SetToolTip(toolTip);
    elementButton->SetValue(false);
    periodicTableGridSizer->Add(elementButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));
    elementButton->SetMinSize(wxSize(30,30));
    
    elementButton->Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(NomadGUI::onElementToggle), NULL, this);
}

void NomadGUI::addUploadRow(wxString uploadID, wxString uploadInfo)
{
    wxBoxSizer* panelUploadsListSizer = (wxBoxSizer*)panelUploadsList->GetSizer();
    
    wxPanel* uploadRow = new wxPanel(panelUploadsList, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(panelUploadsList, wxSize(-1,-1)), wxTAB_TRAVERSAL);
    uploadRow->SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
    
    panelUploadsListSizer->Add(uploadRow, 0, wxALL|wxEXPAND, WXC_FROM_DIP(5));
    
    wxFlexGridSizer* flexGridSizer175517335261 = new wxFlexGridSizer(0, 8, 0, 0);
    flexGridSizer175517335261->SetFlexibleDirection( wxBOTH );
    flexGridSizer175517335261->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    flexGridSizer175517335261->AddGrowableCol(5);
    uploadRow->SetSizer(flexGridSizer175517335261);
    
    wxPanel* m_panel14399182436485362 = new wxPanel(uploadRow, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(uploadRow, wxSize(100,-1)), wxTAB_TRAVERSAL);
    
    flexGridSizer175517335261->Add(m_panel14399182436485362, 1, wxEXPAND, WXC_FROM_DIP(5));
    m_panel14399182436485362->SetMinSize(wxSize(100,-1));

    wxStaticText* m_staticText177234464754630 = new wxStaticText(uploadRow, wxID_ANY, uploadInfo, wxDefaultPosition, wxDLG_UNIT(uploadRow, wxSize(-1,-1)), 0);
    
    flexGridSizer175517335261->Add(m_staticText177234464754630, 0, wxALL|wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));
    
    wxPanel* m_panel1439918243657660 = new wxPanel(uploadRow, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(uploadRow, wxSize(20,-1)), wxTAB_TRAVERSAL);
    
    flexGridSizer175517335261->Add(m_panel1439918243657660, 1, wxEXPAND, WXC_FROM_DIP(5));
    
    wxStaticText* m_staticText17723446475463 = new wxStaticText(uploadRow, wxID_ANY, wxString::Format(wxT("upload_id: %s"), uploadID), wxDefaultPosition, wxDLG_UNIT(uploadRow, wxSize(-1,-1)), 0);
    
    flexGridSizer175517335261->Add(m_staticText17723446475463, 0, wxALL|wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));
    
    wxBitmapButton* copyToClipboardButton = new wxBitmapButton(uploadRow, wxID_ANY, GetPng(clipboard_png,clipboard_png_size), wxDefaultPosition, wxDLG_UNIT(uploadRow, wxSize(-1,-1)), wxBU_AUTODRAW);
    copyToClipboardButton->SetToolTip(uploadID);
    flexGridSizer175517335261->Add(copyToClipboardButton, 0, wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));
    copyToClipboardButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CopyTextToClipboard), NULL, this);
    
    wxPanel* m_panel143991824365766 = new wxPanel(uploadRow, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(uploadRow, wxSize(-1,-1)), wxTAB_TRAVERSAL);
    
    flexGridSizer175517335261->Add(m_panel143991824365766, 1, wxEXPAND, WXC_FROM_DIP(5));
    
    wxButton* uploadButton = new wxButton(uploadRow, wxID_ANY, _("Open"), wxDefaultPosition, wxDLG_UNIT(uploadRow, wxSize(-1,-1)), 0);
    uploadButton->SetToolTip(uploadID);
    flexGridSizer175517335261->Add(uploadButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));
    uploadButton->Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(NomadGUI::openUpload_onClick), NULL, this);

    wxPanel* m_panel1439918243648505968 = new wxPanel(uploadRow, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(uploadRow, wxSize(100,-1)), wxTAB_TRAVERSAL);
    
    flexGridSizer175517335261->Add(m_panel1439918243648505968, 1, wxEXPAND, WXC_FROM_DIP(5));
    m_panel1439918243648505968->SetMinSize(wxSize(100,-1));
}

void NomadGUI::addEmpty(int n, wxGridSizer* periodicTableGridSizer)
{
    for (int i=0; i<n; i++) periodicTableGridSizer->AddSpacer(30);
}

void NomadGUI::initSearchPanel()
{
    wxGridSizer* periodicTableGridSizer = (wxGridSizer*)periodicTable->GetSizer();
//    periodicTable->SetSizer(periodicTableGridSizer);
    
    addElement(periodicTableGridSizer, "1", "1.008", "Hydrogen", "H", "1", "1s1");
    addEmpty(16, periodicTableGridSizer);
    addElement(periodicTableGridSizer, "2", "4.003", "Helium", "He", "18", "1s2");
    
    addElement(periodicTableGridSizer, "3", "6.941", "Lithium", "Li", "1", "[He] 2s1");
    addElement(periodicTableGridSizer, "4", "9.012", "Beryllium", "Be", "2", "[He] 2s2");
    addEmpty(10, periodicTableGridSizer);
    addElement(periodicTableGridSizer, "5", "10.811", "Boron", "B", "13", "[He] 2s2 2p1");
    addElement(periodicTableGridSizer, "6", "12.011", "Carbon", "C", "14", "[He] 2s2 2p2");
    addElement(periodicTableGridSizer, "7", "14.007", "Nitrogen", "N", "15", "[He] 2s2 2p3");
    addElement(periodicTableGridSizer, "8", "15.999", "Oxygen", "O", "16", "[He] 2s2 2p4");
    addElement(periodicTableGridSizer, "9", "18.998", "Fluorine", "F", "17", "[He] 2s2 2p5");
    addElement(periodicTableGridSizer, "10", "20.180", "Neon", "Ne", "18", "[He] 2s2 2p6");
    
    addElement(periodicTableGridSizer, "11", "22.990", "Sodium", "Na", "1", "[Ne] 3s1");
    addElement(periodicTableGridSizer, "12", "24.305", "Magnesium", "Mg", "2", "[Ne] 3s2");
    addEmpty(10, periodicTableGridSizer);
    addElement(periodicTableGridSizer, "13", "26.982", "Aluminum", "Al", "13", "[Ne] 3s2 3p1");
    addElement(periodicTableGridSizer, "14", "28.086", "Silicon", "Si", "14", "[Ne] 3s2 3p2");
    addElement(periodicTableGridSizer, "15", "30.974", "Phosphorus", "P", "15", "[Ne] 3s2 3p3");
    addElement(periodicTableGridSizer, "16", "32.065", "Sulfur", "S", "16", "[Ne] 3s2 3p4");
    addElement(periodicTableGridSizer, "17", "35.453", "Chlorine", "Cl", "17", "[Ne] 3s2 3p5");
    addElement(periodicTableGridSizer, "18", "39.948", "Argon", "Ar", "18", "[Ne] 3s2 3p6");
    
    addElement(periodicTableGridSizer, "19", "39.098", "Potassium", "K", "1", "[Ar] 4s1");
    addElement(periodicTableGridSizer, "20", "40.078", "Calcium", "Ca", "2", "[Ar] 4s2");
    addElement(periodicTableGridSizer, "21", "44.956", "Scandium", "Sc", "3", "[Ar] 3d1 4s2");
    addElement(periodicTableGridSizer, "22", "47.867", "Titanium", "Ti", "4", "[Ar] 3d2 4s2");
    addElement(periodicTableGridSizer, "23", "50.942", "Vanadium", "V", "5", "[Ar] 3d3 4s2");
    addElement(periodicTableGridSizer, "24", "51.996", "Chromium", "Cr", "6", "[Ar] 3d5 4s1");
    addElement(periodicTableGridSizer, "25", "54.938", "Manganese", "Mn", "7", "[Ar] 3d5 4s2");
    addElement(periodicTableGridSizer, "26", "55.845", "Iron", "Fe", "8", "[Ar] 3d6 4s2");
    addElement(periodicTableGridSizer, "27", "58.933", "Cobalt", "Co", "9", "[Ar] 3d7 4s2");
    addElement(periodicTableGridSizer, "28", "58.693", "Nickel", "Ni", "10", "[Ar] 3d8 4s2");
    addElement(periodicTableGridSizer, "29", "63.546", "Copper", "Cu", "11", "[Ar] 3d10 4s1");
    addElement(periodicTableGridSizer, "30", "65.390", "Zinc", "Zn", "12", "[Ar] 3d10 4s2");
    addElement(periodicTableGridSizer, "31", "69.723", "Gallium", "Ga", "13", "[Ar] 3d10 4s2 4p1");
    addElement(periodicTableGridSizer, "32", "72.640", "Germanium", "Ge", "14", "[Ar] 3d10 4s2 4p2");
    addElement(periodicTableGridSizer, "33", "74.922", "Arsenic", "As", "15", "[Ar] 3d10 4s2 4p3");
    addElement(periodicTableGridSizer, "34", "78.960", "Selenium", "Se", "16", "[Ar] 3d10 4s2 4p4");
    addElement(periodicTableGridSizer, "35", "79.904", "Bromine", "Br", "17", "[Ar] 3d10 4s2 4p5");
    addElement(periodicTableGridSizer, "36", "83.800", "Krypton", "Kr", "18", "[Ar] 3d10 4s2 4p6");
    
    addElement(periodicTableGridSizer, "37", "85.468", "Rubidium", "Rb", "1", "[Kr] 5s1");
    addElement(periodicTableGridSizer, "38", "87.620", "Strontium", "Sr", "2", "[Kr] 5s2");
    addElement(periodicTableGridSizer, "39", "88.906", "Yttrium", "Y", "3", "[Kr] 4d1 5s2");
    addElement(periodicTableGridSizer, "40", "91.224", "Zirconium", "Zr", "4", "[Kr] 4d2 5s2");
    addElement(periodicTableGridSizer, "41", "92.906", "Niobium", "Nb", "5", "[Kr] 4d4 5s1");
    addElement(periodicTableGridSizer, "42", "95.940", "Molybdenum", "Mo", "6", "[Kr] 4d5 5s1");
    addElement(periodicTableGridSizer, "43", "98.000", "Technetium", "Tc", "7", "[Kr] 4d5 5s2");
    addElement(periodicTableGridSizer, "44", "101.070", "Ruthenium", "Ru", "8", "[Kr] 4d7 5s1");
    addElement(periodicTableGridSizer, "45", "102.906", "Rhodium", "Rh", "9", "[Kr] 4d8 5s1");
    addElement(periodicTableGridSizer, "46", "106.420", "Palladium", "Pd", "10", "[Kr] 4d10");
    addElement(periodicTableGridSizer, "47", "107.868", "Silver", "Ag", "11", "[Kr] 4d10 5s1");
    addElement(periodicTableGridSizer, "48", "112.411", "Cadmium", "Cd", "12", "[Kr] 4d10 5s2");
    addElement(periodicTableGridSizer, "49", "114.818", "Indium", "In", "13", "[Kr] 4d10 5s2 5p1");
    addElement(periodicTableGridSizer, "50", "118.710", "Tin", "Sn", "14", "[Kr] 4d10 5s2 5p2");
    addElement(periodicTableGridSizer, "51", "121.760", "Antimony", "Sb", "15", "[Kr] 4d10 5s2 5p3");
    addElement(periodicTableGridSizer, "52", "127.600", "Tellurium", "Te", "16", "[Kr] 4d10 5s2 5p4");
    addElement(periodicTableGridSizer, "53", "126.905", "Iodine", "I", "17", "[Kr] 4d10 5s2 5p5");
    addElement(periodicTableGridSizer, "54", "131.293", "Xenon", "Xe", "18", "[Kr] 4d10 5s2 5p6");
    
    addElement(periodicTableGridSizer, "55", "132.906", "Cesium", "Cs", "1", "[Xe] 6s1");
    addElement(periodicTableGridSizer, "56", "137.327", "Barium", "Ba", "2", "[Xe] 6s2");
    addElement(periodicTableGridSizer, "57", "138.906", "Lanthanum", "La", "3", "[Xe] 5d1 6s2");
    addElement(periodicTableGridSizer, "72", "178.490", "Hafnium", "Hf", "4", "[Xe] 4f14 5d2 6s2");
    addElement(periodicTableGridSizer, "73", "180.948", "Tantalum", "Ta", "5", "[Xe] 4f14 5d3 6s2");
    addElement(periodicTableGridSizer, "74", "183.840", "Tungsten", "W", "6", "[Xe] 4f14 5d4 6s2");
    addElement(periodicTableGridSizer, "75", "186.207", "Rhenium", "Re", "7", "[Xe] 4f14 5d5 6s2");
    addElement(periodicTableGridSizer, "76", "190.230", "Osmium", "Os", "8", "[Xe] 4f14 5d6 6s2");
    addElement(periodicTableGridSizer, "77", "192.217", "Iridium", "Ir", "9", "[Xe] 4f14 5d7 6s2");
    addElement(periodicTableGridSizer, "78", "195.078", "Platinum", "Pt", "10", "[Xe] 4f14 5d9 6s1");
    addElement(periodicTableGridSizer, "79", "196.967", "Gold", "Au", "11", "[Xe] 4f14 5d10 6s1");
    addElement(periodicTableGridSizer, "80", "200.590", "Mercury", "Hg", "12", "[Xe] 4f14 5d10 6s2");
    addElement(periodicTableGridSizer, "81", "204.383", "Thallium", "Tl", "13", "[Xe] 4f14 5d10 6s2 6p1");
    addElement(periodicTableGridSizer, "82", "207.200", "Lead", "Pb", "14", "[Xe] 4f14 5d10 6s2 6p2");
    addElement(periodicTableGridSizer, "83", "208.980", "Bismuth", "Bi", "15", "[Xe] 4f14 5d10 6s2 6p3");
    addElement(periodicTableGridSizer, "84", "209.000", "Polonium", "Po", "16", "[Xe] 4f14 5d10 6s2 6p4");
    addElement(periodicTableGridSizer, "85", "210.000", "Astatine", "At", "17", "[Xe] 4f14 5d10 6s2 6p5");
    addElement(periodicTableGridSizer, "86", "222.000", "Radon", "Rn", "18", "[Xe] 4f14 5d10 6s2 6p6");
    
    addElement(periodicTableGridSizer, "87", "223.000", "Francium", "Fr", "1", "[Rn] 7s1");
    addElement(periodicTableGridSizer, "88", "226.000", "Radium", "Ra", "2", "[Rn] 7s2");
    addElement(periodicTableGridSizer, "89", "227.000", "Actinium", "Ac", "3", "[Rn] 6d1 7s2");
    addElement(periodicTableGridSizer, "104", "261.000", "Rutherfordium", "Rf", "4", "");
    addElement(periodicTableGridSizer, "105", "262.000", "Dubnium", "Db", "5", "");
    addElement(periodicTableGridSizer, "106", "266.000", "Seaborgium", "Sg", "6", "");
    addElement(periodicTableGridSizer, "107", "264.000", "Bohrium", "Bh", "7", "");
    addElement(periodicTableGridSizer, "108", "277.000", "Hassium", "Hs", "8", "");
    addElement(periodicTableGridSizer, "109", "268.000", "Meitnerium", "Mt", "9", "");
    addElement(periodicTableGridSizer, "110", "281.000", "Darmstadtium", "Ds", "10", "");
    addElement(periodicTableGridSizer, "111", "282.000", "Roentgenium", "Rg", "11", "");
    addElement(periodicTableGridSizer, "112", "285.000", "Copernicium", "Cn", "12", "");
    addElement(periodicTableGridSizer, "113", "286.000", "Nihonium", "Nh", "", "13");
    addElement(periodicTableGridSizer, "114", "289.000", "Flerovium", "Fl", "14", "");
    addElement(periodicTableGridSizer, "115", "290.000", "Moscovium", "Mc", "15", "");
    addElement(periodicTableGridSizer, "116", "293.000", "Livermorium", "Lv", "16", "");
    addElement(periodicTableGridSizer, "117", "294.000", "Tennessine", "Ts", "17", "");
    addElement(periodicTableGridSizer, "118", "294.000", "Oganesson", "Og", "18", "");
    
    addElement(periodicTableGridSizer, "119", "316.000", "Ununennium (eka-francium)", "Uue", "", "");
    addElement(periodicTableGridSizer, "120", "318.000", "Unbinilium (eka-radium)", "Ubn", "", "");
    addElement(periodicTableGridSizer, "121", "320.000", "Unbiunium (eka-actinium)", "Ubu", "", "");
    addEmpty(15, periodicTableGridSizer);
    
    addEmpty(3, periodicTableGridSizer);
    addElement(periodicTableGridSizer, "58", "140.116", "Cerium", "Ce", "", "[Xe] 4f1 5d1 6s2");
    addElement(periodicTableGridSizer, "59", "140.908", "Praseodymium", "Pr", "", "[Xe] 4f3 6s2");
    addElement(periodicTableGridSizer, "60", "144.240", "Neodymium", "Nd", "", "[Xe] 4f4 6s2");
    addElement(periodicTableGridSizer, "61", "145.000", "Promethium", "Pm", "", "[Xe] 4f5 6s2");
    addElement(periodicTableGridSizer, "62", "150.360", "Samarium", "Sm", "", "[Xe] 4f6 6s2");
    addElement(periodicTableGridSizer, "63", "151.964", "Europium", "Eu", "", "[Xe] 4f7 6s2");
    addElement(periodicTableGridSizer, "64", "157.250", "Gadolinium", "Gd", "", "[Xe] 4f7 5d1 6s2");
    addElement(periodicTableGridSizer, "65", "158.925", "Terbium", "Tb", "", "[Xe] 4f9 6s2");
    addElement(periodicTableGridSizer, "66", "162.500", "Dysprosium", "Dy", "", "[Xe] 4f10 6s2");
    addElement(periodicTableGridSizer, "67", "164.930", "Holmium", "Ho", "", "[Xe] 4f11 6s2");
    addElement(periodicTableGridSizer, "68", "167.259", "Erbium", "Er", "", "[Xe] 4f12 6s2");
    addElement(periodicTableGridSizer, "69", "168.934", "Thulium", "Tm", "", "[Xe] 4f13 6s2");
    addElement(periodicTableGridSizer, "70", "173.040", "Ytterbium", "Yb", "", "[Xe] 4f14 6s2");
    addElement(periodicTableGridSizer, "71", "174.967", "Lutetium", "Lu", "", "[Xe] 4f14 5d1 6s2");
    addEmpty(1, periodicTableGridSizer);
    
    addEmpty(3, periodicTableGridSizer);
    addElement(periodicTableGridSizer, "90", "232.038", "Thorium", "Th", "", "[Rn] 6d2 7s2");
    addElement(periodicTableGridSizer, "91", "231.036", "Protactinium", "Pa", "", "[Rn] 5f2 6d1 7s2");
    addElement(periodicTableGridSizer, "92", "238.029", "Uranium", "U", "", "[Rn] 5f3 6d1 7s2");
    addElement(periodicTableGridSizer, "93", "237.000", "Neptunium", "Np", "", "[Rn] 5f4 6d1 7s2");
    addElement(periodicTableGridSizer, "94", "244.000", "Plutonium", "Pu", "", "[Rn] 5f6 7s2");
    addElement(periodicTableGridSizer, "95", "243.000", "Americium", "Am", "", "[Rn] 5f7 7s2");
    addElement(periodicTableGridSizer, "96", "247.000", "Curium", "Cm", "", "");
    addElement(periodicTableGridSizer, "97", "247.000", "Berkelium", "Bk", "", "");
    addElement(periodicTableGridSizer, "98", "251.000", "Californium", "Cf", "", "");
    addElement(periodicTableGridSizer, "99", "252.000", "Einsteinium", "Es", "", "");
    addElement(periodicTableGridSizer, "100", "257.000", "Fermium", "Fm", "", "");
    addElement(periodicTableGridSizer, "101", "258.000", "Mendelevium", "Md", "", "");
    addElement(periodicTableGridSizer, "102", "259.000", "Nobelium", "No", "", "");
    addElement(periodicTableGridSizer, "103", "262.000", "Lawrencium", "Lr", "", "");
    addEmpty(1, periodicTableGridSizer);
    
    periodicTable->Layout();
    periodicTableGridSizer->Layout();
}

void NomadGUI::setPage(int pageNumber)
{
    if (shownPage == 0 || shownPage == 2) {
        previousMainPage = shownPage;
    }
    shownPage = pageNumber;
//    bool isSearch = pageNumber == 0;
//    ctlBack->Show(!isSearch);
//    ctlNomadLogo->Show(isSearch);
//    ctlNomadAPIText->Show(isSearch);
//    ctlNomadAPI->Show(isSearch);
//    btnSearch->Show(isSearch);
//    searchPanel->Show(isSearch);
//    resultsPanel->Show(!isSearch);
    mainSearchPage->SetSelection(pageNumber);
    
    mainSearchPage->Layout();
}
    
void NomadGUI::nomadEVT_On_State_Active(wxCommandEvent& event)
{
    API_ID ID = (API_ID)event.GetInt();
    switch (ID)
    {
        case API_ID::POST_keycloak_RefreshToken:
        {
//            wxMessageBox(wxT("keycloak_RefreshToken Active"));
            break;
        }
        
        case API_ID::POST_entries_query:
        {
            setPage(1);
            entryList->DeleteAllItems();
            entryList->InsertItem(0, wxT("Searching ..."));
            ctlLeftPage->Enable(false);
            ctlRightPage->Enable(false);
            ctlSortBy->Enable(false);
            break;
        }
        
        case API_ID::GET_entries_entry:
        {
            setLoadingEntryState(true);
            entryInfo->DestroyChildren();
            wxFlexGridSizer* entryInfoGridSizer = (wxFlexGridSizer*)entryInfo->GetSizer();
            entryInfoGridSizer->Clear(false);
            wxStaticText* infoText = new wxStaticText(entryInfo, wxID_ANY, wxT("Please wait! Loading ..."), wxDefaultPosition, wxDLG_UNIT(entryInfo, wxSize(-1,-1)), 0);
            entryInfoGridSizer->Add(infoText, 0, wxALL, WXC_FROM_DIP(5));
            entryInfo->Layout();
                    
            break;
        }
        
        case API_ID::GET_uploads:
        {
            myProjectsTitle->SetLabel(wxT("Loading projects ..."));
            break;
        }
    }
}

void NomadGUI::nomadEVT_On_State_Completed(wxCommandEvent& event)
{
    API_ID ID = (API_ID)event.GetInt();
    
    wxString response = event.GetString();
    // wxMessageBox(response);

//    std::string jsonstring = std::string(response.mb_str(wxConvUTF8).data());    // It works
    std::string jsonstring = std::string(response.ToUTF8().data());
    configuru::Config json = configuru::parse_string(jsonstring.c_str(), configuru::JSON, "string");
//    wxMessageBox(jsonstring);
//    TinyJson json;
//    json.ReadJson(jsonstring);
            
    switch (ID)
    {
        case API_ID::POST_keycloak_RefreshToken:
        {
            std::string access_token = (std::string)json["access_token"];
            std::string refresh_token = (std::string)json["refresh_token"];
            nomad->updateToken(wxString(refresh_token));
//            wxMessageBox(wxString(access_token));
            break;
        }
        
        case API_ID::POST_keycloak_UpdateToken:
        {
            std::string access_token = (std::string)json["access_token"];
            nomad->access_token = access_token;
//            wxMessageBox(wxString(access_token));
            nomad->getUploads();
            break;
        }
        
        case API_ID::POST_entries_query:
        {
            setPage(1);
            entryList->DeleteAllItems();
            
            std::string owner = (std::string)json["owner"];
            
            configuru::Config conf_pagination = json["pagination"];
            
            int total = (int)conf_pagination["total"];
            int page_size = (int)conf_pagination["page_size"];
            int this_page = (int)conf_pagination["page"];
            std::string order_by = (std::string)conf_pagination["order_by"];
            std::string order = (std::string)conf_pagination["order"];
            ctl_pagination_info->SetLabel(wxString::Format(wxT("%d-%d of %d"), (this_page - 1) * page_size + 1, (this_page - 1) * page_size + page_size, total));
            ctl_pagination_info->GetParent()->Layout();
            configuru::Config data = json["data"];
            
            if (data.is_array()) {
                int iEntry = -1;
                int entry_number = 0;
                for (const configuru::Config& entry : data.as_array()) {
                    iEntry++;
                    entry_number = (this_page - 1) * page_size + iEntry + 1;
                    std::string entry_id = (std::string)entry["entry_id"];
                    
                    std::string nomad_version = (std::string)entry["nomad_version"];
                    std::string last_processing_time = (std::string)entry["last_processing_time"];
                    std::string upload_create_time = (std::string)entry["upload_create_time"];
                    std::string upload_id = (std::string)entry["upload_id"];
                    std::string mainfile = (std::string)entry["mainfile"];
                    std::string entry_create_time = (std::string)entry["entry_create_time"];
//                    std::string published = (std::string)entry["published"];   //Sometimes does not exist
                    
                    configuru::Config main_author = entry["main_author"];
                    std::string main_author_name = (std::string)main_author["name"];
                    
                    configuru::Config results = entry["results"];
                    configuru::Config material = results["material"];
                    
                    std::string chemical_formula_reduced = (std::string)material["chemical_formula_reduced"];
                    std::string chemical_formula_descriptive = (std::string)material["chemical_formula_descriptive"];
                    std::string chemical_formula_anonymous = (std::string)material["chemical_formula_anonymous"];
                    std::string chemical_formula_hill = (std::string)material["chemical_formula_hill"];
                    std::string structural_type = (std::string)material["structural_type"];
                    
                    configuru::Config method = results["method"];
                    std::string method_name = (std::string)method["method_name"];
                    configuru::Config simulation = method["simulation"];
                    std::string program_name = (std::string)simulation["program_name"];
                    
                    long index = entryList->InsertItem(iEntry, wxString::Format(wxT("%d"), entry_number));
                    wxString *itemInfo = new wxString(entry_id);
                    entryList->SetItemPtrData(index, wxUIntPtr(itemInfo));
                    entryList->SetItem(index, 1, wxString(chemical_formula_reduced));
                    if (wxString(structural_type) != wxT("unavailable"))
                        entryList->SetItem(index, 2, wxString(structural_type));
                    else
                        entryList->SetItem(index, 2, wxString(""));
                    entryList->SetItem(index, 3, wxString(program_name));
                    
                    wxString method_info = method_name;
                    if (method_name == wxString("DFT")) {
                        configuru::Config dft = simulation["dft"];
                        std::string xc_functional_type = (std::string)dft["xc_functional_type"];
                        if (wxString(xc_functional_type) != wxT("unavailable"))
                            method_info = method_info + wxT(" (") + wxString(xc_functional_type) + wxT(")");
                    }
                    
                    entryList->SetItem(index, 4, wxString(method_info));
                    entryList->SetItem(index, 5, wxString(main_author_name));
                }
                
                if (iEntry == -1) {
                    ctlLeftPage->Enable(false);
                    ctlRightPage->Enable(false);
                    ctlSortBy->Enable(false);
                } else {
                    ctlSortBy->Enable(true);
                    if (entry_number < total) {
                        ctlRightPage->Enable(true);
                    } else {
                        ctlRightPage->Enable(false);
                    }
                    if (this_page == 1) {
                        ctlLeftPage->Enable(false);
                    } else {
                        ctlLeftPage->Enable(true);
                    }
                }
                
            }

        //    entryList->Layout();
            leftPanel->Layout();
            break;
        }
        
        case API_ID::GET_entries_entry:
        {
            if (json.has_key("data")) {
                configuru::Config data = json["data"];
                
                int maxneig, mspin, nKPoint, nAtoms;
                double ChemP;
                bool isBandLoaded;
                Adouble1D lattice_vectors;
                Adouble1D cartesian_site_positions;
                Aint0D dimension_types;
                Astring0D species_at_sites;
                Astring0D nomad_kLabel;
                Adouble1D fractional_KPoints;
                Adouble1D EigVal_spin0;
                Adouble1D EigVal_spin1;

                Astring0D kLabel;
                Aint0D n_perpath;
                
                wxString chemical_formula_reduced, chemical_formula_anonymous, program_name, method_name, entry_id, upload_id, parser_name;
                ImportFromNomad(data, isBandLoaded, nAtoms, maxneig, mspin, ChemP, nKPoint, lattice_vectors, cartesian_site_positions, dimension_types, species_at_sites, nomad_kLabel, fractional_KPoints, EigVal_spin0, EigVal_spin1, n_perpath, chemical_formula_reduced, chemical_formula_anonymous, program_name, method_name, entry_id, upload_id, parser_name, structural_type);
                
                if (isBandLoaded)
                {
                    a[0] = lattice_vectors[0][0];
                    a[1] = lattice_vectors[0][1];
                    a[2] = lattice_vectors[0][2];
                    b[0] = lattice_vectors[1][0];
                    b[1] = lattice_vectors[1][1];
                    b[2] = lattice_vectors[1][2];
                    c[0] = lattice_vectors[2][0];
                    c[1] = lattice_vectors[2][1];
                    c[2] = lattice_vectors[2][2];
                    
                    double ak[3],bk[3],ck[3];
                    remote_sec30->VecToReciprocal(a, b, c, ak, bk, ck);
                    
                    Adouble0D akv(ak, ak + 3);
                    Adouble0D bkv(bk, bk + 3);
                    Adouble0D ckv(ck, ck + 3);
                    remote_sec30->ArraysOf1DDouble[1] = akv;
                    remote_sec30->ArraysOf1DDouble[2] = bkv;
                    remote_sec30->ArraysOf1DDouble[3] = ckv;

                    entryInfo->DestroyChildren();
                    wxFlexGridSizer* entryInfoGridSizer = (wxFlexGridSizer*)entryInfo->GetSizer();
                    entryInfoGridSizer->Clear(false);
                    EntryID->SetValue(entry_id);
                    addInfo("Entry ID", entry_id);
                    addSpacer();
                    addSpacer();
                    
                    addInfo("Upload ID", upload_id);
                    addSpacer();
                    addSpacer();
                    
                    addInfo("Chemical Formula", chemical_formula_reduced);
                    addInfo("Anonymous Formula", chemical_formula_anonymous);
                    addInfo("Parser Name", parser_name);
                    
                    addInfo("a", wxString::Format(wxT("(%.3f, %.3f, %.3f)"), a[0], a[1], a[2]), wxString::Format(wxT("%.8f %.8f %.8f"), a[0], a[1], a[2]));
                    addInfo("b", wxString::Format(wxT("(%.3f, %.3f, %.3f)"), b[0], b[1], b[2]), wxString::Format(wxT("%.8f %.8f %.8f"), b[0], b[1], b[2]));
                    addInfo("c", wxString::Format(wxT("(%.3f, %.3f, %.3f)"), c[0], c[1], c[2]), wxString::Format(wxT("%.8f %.8f %.8f"), c[0], c[1], c[2]));
                    entryInfo->Layout();
                    
//                    addInfo("Program Name", program_name);
//                    addInfo("Method Name", method_name);
                    //addInfo("Entry ID", entry_id);
                    //addInfo("Upload ID", upload_id);
                    
                    int atomIndex = -1;
                    fractional_site_positions.clear();
                    species_indices.clear();
                    for(Adouble1D::iterator it = std::begin(cartesian_site_positions); it != std::end(cartesian_site_positions); ++it) {
                        atomIndex++;
                        double absol[3] = {(*it).at(0), (*it).at(1), (*it).at(2)};
                        double frac[3];
                        remote_sec30->AbsToFrac(a, b, c, absol, frac);
                        Adouble0D A1d;
                        A1d.push_back(frac[0]);
                        A1d.push_back(frac[1]);
                        A1d.push_back(frac[2]);
                        fractional_site_positions.push_back(A1d);
                        int atomKind = sec30->GetAtomLable(wxString(species_at_sites.at(atomIndex)));
                        species_indices.push_back(atomKind);
                    }

                    Adouble1D KPoints;
                    
                    double oldvec[3];
                    int PathCounter = 0;
                    int ThisPathInd = 0;
                    double d = 0.0;
                    int i = -1;
                    
//                    wxString kname1 = wxString(c1, wxConvUTF8);
                    bool isKLabel = nomad_kLabel.size() > 0;
                    wxString kname1;
                    Adouble0D dkLabel;
                    Astring0D kLabel;
                    dkLabel.push_back(d);
                    if (isKLabel)
                        kname1 = nomad_kLabel.at(ThisPathInd);
                    else
                        kname1 = wxString("");
                    if (kname1 == "Γ" || kname1 == "G" || kname1 == "g" || kname1.Contains(_("\G")) || kname1.Contains(_("\g")) || kname1.Contains(_("gamma")) || kname1.Contains(_("Gamma"))) kname1 = _("\\Gamma");
                    if (kname1 == wxT("")) kname1 = _("?");
                    kLabel.push_back(kname1);
                    for(Adouble1D::iterator it = std::begin(fractional_KPoints); it != std::end(fractional_KPoints); ++it) {
                        i++;
                        Adouble0D A1d;
                        double frac[3] = {(*it).at(0), (*it).at(1), (*it).at(2)};
                        double vec[3];
                        
                        remote_sec30->FracToAbs(ak, bk, ck, frac, vec);
                        if (i==0)
                        {
                            oldvec[0]=vec[0];
                            oldvec[1]=vec[1];
                            oldvec[2]=vec[2];
                        }
                        double deltakPath = remote_sec30->norm(vec, oldvec);
                        if (PathCounter == n_perpath[ThisPathInd] || i == fractional_KPoints.size() - 1)
                        {
                            dkLabel.push_back(d);
                            if (isKLabel)
                                kname1 = nomad_kLabel.at(ThisPathInd + 1);
                            else
                                kname1 = wxString("");
                            if (kname1 == "Γ" || kname1 == "G" || kname1 == "g" || kname1.Contains(_("\G")) || kname1.Contains(_("\g")) || kname1.Contains(_("gamma")) || kname1.Contains(_("Gamma"))) kname1 = _("\\Gamma");
                            if (kname1 == wxT("")) kname1 = _("?");
                            kLabel.push_back(kname1);
                            deltakPath = 0.000001;
                            PathCounter = 0;
                            ThisPathInd++;
                        }
                        PathCounter++;
                        d += deltakPath;
                        oldvec[0]=vec[0];
                        oldvec[1]=vec[1];
                        oldvec[2]=vec[2];
                        
                        A1d.clear();
                        for(int j=0; j<3; j++)
                        {
                            double val = frac[j];
                            A1d.push_back(val);
                        }
                        
                        for(int j=0; j<3; j++)
                        {
                            double val = vec[j];
                            A1d.push_back(val);
                        }
                        
                        A1d.push_back(d);
                        
                        KPoints.push_back(A1d);
                    }
                    
                    
                    Adouble1D EigVal;
                    for(Adouble1D::iterator it = std::begin(EigVal_spin0); it != std::end(EigVal_spin0); ++it) EigVal.push_back(*it);
                    for(Adouble1D::iterator it = std::begin(EigVal_spin1); it != std::end(EigVal_spin1); ++it) EigVal.push_back(*it);
                    int nk0 = EigVal.size();
                    int nband0 = EigVal[0].size();
                    Adouble1D EigValWeights(nk0,std::vector<double>(nband0,1.0));
                    
                    remote_sec30->ArraysOf0DInt[0] = 1;
                    remote_sec30->ArraysOf0DInt[1] = nKPoint;
                    remote_sec30->ArraysOf0DInt[2] = maxneig;
                    remote_sec30->ArraysOf0DInt[3] = mspin;
                    remote_sec30->ArraysOf0DInt[6] = 0;
                    remote_sec30->ArraysOf0DDouble[0] = ChemP;
                    remote_sec30->ArraysOf1DDouble[0] = dkLabel;
                    remote_sec30->ArraysOf1DString[0] = kLabel;
                    remote_sec30->ArraysOf2DDouble[0] = KPoints;
                    remote_sec30->ArraysOf2DDouble[1] = EigVal;
                    remote_sec30->ArraysOf2DDouble[4] = EigValWeights;
                    
                    remote_sec30->ArraysOf0DInt[4] = 1;//int DFTnBandMin;
                    remote_sec30->ArraysOf0DInt[5] = maxneig;//int DFTnBandMax;
                    
                    remote_sec30->ArraysOf0DDouble[1] = -10;
                    remote_sec30->ArraysOf0DDouble[2] = 10;
                    remote_sec30->ArraysOf0DDouble[3] = -10;
                    remote_sec30->ArraysOf0DDouble[4] = 10;
                    
                    int nkPoints = remote_sec30->ArraysOf1DDouble[0].size();
                    remote_sec30->ArraysOf0DDouble[5] = 0.0;
                    remote_sec30->ArraysOf0DDouble[6] = remote_sec30->ArraysOf1DDouble[0][nkPoints-1];
                    remote_sec30->ArraysOf0DDouble[7] = 0.0;
                    remote_sec30->ArraysOf0DDouble[8] = remote_sec30->ArraysOf1DDouble[0][nkPoints-1];
                }
                else
                {
                    remote_sec30->ArraysOf0DInt[0] = 0;
                    remote_sec30->ArraysOf0DInt[1] = 0;
                    remote_sec30->ArraysOf0DInt[2] = 0;
                    remote_sec30->ArraysOf0DInt[3] = 0;
                    remote_sec30->ArraysOf0DInt[6] = 0;
                    remote_sec30->ArraysOf0DDouble[0] = 0.0;
                    remote_sec30->ArraysOf1DDouble[0] = Adouble0D();
                    remote_sec30->ArraysOf1DString[0] = Astring0D();
                    remote_sec30->ArraysOf2DDouble[0] = Adouble1D();
                    remote_sec30->ArraysOf2DDouble[1] = Adouble1D();
                    remote_sec30->ArraysOf2DDouble[4] = Adouble1D();
                    remote_sec30->ArraysOf0DDouble[1] = 0.0;
                    remote_sec30->ArraysOf0DDouble[2] = 0.0;
                    remote_sec30->ArraysOf0DDouble[3] = 0.0;
                    remote_sec30->ArraysOf0DDouble[4] = 0.0;
                    remote_sec30->ArraysOf0DDouble[5] = 0.0;
                    remote_sec30->ArraysOf0DDouble[6] = 0.0;
                    remote_sec30->ArraysOf0DDouble[7] = 0.0;
                    remote_sec30->ArraysOf0DDouble[8] = 0.0;
                }
            }

            graph2d->myRefresh2d();
            setLoadingEntryState(false);
            break;
        }
        
        case API_ID::GET_uploads:
        {
            myProjectsTitle->SetLabel(wxT("My projects"));
            
            configuru::Config data = json["data"];
            
            wxBoxSizer* panelUploadsListSizer = (wxBoxSizer*)panelUploadsList->GetSizer();
            
            panelUploadsListSizer->Clear();
            if (data.is_array()) {
                int iUpload = 0;
                for (const configuru::Config& upload : data.as_array()) {
                    std::string upload_id = (std::string)upload["upload_id"];
                    wxString uploadName;
                    wxString uploadOriginalName;
                    if (upload.has_key("upload_name")) {
                        uploadOriginalName = (std::string)upload["upload_name"];
                    } else {
                        uploadOriginalName = wxT("unnamed");
                    }
                    
                    int nChar = uploadOriginalName.length();
                    int maxLength = 15;
                    if (nChar > maxLength) {
                        uploadName = uploadOriginalName.erase(maxLength, nChar - maxLength);
                    } else {
                        wxString whiteSpace = wxT("");
                        for (int i = 0; i<maxLength - nChar; i++) whiteSpace = whiteSpace + wxT(" ");
                        uploadName = uploadOriginalName + whiteSpace;
                    }
                    wxString publishedStatus = wxT("");
                    bool isPublished = (bool)upload["published"];
                    if (isPublished)
                        publishedStatus = wxT("published  ");
                    else
                        publishedStatus = wxT("unpublished");
//                    wxMessageBox(upload_id);
                    addUploadRow(upload_id, wxString::Format(wxT("Project name: %s     Status: %s"), uploadName, publishedStatus));
                    iUpload++;
                }
            }
            
            panelUploadsList->Layout();
            panelUploadsList->GetParent()->Layout();
            break;
        }
    }
}

configuru::Config resolveRef(configuru::Config object, wxString path)
{
    configuru::Config current = object;
    wxStringTokenizer tokenizer(path, "/");
    while ( tokenizer.HasMoreTokens() )
    {
        wxString tk = tokenizer.GetNextToken();
        if (tk.IsEmpty()) continue;
        
        long l = -1;
        bool output = tk.ToLong(&l);
        if (!output) {
            current = current[tk.ToStdString()];
        } else {
            long i = -1;
            for (const configuru::Config& element : current.as_array()) {
                i++;
                if (i == l) {
                    current = element;
                    break;
                }
            }
        }
    }
    
    return current;
}

void ImportFromNomad(configuru::Config data, bool &isBandLoaded, int &nAtoms, int &maxneig, int &mspin, double &ChemP, int &nKp, Adouble1D &lattice_vectors, Adouble1D &cartesian_site_positions, Aint0D &dimension_types, Astring0D &species_at_sites, Astring0D &kLabel, Adouble1D &fractional_KPoints, Adouble1D &energies_spin0, Adouble1D &energies_spin1, Aint0D &n_perpath, wxString &chemical_formula_reduced, wxString &chemical_formula_anonymous, wxString &program_name, wxString &method_name, wxString &entry_id, wxString &upload_id, wxString &parser_name, wxString &structural_type)
{
//    double Hartree2eV = 27.2113961318;
    double Joule2eV = 6.241509e18;
//    double BohrToAng = 1.88973;
    double MeterToAng = 1.0e10;
    isBandLoaded = false;
    
    entry_id = (std::string)data["entry_id"];
    upload_id = (std::string)data["upload_id"];
    parser_name = (std::string)data["parser_name"];
    
    configuru::Config archive = data["archive"];
    configuru::Config results = archive["results"];
    configuru::Config properties = results["properties"];
    configuru::Config band_structure_electronic = properties["electronic"]["band_structure_electronic"];
    //    wxMessageBox(wxString(configuru::dump_string(band_structure_electronic, configuru::JSON)));
    configuru::Config structure_original = properties["structures"]["structure_original"];
//    wxMessageBox(wxString(configuru::dump_string(structure_original, configuru::JSON)));
    
    configuru::Config conf_lattice_vectors = structure_original["lattice_vectors"];
    configuru::Config conf_cartesian_site_positions = structure_original["cartesian_site_positions"];
    configuru::Config conf_dimension_types = structure_original["dimension_types"]; // To set the dimention in tab two
    configuru::Config conf_species_at_sites = structure_original["species_at_sites"]; // String: the name of species. Should be convered to atomic number
    
    configuru::Config material = results["material"];
    std::string chemical_formula_descriptive = (std::string)material["chemical_formula_descriptive"];
    chemical_formula_reduced = (std::string)material["chemical_formula_reduced"];
    chemical_formula_anonymous = (std::string)material["chemical_formula_anonymous"];
    structural_type = (std::string)material["structural_type"];
    
//    configuru::Config method = results["method"];
//    method_name = (std::string)method["method_name"];
//    configuru::Config simulation = method["simulation"];
//    program_name = (std::string)material["program_name"];
                    
    if (conf_lattice_vectors.is_array()) {
        for (const configuru::Config& vec : conf_lattice_vectors.as_array()) {
            Adouble0D A1d;
            for (const configuru::Config& v : vec.as_array()) A1d.push_back(MeterToAng * (double)v);
            lattice_vectors.push_back(A1d);
        }
    }
    
    int _nAtoms = 0;
    if (conf_cartesian_site_positions.is_array()) {
        for (const configuru::Config& vec : conf_cartesian_site_positions.as_array()) {
            Adouble0D A1d;
            for (const configuru::Config& v : vec.as_array()) A1d.push_back(MeterToAng * (double)v);
            cartesian_site_positions.push_back(A1d);
            _nAtoms++;
        }
    }
    
    nAtoms = _nAtoms;
    
    if (conf_dimension_types.is_array()) {
        for (const configuru::Config& dimension_type : conf_dimension_types.as_array()) {
            dimension_types.push_back((int)dimension_type);
        }
    }
    
    if (conf_species_at_sites.is_array()) {
        for (const configuru::Config& spc : conf_species_at_sites.as_array()) {
            species_at_sites.push_back(wxString((std::string)spc));
        }
    }
    
    n_perpath.clear();
    fractional_KPoints.clear();
    energies_spin0.clear();
    energies_spin1.clear();
    
    bool isSpin = false;
    if (band_structure_electronic.has_key("spin_polarized")) {
        configuru::Config spin_polarized = band_structure_electronic["spin_polarized"];
        isSpin = (bool)spin_polarized;    
    }    
    mspin = 0;
    if (isSpin) mspin = 1;
    
    if (band_structure_electronic.has_key("energy_fermi")) {
        configuru::Config energy_fermi = band_structure_electronic["energy_fermi"];
        ChemP = Joule2eV * (double)energy_fermi;   
    } else {
        ChemP = 0.0;
    }

    int _maxneig = 0;
    int _nKp = 0;
    maxneig = 0;
    nKp = 0;
    Astring0D all_start_labels;
    Astring0D all_end_labels;
    configuru::Config segments = band_structure_electronic["segment"];
    if (segments.is_array()) {
        for (const configuru::Config& segment : segments.as_array()) {
            configuru::Config segmentData = resolveRef(archive, wxString((std::string)segment));
            configuru::Config kpoints = segmentData["kpoints"];
//            configuru::Config occupations = segmentData["occupations"];
            configuru::Config energies = segmentData["energies"];
//            wxMessageBox(wxString(configuru::dump_string(segmentData, configuru::JSON)));
            
            if (segmentData.has_key("endpoints_labels")) {
                configuru::Config endpoints_labels = segmentData["endpoints_labels"];
                if (endpoints_labels.is_array()) {
                    int endpoints_label_index = 0;
                    for (const configuru::Config& endpoints_label : endpoints_labels.as_array()) {
                        wxString _label = wxString((std::string)endpoints_label);
                        if (endpoints_label_index == 0) {
                            all_start_labels.push_back(_label);
                        } else if (endpoints_label_index == 1) {
                            all_end_labels.push_back(_label);
                        }
                        endpoints_label_index++;
                    }
                }   
            }
            
            int _nPath = 0;
            for (const configuru::Config& kpoint : kpoints.as_array()) {
                Adouble0D A1d;
                for (const configuru::Config& k : kpoint.as_array()) A1d.push_back((double)k);
                fractional_KPoints.push_back(A1d);
                _nPath++;
                _nKp++;
            }
            
            n_perpath.push_back(_nPath);
            
            configuru::Config conf_energies_spin0;
            configuru::Config conf_energies_spin1;
            int spinpack = 0;
            for (const configuru::Config& energies_spinpack : energies.as_array()) {
                if (spinpack == 0)
                    conf_energies_spin0 = energies_spinpack;
                if (spinpack == 1)
                    conf_energies_spin1 = energies_spinpack;
                spinpack++;
            }
            
            _maxneig = 0;
            for (const configuru::Config& conf_enrgs : conf_energies_spin0.as_array()) {
                Adouble0D A1d;
                for (const configuru::Config& e : conf_enrgs.as_array()) A1d.push_back(Joule2eV * (double)e);
                energies_spin0.push_back(A1d);
                _maxneig = A1d.size();
            }
            
            if (mspin > 0) {
                for (const configuru::Config& conf_enrgs : conf_energies_spin1.as_array()) {
                    Adouble0D A1d;
                    for (const configuru::Config& e : conf_enrgs.as_array()) A1d.push_back(Joule2eV * (double)e);
                    energies_spin1.push_back(A1d);
                }
            }
        }
    } else {
        return;
    }
    
    maxneig = _maxneig;
    nKp = _nKp;
    
    int l_index = 0;
    int nkLabels = all_end_labels.size();
    if (nkLabels > 0) {
        kLabel.push_back(all_start_labels.at(l_index));
        for(Astring0D::iterator it = std::begin(all_end_labels); it != std::end(all_end_labels); ++it) {
            wxString label = (*it);
            if (l_index < nkLabels - 1) {
                wxString nextlabel = all_start_labels.at(l_index + 1);
                if (label == nextlabel) {
                    kLabel.push_back(label);
                } else {
                    kLabel.push_back(wxString::Format(wxT("%s|%s"), label, nextlabel));
                }
            } else {
                kLabel.push_back(label);
            }
            l_index++;
        }
    }
    isBandLoaded = true;
}

void NomadGUI::addInfo(wxString label, wxString value, wxString clipboardValue)
{
    wxFlexGridSizer* entryInfoGridSizer = (wxFlexGridSizer*)entryInfo->GetSizer();
    
    wxStaticText* infoText = new wxStaticText(entryInfo, wxID_ANY, wxString::Format(wxT("%s: %s"), label, value), wxDefaultPosition, wxDLG_UNIT(entryInfo, wxSize(-1,-1)), 0);
    entryInfoGridSizer->Add(infoText, 0, wxALL, WXC_FROM_DIP(5));
    
    wxBitmapButton* copyToClipboardButton = new wxBitmapButton(entryInfo, wxID_ANY, GetPng(clipboard_png,clipboard_png_size), wxDefaultPosition, wxDLG_UNIT(entryInfo, wxSize(-1,-1)), wxBU_AUTODRAW);
    if (clipboardValue == wxT("")) {
        copyToClipboardButton->SetToolTip(value);
    } else {
        copyToClipboardButton->SetToolTip(clipboardValue);
    }
    entryInfoGridSizer->Add(copyToClipboardButton, 0, 0, WXC_FROM_DIP(5));
    copyToClipboardButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CopyTextToClipboard), NULL, this);
    
    
    entryInfoGridSizer->AddSpacer(70);
}

void NomadGUI::addSpacer()
{
    wxFlexGridSizer* entryInfoGridSizer = (wxFlexGridSizer*)entryInfo->GetSizer();
    entryInfoGridSizer->AddSpacer(0);
    entryInfoGridSizer->AddSpacer(0);
    entryInfoGridSizer->AddSpacer(0);
}

void NomadGUI::CopyTextToClipboard(wxCommandEvent& event) {
    wxBitmapButton* element = (wxBitmapButton*)event.GetEventObject();
    wxString dataToClipBoard = element->GetToolTip()->GetTip();
	if(wxTheClipboard->Open())
	{
		wxTheClipboard->Clear();
		wxTheClipboard->SetData(new wxTextDataObject(dataToClipBoard));
		wxTheClipboard->Flush();
		wxTheClipboard->Close();      
	}
}

void NomadGUI::nomadEVT_On_State_Failed(wxCommandEvent& event)
{
    API_ID ID = (API_ID)event.GetInt();
    wxString error = event.GetString();
    switch (ID)
    {
        case API_ID::POST_keycloak_RefreshToken:
        {
//            wxMessageBox(wxT("keycloak_RefreshToken Failed"));
            break;
        }
        
        case API_ID::POST_entries_query:
        {
            setPage(0);
            wxMessageBox(wxT("An error occurred when fetching data."));
            break;
        }
        
        case API_ID::GET_entries_entry:
        {
            entryInfo->DestroyChildren();
            wxFlexGridSizer* entryInfoGridSizer = (wxFlexGridSizer*)entryInfo->GetSizer();
            entryInfoGridSizer->Clear(false);
            wxStaticText* infoText = new wxStaticText(entryInfo, wxID_ANY, wxT("Could not load the given entry ID ..."), wxDefaultPosition, wxDLG_UNIT(entryInfo, wxSize(-1,-1)), 0);
            entryInfoGridSizer->Add(infoText, 0, wxALL, WXC_FROM_DIP(5));
            entryInfo->Layout();
            graph2d->myRefresh2d();
            setLoadingEntryState(false);
            break;
        }
        
        case API_ID::GET_uploads:
        {
            myProjectsTitle->SetLabel(wxT("Unable to load your projects!"));
            break;
        }
    }
}

void NomadGUI::nomadEVT_On_State_Idle(wxCommandEvent& event)
{
    
}

void NomadGUI::nomadEVT_On_State_Cancelled(wxCommandEvent& event)
{
    API_ID ID = (API_ID)event.GetInt();
    wxString error = event.GetString();
    switch (ID)
    {
        case API_ID::POST_entries_query:
        {
            setPage(0);
            wxMessageBox(wxT("Fetching data was canceled."));
            break;
        }
        
        case API_ID::GET_entries_entry:
        {
            entryInfo->DestroyChildren();
            wxFlexGridSizer* entryInfoGridSizer = (wxFlexGridSizer*)entryInfo->GetSizer();
            entryInfoGridSizer->Clear(false);
            wxStaticText* infoText = new wxStaticText(entryInfo, wxID_ANY, wxT("Loading the entry ID was canceled..."), wxDefaultPosition, wxDLG_UNIT(entryInfo, wxSize(-1,-1)), 0);
            entryInfoGridSizer->Add(infoText, 0, wxALL, WXC_FROM_DIP(5));
            entryInfo->Layout();

            graph2d->myRefresh2d();
            setLoadingEntryState(false);
            break;
        }
    }
}

void NomadGUI::nomadEVT_On_State_Unauthorized(wxCommandEvent& event)
{
    API_ID ID = (API_ID)event.GetInt();
    wxString error = event.GetString();
    switch (ID)
    {
        case API_ID::GET_uploads:
        {
            myProjectsTitle->SetLabel(wxT("Authentication failed when loading your projects!"));
            break;
        }
    }
}

void NomadGUI::onElementToggle(wxCommandEvent& event)
{
    //    event.Skip();
    wxToggleButton* element = (wxToggleButton*)event.GetEventObject();
    bool isChecked = element->GetValue();
    if (isChecked)
        add(elements, element->GetLabel());
    else
        remove(elements, element->GetLabel());
}

void NomadGUI::openUpload_onClick(wxCommandEvent& event)
{
    //    event.Skip();
    wxButton* openButton = (wxButton*)event.GetEventObject();
    wxString uploadID = openButton->GetToolTip()->GetTip();
    wxMessageBox(uploadID);
}

int NomadGUI::getIndex(std::vector<wxString>& List, wxString item)
{
    if(!List.empty()){
        auto it = std::find(List.begin(), List.end(), item);
        if(it != List.end()) {
            int index = it - List.begin();
            return index;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

void NomadGUI::add(std::vector<wxString>& List, wxString item)
{
    List.push_back(item);
}

void NomadGUI::remove(std::vector<wxString>& List, wxString item)
{
    int index = getIndex(List, item);
    if (index < 0) return;
    List.erase(List.begin() + index);
}

bool NomadGUI::includes(std::vector<wxString>& List, wxString item)
{
    int index = getIndex(List, item);
    if (index < 0)
        return false;
    else
        return true;
}

void NomadGUI::bulk_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    bool isChecked = checkBox->GetValue();
    if (isChecked)
        add(types, wxString("bulk"));
    else
        remove(types, wxString("bulk"));
}

void NomadGUI::dim_1d_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    bool isChecked = checkBox->GetValue();
    if (isChecked)
        add(types, wxString("1D"));
    else
        remove(types, wxString("1D"));
}

void NomadGUI::dim_2d_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    bool isChecked = checkBox->GetValue();
    if (isChecked)
        add(types, wxString("2D"));
    else
        remove(types, wxString("2D"));
}

void NomadGUI::direct_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    bool isChecked = checkBox->GetValue();
    if (isChecked)
        add(gapTypes, wxString("direct"));
    else
        remove(gapTypes, wxString("direct"));
}

void NomadGUI::exclusively_composition_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    exclusive_composition = checkBox->GetValue();
}

void NomadGUI::indirect_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    bool isChecked = checkBox->GetValue();
    if (isChecked)
        add(gapTypes, wxString("indirect"));
    else
        remove(gapTypes, wxString("indirect"));
}

void NomadGUI::not_spin_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    bool isChecked = checkBox->GetValue();
    if (isChecked)
        add(spins, wxString("false"));
    else
        remove(spins, wxString("false"));
}

void NomadGUI::spin_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    bool isChecked = checkBox->GetValue();
    if (isChecked)
        add(spins, wxString("true"));
    else
        remove(spins, wxString("true"));
}

void NomadGUI::surface_onChanged(wxCommandEvent& event)
{
    wxCheckBox* checkBox = (wxCheckBox*)event.GetEventObject();
    bool isChecked = checkBox->GetValue();
    if (isChecked)
        add(types, wxString("surface"));
    else
        remove(types, wxString("surface"));
}

wxBitmap NomadGUI::GetPng(const void* data, size_t length)
{
    wxMemoryInputStream memIStream(data, length);
    wxImage image(memIStream, wxBITMAP_TYPE_PNG );
    wxBitmap bmp( image );
    return bmp;
}

void NomadGUI::testlistctrl_On_Item_Activated(wxListEvent& event)
{
    
}

void NomadGUI::testlistctrl_On_Item_RightClick(wxListEvent& event)
{
    
}

void NomadGUI::testlistctrl_On_Item_Selected(wxListEvent& event)
{
    if (loadingEntry) return;
    wxString* itemInfo = reinterpret_cast<wxString*>(event.GetItem().GetData());
    wxString entry_id = *itemInfo;
//    wxMessageBox(entry_id);
//    entryWebView->LoadURL(wxString::Format(wxT("https://nomad-lab.eu/prod/v1/staging/gui/search/entries/entry/id/%s"), entry_id));
//    setLoadingEntryState(true);
    nomad->getEntry(entry_id);
}

void NomadGUI::setLoadingEntryState(bool state)
{
    loadingEntry = state;
    EntryID->Enable(!state);
}

void NomadGUI::EntryID_OnEnter(wxCommandEvent& event)
{
    wxString entry_id = EntryID->GetValue().ToStdString();
    setLoadingEntryState(true);
    nomad->getEntry(entry_id);
}

void NomadGUI::LoadEntry_In_TBStudio_OnClick(wxCommandEvent& event)
{
    if (loadingEntry) return;
    CopyToTBStudio();
}

void NomadGUI::UserNamePrefix_OnUpdated(wxCommandEvent& event)
{
    AuthorPrefix = UserNamePrefix->GetValue();
}

void NomadGUI::btnExplore_OnClick(wxCommandEvent& event)
{
    setPage(0);
}

void NomadGUI::btnMyProjects_OnClick(wxCommandEvent& event)
{
    setPage(2);
}
