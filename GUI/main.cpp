#include "main.h"
#include "GridClass.h"
#include <wx/sysopt.h>

bool MainApp::OnInit()
{
    //In MacOS and in the case of the languages their decimal separator is comma we should force TBStudio to use dot as decimal separtor
    //setlocale(LC_NUMERIC, "C");
    wxLocale* locale = new wxLocale();
    locale->Init(wxLANGUAGE_ENGLISH, wxLOCALE_LOAD_DEFAULT);
    
    // Add the common image handlers
    wxImage::AddHandler( new wxPNGHandler );
    wxImage::AddHandler( new wxJPEGHandler );
    
    wxSystemOptions::SetOption	("msw.notebook.themed-background", 0);
    
    MainFrame *mainFrame = new MainFrame(NULL);
    SetTopWindow(mainFrame);
    return GetTopWindow()->Show();
}
    
int MainApp::OnExit()
{
    delete m_glContext;
    delete m_glStereoContext;
    return wxApp::OnExit();
}


MyGLContext& MainApp::GetContext(wxGLCanvas *canvas, int Dim, bool useStereo)
{
    MyGLContext *glContext;
    if ( useStereo )
    {
        if ( !m_glStereoContext )
        {
            // Create the OpenGL context for the first stereo window which needs it:
            // subsequently created windows will all share the same context.
            m_glStereoContext = new MyGLContext(canvas, Dim);
        }
        glContext = m_glStereoContext;
    }
    else
    {
        if ( !m_glContext )
        {
            // Create the OpenGL context for the first mono window which needs it:
            // subsequently created windows will all share the same context.
            m_glContext = new MyGLContext(canvas, Dim);
        }
        glContext = m_glContext;
    }

    glContext->SetCurrent(*canvas);

    return *glContext;
}

IMPLEMENT_APP(MainApp)
