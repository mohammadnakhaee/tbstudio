#ifndef UPDATECLASS_H
#define UPDATECLASS_H
#include "wxcrafter.h"
#include "unistd.h"
#include <wx/mstream.h>
#include "wx/log.h"
#include <wx/statbmp.h>
#include <wx/clipbrd.h> 
#include "Sec30.h"
#include <wx/textdlg.h>

class UpdateClass : public UpdateClassBase
{
public:
    std::vector<wxPoint> pattern;
    wxString MySN;
    wxBitmap GetPng(const void* data, size_t length);
    UpdateClass(wxWindow* parent, wxString SN);
    virtual ~UpdateClass();
    void GenerateActivationKey();
protected:
    virtual void ImageOnMouseLeftDown(wxMouseEvent& event);
    virtual void ImageOnMouseLeftUp(wxMouseEvent& event);
    virtual void ImageOnMouseMove(wxMoveEvent& event);
    virtual void CopyClipboardOnClick(wxCommandEvent& event);
    virtual void ActivateOnClick(wxCommandEvent& event);
};
#endif // UPDATECLASS_H
