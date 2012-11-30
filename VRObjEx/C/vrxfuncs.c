/******************************************************************************
 * VX-REXX Extras Library, REXX functions.                                    *
 * (C) 2010-2012 Alex Taylor.                                                 *
 *                                                                            *
 * LICENSE:                                                                   *
 *                                                                            *
 *   Redistribution and use in source and binary forms, with or without       *
 *   modification, are permitted provided that the following conditions are   *
 *   met:                                                                     *
 *                                                                            *
 *   1. Redistributions of source code must retain the above copyright        *
 *      notice, this list of conditions and the following disclaimer.         *
 *                                                                            *
 *   2. Redistributions in binary form must reproduce the above copyright     *
 *      notice, this list of conditions and the following disclaimer in the   *
 *      documentation and/or other materials provided with the distribution.  *
 *                                                                            *
 *   3. The name of the author may not be used to endorse or promote products *
 *      derived from this software without specific prior written permission. *
 *                                                                            *
 *   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR     *
 *   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED           *
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE   *
 *   DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,       *
 *   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES       *
 *   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR       *
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)       *
 *   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,      *
 *   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN *
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE          *
 *   POSSIBILITY OF SUCH DAMAGE.                                              *
 *                                                                            *
 ******************************************************************************/

#define INCL_DOSPROCESS
#define INCL_DOSERRORS
#define INCL_RXSHV
#define INCL_RXFUNC
#define INCL_PM
#define INCL_WIN

#include "vxrexx.h"
#include "vxfuncs.h"

// #ifndef OS2_INCLUDED
//     #include <os2.h>
// #endif
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// #include <rexxsaa.h>
#include <bseerr.h>

#include "dlgids.h"
#include "../version.h"

// CONSTANTS

#define SZ_LIBRARY_NAME         "VROBJEX"       // Name of this library
#define SZ_ERROR_NAME           "VRXERROR"      // REXX variable used to store error codes

#define US_REXXSTR_MAXZ         256             // Maximum length of a RXSTRING without reallocation
#define US_COMPOUND_MAXZ        250             // Maximum length of a compound variable
#define US_INTEGER_MAXZ         12              // Maximum length of an integer string
#define US_STEM_MAXZ          ( US_COMPOUND_MAXZ - US_INTEGER_MAXZ )  // Maximum length of a stem
#define US_ERRSTR_MAXZ          250             // Maximum length of an error string
#define US_COLOUR_MAXZ          12              // Maximum length of a colour string

// Messages used by the colour-wheel dialog
#define CWN_CHANGE              0x601
#define CWM_SETCOLOUR           0x602


// TYPEDEFS

typedef struct CWPARAM {
    USHORT  cb;
    RGB     rgb;
    PSZ     pszTitle;
    BOOL    fCancel;
} CWPARAM;

typedef struct CWDATA {
    USHORT  updatectl;
    HWND    hwndCol;
    HWND    hwndSpinR;
    HWND    hwndSpinG;
    HWND    hwndSpinB;
    RGB     *rgb;
    RGB     rgbold;
    PBOOL   pfCancel;
} CWDATA;


// GLOBALS

// List of functions to be registered by VRXLoadFuncs
static PSZ RxFunctionTbl[] = {
    "VRXColorDialog",
    "VRXColourDialog",
    "VRXDirectoryDialog",
    "VRXDropFuncs",
    "VRXGetClipboardText",
    "VRXPutClipboardText",
    "VRXVersion"
};


// FUNCTION DECLARATIONS

// Exported REXX functions
RexxFunctionHandler VRXColorDialog;
RexxFunctionHandler VRXColourDialog;
RexxFunctionHandler VRXDirectoryDialog;
RexxFunctionHandler VRXDropFuncs;
RexxFunctionHandler VRXGetClipboardText;
RexxFunctionHandler VRXLoadFuncs;
RexxFunctionHandler VRXPutClipboardText;
RexxFunctionHandler VRXVersion;


// Private internal functions
MRESULT EXPENTRY ClrDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY DirDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
BOOL             SaveResultString( PRXSTRING prsResult, PCH pchBytes, ULONG ulBytes );
void             WriteStemElement( PSZ pszStem, ULONG ulIndex, PSZ pszValue );
void             WriteErrorCode( ULONG ulError, PSZ pszContext );



/* ------------------------------------------------------------------------- *
 * VRXLoadFuncs                                                              *
 *                                                                           *
 * Should be self-explanatory...                                             *
 *                                                                           *
 * REXX ARGUMENTS:    None                                                   *
 * REXX RETURN VALUE: ""                                                     *
 * ------------------------------------------------------------------------- */
ULONG APIENTRY VRXLoadFuncs( PSZ pszName, ULONG argc, RXSTRING argv[], PSZ pszQueue, PRXSTRING prsResult )
{
    int entries,
        i;

    // Reset the error indicator
    WriteErrorCode( 0, NULL );

    if ( argc > 0 ) return ( 40 );
    entries = sizeof(RxFunctionTbl) / sizeof(PSZ);
    for ( i = 0; i < entries; i++ )
        RexxRegisterFunctionDll( RxFunctionTbl[i], SZ_LIBRARY_NAME, RxFunctionTbl[i] );

    MAKERXSTRING( *prsResult, "", 0 );
    return ( 0 );
}


