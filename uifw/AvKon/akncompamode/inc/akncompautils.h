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


#ifndef __AKNCOMPAUTILS_H__
#define __AKNCOMPAUTILS_H__

#include <e32base.h>
#include <f32file.h>
#include <barsc.h>

class CAknCompaButton;
class CAknAppUiBase;
class CCoeEnv;
class CAknCompaClearer;
class CRepository;

/**
 * Compatibility mode utility class
 *
 * Static functions to used by compatility mode
 *
 * @lib compamode.lib
 * @since S60 v5.0
 */
NONSHARABLE_CLASS(AknCompaUtils)
    {
public: // types
    enum
        {
        EQvgaWidth = 240,
        EQvgaHeight = 320,
        EQhdWidth = 360,
        EQhdHeight = 640
        };

    enum TCompaAppCheckResult
        {
        ECompaCheckResultNo,  // not a "compa mode" application
        ECompaCheckResultYes, // "compa mode" application
        ECompaCheckResultUndefinite // unsure whether compa mode is needed
        };

    enum TCompaModePanics
        {
        EButtonCount
        };

public: // functions

    static TInt SetCompaAppScreenModeL(TBool& aScrModeChanged,
        TBool& aIsConsoleApp, CAknCompaClearer*& aClearer,
        TInt aAppUiFlags, CAknAppUiBase& aAppUi,
        const CCoeEnv& aCoeEnv, CRepository& aRepository);

    static TInt FindCompaScreenMode();
    
    static TBool IsGlobalUiSrv(TSecureId aSecureId);
    static TBool IsEikSrv(TSecureId aSecureId);
    static TBool IsAknCapSrv(TSecureId aSecureId);

    static void AknCompaUtils::ReadButtonsL(
        RPointerArray<CAknCompaButton>& aButtons, TInt& aPenButton,
        CCoeEnv& aCoeEnv);

    static void OpenResourceFileLC(RResourceFile& aResourceFile,
        RFs& aFsSession);

    static TInt AddTextResourceFileL(CCoeEnv& aCoeEnv);

    static void WaitTransEffectsOff(CRepository& aThemesCenRep);

    static void Panic(TInt aCode);

    static void ScaleRect(TRect& aRect, TInt aMoveX, TInt aMoveY);
    
private: // functions

    static void SetAppScreenModeL(CAknAppUiBase& aAppUi, TInt aMode);
    
    static void ReadIntegerResourceL(RArray<TInt>& aArray,
        const RResourceFile& aResourceFile, TInt aResId);

    static TCompaAppCheckResult IsCompaModeAppL(TBool aIsConsoleApp,
        TInt aConfigFlags, TInt aAppUiFlags, const CCoeEnv& aCoeEnv);

    static TBool InGlobalUiSrv(TInt aAppUiFlags);

    static TBool IsConsoleApp(CAknAppUiBase& aAppUi);
    };

#endif // __AKNCOMPAUTILS_H__
