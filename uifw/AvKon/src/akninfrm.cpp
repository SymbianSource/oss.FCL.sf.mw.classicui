/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/


// Akninfrm.cpp
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#include <akninfrm.h>
#include <eikenv.h>
#include <barsread.h>
#include <eikedwin.h>

#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>
#include <aknlists.h>
#include <AknsFrameBackgroundControlContext.h>

#include <aknconsts.h>
#include <avkon.mbg>

#include <aknlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <aknapaclayout.cdl.h>
#include <AknIconUtils.h>

#include "akntrace.h"
CAknInputFrame::CAknInputFrame() 
    {
    }

EXPORT_C CAknInputFrame::~CAknInputFrame()
    {
    AknsUtils::DeregisterControlPosition( iField );
    delete iIcon;
    delete iPopupFindCC;
    delete iPopupListCC;
    delete iFileName;

    if ( iFlags & EOwnsInputContext )
        {
        delete iInputContext;
        }
    
    if ( iFlags & EOwnsField )
        {
        delete iField;
        }
    }

/**
 * Creates CAknInputFrame. 
 * Gets six parameters:
 * CCoeControl* aField	  - Control, which will be located inside the input frame.
 * TBool aOwner           - Defines the ownership of the control.
 * const TDesC& aFileName - Bitmap file name and path.
 * TInt aBitmapId         - Bitmap Id
 * TInt aMaskId           - Bitmap Mask Id
 * TUint32 aFlags		  - Flags	
 *
 * 
 */
EXPORT_C CAknInputFrame* CAknInputFrame::NewL(CCoeControl* aField, TBool aOwner, const TDesC& aFileName, TInt aBitmapId,
                                              TInt aMaskId, TUint32 aFlags)
    {
    CAknInputFrame* bf = new (ELeave) CAknInputFrame;
    CleanupStack::PushL(bf);
    bf->ConstructL(aField, aOwner, aFileName, aBitmapId, aMaskId, aFlags);
    CleanupStack::Pop();
    return bf;
    }

/**
 * Creates CAknInputFrame. 
 * Gets six parameters:
 * CCoeControl* aField	  - Control, which will be located inside the input frame.
 * TBool aOwner           - Defines the ownership of the control.
 * CGulIcon* aIcon        - Bitmap file name and path.
 * TUint32 aFlags		  - Flags	
 *
 * 
 */
EXPORT_C CAknInputFrame* CAknInputFrame::NewL(CCoeControl* aField,TBool aOwner, CGulIcon* aIcon, TUint32 aFlags)
    {
    CAknInputFrame* bf = new (ELeave) CAknInputFrame;
    CleanupStack::PushL(bf);
    bf->ConstructL(aField,aOwner, aIcon, aFlags);
    CleanupStack::Pop();
    return bf;
    }

void CAknInputFrame::ConstructL( CCoeControl* aField,
                                 TBool aOwner,
                                 CGulIcon* aIcon,
                                 TUint32 aFlags )
    {
    BaseConstructL(aField, aOwner, aFlags);
    iIcon=aIcon; // May not leave after this
    }

void CAknInputFrame::ConstructL( CCoeControl* aField,
                                 TBool aOwner,
                                 const TDesC& aFileName,
                                 TInt aBitmapId,
                                 TInt aMaskId,
                                 TUint32 aFlags )
    {
    BaseConstructL(aField, aOwner, aFlags);
    iFileName = aFileName.Alloc();
    iBitmapId = aBitmapId;
    iMaskId = aMaskId;
    
    if(aFileName.Length())
        {
        if( aFileName.Compare( KAvkonBitmapFile ) == 0 )
            {
            // If the icon comes from Avkon MBM, set skin IID if known
            switch( aBitmapId )
                {
                case EMbmAvkonQgn_indi_find_glass:
                    iIconSkinID = KAknsIIDQgnIndiFindGlass;
                    break;
                case EMbmAvkonQgn_indi_find_glass_pinb:
                    iIconSkinID = KAknsIIDQgnIndiFindTitle;
                    break;
                case EMbmAvkonQgn_indi_find_goto:
                    iIconSkinID = KAknsIIDQgnIndiFindGoto;
                    break;
                default:
                    iIconSkinID = KAknsIIDNone;
                    break;
                }
            }
		CAknInputFrame::CreateIconL();
        }
    }

