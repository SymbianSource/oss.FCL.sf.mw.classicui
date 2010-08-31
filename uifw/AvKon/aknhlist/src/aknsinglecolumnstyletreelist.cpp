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
* Description:  Implementation for CAknSingleColumnStyleTreeList class.
*
*/


#include <AknDef.h>
#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknTasHook.h> // for testability hooks
#include "aknhlistlib.h"
#include "akntree.h"
#include "akntreelistview.h"
#include "akntreelistinternalconstants.h"
#include "aknsinglecolumnstylecoredatarow.h"
#include "aknsinglecolumnstylesimpledatarow.h"
#include "aknsinglecolumnstylesubtitlerow.h"
#include "aknsinglecolumnstyletreelist.h"


/** Set of flags that are always set on for hierarchical column list. */
const TInt KMandatoryListFlags = NULL;

/** Set of flags that cannot be set for hierarchical column list. */
const TInt KRestrictedListFlags = NULL;

/** Set of default flags for hieararchical column list. */
const TInt KDefaultListFlags = KAknTreeListNoStructureLines;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleColumnStyleTreeList* CAknSingleColumnStyleTreeList::NewL()
    {
    CAknSingleColumnStyleTreeList* self
        = CAknSingleColumnStyleTreeList::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleColumnStyleTreeList* CAknSingleColumnStyleTreeList::NewL(
    const CCoeControl& aContainer )
    {
    CAknSingleColumnStyleTreeList* self
        = CAknSingleColumnStyleTreeList::NewLC( aContainer );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleColumnStyleTreeList* CAknSingleColumnStyleTreeList::NewLC()
    {
    CAknSingleColumnStyleTreeList* self =
        new( ELeave ) CAknSingleColumnStyleTreeList;
    CleanupStack::PushL( self );
    self->ConstructL();
    AKNTASHOOK_ADDL( self, "CAknSingleColumnStyleTreeList" );
    return self;
    }


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleColumnStyleTreeList* CAknSingleColumnStyleTreeList::NewLC(
    const CCoeControl& aContainer )
    {
    CAknSingleColumnStyleTreeList* self =
        new( ELeave ) CAknSingleColumnStyleTreeList;
    CleanupStack::PushL( self );
    self->ConstructL( aContainer );
    AKNTASHOOK_ADDL( self, "CAknSingleColumnStyleTreeList" );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleTreeList::~CAknSingleColumnStyleTreeList()
    {
    AKNTASHOOK_REMOVE();
    }


// ---------------------------------------------------------------------------
// Creates simple data row instance and adds it to the specified node.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknSingleColumnStyleTreeList::AddSimpleDataRowL(
    TAknTreeItemID aParent, const TDesC& aText, TUint32 aFlags,
    TBool aDrawNow )
    {
    // Get flags relevant to simple data row.
    TUint32 flags = NULL;
    if ( aFlags & EPersistent )
        {
        flags |= CAknTreeLeaf::EPersistent;
        }
    if ( aFlags & EMarked )
        {
        flags |= CAknTreeLeaf::EMarked;
        }
    if ( aFlags & EMarkingDisabled )
        {
        flags |= CAknTreeLeaf::EMarkingDisabled;
        }

    CAknSingleColumnStyleSimpleDataRow* row =
        CAknSingleColumnStyleSimpleDataRow::NewLC( aText, flags );
    TAknTreeItemID id = Tree().AddItemL( row, aParent, aDrawNow );
    CleanupStack::Pop( row );
    return id;
    }


// ---------------------------------------------------------------------------
// Creates core data row instance with two text columns and adds it to the
// specified parent node.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknSingleColumnStyleTreeList::AddCoreDataRowL(
    TAknTreeItemID aParent, const TDesC& aFirstColumn,
    const TDesC& aSecondColumn, TUint32 aFlags, TBool aDrawNow )
    {
    // Get flags relevant to core data row.
    TUint32 flags = NULL;
    if ( aFlags & EPersistent )
        {
        flags |= CAknTreeLeaf::EPersistent;
        }
    if ( aFlags & EMarked )
        {
        flags |= CAknTreeLeaf::EMarked;
        }
    if ( aFlags & EMarkingDisabled )
        {
        flags |= CAknTreeLeaf::EMarkingDisabled;
        }
    if ( aFlags & EEmphasis )
        {
        flags |= CAknSingleColumnStyleCoreDataRow::EEmphasis;
        }

    CAknSingleColumnStyleCoreDataRow* row =
        CAknSingleColumnStyleCoreDataRow::NewLC( aFirstColumn,
            aSecondColumn, flags );
    TAknTreeItemID id = Tree().AddItemL( row, aParent, aDrawNow );
    CleanupStack::Pop( row );
    return id;
    }


// ---------------------------------------------------------------------------
// Creates core data row instance with three text columns and adds it to the
// specified parent node.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknSingleColumnStyleTreeList::AddCoreDataRowL(
    TAknTreeItemID aParent, const TDesC& aFirstColumn,
    const TDesC& aSecondColumn, const TDesC& aThirdColumn, TUint32 aFlags,
    TBool aDrawNow )
    {
    // Get flags relevant to core data row.
    TUint32 flags = NULL;
    if ( aFlags & EPersistent )
        {
        flags |= CAknTreeLeaf::EPersistent;
        }
    if ( aFlags & EMarked )
        {
        flags |= CAknTreeLeaf::EMarked;
        }
    if ( aFlags & EMarkingDisabled )
        {
        flags |= CAknTreeLeaf::EMarkingDisabled;
        }
    if ( aFlags & EEmphasis )
        {
        flags |= CAknSingleColumnStyleCoreDataRow::EEmphasis;
        }

    CAknSingleColumnStyleCoreDataRow* row =
        CAknSingleColumnStyleCoreDataRow::NewLC( aFirstColumn,
            aSecondColumn, aThirdColumn, flags );
    TAknTreeItemID id = Tree().AddItemL( row, aParent, aDrawNow );
    CleanupStack::Pop( row );
    return id;
    }


