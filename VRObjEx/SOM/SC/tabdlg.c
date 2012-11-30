
/*
 * This file was generated by the SOM Compiler.
 * FileName: tabdlg.c.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emitc: 1.24
 */

#define VRTabbedDialog_Class_Source
#include "tabdlg.ih"

/*
 *  VRTabbedDialogInstance_somInit
 */

SOM_Scope void   SOMLINK VRTabbedDialogInstance_somInit(VRTabbedDialog *somSelf)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_somInit");

    parent_somInit(somSelf);
}

/*
 *  VRTabbedDialogInstance_somUninit
 */

SOM_Scope void   SOMLINK VRTabbedDialogInstance_somUninit(VRTabbedDialog *somSelf)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_somUninit");

    parent_somUninit(somSelf);
}

/*
 *  VRTabbedDialogInstance_vrLocalCreateWindow
 */

SOM_Scope HWND   SOMLINK VRTabbedDialogInstance_vrLocalCreateWindow(VRTabbedDialog *somSelf,
		PBOOL visible)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrLocalCreateWindow");

    return (parent_vrLocalCreateWindow(somSelf,visible));
}

/*
 *  VRTabbedDialogInstance_vrSet_TabPosition
 */

SOM_Scope bool   SOMLINK VRTabbedDialogInstance_vrSet_TabPosition(VRTabbedDialog *somSelf,
		PSZ str)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrSet_TabPosition");

    return (bool) 0;
}

/*
 *  VRTabbedDialogInstance_vrGet_TabPosition
 */

SOM_Scope bool   SOMLINK VRTabbedDialogInstance_vrGet_TabPosition(VRTabbedDialog *somSelf,
		PSZ *str)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrGet_TabPosition");

    return (bool) 0;
}

/*
 *  VRTabbedDialogInstance_vrSet_TabDirection
 */

SOM_Scope bool   SOMLINK VRTabbedDialogInstance_vrSet_TabDirection(VRTabbedDialog *somSelf,
		PSZ str)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrSet_TabDirection");

    return (bool) 0;
}

/*
 *  VRTabbedDialogInstance_vrGet_TabDirection
 */

SOM_Scope bool   SOMLINK VRTabbedDialogInstance_vrGet_TabDirection(VRTabbedDialog *somSelf,
		PSZ *str)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrGet_TabDirection");

    return (bool) 0;
}

/*
 *  VRTabbedDialogInstance_vrWM_BUTTON1DOWN
 */

SOM_Scope MRESULT   SOMLINK VRTabbedDialogInstance_vrWM_BUTTON1DOWN(VRTabbedDialog *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrWM_BUTTON1DOWN");

    return (MRESULT) 0;
}

/*
 *  VRTabbedDialogInstance_vrWM_CONTEXTMENU
 */

SOM_Scope MRESULT   SOMLINK VRTabbedDialogInstance_vrWM_CONTEXTMENU(VRTabbedDialog *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrWM_CONTEXTMENU");

    return (parent_vrWM_CONTEXTMENU(somSelf,hWnd,msg,mp1,mp2));
}

/*
 *  VRTabbedDialogInstance_vrWM_COMMAND
 */

SOM_Scope MRESULT   SOMLINK VRTabbedDialogInstance_vrWM_COMMAND(VRTabbedDialog *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrWM_COMMAND");

    return (parent_vrWM_COMMAND(somSelf,hWnd,msg,mp1,mp2));
}

/*
 *  VRTabbedDialogInstance_vrWM_CHAR
 */

SOM_Scope MRESULT   SOMLINK VRTabbedDialogInstance_vrWM_CHAR(VRTabbedDialog *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2)
{
    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrWM_CHAR");

    return (parent_vrWM_CHAR(somSelf,hWnd,msg,mp1,mp2));
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
/*
 *  VRTabbedDialogClass_vrLocalClassInit
 */

SOM_Scope bool   SOMLINK VRTabbedDialogClass_vrLocalClassInit(M_VRTabbedDialog *somSelf)
{
    /* M_VRTabbedDialogData *somThis = M_VRTabbedDialogGetData(somSelf); */
    M_VRTabbedDialogMethodDebug("M_VRTabbedDialog","VRTabbedDialogClass_vrLocalClassInit");

    return (parent_vrLocalClassInit(somSelf));
}

/*
 *  VRTabbedDialogClass_vrLocalWindowClassInit
 */

SOM_Scope bool   SOMLINK VRTabbedDialogClass_vrLocalWindowClassInit(M_VRTabbedDialog *somSelf)
{
    /* M_VRTabbedDialogData *somThis = M_VRTabbedDialogGetData(somSelf); */
    M_VRTabbedDialogMethodDebug("M_VRTabbedDialog","VRTabbedDialogClass_vrLocalWindowClassInit");

    return (parent_vrLocalWindowClassInit(somSelf));
}

/*
 *  VRTabbedDialogClass_somInit
 */

SOM_Scope void   SOMLINK VRTabbedDialogClass_somInit(M_VRTabbedDialog *somSelf)
{
    /* M_VRTabbedDialogData *somThis = M_VRTabbedDialogGetData(somSelf); */
    M_VRTabbedDialogMethodDebug("M_VRTabbedDialog","VRTabbedDialogClass_somInit");

    parent_somInit(somSelf);
}

/*
 *  VRTabbedDialogClass_somUninit
 */

SOM_Scope void   SOMLINK VRTabbedDialogClass_somUninit(M_VRTabbedDialog *somSelf)
{
    /* M_VRTabbedDialogData *somThis = M_VRTabbedDialogGetData(somSelf); */
    M_VRTabbedDialogMethodDebug("M_VRTabbedDialog","VRTabbedDialogClass_somUninit");

    parent_somUninit(somSelf);
}

/*
 *  VRTabbedDialogClass_vrShowHelp
 */

SOM_Scope bool   SOMLINK VRTabbedDialogClass_vrShowHelp(M_VRTabbedDialog *somSelf,
		HWND root_frame)
{
    /* M_VRTabbedDialogData *somThis = M_VRTabbedDialogGetData(somSelf); */
    M_VRTabbedDialogMethodDebug("M_VRTabbedDialog","VRTabbedDialogClass_vrShowHelp");

    return (bool) 0;
}