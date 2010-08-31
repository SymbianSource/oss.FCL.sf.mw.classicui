/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Popup toolbar extension
*
*/


#include <barsread.h>
#include <AknsFrameBackgroundControlContext.h>
#include <AknsDrawUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <aknbutton.h>
#include <eikedwin.h>
#include <akntoolbarextension.h>
#include <touchfeedback.h>
#include <eikcolib.h>

#include "akntoolbaritem.h"
#include "akntoolbarextensionview.h"

#include "aknresourceprovider.h"

const TInt KNoItemSelected = -1; 
const TUint32 KToolbarExtensionBgColor = 0x00000000;
const TInt KToolBarExtensionBgAlpha = 0x7F;
const TInt KToolbarButtonBeforeTimeout = 300; 

enum TDirection
    {
    EDirectionLeft = 0,  
    EDirectionRight, 
    EDirectionUp,
    EDirectionDown, 
    ENoDirection
    }; 

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknToolbarExtensionView::NewL
// ---------------------------------------------------------------------------
//
CAknToolbarExtensionView* CAknToolbarExtensionView::NewL( TResourceReader& aReader,
    CAknToolbarExtension* aExtension )
    {
    CAknToolbarExtensionView* self = new ( ELeave ) CAknToolbarExtensionView( aExtension);
    CleanupStack::PushL( self );
    self->ConstructL(); 
    self->ConstructFromResourceL( aReader );
    CleanupStack::Pop( self );
    
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknToolbarExtensionView::~CAknToolbarExtensionView()
    {
    SetFocus( EFalse );
    CEikonEnv::Static()->EikAppUi()->RemoveFromStack( this );
    if ( iSelectedItem >= 0 && iSelectedItem < iItems.Count() ) 
        {
        TRAP_IGNORE( iItems[iSelectedItem]->SetIsSelectedL(EFalse) ); 
        }
    iVisibleItems.Reset();
    iItems.ResetAndDestroy(); 
    delete iFrameContext; 
    delete iResourceProvider;
    }
    
// ---------------------------------------------------------------------------
// From class CCoeControl.
// Constructs extension view
// ---------------------------------------------------------------------------
//
void CAknToolbarExtensionView::ConstructFromResourceL( TResourceReader& aReader )
    {
    TInt numberOfItems = aReader.ReadInt16();
    TBool noFrame(EFalse); 
    for ( TInt i = 0; i < numberOfItems; ++i )
        {
        CAknToolbarItem* item = ConstructControlLC( aReader ); 
        if ( item->Control() )
            {
            iItems.AppendL( item ); 
            item->Control()->SetContainerWindowL( *this );
            item->Control()->SetObserver( iExtension );

            if ( item->ControlType() == EAknCtButton )
                {
                CAknButton* button = static_cast<CAknButton*>(item->Control() ); 
                TInt flags = button->ButtonFlags(); 
                if ( !noFrame && ( !( flags & KAknButtonNoFrame ) ||  
                    !( flags & KAknButtonPressedDownFrame ) ) ) 
                    {
                    // Set flag KAknButtonNoFrame for all buttons except the one
                    // after an editor
                    flags |= KAknButtonNoFrame; 
                    flags |= KAknButtonPressedDownFrame;
                    button->RegisterResourceProvider( iResourceProvider );
                    button->SetButtonFlags( flags ); 
                    }
                else if ( noFrame )
                    {
                    // Setting frames for the button that comes after an editor
                    if ( flags & KAknButtonNoFrame )
                        {
                        flags &= ~KAknButtonNoFrame;
                        flags &= ~KAknButtonPressedDownFrame;  
                        button->SetButtonFlags( flags ); 
                        }
                    noFrame = EFalse; 
                    }
                AdjustButtonL( *button ); 
                }
            else 
                {
                if ( Editor( item->ControlType() ) ) 
                    {
                    noFrame = ETrue; 
                    }
                }
            CleanupStack::Pop( item ); 
            }
        else
            {
            CleanupStack::PopAndDestroy( item );
            item = NULL;
            }
        }
        
    if ( iExtension->ExtensionFlags() & KAknTbExtensionDsaMode )
        {
        iFrameContext->SetFrame( KAknsIIDQgnGrafPopupTrans ); 
        }
        
    ActivateL(); 
    // Activating here the items, because ActivateL uses CountComponentControls
    // which is currently 0 since iVisibleItems is still empty
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        iItems[i]->Control()->ActivateL(); 
        }
    SetComponentsToInheritVisibility( ETrue );
    }

// ---------------------------------------------------------------------------
// From class CCoeControl.
// Shows or hides extension view
// ---------------------------------------------------------------------------
//
void CAknToolbarExtensionView::MakeVisible( TBool aVisible )
    {
    TBool isVisible = IsVisible(); 

    if ( aVisible && !isVisible )
        {
            // the toolbar extension is shown, this happens only with pointer event? 
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->InstantFeedback( ETouchFeedbackPopUp );
                }

        TRect rect; 
        TRAP_IGNORE( rect = CalculateSizeL() ); 
        CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( this, 
            0, ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );
        CEikonEnv::Static()->EikAppUi()->HandleStackChanged();
        
        // Calling this here, so that iVisibleItems array has been updated and
        // all items visible in extension get call makevisible
        CAknControl::MakeVisible( aVisible );
        SetRect( rect );     
        DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNormal );    
        TBool floating = !IsNonFocusing(); 
        for ( TInt i = 0; i < iItems.Count(); i++ )
            {
            if ( !floating && Editor( iItems[i]->ControlType() ) )
                {
                TRAP_IGNORE( SelectItemL( i, ETrue ) ); 
                break; 
                }
            if ( floating && iItems[i]->ControlType() == EAknCtButton )
                {
                CAknButton* button = static_cast<CAknButton*>( iItems[i]->Control() ); 
                TInt j = 0; 
                while( button->State( j ) )
                    {
                    //Setting the texts empty
                    TRAP_IGNORE( button->State( j++ )->SetTextL( KNullDesC ) ); 
                    }
                }
            }

        if ( floating && iVisibleItems.Count() )
            {
            iSelectedItem = NextFocusable( 1 ); 
            TRAP_IGNORE( iVisibleItems[iSelectedItem]->SetFocusL( 
                ETrue, EFalse, ENoDrawNow, this ) ); 
            }
        if ( iPreviousItem >= 0 && IsNonFocusing() )
            {            
            CAknToolbarItem* prevItem = iVisibleItems[iPreviousItem];
            if ( prevItem->Control() )
                {
                if ( prevItem->ControlType() == EAknCtButton ||
                        prevItem->ControlType() == EAknCtToolbarExtension )
                   {
                   CAknButton* button = static_cast<CAknButton*>( prevItem->Control() );
                   button->ResetState();
                   }
                }
            iPreviousItem = KNoItemSelected;
            }
        DrawNow(); 
        }
    else if ( !aVisible && isVisible )
        {
        CEikonEnv::Static()->EikAppUi()->UpdateStackedControlFlags( this, 
            ~0, ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );
        CEikonEnv::Static()->EikAppUi()->HandleStackChanged();
        CAknControl::MakeVisible( aVisible );
        TRAP_IGNORE( SelectItemL( iSelectedItem, EFalse ) ); 
        DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );
        }
    else 
        {
        CAknControl::MakeVisible( aVisible );
        }
    }