// ---------------------------------------------------------------------------
// Creates subtitle row instance and adds it to the specified node.
// ---------------------------------------------------------------------------
//
EXPORT_C TAknTreeItemID CAknSingleColumnStyleTreeList::AddSubtitleRowL(
    TAknTreeItemID aParent, const TDesC& aText, TUint32 aFlags,
    TBool aDrawNow )
    {
    // Get flags relevant to subtitle row.
    TUint32 flags = NULL;
    if ( aFlags & EPersistent )
        {
        flags |= CAknTreeNode::EPersistent;
        }
    if ( aFlags & EMarked )
        {
        flags |= CAknTreeNode::EMarked;
        }
    if ( aFlags & EMarkingDisabled )
        {
        flags |= CAknTreeNode::EMarkingDisabled;
        }
    if ( aFlags & EExpanded )
        {
        flags |= CAknTreeNode::EExpanded;
        }
    if ( aFlags & ENonEmpty )
        {
        flags |= CAknTreeNode::ENonEmpty;
        }

    CAknSingleColumnStyleSubtitleRow* row =
        CAknSingleColumnStyleSubtitleRow::NewLC( aText, flags );
    TAknTreeItemID id = Tree().AddItemL( row, aParent, aDrawNow );
    CleanupStack::Pop( row );
    return id;
    }


// ---------------------------------------------------------------------------
// Returns the text field of the specified list item.
// ---------------------------------------------------------------------------
//
EXPORT_C const TDesC& CAknSingleColumnStyleTreeList::Text(
    TAknTreeItemID aItem ) const
    {
    return Text( aItem, 0 );
    }
    

