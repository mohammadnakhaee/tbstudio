#ifndef BONDSCLASS_H
#define BONDSCLASS_H
/**************************************************************************************/
#include "wxcrafter.h"
#include <sstream>
#include "GraphClass.h"
#include <wx/filedlg.h>
#include <MyMatrix.h>
#include <string.h>
#include <exception>
#include <wx/msgdlg.h>
#include <Sec30.h>
/**************************************************************************************/
class BondsClass : public wxPanel
{
public:
    Sec30* sec30;
    GraphClass* graph3d;

    BondsClass(wxWindow* parent, Sec30* sec30var, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL|wxBORDER_STATIC);
    virtual ~BondsClass();

protected:
    wxTreeItemId ClickedID;
    void Btn_Set_OnClick(wxCommandEvent& event);
    void BondsTree_RightDown(wxMouseEvent& event);
    void OnDelete(wxCommandEvent &event);
    DECLARE_EVENT_TABLE()
};
#endif // BONDSCLASS_H
