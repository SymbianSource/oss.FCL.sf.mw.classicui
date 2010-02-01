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
* Description:  Avkon discreet popup ui server handler.
*
*/

#ifndef C_AKNDISCREETPOPUPSERVERHANDLER_H
#define C_AKNDISCREETPOPUPSERVERHANDLER_H

#include <AknCapServerClient.h>
#include "akndiscreetpopupdata.h"

class MEikCommandObserver;
class CAknDiscreetPopup;
class CAknDiscreetPopupInfoHandler;
class CAknDiscreetPopupGlobalLauncher;

/**
 *  Akn Discreet Popup UI server handler.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknDiscreetPopupServerHandler ) : public CBase
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknDiscreetPopupServerHandler* NewL();

    /**
     * Two-phased constructor.
     */
    static CAknDiscreetPopupServerHandler* NewLC();

    /**
     * Destructor.
     */
    virtual ~CAknDiscreetPopupServerHandler();

    /**
     * Launches global discreet popup via cap server.
     * 
     * @param aTitle First line of text. 
     * @param aText Second line of text.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aFlags Popup flags.
     * @param aCommand Popup command id.
     * @param aPopupId Popup id.
     * @param aCommandObserver Popup command observer.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     * @param aPopupIdData Popupdata containing id for popup.
     */
    void LaunchGlobalPopupL(
            const TDesC& aTitle,
            const TDesC& aText,
            const TAknsItemID& aSkinId,
            const TDesC& aBitmapFile,
            const TInt& aBitmapId,
            const TInt& aMaskId,
            const TInt& aFlags,
            const TInt& aCommandId,
            const TInt& aPopupId,
            MEikCommandObserver* aCommandObserver,
            const TUid& aAppUid,
            const TUid& aViewUid );

    /**
     * Launches global discreet popup via cap server.
     * 
     * @param aResourceId Discreet popup resource id.
     * @param aResourceFile Discreet popup resource file path.
     * @param aCommand Popup command id.
     * @param aPopupId Popup id.
     * @param aCommandObserver Popup command observer.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     */
    void LaunchGlobalPopupL(
            const TInt aResourceId,
            const TDesC& aResourceFile,
            const TInt& aCommandId,
            const TInt& aPopupId,
            MEikCommandObserver* aCommandObserver,
            const TUid& aAppUid,
            const TUid& aViewUid );

    /**
     * Requests permission to launch local popup from cap server.
     * 
     * @param aDiscreetPopup Discreet popup instance requesting the permission.
     */
    void RequestForLocalLaunch( CAknDiscreetPopup* aDiscreetPopup );

    /**
     * Informs handler that ui server has closed a popup.
     * 
     * @param aLauncher Popup launcher.
     */
    void PopupClosed( CAknDiscreetPopupGlobalLauncher* aLauncher );

    /**
     * Checks if popup id is already in use among global popups.
     * 
     * @return Next available popup id.
     */
    TInt CheckPopupId( const TInt& aPopupId );

    /**
     * Provides access to uiserver.
     * 
     * @return Pointer to RAknUiServer.
     */
    RAknUiServer* UiServer();

private:
    
    /**
     * C++ constructor.
     */
    CAknDiscreetPopupServerHandler();

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Checks if popup id is already in use among global popups.
     * 
     * @return ETrue if popup id is already in use.
     */
    TBool PopupIdInUse( const TInt& aPopupId );

private: // data
    
    /**
     * Global popup launcher array.
     */
    RPointerArray<CAknDiscreetPopupGlobalLauncher> iLaunchers;

    /**
     * Cap server session.
     */
    RAknUiServer iUiServer;

    };

/**
 *  Akn Discreet Popup global launch handler.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknDiscreetPopupGlobalLauncher ) 
    : public CActive
    {

public:

    /**
     * Destructor.
     */
    virtual ~CAknDiscreetPopupGlobalLauncher();

    /**
     * Returns stored popup data.
     * 
     * @return Pointer to stored popup data instance.
     */
    virtual TAknDiscreetPopupData* PopupData() = 0;

    /**
     * Launches global discreet popup via cap server.
     */
    void LaunchDiscreetPopup();

// from base class CActive
    
    /**
     * Handles an active object's request completion event.
     */
    void RunL();

    /** 
     * Implements cancellation of an outstanding request.
     */
    void DoCancel();

protected:

    /**
     * C++ constructor.
     * 
     * @param aHandler Popup server handler.
     * @param aObserver Command observer.
     * @param aCommandId Command id.
     */
    CAknDiscreetPopupGlobalLauncher(
            CAknDiscreetPopupServerHandler* aHandler, 
            MEikCommandObserver* aObserver,
            const TInt& aCommandId );

    /**
     * 2-phase constructor.
     */
    void ConstructL();

    /**
     * Renews the request.
     */
    void RenewRequest();