// ---------------------------------------------------------------------------
// Returns the specified text column of specified list item. Null descriptor
// is returned if column with non-zero index is requested from simple data
// row or subtitle row.
// ---------------------------------------------------------------------------
//
EXPORT_C const TDesC& CAknSingleColumnStyleTreeList::Text(
    TAknTreeItemID aItem, TInt aColumnIndex ) const
    {
    CAknTreeItem* item = Tree().Item( aItem );
    TInt type = item->Type();

    if ( type == AknTreeList::KSingleColumnStyleCoreDataRow )
        {
        CAknSingleColumnStyleCoreDataRow* coreDataRow =
            static_cast<CAknSingleColumnStyleCoreDataRow*>( item );
        return coreDataRow->Text( aColumnIndex );
        }

    else if ( type == AknTreeList::KSingleColumnStyleSimpleDataRow &&
        !aColumnIndex )
        {
        CAknSingleColumnStyleSimpleDataRow* simpleDataRow =
            static_cast<CAknSingleColumnStyleSimpleDataRow*>( item );
        return simpleDataRow->Text();
        }

    else if ( type == AknTreeList::KSingleColumnStyleSubtitleRow &&
        !aColumnIndex )
        {
        CAknSingleColumnStyleSubtitleRow* subtitleRow = 
            static_cast<CAknSingleColumnStyleSubtitleRow*>( item );
        return subtitleRow->Text();
        }

    else
        {
        return KNullDesC;
        }
    }


// ---------------------------------------------------------------------------
// Set text for specified item.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSingleColumnStyleTreeList::SetTextL( TAknTreeItemID aItem,
    const TDesC& aText, TBool aDrawNow )
    {
    SetTextL( aItem, aText, 0, aDrawNow );
    }


// ---------------------------------------------------------------------------
// Set text for specified column of specified list item.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSingleColumnStyleTreeList::SetTextL( TAknTreeItemID aItem,
    const TDesC& aText, TInt aColumnIndex, TBool aDrawNow )
    {
    CAknTreeItem* item = Tree().Item( aItem );
    TInt type = item->Type();

    if ( type == AknTreeList::KSingleColumnStyleCoreDataRow )
        {
        CAknSingleColumnStyleCoreDataRow* coreDataRow =
            static_cast<CAknSingleColumnStyleCoreDataRow*>( item );
        coreDataRow->SetTextL( aText, aColumnIndex, aDrawNow );
        }

    else if ( type == AknTreeList::KSingleColumnStyleSimpleDataRow )
        {
        if ( !aColumnIndex )
            {
            CAknSingleColumnStyleSimpleDataRow* simpleDataRow =
                static_cast<CAknSingleColumnStyleSimpleDataRow*>( item );
            simpleDataRow->SetTextL( aText, aDrawNow );
            }
        else
            {
            User::Leave( KErrNotFound );
            }
        }

    else if ( type == AknTreeList::KSingleColumnStyleSubtitleRow )
        {
        if ( !aColumnIndex )
            {
            CAknSingleColumnStyleSubtitleRow* subtitleRow =
                static_cast<CAknSingleColumnStyleSubtitleRow*>( item );
            subtitleRow->SetTextL( aText, aDrawNow );
            }
        else
            {
            User::Leave( KErrNotFound );
            }
        }

    else
        {
        // Invalid item type.
        Panic( EAknHListPanicInvalidItemType );
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the specified core data row is emphasised.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknSingleColumnStyleTreeList::IsEmphasised(
    TAknTreeItemID aItem ) const
    {
    TBool emphasis = EFalse;
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleColumnStyleCoreDataRow )
        {
        CAknSingleColumnStyleCoreDataRow* coreDataRow =
            static_cast<CAknSingleColumnStyleCoreDataRow*>( item );
        emphasis = coreDataRow->IsEmphasised();
        }
    return emphasis;
    }


// ---------------------------------------------------------------------------
// Set emphasis for core data row.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSingleColumnStyleTreeList::SetEmphasis(
    TAknTreeItemID aItem, TBool aEmphasis, TBool aDrawNow )
    {
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleColumnStyleCoreDataRow )
        {
        CAknSingleColumnStyleCoreDataRow* coreDataRow =
            static_cast<CAknSingleColumnStyleCoreDataRow*>( item );
        coreDataRow->SetEmphasis( aEmphasis, aDrawNow );
        }
    else
        {
        // Invalid item type. Set emphasis supported only for core data rows.
        Panic( EAknHListPanicInvalidItemType );
        }
    }


