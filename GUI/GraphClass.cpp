#include "GraphClass.h"

wxString glGetwxString(GLenum name);

GraphClass::GraphClass(wxWindow* parent, int Dim)
    : GraphBaseClass(parent)
{
    int stereoAttribList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_STEREO, 0 };
    bool stereoWindow = false;
    glc = new MyGLCanvas(this, Dim, stereoWindow ? stereoAttribList : NULL);
    
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
    DiscardAtomicStructure();
}

void GraphClass::CreateAtomicStructure(TBModel* tbmodelvar)
{
    tbmodel = tbmodelvar;
    glc->CreateDoubleArray(3,tbmodel->nAtoms);
    glc->CreateIntArray(1,tbmodel->nAtoms);
    
    std::list<double>::iterator x=tbmodel->XArray.begin();
    std::list<double>::iterator y=tbmodel->YArray.begin();
    std::list<double>::iterator z=tbmodel->ZArray.begin();
    std::list<int>::iterator k=tbmodel->KindArray.begin();
    
    for (int i=0; i<tbmodel->nAtoms; i++)
    {
        glc->DoubleArray[0][i] = *x;    x++;
        glc->DoubleArray[1][i] = *y;    y++;
        glc->DoubleArray[2][i] = *z;    z++;
        glc->IntArray[0][i] = *k;   k++;
    }
    glc->LoadToCanvas();
}

void GraphClass::DiscardAtomicStructure()
{
    glc->DiscardDoubleArrays();
    glc->DiscardIntArrays();
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






