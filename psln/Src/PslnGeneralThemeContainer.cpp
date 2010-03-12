/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  General theme view's container.
*
*/


// INCLUDE FILES
// General
#include <aknlists.h>
#include <eikclbd.h>
#include <StringLoader.h>
#include <AknGlobalNote.h>

#include <aknlocalskinlib.h>
#include <aknlistloadertfx.h>

#include <aknnotewrappers.h> 

// Resources.
#include <psln.rsg>

// Constants.
#include "PslnConst.h"

// Help context.
#include <csxhelp/skins.hlp.hrh>

// HAL
#include <hal.h>

// General - psln specific.
#include "PslnGeneralThemeContainer.h"
#include "PslnFeatures.h"
#include "PslnModel.h"
#include "PslnDebug.h"
#include "PslnSkinEntry.h"
#include "PslnUi.h"

// Central Repository and Publish&Subscribe keys.
#include <centralrepository.h>
#include "pslninternalcrkeys.h"


// Framework
#include <pslnfwiconhelper.h>
#include <mpslnfwmsklabelobserver.h>

// Constant for delay for the first timer event
const TTimeIntervalMicroSeconds32 KIdlePreviewDelay = 250000;

// Constant for interval for the subsequent timer events
const TTimeIntervalMicroSeconds32 KIdlePreviewInterval = 200000;

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnGeneralThemeContainer::CPslnGeneralThemeContainer()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::ConstructL( const TRect& aRect )
    {
    iListBox = new (ELeave) CAknSingleGraphicStyleListBox;


    iPreviewIdle = CPeriodic::NewL( CActive::EPriorityIdle );

    RFs& fs = CCoeEnv::Static()->FsSession();
    iLocalSkinInstance = CAknLocalSkinInstance::NewL ( fs, iModel->SkinSrvSession() );
    
    if( PslnFeatures::IsSupported( KPslnSupportFastPreviewTheme ) )
        {
        InitPreviewTime();
        }
    BaseConstructL( aRect, R_PSLN_SKIN_LIST_VIEW_TITLE, KPslnNoResource );
    iOldSkinNum = iModel->NumberOfSkins();
    }

// Destructor
CPslnGeneralThemeContainer::~CPslnGeneralThemeContainer()
    {
    // iListBox is deleted in class CPslnBaseContainer.

    iSkinItemList.Reset();

    if ( iPreviewIdle )
        {
        iPreviewIdle->Cancel();
        }
    delete iPreviewIdle;
    delete iLocalSkinInstance;

    // Remove locally skinned items.
    MAknsSkinInstance* si = AknsUtils::SkinInstance();
    if ( si )
        {        
        si->SetChangeEventsEnabled( EFalse );
        si->RemoveLocalItemDefs();
        si->SetChangeEventsEnabled( ETrue );
        }
    }

// ---------------------------------------------------------------------------
// Checks if embedded browser is supported.
// ---------------------------------------------------------------------------
//
TBool CPslnGeneralThemeContainer::IsEmbeddedLinkVisible() const
    {
    return PslnFeatures::IsEnhancedEmbeddedLinksSupported();
    }

// ---------------------------------------------------------------------------
// Updates skin item list.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::UpdateSkinListItemsL( const TInt& aNewIndex )
{
    // This is needed to make the list effects update
    CAknListLoader::InvalidateAll();

    PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::UpdateSkinListItemsL");
    // Update skins.
    iItemArray->Reset();
    iToBeUsedIndex = KErrNotFound;
    if ( aNewIndex != KErrNotFound )
        {
        iToBeUsedIndex = aNewIndex;
        }
    CreateListBoxItemsL();
    
    // Create pre- and post-text icons.
    CPslnFWIconHelper* iconHelper = CPslnFWIconHelper::NewL();
    CleanupStack::PushL( iconHelper );
    iconHelper->AddIconsToSettingItemsL(
        ETrue,
        KErrNotFound, // not used since we are adding all
        iListBox );
    CleanupStack::PopAndDestroy( iconHelper );
    
    }