// ---------------------------------------------------------------------------
// Checks whether the third text column is enabled.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknSingleColumnStyleTreeList::IsThirdColumnEnabled(
    TAknTreeItemID aItem ) const
    {
    TBool thirdColumn = EFalse;
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleColumnStyleCoreDataRow )
        {
        CAknSingleColumnStyleCoreDataRow* coreDataRow =
            static_cast<CAknSingleColumnStyleCoreDataRow*>( item );
        thirdColumn = coreDataRow->IsThirdColumnEnabled();
        }
    return thirdColumn;
    }


// ---------------------------------------------------------------------------
// Enables or disables third text column for specified item.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSingleColumnStyleTreeList::EnableThirdColumn(
    TAknTreeItemID aItem, TBool aEnable, TBool aDrawNow )
    {
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleColumnStyleCoreDataRow )
        {
        CAknSingleColumnStyleCoreDataRow* coreDataRow =
            static_cast<CAknSingleColumnStyleCoreDataRow*>( item );
        coreDataRow->EnableThirdColumn( aEnable, aDrawNow );
        }
    else
        {
        // Invalid item type.
        Panic( EAknHListPanicInvalidItemType );
        }
    }


// ---------------------------------------------------------------------------
// Get icon ID set for specified item.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknSingleColumnStyleTreeList::Icon( TAknTreeItemID aItem,
    TIconType aType ) const
    {
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleColumnStyleCoreDataRow )
        {
        CAknSingleColumnStyleCoreDataRow::TIconType type;
        switch ( aType )
            {
            case ELeaf:
                type = CAknSingleColumnStyleCoreDataRow::EIcon;
                break;
            case EHighlightedLeaf:
                type = CAknSingleColumnStyleCoreDataRow::EHighlightedIcon;
                break;
            case EOptionalIcon1:
                type = CAknSingleColumnStyleCoreDataRow::EOptIcon1;
                break;
            case EHighlightedOptionalIcon1:
                type = CAknSingleColumnStyleCoreDataRow::EHighlightedOptIcon1;
                break;
            case EOptionalIcon2:
                type = CAknSingleColumnStyleCoreDataRow::EOptIcon2;
                break;
            case EHighlightedOptionalIcon2:
                type = CAknSingleColumnStyleCoreDataRow::EHighlightedOptIcon2;
                break;
            default:
                // Invalid icon type for core data row.
                return KErrNotFound;
            }
        return static_cast<CAknSingleColumnStyleCoreDataRow*>( item )->
            Icon( type );
        }

    else if ( item->Type() == AknTreeList::KSingleColumnStyleSimpleDataRow )
        {
        CAknSingleColumnStyleSimpleDataRow::TIconType type;
        switch ( aType )
            {
            case ELeaf:
                type = CAknSingleColumnStyleSimpleDataRow::EIcon;
                break;
            case EHighlightedLeaf:
                type = CAknSingleColumnStyleSimpleDataRow::EHighlightedIcon;
                break;
            case EOptionalIcon1:
                type = CAknSingleColumnStyleSimpleDataRow::EOptIcon;
                break;
            case EHighlightedOptionalIcon1:
                type = CAknSingleColumnStyleSimpleDataRow::EHighlightedOptIcon;
                break;
            default:
                // Invalid icon type for simple data row.
                return KErrNotFound;
            }
        return static_cast<CAknSingleColumnStyleSimpleDataRow*>( item )->
            Icon( type );
        }

    else if ( item->Type() == AknTreeList::KSingleColumnStyleSubtitleRow )
        {
        CAknSingleColumnStyleSubtitleRow::TIconType type;
        switch ( aType )
            {
            case EExpandedNode:
                type = CAknSingleColumnStyleSubtitleRow::EExpandedIcon;
                break;
            case EHighlightedExpandedNode:
                type = CAknSingleColumnStyleSubtitleRow::EHighlightedExpandedIcon;
                break;
            case ECollapsedNode:
                type = CAknSingleColumnStyleSubtitleRow::ECollapsedIcon;
                break;
            case EHighlightedCollapsedNode:
                type = CAknSingleColumnStyleSubtitleRow::EHighlightedCollapsedIcon;
                break;
            case EOptionalIcon1:
                type = CAknSingleColumnStyleSubtitleRow::EOptIcon;
                break;
            case EHighlightedOptionalIcon1:
                type = CAknSingleColumnStyleSubtitleRow::EHighlightedOptIcon;
                break;
            default:
                // Invalid icon type for subtitle row.
                return KErrNotFound;
            }
        return static_cast<CAknSingleColumnStyleSubtitleRow*>( item )->
            Icon( type );
        }

    else
        {
        return KErrNotFound;
        }
    }


