/*
* Copyright (c) 2005, 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  The interface of the info pop-up note
*
*/


// ------------------------------------------------------------------------
// How to use this info popup component (basic case):
//
//
//  #include <AknInfoPopupNote.h>
//  CAknInfoPopupNoteController* iPopupController;
//  ...
//  iPopupController = CAknInfoPopupNoteController::NewL();
//  ...
//  iPopupController->SetTextL( strTestText );
//  iPopupController->ShowInfoPopupNote();
//  ...
//  delete iPopupController;
// ------------------------------------------------------------------------


#ifndef CAKNINFOPOPUPNOTECONTROLLER_H
#define CAKNINFOPOPUPNOTECONTROLLER_H

//  INCLUDES
#include <e32base.h>
#include <gulalign.h>
#include "avkon.hrh"

// FORWARD DECLARATIONS
class CAknInfoPopupNote;
class CAknInfoPopupNoteController;

// CLASS DECLARATION

/**
 *  Observer class for notifying popup's showing and hiding.
 *
 *  @lib avkon.lib
 *  @since Series 60 3.0
 */
class MAknInfoPopupNoteObserver
    {
    public:

        enum TAknInfoPopupNoteEvent
            {
            EInfoPopupNoteShown,
            EInfoPopupNoteHidden
            };

        /**
        * Handles events reported from info popup note.
        * @param aController The controller that controls the note, from
        *   where the event originates.
        * @param aEvent The event.
        */
        virtual void HandleInfoPopupNoteEvent(
            CAknInfoPopupNoteController* aController,
            TAknInfoPopupNoteEvent aEvent ) = 0;
    };


/**
 *  The controller part of popup.
 *  It is active object, and uses timer to show popup after specified
 *  time interval (default 1 sec.) and popup hides automaticly
 *  after an other period (default 10 sec.).
 *
 *  @lib avkon.lib
 *  @since Series 60 3.0
 */
class CAknInfoPopupNoteController : public CTimer
    {
public:
    /**
     * The tone played before the dialog is shown.
     * Application specific tones may be played by casting the application
     *  defined Sound ID (SID), to TTone
     */
    enum TTone
        {
        /** No tone is played. */
        ENoTone = 0,
        /** A confirmation tone is played. */
        EConfirmationTone = EAvkonSIDConfirmationTone,
        /** A warning tone is played. */
        EWarningTone = EAvkonSIDWarningTone,
        /** An error tone is played. */
        EErrorTone = EAvkonSIDErrorTone
        };

public: // Constructors and destructor

    /**
     * Two-phased constructor.
     */
    IMPORT_C static CAknInfoPopupNoteController* NewL();

    /**
     * Destructor.
     */
    virtual ~CAknInfoPopupNoteController();

public: // New functions

    /**
    * Set time delay period before popup is shown (in milliseconds).
    * (if this isn't set, default delay time before show is 1 sec. )
    * @param aMilliSeconds Wanted delay time in milliseconds.
    */
    IMPORT_C void SetTimeDelayBeforeShow( TInt aMilliSeconds );

    /**
    * Set time period how long popup is in view (in milliseconds).
    * (if this isn't set, default show time is 10 sec. )
    * @param aMilliSeconds Wanted show time in milliseconds.
    * if set to 0, popup is shown until HideInfoPopupNote is called
    */
    IMPORT_C void SetTimePopupInView( TInt aMilliSeconds );

    /**
    * Set text to show in popup. If given text is too long for popup,
    * it is truncated.
    * @param aText Text to show in popup.
    */
    IMPORT_C void SetTextL( const TDesC& aText );

    /**
    * Show popup after delay time (hide possible previous popup immediately)
    * and hide popup again after setted time.
    */
    IMPORT_C void ShowInfoPopupNote();

    /**
    * Hide popup immediately.
    */
    IMPORT_C void HideInfoPopupNote();

    /**
    * Adds an observer for the pop-up.
    * @param aObserver The observer to be added.
    */
    IMPORT_C void AddObserverL( const MAknInfoPopupNoteObserver& aObserver );

    /**
    * Removes an observer from the pop-up.
    * @param aObserver The observer to be removed.
    */
    IMPORT_C void RemoveObserver( const MAknInfoPopupNoteObserver& aObserver );

    /**
    * Sets the position and alignment of the info pop-up note.
    * @since 3.1
    * @param aPosition The position, where pop-up note is displayed.
    * @param aAlignment Specifies the part of pop-up note that will be aligned
    *    with the given position.
    */
    IMPORT_C void SetPositionAndAlignment( const TPoint& aPosition,
                                           const TGulAlignmentValue& aAlignment );

    /**
    * Sets the position of the info pop-up note so that it is aligned with the
    * given rectangle as specified in the LAF data. This is intented to be
    * used in conjunction with lists and grids if the application wishes to
    * implement a pop-up that follows lists/grids item highlight.
    * @since 3.1
    * @param aHighlightRect Screen-relative rectangle used to calculate
    *       pop-up's position.
    */
    IMPORT_C void SetPositionByHighlight( const TRect& aHighlightRect );

    /**
    * Restores the info pop-up note's default position discarding previously
    * set values to position and alignment.
    * @since 3.1
    */
    IMPORT_C void RestoreDefaultPosition();

    /**
    * Sets the tooltip mode. When tooltip mode is on, info pop-up note is
    * displayed with only one line of text, and the width of the pop-up note
    * depends on the text length.
    * @since 3.1
    * @param aTooltipMode ETrue to set tooltip mode on, EFalse to set it off.
    */
    IMPORT_C void SetTooltipModeL( const TBool aTooltipMode );

    /**
    * Notifies the observers of the info popup note of an event.
    * @param aEvent The event, of which the observers are notified.
    */
    void NotifyObservers( MAknInfoPopupNoteObserver::TAknInfoPopupNoteEvent aEvent );

    /**
    * Set the tone to be played when the info popup note is shown
    * @param aTone The tone
    */
    IMPORT_C void SetTone( const TTone& aTone );

    /**
    * Whether info popup note will be automatically hidden 
    * or not when app ui is faded (true by default) 
    * @since 3.1
    * @param aHide ETrue when hidden, EFalse when shown or controlled externally
    */
    IMPORT_C void HideWhenAppFaded( const TBool aHide );

protected:

    /**
	* From CTimer. Cancels an outstanding asynchronous request.
	*/
    void DoCancel();

private: // From CActive

    /**
    * Show popup. Called by system framework.
    */
    void RunL();

private:

    /**
     * C++ default constructor.
     */
    CAknInfoPopupNoteController();

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

    /**
    * Play the tone.
    */
    void PlayTone();

private: // Data

    enum TInfoPopupNoteState
        {
        EHidden,
        EWaitingToShow,
        EShowing
        };

    TInfoPopupNoteState iState;

    // Own. View object for popup's model-view-controller
    CAknInfoPopupNote* iPopup;

    // Array containing the observers of popup.
    RPointerArray<MAknInfoPopupNoteObserver> iObservers;

    // Delay before popup show
    TInt iTimeDelayBeforeShow; // in microseconds

    // How long popup is shown
    TInt iTimeInView; // in microseconds

    // Specifies the tone
    TTone iTone;
    };

#endif // CAKNINFOPOPUPNOTECONTROLLER_H


// End of File
