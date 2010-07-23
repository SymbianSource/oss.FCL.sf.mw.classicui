/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test application_framework_api
*
*/



#ifndef C_TESTSDKAPPFWVIEW_H
#define C_TESTSDKAPPFWVIEW_H

//  INCLUDES
#include "testsdkappfw.h"

/**
*  CTestSDKAppFWAppUi test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKAppFWView ) : public CAknView
    {
public:

    /**
    * Two-phased constructor.
    */
    static CTestSDKAppFWView* NewL();

    /**
     * Constructor.
     */
    CTestSDKAppFWView();

    /**
     * Destructor.
     */
    virtual ~CTestSDKAppFWView();

    /**
     * symbian 2nd constructor
     */
    void ConstructL();

    /**
    * Returns views id, intended for overriding by sub classes.
    * @return id for this view.
    */
    TUid Id() const;

    /** 
     * Handles a view activation and passes the message of type 
     * @c aCustomMessageId. This function is intended for overriding by 
     * sub classes. This function is called by @c AknViewActivatedL().
     * Views should not launch waiting or modal notes or dialogs in
     * @c DoActivateL.
     * @param aPrevViewId Specifies the view previously active.
     * @param aCustomMessageId Specifies the message type.
     * @param aCustomMessage The activation message.
     */
    void DoActivateL( const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
        const TDesC8& aCustomMessage );

    /** 
     * View deactivation function intended for overriding by sub classes. 
     * This function is called by @c AknViewDeactivated().
     */
    void DoDeactivate();

    /** 
     * Accessor for the applications user interface as a @c CAknViewAppUi.
     * @return Pointer to user interface instance.
     */
    CAknViewAppUi* ProtectedAppUi() const;

    /** 
     * Status pane accessor method.
     * @return Pointer to status pane. 
     */
    CEikStatusPane* ProtectedStatusPane() const;

    /** 
     * Button group container (=CBA) accessor method. 
     * This returns the views CBA if there is one, and the applications user 
     * interfaces CBA otherwise.
     * @return Pointer to @c CEikButtonGroupContainer.
     */
    CEikButtonGroupContainer* ProtectedCba() const;

    /** 
     * From @c MCoeView. Takes any action required when this view is activated.
     * Handles this view activation event from view server. Calls 
     * @c CAknViewAppUi::ViewActivatedL()
     * @param aPrevViewId Specifies the view previously active.
     * @param aCustomMessageId Specifies the message type.
     * @param aCustomMessage Activation message.
     */
    void ProtectedViewActivatedL( const TVwsViewId& aPrevViewId,
        TUid aCustomMessageId, const TDesC8& aCustomMessage );

    /** 
     * From @c MCoeView. Takes any action that is required following 
     * deactivation of this view. Handles this view deactivation event from
     * viewserver. Calls @c CAknViewAppUi::ViewDeactivated()
     */
    void ProtectedViewDeactivated();

    /** 
     * From @c MCoeView. Screen device changed function from viewserver.
     * @return TVwsViewIdAndMessage created with default values.
     */
    TVwsViewIdAndMessage ProtectedViewScreenDeviceChangedL();

    /** 
     * From @c MObjectProvider. Gets an (@c MAknsControlContext) object whose 
     * type is encapsulated by the specified TTypeUid object. Calls 
     * @c SupplyMopObject( @c TTypeUid aId, 
     *      @c CEikButtonGroupContainer* iCba, @c CEikMenuBar* iMenu ). 
     * @param aId Encapsulates the @c Uid that identifies the type of object 
     *         required. 
     * @return Pointer to the @c MAknsControlContext object provided. Note that
     *          the pointer may be @c NULL. 
     */
    TTypeUid::Ptr ProtectedMopSupplyObject( TTypeUid aId );

    /** 
     * From @c MObjectProvider. Gets the parent object provider.   
     * @return Pointer to the parent object provider (@c MObjectProvider) that
     *          is @c CAknViewAppUi* iAppUi, or @c NULL.
     */
    MObjectProvider* ProtectedMopNext();

    /** 
     * From @c MEikMenuObserver. Menu emphasising or de-emphasising function. 
     * @c CEikMenuBar objects call this on their observer. Updates the value of
     * the flags for the (@c aMenuControl) on the control stack. 
     * @param aMenuControl The control to be emphasised or de-emphasisied.
     * @param aEmphasis @c ETrue to emphasize the menu, @c EFalse to refuse the
     *          focus.
     */
    void ProtectedSetEmphasis( CCoeControl* aMenuControl, TBool aEmphasis );

    /** 
     * From @c MEikMenuObserver. Foreground event handling function intended 
     * for overriding by sub classes.  
     * @param aForeground Indicates the required focus state of the control.
     */ 
    void ProtectedHandleForegroundEventL( TBool aForeground );

    };

#endif      // C_TESTSDKAPPFWVIEW_H

// End of File