// -----------------------------------------------------------------------------
// Creates listbox.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::ConstructListBoxL( TInt /*aResLbxId*/ )
    {
    iListBox->DisableSingleClick( ETrue );
    UpdateSkinListItemsL( KErrNotFound );
    }

// -----------------------------------------------------------------------------
// Empty implementation of inherited method.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::CreateListBoxItemsL()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::CreateListBoxItemsL BEGIN");
    TInt downloadAdded = 0;
    if ( IsEmbeddedLinkVisible() )
        {
        HBufC* text = StringLoader::LoadLC(
            R_PSLN_QTN_SKINS_DOWNLOAD_SKINS, iEikonEnv );
        // Reallocating invalidates original text, so it is required that
        // original text is popped from cleanupstack, then reassigned to
        // reallocated value and finally pushed back to cleanupstack.
        HBufC* reallocText = text->ReAllocL( text->Length() + KPslnIconSize );
        CleanupStack::Pop( text );
        text = reallocText;
        CleanupStack::PushL( text );
        // Do not use reallocated string after assigning it to the original.
        reallocText = NULL;
        TPtr textPtr = text->Des();

        textPtr.Insert( 0, KPslnFWEmbeddedLinkListItemFormat );
        iItemArray->InsertL( 0, textPtr );
        downloadAdded = 1;
        CleanupStack::PopAndDestroy( text );
        }

    TInt maxSkinIndex = 0;
    if ( iModel )
        {
        // If current skin is not found => update from server.
        if ( iModel->ActiveSkinIndex() == KErrNotFound )
            {
            iModel->PerformCompleteUpdateL();
            }
        maxSkinIndex = iModel->NumberOfSkins();
        }

    HBufC* skinName = HBufC::NewLC( KMaxName );
    TInt currentlyActiveSkinIndex = KErrNotFound;
    static_cast<CPslnUi*>( ControlEnv()->AppUi() )->
        SetDRMProtectedSkinInSkinList( EFalse );

    for ( TInt skinIndex = KPslnSeries60SkinIndex;
          skinIndex < maxSkinIndex; skinIndex++ )
        {
        PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::CreateListBoxItemsL 3");
        TPtr skinNamePtr = skinName->Des();
        iModel->GetSkinNameByIndex(
            skinIndex,
            skinNamePtr,
            EPslnSkinNameTypeList );

        // Add pre-text icon.
        if ( iModel->IsActiveSkinSelected( skinIndex  ) )
            {
            skinNamePtr.Insert( 0, KPslnFWActiveListItemFormat );
            currentlyActiveSkinIndex = skinIndex;
            }
        else
            {
            skinNamePtr.Insert( 0, KPslnFWNonActiveListItemFormat );
            }

        if( iModel->IsActiveSkinSelected( skinIndex  ) && iToBeUsedIndex == KErrNotFound )
            {
            iModel->SetCurrentSelectedSkinIndex (skinIndex);
            iToBeUsedIndex = skinIndex + downloadAdded;
            }

        // Add post-text icon(s).
#ifndef RD_MULTIPLE_DRIVE
        if( iModel->LocationOfSkin( skinIndex ) == EAknsSrvMMC )
            {
            skinNamePtr.Append( KPslnFWListItemFormatMMCSuffix );
            }
#else
        if( iModel->IsThemeOnMemoryCard( skinIndex ) )
            {
            skinNamePtr.Append( KPslnFWListItemFormatMMCSuffix );
            }
        else if( iModel->IsThemeOnMassDrive( skinIndex ) )
            {
            skinNamePtr.Append( KPslnFWListItemFormatMassDriveSuffix );
            }
#endif // RD_MULTIPLE_DRIVE

        switch( iModel->ProtectionOfSkin( skinIndex ) )
            {
            case EAknsSrvProtected:
                skinNamePtr.Append( KPslnFWListItemFormatDRMProtectedSuffix );
                static_cast<CPslnUi*>( ControlEnv()->AppUi() )->
                    SetDRMProtectedSkinInSkinList( ETrue );
                break;
            case EAknsSrvNoRights:
            case EAknsSrvCountBased:
            case EAknsSrvFutureRights:
            case EAknsSrvExpiredRights:
                skinNamePtr.Append( KPslnFWListItemFormatDRMExpiredSuffix );
                static_cast<CPslnUi*>( ControlEnv()->AppUi() )->
                    SetDRMProtectedSkinInSkinList( ETrue );
                break;
            case EAknsSrvNoProtection:
            default:
                // Do nothing
                break;
            }
        PSLN_TRACE_DEBUG1("CPslnGeneralThemeContainer::CreateListBoxItemsL postfix icon: %d", iModel->ProtectionOfSkin( skinIndex ) );
        iItemArray->InsertL( ( skinIndex + downloadAdded ), skinNamePtr );
        skinNamePtr.Zero();
        }
    CleanupStack::PopAndDestroy( skinName );
    
    if ( iOldSkinNum != maxSkinIndex )
        {
        iToBeUsedIndex = currentlyActiveSkinIndex + downloadAdded;
        }
    if ( ( iToBeUsedIndex >= ( 0 + downloadAdded ) ) &&
         ( iToBeUsedIndex <= ( maxSkinIndex + downloadAdded ) ) )
        {
        SetCurrentItemIndex( iToBeUsedIndex );
        iActiveSkinItemIndex = iToBeUsedIndex;
        }
    else
        {    
        SetCurrentItemIndex( ( currentlyActiveSkinIndex + downloadAdded ) );
        iActiveSkinItemIndex = currentlyActiveSkinIndex + downloadAdded;
        }
    iListBox->HandleItemAdditionL();
    if ( iOldSkinNum != maxSkinIndex )
        {
        StartThemePreviewL();
        iOldSkinNum = maxSkinIndex;
        }
    PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::CreateListBoxItemsL END");
    }

