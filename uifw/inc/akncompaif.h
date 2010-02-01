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
* Description:  Compa-mode interface (client) declaration
*
*/


#ifndef __AKNCOMPAIF_H__
#define __AKNCOMPAIF_H__

#include <e32base.h>
#include <coemop.h>

class CCoeEnv;
class CAknAppUiBase;
class CAknCompaKb;
class CRepository;

/**
 * Compa-mode ECOM interface
 *
 * The component is used by CAknAppUiBase to set screen mode
 * and create compa keyboard
 *
 * @lib compamode.lib
 * @since S60 v5.0
 */
class CAknCompaIf : public CBase
    {
public: // constants
    DECLARE_TYPE_ID(0x20010125) // AKNCOMPAIF_ECOM_IF_UID

public: // constructors and destructor

    static CAknCompaIf* NewL();

    ~CAknCompaIf();

public: // functions

    static TBool IsNeeded(TInt aAppUiFlags, CRepository* aRepository);

    virtual TInt SetCompaAppScreenModeL(TBool& aScrModeChanged,
        TBool& aIsConsoleApp, TInt aAppUiFlags, CAknAppUiBase& aAppUi,
        const CCoeEnv& aCoeEnv, CRepository& aRepository) = 0 ;

    virtual void CreateKbL(TInt aCompaScreenMode, TBool aMakeVisible) = 0;

    virtual TBool IsForeground() = 0;

    virtual TInt FindCompaScreenMode() = 0;

    virtual void DisableTransEffects(TBool aDisable) = 0;

private: // data
    TUid iEcomDtorId;
    };

#include "akncompaif.inl"

#endif // __AKNCOMPAIF_H__
