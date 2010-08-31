/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __AKNNOTIFYPLUGIN_H__
#define __AKNNOTIFYPLUGIN_H__

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <AknSignal.h>
#include <AknBattery.h>
#include <AknIndicatorContainer.h>
#include <AknNotifyStd.h>
#include <AknPanic.h>
#include <MediatorEventProvider.h>
#include <MediatorDomainUIDs.h>
#include <AknNotifyStd.h>
#include <SecondaryDisplay/AknSecondaryDisplayDefs.h>

class CAknIndicatorData;

IMPORT_C CArrayPtr<MEikSrvNotifierBase2>* NotifierArray();
GLDEF_C void Panic(TAknPanic aPanic);

const TInt KAknBatteryNoCharging = -1;

class MNotificationObserver
    {
public:
    virtual void NotificationSelected(TInt aIndex) = 0;
    virtual void NotificationCancelled(void) = 0;
    };

enum TNotificationSelection
    {
    EUngroupedNotifierSelected = 1,
    EGroupedSMSSelected,
    EGroupedCallSelected,
    EGroupedEmailSelected
    };

NONSHARABLE_CLASS(CAknMediatorEvent) : public CBase
    {
public:
    ~CAknMediatorEvent()
        {
        if (iImpl)
            {
            for (TInt i = iArray.Count()-1; i >= 0; i--)
                {
                iImpl->UnregisterEvent(
                    KMediatorSecondaryDisplayDomain,
                    KAknSecondaryDisplayCategory, 
                    iArray[i]
                    );
                }
            }
        iArray.Close();
        delete iImpl;        
        }
        
    void RaiseEvent(TInt aId, const TDesC8& aBuf);
    CMediatorEventProvider* iImpl;
    RArray<TInt> iArray;
    };

NONSHARABLE_CLASS(CAknPopupNotifierSubject) : public CBase, public MAknUINotifierBase
    {
public:
    static CAknPopupNotifierSubject* NewL();
    void Release();
    TNotifierInfo RegisterL();
    TNotifierInfo Info() const;
    TPtrC8 StartL(const TDesC8& aBuffer);
    void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    void Cancel();
    TPtrC8 UpdateL(const TDesC8& aBuffer);

private:
    CAknPopupNotifierSubject();
    void ConstructL();
    void PopupL(const TDesC8& aBuffer);

private:
    TNotifierInfo iInfo;
    };


NONSHARABLE_CLASS(CAknSignalNotifierSubject) : public CBase, public MAknUINotifierBase
    {
public:
    static CAknSignalNotifierSubject* NewL(CAknMediatorEvent* aEvent);
    ~CAknSignalNotifierSubject();
    void Release();
    TNotifierInfo RegisterL();
    TNotifierInfo Info() const;
    TPtrC8 StartL(const TDesC8& aBuffer);
    void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    void Cancel();
    TPtrC8 UpdateL(const TDesC8& aBuffer);

private:
    CAknSignalNotifierSubject();
    void ConstructL();
    void HandleSignalMessageL(const TDesC8& aBuffer);

private:
    TNotifierInfo iInfo;
    
public: 
    CAknMediatorEvent* iEvent; // not owned
    };


NONSHARABLE_CLASS(CAknBatteryNotifierSubject) : public CBase, public MAknUINotifierBase
    {
public:
    static CAknBatteryNotifierSubject* NewL(CAknMediatorEvent* aEvent);
    ~CAknBatteryNotifierSubject();
    void Release();
    TNotifierInfo RegisterL();
    TNotifierInfo Info() const;
    TPtrC8 StartL(const TDesC8& aBuffer);
    void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    void Cancel();
    TPtrC8 UpdateL(const TDesC8& aBuffer);

private:
    CAknBatteryNotifierSubject();
    void ConstructL();
    void HandleBatteryMessageL(const TDesC8& aBuffer);
    static TInt TickerCallback(TAny* aThis);
    TInt DoTick();

private:
    TNotifierInfo iInfo;
    
public:
    CAknMediatorEvent* iEvent; // not owned
    };


NONSHARABLE_CLASS(CAknSmallIndicatorSubject) : public CBase, public MAknUINotifierBase
    {
public:
    static CAknSmallIndicatorSubject* NewL(CAknMediatorEvent* aEvent);
    ~CAknSmallIndicatorSubject();
    void Release();
    TNotifierInfo RegisterL();
    TNotifierInfo Info() const;
    TPtrC8 StartL(const TDesC8& aBuffer);
    void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    void Cancel();
    TPtrC8 UpdateL(const TDesC8& aBuffer);

private:
    CAknSmallIndicatorSubject();
    void ConstructL();
    void HandleIndicatorMessageL(const TDesC8& aBuffer);

private:
    TNotifierInfo iInfo;
    TBool iState;
    CAknIndicatorData* iIndicatorSDData;

public: 
    CAknMediatorEvent* iEvent; // onws
    };


NONSHARABLE_CLASS(CAknIncallBubbleSubject) : public CBase, public MAknUINotifierBase
    {
public:
    static CAknIncallBubbleSubject* NewL();
    void Release();
    TNotifierInfo RegisterL();
    TNotifierInfo Info() const;
    TPtrC8 StartL(const TDesC8& aBuffer);
    void StartL(const TDesC8& aBuffer, TInt aReplySlot, const RMessagePtr2& aMessage);
    void Cancel();
    TPtrC8 UpdateL(const TDesC8& aBuffer);

private:
    CAknIncallBubbleSubject();
    void ConstructL();
    void HandleIndicatorMessageL(const TDesC8& aBuffer , const TUint64& aClientId );

private:
    TNotifierInfo iInfo;
    TBool iState;
    };

#endif // __AKNNOTIFYPLUGIN_H__

// End of File
