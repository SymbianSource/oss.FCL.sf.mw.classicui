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
* Description:  Toolbar extension component
*
*/


#include <barsread.h>
#include <akntoolbarextension.h>
#include <avkon.mbg>
#include <aknconsts.h>
#include <akntoolbar.h>

#include "akntoolbarextensionview.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// Constructs an extension with graphics
// ---------------------------------------------------------------------------
//
CAknToolbarExtension* CAknToolbarExtension::NewL()
    {
    CAknToolbarExtension* self = new (ELeave) CAknToolbarExtension();
    CleanupStack::PushL( self );
    self->BaseConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// Constructs an extension with graphics
// ---------------------------------------------------------------------------
//
EXPORT_C CAknToolbarExtension* CAknToolbarExtension::NewL( const TInt aResourceId )
    {
    CAknToolbarExtension* self = NewLC( aResourceId );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Two-phased constructor.
// Constructs an extension with graphics
// ---------------------------------------------------------------------------
//
EXPORT_C CAknToolbarExtension* CAknToolbarExtension::NewLC( const TInt aResourceId )
    {
    CAknToolbarExtension* self = new (ELeave) CAknToolbarExtension();
    CleanupStack::PushL( self );
    self->BaseConstructL();
    self->ConstructFromResourceL( aResourceId ); 
    return self;
    }

   
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknToolbarExtension::~CAknToolbarExtension()
    {
    delete iView;
    if ( iIdle && iIdle->IsActive() )
        {
        iIdle->Cancel(); 
        }
    delete iIdle; 
    }
    
// ---------------------------------------------------------------------------
// From class CAknButton.
// Constructs the toolbar extension and creates the extension view
// ---------------------------------------------------------------------------
//
void CAknToolbarExtension::ConstructFromResourceL( TResourceReader& aReader )
    {
    TInt version = aReader.ReadInt8();     // version
    iFlags = aReader.ReadInt32();    // flags

    if ( iFlags & KAknTbExtensionButtonNoFrame )
        {
        SetButtonFlags( KAknButtonNoFrame ); 
        }

    if ( version > 0 )
        {
        TPtrC txt = aReader.ReadTPtrC();
        CAknButtonState* state = State( 0 );
        
        if ( state )
            {
            state->SetHelpTextL( txt );
            }
        state = State( 1 );
        if ( state )
            {
            state->SetHelpTextL( txt );
            }

        if ( version >= 2 )
            {
            // bmpfile
            TPtrC bmpFile = aReader.ReadTPtrC();

            // bmpid & bmpmask
            TInt bmpId = aReader.ReadInt16();
            TInt maskId = aReader.ReadInt16();

            TAknsItemID id;     
            TInt major = aReader.ReadInt32();
            TInt minor = aReader.ReadInt32();
            if ( major != 0 && minor != 0 )
                {
                id.Set( major, minor ); 
                }
            else if ( bmpFile == KNullDesC || ( bmpId == -1 && maskId == -1 ) )                    
                {
                // To be sure that there will be at least some icon
                id.Set( KAknsIIDQgnIndiTbExtension );
                }

            // dimmed bitmaps
            TInt dimmedBmpId = aReader.ReadInt16();
            TInt dimmedMaskId = aReader.ReadInt16();

            major = aReader.ReadInt32();
            minor = aReader.ReadInt32();

            TAknsItemID dimmedId;     
            if ( major != 0 && minor != 0 )
                {
                dimmedId.Set( major, minor ); 
                }

            // pressed bitmaps
            TInt pressedBmpId = aReader.ReadInt16();
            TInt pressedMaskId = aReader.ReadInt16();

            TAknsItemID pressedId;     
            major = aReader.ReadInt32();
            minor = aReader.ReadInt32();

            if ( major != 0 && minor != 0 )
                {
                pressedId.Set( major, minor ); 
                }

            TBool useNormalIcon = ETrue; // Use normal icon with state 1, if pressed icon does not exist.
            if ( ( bmpFile != KNullDesC && ( pressedBmpId != -1 && pressedMaskId != -1 ) ) 
                || ( major != 0 && minor != 0 ) )  
                {
                useNormalIcon = EFalse; 
                }

            // hover bitmaps
            TInt hoverBmpId = aReader.ReadInt16();
            TInt hoverMaskId = aReader.ReadInt16();

            TAknsItemID hoverId;     
            major = aReader.ReadInt32();
            minor = aReader.ReadInt32();

            if ( major != 0 && minor != 0 )
                {
                hoverId.Set( major, minor ); 
                }

            if ( state )
                {
                state->UpdateIconL( bmpFile, useNormalIcon ? bmpId : pressedBmpId, 
                    useNormalIcon ? maskId : pressedMaskId, dimmedBmpId, dimmedMaskId, 
                    pressedBmpId, pressedMaskId, hoverBmpId, hoverMaskId, 
                    useNormalIcon ? id : pressedId, dimmedId, pressedId, hoverId ); 
                }
            state = State( 0 ); 
            if ( state )
                {
                state->UpdateIconL( bmpFile, bmpId, maskId, dimmedBmpId, dimmedMaskId, 
                    pressedBmpId, pressedMaskId, hoverBmpId, hoverMaskId, id, dimmedId,
                    pressedId, hoverId ); 
                }
            }
        }
       

    // construct view from resource, items are standard TBAR_CTRL structures
    iView = CAknToolbarExtensionView::NewL( aReader, this );

    aReader.ReadInt32();    // extension
    }
    
// ---------------------------------------------------------------------------
// From class CCoeControl.
// Handles key events
// ---------------------------------------------------------------------------
//
TKeyResponse CAknToolbarExtension::OfferKeyEventL( const TKeyEvent& aKeyEvent, 
    TEventCode aType )
    {
    if ( CAknButton::OfferKeyEventL( aKeyEvent, aType ) == EKeyWasNotConsumed )
        {
        return iView->OfferKeyEventL( aKeyEvent, aType );
        }
        
    return EKeyWasConsumed;
    }
    
// ---------------------------------------------------------------------------
// From class CCoeControl.
// Handles resource changes
// ---------------------------------------------------------------------------
//
void CAknToolbarExtension::HandleResourceChange( TInt aType )
    {
    CAknButton::HandleResourceChange( aType ); 
    iView->HandleResourceChange( aType ); 
    }

// ---------------------------------------------------------------------------
// From class CCoeControl.
// Makes extension visible
// ---------------------------------------------------------------------------
//
void CAknToolbarExtension::MakeVisible( TBool aVisible )
    {
    CAknButton::MakeVisible( aVisible ); 
    // When the view is changing the extension is hidden and then shown again 
    // when coming back to view. If extension button stays pressed down, the 
    // extension view should also be shown again. Showing the extension view
    // via idle so that it is shown on top. Otherwise applications container
    // is drawn after extension view, and because they have the same ordinal 
    // position and priority, only container would be shown.  
    if ( StateIndex() == 1 && aVisible )
        {
        ShowViewViaIdle();
        }
    else if ( !aVisible )
        {
        if ( iIdle && iIdle->IsActive() )
            {
            iIdle->Cancel(); 
            }
        iView->MakeVisible( aVisible ); 
        }
    }


// ---------------------------------------------------------------------------
// From class MCoeControlObserver.
// Handles events from itself and from extension view. 
// ---------------------------------------------------------------------------
//
void CAknToolbarExtension::HandleControlEventL( CCoeControl* aControl, 
    TCoeEvent aEventType )
    {
    switch ( aEventType )
        {
        case MCoeControlObserver::EEventRequestExit:
            {
            SetShown( EFalse ); // close view
            break;
            }
        case MCoeControlObserver::EEventStateChanged: 
            {
            if ( !iToolbar )
                {
                iToolbar = static_cast<CAknToolbar*>( Parent() ); 
                }
            if ( aControl == this )
                {
                if ( StateIndex() == 0 )
                    {
                    iView->MakeVisible( EFalse ); // close view
                    }
                else
                    {
                    TBool nonFocusing = iToolbar->IsNonFocusing(); 
                    iView->SetFocusing( !nonFocusing ); 
                    if ( IsVisible() )
                        {
                        iToolbar->DynInitExtensionL( this );
                        iView->MakeVisible( ETrue ); // show view
                        }
                    }
                }
            else
                {
                TInt commandId = iView->CommandIdByControl( aControl ); 
                iToolbar->ExtensionEventL( commandId ); 
                }
            break;     
            }
        default: 
            {
            break; 
            }
        }
    }


// ---------------------------------------------------------------------------
// Gets extension position so that extension view knows where to draw
// ifself 
// ---------------------------------------------------------------------------
//
TInt CAknToolbarExtension::ExtensionPosition( )
    {
    if ( !iToolbar )
        {
        iToolbar = static_cast<CAknToolbar*>(Parent()); 
        }
    return iToolbar->ToolbarVisibleIndexByControl( this ); 
    }


// ---------------------------------------------------------------------------
// Shows view via idle. This is needed when the extension is in pressed down
// state when coming back to view. 
// ---------------------------------------------------------------------------
//
void CAknToolbarExtension::ShowViewViaIdle()
    {
    if ( !iIdle )
        {
        TRAPD( err, iIdle = CIdle::NewL( CActive::EPriorityIdle ) );
        if ( err != KErrNone)
            {
            return; 
            }
        }
    if ( iIdle->IsActive() )
        {
        iIdle->Cancel();
        }
    iIdle->Start( TCallBack ( ShowView, this ) );
    }

// ---------------------------------------------------------------------------
// Shows view when called by idle.  
// ---------------------------------------------------------------------------
//
TInt CAknToolbarExtension::ShowView( TAny* aThis )
    {
    CAknToolbarExtension* extension = static_cast<CAknToolbarExtension*>(aThis);
    extension->iView->MakeVisible( ETrue );     
    return KErrNone; 
    }

// ---------------------------------------------------------------------------
// View uses this method to inform that it has closed ( a tap outside the
// view ) and then extension should change state, so that it does not look
// pressed down. 
// ---------------------------------------------------------------------------
//
void CAknToolbarExtension::ViewClosed( )
    {
    ChangeState( ETrue ); 
    }

// ---------------------------------------------------------------------------
// Returns a pointer to the specified control.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknToolbarExtension::ControlOrNull( TInt aCommandId ) const
    {
    return iView->ControlOrNull( aCommandId ); 
    }


// ---------------------------------------------------------------------------
// Adds new item to extension view
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknToolbarExtension::AddItemL( CCoeControl* aItem,
                                              TInt aType,
                                              TInt aCommandId,
                                              TInt aFlags,
                                              TInt aIndex )
    {
    if ( iView->IsVisible() )
        {
        User::Leave( KErrNotSupported ); 
        }
    iView->AddItemL( aItem, aType, aCommandId, aFlags, aIndex ); 
    }


// ---------------------------------------------------------------------------
// Removes an item from extension view
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknToolbarExtension::RemoveItemL( TInt aCommandId )
    {
    if ( iView->IsVisible() )
        {
        User::Leave( KErrNotSupported ); 
        }
    iView->RemoveItemL( aCommandId ); 
    }


// ---------------------------------------------------------------------------
// Return boolean indicating if extension view is shown. 
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknToolbarExtension::IsShown() const
    {
    if ( iView->IsVisible() )
        {
        return ETrue; 
        }
    return EFalse; 
    }

// ---------------------------------------------------------------------------
// Sets extension view shown or hides it. 
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknToolbarExtension::SetShown( TBool aShown )
    {
    if ( iView->IsVisible() != aShown )
        {
        iView->MakeVisible( aShown ); 
        ChangeState( ETrue ); 
        }
    }


// ---------------------------------------------------------------------------
// Getter for extension flags
// ---------------------------------------------------------------------------
//
TInt CAknToolbarExtension::ExtensionFlags()
    {
    return iFlags;     
    }

// ---------------------------------------------------------------------------
// Default constructor
// ---------------------------------------------------------------------------
//
CAknToolbarExtension::CAknToolbarExtension() : CAknButton( 0 ), iFlags(0)
    {
    }

// ---------------------------------------------------------------------------
// Contructs the button
// ---------------------------------------------------------------------------
//
void CAknToolbarExtension::BaseConstructL()
    {
    SetObserver( this );
    
    CAknButton::ConstructL( KAvkonBitmapFile, 
        -1, 
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        KNullDesC,
        KNullDesC,
        0, 
        KAknsIIDQgnIndiTbExtension
        ); // replace with parametrized version to load graphics etc

    
    AddStateL( KAvkonBitmapFile, 
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        KNullDesC,
        KNullDesC,
        KAknButtonStateHasLatchedFrame, 
        KAknsIIDQgnIndiTbExtension, 
        KAknsIIDDefault, 
        KAknsIIDDefault,
        KAknsIIDDefault ); // add a second state with latched down graphics
 
    } 

// -----------------------------------------------------------------------------
// Constructs controls from a resource file.
// -----------------------------------------------------------------------------
//
void CAknToolbarExtension::ConstructFromResourceL( const TInt aResourceId ) 
    {    
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
    ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    }


// -----------------------------------------------------------------------------
// Returns extension view. Needed by toolbar when dimming the background. 
// We don't want toolbar to be dimmed too. 
// -----------------------------------------------------------------------------
//
CCoeControl* CAknToolbarExtension::ExtensionView() 
    {    
    return iView; 
    }

// -----------------------------------------------------------------------------
// Dims or undims a toolbar item in extension. 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbarExtension::SetItemDimmed( TInt aCommandId, TBool aDimmed )
    {
    iView->SetItemDimmed( aCommandId, aDimmed );
    }

// -----------------------------------------------------------------------------
// Hides or unhides a toolbar item in extension. 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknToolbarExtension::HideItemL( TInt aCommandId, TBool aHide )
    {
    if ( iView->IsVisible() )
        {
        User::Leave( KErrNotSupported ); 
        }
    iView->HideItemL( aCommandId, aHide );
    }