// ---------------------------------------------------------------------------
// From class OfferKeyEventL.
// Consumes key events if floating toolbar extension
// ---------------------------------------------------------------------------
//
TKeyResponse CAknToolbarExtensionView::OfferKeyEventL( 
    const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    if ( aKeyEvent.iCode == EKeyYes || !IsVisible() )
        {
        return EKeyWasNotConsumed; 
        }
    //LSK, RSK, KeyOk
    else if ( IsNonFocusing() && aType == EEventKey 
            && ( aKeyEvent.iCode == EKeyDevice0 
                    || aKeyEvent.iCode == EKeyDevice1 
                    || aKeyEvent.iCode == EKeyDevice3 ) )
        {
        if( IsVisible()&& ( aKeyEvent.iCode == EKeyDevice0 ||
                            aKeyEvent.iCode == EKeyDevice1 ))
        	{
			iExtension->SetShown(EFalse);
		    return EKeyWasConsumed;	
        	}
        return EKeyWasNotConsumed;
        }
    // When this is visible and without focus, nothing to do 
    //
    // Exception for key filter: Image capture key (not a complete solution:
    //       the key map may change corrding to the products)
    else if ( IsNonFocusing()&& aType == EEventKey 
            &&(!( aKeyEvent.iScanCode == EStdKeyDevice3
                  || aKeyEvent.iScanCode == EStdKeyEnter )) )
        {
        return EKeyWasConsumed;
        }
    else if( IsVisible() && aType == EEventKey )
        {
        switch ( aKeyEvent.iCode )
            {
            case EKeyRightArrow:
                MoveHighlightL( EDirectionRight, 0 ); 
                break; 
            case EKeyLeftArrow:
                MoveHighlightL( EDirectionLeft, 0 ); 
                break; 
            case EKeyUpArrow:
                MoveHighlightL( EDirectionUp, 0 ); 
                break; 
            case EKeyDownArrow:
                MoveHighlightL( EDirectionDown, 0 ); 
                break; 
            default: 
                break;     
            }
        return EKeyWasConsumed;
        }
    else
        {
        CAknToolbarItem* item = NULL; 
        if ( iSelectedItem >= 0 && iSelectedItem < iVisibleItems.Count() )
            {
            item = iVisibleItems[iSelectedItem]; 
            }
        // All key events can be given to buttons, other toolbar items must 
        // be seleceted to get events
        if ( item && item->Control() )
            {
            if ( ( item->ControlType() == EAknCtButton ) || 
               ( item->ControlType() == EAknCtToolbarExtension )  || item->IsSelected() )
                {
                if ( aKeyEvent.iScanCode == EStdKeyDevice0 )
                    {
                    TKeyEvent keyEvent = aKeyEvent; 
                    // Button does not accept key events if the code is EStdKeyDevice0
                    // so changing the key event to EStdKeyDevice3    
                    keyEvent.iScanCode = EStdKeyDevice3; 
                    item->Control()->OfferKeyEventL( keyEvent, aType );
                    }
                else if ( aKeyEvent.iScanCode == EStdKeyDevice1 )
                    {
                    MakeVisible( EFalse ); 
                    // Close extension view and let also extension know about it
                    // so it can change state
                    iExtension->ViewClosed(); 
                    // Toolbar should perhaps be closed too! 
                    }
                else
                    {
                    item->Control()->OfferKeyEventL( aKeyEvent, aType );
                    }
                }
            }

        return EKeyWasNotConsumed; 
        }
        
    }

// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::CountComponentControls
// Gets the number of controls contained in a compound control.
// -----------------------------------------------------------------------------
//
TInt CAknToolbarExtensionView::CountComponentControls() const
    {
    return iVisibleItems.Count(); 
    }

// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::ComponentControl
// Gets the specified component of a compound control.
// -----------------------------------------------------------------------------
//    
CCoeControl* CAknToolbarExtensionView::ComponentControl( TInt aIndex ) const
    {
    if ( aIndex < 0 || aIndex >= iVisibleItems.Count() )
        {
        return NULL; 
        }
    return iVisibleItems[aIndex]->Control(); 
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::HandleResourceChange
// Handles resource changes
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::HandleResourceChange( TInt aType )
    {

    iResourceProvider->HandleResourceChange( aType );

    // Hide extension, if non-focusing, and no pen support. Later...
    
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        if ( IsVisible() )
            {
            TRect rect; 
            TRAP_IGNORE( rect = CalculateSizeL() ); 
            SetRect( rect ); 
            }
        }

    // Not calling base class function here, because only visible controls would 
    // be returned by ComponentControl, and thus the font would not be updated
    // for all controls
    for ( TInt i = 0; i < iItems.Count(); ++i )
        {
        iItems[i]->Control()->HandleResourceChange( aType );
        if ( iItems[i]->ControlType() == EAknCtButton )
            {
            CAknButton* button = static_cast<CAknButton*>( iItems[i]->Control() ); 

            if ( aType == KEikDynamicLayoutVariantSwitch )
                {
                TBool useOutline = iExtension->ExtensionFlags() & KAknTbExtensionDsaMode;  
                const CFont* font = AknLayoutUtils::FontFromId( AknLayoutScalable_Avkon::
                    cell_tb_ext_pane_t1( useOutline ? 0 : 1 ).LayoutLine().FontId() );
                button->SetTextFont( font ); 
                }
            
            if ( aType == KAknsMessageSkinChange )
                {
                if ( iExtension->ExtensionFlags() & KAknTbExtensionDsaMode )
                    {
                    TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                        *button, EColorControlBackground, KRgbWhite ) );
                    TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                        *button, EColorButtonText, KRgbBlack ) );
                    }
                }
            }
        }



    // Remember to check here if iSelectedItem still is in iVisibleItems, and if 
    // not then do something. 
    if ( ( aType == KAknsMessageSkinChange || 
        aType == KEikDynamicLayoutVariantSwitch ) && IsVisible() )
        {
        DrawDeferred(); 
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::HandlePointerEventL( 
    const TPointerEvent& aPointerEvent )
    {
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        if ( !Rect().Contains( aPointerEvent.iPosition) )
            {
            iIsDownOutside = ETrue;
            }
        else
            {
            iIsDownOutside = EFalse;
            }
        }
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        if ( !Rect().Contains( aPointerEvent.iPosition) && iIsDownOutside )
            {
            // tapped outside view, 
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->InstantFeedback( ETouchFeedbackPopUp );
                }

            MakeVisible( EFalse ); 
            // Close extension view and let also extension know about it
            // so it can change state
            iExtension->ViewClosed(); 
            iIsDownOutside = EFalse;
            return; 
            }
        }

    TPointerEvent event( aPointerEvent );
    TBool override ( EFalse );
    
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down && IsNonFocusing() && iPreviousItem >=0 )
        {
        CAknToolbarItem* prevItem = iVisibleItems[iPreviousItem];
        if ( prevItem->Control() &&
             !prevItem->Control()->Rect().Contains( aPointerEvent.iPosition ) )
            {
            if ( prevItem->ControlType() == EAknCtButton ||
                    prevItem->ControlType() == EAknCtToolbarExtension )
               {
               CAknButton* button = static_cast<CAknButton*>( prevItem->Control() );
               event.iType = TPointerEvent::EButton1Up;
               button->HandlePointerEventL ( event );
               }
            }            
        }
    // Cancel previous button
    if ( iPreviousItem >=0 && ( aPointerEvent.iType == TPointerEvent::EDrag || 
        aPointerEvent.iType == TPointerEvent::EButtonRepeat ) )
        {
        CAknToolbarItem* prevItem = iVisibleItems[iPreviousItem];

        if ( prevItem->Control() &&
             !prevItem->Control()->Rect().Contains( aPointerEvent.iPosition ) )
                {
                if ( prevItem->ControlType() == EAknCtButton ||
                     prevItem->ControlType() == EAknCtToolbarExtension )
                    {
                    CAknButton* button = static_cast<CAknButton*>( prevItem->Control() );
                    event.iType = TPointerEvent::EButton1Up;
                    button->HandlePointerEventL ( event );
                    override = ETrue;
                    iPreviousItem = KNoItemSelected;
                    }
                }        
        }
    
    CAknToolbarItem* item = NULL;
    for ( TInt ii = 0; ii < iVisibleItems.Count(); ++ii )
        {
        item = iVisibleItems[ii];
        if ( item->Control() && 
             item->Control()->Rect().Contains( aPointerEvent.iPosition ) )
            {
            if ( item->ControlType() == EAknCtButton || 
                 item->ControlType() == EAknCtToolbarExtension )
                {
                CAknButton* button = static_cast<CAknButton*>( item->Control() ); 
                if ( ii != iPreviousItem )
                    {
                    if ( !button->IsDimmed() && !IsNonFocusing() )
                        {
                        MoveHighlightL( ENoDirection, ii ); 
                        // focus has moved from one button to another due to dragging, 
                        // give sensitive feedback
                        if ( iPreviousItem != iSelectedItem )
                            {
                            MTouchFeedback* feedback = MTouchFeedback::Instance();
                            if ( feedback && 
                            ( aPointerEvent.iType == TPointerEvent::EDrag ||
                              aPointerEvent.iType == TPointerEvent::EButtonRepeat ) )
                                {
                                feedback->InstantFeedback( ETouchFeedbackSensitiveButton );
                                }
                            }
                        }
                    if ( aPointerEvent.iType == TPointerEvent::EDrag || 
                         aPointerEvent.iType == TPointerEvent::EButtonRepeat )
                        {
                        // focus has moved from one button to another due to dragging, 
                        // give sensitive feedback
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback && 
                        ( aPointerEvent.iType == TPointerEvent::EDrag ||
                          aPointerEvent.iType == TPointerEvent::EButtonRepeat ) )
                            {
                            feedback->InstantFeedback( ETouchFeedbackSensitiveButton );
                            }
                        button->SetHelpNoteTimeouts( KToolbarButtonBeforeTimeout, 0 );
                        event.iType = TPointerEvent::EButton1Down;
                        button->HandlePointerEventL( event );
                        override = ETrue;
                        }
                    iPreviousItem = ii;
                    }
                
                if ( aPointerEvent.iType == TPointerEvent::EButton1Down )                    
                    {
                    iDownItem = ii;
                    button->SetHelpNoteTimeouts( KToolbarButtonBeforeTimeout, 0 );
                    }
                
                if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                    {
                    // Up and down events are in different items, give basic
                    // feedback to the released item.
                    if ( ii != iDownItem )
                        {
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback )
                            {
                            feedback->InstantFeedback( ETouchFeedbackBasicButton );
                            }
                        }
                
                    button->HandlePointerEventL( aPointerEvent );
                    iPreviousItem = KNoItemSelected;
                    override = ETrue;
                    }
                }
            if ( IsNonFocusing() )
                {
                SelectItemL( ii, ETrue );
                }
            }
        }
    if ( !override )        
        {
        CAknControl::HandlePointerEventL( aPointerEvent );        
        }
    }