// ---------------------------------------------------------------------------
// Set icon for specified item.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknSingleColumnStyleTreeList::SetIcon(
    const TAknTreeItemID aItem, const TIconType aType, const TInt aIconId,
    const TBool aDrawNow )
    {
    CAknTreeItem* item = Tree().Item( aItem );
    if ( item->Type() == AknTreeList::KSingleColumnStyleCoreDataRow )
        {
        CAknSingleColumnStyleCoreDataRow::TIconType type
            = CAknSingleColumnStyleCoreDataRow::EIcon;
        switch ( aType )
            {
            case ELeaf:
                type = CAknSingleColumnStyleCoreDataRow::EIcon;
                break;
            case EHighlightedLeaf:
                type = CAknSingleColumnStyleCoreDataRow::EHighlightedIcon;
                break;
            case EOptionalIcon1:
                type = CAknSingleColumnStyleCoreDataRow::EOptIcon1;
                break;
            case EHighlightedOptionalIcon1:
                type = CAknSingleColumnStyleCoreDataRow::EHighlightedOptIcon1;
                break;
            case EOptionalIcon2:
                type = CAknSingleColumnStyleCoreDataRow::EOptIcon2;
                break;
            case EHighlightedOptionalIcon2:
                type = CAknSingleColumnStyleCoreDataRow::EHighlightedOptIcon2;
                break;
            default:
                // Invalid icon type for core data row.
                Panic( EAknHListPanicInvalidItemType );
                break;
            }
        static_cast<CAknSingleColumnStyleCoreDataRow*>( item )->
            SetIcon( type, aIconId, aDrawNow );
        }

    else if ( item->Type() == AknTreeList::KSingleColumnStyleSimpleDataRow )
        {
        CAknSingleColumnStyleSimpleDataRow::TIconType type
            = CAknSingleColumnStyleSimpleDataRow::EIcon;
        switch ( aType )
            {
            case ELeaf:
                type = CAknSingleColumnStyleSimpleDataRow::EIcon;
                break;
            case EHighlightedLeaf:
                type  = CAknSingleColumnStyleSimpleDataRow::EHighlightedIcon;
                break;
            case EOptionalIcon1:
                type = CAknSingleColumnStyleSimpleDataRow::EOptIcon;
                break;
            case EHighlightedOptionalIcon1:
                type = CAknSingleColumnStyleSimpleDataRow::EHighlightedOptIcon;
                break;
            default:
                // Invalid icon type for simple data row.
                Panic( EAknHListPanicInvalidItemType );
                break;
            }
        static_cast<CAknSingleColumnStyleSimpleDataRow*>( item )->
            SetIcon( type, aIconId, aDrawNow );
        }

    else if ( item->Type() == AknTreeList::KSingleColumnStyleSubtitleRow )
        {
        CAknSingleColumnStyleSubtitleRow::TIconType type
            = CAknSingleColumnStyleSubtitleRow::EExpandedIcon;
        switch ( aType )
            {
            case EExpandedNode:
                type = CAknSingleColumnStyleSubtitleRow::EExpandedIcon;
                break;
            case EHighlightedExpandedNode:
                type = CAknSingleColumnStyleSubtitleRow::
                    EHighlightedExpandedIcon;
                break;
            case ECollapsedNode:
                type = CAknSingleColumnStyleSubtitleRow::ECollapsedIcon;
                break;
            case EHighlightedCollapsedNode:
                type = CAknSingleColumnStyleSubtitleRow::
                    EHighlightedCollapsedIcon;
                break;
            case EOptionalIcon1:
                type = CAknSingleColumnStyleSubtitleRow::EOptIcon;
                break;
            case EHighlightedOptionalIcon1:
                type = CAknSingleColumnStyleSubtitleRow::EHighlightedOptIcon;
                break;
            default:
                // Invalid icon type for subtitle row.
                Panic( EAknHListPanicInvalidItemType );
                break;
            }
        static_cast<CAknSingleColumnStyleSubtitleRow*>( item )->
            SetIcon( type, aIconId, aDrawNow );
        }

    else
        {
        // Invalid item type.
        Panic( EAknHListPanicInvalidItemType );
        }
    }


