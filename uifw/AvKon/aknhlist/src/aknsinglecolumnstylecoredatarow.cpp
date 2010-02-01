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
* Description:  Implementation for CAknSingleColumnStyleCoreDataRow class.
*
*/


#include <AknUtils.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "akntree.h"
#include "aknsinglecolumnstylecoredatarow.h"
#include "akntreelistinternalconstants.h"

using AknTreeListIconID::KDefault;
using AknTreeListIconID::KNone;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor. Two text columns.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleCoreDataRow* CAknSingleColumnStyleCoreDataRow::NewLC(
    const TDesC& aFirstColumn, const TDesC& aSecondColumn, TUint32 aFlags )
    {
    CAknSingleColumnStyleCoreDataRow* self = 
        new ( ELeave ) CAknSingleColumnStyleCoreDataRow( aFlags );
    CleanupStack::PushL( self );
    self->ConstructL( aFirstColumn, aSecondColumn );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor. Three text columns.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleCoreDataRow* CAknSingleColumnStyleCoreDataRow::NewLC(
    const TDesC& aFirstColumn, const TDesC& aSecondColumn,
    const TDesC& aThirdColumn, TUint32 aFlags )
    {
    // By default, the third column is enabled, when core data row is
    // constructed with this method.
    aFlags |= EThirdColumnEnabled;
    CAknSingleColumnStyleCoreDataRow* self = 
        new ( ELeave ) CAknSingleColumnStyleCoreDataRow( aFlags );
    CleanupStack::PushL( self );
    self->ConstructL( aFirstColumn, aSecondColumn, aThirdColumn );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleCoreDataRow::~CAknSingleColumnStyleCoreDataRow()
    {
    delete iFirstColumn;
    delete iSecondColumn;
    delete iThirdColumn;
    }


// ---------------------------------------------------------------------------
// Returns the text set for the specified column of core data row.
// ---------------------------------------------------------------------------
//
const TDesC& CAknSingleColumnStyleCoreDataRow::Text( TInt aColumnIndex ) const
    {
    HBufC* text = NULL;
    switch ( aColumnIndex )
        {
        case 0:
            text = iFirstColumn;
            break;
        case 1:
            text = iSecondColumn;
            break;
        case 2:
            text = iThirdColumn;
            break;
        default:
            break;
        }
    return text ? *text : KNullDesC();
    }


// ---------------------------------------------------------------------------
// Allocates new heap based descriptor for the text, and if the allocation
// succeeds, deletes the specified descriptor and replaces it with the new.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleCoreDataRow::SetTextL( const TDesC& aText,
    TInt aColumnIndex, TBool aDrawNow )
    {
    HBufC* tmp = aText.AllocLC();

    switch ( aColumnIndex )
        {
        case 0:
            delete iFirstColumn;
            iFirstColumn = tmp;
            break;

        case 1:
            delete iSecondColumn;
            iSecondColumn = tmp;
            break;

        case 2:
            delete iThirdColumn;
            iThirdColumn = tmp;
            break;

        default:
            User::Leave( KErrNotFound );
            break;
        }

    CleanupStack::Pop( tmp );

    if ( aDrawNow )
        {
        __ASSERT_DEBUG( Root(), User::Invariant() );
        Root()->ItemModified( this );
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the third text column is enabled.
// ---------------------------------------------------------------------------
//
TBool CAknSingleColumnStyleCoreDataRow::IsEmphasised() const
    {
    return ( Flags() & EEmphasis ) ? ETrue : EFalse;
    }


// ---------------------------------------------------------------------------
// Changes the used layout for core data row.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleCoreDataRow::SetEmphasis( TBool aEmphasis,
    TBool aDrawNow )
    {
    SetFlags( aEmphasis ? Flags() | EEmphasis : Flags() & ~EEmphasis );

    if ( aDrawNow )
        {
        __ASSERT_DEBUG( Root(), User::Invariant() );
        Root()->ItemModified( this );
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the third text column is enabled.
// ---------------------------------------------------------------------------
//
TBool CAknSingleColumnStyleCoreDataRow::IsThirdColumnEnabled() const
    {
    return ( Flags() & EThirdColumnEnabled ) ? ETrue : EFalse;
    }


// ---------------------------------------------------------------------------
// Enables third text column to be usage in landscape mode.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleCoreDataRow::EnableThirdColumn( TBool aEnable,
    TBool aDrawNow )
    {
    SetFlags( aEnable ? ( Flags() | EThirdColumnEnabled ) :
        ( Flags() & ~EThirdColumnEnabled ) );
    
    if ( aDrawNow )
        {
        __ASSERT_DEBUG( Root(), User::Invariant() );
        Root()->ItemModified( this );
        }
    }


// ---------------------------------------------------------------------------
// Returns the icon ID set for the specified core data row icon type.
// ---------------------------------------------------------------------------
//
TInt CAknSingleColumnStyleCoreDataRow::Icon( TIconType aType ) const
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
//  Sets the icon ID for specified core data row icon type.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleCoreDataRow::SetIcon( TIconType aType, TInt aIconId,
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
TInt CAknSingleColumnStyleCoreDataRow::IconId( TBool aFocused ) const
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
TInt CAknSingleColumnStyleCoreDataRow::OptionalIconId( TInt aIndex,
    TBool aFocused ) const
    {
    __ASSERT_DEBUG( aIndex == 0 || aIndex == 1, User::Invariant() );

    // Default ID for optional icon.
    TInt optIconId = AknTreeListIconID::KNone; 

    // Determine ID for specified optional icon.
    if ( IsMarked() )
        {
        if ( aIndex == 0 )
            {
            optIconId = aFocused ?
                AknTreeListIconID::KHighlightedMarkedIndication :
                AknTreeListIconID::KMarkedIndication;
            }
        else if ( aIndex == 1 )
            {
            if ( aFocused && iHighlightedOptIcon1 != KDefault )
                {
                optIconId = iHighlightedOptIcon1;
                }
            else if ( iOptIcon1 != KDefault )
                {
                optIconId = iOptIcon1;
                }
            else if ( aFocused && iHighlightedOptIcon2 != KDefault )
                {
                optIconId = iHighlightedOptIcon2;
                }
            else if ( iOptIcon2 != KDefault )
                {
                optIconId = iOptIcon2;
                }
            }
        }
    else
        {
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
        }

    return optIconId;
    }


// ---------------------------------------------------------------------------
// Text variety for specified column.
// ---------------------------------------------------------------------------
//
TInt CAknSingleColumnStyleCoreDataRow::TextVariety( TInt aColumnIndex,
    TInt aOptIconId1, TInt aOptIconId2, TBool aThirdColumnEnabled ) const
    {
    TInt variety = KErrNotFound;

    TInt optIconCount = 0;
    if ( aOptIconId2 != KNone )
        {
        optIconCount = 2;
        }
    else if ( aOptIconId1 != KNone )
        {
        optIconCount = 1;
        }

    TInt emphasis = IsEmphasised() ? 0 : 3;

    if ( aThirdColumnEnabled )
        {
        // Three columns.
        if ( aColumnIndex == 0 || aColumnIndex == 1 )
            {
            variety = 6 + emphasis + optIconCount;
            }
        else if ( aColumnIndex == 2 )
            {
            variety = 0 + emphasis + optIconCount;
            }
        }
    else
        {
        // Two columns.
        if ( aColumnIndex == 0 || aColumnIndex == 1 )
            {
            variety = 0 + emphasis + optIconCount;
            }
        }

    return variety;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Returns the type of concrete item class.
// ---------------------------------------------------------------------------
//
TInt CAknSingleColumnStyleCoreDataRow::Type() const
    {
    return AknTreeList::KSingleColumnStyleCoreDataRow;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Returns the minimum size of the core data row.
// ---------------------------------------------------------------------------
//
TSize CAknSingleColumnStyleCoreDataRow::MinimumSize() const
    {
    TInt variety = 1;
    TRect minimumSize = RectFromLayout( TRect(),
        AknLayoutScalable_Avkon::aid_size_min_msg( variety ) );
    return minimumSize.Size();
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Draws the core data row to the appointed graphics context.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleCoreDataRow::Draw( CWindowGc& aGc,
    const TRect& aItemRect, const TRect& /*aRect*/, TBool aFocused ) const
    {
    CAknTree* root = Root();
    __ASSERT_DEBUG( root, User::Invariant() );

    // Icon.
    TInt iconVariety = 4; // Arbitrary value!
    TRect iconRect = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_g1( iconVariety ) );

    TInt iconId = IconId( aFocused );
    if ( iIcon != AknTreeListIconID::KNone )
        {
        root->DrawIcon( iconId, iconRect.Size(), aGc, iconRect.iTl,
        iconRect.Size() );
        }    

    // Optional icon IDs.
    TInt optIconId1 = OptionalIconId( 0, aFocused );
    TInt optIconId2 = OptionalIconId( 1, aFocused );

    // Determine whether third text column is used.
    TRect threeColumnMinimum = RectFromLayout( aItemRect,
        AknLayoutScalable_Avkon::aid_size_min_col_2() );
    TBool threeColumns = IsThirdColumnEnabled() &&
        Layout_Meta_Data::IsLandscapeOrientation() &&
        threeColumnMinimum.Width() < aItemRect.Width();

    // First text column.
    TAknLayoutText layoutText;
    TInt textVariety = TextVariety( 0, optIconId1, optIconId2, threeColumns );
    if ( textVariety >= 0 )
        {
        layoutText.LayoutText( aItemRect, AknLayoutScalable_Avkon::
            list_single_2heading_msg_pane_t2( textVariety ).LayoutLine() );
            
        if ( iFirstColumn )
            {
            root->DrawText( aGc, aItemRect, AknLayoutScalable_Avkon::
                list_single_2heading_msg_pane_t2( textVariety ),
                *iFirstColumn, NULL, this, aFocused, EFalse );
            }        
        }

    // Second text column.
    textVariety = TextVariety( 1, optIconId1, optIconId2, threeColumns );
    if ( textVariety >= 0 )
        {
        layoutText.LayoutText( aItemRect, AknLayoutScalable_Avkon::
            list_single_2heading_msg_pane_t3( textVariety ).LayoutLine() );
        if ( iSecondColumn )
            {
            root->DrawText( aGc, aItemRect, AknLayoutScalable_Avkon::
                list_single_2heading_msg_pane_t3( textVariety ),
                *iSecondColumn, NULL, this, aFocused, EFalse );
            }        
        }

    // Third text column.
    textVariety = TextVariety( 2, optIconId1, optIconId2, threeColumns );
    if  ( textVariety >= 0 )
        {
        layoutText.LayoutText( aItemRect, AknLayoutScalable_Avkon::
            list_single_2heading_msg_pane_t4( textVariety ).LayoutLine() );
        if ( iThirdColumn )
            {
            root->DrawText( aGc, aItemRect, AknLayoutScalable_Avkon::
                list_single_2heading_msg_pane_t4( textVariety ),
                *iThirdColumn, NULL, this, aFocused, EFalse );
            }
        }

    // Optional item state indication icon.
    TInt optIconVariety1 = 1;
    TRect optIconRect1 = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_g3( optIconVariety1 ) );
    if ( optIconId1 != KNone  )
        {
        root->DrawIcon( optIconId1, optIconRect1.Size(), aGc,
            optIconRect1.iTl, optIconRect1.Size() );
        }

    // Another optional item state indication icon.
    TInt optIconVariety2 = 1;
    TRect optIconRect2 = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_2heading_msg_pane_g4( optIconVariety2 ) );
    if ( optIconId2 != KNone  )
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
void CAknSingleColumnStyleCoreDataRow::HandlePointerEventL(
    const TPointerEvent& /*aPointerEvent*/, const TRect& /*aItemRect*/ )
    {
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleCoreDataRow::CAknSingleColumnStyleCoreDataRow(
    TUint32 aFlags )
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
// Second phase constructor. Two text columns.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleCoreDataRow::ConstructL( const TDesC& aFirstColumn,
    const TDesC& aSecondColumn )
    {
    iFirstColumn = aFirstColumn.AllocL();
    iSecondColumn = aSecondColumn.AllocL();
    }


// ---------------------------------------------------------------------------
// Second phase constructor. Three text columns.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleCoreDataRow::ConstructL( const TDesC& aFirstColumn,
    const TDesC& aSecondColumn, const TDesC& aThirdColumn )
    {
    iFirstColumn = aFirstColumn.AllocL();
    iSecondColumn = aSecondColumn.AllocL();
    iThirdColumn = aThirdColumn.AllocL();
    }

