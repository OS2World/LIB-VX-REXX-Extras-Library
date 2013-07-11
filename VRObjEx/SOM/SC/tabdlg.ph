#ifndef VRTabbedDialog_PH_INCLUDED
#define VRTabbedDialog_PH_INCLUDED

#include "vxrexx.h"

#ifdef VRTabbedDialog_Class_Source

VRMESSAGEMAP VRTabbedDialogMessageMap[] =
  {
    { WM_BUTTON1DOWN, NULL, "vrWM_BUTTON1DOWN" },
    { WM_CONTEXTMENU, NULL, "vrWM_CONTEXTMENU" },
    { WM_COMMAND, NULL, "vrWM_COMMAND" },
    { WM_CHAR, NULL, "vrWM_CHAR" },
    { WM_CONTROL, NULL, "vrWM_CONTROL" },
    { WM_NULL, NULL, NULL }
  };

#else

extern VRMESSAGEMAP VRTabbedDialogMessageMap[];

#endif


extern const VRPROPENTRY VRTabbedDialogPropertyList[];
extern const VRMETHENTRY VRTabbedDialogMethodList[];

#ifdef VRTabbedDialog_Class_Source

#include "core.ph"
#include "vxcdata.h"
SOM_Scope bool SOMLINK VRTabbedDialogClass_vrLocalClassInit( M_VRTabbedDialog *class )
  {
    bool ok;
    get_rexx_properties( class ) = (PVRPROPENTRY) VRTabbedDialogPropertyList;
    get_rexx_methods( class ) = (PVRMETHENTRY) VRTabbedDialogMethodList;
    get_parent_class( class ) = _somGetParent( class );
    get_is_virtual( class ) = FALSE;
    get_default_prefix( class ) = "TDL";

    get_is_predefined( class ) = FALSE;
    VRInheritMessageMap( class, 20 );

    ok = VRAddToMessageMap( class, VRTabbedDialogMessageMap );
    if( ok ){
        ok = VRAddStandardMap( class );
    }

    VRTabbedDialogClass_vrLocalWindowClassInit( class );
    return( TRUE );
  }

#endif


#endif