// ---------------------------------------------------------------------------
// Updates D column icons.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::UpdateSkinListItemsDColumnOnlyL()
    {
    // Create pre- and post-text icons.
    CPslnFWIconHelper* iconHelper = CPslnFWIconHelper::NewL();
    CleanupStack::PushL( iconHelper );
    iconHelper->AddIconsToSettingItemsL(
        ETrue,
        KErrNotFound, // not used since we are adding all
        iListBox );
    CleanupStack::PopAndDestroy( iconHelper );
    }

// ---------------------------------------------------------------------------
// Starts theme preview.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::StartThemePreviewL( TBool aTouch )
    {    
    // Start timer with 0.5s delay.
    iPreviewIdle->Cancel();
    
    if( PslnFeatures::IsSupported( KPslnSupportFastPreviewTheme ) )
        {
        iPreviewIdle->Start( 
            aTouch ? iPreviewDelayTime : iPreviewDelayTimeOnHardKey, 
            iPreviewIntervalTime, 
            TCallBack( DoHandleIdleTimeL, this ) );
        }
    else
        {
        iPreviewIdle->Start( 
            KIdlePreviewDelay, 
            KIdlePreviewInterval, 
            TCallBack( DoHandleIdleTimeL, this ) );
        }
    }
    
// ---------------------------------------------------------------------------
// Cancel theme preview.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::CancelThemePreviewL()
    {   
    iPreviewIdle->Cancel();
    }

// ---------------------------------------------------------------------------
// Sets theme preview observer.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::SetThemePreviewObserver( 
    MPslnThemePreviewObserver* aObserver )
    {
    iObserver = aObserver;
    }

// ---------------------------------------------------------------------------
// Locks up and down key events.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::LockUpAndDownKeys( const TBool& aLocked )
    {
    TRAPD( transitionEffectsValue, iModel->GetTransitionEffectStateL() );
    // Effects are enabled if value is NOT KMaxTInt.
    // Only lock keys, if transition effects are off.
    if( transitionEffectsValue == KMaxTInt ) 
        {        
        iLockedKeys = aLocked;
        }
    }

// ---------------------------------------------------------------------------
// Gets help context for Help application.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::GetHelpContext(
    TCoeHelpContext& aContext ) const
    {
    aContext.iMajor = KUidPsln;
    aContext.iContext = KSKINS_HLP_LIST;
    }

