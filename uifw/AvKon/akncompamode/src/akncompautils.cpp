/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Compatibility mode utility functions
*
*/


#include <e32base.h>
#include <data_caging_path_literals.hrh>
#include <barsread.h>
#include <bautils.h>
#include <aknappui.h>
#include <coemop.h>
#include <AknScreenMode.h>
#include <AknSgcc.h>
#include <AknCapServerDefs.h>
#include <AknNotifierWrapperDefs.h>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <pslninternalcrkeys.h>

#include <akncompamode.rsg>

#include "akncompautils.h"
#include "akncompakb.h"
#include "akncompabutton.h"
#include "akncompaclearer.h"
#include "akncompaflags.h"

// Class to detect a console application via MopGetObject
class MConsoleApp
    {
public:
    DECLARE_TYPE_ID(0x2001b26a)
    };

// --------------------------------------------------------------------------
// Determine if app requires compa-mode and set to compa screen
// mode if so
// --------------------------------------------------------------------------
TInt AknCompaUtils::SetCompaAppScreenModeL(TBool& aScrModeChanged,
    TBool& aIsConsoleApp, CAknCompaClearer*& aClearer, TInt aAppUiFlags,
    CAknAppUiBase& aAppUi, const CCoeEnv& aCoeEnv, CRepository& aRepository)
    {
    // Change application screen mode before a call to BaseConstructL().
    // This prevents HandleResourceChangeL() to be called before application
    // views have been constructed.

    aScrModeChanged = EFalse;
    aIsConsoleApp = IsConsoleApp(aAppUi);
    aClearer = NULL;
    TInt screenMode = KErrNotFound;

    TInt configFlags = 0;
    aRepository.Get(KAknCompaModeSettings, configFlags);

    // Before CAknAppUi::BaseConstructL(), current screen mode is the
    // same as the application that starts the current application.
    TCompaAppCheckResult result =
        IsCompaModeAppL(aIsConsoleApp, configFlags, aAppUiFlags,
        aCoeEnv);
    if (result == ECompaCheckResultYes)
        {
        screenMode = FindCompaScreenMode();
        if (screenMode != KErrNotFound)
            {
            // Clear whole screen with a skin backround before
            // screen mode changes
            CAknCompaClearer* clearer = CAknCompaClearer::NewLC();

            SetAppScreenModeL(aAppUi, screenMode);
            aScrModeChanged = ETrue;
            CleanupStack::Pop(); // clearer
            aClearer = clearer; // transfer ownership
            }
        }
    else if (InGlobalUiSrv(aAppUiFlags))
        {
        // Current process is a server that may display global
        // notes/notifications. Return compa screen mode but don't
        // set it as current mode.
        screenMode = FindCompaScreenMode();
        }
    return screenMode;
    }

// --------------------------------------------------------------------------
// Find compatibility screen mode
// --------------------------------------------------------------------------
TInt AknCompaUtils::FindCompaScreenMode()
    {
    // Look for screen mode style name QVGACOMPA
    const TInt KNameHash = 0xA786E9F3;
    CAknLayoutConfig::TScreenModeArray scrModeArray =
        CAknSgcClient::LayoutConfig().ScreenModes();
    TInt nModes = scrModeArray.Count();
    TInt mode = KErrNotFound;
    for(TInt i = 0; i < nModes && mode == KErrNotFound; i++)
        {
        if (scrModeArray.At(i).ScreenStyleHash() == KNameHash)
            {
            mode = i;
            }
        }
    return mode;
    }

// --------------------------------------------------------------------------
// Check if process is a server that displays global
// notes/notifications (Eikon server, Avkon notify and cap servers)
// --------------------------------------------------------------------------
TBool AknCompaUtils::IsGlobalUiSrv(TSecureId aSecureId)
    {
    return IsAknCapSrv(aSecureId) ||
        aSecureId.iId == KCommonNotifierAppSrvUid.iUid ||
        IsEikSrv(aSecureId);
    }

// --------------------------------------------------------------------------
// Check if process is eikon server
// --------------------------------------------------------------------------
TBool AknCompaUtils::IsEikSrv(TSecureId aSecureId)
    {
    const TUid KEikSrvUid = {0x10003a4a};
    return aSecureId.iId == KEikSrvUid.iUid;
    }

// --------------------------------------------------------------------------
// Check if process is AknCap server
// --------------------------------------------------------------------------
TBool AknCompaUtils::IsAknCapSrv(TSecureId aSecureId)
    {
    return aSecureId.iId == KAknCapServerUid.iUid;
    }

