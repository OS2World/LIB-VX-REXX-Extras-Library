/**/
"set vxversion=210"
"set vxdllname=VROBJEX"
"set vxsom=SOM1"
if value( "VXCOMPILER", ,"OS2ENVIRONMENT") = "" then "set vxcompiler=CSET"
if value( "VXODK", ,"OS2ENVIRONMENT") = "" then "set vxodk=E:\DEVELOPMENT\VXODK\"
if value( "TOOLKIT", ,"OS2ENVIRONMENT") = "" then "set toolkit=E:\DEVELOPMENT\TOOLKT21"
if value( "WATCOM", ,"OS2ENVIRONMENT") = "" then "set watcom=D:\Dev\WATCOM"
if value( "IBMC", ,"OS2ENVIRONMENT") = "" then "set ibmc=E:\DEVELOPMENT\CSET21"


/*
 * Settings -- Set up environment variables for compiler etc.
 */

vxodk = value( 'VXODK',, 'OS2ENVIRONMENT' )
if( vxodk = '' )then do
    say "Please enter a value for the VXODK environment variable.  It should"
    say "point to the directory where the VX-REXX ODK is installed, as in:"
    say "      C:\VXODK"
    say "Or enter 'quit' to abort:"
    pull vxodk
    if( vxodk = 'QUIT' )then exit 32000
    if( right( vxodk, 1 ) \= '\' )then do
	vxodk = vxodk || '\'
    end
    call value 'VXODK', vxodk, 'OS2ENVIRONMENT'
    call value "PATH", Value( "PATH",,"OS2ENVIRONMENT")";"vxodk"bin", "OS2ENVIRONMENT"
end

toolkit = value( 'TOOLKIT',, 'OS2ENVIRONMENT' )
if( toolkit = '' )then do
    say "Please enter a value for the TOOLKIT environment variable.  It should"
    say "point to the directory where the OS/2 Toolkit is installed, as in:"
    say "      C:\TOOLKT20"
    say "Or enter 'quit' to abort:"
    pull toolkit
    if( toolkit = 'QUIT' )then exit 32000
    call value 'TOOLKIT', toolkit, 'OS2ENVIRONMENT'
end

if value( "TKT2_ENV", ,"OS2ENVIRONMENT") = "" then do
    call value "TKT2_ENV", "1", "OS2ENVIRONMENT"
    call value "PATH",    toolkit"\os2bin;"                                          ||Value("PATH",,   "OS2ENVIRONMENT"), "OS2ENVIRONMENT"
    call value "LIB",     toolkit"\os2lib;"                                          ||Value("LIB",,    "OS2ENVIRONMENT"), "OS2ENVIRONMENT"
    call value "INCLUDE", toolkit"\c\os2h;"toolkit"\c\os2h\vdd;"toolkit"\asm\os2inc;"||Value("INCLUDE",,"OS2ENVIRONMENT"), "OS2ENVIRONMENT"
end
beginlib = toolkit'\dll;'

compiler = translate( value( "VXCOMPILER", ,"OS2ENVIRONMENT" ) )
if( compiler = 'WATCOM' )then do
    watcom = value( 'WATCOM',, 'OS2ENVIRONMENT' )
    if( watcom = '' )then do
        say "Please enter a value for the WATCOM environment variable.  It should"
        say "point to the directory where WATCOM C/C++ is installed, as in:"
        say "      C:\WATCOM"
        say "Or enter 'quit' to abort:"
        pull watcom
        if( watcom = 'QUIT' )then exit 32000
        call value 'WATCOM', watcom, 'OS2ENVIRONMENT'
        call value "PATH", Value( "PATH",,"OS2ENVIRONMENT")";"watcom"\bin", "OS2ENVIRONMENT"
    end
end; else do
    ibmc = value( 'IBMC',, 'OS2ENVIRONMENT' )
    if( ibmc = '' )then do
        say "Please enter a value for the IBMC environment variable.  It should"
        say "point to the directory where CSet is installed, as in:"
        say "      C:\IBMCPP"
        say "Or enter 'quit' to abort:"
        pull ibmc
        if( ibmc = 'QUIT' )then exit 32000
        call value 'IBMC', ibmc, 'OS2ENVIRONMENT'
    end
    beginlib=beginlib||ibmc"\dll;"
    if value( "CSET_ENV",,"OS2ENVIRONMENT") = "" then do
        call value "CSET_ENV", "1", "OS2ENVIRONMENT"
        call value "PATH",    ibmc"\bin;"                          ||Value("PATH",,   "OS2ENVIRONMENT"), "OS2ENVIRONMENT"
        call value "DPATH",   ibmc"\locale;"ibmc"\help;"ibmc"\sys;"||Value("DPATH",,  "OS2ENVIRONMENT"), "OS2ENVIRONMENT"
        call value "LIB",     ibmc"\lib;"                          ||Value("LIB",,    "OS2ENVIRONMENT"), "OS2ENVIRONMENT"
        call value "INCLUDE", ibmc"\include;"ibmc"\ibmclass;"      ||Value("INCLUDE",,"OS2ENVIRONMENT"), "OS2ENVIRONMENT"
    end
end

"set beginlibpath="beginlib

exit 0

