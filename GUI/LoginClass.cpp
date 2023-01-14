#include "LoginClass.h"

LoginClass::LoginClass(wxWindow* parent)
    : LoginBaseClass(parent)
{
    wxTextCtrl* ctlUserName = new wxTextCtrl(parent, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(UserNamePanel, wxSize(150,-1)), 0);
//    delete ctlUserName;
    
//    #if wxVERSION_NUMBER >= 3000
//    ctlUserName->SetHint(wxT(""));
//    #endif
//
//    wxBoxSizer* UserNamePanelSizer = (wxBoxSizer*)UserNamePanel->GetSizer();
//    UserNamePanelSizer->Add(ctlUserName, 0, wxALL|wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));
//    ctlUserName->SetMinSize(wxSize(150,-1));
    
    
//    ctlPassword = new wxTextCtrl(PasswordPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(PasswordPanel, wxSize(150,-1)), wxTE_PASSWORD);
//    #if wxVERSION_NUMBER >= 3000
//    ctlPassword->SetHint(wxT(""));
//    #endif
//
//    wxBoxSizer* PasswordPanelSizer = (wxBoxSizer*)PasswordPanel->GetSizer();    
//    PasswordPanelSizer->Add(ctlPassword, 0, wxALL|wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));
//    ctlPassword->SetMinSize(wxSize(150,-1));
}

LoginClass::~LoginClass()
{
//    if (ctlUserName != NULL) delete ctlUserName;
//    if (ctlPassword != NULL) delete ctlPassword;
//    ctlUserName = NULL;
//    ctlPassword = NULL;
}

