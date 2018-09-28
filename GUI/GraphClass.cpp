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

void GraphClass::CreateAtomicStructure(Sec30* sec30Var)
{
    sec30 = sec30Var;
    int nUnitcellAtoms = 0;
    sec30->GetVar(_("nAtoms[0]"),nUnitcellAtoms);
    
    int kind[nUnitcellAtoms];
    double XArray[nUnitcellAtoms];
    double YArray[nUnitcellAtoms];
    double ZArray[nUnitcellAtoms];
    
    for (int icell=0; icell<nUnitcellAtoms; icell++)
    {
        sec30->GetVar(_("KABC_Coords"), icell, 0, kind[icell]);
        sec30->GetVar(_("XYZ_Coords"), icell, 0, XArray[icell]);
        sec30->GetVar(_("XYZ_Coords"), icell, 1, YArray[icell]);
        sec30->GetVar(_("XYZ_Coords"), icell, 2, ZArray[icell]);
    }
    
    double a[3],b[3],c[3];
    sec30->GetVar(_("a[0]"), a[0]);
    sec30->GetVar(_("a[1]"), a[1]);
    sec30->GetVar(_("a[2]"), a[2]);
    sec30->GetVar(_("b[0]"), b[0]);
    sec30->GetVar(_("b[1]"), b[1]);
    sec30->GetVar(_("b[2]"), b[2]);
    sec30->GetVar(_("c[0]"), c[0]);
    sec30->GetVar(_("c[1]"), c[1]);
    sec30->GetVar(_("c[2]"), c[2]);
    
    int nShowingAtoms = 0;
    sec30->GetVar(_("nShowingAtoms[0]"),nShowingAtoms);
    
    glc->CreateDoubleArray(3,nShowingAtoms);
    glc->CreateIntArray(1,nShowingAtoms);

    int ma[2],mb[2],mc[2],TBl,TBm,TBn;
    sec30->GetVar(_("ma[0]"), ma[0]);
    sec30->GetVar(_("ma[1]"), ma[1]);
    sec30->GetVar(_("mb[0]"), mb[0]);
    sec30->GetVar(_("mb[1]"), mb[1]);
    sec30->GetVar(_("mc[0]"), mc[0]);
    sec30->GetVar(_("mc[1]"), mc[1]);
    sec30->GetVar(_("TBl[0]"), TBl);
    sec30->GetVar(_("TBm[0]"), TBm);
    sec30->GetVar(_("TBn[0]"), TBn);
    
    bool CustomViewmode,TBViewmode,TBEssentialViewmode;
    sec30->GetRadioVar(_("CustomViewmode[0]"),CustomViewmode);
    sec30->GetRadioVar(_("TBViewmode[0]"),TBViewmode);
    sec30->GetRadioVar(_("TBEssentialViewmode[0]"),TBEssentialViewmode);
    
    int lmin,lmax,mmin,mmax,nmin,nmax;
    
    if (CustomViewmode)
    {
        lmin = ma[0]; lmax = ma[1];
        mmin = mb[0]; mmax = mb[1];
        nmin = mc[0]; nmax = mc[1];
    }
    else if (TBViewmode || TBEssentialViewmode)
    {
        lmin = -TBl; lmax = TBl;
        mmin = -TBm; mmax = TBm;
        nmin = -TBn; nmax = TBn;
    }
    
    if (TBEssentialViewmode)
    {
        EssentialListi.clear();
        EssentialListj.clear();
        EssentialListk.clear();
    }
    
    if (lmin>lmax) {int dummy = lmax; lmax = lmin; lmin = dummy;}
    if (mmin>mmax) {int dummy = mmax; mmax = mmin; mmin = dummy;}
    if (nmin>nmax) {int dummy = nmax; nmax = nmin; nmin = dummy;}
    
    int iAtom = -1;
    for (int i=lmax; i>=lmin; i--)
        for (int j=mmax; j>=mmin; j--)
            for (int k=nmax; k>=nmin; k--)
            {
                if ( CustomViewmode || TBViewmode || (TBEssentialViewmode && isItNew(i,j,k)))
                for (int icell=0; icell<nUnitcellAtoms; icell++)
                {
                    iAtom++;
                    glc->IntArray[0][iAtom] = kind[icell];
                    glc->DoubleArray[0][iAtom] = XArray[icell] + i*a[0] + j*b[0] + k*c[0];
                    glc->DoubleArray[1][iAtom] = YArray[icell] + i*a[1] + j*b[1] + k*c[1];
                    glc->DoubleArray[2][iAtom] = ZArray[icell] + i*a[2] + j*b[2] + k*c[2];
                }
            }
    
    glc->LoadToCanvas();
}

void GraphClass::DiscardAtomicStructure()
{
    glc->DiscardDoubleArrays();
    glc->DiscardIntArrays();
}

bool GraphClass::isItNew(int i,int j,int k)
{
    std::list<int>::iterator ii;
    std::list<int>::iterator ij;
    std::list<int>::iterator ik;
    bool isOK = true;
    
    ii=EssentialListi.begin();
    ij=EssentialListj.begin();
    ik=EssentialListk.begin();
    for (int s=0; s!=EssentialListi.size(); s++)
    {
        if (*ii == -i && *ij == -j && *ik == -k) {isOK = false; break;}
        ii++;ij++;ik++;
    }
    
    if (isOK)
    {
        EssentialListi.insert(ii,i);
        EssentialListi.insert(ij,j);
        EssentialListi.insert(ik,k);
    }
    return isOK;
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






