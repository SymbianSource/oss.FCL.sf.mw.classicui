/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  View part of the preview pop-up component.
*
*/


// INCLUDE FILES
#include "AknPreviewPopUp.h"
#include <AknPreviewPopUpObserver.h>
#include <AknPreviewPopUpController.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>
#include <aknViewAppUi.h>
#include <AknsFrameBackgroundControlContext.h>
#include <akntouchpane.h>
#include <aknbutton.h>
#include <vwsdef.h>
#include <aknview.h>
#include <apgwgnam.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <akntransitionutils.h>
#include <AknTasHook.h> // for testability hooks
#include <touchfeedback.h>
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntranseffect.h>
#include <akntransitionutils.h>
const TInt KWindowPosition = 1000;             // window's position

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::NewL
// -----------------------------------------------------------------------------
//
CAknPreviewPopUp* CAknPreviewPopUp::NewL( CCoeControl& aContent,
        CAknPreviewPopUpController& aController,
        const TInt aStyle )
    {
    CAknPreviewPopUp* self = new ( ELeave ) CAknPreviewPopUp( aContent, 
                                                              aController,
                                                              aStyle );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    AKNTASHOOK_ADDL( self, "CAknPreviewPopUp" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::CAknPreviewPopUp
// -----------------------------------------------------------------------------
//
CAknPreviewPopUp::CAknPreviewPopUp( CCoeControl& aContent,
                                    CAknPreviewPopUpController& aController,
                                    const TInt aStyle )
    : iContent( aContent ),
      iController( aController ),
      iFlags( aStyle ),
      iAllowUpEvent(EFalse)
    {
    GfxTransEffect::Register( this, KGfxPreviewPopupControlUid );
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::~CAknPreviewPopUp
// -----------------------------------------------------------------------------
//
CAknPreviewPopUp::~CAknPreviewPopUp()
    {
    if( iIsDeleted )
        {
    	*iIsDeleted = ETrue ;
        iIsDeleted = 0 ;
        }

    if ( IsVisible() )
        {
        iCloseMenu = ETrue;
        iController.HidePopUp();
        }
		
    AKNTASHOOK_REMOVE();
    
    GfxTransEffect::Deregister( this );

    if ( CapturesPointer() )
        {
        SetPointerCapture( EFalse );
        }

    if ( iAvkonAppUi )
        {
        iAvkonAppUi->RemoveFromStack( this );
        }
         
    delete iBgContext;
    delete iHeadingText;
    delete iClosingIcon;
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::ConstructL
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::ConstructL()
    {
    // set skin ids
    if ( iFlags & CAknPreviewPopUpController::ELayoutSubMenu )
        {
        iFrameId = KAknsIIDQsnFrPopupSub;
        iCenterId = KAknsIIDQsnFrPopupCenterSubmenu;
        }
    else
        {
        iFrameId = KAknsIIDQsnFrPopupPreview;
        iCenterId = KAknsIIDDefault;
        }
    
    TRect nullRect( 0,0,0,0 );
    iBgContext = CAknsFrameBackgroundControlContext::NewL(
        iFrameId, nullRect, nullRect, EFalse );

    CreateWindowL();
    EnableWindowTransparency();
    
    TInt stackPriority = ECoeStackPriorityCba;
    
    if ( !( iFlags & CAknPreviewPopUpController::EPermanentMode ) )
        {
        Window().SetPointerGrab( ETrue );
        SetGloballyCapturing( ETrue );
        Window().SetOrdinalPosition(KWindowPosition);
        }
    else
        {
        stackPriority = ECoeStackPriorityDefault;
        Window().SetOrdinalPosition( 0, ECoeWinPriorityNormal );
        }

    iAvkonAppUi->AddToStackL( this, stackPriority,
                              ECoeStackFlagRefusesAllKeys |
                              ECoeStackFlagRefusesFocus );

    EnableDragEvents();
    SetComponentsToInheritVisibility( ETrue );

    iContent.SetBackground( this );
    iContent.SetContainerWindowL( *this );
    iContent.ActivateL();

    if ( iFlags & CAknPreviewPopUpController::EFixedMode )
        {
        TRect appWindow;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow, appWindow );
        
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( appWindow, AknLayoutScalable_Avkon::popup_preview_fixed_window().LayoutLine() );
        
        SetRect( layoutRect.Rect() );
        }

    MakeVisible( EFalse );   
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::Show
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::Show()
    {
    if ( !( iFlags & CAknPreviewPopUpController::EPermanentMode ) )
        {
        Window().SetOrdinalPosition( 0 );
        iAvkonAppUi->UpdateStackedControlFlags( this, NULL,
                                                ECoeStackFlagRefusesAllKeys );

        SetPointerCapture( ETrue );
        }

    iCloseMenu = EFalse; 
    TBool useTfx = !( iFlags & CAknPreviewPopUpController::EPermanentMode 
            || iFlags & CAknPreviewPopUpController::EFixedMode );
    
    if ( useTfx && GfxTransEffect::IsRegistered( this ) )
        {
        GfxTransEffect::Begin( this, KGfxControlAppearAction );
        MakeVisible( ETrue );
        GfxTransEffect::SetDemarcation( this, iPosition );
        GfxTransEffect::End( this );
        }
    else
        {
        MakeVisible( ETrue );
        }
    if( GrabbingComponent() )
        {
        iCloseMenu = ETrue;
        }
    iController.NotifyObservers( MAknPreviewPopUpObserver::EPreviewPopUpShown );
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::Hide
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::Hide()
    {
    if ( !IsVisible() || ( GrabbingComponent() && !iCloseMenu && 
            !( iFlags & CAknPreviewPopUpController::EPermanentMode ) ) )
        {
        return; 
        }

    // Skip disappear transition if the popup is either permanent, fixed or
    // faded. Fading status is checked because there can't be two parallel
    // effects applied to the same window.
    TBool useTfx = !( iFlags & CAknPreviewPopUpController::EPermanentMode 
            || iFlags & CAknPreviewPopUpController::EFixedMode ) 
                    && !Window().IsFaded();
    
    if ( useTfx && GfxTransEffect::IsRegistered( this ) )
        {
        GfxTransEffect::Begin( this, KGfxControlDisappearAction );
        MakeVisible( EFalse );
        GfxTransEffect::End( this );
        }
    else
        {
        MakeVisible( EFalse );
        }

    Window().ClearRedrawStore();

    if ( !( iFlags & CAknPreviewPopUpController::EPermanentMode ) )
        {
        Window().SetOrdinalPosition( KWindowPosition );
        iAvkonAppUi->UpdateStackedControlFlags( this,
                                                ECoeStackFlagRefusesAllKeys,
                                                ECoeStackFlagRefusesAllKeys );
        }

    if ( CapturesPointer() )
        {
        SetPointerCapture( EFalse );
        }

    iController.NotifyObservers( MAknPreviewPopUpObserver::EPreviewPopUpHidden );
   }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::Flags
// -----------------------------------------------------------------------------
//
TInt CAknPreviewPopUp::Flags() const
    {
    return iFlags;
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::SetHeadingTextL
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::SetHeadingTextL( const TDesC& aText )
    {
    delete iHeadingText;
    iHeadingText = NULL;
    
    if ( aText.Length() > 0 )
        {
        iHeadingText = aText.AllocL();    
        CreateClosingIconL();
        }
    else
        {
        if ( iClosingIcon )
            {
            delete iClosingIcon;
            iClosingIcon = NULL;
            }
        }    
    SetSize( MinimumSize() );
    }
    
// -----------------------------------------------------------------------------
// CAknPreviewPopUp::MinimumSize
// -----------------------------------------------------------------------------
//
TSize CAknPreviewPopUp::MinimumSize()
    {
    TSize size;
    
    if ( iFlags & CAknPreviewPopUpController::EFixedMode )
        {
        TRect appWindow;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow, appWindow );

        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( appWindow, AknLayoutScalable_Avkon::popup_preview_fixed_window().LayoutLine() );

        size = layoutRect.Rect().Size();
        }
    else
        {
        TSize contentSize( iContent.MinimumSize() );
        TSize headingSize;

        // heading
        if ( HasHeading() )
            {
            TRect rect( 0, 0, 100, 100 ); // dummy rect to calculate heading
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( rect, AknLayoutScalable_Avkon::heading_preview_pane().LayoutLine() );
            
            headingSize.iHeight = layoutRect.Rect().Height() + layoutRect.Rect().iTl.iY;
            }
        
        size = contentSize + headingSize;
        // If size is empty return it now so the size won't be increased below
        if ( size == TSize() )
            {
            return size; 
            }
        // frame borders
        TAknWindowComponentLayout center( CenterLayout() );
        size.iWidth += center.LayoutLine().il + center.LayoutLine().ir;
        size.iHeight += center.LayoutLine().it + center.LayoutLine().ib;
        }
    
    return size;
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    
    switch ( aType )
        {
        case KAknsMessageSkinChange:
            if ( iClosingIcon )
                {
                delete iClosingIcon;
                iClosingIcon = NULL;
                TRAP_IGNORE( CreateClosingIconL() );
                }
            break;
            
        case KEikDynamicLayoutVariantSwitch:
            if ( iFlags & CAknPreviewPopUpController::EFixedMode )
                {
                TRect appWindow;
                AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow, appWindow );
                
                TAknLayoutRect layoutRect;
                layoutRect.LayoutRect( appWindow, AknLayoutScalable_Avkon::popup_preview_fixed_window().LayoutLine() );
                
                SetRect( layoutRect.Rect() );
                }
            else
                {
                SetSize( MinimumSize() );
                }
            break;
            
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::HandleControlEventL
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::HandleControlEventL( CCoeControl* aControl, 
                                            TCoeEvent aEventType )
    {
    if ( aControl == iClosingIcon && aEventType == EEventStateChanged )
        {
        Hide();
        }
    }
    
// -----------------------------------------------------------------------------
// CAknPreviewPopUp::Draw
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::Draw( CWindowGc& aGc, const CCoeControl& /*aControl*/,
                             const TRect& aRect ) const
    {
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        DrawBackground( aGc, aRect );
        }
    else
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

        AknsDrawUtils::Background( skin, cc, this, aGc, aRect ); 
        }
    }

    
// -----------------------------------------------------------------------------
// CAknPreviewPopUp::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CAknPreviewPopUp::CountComponentControls() const
    {
    if ( !iClosingIcon )
        {
        return 1; // iContent
        }
        
    return 2; // iContent, iClosingIcon
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CAknPreviewPopUp::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case 0:
            return &iContent;
            
        case 1:
            return iClosingIcon;
            
        default:
            return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::SizeChanged
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::SizeChanged()
    {
    TRect rect( Rect() );
    TAknLayoutRect layoutRect;
    TAknWindowComponentLayout center( CenterLayout() );

    layoutRect.LayoutRect( rect, center.LayoutLine() );
    iBgContext->SetFrameRects( rect, layoutRect.Rect() );
    
    if ( iFlags & CAknPreviewPopUpController::EFixedMode )
        {
        if ( iFlags & CAknPreviewPopUpController::EExcludeFrames )
            {
            rect = layoutRect.Rect();
            
            if ( HasHeading() )
                {
                layoutRect.LayoutRect( Rect(), AknLayoutScalable_Avkon::heading_preview_pane().LayoutLine() );
                rect.iTl.iY = layoutRect.Rect().iBr.iY;
                }
            }
        
        iContent.SetRect( rect );
        }
    else
        {
        // content
        TPoint contentPosition;
        contentPosition.iX = center.LayoutLine().il;
        
        if ( HasHeading() )
            {
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( rect, AknLayoutScalable_Avkon::heading_preview_pane().LayoutLine() );
            contentPosition.iY = layoutRect.Rect().iBr.iY;
            }
        else
            {
            contentPosition.iY = center.LayoutLine().it;
            }

        TSize contentSize( iContent.MinimumSize() );
        TSize maximumSize( Abs( layoutRect.Rect().iBr.iX - contentPosition.iX ),
                           Abs( layoutRect.Rect().iBr.iY - contentPosition.iY ) );
        
        if ( maximumSize.iWidth > contentSize.iWidth ||
             maximumSize.iHeight > contentSize.iHeight )
            {
            contentSize = maximumSize;
            }
        
        iContent.SetExtent( contentPosition, contentSize );
        }
    
    // closing icon    
    if ( iClosingIcon )
        {
        layoutRect.LayoutRect( Rect(), TAknWindowComponentLayout::Compose(
            AknLayoutScalable_Avkon::heading_preview_pane(),
            AknLayoutScalable_Avkon::heading_preview_pane_g1() ).LayoutLine() );

        iClosingIcon->SetRect( layoutRect.Rect() );
        }
    DrawDeferred();        
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {   
	TBool isDelete = EFalse; 
	iIsDeleted = &isDelete;
	
    if ( AknLayoutUtils::PenEnabled() )
        {
        iCloseMenu = EFalse;
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up && !IsVisible() )
            {
            SetPointerCapture( EFalse );
            }

        // redirect pointer event to content
        if ( Rect().Contains( aPointerEvent.iPosition ) && IsVisible() )
            {
            iAllowUpEvent = ETrue;         
            CleanupStack::PushL( TCleanupItem( CleanLocalRef, this ) );
            CCoeControl::HandlePointerEventL( aPointerEvent );
            CleanupStack::Pop();
            if( isDelete )
            	{
            	return;
            	}
            if ( !( iFlags & CAknPreviewPopUpController::EPermanentMode ) && aPointerEvent.iType == TPointerEvent::EButton1Up && IsVisible() )
                {
            	  // if pointer up is already redirected to the content, but the popup is still visible,
            	  // then the original timeout has already happened and we need to reset the timer.
            	  // TSW Error EJZG-7JR3PC.
            	  iController.ResetTimer();
                }
            }
        else
            {
            if ( !( iFlags & CAknPreviewPopUpController::EPermanentMode ) && 
                aPointerEvent.iType != TPointerEvent::EDrag &&
                aPointerEvent.iType != TPointerEvent::EButtonRepeat )
                {
                
                // handle here mainly up and down events outside popup rect 
                if ( iFlags & CAknPreviewPopUpController::EDontClose )
                    {
                    // If EDontClose flag is on:
                    // Up event outside popup's rect don't close popup,
                    // but resets timer to give more time for popup
                    // All other events outside popup's rect (mainly down)
                    // hides the popup
                    
                    if ( aPointerEvent.iType != TPointerEvent::EButton1Up )
                        {
                        // popup will be hiden when EButton1Down comes.
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback )
                            {
                            TTouchLogicalFeedback feedbackType = ETouchFeedbackPopUp;
                            if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                                {
                                feedbackType = ETouchFeedbackOptionsMenuClosed;
                                }
                            feedback->InstantFeedback( feedbackType );
                            }        
                        iCloseMenu = ETrue; 
                        iController.HidePopUp(); 
                        }
                    else if ( IsVisible() )
                        {
                        iController.ResetTimer();
                        }    
                    }
                else
                    {
                    MTouchFeedback* feedback = MTouchFeedback::Instance();
                    if ( feedback )
                        {
                        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                            {
                            feedback->InstantFeedback( this,
                                                       ETouchFeedbackPopUp,
                                                       ETouchFeedbackVibra,
                                                       aPointerEvent );
                            }
                        else
                            {
                            // popup will be hiden when EButton1Down comes.
                            TTouchLogicalFeedback feedbackType = ETouchFeedbackPopUp;
                            if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                                {
                                feedbackType = ETouchFeedbackOptionsMenuClosed;
                                }
                            feedback->InstantFeedback( this,
                                                       feedbackType,
                                                       aPointerEvent );
                            }
                        }
                    iCloseMenu = ETrue;
                    iController.HidePopUp();
                    }          
                }
                
            // If EDontClose flag is on, also button up is forwarded for base class    
            if ( iFlags & CAknPreviewPopUpController::EDontClose )
                {
                if ( aPointerEvent.iType == TPointerEvent::EDrag || 
                    aPointerEvent.iType == TPointerEvent::EButtonRepeat ||
                    (aPointerEvent.iType == TPointerEvent::EButton1Up && iAllowUpEvent ) )
                    {
                    CleanupStack::PushL( TCleanupItem( CleanLocalRef, this ) );
                    CCoeControl::HandlePointerEventL( aPointerEvent );
                    CleanupStack::Pop();
                    if( isDelete )
                    	{
                    	return;
                    	}
                    }
                }
            else
                {
                if ( aPointerEvent.iType == TPointerEvent::EDrag || 
                    aPointerEvent.iType == TPointerEvent::EButtonRepeat )
                    {
                    CleanupStack::PushL( TCleanupItem( CleanLocalRef, this ) );
                    CCoeControl::HandlePointerEventL( aPointerEvent );
                    CleanupStack::Pop();
                    if( isDelete )
                    	{
                    	return;
                    	}
                    }
                }
                
            }
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            iAllowUpEvent = EFalse;
            }
        }
       
    iIsDeleted = NULL;
    }
    
// -----------------------------------------------------------------------------
// CAknPreviewPopUp::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CAknPreviewPopUp::OfferKeyEventL( const TKeyEvent& /*aKeyEvent*/,
                                               TEventCode aType )
    {
    TKeyResponse ret ( EKeyWasNotConsumed );

    if ( !( iFlags & CAknPreviewPopUpController::EPermanentMode ) )
        {
        if ( !( iFlags & CAknPreviewPopUpController::EConsumeKeys ) )
            {
            iCloseMenu = ETrue;
            iController.HidePopUp();
            }
        else
            {
            if ( aType == EEventKey || aType == EEventKeyUp )
                {
                iCloseMenu = ETrue;
                iController.HidePopUp();

                ret = EKeyWasConsumed;
                }
            }
        }

    if ( CapturesPointer() )
        {
        SetPointerCapture( EFalse );
        }

    return ret;
    }
    
// -----------------------------------------------------------------------------
// CAknPreviewPopUp::MopSupplyObject
// -----------------------------------------------------------------------------
//
TTypeUid::Ptr CAknPreviewPopUp::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == MAknsControlContext::ETypeId )
        {
        if ( iBgContext )
            {
            return MAknsControlContext::SupplyMopObject( aId, iBgContext );
            }
        else
            {
            return TTypeUid::Null();
            }
        }
        
    return CCoeControl::MopSupplyObject( aId );
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::Draw
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();

    TRegionFix<4> region;
    region.AddRect( Rect() );
    region.SubRect( iContent.Rect() );
    gc.SetClippingRegion( region );

    DrawBackground( gc, aRect );

    gc.CancelClippingRegion();
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::CenterLayout
// -----------------------------------------------------------------------------
//
TAknWindowComponentLayout CAknPreviewPopUp::CenterLayout()
    {
    if ( iFlags & CAknPreviewPopUpController::ELayoutSubMenu )
        {
        return AknLayoutScalable_Avkon::bg_popup_sub_pane_g1();
        }

    return AknLayoutScalable_Avkon::bg_popup_preview_window_pane_g1();
    }
    
// -----------------------------------------------------------------------------
// CAknPreviewPopUp::CreateClosingIconL
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::CreateClosingIconL()
    {
    if ( !iClosingIcon && AknLayoutUtils::PenEnabled() &&
         !( iFlags & CAknPreviewPopUpController::EPermanentMode ) )
        {
        iClosingIcon = CAknButton::NewL( KNullDesC, 0, 0, 0, 0, 0, 0, 0, 0, 
                                         KNullDesC, KNullDesC, 0, 0, 
                                         KAknsIIDQgnIndiTpIdle );

        iClosingIcon->SetContainerWindowL( *this );
        iClosingIcon->SetObserver( this );
        iClosingIcon->SetIconScaleMode( EAspectRatioPreserved );
        iClosingIcon->ActivateL();
        }
    else if ( iClosingIcon && !AknLayoutUtils::PenEnabled() )
        {
        delete iClosingIcon;
        iClosingIcon = NULL;
        }
    }
    
// -----------------------------------------------------------------------------
// CAknPreviewPopUp::HasHeading
// -----------------------------------------------------------------------------
//
TBool CAknPreviewPopUp::HasHeading() const
    {
    if ( !iHeadingText )
        {
        return EFalse;
        }
        
    if ( *iHeadingText == KNullDesC )
        {
        return EFalse;
        }
        
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::DrawBackground
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::DrawBackground( CWindowGc& aGc, const TRect& aRect ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    
    TBool drawn = AknsDrawUtils::Background( skin, cc, this, aGc, aRect, 
        KAknsDrawParamNoClearUnderImage );

    if ( !drawn )
        {
        aGc.Clear( aRect );
        }
    
    if ( HasHeading() )
        {
        aGc.SetClippingRect( aRect );
        
        // heading graphics
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( Rect(),
            TAknWindowComponentLayout::Compose( 
            AknLayoutScalable_Avkon::heading_preview_pane(),
            AknLayoutScalable_Avkon::bg_popup_heading_pane_cp2( 1 ) ).LayoutLine() );
        
        TRect outerRect( layoutRect.Rect() );
        
        layoutRect.LayoutRect( outerRect, 
            AknLayoutScalable_Avkon::bg_popup_heading_pane_g1() );
            
        // There's no error checking since if skinned drawing fails heading 
        // text will be drawn on top of the background.
        AknsDrawUtils::DrawFrame( skin, aGc, outerRect, layoutRect.Rect(), 
            KAknsIIDQsnFrPopupHeading, KAknsIIDDefault );
        
        // heading text                               
        TAknLayoutText textLayout;
        textLayout.LayoutText( Rect(),
            TAknWindowComponentLayout::ComposeText(
            AknLayoutScalable_Avkon::heading_preview_pane(),
            AknLayoutScalable_Avkon::heading_preview_pane_t1( 1 ) ).LayoutLine() );

        aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
        
        TRgb color( textLayout.Color() );

        if ( iFlags & CAknPreviewPopUpController::ELayoutSubMenu )
            {
            AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnTextColors,
                 EAknsCIQsnTextColorsCG55 );
            }
        else
            {
            AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnTextColors,
                 EAknsCIQsnTextColorsCG19 );
            }
        
        textLayout.DrawText( aGc, *iHeadingText, ETrue, color );
        
        aGc.CancelClippingRect();
        }   
    }

// -----------------------------------------------------------------------------
// CAknPreviewPopUp::CleanLocalRef
// -----------------------------------------------------------------------------
//
void CAknPreviewPopUp::CleanLocalRef( TAny* aParam )
    {
    static_cast<CAknPreviewPopUp*>( aParam )->iIsDeleted = NULL;
    }

//  End of File  

