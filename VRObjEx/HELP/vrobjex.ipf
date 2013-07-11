:userdoc.
:title.VX-REXX Extras Reference


.* ****************************************************************************
:h1 x=left y=bottom width=100% height=100% id=vrx_functions.VX-REXX Extras - Functions
:p.This section describes the new functions provided by the VX-REXX Extras library.


.* ----------------------------------------------------------------------------
.* VRXLoadFuncs & VRXDropFuncs
.* ----------------------------------------------------------------------------

:h2 x=left y=bottom width=25% height=100% id=func_vrxfuncs group=1.Library management
:p.Select an item&colon.
:link reftype=hd refid=vrxfuncs_desc auto.
:p.:link reftype=hd refid=vrxfuncs_desc.Overview:elink.
.br
:link reftype=hd refid=vrxfuncs_args.Arguments:elink.
.br
:link reftype=hd refid=vrxfuncs_returns.Returns:elink.
.br
:link reftype=hd refid=vrxfuncs_examples.Examples:elink.


:h2 x=25% y=bottom width=75% height=100% id=vrxfuncs_desc hide group=2.Overview - VRXLoadFuncs &amp. VRXDropFuncs
:p.:hp7.Syntax:ehp7.
:xmp.VRXLoadFuncs()

VRXDropFuncs()
:exmp.

:p.:hp7.Description:ehp7.
:p.:hp2.VRXLoadFuncs:ehp2. registers all functions in the VX-REXX Extras library
(other than itself).
:p.:hp2.VRXDropFuncs:ehp2. deregisters all functions in the VX-REXX Extras
library (including itself).


:h2 x=25% y=bottom width=75% height=50% id=vrxfuncs_args hide group=3.Arguments - VRXLoadFuncs &amp. VRXDropFuncs
:p.The :hp2.VRXLoadFuncs:ehp2. and :hp2.VRXDropFuncs:ehp2. functions take no arguments.

:h2 x=25% y=bottom width=75% height=50% id=vrxfuncs_returns hide group=3.Returns - VRXLoadFuncs &amp. VRXDropFuncs
:p.Both :hp2.VRXLoadFuncs:ehp2. and :hp2.VRXDropFuncs:ehp2. return a null string
("").

:h2 x=25% y=bottom width=75% height=50% id=vrxfuncs_examples hide group=3.Examples - VRXLoadFuncs &amp. VRXDropFuncs
:p.This example loads all functions in the VX-REXX Extras library.
:xmp.
call RxFuncAdd 'VRXLoadFuncs', 'VROBJEX', 'VRXLoadFuncs'
call VRXLoadFuncs
:exmp.
:p.This example unloads all functions in the VX-REXX Extras library.
:xmp.
call VRXDropFuncs
:exmp.


.* ----------------------------------------------------------------------------
.* VRXColourDialog function
.* ----------------------------------------------------------------------------

:h2 x=left y=bottom width=25% height=100% id=func_vrxcolordialog.VRXColorDialog
:link reftype=hd refid=func_vrxcolourdialog auto.

:h2 x=left y=bottom width=25% height=100% id=func_vrxcolourdialog group=1.VRXColourDialog
:p.Select an item&colon.
:link reftype=hd refid=vrxcolourdialog_desc auto.
:p.:link reftype=hd refid=vrxcolourdialog_desc.Overview:elink.
.br
:link reftype=hd refid=vrxcolourdialog_args.Arguments:elink.
.br
:link reftype=hd refid=vrxcolourdialog_returns.Returns:elink.
.br
:link reftype=hd refid=vrxcolourdialog_notes.Notes:elink.
.br
:link reftype=hd refid=vrxcolourdialog_examples.Examples:elink.
.br
:link reftype=hd refid=vrxcolourdialog_refs.See also :elink.


:h2 x=25% y=bottom width=75% height=100% id=vrxcolourdialog_desc hide group=2.Overview - VRXColourDialog function
:p.:hp7.Syntax:ehp7.
:xmp.clrValue = VRXColourDialog( [ :hp1.object:ehp1. ], [ :hp1.initialClr:ehp1. ], [ :hp1.title:ehp1. ] )
:exmp.
:hp2.or:ehp2.
:xmp.clrValue = VRXColorDialog( [ :hp1.object:ehp1. ], [ :hp1.initialClr:ehp1. ], [ :hp1.title:ehp1. ] )
:exmp.

:p.:hp7.Description:ehp7.
:p.This function presents a colour selection dialog.  It can be used to allow
a user to select or edit a colour value using the OS/2 Presentation Manager
&osq.colour wheel&csq. and/or RGB value spinbutton controls.
:p.The dialog includes the following buttons&colon.
:dl compact.
:dt.OK
:dd.Closes the dialog and returns the currently-selected colour value.
:dt.Reset
:dd.Reverts the current selections to the :hp1.initialClr:ehp1. value
(without closing the dialog).
:dt.Cancel
:dd.Closes the dialog and returns a null string.
:edl.


:h2 x=25% y=bottom width=75% height=50% id=vrxcolourdialog_args hide group=3.Arguments - VRXColourDialog function
:dl break=all.
:dt.:hp1.object:ehp1.
:dd.The name of the window to which the dialog is to be modal.  This may be the
object's name (e.g. "Window1"), or its VX-REXX handle (as returned by
:link reftype=hd refid='7800' database='A2Z.INF'.VRWindow:elink.).  The
specified object will be disabled while the dialog is open.
:p.If this parameter is omitted, or a null string is specified, the desktop
window will be used.  This will cause the dialog to be non-modal, but the
caller will still wait for the dialog to close before continuing.  (Note that
any events sent to the caller while the dialog is open will accumulate in
the message queue.)

:dt.:hp1.initialClr:ehp1.
:dd.The initial colour selection which the dialog will display.  Must be one
of the following&colon.
:ul compact.
:li.A string of the form "(R,G,B)", where R, G, and B are decimal numbers (0 to
255) representing red, green, and blue colour values, respectively.
:li.A string of the form "#RRGGBB", where RR, GG, and BB are two-digit
hexadecimal numbers (0 to FF) representing red, green, and blue colour values,
respectively.
:eul.
:p.If not specified, the default is "(255,255,255)" (white).

:dt.:hp1.title:ehp1.
:dd.The title to be displayed in the dialog window.  If omitted, the default
title is "".
:edl.

