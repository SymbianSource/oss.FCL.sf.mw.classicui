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


#ifndef __AKN_TRANSITION_UTILS_H__
#define __AKN_TRANSITION_UTILS_H__

#include <coemain.h>
#include <gfxtranseffect/gfxtranseffect.h>

class CRepository;

// Constants for component appear/disappear actions
const TInt KGfxControlAppearAction = 3;
const TInt KGfxControlDisappearAction = 4;

// Constants for the types of component effects
#define KGfxOptionsMenuControlUid TUid::Uid(0x10281F88)
#define KGfxOptionsMenuCascadeControlUid TUid::Uid(0x10281F89)
#define KGfxTouchToolbarControlUid TUid::Uid(0x10282E49)
#define KGfxToolbarControlUid TUid::Uid(0x10282E4A)
#define KGfxContextMenuControlUid TUid::Uid(0x10282E4C)
#define KGfxTaskSwapperControlUid TUid::Uid(0x10281F90)
#define KGfxNumberEntryPopupUid TUid::Uid( 0x10282E4D )
#define KGfxMediaBarControlUid TUid::Uid( 0x20007B17 )

#define KGfxErrorNoteControlUid TUid::Uid( 0x10282E50 )
#define KGfxWarningNoteControlUid TUid::Uid( 0x10282E51 )
#define KGfxInformationNoteControlUid TUid::Uid( 0x10282E52 )
#define KGfxConfirmationNoteControlUid TUid::Uid( 0x10282E53 )
#define KGfxWaitNoteControlUid TUid::Uid( 0x10282E54 )
#define KGfxQueryControlUid TUid::Uid( 0x10282E56 )
#define KGfxPopupDefaultControlUid TUid::Uid( 0x10282E57 )
#define KGfxSystemNotificationControlUid TUid::Uid( 0x2000B472 )
#define KGfxSystemNotifBatteryControlUid TUid::Uid( 0x2000B473 )

#define KGfxSequenceFirstControlUid TUid::Uid( 0x2000B474 )
#define KGfxSequenceMiddleControlUid TUid::Uid( 0x2000B475 )
#define KGfxSequenceLastControlUid TUid::Uid( 0x2000B476 )

// Enumerations for notifying tfx server (used via 
// GfxTransEffect::NotifyExternalState)
enum TGfxTransNotification 
    {
    ENotifyGlobalAbort,
    ENotifySetExtent
    ,ECaptureComponentsBegin
    ,ECaptureComponentsEnd
    ,EBeginPopupSequence
    ,ELastPopupInSequence
    ,EEndPopupSequence
    ,EInternalHandleSequence
    // Get the type of the current transition.  Must be called during
    // a transition, ie. between Begin() and End().
    ,EGetRegistrationType
    ,ECaptureComponentsAbort
    ,EAddIgnoreWOChildComponent
    ,ERemoveIgnoreWOChildComponent
    };

// Enumeration for data that should be accessible globally. (cross-class)
// For local data, use this pointer or key > EUserDefinedKey
enum TAknTransitionUtilsDataKey
	{
	EDontAnimateBitmaps,
	EUserDefinedKey = 0xFFFF,
	};

// Constants for unique ID's to store values with SetData().
// These must not collide with pointers to controls, which are used as keys
// in some places, so starting from 1 is safe.
const TInt KScreensaverCallStateChange = 1;

const TUid KAknTransitionUtilsUid = { 0x10282E4B };

class CAknPsObserver;

NONSHARABLE_CLASS( MAknPsObserver )
    {
public:
    virtual void PsValueUpdated( const TUid aCategory, const TUint aKey,
                                 const TInt aVal ) = 0;
    };

/**
 * Transition callback interface.
 */
class MAknTransitionUtilsObserver
    {
public:
    virtual TInt AknTransitionCallback(TInt aEvent, TInt aState = 0, 
                                       const TDesC8* aParams = NULL) = 0;
	};

