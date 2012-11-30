/*
 * icobtn.c
 *
 * This class definition file has been generated from the file
 * ..\SOM\SC\icobtn.c in preparation for compiling.  New
 * methods will be appended at the end only.
 */

// Uncomment to use 'raw' GPI functions for drawing the button caption, rather
// than WinDrawText.  Note that this prevents mnemonic characters from being
// rendered properly.
//#define GPI_DRAWTEXT


#define INCL_PM
#define INCL_GPI

#include "vxrexx.h"
#include "vxfuncs.h"

#define VRIconButton_Class_Source
#ifdef __WATCOMC__
#pragma disable_message(111)
#endif
#include "icobtn.ih"
#ifdef __WATCOMC__
#pragma enable_message(111)
#endif
#include "icobtn.ph"
#include "vxcdata.h"

#ifndef BS_TEXT
#define BS_TEXT 0x0010
#endif
#ifndef BS_MINIICON
#define BS_MINIICON 0x0020
#endif

// text alignment values (for _bAlign):
#define ALIGN_CENTER    1
#define ALIGN_TOP       2
#define ALIGN_BOTTOM    3
#define ALIGN_LEFT      4
#define ALIGN_RIGHT     5


// useful rectangle macros
#define RECTL_HEIGHT(rcl)       (rcl.yTop - rcl.yBottom)
#define RECTL_WIDTH(rcl)        (rcl.xRight - rcl.xLeft)


extern PSZ VRIconButtonPicturePath;


/*
 * LoadPicture (internal function)
 */

PVRMEMPICTURE LoadPicture( VRIconButton *somSelf )
{
    HAB hab = VRQueryAnchorBlock();
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);

    if ( _pPic ) {
        VRPictUnload( _pPic );
        _pPic = NULL;
    }
    if ( _pszImg && *_pszImg )
        _pPic = VRPictLoad( hab, _pszImg, MEMP_ANY );

    return _pPic;
}

/*
 * FindMnemonic (internal function)
 */

int FindMnemonic( VRIconButton *somSelf )
{
    PSZ psz;
    int iPos;
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);

    /* RC=0 indicates no mnemonic.  (Since a mnemonic must be preceded by '~',
     * by definition it can never be in position 0.)
     */
    if ( !_pszText || !(*_pszText) ) return 0;

    psz = _pszText;
    iPos = 0;
    do {
        if (( psz = strchr( psz, '~')) != NULL ) {
            psz++;
            if ( *psz && ( *psz == '~'))
                psz++;
            else if ( *psz )
                iPos = psz - _pszText;
        }
    } while ( psz && *psz && !iPos );

    return iPos;
}

/*
 * SetAutoSize (internal function)
 */

void SetAutoSize( VRIconButton *somSelf )
{
    FONTMETRICS fm;
    HWND   hwnd;
    HPS    hps;
    POINTL aptl[ TXTBOX_COUNT ];
    LONG   lMinW = 8,   // We always require border+margin of at least 8 pixels
           lMinH = 8,
           lStrW = 0,
           lStrH = 0;

    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    hwnd = _vrGetWindowHandle( somSelf );

    if ( _pszText && *_pszText ) {

        // Get the required size for the text string
        hps = WinGetPS( hwnd );
        GpiQueryFontMetrics( hps, sizeof( FONTMETRICS ), &fm );
        GpiQueryTextBox( hps, strlen( _pszText ),
                         _pszText, TXTBOX_COUNT, aptl );
        WinReleasePS( hps );
        lStrW = aptl[TXTBOX_TOPRIGHT].x - aptl[TXTBOX_TOPLEFT].x;
        lStrW += ( 2 * fm.lAveCharWidth );
        lStrH = fm.lMaxBaselineExt + fm.lInternalLeading + fm.lMaxDescender;

        // We have an image as well as text
        if ( _pPic && ( !_fResize || ( _pPic->type & MEMP_ICON ))) {
            switch ( _bAlign ) {
                case ALIGN_LEFT:
                case ALIGN_RIGHT:
                    lMinW += _pPic->width + lStrW + 7;
                    lMinH += max( _pPic->height + 6, lStrH );
                    break;

                case ALIGN_TOP:
                case ALIGN_BOTTOM:
                    lMinW += max( _pPic->width + 6, lStrW );
                    lMinH += _pPic->height + lStrH + 7;
                    break;

                default:    // ALIGN_CENTER
                    lMinW += max( _pPic->width + 6, lStrW );
                    lMinH += max( _pPic->height + 6, lStrH );
                    break;
            }
        }

        // We have only text (or if there is an image, it's auto-scaled)
        else {
            lMinW += lStrW;
            lMinH += lStrH;
        }
    }
    else if ( _pPic ) {
        // Image (non-rescaled) only
        lMinW += _pPic->width + 6;
        lMinH += _pPic->height + 6;
    }

    WinSetWindowPos( hwnd, NULLHANDLE, 0, 0, lMinW, lMinH, SWP_SIZE );
}

