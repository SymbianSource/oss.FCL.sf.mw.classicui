/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     
*
*/


#ifndef HGKEYUTILS_H_
#define HGKEYUTILS_H_

#include <e32base.h>
#include <w32std.h>
#include <e32property.h>
#include <featmgr.h>
#include <centralrepository.h>
#include <cenrepnotifyhandler.h>
#include <AknFepInternalCRKeys.h> // KAknFepHashKeySelection
#include <AvkonInternalCRKeys.h>  // KAknQwertyInputModeActive
#include <eikcmobs.h>
#include <coedef.h>

// Forward declarations
class CPeriodic;
struct TKeyEvent;
class CHgScroller;
class CEikButtonGroupContainer;
class CCoeControl;
class CEikCba;

NONSHARABLE_CLASS( CHgKeyUtils ) : 
    public CBase, 
    public MCenRepNotifyHandlerCallback,
    public MEikCommandObserver
    {
public:
    static CHgKeyUtils* NewL( CHgScroller& aScroller );
    
    virtual ~CHgKeyUtils();

    void HandleLosingFocus();
    void HandleGainingFocus();
    
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
        
public: // from MCenRepNotifyHandlerCallback
    
    void HandleNotifyInt(TUint32 aId, TInt aNewValue);
    
private:
    CHgKeyUtils( CHgScroller& aScroller );
    
    void ConstructL();

    void UpdateMSKVars();
    
    TBool SelectionMode( const TKeyEvent& aKeyEvent );
    
    void ProcessCommandL(TInt aCommandId);

    void CreateMSKObserver();
    
    void RemoveMSKObserver();    
        
private:

    CHgScroller& iScroller; // Not Own.
    CRepository* iCenRep; // Own.
    CCenRepNotifyHandler* iCenRepNotifyHandler; // Own.      
    CEikCba* iCba; // Not own
    
    TBool iSelectionModeEnabled;    
    TBool iAknFepHashKeySelection;
    TBool iShiftKeyPressed;
    TBool iMskEnabledInPlatform;
    TBool iMSKButtonGroupAlive; // status of buttongroup, which is used for MSK observer

    };

#endif // HGKEYUTILS_H_
