#include "main.h"
#include "GridClass.h"

bool MainApp::OnInit()
{
    // Add the common image handlers
    wxImage::AddHandler( new wxPNGHandler );
    wxImage::AddHandler( new wxJPEGHandler );
    
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