private: // data
    
    /**
     * Popup command observer.
     * Not own.
     */
    MEikCommandObserver* iCommandObserver;

    /**
     * Popup command id.
     */
    TInt iCommandId;

    /**
     * Pointer to server handler.
     * Not own.
     */
    CAknDiscreetPopupServerHandler* iHandler;

    };

/**
 *  Akn Discreet Popup global param launch handler.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknDiscreetPopupGlobalParamLauncher ) : public CAknDiscreetPopupGlobalLauncher
    {

public:

    /**
     * Two-phased constructor.
     *
     * @param aHandler Popup server handler.
     * @param aObserver Command observer.
     * @param aCommandId Command id.
     */
    static CAknDiscreetPopupGlobalParamLauncher* NewL(
            CAknDiscreetPopupServerHandler* aHandler, 
            MEikCommandObserver* aObserver,
            const TInt& aCommandId,
            const TInt& aPopupId,
            const TUid& aAppUid,
            const TUid& aViewUid );

    /**
     * Destructor.
     */
    virtual ~CAknDiscreetPopupGlobalParamLauncher();
    
    /**
     * Sets launcher data.
     * 
     * @param aTitle First line of text. 
     * @param aText Second line of text.
     * @param aSkinId Icon skin item id.
     * @param aBitmapFile Icon bitmap file.
     * @param aBitmapId Icon bitmap id.
     * @param aMaskId Icon mask id.
     * @param aFlags Popup flags.
     * @param aCommand Popup command id.
     * @param aCommandObserver Popup command observer.
     */
    void SetData(
            const TDesC& aTitle,
            const TDesC& aText,
            const TAknsItemID& aSkinId,
            const TDesC& aBitmapFile,
            const TInt& aBitmapId,
            const TInt& aMaskId,
            const TInt& aFlags );

private:

    /**
     * C++ constructor.
     *
     * @param aHandler Popup server handler.
     * @param aObserver Command observer.
     * @param aCommandId Command id.
     * @param aPopupId Popup id.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     */
    CAknDiscreetPopupGlobalParamLauncher(
            CAknDiscreetPopupServerHandler* aHandler,
            MEikCommandObserver* aObserver,
            const TInt& aCommandId,
            const TInt& aPopupId,
            const TUid& aAppUid,
            const TUid& aViewUid );

    /**
     * Returns stored popup data.
     * 
     * @return Pointer to stored popup data instance.
     */
    TAknDiscreetPopupData* PopupData();

private: // data
    
    /**
     * Popup data.
     */
    TAknDiscreetPopupParamData iPopupData;
    
    };

/**
 *  Akn Discreet Popup global resource launch handler.
 *
 *  @lib avkon
 *  @since S60 v5.2
 */
NONSHARABLE_CLASS( CAknDiscreetPopupGlobalResourceLauncher ) : 
    public CAknDiscreetPopupGlobalLauncher
    {

public:
    
    /**
     * Two-phased constructor.
     *
     * @param aHandler Popup server handler.
     * @param aObserver Command observer.
     * @param aCommandId Command id.
     * @param aPopupId Popup id.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     */
    static CAknDiscreetPopupGlobalResourceLauncher* NewL(
            CAknDiscreetPopupServerHandler* aHandler, 
            MEikCommandObserver* aObserver,
            const TInt& aCommandId,
            const TInt& aPopupId,
            const TUid& aAppUid,
            const TUid& aViewUid );

    /**
     * Destructor.
     */
    virtual ~CAknDiscreetPopupGlobalResourceLauncher();
    
    /**
     * Sets launcher data.
     * 
     * @param aResourceId Discreet popup resource id.
     * @param aResourceFile Discreet popup resource file path.
     */
    void SetData(
            const TInt aResourceId,
            const TDesC& aResourceFile );

private:

    /**
     * C++ constructor.
     *
     * @param aHandler Popup server handler.
     * @param aObserver Command observer.
     * @param aCommandId Command id.
     * @param aPopupId Popup id.
     * @param aAppUid Application uid to be launched.
     * @param aViewUid Application view uid to be activated.
     */
    CAknDiscreetPopupGlobalResourceLauncher(
            CAknDiscreetPopupServerHandler* aHandler,
            MEikCommandObserver* aObserver,
            const TInt& aCommandId,
            const TInt& aPopupId,
            const TUid& aAppUid,
            const TUid& aViewUid );

    /**
     * Returns stored popup data.
     * 
     * @return Pointer to stored popup data instance.
     */
    TAknDiscreetPopupData* PopupData();

private: // data
    
    /**
     * Popup data.
     */
    TAknDiscreetPopupResourceData iPopupData;
    
    };

#endif // C_AKNDISCREETPOPUPSERVERHANDLER_H
