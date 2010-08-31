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
* Description:  Implementation for CAknSingleColumnStyleSubtitleRow class.
*
*/


#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "akntree.h"
#include "aknsinglecolumnstylesubtitlerow.h"
#include "akntreelistinternalconstants.h"

using AknTreeListIconID::KDefault;
using AknTreeListIconID::KNone;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleSubtitleRow* CAknSingleColumnStyleSubtitleRow::NewLC(
    const TDesC& aText, TUint32 aFlags )
    {
    CAknSingleColumnStyleSubtitleRow* self = 
        new ( ELeave ) CAknSingleColumnStyleSubtitleRow( aFlags );
    CleanupStack::PushL( self );
    self->ConstructL( aText );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleSubtitleRow::~CAknSingleColumnStyleSubtitleRow()
    {
    delete iText;
    }


// ---------------------------------------------------------------------------
// Returns the text set for the subtitle row.
// ---------------------------------------------------------------------------
//
const TDesC& CAknSingleColumnStyleSubtitleRow::Text() const
    {
    return iText ? *iText : KNullDesC();
    }


// ---------------------------------------------------------------------------
// Allocates new heap based descriptor for the text, and if the allocation
// succeeds, deletes the old descriptor and replaces it with the new.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSubtitleRow::SetTextL( const TDesC& aText,
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
// Returns the icon ID set for the specified subtitle row icon type.
// ---------------------------------------------------------------------------
//
TInt CAknSingleColumnStyleSubtitleRow::Icon( TIconType aType ) const
    {
    TInt iconId = KDefault;
    switch ( aType )
        {
        case EExpandedIcon:
            iconId = iExpandedIcon;
            break;

        case ECollapsedIcon:
            iconId = iCollapsedIcon;
            break;

        case EOptIcon:
            iconId = iOptIcon;
            break;

        case EHighlightedExpandedIcon:
            iconId = iHighlightedExpandedIcon;
            break;

        case EHighlightedCollapsedIcon:
            iconId = iHighlightedCollapsedIcon;
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
//  Sets the icon ID for specified subtitle row icon type.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSubtitleRow::SetIcon( TIconType aType,
    TInt aIconId, TBool aDrawNow )
    {
    switch( aType )
        {
        case EExpandedIcon:
            iExpandedIcon = aIconId;
            break;
        
        case ECollapsedIcon:
            iCollapsedIcon = aIconId;
            break;

        case EOptIcon:
            iOptIcon = aIconId;
            break;

        case EHighlightedExpandedIcon:
            iHighlightedExpandedIcon = aIconId;
            break;

        case EHighlightedCollapsedIcon:
            iHighlightedCollapsedIcon = aIconId;
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
TInt CAknSingleColumnStyleSubtitleRow::IconId( TBool aFocused ) const
    {
    TInt iconId = KNone;
    if ( IsExpanded() )
        {
        iconId = CAknTree::EOpenFolderIndication;
        if ( aFocused && iHighlightedExpandedIcon != KDefault )
            {
            iconId = iHighlightedExpandedIcon;
            }
        else if ( iExpandedIcon != KDefault )
            {
            iconId = iExpandedIcon;
            }
        }
    else
        {
        iconId = CAknTree::EClosedFolderIndication;
        if ( aFocused && iHighlightedCollapsedIcon != KDefault )
            {
            iconId = iHighlightedCollapsedIcon;
            }
        else if ( iCollapsedIcon != KDefault )
            {
            iconId = iCollapsedIcon;
            }
        }
    return iconId;
    }


// ---------------------------------------------------------------------------
// Optional icon ID.
// ---------------------------------------------------------------------------
//
TInt CAknSingleColumnStyleSubtitleRow::OptionalIconId( TBool aFocused ) const
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
TInt CAknSingleColumnStyleSubtitleRow::Type() const
    {
    return AknTreeList::KSingleColumnStyleSubtitleRow;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Draws the subtitle row to the appointed graphics context.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSubtitleRow::Draw( CWindowGc& aGc,
    const TRect& aItemRect, const TRect& /*aRect*/, TBool aFocused ) const
    {
    CAknTree* root = Root();
    __ASSERT_DEBUG( root, User::Invariant() );

    // Icon.
    TInt iconVariety =  IsMarked() ? 3 : 2;
    TRect iconRect = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_g1( iconVariety ) );

    TInt iconId = IconId( aFocused );
    
    if ( iconId != AknTreeListIconID::KNone )
        {
        root->DrawIcon( iconId, iconRect.Size(), aGc, iconRect.iTl,
            iconRect.Size() );
        }    

    // Non-empty folder indication icon.
    if ( !IsEmpty() )
        {
        TInt indicatorId = IsExpanded() ?
            CAknTree::ECollapseFunctionIndication :
            CAknTree::EExpandFunctionIndication;

        root->DrawIcon( indicatorId, iconRect.Size(), aGc, iconRect.iTl,
            iconRect.Size() );        
        }

    // Optional icon ID.
    TInt optIconId = OptionalIconId( aFocused );

    // Text.
    TAknLayoutText layoutText;
    TInt textVariety = ( optIconId == KNone ) ? 2 : 3;
    layoutText.LayoutText( aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_t1( textVariety ).LayoutLine() );

    root->DrawText( aGc, aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_t1( textVariety ), *iText, NULL,
        this, aFocused, ETrue );    

    // Optional indication icon.
    TInt optIconVariety = 1; // Sorting group. Marked.
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
void CAknSingleColumnStyleSubtitleRow::HandlePointerEventL(
    const TPointerEvent& /*aPointerEvent*/, const TRect& /*aItemRect*/ )
    {
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleSubtitleRow::CAknSingleColumnStyleSubtitleRow(
    TUint32 aFlags )
    : CAknTreeNode( aFlags ),
    iExpandedIcon( KDefault ),
    iCollapsedIcon( KDefault ),
    iOptIcon( KDefault ),
    iHighlightedExpandedIcon( KDefault ),
    iHighlightedCollapsedIcon( KDefault ),
    iHighlightedOptIcon( KDefault )
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleSubtitleRow::ConstructL( const TDesC& aText )
    {
    iText = aText.AllocL();
    }



