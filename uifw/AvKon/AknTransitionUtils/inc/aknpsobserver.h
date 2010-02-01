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
* Description:  Transition utilities.
*
*/


#ifndef AKN_PS_OBSERVER_H
#define AKN_PS_OBSERVER_H

#include <e32base.h>
#include <e32property.h>
#include "akntransitionutils.h"

const TUid KTestCategoryUid = { 0x10281f87 };
const TUint KTfxClientKey =  0x12341234;
const TUint KTfxServerKey = 0x12341235;
const TUint KTfxServerCompFsKey = 0x12341236;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
NONSHARABLE_CLASS( CAknPsObserver ) : public CActive
    {
public:
    static CAknPsObserver* NewL( MAknPsObserver* aClient, const TUid aCategory, 
                                 const TUint aKey );
    static CAknPsObserver* New( MAknPsObserver* aClient, const TUid aCategory, 
                                const TUint aKey );
    ~CAknPsObserver();
    
    // From CActive
    virtual void DoCancel();
    virtual void RunL();
    
    TInt GetCurrentValue( TInt& aValue );
    
private:
    CAknPsObserver( MAknPsObserver* aClient, const TUid aCategory, 
                    const TUint aKey);
    void Construct( const TUid aCategory, const TUint aKey );

private: // data
    RProperty iProperty;
    MAknPsObserver* iClient;
    TUid iCategory;
    TUint iKey;
    };

#endif // AKN_PS_OBSERVER_H
