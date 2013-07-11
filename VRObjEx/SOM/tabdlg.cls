;
; Class 'VRTabbedDialog'
;

class VRTabbedDialog VRNotebook
filepath tabdlg
prefix TDL
<passthru>
<endpassthru>
<classdata>
<endclassdata>
<instancedata>
<endinstancedata>
<rexxmethods>
SetFocus
<endrexxmethods>
<messages>
WM_BUTTON1DOWN
WM_CONTEXTMENU
WM_COMMAND
WM_CHAR
WM_CONTROL
<endmessages>
<properties>
Binding create-time saveable hidden [type=cstring] [editGroup=Style] [editEnumValues=] [editType=enumerated type]
StatusTextAlignment create-time saveable hidden optimizable [type=cstring] [editGroup=Style] [editEnumValues=] [editType=enumerated type]
TabShape create-time saveable hidden optimizable [type=cstring] [editGroup=Pages] [editEnumValues=] [editType=enumerated type]
TabTextAlignment create-time saveable hidden optimizable [type=cstring] [editGroup=Pages] [editEnumValues=] [editType=enumerated type]
MajorTabPos create-time saveable hidden optimizable [type=cstring] [editGroup=Pages] [editEnumValues=] [editType=enumerated type]
BackPages create-time saveable hidden [type=cstring] [editGroup=Style] [editEnumValues=] [editType=enumerated type]
TabPosition create-time read-only saveable [type=cstring] [editGroup=Style] [editEnumValues=;Top;Bottom] [editType=enumerated type]
TabDirection create-time read-only saveable [type=cstring] [editGroup=Style] [editEnumValues=;LeftToRight;RightToLeft] [editType=enumerated type]
ContextMenu event saveable hidden [type=event] [editGroup=Event] [editEnumValues=] [editType=event]
<endproperties>
<classmethods>
vrLocalClassInit [bool] 
vrLocalWindowClassInit [bool] 
somInit [void] 
somUninit [void] 
vrShowHelp [bool] HWND root_frame
<endclassmethods>
<instancemethods>
somInit [void] 
somUninit [void] 
vrLocalCreateWindow [HWND] HWND myparent, LONG argc, PRXSTRING argv
<endinstancemethods>
endclass