/* ------------------------------------------------------------------------- *
 * VRXDropFuncs                                                              *
 *                                                                           *
 * Ditto.                                                                    *
 *                                                                           *
 * REXX ARGUMENTS:    None                                                   *
 * REXX RETURN VALUE: ""                                                     *
 * ------------------------------------------------------------------------- */
ULONG APIENTRY VRXDropFuncs( PSZ pszName, ULONG argc, RXSTRING argv[], PSZ pszQueue, PRXSTRING prsResult )
{
    int entries,
        i;

    // Reset the error indicator
    WriteErrorCode( 0, NULL );

    if ( argc > 0 ) return ( 40 );
    entries = sizeof(RxFunctionTbl) / sizeof(PSZ);
    for ( i = 0; i < entries; i++ )
        RexxDeregisterFunction( RxFunctionTbl[i] );

    MAKERXSTRING( *prsResult, "", 0 );
    return ( 0 );
}


/* ------------------------------------------------------------------------- *
 * VRXVersion                                                                *
 *                                                                           *
 * Returns the current VROBJEX library version.                              *
 *                                                                           *
 * REXX ARGUMENTS:    None                                                   *
 * REXX RETURN VALUE: Current version in the form "major.minor.refresh"      *
 * ------------------------------------------------------------------------- */
ULONG APIENTRY VRXVersion( PSZ pszName, ULONG argc, RXSTRING argv[], PSZ pszQueue, PRXSTRING prsResult )
{
    USHORT usMaj, usMin, usRef;
    CHAR   szVersion[ 12 ];

    // Reset the error indicator
    WriteErrorCode( 0, NULL );

    if ( argc > 0 ) return ( 40 );
    usMaj = VERSION / 100;
    usMin = ( VERSION % 100 ) / 10;
    usRef = ( VERSION % 100 ) % 10;
    sprintf( szVersion, "%d.%d.%d", usMaj, usMin, usRef );

    MAKERXSTRING( *prsResult, szVersion, strlen(szVersion) );
    return ( 0 );
}


/* ------------------------------------------------------------------------- *
 * VRXPutClipboardText                                                       *
 *                                                                           *
 * Write data to the clipboard in plain-text format.  Specifying either no   *
 * value or an empty string in the first argument will simply clear the      *
 * clipboard.                                                                *
 *                                                                           *
 * REXX ARGUMENTS:                                                           *
 *   1. String to be written to the clipboard.  (DEFAULT: "")                *
 *   2. Flag indicating whether other clipboard formats should be cleared:   *
 *        1 or Y = call WinEmptyClipbrd() before writing data  (DEFAULT)     *
 *        0 or N = leave clipboard data not in CF_TEXT format intact         *
 *                                                                           *
 * REXX RETURN VALUE:  1 on success, 0 on failure                            *
 * ------------------------------------------------------------------------- */
ULONG APIENTRY VRXPutClipboardText( PSZ pszName, ULONG argc, RXSTRING argv[], PSZ pszQueue, PRXSTRING prsResult )
{
    PSZ     pszShareMem;            // text in clipboard
    ULONG   ulRC     = 0,           // return code
            ulBytes  = 0,           // size of input string
            ulPType  = 0;           // process-type flag
    BOOL    fEmptyCB = TRUE,        // call WinEmptyClipbrd() first?
            fHabTerm = TRUE;        // terminate HAB ourselves?
    HAB     hab;                    // anchor-block handle (for Win*)
    HMQ     hmq;                    // message-queue handle
    PPIB    ppib;                   // process information block
    PTIB    ptib;                   // thread information block


    // Reset the error indicator
    WriteErrorCode( 0, NULL );

    // Make sure we have at least one valid argument (the input string)
    if ( argc < 1  || ( !RXVALIDSTRING(argv[0]) )) return ( 40 );

    // The second argument is optional, but must be correct if specified
    if ( argc >= 2 ) {
        // second argument: flag to clear clipboard (Y/N, but also accept 0/1)
        if ( RXVALIDSTRING(argv[1]) ) {
            strupr( argv[1].strptr );
            if ( strcspn(argv[1].strptr, "YN01") > 0 ) return ( 40 );
            switch ( argv[1].strptr[0] ) {
                case 'N':
                case '0': fEmptyCB = FALSE; break;
                case 'Y':
                case '1':
                default : fEmptyCB = TRUE;  break;
            }
        } else fEmptyCB = TRUE;
    }

    // Initialize the PM API
    DosGetInfoBlocks( &ptib, &ppib );
    ulPType = ppib->pib_ultype;
    ppib->pib_ultype = 3;
    hab = WinInitialize( 0 );
    if ( !hab ) {
        fHabTerm = FALSE;
        hab = 1;
    }

    /* Try to create a message-queue if one doesn't exist.  Don't worry if it
     * fails, because the caller may already have created one.
     */
    hmq = WinCreateMsgQueue( hab, 0 );

    // Place the string on the clipboard as CF_TEXT
    ulRC = WinOpenClipbrd( hab );
    if ( ulRC ) {

        if ( fEmptyCB ) WinEmptyClipbrd( hab );

        ulBytes = argv[0].strlength + 1;
        ulRC = DosAllocSharedMem( (PVOID) &pszShareMem, NULL, ulBytes,
                                  PAG_READ | PAG_WRITE | PAG_COMMIT | OBJ_GIVEABLE );
        if ( ulRC == 0 ) {
            memset( pszShareMem, 0, ulBytes );
            strncpy( pszShareMem, argv[0].strptr , ulBytes - 1 );
            if ( ! WinSetClipbrdData( hab, (ULONG) pszShareMem, CF_TEXT, CFI_POINTER ))
                WriteErrorCode( ERRORIDERROR(WinGetLastError(hab)), "WinSetClipbrdData");
            else
                MAKERXSTRING( *prsResult, "", 0 );
        } else {
            WriteErrorCode( ulRC, "DosAllocSharedMem");
            MAKERXSTRING( *prsResult, "", 0 );
        }

        WinCloseClipbrd( hab );
    } else {
        WriteErrorCode( ulRC, "WinOpenClipbrd");
        MAKERXSTRING( *prsResult, "", 0 );
    }

    if ( hmq != NULLHANDLE ) WinDestroyMsgQueue( hmq );
    if ( fHabTerm ) WinTerminate( hab );
    ppib->pib_ultype = ulPType;

    return ( 0 );
}


