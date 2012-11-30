/*
 * SOMINIT.C -- SOM class initialization.
 */

#define INCL_PM
#define INCL_DOS

#include "vxrexx.h"
#include "visible.h"
#include "vxfuncs.h"

/* Header files for classes */
#include "tabdlg.h"
#include "icobtn.h"
/* :sominit:hfiles: */


#include "..\version.h"

/* Icon definitions */
PSZ VRTabbedDialogPicturePath = "#100:" DLLNAME ;
PSZ VRIconButtonPicturePath = "#102:" DLLNAME ;
/* :sominit:icons:104: */

#ifndef MAKELIB

extern HMODULE VRParentModule;
extern PSZ     VRParentName;
extern PFN     VRParentLoadFunction;

/*
 * _VXREXX_CALLER_ -- If this routine is found by VX-REXX, it is called
 *                    before the SOMInitModule routine is called.  The
 *                    two args that are passed are the module name
 *                    and module handle of the caller.
 */

void _System _VXREXX_CALLER_( PSZ modname, HMODULE modhandle )
  {
    PTIB tib;
    PPIB pib;

    DosGetInfoBlocks( &tib, &pib );

    if( modhandle == pib->pib_hmte && modname ){
        VRParentLoadFunction = (PFN) modname;
        VRParentModule       = modhandle;
    } else {
        if( modname ){
            VRParentName = modname;
        }

        if( modhandle ){
            VRParentModule = modhandle;
        }
    }
  }

#endif

/*
 * SomInit       -- This routine is called automatically by VX-REXX
 *                  when the DLL is loaded.  It should call the
 *                  appropriate class initialization routines.
 *
 *   Note: "SomInit" is a macro defined above.
 */

void _System SomInit( integer4 majorVersion, integer4 minorVersion )
  {
    /* Make sure we're running the correct version of VX-REXX... if not,
     * then don't load the classes...
     */

    if( VRVersion() < MINIMUM_VXREXX_LEVEL ){
        WinMessageBox( HWND_DESKTOP, hNULL, LEVEL_ERRORMSG,
                       LEVEL_TITLE, 0, MB_OK | MB_MOVEABLE );
        return;
    }

    /* This is where you add your class definitions, as in...
     *     MyClassNewClass( majorVersion, minorVersion )
     */

    VRTabbedDialogNewClass( majorVersion, minorVersion );
    VRIconButtonNewClass( majorVersion, minorVersion );
    /* :sominit:init: */
  }

/* SomUninit -- Note: "SomUninit" is a macro defined above */

#define UnClass( x ) _somUnregisterClass( SOMClassMgrObject, x ## ClassData.classObject )

void _System SomUninit( void )
  {
    /* This is where you undefine the class, as in...
     *        UnClass( MyClass )
     */

    UnClass( VRTabbedDialog );
    UnClass( VRIconButton );
    /* :sominit:uninit: */
  }

/* VersionEntry is a macro -- see above for its definition */

ULONG _System VersionEntry( PULONG version_number, PSZ buf, ULONG length )
  {
    ULONG ok = TRUE;

    if( version_number ){
        *version_number = VERSION;
    }

    if( buf && length > 0 ){
        if( strlen( VERSION_STRING ) <= length + 1 ){
            strcpy( buf, VERSION_STRING );
        }
    }

    return( ok );
  }

#ifdef MAKELIB

#include "vrinit.h"

static void Init()
  {
    extern void VRRegisterInitializer( PFN );

    VRRegisterInitializer( (PFN) SomInit );
  }

AXI( Init, 32 )

#endif
