#ifndef CHOOSECLASS_H
#define CHOOSECLASS_H
#include "wxcrafter.h"
#include "Sec30.h"

class ChooseClass : public ChooseClassBase
{
public:
    ChooseClass(wxWindow* parent, int ndatasets, wxString filetype);
    virtual ~ChooseClass();
protected:
    virtual void Cancel_OnClick(wxCommandEvent& event);
    virtual void OK_OnCLick(wxCommandEvent& event);
};
#endif // CHOOSECLASS_H
