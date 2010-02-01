/*
* Copyright (c) 2003-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This class is additional notifier class for signal notifier
*                and is used together with CAknSignalNotify.
*
*/

#ifndef __AKNSIGNALNOTIFYADDITION_H__
#define __AKNSIGNALNOTIFYADDITION_H__

#include <e32base.h>

NONSHARABLE_CLASS(CAknSignalNotifyAddition) : public CBase
    {
    // Allow navipane to set background type. 
    friend class CAknNavigationControlContainer;

public:

protected:
    CAknSignalNotifyAddition();
    void ConstructL();
    void UpdateL(const TDesC8& aBuffer,TDes8& aResponse);
    
private:
    IMPORT_C ~CAknSignalNotifyAddition();
    IMPORT_C static CAknSignalNotifyAddition* NewL();
    IMPORT_C static CAknSignalNotifyAddition* NewLC();
    IMPORT_C void Connect();
    
    /**
     * This method is used to notify signal pane
     * about the current naviwipe background in navipane. This notifier 
     * does not attempt to start or stop the notifier, it assumes
     * that notifier is already set running by the CAknSignalNotify.
     * If not notifier is not running, then this method leaves.
     *
     * Available backgroud types are:
     *      EAknNaviPaneBackgroundTypeNotDefined  
     *      EAknNaviPaneBackgroundTypeWipe        
     *      EAknNaviPaneBackgroundTypeSolid       
     *
     * @param aType Background type.
     * @since 2.1
     */
    IMPORT_C void SetNaviPaneBackgroundTypeL(TInt aType);

private:
    RNotifier iNotify;
    TInt iConnected;
    TInt iSpare1;
    };

#endif // __AKNSIGNALNOTIFYADDITION_H__