/**
 * Utility class for transition effects.
 *
 * There are three different kinds of utilities here:
 * 1. Callbacks for different transition related events.
 * 2. Temporary storage of arbitrary data, associated with a key.
 * 3. General transition related functions.
 *
 * The data storage functionality is useful when you need to pass data
 * between different parts of the code, and there is no natural way to
 * do it, eg. when doing control transitions with integration in 
 * components that aren't explicitly connected.  In this case a fitting
 * key would be a pointer to the CCoeControl.
 */
NONSHARABLE_CLASS( CAknTransitionUtils ) : public CCoeStatic, 
                                           public MGfxTransEffectObserver,
                                           public MAknPsObserver
    {
    public:

    /**
     * Types of events for which callbacks can be registered.
     */
    enum TEvents
        { 
        ENone = 0x0,
        
        /**
         * Changes in screen redirection.
         */
        EEventWsBufferRedirection = 0x1,
        
        /**
         * Component effect completion.
         */
        EEventControlTransitionFinished = 0x2
		};

    /**
     * Control type specification for CAknTransitionUtils::GetDemarcation().
     */
    enum TGfxControlType
        {
        EOptionsMenu,
        EPopup
        };

    enum TMakeVisibleSubComponentsInfo
        {
        EForceInvisible,
        EForceVisible,
        EDisappearInvisible,
        EAppearInvisible,
        EAppearVisible,
        EClearIgnored
        };

    ~CAknTransitionUtils();

    /**
     * Add an observer for transition events.  If the observer has already
     * been added, the events for which it is listening will be updated to
     * the new set of events passed in.
     *
     * @param aObserver The observer object.
     * @param aEvent The event(s) to listen to.  To register an observer
     *        for multiple events, the event flags should be OR-ed together.
     * @param aParams Extra parameters.  Not used with
     *        EEventWsBufferRedirection.  With EEventControlTransitionFinished,
     *        a pointer to the CCoeControl of the transition should be passed
     *        in, as this will be passed back to the observer in the callback.
     *        Send this pointer directly as the argument, cast to a 
     *        const TDesC8*.
     *
     * @return KErrNone on success, otherwise one of the other system-wide 
     *         error codes.
     */
    IMPORT_C static TInt AddObserver( MAknTransitionUtilsObserver* aObserver,
                                      TInt aEvents,
                                      const TDesC8* aParams = NULL );
                                      
    /**
     * Remove an observer for transition events.  The events specified are
     * significant: only the specified events will be removed.  If there are
     * no remaining events, the observer will be removed and the
     * actual observer object can be safely deleted.
     *
     * @param aObserver The observer to remove.
     * @param aEvent The event(s) that should be removed.
     *
     * @return KErrNone on success, otherwise one of the other system-wide
     *         error codes.
     */
    IMPORT_C static TInt RemoveObserver( MAknTransitionUtilsObserver* aObserver,
                                         TInt aEvents );

    /**
     * Get the state of the observed event.  This currently only applies to
     * window redirection, not to component transition completion.
     *
     * @param aEvent The event to check the state of.  Currently
     *        EEventWsBufferRedirection is the only valid alternative.
     * @param aState On return, the state is set.  For window redirection,
     *        this is 0 (false) if it's not redirected, and non-zero (true)
     *        if it is.
     * @param aParams Additional parameters.  Not currently used.
     *
     * @return KErrNone on success, otherwise one of the other system-wide
     *         error codes.
     */
    IMPORT_C static TInt GetState( TInt aEvent, TInt* aState, 
                                   TDes8* aParams = NULL);

    /**
     * Store arbitrary data, associated with a key.  Only one data pointer
     * can be stored per key, so if data has already been stored using aKey,
     * aData will be stored instead of the old data.
     *
     * @param aKey The key, which can be used to retrieve the data.
     * @param aData The data to store.
     *
     * @return KErrNone on success, otherwise one of the other
     *         system-wide error codes.
     */
    IMPORT_C static TInt SetData( const TInt aKey, TAny* aData );

    /**
     * Retrieve stored data, using its associated key.
     * 
     * @param aKey The key to which the data is associated.
     *
     * @return The data, or NULL on error.
     */
    IMPORT_C static TAny* GetData( const TInt aKey );

    /**
     * Remove stored data.  This does not free the stored data, just removes
     * it from storage, so that it can no longer be retrieved.  This should
     * be done when the data no longer needs to be retrieved, to free up
     * data internal to this class.
     *
     * @param aKey The key to which the data is associated.
     */
    IMPORT_C static void RemoveData( const TInt aKey );

    /**
     * Recursively sets all parents to the control tree.  Used by control
     * transition integration points to ensure that all controls will be
     * included in the transition.
     *
     * @param aControl The base (key) control of a control transition.
     */
    IMPORT_C static void SetAllParents( const CCoeControl* aControl );
    
    /**
     * Check if transition effects are enabled.
     *
     * @param aEffectCategory Specify which category of effects to inquire
     *        about.  The categories are specified in akntranseffect.h,
     *        (EFullScreenTransitionsOff etc.).
     *
     * @return ETrue if effects in the specified category are enabled, 
     *         EFalse if not.
     */
    IMPORT_C static TBool TransitionsEnabled( TInt aEffectCategory );

    /**
     * Set the visibility for all the subcomponents of a control.  NB: does
     * NOT set the visibility for the control itself (aControl).
     *
     * @param aControl The main control, whose subcomponents will have their
     *        visibility set.
     * @param aInfo EForceInvisible = Makes all window owning sub controls
     *                  invisible
     *             EForceVisible: Makes all window owning sub controls visible
     *             EDisappearInvisible: Makes all window owning sub controls
     *                  invisible
     *             EAppearInvisible: Makes all visible subcontrols invisible
     *                  (must be followed by a call using EAppearVisible or
     *                  EClearIgnored)
     *             EAppearVisible: Makes all controls visible that was made
     *                  invisible using argument EAppearInvisible
     *             EClearIgnored: Reset the list of controls that was added
     *                  to ignore list
     *
     * @return KErrNone on success, otherwise one of the system-wide error 
     *         codes.
     */
    IMPORT_C static TInt MakeVisibleSubComponents( CCoeControl* aControl, 
                                        TMakeVisibleSubComponentsInfo aInfo );

    /**
     * Get the demarcation rect for a specified component.  The demarcation
     * rect is the area where an appear transition should start, and a
     * disappear transition should end.  For example, for the options menu,
     * this would probably be the left softkey.  With the proper KML, this
     * could be used to give the impression that the options menu grows 
     * out from the left softkey.
     *
     * This function handles portrait and landscape mode transparently, so
     * the integration code should always get the appropriate demarcation
     * rect.
     *
     * @param aControlType The control type to get the demarcation for.
     * @param aRect On return, contains the resulting rect.
     *
     * @return KErrNone on success, otherwise one of the system-wide error
     *         codes.
     */
    IMPORT_C static TInt GetDemarcation( TGfxControlType aControlType, 
                                         TRect& aRect );

    private:
    CAknTransitionUtils();

    /**
     * Returns the AknTransitionUtils singleton.
     *
     * The AknTransitionUtils singleton, or NULL or error.
     */    
    static CAknTransitionUtils* Static();
    
    // From MGfxTransEffectObserver
    void TransitionFinished( const CCoeControl* aControl, 
                                      TUint aAction );

    // From MAknPsObserver
    void PsValueUpdated( const TUid aCategory, const TUint aKey,
                         const TInt aVal );
    
    void RemoveControlTransitionObserver( const TInt aKey );

    TInt MakeVisibleSubComponentsR( CCoeControl* aControl, 
                                    TMakeVisibleSubComponentsInfo aInfo );

private:
    struct TDataEntry;
    struct TTransitionObserver;
  
    RPointerArray<TDataEntry> iUserData;

    RPointerArray<TTransitionObserver> iObservers;
    TInt iNumControlTransitionObservers;
    
    CAknPsObserver* iPsObserver;
    TInt iNumPsObservers;
    TBool iScreenRedirected;
    
    CRepository* iRepository;
    RPointerArray<const CCoeControl> iIgnoredChildControls;
    };

#endif // __AKN_TRANSITION_UTILS_H__
