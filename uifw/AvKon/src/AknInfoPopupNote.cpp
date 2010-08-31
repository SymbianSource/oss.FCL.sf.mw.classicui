/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Info popup note UI control.
*
*/



// INCLUDE FILES

#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <eiklabel.h>
#include <gulicon.h>
#include <aknappui.h>
#include <AknUtils.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknStatuspaneUtils.h>
#include <touchfeedback.h>
#include "akntextcontrol.h"
#include "AknInfoPopupNote.h"
#include "AknInfoPopupNoteController.h"

#include <AknTasHook.h> // for testability hooks

// CONSTANTS
const TInt KMaxNumOfLines = 5; // max number of lines in popup

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ConstructL
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::ConstructL()
    {
    /* Popup should disappear quickly. By making popup as window-owning 
     * control, that backups graphics behind it (backed-up-behind window) 
     * we enable fast hiding. However, it eats more memory, and in OOM
     * situation backup is not done, but status pane is actually redrawn.
     * See Symbian documentation of RWindowBase::EnableBackup for more
     * information.
     */    
    
    delete iBgContext;
    iBgContext = NULL;

    iBgContext = CAknsFrameBackgroundControlContext::NewL(
        KAknsIIDQsnFrPopupPreview, TRect(), TRect(), EFalse );

    CreateWindowL();
    
    EnableDragEvents();
    SetAllowStrayPointers();
    
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        // try to enable window transparency
        if ( Window().SetTransparencyAlphaChannel() == KErrNone )
            {
            Window().SetRequiredDisplayMode( EColor16MA );
            Window().SetBackgroundColor( ~0 );
            }
        }

    DrawableWindow()->EnableBackup( EWindowBackupAreaBehind );

    DrawableWindow()->SetNonFading( ETrue);
    if ( !iText )
        {
        iText = CAknTextControl::NewL();
        iText->SetContainerWindowL( *this );
        iText->CopyControlContextFrom( this );
        iText->SetComponentsToInheritVisibility( ETrue );
        }

    iAvkonAppUi->AddToStackL( this, ECoeStackPriorityCba,
                              ECoeStackFlagRefusesAllKeys |
                              ECoeStackFlagRefusesFocus );

    DrawableWindow()->SetPointerGrab( ETrue );
    
    SetComponentsToInheritVisibility( ETrue );
    Hide();
    
    ControlEnv()->AddForegroundObserverL( *this );
    }

// -----------------------------------------------------------------------------
// NewL
// 
// -----------------------------------------------------------------------------
//
CAknInfoPopupNote* CAknInfoPopupNote::NewL(
        CAknInfoPopupNoteController& aController )
    {
    CAknInfoPopupNote* self = 
        new( ELeave ) CAknInfoPopupNote( aController );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    AKNTASHOOK_ADDL( self, "CAknInfoPopupNote" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknInfoPopupNote
// 
// -----------------------------------------------------------------------------
//
CAknInfoPopupNote::CAknInfoPopupNote( CAknInfoPopupNoteController& aController )
    : iController( aController ),
      iTooltipMode( EFalse ),
      iHideWhenAppFaded( ETrue ),
      iFloatingPositionUsed( EFalse ),
      iFloatingPosition( 0, 0 ),
      iAlignment( EHLeftVTop )

    {   
    }

// -----------------------------------------------------------------------------
// ~CAknInfoPopupNote
// 
// -----------------------------------------------------------------------------
//
CAknInfoPopupNote::~CAknInfoPopupNote()
    {
    AKNTASHOOK_REMOVE();
    ControlEnv()->RemoveForegroundObserver( *this );

    if ( iAvkonAppUi )
        {
        iAvkonAppUi->RemoveFromStack( this );
        }

    delete iBgContext;
    delete iText;
    }

// -----------------------------------------------------------------------------
// CountComponentControls
// 
// -----------------------------------------------------------------------------
//
TInt CAknInfoPopupNote::CountComponentControls() const
    {
    return 1;    
    }

// -----------------------------------------------------------------------------
// ComponentControl
// 
// -----------------------------------------------------------------------------
//
CCoeControl* CAknInfoPopupNote::ComponentControl( TInt /*aIndex*/ ) const 
    {
    return iText;
    }

// -----------------------------------------------------------------------------
// Hide
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::Hide()
    {
    if ( IsVisible() )
        {        
        MakeVisible( EFalse );

        // Change stacked control to refuse all key events while not visible.
        iAvkonAppUi->UpdateStackedControlFlags( this,
                                                ECoeStackFlagRefusesAllKeys,
                                                ECoeStackFlagRefusesAllKeys );
        }
    }

// -----------------------------------------------------------------------------
// SetTextL
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::SetTextL( const TDesC& aText )
    {
    if ( aText != iText->Text() )
        {
        iText->SetTextL( aText );

        for ( TInt i = 0; i < iText->NumberOfLines(); i++ )
            {
            // Draw the label after the background.
            CEikLabel* line = iText->Line( i );
            line->ActivateL(); // Never leaves

            if ( !IsVisible() )
                {
                line->MakeVisible( EFalse );
                }

            iText->SetLineModified( i, EFalse );
            }

        SetWindowLayoutL();

        if ( IsVisible() )
            {
            Window().Invalidate( Rect() );
            }
        }
    }

// -----------------------------------------------------------------------------
// GetText
// 
// -----------------------------------------------------------------------------
//
const TPtrC CAknInfoPopupNote::GetText() const
    {
    if ( iText->Text().Length() == 0 )
        {
        return KNullDesC().Ptr();
        }
    return iText->Text();
    }

// -----------------------------------------------------------------------------
// SetPositionAndAlignment
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::SetPositionAndAlignment( const TPoint& aPosition,
        const TGulAlignmentValue& aAlignment  )
    {
    iFloatingPositionUsed = ETrue;
    iFloatingPosition = aPosition;
    iAlignment = aAlignment;
    Relocate();
    }

// -----------------------------------------------------------------------------
// SetPositionAndAlignment
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::SetPositionByHighlight( const TRect& aHighlightRect )
    {
    SetRect( AknLayoutUtils::HighlightBasedRect( aHighlightRect, this ) );
    iFloatingPositionUsed = ETrue;
    iFloatingPosition = Position();
    iAlignment = EHLeftVTop;
    }

// -----------------------------------------------------------------------------
// RestoreDefaultPosition
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::RestoreDefaultPosition()
    {
    // Get parameter limits for popup preview text window
    TAknLayoutScalableParameterLimits limits = 
        AknLayoutScalable_Avkon::popup_preview_text_window_ParamLimits();

    // Select the variety index depending on the number of lines
    TInt variety = SelectWindowVariety( iText->NumberOfLines(), limits );

    // Get layout rects
    TRect rectScreen = iAvkonAppUi->ApplicationRect();
    TRect rectMainPane = rectScreen;
    TRect rectPopupWindow = RectFromLayout( rectMainPane,
        AknLayoutScalable_Avkon::popup_preview_text_window( variety ) );

    // Set the default position
    SetPosition( rectPopupWindow.iTl );
    iFloatingPositionUsed = EFalse;
    }

// -----------------------------------------------------------------------------
// SetTooltipModeL
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::SetTooltipModeL( const TBool aTooltipMode )
    {
    if ( iTooltipMode != aTooltipMode )
        {
        iTooltipMode = aTooltipMode;
        SetWindowLayoutL();
        }
    }

// -----------------------------------------------------------------------------
//  AppFaded
//
// -----------------------------------------------------------------------------
//

void CAknInfoPopupNote::HideWhenAppFaded( const TBool aHide )
    {
    iHideWhenAppFaded = aHide;
    }
    
// -----------------------------------------------------------------------------
// ShowL
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::ShowL()
    {
    // Info pop-up note is not shown, when it does not contain any text, or
    // when the screen background is faded by some other UI component.
    if ( !iText->Text().Length() || ( !iAvkonAppUi->IsForeground() 
    		&& iAvkonAppUi->IsFaded() && iHideWhenAppFaded ))
        {        
        return;
        }

    // Because info pop-up note has to be drawn over pop-up toolbar, which has
    // normal window priority, the window priority of info pop-up note has to
    // be also set again to be shown over toolbar.
    Window().SetOrdinalPosition( 0, ECoeWinPriorityNormal );

    if( !IsActivated() )
        {
        ActivateL();
        }

    MakeVisible( ETrue );

    // Change stacked control not to refuse key events
    iAvkonAppUi->UpdateStackedControlFlags( this, NULL,
                                            ECoeStackFlagRefusesAllKeys );    
    }

// -----------------------------------------------------------------------------
// Draw
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    if ( !AknsDrawUtils::Background( skin, iBgContext, gc, aRect ) )
        {
        gc.Clear( aRect );
        gc.DrawRect( aRect );
        }
    }

// -----------------------------------------------------------------------------
// SizeChanged
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::SizeChanged()
    {
    const TRect popupRect( Rect() );

    TRect windowPaneBgRect = RectFromLayout( popupRect,
        AknLayoutScalable_Avkon::bg_popup_preview_window_pane( 0 ) );

    // Note: bg_popup_preview_window_pane might not be the right outer rect,
    // but it is used for now, because bg_popup_preview_window_pane_g#
    // functions do not return the correct values.
    iOuterRect = windowPaneBgRect;
    iInnerRect = RectFromLayout( windowPaneBgRect,
        AknLayoutScalable_Avkon::bg_popup_preview_window_pane_g1() );

    iBgContext->SetFrameRects( iOuterRect, iInnerRect );
    }

// -----------------------------------------------------------------------------
// OfferKeyEventL
// 
// -----------------------------------------------------------------------------
//
TKeyResponse CAknInfoPopupNote::OfferKeyEventL( const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( aType == EEventKeyDown || aKeyEvent.iCode == EKeyEscape )
        {
        Hide();
        }

    return EKeyWasNotConsumed;
    }
    
// -----------------------------------------------------------------------------
// CAknInfoPopupNote::MakeVisible
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::MakeVisible( TBool aVisible )
    {
    if ( aVisible != IsVisible() )
        {
        CCoeControl::MakeVisible( aVisible );
        
        if ( aVisible )
            {
            iController.NotifyObservers(
                MAknInfoPopupNoteObserver::EInfoPopupNoteShown );
            }
        else
            {
            iController.NotifyObservers(
                MAknInfoPopupNoteObserver::EInfoPopupNoteHidden );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknInfoPopupNote::HandleResourceChange
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        TRAP_IGNORE( SetWindowLayoutL() );
        }
    else if ( aType == KAknsMessageSkinChange && iText )
        {
        TRgb textColor = KRgbBlack;
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG55 );
        TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iText, EColorLabelText,
                textColor ) );
        }
    else if( aType == KEikMessageFadeAllWindows )
        {
        if ( IsVisible() && iHideWhenAppFaded )
            {
            iController.HideInfoPopupNote();
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknInfoPopupNote::HandlePointerEventL
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        SetPointerCapture( ETrue );

        if ( aPointerEvent.iType == TPointerEvent::EButton1Down
             || aPointerEvent.iType == TPointerEvent::EButton1Up
             || aPointerEvent.iType == TPointerEvent::EDrag )
            {
            if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback )
                    {
                    feedback->InstantFeedback( ETouchFeedbackPopUp );
                    }
                }

            Hide();
            SetPointerCapture( EFalse ); 
            }
        }
    }

