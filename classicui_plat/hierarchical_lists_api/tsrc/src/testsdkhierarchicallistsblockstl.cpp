/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test akntreelist.h 
*
*/

#include <akntreelist.h>
#include <aknsinglestyletreelist.h>
#include <akniconutils.h>
#include <avkon.mbg>
#include <aknsconstants.h>

#include "testsdkhierarchicallists.h"
#include "testsdkhierarchicallistsordering.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLSetFlagsL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLSetFlagsL( CStifItemParser& /*aItem*/ )
    {
    CAknTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    treeList->SetFlags( KAknTreeListLooping );
    TUint32 flag = treeList->Flags();
    STIF_ASSERT_TRUE( flag == KAknTreeListLooping );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLFlagsL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLFlagsL( CStifItemParser& aItem )
    {
    return TestHLTLSetFlagsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLMoveItemL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLMoveItemL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( KAknTreeIIDRoot, KTextLeaf, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idLeaf );
    
    CAknTreeList* list = treeList;
    list->MoveItemL( idLeaf, idNode, ETrue );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLRemoveItemL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLRemoveItemL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( KAknTreeIIDRoot, KTextLeaf, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idLeaf );
    
    CAknTreeList* list = treeList;
    list->MoveItemL( idLeaf, idNode, ETrue );
    
    list->RemoveItem( idNode, ETrue );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLExpandNodeL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLExpandNodeL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    list->ExpandNode( idNode, ETrue );
    STIF_ASSERT_TRUE( list->IsExpanded( idNode ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLCollapseNodeL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLCollapseNodeL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    list->ExpandNode( idNode, ETrue );
    list->CollapseNode( idNode, ETrue );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLIsExpandedL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLIsExpandedL( CStifItemParser& aItem )
    {
    return TestHLTLExpandNodeL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLFocusedItemL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLFocusedItemL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    list->SetFocusedItem( idNode );
    STIF_ASSERT_TRUE( idNode == list->FocusedItem() );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLSetFocusedItemL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLSetFocusedItemL( CStifItemParser& aItem )
    {
    return TestHLTLFocusedItemL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLHighlightRectL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLHighlightRectL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    TRect rect = list->HighlightRect();
    TPoint point = rect.Size().AsPoint();
    STIF_ASSERT_EQUALS( 0, point.iX );
    STIF_ASSERT_EQUALS( 0, point.iY );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLAddIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLAddIconL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    TInt icon = list->AddIconL( KAknsIIDQgnPropHlFolderOpen, 
                                AknIconUtils::AvkonIconFileName(),
                                EMbmAvkonQgn_prop_hl_folder_open, 
                                EMbmAvkonQgn_prop_hl_folder_open_mask, 
                                EAspectRatioPreserved );
    STIF_ASSERT_NOT_EQUALS( 0, icon );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLAddIIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLAddIIconL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    _LIT( KBitmapFile, "z:\\resource\\apps\\avkon2.mbm" );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic,
                               EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );
    TInt icon = list->AddIconL( bitmap, mask, ETrue, EAspectRatioPreserved );
    STIF_ASSERT_NOT_EQUALS( 0, icon );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLAddColorIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLAddColorIconL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    TInt icon = list->AddColorIconL( KAknsIIDQgnPropHlFolder, 
                                     KAknsIIDQsnTextColors, 
                                     EAknsCIQsnTextColorsCG10, 
                                     AknIconUtils::AvkonIconFileName(),
                                     EMbmAvkonQgn_prop_hl_folder,
                                     EMbmAvkonQgn_prop_hl_folder_mask,
                                     KRgbWhite,
                                     EAspectRatioPreserved );
    STIF_ASSERT_NOT_EQUALS( 0, icon );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLAssignIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLAssignIconL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    _LIT( KBitmapFile, "z:\\resource\\apps\\avkon2.mbm" );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic,
                               EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );
    TInt icon = list->AddIconL( bitmap, mask, ETrue, EAspectRatioPreserved );
    STIF_ASSERT_NOT_EQUALS( 0, icon );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    list->AssignIconL( icon, 
                       KAknsIIDQgnPropHlFolderOpen, 
                       AknIconUtils::AvkonIconFileName(),
                       EMbmAvkonQgn_prop_hl_folder_open, 
                       EMbmAvkonQgn_prop_hl_folder_open_mask, 
                       EAspectRatioPreserved );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLAssignIIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLAssignIIconL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    _LIT( KBitmapFile, "z:\\resource\\apps\\avkon2.mbm" );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic,
                               EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );
    TInt icon = list->AddIconL( bitmap, mask, ETrue, EAspectRatioPreserved );
    STIF_ASSERT_NOT_EQUALS( 0, icon );
    
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    CFbsBitmap* bitmapAssign = NULL;
    CFbsBitmap* maskAssign = NULL;
    
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_level_back,
                               EMbmAvkonQgn_indi_level_back_mask );
    CleanupStack::PushL( bitmapAssign );
    CleanupStack::PushL( maskAssign );
    list->AssignIconL( icon, bitmap, mask, ETrue, EAspectRatioPreserved );
    CleanupStack::Pop( maskAssign );
    CleanupStack::Pop( bitmapAssign );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLAssignColorIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLAssignColorIconL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;

    TInt icon = list->AddColorIconL( KAknsIIDQgnPropHlFolder, 
                                     KAknsIIDQsnTextColors, 
                                     EAknsCIQsnTextColorsCG10, 
                                     AknIconUtils::AvkonIconFileName(),
                                     EMbmAvkonQgn_prop_hl_folder,
                                     EMbmAvkonQgn_prop_hl_folder_mask,
                                     KRgbWhite,
                                     EAspectRatioPreserved );
    STIF_ASSERT_NOT_EQUALS( 0, icon );
    
    list->AssignColorIconL( icon,
                            KAknsIIDQgnIndiHlLineBranch,
                            KAknsIIDQsnTextColors, 
                            EAknsCIQsnTextColorsCG10, 
                            AknIconUtils::AvkonIconFileName(),
                            EMbmAvkonQgn_indi_hl_line_branch,
                            EMbmAvkonQgn_indi_hl_line_branch_mask,
                            KRgbWhite,
                            EAspectRatioPreserved );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLRemoveIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLRemoveIconL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    _LIT( KBitmapFile, "z:\\resource\\apps\\avkon2.mbm" );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic,
                               EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );
    TInt icon = list->AddIconL( bitmap, mask, ETrue, EAspectRatioPreserved );
    STIF_ASSERT_NOT_EQUALS( 0, icon );
    list->RemoveIconL( icon );
    
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLChildCountL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLChildCountL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    CAknTreeList* list = treeList;
    
    TInt count = list->ChildCount( idNode );
    STIF_ASSERT_EQUALS( 0, count );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLChildL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLChildL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextChild, "AddChild" );
    TAknTreeItemID idChild =treeList->AddNodeL( idNode, KTextChild, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    STIF_ASSERT_TRUE( idChild == list->Child( idNode, 0 ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLParentL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLParentL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextChild, "AddChild" );
    TAknTreeItemID idChild =treeList->AddNodeL( idNode, KTextChild, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    STIF_ASSERT_TRUE( idNode == list->Parent( idChild ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLContainsL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLContainsL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextChild, "AddChild" );
    TAknTreeItemID idChild =treeList->AddNodeL( idNode, KTextChild, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    STIF_ASSERT_TRUE( list->Contains( idNode ) );
    STIF_ASSERT_TRUE( list->Contains( idChild ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLIsNodeL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLIsNodeL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextChild, "AddChild" );
    TAknTreeItemID idChild =treeList->AddNodeL( idNode, KTextChild, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    STIF_ASSERT_TRUE( list->IsNode( idNode ) );
    STIF_ASSERT_TRUE( list->IsNode( idChild ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLIsLeafL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLIsLeafL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    STIF_ASSERT_FALSE( list->IsLeaf( idNode ) );
    STIF_ASSERT_TRUE( list->IsLeaf( idLeaf ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLIsMarkedL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLIsMarkedL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    list->SetMarked( idNode, ETrue, ETrue );
    STIF_ASSERT_TRUE( list->IsMarked( idNode ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLSetMarkedL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLSetMarkedL( CStifItemParser& aItem )
    {
    return TestHLTLIsMarkedL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLEnableMarkingL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLEnableMarkingL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    list->EnableMarking( idNode, ETrue );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLGetMarkedRItemsL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLGetMarkedRItemsL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    RArray<TAknTreeItemID> array;
    CleanupClosePushL( array );
    
    const TInt count = 2;
    list->SetMarked( idNode, ETrue, ETrue );
    list->SetMarked( idLeaf, ETrue, ETrue );
    list->GetMarkedItemsL( array );
    STIF_ASSERT_EQUALS( count, array.Count() );
    
    CleanupStack::PopAndDestroy( &array );
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLGetMarkedItemsL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLGetMarkedItemsL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    RArray<TAknTreeItemID> array;
    CleanupClosePushL( array );
    
    const TInt count = 1;
    list->SetMarked( idNode, ETrue, ETrue );
    list->SetMarked( idLeaf, ETrue, ETrue );
    list->GetMarkedItemsL( idNode, array );
    STIF_ASSERT_EQUALS( count, array.Count() );
    
    CleanupStack::PopAndDestroy( &array );
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLIsEmptyL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLIsEmptyL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    STIF_ASSERT_FALSE( list->IsEmpty( idNode ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLSetNonEmptyL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLSetNonEmptyL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    list->SetNonEmpty( idNode, EFalse, ETrue );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLIsPersistentL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLIsPersistentL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    list->SetPersistent( idNode, ETrue );
    STIF_ASSERT_TRUE( list->IsPersistent( idNode ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLSetPersistentL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLSetPersistentL( CStifItemParser& aItem )
    {
    return TestHLTLIsPersistentL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLSortL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLSortL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    CTestSDKOrdering* ordering = new (ELeave) CTestSDKOrdering;
    CleanupStack::PushL( ordering );
    STIF_ASSERT_NOT_NULL( ordering );
    
    list->Sort( ordering, ETrue );
    
    CleanupStack::PopAndDestroy( ordering );
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLNSortL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLNSortL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    list->Sort( idNode, ETrue, ETrue );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLAddObserverL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLAddObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    CTestSDKOrdering* ordering = new (ELeave) CTestSDKOrdering;
    CleanupStack::PushL( ordering );
    STIF_ASSERT_NOT_NULL( ordering );
    
    list->AddObserverL( ordering );
    list->RemoveObserver( ordering );
    
    CleanupStack::PopAndDestroy( ordering );
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLRemoveObserverL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLRemoveObserverL( CStifItemParser& aItem )
    {
    return TestHLTLAddObserverL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLTabModeFunctionIndicatorsL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLTabModeFunctionIndicatorsL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    list->EnableTabModeFunctionIndicatorsL( ETrue );
    STIF_ASSERT_TRUE( list->TabModeFunctionIndicators() );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLEnableTabModeFunctionIndicatorsL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLEnableTabModeFunctionIndicatorsL( CStifItemParser& aItem )
    {
    return TestHLTLTabModeFunctionIndicatorsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLSetFocusedItemIDL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLSetFocusedItemIDL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    list->SetFocusedItem( idNode );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLFocusedItemIndexL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLFocusedItemIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    const TInt index = -1;
    STIF_ASSERT_EQUALS( index, list->FocusedItemIndex() );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLVisibleItemIndexL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLVisibleItemIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    const TInt index = 0;
    STIF_ASSERT_EQUALS( index, list->VisibleItemIndex( idNode ) );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLOSortL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLOSortL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    CTestSDKOrdering* ordering = new (ELeave) CTestSDKOrdering;
    CleanupStack::PushL( ordering );
    STIF_ASSERT_NOT_NULL( ordering );
    
    list->Sort( ordering, CAknTreeList::ESaveFocus, ETrue );
    
    CleanupStack::PopAndDestroy( ordering );
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLFBSortL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLFBSortL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KTextNode, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID idNode = treeList->AddNodeL( KAknTreeIIDRoot, KTextNode, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, idNode );
    
    _LIT( KTextLeaf, "AddLeaf" );
    TAknTreeItemID idLeaf = treeList->AddLeafL( idNode, KTextLeaf, flags, ETrue );
    
    CAknTreeList* list = treeList;
    
    list->Sort( idNode, CAknTreeList::ESaveFocus, ETrue, ETrue );

    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLTLSetEmptyTextL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLTLSetEmptyTextL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    CAknTreeList* list = treeList;
    
    _LIT( KText, "EmptyText" );
    list->SetEmptyTextL( KText );

    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }
