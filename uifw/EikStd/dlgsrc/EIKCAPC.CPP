/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikcapc.h>
#include <coemain.h>
#include <barsread.h>
#include <eikenv.h>
#include <eikon.hrh>
#include <eikbctrl.h>
#include <eiksfont.h>
#include <gulcolor.h>
#include <eikimage.h>
#include <eikappui.h>
#include <eikbtgpc.h>

#include <eikedwin.h>
#include <frmtlay.h>

#include <eikdialg.pan>
#include <AknUtils.h>  // Avkon drawing utilities 
#include <aknenv.h>
#include <AknDef.h>
#include <aknconsts.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <AknPopupFieldText.h>
#include <aknslider.h> 
#include <eikseced.h>
#include <eikdpage.h>
#include <eikdialogext.h>
#include <eikcapca.h>
#include <eikmfne.h>
#include <eikform.pan>
#include <eikdpobs.h>
#include <eikdpsel.h>
#include <gulicon.h>
#include <gdi.h>  // for CEikCapCLabel
#include <biditext.h> // for TDirectionality
#include <AknBidiTextUtils.h>
#include <AknIconUtils.h>
#include <AknPanic.h>
#include <touchfeedback.h>

#include <AknTasHook.h> // for testability hooks
//<SKIN>
#include <AknsDrawUtils.h>
#include <AknsUtils.h>
#include <AknsListBoxBackgroundControlContext.h>
#include <AknsFrameBackgroundControlContext.h>
#include <skinlayout.cdl.h>
#include <aknappui.h>

#include <aknlayoutscalable_avkon.cdl.h>
#include <aknextendedinputcapabilities.h>
#include "EIKFANIM.H"

//#define BLACKBACKGROUND  // useful when debugging form layout.


#if defined( RD_SCALABLE_UI_V2)
//class CAknButton is available from week 20 version 5.0 onwards
#include "aknbutton.h"
#include <avkon.mbg>
// For MAknMfneCommandObserver
#include <aknmfnecommandobserver.h>
#endif //if defined( RD_SCALABLE_UI_V2)



GLREF_C void Panic(TEikDialogPanic aPanic);

const TInt KViewHighlightColor = 244 ;
// const TInt KViewHighlightShadowColor = 222 ; 
// const TInt KNormalBackgroundColor = 0 ;


// Do not reference these directly... Use MaximumNumberOfControlLinesOnVisiblePage() 
// const TInt KMaxControlLinesOnPageSingleLineFormat =6;
// const TInt KMaxControlLinesOnPageDoubleLineFormat =5;

enum
    {// must carry on from TSpaceSharingFlags
    EUsesEars       =0x10,
    ELeftEarDown    =0x20,
    ERightEarDown   =0x40,
    ELeftEarGrab    =0x80,
    ERightEarGrab   =0x100,
    ECurrent        =0x200,
    ESeparatorAfter =0x400,
    EExtraAscent    =0x800,
    ELatent         =0x1000,
    ELglf           =0x2000,
    ETakesEnterKey  =0x4000,
    EOfferAllHotKeys=0x8000,
    ETrailerAfterEar=0x10000,
    ENoBorder       = 0x20000
    };

const TInt KDynamicEarMask=(ELeftEarDown|ERightEarDown|ELeftEarGrab|ERightEarGrab);

const TInt KCapCDefaultHorzEdgeSpacing=0;
const TInt KCapCDefaultVertEdgeSpacing=0; 
const TInt KCapCCenterSpacing=0;
const TInt KControlTrailerSpacing=0;
// const TInt KCapCEarHeightTopHalf=0;
// const TInt KCapCEarHeightBottomHalf=0;
// const TInt KCapCEarHeight=KCapCEarHeightTopHalf+KCapCEarHeightBottomHalf;
const TInt KCapCEarWidth=0;
const TInt KCapCEarSpacing=0;
const TInt KCapCVertCaptionOffset=0;
const TInt KCapCExtraAscent=KCapCVertCaptionOffset+0;
const TInt KTrailCVertCaptionOffset=0;
const TInt KCapCSeparatorAfterSpace=0;

const TInt KCapCInitialEarRepeat=600000;    // 6 tenths of a second
const TInt KCapCEarRepeat=100000; // one tenth of a second

/*
 *  The following set of static functions return value which have been hard coded from the Series 60 Skins LAF v2.0
 *  If a layout DLL becomes available the hard-coded values may be replaced with equivalent Macros.
 *  NOTE THAT THERE ARE COPIES OF SOME OF THESE FUNCTIONS IN EIKDPAGE.CPP
 */

/*
* Note, that table numbers have changed, 5.24 is 5.26 in current (3.1) laf,
* and 5.17 seems to be 5.16
* Also, these original hard coded values mostly ignore l & t fields, as
* code only wants to know W & H, and it will break if l & t are used
* comments indicate overriden values
*/

LOCAL_D TRect EditFrameTopLeftRect( const TRect& aParentRect )
    {// Skins LAF table 5.24 Line 2
    TAknLayoutRect topLeft ;
    topLeft.LayoutRect( aParentRect, SkinLayout::Input_field_skin_placing__general__Line_2() ); 
    TRect rectTopLeft( topLeft.Rect() );
    return rectTopLeft;
    }

LOCAL_D TRect EditFrameTopRightRect( const TRect& aParentRect )
    {// Skins LAF table 5.24 Line 3
    TAknLayoutRect topRight ;  
    TAknWindowLineLayout l( SkinLayout::Input_field_skin_placing__general__Line_3() );
    // l field should be w - 3
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParentRect, l );
    TRect rectLayout( layoutRect.Rect() );

	// COMPLETELY BROKEN -- SHOULD NEVER INVENT OWN COORDINATES FOR LAYOUTRECT().
    //topRight.LayoutRect( aParentRect, ELayoutEmpty, ELayoutEmpty, 0, 0, ELayoutEmpty, rectLayout.Width(), rectLayout.Height() ) ;
    //TRect rectTopRight( topRight.Rect() );

    return rectLayout /*rectTopRight*/;
    }

LOCAL_D TRect EditFrameBottomLeftRect( const TRect& aParentRect )
    {// Skins LAF table 5.24 Line 4
    TAknLayoutRect bottomLeft ;
    TAknWindowLineLayout l( SkinLayout::Input_field_skin_placing__general__Line_4() );
    // t should be h-3
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParentRect, l );
    TRect rectLayout( layoutRect.Rect() );

	// COMPLETELY BROKEN -- SHOULD NEVER INVENT OWN COORDINATES FOR LAYOUTRECT().
    //bottomLeft.LayoutRect( aParentRect, ELayoutEmpty, 0, ELayoutEmpty, ELayoutEmpty, 0, rectLayout.Width(), rectLayout.Height() ) ;
    //TRect rectBottomLeft( bottomLeft.Rect() );

    return rectLayout /*rectBottomLeft*/;
    }

LOCAL_D TRect EditFrameBottomRightRect( const TRect& aParentRect )
    {// Skins LAF table 5.24 Line 5
    TAknLayoutRect bottomRight ;
    TAknWindowLineLayout l( SkinLayout::Input_field_skin_placing__general__Line_5() );
    // l should be w-3, t should be h-3
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParentRect, l );
    TRect rectLayout( layoutRect.Rect() );

	// COMPLETELY BROKEN -- SHOULD NEVER INVENT OWN COORDINATES FOR LAYOUTRECT().
    //bottomRight.LayoutRect( aParentRect, ELayoutEmpty, ELayoutEmpty, ELayoutEmpty, 0, 0, rectLayout.Width(), rectLayout.Height() ) ;
    //TRect rectBottomRight( bottomRight.Rect() );

    return rectLayout /*rectBottomRight*/;
    }

LOCAL_D TRect EditFrameTopRect( const TRect& aParentRect )
    {// Skins LAF table 5.24 Line 6
    TAknLayoutRect top ;
    TAknWindowLineLayout l (SkinLayout::Input_field_skin_placing__general__Line_6() );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParentRect, l );
    TRect rectLayout( layoutRect.Rect() );

	// COMPLETELY BROKEN -- SHOULD NEVER INVENT OWN COORDINATES FOR LAYOUTRECT().
    //top.LayoutRect( aParentRect, ELayoutEmpty, rectLayout.iTl.iX, rectLayout.iTl.iY, ELayoutEmpty, ELayoutEmpty, aParentRect.Width()+rectLayout.Width(), rectLayout.Height() ) ;
    //TRect rectTop( top.Rect() );

    return rectLayout /*rectTop*/;
    }

LOCAL_D TRect EditFrameBottomRect( const TRect& aParentRect )
    {// Skins LAF table 5.24 Line 7
    TAknLayoutRect bottom ;
    TAknWindowLineLayout l (SkinLayout::Input_field_skin_placing__general__Line_7() );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParentRect, l );
    TRect rectLayout( layoutRect.Rect() );

	// COMPLETELY BROKEN -- SHOULD NEVER INVENT OWN COORDINATES FOR LAYOUTRECT().
    //bottom.LayoutRect( aParentRect, ELayoutEmpty, rectLayout.iTl.iX, 0, aParentRect.Height()+rectLayout.iTl.iY, ELayoutEmpty, aParentRect.Width()+rectLayout.Width(), rectLayout.Height() ) ;
    //TRect rectBottom( bottom.Rect() );

    return rectLayout /*rectBottom*/;
    }


LOCAL_D TRect ViewFrameTopLeftRect( const TRect& aParentRect )
    {// Skins LAF table 5.17 line 2
    TAknLayoutRect topLeft ;
    topLeft.LayoutRect( aParentRect, SkinLayout::List_highlight_skin_placing__general__Line_2() );
    TRect rectTopLeft( topLeft.Rect() );

    return rectTopLeft;
    }

LOCAL_D TRect ViewFrameBottomRightRect( const TRect& aParentRect )
    {// Skins LAF table 5.17 line 5
    TAknLayoutRect bottomRight ;
    TAknWindowLineLayout l ( SkinLayout::List_highlight_skin_placing__general__Line_5() );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParentRect, l );
    TRect rectLayout( layoutRect.Rect() );

	// COMPLETELY BROKEN -- SHOULD NEVER INVENT OWN COORDINATES FOR LAYOUTRECT().
    //bottomRight.LayoutRect( aParentRect, ELayoutEmpty, ELayoutEmpty, ELayoutEmpty, 0, 0, rectLayout.Width(), rectLayout.Height() ) ;
    //TRect rectBottomRight( bottomRight.Rect() );

    return rectLayout;
    }


LOCAL_D TInt ScaledSubLength(TInt aScaledTotal, TInt aSubLength, TInt aTotal)
    {
	if(aTotal)
		return ((aSubLength*aScaledTotal)+(aTotal/2))/aTotal;
	else
		return aScaledTotal;
    }

LOCAL_D TBool IsPopupField(const CEikCaptionedControl* aCC)
{
	TInt ctrlType = aCC->iControlType;
	if (ctrlType == EAknCtPopupField || ctrlType == EAknCtPopupFieldText)
	{
		CAknPopupField *field = (CAknPopupField*)aCC->iControl;
		if (field->SelectionMode() != CAknPopupField::EAknPopupFieldLabelMode)
			return ETrue;
		return EFalse;
	}
	return EFalse;
}

class CIdleCallbackData;
/**
* 
* Extension class for additional data members.
*
*/
NONSHARABLE_CLASS( CEikCapCExtension ): public MEikFormAnimObserver
    {
    friend class CEikCaptionedControl ;

private:
    CEikCapCExtension();
    ~CEikCapCExtension();

    TBool IsHighlightAnimated() const;
    void SkinChanged();
    void HandleLayoutSwitch( const TSize& aSize );

    // Implementation of MEikFormAnimObserver
    void AnimFrameReady();
    TBool AnimDrawHighlightBackground( CFbsBitGc& aGc );

    /**
     * Simulates pointer event to control if required.
     * 
     * @param aPointerEvent Received pointer event.
     */
    void SimulatePointerEventToControlL( const TPointerEvent& aPointerEvent );

    /**
     * Returns ETrue if control launches a virtual input when tapped.
     * 
     * @return ETrue if virtual input should be launched.
     */
    TBool LaunchInputType() const;

private:    //Data members.  None owned.
    CEikCaptionedControl* iSelf ; // pointer to full class
    CAknsFrameBackgroundControlContext* iEditModeHighlightControlContext ;
    CAknsFrameBackgroundControlContext* iViewModeHighlightControlContext ;
    CAknsFrameBackgroundControlContext* iEditModeHighlightControlContextPressed;
    CAknsFrameBackgroundControlContext* iViewModeHighlightControlContextPressed ;
    TRect iPreviousRect ;
    TBool iPreviousState ; // Editable state
    TBool iPressDownEffect; //Press Down Effect
    // Offset necessary because LAF instructs use of List Layout for Forms but the parent panes have different origins.
    TInt iXOffsetForDataPaneInEditMode ;
    TInt iYOffsetForDataPaneInEditMode ;

    TBool iDrawNoWhiteBackground;

    CEikFormAnim* iAnimation;

	CEikImage* iIndicator;
	CEikImage* iIndicator2;
	
	MPointerEventObserver *iObserver;

    /**
     * ETrue if to control is sent simulated down event.
     */
    TBool iSimulatedDownEvent;

    /**
     * Tactile feedback provider.
     * Not own.
     */
    MTouchFeedback* iFeedback;

public: // needs to be public because idle callback uses these members.
	CIdle *iIdle;
	CIdleCallbackData *iIdleData;
    /** iPartiallyVisible is used as a protection from changing subcontrol positions of 
      * partially-visible controls in PositionFormComponents(). This is needed only for
      * dynamic screen size change.
      */
    TBool iPartiallyVisible;
    
    /**
     * Boolean used to check if application is single touch compatible.
     */
    TBool iUsesSingleClick;

private:

    } ;

NONSHARABLE_CLASS(CIdleCallbackData) : public CBase
{
public:
	CEikCaptionedControl *iCtrl;
	CEikCapCExtension *iExt;
};


CEikCapCExtension::CEikCapCExtension() : 
    // Member initialisaction list - all values to NULL/0
    iSelf( NULL ), 
    iEditModeHighlightControlContext ( NULL ) ,
    iViewModeHighlightControlContext ( NULL ) ,
    iEditModeHighlightControlContextPressed( NULL ),
    iViewModeHighlightControlContextPressed( NULL ),
    iPreviousRect( TPoint(0, 0), TSize(0, 0) ) ,
    iPreviousState( EFalse ) ,
    iPressDownEffect( EFalse ),
    iXOffsetForDataPaneInEditMode( ELayoutEmpty ) ,
    iYOffsetForDataPaneInEditMode( ELayoutEmpty ) ,
    iDrawNoWhiteBackground( EFalse ),
    iAnimation( NULL )
	, iIndicator(NULL),
	iIndicator2(NULL),
	iObserver(NULL),
    iFeedback( MTouchFeedback::Instance() ),
	iIdle(NULL),
	iIdleData(NULL),
    iPartiallyVisible( EFalse )
    {
    if ( iAvkonAppUi )
        {
        iUsesSingleClick = iAvkonAppUi->IsSingleClickCompatible();
        }
    };

CEikCapCExtension::~CEikCapCExtension()
    {
    // Remember to unacquire animation
    if( iAnimation && iSelf )
        {
        if( iSelf->iDialogPage )
            iSelf->iDialogPage->AcquireAnim( EFalse, this );
        }
    }

TBool CEikCapCExtension::IsHighlightAnimated() const
    {
    if( iAnimation )
        {
        if( iAnimation->Animation() )
            return ETrue;
        }

    // No animation available at all...
    return EFalse;
    }

void CEikCapCExtension::SkinChanged()
    {
    iAnimation = NULL;
    if( iSelf->iDialogPage )
        iAnimation = iSelf->iDialogPage->AcquireAnim( ETrue, this );

    if( iAnimation )
        {
        iAnimation->SetHighlightSize( iSelf->Rect().Size() );
        }
    }

void CEikCapCExtension::HandleLayoutSwitch( const TSize& aSize )
    {
    if( iAnimation )
        {
        if( iAnimation->Size() == aSize )
            {
            // No need to resize, just change the background used
            // as animation input.
            iAnimation->ChangeHighlightBackground();
            }
        else
            {
            iAnimation->SetHighlightSize( aSize );
            }
        }
    }

void CEikCapCExtension::AnimFrameReady()
    {
    if( iSelf )
        iSelf->DrawNow();
    }

TBool CEikCapCExtension::AnimDrawHighlightBackground( CFbsBitGc& aGc )
    {
    if( !iSelf->iDialogPage )
        return EFalse;

    // Draw the background under the current highlight. This simplified
    // drawing, we only grab a piece from the list background bitmap.
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( iSelf->iDialogPage );

    return AknsDrawUtils::DrawBackground( skin, cc, iSelf->iDialogPage, aGc, TPoint(0,0),
                                          iSelf->ViewRect(), KAknsDrawParamRGBOnly );
    }


void CEikCapCExtension::SimulatePointerEventToControlL(
        const TPointerEvent& aPointerEvent )
    {
    // Extend form item touch area to whole item area
    if ( iSelf->iIsEditable
         && ( aPointerEvent.iType == TPointerEvent::EButton1Down 
            || aPointerEvent.iType == TPointerEvent::EButton1Up ) )
        {

        // Check control type
        TBool edwinControl( LaunchInputType() );
        TBool simulate = EFalse;
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down
                && iSelf->Rect().Contains( aPointerEvent.iPosition )
                && !iSelf->iControl->Rect().Contains(
                        aPointerEvent.iPosition ) )
            {
            iSimulatedDownEvent = ETrue;
            if ( !edwinControl )
                {
                simulate = ETrue;
                }
            }
        else if ( aPointerEvent.iType == TPointerEvent::EButton1Up
                && iSimulatedDownEvent )
            {
            simulate = ETrue;
            }

        // Simulate pointer event to control
        if ( simulate && !edwinControl )
            {
            TPointerEvent controlEvent( aPointerEvent );
            controlEvent.iPosition =
                iSelf->iControl->Rect().iTl + TPoint( 1, 1 );
            iSelf->iControl->HandlePointerEventL( controlEvent );
            }

        // With edwin do action directly (due to cursor problems)
        else if ( edwinControl && simulate
                && aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            CAknExtendedInputCapabilities* input( NULL );
            iSelf->iControl->InputCapabilities().ObjectProvider(
                    )->MopGetObjectNoChaining( input );
            if ( input )
                {
                iFeedback->InstantFeedback(
                        iSelf->iControl, ETouchFeedbackEditor,
                        ETouchFeedbackVibra, aPointerEvent );
                input->ReportEventL(
                        CAknExtendedInputCapabilities::\
                        MAknEventObserver::EActivatePenInputRequest,
                        NULL );
                }
            }
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            iSimulatedDownEvent = EFalse;
            }
        }
    }


TBool  CEikCapCExtension::LaunchInputType() const
    {
    TBool launchInput( EFalse );

    switch( iSelf->iControlType )
        {
        case EEikCtEdwin:
        case EEikCtGlobalTextEditor:
        case EEikCtRichTextEditor:
        case EAknCtIntegerEdwin:
        case EEikCtFlPtEd:
        case EEikCtFxPtEd:
            {
            launchInput = ETrue;
            break;
            }
        default:
            {
            break;
            }
        }

    return launchInput || iSelf->ControlIsASecretEditor( iSelf->iControlType );
    }


NONSHARABLE_CLASS(CEikCaptionedControlFormHighlightLine) : public CCoeControl
    {
public:
        enum TTopOrBottom
            {
            EUnset,
            ETop,
            EBottom
            };
    CEikCaptionedControlFormHighlightLine( const CEikCaptionedControl& aParent ) : iCapCtl( aParent ) 
        { iTopOrBottom=EUnset; };
    void ConstructL() ;
    void Draw(const TRect& aRect) const;
    void SetTopOrBottom(TTopOrBottom aTopOrBottom) {iTopOrBottom=aTopOrBottom;};
    TInt HeightOfHighlight(TTopOrBottom aTopOrBottom) const;
private:
    TBool DrawingSkins() const ;
    const CEikCaptionedControl& iCapCtl ; // pointer to parent class
    TTopOrBottom iTopOrBottom;
   };

/**
* This draws the form highlight line
*
*/
void CEikCaptionedControlFormHighlightLine::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc=SystemGc();
    TBool drawn = EFalse;

    if ( IsVisible() && DrawingSkins() )
        {
        //<SKIN>
        MAknsSkinInstance* skin = AknsUtils::SkinInstance() ;

        // Drawn as three parts 
        if (iTopOrBottom == ETop)
            {
            AknsDrawUtils::DrawFramePart( skin, gc, EditFrameTopRect( Rect() ), KAknsIIDQsnFrInput, EAknsFrameIndexT ) ;
            AknsDrawUtils::DrawFramePart( skin, gc, EditFrameTopLeftRect( Rect() ), KAknsIIDQsnFrInput, EAknsFrameIndexTl );
            AknsDrawUtils::DrawFramePart( skin, gc, EditFrameTopRightRect( Rect() ), KAknsIIDQsnFrInput, EAknsFrameIndexTr );
            }
        else if (iTopOrBottom == EBottom)
            {
            AknsDrawUtils::DrawFramePart( skin, gc, EditFrameBottomLeftRect( Rect() ), KAknsIIDQsnFrInput, EAknsFrameIndexBl );
            AknsDrawUtils::DrawFramePart( skin, gc, EditFrameBottomRightRect( Rect() ), KAknsIIDQsnFrInput, EAknsFrameIndexBr );
            AknsDrawUtils::DrawFramePart( skin, gc, EditFrameBottomRect( Rect() ), KAknsIIDQsnFrInput, EAknsFrameIndexB );
            }
 
        drawn = ETrue ;
        }

    if ( IsVisible() && !drawn ) // old, non-skin, drawing code
        {
        if (!iTopOrBottom==EUnset)
            {
            // Assert control is the correct height.
            __ASSERT_DEBUG(Rect().Height()==HeightOfHighlight(iTopOrBottom), Panic(EEikDialogPanicFocusableLineWithIdZero));
// numbers used to just get data on how the line looks in terms of color.
            TRect someArbitraryRect=TRect(TPoint(0,0),TPoint(11,22));
            TInt someArbitraryNumber=0;
            TAknLayoutRect line2Rect;
            line2Rect.LayoutRect
                (someArbitraryRect,     
                AKN_LAYOUT_WINDOW_Form_data_field_elements_Line_2
                );
            TAknLayoutRect line3Rect;
            line3Rect.LayoutRect
                (someArbitraryRect,     
                AKN_LAYOUT_WINDOW_Form_data_field_elements_Line_3
                    ( someArbitraryNumber)
                );
            gc.SetPenStyle(CGraphicsContext::ESolidPen);
            gc.SetBrushStyle( CGraphicsContext::ENullBrush) ;

            if (iTopOrBottom == ETop)
                {
                // Draw solid black 2 pixel rectangle
                TRect rectToDraw=Rect();
                gc.SetPenColor( line3Rect.Color() ) ; // black line;
                gc.DrawRect(rectToDraw);
                // Draw grey line, over black
                rectToDraw.iTl.iY++; 
                rectToDraw.Shrink(1,0);
                gc.SetPenColor( line2Rect.Color() ) ; // Greyline;
                gc.DrawRect(rectToDraw);            
                }
            else if (iTopOrBottom == EBottom)
                {
                // Draw solid black 1 pixel rectangle (i.e. a line :-)
                TRect rectToDraw=Rect();
                gc.SetPenColor( line3Rect.Color() ) ; // black line;
                gc.DrawRect(rectToDraw);
                }
            }
        }
    };


TInt CEikCaptionedControlFormHighlightLine::HeightOfHighlight(TTopOrBottom aTopOrBottom) const
    {
    if ( DrawingSkins() ) 
        {
        // Also, what it skins is enabled, but this part has not skinning...
        switch (aTopOrBottom)
            {
            case ETop :
                return EditFrameTopRect( Rect().Size() ).Height();
            case EBottom :
                return EditFrameBottomRect( Rect().Size() ).Height();
        default:
            return 0;
            }
        }
    else // no skin - old code
        {
        switch (aTopOrBottom)
            {
        case ETop:
            return 2;
        case EBottom:
            return 1;
        default:
            return 0;
            };
        }
    }

void CEikCaptionedControlFormHighlightLine::ConstructL()
      {
      SetContainerWindowL(  iCapCtl  ) ;
      }


TBool CEikCaptionedControlFormHighlightLine::DrawingSkins() const
    {
    TBool drawingSkins = EFalse;
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance() ;
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( &iCapCtl ) ;
        CWindowGc& gc = SystemGc();
        drawingSkins = AknsDrawUtils::Background( skin, cc, this, gc, Rect(), KAknsDrawParamPrepareOnly ); 
        }
    return drawingSkins;
    }

EXPORT_C CEikCaptionedControl::CEikCaptionedControl() : iHasAppendedEditIndicator(EFalse)
    {
    iNumberOfLines = 1 ;  // default starting value
    AKNTASHOOK_ADD( this, "CEikCaptionedControl" );
    }

EXPORT_C CEikCaptionedControl::~CEikCaptionedControl()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition(this);
    AknsUtils::DeregisterControlPosition(iBitmap);
    AknsUtils::DeregisterControlPosition(iCaption);
    AknsUtils::DeregisterControlPosition(iControl);
    AknsUtils::DeregisterControlPosition(iTrailer);
    AknsUtils::DeregisterControlPosition(iHighlightControl);
    if ( ControlIsAnEdwin( iControlType ) )
        {
        static_cast<CEikEdwin*>( iControl )->SetEdwinObserver( NULL );
        }
    if (iIsFormControl && iControl) 
        iControl->SetFocus( EFalse);
    delete iControl;
    delete iCaptionText;
    delete iCaption;
    delete iTrailer;
    delete iToolTipText ;
    delete iBitmap ;
    delete iHighlightControl ;
    if ( iExtension )
        {
		delete iExtension->iIdle;
		delete iExtension->iIdleData;
        delete iExtension->iEditModeHighlightControlContext ;
        delete iExtension->iViewModeHighlightControlContext  ;
        delete iExtension->iEditModeHighlightControlContextPressed;
        delete iExtension->iViewModeHighlightControlContextPressed;
	    delete iExtension->iIndicator;
  		delete iExtension->iIndicator2;
        }
    delete iExtension ; 
    }

EXPORT_C void CEikCaptionedControl::SetPointerEventObserver(MPointerEventObserver *aObserver)
	{
	if (iExtension)	
		iExtension->iObserver = aObserver;
	}

MPointerEventObserver *CEikCaptionedControl::PointerEventObserver() const
	{
	if (iExtension)
		return iExtension->iObserver;
	return NULL;
	}

EXPORT_C void CEikCaptionedControl::SetUsesEars()
    {
    iCapCFlags&=(~EUsesEars) ;  // switch them off to make sure
    }

EXPORT_C void CEikCaptionedControl::SetExtraAscent()
    {
    iCapCFlags|=EExtraAscent;
    }

void CEikCaptionedControl::SetPictographCallBack()
    {
    if ( ControlIsAnEdwin( iControlType ) )
        {
        TCallBack cb( PictographAnimationCallBack, this );
        static_cast<CEikEdwin*>( iControl )->SetPictographAnimationCallBack( cb );
        }
    }

TInt CEikCaptionedControl::PictographAnimationCallBack( TAny* aPtr )
    {
    CEikCaptionedControl* me = static_cast<CEikCaptionedControl*>( aPtr );
    me->iHighlightControl->DrawNow();
    return KErrNone;
    }

EXPORT_C TSize CEikCaptionedControl::MinimumSize()
    {
// NTBD Add an extra line for those with the label on a separate 
    if ( iIsFormControl )
        {
        if (iControl->IsDimmed())
            {
            iSize = TSize( 0, 0) ; 
            return iSize;
            }
        // We can get the minimum size from the resource - and the size of the editor (EditorControlSize() in lines)
        CalculateNumberOfLinesForControl( ENotSupplied );

        // temporary hack
        TBool fixedNumOfLines(EFalse);
        if (ControlIsAnEdwin(iControlType) && iNumberOfLines == 0) 
            {
            iNumberOfLines = 1;
            fixedNumOfLines = ETrue;
            }
        // ---------------


        // TInt heightExpectedForNumberOfLines=0; (NOT USED)
		TRect layout = TRect(0,0,0,0);        
        TRect mainPaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPaneRect  );
		TAknLayoutRect l;
		l.LayoutRect(mainPaneRect, AknLayoutScalable_Avkon::listscroll_form_pane().LayoutLine());
		l.LayoutRect(l.Rect(), AknLayoutScalable_Avkon::list_form_gen_pane().LayoutLine());
		TRect parentRect = l.Rect();		
		
        if ( iNumberOfLines > 0 )
            {
            if ( iNumberOfLines > MaximumNumberOfControlLinesOnVisiblePage() ) // MAX LINES
                Panic( EEikDialogPanicControlIsBiggerThanPage ) ;

            switch ( FormLayout() )
                {
            case CEikDialogPage::ESingle :
                {
                TAknWindowLineLayout l;
		if (IsPopupField(this))
			l = AknLayoutScalable_Avkon::form_field_popup_pane(iNumberOfLines - 1).LayoutLine();
		else
			l = AknLayoutScalable_Avkon::form_field_data_pane(iNumberOfLines - 1).LayoutLine();
                
                TAknLayoutRect layoutRect;

                layoutRect.LayoutRect( parentRect, l );
                TRect rectSingle( layoutRect.Rect() );
				layout = layoutRect.Rect();
                //heightExpectedForNumberOfLines = rectSingle.Height();
                }
                break ;
            case CEikDialogPage::EDouble :
                {
                TAknWindowLineLayout l;
		if (IsPopupField(this))
			l = AknLayoutScalable_Avkon::form_field_popup_wide_pane(iNumberOfLines - 1).LayoutLine();
		else
			l = AknLayoutScalable_Avkon::form_field_data_wide_pane(iNumberOfLines - 1).LayoutLine();
                TAknLayoutRect layoutRect;

                layoutRect.LayoutRect( parentRect, l );
                TRect rectDouble( layoutRect.Rect() );
				layout = layoutRect.Rect();
                //heightExpectedForNumberOfLines = rectDouble.Height();
                }
                break ;
            default :
                break ;
                }
            }
        // temporary hack continues
        if (fixedNumOfLines)
            {
            iNumberOfLines = 0;
            }
        // ------------------------

        iSize = layout.Size();
        return ( iSize ) ;
        }
    else
        {   
        TSize size=iControl->MinimumSize();
        TPoint ctlTl = iControl->Rect().iTl;
        TPoint ownTl = Rect().iTl;
        TRect mainPaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPaneRect );
                
        if (ctlTl.iX > ownTl.iX || ctlTl.iY > ownTl.iY)
            {
            size = size + (ctlTl - ownTl);   
            
            if ( size.iHeight > mainPaneRect.Size().iHeight && iDialogPage && 
                !( iDialogPage->PageContainer()->PageSelector()->Dialg()->
            	 DialogFlags() & EEikDialogFlagFillScreen )  &&
                 !iDialogPage->PageContainer()->PageSelector()->Dialg()->               
                Extension()->iPublicFlags.IsSet( CEikDialogExtension::EUseVirtualInput ) )
                {
                size.iHeight  =  mainPaneRect.Size().iHeight;
                }

            }
            
        if ( !iIsFormControl && iCaption && !(iCaption->Text()->Length()) )  
            // Non form controls mustn't have empty captions.
            {
            delete iCaption ;
            iCaption = NULL ;
            ResetMinimumSizes() ;
            }

        if (iCaption)
            {
            if (iCapCFlags&EExtraAscent)
                size.iHeight+=KCapCExtraAscent;
            TSize capSize=iCaption->MinimumSize();
            capSize.iHeight+=KCapCVertCaptionOffset;
            if (capSize.iHeight>size.iHeight)
                size.iHeight=capSize.iHeight;
            iCaptionWidth=capSize.iWidth+KCapCCenterSpacing;
            }
        if (iTrailer)
            {
            TSize trailSize=iTrailer->MinimumSize();
            trailSize.iHeight+=KTrailCVertCaptionOffset;
            if (trailSize.iHeight>size.iHeight)
                size.iHeight=trailSize.iHeight;
            size.iWidth+=trailSize.iWidth+KControlTrailerSpacing;
            }
        if ( iBitmap )
            {
            // Decisions... decisions...
            // Do we use the bitmap as is, or do we resize it?
            // Do we need some border spacing values added?
            TSize bitmapSize = iBitmap->MinimumSize() ;
            if ( bitmapSize.iHeight > size.iHeight )
                size.iHeight = bitmapSize.iHeight ;
            //T: size.iWidth += bitmapSize.iWidth ;
            iCaptionWidth += bitmapSize.iWidth ; // Include the bitmap in the caption 
            }
        if (iCapCFlags&EUsesEars)
            {
            size.iWidth+=KCapCEarWidth+KCapCEarSpacing;
            iCaptionWidth+=KCapCEarWidth+KCapCEarSpacing;
            }
        size.iHeight+=2*iVertEdgeSpacing;
        size.iWidth+=iCaptionWidth+2*iHorzEdgeSpacing;
        if (iCapCFlags&ESeparatorAfter)
            size.iHeight+=KCapCSeparatorAfterSpace;
        iMinSize=size;

        if ( iDoNotDisplay )
            // This flag is set if the control is not to be shown - so set it's height to zero
            iMinSize.iHeight = 0 ;
       return(size);
        }
    }
/**
* This routine should always called when any state affecting layout changed, including
* dynamically notified changes to the environment.
* 
* This is also called from Cone as a matter of course when SetRect is called on the object.
*/
EXPORT_C void CEikCaptionedControl::SizeChanged()
    {
    // Resize the animation
    if( iIsFormControl && iExtension->iAnimation )
        {
        iExtension->iAnimation->SetHighlightSize( Rect().Size() );
        }

    // If the size hasn't changed from the last time this was called we might be able to save a load of processing
#if ENABLE_BAD_OPTIMIZATION
    if ( iExtension->iPreviousRect != Rect() || iExtension->iPreviousState != iIsEditable || 
                    iDialogPage && iDialogPage->GetFormFlags() & CEikDialogPage::EFormForceEdwinResizeFlag )
        {
        iExtension->iPreviousRect = Rect() ;
        iExtension->iPreviousState = iIsEditable ;
        }
    else
        {
        return ;
        }
#endif
        // Routine is strictly in two parts. This part for Form layout.
    if (iIsFormControl)
        {
        // If Offset values have not been set up to adjust Layout for parent pane do so  now
        if ( iExtension->iXOffsetForDataPaneInEditMode == ELayoutEmpty || iExtension->iYOffsetForDataPaneInEditMode == ELayoutEmpty )
            {
            TRect mainPaneRect;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPaneRect );

            TAknLayoutRect formPaneRect ;
            // RWindow origin is same as mainPainRect origin, so move mainPaneRect to 0,0
			TAknWindowLineLayout dataPane = TAknWindowComponentLayout::Compose(
				AknLayoutScalable_Avkon::listscroll_form_pane(), 
				AknLayoutScalable_Avkon::list_form_gen_pane()).LayoutLine();
            formPaneRect.LayoutRect( TRect( TPoint(0 ,0 ), mainPaneRect.Size() ), dataPane ) ;
            
            iExtension->iXOffsetForDataPaneInEditMode = formPaneRect.Rect().iTl.iX ;
            iExtension->iYOffsetForDataPaneInEditMode = formPaneRect.Rect().iTl.iY ;
            }
        PositionFormComponents() ;
        LayoutSkinControlContexts();
        

        if (iIsEditable)
            {
            if (iBitmap && iBitmap->Bitmap())
                {
		TAknWindowLineLayout l = AknLayoutScalable_Avkon::form_field_data_wide_pane_g1().LayoutLine();
                TAknLayoutRect layoutRect;
                TRect parentRect = Rect();
                layoutRect.LayoutRect( parentRect, l );
                TRect rectElements( layoutRect.Rect() );

                AknIconUtils::SetSize(CONST_CAST(CFbsBitmap*, iBitmap->Bitmap()), 
                                      rectElements.Size() );
                }
            }
        else
            {
            if (iBitmap && iBitmap->Bitmap())
                {
                TAknWindowLineLayout l = AknLayout::List_pane_elements__single_graphic_heading__Line_1();
                TAknLayoutRect layoutRect;
                TRect parentRect = Rect();
                layoutRect.LayoutRect( parentRect, l );
                TRect rectElements( layoutRect.Rect() );

                AknIconUtils::SetSize(CONST_CAST(CFbsBitmap*, iBitmap->Bitmap()), 
                                      rectElements.Size() );
                }
            }
        }
    else
        {
        TRect rect=Rect();
        if(rect.Width()<MinimumSize().iWidth)
            {
            SquashComponents();
            }
        else
            {
            StretchComponents();
            }
        
        if (iBitmap && iBitmap->Bitmap())
        {
        TAknWindowLineLayout l = AknLayout::List_pane_elements__single_graphic_heading__Line_1();
        TAknLayoutRect layoutRect;
        TRect parentRect = Rect();
        layoutRect.LayoutRect( parentRect, l );
        TRect rectElements( layoutRect.Rect() );

        AknIconUtils::SetSize(CONST_CAST(CFbsBitmap*, iBitmap->Bitmap()), 
                              rectElements.Size() );
        }            
    }
    
    // This flag is also set in ConstructFromResourceL() but has to be re-visited once iIsFormControl has been set
    if ( !(iCapCFlags & ENoBorder) && iIsFormControl )
        {
        ((CEikBorderedControl*)iControl)->SetBorder( TGulBorder::ENone ) ;
        SetExtraAscent() ;
        iCapCFlags |= ENoBorder ;
        }

    if (iCaption)
        {
        TRAP_IGNORE(iCaption->SetTextL(*iCaptionText));
        iCaption->CropText(); 
        }

	if (iExtension && iExtension->iIndicator)
		{
		TInt variety = 0;
		if (iExtension->iIndicator2)
			variety = 1;
		AknLayoutUtils::LayoutImage(iExtension->iIndicator, Rect(), AknLayoutScalable_Avkon::form_field_data_wide_pane_g2(variety).LayoutLine());
		}
	if (iExtension && iExtension->iIndicator2)
		{
		AknLayoutUtils::LayoutImage(iExtension->iIndicator2, Rect(), AknLayoutScalable_Avkon::form_field_data_wide_pane_g3(1).LayoutLine());
		}


    // Deregister control positions. Registering new positions here
    // would cause undesired WS flush.
    // So, they are registered later in CEikDialogPage::SetDataPosition.

    AknsUtils::DeregisterControlPosition(this);
    AknsUtils::DeregisterControlPosition(iBitmap);
	if (iExtension)
		{		
    	AknsUtils::DeregisterControlPosition(iExtension->iIndicator);
    	AknsUtils::DeregisterControlPosition(iExtension->iIndicator2);
		}
    AknsUtils::DeregisterControlPosition(iCaption);
    AknsUtils::DeregisterControlPosition(iControl);
    AknsUtils::DeregisterControlPosition(iTrailer);
    AknsUtils::DeregisterControlPosition(iHighlightControl);
    
    if ( iIsFormControl && iDialogPage )
        {
        CEikEdwin* edwin = NULL;
        CEikMfne* mfne = NULL;
        
        if ( ControlIsAnEdwin( iControlType ) )
            {
            edwin = static_cast<CEikEdwin*>( iControl );
            edwin->SetSuppressBackgroundDrawing( ETrue );
            }
        else if ( ControlIsAMfne( iControlType ) )
            {
            mfne = static_cast<CEikMfne*>( iControl ); 
            mfne->SetSuppressBackgroundDrawing( ETrue );
            }
        
        iDialogPage->UpdateLineInCache( this );
        
        if ( edwin )
            {
            edwin->SetSuppressBackgroundDrawing( EFalse );
            }
        else if ( mfne )
            {
            mfne->SetSuppressBackgroundDrawing( EFalse );
            }
        }
    }


