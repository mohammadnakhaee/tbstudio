#ifndef checktree_H_INCLUDED
#define checktree_H_INCLUDED

#include "wx/treectrl.h"
#include <map>
#include "checked2.xpm"
#include "checked_d.xpm"
#include "checked_ld.xpm"
#include "checked_mo.xpm"
#include "unchecked2.xpm"
#include "unchecked_d.xpm"
#include "unchecked_ld.xpm"
#include "unchecked_mo.xpm"
#include <wx/icon.h>
#include <wx/imaglist.h>
#include <stack>
#include <wx/tokenzr.h>

#define WXDLLIMPEXP_CHECKTREE

class WXDLLIMPEXP_CHECKTREE wxCheckTree : public wxTreeCtrl
{
    public:
        wxCheckTree(wxWindow *parent, const wxWindowID id,
                   const wxPoint& pos, const wxSize& size,
                   long style = wxTR_DEFAULT_STYLE);
        virtual ~wxCheckTree();

        //methods overriden from base class:
        virtual void SetFocusFromKbd();
        virtual void SetItemTextColour(const wxTreeItemId &item, const wxColour &col);

        //interaction with the check boxes:
        bool EnableCheckBox(const wxTreeItemId &item, bool enable = true );
        bool DisableCheckBox(const wxTreeItemId &item);
        void Check(const wxTreeItemId &item,bool state=true);
        void Uncheck(const wxTreeItemId &item);
        void MakeCheckable(const wxTreeItemId &item,bool state=false);
        wxTreeItemId tree_add(const wxTreeItemId& parent, const wxString& text, bool set_state=false, bool checked=false, bool enabled=true );
        wxTreeItemId tree_add(const wxTreeItemId& parent, const wxString& text, int tree_node, bool set_state=false, bool checked=false, bool enabled=true );
        std::map<int,wxTreeItemId> m_items;
        wxTreeItemId FindItemNamed(const wxString &name);
        wxTreeItemId FindItemIn(wxTreeItemId root, const wxString& sSearchFor);
        wxTreeItemId ContainsItemIn(wxTreeItemId root, const wxString& sSearchFor);
        wxTreeItemId ActiveAndContainsItemIn(wxTreeItemId root, const wxString& sSearchFor);
        int GetItemCount();
        wxTreeItemId FindItemViaDIR(const wxString& dir);
        wxString MyDIR(wxTreeItemId root, wxTreeItemId ID);
        
		enum
		{
		    UNCHECKED,
		    UNCHECKED_MOUSE_OVER,
		    UNCHECKED_LEFT_DOWN,
		    UNCHECKED_DISABLED,
            CHECKED,
		    CHECKED_MOUSE_OVER,
		    CHECKED_LEFT_DOWN,
		    CHECKED_DISABLED
		};

    private:
        //event handlers
		void On_Tree_Sel_Changed( wxTreeEvent& event );

        void On_Char( wxKeyEvent& event );
        void On_KeyDown( wxKeyEvent& event );
        void On_KeyUp( wxKeyEvent& event );

        void On_Mouse_Enter_Tree( wxMouseEvent& event );
        void On_Mouse_Leave_Tree( wxMouseEvent& event );
        void On_Left_DClick( wxMouseEvent& event );
        void On_Left_Down( wxMouseEvent& event );
        void On_Left_Up( wxMouseEvent& event );
        void On_Mouse_Motion( wxMouseEvent& event );
        void On_Mouse_Wheel( wxMouseEvent& event );

        void On_Tree_Focus_Set( wxFocusEvent& event );
        void On_Tree_Focus_Lost( wxFocusEvent& event );

        //private data:
        std::map<wxTreeItemId,wxColor> m_colors;

        bool mouse_entered_tree_with_left_down;

        wxTreeItemId last_mo;
		wxTreeItemId last_ld;
		wxTreeItemId last_kf;


    // NB: due to an ugly wxMSW hack you _must_ use DECLARE_DYNAMIC_CLASS()
    //     if you want your overloaded OnCompareItems() to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default (alphabetical) sorting much faster under wxMSW.
    //DECLARE_DYNAMIC_CLASS(MyTreeCtrl)
};

wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_CHECKTREE, wxEVT_CHECKTREE_CHOICE, wxTreeEvent);
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_CHECKTREE, wxEVT_CHECKTREE_FOCUS, wxTreeEvent);
wxDECLARE_EVENT(CHECKTREE_CheckChanged, wxCommandEvent);

#endif // checktree_H_INCLUDED