// ---------------------------------------------------------------------------
// Returns the type of the specified item.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknSingleColumnStyleTreeList::TItemType
    CAknSingleColumnStyleTreeList::ItemType( TAknTreeItemID aItem ) const
    {
    TItemType type = ENone;
    if ( aItem != KAknTreeIIDNone )
        {
        CAknTreeItem* item = Tree().Item( aItem );
        switch ( item->Type() )
            {
            case AknTreeList::KTree:
                type = ETreeRoot;
                break;
            case AknTreeList::KSingleColumnStyleSimpleDataRow:
                type = ESimpleDataRow;
                break;
            case AknTreeList::KSingleColumnStyleCoreDataRow:
                type = ECoreDataRow;
                break;
            case AknTreeList::KSingleColumnStyleSubtitleRow:
                type = ESubtitleRow;
                break;
            default:
                break;
            }
        }
    return type;
    }


// ---------------------------------------------------------------------------
// From class CAknTreeList.
// Sets flags for the list.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleTreeList::SetFlags( TUint32 aFlags )
    {
    TUint32 flags = ( aFlags | KMandatoryListFlags ) & ~KRestrictedListFlags;
    CAknTreeList::SetFlags( flags );
    }


// ---------------------------------------------------------------------------
// From class CAknTreeList.
// Handles resource changes.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleTreeList::HandleResourceChange( TInt aType )
    {
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        UpdateIndention();
        }
    CAknTreeList::HandleResourceChange( aType );
    }



// ---------------------------------------------------------------------------
// Default C++ constructor.
// ---------------------------------------------------------------------------
//
CAknSingleColumnStyleTreeList::CAknSingleColumnStyleTreeList()
    {
    }


// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleTreeList::ConstructL()
    {
    BaseConstructL();
    UpdateIndention();

    // Set default flags on.
    SetFlags( KDefaultListFlags );
    }

// ---------------------------------------------------------------------------
// Second phase constructor.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleTreeList::ConstructL( const CCoeControl& aContainer )
    {
    BaseConstructL( aContainer );
    UpdateIndention();

    // Sets default flags on.
    SetFlags( KDefaultListFlags );
    }


// ---------------------------------------------------------------------------
// Updates the width of single indentation step.
// ---------------------------------------------------------------------------
//
void CAknSingleColumnStyleTreeList::UpdateIndention()
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( Rect(),
        AknLayoutScalable_Avkon::aid_indentation_list_msg().LayoutLine() );
    TInt indentationWidth = layoutRect.Rect().Width();
    View().SetIndentionWidth( indentationWidth );
    }