/*
 * PaintButton (internal function)
 */

bool PaintButton( VRIconButton *somSelf, PUSERBUTTON pbtn )
{
    FONTMETRICS fm;
    HAB    hab;
    RECTL  rcl,
           rclTxt,
           rclImg;
    POINTL ptl,
           aptl[ TXTBOX_COUNT ];
    LONG   lFlags,
           flPic,
           flTxt,
           lStrW,
           lStrH,
           lOffset,
           lClr;
    ULONG  cb;
    BOOL   fPosition;

//FILE *f = fopen("c:\\iconbtn.log", "a");

    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    lFlags = _vrGetWindowFlags( somSelf );

//fprintf(f, "----[ Entering PaintButton ] ----\n");

    if ( !pbtn || ( ! WinQueryWindowRect( pbtn->hwnd, &rcl )))
        return FALSE;

    // Get the current background colour
    cb = WinQueryPresParam( pbtn->hwnd, PP_BACKGROUNDCOLOR,
                            PP_BACKGROUNDCOLORINDEX, NULL,
                            sizeof( lClr ), &lClr, QPF_ID2COLORINDEX );
    if ( cb )
        GpiCreateLogColorTable( pbtn->hps, 0, LCOLF_RGB, 0, 0, NULL );
    else
        lClr = GpiQueryRGBColor( pbtn->hps, 0, SYSCLR_BUTTONMIDDLE );

    // Fill in the button background
    WinFillRect( pbtn->hps, &rcl, lClr );

    ptl.x = rcl.xLeft;
    ptl.y = rcl.yBottom;
    GpiMove( pbtn->hps, &ptl );
    ptl.x = rcl.xRight - 1;
    ptl.y = rcl.yTop - 1;
    // Draw the "default" state outline if applicable
    if ( pbtn->fsState & BDS_DEFAULT ) {
        GpiSetColor( pbtn->hps, SYSCLR_BUTTONDEFAULT );
        GpiBox( pbtn->hps, DRO_OUTLINE, &ptl, 0, 0 );
    }
    else {
        cb = WinQueryPresParam( WinQueryWindow( pbtn->hwnd, QW_PARENT ),
                                PP_BACKGROUNDCOLOR, PP_BACKGROUNDCOLORINDEX,
                                NULL, sizeof( lClr ), &lClr, QPF_ID2COLORINDEX );
        if ( cb )
            GpiSetColor( pbtn->hps, lClr );
        else
            GpiSetColor( pbtn->hps, SYSCLR_DIALOGBACKGROUND );
        GpiBox( pbtn->hps, DRO_OUTLINE, &ptl, 0, 0 );
    }

    if ( !( lFlags & BS_NOBORDER )) {
        /* Draw the button border (if appropriate) depending on the current
         * state(s).
         */
        GpiSetColor( pbtn->hps, ( _fDown || ( pbtn->fsState & BDS_HILITED )) ?
                                CLR_BLACK: SYSCLR_BUTTONDARK );
        ptl.x = rcl.xLeft + 1;
        ptl.y = rcl.yBottom + 2;
        GpiMove( pbtn->hps, &ptl );
        ptl.y = rcl.yTop - 2;
        GpiLine( pbtn->hps, &ptl );
        GpiMove( pbtn->hps, &ptl );
        ptl.x = rcl.xRight - 2;
        GpiLine( pbtn->hps, &ptl );
        GpiSetColor( pbtn->hps, ( _fDown || ( pbtn->fsState & BDS_HILITED )) ?
                                SYSCLR_BUTTONDARK: CLR_BLACK );
        ptl.x = rcl.xLeft + 1;
        ptl.y = rcl.yBottom + 1;
        GpiMove( pbtn->hps, &ptl );
        ptl.x = rcl.xRight - 2;
        GpiLine( pbtn->hps, &ptl );
        GpiMove( pbtn->hps, &ptl );
        ptl.y = rcl.yTop - 3;
        GpiLine( pbtn->hps, &ptl );

        GpiSetColor( pbtn->hps, ( _fDown || ( pbtn->fsState & BDS_HILITED )) ?
                                SYSCLR_BUTTONLIGHT: SYSCLR_BUTTONDARK );
        ptl.x = rcl.xLeft + 2;
        ptl.y = rcl.yBottom + 2;
        GpiMove( pbtn->hps, &ptl );
        ptl.x = rcl.xRight - 3;
        GpiLine( pbtn->hps, &ptl );
        GpiMove( pbtn->hps, &ptl );
        ptl.y = rcl.yTop - 3;
        GpiLine( pbtn->hps, &ptl );
        GpiSetColor( pbtn->hps, ( _fDown || ( pbtn->fsState & BDS_HILITED )) ?
                                SYSCLR_BUTTONDARK: SYSCLR_BUTTONLIGHT );
        ptl.x = rcl.xLeft + 2;
        ptl.y = rcl.yBottom + 3;
        GpiMove( pbtn->hps, &ptl );
        ptl.y = rcl.yTop - 3;
        GpiLine( pbtn->hps, &ptl );
        GpiMove( pbtn->hps, &ptl );
        ptl.x = rcl.xRight - 3;
        GpiLine( pbtn->hps, &ptl );

        if ( pbtn->fsState & BDS_HILITED ) {
            GpiSetColor( pbtn->hps, SYSCLR_BUTTONLIGHT );
            ptl.x = rcl.xLeft + 3;
            ptl.y = rcl.yBottom + 3;
            GpiMove( pbtn->hps, &ptl );
            ptl.x = rcl.xRight - 4;
            GpiLine( pbtn->hps, &ptl );
            GpiMove( pbtn->hps, &ptl );
            ptl.y = rcl.yTop - 4;
            GpiLine( pbtn->hps, &ptl );
            GpiSetColor( pbtn->hps, SYSCLR_BUTTONDARK );
            ptl.x = rcl.xLeft + 3;
            ptl.y = rcl.yBottom + 4;
            GpiMove( pbtn->hps, &ptl );
            ptl.y = rcl.yTop - 4;
            GpiLine( pbtn->hps, &ptl );
            GpiMove( pbtn->hps, &ptl );
            ptl.x = rcl.xRight - 4;
            GpiLine( pbtn->hps, &ptl );
        }

    } // if ( !( lFlags & BS_NOBORDER ))

    /* After this point, rcl is used for the clipping boundaries of the entire
     * button contents exclusive of the border.  Separate bounding rectangles
     * for the image and the text will now be calculated within this area.
     */
    if ( rcl.xRight > 6 ) {
        rcl.xLeft += 3;
        rcl.xRight -= 3;
    }
    if ( rcl.yTop > 6 ) {
        rcl.yBottom += 3;
        rcl.yTop -= 3;
    }
    memcpy( &rclTxt, &rcl, sizeof( RECTL ));
    if ( RECTL_WIDTH( rclTxt ) > 4 ) {
        rclTxt.xLeft += 2;
        rclTxt.xRight -= 2;
    }
    if ( RECTL_WIDTH( rclTxt ) > 4 ) {
        rclTxt.yBottom += 2;
        rclTxt.yTop -= 2;
    }
    if ( _pPic && ( _pPic->type & MEMP_BITMAP ) && _fResize )
        memcpy( &rclImg, &rcl, sizeof( RECTL ));
    else {
        rclImg.xLeft   = ( RECTL_WIDTH( rclTxt ) > 6 )  ?
                         rclTxt.xLeft + 3   : rclTxt.xLeft;
        rclImg.xRight  = ( RECTL_WIDTH( rclTxt ) > 6 )  ?
                         rclTxt.xRight - 3  : rclTxt.xRight;
        rclImg.yBottom = ( RECTL_HEIGHT( rclTxt ) > 6 ) ?
                         rclTxt.yBottom + 3 : rclTxt.yBottom;
        rclImg.yTop    = ( RECTL_HEIGHT( rclTxt ) > 6 ) ?
                         rclTxt.yTop - 3    : rclTxt.yTop;
    }

//fprintf(f, "rcl     = {%d %d %d %d}, width = %d, height= %d\n", rcl.xLeft, rcl.yBottom, rcl.xRight, rcl.yTop, RECTL_WIDTH(rcl), RECTL_HEIGHT(rcl) );
//fprintf(f, "rclImg  = {%d %d %d %d}, width = %d, height= %d\n", rclImg.xLeft, rclImg.yBottom, rclImg.xRight, rclImg.yTop, RECTL_WIDTH(rclImg), RECTL_HEIGHT(rclImg) );

    fPosition = _pPic && ( !_fResize || _pPic->type & MEMP_ICON ) &&
                (( _bAlign == ALIGN_LEFT ) || ( _bAlign == ALIGN_RIGHT )) ?
                TRUE : FALSE;

    /* We won't draw the text until after the image... but unless we're scaling
     * the image into the whole button, we need to calculate how much space the
     * text is going to require so we can fit the image next to it.  (Note that
     * we behave differently for top/bottom alignment vs left/right alignment -
     * with top/bottom, the text area is fixed to the height of the string plus
     * a certain margin.  With left/right alignment, the image rectangle is set
     * to the physical image size, and the text rectangle is offset from that.)
     */
    lStrW = 0;
    lStrH = 0;
    GpiQueryFontMetrics( pbtn->hps, sizeof( FONTMETRICS ), &fm );
    if ( _pszText && *_pszText ) {

        // Get the width of the text as it would be rendered in the current font
        GpiQueryTextBox( pbtn->hps, strlen( _pszText ),
                         _pszText, TXTBOX_COUNT, aptl );

        lStrW = aptl[TXTBOX_TOPRIGHT].x - aptl[TXTBOX_TOPLEFT].x;
        lStrW += ( 2 * fm.lAveCharWidth );
        lStrH = fm.lMaxBaselineExt + fm.lInternalLeading + fm.lMaxDescender;

        // Adjust the bounding rectangles for the text and image
        switch ( _bAlign ) {
            case ALIGN_TOP:
                rclTxt.yBottom = rclTxt.yTop - lStrH;
                if ( _pPic && ( !_fResize || _pPic->type & MEMP_ICON )) {
                    if (( rclTxt.yBottom - rclImg.yBottom ) > _pPic->height )
                        rclImg.yTop = rclTxt.yBottom - 1;
                    else if (( rcl.yTop - rclImg.yBottom ) > _pPic->height )
                        rclImg.yTop = rcl.yBottom + _pPic->height;
                }
                break;
            case ALIGN_BOTTOM:
                rclTxt.yTop = rclTxt.yBottom + lStrH;
                if ( _pPic && ( !_fResize || _pPic->type & MEMP_ICON )) {
                    if ((( rclImg.yTop - rclTxt.yTop ) > _pPic->height ))
                        rclImg.yBottom = rclTxt.yTop + 1;
                    else if (( rclImg.yTop - rcl.yBottom ) > _pPic->height )
                        rclImg.yBottom = (LONG) ( rcl.yTop - _pPic->height );
                }
                break;
            case ALIGN_LEFT:
                if ( fPosition ) {
                    if (( rclTxt.xLeft + lStrW + _pPic->width ) < rclImg.xRight ) {
                        rclImg.xLeft = rclImg.xRight - _pPic->width;
                        rclTxt.xRight = rclImg.xLeft - 1;
                    }
                    else  {
                        rclTxt.xRight = rclTxt.xLeft + lStrW;
                        if (( rclImg.xRight - _pPic->width ) < RECTL_WIDTH( rcl ))
                            rclImg.xLeft = (LONG) ( rclImg.xRight - _pPic->width );
                    }
                }
                else
                    rclTxt.xRight = rclTxt.xLeft + lStrW;
                break;
            case ALIGN_RIGHT:
                if ( fPosition ) {
                    if (( rclImg.xLeft + _pPic->width + lStrW ) < rclImg.xRight ) {
                        rclImg.xRight = rclImg.xLeft + _pPic->width;
                        rclTxt.xLeft = rclImg.xRight + 1;
                    }
                    else {
                        rclTxt.xLeft = rclTxt.xRight - lStrW;
                        if (( rclImg.xLeft + _pPic->width ) < RECTL_WIDTH( rcl ))
                            rclImg.xRight = rclImg.xLeft + _pPic->width;
                    }
                }
                else
                    rclTxt.xLeft = rclTxt.xRight - lStrW;
                break;
            default: break;   // ALIGN_CENTER, no adjustment needed
        }
        if ( rclTxt.yBottom < rcl.yBottom ) rclTxt.yBottom = rcl.yBottom;
        if ( rclTxt.yTop > rcl.yTop ) rclTxt.yTop = rcl.yTop;
        if ( rclTxt.xLeft < rcl.xLeft ) rclTxt.xLeft = rcl.xLeft;
        if ( rclTxt.xRight > rcl.xRight ) rclTxt.xRight = rcl.xRight;
    }

    // Draw the image, if one is defined
    if ( _pPic ) {

        if (( pbtn->fsState & BDS_HILITED ) &&
            !( _fResize && ( _pPic->type & MEMP_BITMAP )))
        {
            rclImg.xLeft++;
            rclImg.xRight++;
            rclImg.yBottom--;
            rclImg.yTop--;
        }

        flPic = PICTDRAW_CENTER_ICON;
        if ( pbtn->fsState & BDS_DISABLED ) flPic |= PICTDRAW_DISABLE;
        if ( _pPic->type & MEMP_BITMAP ) {
            if ( _fResize )
                flPic |= PICTDRAW_STRETCH_BITMAP;
            else {
                ptl.x = ((LONG)( RECTL_WIDTH( rclImg ) - _pPic->width ) / 2 );
                ptl.y = ((LONG)( RECTL_HEIGHT( rclImg ) - _pPic->height ) / 2 );
                if ( ptl.x > 0 ) rclImg.xLeft += ptl.x;
                if ( ptl.y > 0 ) rclImg.yBottom += ptl.y;
            }
        }

        VRPictDisplay( pbtn->hwnd, pbtn->hps, _pPic, &rclImg, flPic );
    }

    // Now draw the text, if any
    if ( _pszText && *_pszText ) {

        // Get the current foreground colour
        if ( pbtn->fsState & BDS_DISABLED )
            lClr = GpiQueryRGBColor( pbtn->hps, 0, SYSCLR_MENUDISABLEDTEXT );
        else {
            cb = WinQueryPresParam( pbtn->hwnd, PP_FOREGROUNDCOLOR,
                                    PP_FOREGROUNDCOLORINDEX, NULL,
                                    sizeof( lClr ), &lClr, QPF_ID2COLORINDEX );
            if ( !cb )
                lClr = GpiQueryRGBColor( pbtn->hps, 0, SYSCLR_WINDOWTEXT );
        }
        GpiSetColor( pbtn->hps, lClr );

        // Now position and draw the button text
        switch ( _bAlign ) {

            case ALIGN_TOP:
#ifdef GPI_DRAWTEXT
                ptl.x = rclTxt.xLeft + ( RECTL_WIDTH( rclTxt ) / 2 );
                ptl.y = ( RECTL_HEIGHT( rclTxt ) < lStrH ) ? rclTxt.yTop :
                        rclTxt.yTop - ( 2 * fm.lInternalLeading );
                GpiSetTextAlignment( pbtn->hps, TA_CENTER, TA_TOP );
#else
                flTxt = DT_CENTER | (( RECTL_HEIGHT( rclTxt ) < lStrH )
                                    ? DT_TOP : DT_VCENTER ) |
                        DT_TEXTATTRS | DT_MNEMONIC;
#endif
                break;

            case ALIGN_BOTTOM:
#ifdef GPI_DRAWTEXT
                ptl.x = rclTxt.xLeft + ( RECTL_WIDTH( rclTxt ) / 2 );
                ptl.y = ( RECTL_HEIGHT( rclTxt ) < lStrH ) ? rclTxt.yBottom :
                        rclTxt.yBottom + ( 2 * fm.lInternalLeading );
                GpiSetTextAlignment( pbtn->hps, TA_CENTER, TA_BOTTOM );
#else
                flTxt = DT_CENTER | (( RECTL_HEIGHT( rclTxt ) < lStrH ) ?
                                    DT_BOTTOM : DT_VCENTER ) |
                        DT_TEXTATTRS | DT_MNEMONIC;
#endif
                break;

            case ALIGN_LEFT:
#ifdef GPI_DRAWTEXT
                ptl.x = rclTxt.xLeft + fm.lAveCharWidth;
                ptl.y = rclTxt.yBottom + (( RECTL_HEIGHT( rclTxt ) - fm.lXHeight ) / 2 );
                GpiSetTextAlignment( pbtn->hps, TA_NORMAL_HORIZ, TA_BASE );
#else
                flTxt = DT_LEFT | DT_VCENTER | DT_TEXTATTRS | DT_MNEMONIC;
                rclTxt.xLeft += fm.lAveCharWidth;
#endif
                break;

            case ALIGN_RIGHT:
#ifdef GPI_DRAWTEXT
                ptl.x = rclTxt.xLeft + fm.lAveCharWidth;
                ptl.y = rclTxt.yBottom + (( RECTL_HEIGHT( rclTxt ) - fm.lXHeight ) / 2 );
                GpiSetTextAlignment( pbtn->hps, TA_NORMAL_HORIZ, TA_BASE );
#else
                flTxt = (fPosition? DT_LEFT: DT_RIGHT) | DT_VCENTER | DT_TEXTATTRS | DT_MNEMONIC;
                if ( RECTL_WIDTH( rclTxt ) > fm.lAveCharWidth ) {
                    if ( fPosition )
                        rclTxt.xLeft += fm.lAveCharWidth;
                    else
                        rclTxt.xRight -= fm.lAveCharWidth;
                }
#endif
                break;

            default:    // ALIGN_CENTER
#ifdef GPI_DRAWTEXT
                ptl.x = rclTxt.xLeft + ( RECTL_WIDTH( rclTxt ) / 2 );
                ptl.y = rclTxt.yBottom + (( RECTL_HEIGHT( rclTxt ) - fm.lXHeight ) / 2 );
                GpiSetTextAlignment( pbtn->hps, TA_CENTER, TA_BASE );
#else
                flTxt = DT_CENTER | DT_VCENTER | DT_TEXTATTRS | DT_MNEMONIC;
#endif
                break;
        }
        if ( pbtn->fsState & BDS_HILITED ) {
            ptl.x++;
            ptl.y--;
        }
        cb = strlen( _pszText );
#ifdef GPI_DRAWTEXT
        GpiCharStringPosAt( pbtn->hps, &ptl, &rclTxt, CHS_CLIP, cb, _pszText, NULL );
#else
        WinDrawText( pbtn->hps, cb, _pszText, &rclTxt, 0, 0, flTxt );
#endif
    }

//fprintf(f, "----[ Leaving PaintButton ] ----\n\n");
//fclose(f);

    return TRUE;
}


