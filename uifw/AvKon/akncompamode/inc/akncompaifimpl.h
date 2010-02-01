/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Compa-mode interface ecom implementation
*
*/


#ifndef __AKNCOMPAIFIMPL_H__
#define __AKNCOMPAIFIMPL_H__

#include <e32base.h>

#include "akncompaif.h"

class CCoeEnv;
class CAknAppUiBase;
class CAknCompaKb;
class CAknCompaClearer;
class CRepository;

/**
 * Compa-mode ECOM interface implementation
 *
 * @lib compamode.lib
 * @since S60 v5.0
 */
NONSHARABLE_CLASS(CAknCompaIfImpl) : public CAknCompaIf
    {
public: // constructors and destructor

    static CAknCompaIfImpl* NewL();

    ~CAknCompaIfImpl();

public: // from CAknCompaIf

    TInt SetCompaAppScreenModeL(TBool& aScrModeChanged, TBool& aIsConsoleApp,
        TInt aAppUiFlags, CAknAppUiBase& aAppUi, const CCoeEnv& aCoeEnv,
        CRepository& aRepository);

    void CreateKbL(TInt aCompaScreenMode, TBool aMakeVisible);

    TInt IsForeground();

    TInt FindCompaScreenMode();

    void DisableTransEffects(TBool aDisable);

private: // data

    CAknCompaKb* iCompaKb;
    CAknCompaClearer* iClearer;
    };

#endif // __AKNCOMPAIFIMPL_H__