/* ------------------------------------------------------------------------- *
 * VRXGetClipboardText                                                       *
 *                                                                           *
 * Retrieve a plain-text string from the clipboard if one is available.      *
 *                                                                           *
 * REXX ARGUMENTS:                                                           *
 *   None.                                                                   *
 *                                                                           *
 * REXX RETURN VALUE: The retrieved clipboard string                         *
 * ------------------------------------------------------------------------- */
ULONG APIENTRY VRXGetClipboardText( PSZ pszName, ULONG argc, RXSTRING argv[], PSZ pszQueue, PRXSTRING prsResult )
{
    PSZ     pszClipText,            // pointer to clipboard data
            pszLocalText;           // our copy of the data (to return)
    ULONG   ulRC     = 0,           // return code
            ulBytes  = 0,           // size in bytes of output string
            ulPType  = 0;           // process-type flag
    BOOL    fHabTerm = TRUE;        // terminate HAB ourselves?
    HAB     hab;                    // anchor-block handle (for Win*)
    HMQ     hmq;                    // message-queue handle
    PPIB    ppib;                   // process information block
    PTIB    ptib;                   // thread information block


    // Reset the error indicator
    WriteErrorCode( 0, NULL );

    // Initialize the PM API
    DosGetInfoBlocks( &ptib, &ppib );
    ulPType = ppib->pib_ultype;
    ppib->pib_ultype = 3;
    hab = WinInitialize( 0 );
    if ( !hab ) {
        fHabTerm = FALSE;
        hab = 1;
    }

    /* Try to create a message-queue if one doesn't exist.  Don't worry if it
     * fails, because the caller may already have created one.
     */
    hmq = WinCreateMsgQueue( hab, 0 );

    // Open the clipboard
    ulRC = WinOpenClipbrd( hab );
    if ( ulRC ) {

        // Read plain text from the clipboard, if available
        if (( pszClipText = (PSZ) WinQueryClipbrdData( hab, CF_TEXT )) != NULL ) {

            ulBytes = strlen( pszClipText ) + 1;
            if (( pszLocalText = (PSZ) malloc( ulBytes )) != NULL ) {
                memset( pszLocalText, 0, ulBytes );
                strncpy( pszLocalText, pszClipText, ulBytes - 1 );
                if ( ! SaveResultString( prsResult, pszLocalText, ulBytes - 1 )) {
                    MAKERXSTRING( *prsResult, "", 0 );
                }
                free( pszLocalText );
            } else {
                WriteErrorCode( ERROR_NOT_ENOUGH_MEMORY, "malloc");
                MAKERXSTRING( *prsResult, "", 0 );
            }

        } else {
            // Either no text exists, or clipboard is not readable
            MAKERXSTRING( *prsResult, "", 0 );
        }

        WinCloseClipbrd( hab );
    } else {
        WriteErrorCode( ulRC, "WinOpenClipbrd");
        MAKERXSTRING( *prsResult, "", 0 );
    }

    if ( hmq != NULLHANDLE ) WinDestroyMsgQueue( hmq );
    if ( fHabTerm ) WinTerminate( hab );

    ppib->pib_ultype = ulPType;

    return ( 0 );
}


/* ------------------------------------------------------------------------- *
 * VRXColourDialog                                                           *
 *                                                                           *
 * Open a colour-wheel dialog.                                               *
 *                                                                           *
 * REXX ARGUMENTS:                                                           *
 *   1. VX-REXX ID or handle of the owner window.  (DEFAULT: HWND_DESKTOP)   *
 *   2. Initial colour value string.  Must be either "#RRGGBB" where R, G, B *
 *      are hex values, or "r,g,b" where r, g, b are decimal values.         *
 *      (DEFAULT: 255,255,255)                                               *
 *   3. Title for the dialog.  (DEFAULT: "")                                 *
 *                                                                           *
 * REXX RETURN VALUE:                                                        *
 *   - "" if cancelled or if an error occurred                               *
 *   - "#RRGGBB" hex string if parameter 2 was provided in the same format   *
 *   - "r,g,b" decimal string otherwise                                      *
 * ------------------------------------------------------------------------- */