// -----------------------------------------------------------------------------
// SetWindowLayoutL
//
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::SetWindowLayoutL()
    {
    if ( iText && iText->Text().Length() > 0 )
        {
        if ( iTooltipMode )
            {
            SetTooltipWindowLayoutL();
            }
        else
            {
            SetInfoPopupWindowLayoutL();
            }
        }
    }

// -----------------------------------------------------------------------------
// SetInfoPopupWindowLayoutL
//
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::SetInfoPopupWindowLayoutL()
    {
    // Get parameter and table limits for popup preview text window
    TAknLayoutScalableParameterLimits limits = 
        AknLayoutScalable_Avkon::popup_preview_text_window_ParamLimits();

    TAknLayoutScalableTableLimits tableLimits =
        AknLayoutScalable_Avkon::popup_preview_text_window_t_Limits();

    // Get layout rects
    TRect rectScreen = iAvkonAppUi->ApplicationRect();
    TInt mainPaneVariety = Layout_Meta_Data::IsLandscapeOrientation() ? 4 : 1;
    TRect rectMainPane = RectFromLayout( rectScreen,
        AknLayoutScalable_Avkon::main_pane( mainPaneVariety ) );

    // Use first variety to be able to get the font for text parsing
    TInt firstVariety = SelectWindowVariety( 1, limits );

    TRect rectPopupWindow = RectFromLayout( rectMainPane,
        AknLayoutScalable_Avkon::popup_preview_text_window( firstVariety ) );

    TInt firstIndex = tableLimits.FirstIndex();
    TInt firstLineVariety = AknLayoutScalable_Avkon::
        popup_preview_text_window_t_ParamLimits( firstIndex ).FirstVariety();
        
    TAknTextLineLayout popupTextLayout =
        AknLayoutScalable_Avkon::popup_preview_text_window_t(
            firstIndex, firstLineVariety );

    TAknLayoutText layoutText;
    layoutText.LayoutText( rectPopupWindow, popupTextLayout );
    TRect rectText = layoutText.TextRect();

    // Prepare text parsing
    const CFont *font = layoutText.Font();

    CArrayFixFlat<TInt>* lineWidths 
        = new ( ELeave ) CArrayFixFlat<TInt>( KMaxNumOfLines );
    CleanupStack::PushL( lineWidths );

    for ( TInt i = 0; i < KMaxNumOfLines; i++ )
        {
        lineWidths->AppendL( rectText.Width() );
        }

    // Parse text
    iText->ParseTextL( font, lineWidths );
    TInt numberOfLines = iText->NumberOfLines();

    CleanupStack::PopAndDestroy( lineWidths );

    // Select the variety index depending on the number of lines
    TInt windowVariety = SelectWindowVariety( numberOfLines, limits );

    // Set layouts for window and text lines
    AknLayoutUtils::LayoutControl( this, rectMainPane,       
        AknLayoutScalable_Avkon::popup_preview_text_window( windowVariety ) );

    rectPopupWindow = Rect();
    iText->SetRect( rectPopupWindow );

    for ( TInt lineIndex = tableLimits.FirstIndex(), ii = 0;
          ( lineIndex <= tableLimits.LastIndex() ) && ( ii < numberOfLines );
          ++lineIndex, ++ii )
        {
        // Select the variety index depending on the number of lines
        TInt lineVariety = SelectLineVariety( numberOfLines, 
            AknLayoutScalable_Avkon::popup_preview_text_window_t_ParamLimits(
                lineIndex ) );

        popupTextLayout = AknLayoutScalable_Avkon::popup_preview_text_window_t(
            lineIndex, lineVariety );

        AknLayoutUtils::LayoutLabel( iText->Line( ii ), rectPopupWindow,
            popupTextLayout, font );
       }

    // Override text color
    TRgb textColor = KRgbBlack;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor,
        KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG55 );
    AknLayoutUtils::OverrideControlColorL( *iText, EColorLabelText, textColor );

    // Move pop-up note to right location
    if ( IsVisible() )
        {
        Relocate();
        }
    }