void CAknInputFrame::BaseConstructL( CCoeControl* aField, TBool aOwner, TUint32 aFlags )
    {
    iFlags = aFlags;

    if ( aField )
        {
        aField->SetContainerWindowL(*this);
        aField->SetObserver(this);
        static_cast<CEikBorderedControl*>( aField )->SetBorder( TGulBorder::ENone );
        }

    // Construct context for popup find background
    if( iFlags & EPopupLayout )
        {
        iPopupFindCC = CAknsFrameBackgroundControlContext::NewL( KAknsIIDQsnFrPopup, Rect(), Rect(), EFalse );
        }
    // Construct context for popup list background
    if  ( iFlags & EPopupWindowLayout )
        {
        iPopupListCC = CAknsBasicBackgroundControlContext::NewL( KAknsIIDQsnFrPopupCenter, Rect(), EFalse );
        }
    
    if ( aOwner )
        {
        iFlags|=EOwnsField;
        }
    
    iField = aField; // May not leave after this
    iIconSkinID = KAknsIIDNone;
    }

EXPORT_C void CAknInputFrame::ConstructFromResourceL(TResourceReader& aReader)
    {
    TPtrC filename = aReader.ReadTPtrC();
    TInt32 pid = aReader.ReadInt16();
    TInt32 mid = aReader.ReadInt16();
    TInt32 flags = aReader.ReadInt16();
    const TInt ctrlType = aReader.ReadInt16();
    TPtrC infoText = aReader.ReadTPtrC(); // discarded, since infotext is deprecated

    CCoeControl* field = EikControlFactory::CreateByTypeL(ctrlType).iControl;
    CleanupStack::PushL(field);
    field -> ConstructFromResourceL(aReader);
    ConstructL(field,ETrue,filename,pid,mid,flags);
    CleanupStack::Pop(); // field
    if ((ctrlType==EEikCtGlobalTextEditor) || (ctrlType==EEikCtEdwin))
        {
        TMargins8 margins;
        margins.SetAllValuesTo(0);
        STATIC_CAST(CEikBorderedControl*,iField)->SetBorder(TGulBorder::ENone);                
        STATIC_CAST(CEikEdwin*,field)->SetBorderViewMargins(margins);
        }
    }

/**
* Return pointer to field 
*/
EXPORT_C CCoeControl* CAknInputFrame::Field() const
    {
    return iField;
    }

EXPORT_C void CAknInputFrame::SetInfoTextL(const TDesC& /*aText*/)
    {
    RDebug::Printf("%s: Warning: deprecated method CAknInputFrame::SetInfoTextL() called", __FILE__ );
    }

/**
* Sets additional icon to input frame 
* Gets one parameter:
* CGulIcon* aIcon          - Icon.
*/
void CAknInputFrame::SetIcon( CGulIcon* aIcon )
    {
    delete iIcon;
    iIcon = aIcon;
    iIconSkinID = KAknsIIDNone;
    }

TUint CAknInputFrame::Flags() const
    {
    return iFlags;
    }

void CAknInputFrame::SetFlags( TUint aNewFlags )
    {
    iFlags = aNewFlags;
    }

EXPORT_C void CAknInputFrame::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent aEventType)
    {
    if (aEventType == EEventRequestFocus)
        {
        FocusChanged(EDrawNow);
        }
    }

void CAknInputFrame::PrepareForFocusLossL()
    {
    iField->PrepareForFocusLossL();
    }

EXPORT_C TKeyResponse CAknInputFrame::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    if ( iField )
        {
        return iField->OfferKeyEventL( aKeyEvent, aType );
        }
    return EKeyWasNotConsumed;
    }