void CEikCaptionedControl::StretchComponents()
    {
    if (iCapCFlags&EIfTooSmallDontStrech)
    	return;
    
    TRect rect=Rect();
    rect.Shrink(iHorzEdgeSpacing,iVertEdgeSpacing);
    if (iCapCFlags&ESeparatorAfter)
        rect.iBr.iY-=KCapCSeparatorAfterSpace;

    const CFont* editorFont = AknLayoutUtils::FontFromId( iEditorFontId ) ;

    TInt normalEditorHeight = editorFont->HeightInPixels() + editorFont->DescentInPixels() + ( 2 * iVertEdgeSpacing ) ;
    if ( normalEditorHeight > rect.Height() )
        normalEditorHeight = rect.Height() ;

    // Insert Bitmap before caption 
    // Note, if position of caption & bitmap is to be configurable this routine will have to be re structured
    if ( iBitmap )
        {       
        TPoint bitmapTl = rect.iTl ;
        TSize bitmapSize = iBitmap->MinimumSize() ;
        if ( bitmapSize.iHeight > normalEditorHeight )
            {
            // reduce the size of the bitmap whilst retaining proportion. (will clip the bitmap methinks)
            TReal ratio = normalEditorHeight/bitmapSize.iHeight ;
            bitmapSize = TSize( TInt(bitmapSize.iWidth * ratio) , TInt(bitmapSize.iHeight * ratio) ) ;
            }
        //else
        //    bitmapTl.iY += ( normalEditorHeight - bitmapSize.iHeight ) ;
        iBitmap->SetExtent( bitmapTl, bitmapSize ) ;
    }
    if (iCaption)
        {
        TPoint capPos=rect.iTl;
        TSize capSize=iCaption->MinimumSize();
        // For SERIES60 the caption is aligned to the the right if the available space
        if ( iCaptionWidth > capSize.iWidth ) // & it should be!
            capPos.iX += ( iCaptionWidth - capSize.iWidth - KCapCCenterSpacing ) ;

        if ( capSize.iHeight > normalEditorHeight )
            capSize.iHeight = normalEditorHeight ;
        //capPos.iY += ( normalEditorHeight - capSize.iHeight /*- KCapCVertCaptionOffset*/           ) ;

        iCaption->SetExtent(capPos,capSize);
        if (iCapCFlags&EExtraAscent)
            rect.iTl.iY+=KCapCExtraAscent;
        }
    rect.iTl.iX+=iCaptionWidth;

    if ((iCapCFlags&EUsesEars) && !(iCapCFlags&ETrailerAfterEar))
        rect.iBr.iX-=(KCapCEarWidth+KCapCEarSpacing);

    if (iTrailer)
        {
        TSize trailSize=iTrailer->MinimumSize();
        TInt trailPosX=rect.iBr.iX-trailSize.iWidth;
        TInt trailPosY=rect.iTl.iY+KTrailCVertCaptionOffset;
        if(trailSize.iHeight+trailPosY>Rect().iBr.iY)
            trailSize.iHeight=Rect().iBr.iY-trailPosY;
        iTrailer->SetExtent(TPoint(trailPosX,trailPosY),trailSize);
        rect.iBr.iX=trailPosX-KControlTrailerSpacing;
        }
    if ((iCapCFlags&EUsesEars) && (iCapCFlags&ETrailerAfterEar))
        rect.iBr.iX-=(KCapCEarWidth+KCapCEarSpacing);

    if(iCapCFlags&EIfTooBigCtlStaysMinHeight && rect.Height()>iControl->MinimumSize().iHeight)
        rect.iBr.iY=rect.iTl.iY+iControl->MinimumSize().iHeight;
    if(iCapCFlags&EIfTooBigCtlStaysMinWidth && rect.Width()>iControl->MinimumSize().iWidth)
        rect.iBr.iX=rect.iTl.iX+iControl->MinimumSize().iWidth;
    iControl->SetRect(rect);
    
    }


TInt CEikCaptionedControl::WidthForEars(TInt aWidthRemaining) const
    {
    TInt earWidth=0;
    if(iCapCFlags&EUsesEars)
        {
        const TInt earAndMarginWidth=KCapCEarWidth+KCapCEarSpacing;
        if(iTrailer || iCaption)
            {
            if(aWidthRemaining>(2+(iTrailer?1:0)+(iCaption?1:0))*earAndMarginWidth)
                earWidth=earAndMarginWidth;
            else if(aWidthRemaining>(2+(iTrailer?1:0)+(iCaption?1:0))*KCapCEarWidth)
                earWidth=KCapCEarWidth;
            }
        else
            earWidth=Min(aWidthRemaining/2,earAndMarginWidth);
        }
    return earWidth;
    }


void CEikCaptionedControl::SquashComponents()
    {
    TRect rect=Rect();
    // Shrink for Separator
    if (iCapCFlags&ESeparatorAfter)
        rect.iBr.iY-=KCapCSeparatorAfterSpace;

    // Space required before the left of the control rect
    TInt desiredLeft=iHorzEdgeSpacing;
    if(iCaption)
        desiredLeft+=iCaption->MinimumSize().iWidth+KCapCCenterSpacing;
    if ( iBitmap )
        desiredLeft += iBitmap->MinimumSize().iWidth ; // + additional separation?

    // Space required after the right of the control rect
    TInt desiredRight=iHorzEdgeSpacing;
    if(iTrailer)
        desiredRight+=iTrailer->MinimumSize().iWidth+KControlTrailerSpacing;
    
    // Decide on space for the control rect.
    TInt controlWidth=0;
    TInt desiredControl=0;
    TInt widthRemaining=rect.Width();
    if(iControl)
        {
        desiredControl=iControl->MinimumSize().iWidth;
        if(iCapCFlags&EIfTooSmallCtlGetsWidthFirst)
            controlWidth=Min(desiredControl,widthRemaining);
        else if(iCapCFlags&EIfTooSmallCtlGetsEqualShareOfWidth)
            controlWidth=ScaledSubLength(widthRemaining,desiredControl,MinimumSize().iWidth);
        else
            controlWidth=Max(0,widthRemaining-(desiredLeft+desiredRight+2*(KCapCEarWidth+KCapCEarSpacing)));
        widthRemaining-=controlWidth;
        }
    
    // Decide if there is space for ears with margins, ears only, or no ears.
    TInt earWidth=WidthForEars(widthRemaining);
    widthRemaining-=2*earWidth;
    
    // Space assigned for before the left of the control rect
    TInt actualLeft=0;
    actualLeft=ScaledSubLength(widthRemaining,desiredLeft,desiredLeft+desiredRight);
    // Space assigned for after the right of the control rect
    TInt actualRight=widthRemaining-actualLeft;
	TInt actualCaption = actualLeft;

    // Check in debug builds that actualRight is the same (+/-1) to what would be calculated
    __ASSERT_DEBUG(((desiredRight==0)||(ScaledSubLength(widthRemaining,desiredRight,desiredLeft+desiredRight)<actualRight+2
        || ScaledSubLength(widthRemaining,desiredRight,desiredLeft+desiredRight)>actualRight-2)),
        User::Invariant()); // check our calculations!

    // Decide if there is room in actualLeft for caption only, or caption with margins.
    if ( iBitmap )
        {
        // slip the bitmap in before the caption.   
        TPoint bitmapTl = rect.iTl ;
        // Offset from top of rectangle in here ( bitmapTl.iY += vertical offset )
        TSize bitmapSize = iBitmap->MinimumSize() ;
        if ( (bitmapSize.iHeight + bitmapTl.iY) > Rect().iBr.iY )
            bitmapSize.iHeight = (Rect().iBr.iY - bitmapTl.iY ) ;
        iBitmap->SetExtent( bitmapTl, bitmapSize ) ;
		actualCaption = Max(0, actualLeft-bitmapSize.iWidth);
        }
        
    if(iCaption)
        {
        TRect captionRect=rect;
        captionRect.iTl.iY+=KCapCVertCaptionOffset;
        captionRect.iTl.iX+=actualLeft-actualCaption;
        captionRect.iBr.iX=captionRect.iTl.iX+actualCaption;
        if (iCapCFlags&EExtraAscent)
            rect.iTl.iY+=KCapCExtraAscent;
        
        if(actualLeft>2*(KCapCCenterSpacing+iHorzEdgeSpacing))
                {
                captionRect.iTl.iX+=iHorzEdgeSpacing;
                captionRect.iBr.iX-=KCapCCenterSpacing;
                }
        const TSize capMin=iCaption->MinimumSize();
        iCaption->SetExtent(captionRect.iTl,TSize(Min(captionRect.Width(),capMin.iWidth)
            ,Min(captionRect.Height(),iCaption->MinimumSize().iHeight)));
        }
    
    // Decide if there is room in actualRight for trailer only, or trailer with margins.
    if(iTrailer)
        {
        TInt leftAdjust=0;
        TInt rightAdjust=0;
        TRect trailerRect=rect;
        trailerRect.iTl.iX+=actualLeft+controlWidth+(iCapCFlags&EUsesEars ? earWidth : 0);
        trailerRect.iTl.iY+=KTrailCVertCaptionOffset;

        if(actualRight>2*(iHorzEdgeSpacing+KControlTrailerSpacing))
            {
            if(iCapCFlags&ETrailerAfterEar)
                {
                leftAdjust=KControlTrailerSpacing+earWidth;
                rightAdjust=iHorzEdgeSpacing;
                }
            else
                {
                rightAdjust=earWidth+iHorzEdgeSpacing;
                leftAdjust=KControlTrailerSpacing;
                }
            }
        else
            {
            if(iCapCFlags&ETrailerAfterEar)
                leftAdjust=earWidth;
            else
                rightAdjust=earWidth;
            }
        trailerRect.iTl.iX+=leftAdjust;
        trailerRect.iBr.iX-=rightAdjust;
        iTrailer->SetExtent(trailerRect.iTl,TSize(trailerRect.Width(),
            Min(trailerRect.Height(),iTrailer->MinimumSize().iHeight)));
        }
    // Position and set the controls space
    TRect controlRect=rect;
    controlRect.iTl.iX+=actualLeft+earWidth;
    controlRect.iBr.iX-=(actualRight+earWidth);
    if(iCapCFlags&EIfTooBigCtlStaysMinHeight && controlRect.Height()>iControl->MinimumSize().iHeight)
        controlRect.iBr.iY=controlRect.iTl.iY+iControl->MinimumSize().iHeight;
    iControl->SetRect(controlRect);
    
    }



/**
 * Sets the flags, aFlags, (see TSpaceSharingFlags), which determine
 * the way space is distributed if the captioned control is given too
 * much or too little space, relative to its minimum size.
 *
 */
EXPORT_C void CEikCaptionedControl::SetSpaceSharingFlags(TInt aFlags)
    {
    iCapCFlags|=aFlags;
    }


static TInt IdleCallback(TAny *aAny)
{
	CIdleCallbackData *data = (CIdleCallbackData*)aAny;
	CEikCapCExtension *ext = data->iExt;
	CEikCaptionedControl *ctrl = data->iCtrl;

	CEikEdwin *edwin = (CEikEdwin*)ctrl->iControl;
	ctrl->DrawNow();
	TInt textLength = edwin->TextLength();
	TRAP_IGNORE ( edwin->SetCursorPosL( (textLength>=0 ? textLength : 0), EFalse) );
	delete ext->iIdle;
	ext->iIdle = NULL;
	delete data;
	ext->iIdleData = NULL;
	return EFalse;	
}

void CEikCaptionedControl::ScrollBackEditor()
{
        //
		// For long single-line edwin, scroll horizontally to show beginning of the edwin
		// when focus changes away from the edwin.
		// 
      	if ( iIsEditable && ControlIsAnEdwin(iControlType) )
			{
			delete iExtension->iIdle;
			delete iExtension->iIdleData;
			iExtension->iIdleData = new (ELeave) CIdleCallbackData;
			iExtension->iIdleData->iCtrl = this;
			iExtension->iIdleData->iExt = iExtension;
			iExtension->iIdle = CIdle::NewL(0);
			iExtension->iIdle->Start(TCallBack(&IdleCallback, iExtension->iIdleData));
			}	
}

EXPORT_C void CEikCaptionedControl::FocusChanged(TDrawNow aDrawNow)
    {    
    // Only form controls need to adapt animation to focus changes.
    if( iExtension->iAnimation && iIsFormControl )
        {
        // Pause animation when losing focus (other states ignored)
        if( !IsFocused() )
            {
            iExtension->iAnimation->Pause();
            }
        else if( iIsCurrentLine && !iIsEditable ) // Current and in view mode
            {
            CAknAppUi* aui = static_cast<CAknAppUi*>(CEikonEnv::Static()->AppUi());
            if( aui->IsForeground() )
                {
                iExtension->iAnimation->Play();
                }
            }
        }

    TBool focused=IsFocused();
   
    if ( iIsFormControl )
        {
        // this bit can't be done in Draw() because that is a const function.
        // It shouldn't be done here either because it can leave but...
        TRgb brushColor;
        TRgb textColor;

        if ( iIsCurrentLine && !iIsEditable)
			{
            brushColor = AKN_LAF_COLOR( KViewHighlightColor ) ;
			}
        else
			{
            brushColor = ( iEikonEnv->ControlColor( EColorWindowBackground, *this ) ) ;
			}
        TRAP_IGNORE(
			{
			SetElementBrushColorsL( brushColor );
			SetElementTextColorsL( textColor );
			})

        // as focused has changed, need to layout the contained controls
        // all over again, to ensure that the highlight text colours are correct
        // Anyway, don't do this unless activated
        if (IsReadyToDraw())
            PositionFormComponents();

        if (iIsEditable)
            {
            SetPressedDownState( EFalse );

#if defined( RD_SCALABLE_UI_V2)        
            if( AknLayoutUtils::PenEnabled() )
                {
    			if(focused && ControlIsAMfne(iControlType))
    	    		{
    	    		CEikMfne* mfne = static_cast<CEikMfne*>(iControl);
    				mfne->SetFeature( CEikMfne::EFingerSupport, CEikMfne::EnableWithAllHighlight );
    	    		}
        		}
#endif  //if defined( RD_SCALABLE_UI_V2)  
        	iControl->SetFocus(focused,aDrawNow);	
            }
            
        }
    else
        {
        iControl->SetFocus(focused,aDrawNow);
        if (iCaption)
            {
            CEikLabel::TTextEmphasis emphasis=CEikLabel::EFullEmphasis;
            if (!focused)
                emphasis=(iCapCFlags&ECurrent? CEikLabel::EPartialEmphasis: CEikLabel::ENoEmphasis);
            iCaption->SetEmphasis(emphasis);
            }
        }
    

    if (aDrawNow && iCapCFlags&EUsesEars && IsReadyToDraw())
        DrawEarsNow(EBothEars);
    }



void CEikCaptionedControl::DrawEarsNow(TWhichEars aEar) const
    {
    ActivateGc();
    DrawEars(aEar);
    DeactivateGc();
    }

void CEikCaptionedControl::DrawEars(TWhichEars aEar) const
    {
    if (aEar&ELeftEar)
        DrawSingleEar(ELeftEar,iCapCFlags&ELeftEarDown);
    if (aEar&ERightEar)
        DrawSingleEar(ERightEar,iCapCFlags&ERightEarDown);
    }

void CEikCaptionedControl::DrawSingleEar(TWhichEars /*aEar*/,TBool /*aPressed*/) const
    {
    // not needed in S60
    }

TRect CEikCaptionedControl::EarRect(TWhichEars /*aEar*/) const
    {
    return(TRect(0,0,0,0)); // not needed in S60
    }

EXPORT_C TInt CEikCaptionedControl::CountComponentControls() const
    {
    CCoeControl* controls[] = 
    {
        iBitmap,
        iCaption,
        iControl,
        iTrailer,
        iHighlightControl, 
        iExtension->iIndicator,
		iExtension->iIndicator2
        };

    TInt count = 0;
    for (TUint ii=0; ii<sizeof(controls)/sizeof(CCoeControl*); ii++)
        {        
        if (controls[ii])
            {            
            count++;
            }
        }
    return count;
    }


EXPORT_C CCoeControl* CEikCaptionedControl::ComponentControl(TInt aIndex) const
    {
    CCoeControl* controls[] = 
        {
        iBitmap,
        iCaption,
        iControl,
        iTrailer,
        iHighlightControl,
		iExtension->iIndicator,
		iExtension->iIndicator2
        };

    for (TUint ii=0; ii<sizeof(controls)/sizeof(CCoeControl*); ii++)
        if (controls[ii] && aIndex-- == 0)
            return controls[ii];
    return NULL;
    }


EXPORT_C void CEikCaptionedControl::Draw(const TRect& aRect) const
    {   
    if (iIsFormControl )
        DrawAsForm( aRect );
    else
        DrawAsEikonDialog( aRect );
    }

void CEikCaptionedControl::DrawAsForm( const TRect& aRect ) const
    {

    CWindowGc& gc=SystemGc();

    gc.SetPenStyle(CGraphicsContext::ENullPen);
    if ( iRefresh )
        {
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
        gc.SetBrushColor( iEikonEnv->ControlColor( EColorWindowBackground, *this ) ) ;
        }

    if ( iCaption )
        {
// Draw ':' for edit indicator.  ( Skin independant )
        if ( iIsEditable && iIsCurrentLine )
            iCaption->EnableColon( ETrue ) ;
        else
            iCaption->EnableColon( EFalse ) ;
        }

    if (iHighlightControl)
        STATIC_CAST(CEikCaptionedControlFormHighlightLine*,iHighlightControl)->SetTopOrBottom(CEikCaptionedControlFormHighlightLine::EUnset);

    // assumed that CalculateNumberOfLinesForControl has been called                
    if (!iNumberOfLines)
        return;
    
     if( ControlIsASecretEditor(iControlType) && iIsCurrentLine )
        {
        CEikSecretEditor* edwin=(CEikSecretEditor*)iControl;
        edwin->EnableCursor( ETrue );
        }
    
    if ( DrawingSkins() || iExtension->iAnimation )
        {
        DrawAsSkinnedForm(gc, aRect);
        return;
        }

    if (iIsEditable && iIsCurrentLine )
        DrawAsFormInEditMode( aRect );
    else if (!iIsEditable && iIsCurrentLine )
        DrawAsFormInViewMode( aRect );
    else
        DrawAsFormUnFocusedLine( aRect );
    }

void CEikCaptionedControl::DrawAsFormInEditMode( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc=SystemGc();

    gc.SetPenStyle(CGraphicsContext::ENullPen);

    if ( iRefresh )
        {
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
        gc.SetBrushColor( iEikonEnv->ControlColor( EColorWindowBackground, *this ) ) ;
        }

    if (iDialogPage&& iHighlightControl)
        {
        TInt height(Rect().Height());
        TBool top = iDialogPage->VisibleSizeOnPage(height,iControl);
        if (height<Rect().Height())
            {
            CEikCaptionedControlFormHighlightLine::TTopOrBottom topOrBottom = (top) ? CEikCaptionedControlFormHighlightLine::ETop : CEikCaptionedControlFormHighlightLine::EBottom;
            TInt heightOfHighlight = STATIC_CAST(CEikCaptionedControlFormHighlightLine*,iHighlightControl)->HeightOfHighlight(topOrBottom);
// is off page, and needs a line drawing.
            TRect controlRect = (top) 
                ? TRect
                    (
                    TPoint(Rect().iTl.iX,Rect().iBr.iY-height),
                    TPoint(Rect().iBr.iX,Rect().iBr.iY-(height-heightOfHighlight))
                    )
                : TRect
                    (
                    TPoint(Rect().iTl.iX,Rect().iTl.iY+(height-heightOfHighlight)),
                    TPoint(Rect().iBr.iX,Rect().iTl.iY+height)
                    );
            iHighlightControl->SetRect(controlRect);
            STATIC_CAST(CEikCaptionedControlFormHighlightLine*,iHighlightControl)->SetTopOrBottom(topOrBottom); 
            iHighlightControl->MakeVisible( ETrue ) ;
            }
        else // control rect is not visible
            iHighlightControl->MakeVisible( EFalse ) ;
        }

    TInt noLinesToDraw =iNumberOfLines-1;
    if ( FormLayout() == CEikDialogPage::EDouble )
        ++noLinesToDraw;
    TAknLayoutRect line3Rect;
    line3Rect.LayoutRect
        (Rect(),    
        AKN_LAYOUT_WINDOW_Form_data_field_elements_Line_3
            ( noLinesToDraw )
        );
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
    gc.SetBrushColor( iEikonEnv->ControlColor( EColorWindowBackground, *this ) ) ;  
    gc.SetPenColor( line3Rect.Color() ) ;   
    gc.DrawRect(line3Rect.Rect());
    TAknLayoutRect line1Rect;
    line1Rect.LayoutRect
        (Rect(),    
        AKN_LAYOUT_WINDOW_Form_data_field_elements_Line_1
            ( noLinesToDraw )
        );
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetBrushStyle( CGraphicsContext::ENullBrush ) ;
    gc.SetPenColor( line1Rect.Color() ) ;   
    gc.DrawRect(line1Rect.Rect());
        TAknLayoutRect line2Rect;
        line2Rect.LayoutRect
        (Rect(),    
        AKN_LAYOUT_WINDOW_Form_data_field_elements_Line_2
        );
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetBrushStyle( CGraphicsContext::ENullBrush ) ;
    gc.SetPenColor( line2Rect.Color() ) ;   
    gc.DrawRect(line2Rect.Rect());
    }


void CEikCaptionedControl::DrawAsFormInViewMode( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc=SystemGc();

    gc.SetPenStyle(CGraphicsContext::ENullPen);

    if ( iRefresh )
        {
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
        gc.SetBrushColor( iEikonEnv->ControlColor( EColorWindowBackground, *this ) ) ;
        }

    // This gives the correct Rect for using the Layout functions
    TRect viewRect=ViewRect(); 

    TAknLayoutRect line1Rect;
    line1Rect.LayoutRect( viewRect, AKN_LAYOUT_WINDOW_List_pane_highlight_graphics__various__Line_1 (viewRect) );

    /* This is in view mode, and is the current line
    Do not clear the bit which will be recoloured in the next 
    draw, Instead, alter the GC drawing region to prevent this
    */
    TRegionFix<4> region(Rect());
    region.SubRect(line1Rect.Rect());                   
    for (TInt i=0;i< region.Count();i++)
        gc.Clear(region[i]);    

    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetPenColor(line1Rect.Color());
    gc.SetBrushStyle( CGraphicsContext::ENullBrush ) ;
    TRect rect=line1Rect.Rect();
    gc.DrawRect(rect);

    TAknLayoutRect line2Rect;
    line2Rect.LayoutRect
        (
        viewRect, 
        AKN_LAYOUT_WINDOW_List_pane_highlight_graphics__various__Line_2 (viewRect)  
        );
    line2Rect.DrawRect(gc);

    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetPenColor(iEikonEnv->ControlColor(EColorDialogText,*this));
    gc.SetBrushStyle( CGraphicsContext::ENullBrush ) ;

    TAknLayoutId layout;
    iAvkonEnv->GetCurrentLayoutId( layout );

    if ( layout == EAknLayoutIdAPAC )
        {
        gc.DrawLine(TPoint(iVerticalLineXPosition,Rect().iTl.iY),
            TPoint(iVerticalLineXPosition,Rect().iTl.iY+1));
        }

    else    // ELAF
        {
        gc.DrawLine(TPoint(iVerticalLineXPosition,Rect().iTl.iY),
            TPoint(iVerticalLineXPosition,Rect().iTl.iY+2));
        }

    gc.DrawLine(TPoint(iVerticalLineXPosition,Rect().iBr.iY-1),
        TPoint(iVerticalLineXPosition,Rect().iBr.iY+1));
    }
    
void CEikCaptionedControl::DrawAsFormUnFocusedLine( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc=SystemGc();

    gc.SetPenStyle(CGraphicsContext::ENullPen);

    if ( iRefresh )
        {
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
        gc.SetBrushColor( iEikonEnv->ControlColor( EColorWindowBackground, *this ) ) ;
        }

    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
    gc.SetBrushColor( iEikonEnv->ControlColor( EColorWindowBackground, *this ) ) ;  

    gc.DrawRect(Rect()); // clear region

    //list_single_heading_pane
/* 
offset of datapane is 1,7.  I'm afraid some mathematics here is unavoidable
In fact I will hard code this until later.
*/
// from LAF, color 210, position 50 - iXOffsetForDataPaneInEditMode
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetPenColor(iEikonEnv->ControlColor(EColorDialogText,*this));
    gc.SetBrushStyle( CGraphicsContext::ENullBrush ) ;
    gc.DrawLine(TPoint(iVerticalLineXPosition,Rect().iTl.iY),
        TPoint(iVerticalLineXPosition,Rect().iBr.iY+1));
    // CEikCaptionedControl* visibleBelow=0; (NOT USED)

    if (iDialogPage) 
        {
        // visibleBelow=iDialogPage->FindNextControlOnPageWithHeight(EFalse,this); 

        //draw separator line unless This control is at or off the top of the page.
        TBool atTopOfPage = (iDialogPage && iDialogPage->IsAtOrOffTopOfPage(iControl) );
        if (HasSeparator() && !atTopOfPage)
            DrawFormSeparator( gc );
        }
    } 


// ---------------------------------------------------------------------------
// CEikCaptionedControl::TextColorIndex
// ---------------------------------------------------------------------------
//
TAknsQsnTextColorsIndex CEikCaptionedControl::TextColorIndex() const
    {
    TAknsQsnTextColorsIndex colorIndex = EAknsCIQsnTextColorsCG8;

    // Note control doesn't use highlight text color
    if ( iControlType != EAknCtNote )
        {
        if ( iIsCurrentLine && iDialogPage->HighlightVisible() )
            {
            colorIndex = EAknsCIQsnTextColorsCG10;
            }
        }
    
    return colorIndex;
    }


void CEikCaptionedControl::DrawAsEikonDialog( const TRect& aRect ) const
    {
    CWindowGc& gc=SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);

    if (iHighlightControl)
        STATIC_CAST(CEikCaptionedControlFormHighlightLine*,iHighlightControl)->SetTopOrBottom(CEikCaptionedControlFormHighlightLine::EUnset);

    if ( iRefresh )
        {
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush ) ;
        gc.SetBrushColor( iEikonEnv->ControlColor( EColorWindowBackground, *this ) ) ;
        }


    TRect redrawRect=Rect();
    redrawRect.Intersection(aRect);

    /*
    *
    * FIX TSW JTON-6HGAND - see also eikdpage.cpp
    *
    *if (!iExtension->iDrawNoWhiteBackground)
    *    gc.DrawRect(redrawRect);
    *
    * Most likely other places using gc.Clear() ( or gc.DrawRect() as 'clear'
    * should be fixed also.
    */
    
    if (iCapCFlags&ESeparatorAfter)
        {
        TRect rect(Rect());
        TPoint separatorStartPt(rect.iTl.iX+iHorzEdgeSpacing/2,rect.iBr.iY-1);
        TPoint separatorEndPt(separatorStartPt.iX+(iFullWidth-iHorzEdgeSpacing), separatorStartPt.iY);
        gc.SetPenStyle(CGraphicsContext::ESolidPen);
        gc.SetPenColor(iEikonEnv->ControlColor(EColorWindowText, *this));
        gc.DrawLine(separatorStartPt, separatorEndPt);
        };

    if (iCapCFlags&EUsesEars)
        DrawEars(EBothEars); 
    }

/*
* Method to return T/F whether this CEikCaptionedControl has a separator.
*/
TBool CEikCaptionedControl::HasSeparator() const
    {
    return iCapCFlags & ESeparatorAfter;
    }


EXPORT_C TKeyResponse CEikCaptionedControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if ( !iIsFormControl) 
        return iControl->OfferKeyEventL(aKeyEvent,aType);
    else if ( iIsFormControl && iIsEditable )
        {
        TKeyResponse retVal ;
        retVal = iControl->OfferKeyEventL( aKeyEvent, aType ) ;
        return retVal ;
        }
    else
        return EKeyWasNotConsumed ;
    }

EXPORT_C TCoeInputCapabilities CEikCaptionedControl::InputCapabilities() const
    {
    return TCoeInputCapabilities(TCoeInputCapabilities::ENone, NULL, CONST_CAST(CEikCaptionedControl*, this));
    }

EXPORT_C void CEikCaptionedControl::SetDimmed(TBool aDimmed)
    {
    CCoeControl::SetDimmed(aDimmed);
    if (iControl && iControl->IsVisible())
        {
        iControl->SetDimmed(aDimmed);
        }
    if (iCaption)
        {
        iCaption->SetDimmed(aDimmed);
        }
    if (iTrailer)
        {
        iTrailer->SetDimmed(aDimmed);
        }
    }

EXPORT_C void* CEikCaptionedControl::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }   

EXPORT_C void CEikCaptionedControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if (!IsNonFocusing())
        {
        TWhichEars ear=ENoEar;
        if (aPointerEvent.iType!=TPointerEvent::EButton1Down)
            {
            if (iCapCFlags&ELeftEarGrab)
                ear=ELeftEar;
            else if (iCapCFlags&ERightEarGrab)
                ear=ERightEar;
            if (ear)
                {
                TInt oldDrawFlags=iCapCFlags&(ELeftEarDown|ERightEarDown);
                if (aPointerEvent.iType==TPointerEvent::EButton1Up)
                    iCapCFlags&=(~KDynamicEarMask);
                else
                    {
                    iCapCFlags&=(~(ELeftEarDown|ERightEarDown));
                    if (EarRect(ear).Contains(aPointerEvent.iPosition))
                        {
                        FireEarL(ear, KCapCEarRepeat);
                        return;
                        }
                    }
                if (oldDrawFlags!=(iCapCFlags&(ELeftEarDown|ERightEarDown)))
                    DrawEarsNow(ear);
                return;
                }
            }
        else if (iCapCFlags&EUsesEars)
            {
            iCapCFlags&=(~KDynamicEarMask);
            if (EarRect(ELeftEar).Contains(aPointerEvent.iPosition))
                ear=ELeftEar;
            else if (EarRect(ERightEar).Contains(aPointerEvent.iPosition))
                ear=ERightEar;
            if (ear)
                {
                FireEarL(ear, KCapCInitialEarRepeat);
                return;
                }
            }
        }
     if (iIsFormControl)
        {
        if ( PressedDownState()&&
            aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            SetPressedDownState( ETrue );
            DrawDeferred();    
            }
        else if(aPointerEvent.iType == TPointerEvent::EButton1Up)
            {
            SetPressedDownState( EFalse );
            DrawDeferred();
            }       
        }
    
    if ( !iIsEditable && (ControlIsAnEdwin(iControlType) || ControlIsAMfne(iControlType))
       &&( iDialogPage && CEikDialogPage::EDouble == iDialogPage->FormLayout() ))
        {
		return;
        }

    CCoeControl::HandlePointerEventL(aPointerEvent);    
     
    if ( iExtension )
        {
        iExtension->SimulatePointerEventToControlL( aPointerEvent );
        }
    }

void CEikCaptionedControl::FireEarL(TWhichEars aEar, TInt aEarRepeat)
    {
    Window().RequestPointerRepeatEvent(aEarRepeat, EarRect(aEar));
    TKeyEvent key;
    key.iModifiers=0;
    if (aEar==ELeftEar)
        {
        key.iCode=EKeyLeftArrow;
        iCapCFlags|=ELeftEarDown|ELeftEarGrab;
        }
    else
        {
        key.iCode=EKeyRightArrow;
        iCapCFlags|=ERightEarDown|ERightEarGrab;
        }
    DrawEarsNow(aEar);
    iControl->OfferKeyEventL(key,EEventKey);
    }

EXPORT_C void CEikCaptionedControl::SetCaptionL(const TDesC& aText)
    {
    ConstructExtensionL() ; // One of several places where this is made
    if (!iCaption)
        {
//      Retain a zero sized caption for formatting forms
        iCaption=new(ELeave) CEikCapCLabel;
        iCaption->SetNonFocusing();
        iCaption->SetFont( AknLayoutUtils::FontFromId( iCaptionFontId ) ) ;
        delete iCaptionText; // get rid of old iCaptionText
        iCaptionText=0;
        iCaptionText = aText.AllocL();
        }
        
    if (iCaption->DrawableWindow() == NULL)    
        {
        iCaption->SetContainerWindowL(*this);
        iCaption->CopyControlContextFrom(this);
        }
/*
Forms have truncated labels with elipses.  
iCaption should reflect this data
iCaptionText should contain the whoel string.
*/
    if (iIsFormControl)
        DoFormCaptionSettingsL(aText);
    else
        iCaption->SetTextL(aText);
    }

EXPORT_C void CEikCaptionedControl::SetDrawNoWhiteBackground(TBool aEnabled)
    {
    iExtension->iDrawNoWhiteBackground = aEnabled;
    }

EXPORT_C void CEikCaptionedControl::SetTrailerL(const TDesC& aText)
    {
    if (!aText.Length())
        return;
    if (!iTrailer)
        {
        iTrailer=new(ELeave) CEikLabel;
        iTrailer->SetFont( AknLayoutUtils::FontFromId( iCaptionFontId ) ) ;
        iTrailer->SetContainerWindowL(*this);
        iTrailer->CopyControlContextFrom(this);
        iTrailer->SetAllMarginsTo(1);
        iTrailer->SetNonFocusing();
        }
    iTrailer->SetTextL(aText);
    }

EXPORT_C void CEikCaptionedControl::SetCurrent(TBool aSelected)
    {
    SetCurrent( aSelected, ETrue );
    }