// -----------------------------------------------------------------------------
// SetTooltipWindowLayoutL
//
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::SetTooltipWindowLayoutL()
    {
    // Get parameter and table limits for popup preview text window
    TAknLayoutScalableParameterLimits limits = 
        AknLayoutScalable_Avkon::popup_preview_text_window_ParamLimits();

    TAknLayoutScalableTableLimits tableLimits =
        AknLayoutScalable_Avkon::popup_preview_text_window_t_Limits();

    // Get layout rects
    const TRect rectScreen = iAvkonAppUi->ApplicationRect();
    const TRect rectMainPane = rectScreen;

    // Set pop-up to contain only one line of text
    const TInt numberOfLines = 1;
    TInt windowVariety = SelectWindowVariety( numberOfLines, limits );

    TInt lineVariety = SelectLineVariety( numberOfLines, 
        AknLayoutScalable_Avkon:: popup_preview_text_window_t_ParamLimits(
             tableLimits.FirstIndex() ) );

    // Get the font for the text
    TRect rectPopupWindow = RectFromLayout( rectMainPane,
        AknLayoutScalable_Avkon::popup_preview_text_window(
            windowVariety ) );

    TAknTextComponentLayout popupTextLayout =
        AknLayoutScalable_Avkon::popup_preview_text_window_t(
            tableLimits.FirstIndex(), lineVariety );

    TAknLayoutText layoutText;
    layoutText.LayoutText( rectPopupWindow, popupTextLayout );
    const CFont *font = layoutText.Font();
    
    TInt maxLineWidth = ( rectMainPane.Width() - popupTextLayout.l() )
                        - popupTextLayout.r();

    TInt textWidth = font->TextWidthInPixels( iText->Text() );
    textWidth = Min( textWidth, maxLineWidth );

    // Parse text
    CArrayFixFlat<TInt>* lineWidths 
        = new ( ELeave ) CArrayFixFlat<TInt>( numberOfLines );
    CleanupStack::PushL( lineWidths );

    lineWidths->AppendL( textWidth );
    iText->ParseTextL( font, lineWidths );
    
    CleanupStack::PopAndDestroy( lineWidths );

    // Set layout for window
    rectPopupWindow = RectFromLayout( rectMainPane,
        AknLayoutScalable_Avkon::popup_preview_text_window( windowVariety ) );

    // Adjust window size depending on text length
    SetSize( TSize( textWidth + popupTextLayout.l() + popupTextLayout.r(),
                    rectPopupWindow.Height() ) );

    // Set layout for text lines
    rectPopupWindow = Rect();
    iText->SetRect( rectPopupWindow );

    for ( TInt lineIndex = tableLimits.FirstIndex(), ii = 0;
          ( lineIndex <= tableLimits.LastIndex() ) && ( ii < numberOfLines );
          ++lineIndex, ++ii )
        {
        popupTextLayout = AknLayoutScalable_Avkon::popup_preview_text_window_t(
            lineIndex, lineVariety );

        AknLayoutUtils::LayoutLabel( iText->Line( ii ), rectPopupWindow,
                                     popupTextLayout, font );
        }

    // Override text color
    TRgb textColor = KRgbBlack;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor,
        KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG55 );
    AknLayoutUtils::OverrideControlColorL( *iText, EColorLabelText, textColor );

    // Move tooltip to right location
    if ( IsVisible() )
        {
        Relocate();
        }
    }

// -----------------------------------------------------------------------------
// Relocate
// 
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::Relocate()
    {
    if ( !iFloatingPositionUsed )
        {
        return;
        }

    TRect rect( Rect() );
    TPoint delta( 0, 0 );

    switch (iAlignment)
        {
        case EHLeftVTop:
            {
            // Tooltip is left and top aligned.
            break;
            }
        case EHLeftVCenter:
            {
            // Tooltip left aligned and centred vertically.
            delta.iY = rect.Height() / 2;
            break;
            }
        case EHLeftVBottom:
            {
            // Tooltip is left aligned and at the bottom.
            delta.iY = rect.Height();
            break;
            }
        case EHCenterVTop:
            {
            // Tooltip is centre aligned horizontally and at the top.
            delta.iX = rect.Width() / 2;
            break;
            }
        case EHCenterVCenter:
            {
            // Tooltip is centred horizontally and vertically.
            delta.SetXY( rect.Width() / 2, rect.Height() / 2 );
            break;
            }
        case EHCenterVBottom:
            {
            // Tooltip is centred horizontally and at the bottom.
            delta.SetXY( rect.Width() / 2, rect.Height() );
            break;
            }
        case EHRightVTop:
            {
            // Tooltip is right and top aligned.
            delta.iX = rect.Width();
            break;
            }
        case EHRightVCenter:
            {
            // Tooltip right aligned and centred vertically.
            delta.SetXY( rect.Width(), rect.Height() / 2 );
            break;
            }
        case EHRightVBottom:
            {
            // Tooltip is right aligned and at the bottom.
            delta.SetXY( rect.Width(), rect.Height() );
            break;
            }
        default:
            {
            break;
            }
        }
        
    AdjustPosition( TPoint( iFloatingPosition - delta ) );

    if ( iFloatingPosition != iPosition )
        {
        SetPosition( iFloatingPosition );
        }
    }

