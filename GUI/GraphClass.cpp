#include "GraphClass.h"
#include "MyOpenGL.h"

wxString glGetwxString(GLenum name);

GraphClass::GraphClass(wxWindow* parent, int Dim)
    : GraphBaseClass(parent)
{
    int stereoAttribList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_STEREO, 0 };
    bool stereoWindow = false;
    MyGLCanvas* glc = new MyGLCanvas(this, Dim, stereoWindow ? stereoAttribList : NULL);
    
    TopPanel->GetContainingSizer()->Add(glc,wxSizerFlags().Proportion(1).Expand().Border(wxALL, 0));
    // test IsDisplaySupported() function:
    static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };
    wxLogStatus("Double-buffered display %s supported",
                wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");

    if ( stereoWindow )
    {
        const wxString vendor = glGetwxString(GL_VENDOR).Lower();
        const wxString renderer = glGetwxString(GL_RENDERER).Lower();
        //if ( vendor.find("nvidia") != wxString::npos &&
            //    renderer.find("quadro") == wxString::npos )
            //ShowFullScreen(true);
    }
}

GraphClass::~GraphClass()
{
}

void GraphClass::graph_OnPaint(wxPaintEvent& event)
{
    
}


wxString glGetwxString(GLenum name)
{
    const GLubyte *v = glGetString(name);
    if ( v == 0 )
    {
        // The error is not important. It is GL_INVALID_ENUM.
        // We just want to clear the error stack.
        glGetError();

        return wxString();
    }

    return wxString((const char*)v);
}