EXPORT_C void CEikCaptionedControl::ConstructFromResourceL(TResourceReader& aReader)
    {
    TPtrC capTextTPtrC = aReader.ReadTPtrC();
    iCaptionText = capTextTPtrC.AllocL();
    SetCaptionL(capTextTPtrC);
    iId=aReader.ReadInt16();
    TInt itemFlags=aReader.ReadInt32();
    TInt divider=itemFlags&EEikDlgItemSeparatorMask;
    if (divider==EEikDlgItemSeparatorAfter)
        {
        iCapCFlags|=ESeparatorAfter;
        SetCanDrawOutsideRect();
        }
    iControl->CopyControlContextFrom(this);
    iControl->ConstructFromResourceL(aReader);

    // For form items in SERIES60 the default is NOT to show the border
    // Unfortunately we can't tell at this point whether that is the case so
    // for the moment just remove the border completely
    if ( itemFlags&EEikDlgItemNoBorder )
        {
        ((CEikBorderedControl*)iControl)->SetBorder(TGulBorder::ENone);
        SetExtraAscent();
        iCapCFlags|=ENoBorder ;
        }
    if (itemFlags&EEikDlgItemNonFocusing)
        {
        SetNonFocusing();
        iControl->SetNonFocusing();
        iCapCFlags&=(~EUsesEars);
        }
    else
        {
        __ASSERT_DEBUG(iId!=0, Panic(EEikDialogPanicFocusableLineWithIdZero));
        }
    SetTrailerL(aReader.ReadTPtrC());
    if (itemFlags&EEikDlgItemLatent)
        SetLatent(ETrue);
    if (itemFlags&EEikDlgItemLglf)
        iCapCFlags|=ELglf;
    if (itemFlags&EEikDlgItemTakesEnterKey)
        iCapCFlags|=ETakesEnterKey;
    if (itemFlags&EEikDlgItemOfferAllHotKeys)
        iCapCFlags|=EOfferAllHotKeys;
    if (itemFlags&EEikDlgItemTrailerAfterEar)
        iCapCFlags|=ETrailerAfterEar;
    if(itemFlags&EEikDlgItemCtlMinHeightOrLess)
        iCapCFlags|=EIfTooBigCtlStaysMinHeight;
    if(itemFlags&EEikDlgItemCtlMinWidthOrLess)
        iCapCFlags|=EIfTooBigCtlStaysMinWidth;
    if(itemFlags&EEikDlgItemCtlGetsWidthFirst)
        iCapCFlags|=EIfTooSmallCtlGetsWidthFirst;
    else if(itemFlags&EEikDlgItemCtlSharesWidth)
        iCapCFlags|=EIfTooSmallCtlGetsEqualShareOfWidth; 
    if (itemFlags&EEikDlgItemCtlRefusesStrecth)
    	iCapCFlags|=EIfTooSmallDontStrech;

    // Process bmpfile, bmpid, bmpmask from Resource File.
    TPtrC16 bitmapFileName = aReader.ReadTPtrC() ;
    TInt16 bitmapId = TInt16(aReader.ReadInt16()) ;
    TInt16 bitmapMaskId = TInt16(aReader.ReadInt16()) ;
    if ( bitmapFileName.Length() != 0 )
        SetBitmapFromFileL( bitmapFileName, bitmapId, bitmapMaskId ) ;

    // Process ToolTip
    TPtrC16 toolTip = aReader.ReadTPtrC() ;
    SetToolTipTextL( toolTip ) ; 
    
    // Set the border spacing to the default value
    SetVertEdgeSpacing( KCapCDefaultVertEdgeSpacing ) ;
    SetHorzEdgeSpacing( KCapCDefaultHorzEdgeSpacing ) ;

    //Added to create new form box closer for edwins in forms.
    if (!iHighlightControl)
        {
        iHighlightControl = new(ELeave) CEikCaptionedControlFormHighlightLine( *this ) ;
        STATIC_CAST(CEikCaptionedControlFormHighlightLine*,iHighlightControl)->ConstructL() ;
        }
    ConstructExtensionL() ;
    }


EXPORT_C void CEikCaptionedControl::SetBitmapFromFileL( const TDesC& aFilename,TInt aMainId,TInt aMaskId /*=-1*/ ) 
    {
    if ( iBitmap )
        delete iBitmap;
    iBitmap = 0;

    iBitmap = new ( ELeave ) CEikImage();
    iBitmap->CreatePictureFromFileL( aFilename, aMainId, aMaskId );
    
    if (iBitmap && iBitmap->Bitmap())
        SetIconSizeL( CONST_CAST( CFbsBitmap*, iBitmap->Bitmap() ) );
 
    iBitmap->SetContainerWindowL(*this);
    iBitmap->CopyControlContextFrom(this);
    iBitmap->SetNonFocusing();
    iBitmap->SetBrushStyle(CGraphicsContext::ENullBrush );
    }

EXPORT_C void CEikCaptionedControl::CheckDimmedDisplayState()
    {
    TBool lineDimmed=(iControl->IsDimmed());
    SetDimmed(lineDimmed);
    if (iCaption)
        {
        iCaption->SetDimmed(lineDimmed);
        iCaption->DrawNow();
        }
    if (iTrailer)
        {
        TBool controlVisible=iControl->IsVisible();
        if (iTrailer->IsVisible()!=controlVisible)
            iTrailer->MakeVisible(controlVisible);
        iTrailer->SetDimmed(lineDimmed);
        iTrailer->DrawNow();
        }
    }

EXPORT_C void CEikCaptionedControl::ResetMinimumSizes()
    {
    iMinSize.iWidth=0;
    iCaptionWidth=0;
    iFullWidth=0;
    }

EXPORT_C TBool CEikCaptionedControl::IsLatent() const
    {
    return(iCapCFlags&ELatent);
    }

EXPORT_C void CEikCaptionedControl::SetLatent(TBool aLatent)
    {
    TBool visible=ETrue;
    iCapCFlags&=(~ELatent);
    if (aLatent)
        {
        iCapCFlags|=ELatent;
        visible=EFalse;
        }
    iControl->MakeVisible(visible);
    if (iCaption)
        iCaption->MakeVisible(visible);
    if (iTrailer)
        iTrailer->MakeVisible(visible);
    MakeVisible(visible);
    }

EXPORT_C TBool CEikCaptionedControl::LatentGroupLineFollows() const
    {
    return(iCapCFlags&ELglf);
    }

EXPORT_C void CEikCaptionedControl::SetLatentGroupLineFollows(TBool aLglf)
    {
    if (aLglf)
        iCapCFlags|=ELglf;
    else
        iCapCFlags&=(~ELglf);
    }

EXPORT_C TBool CEikCaptionedControl::DividerAfter() const
    {
    return(iCapCFlags&ESeparatorAfter);
    }

EXPORT_C void CEikCaptionedControl::SetDividerAfter(TBool aDividerAfter)
    {
    if (aDividerAfter)
        iCapCFlags|=ESeparatorAfter;
    else
        iCapCFlags&=(~ESeparatorAfter);
    }

EXPORT_C TBool CEikCaptionedControl::TakesEnterKey() const
    {
    return(iCapCFlags&ETakesEnterKey);
    }

EXPORT_C void CEikCaptionedControl::SetTakesEnterKey(TBool aTakesEnter)
    {
    if (aTakesEnter)
        iCapCFlags|=ETakesEnterKey;
    else
        iCapCFlags&=(~ETakesEnterKey);
    }

EXPORT_C TBool CEikCaptionedControl::OfferHotKeys() const
    {
    return iCapCFlags&EOfferAllHotKeys;
    }

EXPORT_C void CEikCaptionedControl::SetOfferHotKeys(TBool aOffer)
    {
    if (aOffer)
        iCapCFlags|=EOfferAllHotKeys;
    else
        iCapCFlags&=~EOfferAllHotKeys;
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikCaptionedControl::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CCoeControl::GetColorUseListL(aColorUseList);

    TCoeColorUse colorUse;
    colorUse.SetLogicalColor(EColorWindowText);
    colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|TCoeColorUse::ESurrounds|TCoeColorUse::ENormal|TCoeColorUse::ENeutral);
    aColorUseList.AppendL(colorUse);

    const TInt count=CountComponentControls();
    for(TInt ii=0;ii<count;ii++)
        ComponentControl(ii)->GetColorUseListL(aColorUseList);  
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikCaptionedControl::HandleResourceChange(TInt aType)
    {
    CCoeControl::HandleResourceChange(aType);

    // Animation is skin dependent, whenever skin changes animation changes
    // too.
    if( KAknsMessageSkinChange == aType )
        {
        TRAP_IGNORE( SetElementTextColorsL(TRgb()));

        if( iIsCurrentLine )
            {
            iExtension->SkinChanged();
            }
        }
    else if( KEikDynamicLayoutVariantSwitch == aType && iIsFormControl )
        {
        SizeChanged();
        CalculateNumberOfLinesForControl( ENotSupplied );
        if( iIsCurrentLine )
            {
            iExtension->HandleLayoutSwitch( Rect().Size() );
            }
        DrawDeferred();
        }
   }


/* Deactivated as requested in AISA-595AEZ
*/

EXPORT_C void CEikCaptionedControl::SetToolTipTextL( const TDesC& /*aText*/ ) 
    {
    }

EXPORT_C const TDesC* CEikCaptionedControl::ToolTipText() const 
    {
    if ( iToolTipText )
        return  iToolTipText ;
    else
        return NULL ;
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikCaptionedControl::WriteInternalStateL(RWriteStream&) const
    {}
#else
EXPORT_C void CEikCaptionedControl::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CCoeControl::WriteInternalStateL(aWriteStream);
    }
#endif

EXPORT_C void CEikCaptionedControl::Reserved_2()
    {}

EXPORT_C void CEikCaptionedControl::GetCaptionForFep(TDes& aCaption) const
    {
    if (iCaption==NULL)
        {
        aCaption=KNullDesC;
        }
    else
        {
        const TDesC* caption=iCaption->Text();
        if (caption==NULL)
            {
            aCaption=KNullDesC;
            }
        else
            {
            const TInt maximumLength=aCaption.MaxLength();
            if (caption->Length()>maximumLength)
                {
                aCaption=caption->Left(maximumLength);
                }
            else
                {
                aCaption=*caption;
                }
            }
        }
    }

EXPORT_C void CEikCaptionedControl::MCoeCaptionRetrieverForFep_Reserved_1()
    {}

EXPORT_C void CEikCaptionedControl::MCoeCaptionRetrieverForFep_Reserved_2()
    {}

EXPORT_C void CEikCaptionedControl::SetEditableL( TBool aEditable, TBool /*aShowEmptyFields*/ )
    {
    // Construct extension object if needed
    ConstructExtensionL() ;

    // Animation is not run when editing
    if( iIsFormControl && iExtension->iAnimation && aEditable )
        {
        iExtension->iAnimation->Pause();
        }

    // Ensure that iHighlightControl gets created
    if (!iHighlightControl)
        {
        iHighlightControl=new(ELeave) CEikCaptionedControlFormHighlightLine ( *this ) ;
        STATIC_CAST(CEikCaptionedControlFormHighlightLine*,iHighlightControl)->ConstructL() ;
        }   
    if (iIsFormControl && iIsEditable && iIsCurrentLine&& !aEditable)
        {
        iControl->SetFocus( EFalse) ;
        }
    if ( iIsFormControl )
        {
        iIsEditable = aEditable ;
        SetFocusing( ETrue ) ;  // Might be modified later on

        iControl->SetFocusing( aEditable ) ;

        if ( !ControlIsAPopfield(iControlType) )
            {
            if( aEditable )
            	iControl->HandleResourceChange(KEikMessageCaptionedControlEditableStateChange);	               
            else
                iControl->HandleResourceChange(KEikMessageCaptionedControlNotEditableStateChange);
            }
        else
            { // so popupfield derived
            TBool isSingleLineLayout = ( FormLayout() == CEikDialogPage::ESingle);
            TBool hasBitmaps = ShowBitmap();
            if( isSingleLineLayout )
                {
                if( aEditable )
                    iControl->HandleResourceChange(KEikMessageCaptionedControlEditableStateChange);
                else
                    iControl->HandleResourceChange(KEikMessageCaptionedControlNotEditableStateChange);
                }
            else
                { // double line layout
                if( hasBitmaps )
                    { // wide with graphic
                    if( aEditable )
                        iControl->HandleResourceChange(KEikMessageCaptionedControlEditableStateChangeWideWithGraphic);
                    else
                        iControl->HandleResourceChange(KEikMessageCaptionedControlNotEditableStateChangeWideWithGraphic);
                    }
                else
                    { // wide without graphic
                    if( aEditable )
                        iControl->HandleResourceChange(KEikMessageCaptionedControlEditableStateChangeWideWithoutGraphic);
                    else
                        iControl->HandleResourceChange(KEikMessageCaptionedControlNotEditableStateChangeWideWithoutGraphic);
                    }
                }
            }

        if ( iCaption )
            iCaption->SetFocusing( !aEditable ) ;

        CalculateNumberOfLinesForControl( ENotSupplied ) ;

        // Force the layout
        ResetMinimumSizes() ;
        LayoutSkinControlContexts();
		if (IsReadyToDraw())
			SizeChanged(); // needed because layout lines change when editable flag is switched.
        }
    }

void CEikCaptionedControl::SetVertEdgeSpacing( TInt aVertEdgeSpacing ) 
    {
    iVertEdgeSpacing = aVertEdgeSpacing ;
    }

void CEikCaptionedControl::SetHorzEdgeSpacing( TInt aHorzEdgeSpacing ) 
    {
    iHorzEdgeSpacing = aHorzEdgeSpacing ;
    }

/**
 * Avkon component positioning for Forms
 */

void CEikCaptionedControl::PositionFormComponents()
    {
    if( iExtension->iPartiallyVisible )
        return;
    TBool isFocused = iIsCurrentLine;
    TBool isSingleLineLayout = ( FormLayout() == CEikDialogPage::ESingle);
    MinimumSize() ;
    TBool hasBitmaps = ShowBitmap();
    
/* 
if control has no height, return now (no point laying out)
*/
    if (!Rect().Height())  
        return;

    TAknWindowLineLayout verticalLine = AKN_LAYOUT_WINDOW_List_pane_elements__single_heading__Line_1 ; 

    // If double line layout update verticalLine
    if ( !isSingleLineLayout )
        {
        if (iDialogPage)
            { // use  form flags from dialog
            if (iDialogPage->GetFormFlags()&EEikFormShowBitmaps)
                {
                verticalLine = AKN_LAYOUT_WINDOW_List_pane_elements__double_graphic__Line_1;
                }
            else
                {
                verticalLine = AKN_LAYOUT_WINDOW_List_pane_lines__A_column__Line_1(0);
                }
            }
        else
            { // use local form flags
            if (iFlags&EEikFormShowBitmaps)
                {
                verticalLine = AKN_LAYOUT_WINDOW_List_pane_elements__double_graphic__Line_1;
                }
            else
                {
                verticalLine = AKN_LAYOUT_WINDOW_List_pane_lines__A_column__Line_1(0);
                }
            }    
        }
        TRect parentRect = Rect();
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( parentRect, verticalLine );
        TRect rectVerticalLine( layoutRect.Rect() );


    // set vertical line position.  
    if ( AknLayoutUtils::LayoutMirrored() )
        {
        iVerticalLineXPosition = Rect().Width() - rectVerticalLine.iBr.iX;
        }
    else
        {
        iVerticalLineXPosition = rectVerticalLine.iTl.iX - iExtension->iXOffsetForDataPaneInEditMode;
        }

    MEikDialogPageObserver::TFormControlTypes typeOfControlToLayout = MEikDialogPageObserver::EUnknownType;
    if (ControlIsAnEdwin(iControlType))
        typeOfControlToLayout=MEikDialogPageObserver::EEdwinDerived;
    else if (ControlIsAMfne(iControlType))
        typeOfControlToLayout=MEikDialogPageObserver::EMfneDerived;
    else if (ControlIsAPopfield(iControlType))
        typeOfControlToLayout=MEikDialogPageObserver::EPopfieldDerived;
    else if (ControlIsASecretEditor(iControlType))
        typeOfControlToLayout=MEikDialogPageObserver::ESecretEditorDerived;
    else if (ControlIsASlider(iControlType))
        typeOfControlToLayout=MEikDialogPageObserver::ESliderDerived;
    else 
        {
/* 
Each control type checks to see if it a user-defined control type is of that type, using the
ConvertCustomControlTypeToBaseControlType mechanism so if the code gets here, the control is 
"none of the above".
*/
        Panic(EEikFormPanicUnknownControlType);
        };

    //TRect layoutRectOfDataPane =(iIsEditable)? EditRect() : ViewRect();

   //view and edit data pane rect should be the same
    TRect layoutRectOfDataPane = ViewRect();    

    if ( hasBitmaps )
        {
        if (iBitmap)
            FormLayoutControlBitmap
                (
                iBitmap,
                layoutRectOfDataPane,
                iIsEditable,
                isSingleLineLayout,
                iNumberOfLines
                );
        }
    if (iCaption)
        {
		TInt numOfIcons = 0;
		if (iExtension && iExtension->iIndicator) numOfIcons = 1;
		if (iExtension && iExtension->iIndicator2) numOfIcons = 2;

        FormLayoutControlLabel
            (
            iCaption,
            layoutRectOfDataPane,
            iIsEditable,
            isSingleLineLayout,
            iNumberOfLines,
            hasBitmaps,
            isFocused,
            numOfIcons
            );
        }

    switch (typeOfControlToLayout)
        {
        case MEikDialogPageObserver::EEdwinDerived:
            {
#ifdef _DEBUG            
            TInt numberOfLines=iNumberOfLines;
#endif // _DEBUG

/* WARNING... The following is done to prevent edwin resize events.  The flag 
iIgnoreFurtherEdwinResizeEvents should only be set for the shortest time possible and only
when resizing an edwin.
*/
            CEikEdwin* edwinPtr=STATIC_CAST(CEikEdwin*, iControl);
            CEikEdwin* previousVal=iDialogPage->iIgnoreFurtherEdwinResizeEvents;

#ifdef _DEBUG            
            if (previousVal)
                {
                RDebug::Print(_L("Warning - Editor has changed number of lines post-layout."));
                }
#endif // _DEBUG
            iDialogPage->iIgnoreFurtherEdwinResizeEvents=edwinPtr;
            FormLayoutControlEdwin
                (
                edwinPtr,
                layoutRectOfDataPane,
                iIsEditable,
                isSingleLineLayout,
                iNumberOfLines,
                hasBitmaps,
                isFocused 
                );
            iDialogPage->iIgnoreFurtherEdwinResizeEvents=previousVal;

#ifdef _DEBUG
            if (numberOfLines!=iNumberOfLines)  
                {
/* 
Due to some rather sneaky code which lays out the editors on mode change, initially
the number of lines should be correct (may be incorrect if the editor had a different
width before the layout to after the layout).

  This will warn if this has not worked.
*/
                RDebug::Print(_L("Warning - Editor has changed number of lines post-layout."));
                RDebug::Print(_L("pre-layout phase must have used a different format."));
                }
#endif // _DEBUG
            break;
            }
        case MEikDialogPageObserver::EMfneDerived:
            {
            FormLayoutControlMfne
                (
                STATIC_CAST(CEikMfne*, iControl),
                layoutRectOfDataPane,
                iIsEditable,
                isSingleLineLayout,
                iNumberOfLines,
                hasBitmaps,
                isFocused 
                );
            break;
            }
        case MEikDialogPageObserver::EPopfieldDerived:
            {
            FormLayoutControlPopfield
                (
                STATIC_CAST(CAknPopupField*, iControl),
                layoutRectOfDataPane,
                iIsEditable,
                isSingleLineLayout,
                iNumberOfLines,
                hasBitmaps,
                isFocused 
                );
            break;
            }
        case MEikDialogPageObserver::ESecretEditorDerived:
            {
            FormLayoutControlSecretEditor
                (
                STATIC_CAST(CEikSecretEditor*, iControl),
                layoutRectOfDataPane,
                iIsEditable,
                isSingleLineLayout,
                iNumberOfLines,
                hasBitmaps,
                isFocused 
                );
            break;
            }
        case MEikDialogPageObserver::ESliderDerived:
            {
            FormLayoutControlSlider
                (
                STATIC_CAST(CAknSlider*, iControl),
                layoutRectOfDataPane,
                iIsEditable,
                isSingleLineLayout,
                iNumberOfLines,
                hasBitmaps 
                );
            break;
            }
        default:
            Panic(EEikFormPanicLayoutErrorUnknownControlType);  
        }
        
    TRAP_IGNORE( SetElementTextColorsL(TRgb()));
    }

