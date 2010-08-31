/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


// INCLUDES
#include "CAknFileSelectionEventHandler.h"

#include <eikbtgpc.h> // CEikButtonGroupContainer
#include <avkon.hrh>

#include "CAknFileSelectionModel.h"
#include "MAknFileSelectionObserver.h"
#include "AknCFDUtility.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknFileSelectionEventHandler::CAknFileSelectionEventHandler
//
//
// -----------------------------------------------------------------------------
//
CAknFileSelectionEventHandler::CAknFileSelectionEventHandler(
    CCoeEnv* aCoeEnv,
    CAknFileSelectionModel* aModel,
    const TCommonDialogType& aDialogType,
    MAknFileSelectionObserver*& aObserver,
    const HBufC*& aLeftSoftkeyFile,
    const HBufC*& aLeftSoftkeyFolder,
    const HBufC*& aRightSoftkeyRootFolder,
    const HBufC*& aRightSoftkeySubfolder )
    :   iCoeEnv( aCoeEnv ),
        iModel( aModel ),
        iDialogType( aDialogType ),
        iObserver( aObserver ),
        iLeftSoftkeyFile( aLeftSoftkeyFile ),
        iLeftSoftkeyFolder( aLeftSoftkeyFolder ),
        iRightSoftkeyRootFolder( aRightSoftkeyRootFolder ),
        iRightSoftkeySubfolder( aRightSoftkeySubfolder )
    {
    ResetSoftkeyStatus();
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionEventHandler::ConstructL
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionEventHandler::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionEventHandler::NewL
//
// -----------------------------------------------------------------------------
//
CAknFileSelectionEventHandler* CAknFileSelectionEventHandler::NewL(
    CCoeEnv* aCoeEnv,
    CAknFileSelectionModel* aModel,
    const TCommonDialogType& aDialogType,
    MAknFileSelectionObserver*& aObserver,
    const HBufC*& aLeftSoftkeyFile,
    const HBufC*& aLeftSoftkeyFolder,
    const HBufC*& aRightSoftkeyRootFolder,
    const HBufC*& aRightSoftkeySubfolder )
    {
    CAknFileSelectionEventHandler* self = new( ELeave ) CAknFileSelectionEventHandler(
        aCoeEnv, aModel, aDialogType, aObserver,
        aLeftSoftkeyFile, aLeftSoftkeyFolder, aRightSoftkeyRootFolder, aRightSoftkeySubfolder );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// Destructor
CAknFileSelectionEventHandler::~CAknFileSelectionEventHandler()
    {
    }


// -----------------------------------------------------------------------------
// CAknFileSelectionEventHandler::PushIndicesL
//
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionEventHandler::PushIndicesL( TInt aTopIndex, TInt aFocus )
    {
    TFocusItem* item = new( ELeave ) TFocusItem( aTopIndex, aFocus );
    CleanupStack::PushL( item );
    iStack.PushL( item );
    CleanupStack::Pop();
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionEventHandler::PopIndices
//
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionEventHandler::PopIndices( TInt& aTopIndex, TInt& aFocus )
    {
    if( iStack.IsEmpty() )
        {
        aTopIndex = 0;
        aFocus = 0;
        return;
        }
    TFocusItem* item = iStack.Pop();
    aTopIndex = item->iTopIndex;
    aFocus = item->iFocus;
    delete item;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionEventHandler::ResetSoftkeyStatus
//
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionEventHandler::ResetSoftkeyStatus()
    {
    iCurrentLeftSoftkey = EFirstTime;
    iCurrentRightSoftkey = EFirstTime;
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionEventHandler::UpdateSoftkeysL
//
//
// -----------------------------------------------------------------------------
//
void CAknFileSelectionEventHandler::UpdateSoftkeysL( TInt aCurrentItemIndex,
    CEikButtonGroupContainer* aContainer )
    {
    if( !aContainer )
        {
        return;
        }
    TBool needDrawing( EFalse );
    TSoftkeyStatus targetLeftSoftkey( ESKNotVisible );
    TSoftkeyStatus targetRightSoftkey( ESKNotVisible );

    // Solve correct left softkey
    if( iModel->MdcaCount() > 0 )
        {
        if( ( aCurrentItemIndex == 0 ) &&
            ( AknCFDUtility::DirectoriesOnly( iDialogType ) ) )
            {
            targetLeftSoftkey = ESKFileFocused;
            }
        else
            {
            if( iModel->Entry( aCurrentItemIndex ).IsDir() )
                {
                targetLeftSoftkey = ESKFolderFocused;
                }
            else
                {
                targetLeftSoftkey = ESKFileFocused;
                }
            }
        }

    // Solve correct right softkey
    if( iModel->DirectoryLevel() > 0 )
        {
        targetRightSoftkey = ESKInSubfolder;
        }
    else
        {
        targetRightSoftkey = ESKInRootFolder;
        }

    MEikButtonGroup* bg = aContainer->ButtonGroup();

    // Change left softkey text if needed
    if( targetLeftSoftkey != iCurrentLeftSoftkey )
        {
        TInt commandId( bg->CommandId( 0 ) ); // Left softkey command id
        switch( targetLeftSoftkey )
            {
            case ESKFileFocused:
                {
                aContainer->SetCommandL( commandId, *iLeftSoftkeyFile );
                break;
                }
            case ESKFolderFocused:
                {
                aContainer->SetCommandL( commandId, *iLeftSoftkeyFolder );
                break;
                }
            case ESKNotVisible:
                {
                aContainer->SetCommandL( commandId, KNullDesC );
                break;
                }
            default:
                {
                break;
                }
            }
        needDrawing = ETrue;
        iCurrentLeftSoftkey = targetLeftSoftkey;
        }

    // Change right softkey text if needed
    if( targetRightSoftkey != iCurrentRightSoftkey )
        {
        TInt commandId( bg->CommandId( 2 ) ); // Right softkey command id
        switch( targetRightSoftkey )
            {
            case ESKInRootFolder:
                {
                aContainer->SetCommandL( commandId, *iRightSoftkeyRootFolder );
                break;
                }
            case ESKInSubfolder:
                {
                aContainer->SetCommandL( commandId, *iRightSoftkeySubfolder );
                break;
                }
            case ESKNotVisible:
                {
                aContainer->SetCommandL( commandId, KNullDesC );
                break;
                }
            default:
                {
                break;
                }
            }
        needDrawing = ETrue;
        iCurrentRightSoftkey = targetRightSoftkey;
        }

    // Redraw if necessary
    if( needDrawing )
        {
        aContainer->DrawNow();
        }
    }

// -----------------------------------------------------------------------------
// CAknFileSelectionEventHandler::HandleEventL
//
//
// -----------------------------------------------------------------------------
//
MAknCommonDialogsEventObserver::TAction CAknFileSelectionEventHandler::HandleEventL(
    TEvent aEvent,
    TInt& aFocusedItemIndex,
    TInt& aTopItemIndex,
    CEikButtonGroupContainer* aContainer )
    {

    // Default action is did nothing
    TAction returnType( EDidNothing );
    // Cache entry count
    TInt entries( iModel->MdcaCount() );

    //TEntry entry;

    if( entries > 0 )
        {
        iEntry = iModel->Entry( aFocusedItemIndex );
        }

    switch( aEvent )
        {
        case ERightSoftkeyPress: // USER HAS HIT RIGHT SOFTKEY
            {
            if( iModel->DirectoryLevel() > 0 ) // We are not in the root folder
                {
                while( ETrue ) // Find until existing contents
                    {
                    entries = iModel->GotoParentFolderL();
                    PopIndices( aTopItemIndex, aFocusedItemIndex );
                    if( entries > 0 || entries < KErrNotFound )
                        {
                        break;
                        }
                    }
                if( entries > 0 )
                    {
                    if (aFocusedItemIndex >= entries)
                        {
                        aFocusedItemIndex = entries - 1;
                        }
                    UpdateSoftkeysL( aFocusedItemIndex, aContainer );
                    returnType = EItemsUpdated;
                    }
                }
            else // We are in the root folder
                {
                returnType = ETryingToExit;
                }
            break;
            }

        case ELeftSoftkeyPress: // USER HAS HIT LEFT SOFTKEY
        case ESelectionKeyPress: // USER HAS HIT SELECTION KEY
        case EEventClicked:
            {
            if( entries > 0 ) // There are entries in the directory
                {
                if( ( aFocusedItemIndex == 0 ) && ( AknCFDUtility::DirectoriesOnly( iDialogType ) ) )
                    {
                    returnType = ETryingToExit;
                    break;
                    }
                if( iEntry.IsDir() )
                    {
                    entries = iModel->GotoSubFolderL( iEntry.iName );
                    if ( ( entries == 0 ) && ( iDialogType == ECFDDialogTypeSelect ) )
                        {
                        entries = iModel->GotoParentFolderL();
                        returnType = ELaunchEmptyPopup;
                        }
                    else if ( entries >= KErrNone )
                        {
                        PushIndicesL( aTopItemIndex, aFocusedItemIndex );
                        // In new folder the focus is always on first item
                        aTopItemIndex = 0;
                        aFocusedItemIndex = 0;
                        UpdateSoftkeysL( aFocusedItemIndex, aContainer );
                        returnType = EItemsUpdated;
                        }
                    }
                else // The selected entry is a file
                    {
                    returnType = ETryingToExit;
                    }
                }
            break;
            }

        case EFocusChange: // USER HAS HIT UP OR DOWN
            {
            UpdateSoftkeysL( aFocusedItemIndex, aContainer );
            break;
            }

        default:
            {
            break;
            }
        }
    if( ( returnType == ETryingToExit ) && ( aEvent != ERightSoftkeyPress ) )
        {
        if( iObserver )
            {
            //TPath path;
            HBufC * bufPath = HBufC::NewLC(KMaxPath);
            TPtr path = bufPath->Des();

            iModel->GetCurrentPath( path );
            if( !iObserver->OkToExitL( path, iEntry ) )
                {
                returnType = EDidNothing;
                }

            CleanupStack::PopAndDestroy();
            }
        }
    return returnType;
    }

// End of File