// -----------------------------------------------------------------------------
// Returns control corresponding the specified command id. 
// -----------------------------------------------------------------------------
//
CCoeControl* CAknToolbarExtensionView::ControlOrNull( TInt aCommandId ) const
    {
    for ( TInt i=0; i < iItems.Count(); i++ )
        {
        if ( aCommandId == iItems[i]->CommandId() )
            {
            return iItems[i]->Control(); 
            }
        }
    return NULL; 
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtension::CommandIdByControl
// 
// -----------------------------------------------------------------------------
// 
TInt CAknToolbarExtensionView::CommandIdByControl( CCoeControl* aControl ) const
    {
    for ( TInt i=0; i < iItems.Count(); i++ )
        {
        if ( aControl == iItems[i]->Control() )
            {
            return iItems[i]->CommandId(); 
            }
        }
    return KErrNotFound; 
    }




// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::Editor
// Checks if the controltype given is editor
// -----------------------------------------------------------------------------
//
TBool CAknToolbarExtensionView::Editor( TInt aControlType )
    {
    // This is almost copied from toolbar item, perhaps to CAknToolbarUtils
    switch ( aControlType )
        {
        case EEikCtEdwin:
        case EEikCtGlobalTextEditor:
        case EEikCtRichTextEditor:
        case EAknCtIntegerEdwin:
        case EEikCtFlPtEd:
        case EEikCtFxPtEd:
            return ETrue; 
        default:
            return EFalse;
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::AddItemL
// Adds new extension item
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::AddItemL( CCoeControl* aItem,
                                         TInt aType,
                                         TInt aCommandId,
                                         TInt aFlags,
                                         TInt aIndex )
    {
    if ( aItem && aIndex >= 0 && aIndex <= iItems.Count() )
        {
        aItem->SetContainerWindowL( *this );
        aItem->SetObserver( iExtension );
        aItem->ActivateL(); 
        CAknToolbarItem* tbItem = new ( ELeave ) CAknToolbarItem( aItem, aType, 
            aCommandId, aFlags );
        CleanupStack::PushL( tbItem );
        iItems.InsertL( tbItem, aIndex );
        CleanupStack::Pop( tbItem );
        if ( aType == EAknCtButton )
            {
            CAknButton* button = static_cast<CAknButton*>( aItem ); 
            AdjustButtonL( *button );
            }
        CheckButtonFrames( ETrue, aIndex ); 
        // Do something here for the selected item when focusing toolbar ready
        }
    else
        {
        User::Leave( KErrArgument );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::AdjustButtonL
// Adjusts button to what is needed by toolbar extension view. 
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::AdjustButtonL( CAknButton& aButton )
    {
    aButton.SetTextAndIconAlignment( CAknButton::EIconOverText ); 

    TBool useOutline = iExtension->ExtensionFlags() & KAknTbExtensionDsaMode;  
    const CFont* font = AknLayoutUtils::FontFromId( AknLayoutScalable_Avkon::
        cell_tb_ext_pane_t1( useOutline ? 0 : 1 ).LayoutLine().FontId() );

    aButton.SetTextFont( font ); 
    aButton.SetTextColorIds( KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG60 );

    if ( iExtension->ExtensionFlags() & KAknTbExtensionDsaMode )
        {
        AknLayoutUtils::OverrideControlColorL( aButton, 
            EColorControlBackground, KRgbWhite );
        AknLayoutUtils::OverrideControlColorL( aButton, 
            EColorButtonText, KRgbBlack );
        }
    }



// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::RemoveItemL
// Removes an item corresponding to command id
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::RemoveItemL( TInt aCommandId )
    {
    TInt itemIndex = ToolbarItemIndexById( EFalse, aCommandId );
    if ( itemIndex == KErrNotFound )
        {
        User::Leave( KErrNotFound ); 
        }
    if ( itemIndex >= 0 && itemIndex < iItems.Count() )
        {
        // Need to remove item also from iVisibleItems array, so the non-existent
        // item is not returned by ComponentControl
        TInt visibleIndex = ToolbarItemIndexById( ETrue, aCommandId ); 
        if ( visibleIndex >= 0 && visibleIndex < iVisibleItems.Count() )
            {
            iVisibleItems.Remove( visibleIndex ); 
            }
        delete iItems[itemIndex];
        iItems.Remove( itemIndex );
        // Need to check button frames so that only the item next to editor has
        // frames
        CheckButtonFrames( EFalse, itemIndex ); 
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::Draw
// Draw frames for extension view
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::Draw( const TRect& aRect ) const
    {
    TRect rect( Rect() );
    CWindowGc& gc = SystemGc();
    gc.SetClippingRect( aRect );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if ( iExtension->ExtensionFlags() & KAknTbExtensionDsaMode )
        {
        gc.SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );
        gc.SetBrushColor( TRgb( KToolbarExtensionBgColor, KToolBarExtensionBgAlpha ) );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.DrawRect( rect );
        gc.SetDrawMode( CGraphicsContext::EDrawModePEN );
        TSize penSize( 1, 1 );
        gc.SetPenSize( penSize );
        gc.SetPenStyle( CGraphicsContext::EDottedPen );
        gc.SetPenColor( KRgbWhite );
        gc.SetBrushStyle( CGraphicsContext::ENullBrush );
        gc.DrawRect( rect );
        }
    else
        {
        AknsDrawUtils::Background( skin, iFrameContext, gc, rect );
        }


    // draw toolbar item highlight
    if ( !IsNonFocusing() && iSelectedItem != KNoItemSelected )
        {
        CAknToolbarItem* item = iVisibleItems[iSelectedItem];
        if ( item && item->HighlightRect().Intersects( aRect ) )
            {
            TRect outerRect( item->HighlightRect() );
            TRect innerRect(outerRect); 

            TAknWindowLineLayout unit = AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine();
            innerRect.Shrink( unit.iW/10, unit.iH/10 ); 

            if ( !AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(), 
                                            gc, outerRect, innerRect,
                                            KAknsIIDQsnFrGrid, KAknsIIDDefault ) )
                {
                gc.SetBrushColor( KRgbRed );
                gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                gc.DrawRect( item->HighlightRect() );
                }                
            }
        }


    }

// ---------------------------------------------------------------------------
// Default constructor
// ---------------------------------------------------------------------------
//
CAknToolbarExtensionView::CAknToolbarExtensionView( 
    CAknToolbarExtension* aExtension): iExtension( aExtension ),
    iSelectedItem( KNoItemSelected ), iNumberOfColumns( 1 ),
    iIsDownOutside( EFalse )
    {
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::ConstructL
// 2nd phase constructor
// -----------------------------------------------------------------------------
// 
void CAknToolbarExtensionView::ConstructL()
    {
    CreateWindowL(); 
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        Window().SetRequiredDisplayMode( EColor16MA ); // Without this, ACT does not work in all cases in HW
        TInt err = Window().SetTransparencyAlphaChannel();

        if ( err == KErrNone )
            {
            // Set the window initially completely transparent. This needs to be called only once.
            Window().SetBackgroundColor(~0);
            if ( iExtension->ExtensionFlags() & KAknTbExtensionTransparent )
                {
                iFrameContext = CAknsFrameBackgroundControlContext::NewL( KAknsIIDQgnGrafPopupTrans, 
                    TRect(), TRect(), EFalse );  
                }
            else
                {
                iFrameContext = CAknsFrameBackgroundControlContext::NewL( KAknsIIDQsnFrPopupSub, 
                    TRect(), TRect(), EFalse );  
                }
            }
        else
            {
            iFrameContext = CAknsFrameBackgroundControlContext::NewL( KAknsIIDQsnFrPopupSub, 
                TRect(), TRect(), EFalse );  
            
            }
        }
    else
        {
        iFrameContext = CAknsFrameBackgroundControlContext::NewL( KAknsIIDQsnFrPopupSub, 
            TRect(), TRect(), EFalse );  
        }
                
    SetGloballyCapturing( ETrue );
    SetPointerCapture( ETrue );
    // Control stack priority needs to be same as toolbars, otherwise floating
    // toolbar will receive the key events when extension is open. If lowering 
    // toolbar's control stack priority, then this can be lowered too. 
    CEikonEnv::Static()->EikAppUi()->AddToStackL( this, ECoeStackPriorityCba,
        ECoeStackFlagRefusesFocus | ECoeStackFlagRefusesAllKeys );
    MakeVisible( EFalse ); 
    SetFocusing( EFalse ); 

    iResourceProvider = CAknResourceProvider::NewL();
    iPreviousItem = KNoItemSelected;
    }

// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::ConstructControlLC
// Constructs one of the toolbar extension items
// -----------------------------------------------------------------------------
// 
CAknToolbarItem* CAknToolbarExtensionView::ConstructControlLC( TResourceReader& aReader )
    {
    CAknToolbarItem* item = new(ELeave) CAknToolbarItem;
    CleanupStack::PushL( item );
    item->ConstructFromResourceL( aReader );
    return item;
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::CalculateSizeL
// Calculates size and position for toolbar extension
// -----------------------------------------------------------------------------
// 
TRect CAknToolbarExtensionView::CalculateSizeL()
    {
    iVisibleItems.Reset();
    TBool landscape = Layout_Meta_Data::IsLandscapeOrientation(); 
    
    
    TRect extensionRect;
    TRect windowRect;
    TRect gridExtRect;
    TRect cellExtRect;

    TRect mainPaneRect = static_cast<CEikAppUiFactory*> 
                        ( iEikonEnv->AppUiFactory() )->ClientRect();
    TBool floating = !IsNonFocusing(); 

    if ( floating )
        {
        extensionRect = RectFromLayout( mainPaneRect,
            AknLayoutScalable_Avkon::popup_tb_float_extension_window( 0 ) );

        windowRect = TRect( TPoint(), extensionRect.Size() );

        gridExtRect = RectFromLayout( windowRect,
            AknLayoutScalable_Avkon::grid_tb_float_ext_pane( 0 ) );

        cellExtRect = RectFromLayout( gridExtRect,
            AknLayoutScalable_Avkon::cell_tb_float_ext_pane( 0, 0, 0 ) );
        }   
    else 
        {
        extensionRect = RectFromLayout( mainPaneRect,
            AknLayoutScalable_Avkon::popup_tb_extension_window( 0 ) );

        windowRect = TRect( TPoint(), extensionRect.Size() );

        gridExtRect = RectFromLayout( windowRect,
            AknLayoutScalable_Avkon::grid_tb_ext_pane( landscape ? 1 : 0 ) );

        cellExtRect = RectFromLayout( gridExtRect,
            AknLayoutScalable_Avkon::cell_tb_ext_pane( landscape ? 1 : 0, 0, 0 ) );
        }

    TSize buttonSize = cellExtRect.Size(); 

    iNumberOfColumns = gridExtRect.Width() / buttonSize.iWidth; 
   
    // Calculate and set controls positions according to layout rects
    TInt extensionWidth = CalculateControlPositions( 
        windowRect, gridExtRect, cellExtRect );
    
    TSize viewSize( extensionWidth + ( extensionRect.Width() - gridExtRect.Width() ),
        ( extensionRect.Height() - gridExtRect.Height() ) + iNumberOfRows * 
        buttonSize.iHeight ); 
    
    //reset the height in portrait mode
    if ( !landscape )
        {
        //In some cases, extension rect is more larger than grid rect. 
        //And for they are only used to define the margin size, width is more exact than height.
        viewSize = TSize( extensionWidth + ( extensionRect.Width() - gridExtRect.Width() ),
            ( extensionRect.Width() - gridExtRect.Width() ) + iNumberOfRows * 
            buttonSize.iHeight ); 
        }

    TInt variety = GetVariety( iNumberOfRows - 1, landscape );

     // To get the correct y-coordinate
    TRect positionRect = RectFromLayout( mainPaneRect, floating ? 
         AknLayoutScalable_Avkon::popup_tb_float_extension_window( variety ) : 
         AknLayoutScalable_Avkon::popup_tb_extension_window( variety ) );
         
    if( landscape && !floating )
        {

        TRect extButtonRect( iExtension->Rect() );

        // Calculate new y coordinate according to button middle point
        TInt newY = 
            ( extButtonRect.iTl.iY + ( extButtonRect.Height() / 2 ) )
             - viewSize.iHeight / 2 
             + mainPaneRect.iTl.iY;
             
        // Check that rect with new y fits to extension view area
        if( newY < extensionRect.iTl.iY ) // Top
            {
            newY = extensionRect.iTl.iY;
            }
        else if( newY + viewSize.iHeight > extensionRect.iBr.iY ) // Bottom
            {
            newY = positionRect.iTl.iY;
            }
        positionRect.iTl.iY = newY;
        }
    //In some case, such as browser application, 
    //view position is incorrect in portait mode. So, reset the position 
    //according to the view size and toolbar window position.
    else if ( !landscape && !floating 
            && iExtension && iExtension->DrawableWindow() )
        {        
        TPoint buttonPos = iExtension->DrawableWindow()->Position();
        TInt newY = buttonPos.iY - viewSize.iHeight;
        if ( newY < extensionRect.iTl.iY )
            {
            newY = extensionRect.iTl.iY;
            }
        positionRect.iTl.iY = newY;
        }
        
    TInt xCoordinate = extensionRect.iTl.iX; 
    // Get 
    if ( iNumberOfRows == 1 )
        {
        variety = 0; 
        // Currently checking from number of items, might need to be changed
        if ( iVisibleItems.Count() == 2 )
            {
            variety = landscape ? 5 : 1; 
            }
        else if ( iVisibleItems.Count() == 3 && landscape)
            {
            variety = 6; 
            }
        extensionRect = RectFromLayout( mainPaneRect,
            AknLayoutScalable_Avkon::popup_tb_extension_window( variety ) );
        xCoordinate = extensionRect.iTl.iX; 
        }

    TPoint position( xCoordinate, positionRect.iTl.iY ); 

    TRect outerRect( TPoint(), viewSize );
    TRect innerRect(outerRect); 

    TAknWindowLineLayout unit = AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine();
    innerRect.Shrink( unit.iW/10, unit.iH/10 ); 
    iFrameContext->SetFrameRects( outerRect , innerRect );

    return TRect( position, viewSize ); 
    }

// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::CalculateControlPositions
// 
// -----------------------------------------------------------------------------
//
TInt CAknToolbarExtensionView::CalculateControlPositions( TRect& aWindowRect, 
                                                          TRect& aGridRect, 
                                                          TRect& aCellRect )
    {
    TInt width( 0 ), extensionWidth( 0 ), row( 0 );
    TPoint controlPosition( 0, 0 );
    TInt maxNumberOfRows = aGridRect.Height() / aCellRect.Height();
    TSize cellSize = aCellRect.Size();
    TInt extGridRight = aGridRect.iBr.iX;
    TInt extGridLeft = aGridRect.iTl.iX;
    TBool floating = !IsNonFocusing();
    // iVisibleItems may not be updated, so count hidden items
    TInt visibleItems( iItems.Count() - CountHiddenItems() );
    
    // If extension does not fill the whole grid rect, this takes the missing
    // cells width into account when locating items from right to left
    if ( AknLayoutUtils::LayoutMirrored() && visibleItems < iNumberOfColumns )
        {
        TInt missingCells( iNumberOfColumns - visibleItems );
        extGridRight = aGridRect.iBr.iX - cellSize.iWidth * missingCells;
        }

    // Fetch button icon size
    TSize iconSize;
    if ( floating )
        {
        iconSize = RectFromLayout( aCellRect, 
            AknLayoutScalable_Avkon::cell_tb_float_ext_pane_g1( 1 ) ).Size(); 
        }
    else
        {
        iconSize = RectFromLayout( aCellRect, 
        AknLayoutScalable_Avkon::cell_tb_ext_pane_g1( 1 ) ).Size(); 
        }
    
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        if ( iItems[i]->IsHidden() )
            {
            continue; 
            }
        // Buttons
        if ( iItems[i]->ControlType() == EAknCtButton )
            {

            // Layout items from right to left -> calculate position from right
            // end of the grid rect
            if ( AknLayoutUtils::LayoutMirrored() )
                {
                controlPosition.SetXY( extGridRight - width - cellSize.iWidth,
                    aGridRect.iTl.iY + row * cellSize.iHeight ); 
                }
            // Left to right
            else
                {
                controlPosition.SetXY( extGridLeft + width,
                    aGridRect.iTl.iY + row * cellSize.iHeight ); 
                }
                
            width += cellSize.iWidth; 
            iItems[i]->Control()->SetExtent( controlPosition, cellSize ); 
            TRAP_IGNORE( iVisibleItems.AppendL( iItems[i] ) ); 
            CAknButton* button = static_cast<CAknButton*>( 
                iItems[i]->Control() ); 
            button->SetIconSize( iconSize ); 
            if ( floating )
                {
                TRect highlightRect = RectFromLayout( 
                    TRect( controlPosition, cellSize ), 
                    AknLayoutScalable_Avkon::grid_highlight_pane_cp12( 0 ) ); 
                iItems[i]->SetHighlightRect( highlightRect ); 
                }
            }
        // Editors take the whole row
        else if ( Editor( iItems[i]->ControlType() ) )
            {
            // Changing to next line
            if ( width > 0 )
                {
                width = 0; 
                row++; 
                }
            if ( row >= maxNumberOfRows )
                {
                break; 
                }

            TInt position = maxNumberOfRows - row - 1; 
            TRAP_IGNORE( ResizeFindPaneL( aWindowRect, 
                Layout_Meta_Data::IsLandscapeOrientation(), position, i ) ); 
            width = aGridRect.Width(); 
            }
        else
            {
            // Other controls here later..
            }

        extensionWidth = Max( extensionWidth , width ); 
        
        // No more items to this row
        if ( width + cellSize.iWidth > aGridRect.Width() )
            {
            width = 0;
            // No more item to extension
            if ( row + 1 >= maxNumberOfRows || i + 1 == iItems.Count() )
                {
                break; 
                }
                
            // Switch row only if there are visible items left to locate
            if ( iVisibleItems.Count() < visibleItems )
                {
                row++;
                }
            }

        }
    iNumberOfRows = row + 1;
    return extensionWidth;
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::CountHiddenItems
// Returns hidden items count
// -----------------------------------------------------------------------------
//
TInt CAknToolbarExtensionView::CountHiddenItems()
    {
    TInt hiddenItems( 0 );
    for ( TInt i = 0; i < iItems.Count(); i++ )
        {
        if ( iItems[i]->IsHidden() )
            {
            hiddenItems++;
            }
        }
    return hiddenItems;
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::SelectItemL
// Selects or unselects items
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::SelectItemL( TInt aIndex, TBool aSelect )
    {
    if ( aSelect )
        {
        if ( aIndex != iSelectedItem )
            {
            if ( iSelectedItem > KNoItemSelected &&
                 iSelectedItem < iVisibleItems.Count() )
                {
                iVisibleItems[iSelectedItem]->SetIsSelectedL( EFalse );
                }

            if ( aIndex > KNoItemSelected && aIndex < iVisibleItems.Count() )
                {
                if ( iVisibleItems[aIndex]->SetIsSelectedL( ETrue ) )
                    {
                    iSelectedItem = aIndex;
                    }
                else
                    {
                    iSelectedItem = KNoItemSelected;
                    }
                }
            else
                {
                iSelectedItem = KNoItemSelected;
                }
            }
        }
    else
        {
        if ( aIndex == iSelectedItem )
            {
            if ( aIndex != KNoItemSelected && aIndex < iVisibleItems.Count() )
                {
                iVisibleItems[aIndex]->SetIsSelectedL( EFalse );
                }
            iSelectedItem = KNoItemSelected;
            }
        }
    }



// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::RectFromLayout
// -----------------------------------------------------------------------------
//
TRect CAknToolbarExtensionView::RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout ) const
    {
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, lineLayout );
    return layoutRect.Rect();
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::ResizeFindPane
// Resizes editor and the button after it. 
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::ResizeFindPaneL( TRect& aWindowRect, TBool aLandscape,
    TInt aPosition, TInt& aIndex )
    {
    TRect editorRect = RectFromLayout( aWindowRect,
        AknLayoutScalable_Avkon::tb_ext_find_pane( aLandscape ? 1 : 0 ) );
            
    editorRect.Move( 0, -editorRect.Height() * ( aPosition ) ); 

    TAknTextLineLayout layoutLine = 
        AknLayoutScalable_Avkon::tb_ext_find_pane_t1( 0 ).LayoutLine();
    TAknLayoutText layoutText;
    layoutText.LayoutText( editorRect, layoutLine );
    // Using curretly the skin color id of hwr/vkb input field
    TAknsQsnTextColorsIndex colorIndex = EAknsCIQsnTextColorsCG60;    

    CEikEdwin* edwin = static_cast<CEikEdwin*>( iItems[aIndex]->Control() ); 
    AknLayoutUtils::LayoutEdwin( edwin, editorRect, layoutLine, colorIndex ); 

    iVisibleItems.AppendL( iItems[aIndex] ); 

    if ( aIndex + 1 >= iItems.Count() || iItems[aIndex +1]->ControlType() != 
        EAknCtButton )
        {
        // If no button after editor, then return
        return; 
        }
    aIndex++; 
    // Now calculate the size for the button after editor
    TRect findButtonRect = RectFromLayout( editorRect, 
        AknLayoutScalable_Avkon::tb_ext_find_button_pane( 0 ) ); 
    iItems[aIndex]->Control()->SetRect( findButtonRect ); 
    iVisibleItems.AppendL( iItems[aIndex] ); 
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::GetVariety
// -----------------------------------------------------------------------------
//
TInt CAknToolbarExtensionView::GetVariety( TInt aRow, TBool aLandscape )
    {
    TInt variety = 0; 
    if ( IsNonFocusing() )
        {
        TInt index = iExtension->ExtensionPosition(); 
        switch ( aRow ) 
            {
            case 0: 
                if ( index == 0 )
                    {
                    variety = aLandscape ? 7 : 2; 
                    }
                else if ( index == 1 )
                    {
                    variety = aLandscape ? 6 : 2; 
                    }
                else 
                    {
                    variety = aLandscape ? 5 : 1; 
                    }
                break; 
            case 1: 
                if ( index == 0 )
                    {
                    variety = aLandscape ? 0 : 3; 
                    }
                else if ( index == 1 )
                    {
                    variety = aLandscape ? 6 : 3; 
                    }
                else 
                    {
                    variety = aLandscape ? 8 : 3; 
                    }
                break; 
            case 2: 
            default: 
                variety = aLandscape ? 0 : 4; 
                break; 
            case 3: 
                variety = 0; 
                break; 
            }
        }
    else 
        {
        switch ( aRow ) 
            {
            case 0: 
                variety = 3; 
                break; 
            case 1: 
                variety = 2; 
                break; 
            case 2: 
                variety = 1; 
                break; 
            case 3: 
            default: 
                variety = 0; 
                break; 
            }        
        }
    return variety;     
    }


// -----------------------------------------------------------------------------
// When an item is added, hidden or removed, there is a need to check that
// the buttons have correct frames. 
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::CheckButtonFrames( TBool aAdd, TInt aIndex )
    {
    // @todo What if adding editors? Then need to check next buttons, does this 
    // work then?
    
    // this is the index from which to remove noframes flag if necessary
    TInt index = aIndex; 
    if ( aIndex > 0 && Editor( iItems[aIndex - 1]->ControlType() ) )
        {
        // Add here later code also for hiding/unhiding
        if ( iItems[aIndex]->ControlType() == EAknCtButton )     
            {
            CAknButton* button = static_cast<CAknButton*>( iItems[aIndex]->Control() ); 
            TInt flags = button->ButtonFlags(); 
            // Add frames for the button because it comes after an editor
            if ( flags & KAknButtonNoFrame )
                {
                flags &= ~KAknButtonNoFrame; 
                flags &= ~KAknButtonPressedDownFrame; 
                button->UnregisterResourceProvider();
                button->SetButtonFlags( flags ); 
                }
            }
        index++; 
        }

    if ( aAdd && iItems.Count() > index && 
        iItems[index]->ControlType() == EAknCtButton  ) 
        {
        CAknButton* button = static_cast<CAknButton*>( iItems[index]->Control() ); 
        TInt flags = button->ButtonFlags(); 
        // Checking that the button that was previously after editor
        // does not have frames
        if ( !( flags & KAknButtonNoFrame ) || !( flags & KAknButtonPressedDownFrame ) )
            {
            flags |= KAknButtonNoFrame; 
            flags |= KAknButtonPressedDownFrame;
            button->RegisterResourceProvider( iResourceProvider );
            button->SetButtonFlags( flags ); 
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::ToolbarItemIndexById
// Returns the index of the toolbar item inside of the iItems or iVisibleItems 
// array.
// -----------------------------------------------------------------------------
//
TInt CAknToolbarExtensionView::ToolbarItemIndexById( TBool aVisibleItems, 
    const TInt aId ) const 
    {
    for ( TInt i = 0; i < aVisibleItems ? iVisibleItems.Count() : 
        iItems.Count(); i++ )
        {
        CAknToolbarItem* item = aVisibleItems ? iVisibleItems[i] : iItems[i];
        if ( item && item->CommandId() == aId )
            {
            return i;
            }
        }
    return KErrNotFound;
    }


// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::MoveHighlightL
// Moves highlight from one item to another. Does nothing if this is fixed 
// toolbar extension's view. 
// -----------------------------------------------------------------------------
//    
void CAknToolbarExtensionView::MoveHighlightL( TInt aDirection, TInt aIndex )
    {
    if ( IsNonFocusing() || !iVisibleItems.Count() )
        {
        iSelectedItem = KNoItemSelected;
        return; 
        }

    TInt oldFocused = iSelectedItem; 
    if ( iSelectedItem == KNoItemSelected )
        {
        iSelectedItem = 0; 
        }

    switch ( aDirection )
        {
        case EDirectionUp: 
            {
            iSelectedItem = NextFocusable( -iNumberOfColumns ); 
            break; 
            }

        case EDirectionDown: 
            {
            iSelectedItem = NextFocusable( iNumberOfColumns ); 
            break;             
            }
        case EDirectionRight: 
            {
            iSelectedItem = NextFocusable( 1 ); 
            break; 
            }

        case EDirectionLeft: 
            {
            iSelectedItem = NextFocusable( -1 ); 
            break;             
            }
        case ENoDirection: 
            {
            iSelectedItem = aIndex; 
            break; 
            }
        }

    CAknToolbarItem* item = NULL;

    if ( iSelectedItem != KNoItemSelected )  
        {
        item = iVisibleItems[iSelectedItem];

        // set this item focused
        item->SetFocusL( ETrue, EFalse, ENoDrawNow, this );
        DrawNow( item->HighlightRect() ); 
        }
    item = NULL; 

    if ( oldFocused != KNoItemSelected && oldFocused != aIndex )
        {
        item = iVisibleItems[oldFocused];
        if ( item && item->Control() )
            {
            SelectItemL( oldFocused, EFalse );

            // take the focus away
            item->SetFocusL( EFalse, EFalse, EDrawNow, this );
            DrawNow( item->HighlightRect() ); 
            }
        }
    }



// -----------------------------------------------------------------------------
// CAknToolbarExtensionView::NextFocusable
// Calculates next focusable item. Used with floating toolbar extension. 
// -----------------------------------------------------------------------------
//
TInt CAknToolbarExtensionView::NextFocusable( TInt aStep )
    {
    TInt index = iSelectedItem; 
    TInt startIndex = iSelectedItem; 

    CAknButton* button = NULL;  
    // we will do it till we don't get valid non-dimmed item or till we don't
    // make the whole round ( all items are dimmed )
    do 
        {
        button = NULL; 
        if ( aStep == 1 && index >= iVisibleItems.Count() - 1 )
            {
            index = 0;
            }
        else if ( aStep == -1 && index == 0 )
            {
            index = iVisibleItems.Count() - 1;
            }
        else if ( aStep > 1 )
            {
            if ( index + aStep >= iVisibleItems.Count() )
                {
                index = ( index + 1 ) % aStep; 
                }
            else 
                {
                index += aStep; 
                }
            }
        else if ( aStep < -1 )
            {
            if ( index + aStep < 0 ) 
                {
                TInt modResult = index - 1;  
                index = iVisibleItems.Count() - 1 ; 
                if ( modResult < 0 )
                    {
                    modResult = iNumberOfColumns - 1; 
                    }
                while ( index % ( +aStep ) != modResult )
                    {
                    index--; 
                    }
                }
            else 
                {
                index += aStep; 
                }
            }
        else             
            {
            index += aStep; 
            }
        button = static_cast<CAknButton*>( iVisibleItems[index]->Control() );

        } while ( ( !button || button->IsDimmed() ) && startIndex != index );

    return index; 
    }


// -----------------------------------------------------------------------------
// Sets item dimmed
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::SetItemDimmed( TInt aCommandId, TBool aDimmed )
    {
    CCoeControl* control = ControlOrNull( aCommandId );     
    if ( control ) 
        {
        control->SetDimmed( aDimmed ); 
        if ( IsVisible() )
            {
            control->DrawNow(); 
            }
        }
    }

// -----------------------------------------------------------------------------
// Hides an item
// -----------------------------------------------------------------------------
//
void CAknToolbarExtensionView::HideItemL( TInt aCommandId, TBool aHide )
    {
    CAknToolbarItem* item = NULL; 
    for ( TInt i=0; i < iItems.Count(); i++ )
        {
        if ( aCommandId == iItems[i]->CommandId() )
            {
            item = iItems[i]; 
            break; 
            }
        }

    if ( item && item->Control() && item->IsHidden() != aHide ) 
        {
        item->SetHidden( aHide ); 
        }
    }
