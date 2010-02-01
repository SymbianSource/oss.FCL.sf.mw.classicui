/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test akntransparentcamerasettingpage.h
*
*/



#ifndef C_TESTDOMSETPAGEEXT_H
#define C_TESTDOMSETPAGEEXT_H


// forward declarations
class CAknTransparentCameraSettingPage;

// class declaration

class CAknTransparentCameraSettingPageExt : public CAknTransparentCameraSettingPage
    {

public:

    /**
     * C++ default constructor
     */ 
    CAknTransparentCameraSettingPageExt( TInt aResourceID, 
                                         TInt& aCurrentSelectionIndex, 
                                         const MDesCArray* aItemArray );

public: // test protected functions of CAknTransparentCameraSettingPage

    /**
    * Called when the external setting is to be updated
    * @since 2.6
    */
    virtual void DoUpdateSettingL();

    /**
    * Called immediately prior to activation, but after all construction
    * @since 2.6
    */
    void DoDynamicInitL();

    /**
     * This method overrides the default implementation in order to do the special 
     * processing of selecting an item
     *
     * @since 2.6
     */
    virtual void DoSelectCurrentItemL();

//From MCoeControlObserver

    /**
    * Acts upon changes in the hosted control's state. 
    *
    * @param    aControl    The control changing its state (not used)
    * @param    aEventType  The type of control event 
    * @since 5.0
    */
    void DoHandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

//From MEikCommandObserver

    /**
    * Processes events from the softkeys. Responds to EAknSoftkeyOk and EAknSoftkeyBack
    * to accept or cancel the pop-up.
    *
    * @param    aCommandId  Event Id from the soft-key
    * @since 5.0
    */
    void DoProcessCommandL( TInt aCommandId );

    /**
     * Writes the internal state of the control and its components to aStream.
     * Does nothing in release mode.
     * Designed to be overidden and base called by subclasses.
     *
     * @param   aWriteSteam     A connected write stream
     * @since 2.6
     */ 
    virtual void DoWriteInternalStateL( RWriteStream& aWriteStream ) const;

    /**
    * Handles the size change events.
    * @since 2.6
    */
    virtual void DoSizeChanged();

    /** 
    * Draws the setting page on top of the camera view 
    *
    * @param aRect  rectangle within which to draw
    * @since 2.6
    */
    void DoDraw( const TRect& aRect ) const;

    };


#endif // C_TESTDOMSETPAGEEXT_H
