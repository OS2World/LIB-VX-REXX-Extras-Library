#
# This file was generated by the VX-REXX Class Browser
#

#include "somobj.sc"
#include "core.sc"
#include "visible.sc"
#include "manager.sc"
#include "notebk.sc"

class: VRTabbedDialog,
    local,
    classprefix = VRTabbedDialogClass_,
    external prefix = VRTabbedDialogInstance_,
    major version = 1,
    minor version = 1;

parent class: VRNotebook;

release order:
    vrSet_TabPosition, vrGet_TabPosition, vrSet_TabDirection, 
    vrGet_TabDirection, vrShowHelp, vrWM_BUTTON1DOWN, 
    vrWM_CONTEXTMENU;

passthru: C.h, after;
#ifdef __WATCOMC__
    #pragma aux VRTabbedDialogCClassData "*"
    #pragma aux VRTabbedDialogClassData "*"
    #pragma aux M_VRTabbedDialogCClassData "*"
    #pragma aux M_VRTabbedDialogClassData "*"
#endif
endpassthru;


passthru: C.ih, after;

#include "vxrexx.h"

endpassthru;

methods:


#
# Instance methods
#

    override somInit;
    -- VRTabbedDialogInstance_somInit
    override somUninit;
    -- VRTabbedDialogInstance_somUninit
    override vrLocalCreateWindow;
    -- VRTabbedDialogInstance_vrLocalCreateWindow

#
# REXX Properties
#

    bool vrSet_TabPosition( PSZ str );
    -- VRTabbedDialogInstance_vrSet_TabPosition
    bool vrGet_TabPosition( PSZ *str );
    -- VRTabbedDialogInstance_vrGet_TabPosition
    bool vrSet_TabDirection( PSZ str );
    -- VRTabbedDialogInstance_vrSet_TabDirection
    bool vrGet_TabDirection( PSZ *str );
    -- VRTabbedDialogInstance_vrGet_TabDirection

#
# Message handlers
#

    MRESULT vrWM_BUTTON1DOWN( HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2 ), generate apply = VRTabbedDialog_WM_stub;
    -- VRTabbedDialogInstance_vrWM_BUTTON1DOWN
    override vrWM_CONTEXTMENU;
    -- VRTabbedDialogInstance_vrWM_CONTEXTMENU
    override vrWM_COMMAND;
    -- VRTabbedDialogInstance_vrWM_COMMAND
    override vrWM_CHAR;
    -- VRTabbedDialogInstance_vrWM_CHAR

#
# Class methods
#

    override vrLocalClassInit, class;
    -- VRTabbedDialogClass_vrLocalClassInit
    override vrLocalWindowClassInit, class;
    -- VRTabbedDialogClass_vrLocalWindowClassInit
    override somInit, class;
    -- VRTabbedDialogClass_somInit
    override somUninit, class;
    -- VRTabbedDialogClass_somUninit
    bool vrShowHelp( HWND root_frame ), class;
    -- VRTabbedDialogClass_vrShowHelp
