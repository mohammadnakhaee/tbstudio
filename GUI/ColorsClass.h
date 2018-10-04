#ifndef COLORSCLASS_H
#define COLORSCLASS_H
/**************************************************************************************/
#include "wxcrafter.h"
#include <Sec30.h>
/**************************************************************************************/
class ColorsClass : public ColorsBaseClass
{
public:
    Sec30* sec30;
    ColorsClass(wxWindow* parent, Sec30* sec30var);
    virtual ~ColorsClass();
protected:
    virtual void OnClose(wxCloseEvent& event);
};
#endif // COLORSCLASS_H
