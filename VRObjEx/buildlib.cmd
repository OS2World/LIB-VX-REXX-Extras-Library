/*
 * buildlib -- Make the object into a .lib file
 */
 
'@echo off'
if settings()<>0 then exit 32000

compiler = Value( "vxcompiler", ,"OS2ENVIRONMENT" )
version = Value( "vxversion", , "OS2ENVIRONMENT" )
dllname = Value( "vxdllname", , "OS2ENVIRONMENT" ) 
som = Value( "vxsom", , "OS2ENVIRONMENT" )

vxodk = value( 'VXODK',, 'OS2ENVIRONMENT' )
if( right( vxodk, 1 ) \= '\' )then do
    vxodk = vxodk || '\'
end

say 'Making sure class information is up-to-date...'

somlib  = 'som.lib'
if( som = 'SOM2' )then
    somlib = 'somtk.lib'

exports = 'SOMInitModule SOMUninitModule _VXREXX_CALLER_ _' || dllname || '_VERSION_INFO_'
libs    = somlib 'rexx.lib os2386.lib'

say 'Making sure class information is up-to-date...'

old = directory()
call directory 'som'
call make
call directory old

makefile = 'makefile'
linkfile = dllname || '.LNK'  /* only for CSET */
deffile  = dllname || '.DEF'  /* only for CSET */

compiler = translate( compiler )
if( left( compiler, 1 ) = 'W' )then do
    compiler = 'WATCOM'
end; else do
    compiler = 'CSET'
    say 'The ODK is not enabled to build .LIB files with the CSet compiler.'
    say 'You will have to use Watcom C to build the .LIB file.'
    exit 1
end 
    
say 'Building makefile for use with the' compiler 'compiler...'

version = translate( version )
if( left( version, 1 ) = '1' )then
    version = '101'

call rxfuncadd 'sysloadfuncs', 'REXXUTIL', 'SysLoadFuncs'
call sysloadfuncs

call Erase makefile

if( compiler = 'CSET' )then
    call Erase linkfile

call lineout makefile, '#'
call lineout makefile, '# This makefile is automatically generated by build.cmd'
call lineout makefile, '# Don''t edit it manually!'
call lineout makefile, '#'
call lineout makefile, ''
call lineout makefile, 'ODKDIR   =' vxodk || '    '
call lineout makefile, 'SOMDIR   =' vxodk || 'SOM.' || version || '\' || '    '
call lineout makefile, 'dllname  =' dllname || '   '
call lineout makefile, 'somlevel =' som
call lineout makefile, ''

if( compiler = 'WATCOM' )then do
    call lineout makefile, 'objs = &'
end; else do
    call lineout makefile, 'objs = \'
end

call sysfiletree 'SOM\SC\*.PRP', 'files', 'fo'
prplist = ''
do i = 1 to files.0
    name = filespec( 'name', files.i )
    prplist = prplist || ' som\sc\' || name
end

call sysfiletree 'RC\*.ICO', 'files', 'fo'
iconlist = ''
do i = 1 to files.0
    name = filespec( 'name', files.i )
    iconlist = iconlist || ' rc\' || name
end

call sysfiletree 'C\*.C', 'files', 'fo'
do i = 1 to files.0
    name = filespec( 'name', files.i )
    name = left( name, length( name ) - 2 )
    files.i = name

    if( compiler = 'WATCOM' )then do
        call lineout makefile, '   ' name || '.obj &'
    end; else do
        call lineout makefile, '    $(o)\' || name || '.obj \'

        str = name || '.obj'
        if( i < files.0 )then do
            str = str || ' +'
        end
        call lineout linkfile, str
    end
end

call lineout makefile, ''
if( compiler = 'WATCOM' )then do
    call lineout makefile, '!include' vxodk'\bin\makewatc.inc'
end; else do
    call lineout makefile, '!include' vxodk'\bin\makecset.inc'
end
call lineout makefile, ''

if( compiler = 'WATCOM' )then do
    call WatcomOut
end; else do
    call CSetOut
end

call stream makefile, 'c', 'close'

if( compiler = 'WATCOM' )then do
    say "Invoking wmake on the makefile..."
    'wmake MAKELIB=1 MAKEEXE=1' arg(1)
end; else do
    say "Invoking nmake on the makefile..."
    'nmake MAKELIB=1 MAKEEXE=1' arg(1)
end

say ''
say 'Done build.'

exit 0

/*
 * CSetOut
 */

CSetOut:
    call lineout makefile, '$(o)\$(dllname).dll : $(objs) $(o)\$(dllname).res $(dllname).lnk $(dllname).def'
    call lineout makefile, '    cd $(o)'
    call lineout makefile, '    set LIB=$(ODKDIR)lib;$(LIB)'
    call lineout makefile, '    link386 $(lflags) @..\$(dllname).lnk'
    call lineout makefile, '    rc $(dllname).res $(dllname).dll'
    call lineout makefile, '    cd ..'

    say 'Building LNK file ...'

    call lineout linkfile, dllname || '.DLL'
    call lineout linkfile, dllname || '.MAP'
    call lineout linkfile, 'vxrexxc.lib' libs
    call lineout linkfile, '..\' || dllname || '.DEF'

    if( stream( deffile, 'c', 'query exists' ) = '' )then do
        say 'Building DEF file ...'

        call lineout deffile, '; DEF file for' dllname
        call lineout deffile, 'library' dllname 'initinstance terminstance'
        call lineout deffile, 'data multiple readwrite preload nonshared'
        call lineout deffile, 'code loadoncall'
        call lineout deffile, 'protmode'
        call lineout deffile, 'exports'
        do i = 1 to words( exports )
            call lineout deffile, '   ' word( exports, i )
        end
    end

    call lineout makefile, ''
    call lineout makefile, '$(o)\props.obj : c\props.c' prplist
    call lineout makefile, ''
    call lineout makefile, '$(o)\$(dllname).res : rc\$(dllname).rc' iconlist
    call lineout makefile, ''

    return

/*
 * WatcomOut
 */

WatcomOut:
    
    call lineout makefile, 'exports =' exports
    call lineout makefile, 'libs =' libs
    call lineout makefile, ''
    call lineout makefile, '$(obj_dir)\$(dllname).lib : $(objs) $(obj_dir)\$(dllname).res'
    call lineout makefile, '    %create files.tmp'
    call lineout makefile, '    @cd $(obj_dir)'
    call lineout makefile, '    @for %i in ($(objs)) do @%append files.tmp %i'
    call lineout makefile, '    wlib /n/b/q $(dllname).lib @files.tmp'
    call lineout makefile, '    @cd $(main_dir)'
    call lineout makefile, ''
    call lineout makefile, '$(obj_dir)\$(dllname).res : $(rc_dir)\$(dllname).rc' iconlist
    call lineout makefile, '    @cd $(rc_dir)'
    call lineout makefile, '    rc -r $[*.rc $(obj_dir)\$[&.res'
    call lineout makefile, '    @cd $(main_dir)'
    call lineout makefile, ''
    call lineout makefile, 'props.obj : c\props.c' prplist
    call lineout makefile, ''
    call lineout makefile, ''
    
    return

/*
 * Erase
 */

Erase:
    file = arg(1)
    if( stream( file, 'c', 'query exists' ) \= '' )then do
        address cmd '@del' file
    end
    return