ULONG APIENTRY VRXColourDialog( PSZ pszName, ULONG argc, RXSTRING argv[], PSZ pszQueue, PRXSTRING prsResult )
{
    SOMAny  *object = NULL;           // SOM object of REXX window
    HWND    hwnd    = NULLHANDLE;     // handle of owner window
    HWND    hwndDlg = NULLHANDLE;     // handle of colour dialog
    CWPARAM cwparam = {0};            // colour values
    MQINFO  mqinfo;                   // message-queue info
    HAB     hab = NULLHANDLE;         // anchor-block handle (for Win*)
    HMQ     hmq = NULLHANDLE;         // message-queue handle
    HLIB    hlib;                     // handle to WPCONFIG.DLL
    HMODULE hMod = NULLHANDLE;        // our own module handle
    TID     tid;                      // current thread ID
    PPIB    ppib;                     // process information block
    PTIB    ptib;                     // thread information block
    ULONG   ulPType = 0;              // process-type identifier
    BOOL    fRGB    = FALSE,          // colour specified in hex RGB format?
            fNewHab = FALSE,          // did we create a new HAB?
            fHMQ;                     // does thread have a message queue?
    int     R, G, B;                  // input colour byte values
    CHAR    szBuf[ US_COLOUR_MAXZ ];  // buffer for returned string
    APIRET  rc = 0;

    // Reset the error indicator
    WriteErrorCode( 0, NULL );

    DosGetInfoBlocks( &ptib, &ppib );
    if ( !ptib || !ppib ) {
        WriteErrorCode( 0xFFFF, "DosGetInfoBlocks");
        MAKERXSTRING( *prsResult, "", 0 );
        return 0;
    }
    ulPType = ppib->pib_ultype;

    // Make sure the owner window (if specified) is valid, and get its HWND
    if (( argc >= 1 ) && ( RXVALIDSTRING(argv[0]) )) {
        // VRRXStringToSOMObject requires the current thread ID
        tid = ptib->tib_ptib2->tib2_ultid;
        if ( VRRXStringToSOMObject( &(argv[0]), &object, tid ) && object ) {
            hwnd = VRMapObjectToWindow( object );
            if ( !hwnd ) return 40;
        }
        else return 40;
    } else hwnd = HWND_DESKTOP;

    // Get the initial colour value
    if (( argc >= 2 ) && ( RXVALIDSTRING(argv[1]) )) {
        strupr( argv[1].strptr );
        if ( argv[1].strptr[0] == '#') {
            if ( sscanf( argv[1].strptr,
                         "#%02X%02X%02X", &R, &G, &B ) != 3 ) return 40;
            fRGB = TRUE;
        } else {
            if ( sscanf( argv[1].strptr,
                         "(%u,%u,%u)", &R, &G, &B ) != 3 ) return 40;
        }
        cwparam.rgb.bRed   = R;
        cwparam.rgb.bGreen = G;
        cwparam.rgb.bBlue  = B;
    }
    else {
        cwparam.rgb.bRed   = 0xFF;
        cwparam.rgb.bGreen = 0xFF;
        cwparam.rgb.bBlue  = 0xFF;
    }

    if (( argc >= 3 ) && ( RXVALIDSTRING(argv[2]) ))
        cwparam.pszTitle = (PSZ) argv[2].strptr;
    else
        cwparam.pszTitle = "";

    cwparam.fCancel = FALSE;
    cwparam.cb = sizeof( CWPARAM );

    /* Now make sure we're running in PM mode, and we have a HAB and HMQ.
    */
    if ( ulPType != 3 ) {
        ppib->pib_ultype = 3;
        hab = WinInitialize( 0 );
        hmq = WinCreateMsgQueue( hab, 0 );
        fNewHab = TRUE;
    }
    else {
        hab = WinQueryAnchorBlock( hwnd );
        if ( !hab ) {
            hab = WinInitialize( 0 );
            fNewHab = TRUE;
        }
        fHMQ = WinQueryQueueInfo( HMQ_CURRENT, &mqinfo, sizeof(mqinfo) );
        if ( !fHMQ )
            hmq = WinCreateMsgQueue( hab, 0 );
    }
    if ( !hab ) {
        WriteErrorCode( 0xFFFF, "WinInitialize");
        MAKERXSTRING( *prsResult, "", 0 );
        goto cleanup;
    }

    hlib = WinLoadLibrary( hab, "WPCONFIG.DLL");
    if ( !hlib ) {
        WriteErrorCode( ERRORIDERROR(WinGetLastError(hab)), "WinLoadLibrary");
        MAKERXSTRING( *prsResult, "", 0 );
        goto cleanup;
    }
    hMod = (HMODULE) WinLoadLibrary( hab, SZ_LIBRARY_NAME );
    if ( !hMod ) {
        WriteErrorCode( ERRORIDERROR(WinGetLastError(hab)), "WinLoadLibrary");
        WinDeleteLibrary( hab, hlib );
        MAKERXSTRING( *prsResult, "", 0 );
        goto cleanup;
    }

    hwndDlg = WinLoadDlg( HWND_DESKTOP, hwnd, ClrDlgProc, hMod, ID_CLRDLG, &cwparam );
    if ( !hwndDlg ) {
        WriteErrorCode( ERRORIDERROR(WinGetLastError(hab)), "WinLoadDlg");
        WinDeleteLibrary( hab, hlib );
        WinDeleteLibrary( hab, hMod );
        MAKERXSTRING( *prsResult, "", 0 );
        goto cleanup;
    }
    WinProcessDlg( hwndDlg );
    WinDestroyWindow( hwndDlg );

    if ( cwparam.fCancel ) {
        MAKERXSTRING( *prsResult, "", 0 );
    } else {
        if ( fRGB )
            sprintf( szBuf, "#%02X%02X%02X", cwparam.rgb.bRed, cwparam.rgb.bGreen, cwparam.rgb.bBlue );
        else
            sprintf( szBuf, "(%u,%u,%u)", cwparam.rgb.bRed, cwparam.rgb.bGreen, cwparam.rgb.bBlue );
        SaveResultString( prsResult, szBuf, strlen(szBuf) );
    }
    WinDeleteLibrary( hab, hlib );
    WinDeleteLibrary( hab, hMod );

cleanup:
    if ( hmq != NULLHANDLE ) WinDestroyMsgQueue( hmq );
    if ( fNewHab ) WinTerminate( hab );
    ppib->pib_ultype = ulPType;

    return 0;
}

