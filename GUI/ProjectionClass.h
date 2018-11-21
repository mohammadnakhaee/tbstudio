#ifndef PROJECTIONCLASS_H
#define PROJECTIONCLASS_H
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
class ProjectionClass : public wxPanel
{
public:
    Sec30* sec30;
    GraphClass* graph3d;

    ProjectionClass(wxWindow* parent, Sec30* sec30var, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL|wxBORDER_STATIC);
    virtual ~ProjectionClass();

protected:
    
};
#endif // BONDSCLASS_H