// --------------------------------------------------------------------------
// Read and create buttons from a resource file
// --------------------------------------------------------------------------
void AknCompaUtils::ReadButtonsL(RPointerArray<CAknCompaButton>& aButtons,
    TInt& aPenButton, CCoeEnv& aCoeEnv)
    {
    RResourceFile resFile;
    AknCompaUtils::OpenResourceFileLC(resFile, aCoeEnv.FsSession());

    // Add localized text resource to CoeEnv
    TInt textResFileOffs = AddTextResourceFileL(aCoeEnv);

    // Read button resources
    HBufC8* buff = resFile.AllocReadLC(R_COMPAMODE_BUTTONS);
    TResourceReader reader;
    reader.SetBuffer(buff);   

    TInt buttonFlags(reader.ReadInt16());
    TInt numButtons(reader.ReadInt16());

    aPenButton = KErrNotFound;
    for(TInt i = 0; i < numButtons; i++)
        {
        // Create button
        CAknCompaButton* button = CAknCompaButton::NewLC(reader);

        if (button->ScanCode() != EStdKeyRightShift)
            {
            // Set flags for button
            button->SetButtonFlags(buttonFlags);
            }
        else
            {
            // Enable long press event for "pen" button
            button->SetButtonFlags(buttonFlags + KAknButtonReportOnLongPress);
            aPenButton = i;
            }

        aButtons.AppendL(button);

        CleanupStack::Pop(); // button
        }  

    aCoeEnv.DeleteResourceFile(textResFileOffs);

    CleanupStack::PopAndDestroy(2); // buff, resFile
    }

// --------------------------------------------------------------------------
// Open compamode resource file
// --------------------------------------------------------------------------
void AknCompaUtils::OpenResourceFileLC(RResourceFile& aResourceFile,
    RFs& aFsSession)
    {
    _LIT(KResourceFileName, "z:akncompamode.rsc");

    TParse parse;
    parse.Set(KResourceFileName, &KDC_RESOURCE_FILES_DIR, NULL);
    TFileName fileName(parse.FullName());
    aResourceFile.OpenL(aFsSession, fileName);

    CleanupClosePushL(aResourceFile);
    aResourceFile.ConfirmSignatureL();
    }

// --------------------------------------------------------------------------
// Add compamode localized text resource file into CoeEnv
// --------------------------------------------------------------------------
TInt AknCompaUtils::AddTextResourceFileL(CCoeEnv& aCoeEnv)
    {
    _LIT(KResourceFileName, "z:akncomparesources.rsc");

    TParse parse;
    parse.Set(KResourceFileName, &KDC_RESOURCE_FILES_DIR, NULL);
    TFileName fileName(parse.FullName());

    BaflUtils::NearestLanguageFile(aCoeEnv.FsSession(), fileName);
    return aCoeEnv.AddResourceFileL(fileName);
    }

// --------------------------------------------------------------------------
// Wait for effects to go into disabled state
// --------------------------------------------------------------------------
void AknCompaUtils::WaitTransEffectsOff(CRepository& aThemesCenRep)
    {
    const TInt KTick = 10000; // 10 ms
    const TInt KMaxWait = 100;

    // There could be a timing issue between CenRep variable change and
    // when tfx server actually disables the effects. Tested following loop
    // with a busy wait and there were no problems. So timing doesn't seem
    // to matter. It would be better of course if tfx server
    // would provide a feedback when effects actually are disabled.
    TInt effects;
    for(TInt i = 0; i < KMaxWait; i++)
        {
        aThemesCenRep.Get(KThemesTransitionEffects, effects);
        if (effects == KAknCompaModeEffectsDisabled)
            {
            return;
            }
        User::After(KTick);
        }
    }

// --------------------------------------------------------------------------
// Panic application
// --------------------------------------------------------------------------
void AknCompaUtils::Panic(TInt aCode)
    {
    _LIT(KCategory, "Compamode");
    User::Panic(KCategory, aCode);
    }

// --------------------------------------------------------------------------
// Scale rectangle to correct size and move it if necessary.
// --------------------------------------------------------------------------
void AknCompaUtils::ScaleRect(TRect& aRect, TInt aMoveX, TInt aMoveY)
    {    
    aRect.iTl.iY = (aRect.iTl.iY * 2);
    aRect.iBr.iY = (aRect.iBr.iY * 2);

    TInt bX = aRect.iBr.iX;
    TInt tmp = bX / 2;
    aRect.iBr.iX = ((bX * 2) - tmp);

    TInt tX = aRect.iTl.iX;
    tmp = tX / 2;
    aRect.iTl.iX = ((tX * 2) - tmp);
    
    if(aMoveX != 0 || aMoveY != 0)
        {
        aRect.Move(aMoveX, aMoveY);
        }
    }

