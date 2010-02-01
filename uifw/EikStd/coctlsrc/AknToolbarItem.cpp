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
* Description:  Toolbar item 
*
*/


#include <AknsUtils.h>
#include <barsread.h>
#include <aknbutton.h>
#include <e32std.h>
#include <e32property.h>
#include <avkondomainpskeys.h>


#include "akntoolbaritem.h"
#include "touchtoolbardata.h"


// -----------------------------------------------------------------------------
// CAknToolbarItem::CAknToolbarItem
// Default constructor
// -----------------------------------------------------------------------------
//
CAknToolbarItem::CAknToolbarItem()
    {
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::CAknToolbarItem
// Constructor
// -----------------------------------------------------------------------------
//
CAknToolbarItem::CAknToolbarItem( CCoeControl* aControl, TInt aType, 
                                  TInt aId, TInt aFlags ) 
    : iControl( aControl ), iControlType( aType ), 
      iCommandId( aId ), iFlags( aFlags )
    {
    SetKeyRefuse();
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknToolbarItem::~CAknToolbarItem()
    {
    AknsUtils::DeregisterControlPosition( iControl );
    delete iControl;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::ConstructFromResourceL
// Constructs one item from resource file
// -----------------------------------------------------------------------------
//
void CAknToolbarItem::ConstructFromResourceL( TResourceReader& aReader )
    {
    iControlType = aReader.ReadInt16();
    iCommandId = aReader.ReadInt16();
    iFlags = aReader.ReadInt16();
    aReader.ReadInt16(); // length, not used
    
    iControl = EikControlFactory::CreateByTypeL( iControlType ).iControl;

    if ( iControl )
        {
        iControl->ConstructFromResourceL( aReader );
        }
        
    SetKeyRefuse();
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::Control
// -----------------------------------------------------------------------------
//
CCoeControl* CAknToolbarItem::Control() const
    {
    return iControl;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::ControlType
// -----------------------------------------------------------------------------
//    
TInt CAknToolbarItem::ControlType() const
    {
    return iControlType;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::CommandId
// -----------------------------------------------------------------------------
//    
TInt CAknToolbarItem::CommandId() const
    {
    return iCommandId;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::Flags
// -----------------------------------------------------------------------------
//    
TInt CAknToolbarItem::Flags() const
    {
    return iFlags;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::IsSelected
// -----------------------------------------------------------------------------
//    
TBool CAknToolbarItem::IsSelected() const
    {
    return iIsSelected;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::SetIsSelectedL
// -----------------------------------------------------------------------------
//
TBool CAknToolbarItem::SetIsSelectedL( TBool aIsSelected )
    {
    // Toolbar items containing buttons are not set to selected state
    if ( Control() && ( ControlType() == EAknCtButton || 
         ControlType() == EAknCtToolbarExtension ) )
        {
        return EFalse;
        }

    iIsSelected = aIsSelected;

    // Set item focused, when selected
    Control()->SetFocus( aIsSelected );
    if ( aIsSelected )
        {
        CEikonEnv::Static()->EikAppUi()->AddToStackL( Control(), ECoeStackPriorityDefault,
            0 );
        }
    else
        {
        CEikonEnv::Static()->EikAppUi()->RemoveFromStack( Control() );
        }

    return ETrue;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::SetCloseOnCommand
// -----------------------------------------------------------------------------
//
void CAknToolbarItem::SetCloseOnCommand( const TBool aCloseOnCommand )
    {
    if ( Control() && ( ControlType() == EAknCtButton || 
        ControlType() == EAknCtToolbarExtension ) )
        {
        static_cast<CAknButton*>( Control() )->SetRequestExit( aCloseOnCommand );
        }
    } //lint !e1762

// -----------------------------------------------------------------------------
// CAknToolbarItem::SetHighlightRect
// -----------------------------------------------------------------------------
//
void CAknToolbarItem::SetHighlightRect( const TRect& aRect )
    {
    iHighlightRect = aRect;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::HighlightRect
// -----------------------------------------------------------------------------
//
TRect CAknToolbarItem::HighlightRect() const
    {
    return iHighlightRect;
    }
    
// -----------------------------------------------------------------------------
// CAknToolbarItem::SetFocusL
// -----------------------------------------------------------------------------
//
void CAknToolbarItem::SetFocusL( TBool aFocus, TBool aPrepareControl,
                                 TDrawNow aDrawNow, const CCoeControl* aParent )
    {
    // Editor is set focused, when it is selected, not here.
    if ( iControl && ( iControlType == EAknCtButton ) )
        {
        if ( aPrepareControl )
            {
            if ( aFocus )
                {
                TInt state = 0;
                CTouchToolbarData* data =
                            (CTouchToolbarData*) CAknTransitionUtils::GetData(
                                                                (TInt) aParent );
                if ( data )
                    {
                    RProperty::Get( KPSUidAvkonDomain,
                                    KAknTfxServerRedirectionStatus,
                                    state );
                    data->SetFocusedItem( state ? iControl : NULL );
                    }
                if ( state == 0 )
                    {
                    iControl->PrepareForFocusGainL();
                    }
                }
            else
                {
                iControl->PrepareForFocusLossL();
                }
            }
            
        iControl->SetFocus( aFocus, aDrawNow );
        }
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::RegisterPosition
// -----------------------------------------------------------------------------
//
void CAknToolbarItem::RegisterPosition( const TPoint& aParentPosition ) const
    {
    AknsUtils::RegisterControlPosition( iControl, aParentPosition +
                                                  iControl->Position() );
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::IsHidden
// -----------------------------------------------------------------------------
//
TBool CAknToolbarItem::IsHidden() const
    {
    return iHidden;
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::SetHidden
// -----------------------------------------------------------------------------
//
void CAknToolbarItem::SetHidden( TBool aHidden )
    {
    iHidden = aHidden; 
    }

// -----------------------------------------------------------------------------
// CAknToolbarItem::RefusesKeys
// -----------------------------------------------------------------------------
//
TBool CAknToolbarItem::RefusesKeys() const
    {
    return iRefusesKeys;
    }
    
// -----------------------------------------------------------------------------
// CAknToolbarItem::RefusesKeys
// -----------------------------------------------------------------------------
//
void CAknToolbarItem::SetKeyRefuse()
    {
    switch ( iControlType )
        {
        case EEikCtEdwin: // fallback done on purpose
        case EEikCtRichTextEditor:
        case EEikCtSecretEd:
        case EEikCtFileNameEd:
        case EEikCtFolderNameEd:
        case EEikCtFlPtEd:
        case EEikCtFxPtEd:
        case EEikCtTwipsEd:
        case EEikCtNumberEditor:
        case EEikCtRangeEditor:
        case EEikCtTimeEditor:
        case EEikCtDateEditor:
        case EEikCtTimeAndDateEditor:
        case EEikCtDurationEditor:
        case EEikCtTimeOffsetEditor:
        case EEikCtGlobalTextEditor:
        case EAknCtIpFieldEditor:
        case EEikCtRangeRefEditor:
        case EEikCtTelephoneNumberEditor:
        case EAknCtLocationEditor:
        case EAknCtUnitEditor:
            iRefusesKeys = ETrue;
            break;
            
        default:
            iRefusesKeys = EFalse;
        }
    }
