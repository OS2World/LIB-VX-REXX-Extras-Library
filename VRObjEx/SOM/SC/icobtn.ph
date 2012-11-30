#ifndef VRIconButton_PH_INCLUDED
#define VRIconButton_PH_INCLUDED

#include "vxrexx.h"

#ifdef VRIconButton_Class_Source

VRMESSAGEMAP VRIconButtonMessageMap[] =
  {
    { WM_CONTROL, NULL, "vrWM_CONTROL" },
    { WM_PAINT, NULL, "vrWM_PAINT" },
    { WM_MATCHMNEMONIC, NULL, "vrWM_MATCHMNEMONIC" },
    { WM_NULL, NULL, NULL }
  };

#else

extern VRMESSAGEMAP VRIconButtonMessageMap[];

#endif


extern const VRPROPENTRY VRIconButtonPropertyList[];
extern const VRMETHENTRY VRIconButtonMethodList[];

#ifdef VRIconButton_Class_Source

#include "core.ph"
#include "vxcdata.h"
SOM_Scope bool SOMLINK VRIconButtonClass_vrLocalClassInit( M_VRIconButton *class )
  {
    bool ok;
    get_rexx_properties( class ) = (PVRPROPENTRY) VRIconButtonPropertyList;
    get_rexx_methods( class ) = (PVRMETHENTRY) VRIconButtonMethodList;
    get_parent_class( class ) = _somGetParent( class );
    get_is_virtual( class ) = FALSE;
    get_default_prefix( class ) = "ICB";

    get_is_predefined( class ) = FALSE;
    VRInheritMessageMap( class, 20 );

    ok = VRAddToMessageMap( class, VRIconButtonMessageMap );
    if( ok ){
        ok = VRAddStandardMap( class );
    }

    VRIconButtonClass_vrLocalWindowClassInit( class );
    return( TRUE );
  }

#endif


#endif
