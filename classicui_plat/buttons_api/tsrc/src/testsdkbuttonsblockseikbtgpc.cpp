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
* Description:  Test api in eikbtgpc.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkbuttons.rsg>
#include <akniconutils.h>
#include <avkon.mbg>
#include <s32mem.h>

#include "testsdkbuttons.hrh"
#include "testsdkbuttons.h"

// CONSTANTS
_LIT( KBtTxt, "BtGroupContainer" );
_LIT( KBitmapFile, "Z:\\resource\\apps\\avkon2.mbm" );
const TInt KHeapSize = 20000;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerNewL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    switch ( num )
        {
        case ECaseOne:
            {
            CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                                CEikButtonGroupContainer::ECba,
                                                                                CEikButtonGroupContainer::EHorizontal,
                                                                                iContainer,
                                                                                R_GPS_CBABUTTON );
            CleanupStack::PushL( btgroupcontainer );
            CleanupStack::PopAndDestroy( btgroupcontainer );
            break;
            }
        case ECaseTwo:
            {
            CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                                CEikButtonGroupContainer::ECba,
                                                                                CEikButtonGroupContainer::EHorizontal,
                                                                                iContainer,
                                                                                R_GPS_CBABUTTON,
                                                                                *iContainer );
            CleanupStack::PushL( btgroupcontainer );
            CleanupStack::PopAndDestroy( btgroupcontainer );
            break;
            }
        case ECaseThree:
            {
            CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                    CEikButtonGroupContainer::ECba,
                                                                    CEikButtonGroupContainer::EHorizontal,
                                                                    iContainer,
                                                                    R_GPS_CBABUTTON,
                                                                    CCoeEnv::Static()->RootWin() );
            CleanupStack::PushL( btgroupcontainer );
            CleanupStack::PopAndDestroy( btgroupcontainer );
            break;
            }
        default:
            return KErrNotSupported;
        }
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerCurrent
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerCurrent( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer::Current();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerSetCommandL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    switch ( num )
        {
        case ECaseOne:
            {
            btgroupcontainer->SetCommandL( 0, EBckBt, KBtTxt );
            break;
            }
        case ECaseTwo:
            {
            CFbsBitmap* bitmap = NULL;
            CFbsBitmap* mask = NULL;
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            btgroupcontainer->SetCommandL( 0, EBckBt, *bitmap, *mask );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseThree:
            {
            CFbsBitmap* bitmap = NULL;
            CFbsBitmap* mask = NULL;
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            btgroupcontainer->SetCommandL( 0, EBckBt, KBtTxt , *bitmap, *mask );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseFour:
            {
            btgroupcontainer->SetCommandL( 0, EBckBt, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            break;
            }
        case ECaseFive:
            {
            btgroupcontainer->SetCommandL( 0, EBckBt, KBtTxt, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            break;
            }
        case ECaseSix:
            {
            btgroupcontainer->SetCommandL( 0, R_GPS_CBABUTTON );
            break;
            }
        case ECaseSeven:
            {
            TRAP( err, btgroupcontainer->SetCommandL( EBckBt, KBtTxt ) );
            break;
            }
        case ECaseEight:
            {
            CFbsBitmap* bitmap = NULL;
            CFbsBitmap* mask = NULL;
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            TRAP( err, btgroupcontainer->SetCommandL( EBckBt, *bitmap, *mask ) );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseNine:
            {
            CFbsBitmap* bitmap = NULL;
            CFbsBitmap* mask = NULL;
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            TRAP( err, btgroupcontainer->SetCommandL( EBckBt, KBtTxt , *bitmap, *mask ) );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseTen:
            {
            TRAP( err, btgroupcontainer->SetCommandL( EBckBt, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask ) );
            break;
            }
        case ECaseEleven:
            {
            TRAP( err, btgroupcontainer->SetCommandL( ELeftBt, KBtTxt, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask ) );
            break;
            }
        default:
            CleanupStack::PopAndDestroy( btgroupcontainer );
            return KErrNotSupported;
        }
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    if ( err != KErrNone )
        {
        err = KErrNone;
        }
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerSetCommandSetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerSetCommandSetL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->SetCommandSetL( R_GPS_CBABUTTON_FORSET );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerSetCommandSetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerAddCommandL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    switch ( num )
        {
        case ECaseOne:
            {
            TRAP( err, btgroupcontainer->AddCommandL( 0, EBckBt, KBtTxt ) );
            break;
            }
        case ECaseTwo:
            {
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            TRAP( err, btgroupcontainer->AddCommandL( 0, EBckBt, *bitmap, *mask ) );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseThree:
            {
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            TRAP( err, btgroupcontainer->AddCommandL( 0, EBckBt, KBtTxt, *bitmap, *mask ) );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseFour:
            {
            TRAP( err, btgroupcontainer->AddCommandL( 0, EBckBt, KBitmapFile, *bitmap, *mask ) );
            break;
            }
        case ECaseFive:
            {
            TRAP( err, btgroupcontainer->AddCommandL( 0, EBckBt, KBtTxt, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask ) );
            break;
            }
        default:
            CleanupStack::PopAndDestroy( btgroupcontainer );
            return KErrNotSupported;
        }
    
    CleanupStack::PopAndDestroy( btgroupcontainer );
    if ( err != KErrNone )
        {
        err = KErrNone;
        }
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerSetCommandSetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerAddCommandToStackL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    switch ( num )
        {
        case ECaseOne:
            {
            btgroupcontainer->AddCommandToStackL( 0, EBckBt, KBtTxt );
            break;
            }
        case ECaseTwo:
            {
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            btgroupcontainer->AddCommandToStackL( 0, EBckBt, *bitmap, *mask );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseThree:
            {
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            btgroupcontainer->AddCommandToStackL( 0, EBckBt, KBtTxt, *bitmap, *mask );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseFour:
            {
            AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            CleanupStack::PushL( bitmap );
            CleanupStack::PushL( mask );
            btgroupcontainer->AddCommandToStackL( 0, EBckBt, KBitmapFile, *bitmap, *mask );
            CleanupStack::Pop( 2 );
            break;
            }
        case ECaseFive:
            {
            btgroupcontainer->AddCommandToStackL( 0, EBckBt, KBtTxt, KBitmapFile, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
            break;
            }
        case ECaseSix:
            {
            btgroupcontainer->AddCommandToStackL( 0, R_GPS_CBABUTTON_FORSET );
            break;
            }
        default:
            CleanupStack::PopAndDestroy( btgroupcontainer );
            return KErrNotSupported;
        }
    CCoeEnv::Static()->AppUi()->RemoveFromStack( btgroupcontainer );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerAddCommandSetToStackL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerAddCommandSetToStackL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->AddCommandSetToStackL( R_GPS_CBABUTTON_FORSET );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( btgroupcontainer );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerRemoveCommandFromStackL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerRemoveCommandFromStackL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->AddCommandSetToStackL( R_GPS_CBABUTTON_FORSET );
    btgroupcontainer->RemoveCommandFromStack( 0, ELeftBt );
    
    CCoeEnv::Static()->AppUi()->RemoveFromStack( btgroupcontainer );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerSetDefaultCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerSetDefaultCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->AddCommandSetToStackL( R_GPS_CBABUTTON_FORSET );
    btgroupcontainer->SetDefaultCommand( ELeftBt );
    
    CCoeEnv::Static()->AppUi()->RemoveFromStack( btgroupcontainer );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerCalcMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerCalcMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    TSize size( 0, 0);
    size = btgroupcontainer->CalcMinimumSizeL( R_GPS_CBABUTTON );
    if ( size.iHeight == 0 || size.iWidth == 0 )
        {
        CCoeEnv::Static()->AppUi()->RemoveFromStack( btgroupcontainer );
        CleanupStack::PopAndDestroy( btgroupcontainer );
        return KErrGeneral;
        }
    CCoeEnv::Static()->AppUi()->RemoveFromStack( btgroupcontainer );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerCalcMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerCleanupFunctionL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->CleanupCommandPushL( 0 );
    btgroupcontainer->CleanupCommandPop();
    btgroupcontainer->CleanupCommandPushL( 0 );
    btgroupcontainer->CleanupCommandPushL( 1 );
    btgroupcontainer->CleanupCommandPop( 2 );
    
    btgroupcontainer->CleanupCommandPushL( 0 );
    btgroupcontainer->CleanupCommandPopAndDestroy();
    btgroupcontainer->CleanupCommandPushL( 0 );
    btgroupcontainer->CleanupCommandPopAndDestroy( 1 );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerBtNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerBtNumberL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->AddCommandSetToStackL( R_GPS_CBABUTTON_FORSET );
    btgroupcontainer->MaxCommands();
    TInt count = btgroupcontainer->ButtonCount();
    if ( count != 3 )
        {
        CCoeEnv::Static()->AppUi()->RemoveFromStack( btgroupcontainer );
        CleanupStack::PopAndDestroy( btgroupcontainer );
        return KErrGeneral;
        }
    CCoeEnv::Static()->AppUi()->RemoveFromStack( btgroupcontainer );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerCmdDimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerCmdDimL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->DimCommand( ELeftBt, ETrue );
    TBool result = btgroupcontainer->IsCommandDimmed( ELeftBt );
    if ( result )
        {
        CleanupStack::PopAndDestroy( btgroupcontainer );
        return KErrCorrupt;
        }
    btgroupcontainer->DimCommandByPosition( CEikButtonGroupContainer::ELeftSoftkeyPosition, EFalse );
    result = btgroupcontainer->IsCommandDimmedByPosition( CEikButtonGroupContainer::ELeftSoftkeyPosition );
    if ( result )
        {
        CleanupStack::PopAndDestroy( btgroupcontainer );
        return KErrCorrupt;
        }
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerCmdAnimateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerCmdAnimateL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->AnimateCommand( ELeftBt );
    btgroupcontainer->AnimateCommandByPosition( CEikButtonGroupContainer::ELeftSoftkeyPosition );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerCmdVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerCmdVisibleL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->MakeCommandVisible( ELeftBt, ETrue );
    TBool result = btgroupcontainer->IsCommandVisible( ELeftBt );
    if ( result )
        {
        CleanupStack::PopAndDestroy( btgroupcontainer );
        return KErrCorrupt;
        }
    btgroupcontainer->MakeCommandVisibleByPosition( CEikButtonGroupContainer::ELeftSoftkeyPosition, EFalse );
    result = btgroupcontainer->IsCommandVisibleByPosition( CEikButtonGroupContainer::ELeftSoftkeyPosition );
    if ( result )
        {
        CleanupStack::PopAndDestroy( btgroupcontainer );
        return KErrCorrupt;
        }
    
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerLocationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerLocationL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    CEikButtonGroupContainer::TLocation local = btgroupcontainer->Location();
    if ( local != CEikButtonGroupContainer::EExternal )
        {
        CleanupStack::PopAndDestroy( btgroupcontainer );
        return KErrCorrupt;
        }
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerCommandButtonOrNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerCommandButtonOrNullL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->CommandButtonOrNull( ELeftBt );
    // debug will panic directly and urel will return null directly 
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerControlOrNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerControlOrNullL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->ControlOrNull( ELeftBt );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerSetBoundingRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerSetBoundingRectL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    TRect rect( 20, 20, 40, 40);
    btgroupcontainer->SetBoundingRect( rect );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerReduceRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerReduceRectL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    TRect rect( 20, 20, 40, 40);
    btgroupcontainer->ReduceRect( rect );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerGetBtAndBtPositionAndBtTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerGetBtAndBtPositionAndBtTypeL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->ButtonById( ELeftBt );
    // debug will panic directly and urel will return null directly 
    btgroupcontainer->PositionById( ELeftBt );
    // debug will panic directly and urel will return null directly 
    if (CEikButtonGroupContainer::ECba != btgroupcontainer->ButtonGroupType() )
        {
        return KErrCorrupt;
        }
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerUpdateHotKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerUpdateHotKeyL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->UpdateHotKey( ELeftBt, CEikButtonGroupContainer::EShowHotKey, 0 );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerUpdateCommandObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerUpdateCommandObserverL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->UpdateCommandObserverL( 0, *iContainer );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerRemoveCommandObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerRemoveCommandObserverL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->UpdateCommandObserverL( 0, *iContainer );
    btgroupcontainer->RemoveCommandObserver( 0 );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerUpdatedCommandObserverExistsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerUpdatedCommandObserverExistsL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->UpdatedCommandObserverExists( CEikButtonGroupContainer::ELeftSoftkeyPosition );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerDelayActivationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerDelayActivationL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->DelayActivation();
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerButtonGroupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerButtonGroupL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    STIF_ASSERT_NOT_NULL( btgroupcontainer->ButtonGroup() );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerReservedFunctionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerReservedFunctionL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->Reserved_MtsmObject();
    btgroupcontainer->Reserved_MtsmPosition();
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerOfferCommandListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerOfferCommandListL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    RArray<TInt> cmdlist;
    for ( TInt i = 0; i < btgroupcontainer->ButtonCount(); i++ )
        {
        cmdlist.AppendL( i );
        }
    btgroupcontainer->OfferCommandListL( cmdlist );
    btgroupcontainer->OfferCommandListL( R_GPS_CBABUTTON_FORSET );
    STIF_ASSERT_NOT_NULL( btgroupcontainer->ButtonGroup() );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerIsCommandInGroupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerIsCommandInGroupL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->IsCommandInGroup( ELeftBt );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerIsCommandInGroupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerReplaceCommandL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->ReplaceCommand( ELeftBt, R_GPS_BUTTON );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->MinimumSize();
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    TKeyEvent keyevent;
    keyevent.iCode = EKeyDevice3;
    btgroupcontainer->OfferKeyEventL( keyevent, EEventKey );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerMakeVisibleL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    btgroupcontainer->MakeVisible( ETrue );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKButtons::TestCEikBtGroupContainerMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKButtons::TestCEikBtGroupContainerWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CEikButtonGroupContainer* btgroupcontainer = CEikButtonGroupContainer::NewL(
                                                                        CEikButtonGroupContainer::ECba,
                                                                        CEikButtonGroupContainer::EHorizontal,
                                                                        iContainer,
                                                                        R_GPS_CBABUTTON );
    CleanupStack::PushL( btgroupcontainer );
    HBufC8* buf8 = HBufC8::NewL( KHeapSize );
    CleanupStack::PushL( buf8 );
    TPtr8 ptr = buf8->Des();
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    stream.Open( ptr );
    btgroupcontainer->WriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    CleanupStack::PopAndDestroy( &stream );
    CleanupStack::PopAndDestroy( buf8 );
    CleanupStack::PopAndDestroy( btgroupcontainer );
    
    return KErrNone;
    }

// End of file