:h2 x=25% y=bottom width=75% height=50% id=vrxcolourdialog_returns hide group=3.Returns - VRXColourDialog function
:p.The return value is a string representing the selected colour value.
:p.If the :hp1.initialClr:ehp1. value was specified using "#RRGGBB" format,
then the return value will use the same format.  Otherwise, the return value is
a string in of form "(R,G,B)".  (Refer to the :hp1.initialClr:ehp1. argument
for a description of these strings.)
:p.If the dialog is closed using the Cancel button, or if an error occurred,
then the return value will be a null string ("").
:p.If the event of an error, the global variable VRXERROR will contain a
non-zero error code.

:h2 x=25% y=bottom width=75% height=50% id=vrxcolourdialog_notes hide group=3.Notes - VRXColourDialog function
:p.In order to accomodate the different spelling conventions within the English
language, this function is available under two names&colon.
:hp2.VRXColorDialog:ehp2. and :hp2.VRXColourDialog:ehp2..  Either may be used,
as the developer prefers.

:h2 x=25% y=bottom width=75% height=50% id=vrxcolourdialog_examples hide group=3.Examples - VRXColourDialog function
:p.This example changes a pushbutton control's background to a new colour
chosen by the user.
:xmp.
defClr = VRGet("PB_1", "BackColor")
if defClr == "<default>" then
    defClr = "(204,204,204)"
clr = VRXColourDialog( VRWindow(), defClr, "Select Colour")
if clr <> "" then
    call VRSet "PB_1", "BackColor", clr
:exmp.

:h2 x=25% y=bottom width=75% height=50% id=vrxcolourdialog_refs hide group=3.See also - VRXColourDialog function
:ul compact.
:li.:link reftype=hd refid='2040' database='A2Z.INF'.BackColor:elink.
:li.:link reftype=hd refid='2340' database='A2Z.INF'.ForeColor:elink.
:eul.


.* ----------------------------------------------------------------------------
.* VRXDirectoryDialog function
.* ----------------------------------------------------------------------------

:h2 x=left y=bottom width=25% height=100% id=func_vrxdirectorydialog group=1.VRXDirectoryDialog
:p.Select an item&colon.
:link reftype=hd refid=vrxdirectorydialog_desc auto.
:p.:link reftype=hd refid=vrxdirectorydialog_desc.Overview:elink.
.br
:link reftype=hd refid=vrxdirectorydialog_args.Arguments:elink.
.br
:link reftype=hd refid=vrxdirectorydialog_returns.Returns:elink.
.br
:link reftype=hd refid=vrxdirectorydialog_notes.Notes:elink.
.br
:link reftype=hd refid=vrxdirectorydialog_examples.Examples:elink.
.br
:link reftype=hd refid=vrxdirectorydialog_refs.See also :elink.


:h2 x=25% y=bottom width=75% height=100% id=vrxdirectorydialog_desc hide group=2.Overview - VRXDirectoryDialog function
:p.:hp7.Syntax:ehp7.
:xmp.path = VRXDirectoryDialog( [ :hp1.object:ehp1. ], [ :hp1.initialPath:ehp1. ], [ :hp1.title:ehp1. ] )
:exmp.

:p.:hp7.Description:ehp7.
:p.This function presents a directory selection dialog.  This is similar to the
standard file dialog except that only the directory selection control is shown -
individual files cannot be selected.  This dialog is useful in the case where
the user needs to select a directory, rather than a file, for some purpose

:p.The dialog includes the following buttons&colon.
:dl compact.
:dt.OK
:dd.Closes the dialog and returns the currently-selected directory path.
:dt.Cancel
:dd.Closes the dialog and returns a null string.
:edl.


:h2 x=25% y=bottom width=75% height=50% id=vrxdirectorydialog_args hide group=3.Arguments - VRXDirectoryDialog function
:dl break=all.
:dt.:hp1.object:ehp1.
:dd.The name of the window to which the dialog is to be modal.  This may be the
object's name (e.g. "Window1"), or its VX-REXX handle (as returned by
:link reftype=hd refid='7800' database='A2Z.INF'.VRWindow:elink.).  The
specified object will be disabled while the dialog is open.
:p.If this parameter is omitted, or a null string is specified, the desktop
window will be used.  This will cause the dialog to be non-modal, but the
caller will still wait for the dialog to close before continuing.  (Note that
any events sent to the caller while the dialog is open will accumulate in
the message queue.)

