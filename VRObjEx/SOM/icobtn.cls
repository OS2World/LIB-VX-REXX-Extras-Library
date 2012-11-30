;
; Class 'VRIconButton'
;

class VRIconButton VRPushButton
filepath icobtn
prefix ICB
<passthru>
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
PSZ pszText;
PSZ pszImg;
BOOL fMini;
BOOL fResize;
BOOL fAutosize;
BOOL fDown;
BYTE bAlign;
int iMnPos;
PVRMEMPICTURE pPic;

<endinstancedata>
<rexxmethods>
<endrexxmethods>
<messages>
WM_CONTROL
WM_PAINT
WM_MATCHMNEMONIC
<endmessages>
<properties>
Caption saveable [type=cstring] [editGroup=Text] [editEnumValues=] [editType=string]
PicturePath create-time saveable [type=cstring] [editGroup=Picture] [editEnumValues=] [editType=string]
ResizePicture create-time saveable [type=boolean] [editGroup=Picture] [editEnumValues=] [editType=boolean]
TextPosition create-time saveable [type=cstring] [editGroup=Text] [editEnumValues=;Bottom;Center;Left;Right;Top;] [editType=enumerated type]
Pushed create-time saveable [type=boolean] [editGroup=Style] [editEnumValues=] [editType=boolean]
BorderColor saveable hidden [type=cstring] [editGroup=Style] [editEnumValues=] [editType=color]
Autosize saveable [type=boolean] [editGroup=Size] [editEnumValues=] [editType=boolean]
<endproperties>
<classmethods>
vrLocalClassInit [bool] 
vrLocalWindowClassInit [bool] 
somInit [void] 
somUninit [void] 
<endclassmethods>
<instancemethods>
somInit [void] 
somUninit [void] 
vrLocalCreateWindow [HWND] HWND myparent, LONG argc, PRXSTRING argv
<endinstancemethods>
endclass