// ---------------------------------------------------------------------------
// Handles key events.
// Starts the new preview theme load before passing the event to base class.
// ---------------------------------------------------------------------------
//
TKeyResponse CPslnGeneralThemeContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, 
    TEventCode aType )
    {
    TKeyResponse resp = EKeyWasConsumed;

    // If lock is active, ignore up and down key events.
    if ( iLockedKeys &&
         !( aKeyEvent.iCode == EKeyUpArrow || aKeyEvent.iCode == EKeyDownArrow ) ||
        !iLockedKeys )
        {
        resp = CPslnBaseContainer::OfferKeyEventL( aKeyEvent, aType );
        }
    
       // React to up and down arrow key events IF download skin is not selected.
    if ( aType == EEventKey && 
         (aKeyEvent.iCode == EKeyUpArrow || aKeyEvent.iCode == EKeyDownArrow ) &&
         !iLockedKeys )
        {
        iObserver->HandlePreviewStateChange( ETrue );
        StartThemePreviewL( EFalse );
        }

    return resp;
    }

// ---------------------------------------------------------------------------
// Creates the skin item list for local item skinning.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::CreateSkinItemList()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::CreateSkinItemList" );
    TInt retVal = KErrNone;

    // Main area, screen, status pane and control pane.
    retVal += AddItemToList( KAknsIIDQsnBgScreen );
    //retVal += AddItemToList( KAknsIIDQsnBgAreaMainListGene );
    retVal += AddItemToList( KAknsIIDQsnBgAreaStaconRt );
    retVal += AddItemToList( KAknsIIDQsnBgAreaStaconLt );
    retVal += AddItemToList( KAknsIIDQsnBgAreaStaconRb );
    retVal += AddItemToList( KAknsIIDQsnBgAreaStaconLb );
    retVal += AddItemToList( KAknsIIDQsnBgAreaControl );
    retVal += AddItemToList( KAknsIIDQsnBgAreaControlPopup );
    retVal += AddItemToList( KAknsIIDQsnBgAreaStatus );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlat );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatCornerTl );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatCornerTr );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatCornerBl );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatCornerBr );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatSideT );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatSideB );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatSideL );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatSideR );
    retVal += AddItemToList( KAknsIIDQsnFrStatusFlatCenter );

    // Navipane
    retVal += AddItemToList( KAknsIIDQsnBgNavipaneSolid );
    retVal += AddItemToList( KAknsIIDQsnBgNavipaneWipe );
    retVal += AddItemToList( KAknsIIDQgnIndiNaviArrowLeft );
    retVal += AddItemToList( KAknsIIDQgnIndiNaviArrowRight );

    // Battery pane, signal pane
    retVal += AddItemToList( KAknsIIDQgnIndiSignalStrength );
    retVal += AddItemToList( KAknsIIDQgnIndiBatteryStrength );

    // Scrollbars
    retVal += AddItemToList( KAknsIIDQsnCpScrollBgTop );
    retVal += AddItemToList( KAknsIIDQsnCpScrollBgMiddle );
    retVal += AddItemToList( KAknsIIDQsnCpScrollBgBottom );
    retVal += AddItemToList( KAknsIIDQsnCpScrollHandleBgTop );
    retVal += AddItemToList( KAknsIIDQsnCpScrollHandleBgMiddle );
    retVal += AddItemToList( KAknsIIDQsnCpScrollHandleBgBottom );
    retVal += AddItemToList( KAknsIIDQsnCpScrollHandleTop );
    retVal += AddItemToList( KAknsIIDQsnCpScrollHandleMiddle );
    retVal += AddItemToList( KAknsIIDQsnCpScrollHandleBottom );

    // Tabs
    retVal += AddItemToList( KAknsIIDQgnGrafTabActiveL );
    retVal += AddItemToList( KAknsIIDQgnGrafTabActiveM );
    retVal += AddItemToList( KAknsIIDQgnGrafTabActiveR );
    retVal += AddItemToList( KAknsIIDQgnGrafTabPassiveL );
    retVal += AddItemToList( KAknsIIDQgnGrafTabPassiveM );
    retVal += AddItemToList( KAknsIIDQgnGrafTabPassiveR );    

    // Highlight
    retVal += AddItemToList( KAknsIIDQsnFrList );
    retVal += AddItemToList( KAknsIIDQsnFrListCornerTl );
    retVal += AddItemToList( KAknsIIDQsnFrListCornerTr );
    retVal += AddItemToList( KAknsIIDQsnFrListCornerBl );
    retVal += AddItemToList( KAknsIIDQsnFrListCornerBr );
    retVal += AddItemToList( KAknsIIDQsnFrListSideT );
    retVal += AddItemToList( KAknsIIDQsnFrListSideB );
    retVal += AddItemToList( KAknsIIDQsnFrListSideL );
    retVal += AddItemToList( KAknsIIDQsnFrListSideR );
    retVal += AddItemToList( KAknsIIDQsnFrListCenter );

    // Options menu
    retVal += AddItemToList( KAknsIIDQsnFrPopup );
    retVal += AddItemToList( KAknsIIDQsnFrPopupCornerTl );
    retVal += AddItemToList( KAknsIIDQsnFrPopupCornerTr );
    retVal += AddItemToList( KAknsIIDQsnFrPopupCornerBl );
    retVal += AddItemToList( KAknsIIDQsnFrPopupCornerBr );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSideT );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSideB );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSideL );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSideR );
    retVal += AddItemToList( KAknsIIDQsnFrPopupCenter );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSub );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSubCornerTl );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSubCornerTr );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSubCornerBl );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSubCornerBr );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSubSideT );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSubSideB );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSubSideL );
    retVal += AddItemToList( KAknsIIDQsnFrPopupSubSideR );
    retVal += AddItemToList( KAknsIIDQsnFrPopupCenterSubmenu );
    retVal += AddItemToList( KAknsIIDQgnIndiSubmenu );

    // Icons
    retVal += AddItemToList( KAknsIIDQgnPropPslnActive );
    retVal += AddItemToList( KAknsIIDQgnIndiMmcAdd );

    // QHD specific CBA.    
    retVal += AddItemToList( KAknsIIDQgnIndiSctrlMaskInactLsc );
    retVal += AddItemToList( KAknsIIDQgnIndiSctrlMaskActLsc );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButton );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonCornerTl );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonCornerTr );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonCornerBl );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonCornerBr );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonSideT );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonSideB );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonSideL );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonSideR );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlButtonCenter );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButton  );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonCornerTl );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonCornerTr );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonCornerBl );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonCornerBr );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonSideT );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonSideB );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonSideL );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonSideR );
    retVal += AddItemToList( KAknsIIDQgnFrSctrlSkButtonCenter );

    __ASSERT_DEBUG( retVal == KErrNone, User::Panic(_L("Error in inserting"), 1) );
    }