void CAknInputFrame::SizeChanged()
    {
    // There are 5 different layouts to be handled by this component:
    // --------------------------------------------------------------
    // Standard          ( fixed find pane in column lists )
    // PopupLayout       ( popup find pane in any mainpane list )
    // PinbLayout        ( used by pinboard app )
    // ClockAppLayout    ( has been removed from laf - fall back to standard )
    // PopupWindowLayout ( used by list query and popuplist )
    _AKNTRACE_FUNC_ENTER;
    TRect parent( Rect() );       // parent for components
    TRect editorParent( Rect() ); // parent for the editor
    TRect rect( Rect() );         // rect of the whole shebang
    TAknLayoutRect r;            // common temporary layout rect

    TAknWindowComponentLayout outline(0);
    TAknWindowLineLayout      iconPos(0);
    TAknTextComponentLayout   editor(0);

    TBool apac( AknLayoutUtils::Variant() == EApacVariant && ( iFlags & EShowIndicators ) );

    if ( iFlags & EPopupLayout ) // popup find box 
        {
        _AKNTRACE( "[%s][%s] PopupLayout", 
        		"CAknInputFrame", __FUNCTION__ );
        r.LayoutRect( parent, AknLayoutScalable_Avkon::find_popup_pane() );
        parent = r.Rect();
        r.LayoutRect( r.Rect(), AknLayoutScalable_Avkon::input_popup_find_pane_cp() );
        editorParent = r.Rect();
        outline  = AknLayoutScalable_Avkon::input_popup_find_pane_cp();
        iconPos  = AknLayoutScalable_Avkon::find_popup_pane_g1().LayoutLine();
        editor = AknLayoutScalable_Avkon::input_popup_find_pane_t1( apac ? 2 : 0 );
        if ( iPopupFindCC )
            {
            r.LayoutRect( rect, AknLayoutScalable_Avkon::find_popup_pane() );
            iPopupFindCC->SetFrameRects( rect, r.Rect() );
            }
        }
    else if ( iFlags & EPinbLayout ) // used by pinboard app
        {
        _AKNTRACE( "[%s][%s] PinbLayout", 
                "CAknInputFrame", __FUNCTION__ );
        outline = AknLayoutScalable_Apps::input_focus_pane_cp01(0);
        iconPos = AknLayoutScalable_Apps::find_pinb_pane_g1(0);
        editor = AknLayoutScalable_Apps::find_pinb_pane_t2( apac ? 1 : 0 );
        }

    else if ( iFlags & EPopupWindowLayout )     // list query or popup list
        {
        _AKNTRACE( "[%s][%s] PopupWindowLayout", 
                 "CAknInputFrame", __FUNCTION__ );
        outline = AknLayoutScalable_Avkon::input_popup_find_pane_cp();
        iconPos = AknLayoutScalable_Avkon::find_popup_pane_g1();
        
        TAknTextComponentLayout textComponentLayout(
            TAknWindowComponentLayout::ComposeText( outline, 
                AknLayoutScalable_Avkon::input_popup_find_pane_t1( apac ? 2 : 0 ) ) );
                
        editor = textComponentLayout;
        
        if ( iPopupListCC )
            {
            iPopupListCC->SetRect( rect );
            }
        }
    else // standard find pane
        {
        _AKNTRACE( "[%s][%s] Standard Layout", 
                 "CAknInputFrame", __FUNCTION__ );
        outline = AknLayoutScalable_Avkon::input_find_pane();
        iconPos = AknLayoutScalable_Avkon::find_pane_g1();
        editor = AknLayoutScalable_Avkon::input_find_pane_t2( apac ? 1: 0 );
        r.LayoutRect( rect, AknLayoutScalable_Avkon::input_find_pane() );
        editorParent = r.Rect();
        }



    // --- set size and position of the frame around editor ---
    r.LayoutRect( parent, outline );
    iOutlineRect = r.Rect();
    _AKNTRACE( "[%s][%s] iOutlineRect: %s:%d,%d %s:%d,%d", 
            "CAknInputFrame", __FUNCTION__, 
            "LT", iOutlineRect.iTl.iX, iOutlineRect.iTl.iY, 
            "BR", iOutlineRect.iBr.iX, iOutlineRect.iBr.iY );

    if ( !iInputContext )
        {
        // we need to provide own context if one does not exist
        // because old style drawing did kind of work even
        // without calling SetInputContext( ... )
        iInputContext = CAknsFrameBackgroundControlContext::NewL(
            KAknsIIDQsnFrInput, TRect(0,0,0,0), TRect(0,0,0,0), EFalse );
        iFlags = iFlags | EOwnsInputContext;
        // also need to provide skin for the editor in this case
        static_cast<CEikEdwin*>( iField )->SetSkinBackgroundControlContextL( iInputContext );
        }

    if ( iInputContext )
        {
        // this layout is actually from form!
        // there exists no layout for find box :-/ but this should do
        // no help from adaptation layer either
        r.LayoutRect( iOutlineRect, AknLayoutScalable_Avkon::input_focus_pane_g1() );
        iInputContext->SetFrameRects( iOutlineRect, r.Rect() );

        // and chain transparent contexts properly
        MAknsControlContext* bg = iPopupFindCC ? iPopupFindCC : iPopupListCC;
        if( !bg )
            {
            bg = AknsDrawUtils::ControlContext( this );
            }
        iInputContext->SetParentContext( bg );
        }

    // --- set magnifying glass icon size & position ---
    iMagnIconPos.LayoutRect( parent, iconPos);
    CFbsBitmap* iconBitmap = iIcon->Bitmap();
    if ( iconBitmap  )
        {
        AknIconUtils::SetSize( iconBitmap, iMagnIconPos.Rect().Size() );
        }
    // --- layout the editor ---
    AknLayoutUtils::LayoutEdwin( static_cast<CEikEdwin*>( iField ),
                                 editorParent,
                                 editor.LayoutLine(),
                                 EAknsCIQsnTextColorsCG25,
                                 0,
                                 ETrue );    
                                 
    AknsUtils::RegisterControlPosition( iField );  // prevent flicker
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TSize CAknInputFrame::MinimumSize()
    {        
    return TSize(0,0);
    }
 
void CAknInputFrame::FocusChanged( TDrawNow aDrawNow )
    {
    iField->SetFocus( IsFocused(), aDrawNow );
    }

void CAknInputFrame::Draw( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    TRect rect( Rect() );
    
    if ( iFlags & EPopupLayout ) // popup find box
        {
        // draw background behind the frame
        AknsDrawUtils::Background( skin, cc, this, gc, rect );
        // draw background & frames of popup find window
        AknsDrawUtils::Background( skin, iPopupFindCC, gc, rect );
        }
    else if ( iFlags & EPopupWindowLayout ) // popuplist / list query
        {    
        // If softkeys are embedded to popup, background is drawn in popup
        if ( !( iFlags & EPopupWindowEmbeddedSoftkeys ) )
            {
            AknsDrawUtils::Background( skin, iPopupListCC, gc, rect );
            }
        }
    else  // standard fixed find pane or pinboard
        {
        // 'this' is required for parent absolute layouts 
        AknsDrawUtils::Background( skin, cc, this, gc, rect );
        }


    // draw the frame (and bg) around editor. currently same for all layouts
    // We have to use BackGround() because
    // - frame is transparent
    // - frame has parent context if popup layout is used
    // - frame also acts as background for the editor
    // 'this' is required for parent absolute layouts 
    AknsDrawUtils::BackgroundBetweenRects( skin, iInputContext, this, gc, iOutlineRect, iField->Rect() );
    
    // draw the icon
    CFbsBitmap* iconBitmap = iIcon->Bitmap();
    CFbsBitmap* iconMask = iIcon->Mask();
    iMagnIconPos.DrawImage( gc, iconBitmap, iconMask );
    }


EXPORT_C void CAknInputFrame::SetLineState(TBool aLineVisible)
    {
    if (!aLineVisible)
        {
        iFlags |= EFixedFindWithoutLine;
        }
    else
        {
        iFlags &= ~EFixedFindWithoutLine;
        }
    }

EXPORT_C void CAknInputFrame::SetInputContext(CAknsFrameBackgroundControlContext* aContext)
    {
    if ( iInputContext && iFlags & EOwnsInputContext )
        {
        delete iInputContext;
        iInputContext = NULL;
        iFlags = iFlags &~ EOwnsInputContext;
        }
    iInputContext = aContext;
    }

void CAknInputFrame::CreateIconL()
	{
    CFbsBitmap *icon;
    CFbsBitmap *mask;
    
    TSize iconSize( 0, 0 );
    
    if ( iIcon && iIcon->Bitmap() )
        {
        iconSize = iIcon->Bitmap()->SizeInPixels();         
        }
    
    AknsUtils::CreateIconL( AknsUtils::SkinInstance(),
                                iIconSkinID,
                                icon, mask, *iFileName, iBitmapId, iMaskId );

    delete iIcon;
    iIcon = NULL;
    
    iIcon = CGulIcon::NewL(icon, mask);                                 

    if ( iconSize != TSize( 0, 0 ) )
        {
        AknIconUtils::SetSize( iIcon->Bitmap(), iconSize );
        }
	}
	


void CAknInputFrame::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    switch ( aType )
        {
        case KAknsMessageSkinChange:
        case KEikDynamicLayoutVariantSwitch:
            CreateIconL();
            break;
            
        default:
            break;
        }
    }
// End of File