ULONG APIENTRY VRXColorDialog( PSZ pszName, ULONG argc, RXSTRING argv[], PSZ pszQueue, PRXSTRING prsResult )
{
    return VRXColourDialog( pszName, argc, argv, pszQueue, prsResult );
}



/* ------------------------------------------------------------------------- *
 * VRXDirectoryDialog                                                        *
 *                                                                           *
 * Open a directory selection dialog.                                        *
 *                                                                           *
 * REXX ARGUMENTS:                                                           *
 *   1. VX-REXX ID or handle of the owner window.  (DEFAULT: HWND_DESKTOP)   *
 *   2. Initial directory string, or "" for the current working directory.   *
 *      (DEFAULT: "")                                                        *
 *   3. Title for the dialog.  (DEFAULT: "")                                 *
 *                                                                           *
 * REXX RETURN VALUE:                                                        *
 *   - "" if cancelled or if an error occurred                               *
 *   - pathname of selected directory otherwise                              *
 * ------------------------------------------------------------------------- */
ULONG APIENTRY VRXDirectoryDialog( PSZ pszName, ULONG argc, RXSTRING argv[], PSZ pszQueue, PRXSTRING prsResult )
{
    SOMAny  *object = NULL;           // SOM object of REXX window
    HWND    hwnd    = NULLHANDLE;     // handle of owner window
    HWND    hwndDlg = NULLHANDLE;     // handle of custom file dialog
    FILEDLG fd      = {0};            // PM file dialog structure
    HAB     hab     = NULLHANDLE;     // anchor-block handle (for Win*)
    HMQ     hmq     = NULLHANDLE;     // message-queue handle
    MQINFO  mqinfo;                   // message-queue info
    TID     tid;                      // current thread ID
    PPIB    ppib;                     // process information block
    PTIB    ptib;                     // thread information block
    ULONG   ulPType = 0;              // process-type identifier
    BOOL    fNewHab = FALSE,          // did we create a new HAB?
            fHMQ;                     // does thread have a message queue?
    APIRET  rc = 0;


    // Reset the error indicator
    WriteErrorCode( 0, NULL );

    DosGetInfoBlocks( &ptib, &ppib );
    if ( !ptib || !ppib ) {
        WriteErrorCode( 0xFFFF, "DosGetInfoBlocks");
        MAKERXSTRING( *prsResult, "", 0 );
        return 0;
    }
    ulPType = ppib->pib_ultype;

    // Make sure the owner window (if specified) is valid, and get its HWND
    if (( argc >= 1 ) && ( RXVALIDSTRING(argv[0]) )) {
        // VRRXStringToSOMObject requires the current thread ID
        tid = ptib->tib_ptib2->tib2_ultid;
        if ( VRRXStringToSOMObject( &(argv[0]), &object, tid ) && object ) {
            hwnd = VRMapObjectToWindow( object );
            if ( !hwnd ) return 40;
        }
        else return 40;
    } else hwnd = HWND_DESKTOP;

    // Get the initial directory
    if (( argc >= 2 ) && ( RXVALIDSTRING(argv[1]) )) {
        strncpy( fd.szFullFile, RXSTRPTR( argv[1] ), RXSTRLEN( argv[1] ));
        if ( fd.szFullFile[ RXSTRLEN( argv[1] ) - 1 ] != '\\')
            strncat( fd.szFullFile, "\\", CCHMAXPATH-1 );
    }

    // Get the dialog title
    if (( argc >= 3 ) && ( RXVALIDSTRING(argv[2]) ))
        fd.pszTitle = (PSZ) argv[2].strptr;
    else
        fd.pszTitle = "";

    fd.cbSize  = sizeof( FILEDLG );
    fd.fl      = FDS_CENTER | FDS_CUSTOM | FDS_OPEN_DIALOG;
    fd.lReturn = DID_CANCEL;
    fd.pfnDlgProc = DirDlgProc;

    /* Now make sure we're running in PM mode, and we have a HAB and HMQ.
     */
    if ( ulPType != 3 ) {
        ppib->pib_ultype = 3;
        hab = WinInitialize( 0 );
        hmq = WinCreateMsgQueue( hab, 0 );
        fNewHab = TRUE;
    }
    else {
        hab = WinQueryAnchorBlock( hwnd );
        if ( !hab ) {
            hab = WinInitialize( 0 );
            fNewHab = TRUE;
        }
        fHMQ = WinQueryQueueInfo( HMQ_CURRENT, &mqinfo, sizeof(mqinfo) );
        if ( !fHMQ )
            hmq = WinCreateMsgQueue( hab, 0 );
    }
    if ( !hab ) {
        WriteErrorCode( 0xFFFF, "WinInitialize");
        MAKERXSTRING( *prsResult, "", 0 );
        goto cleanup;
    }

    // Get a module handle to ourself so we can load the dialog resource
    fd.hMod = (HMODULE) WinLoadLibrary( hab, SZ_LIBRARY_NAME );
    if ( !fd.hMod ) {
        WriteErrorCode( ERRORIDERROR(WinGetLastError(hab)), "WinLoadLibrary");
        MAKERXSTRING( *prsResult, "", 0 );
        goto cleanup;
    }
    fd.usDlgId = IDD_DIRDLG;

    // Load and process our custom file dialog
    hwndDlg = WinFileDlg( HWND_DESKTOP, hwnd, &fd );
    if ( !hwndDlg ) {
        WriteErrorCode( ERRORIDERROR(WinGetLastError(hab)), "WinFileDlg");
        WinDeleteLibrary( hab, fd.hMod );
        MAKERXSTRING( *prsResult, "", 0 );
        goto cleanup;
    }

    // Now save the return value
    if ( fd.lReturn == DID_CANCEL ) {
        MAKERXSTRING( *prsResult, "", 0 );
    }
    else {
        SaveResultString( prsResult, fd.szFullFile, strlen( fd.szFullFile ));
    }
    WinDeleteLibrary( hab, fd.hMod );

cleanup:
    if ( hmq != NULLHANDLE ) WinDestroyMsgQueue( hmq );
    if ( fNewHab ) WinTerminate( hab );
    ppib->pib_ultype = ulPType;

    return 0;
}