// ---------------------------------------------------------------------------
// Adds one item to skin item list.
// ---------------------------------------------------------------------------
//
TInt CPslnGeneralThemeContainer::AddItemToList( const TAknsItemID& aSkinID )
    {
    TAknsItemID skinItem;
    skinItem.Set( aSkinID.iMajor, aSkinID.iMinor );
    TInt error = iSkinItemList.InsertInOrder( skinItem, TAknsItemID::LinearOrder );
    PSLN_TRACE_DEBUG3("CPslnGeneralThemeContainer::AddItemToList item=%d %d added %d", 
        aSkinID.iMajor, aSkinID.iMinor, error );
    return error;
    }

// -----------------------------------------------------------------------------
// Callback function when application is idle.
// -----------------------------------------------------------------------------
//
TInt CPslnGeneralThemeContainer::DoHandleIdleTimeL( TAny* aAny )
    {
    static_cast< CPslnGeneralThemeContainer* >( aAny )->HandleIdleTimeL();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Callback function when application is idle.
// -----------------------------------------------------------------------------
//
TInt CPslnGeneralThemeContainer::DoHandleEffectEndL( TAny* aAny )
    {
    static_cast< CPslnGeneralThemeContainer* >( aAny )->HandleEffectEndL();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Handle idle time.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::HandleIdleTimeL()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::HandleIdleTimeL" );
    // First stop timer.
    iPreviewIdle->Cancel();
    
    // No re-preview the same theme
    if( iActiveSkinItemIndex == iListBox->CurrentItemIndex() )
        {
        return;
        }

    // Check free mem
    TInt freeMem = 0;
    HAL::Get( HALData::EMemoryRAMFree , freeMem );
    if( freeMem <= KPslnMinMemSize )
        {
        HBufC* errorBuf = StringLoader::LoadLC(
            R_PSLN_QTN_MEMLO_RAM_OUT_OF_MEM );
        // Display global note.
        CAknGlobalNote* errorNote = CAknGlobalNote::NewLC();
        errorNote->ShowNoteL( EAknGlobalErrorNote, *errorBuf );
        CleanupStack::PopAndDestroy( 2 ); // errorNote & errorBuf
        return;
        }

    iActiveSkinItemIndex = iListBox->CurrentItemIndex();
    // Ignore download skin item if it is available.
    TInt modifier = IsEmbeddedLinkVisible();
    TInt activeSkinIndex = iActiveSkinItemIndex - modifier;
    
    TBool usbAttached = static_cast<CPslnUi*>( ControlEnv()->AppUi() )->USBAttachState();
            
    if( iModel->IsValidForPreview(activeSkinIndex) == EFalse )
        {
        // If skin file didn't valid, preview active skin.
        activeSkinIndex = iModel->ActiveSkinIndex();
        }
    if ( IsEmbeddedLinkVisible() && iListBox->CurrentItemIndex() == 0 )
        {
        activeSkinIndex = iModel->ActiveSkinIndex();
        }
    if( iModel->IsThemeOnMemoryCard( activeSkinIndex ) && usbAttached)
        {
        activeSkinIndex = 0;
        }
    
    CPslnSkinEntry* activeSkin = iModel->VisibleSkin( activeSkinIndex );
    
    if ( activeSkin )
        {
        // Re-create the list, since skin preview library removes skinned items
        // from used list (performance reasons).
        iSkinItemList.Reset();
        CreateSkinItemList();        
        PSLN_TRACE_DEBUG("CPslnGeneralThemeContainer::HandleIdleTimeL Create Preview" );
        static_cast<CPslnUi*>( ControlEnv()->AppUi() )->ToggleScreenBlankerL( ETrue, ETrue, EFalse );

        if ( iModel->IsActiveSkinSelected( activeSkinIndex  ) )
            {            
            // Remove locally skinned items.
            MAknsSkinInstance* si = AknsUtils::SkinInstance();
            if ( si )
                {        
                si->SetChangeEventsEnabled( EFalse );
                si->RemoveLocalItemDefs();
                si->SetChangeEventsEnabled( ETrue );
                }
            }
        else
            {   
            TRAPD(err,iLocalSkinInstance->ApplyL( activeSkin->FullName(), iSkinItemList ));
            if (err == EAknsSrvProtected)
                {            
                ShowErrorNoteL( R_PSLN_QTN_DRM_PREV_RIGHTS_SET );
                }
            else if (err == KErrCorrupt)
                {
                //Skin corrupt
                ShowErrorNoteL( R_PSLN_QTN_SKINS_ERROR_CORRUPTED );
                //Preview the active skin
                TRAP_IGNORE(iLocalSkinInstance->ApplyL( 
                                iModel->VisibleSkin(iModel->ActiveSkinIndex())->FullName(),
                                iSkinItemList ));
                SetCurrentItemIndex( iModel->ActiveSkinIndex() + modifier);
                if ( iMSKObserver )
                    {
                    iMSKObserver->CheckMiddleSoftkeyLabelL();
                    }
                }
            else
                {
                User::LeaveIfError(err);    
                }        
            }

        // This is needed to make the list effects update
        CAknListLoader::InvalidateAll();

        if( PslnFeatures::IsSupported( KPslnSupportFastPreviewTheme ) )
            {
            iPreviewIdle->Start( 
                iPreviewDelayTime, 
                iPreviewIntervalTime, 
                TCallBack( DoHandleEffectEndL, this ) );
            }
        else
            {
            iPreviewIdle->Start( 
                KIdlePreviewDelay, 
                KIdlePreviewInterval, 
                TCallBack( DoHandleEffectEndL, this ) );
            }
        }
    }

// ---------------------------------------------------------------------------
// Handle effect end.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::HandleEffectEndL()
    {
    // First stop timer.
    iPreviewIdle->Cancel();
    static_cast<CPslnUi*>( ControlEnv()->AppUi() )->
        ToggleScreenBlankerL( EFalse, EFalse );
    iObserver->HandlePreviewStateChange( EFalse );
    }


    
// ---------------------------------------------------------------------------
// Restart Quick Preview
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::RestartQuickPreviewL()
    {
    TInt modifier = IsEmbeddedLinkVisible();
    TInt activeSkinIndex = iListBox->CurrentItemIndex() - modifier;
    if( iModel->IsThemeOnMemoryCard(activeSkinIndex) )
        {
        HandleIdleTimeL();
        }
    }
    
// ---------------------------------------------------------------------------
// Get Preview Skin Index
// ---------------------------------------------------------------------------
//    
TInt CPslnGeneralThemeContainer::PreviewSkinIndex()
    {
    // Ignore download skin item if it is available.
    TInt modifier = IsEmbeddedLinkVisible();
    TInt previewSkinIndex = iListBox->CurrentItemIndex() - modifier;
    
    TBool usbAttached = static_cast<CPslnUi*>( ControlEnv()->AppUi() )->USBAttachState();
    
    if( !iModel->IsValidForPreview(previewSkinIndex) )
        {
        // If skin file on memorycard and usb attached, preview default skin.
        previewSkinIndex = 0;
        }
    else if( iModel->IsThemeOnMemoryCard( previewSkinIndex ) && usbAttached)
        {
        // If skin file didn't exist, preview default skin.
        previewSkinIndex = 0;
        }
    return previewSkinIndex;
    }

// ---------------------------------------------------------------------------
// Set theme preview state active.
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::SetPreviewStateActive()
    {
    iObserver->HandlePreviewStateChange( ETrue );
    }
    
// ---------------------------------------------------------------------------
// Checks if current focus theme is in preview state. 
// ---------------------------------------------------------------------------
//
TBool CPslnGeneralThemeContainer::CurrentThemeInPreviewState()
    {
    return iListBox->CurrentItemIndex() != iActiveSkinItemIndex;
    }
    
// -----------------------------------------------------------------------------
// Load preview delay time settings from CenRep.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::InitPreviewTime()
    {
    //load from cenrep
    iPreviewDelayTime = KErrNone;
    iPreviewDelayTimeOnHardKey = KErrNone;
    iPreviewIntervalTime = KErrNone;
    CRepository* timeRepository = NULL;
    TRAPD( err, timeRepository = CRepository::NewL( KCRUidThemes ) );
    if( err != KErrNone )
        {
        return;
        }
    timeRepository->Get( KThemesPreviewDelayTime, iPreviewDelayTime ); 
    timeRepository->Get( KThemesPreviewDelayTimeOnHardKey, iPreviewDelayTimeOnHardKey ); 
    timeRepository->Get( KThemesPreviewIntervalTime, iPreviewIntervalTime );
    delete timeRepository;
    timeRepository = NULL;
    }

// -----------------------------------------------------------------------------
// Show Error Note.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::ShowErrorNoteL( TInt  aResourceId ) 
    {
    HBufC* errorText = StringLoader::LoadLC(aResourceId);
    CAknErrorNote * note = new(ELeave) CAknErrorNote (EFalse);
    note->ExecuteLD(*errorText);
    CleanupStack::PopAndDestroy(errorText);
    }

// -----------------------------------------------------------------------------
// Handle Pointer Event.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeContainer::HandlePointerEventL( const TPointerEvent &aPointerEvent )
    {
    // Cancel this kind of preview, in conflict with kinetic scrolling.
/*
    // Launch theme preview when pen up, in case pen is out of listbox.
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        iObserver->HandlePreviewStateChange( ETrue );
        StartThemePreviewL( ETrue );
        }
*/
    
    CCoeControl::HandlePointerEventL( aPointerEvent );
    }

//  End of File
