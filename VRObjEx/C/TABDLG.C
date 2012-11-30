/*
 * tabdlg.c
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\tabdlg.c in preparation for compiling.  New
 * methods will be appended at the end only.
 */

#define INCL_PM

#include "vxrexx.h"
#include "vxfuncs.h"

#define VRTabbedDialog_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "tabdlg.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "tabdlg.ph"
#include "vxcdata.h"

#ifndef BKS_TABBEDDIALOG
#define BKS_TABBEDDIALOG         0x00000800
#endif

static somId id_Click = 0;

extern PSZ VRTabbedDialogPicturePath;

/*
static void _System SetChildVisible( SOMAny *obj, PVOID data )
{

}
*/

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
    HWND hwnd;
    LONG flags;

    flags = _vrGetWindowFlags( somSelf );
    flags |= BKS_TABBEDDIALOG;
    _vrSetWindowFlags( somSelf, flags );

//  *visible = (( flags & WS_VISIBLE ) != 0 );

    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrLocalCreateWindow");
    hwnd = parent_vrLocalCreateWindow(somSelf,visible);

    return (hwnd);
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
/*
 *  VRTabbedDialogClass_vrLocalClassInit

 * Note: The vrLocalClassInit function is defined
 * in the .ph file for this class....
 */


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

    get_picturepath( somSelf ) = VRTabbedDialogPicturePath;

    if( VRQueryRunMode() == VR_DESIGN_MODE ){
        VRInstallHelp( somSelf );
    }
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


#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRTabbedDialogInstance_vrSet_TabPosition
 */

SOM_Scope bool   SOMLINK VRTabbedDialogInstance_vrSet_TabPosition(VRTabbedDialog *somSelf,
        PSZ str)
{
    LONG flags;

    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrSet_TabPosition");

    flags = _vrGetWindowFlags( somSelf );
    if ( str && tolower( *str ) == 't') {
        flags |= BKS_MAJORTABTOP;
        flags &= ~BKS_MAJORTABBOTTOM;
    }
    else if ( str && tolower( *str ) == 'b') {
        flags &= ~BKS_MAJORTABTOP;
        flags |= BKS_MAJORTABBOTTOM;
    }
    _vrSetWindowFlags( somSelf, flags );

    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRTabbedDialogInstance_vrGet_TabPosition
 */

SOM_Scope bool   SOMLINK VRTabbedDialogInstance_vrGet_TabPosition(VRTabbedDialog *somSelf,
        PSZ *str)
{
    LONG flags;
    BOOL ok = FALSE;
    PSZ  type;

    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrGet_TabPosition");

    flags = _vrGetWindowFlags( somSelf );

    if ( flags & BKS_MAJORTABBOTTOM )
        type = "Bottom";
    else
        type = "Top";

    *str = VRMemAlloc( strlen( type ) + 1 );
    if ( *str ) {
        strcpy( *str, type );
        ok = TRUE;
    }

    return( ok );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRTabbedDialogInstance_vrSet_TabDirection
 */

SOM_Scope bool   SOMLINK VRTabbedDialogInstance_vrSet_TabDirection(VRTabbedDialog *somSelf,
        PSZ str)
{
    LONG flags;

    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrSet_TabDirection");

    flags = _vrGetWindowFlags( somSelf );
    if ( str && tolower( *str ) == 'l') {
        if ( flags & BKS_MAJORTABBOTTOM ) {     // tabs on bottom, left-to-right order
            flags |= BKS_BACKPAGESBR;
            flags &= ~BKS_BACKPAGESTR & ~BKS_BACKPAGESTL & ~BKS_BACKPAGESBL;
        } else {                                // tabs on top, left-to-right order
            flags |= BKS_BACKPAGESTR;
            flags &= ~BKS_BACKPAGESTL & ~BKS_BACKPAGESBL & ~BKS_BACKPAGESBR;
        }
    }
    else if ( str && tolower( *str ) == 'r') {
        if ( flags & BKS_MAJORTABBOTTOM ) {     // tabs on bottom, right-to-left order
            flags |= BKS_BACKPAGESBL;
            flags &= ~BKS_BACKPAGESTR & ~BKS_BACKPAGESTL & ~BKS_BACKPAGESBR;
        } else {                                // tabs on top, right-to-left order
            flags |= BKS_BACKPAGESTL;
            flags &= ~BKS_BACKPAGESTR & ~BKS_BACKPAGESBL & ~BKS_BACKPAGESBR;
        }
    }
    _vrSetWindowFlags( somSelf, flags );

    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRTabbedDialogInstance_vrGet_TabDirection
 */

SOM_Scope bool   SOMLINK VRTabbedDialogInstance_vrGet_TabDirection(VRTabbedDialog *somSelf,
        PSZ *str)
{
    LONG flags;
    BOOL ok = FALSE;
    PSZ  type;

    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrGet_TabDirection");

    flags = _vrGetWindowFlags( somSelf );

    if (( flags & BKS_BACKPAGESTL ) || ( flags & BKS_BACKPAGESBL ))
        type = "RightToLeft";
    else
        type = "LeftToRight";

    *str = VRMemAlloc( strlen( type ) + 1 );
    if ( *str ) {
        strcpy( *str, type );
        ok = TRUE;
    }

    return( ok );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta

/*
 *  VRTabbedDialogClass_vrShowHelp
 */

SOM_Scope bool   SOMLINK VRTabbedDialogClass_vrShowHelp(M_VRTabbedDialog *somSelf,
        HWND root_frame)
{
    /* M_VRTabbedDialogData *somThis = M_VRTabbedDialogGetData(somSelf); */
    M_VRTabbedDialogMethodDebug("M_VRTabbedDialog","VRTabbedDialogClass_vrShowHelp");

    return FALSE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRTabbedDialogInstance_vrWM_BUTTON1DOWN
 */

SOM_Scope MRESULT   SOMLINK VRTabbedDialogInstance_vrWM_BUTTON1DOWN(VRTabbedDialog *somSelf,
        HWND hWnd,
        ULONG msg,
        MPARAM mp1,
        MPARAM mp2)
{
    SHORT usCount;

    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrWM_BUTTON1DOWN");

    /* Force a no-op when there are no pages (this avoids a trap in PM) */
    usCount = (SHORT) WinSendMsg( hWnd, BKM_QUERYPAGECOUNT, 0, MPFROMSHORT( BKA_END ));
    if ( !usCount ) return (MRESULT) 0;

    return _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

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

    /* This makes the "page menu" work when MB2 is clicked on the tab area */
    return _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );

    /* return (parent_vrWM_CONTEXTMENU(somSelf,hWnd,msg,mp1,mp2)); */
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

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

    if ( SHORT1FROMMP( mp2 ) == CMDSRC_MENU ) {
        /* Make sure page menu selections get handled by PM */
        _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );
    }

    return (parent_vrWM_COMMAND(somSelf,hWnd,msg,mp1,mp2));
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRTabbedDialogInstance_vrWM_CHAR
 */

SOM_Scope MRESULT   SOMLINK VRTabbedDialogInstance_vrWM_CHAR(VRTabbedDialog *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2)
{
    USHORT fsKeyFlags;

    /* VRTabbedDialogData *somThis = VRTabbedDialogGetData(somSelf); */
    VRTabbedDialogMethodDebug("VRTabbedDialog","VRTabbedDialogInstance_vrWM_CHAR");

    fsKeyFlags = (USHORT) SHORT1FROMMP(mp1);
    if ( fsKeyFlags & KC_VIRTUALKEY ) {
        if (( SHORT2FROMMP( mp2 ) == VK_PAGEUP ) ||
            ( SHORT2FROMMP( mp2 ) == VK_PAGEDOWN ))
        {
            /* This avoids an endless message loop in the VX-REXX notebook event handler */
            return _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );
        }
     }

    return (parent_vrWM_CHAR(somSelf,hWnd,msg,mp1,mp2));
}


