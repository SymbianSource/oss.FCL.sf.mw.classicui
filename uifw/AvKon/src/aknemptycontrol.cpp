/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for an empty control, which only draws the
*                background, to be used on empty areas of status pane.
*
*/


// INCLUDE FILES
#include <bacntf.h>
#include <eikspane.h>
#include <aknconsts.h>
#include <AknsDrawUtils.h>
#include <AknsUtils.h>
#include <AknUtils.h>
#include <aknnavi.h>
#include <aknnavide.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknTasHook.h>

#include "aknemptycontrol.h"
#include "AknStatuspaneUtils.h"


// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CAknEmptyControl::CAknEmptyControl
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CAknEmptyControl::CAknEmptyControl()
	{
	AKNTASHOOK_ADD( this, "CAknEmptyControl" );
    iIsActiveIdle = AknStatuspaneUtils::IsActiveIdle();
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknEmptyControl::~CAknEmptyControl()
	{
	AKNTASHOOK_REMOVE();
	AknsUtils::DeregisterControlPosition( this );
    }


// ---------------------------------------------------------------------------
// CAknEmptyControl::ConstructFromResourceL
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknEmptyControl::ConstructFromResourceL( TResourceReader& /*aReader*/ )
    {
    MakeVisible( ETrue );
  	}


// ---------------------------------------------------------------------------
// CAknEmptyControl::HandlePointerEventL
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknEmptyControl::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    if ( !PassPointerEventToAdjacentControlL( aPointerEvent ) )
        {
        CAknControl::HandlePointerEventL( aPointerEvent );
        }
    }


// ---------------------------------------------------------------------------
// CAknEmptyControl::SizeChanged
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknEmptyControl::SizeChanged()
    {
    // No fading if staconpane is active.
    Window().SetNonFading( AknStatuspaneUtils::StaconPaneActive() );

    AknsUtils::RegisterControlPosition( this );
    DrawableWindow()->SetOrdinalPosition( -1 ); // Send to back
    }


// ---------------------------------------------------------------------------
// CAknEmptyControl::Draw
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknEmptyControl::Draw( const TRect& /*aRect*/ ) const
    {
    if ( iIsActiveIdle )
        {
        return;
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    CWindowGc& gc = SystemGc();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    TRect rect( Rect() );
    AknsDrawUtils::Background( skin, cc, this, gc, rect );
    }


// ---------------------------------------------------------------------------
// CAknEmptyControl::PassPointerEventToAdjacentControlL
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
TBool CAknEmptyControl::PassPointerEventToAdjacentControlL(
    const TPointerEvent& aPointerEvent )
    {
    TBool pointerEventPassedOn( EFalse );

    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    if ( statusPane )
        {
        TInt currentLayoutResId( statusPane->CurrentLayoutResId() );

        switch ( currentLayoutResId )
            {
            case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL:
            case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE:
                {
                TRect statusPaneRect;
                AknLayoutUtils::LayoutMetricsRect(
                    AknLayoutUtils::EStatusPane, statusPaneRect );

                // Check if the pointer event happened in the navi
                // pane touch responsive area.
                TAknLayoutRect layoutRect;
                layoutRect.LayoutRect(
                    statusPaneRect,
                    AknLayoutScalable_Avkon::aid_touch_navi_pane() );
                TRect naviPaneTouchRect( layoutRect.Rect() );

                if ( naviPaneTouchRect.Contains( aPointerEvent.iPosition ) )
                    {
                    CAknNavigationControlContainer* naviPane =
                    static_cast<CAknNavigationControlContainer*>(
                        statusPane->ControlL(
                            TUid::Uid( EEikStatusPaneUidNavi ) ) );
                    if ( naviPane )
                        {
                        // Pass the event directly to the decorator
                        // because navi pane doesn't handle the events.
                        CAknNavigationDecorator* naviPaneControl =
                            static_cast<CAknNavigationDecorator*>(
                                naviPane->Top() );

                        if ( naviPaneControl )
                            {
                            // The position of the pointer event position
                            // needs to be modified so that it's relative
                            // to the navi pane area.
                            TRect naviPaneRect( naviPaneControl->Rect() );

                            TPointerEvent naviPaneRelativePointerEvent(
                                aPointerEvent );

                            naviPaneRelativePointerEvent.iPosition.iX =
                                naviPaneRelativePointerEvent.iPosition.iX -
                                    naviPaneTouchRect.iTl.iX -
                                    Rect().iTl.iX;

                            naviPaneRelativePointerEvent.iPosition.iY -=
                                ( naviPaneTouchRect.iBr.iY -
                                  naviPaneRect.Height() );

                            // Pass the modified event to the navi decorator.
                            naviPaneControl->HandlePointerEventL(
                                naviPaneRelativePointerEvent );
                            pointerEventPassedOn = ETrue;
                            }
                        }
                    }
                break;
                }
            default:
                {
                break;
                }
            }
        }

    return pointerEventPassedOn;
    }

// -----------------------------------------------------------------------------
// CAknEmptyControl::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CAknEmptyControl::HandleResourceChange( TInt aType ) 
    {
    CCoeControl::HandleResourceChange( aType );
    
    if ( aType == KEikDynamicLayoutVariantSwitch ||
         aType == KAknsMessageSkinChange )
        {      
        DrawDeferred();
        }
    }
//  End of File
