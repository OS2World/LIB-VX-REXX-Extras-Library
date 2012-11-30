VX-REXX EXTRAS
  Version 1.1.1 (2012-02-08)

  VX-REXX Extras is an extension library for Watcom VX-REXX version 2.1.  It
  contains a number of useful functions and two new object classes (a Warp 4
  style notebook control and an improved graphical pushbutton).  See the
  descriptions in VROBJEX.INF for details.


Files

  README.TXT      This file.
  ICONBUTT.MTO    IconButton drag-and-drop information for VX-REXX designer.
  TABBEDDI.MTO    TabbedDialog drag-and-drop information for VX-REXX designer.
  VROBJEX.DLL     The VX-REXX Extras library (developers and runtime).
  VROBJEX.INF     Online help & programming reference.
  VROBJEX.SYM     Symbol file for support.
  VROBJEX.VXO     Library loader for VX-REXX designer.


Installing (Users)

  Copy VROBJEX.DLL to any directory on your LIBPATH.  If you have a previous 
  version installed, close all VX-REXX applications before replacing the old
  copy.  Also make sure that any other old versions of VROBJEX.DLL are removed
  from your system.

  (If you installed the very first preview release, called VRTABDLG.DLL, then 
  you should also delete VRTABDLG.DLL if it is still present on your system.)

  You can safely ignore all other files from this package unless you plan to
  develop REXX programs using this library.


Installing (Developers)

| If you have been using any functions from a previous version of this library,
| make sure you call VRXDropFuncs() from a REXX program before upgrading.  
| Close all VX-REXX applications before replacing the old DLL, and also make 
| sure that no other copies of VROBJEX.DLL are present on your LIBPATH, or in
| the VXREXX directory.

  Copy VROBJEX.DLL to any directory on your LIBPATH.  Copy VROBJEX.VXO and
  VROBJEX.INF to your VXREXX directory, and *.MTO to the VXREXX\SYSTEM
  subdirectory.  Save VROBJEX.SYM anywhere you like, or ignore it entirely - it
  is only needed if you want to analyze process dumps (and if you don't know 
  what that means then you almost certainly don't need it).

  Start VX-REXX and make sure that the new object classes appear on the object
| toolbar.  (If they don't, go into "Options" --> "Object libraries", and make 
| sure that the "Search for and load all VXO files" checkbox is enabled, or 
  else add VROBJEX.DLL to the "Loaded object libraries" list manually.)

  (If you installed the very first preview release, called VRTABDLG.DLL, then 
  you should delete TABDLG.VXO from your VX-REXX directory if it exists.  You 
  can also delete VRTABDLG.DLL if it is installed on your system.)


Using the TabbedDialog class

  TabbedDialog works much like a regular notebook.  In fact, it's implemented
  as a subclass of the normal Notebook class, so it has all the same methods
  and most of the same properties.  (A few properties, like "TabShape", have
  been removed because they don't apply to this type of control.)  See the
  programming reference for details.

  Consequently, it should be quite easy to replace your old notebook objects
  with this new one.  (In most cases, just deleting the old Notebook object
  and creating a new TabbedDialog object with the same name in its place should
  work fine -- although make sure you save any properties you have configured
  in the object settings, like "InitialPageList".)

  IMPORTANT: There is, however, one extra step that you MUST take.  In the
  "Init" section of EVERY page dialog which you are adding to the TabbedDialog
  notebook, you must edit the following code:

    if( \VRIsChildOf( window, "Notebook" ) ) then do
        call VRMethod window, "CenterWindow"
        call VRSet window, "Visible", 1
        call VRMethod window, "Activate"
    end

  Either delete this code entirely, or replace the string "Notebook" with
  "TabbedDialog".  Failure to do so will cause your pages to render improperly
  when the dialog is first populated.

  The above code is managed by VX-REXX itself, and not by the object class;
  therefore, there is unfortunately no way to automate this task.


Known Problems/Limitations

| IconButton control:
|  - When using an Icon image in a button which is smaller than the icon device
|    size, the icon may extend outside the button area.  This appears to be 
|    caused by the internal VX-REXX API used for rendering.
|
| TabbedDialog control:
|  - When a notebook page window has focus, key events are never passed up to 
|    the notebook control.  This prevents things like PageUp, PageDn, and tab
|    focus switching from working properly.  This is a bug in VX-REXX's own
|    dialog processing, and also occurs with the standard Notebook control.
|    There does not appear to be any solution other than to manually handle
|    the corresponding KeyPress events in each page dialog within your VX-REXX
|    program and direct the notebook control to react accordingly.


History

| Version 1.1.1  (2012-02-08)
| - (IconButton) Fixed positioning and cropping of non-scaled bitmap images 
|   when the button is smaller than the image size.
| - (IconButton) Autosize property now properly takes both the image and
|   text dimensions into account (where applicable).
| - (IconButton) Slightly increased the margin around non-rescaled images.


  Version 1.1.0  (2012-02-06)
  - Added new IconButton control.
  - Added new VRXDirectoryDialog function.
  - Removed ContextMenu from the list of events supported by TabbedDialog
    (since v1.0.1 it hasn't been triggered anyway).
  - Added some missing property information to TABBEDDI.MTO.
  - Fixed misreported version string from VRXVersion() and reworked logic to
    make sure it's always in sync with the BLDLEVEL string.
  - Corrected several minor errors in the help file.
  - Increased minimum required VX-REXX version to 2.1.


  Version 1.0.1  (2012-01-20)
  - Implemented workaround for PM exception when clicking on a TabbedDialog 
    control with no pages.
  - TabbedDialog control now supports the page list (MB2 popup) menu.
  - Added BLDLEVEL information to DLL.


  Version 1.0.0  (2010-09-26)
  - Initial release.


Acknowledgements

  Much of the VRXColourDialog function is based on public domain code by
  Paul Ratcliffe.

  While I didn't use any of his actual code, the sources for Chris 
  Wohlgemuth's DrDialog User Controls library were quite helpful to me in 
  fine-tuning the VRXDirectoryDialog logic.

  I'd also like to thank Herwig Bauernfeind for providing testing and 
  feedback.


Notices

  The VX-REXX Extras Library is (C) 2010-2012 Alex Taylor

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  3. The name of the author may not be used to endorse or promote products
     derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

--
Alex Taylor - alex at altsan dot org
February 2012