/*
 *  VRIconButtonInstance_somInit
 */

SOM_Scope void   SOMLINK VRIconButtonInstance_somInit(VRIconButton *somSelf)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_somInit");

    _pszText   = NULL;
    _pszImg    = NULL;
    _pPic      = NULL;
    _fMini     = FALSE;
    _fResize   = FALSE;
    _fAutosize = FALSE;
    _iMnPos    = 0;
    _bAlign    = ALIGN_CENTER;

    parent_somInit(somSelf);
}

/*
 *  VRIconButtonInstance_somUninit
 */

SOM_Scope void   SOMLINK VRIconButtonInstance_somUninit(VRIconButton *somSelf)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_somUninit");

    if ( _pszText ) VRMemFree( _pszText );
    if ( _pszImg  ) VRMemFree( _pszImg  );
    if ( _pPic )    VRPictUnload( _pPic );

    parent_somUninit(somSelf);
}

/*
 *  VRIconButtonInstance_vrLocalCreateWindow
 */

SOM_Scope HWND   SOMLINK VRIconButtonInstance_vrLocalCreateWindow(VRIconButton *somSelf,
		PBOOL visible)
{
    LONG flags;

    /* VRIconButtonData *somThis = VRIconButtonGetData(somSelf); */
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrLocalCreateWindow");

    flags = _vrGetWindowFlags( somSelf );
    flags |= BS_USERBUTTON;
    _vrSetWindowFlags( somSelf, flags );

    return (parent_vrLocalCreateWindow(somSelf,visible));
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
/*
 *  VRIconButtonClass_vrLocalClassInit

 * Note: The vrLocalClassInit function is defined
 * in the .ph file for this class....
 */


/*
 *  VRIconButtonClass_vrLocalWindowClassInit
 */

SOM_Scope bool   SOMLINK VRIconButtonClass_vrLocalWindowClassInit(M_VRIconButton *somSelf)
{
    /* M_VRIconButtonData *somThis = M_VRIconButtonGetData(somSelf); */
    M_VRIconButtonMethodDebug("M_VRIconButton","VRIconButtonClass_vrLocalWindowClassInit");

    return (parent_vrLocalWindowClassInit(somSelf));
}

/*
 *  VRIconButtonClass_somInit
 */

SOM_Scope void   SOMLINK VRIconButtonClass_somInit(M_VRIconButton *somSelf)
{
    /* M_VRIconButtonData *somThis = M_VRIconButtonGetData(somSelf); */
    M_VRIconButtonMethodDebug("M_VRIconButton","VRIconButtonClass_somInit");

    parent_somInit(somSelf);

    get_picturepath( somSelf ) = VRIconButtonPicturePath;

    if( VRQueryRunMode() == VR_DESIGN_MODE ){
        VRInstallHelp( somSelf );
    }
}

/*
 *  VRIconButtonClass_somUninit
 */

SOM_Scope void   SOMLINK VRIconButtonClass_somUninit(M_VRIconButton *somSelf)
{
    /* M_VRIconButtonData *somThis = M_VRIconButtonGetData(somSelf); */
    M_VRIconButtonMethodDebug("M_VRIconButton","VRIconButtonClass_somUninit");

    parent_somUninit(somSelf);
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrSet_Caption
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrSet_Caption(VRIconButton *somSelf,
		PSZ str)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrSet_Caption");

    if ( !str ) return FALSE;
    if ( _pszText ) VRMemFree( _pszText );

    _pszText = VRMemAlloc( strlen( str ) + 1 );
    if ( !_pszText ) return FALSE;

    strcpy( _pszText, str );
    _iMnPos = FindMnemonic( somSelf );

    WinInvalidateRect( _vrGetWindowHandle( somSelf ), NULL, TRUE );
    if ( _fAutosize ) SetAutoSize( somSelf );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrGet_Caption
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrGet_Caption(VRIconButton *somSelf,
		PSZ *str)
{
    PSZ pszValue;
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrGet_Caption");

    pszValue = _pszText ? _pszText : "";
    *str = VRMemAlloc( strlen( pszValue ) + 1 );
    if ( *str == NULL ) return FALSE;

    strcpy( *str, pszValue );
    return TRUE;

    /* return (parent_vrGet_Caption(somSelf,str)); */
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrSet_PicturePath
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrSet_PicturePath(VRIconButton *somSelf,
		PSZ str)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrSet_PicturePath");

    if ( !str ) return FALSE;
    if ( _pszImg ) VRMemFree( _pszImg );

    _pszImg = VRMemAlloc( strlen( str ) + 1 );
    if ( !_pszImg ) return FALSE;
    strcpy( _pszImg, str );

    LoadPicture( somSelf );
    WinInvalidateRect( _vrGetWindowHandle( somSelf ), NULL, TRUE );
    if ( _fAutosize ) SetAutoSize( somSelf );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrGet_PicturePath
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrGet_PicturePath(VRIconButton *somSelf,
		PSZ *str)
{
    PSZ pszValue;
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrGet_PicturePath");

    pszValue = _pszImg ? _pszImg : "";
    *str = VRMemAlloc( strlen( pszValue ) + 1 );
    if ( *str == NULL ) return FALSE;

    strcpy( *str, pszValue );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrWM_CONTROL
 */

SOM_Scope MRESULT   SOMLINK VRIconButtonInstance_vrWM_CONTROL(VRIconButton *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrWM_CONTROL");

    if ( SHORT2FROMMP( mp1 ) == BN_PAINT ) {
        PaintButton( somSelf, (PUSERBUTTON) mp2 );
    }

    return (MRESULT) 0;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrSet_ResizePicture
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrSet_ResizePicture(VRIconButton *somSelf,
		BOOL on)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrSet_ResizePicture");

    _fResize = on;
    WinInvalidateRect( _vrGetWindowHandle( somSelf ), NULL, TRUE );
    if ( _fAutosize ) SetAutoSize( somSelf );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrGet_ResizePicture
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrGet_ResizePicture(VRIconButton *somSelf,
		BOOL *on)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrGet_ResizePicture");

    *on = _fResize;
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrSet_TextPosition
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrSet_TextPosition(VRIconButton *somSelf,
		PSZ str)
{
    CHAR c;
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrSet_TextPosition");

    if ( !str || !(*str) ) return FALSE;
    c = tolower( *str );
    switch ( c ) {
        case 'b': _bAlign = ALIGN_BOTTOM; break;
        case 'c': _bAlign = ALIGN_CENTER; break;
        case 'l': _bAlign = ALIGN_LEFT;   break;
        case 'r': _bAlign = ALIGN_RIGHT;  break;
        case 't': _bAlign = ALIGN_TOP;    break;
        default:  return FALSE;           break;
    }
    WinInvalidateRect( _vrGetWindowHandle( somSelf ), NULL, TRUE );
    if ( _fAutosize ) SetAutoSize( somSelf );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrGet_TextPosition
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrGet_TextPosition(VRIconButton *somSelf,
		PSZ *str)
{
    PSZ pszValue;
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrGet_TextPosition");

    switch ( _bAlign ) {
        case ALIGN_BOTTOM: pszValue = "Bottom"; break;
        case ALIGN_LEFT:   pszValue = "Left";   break;
        case ALIGN_RIGHT:  pszValue = "Right";  break;
        case ALIGN_TOP:    pszValue = "Top";    break;
        default:           pszValue = "Center"; break;
    }

    *str = VRMemAlloc( strlen( pszValue ) + 1 );
    if ( *str == NULL ) return FALSE;

    strcpy( *str, pszValue );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrSet_Pushed
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrSet_Pushed(VRIconButton *somSelf,
		BOOL on)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrSet_Pushed");

    _fDown = on;
    WinInvalidateRect( _vrGetWindowHandle( somSelf ), NULL, TRUE );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrGet_Pushed
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrGet_Pushed(VRIconButton *somSelf,
		BOOL *on)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrGet_Pushed");

    *on = _fDown;
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrWM_PAINT
 */

SOM_Scope MRESULT   SOMLINK VRIconButtonInstance_vrWM_PAINT(VRIconButton *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2)
{
    USERBUTTON btn = {0};
    RECTL rcl;
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrWM_PAINT");

    if ( VRQueryRunMode() == VR_DESIGN_MODE ) {
        /* Workaround for BN_PAINT apparently not getting sent to groupbox
         * children when in VX-REXX is in Design mode.
         */
        btn.hps = WinBeginPaint( hWnd, NULLHANDLE, &rcl );
        btn.hwnd = hWnd;
        PaintButton( somSelf, &btn );
        WinEndPaint( btn.hps );
        return (MRESULT) 0;
    }
    else
        return _vrCallDefProc( somSelf, hWnd, msg, mp1, mp2 );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrWM_MATCHMNEMONIC
 */

SOM_Scope MRESULT   SOMLINK VRIconButtonInstance_vrWM_MATCHMNEMONIC(VRIconButton *somSelf,
		HWND hWnd,
		ULONG msg,
		MPARAM mp1,
		MPARAM mp2)
{
    UCHAR uc;
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrWM_MATCHMNEMONIC");

    if ( !_iMnPos || !_pszText || !(*_pszText ))
        return (MRESULT) FALSE;

    uc = toupper( (UCHAR) SHORT1FROMMP( mp1 ) );
    if ( uc == toupper( _pszText[ _iMnPos ] ))
        return (MRESULT) TRUE;

    return (MRESULT) FALSE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrSet_Autosize
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrSet_Autosize(VRIconButton *somSelf,
		BOOL on)
{
    bool bOK = TRUE;
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrSet_Autosize");
    _fAutosize = on;
    if ( on ) SetAutoSize( somSelf );
    return TRUE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

/*
 *  VRIconButtonInstance_vrGet_Autosize
 */

SOM_Scope bool   SOMLINK VRIconButtonInstance_vrGet_Autosize(VRIconButton *somSelf,
		BOOL *on)
{
    VRIconButtonData *somThis = VRIconButtonGetData(somSelf);
    VRIconButtonMethodDebug("VRIconButton","VRIconButtonInstance_vrGet_Autosize");

    *on = _fAutosize;
    return TRUE;
}