/* ------------------------------------------------------------------------- *
 * ClrDlgProc                                                                *
 *                                                                           *
 * Dialog procedure for colour dialog (private function).                    *
 * ------------------------------------------------------------------------- */
MRESULT EXPENTRY ClrDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    CWDATA  *cwdata;
    CWPARAM *cwparam;
    HWND    hwndSpin;
    ULONG   newval;
    SWP     swp;
    LONG    cxscr, cyscr, x, y;

    cwdata = (CWDATA *) WinQueryWindowULong (hwnd, QWL_USER);
    switch(msg)
    {
    case WM_INITDLG:
        cwparam = (CWPARAM *) mp2;
        if (!(cwdata = malloc(sizeof(CWDATA))) ||
            !mp2 || !(cwdata->rgb = &(cwparam->rgb)))
        {
            WinPostMsg (hwnd, WM_CLOSE, MPVOID, MPVOID);
            break;
        }
        cwdata->pfCancel = &(cwparam->fCancel);
        WinSetWindowULong (hwnd, QWL_USER, (ULONG) cwdata);
        if (cwparam->pszTitle)
            WinSetWindowText (hwnd, cwparam->pszTitle);
        cwdata->rgbold = *cwdata->rgb;
        cwdata->hwndCol = WinWindowFromID (hwnd, ID_COL);
        cwdata->hwndSpinR = WinWindowFromID (hwnd, ID_SPINR);
        cwdata->hwndSpinG = WinWindowFromID (hwnd, ID_SPING);
        cwdata->hwndSpinB = WinWindowFromID (hwnd, ID_SPINB);
        cwdata->updatectl = FALSE;
        WinSendMsg (cwdata->hwndSpinR, SPBM_SETLIMITS,
                    MPFROMSHORT(255), MPFROMSHORT(0));
        WinSendMsg (cwdata->hwndSpinG, SPBM_SETLIMITS,
                    MPFROMSHORT(255), MPFROMSHORT(0));
        WinSendMsg (cwdata->hwndSpinB, SPBM_SETLIMITS,
                    MPFROMSHORT(255), MPFROMSHORT(0));
        WinSendMsg (hwnd, CWN_CHANGE,
                    MPFROMLONG(*((ULONG *) cwdata->rgb) & 0xFFFFFF), MPVOID);
        WinSendMsg (cwdata->hwndCol, CWM_SETCOLOUR,
                    MPFROMLONG(*((ULONG *) cwdata->rgb) & 0xFFFFFF), MPVOID);

        // centre the dialog on screen
        if ( WinQueryWindowPos( hwnd, &swp )) {
            cxscr = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
            cyscr = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );
            x = ( cxscr - swp.cx ) / 2;
            y = ( cyscr - swp.cy ) / 2;
            WinSetWindowPos( hwnd, HWND_TOP, x, y, 0, 0,
                             SWP_MOVE | SWP_SHOW | SWP_ACTIVATE );
        }
        break;

    case WM_COMMAND:
        switch(SHORT1FROMMP(mp1))
        {
            case ID_UNDO:
                WinSendMsg (hwnd, CWN_CHANGE,
                            MPFROMLONG(*((ULONG *) &cwdata->rgbold) & 0xFFFFFF),
                            MPVOID);
                WinSendMsg (cwdata->hwndCol, CWM_SETCOLOUR,
                            MPFROMLONG(*((ULONG *) &cwdata->rgbold) & 0xFFFFFF),
                            MPVOID);
                return ((MPARAM) 0);

            case DID_CANCEL:
                WinSendMsg (hwnd, CWN_CHANGE,
                            MPFROMLONG(*((ULONG *) &cwdata->rgbold) & 0xFFFFFF),
                            MPVOID);
                WinSendMsg (cwdata->hwndCol, CWM_SETCOLOUR,
                            MPFROMLONG(*((ULONG *) &cwdata->rgbold) & 0xFFFFFF),
                            MPVOID);
                *(cwdata->pfCancel) = TRUE;
                break;
        }
        break;

    case CWN_CHANGE:
        *cwdata->rgb = *((RGB *) &mp1);
        cwdata->updatectl = FALSE;
        WinSendMsg (cwdata->hwndSpinR, SPBM_SETCURRENTVALUE,
                    MPFROMSHORT(cwdata->rgb->bRed), MPVOID);
        WinSendMsg (cwdata->hwndSpinG, SPBM_SETCURRENTVALUE,
                    MPFROMSHORT(cwdata->rgb->bGreen), MPVOID);
        WinSendMsg (cwdata->hwndSpinB, SPBM_SETCURRENTVALUE,
                    MPFROMSHORT(cwdata->rgb->bBlue), MPVOID);
        cwdata->updatectl = TRUE;
        break;

    case WM_CONTROL:
            switch(SHORT1FROMMP(mp1))
            {
                case ID_SPINR:
                case ID_SPING:
                case ID_SPINB:
                    hwndSpin = WinWindowFromID (hwnd, SHORT1FROMMP(mp1));
                    switch(SHORT2FROMMP(mp1))
                    {
                        case SPBN_CHANGE:
                        case SPBN_KILLFOCUS:
                            if (cwdata->updatectl)
                            {
                                WinSendMsg (hwndSpin, SPBM_QUERYVALUE,
                                            (MPARAM) &newval,
                                            MPFROM2SHORT(0, SPBQ_ALWAYSUPDATE));
                                switch(SHORT1FROMMP(mp1))
                                {
                                    case ID_SPINR:
                                        cwdata->rgb->bRed = (BYTE) newval;
                                        break;

                                    case ID_SPING:
                                        cwdata->rgb->bGreen = (BYTE) newval;
                                        break;

                                    case ID_SPINB:
                                        cwdata->rgb->bBlue = (BYTE) newval;
                                }

                                WinSendMsg (cwdata->hwndCol, CWM_SETCOLOUR,
                                            MPFROMLONG(*((ULONG *) cwdata->rgb) &
                                            0xFFFFFF), MPVOID);
                            }
                    }
            }
        break;

    case WM_DESTROY:
        free(cwdata);
    }

    return (WinDefDlgProc (hwnd, msg, mp1, mp2));
}