TBool CEikCaptionedControl::ShowBitmap() const
    {
    return (iFlags & EEikFormShowBitmaps);
    }

void CEikCaptionedControl::LayoutBitmap(const TRect& aRect)
    {
    if ( ShowBitmap() && iBitmap )
        {
        iBitmap->SetAllMarginsTo(0);
        AknLayoutUtils::LayoutControl( iBitmap, aRect, R_AVKON_FORM_ICON ) ;
        }
    }

void CEikCaptionedControl::LayoutCaption(const TRect& aRect)
    {
    if ( iCaption )
        {
        if ( ShowBitmap() )
            {
            AknLayoutUtils::LayoutLabel( iCaption, aRect, R_AVKON_FORM_LABEL_WITH_ICON ) ;
            }
        else
            {
            AknLayoutUtils::LayoutLabel( iCaption, aRect, R_AVKON_FORM_LABEL_NO_ICON ) ;
            }
        }
    }

TSize CEikCaptionedControl::EditorControlSize() const 
    {
    return iEditorControlSize ;
    }

TInt CEikCaptionedControl::NumberOfLines() const
	{
	return iNumberOfLines;
	}

TInt CEikCaptionedControl::NumberOfLinesForScrollBar() const
	{
	if ( FormLayout() == CEikDialogPage::ESingle ) return NumberOfLines();
	return NumberOfLines()+1;
	}

/**
 * Recalculates the number of required lines for a control.
 */
void CEikCaptionedControl::CalculateNumberOfLinesForControl( TInt aLines )
    {
    // NB if new control types are added, ones which should be invisible in view mode
    // should be also added to IsDisplayable().
    if ( aLines == ENotSupplied )
        {
        // Function has to be aware of edit/view state.  
        if ( iIsEditable )
            {
            if (ControlIsAnEdwin(iControlType))
                {
                CEikEdwin* edwin = STATIC_CAST( CEikEdwin*, iControl );
                if (iIsFormControl)
                    edwin->SetMaximumHeightInLines(MaximumNumberOfControlLinesOnVisiblePage());

                TInt limitForView = edwin->MaximumHeightInLines();
                TInt noLinesInTotal=0;
                if (edwin->TextLayout()) 
                    noLinesInTotal= edwin->TextLayout()->NumFormattedLines() ;
                aLines  = ((limitForView < noLinesInTotal) && limitForView)
                        ? limitForView : noLinesInTotal ;
                }
            else
                {
                switch ( iControlType )
                    {
                    case EAknCtPopupField: 
                    case EAknCtPopupFieldText :
                    	{
                    	CAknPopupField* popupField = static_cast<CAknPopupField*>(iControl);
                    	popupField->SetMaxNumberOfLinesPermitted(MaximumNumberOfControlLinesOnVisiblePage());
                        aLines = popupField->NumLines();
                    	}
                        break;
                    case EAknCtSlider :
                        aLines = STATIC_CAST(CAknSlider*, iControl )->NumberOfLines();
                        break;
                    default :
                        aLines = 1 ;
                        break ;
                    }
                }
            }
        else  // not editable
            {
            if ( iFlags & EEikFormHideEmptyFields 
                    && ControlIsAnEdwin(iControlType)
                    && STATIC_CAST( CEikEdwin*, iControl )->TextLength() == 0 ) 
                            {
                            SetFocusing( EFalse ) ;  // don't want the focus on invisible control!
                            aLines = 0 ;
                }
            else
                aLines=1;
            }
        }
    iNumberOfLines = aLines ;
    }

EXPORT_C void CEikCaptionedControl::SetFormFlags( TInt aFlags ) 
    {
    iFlags = aFlags ;
    }

/*
* Set the background colours of iBitmap, iCaption and iControl 
*/
void CEikCaptionedControl::SetElementBrushColorsL( TRgb aColor ) 
    {
    AknLayoutUtils::OverrideControlColorL(*this, EColorControlBackground, aColor ) ;
    }

/*
* Set the foreground colours of iBitmap, iCaption and iControl 
*/
void CEikCaptionedControl::SetElementTextColorsL( TRgb aColor ) 
    {
	TRgb textColor = aColor;
        {
        if ( AknsUtils::AvkonSkinEnabled() )
            {
            // extended skin support
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            
            // sets the color according the skin LAF
            TAknsQsnTextColorsIndex colorIndex = TextColorIndex();
            AknsUtils::GetCachedColor( skin, textColor, KAknsIIDQsnTextColors, colorIndex );
            }
        }
    AknLayoutUtils::OverrideControlColorL(*this, EColorLabelText, textColor );
    
    if(ControlIsAnEdwin(iControlType))
        {
        AknLayoutUtils::OverrideControlColorL(*this, EColorControlText, textColor );
        }
    
    }

/**
 * Retrieves the Series 60 European LAF layout values from avkon.rh
 *
 */
void CEikCaptionedControl::GetAknLayoutValuesL()
    {
    TAknWindowLineLayout l = AknLayoutScalable_Avkon::form_field_data_pane(0).LayoutLine();
    TRect parentRect = iAvkonAppUi->ClientRect();
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( parentRect, l );
    TRect rectDataPane( layoutRect.Rect() );

    iAknFormControlWidth = rectDataPane.Width();
    iAknFormControlHeight = rectDataPane.Height();
   }

    

TBool   CEikCaptionedControl::IsDisplayable() const
    {
/*
Added to provide whether the control should be displayed without calls to minimumsize.
*/

// If new control types are added which can be invisible in view mode
// with the appropriate flag (EEikFormHideEmptyFields), they should be added here.
    if (iIsFormControl &&  (!iIsEditable) &&(iFlags & EEikFormHideEmptyFields ))
            {
        if (ControlIsAnEdwin(iControlType)&&
            STATIC_CAST( CEikEdwin*, iControl )->TextLength() == 0 )
                    return EFalse;
            }
    return ETrue;
    }

TInt CEikCaptionedControl::ControlType() const
	{
	return iControlType;
	}

TBool CEikCaptionedControl::ControlIsAnEdwin(TInt aControlType) const 
            {
// function used to return which controls are editors (i.e. derived from Edwin)
// The idea is to leave this as expandable as possible.
    switch (aControlType)
            {
        case EEikCtEdwin:
        case EEikCtGlobalTextEditor:
        case EEikCtRichTextEditor:
        case EAknCtIntegerEdwin:
        case EEikCtFlPtEd:
        case EEikCtFxPtEd:
            return ETrue;
            }
/* 
See if the control is an Edwin via the Edwin->Derived route
*/
    if (iDialogPage)
        {
        TInt typeOfControlToLayout=iDialogPage->PageContainer()->PageSelector()->Dialg()->ConvertCustomControlTypeToBaseControlType(iControlType);
        if (typeOfControlToLayout==MEikDialogPageObserver::EEdwinDerived)
            return ETrue;
        }
    return EFalse;
    }

TBool CEikCaptionedControl::ControlIsAMfne(TInt aControlType) const 
    {
// function used to return which controls are mfnes (i.e. derived from CEikmfne)
// The idea is to leave this as expandable as possible.
    switch (aControlType)
        {
        case EEikCtRangeEditor:
        case EEikCtTimeEditor:
        case EEikCtDateEditor:
        case EEikCtTimeAndDateEditor:
        case EEikCtDurationEditor:
        case EEikCtTimeOffsetEditor:
        case EEikCtNumberEditor:
        case EAknCtLocationEditor:
        case EAknCtUnitEditor:
            return ETrue;
        }
    TInt typeOfControlToLayout=iDialogPage->PageContainer()->PageSelector()->Dialg()->ConvertCustomControlTypeToBaseControlType(iControlType);
    if (typeOfControlToLayout==MEikDialogPageObserver::EMfneDerived)
        return ETrue;
    return EFalse;
    }

TBool CEikCaptionedControl::ControlIsAPopfield(TInt aControlType) const 
    {
// function used to return which controls are mfnes (i.e. derived from CEikmfne)
// The idea is to leave this as expandable as possible.
    switch (aControlType)
        {
        case EAknCtPopupField :
        case EAknCtPopupFieldText :
            return ETrue;
        }
    if (iDialogPage)    
        {
        TInt typeOfControlToLayout=iDialogPage->PageContainer()->PageSelector()->Dialg()->ConvertCustomControlTypeToBaseControlType(iControlType);
        if (typeOfControlToLayout==MEikDialogPageObserver::EPopfieldDerived)
            return ETrue;
        }
    return EFalse;
    }

TBool CEikCaptionedControl::ControlIsASecretEditor(TInt aControlType) const 
    {
// function used to return which controls are mfnes (i.e. derived from CEikmfne)
// The idea is to leave this as expandable as possible.
    switch (aControlType)
        {
        case EEikCtSecretEd:
        case EAknCtNumericSecretEditor:
            return ETrue;
        }
    TInt typeOfControlToLayout=iDialogPage->PageContainer()->PageSelector()->Dialg()->ConvertCustomControlTypeToBaseControlType(iControlType);
    if (typeOfControlToLayout==MEikDialogPageObserver::ESecretEditorDerived)
        return ETrue;
    return EFalse;
    }

TBool CEikCaptionedControl::ControlIsASlider(TInt aControlType) const 
    {
// function used to return which controls are sliders 
// The idea is to leave this as expandable as possible.
    switch (aControlType)
        {
        case EAknCtSlider :
            return ETrue;
        }
    TInt typeOfControlToLayout=iDialogPage->PageContainer()->PageSelector()->Dialg()->ConvertCustomControlTypeToBaseControlType(iControlType);
    if (typeOfControlToLayout==MEikDialogPageObserver::ESliderDerived)
        return ETrue;
    return EFalse;
    }

//------------------------------------------------------------------------
// CEikCaptionedControl::ControlIsAColourSelGrid
// Returns true if control is colourselection grid or nonefield .
//------------------------------------------------------------------------
TBool CEikCaptionedControl::ControlIsAColourSelGrid(TInt aControlType) const 
    {
// function used to return which controls are ColourSelectionGrids 
// The idea is to leave this as expandable as possible.
    switch (aControlType)
        {
        case EAknCtColourSelectionDialogGrid :   // Deprecated
        case EAknCtColourSelectionGridDialog :
        case EAknCtColourSelectionDialogNoneField:
            return ETrue;
        }
    TInt typeOfControlToLayout=iDialogPage->PageContainer()->PageSelector()->Dialg()->ConvertCustomControlTypeToBaseControlType(iControlType);
    if (typeOfControlToLayout==MEikDialogPageObserver::EColourSelectionGridDerived)
        return ETrue;
    return EFalse;
    }  
 
void CEikCaptionedControl::DoFormCaptionSettingsL(const TDesC& aText)
    {
    delete iCaptionText; // get rid of old iCaptionText
    iCaptionText=0;
    iCaptionText = aText.AllocL();
    iCaption->SetTextL(aText);
    iCaption->CropText();
    }


EXPORT_C const TPtrC CEikCaptionedControl::GetFullCaptionText() const
    {
    return *iCaptionText;
    };

void CEikCaptionedControl::RegisterPageWithCaptionControl(CEikDialogPage* aPage)
    {
    iDialogPage=aPage;
    };

TInt CEikCaptionedControl::MaximumNumberOfControlLinesOnVisiblePage() const
    {
	TInt maxItems = 0;
	TAknLayoutScalableParameterLimits paneLimits;
	if (IsPopupField(this))
    	{
        if (iDialogPage&& CEikDialogPage::EDouble == iDialogPage->FormLayout())
    		paneLimits = AknLayoutScalable_Avkon::form_field_popup_wide_pane_ParamLimits();
    	else
    		paneLimits = AknLayoutScalable_Avkon::form_field_popup_pane_ParamLimits();
    	}
	else
    	{
        if (iDialogPage&& CEikDialogPage::EDouble == iDialogPage->FormLayout())
    		paneLimits = AknLayoutScalable_Avkon::form_field_data_wide_pane_ParamLimits();
    	else
    		paneLimits = AknLayoutScalable_Avkon::form_field_data_pane_ParamLimits();
    	}
	maxItems = paneLimits.LastVariety() + 1; // last variety is a zero based index, we need num items which is 1 based

	TInt maxItems2 = maxItems;
	if (!IsPopupField(this))
		{
		paneLimits = AknLayoutScalable_Avkon::data_form_wide_pane_t1_ParamLimits();
		maxItems2 = paneLimits.LastRow()+1;
		}
	else 
		{
	    if (iDialogPage&& CEikDialogPage::EDouble == iDialogPage->FormLayout())
	    	paneLimits = AknLayoutScalable_Avkon::list_form_graphic_pane_cp_ParamLimits();
	    else
			paneLimits = AknLayoutScalable_Avkon::list_form_graphic_pane_ParamLimits();	
	    maxItems2 = paneLimits.LastRow()+1;
		}

	if (maxItems2 < maxItems) maxItems = maxItems2;
	
    if ( ControlIsAnEdwin( iControlType ) )
        {
        TInt defineHeight = static_cast<CEikEdwin*>( iControl )->MaximumHeightInLines();
        if ( defineHeight && defineHeight < maxItems )
            return defineHeight;
        }
	//maxItems -= 1; // TODO: this is a temporary workaround for layout data being incorrect, it has too many options available
    return maxItems;
    };


TRect CEikCaptionedControl::ViewRect() const

    {
/* 
The Rect that the view mode is expecting is:
176 across 
21 high
set from 0,0

We are
174 across
23 high
set from (1,1) relative to viewwin.

To convert we must:
* Shrink(-1,1) to make Y cord and size equal, and X coord equal.
* add 1 to the BR X coord. to make X size equal.
*/
    TRect viewRectConversion(EditRect());
    viewRectConversion.Shrink(0,1);
    return viewRectConversion;
    }

TRect CEikCaptionedControl::EditRect() const
    {
    //The Rect provided by Rect() is fine  
    return Rect();
    } 

void CEikCaptionedControl::FormLayoutControlBitmap(CEikImage* aBitmap, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines)
    {   
    if (!aNumberOfLines)
        return;
    aBitmap->SetAllMarginsTo(0);
    if (aSingleLayout)
        {
        if (aIsEditable)
            {
            AknLayoutUtils::LayoutControl
                ( 
                aBitmap, 
                aParent, 
                AKN_LAYOUT_WINDOW_Form_data_field_elements_Line_4
                );
            }
        else
            {
            AknLayoutUtils::LayoutImage
                ( 
                aBitmap, 
                aParent, 
                AKN_LAYOUT_WINDOW_List_pane_elements__single_graphic_heading__Line_1
                );
            }
        }
    else 
        {
        if (aIsEditable)
            {
            AknLayoutUtils::LayoutControl
                ( 
                aBitmap, 
                aParent, 
                AKN_LAYOUT_WINDOW_Form_data_wide_field_elements_Line_4
                );
            }
        else
            {
            AknLayoutUtils::LayoutControl
                ( 
                aBitmap, 
                aParent, 
                AKN_LAYOUT_WINDOW_List_pane_elements__single_graphic_heading__Line_1
                );
            }
        }   
    }

static TRect LineRect(TRect aParentRect, TInt aLine, TAknTextLineLayout aLayout)
	{
	TAknLayoutText text;
	text.LayoutText(aParentRect, aLayout);
	TRect rect = text.TextRect();
	rect.iTl.iY += aLayout.iBaselineSkip * aLine;
	rect.iBr.iY += aLayout.iBaselineSkip * aLine;
	return rect;
	}

static void SetScrollRect(CEikEdwin *aEdwin, TRect aParentRect, TAknTextLineLayout aLayout, TInt aNumberOfLines)
	{
	TRect top = LineRect(aParentRect, 1, aLayout);
	TRect bottom = LineRect(aParentRect, aNumberOfLines-2, aLayout);
	TRect area = TRect(top.iTl, bottom.iBr);
	aEdwin->SetScrollRect(area);
	}

