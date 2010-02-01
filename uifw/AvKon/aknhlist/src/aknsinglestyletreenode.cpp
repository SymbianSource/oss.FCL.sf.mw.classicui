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
* Description:  Implementation for CAknSingleStyleTreeNode class.
*
*/


#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "aknsinglestyletreenode.h"
#include "akntree.h"
#include "akntreelistinternalconstants.h"

using AknTreeListIconID::KDefault;
using AknTreeListIconID::KNone;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeNode* CAknSingleStyleTreeNode::NewL( const TDesC& aText,
    TUint32 aFlags )
    {
    CAknSingleStyleTreeNode* self =
        CAknSingleStyleTreeNode::NewLC( aText, aFlags );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeNode* CAknSingleStyleTreeNode::NewLC( const TDesC& aText,
    TUint32 aFlags )
    {
    CAknSingleStyleTreeNode* self =
        new ( ELeave ) CAknSingleStyleTreeNode( aFlags );
    CleanupStack::PushL( self );
    self->ConstructL( aText );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeNode::~CAknSingleStyleTreeNode()
    {
    delete iText;
    }


// ---------------------------------------------------------------------------
// Returns the text set for the the node.
// ---------------------------------------------------------------------------
//
const TDesC& CAknSingleStyleTreeNode::Text() const
    {
    return iText ? *iText : KNullDesC();
    }


// ---------------------------------------------------------------------------
// Allocates new heap based descriptor for the text, and if the allocation
// succeeds, deletes the old descriptor and replaces it with the new.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeNode::SetTextL( const TDesC& aText, TBool aDrawNow )
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
// Returns the icon ID set for the specified tree node icon type.
// ---------------------------------------------------------------------------
//
TInt CAknSingleStyleTreeNode::Icon( TIconType aType ) const
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

        case EOptIcon1:
            iconId = iOptIcon1;
            break;

        case EOptIcon2:
            iconId = iOptIcon2;
            break;

        case EHighlightedExpandedIcon:
            iconId = iHighlightedExpandedIcon;
            break;

        case EHighlightedCollapsedIcon:
            iconId = iHighlightedCollapsedIcon;
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
// Sets the icon ID for specified tree node icon type.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeNode::SetIcon( TIconType aType, TInt aIconId,
    TBool aDrawNow )
    {
    switch ( aType )
        {
        case EExpandedIcon:
            iExpandedIcon = aIconId;
            break;
        
        case ECollapsedIcon:
            iCollapsedIcon = aIconId;
            break;

        case EOptIcon1:
            iOptIcon1 = aIconId;
            break;

        case EOptIcon2:
            iOptIcon2 = aIconId;
            break;

        case EHighlightedExpandedIcon:
            iHighlightedExpandedIcon = aIconId;
            break;

        case EHighlightedCollapsedIcon:
            iHighlightedCollapsedIcon = aIconId;
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
TInt CAknSingleStyleTreeNode::IconId( TBool aFocused ) const
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
TInt CAknSingleStyleTreeNode::OptionalIconId( TInt aIndex,
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
TInt CAknSingleStyleTreeNode::TextVariety( TInt aOptIconId1,
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
TInt CAknSingleStyleTreeNode::Type() const
    {
    return AknTreeList::KSingleStyleTreeNode;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeItem.
// Draws the content of the node to given graphic context.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeNode::Draw( CWindowGc& aGc, const TRect& aItemRect,
    const TRect& /*aRect*/, TBool aFocused ) const
    {
    CAknTree* root = Root();
    __ASSERT_DEBUG( root, User::Invariant() );

    // Icon.
    TInt iconVariety = 2; // Arbitrarily selected variety.
    TRect iconRect = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
        list_single_graphic_hl_pane_g2( iconVariety ) );

    TInt iconId = IconId( aFocused );
    
    // dragging / flicking
    
    if ( iconId != AknTreeListIconID::KNone )
        {
        root->DrawIcon( iconId, iconRect.Size(), aGc, iconRect.iTl,
            iconRect.Size() );
        }

    // Non-empty folder indication icon.
    if ( !IsEmpty() )
        {
        TInt indicatorVariety = 2; // Arbitrarily selected variety.
        TRect indicatorRect = RectFromLayout( aItemRect, AknLayoutScalable_Avkon::
            list_single_graphic_hl_pane_g3( indicatorVariety ) );

        TInt indicatorId = IsExpanded() ?
            CAknTree::ECollapseFunctionIndication : 
            CAknTree::EExpandFunctionIndication;

        root->DrawIcon( indicatorId, indicatorRect.Size(), aGc,
            indicatorRect.iTl, indicatorRect.Size() );
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
void CAknSingleStyleTreeNode::HandlePointerEventL(
    const TPointerEvent& /*aPointerEvent*/, const TRect& /*aItemRect*/ )
    {
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSingleStyleTreeNode::CAknSingleStyleTreeNode( TUint32 aFlags )
    : CAknTreeNode( aFlags ),
    iExpandedIcon( KDefault ),
    iCollapsedIcon( KDefault ),
    iOptIcon1( KDefault ),
    iOptIcon2( KDefault ),
    iHighlightedExpandedIcon( KDefault ),
    iHighlightedCollapsedIcon( KDefault ),
    iHighlightedOptIcon1( KDefault ),
    iHighlightedOptIcon2( KDefault )
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleStyleTreeNode::ConstructL( const TDesC& aText )
    {
    iText = aText.AllocL();
    }