:dt.:hp1.initialPath:ehp1.
:dd.The initial directory which will be selected when the dialog appears.  This
is a standard-format path specification identifying a specific directory, and
should not contain wildcards.  A trailing backslash character ("\") is not
required.
:p.If not specified, the dialog will open in the current working directory.

:dt.:hp1.title:ehp1.
:dd.The title to be displayed in the dialog window.  If omitted, the default
title is "".
:edl.


:h2 x=25% y=bottom width=75% height=50% id=vrxdirectorydialog_returns hide group=3.Returns - VRXDirectoryDialog function
:p.The return value is a string representing the selected directory as a
fully-qualified path name.  The string does not include a trailing backslash
character ("\") except when it corresponds to the root directory of a drive.
:p.If the dialog is closed using the Cancel button, or if an error occurred,
then the return value will be a null string ("").
:p.If the event of an error, the global variable VRXERROR will contain a
non-zero error code.


:h2 x=25% y=bottom width=75% height=50% id=vrxdirectorydialog_notes hide group=3.Notes - VRXDirectoryDialog function
:p.It is possible to specify a non-existent directory in the initial path
parameter.  In such a case the path will be initially selected in the dialog,
but will not be re-selectable from within the dialog if the user changes the
selected directory.  As this is liable to be confusing, specifying a
non-existent directory is not generally recommended.


:h2 x=25% y=bottom width=75% height=50% id=vrxdirectorydialog_examples hide group=3.Examples - VRXDirectoryDialog function
:p.This example populates an entryfield control with the path name selected by
the user.
:xmp.
path = VRXDirectoryDialog( VRWindow(),, "Select Directory")
if path <> "" then
    call VRSet "EF_1", "Value", path
:exmp.

:h2 x=25% y=bottom width=75% height=50% id=vrxdirectorydialog_refs hide group=3.See also - VRXDirectoryDialog function
:ul compact.
:li.:link reftype=hd refid='7380' database='A2Z.INF'.VRFileDialog:elink.
:eul.


.* ----------------------------------------------------------------------------
.* VRXGetClipboardText function
.* ----------------------------------------------------------------------------

:h2 x=left y=bottom width=25% height=100% id=func_vrxgetclipboardtext group=1.VRXGetClipboardText
:p.Select an item&colon.
:link reftype=hd refid=vrxgetclipboardtext_desc auto.
:p.:link reftype=hd refid=vrxgetclipboardtext_desc.Overview:elink.
.br
:link reftype=hd refid=vrxgetclipboardtext_args.Arguments:elink.
.br
:link reftype=hd refid=vrxgetclipboardtext_returns.Returns:elink.
.br
:link reftype=hd refid=vrxgetclipboardtext_notes.Notes:elink.
.br
:link reftype=hd refid=vrxgetclipboardtext_examples.Examples:elink.
.br
:link reftype=hd refid=vrxgetclipboardtext_refs.See also :elink.


:h2 x=25% y=bottom width=75% height=100% id=vrxgetclipboardtext_desc hide group=2.Overview - VRXGetClipboardText function
:p.:hp7.Syntax:ehp7.
:xmp.clipText = VRXGetClipboardText()
:exmp.
:p.:hp7.Description:ehp7.
:p.This function retrieves the current text from the OS/2 clipboard, if any
exists.
:p.Unlike the :link reftype=hd  refid='5950' database='A2Z.INF'.GetClipboard:elink.
method, this function does not require an
:link reftype=hd  refid='1000' database='A2Z.INF'.Application:elink. object,
and can be used by text-mode REXX programs (as long as Presentation Manager is
running).

:h2 x=25% y=bottom width=75% height=50% id=vrxgetclipboardtext_args hide group=3.Arguments - VRXGetClipboardText function
:p.The :hp2.VRXGetClipboardText:ehp2. function has no arguments.

:h2 x=25% y=bottom width=75% height=50% id=vrxgetclipboardtext_returns hide group=3.Returns - VRXGetClipboardText function
:p.The returned value is a string corresponding to the text retrieved from the
clipboard.
:p.If the event of an error, a null string will be returned, and the global
variable VRXERROR will contain a non-zero error code.

:h2 x=25% y=bottom width=75% height=50% id=vrxgetclipboardtext_notes hide group=3.Notes - VRXGetClipboardText function
:p.This function retrieves the current CF_TEXT (plain text) contents of the
clipboard.  Other clipboard formats are ignored.
:p.There is no specific limit on the amount of text which may be retrieved by
this function.  However, various window controls may have their own limits on
the amount of text which may be inserted.

:h2 x=25% y=bottom width=75% height=50% id=vrxgetclipboardtext_examples hide group=3.Examples - VRXGetClipboardText function
:p.This example retrives the current clipboard text.
:xmp.
    text = VRXGetClipboardText()
:exmp.

:h2 x=25% y=bottom width=75% height=50% id=vrxgetclipboardtext_refs hide group=3.See also - VRXGetClipboardText function
:ul compact.
:li.:link reftype=hd refid=func_vrxputclipboardtext.VRXPutClipboardText:elink.
:eul.


.* ----------------------------------------------------------------------------
.* VRXPutClipboardText function
.* ----------------------------------------------------------------------------

:h2 x=left y=bottom width=25% height=100% id=func_vrxputclipboardtext group=1.VRXPutClipboardText
:p.Select an item&colon.
:link reftype=hd refid=vrxputclipboardtext_desc auto.
:p.:link reftype=hd refid=vrxputclipboardtext_desc.Overview:elink.
.br
:link reftype=hd refid=vrxputclipboardtext_args.Arguments:elink.
.br
:link reftype=hd refid=vrxputclipboardtext_returns.Returns:elink.
.br
:link reftype=hd refid=vrxputclipboardtext_notes.Notes:elink.
.br
:link reftype=hd refid=vrxputclipboardtext_examples.Examples:elink.
.br
:link reftype=hd refid=vrxputclipboardtext_refs.See also :elink.


:h2 x=25% y=bottom width=75% height=100% id=vrxputclipboardtext_desc hide group=2.Overview - VRXPutClipboardText function
:p.:hp7.Syntax:ehp7.
:xmp.ok = VRXPutClipboardText( [ :hp1.text:ehp1. ], [ :hp1.clearFormats:ehp1. ] )
:exmp.
:p.:hp7.Description:ehp7.
:p.This function writes text to the OS/2 clipboard.
:p.Unlike the :link reftype=hd  refid='5960' database='A2Z.INF'.PutClipboard:elink.
method, this function does not require an
:link reftype=hd  refid='1000' database='A2Z.INF'.Application:elink. object,
and can be used by text-mode REXX programs (as long as Presentation Manager is
running).

:h2 x=25% y=bottom width=75% height=50% id=vrxputclipboardtext_args hide group=3.Arguments - VRXPutClipboardText function
:dl break=all.
:dt.:hp1.text:ehp1.
:dd.The string to be written to the clipboard.  The string's contents will be
saved to the clipboard in CF_TEXT format; any existing clipboard data which is
in CF_TEXT format will be cleared.
:p.If either no value or a null string is specified, all CF_TEXT data currently
in the clipboard will be cleared.
:dt.:hp1.clearFormats:ehp1.
:dd.Determines whether or not the clipboard should be emptied of all formats
(not just CF_TEXT) before writing the new text.
:dl compact break=none.
:dt.1 or Y
:dd.Clear all clipboard formats before writing data; this is the default.
:dt.0 or N
:dd.Leave intact any clipboard data which is not in CF_TEXT format.
:edl.
:edl.

:h2 x=25% y=bottom width=75% height=50% id=vrxputclipboardtext_returns hide group=3.Returns - VRXPutClipboardText function
:p.The return value will be 1 if the text was written to the clipboard
successfully, or 0 if writing to the clipboard failed.
:p.If an error occurred, the global variable VRXERROR will be set to a non-zero
error code.

:h2 x=25% y=bottom width=75% height=50% id=vrxputclipboardtext_notes hide group=3.Notes - VRXPutClipboardText function
:p.It is possible, using this function, to leave non-text clipboard data intact
when copying (unlike the standard VX-REXX
:link reftype=hd  refid='5960' database='A2Z.INF'.PutClipboard:elink.
method).  Doing so is not normally recommended, as it leaves the clipboard in
an unpredictable state which can be confusing for the user.  However, there may
be circumstances where this is desirable.

:h2 x=25% y=bottom width=75% height=50% id=vrxputclipboardtext_examples hide group=3.Examples - VRXPutClipboardText function
:p.The following example copies a string to the clipboard (clearing all other
clipboard data beforehand)&colon.
:xmp.
copytext = "New clipboard text."
call VRXPutClipboardText copytext
:exmp.

:p.The following example simply clears the OS/2 clipboard of all data&colon.
:xmp.
call VRXPutClipboardText ""
:exmp.

:h2 x=25% y=bottom width=75% height=50% id=vrxputclipboardtext_refs hide group=3.See also - VRXPutClipboardText function
:ul compact.
:li.:link reftype=hd refid=func_vrxgetclipboardtext.VRXGetClipboardText:elink.
:eul.


.* ----------------------------------------------------------------------------
.* VRXVersion function
.* ----------------------------------------------------------------------------

:h2 x=left y=bottom width=25% height=100% id=func_vrxversion group=1.VRXVersion
:p.Select an item&colon.
:link reftype=hd refid=vrxversion_desc auto.
:p.:link reftype=hd refid=vrxversion_desc.Overview:elink.
.br
:link reftype=hd refid=vrxversion_args.Arguments:elink.
.br
:link reftype=hd refid=vrxversion_returns.Returns:elink.
.br
:link reftype=hd refid=vrxversion_examples.Examples:elink.


:h2 x=25% y=bottom width=75% height=100% id=vrxversion_desc hide group=2.Overview - VRXVersion function
:p.:hp7.Syntax:ehp7.
:xmp.version = VRXVersion()
:exmp.

:p.:hp7.Description:ehp7.
:p.This function returns the current version of the VX-REXX Extras library.

:h2 x=25% y=bottom width=75% height=50% id=vrxversion_args hide group=3.Arguments - VRXVersion function
:p.The :hp2.VRXVersion:ehp2. function has no arguments.

:h2 x=25% y=bottom width=75% height=50% id=vrxversion_returns hide group=3.Returns - VRXVersion function
:p.The return value is a string in the form "X.Y.Z", where X, Y and Z are
decimal numbers representing the major version, minor version, and refresh
level, respectively.
:p.For example, for VX-REXX Extras version 1.0.1, the returned string will be
"1.0.1".

:h2 x=25% y=bottom width=75% height=50% id=vrxversion_examples hide group=3.Examples - VRXVersion function
:p.This example demonstrates how to verify the current VX-REXX Extras version.
:xmp.
version = VRXVersion()
parse var version with _major "." _minor "." _refresh
if _major < 2 then do
    call VRMessage VRWindow(),,
                   "You will need to upgrade to version 2 or later of the " ||,
                   "VX-REXX Extras library before you can use this program." ,,
                   "Wrong Library Version", "E"
    call Quit
end
:exmp.


.* ****************************************************************************
:h1 x=left y=bottom width=100% height=100%.VX-REXX Extras - Objects
:p.This section describes the new objects provided by the VX-REXX Extras
library.


.* ----------------------------------------------------------------------------
.* IconButton object
.* ----------------------------------------------------------------------------

:h2 x=left y=bottom width=25% height=100% id=icb_top group=1.IconButton object
:p.Select an item&colon.
:link reftype=hd refid=icb_desc auto.
:p.:link reftype=hd refid=icb_desc.Description :elink.
.br
:link reftype=hd refid=icb_props.Properties :elink.
.br
:link reftype=hd refid=icb_events.Events :elink.
.br
:link reftype=hd refid=icb_methods.Methods :elink.
.br
:link reftype=hd refid=icb_notes.Notes :elink.
.br
:link reftype=hd refid=icb_refs.See also :elink.


:h2 x=25% y=bottom width=75% height=100% id=icb_desc hide group=2.Description - IconButton object
:artwork name='iconbtn.bmp'.
:p.The IconButton object is a graphical pushbutton control with considerably
more flexibility than the standard VX-REXX
:link reftype=hd refid='1140' database='A2Z.INF'.ImagePushButton:elink.
object.
:p.An IconButton can have an image, a text caption, or both.  The text
can be aligned in several different ways relative to the image, or even
be overlayed on top of the image.  The button can be drawn with or without
a default border, or with a depressed appearance.


:h2 x=25% y=bottom width=75% height=100% id=icb_props hide group=2.Properties - IconButton object
:ul compact.
:li.:link reftype=hd  refid='2020' database='A2Z.INF'.AutoSize :elink.
:li.:link reftype=hd  refid='2040' database='A2Z.INF'.BackColor :elink.
:li.:link reftype=hd  refid='2060' database='A2Z.INF'.Border :elink.
:li.:link reftype=hd  refid='2140' database='A2Z.INF'.Cancel :elink.
:li.:link reftype=hd  refid='2160' database='A2Z.INF'.Caption :elink.
:li.:link reftype=hd  refid='2200' database='A2Z.INF'.ClassName :elink.
:li.:link reftype=hd  refid='2260' database='A2Z.INF'.Default :elink.
:li.:link reftype=hd  refid='2280' database='A2Z.INF'.Enabled :elink.
:li.:link reftype=hd  refid='2300' database='A2Z.INF'.FirstChild :elink.
:li.:link reftype=hd  refid='2320' database='A2Z.INF'.Font :elink.
:li.:link reftype=hd  refid='2340' database='A2Z.INF'.ForeColor :elink.
:li.:link reftype=hd  refid='2360' database='A2Z.INF'.Height :elink.
:li.:link reftype=hd  refid='2400' database='A2Z.INF'.HelpTag :elink.
:li.:link reftype=hd  refid='2420' database='A2Z.INF'.HelpText :elink.
:li.:link reftype=hd  refid='2460' database='A2Z.INF'.HintText :elink.
:li.:link reftype=hd  refid='3420' database='A2Z.INF'.HWnd :elink.
:li.:link reftype=hd  refid='3780' database='A2Z.INF'.KeyString :elink.
:li.:link reftype=hd  refid='2640' database='A2Z.INF'.Left :elink.
:li.:link reftype=hd  refid='2760' database='A2Z.INF'.Name :elink.
:li.:link reftype=hd  refid='8836' database='A2Z.INF'.NoPointerFocus :elink.
:li.:link reftype=hd  refid='3960' database='A2Z.INF'.Painting :elink.
:li.:link reftype=hd  refid='2780' database='A2Z.INF'.Parent :elink.
:li.:link reftype=hd  refid='2800' database='A2Z.INF'.PicturePath :elink.
:li.:link reftype=hd  refid='prop_pushed'.Pushed :elink.
:li.:link reftype=hd  refid='2860' database='A2Z.INF'.ResizePicture :elink.
:li.:link reftype=hd  refid='2980' database='A2Z.INF'.Self :elink.
:li.:link reftype=hd  refid='3060' database='A2Z.INF'.Sibling :elink.
:li.:link reftype=hd  refid='3080' database='A2Z.INF'.SiblingOrder :elink.
:li.:link reftype=hd  refid='3995' database='A2Z.INF'.TabGroup :elink.
:li.:link reftype=hd  refid='3180' database='A2Z.INF'.TabIndex :elink.
:li.:link reftype=hd  refid='3200' database='A2Z.INF'.TabStop :elink.
:li.:link reftype=hd  refid='prop_textposition'.TextPosition :elink.
:li.:link reftype=hd  refid='3240' database='A2Z.INF'.Top :elink.
:li.:link reftype=hd  refid='3260' database='A2Z.INF'.UserData :elink.
:li.:link reftype=hd  refid='3320' database='A2Z.INF'.Visible :elink.
:li.:link reftype=hd  refid='3340' database='A2Z.INF'.Width :elink.
:eul.


:h2 x=25% y=bottom width=75% height=100% id=icb_events hide group=2.Events - IconButton object
:ul compact.
:li.:link reftype=hd  refid='4020' database='A2Z.INF'.Click :elink.
:li.:link reftype=hd  refid='4320' database='A2Z.INF'.ContextMenu :elink.
:li.:link reftype=hd  refid='8105' database='A2Z.INF'.DragDiscard :elink.
:li.:link reftype=hd  refid='8103' database='A2Z.INF'.DragDrop :elink.
:li.:link reftype=hd  refid='8104' database='A2Z.INF'.DragPrint :elink.
:li.:link reftype=hd  refid='8796' database='A2Z.INF'.DragStart :elink.
:li.:link reftype=hd  refid='4140' database='A2Z.INF'.GotFocus :elink.
:li.:link reftype=hd  refid='4400' database='A2Z.INF'.KeyPress :elink.
:li.:link reftype=hd  refid='4160' database='A2Z.INF'.LostFocus :elink.
:eul.


:h2 x=25% y=bottom width=75% height=100% id=icb_methods hide group=2.Methods - IconButton object
:ul compact.
:li.:link reftype=hd  refid='8837' database='A2Z.INF'.DefineEvent :elink.
:li.:link reftype=hd  refid='5320' database='A2Z.INF'.InvokeHelp :elink.
:li.:link reftype=hd  refid='5340' database='A2Z.INF'.ListMethods :elink.
:li.:link reftype=hd  refid='5360' database='A2Z.INF'.ListProperties :elink.
:li.:link reftype=hd  refid='5480' database='A2Z.INF'.SetFocus :elink.
:eul.


:h2 x=25% y=bottom width=75% height=100% id=icb_notes hide group=2.Notes - IconButton object
:p.The IconButton object supports the same events as the standard
:link reftype=hd  refid='1300' database='A2Z.INF'.PushButton:elink. object,
and all of the same properties with the exception of
:link reftype=hd refid='2080' database='A2Z.INF'.BorderColor:elink..  It also
supports the following additional properties&colon.
:ul compact.
:li.:link reftype=hd  refid='2800' database='A2Z.INF'.PicturePath :elink.
:li.:link reftype=hd  refid='prop_pushed'.Pushed :elink.
:li.:link reftype=hd  refid='2860' database='A2Z.INF'.ResizePicture :elink.
:li.:link reftype=hd  refid='prop_textposition'.TextPosition :elink.
:eul.

:p.How the caption is positioned on the button depends not only on the
:link reftype=hd  refid='prop_textposition'.TextPosition:elink. property, but
also on whether or not an image is defined (via the
:link reftype=hd  refid='2800' database='A2Z.INF'.PicturePath:elink. property),
and on whether or the image is rescaled to fit the entire button area (which is
controlled by the
:link reftype=hd refid='2860' database='A2Z.INF'.ResizePicture:elink. property).

:p.As with the :link reftype=hd  refid='1280' database='A2Z.INF'.PictureBox:elink.
object, the :link reftype=hd  refid='2800' database='A2Z.INF'.PicturePath:elink.
property supports images in either OS/2 Icon or Bitmap format.  By default, the
image will be centered within the area of the button assigned to it (which
depends on the value of the
:link reftype=hd  refid='prop_textposition'.TextPosition:elink. property
- see below.)  Alternatively, if the
:link reftype=hd refid='2860' database='A2Z.INF'.ResizePicture:elink.
property is 1 and the image is in bitmap format, it will be rescaled to fill
the entire button (exclusive of the button border, if enabled).
:p.Note that icons cannot be rescaled; if an icon is specified, the
:link reftype=hd refid='2860' database='A2Z.INF'.ResizePicture:elink. property
will have no effect.
:nt.Using a rescaled image will cause the
:link reftype=hd refid='2020' database='A2Z.INF'.AutoSize:elink. property, if
set, to take only the button text into account when determining the object
size.:ent.

:p.:hp5.Effects of &osq.TextPosition&csq.:ehp5.

:p.When :link reftype=hd  refid='prop_textposition'.TextPosition:elink. is
'Center', the text is simply centered in the button area.  If an image is
defined as well, the text will appear overlayed on top of it.

:p.Things become a bit more complex when
:link reftype=hd refid='prop_textposition'.TextPosition:elink. is 'Top',
'Bottom', 'Left', or 'Right'&colon.
:ul.
:li.If no image is defined, :hp1.or:ehp1. an image in bitmap format is defined
and :link reftype=hd refid='2860' database='A2Z.INF'.ResizePicture:elink. is 1,
then :link reftype=hd refid='prop_textposition'.TextPosition:elink. is
interpreted as a :hp1.justification:ehp1. setting&colon. the text is aligned
relative to the corresponding button edge.
:li.If an image is defined and
:link reftype=hd refid='2860' database='A2Z.INF'.ResizePicture:elink. is 0 (or
the image is in OS/2 Icon format), then
:link reftype=hd  refid='prop_textposition'.TextPosition:elink. is interpreted
as a text :hp1.positioning:ehp1. setting&colon. the text will be positioned on
the indicated side of the image, but justified normally.  In this case, the
IconButton will attempt to position the text and the image side-by-side with
no overlap; however, overlap may still occur if the overall button area is
too small.
:eul.
:p.Refer to the description of the
:link reftype=hd refid='prop_textposition'.TextPosition:elink. property for
further details.


:h2 x=25% y=bottom width=75% height=100% id=icb_refs hide group=2.See also - IconButton object
:ul compact.
:li.:link reftype=hd refid='1280' database='A2Z.INF'.PictureBox:elink.
:li.:link reftype=hd refid='1300' database='A2Z.INF'.PushButton:elink.
:li.:link reftype=hd refid='1360' database='A2Z.INF'.Window:elink.
:eul.


.* ----------------------------------------------------------------------------
.* TabbedDialog object
.* ----------------------------------------------------------------------------

:h2 x=left y=bottom width=25% height=100% id=tdl_top group=1.TabbedDialog object
:p.Select an item&colon.
:link reftype=hd refid=tdl_desc auto.
:p.:link reftype=hd refid=tdl_desc.Description :elink.
.br
:link reftype=hd refid=tdl_props.Properties :elink.
.br
:link reftype=hd refid=tdl_events.Events :elink.
.br
:link reftype=hd refid=tdl_methods.Methods :elink.
.br
:link reftype=hd refid=tdl_notes.Notes :elink.
.br
:link reftype=hd refid=tdl_refs.See also :elink.


:h2 x=25% y=bottom width=75% height=100% id=tdl_desc hide group=2.Description - TabbedDialog object
:artwork name='tabdlg.bmp'.
:p.The TabbedDialog object provides a Warp 4 "new style" notebook control.
:p.This style of notebook is referred to by the Presentation Manager API as a
"tabbed dialog", and this name was chosen for the VX-REXX object in order to
differentiate it from the &osq.regular&csq.
:link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink. control.


:h2 x=25% y=bottom width=75% height=100% id=tdl_props hide group=2.Properties - TabbedDialog object
:ul compact.
:li.:link reftype=hd  refid='2040' database='A2Z.INF'.BackColor :elink.
:li.:link reftype=hd  refid='2200' database='A2Z.INF'.ClassName :elink.
:li.:link reftype=hd  refid='2280' database='A2Z.INF'.Enabled :elink.
:li.:link reftype=hd  refid='2300' database='A2Z.INF'.FirstChild :elink.
:li.:link reftype=hd  refid='2320' database='A2Z.INF'.Font :elink.
:li.:link reftype=hd  refid='2340' database='A2Z.INF'.ForeColor :elink.
:li.:link reftype=hd  refid='2360' database='A2Z.INF'.Height :elink.
:li.:link reftype=hd  refid='2400' database='A2Z.INF'.HelpTag :elink.
:li.:link reftype=hd  refid='2420' database='A2Z.INF'.HelpText :elink.
:li.:link reftype=hd  refid='2460' database='A2Z.INF'.HintText :elink.
:li.:link reftype=hd  refid='3420' database='A2Z.INF'.HWnd :elink.
:li.:link reftype=hd  refid='3560' database='A2Z.INF'.InitialPageList :elink.
:li.:link reftype=hd  refid='3780' database='A2Z.INF'.KeyString :elink.
:li.:link reftype=hd  refid='2640' database='A2Z.INF'.Left :elink.
:li.:link reftype=hd  refid='2760' database='A2Z.INF'.Name :elink.
:li.:link reftype=hd  refid='3520' database='A2Z.INF'.PageCount :elink.
:li.:link reftype=hd  refid='3960' database='A2Z.INF'.Painting :elink.
:li.:link reftype=hd  refid='2780' database='A2Z.INF'.Parent :elink.
:li.:link reftype=hd  refid='8640' database='A2Z.INF'.PreloadPages :elink.
:li.:link reftype=hd  refid='2880' database='A2Z.INF'.Selected :elink.
:li.:link reftype=hd  refid='2980' database='A2Z.INF'.Self :elink.
:li.:link reftype=hd  refid='3060' database='A2Z.INF'.Sibling :elink.
:li.:link reftype=hd  refid='3080' database='A2Z.INF'.SiblingOrder :elink.
:li.:link reftype=hd  refid='prop_tabdirection'.TabDirection :elink.
:li.:link reftype=hd  refid='3180' database='A2Z.INF'.TabIndex :elink.
:li.:link reftype=hd  refid='prop_tabposition'.TabPosition :elink.
:li.:link reftype=hd  refid='3200' database='A2Z.INF'.TabStop :elink.
:li.:link reftype=hd  refid='3240' database='A2Z.INF'.Top :elink.
:li.:link reftype=hd  refid='3260' database='A2Z.INF'.UserData :elink.
:li.:link reftype=hd  refid='3320' database='A2Z.INF'.Visible :elink.
:li.:link reftype=hd  refid='3340' database='A2Z.INF'.Width :elink.
:eul.


:h2 x=25% y=bottom width=75% height=100% id=tdl_events hide group=2.Events - TabbedDialog object
:ul compact.
:li.:link reftype=hd  refid='4020' database='A2Z.INF'.Click :elink.
.* :li.:link reftype=hd  refid='4320' database='A2Z.INF'.ContextMenu :elink.
:li.:link reftype=hd  refid='8105' database='A2Z.INF'.DragDiscard :elink.
:li.:link reftype=hd  refid='8103' database='A2Z.INF'.DragDrop :elink.
:li.:link reftype=hd  refid='8104' database='A2Z.INF'.DragPrint :elink.
:li.:link reftype=hd  refid='8796' database='A2Z.INF'.DragStart :elink.
:li.:link reftype=hd  refid='4140' database='A2Z.INF'.GotFocus :elink.
:li.:link reftype=hd  refid='4400' database='A2Z.INF'.KeyPress :elink.
:li.:link reftype=hd  refid='4160' database='A2Z.INF'.LostFocus :elink.
:li.:link reftype=hd  refid='4240' database='A2Z.INF'.NewPageSize :elink.
:li.:link reftype=hd  refid='4220' database='A2Z.INF'.PageDeleted :elink.
:li.:link reftype=hd  refid='8660' database='A2Z.INF'.PageLoad :elink.
:li.:link reftype=hd  refid='4200' database='A2Z.INF'.PageSelected :elink.
:eul.


:h2 x=25% y=bottom width=75% height=100% id=tdl_methods hide group=2.Methods - TabbedDialog object
:ul compact.
:li.:link reftype=hd  refid='5580' database='A2Z.INF'.DeletePage :elink.
:li.:link reftype=hd  refid='8665' database='A2Z.INF'.GetPageNumber :elink.
:li.:link reftype=hd  refid='8500' database='A2Z.INF'.GetPageWindow :elink.
:li.:link reftype=hd  refid='8580' database='A2Z.INF'.GetStatusText :elink.
:li.:link reftype=hd  refid='8540' database='A2Z.INF'.GetTabText :elink.
:li.:link reftype=hd  refid='8620' database='A2Z.INF'.InsertBlankPage :elink.
:li.:link reftype=hd  refid='5560' database='A2Z.INF'.InsertPage :elink.
:li.:link reftype=hd  refid='5320' database='A2Z.INF'.InvokeHelp :elink.
:li.:link reftype=hd  refid='5970' database='A2Z.INF'.ListChildren :elink.
:li.:link reftype=hd  refid='5340' database='A2Z.INF'.ListMethods :elink.
:li.:link reftype=hd  refid='5360' database='A2Z.INF'.ListProperties :elink.
:li.:link reftype=hd  refid='5480' database='A2Z.INF'.SetFocus:elink.
:li.:link reftype=hd  refid='8520' database='A2Z.INF'.SetPageWindow :elink.
:li.:link reftype=hd  refid='8600' database='A2Z.INF'.SetStatusText :elink.
:li.:link reftype=hd  refid='8560' database='A2Z.INF'.SetTabText :elink.
:eul.


:h2 x=25% y=bottom width=75% height=100% id=tdl_notes hide group=2.Notes - TabbedDialog object
:p.The TabbedDialog object is a subclass of the standard
:link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink. object, and
is almost completely compatible.
:p.There is one significant difference, however, in how you must handle page
windows.  Normally, when you create a secondary window, VX-REXX automatically
adds the following code to its :hp3.WindowName_:ehp3.:hp2.Init:ehp2.
method&colon.
:xmp.
    if( \VRIsChildOf( window, "Notebook" ) ) then do
        call VRMethod window, "CenterWindow"
        call VRSet window, "Visible", 1
        call VRMethod window, "Activate"
    end
:exmp.
:p.For every page window which is added to the TabbedDialog notebook, you
:hp2.must:ehp2. either remove the above code entirely, or else change the
"Notebook" string in the first line to "TabbedDialog".  Failure to do so will
cause your pages to render improperly when the dialog is first populated.

:p.
:p.Programatically speaking, the only other differences from the standard
:link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink. object are as
follows&colon.
:ul.
:li.The TabbedDialog object does :hp2.not:ehp2. support the following
:link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink. properties&colon.
:ul compact.
:li.:link reftype=hd refid='3600' database='A2Z.INF'.BackPages:elink.
:li.:link reftype=hd  refid='3580' database='A2Z.INF'.Binding:elink.
:li.:link reftype=hd refid='3540' database='A2Z.INF'.MajorTabPos:elink.
:li.:link reftype=hd  refid='3480' database='A2Z.INF'.StatusTextAlignment:elink.
:li.:link reftype=hd  refid='3460' database='A2Z.INF'.TabShape:elink.
:li.:link reftype=hd  refid='3440' database='A2Z.INF'.TabTextAlignment:elink.
:eul.
:li.The TabbedDialog object supports the following properties which are not
supported by the standard
:link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink. object&colon.
:ul compact.
:li.:link reftype=hd  refid='prop_tabdirection'.TabDirection :elink.
:li.:link reftype=hd  refid='prop_tabposition'.TabPosition :elink.
:eul.
:li.In addition, unlike the standard
:link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink., the
TabbedDialog object supports the
:link reftype=hd  refid='5480' database='A2Z.INF'.SetFocus:elink. method.
:li.Finally, the TabbedDialog object does not support the
:link reftype=hd  refid='4320' database='A2Z.INF'.ContextMenu:elink. event, as
it defines and handles its own context menu (a list of notebook pages)
automatically.
:eul.
:p.In all other respects, using the TabbedDialog object is exactly the same as
using the :link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink.
object.
:p.Refer to the :link reftype=hd  refid='UNOTEBK' database='PROGGUID.INF'.Notebooks:elink.
section in the :hp1.VX-REXX Programmer's Guide:ehp1. for details on how to use
notebook controls under VX-REXX.

:h2 x=25% y=bottom width=75% height=100% id=tdl_refs hide group=2.See also - TabbedDialog object
:ul compact.
:li.:link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink.
:li.:link reftype=hd refid='1360' database='A2Z.INF'.Window:elink.
:eul.


.* ****************************************************************************
:h1 x=left y=bottom width=100% height=100% id=vrx_properties.VX-REXX Extras - Properties
:p.This section describes new properties used by objects in the VX-REXX Extras
library.


.* ----------------------------------------------------------------------------
:h2 x=left y=bottom id=prop_pushed.Pushed property
:p.The Pushed property applies to
:link reftype=hd refid=icb_top.IconButton:elink. objects.  It causes the
button border to be drawn in a depressed or 'pushed-in' style.
:p.Use a value of 1 to enable this property, or a value 0 to disable it.  By
default, this property is disabled.

:p.
:p.:hp7.Applies to:ehp7.
:p.:link reftype=hd refid=icb_top.IconButton:elink.

:p.
:p.:hp7.Notes:ehp7.
:p.As the Pushed property affects the style in which the button border is drawn,
it has no effect if the
:link reftype=hd refid='2060' database='A2Z.INF'.Border:elink. property is set
to 0.

:p.
:p.:hp7.See also:ehp7.
:ul compact.
:li.:link reftype=hd refid='2060' database='A2Z.INF'.Border:elink.
:eul.

.* ----------------------------------------------------------------------------
:h2 x=left y=bottom id=prop_tabdirection.TabDirection property
:p.The TabDirection property indicates in which direction the tabs on a
:link reftype=hd refid=tdl_top.TabbedDialog:elink. notebook will be aligned
&amp. ordered.
:p.This property may only be set at design time.
:p.There are two possible values&colon.
:dl break=fit tsize=20.
:dt.LeftToRight
:dd.The tabs will be aligned to the left side of the notebook, and ordered from
left to right.  This is the default.
:dt.RightToLeft
:dd.The tabs will be aligned to the right side of the notebook, and ordered from
right to left.
:edl.

:p.
:p.:hp7.Applies to:ehp7.
:p.:link reftype=hd refid=tdl_top.TabbedDialog:elink.

:p.
:p.:hp7.Notes:ehp7.
:p.None.

:p.
:p.:hp7.See also:ehp7.
:ul compact.
:li.:link reftype=hd refid=prop_tabposition.TabPosition:elink.
:eul.

.* ----------------------------------------------------------------------------
:h2 x=left y=bottom width=100% height=100% id=prop_tabposition.TabPosition property
:p.The TabPosition property indicates the location of the tabs on a
:link reftype=hd refid=tdl_top.TabbedDialog:elink. notebook.
:p.This property may only be set at design time.
:p.There are two possible values&colon.
:dl break=fit tsize=20.
:dt.Bottom
:dd.The tabs will appear on the bottom edge of the notebook.
:dt.Top
:dd.The tabs will appear on the top edge of the notebook.  This is the default.
:edl.

:p.
:p.:hp7.Applies to:ehp7.
:p.:link reftype=hd refid=tdl_top.TabbedDialog:elink.

:p.
:p.:hp7.Notes:ehp7.
:p.The TabPosition property of the TabbedDialog control corresponds in both
behaviour and internal implementation to the
:link reftype=hd refid='3540' database='A2Z.INF'.MajorTabPos:elink. property
of the standard
:link reftype=hd refid='1270' database='A2Z.INF'.Notebook:elink. control.  Unlike
the :link reftype=hd refid='3540' database='A2Z.INF'.MajorTabPos:elink. property,
however, TabPosition only supports the values :hp2.Top:ehp2. and
:hp2.Bottom:ehp2., as these are the only styles allowed by the Presentation
Manager tabbed-dialog notebook.

:p.
:p.:hp7.See also:ehp7.
:ul compact.
:li.:link reftype=hd refid=prop_tabdirection.TabDirection:elink.
:eul.

.* ----------------------------------------------------------------------------
:h2 x=left y=bottom id=prop_textposition.TextPosition property
:p.The TextPosition property indicates the position of the text on an
:link reftype=hd refid=icb_top.IconButton:elink. control.  Note that the effect
of this property varies slightly depending on whether or not the
:link reftype=hd  refid='2800' database='A2Z.INF'.PicturePath:elink. and/or
:link reftype=hd  refid='2860' database='A2Z.INF'.ResizePicture:elink.
properties of the IconButton are set, as described under :hp2.Notes:ehp2..
:p.There are five possible values&colon.
:dl break=fit tsize=20.
:dt.Bottom
:dd.The text will be aligned to the bottom edge of the button.
:dt.Center
:dd.The text will be centered in the middle of the button.  This is the
default.
:dt.Left
:dd.If the button is displaying an image which is :hp1.not:ehp1. rescaled
to the entire button area, then the text will be positioned to the left of
the button image with standard justification.  Otherwise, the text will be
aligned to the left edge of the button.
:dt.Right
:dd.If the button is displaying an image which is :hp1.not:ehp1. rescaled,
then the text will be positioned to the right of the button image with
standard justification.  Otherwise, it will be aligned to the right edge of
the button.
:dt.Top
:dd.The text will be aligned to the top edge of the button.
:edl.

:p.
:p.:hp7.Applies to:ehp7.
:p.:link reftype=hd refid=icb_top.IconButton:elink.

:p.
:p.:hp7.Notes:ehp7.
:p.If the TextPosition property is set to 'Center', then the text will be
overlayed on the image if there is one.
:p.Otherwise, the behaviour depends on whether or not the button is displaying
an image, and whether or not the image is rescaled to fill the entire button
area.
:ul.
:li.If the button has no image, then the TextPosition property is used to
justify the text to the specified button edge.
:p.:artwork align='center' name='textpos1.bmp' runin.
:hp1.
.ce The effect of TextPosition = 'Right' in an IconButton with no image
:ehp1.
:li.If a Bitmap format image is used :hp1.and:ehp1. is rescaled to fill the
button area (i.e. the
:link reftype=hd  refid='2860' database='A2Z.INF'.ResizePicture:elink. property
is 1), then the behaviour of TextPosition is the same as if there is no
image (see above).  In this case, the text will always be overlayed on the image.
:li.Otherwise (when there is an image but it is not being rescaled), the text
will be placed on the indicated side of the image.
:p.Note that values of 'Right' or 'Left' behave differently in this case, in
that the text is aligned to the image rather than to the button edge, and
left-justified.  Values of 'Top' or 'Bottom', on the other hand, behave the same
with respect to the text position as they do when there is no image&colon. the
text is always positioned next to the button edge, and centered horizontally.
:p.In this case, the text will be positioned so as not to overlap the image
:hp1.if:ehp1. there is sufficient space on the button control&colon.
:p.:artwork align='center' name='textpos2.bmp' runin.
:hp1.
.ce The effect of TextPosition = 'Right' in an IconButton with a non-rescaled image
:ehp1.
:p.However, if the button does not provide enough space for both the image and
text to appear separately, then the text will be permitted to overlap the
image&colon.
:p.:artwork align='center' name='textpos3.bmp' runin.
:hp1.
.ce The effect of TextPosition = 'Right' in an IconButton with a non-rescaled image, when there is insufficient space to avoid overlap
:ehp1.
:eul.

:p.
:p.:hp7.See also:ehp7.
:ul compact.
:li.:link reftype=hd  refid='2800' database='A2Z.INF'.PicturePath:elink.
:li.:link reftype=hd  refid='2860' database='A2Z.INF'.ResizePicture:elink.
:eul.
:euserdoc.

