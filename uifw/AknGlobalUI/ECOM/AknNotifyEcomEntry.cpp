/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Creates Avkon old style notifier wrappers.
*
*/

// INCLUDE FILES
#include <uikon/eiksrvui.h> 
#include <AknNotifierWrapper.h>
#include <ecom/implementationproxy.h>
#include <eiknotapi.h>
#include <AknNotifierControllerPlugin.h>

#include <AknNotifyStd.h>
#include <eikenv.h>
#include <eikspane.h>
#include <avkon.hrh>
#include <eikspane.h>
#include <aknappui.h>

#include <bautils.h> // For NearestLanguageFile
#include <aknnotpi.rsg>

#include <AknNotifySignature.h>
#include <AknNotifierControllerPlugin.h>
#include <AknCapServerDefs.h> 

const TInt KReplyBufSize = 200;
const TInt KArrayGranularity = 3;

// All our notifiers are derived from CBase so safe.
void CleanupArray(TAny* aArray)
    {
    CArrayPtrFlat<MEikSrvNotifierBase2>* subjects = 
        static_cast<CArrayPtrFlat<MEikSrvNotifierBase2>*>(aArray);
        
    subjects->ResetAndDestroy();
    delete subjects;
    }

CArrayPtr<MEikSrvNotifierBase2>* DoCreateNotifierArrayL()
    {
    CArrayPtrFlat<MEikSrvNotifierBase2>* subjects = 
        new (ELeave) CArrayPtrFlat<MEikSrvNotifierBase2>(KArrayGranularity);
        
    CleanupStack::PushL(TCleanupItem(CleanupArray, subjects));

    // -------------------------------------------------------------------------
    // Create master wrapper. 
    // -------------------------------------------------------------------------
    CAknNotifierWrapper* master = CAknNotifierWrapper::NewL( 
        KAknKeyLockNotifierUid,
        KAknKeyLockNotifierUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh,
        KAknCapServerUid,
        KReplyBufSize);

    CleanupStack::PushL(master);
    subjects->AppendL(master);
    CleanupStack::Pop(master);
    
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light1 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknPopupNotifierUid,
        KAknPopupNotifierUid,
        MEikSrvNotifierBase2::ENotifierPriorityLow);

    CleanupStack::PushL(light1);
    subjects->AppendL(light1);
    CleanupStack::Pop(light1);

    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light2 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknSignalNotifierUid,
        KAknSignalNotifierUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light2);
    subjects->AppendL(light2);
    CleanupStack::Pop(light2);
        
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light3 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknBatteryNotifierUid,
        KAknBatteryNotifierUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light3);
    subjects->AppendL(light3);
    CleanupStack::Pop(light3);        
        
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light4 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknSmallIndicatorUid,
        KAknSmallIndicatorUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light4);
    subjects->AppendL(light4);
    CleanupStack::Pop(light4);        
    
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light5 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknGlobalNoteUid,
        KAknGlobalNoteUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light5);
    subjects->AppendL(light5);
    CleanupStack::Pop(light5);        
    
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light6 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknSoftNotificationUid,
        KAknSoftNotificationUid, // Separate channel from global notes, new in S60 3.0.
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);

    CleanupStack::PushL(light6);
    subjects->AppendL(light6);
    CleanupStack::Pop(light6);        

    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light7 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknIncallBubbleUid,
        KAknIncallBubbleUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light7);
    subjects->AppendL(light7);
    CleanupStack::Pop(light7);        

    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light8 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknGlobalListQueryUid,
        KAknGlobalListQueryUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light8);
    subjects->AppendL(light8);
    CleanupStack::Pop(light8);        
    
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light9 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknGlobalMsgQueryUid,
        KAknGlobalMsgQueryUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light9);
    subjects->AppendL(light9);
    CleanupStack::Pop(light9);        
    
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light10 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknGlobalConfirmationQueryUid,
        KAknGlobalConfirmationQueryUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light10);
    subjects->AppendL(light10);
    CleanupStack::Pop(light10);        
    
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light11 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknGlobalProgressDialogUid,
        KAknGlobalProgressDialogUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light11);
    subjects->AppendL(light11);
    CleanupStack::Pop(light11);        
    
    // -------------------------------------------------------------------------
    // Notifiers using master's session.
    // -------------------------------------------------------------------------
    CAknNotifierWrapperLight* light12 = new (ELeave) CAknNotifierWrapperLight(
        *master, 
        KAknGlobalListMsgQueryUid,
        KAknGlobalListMsgQueryUid,
        MEikSrvNotifierBase2::ENotifierPriorityVHigh);
        
    CleanupStack::PushL(light12);
    subjects->AppendL(light12);
    CleanupStack::Pop(light12);        

    CleanupStack::Pop(subjects);
    return subjects;
    }

CArrayPtr<MEikSrvNotifierBase2>* NotifierArray()
    {
    CArrayPtr<MEikSrvNotifierBase2>* subjects = NULL;
    TRAP_IGNORE(subjects = DoCreateNotifierArrayL());
    return subjects;
    }

const TImplementationProxy ImplementationTable[] =
    {
#ifdef __EABI__
    {{0x1020721A},(TFuncPtr)NotifierArray}
#else
    {{0x1020721A},NotifierArray}
#endif
    };

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }
