
/*
 * This file was generated by the SOM Compiler.
 * FileName: icobtn.h.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emith: 1.11
 */

#ifndef icobtn_h
#define icobtn_h


#include <som.h>

/*
 * Define the class name as an object type
 */
#ifndef VRIconButton
#define VRIconButton SOMAny
#endif
#include "pbutton.h"

/*
 * Passthru lines: File: "C.h", "after"
 */
#ifdef __WATCOMC__
    #pragma aux VRIconButtonCClassData "*"
    #pragma aux VRIconButtonClassData "*"
    #pragma aux M_VRIconButtonCClassData "*"
    #pragma aux M_VRIconButtonClassData "*"
#endif

#define VRIconButton_MajorVersion 1
#define VRIconButton_MinorVersion 1

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define VRIconButtonNewClass c
#pragma linkage(c, system)
#define VRIconButtonClassData d
#define VRIconButtonCClassData x
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define VRIconButton_classObj VRIconButtonClassData.classObject
#define _VRIconButton VRIconButton_classObj

/*
 * New and Renew macros for VRIconButton
 */
#define _VRIconButtonNew() (_somNew(VRIconButtonClassData.classObject))
#define VRIconButtonNew() \
	( VRIconButtonClassData.classObject \
		? _VRIconButtonNew() \
		: ( VRIconButtonNewClass(VRIconButton_MajorVersion, VRIconButton_MinorVersion), _VRIconButtonNew() ) )
#define VRIconButtonRenew(buf) \
	( _somRenew(VRIconButtonClassData.classObject, buf) )

/*
 * Override method: somInit
 */
#define VRIconButton_somInit(somSelf) \
	SOMObject_somInit(somSelf)

/*
 * Override method: somUninit
 */
#define VRIconButton_somUninit(somSelf) \
	SOMObject_somUninit(somSelf)

/*
 * Override method: vrLocalCreateWindow
 */
#define VRIconButton_vrLocalCreateWindow(somSelf,visible) \
	VRCore_vrLocalCreateWindow(somSelf,visible)

/*
 * Override method: vrSet_Caption
 */
#define VRIconButton_vrSet_Caption(somSelf,str) \
	VRVisible_vrSet_Caption(somSelf,str)

/*
 * Override method: vrGet_Caption
 */
#define VRIconButton_vrGet_Caption(somSelf,str) \
	VRVisible_vrGet_Caption(somSelf,str)

/*
 * Override method: vrSet_Autosize
 */
#define VRIconButton_vrSet_Autosize(somSelf,on) \
	VRButton_vrSet_Autosize(somSelf,on)

/*
 * Override method: vrGet_Autosize
 */
#define VRIconButton_vrGet_Autosize(somSelf,on) \
	VRButton_vrGet_Autosize(somSelf,on)

/*
 * New Method: vrSet_PicturePath
 */
typedef bool    SOMLINK somTP_VRIconButton_vrSet_PicturePath(VRIconButton *somSelf,
		PSZ str);
#pragma linkage(somTP_VRIconButton_vrSet_PicturePath, system)
typedef somTP_VRIconButton_vrSet_PicturePath *somTD_VRIconButton_vrSet_PicturePath;
#define somMD_VRIconButton_vrSet_PicturePath "----"
#define VRIconButton_vrSet_PicturePath(somSelf,str) \
    (SOM_Resolve(somSelf, VRIconButton, vrSet_PicturePath) \
	(somSelf,str))
#define _vrSet_PicturePath VRIconButton_vrSet_PicturePath

/*
 * New Method: vrGet_PicturePath
 */
typedef bool    SOMLINK somTP_VRIconButton_vrGet_PicturePath(VRIconButton *somSelf,
		PSZ *str);
#pragma linkage(somTP_VRIconButton_vrGet_PicturePath, system)
typedef somTP_VRIconButton_vrGet_PicturePath *somTD_VRIconButton_vrGet_PicturePath;
#define somMD_VRIconButton_vrGet_PicturePath "----"
#define VRIconButton_vrGet_PicturePath(somSelf,str) \
    (SOM_Resolve(somSelf, VRIconButton, vrGet_PicturePath) \
	(somSelf,str))
#define _vrGet_PicturePath VRIconButton_vrGet_PicturePath

/*
 * New Method: vrSet_ResizePicture
 */
typedef bool    SOMLINK somTP_VRIconButton_vrSet_ResizePicture(VRIconButton *somSelf,
		BOOL on);
#pragma linkage(somTP_VRIconButton_vrSet_ResizePicture, system)
typedef somTP_VRIconButton_vrSet_ResizePicture *somTD_VRIconButton_vrSet_ResizePicture;
#define somMD_VRIconButton_vrSet_ResizePicture "----"
#define VRIconButton_vrSet_ResizePicture(somSelf,on) \
    (SOM_Resolve(somSelf, VRIconButton, vrSet_ResizePicture) \
	(somSelf,on))
#define _vrSet_ResizePicture VRIconButton_vrSet_ResizePicture

/*
 * New Method: vrGet_ResizePicture
 */
typedef bool    SOMLINK somTP_VRIconButton_vrGet_ResizePicture(VRIconButton *somSelf,
		BOOL *on);
#pragma linkage(somTP_VRIconButton_vrGet_ResizePicture, system)
typedef somTP_VRIconButton_vrGet_ResizePicture *somTD_VRIconButton_vrGet_ResizePicture;
#define somMD_VRIconButton_vrGet_ResizePicture "----"
#define VRIconButton_vrGet_ResizePicture(somSelf,on) \
    (SOM_Resolve(somSelf, VRIconButton, vrGet_ResizePicture) \
	(somSelf,on))
#define _vrGet_ResizePicture VRIconButton_vrGet_ResizePicture

/*
 * New Method: vrSet_TextPosition
 */
typedef bool    SOMLINK somTP_VRIconButton_vrSet_TextPosition(VRIconButton *somSelf,
		PSZ str);
#pragma linkage(somTP_VRIconButton_vrSet_TextPosition, system)
typedef somTP_VRIconButton_vrSet_TextPosition *somTD_VRIconButton_vrSet_TextPosition;
#define somMD_VRIconButton_vrSet_TextPosition "----"
#define VRIconButton_vrSet_TextPosition(somSelf,str) \
    (SOM_Resolve(somSelf, VRIconButton, vrSet_TextPosition) \
	(somSelf,str))
#define _vrSet_TextPosition VRIconButton_vrSet_TextPosition

/*
 * New Method: vrGet_TextPosition
 */
typedef bool    SOMLINK somTP_VRIconButton_vrGet_TextPosition(VRIconButton *somSelf,
		PSZ *str);
#pragma linkage(somTP_VRIconButton_vrGet_TextPosition, system)
typedef somTP_VRIconButton_vrGet_TextPosition *somTD_VRIconButton_vrGet_TextPosition;
#define somMD_VRIconButton_vrGet_TextPosition "----"
#define VRIconButton_vrGet_TextPosition(somSelf,str) \
    (SOM_Resolve(somSelf, VRIconButton, vrGet_TextPosition) \
	(somSelf,str))
#define _vrGet_TextPosition VRIconButton_vrGet_TextPosition

/*
 * New Method: vrSet_Pushed
 */
typedef bool    SOMLINK somTP_VRIconButton_vrSet_Pushed(VRIconButton *somSelf,
		BOOL on);
#pragma linkage(somTP_VRIconButton_vrSet_Pushed, system)
typedef somTP_VRIconButton_vrSet_Pushed *somTD_VRIconButton_vrSet_Pushed;
#define somMD_VRIconButton_vrSet_Pushed "----"
#define VRIconButton_vrSet_Pushed(somSelf,on) \
    (SOM_Resolve(somSelf, VRIconButton, vrSet_Pushed) \
	(somSelf,on))
#define _vrSet_Pushed VRIconButton_vrSet_Pushed

/*
 * New Method: vrGet_Pushed
 */
typedef bool    SOMLINK somTP_VRIconButton_vrGet_Pushed(VRIconButton *somSelf,
		BOOL *on);
#pragma linkage(somTP_VRIconButton_vrGet_Pushed, system)
typedef somTP_VRIconButton_vrGet_Pushed *somTD_VRIconButton_vrGet_Pushed;
#define somMD_VRIconButton_vrGet_Pushed "----"
#define VRIconButton_vrGet_Pushed(somSelf,on) \
    (SOM_Resolve(somSelf, VRIconButton, vrGet_Pushed) \
	(somSelf,on))
#define _vrGet_Pushed VRIconButton_vrGet_Pushed

/*
 * New Method: vrWM_CONTROL
 */
typedef MRESULT    SOMLINK somTP_VRIconButton_vrWM_CONTROL(VRIconButton *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2);
#pragma linkage(somTP_VRIconButton_vrWM_CONTROL, system)
typedef somTP_VRIconButton_vrWM_CONTROL *somTD_VRIconButton_vrWM_CONTROL;
#define somMD_VRIconButton_vrWM_CONTROL "----"
#define VRIconButton_vrWM_CONTROL(somSelf,hWnd,msg,mp1,mp2) \
    (SOM_Resolve(somSelf, VRIconButton, vrWM_CONTROL) \
	(somSelf,hWnd,msg,mp1,mp2))
#define _vrWM_CONTROL VRIconButton_vrWM_CONTROL

/*
 * New Method: vrWM_PAINT
 */