// Edit fields
void CEikCaptionedControl::FormLayoutControlEdwin(
        CEikEdwin* aEdwin, const TRect& aParentRect, TBool aIsEditable,
        TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent,
        TBool /*aIsFocused*/ )
    {
    if (!aNumberOfLines)
        return;
    // Create a standard text layout object with scope at this level
    TRect layoutRect = aParentRect;
    TAknTextLineLayout textLayout (
                AKN_LAYOUT_TEXT_List_pane_texts__single_graphic_heading__Line_2(0) );

    if (aSingleLayout)
        {
        if (aIsEditable)
            {
            TAknTextLineLayout specificLayout( 
                AKN_LAYOUT_MULTILINE_TEXT_Form_data_field_texts_Line_2(aNumberOfLines) );
            textLayout = specificLayout;
            }
        else
            {
            // should assert only 1 line
            TAknTextLineLayout specificLayout( 
                AKN_LAYOUT_TEXT_List_pane_texts__single_graphic_heading__Line_2(0) );
            textLayout = specificLayout;
            }
        }
    else 
        {
        // Not currently specified, so making temporary alterations here.
        if (aIsEditable)
            {
            if (aBitmapPresent)
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_MULTILINE_TEXT_Form_data_wide_graphic_field_texts_Line_2(aNumberOfLines) );
                textLayout = specificLayout;
                }
            else
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_MULTILINE_TEXT_Form_data_wide_field_texts_Line_2(aNumberOfLines) );

                textLayout = specificLayout;
                }
            }
        else 
            {
            if (aBitmapPresent)
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_TEXT_List_pane_texts__large_single_heading_graphic__Line_2 );
                textLayout = specificLayout;
                }
            else
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_TEXT_List_pane_texts__large_single_heading__Line_2 );

                textLayout = specificLayout;
                }
            }
        }

    if( aEdwin->TextLayout() )
        {
        aEdwin->TextLayout()->RestrictScrollToTopsOfLines(EFalse);

        if (AknLayoutUtils::LayoutMirrored() && textLayout.iJ == ELayoutAlignRight && aIsEditable)
            {
            textLayout.iJ = ELayoutAlignBidi;
            }

        TAknsQsnTextColorsIndex colorIndex = TextColorIndex();
        AknLayoutUtils::LayoutEdwin( aEdwin, layoutRect, textLayout,
                                     colorIndex, 0, ETrue );
    	SetScrollRect(aEdwin, layoutRect, textLayout, aNumberOfLines);
	    }

	TBool isviewmode = !aIsEditable;
	aEdwin->SetSuppressBackgroundDrawing(isviewmode);
    }


// Labels
void CEikCaptionedControl::FormLayoutControlLabel(
        CEikLabel* aLabel, const TRect& aParent, TBool aIsEditable,
        TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent,
        TBool /*aIsFocused*/, TInt aIconCount)
    {
    if (!aNumberOfLines)
        return;
    TInt bitmap = (aBitmapPresent)?1:0;
    TRect layoutRect = aParent;

	TInt numOfIcons = aIconCount;

    // Put a layout object at this level of scope 
    TAknTextLineLayout textLayout( AKN_LAYOUT_TEXT_Form_data_field_texts_Line_1(bitmap,0) );
    
    // Layout the label for the single line format
    if (aSingleLayout) 
        {
        if (aIsEditable)
            {
            // Do nothing; this is the default used
            }
        else
            {
            // This layout is dy
            if (aBitmapPresent)
                {
                TAknTextLineLayout anotherTextLayout(AKN_LAYOUT_TEXT_List_pane_texts__single_graphic_heading__Line_1(0) );
                textLayout = anotherTextLayout;
                }
            else
                {
		textLayout = AknLayoutScalable_Avkon::form_field_data_pane_t1(0).LayoutLine();
                };
            }
        }
    else
    // Double line format
        {
        if (aIsEditable)
            {
            if (aBitmapPresent)
                {
                TAknTextLineLayout anotherTextLayout( AknLayoutScalable_Avkon::form_field_data_wide_pane_t1(1+numOfIcons).LayoutLine() ) ;
                textLayout = anotherTextLayout;
                }
            else
                {
                TAknTextLineLayout anotherTextLayout( AknLayoutScalable_Avkon::form_field_data_wide_pane_t1(numOfIcons ? numOfIcons+1 : 0).LayoutLine() ) ;
                textLayout = anotherTextLayout;

                }
            }
        else
            {
            if (aBitmapPresent)
                {
                TAknTextLineLayout anotherTextLayout( 
                    AKN_LAYOUT_TEXT_List_pane_texts__large_single_heading_graphic__Line_1(numOfIcons) );
                textLayout = anotherTextLayout;
                }
            else
                {
                TAknTextLineLayout anotherTextLayout( 
                    AknLayoutScalable_Avkon::list_double_heading_pane_t1(numOfIcons).LayoutLine() );
                textLayout = anotherTextLayout;
                }
            }

        }
        
    // Finally, lay out the label
    AknLayoutUtils::LayoutLabel( aLabel, layoutRect, textLayout);

    aLabel->SetFont( AknLayoutUtils::FontFromId( textLayout.FontId() ) ) ;
                   TRgb textColor;
               
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
               
    if (skin)
        {
        TAknsQsnTextColorsIndex colorIndex = TextColorIndex();
        TInt error = AknsUtils::GetCachedColor( skin, textColor, KAknsIIDQsnTextColors, colorIndex );
        if (error == KErrNone )
            {
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *aLabel, EColorLabelText, textColor ) );
            }          
        }
    }
    
    
// Number editors
void CEikCaptionedControl::FormLayoutControlMfne(
        CEikMfne* aMfne,  const TRect& aParent, TBool aIsEditable,
        TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent,
        TBool /*aIsFocused*/ )
    {
    if (!aNumberOfLines)
        return;
    TAknTextLineLayout layoutMFNE(AKN_LAYOUT_MULTILINE_TEXT_Form_data_field_texts_Line_2(0)); 
    TRect finalRect(aParent);
    if (aSingleLayout)
        {
        if (aIsEditable)
            {
            layoutMFNE = AKN_LAYOUT_MULTILINE_TEXT_Form_data_field_texts_Line_2(0);
            }
        else 
            {
            layoutMFNE =AKN_LAYOUT_TEXT_List_pane_texts__single_graphic_heading__Line_2(0);
            }
        }
    else 
        {
        if (aIsEditable)
            {
            if (aBitmapPresent)
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_MULTILINE_TEXT_Form_data_wide_graphic_field_texts_Line_2(aNumberOfLines) );
                layoutMFNE = specificLayout;
                }
            else 
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_MULTILINE_TEXT_Form_data_wide_field_texts_Line_2(aNumberOfLines) );
                layoutMFNE = specificLayout;
                }
            }
        else 
            {
            if (aBitmapPresent)
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_TEXT_List_pane_texts__large_single_heading_graphic__Line_2 );
                layoutMFNE = specificLayout;
                }
            else
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_TEXT_List_pane_texts__large_single_heading__Line_2 );
                layoutMFNE = specificLayout;
                }

            }
        }   
    AknLayoutUtils::LayoutMfne
        ( 
        aMfne, 
        finalRect, 
        layoutMFNE
        );
    
    TRAP_IGNORE( aMfne->SetSkinTextColorL( TextColorIndex() ) );

	TBool isviewmode = !aIsEditable;
	aMfne->SetSuppressBackgroundDrawing(isviewmode);
    }

// Pop-fields
void CEikCaptionedControl::FormLayoutControlPopfield(
        CAknPopupField* aPopfield, const TRect& aParent, TBool aIsEditable,
        TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent,
        TBool /*aIsFocused*/)
    {
    TRect layoutRect = aParent;
    TAknWindowLineLayout layoutData(AKN_LAYOUT_WINDOW_list_form_pane(aNumberOfLines-1));
	TAknTextLineLayout labelLayout(AknLayout::Form_data_field_texts_Line_2(0));
    if (!aNumberOfLines)
        return;
    
	if (aPopfield->FormMode() == CAknPopupField::EAknFormModeEdit || aPopfield->FormMode() == CAknPopupField::EAknFormModeView)
		{
		labelLayout = AknLayout::Form_data_field_texts_Line_2(0);
		}
    else if ( aPopfield->FormMode()==CAknPopupField::EAknFormModeEditWideWithoutGraphic || aPopfield->FormMode()==CAknPopupField::EAknFormModeViewWideWithoutGraphic )
        {
		labelLayout = AknLayout::Form_data_wide_field_texts_Line_2(0);
		}
	else // wide with bitmap for now use wide style
    	{
		labelLayout = AknLayout::Form_data_wide_graphic_field_texts_Line_2(0);
		}
    TBool isText = EFalse;
	if (aPopfield->SelectionMode() == CAknPopupField::EAknPopupFieldLabelMode)
		{
		isText = ETrue;
		}
 
    if (aSingleLayout)
        {
        if (aIsEditable)
            {
            layoutData=AKN_LAYOUT_WINDOW_list_form_pane(aNumberOfLines-1);
            }
        else
            {
/* 
popupfields not specified in lists.  
Have to convert aParent to form equivalent and use that layout.
*/
            ConvertViewRectToEditRect(layoutRect);
            layoutData=AKN_LAYOUT_WINDOW_list_form_pane(aNumberOfLines-1);
            }
        }
    else  // double layout
        {
        TInt newpar = ( aBitmapPresent ? 1 : 0 ) ;
        if (!aBitmapPresent)
            {
            if (aIsEditable)
                {
                layoutData=AKN_LAYOUT_WINDOW_list_form_wide_pane(newpar, aNumberOfLines-1);
                }
            else
                {
                // have to convert Rect before doing this.
                ConvertViewRectToEditRect(layoutRect);
                layoutData=AKN_LAYOUT_WINDOW_list_form_wide_pane(newpar, aNumberOfLines-1);
                }
            }
        else //AKN_LAYOUT_WINDOW_list_form_graphic_wide_pane
            {
            if (aIsEditable)
                {
                layoutData=AKN_LAYOUT_WINDOW_list_form_wide_pane(newpar, aNumberOfLines-1);
                }
            else
                {
                // have to convert Rect before doing this.
                ConvertViewRectToEditRect(layoutRect);
                layoutData=AKN_LAYOUT_WINDOW_list_form_wide_pane(newpar, aNumberOfLines-1);
				//move bitmap's width for display second line text
		        TAknWindowLineLayout l = AknLayout::List_pane_elements__single_graphic_heading__Line_1();
		        TAknLayoutRect bmpRect;
		        TRect tempRect;
		        bmpRect.LayoutRect( tempRect, l );
				layoutRect.iTl.iX += bmpRect.Rect().Width();
                }
            }
        };
	aPopfield->SetFormFieldRect(layoutRect);
	if (isText)
		{ // popup field will be same size as text element
		TAknLayoutText r;
		r.LayoutText(layoutRect, labelLayout);
		TRect resultRect = r.TextRect();
		aPopfield->SetRect(resultRect);
		}
	else
		{ // popup field will be same size as list_pane
	    AknLayoutUtils::LayoutControl
    	    (
       	 	aPopfield, 
        	layoutRect, 
        	layoutData
        	);			
		}

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
               
    if (skin)
        {
        TRgb textColor;
        TAknsQsnTextColorsIndex colorIndex = TextColorIndex();
        TInt error = AknsUtils::GetCachedColor( skin, textColor, KAknsIIDQsnTextColors, colorIndex );
        if (error == KErrNone )
            {
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *aPopfield, EColorLabelText, textColor ) ); 
            }          
        }
        
    }

// Password editor
void CEikCaptionedControl::FormLayoutControlSecretEditor(
        CEikSecretEditor* aSecretEd, const TRect& aParent, TBool aIsEditable,
        TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent,
        TBool /*aIsFocused*/)
    {
    if (!aNumberOfLines)
        return;
    TAknTextLineLayout layoutSecEd(AKN_LAYOUT_MULTILINE_TEXT_Form_data_field_texts_Line_2(0)); 

    if (aSingleLayout)
        {
        if (aIsEditable)
            {
            layoutSecEd=AKN_LAYOUT_MULTILINE_TEXT_Form_data_field_texts_Line_2(1);
            }
        else
            {
            layoutSecEd = AKN_LAYOUT_TEXT_List_pane_texts__single_graphic_heading__Line_2(0);
            }
        }
    else 
        {
        if (aIsEditable)
            {
            if (aBitmapPresent)
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_MULTILINE_TEXT_Form_data_wide_graphic_field_texts_Line_2(aNumberOfLines) );
                layoutSecEd = specificLayout;
                }
            else 
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_MULTILINE_TEXT_Form_data_wide_field_texts_Line_2(aNumberOfLines) );
                layoutSecEd = specificLayout;
                }
            }
        else
            {
            if (aBitmapPresent)
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_TEXT_List_pane_texts__large_single_heading_graphic__Line_2 );
                layoutSecEd = specificLayout;
                }
            else 
                {
                TAknTextLineLayout specificLayout( 
                    AKN_LAYOUT_TEXT_List_pane_texts__large_single_heading__Line_2 );
                layoutSecEd = specificLayout;
                }
            }
        }   
    AknLayoutUtils::LayoutSecretEditor
        ( 
        aSecretEd,
        aParent, 
        layoutSecEd
        );
		
    TRAP_IGNORE( aSecretEd->SetSkinTextColorL( TextColorIndex() ) );
    }

// Slider control
void CEikCaptionedControl::FormLayoutControlSlider(CAknSlider* aSlider, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool /*aBitmapPresent*/)
    {   
    if (!aNumberOfLines)
        return;
    if (aSingleLayout)
        {
        if (aIsEditable)
            {
            aSlider->SetRect(aParent);
            }
        else
            {
/* 
sliders not specified in lists.  
Have to convert aParent to form equivalent and use that layout.
*/
            TRect conversionRect(aParent);
            ConvertViewRectToEditRect(conversionRect);
            aSlider->SetRect(conversionRect);
            }
        }
    else 
        {
        // Not currently specified, so making temporary alterations here.
        TInt baselineSkip= AKN_LAYOUT_MULTILINE_TEXT_Form_data_field_texts_Line_2(1).BaselineSkip();
        TRect newParentRect(aParent);
        //Only move the rect will cover a part or next dialogline, so decrease height of rect form iTl.
        if( !aIsEditable )
	        {
	        newParentRect.iTl.iX += baselineSkip;          	
	        }
        newParentRect.iTl.iY += baselineSkip;
            
        if (aIsEditable)
            {
            aSlider->SetRect(newParentRect);
            }
        else 
            {
            TRect conversionRect(newParentRect);
            ConvertViewRectToEditRect(conversionRect);
            aSlider->SetRect(conversionRect);
            }
        }   

        // Exteded skin support for sliders coded in slider file: \s60\AvKon\src\Aknslider.cpp
    }

void CEikCaptionedControl::ConvertViewRectToEditRect(TRect& aRect)
    {
    aRect.Grow(-1,1);
    aRect.iBr.iX--;
    }

void CEikCaptionedControl::ConvertEditRectToViewRect(TRect& aRect)
    {
    aRect.Shrink(-1,1);
    aRect.iBr.iX++;
    }

// Standard access method for the form layout from within captioned control
CEikDialogPage::TFormLayoutSelection CEikCaptionedControl::FormLayout() const
    {
    // There is no undefined style, but initialize to single...
    CEikDialogPage::TFormLayoutSelection ret = CEikDialogPage::ESingle;
    if ( iDialogPage )
        ret = iDialogPage->FormLayout();
    
    if (!iDialogPage)
        {
        if (iFlags & EEikFormUseDoubleSpacedFormat) // similar to CEikDialogPage::ConstructFormFromResourceL()
            ret = CEikDialogPage::EDouble;
        }
    return ret;
    }

void CEikCaptionedControl::DrawFormSeparator( CWindowGc& gc ) const
    {
    TAknLayoutRect sepLineRect;
    if ( FormLayout() == CEikDialogPage::ESingle )
        {
        sepLineRect.LayoutRect
            (
            ViewRect(), 
            AKN_LAYOUT_WINDOW_List_pane_elements__single_heading__Line_2
            );
        sepLineRect.DrawRect(gc);

        }
//  else
//      {
// Currently no LAF specification for separator in double mode
//      sepLineRect.LayoutRect
//          (
//          ViewRect(), 
//          AKN_LAYOUT_WINDOW_List_pane_elements__double_graphic__Line_??
//          );
//      sepLineRect.DrawRect(gc);
//
//      }
    }

void CEikCaptionedControl::DrawClosingLine() const
    {
    if (iHighlightControl)
        iHighlightControl->DrawDeferred();
    };

/**
 * Ensure that iExtension is constructed (there is no BaseConstructL() in which to place this stuff)
 * 
 */
void CEikCaptionedControl::ConstructExtensionL()
    {
    if ( !iExtension )
        {
        iExtension = new (ELeave) CEikCapCExtension ;
        iExtension->iSelf = this ;
        SetPressedDownState( EFalse );

        if ( iIsFormControl )
            {
            TRect innerRect, outerRect ; // Place holder rectangles
            iExtension->iEditModeHighlightControlContext = CAknsFrameBackgroundControlContext::NewL(
                                            KAknsIIDQsnFrInput,  outerRect,  innerRect, EFalse /*parent absolute*/ ) ;
            iExtension->iEditModeHighlightControlContextPressed = CAknsFrameBackgroundControlContext::NewL(
                                              KAknsIIDQsnFrListPressed,  outerRect,  innerRect, EFalse /*parent absolute*/ ) ;
            iExtension->iViewModeHighlightControlContext = CAknsFrameBackgroundControlContext::NewL(
                                            KAknsIIDQsnFrList,  outerRect,  innerRect, EFalse /*parent absolute*/ ) ;
            iExtension->iViewModeHighlightControlContextPressed = CAknsFrameBackgroundControlContext::NewL(
                                            KAknsIIDQsnFrListPressed,  outerRect,  innerRect, EFalse /*parent absolute*/ ) ;
            }
        }
    }

EXPORT_C TTypeUid::Ptr CEikCaptionedControl::MopSupplyObject(TTypeUid aId)
    {
    if ( aId.iUid == MAknsControlContext::ETypeId && iIsFormControl )
        {
        if ( iIsFormControl && iIsCurrentLine && iExtension )
            {
            // The highlighted field in Forms has its own context.  Otherwise take that of the MOP Parent.
            if ( iIsEditable )
                if ( PressedDownState() )
                    {
                    return ( MAknsControlContext::SupplyMopObject( aId, iExtension->iEditModeHighlightControlContextPressed ) ) ;
                    }
                else
                    {
                    return ( MAknsControlContext::SupplyMopObject( aId, iExtension->iEditModeHighlightControlContext ) ) ;
                    } 
            else
                if ( PressedDownState() )
                    {
                    return ( MAknsControlContext::SupplyMopObject( aId, iExtension->iViewModeHighlightControlContextPressed ) ) ;
                    }
                else
                    {
                    return ( MAknsControlContext::SupplyMopObject( aId, iExtension->iViewModeHighlightControlContext ) ) ;
                    }
            }
        }
    // Otherwise, do a base call to immediate parent class
    return CCoeControl::MopSupplyObject( aId ) ; 
    }

