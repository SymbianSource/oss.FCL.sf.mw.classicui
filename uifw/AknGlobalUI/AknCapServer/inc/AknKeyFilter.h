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
* Description:  Translates key events for different UI related situations.
*
*/

#ifndef __AKN_KEY_FILTER__
#define __AKN_KEY_FILTER__

#include <coecntrl.h>
#ifdef RD_INTELLIGENT_TEXT_INPUT
#include <centralrepository.h>
#endif
#include "AknCapServerEntry.h"

const TInt KHomeHoldDelay = 600000;   // 0.6 sec

class CAknServKeyFilter : public CCoeControl
    {
public:
    CAknServKeyFilter();
    void ConstructL(CAknCapAppServerAppUi& aAppUi);
    ~CAknServKeyFilter();
    
private: // framework
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    
private: // new functions
    TKeyResponse HandleQwertyKeyEvent(const TKeyEvent& aKeyEvent, TEventCode aType);
    void HandleFlipKeyEvent(TInt aCode);
    static TInt HomeTickL(TAny* aThis);
    void DoHomeTickL();
    void ToggleShellL();
    void ActivateViewL( const TVwsViewId& aViewId, TUid aCustomMessageId );
    void CaptureHardwareStateKeysL();
    void InitHardwareStateL();
    TBool HandleHardwareStateKeyL(TInt aCode);
    void FreeHardwareStateKeys();
    void SetHardwareStateL(TInt aState);
#ifdef RD_INTELLIGENT_TEXT_INPUT
    TInt CAknServKeyFilter::HwKeyToKeyBoardType(TInt aKeyCode);
#endif

private:
    CAknCapAppServerAppUi* iAppUi; // not owned
    CPeriodic* iHomeTimer;
    TInt iSuppressAppSwitch;
    TVwsViewId iHomeViewId;
    RArray<TInt32> iHardwareStateKeyCaptures;
    TInt iQwertyOnKeyHandle;
    TInt iQwertyOffKeyHandle;
    TInt iFlipOpenKeyHandle;
    TInt iFlipCloseKeyHandle;
#ifdef RD_INTELLIGENT_TEXT_INPUT
    CRepository* iAvkonRepository;
#endif
    };

#endif // __AKN_KEY_FILTER__
