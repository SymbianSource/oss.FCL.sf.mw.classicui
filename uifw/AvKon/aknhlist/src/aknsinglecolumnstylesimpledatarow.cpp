/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for CAknSingleColumnStyleSimpleDataRow class.
*
*/


#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "akntree.h"
#include "aknsinglecolumnstylesimpledatarow.h"
#include "akntreelistinternalconstants.h"

using AknTreeListIconID::KDefault;
using AknTreeListIconID::KNone;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleSimpleDataRow* CAknSingleColumnStyleSimpleDataRow::NewLC(
    const TDesC& aText, TUint32 aFlags )
    {
    CAknSingleColumnStyleSimpleDataRow* self = 
        new ( ELeave ) CAknSingleColumnStyleSimpleDataRow( aFlags );
    CleanupStack::PushL( self );
    self->ConstructL( aText );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleSimpleDataRow::~CAknSingleColumnStyleSimpleDataRow()
    {
    delete iText;
    }


// ---------------------------------------------------------------------------
// Returns the text set for the simple data row.
// ---------------------------------------------------------------------------
//
const TDesC& CAknSingleColumnStyleSimpleDataRow::Text() const
    {
    return iText ? *iText : KNullDesC();
    }


// ---------------------------------------------------------------------------
// Allocates new heap based descriptor for the text, and if the allocation
// succeeds, deletes the old descriptor and replaces it with the new.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSimpleDataRow::SetTextL( const TDesC& aText,
    TBool aDrawNow  )
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
// Returns the icon ID set for the specified simple data row icon type.
// ---------------------------------------------------------------------------
//
TInt CAknSingleColumnStyleSimpleDataRow::Icon( TIconType aType ) const
    {
    TInt iconId = KDefault;
    switch ( aType )
        {
        case EIcon:
            iconId = iIcon;
            break;

        case EOptIcon:
            iconId = iOptIcon;
            break;

        case EHighlightedIcon:
            iconId = iHighlightedIcon;
            break;

        case EHighlightedOptIcon:
            iconId = iHighlightedOptIcon;
            break;

        default:
            break;
        }
    return iconId;
    }


// ---------------------------------------------------------------------------
//  Sets the icon ID for specified simple row icon type.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSimpleDataRow::SetIcon( TIconType aType,
    TInt aIconId, TBool aDrawNow )
    {
    switch( aType )
        {
        case EIcon:
            iIcon = aIconId;
            break;
        
        case EOptIcon:
            iOptIcon = aIconId;
            break;

        case EHighlightedIcon:
            iHighlightedIcon = aIconId;
            break;

        case EHighlightedOptIcon:
            iHighlightedOptIcon = aIconId;
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
TInt CAknSingleColumnStyleSimpleDataRow::IconId( TBool aFocused ) const
    {
    // Default ID for icon.
    TInt iconId = KNone;

    // Determines ID for the icon based on focusing and set IDs.
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
TInt CAknSingleColumnStyleSimpleDataRow::OptionalIconId( TBool aFocused ) const
    {
    // Default ID for optional icon.
    TInt iconId = KNone;

    // Determines ID for the optional icon based on focusing, item marking,
    // and set optional icon IDs.
    if ( IsMarked() )
        {
        iconId = aFocused ? AknTreeListIconID::KHighlightedMarkedIndication :
            AknTreeListIconID::KMarkedIndication;
        }
    else if ( aFocused && iHighlightedOptIcon != KDefault )
        {
        iconId = iHighlightedOptIcon;
        }
    else if ( iOptIcon != KDefault )
        {
        iconId = iOptIcon;
        }

    return iconId;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Returns the type of concrete item class.
// ---------------------------------------------------------------------------
//
TInt CAknSingleColumnStyleSimpleDataRow::Type() const
    {
    return AknTreeList::KSingleColumnStyleSimpleDataRow;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Draws the simple data row to the appointed graphics context.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSimpleDataRow::Draw( CWindowGc& aGc,
    const TRect& aItemRect, const TRect& /*aRect*/, TBool aFocused ) const
    {
    CAknTree* root = Root();
    __ASSERT_DEBUG( root, User::Invariant() );

    // Icon.
    TInt iconVariety = IsMarked() ? 1 : 0;
    TRect iconRect = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_g1( iconVariety ) );

    TInt iconId = IconId( aFocused );
    if ( iIcon != AknTreeListIconID::KNone )
        {
        root->DrawIcon( iconId, iconRect.Size(), aGc, iconRect.iTl,
            iconRect.Size() );
        }    

    // Optional icon ID.
    TInt optIconId = OptionalIconId( aFocused );

    // Text.
    TAknLayoutText layoutText;
    TInt textVariety = ( optIconId == KNone ) ? 0 : 1;
    layoutText.LayoutText( aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_t1( textVariety ).LayoutLine() );
    root->DrawText( aGc, aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_t1( textVariety ), *iText, NULL,
        this, aFocused, ETrue );    
    
    // Optional indication icon.
    TInt optIconVariety = 0; // Marked folder.
    TRect optIconRect = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_g2( optIconVariety ) );
    if ( optIconId != KNone )
        {
        root->DrawIcon( optIconId, optIconRect.Size(), aGc,
            optIconRect.iTl, optIconRect.Size() );
        }    
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Handles pointer events.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSimpleDataRow::HandlePointerEventL(
    const TPointerEvent& /*aPointerEvent*/, const TRect& /*aItemRect*/ )
    {
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleSimpleDataRow::CAknSingleColumnStyleSimpleDataRow(
    TUint32 aFlags )
    : CAknTreeLeaf( aFlags ),
    iIcon( KDefault ),
    iOptIcon( KDefault ),
    iHighlightedIcon( KDefault ),
    iHighlightedOptIcon( KDefault )
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSimpleDataRow::ConstructL( const TDesC& aText )
    {
    iText = aText.AllocL();
    }