typedef MRESULT    SOMLINK somTP_VRIconButton_vrWM_PAINT(VRIconButton *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2);
#pragma linkage(somTP_VRIconButton_vrWM_PAINT, system)
typedef somTP_VRIconButton_vrWM_PAINT *somTD_VRIconButton_vrWM_PAINT;
#define somMD_VRIconButton_vrWM_PAINT "----"
#define VRIconButton_vrWM_PAINT(somSelf,hWnd,msg,mp1,mp2) \
    (SOM_Resolve(somSelf, VRIconButton, vrWM_PAINT) \
	(somSelf,hWnd,msg,mp1,mp2))
#define _vrWM_PAINT VRIconButton_vrWM_PAINT

/*
 * New Method: vrWM_MATCHMNEMONIC
 */
typedef MRESULT    SOMLINK somTP_VRIconButton_vrWM_MATCHMNEMONIC(VRIconButton *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2);
#pragma linkage(somTP_VRIconButton_vrWM_MATCHMNEMONIC, system)
typedef somTP_VRIconButton_vrWM_MATCHMNEMONIC *somTD_VRIconButton_vrWM_MATCHMNEMONIC;
#define somMD_VRIconButton_vrWM_MATCHMNEMONIC "----"
#define VRIconButton_vrWM_MATCHMNEMONIC(somSelf,hWnd,msg,mp1,mp2) \
    (SOM_Resolve(somSelf, VRIconButton, vrWM_MATCHMNEMONIC) \
	(somSelf,hWnd,msg,mp1,mp2))
#define _vrWM_MATCHMNEMONIC VRIconButton_vrWM_MATCHMNEMONIC

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMAny * SOMLINK VRIconButtonNewClass(integer4 scemajorVersion,
		integer4 sceminorVersion);
#pragma linkage(VRIconButtonNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct VRIconButtonClassDataStructure {
	SOMAny *classObject;
	somMToken vrSet_PicturePath;
	somMToken vrGet_PicturePath;
	somMToken vrWM_CONTROL;
	somMToken vrSet_ResizePicture;
	somMToken vrGet_ResizePicture;
	somMToken vrSet_TextPosition;
	somMToken vrGet_TextPosition;
	somMToken vrSet_Pushed;
	somMToken vrGet_Pushed;
	somMToken vrWM_PAINT;
	somMToken vrWM_MATCHMNEMONIC;
} VRIconButtonClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct VRIconButtonCClassDataStructure {
	somMethodTab *parentMtab;
	somDToken instanceDataToken;
} VRIconButtonCClassData;

#endif       /* icobtn_h */

/*
 * This file was generated by the SOM Compiler.
 * FileName: icobtn.h.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emith: 1.11
 */

#ifndef icobtn_mh
#define icobtn_mh


/*
 * Define the class name as an object type
 */
#ifndef M_VRIconButton
#define M_VRIconButton SOMAny
#endif

#define M_VRIconButton_MajorVersion 1
#define M_VRIconButton_MinorVersion 1

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define M_VRIconButtonNewClass c
#pragma linkage(c, system)
#define M_VRIconButtonClassData d
#define M_VRIconButtonCClassData x
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define M_VRIconButton_classObj M_VRIconButtonClassData.classObject
#define _M_VRIconButton M_VRIconButton_classObj

/*
 * New and Renew macros for M_VRIconButton
 */
#define _M_VRIconButtonNew() (_somNew(M_VRIconButtonClassData.classObject))
#define M_VRIconButtonNew() \
	( M_VRIconButtonClassData.classObject \
		? _M_VRIconButtonNew() \
		: ( M_VRIconButtonNewClass(M_VRIconButton_MajorVersion, M_VRIconButton_MinorVersion), _M_VRIconButtonNew() ) )
#define M_VRIconButtonRenew(buf) \
	( _somRenew(M_VRIconButtonClassData.classObject, buf) )

/*
 * Override method: vrLocalClassInit
 */
#define M_VRIconButton_vrLocalClassInit(somSelf) \
	M_VRCore_vrLocalClassInit(somSelf)

/*
 * Override method: vrLocalWindowClassInit
 */
#define M_VRIconButton_vrLocalWindowClassInit(somSelf) \
	M_VRCore_vrLocalWindowClassInit(somSelf)

/*
 * Override method: somInit
 */
#define M_VRIconButton_somInit(somSelf) \
	SOMObject_somInit(somSelf)

/*
 * Override method: somUninit
 */
#define M_VRIconButton_somUninit(somSelf) \
	SOMObject_somUninit(somSelf)

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMAny * SOMLINK M_VRIconButtonNewClass(integer4 scemajorVersion,
		integer4 sceminorVersion);
#pragma linkage(M_VRIconButtonNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct M_VRIconButtonClassDataStructure {
	SOMAny *classObject;
} M_VRIconButtonClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct M_VRIconButtonCClassDataStructure {
	somMethodTab *parentMtab;
	somDToken instanceDataToken;
} M_VRIconButtonCClassData;

#endif       /* icobtn_h */