void CEikCaptionedControl::LayoutSkinControlContexts()
    {
    TRect outerRect( Rect() );
    TRect innerRect( outerRect );

    // Only lay out the "current" context
    if ( iIsEditable )
        {
        innerRect.iTl = EditFrameTopLeftRect( outerRect ).iBr ;
        innerRect.iBr = EditFrameBottomRightRect( outerRect ).iTl ;
        iExtension->iEditModeHighlightControlContext->SetFrameRects( outerRect, innerRect);
        iExtension->iEditModeHighlightControlContext->SetParentContext(
            GetDialogControlContext( iDialogPage ) );
        iExtension->iEditModeHighlightControlContextPressed->SetFrameRects( outerRect, innerRect);
        iExtension->iEditModeHighlightControlContextPressed->SetParentContext(
            GetDialogControlContext( iDialogPage ) );
        }
    else
        {
        outerRect = ViewRect() ;
        innerRect = outerRect ;
        innerRect.iTl = ViewFrameTopLeftRect( outerRect ).iBr ;
        innerRect.iBr = ViewFrameBottomRightRect( outerRect ).iTl ;
        iExtension->iViewModeHighlightControlContext->SetFrameRects( outerRect, innerRect );
        iExtension->iViewModeHighlightControlContext->SetParentContext(
            GetDialogControlContext( iDialogPage ) );
        iExtension->iViewModeHighlightControlContextPressed->SetFrameRects( outerRect, innerRect);
        iExtension->iViewModeHighlightControlContextPressed->SetParentContext(
            GetDialogControlContext( iDialogPage ) );
        }
    }
    
TBool CEikCaptionedControl::PressedDownState() const
    {
    return iExtension->iPressDownEffect;
    }
    
void CEikCaptionedControl::SetPressedDownState( TBool aPressed )
    {
    // there's no pressed down highlight in single click UI
    if ( !iExtension->iUsesSingleClick )
        {
        iExtension->iPressDownEffect = aPressed;
        }
    }
    
void CEikCaptionedControl::DrawAsSkinnedForm( CWindowGc& aGc, const TRect& /*aRect*/ ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance() ;

    if ( !iIsCurrentLine )
        {
        aGc.SetBrushStyle( CGraphicsContext::ENullBrush ) ; 
        }
    else // Highlight Skinning.  Requires Frame
        {
        if ( iIsEditable )
            {
            TRect innerRect( EditRect() ) ;
            innerRect.iTl = EditFrameTopLeftRect( Rect() ).iBr ;
            innerRect.iBr = EditFrameBottomRightRect( Rect() ).iTl ;

            MAknsControlContext* parentCc = GetDialogControlContext( iDialogPage ) ; 
            AknsDrawUtils::Background( skin, parentCc, this, aGc, Rect() ) ;

            // Set the rectangle(s) for the Frame context
            iExtension->iEditModeHighlightControlContext->SetFrameRects( EditRect(), innerRect ) ;
            iExtension->iEditModeHighlightControlContextPressed->SetFrameRects( EditRect(), innerRect ) ;
            
            AknsDrawUtils::DrawFrame( skin, aGc, EditRect(), innerRect,
                                      PressedDownState() ?
                                      KAknsIIDQsnFrListPressed : KAknsIIDQsnFrInput, KAknsIIDDefault );
            }
        else // View Mode highlight
            {
            TBool drawOk = EFalse;
            if( iExtension->IsHighlightAnimated() ) // Draw animated highlight
                {
                CAknsEffectAnim* anim = iExtension->iAnimation->Animation();

                // TODO: Background is drawn first to prevent white stripes
                // appearing above and below the highlight. Wasting resources
                // here, you could create animation that is a tad bigger and
                // remove background drawing from here.
                TRect viewRect = ViewRect() ;
                TRect innerRect( viewRect ) ;
                innerRect.iTl = ViewFrameTopLeftRect( viewRect ).iBr ;
                innerRect.iTl.iX-- ; innerRect.iTl.iY-- ;  // not sure why this adjustment is required here and not above.
                innerRect.iBr = ViewFrameBottomRightRect( viewRect ).iTl ;

                // The bit around the outside must use the parent's control context
                MAknsControlContext* parentCc = GetDialogControlContext( iDialogPage ) ;
                AknsDrawUtils::BackgroundBetweenRects( skin, parentCc, this, aGc, Rect() , innerRect ) ;

                // Draw the animation itself
                if( anim )
                    {
                    drawOk = anim->Render( aGc, ViewRect() );
                    }
                }

            if( !drawOk )
                {
                // Code for skinning Highlight ( Using AVKON LAF highlight in place of
                // Skins LAF to establish highlight outer rect )
                TRect viewRect = ViewRect() ;
                TRect innerRect( viewRect ) ;
                innerRect.iTl = ViewFrameTopLeftRect( viewRect ).iBr ;
                innerRect.iTl.iX-- ; innerRect.iTl.iY-- ;  // not sure why this adjustment is required here and not above.
                innerRect.iBr = ViewFrameBottomRightRect( viewRect ).iTl ;

                // The bit around the outside must use the parent's control context
                MAknsControlContext* parentCc = GetDialogControlContext( iDialogPage ) ;
                AknsDrawUtils::BackgroundBetweenRects( skin, parentCc, this, aGc, Rect() , innerRect ) ;

                // Set the rectangle(s) for the Frame context
                iExtension->iViewModeHighlightControlContext->SetFrameRects( viewRect, innerRect ) ;
                iExtension->iViewModeHighlightControlContextPressed->SetFrameRects( viewRect, innerRect ) ;
                
                AknsDrawUtils::DrawFrame( skin, aGc, viewRect, innerRect,
                                          PressedDownState() ?
                                          KAknsIIDQsnFrListPressed : KAknsIIDQsnFrList, KAknsIIDDefault );
                }
            }
        }

    // Enable/disable the control line as required.  (Hide first, show if necessary)
    TBool showHighlightControl = EFalse ;

    if (iDialogPage&& iHighlightControl && iIsCurrentLine )
        {
        TInt height(Rect().Height());
        TBool top = iDialogPage->VisibleSizeOnPage(height,iControl);
        if (height<Rect().Height())
            {
            CEikCaptionedControlFormHighlightLine::TTopOrBottom topOrBottom = (top) ? CEikCaptionedControlFormHighlightLine::ETop : CEikCaptionedControlFormHighlightLine::EBottom;
            TInt heightOfHighlight = STATIC_CAST(CEikCaptionedControlFormHighlightLine*,iHighlightControl)->HeightOfHighlight(topOrBottom);
// is off page, and needs a line drawing.
            TRect controlRect = (top) 
                ? TRect
                    (
                    TPoint(Rect().iTl.iX,Rect().iBr.iY-height),
                    TPoint(Rect().iBr.iX,Rect().iBr.iY-(height-heightOfHighlight))
                    )
                : TRect
                    (
                    TPoint(Rect().iTl.iX,Rect().iTl.iY+(height-heightOfHighlight)),
                    TPoint(Rect().iBr.iX,Rect().iTl.iY+height)
                    );
            iHighlightControl->SetRect(controlRect);
            STATIC_CAST(CEikCaptionedControlFormHighlightLine*,iHighlightControl)->SetTopOrBottom(topOrBottom); 
            showHighlightControl = ETrue ;
            }
        }
    if (iHighlightControl)    
        {
        iHighlightControl->MakeVisible( showHighlightControl );
        }
    }

TBool CEikCaptionedControl::DrawingSkins() const
    {
    TBool drawingSkins = EFalse;
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance() ;
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this ) ;
        CWindowGc& gc = SystemGc();
        drawingSkins = AknsDrawUtils::Background( skin, cc, this, gc, Rect(), KAknsDrawParamPrepareOnly );  
        }
    return drawingSkins;
    }
    
EXPORT_C void CEikCaptionedControl::SetIconL( CFbsBitmap* aBitmap, CFbsBitmap* aMask )
    {
    SetIconSizeL(aBitmap);

    if ( iBitmap )
        delete iBitmap;
    iBitmap = 0;
    iBitmap = new ( ELeave ) CEikImage();    
    iBitmap->SetPicture(aBitmap, aMask);
    }    

EXPORT_C void CEikCaptionedControl::SetIndicatorIconL( TInt aIcon, CFbsBitmap *aBitmap, CFbsBitmap *aMask )
	{
	if (aIcon == 0)
		{
		if (iExtension)
			{
			if (aBitmap == NULL)
				{
				delete iExtension->iIndicator;
				iExtension->iIndicator = 0;
				}
			else
				{	
				if (!iExtension->iIndicator)
					{
					iExtension->iIndicator = new(ELeave) CEikImage();
				    iExtension->iIndicator->SetContainerWindowL(*this);
   	 				iExtension->iIndicator->CopyControlContextFrom(this);
   	 				iExtension->iIndicator->SetNonFocusing();
    				iExtension->iIndicator->SetBrushStyle(CGraphicsContext::ENullBrush );
					}
				iExtension->iIndicator->SetPicture(aBitmap, aMask);
				}
			}
		}
	else if (aIcon == 1)
		{
		if (iExtension)
			{
			if (aBitmap == NULL)
				{
				delete iExtension->iIndicator2;
				iExtension->iIndicator2 = 0;
				}
			else
				{	
				if (!iExtension->iIndicator2)
					{
					iExtension->iIndicator2 = new(ELeave) CEikImage();
				    iExtension->iIndicator2->SetContainerWindowL(*this);
	    			iExtension->iIndicator2->CopyControlContextFrom(this);
    				iExtension->iIndicator2->SetNonFocusing();
    				iExtension->iIndicator2->SetBrushStyle(CGraphicsContext::ENullBrush );
					}
				iExtension->iIndicator2->SetPicture(aBitmap, aMask);

				}
			}
		}
	}

void CEikCaptionedControl::SetIconSizeL(CFbsBitmap* aBitmap)
    {
    if (iIsFormControl && iIsEditable)
        {
        TAknWindowLineLayout l = AknLayout::Form_data_field_elements_Line_4();
        TAknLayoutRect layoutRect;
        TRect parentRect = Rect();
        layoutRect.LayoutRect( parentRect, l );
        TRect rectElements( layoutRect.Rect() );

        User::LeaveIfError(AknIconUtils::SetSize(aBitmap, 
                           rectElements.Size() ));
        }
    else
        {
        TAknWindowLineLayout l = AknLayout::List_pane_elements__single_graphic_heading__Line_1();
        TAknLayoutRect layoutRect;
        TRect parentRect = Rect();
        layoutRect.LayoutRect( parentRect, l );
        TRect rectElements( layoutRect.Rect() );

        User::LeaveIfError(AknIconUtils::SetSize(aBitmap, 
                              rectElements.Size() ));
        }
/*        
    
    if (iIsFormControl)
        {
        if (iIsEditable)
            {
            if (iBitmap && iBitmap->Bitmap())
                {
                AknIconUtils::SetSize(CONST_CAST(CFbsBitmap*, iBitmap->Bitmap()), 
                                        TSize(AKN_LAYOUT_WINDOW_Form_data_field_elements_Line_4.iW, 
                                        AKN_LAYOUT_WINDOW_Form_data_field_elements_Line_4.iH));
                }
            }
        else
            {
            if (iBitmap && iBitmap->Bitmap())
                {
                AknIconUtils::SetSize(CONST_CAST(CFbsBitmap*, iBitmap->Bitmap()), 
                                        TSize(AKN_LAYOUT_WINDOW_List_pane_elements__single_graphic_heading__Line_1.iW, 
                                        AKN_LAYOUT_WINDOW_List_pane_elements__single_graphic_heading__Line_1.iH));
                }
            }
        }
    else
        {
        if (iBitmap && iBitmap->Bitmap())
            {
            AknIconUtils::SetSize(CONST_CAST(CFbsBitmap*, iBitmap->Bitmap()), 
                        TSize(AKN_LAYOUT_WINDOW_List_pane_elements__single_graphic_heading__Line_1.iW, 
                        AKN_LAYOUT_WINDOW_List_pane_elements__single_graphic_heading__Line_1.iH));
            }
        }                       */
    }
    


// -----------------------------------------------------------------------------
// CEikCaptionedControl::HandleControlEventL
// Implementation of MCoeControlObserver observer interface for observing touch button 
// events used with MFNE editors.
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikCaptionedControl::HandleControlEventL(CCoeControl* /*aControl*/,
				 MCoeControlObserver::TCoeEvent /*aEventType*/)
	{
    }

MAknsControlContext* CEikCaptionedControl::GetDialogControlContext(const CCoeControl* aDialog) const
    {
    MAknsControlContext* parentCc = AknsDrawUtils::ControlContext(aDialog);
    if (!parentCc)
        {
        // try to find a window owning parent control
        const CCoeControl* parent = WindowOwningParent();
        parentCc = AknsDrawUtils::ControlContext(parent);    
        }
    return parentCc;    
    }

const CCoeControl* CEikCaptionedControl::WindowOwningParent() const
    {
    const CCoeControl* parent = this;

    while ( parent && !parent->OwnsWindow() )
        {
        parent = parent->Parent();
        }

    return parent;
    }  
    
void CEikCaptionedControl::SetCurrent(TBool aSelected, TBool aRedraw)
    {
    if (aSelected)
        iCapCFlags|=ECurrent;
    else
        iCapCFlags&=(~ECurrent);
    iIsCurrentLine=aSelected;

    // Only form controls need to play animation
    if( iDialogPage && iIsFormControl )
        {
        if( !aSelected )
            {
            // Deselected -> unacquire animation
            if( iExtension->iAnimation )
                {
                iExtension->iAnimation->Pause();
                iExtension->iAnimation = iDialogPage->AcquireAnim( EFalse, iExtension );
                }
            }
        else
            {
            // Acquire highlight animation
            if( !iIsEditable )
                {
                iExtension->iAnimation = iDialogPage->AcquireAnim( ETrue, iExtension );

                if( iExtension->iAnimation )
                    {
                    // We need to apply the size because different lines can be
                    // of different size (at least in theory).
                    if( iExtension->iAnimation->Size() == Rect().Size() )
                        {
                        // No need to resize, just change the background used
                        // as animation input.
                        iExtension->iAnimation->ChangeHighlightBackground();
                        }
                    else
                        {
                        iExtension->iAnimation->SetHighlightSize( Rect().Size() );
                        }

                    // Animation playing is not started here (it is done when
                    // focus is received).
                    }
                }
            }
        }

    if ( iIsFormControl || !aRedraw )
        SetFocus(aSelected,ENoDrawNow);
    else
        SetFocus(aSelected,EDrawNow); 
    }


void CEikCaptionedControl::SetPartiallyVisible( TBool aPVisible )
    {
    iExtension->iPartiallyVisible = aPVisible;
    }
    
/*  
 * Special Label Class which appends colon to label text
 */

CEikCapCLabel::CEikCapCLabel() : iIsColonEnabled( EFalse ) 
    {
    }

CEikCapCLabel::~CEikCapCLabel()
    {
    }

void CEikCapCLabel::Draw( const TRect& aRect ) const
    {

    // <SKIN> // Make the caption label transparent.  Has to be done here as other labels (eg popupfield) rely on opaque labels.
    CWindowGc& gc = SystemGc() ;
    gc.SetBrushStyle( CGraphicsContext::ENullBrush ) ; 

    if ( ColonEnabled() ) 
        {
        TRAPD( err, const_cast<CEikCapCLabel*>(this)->DrawL( aRect ) )  ;  // const_cast and TRAP required to call DrawL() function
        if ( err != KErrNone )
            CEikLabel::Draw( aRect ) ; 
        }
    else
        CEikLabel::Draw( aRect ) ; 
    }


//static const TInt KUnicodeLeftToRightMark = 0x200E;
//static const TInt KUnicodeRightToLeftMark = 0x200F;
 
 
void CEikCapCLabel::DrawL( const TRect& /*aRect*/ ) 
    {
    // It might be necessary to expand the label to accommodate the colon without reducing the space available for text.
    // Store the original size so that it can be restored.
    TRect originalRect( Rect() );
    TRect modifiedRect( originalRect );

    // Store a pointer to the existing text
    HBufC* storedText = iText;
    // Create a local copy to modify, +1 is for colon
    HBufC* labelText = HBufC::NewLC( 
        storedText->Length() + KAknBidiExtraSpacePerLine + 1 );

    *labelText = *storedText;
    TPtr ptr = labelText->Des(); 
   
    AknBidiTextUtils::TParagraphDirectionality directionality =
        AknLayoutUtils::LayoutMirrored() ?
        AknBidiTextUtils::ERightToLeft :
        AknBidiTextUtils::ELeftToRight;

    AknBidiTextUtils::ConvertToVisualAndClipL(
        ptr,
        *Font(),
        Size().iWidth,
        Size().iWidth,
        directionality );

    // Increase the size of the control to ensure that the colon can be fitted in.
    TInt colonWidthInPixels = Font()->CharWidthInPixels( ':' );

    if ( AknLayoutUtils::LayoutMirrored() )
        {
        modifiedRect.iTl.iX -= colonWidthInPixels ;
        }
    else
        {
        modifiedRect.iBr.iX += colonWidthInPixels ;
        }
    SetRect( modifiedRect ) ;

    // Insert colon (in the beginning or in the end of the visual line)

    _LIT( KColon, ":" );

    if ( AknLayoutUtils::LayoutMirrored() )
        {
        ptr.Insert( 0, KColon );
        }
    else
        {
        ptr.Append( KColon );
        }
    
    // Switch the adjusted text in, draw it, and then restore the original text and dimensions
    iText = labelText ;

    TBool normalState =
        LogicalToVisualConversionUsed();

    // Disable logical-to-visual conversion in CEikLabel
    // because we have done it already
    UseLogicalToVisualConversion( EFalse );
    CEikLabel::Draw( modifiedRect ) ;

    UseLogicalToVisualConversion( normalState );
    iText = storedText ;
    SetRect( originalRect ) ;

    CleanupStack::PopAndDestroy() ;  // labelText
    }

TBool CEikCapCLabel::ColonEnabled() const 
    {
    return ( iIsColonEnabled ) ;
    }

void CEikCapCLabel::EnableColon( TBool aEnable ) 
    {
    iIsColonEnabled = aEnable ;
    }


