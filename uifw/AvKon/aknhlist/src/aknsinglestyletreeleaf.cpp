/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for CAknSingleStyleTreeLeaf class.
*
*/


#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "aknsinglestyletreeleaf.h"
#include "akntree.h"
#include "akntreelistinternalconstants.h"

using AknTreeListIconID::KDefault;
using AknTreeListIconID::KNone;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeLeaf* CAknSingleStyleTreeLeaf::NewL( const TDesC& aText,
    TUint32 aFlags )
    {
    CAknSingleStyleTreeLeaf* self = CAknSingleStyleTreeLeaf::NewLC( aText,
        aFlags );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeLeaf* CAknSingleStyleTreeLeaf::NewLC( const TDesC& aText,
    TUint32 aFlags )
    {
    CAknSingleStyleTreeLeaf* self = 
        new ( ELeave ) CAknSingleStyleTreeLeaf( aFlags );
    CleanupStack::PushL( self );
    self->ConstructL( aText );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeLeaf::~CAknSingleStyleTreeLeaf()
    {
    delete iText;
    }


// ---------------------------------------------------------------------------
// Returns the text set for the leaf.
// ---------------------------------------------------------------------------
//
const TDesC& CAknSingleStyleTreeLeaf::Text() const
    {
    return iText ? *iText : KNullDesC();
    }


// ---------------------------------------------------------------------------
// Allocates new heap based descriptor for the text, and if the allocation
// succeeds, deletes the old descriptor and replaces it with the new.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeLeaf::SetTextL( const TDesC& aText, TBool aDrawNow  )
    {
    HBufC* tmp = aText.AllocL();
    delete iText;
    iText = tmp;

    if ( aDrawNow )
        {
        __ASSERT_DEBUG( Root(), User::Invariant() );
        Root()->ItemModified( this );
        }
    }


// ---------------------------------------------------------------------------
// Returns the icon ID set for the specified tree leaf icon type.
// ---------------------------------------------------------------------------
//
TInt CAknSingleStyleTreeLeaf::Icon( TIconType aType ) const
    {
    TInt iconId = KDefault;
    switch ( aType )
        {
        case EIcon:
            iconId = iIcon;
            break;

        case EOptIcon1:
            iconId = iOptIcon1;
            break;

        case EOptIcon2:
            iconId = iOptIcon2;
            break;

        case EHighlightedIcon:
            iconId = iHighlightedIcon;
            break;

        case EHighlightedOptIcon1:
            iconId = iHighlightedOptIcon1;
            break;

        case EHighlightedOptIcon2:
            iconId = iHighlightedOptIcon2;
            break;

        default:
            break;
        }
    return iconId;
    }


// ---------------------------------------------------------------------------
//  Sets the icon ID for specified tree leaf icon type.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeLeaf::SetIcon( TIconType aType, TInt aIconId,
    TBool aDrawNow )
    {
    switch( aType )
        {
        case EIcon:
            iIcon = aIconId;
            break;
        
        case EOptIcon1:
            iOptIcon1 = aIconId;
            break;

        case EOptIcon2:
            iOptIcon2 = aIconId;
            break;

        case EHighlightedIcon:
            iHighlightedIcon = aIconId;
            break;

        case EHighlightedOptIcon1:
            iHighlightedOptIcon1 = aIconId;
            break;

        case EHighlightedOptIcon2:
            iHighlightedOptIcon2 = aIconId;
            break;

        default:
            __ASSERT_DEBUG( EFalse, User::Invariant() );
            break;
        }

    if ( aDrawNow )
        {
        __ASSERT_DEBUG( Root(), User::Invariant() );
        Root()->ItemModified( this );
        }
    }


// ---------------------------------------------------------------------------
// Icon ID.
// ---------------------------------------------------------------------------
//
TInt CAknSingleStyleTreeLeaf::IconId( TBool aFocused ) const
    {
    // Default ID for icon.
    TInt iconId = CAknTree::EDefaultFileIndication;

    // Determine ID for the icon based on focusing and set IDs.
    if ( aFocused && iHighlightedIcon != KDefault )
        {
        iconId = iHighlightedIcon;
        }
    else if ( iIcon != KDefault )
        {
        iconId = iIcon;
        }

    return iconId;
    }


// ---------------------------------------------------------------------------
// Optional icon ID.
// ---------------------------------------------------------------------------
//
TInt CAknSingleStyleTreeLeaf::OptionalIconId( TInt aIndex,
    TBool aFocused ) const
    {
    __ASSERT_DEBUG( aIndex == 0 || aIndex == 1, User::Invariant() );

    // Default ID for optional icon.
    TInt optIconId = AknTreeListIconID::KNone; 

    // Determine ID for specified optional icon.
    if ( aIndex == 0 )
        {
        if ( aFocused && iHighlightedOptIcon1 != KDefault )
            {
            optIconId = iHighlightedOptIcon1;
            }
        else if ( iOptIcon1 != KDefault )
            {
            optIconId = iOptIcon1;
            }
        }
    else if ( aIndex == 1 )
        {
        if ( aFocused && iHighlightedOptIcon2 != KDefault )
            {
            optIconId = iHighlightedOptIcon2;
            }
        else if ( iOptIcon2 != KDefault )
            {
            optIconId = iOptIcon2;
            }
        }

    return optIconId;
    }


// ---------------------------------------------------------------------------
// Text variety depending on optional icons.
// ---------------------------------------------------------------------------
//
TInt CAknSingleStyleTreeLeaf::TextVariety( TInt aOptIconId1,
    TInt aOptIconId2 ) const
    {
    TInt textVariety = 0;
    if ( aOptIconId1 != AknTreeListIconID::KNone )
        {
        textVariety = 1;
        }
    if ( aOptIconId2 != AknTreeListIconID::KNone )
        {
        textVariety = 2;
        }
    return textVariety;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Returns the type of concrete item class.
// ---------------------------------------------------------------------------
//
TInt CAknSingleStyleTreeLeaf::Type() const
    {
    return AknTreeList::KSingleStyleTreeLeaf;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Draws the tree leaf to appointed graphics context.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeLeaf::Draw( CWindowGc& aGc, const TRect& aItemRect,
    const TRect& /*aRect*/, TBool aFocused ) const
    {
    CAknTree* root = Root();
    __ASSERT_DEBUG( root, User::Invariant() );

    // Icon.
    TInt iconVariety = 0; // Arbitrarily selected variety.
    TRect iconRect = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_graphic_hl_pane_g2( iconVariety ) );

    TInt iconId = IconId( aFocused );
    // Dragging/flicking
    
    if ( iIcon != AknTreeListIconID::KNone )
        {
        root->DrawIcon( iconId, iconRect.Size(), aGc, iconRect.iTl,
            iconRect.Size() );
        }

    // Optional icon IDs.
    TInt optIconId1 = OptionalIconId( 0, aFocused );
    TInt optIconId2 = OptionalIconId( 1, aFocused );

    // Text variety is set according to required optional icons.
    TInt textVariety = TextVariety( optIconId1, optIconId2 );

    // Text.
    TAknLayoutText layoutText;
    layoutText.LayoutText( aItemRect, AknLayoutScalable_Avkon::
        list_single_graphic_hl_pane_t1( textVariety ).LayoutLine() );

    root->DrawText( aGc, aItemRect, AknLayoutScalable_Avkon::
        list_single_graphic_hl_pane_t1( textVariety ), *iText, NULL, this,
        aFocused, ETrue );

    // Optional item state indication icon.
    TInt optIconVariety1 = 1;
    TRect optIconRect1 = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_graphic_hl_pane_g4( optIconVariety1 ) );

    if ( optIconId1 != KNone )
        {
        root->DrawIcon( optIconId1, optIconRect1.Size(), aGc,
            optIconRect1.iTl, optIconRect1.Size() );
        }

    // Another optional item state indication icon.
    TInt optIconVariety2 = 1;
    TRect optIconRect2 = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_graphic_hl_pane_g5( optIconVariety2 ) );

    if ( optIconId2 != KNone )
        {
        root->DrawIcon( optIconId2, optIconRect2.Size(), aGc,
            optIconRect2.iTl, optIconRect2.Size() );
        }    
    }   


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Handles pointer events.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeLeaf::HandlePointerEventL(
    const TPointerEvent& /*aPointerEvent*/, const TRect& /*aItemRect*/ )
    {
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeLeaf::CAknSingleStyleTreeLeaf( TUint32 aFlags )
    : CAknTreeLeaf( aFlags ),
    iIcon( KDefault ),
    iOptIcon1( KDefault ),
    iOptIcon2( KDefault ),
    iHighlightedIcon( KDefault ),
    iHighlightedOptIcon1( KDefault ),
    iHighlightedOptIcon2( KDefault )
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeLeaf::ConstructL( const TDesC& aText )
    {
    iText = aText.AllocL();
    }

