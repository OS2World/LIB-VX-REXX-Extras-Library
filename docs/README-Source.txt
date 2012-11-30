VX-REXX EXTRAS SOURCE CODE

VX-REXX Extras is an extension library for Watcom VX-REXX version 2.1.  It
contains a number of useful functions and two new object classes (a Warp 4
style notebook control and an improved graphical pushbutton).  This is the 
source code, written in C and SOM.


BUILDING

Building this library from source requires the following:

 * The Watcom VX-REXX Object Development Kit (ODK).  This was originally
   sold by Watcom but is now abandonware like VX-REXX itself.  If you don't
   have a copy, it is quite easy to find it available for download from 
   various sources.  (Of course, the legality of obtaining it this way is 
   ambiguous at best, so I'm not actually advocating it... use your own
   judgement.)

 * The IBM OS/2 Developer's Toolkit version 2.1.  This specific version of
   the toolkit is required, as the build scripts and header files provided
   by the ODK make assumptions which depend on it.  It may well be possible
   to rewrite things to allow use of the latest Toolkit (v4.52 at the time
   of writing), but in spite of various attempts I've never succeeded in
   accomplishing this.

   Note that the 2.1 Toolkit doesn't have to be properly installed through
   your CONFIG.SYS and other system files - it's enough that the files and
   directories exist.  The included SETTINGS.CMD (which is called by all the
   build scripts) sets up the path and environment settings as needed, as 
   long as you provide it with the path to the top-level directory.

 * IBM C/Set++ version 2.1.  Again, as with the toolkit, you must have this
   specific version of the IBM compiler, as the ODK link libraries seem to
   have fixed dependencies on it.

   As with the toolkit, only the actual files and directories of C/Set++ 
   are required.  SETTINGS.CMD will set up the necessary environment 
   automatically when you run any of the build scripts.  Just make sure 
   that SETTINGS.CMD as the correct path to the top-level C/Set++ directory.

   Note: It should also be possible to use Watcom C version 10, although 
   I haven't tested this.  OpenWatcom does not work with the current codebase,
   although it may be possible to hack the build scripts and/or header files 
   to support it.  Since I'm not very familiar with the Watcom compilers I'm 
   not up to doing this myself.  (If anybody does manage to do this, I'd 
   appreciate it.)

 * MAKEDESC.CMD somewhere in your PATH.  This is a REXX script included with
   a number of open source projects from NetLabs and elsewhere, so I haven't
   bothered to include it here.  (If you need to disable it, comment out the
   line in BUILD.CMD referring to it.)

To build the library (VROBJEX.DLL), first edit SETTINGS.CMD and either delete
everything between the first two comment blocks (in which case you will be
prompted for the necessary paths the next time you run BUILD.CMD), or else 
directly edit the path names at the top of this file to point to the correct
locations.

Run BUILD.CMD to build a release version of the library, or BUILDDBG.CMD to
build a debug version.  (In my experience, there's rarely much point in 
building the debug version, since trying to use the IBM debugger on it just
resulted in IPMD crashing.  If you need to trace the internal execution, it
may be simpler to just add some code which dumps whatever information you need
into a logfile.)

If you want to change the version number, simply edit version.h and update
the "VERSION" and "VERSION_STRING" definitions.  The former is used to generate
the return value from VRXVersion(); the latter is used in the BLDLEVEL string.


LEARNING HOW TO USE THE ODK

The documentation provided by the VX-REXX ODK is rather terse, to say the 
least, and the programming reference is rather incomplete.  The best way to
learn how to use the ODK is simply practice.

It's not necessary to be familiar with SOM programming (the ODK automates
pretty much all the SOM code generation), but you should at least try to
understand the basic principles involved.

Read through the Programmer's Guide from start to finish, and actually do
the programming tutorial - there's no substitute for experience.  You will
also find that you can learn quite a bit from the sample project code which
isn't otherwise documented.

NOTE: There's one thing that the ODK fails to properly automate, and the
Programmer's Guide doesn't mention this.  If you add methods, properties,
events, etc. to an object class via the Class Browser, and then subsequently
delete them, references to the deleted items may remain left-over in the
SOM source files.  This can cause problems when you try to recompile.  I've
found that the following trick seems to work to get rid of cruft:
 - Delete the obsolete items in the Class Browser, and Exit when done.
 - Run MAKE.CMD in the SOM directory (I'm not sure if this step is actually
   necessary, but it doesn't hurt).
 - Edit SOM\SC\<file>.csc where <file> is the base filename of the class 
   you have just modified.  Look for references to the items you deleted
   (usually these are under the "ReleaseOrder" section).  Delete any you
   find, and save the file.
 - Run MAKE.CMD from the SOM directory again.
 - Now you can edit C\<file>.C and remove any functions which refer to the
   deleted properties/events.  
 - Now you can build the project with BUILD.CMD.


LICENSE

VX-REXX Extras Library, (C) 2010-2012 Alex Taylor

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