/* ------------------------------------------------------------------------- *
 * DirDlgProc                                                                *
 *                                                                           *
 * Dialog procedure for directory dialog (private function).                 *
 * ------------------------------------------------------------------------- */
MRESULT EXPENTRY DirDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    PFILEDLG pfd;
    ULONG    cch;
    MRESULT  mres;

    switch( msg ) {

        case WM_INITDLG:
            mres = WinDefFileDlgProc( hwnd, msg, mp1, mp2 );
            WinEnableControl( hwnd, DID_OK, TRUE );
            return mres;


        case WM_COMMAND:
            switch ( SHORT1FROMMP( mp1 )) {
                case DID_OK:
                    pfd = (PFILEDLG) WinQueryWindowULong( hwnd, QWL_USER );
                    cch = strlen( pfd->szFullFile );
                    if ( pfd->szFullFile[ cch-1 ] == '\\')
                        pfd->szFullFile[ cch-1 ] = '\0';
                    pfd->lReturn = DID_OK;
                    WinDismissDlg( hwnd, DID_OK );
                    return (MRESULT) FALSE;
            }
            break;


        case WM_CONTROL:
            switch ( SHORT2FROMMP( mp1 )) {
                case CBN_EFCHANGE:
                    pfd = (PFILEDLG) WinQueryWindowULong( hwnd, QWL_USER );
                    cch = strlen( pfd->szFullFile );
                    if (( pfd->szFullFile[ cch-1 ] == '\\') &&
                        ! (( cch == 3 ) && ( pfd->szFullFile[ 1 ] == ':')))
                        pfd->szFullFile[ cch-1 ] = '\0';
                    WinSetDlgItemText( hwnd, IDD_FULLNAME, pfd->szFullFile );
                    break;
            }

    }
    return WinDefFileDlgProc( hwnd, msg, mp1, mp2 );
}