// -----------------------------------------------------------------------------
// AdjustPosition
// Adjusts the position of the info pop-up note so that it fits the screen and
// does not overlap with the control pane.
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::AdjustPosition( const TPoint& aFloatingPosition )
    {
    TRect area( iAvkonAppUi->ApplicationRect() );

    if ( iAvkonAppUi->IsDisplayingControlBetweenPriorities(
             ECoeStackPriorityCba - 1, ECoeStackPriorityCba + 1 ) )
        {
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, area );

        if ( !AknStatuspaneUtils::StaconPaneActive() )
            {
            TRect statusPaneRect;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EStatusPane,
                                               statusPaneRect );
            
            area.BoundingRect( statusPaneRect );
            }
        }

    TRect rect( aFloatingPosition, Size() );

    iFloatingPosition.SetXY( Max( area.iTl.iX, Min( rect.iBr.iX, area.iBr.iX )
                              - rect.Width() ),
                         Max( area.iTl.iY, Min( rect.iBr.iY, area.iBr.iY )
                              - rect.Height() ) );
    }

// -----------------------------------------------------------------------------
// RectFromLayout
//
// -----------------------------------------------------------------------------
//
TRect CAknInfoPopupNote::RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout ) const
    {
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(aParent, lineLayout);
    return layoutRect.Rect();
    }

// -----------------------------------------------------------------------------
// SelectLineVariety
//
// -----------------------------------------------------------------------------
//
TInt CAknInfoPopupNote::SelectLineVariety( const TInt aNumberOfLines,
        const TAknLayoutScalableParameterLimits& aLimits ) const
    {
    return Min( Max( aNumberOfLines - 1, aLimits.FirstVariety() ),
                aLimits.LastVariety() );
    }

// -----------------------------------------------------------------------------
// SelectWindowVariety
//
// -----------------------------------------------------------------------------
//
TInt CAknInfoPopupNote::SelectWindowVariety( const TInt aNumberOfLines,
        const TAknLayoutScalableParameterLimits& aLimits ) const
    {
    TInt index = aNumberOfLines - 1;
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        index += 5;
        }

    return Min( Max( index, aLimits.FirstVariety() ),
                aLimits.LastVariety() );
    }

// -----------------------------------------------------------------------------
// HandleGainingForeground
//
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::HandleGainingForeground()
    {
    // empty implementation
    }
    
// -----------------------------------------------------------------------------
// HandleLosingForeground
//
// -----------------------------------------------------------------------------
//
void CAknInfoPopupNote::HandleLosingForeground()
    {
    if ( IsVisible() && iHideWhenAppFaded )
        {
        iController.HideInfoPopupNote();
        }
    }

//  End of File  