// --------------------------------------------------------------------------
// Set application screen mode
// --------------------------------------------------------------------------
void AknCompaUtils::SetAppScreenModeL(CAknAppUiBase& aAppUi, TInt aMode)
    {
    TAknScreenModes scrModes = TAknScreenModes::GetModes();
    TAknScreenModes::SetAppUiScreenModeL(&aAppUi, scrModes[aMode]);
    }

// --------------------------------------------------------------------------
// Read a vector of integers from a resource file
// --------------------------------------------------------------------------
void AknCompaUtils::ReadIntegerResourceL(RArray<TInt>& aArray,
        const RResourceFile& aResourceFile, TInt aResId)
    {
    HBufC8* buff = aResourceFile.AllocReadLC(aResId);

    TResourceReader resReader;
    resReader.SetBuffer(buff);

    aArray.Reset();
    TInt cnt = resReader.ReadInt16();
    while(cnt--)
        {
        aArray.AppendL(resReader.ReadInt32());
        }
    CleanupStack::PopAndDestroy(); // buff
    }

// --------------------------------------------------------------------------
// Check if application requires a compatibility mode
// --------------------------------------------------------------------------
AknCompaUtils::TCompaAppCheckResult AknCompaUtils::IsCompaModeAppL(
    TBool aIsConsoleApp, TInt aConfigFlags, TInt aAppUiFlags,
    const CCoeEnv& aCoeEnv)
    {
    if ((aAppUiFlags & CAknAppUiBase::EAknTouchCompatible) ||
        (aAppUiFlags & CEikAppUi::ENoScreenFurniture && !aIsConsoleApp) ||
        (aConfigFlags & KAknCompaSettingEnaApps) == 0)
        {
        return ECompaCheckResultNo;
        }

    RResourceFile resFile;
    OpenResourceFileLC(resFile, aCoeEnv.FsSession());

    RProcess process;
    TSecureId secureId = process.SecureId();

    TCompaAppCheckResult appCheckResult = ECompaCheckResultUndefinite;

    RArray<TInt> array;
    CleanupClosePushL(array);
    // Application is not put into compa-mode if it is in non compa-mode list
    ReadIntegerResourceL(array, resFile, R_COMPAMODE_NON_COMPA_APPS);
    if (array.Find(secureId.iId) != KErrNotFound)
        {
        appCheckResult = ECompaCheckResultNo;
        }
    if (appCheckResult == ECompaCheckResultUndefinite)
        {
        // Application is put into compa-mode if it is in compa-mode list
        ReadIntegerResourceL(array, resFile, R_COMPAMODE_COMPA_APPS);
        if (array.Find(secureId.iId) != KErrNotFound)
            {
            appCheckResult = ECompaCheckResultYes;
            }
        }

    if (appCheckResult == ECompaCheckResultUndefinite)
        {
        // By default, all applications included in a rom image are
        // not put into compa-mode. Unless overriden by a flag or if
        // the app. is a console application.
        TFileName fileName = process.FileName();
        _LIT(KRomDrive,"z:");
        if (fileName.FindF(KRomDrive) == 0)
            {
            appCheckResult =
                aConfigFlags & KAknCompaSettingEnaRomApps || aIsConsoleApp ?
                ECompaCheckResultYes:ECompaCheckResultNo;
            }
        }

    if (appCheckResult == ECompaCheckResultUndefinite)
        {
        // Application is not executing from rom drive. Go to compa-mode.
        appCheckResult = ECompaCheckResultYes;
        }

    CleanupStack::PopAndDestroy(2); // resFile, array
    return appCheckResult;
    }

// --------------------------------------------------------------------------
// Check if current process is a server that displays global
// notes/notifications (Eikon server, Avkon notify and cap servers)
// --------------------------------------------------------------------------
TBool AknCompaUtils::InGlobalUiSrv(TInt aAppUiFlags)
    {
    // Optimization: don't check secure id if ENoScreenFurniture
    // flag not set.
    TBool inGlobalUiSrv = EFalse;
    if (aAppUiFlags & CEikAppUi::ENoScreenFurniture)
        {
        RProcess process;
        inGlobalUiSrv = IsGlobalUiSrv(process.SecureId());
        }
    return inGlobalUiSrv;
    }

// --------------------------------------------------------------------------
// Check if application is console application
// --------------------------------------------------------------------------
TBool AknCompaUtils::IsConsoleApp(CAknAppUiBase& aAppUi)
    {
    MConsoleApp* consoleApp;
    aAppUi.MopGetObjectNoChaining(consoleApp);
    return consoleApp != NULL;
    }