/* ------------------------------------------------------------------------- *
 * SaveResultString                                                          *
 *                                                                           *
 * Writes new string contents to the specified RXSTRING, allocating any      *
 * additional memory that may be required.  If the string to be written has  *
 * zero length, nothing is done.                                             *
 *                                                                           *
 * ARGUMENTS:                                                                *
 *   PRXSTRING prsResult: Pointer to an existing RXSTRING for writing.       *
 *   PCH       pchBytes : The string contents to write to prsResult.         *
 *   ULONG     ulBytes  : The number of bytes in pchBytes to write.          *
 *                                                                           *
 * RETURNS: BOOL                                                             *
 *   TRUE if prsResult was successfully updated.  FALSE otherwise.           *
 * ------------------------------------------------------------------------- */
BOOL SaveResultString( PRXSTRING prsResult, PCH pchBytes, ULONG ulBytes )
{
    ULONG ulRC;
    PCH   pchNew;

    if ( ulBytes == 0 ) return ( FALSE );
    if ( ulBytes > 256 ) {
        // REXX provides 256 bytes by default; allocate more if necessary
        ulRC = DosAllocMem( (PVOID) &pchNew, ulBytes, PAG_WRITE | PAG_COMMIT );
        if ( ulRC != 0 ) {
            WriteErrorCode( ulRC, "DosAllocMem");
            return ( FALSE );
        }
        DosFreeMem( prsResult->strptr );
        prsResult->strptr = pchNew;
    }
    memcpy( prsResult->strptr, pchBytes, ulBytes );
    prsResult->strlength = ulBytes;

    return ( TRUE );
}


/* ------------------------------------------------------------------------- *
 * WriteStemElement                                                          *
 *                                                                           *
 * Creates a stem element (compound variable) in the calling REXX program    *
 * using the REXX shared variable pool interface.                            *
 *                                                                           *
 * ARGUMENTS:                                                                *
 *   PSZ   pszStem  : The name of the stem (before the '.')                  *
 *   ULONG ulIndex  : The number of the stem element (after the '.')         *
 *   PSZ   pszValue : The value to write to the compound variable.           *
 *                                                                           *
 * RETURNS: N/A                                                              *
 * ------------------------------------------------------------------------- */
void WriteStemElement( PSZ pszStem, ULONG ulIndex, PSZ pszValue )
{
    SHVBLOCK shvVar;                   // REXX shared variable pool block
    ULONG    ulRc;
    CHAR     szCompoundName[ US_COMPOUND_MAXZ ],
             szValue[ US_REXXSTR_MAXZ ];

    sprintf( szCompoundName, "%s.%d", pszStem, ulIndex );
    strncpy( szValue, pszValue, US_REXXSTR_MAXZ );
    MAKERXSTRING( shvVar.shvname,  szCompoundName, strlen(szCompoundName) );
    MAKERXSTRING( shvVar.shvvalue, szValue,        strlen(szValue) );
    shvVar.shvnamelen  = RXSTRLEN( shvVar.shvname );
    shvVar.shvvaluelen = RXSTRLEN( shvVar.shvvalue );
    shvVar.shvcode     = RXSHV_SYSET;
    shvVar.shvnext     = NULL;
    ulRc = RexxVariablePool( &shvVar );
    if ( ulRc > 1 )
        printf("Unable to set %s: rc = %d\n", shvVar.shvname.strptr, shvVar.shvret );

}


/* ------------------------------------------------------------------------- *
 * WriteErrorCode                                                            *
 *                                                                           *
 * Writes an error code to a special variable in the calling REXX program    *
 * using the REXX shared variable pool interface.  This is used to return    *
 * API error codes to the REXX program, since the REXX functions themselves  *
 * normally return string values.                                            *
 *                                                                           *
 * ARGUMENTS:                                                                *
 *   ULONG ulError   : The error code returned by the failing API call.      *
 *   PSZ   pszContext: A string describing the API call that failed.         *
 *                                                                           *
 * RETURNS: N/A                                                              *
 * ------------------------------------------------------------------------- */
void WriteErrorCode( ULONG ulError, PSZ pszContext )
{
    SHVBLOCK shvVar;                   // REXX shared variable pool block
    ULONG    ulRc;
    CHAR     szErrorText[ US_ERRSTR_MAXZ ];

    if ( pszContext == NULL )
        sprintf( szErrorText, (ulError? "0x%X" : "%X"), ulError );
    else
        sprintf( szErrorText, "0x%X: %s", ulError, pszContext );
    MAKERXSTRING( shvVar.shvname,  SZ_ERROR_NAME, strlen(SZ_ERROR_NAME) );
    MAKERXSTRING( shvVar.shvvalue, szErrorText,   strlen(szErrorText) );
    shvVar.shvnamelen  = RXSTRLEN( shvVar.shvname );
    shvVar.shvvaluelen = RXSTRLEN( shvVar.shvvalue );
    shvVar.shvcode     = RXSHV_SYSET;
    shvVar.shvnext     = NULL;
    ulRc = RexxVariablePool( &shvVar );
    if ( ulRc > 1 )
        printf("Unable to set %s: rc = %d\n", shvVar.shvname.strptr, shvVar.shvret );
}


