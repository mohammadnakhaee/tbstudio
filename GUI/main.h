#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include <wx/image.h>
#include <MyOpenGL.h>

#define __cpp_2011 201103L
/* Check support for override keywords */ 
#ifndef HAVE_OVERRIDE 
    #if __cplusplus >= __cpp_2011 
        /* All C ++ 11 compilers should have it */ 
        #define HAVE_OVERRIDE 
    #elif wxCHECK_VISUALC_VERSION (11) 
        /*
           VC ++ supports the override keyword in version 8 and later, but C ++ 11
           Since __cplusplus is not defined to indicate support (up to 12),
           In that case, please handle it specially.
 
           Also, keywords are supported, but when used with versions 8, 9, and 10 C4481
           Do not use because a compiler warning ("nonstandard extension used") will occur.
           If you don't mind, you can disable this warning and predefine HAVE_OVERRIDE.
         */ 
        #define HAVE_OVERRIDE 
    #elif WX_HAS_CLANG_FEATURE (cxx_override_control) 
        #define HAVE_OVERRIDE 
    #endif
 
    #ifdef HAVE_OVERRIDE 
        #define wxOVERRIDE override 
    #else /*! HAVE_OVERRIDE */ 
        #define wxOVERRIDE 
    #endif /* HAVE_OVERRIDE */ 
#endif /*! HAVE_OVERRIDE */

// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp() {m_glContext = NULL; m_glStereoContext = NULL;
	wxSetEnv( wxT( "GDK_BACKEND" ), wxT( "x11" ) );
	wxSetEnv( wxT( "GTK_OVERLAY_SCROLLING" ), wxT( "0" ) );}
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