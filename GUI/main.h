#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include <wx/image.h>
#include <MyOpenGL.h>

// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp() {m_glContext = NULL; m_glStereoContext = NULL;}
    virtual ~MainApp() {}

    // shared context between all frames; set it as current for the given canvas.
    MyGLContext& GetContext(wxGLCanvas *canvas, int Dim, bool useStereo);

    // virtual wxApp methods
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;
    
private:
    // the GL context we use for all our mono rendering windows
    MyGLContext *m_glContext;
    // the GL context we use for all our stereo rendering windows
    MyGLContext *m_glStereoContext;
};


DECLARE_APP(MainApp)