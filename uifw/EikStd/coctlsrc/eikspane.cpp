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
* Description:  EIKON Status Pane control.
*
*/


// SYSTEM INCLUDE FILES
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include <barsread.h>
#include <eikspane.h>
#include <coeccntx.h>
#include <aknappui.h>
#include <eikenv.h>
#include <uiklaf/private/lafspane.h>
#include <AknSgcc.h>
#include <AknUtils.h>
#include <AknStatuspaneUtils.h>
#include <AknsCombinedBackgroundControlContext.h>
#include <AknsMaskedLayerBackgroundControlContext.h>
#include <eikapp.h>

#include <coecntrl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <AknsDrawUtils.h>
#include "aknstatuspanedatasubscriber.h"

#ifdef RD_SCALABLE_UI_V2
#include <akntouchpane.h>
#endif // RD_SCALABLE_UI_V2

#include <pslninternalcrkeys.h>
#include <centralrepository.h>
#include <akntranseffect.h>

#include <AknTasHook.h>
/** Granularity of the sub-pane control array. */
const TInt KEikStatusPaneControlGranularity = 4;

/** Fading is no longer handled here. */
// const TInt KEikStatusPaneBaseFadedBit    = 1;

/** Flag indicating status pane visibility. */
const TInt KEikStatusPaneBaseVisibleBit     = 2;

/** Flag indicating status pane dimming state. */
const TInt KEikStatusPaneBaseDimmedBit      = 4;

/** Unique UID for status pane TLS singleton. */
const TUid KUidStatusPaneTls = { 0x10005FB5 };

/** Default timeout for status pane blanker. */
const TInt KDefaultUnblankTimeout = 100000; // 0.1 s

/** This flag is used to turn redraw storing on/off in status pane. */
const TInt KEnableRedrawStoring = ETrue;

const TUid KActiveIdle2Uid = {0x102750F0};

inline void CEikStatusPaneBase::TPaneCapabilities::SetPresent()
    {
    iFlags |= KStatusPaneCapsPresentBit;
    }

inline void CEikStatusPaneBase::TPaneCapabilities::SetAppOwned()
    {
    iFlags |= KStatusPaneCapsAppOwnedBit;
    }

inline void CEikStatusPaneBase::TPaneCapabilities::SetInCurrentLayout()
    {
    iFlags |= KStatusPaneCapsInCurrentLayoutBit;
    }

#ifdef RD_FULLSCREEN_WALLPAPER

/**
* Skin background context layers used in usual status pane layouts.
*/
enum
    {
    ELayerWallpaper  = 0,
    ELayerBackground = 1,
    ELayerExtension  = 2,
    ELayerStripe     = 3,
    ELayerN          = 4
    };

/**
* Skin background layers for first context used in stacon pane layouts.
*/
enum
    {
    ELayerStaconWallpaper = 0,
    ELayerStaconTop       = 1,
    ELayerStaconBottom    = 2,
    ELayerStaconN         = 3
    };

/**
* Skin background layers for second context used in stacon pane layouts.
*/
enum
    {
    ELayerStaconWp   = 0,
    ELayerStaconSkin = 1
    };

/**
* Skin background layers for second context used in flat status pane layouts.
*/
enum
    {
    ELayerFlatCbaWp   = 0,
    ELaterFlatCbaSkin = 1
    };

/**
* Skin background layers for first context used in flat status pane layouts.
*/
enum
    {
    ELayerFlatWallpaper  = 0,
    ELayerFlatBackground = 1,
    ELayerFlatTl         = 2,
    ELayerFlatTr         = 3,
    ELayerFlatBl         = 4,
    ELayerFlatBr         = 5,
    ELayerFlatT          = 6,
    ELayerFlatB          = 7,
    ELayerFlatR          = 8,
    ELayerFlatL          = 9,
    ELayerFlatCenter     = 10,
    ELayerFlatMain       = 11,
    ELayerFlatCba        = 12,
    ELayerFlatN          = 13
    };

#else

/**
* Skin background context layers used in usual status pane layouts.
*/
enum
    {
    ELayerBackground = 0,
    ELayerExtension  = 1,
    ELayerStripe     = 2,
    ELayerWallpaper  = 3,
    ELayerN          = 4
    };

/**
* Skin background context layers used in stacon pane layouts.
*/
enum
    {
    ELayerStaconTop       = 0,
    ELayerStaconBottom    = 1,
    ELayerStaconMain      = 2,
    ELayerStaconWallpaper = 3,
    ELayerStaconN         = 4
    };

/**
* Skin background context layers used in flat status pane layouts.
*/
enum
    {
    ELayerFlatBackground = 0,
    ELayerFlatTl         = 1,
    ELayerFlatTr         = 2,
    ELayerFlatBl         = 3,
    ELayerFlatBr         = 4,
    ELayerFlatT          = 5,
    ELayerFlatB          = 6,
    ELayerFlatR          = 7,
    ELayerFlatL          = 8,
    ELayerFlatCenter     = 9,
    ELayerFlatMain       = 10,
    ELayerFlatWallpaper  = 11,
    ELayerFlatCba        = 12,
    ELayerFlatN          = 13
    };

#endif // RD_FULLSCREEN_WALLPAPER

/**
* Status pane blanker disable levels.
* As of release 3.2 status pane blanker is not used anymore.
*/
enum
    {
    EBlankDisableLevelNone   = 0, ///< Blanker is enabled.
    EBlankDisableLevelNormal = 1, ///< Blanker is disabled, but may be used in some situations.
    EBlankDisableLevelHigh   = 2  ///< Blanker is always disabled.
    };

/** Resource IDs for portrait mode status pane layouts. */
const TInt KStatusPanePortraitResIds[] =
    {
    R_AVKON_STATUS_PANE_LAYOUT_IDLE,
    R_AVKON_STATUS_PANE_LAYOUT_USUAL,
    R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE,
    R_AVKON_STATUS_PANE_LAYOUT_EMPTY,
    R_AVKON_STATUS_PANE_LAYOUT_SMALL,
    R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE,
    R_AVKON_STATUS_PANE_LAYOUT_VT,
    R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED,
    R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED,
    R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED,
    R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED,
    R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED,
    R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT,
    R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT,
    R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT,
    R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT,
    R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS
    };

/** Resource IDs for landscape mode status pane layouts. */
const TInt KStatusPaneLandscapeResIds[] =
    {
    R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE,
    R_AVKON_STATUS_PANE_LAYOUT_EMPTY,
    R_AVKON_STATUS_PANE_LAYOUT_SMALL,
    R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE,
    R_AVKON_STATUS_PANE_LAYOUT_VT,
    R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED,
    R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED,
    R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED,
    R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT,
    R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT,
    R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT,
    R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT,
    R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT,
    R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT,
    R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT,
    R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT,
    R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL,
    R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE,
    R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT,
    R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT,
    R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS,
    R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS
    };


// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// Checks if a specified status pane layout is supported in portrait.
// ---------------------------------------------------------------------------
//
static TBool SupportedPortraitResId( TInt aResId )
    {
    for ( TUint ii = 0;
          ii < sizeof( KStatusPanePortraitResIds ) /
               sizeof( *KStatusPanePortraitResIds );
          ii++ )
        {
        if ( KStatusPanePortraitResIds[ii] == aResId )
            {
            return ETrue;
            }
        }
	return EFalse;
	}


// ---------------------------------------------------------------------------
// Checks if a specified status pane layout is supported in landscape.
// ---------------------------------------------------------------------------
//
static TBool SupportedLandscapeResId( TInt aResId )
	{
    for ( TUint ii = 0;
          ii < sizeof( KStatusPaneLandscapeResIds ) /
               sizeof( *KStatusPaneLandscapeResIds );
          ii++ )
        {
        if ( KStatusPaneLandscapeResIds[ii] == aResId )
            {
            return ETrue;
            }
        }
	return EFalse;
	}


// ---------------------------------------------------------------------------
// Helper method to compose two layout lines together.
// ---------------------------------------------------------------------------
//
inline TAknWindowComponentLayout DoCompose( TAknWindowComponentLayout aLine1,
                                            TAknWindowComponentLayout aLine2 )
    {
    return TAknWindowComponentLayout::Compose( aLine1, aLine2 );
    }


/**
 * Interface for key - value pair getter.
 */
NONSHARABLE_CLASS( MKeyValue )
	{
public:

    /**
    * Return CR key ID.
    */
	virtual TUint32 Key() const = 0;

	/**
    * Return CR key value.
    */
	virtual TInt Value() const = 0;
	};

/**
 * Interface for a key change listener.
 */
NONSHARABLE_CLASS( MKeyListener )
	{
public:

    /**
    * Called when a value of a key changes.
    */
	virtual void KeyChanged( const MKeyValue& aKeyValue ) = 0;
	};

/**
 * Class for observing changes in Central Repository properties.
 */
NONSHARABLE_CLASS( CCenRepListen ) : public CActive, public MKeyValue
	{
public:

    /**
    * Two-phased constructor.
    *
    * @param  aRep       UID of the repository.
    * @param  aKey       ID  of the key inside the repository.
    * @param  aListener  Listener to be informed of changes.
    */
	static CCenRepListen* NewL( const TUid& aRep,
	                            const TUint32 aKey,
	                            MKeyListener& aListener );

    /**
    * Returns the current value of a CR key.
    *
    * @return Value of the key.
    */
	TInt Value() const;

	/**
    * Returns the ID of a CR key that is being listened to.
    *
    * @return ID of a CR key.
    */
	TUint32 Key() const;

	/**
	* Starts listening to the CR key.
	*/
	void Listen();

	/**
	* Destructor.
	*/
	~CCenRepListen();

private:

    /**
    * C++ constructor.
    *
    * @param  aKey       ID  of the key inside the repository.
    * @param  aListener  Listener to be informed of changes.
    */
	CCenRepListen( const TUint32 aKey, MKeyListener& aListener );

	/**
	* Second-phase constructor.
	*
	* @param  aRep  UID of the repository.
	*/
	void ConstructL( const TUid& aRep );

	/**
	* Cancels listening.
	*/
	void DoCancel();

	/**
	* Called when the key value is changed.
	*/
	void RunL();

private:

    /** ID of the key being listened to. */
	const TUint32   iKey;

	/** Listener to be informed of changes. */
	MKeyListener&   iListener;

	/** Current value of the key. */
	TInt            iValue;

	/** Pointer to a repository. */
	CRepository*    iRepository;
	};


// ---------------------------------------------------------------------------
// CCenRepListen::NewL
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CCenRepListen* CCenRepListen::NewL( const TUid& aRep,
                                    const TUint32 aKey,
                                    MKeyListener& aListener )
	{
	CCenRepListen* l = new (ELeave) CCenRepListen( aKey, aListener );
	CleanupStack::PushL( l );
	l->ConstructL( aRep );
    CleanupStack::Pop( l );
	return l;
	}


// ---------------------------------------------------------------------------
// CCenRepListen::Value
// Returns the current value of the key.
// ---------------------------------------------------------------------------
//
TInt CCenRepListen::Value() const
	{
	return iValue;
	}


// ---------------------------------------------------------------------------
// CCenRepListen::Value
// Returns the key being listened to.
// ---------------------------------------------------------------------------
//
TUint32 CCenRepListen::Key() const
	{
	return iKey;
	}


// ---------------------------------------------------------------------------
// CCenRepListen::Listen
// Starts listening to a value changes.
// ---------------------------------------------------------------------------
//
void CCenRepListen::Listen()
	{
	Cancel();
	SetActive();
	iRepository->NotifyRequest( iKey, iStatus );
	}

// ---------------------------------------------------------------------------
// CCenRepListen::CCenRepListen
// C++ constructor
// ---------------------------------------------------------------------------
//
CCenRepListen::CCenRepListen( const TUint32 aKey,
                              MKeyListener& aListener )
    : CActive( CActive::EPriorityStandard ),
      iKey( aKey ),
      iListener( aListener )
	{
	CActiveScheduler::Add( this );
	}


// ---------------------------------------------------------------------------
// CCenRepListen::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CCenRepListen::ConstructL( const TUid& aRep )
	{
	iRepository = CRepository::NewL( aRep );
	User::LeaveIfError( iRepository->Get( iKey, iValue ) );
	}


// ---------------------------------------------------------------------------
// CCenRepListen::DoCancel
// Cancels listening.
// ---------------------------------------------------------------------------
//
void CCenRepListen::DoCancel()
	{
	iRepository->NotifyCancelAll();
	}


// ---------------------------------------------------------------------------
// CCenRepListen::RunL
// Called when the key value changes.
// ---------------------------------------------------------------------------
//
void CCenRepListen::RunL()
	{
	User::LeaveIfError( iRepository->Get( iKey, iValue ) );
	iListener.KeyChanged( *this );
	}


// ---------------------------------------------------------------------------
// CCenRepListen::~CCenRepListen
// Destructor.
// ---------------------------------------------------------------------------
//
CCenRepListen::~CCenRepListen()
	{
	Cancel();
	delete iRepository;
	}


/**
 * Helper class for setting the state of redraw storing.
 */
NONSHARABLE_CLASS( CRedrawStoreHandler ) : public CBase, public MKeyListener
	{
public:

    /**
    * Destructor.
    */
	~CRedrawStoreHandler();

	/**
	* Second-phase constructor.
	*/
	void ConstructL();

	/**
	* Sets the redraw storing on/off for a specified window.
	*/
	void SetStore( RWindow* aWindow, TBool aOn );

private: // From base class @c MKeyListener.

    /**
    * Handles changes in the observer CR key value.
    */
	void KeyChanged( const MKeyValue& aKeyValue );

private:

    /** Pointer to the window whose redraw storing state is controlled. */
	RWindow* iWindow;

	/** CR key change listener. */
	CCenRepListen* iListen;

	/** Set state of the redraw storing. */
	TBool iStoreValue;
	};


// ---------------------------------------------------------------------------
// CRedrawStoreHandler::~CRedrawStoreHandler
// Destructor.
// ---------------------------------------------------------------------------
//
CRedrawStoreHandler::~CRedrawStoreHandler()
	{
	delete iListen;
	}


// ---------------------------------------------------------------------------
// CRedrawStoreHandler::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CRedrawStoreHandler::ConstructL()
	{
    if ( !CAknEnv::Static()->TransparencyEnabled() )
        {
	iListen = CCenRepListen::NewL( KCRUidThemes,
	                               KThemesTransitionEffects,
	                               *this );
	iListen->Listen();
        }

	}


// ---------------------------------------------------------------------------
// CRedrawStoreHandler::SetStore
// Sets the redraw storing on/off for a specified window.
// ---------------------------------------------------------------------------
//
void CRedrawStoreHandler::SetStore( RWindow* aWindow, TBool aOn )
	{
    if ( !CAknEnv::Static()->TransparencyEnabled() )
        {
	    iWindow     = aWindow;
	    iStoreValue = aOn;

	    if ( aOn )
		    {
		    KeyChanged( *iListen );
		    }
	    else
		    {
		    iWindow->EnableRedrawStore( EFalse );
		    }
        }
	}


// ---------------------------------------------------------------------------
// CRedrawStoreHandler::KeyChanged
// Disables redraw storing if fullscreen transition effects are set on.
// ---------------------------------------------------------------------------
//
void CRedrawStoreHandler::KeyChanged( const MKeyValue& aKeyValue )
	{
	if ( iWindow && aKeyValue.Key() == KThemesTransitionEffects )
		{
		const TBool fullScreen =
		    !aKeyValue.Value() & AknTransEffect::EFullScreenTransitionsOff;
		if ( iStoreValue )
			{
			iWindow->EnableRedrawStore( !fullScreen );
			}
		iListen->Listen();
		}

	}


/**
 * This class is used for drawing a empty (blank) statuspane background.
 */
NONSHARABLE_CLASS( CAknStatuspaneClearer ) : public CAknControl
	{
public:

    /**
    * Two-phased constructor.
    */
    static CAknStatuspaneClearer* NewLC( RWindowGroup& aParent,
                                         TInt aStatuspaneLayoutId,
                                         TBool aOwnWindowGroup );

    /**
    * Two-phased constructor.
    */
	static CAknStatuspaneClearer* NewL( RWindowGroup& aParent,
	                                    TInt aStatuspaneLayoutId,
	                                    TBool aOwnWindowGroup );

    /**
    * Sets blank window shape to same as statuspanes shape.
    */
    void SetDefaultShape();

    /**
    * Sets blank window shape to given shape.
    */
    void SetShape( TRegion& aRegion );

    /**
    * Sets blank window skin backgound to match given statuspane layout.
    */
    void SetSkinBackgroundContext( TInt aStatuspaneLayoutId,
                                   TBool aDrawNavi = ETrue );

    /**
    * Enables blank functionality. If this has been called, then calls
    * to method Blank() works normally.
    */
    void EnableBlank();

    /**
    * Disables blank functionality. If this has been called, then calls
    * to method Blank() does nothing.
    */
    void DisableBlank( TInt aDisableLevel );

    /**
    * Tells if blank functionality has been disabled
    */
    TInt BlankDisabled();

    /**
    * Draws blank statuspane background using previously set shape and
    * skin background and makes blank window visible.
    */
    void Blank();

    /**
    * Draws blank statuspane background using previously set shape and
    * skin background. Unblanks window automatically after aUnblankTimeout
    * time (in milliseconds).
    */
    void Blank( TInt aUnblankTimeout );

    /**
    * Tells wheter Blank() has been called but Unblank() has not yet been
    * called.
    */
    TBool IsBlank();

    /**
    * Makes blank window not visible.
    */
    void UnBlank();

    /**
    * Sets blank window ordinal position.
    */
	void SetOrdinalPosition( TInt aPosition );

    /**
    * Destructor.
    */
	virtual ~CAknStatuspaneClearer();

private:

    /**
    * Private construction function.
    */
	void ConstructL( RWindowGroup& aParent,
	                 TInt aStatuspaneLayoutId,
	                 TBool aOwnWindowGroup );

    /**
    * Starts timer.
    */
    void InitTimer( TInt aDelay, TInt aInterval );

    /**
    * Cancels timer.
    */
    void CancelTimer();

    /**
    * Static timer callback.
    */
    static TInt TimerEvent( TAny* aPtr );

    /**
    * Timer callback.
    */
    void DoTimerEvent();

private:	// From base class @c CCoeControl.

	void Draw( const TRect& aRect ) const;

private:

    /** Timer for automatic unblanking. */
    CPeriodic* iUnblankTimer;

    /**
    * Statuspane layout ID which is used to decide what
    * kind of skin background is drawn.
    */
    TInt iStatuspaneLayoutId;

    /** A flag to temporarily disable blanking functionality. */
    TInt iBlankDisableLevel;

    /** Skin background context. */
    CAknsMaskedLayerBackgroundControlContext* iBgContext;

    /**
    * Parent window group.
    * Own if iOwnWindowGroup is ETrue.
    */
	RWindowGroup* iParent;

	/**
	* A flag indicating whether or not blanker owns it's window group.
	*/
	TBool iOwnWindowGroup;
	};


/**
 * Delayed foreground state observer class.
 * Used by the status pane in situations where the state of redraw storing
 * needs to be changed when foreground state changes, but it cannot be
 * done at the moment when the foreground event is received.
 */
NONSHARABLE_CLASS( CAknDelayedForegroundObserver ) : public CBase
	{
public:

    /**
    * Two-phased constructor.
    */
	static CAknDelayedForegroundObserver* NewLC(
	    MCoeForegroundObserver* aObserver );

    /**
    * Two-phased constructor.
    */
	static CAknDelayedForegroundObserver* NewL(
	    MCoeForegroundObserver* aObserver );

    /**
    * Destructor.
    */
	virtual ~CAknDelayedForegroundObserver();

    /**
    * Starts delay, after delay MCoeForegroundObserver::HandleGainingForeground
    * is called. This is repeated aNumberOfRepeats of times.
    */
    void StartDelayedForegroundGainObservation( TInt aDelay,
                                                TInt aNumberOfRepeats );

    /**
    * Starts delay, after delay MCoeForegroundObserver::HandleLosingForeground
    * is called. This is repeated aNumberOfRepeats of times.
    */
    void StartDelayedForegroundLossObservation( TInt aDelay,
                                                TInt aNumberOfRepeats );

    /**
    * Stops delayed observation timer.
    */
    void StopDelayedObservation();

    /**
    * Tells if a call to MCoeForegroundObserver interface has been
    * called but the call has not yet returned.
    */
	TBool IsDelayedCallbackActive();

private:

    /**
    * Private construction function.
    */
	void ConstructL( MCoeForegroundObserver* aObserver );

    /**
    * Starts timer.
    */
    void InitTimer( TInt aDelay, TInt aInterval );

    /**
    * Cancels timer.
    */
    void CancelTimer();

    /**
    * Static timer callback.
    */
    static TInt TimerEvent( TAny* aPtr );

    /**
    * Timer callback.
    */
    void DoTimerEvent();

private:

    CPeriodic* iTimer;
	MCoeForegroundObserver* iObserver;
	TBool iForegroundLossObserverved;
	TBool iDelayedCallbackActive;
	TInt  iNumberOfRepeats;
	};



// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::NewLC
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknDelayedForegroundObserver* CAknDelayedForegroundObserver::NewLC(
    MCoeForegroundObserver* aObserver )
	{
	CAknDelayedForegroundObserver* self =
	    new (ELeave) CAknDelayedForegroundObserver;
	CleanupStack::PushL( self );
	self->ConstructL( aObserver );
	return self;
	}


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::NewL
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAknDelayedForegroundObserver* CAknDelayedForegroundObserver::NewL(
    MCoeForegroundObserver* aObserver )
	{
	CAknDelayedForegroundObserver* self =
	    CAknDelayedForegroundObserver::NewLC( aObserver );
	CleanupStack::Pop( self );
	return self;
	}


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknDelayedForegroundObserver::ConstructL(
    MCoeForegroundObserver* aObserver )
	{
	iObserver = aObserver;
   	iTimer    = CPeriodic::NewL( CActive::EPriorityStandard );
	}


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::~CAknDelayedForegroundObserver
// Destructor.
// ---------------------------------------------------------------------------
//
CAknDelayedForegroundObserver::~CAknDelayedForegroundObserver()
	{
    if ( iTimer )
    	{
   	    iTimer->Cancel();
        delete iTimer;
    	}
	}


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::StartDelayedForegroundGainObservation
// Starts delayed observation of foreground gain.
// ---------------------------------------------------------------------------
//
void CAknDelayedForegroundObserver::StartDelayedForegroundGainObservation(
    TInt aDelay, TInt aNumberOfRepeats )
	{
	CancelTimer();
	iNumberOfRepeats           = aNumberOfRepeats;
	iForegroundLossObserverved = EFalse;
	InitTimer( aDelay, aDelay );
	}


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::StartDelayedForegroundLossObservation
// Starts delayed observation of foreground loss.
// ---------------------------------------------------------------------------
//
void CAknDelayedForegroundObserver::StartDelayedForegroundLossObservation(
    TInt aDelay, TInt aNumberOfRepeats )
	{
	CancelTimer();
	iNumberOfRepeats           = aNumberOfRepeats;
	iForegroundLossObserverved = ETrue;
	InitTimer( aDelay, aDelay );
	}


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::StopDelayedObservation
// Stops delayed observation.
// ---------------------------------------------------------------------------
//
void CAknDelayedForegroundObserver::StopDelayedObservation()
	{
	CancelTimer();
	}


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::IsDelayedCallbackActive
// Checks whether the callback is already active.
// ---------------------------------------------------------------------------
//
TBool CAknDelayedForegroundObserver::IsDelayedCallbackActive()
	{
	return iDelayedCallbackActive;
	}


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::InitTimer
// Starts the timer.
// ---------------------------------------------------------------------------
//
void CAknDelayedForegroundObserver::InitTimer( TInt aDelay, TInt aInterval )
    {
    CancelTimer();
    if ( iTimer && !iTimer->IsActive() ) // start timer if not already started
        {
        iTimer->Start(
            TTimeIntervalMicroSeconds32( aDelay ),
		    TTimeIntervalMicroSeconds32( aInterval ),
            TCallBack( TimerEvent, this ) );
        }
    }


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::CancelTimer
// Cancels the timer.
// ---------------------------------------------------------------------------
//
void CAknDelayedForegroundObserver::CancelTimer()
    {
   	if ( iTimer && iTimer->IsActive() )
    	{
   		iTimer->Cancel();
    	}
    }


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::TimerEvent
// Static timer callback function.
// ---------------------------------------------------------------------------
//
TInt CAknDelayedForegroundObserver::TimerEvent( TAny* aPtr )
    {
    static_cast<CAknDelayedForegroundObserver*>( aPtr )->DoTimerEvent();
    return TRUE;
    }


// ---------------------------------------------------------------------------
// CAknDelayedForegroundObserver::DoTimerEvent
// Timer callback function.
// ---------------------------------------------------------------------------
//
void CAknDelayedForegroundObserver::DoTimerEvent()
    {
    if ( !iNumberOfRepeats-- )
        {
    	CancelTimer();
        }

	iDelayedCallbackActive = ETrue;

    if ( iForegroundLossObserverved )
        {
    	iObserver->HandleLosingForeground();
        }
    else
        {
    	iObserver->HandleGainingForeground();
        }

	iDelayedCallbackActive = EFalse;
    }


/**
 * class CEikStatusPaneContainer.
 * Container class for status pane's sub-pane controls.
 */
NONSHARABLE_CLASS( CEikStatusPaneContainer ) : public CCoeControl,
                                               public MCoeControlObserver,
                                               public MCoeControlContext
	{
public:

    /**
    * Two-phased constructor.
    */
    static CEikStatusPaneContainer* NewL(
        TPaneId aPaneId,
        TInt aControlTypeId,
        TInt aControlResId,
        RWindowGroup* aParent,
        CAknsMaskedLayerBackgroundControlContext* aBgContext1,
        CAknsMaskedLayerBackgroundControlContext* aBgContext2,
        CAknStatusPaneDataSubscriber* aDataSubscriber,
        CRedrawStoreHandler& aRedrawStoreHandler );

    /**
    * Destructor.
    */
    ~CEikStatusPaneContainer();

    /**
    * Returns the sub-pane ID of this container.
    */
    inline TPaneId Id() const;

    /**
    * Returns the control inside this container.
    */
    inline CCoeControl* Control() const;

    /**
    * Sets the control inside this container.
    */
    inline void SetControl( CCoeControl* aNewControl );

    /**
    * Prepares the skin background context for drawing.
    */
    static void PrepareBackgroundContext(
        CAknsMaskedLayerBackgroundControlContext* aBgContext,
        TInt aLayoutId,
        TBool aDrawNavi = ETrue,
        TInt aContextNumber = 0,
        TAknsItemID aCbaBgID = KAknsIIDQsnBgAreaControl );

    /**
    * Prepares the base skin background context for drawing.
    */
    static void PrepareBackgroundBaseContext( MAknsControlContext* aBgContext,
                                              TInt aLayoutId,
                                              TBool aDrawNavi = ETrue );

    /**
    * Handles resource change events.
    */
    void HandleResourceChange( TInt aType );

public: // From base class @c CCoeControl.

    /**
    * Sets the dimming status.
    */
    virtual void SetDimmed( TBool aDimmed );

protected: // From base class @c CCoeControl.

    /**
    * Supplies an object of type aId to the mop-chain.
    */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

private:

    /**
    * C++ constructor.
    */
    CEikStatusPaneContainer( TPaneId aPaneId );

    /**
    * Second-phase constructor.
    */
    void ConstructL( TInt aControlTypeId,
                     TInt aControlResId,
                     RWindowGroup* aParent,
                     CAknsMaskedLayerBackgroundControlContext* aBgContext1,
                     CAknsMaskedLayerBackgroundControlContext* aBgContext2,
                     CAknStatusPaneDataSubscriber* aDataSubscriber,
                     CRedrawStoreHandler& aRedrawStoreHandler );

    /**
    * Handles size change events.
    */
	virtual void SizeChanged();

	/**
    * Returns the number of component control inside this container.
    */
	virtual TInt CountComponentControls() const;

	/**
    * Gets a component control by control index.
    */
	virtual CCoeControl* ComponentControl( TInt aIndex ) const;

	/**
    * Handles events from an observed control.
    */
	void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

	/**
	* Writes the internal state of the control and its components to aStream.
	*/
	void WriteInternalStateL( RWriteStream& aWriteStream ) const;

    /**
	* Draws the control.
	*/
	void Draw( const TRect& aRect ) const;

private:

    /** Sub-pane ID of this container. */
	TPaneId iPaneId;

	/** Contained control. */
	CCoeControl* iControl;

private:

    /**
    * First skin background context.
    * Not own.
    */
    CAknsMaskedLayerBackgroundControlContext* iBgContext1;

    /**
    * Second skin background context.
    * Not own.
    */
    CAknsMaskedLayerBackgroundControlContext* iBgContext2;

    /**
    * Pointer to the status pane data subscriber.
    * Not own.
    */
    CAknStatusPaneDataSubscriber* iDataSubscriber;
	};


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::Id
// Returns the sub-pane ID.
// ---------------------------------------------------------------------------
//
inline TPaneId CEikStatusPaneContainer::Id() const
    {
    return iPaneId;
    }

// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::Control
// Gets the control inside this container.
// ---------------------------------------------------------------------------
//
inline CCoeControl* CEikStatusPaneContainer::Control() const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::SetControl
// Sets the control inside this container.
// ---------------------------------------------------------------------------
//
inline void CEikStatusPaneContainer::SetControl( CCoeControl* aNewControl )
    {
    iControl = aNewControl;
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::NewL
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CEikStatusPaneContainer* CEikStatusPaneContainer::NewL(
    TPaneId aPaneId,
    TInt aControlTypeId,
    TInt aControlResId,
    RWindowGroup* aParent,
    CAknsMaskedLayerBackgroundControlContext* aBgContext1,
    CAknsMaskedLayerBackgroundControlContext* aBgContext2,
    CAknStatusPaneDataSubscriber* aDataSubscriber,
    CRedrawStoreHandler& aRedrawStoreHandler )
    {
    CEikStatusPaneContainer* self =
        new (ELeave) CEikStatusPaneContainer( aPaneId );
    CleanupStack::PushL( self );
    self->ConstructL( aControlTypeId,
                      aControlResId,
                      aParent,
                      aBgContext1,
                      aBgContext2,
                      aDataSubscriber,
                      aRedrawStoreHandler );
    CleanupStack::Pop( self );
    AKNTASHOOK_ADDL( self, "CEikStatusPaneContainer" );
    return self;
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::CEikStatusPaneContainer
// C++ constructor.
// ---------------------------------------------------------------------------
//
CEikStatusPaneContainer::CEikStatusPaneContainer( TPaneId aPaneId )
    : iPaneId( aPaneId )
	{
	}



// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::~CEikStatusPaneContainer
// Destructor.
// ---------------------------------------------------------------------------
//
CEikStatusPaneContainer::~CEikStatusPaneContainer()
	{
	AKNTASHOOK_REMOVE();
	delete iControl;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneContainer::ConstructL(
    TInt aControlTypeId,
    TInt aControlResId,
    RWindowGroup* aParent,
    CAknsMaskedLayerBackgroundControlContext* aBgContext1,
    CAknsMaskedLayerBackgroundControlContext* aBgContext2,
    CAknStatusPaneDataSubscriber* aDataSubscriber,
    CRedrawStoreHandler& aRedrawStoreHandler )
    {
    SetMopParent( iEikonEnv->EikAppUi() );

    CreateWindowL( aParent );
    
    //This is added for homescreen transparent
    CEikApplication* app = iEikonEnv->EikAppUi()->Application();
    if ( app && app->AppDllUid() == KActiveIdle2Uid  )
        {
        if( KErrNone == Window().SetTransparencyAlphaChannel())
            Window().SetBackgroundColor(~0);
        }
    else
        {
        Window().SetBackgroundColor(
        iEikonEnv->ControlColor( EColorStatusPaneBackground, *this ) );
        }

    // This helps for unsyncronized undimming problems.
    aRedrawStoreHandler.SetStore( &Window(), KEnableRedrawStoring );

    iBgContext1 = aBgContext1;
    iBgContext2 = aBgContext2;

    iDataSubscriber = aDataSubscriber;

	SetControlContext( this );

	RWindow& window = Window();
	window.SetPointerGrab( ETrue );
	window.SetShadowDisabled( ETrue );
	window.SetNonFading( !LafStatusPaneContainer::AllowFading() );
	EnableDragEvents();

	HandleResourceChange( KEikColorResourceChange );

	iControl = EikControlFactory::CreateByTypeL( aControlTypeId ).iControl;
	iControl->SetContainerWindowL( *this );
	iControl->SetNonFocusing();

	TResourceReader res;
	if ( aControlResId )
	    {
		iEikonEnv->CreateResourceReaderLC( res, aControlResId );
	    }

	// If the following line panics, you forgot to give a resource
	// to a control that needs one.
	iControl->ConstructFromResourceL( res );
	if ( aControlResId )
	    {
		CleanupStack::PopAndDestroy();	// res
	    }

	SetComponentsToInheritVisibility();
	MakeVisible( EFalse );

	ActivateL();
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::SizeChanged
// Handles size change events.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneContainer::SizeChanged()
	{
	iControl->SetRect( Rect() );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::CountComponentControls
// Returns the amount of component controls.
// ---------------------------------------------------------------------------
//
TInt CEikStatusPaneContainer::CountComponentControls() const
	{
	return 1;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::ComponentControl
// Returns a contained control.
// ---------------------------------------------------------------------------
//
CCoeControl* CEikStatusPaneContainer::ComponentControl(
    TInt /*aIndex*/ ) const
	{
	return iControl;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::HandleControlEventL
// Handles events received from the observed control.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneContainer::HandleControlEventL( CCoeControl* aControl,
                                                   TCoeEvent aEventType )
	{
	if ( aControl == iControl && aEventType == EEventStateChanged )
	    {
		DrawNow();
	    }
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::PrepareBackgroundBaseContext
// Prepares base skin background context for drawing.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneContainer::PrepareBackgroundBaseContext(
    MAknsControlContext* aBgContext, TInt aLayoutId, TBool aDrawNavi )
    {

    if ( aBgContext->IsCompatibleWithType( EAknsControlContextTypeCombined ) )
        {
        TInt contextCount = 0;
        // Get first part of combination.
        MAknsControlContext* partOfCombinedContext =
            static_cast<CAknsCombinedBackgroundControlContext*>(
                aBgContext )->GetControlContext( contextCount );

        // While there are parts, fetch them and prepare each separately.
        while ( partOfCombinedContext )
            {
            CEikStatusPaneContainer::PrepareBackgroundContext(
                static_cast<CAknsMaskedLayerBackgroundControlContext*>(
                    partOfCombinedContext),
                aLayoutId,
                aDrawNavi,
                contextCount );
            partOfCombinedContext =
                static_cast<CAknsCombinedBackgroundControlContext*>(
                    aBgContext)->GetControlContext( ++contextCount );
            }
        }
    else // other contextes should be compatible with layered cc's.
        {
        CEikStatusPaneContainer::PrepareBackgroundContext(
            static_cast<CAknsMaskedLayerBackgroundControlContext*>(
                aBgContext),
            aLayoutId,
            aDrawNavi );
        }
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::PrepareBackgroundContext
// Prepares skin background context for drawing.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneContainer::PrepareBackgroundContext(
    CAknsMaskedLayerBackgroundControlContext* aBgContext,
    TInt aLayoutId,
    TBool aDrawNavi,
    TInt aContextNumber,
    TAknsItemID aCbaBgID )
    {
    if ( !SupportedPortraitResId( aLayoutId ) &&
         !SupportedLandscapeResId( aLayoutId ) )
        {
        // Layout not supported, do nothing.
        return;
        }

    // This is not using ApplicationRect(), because it
    // causes RWsSession::Flush().
    TRect screen;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );

    // Application window rectangle.
    TRect application_window;
    AknLayoutUtils::LayoutMetricsRect(
        AknLayoutUtils::EApplicationWindow, application_window );

    // Usual status pane
    TAknWindowLineLayout statusPane(
        DoCompose( AknLayoutScalable_Avkon::area_top_pane( 0 ),
                   AknLayoutScalable_Avkon::status_pane( 0 ) ).LayoutLine() );
    TAknLayoutRect status_pane_usual;
    status_pane_usual.LayoutRect( application_window, statusPane );
    TRect statusPaneUsual( status_pane_usual.Rect() );

    // Stacon top pane.
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(
        application_window,
        DoCompose( AknLayoutScalable_Avkon::area_top_pane( 2 ),
                   AknLayoutScalable_Avkon::stacon_top_pane() ).LayoutLine() );
    TRect staconTop( layoutRect.Rect() );

    // Stacon bottom pane.
    layoutRect.LayoutRect(
        application_window,
        DoCompose( AknLayoutScalable_Avkon::area_bottom_pane( 2 ),
                   AknLayoutScalable_Avkon::stacon_bottom_pane() ).LayoutLine() );
    TRect staconBottom( layoutRect.Rect() );

    // CBA for landscape bottom softkeys.
    TRect cbaRect( 0,0,0,0 );
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        layoutRect.LayoutRect(
            application_window,
            DoCompose( AknLayoutScalable_Avkon::area_bottom_pane( 6 ),
                       AknLayoutScalable_Avkon::control_pane() ).LayoutLine() );
        cbaRect = layoutRect.Rect();
        }

    // Clear the layers first.
    for ( TInt n = 0; n < ELayerFlatN; n++ )
        {
        aBgContext->SetLayerImage( n, KAknsIIDNone );
        }

    // By default - no mask.
    TAknsItemID maskIID( KAknsIIDNone );
    TRAP_IGNORE( aBgContext->SetLayerMaskAndSizeL(
        maskIID, application_window ) );
    TRect maskRect( 0,0,0,0 );

    switch( aLayoutId )
        {
        case R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE:
        case R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED:
			  {
           TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );

           if ( isLandscape )
               {
               TAknWindowLineLayout topLayout( AknLayoutScalable_Avkon::area_top_pane(8).LayoutLine() );

               TAknLayoutRect layoutRect;
               layoutRect.LayoutRect( application_window, topLayout );
               TRect topLayoutRect( layoutRect.Rect() );

               TAknWindowLineLayout statuspaneLayout( AknLayoutScalable_Avkon::status_pane(2).LayoutLine() );
               layoutRect.LayoutRect( topLayoutRect, statuspaneLayout );
               TRect spRect( layoutRect.Rect() );

               aBgContext->SetLayerImage( ELayerBackground, KAknsIIDQsnBgAreaStatus );
               aBgContext->SetLayerRect( ELayerBackground, spRect );
               }
           else
               {
               aBgContext->SetLayerImage( ELayerBackground, KAknsIIDQsnBgAreaStatus );
               aBgContext->SetLayerRect( ELayerBackground, status_pane_usual.Rect() );
               }

			  break;
			  }
        case R_AVKON_STATUS_PANE_LAYOUT_USUAL_WITH_BATTERY_PANE:
        case R_AVKON_STATUS_PANE_LAYOUT_USUAL:
        case R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED:
        case R_AVKON_STATUS_PANE_LAYOUT_VT:
        case R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED:
            {
            // First
            aBgContext->SetLayerImage( ELayerBackground, KAknsIIDQsnBgAreaStatus );
            aBgContext->SetLayerRect(  ELayerBackground, statusPaneUsual );

            // Extension
            aBgContext->SetLayerImage( ELayerExtension, KAknsIIDNone );

            // Stripe
            if ( aDrawNavi )
                {
                aBgContext->SetLayerImage( ELayerStripe, KAknsIIDQsnBgNavipaneSolid );
                }
            else
                {
                aBgContext->SetLayerImage( ELayerStripe, KAknsIIDNone );
                }

            // skin does not follow avkon LAF, skin wipe is 176x15, not 174x15
            TAknLayoutRect navi_wipe;
            navi_wipe.LayoutRect(
                statusPaneUsual,
                AknLayoutScalable_Avkon::status_pane_g1( 0 ).LayoutLine() );
            TRect skinnedNaviWipeRect( navi_wipe.Rect() );
            skinnedNaviWipeRect.iTl.iX = 0;
            skinnedNaviWipeRect.iBr.iX = statusPaneUsual.iBr.iX;

            aBgContext->SetLayerRect( ELayerStripe, skinnedNaviWipeRect );

            // Wallpaper
            aBgContext->SetLayerImage( ELayerWallpaper, KAknsIIDNone );
            break;
            }

        case R_AVKON_STATUS_PANE_LAYOUT_IDLE:
        case R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED:
            {
            // First
            TAknLayoutRect status_pane;
            status_pane = status_pane_usual;

            // Extension
            TAknLayoutRect extension;
            extension.LayoutRect(
                application_window,
                AKN_LAYOUT_WINDOW_main_pane( application_window, 0, 1, 1 ) );

            // Wallpaper
            aBgContext->SetLayerImage( ELayerWallpaper,  KAknsIIDWallpaper );
            aBgContext->SetLayerRect(  ELayerWallpaper,  screen );
            aBgContext->SetLayerImage( ELayerBackground, KAknsIIDQsnBgAreaStatusIdle );
            aBgContext->SetLayerRect(  ELayerBackground, statusPaneUsual );

            if ( aDrawNavi )
                {
                aBgContext->SetLayerImage( ELayerStripe, KAknsIIDQsnBgNavipaneSolidIdle );
                }
            else
                {
                aBgContext->SetLayerImage( ELayerStripe, KAknsIIDNone );
                }

            // skin does not follow avkon LAF, skin wipe is 176x15, not 174x15
            TAknLayoutRect navi_wipe;
            navi_wipe.LayoutRect(
                statusPaneUsual,
                AknLayoutScalable_Avkon::status_pane_g1( 0 ).LayoutLine() );
            TRect skinnedNaviWipeRect( navi_wipe.Rect() );
            skinnedNaviWipeRect.iTl.iX = 0;
            skinnedNaviWipeRect.iBr.iX = statusPaneUsual.iBr.iX;
            aBgContext->SetLayerRect( ELayerStripe, skinnedNaviWipeRect );

            maskIID  = KAknsIIDQgnGrafBgPrtTopMaskIcon;
            maskRect = statusPaneUsual;

            break;
            }

        case R_AVKON_STATUS_PANE_LAYOUT_SMALL:
        case R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE:
        case R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED:
            {
            // First
            TAknWindowLineLayout topAreaLayout;
            TAknsItemID bgID = KAknsIIDQsnBgNavipaneSolid;
            if ( AknLayoutUtils::CbaLocation() ==
                    AknLayoutUtils::EAknCbaLocationBottom &&
                 Layout_Meta_Data::IsLandscapeOrientation() )
                {
                // Landscape with bottom softkeys is the only landscape mode
                // in which small status pane can be shown.
                topAreaLayout =
                    AknLayoutScalable_Avkon::area_top_pane( 2 ).LayoutLine();
                // This is used because doesn't quite work with the same
                // skin item ID as in portrait mode.
                bgID = KAknsIIDQsnBgAreaStaconRt;
                }
            else
                {
                topAreaLayout =
                    AknLayoutScalable_Avkon::area_top_pane( 1 ).LayoutLine();
                }

            // The status pane fills the whole top area in this layout.
            TAknLayoutRect topAreaLayoutRect;
            topAreaLayoutRect.LayoutRect( application_window, topAreaLayout );
            TRect topAreaRect( topAreaLayoutRect.Rect() );

            aBgContext->SetLayerImage( ELayerBackground, bgID );
            aBgContext->SetLayerRect(  ELayerBackground, topAreaRect );

            // Extension
            aBgContext->SetLayerImage( ELayerExtension, KAknsIIDNone );

            // Stripe
            aBgContext->SetLayerImage( ELayerStripe, KAknsIIDNone );

            // Wallpaper
            aBgContext->SetLayerImage( ELayerWallpaper, KAknsIIDNone );
            break;
            }

        case R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT:
        case R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT:
            {
            aBgContext->SetLayerImage( ELayerStaconTop,
                                       KAknsIIDQsnBgAreaStaconRt );
            aBgContext->SetLayerRect(  ELayerStaconTop, staconTop );

            aBgContext->SetLayerImage( ELayerStaconBottom,
                                       KAknsIIDQsnBgAreaStaconRb );
            aBgContext->SetLayerRect(  ELayerStaconBottom, staconBottom );

            aBgContext->SetLayerImage( ELayerStaconWallpaper, KAknsIIDNone );

            aBgContext->SetLayerImage( ELayerStaconN, KAknsIIDNone );
            break;
            }

        case R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT:
            {
            // First
            TAknLayoutRect status_pane;
            status_pane.LayoutRect(
                application_window,
                AKN_LAYOUT_WINDOW_status_pane( application_window, 1 ) );

            // Wallpaper
            aBgContext->SetLayerImage( ELayerStaconWp, KAknsIIDWallpaper );

            // Top
            if ( aContextNumber == 0 )
                {
                aBgContext->SetLayerRect( ELayerStaconWp, staconTop );

                aBgContext->SetLayerImage( ELayerStaconSkin,
                                           KAknsIIDQsnBgAreaStaconRtIdle );
                aBgContext->SetLayerRect(  ELayerStaconSkin, staconTop );

                maskIID  = KAknsIIDQgnGrafBgLscTopMaskIcon;
                maskRect = staconTop;
                }
            // Bottom
            else if ( aContextNumber == 1 )
                {
                aBgContext->SetLayerRect( ELayerStaconWp, screen );

                aBgContext->SetLayerImage( ELayerStaconSkin,
                                           KAknsIIDQsnBgAreaStaconRbIdle );
                aBgContext->SetLayerRect(  ELayerStaconSkin, staconBottom );

                maskIID  = KAknsIIDQgnGrafBgLscBottomMaskIcon;
                maskRect = staconBottom;
                }

            break;
            }

        case R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT:
        case R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT:
            {
            aBgContext->SetLayerImage( ELayerStaconTop,
                                       KAknsIIDQsnBgAreaStaconLt );
            aBgContext->SetLayerRect(  ELayerStaconTop, staconTop );

            aBgContext->SetLayerImage( ELayerStaconBottom,
                                       KAknsIIDQsnBgAreaStaconLb );
            aBgContext->SetLayerRect(  ELayerStaconBottom, staconBottom );

            aBgContext->SetLayerImage( ELayerStaconWallpaper, KAknsIIDNone );
            break;
            }

        case R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT:
            {
            // Wallpaper
            aBgContext->SetLayerImage( ELayerStaconWp, KAknsIIDWallpaper );

            // Top
            if ( aContextNumber == 0 )
                {
                aBgContext->SetLayerRect( ELayerStaconWp, staconTop );

                aBgContext->SetLayerImage( ELayerStaconSkin,
                                           KAknsIIDQsnBgAreaStaconLtIdle );
                aBgContext->SetLayerRect(  ELayerStaconSkin, staconTop );

                maskIID  = KAknsIIDQgnGrafBgLscTopMaskIcon;
                maskRect = staconTop;
                }
            // Bottom
            else if ( aContextNumber == 1 )
                {
                aBgContext->SetLayerRect( ELayerStaconWp, screen );

                aBgContext->SetLayerImage( ELayerStaconSkin,
                                           KAknsIIDQsnBgAreaStaconLbIdle );
                aBgContext->SetLayerRect(  ELayerStaconSkin, staconBottom );

                maskIID  = KAknsIIDQgnGrafBgLscBottomMaskIcon;
                maskRect = staconBottom;
                }

            break;
            }

        case R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT:
        case R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT:
            {
            if ( aContextNumber == 0 )
                {
                // We use frame as layered context so that we can avoid having 2
                // separate bg contextes in this class. Anyway framecontext is
                // implemented using layered context so this should be quite ok
                // thing to do.

                TInt topVariety = 0;
                TInt spVariety  = 0;
                TInt bgVariety  = 0;

                TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );

                if ( isLandscape )
                    {
                    topVariety = 8;
                    spVariety  = 2;
                    bgVariety  = 1;
                    }
                else
                    {
                    topVariety = 6;
                    spVariety  = 3;
                    bgVariety  = 0;
                    }

                TAknLayoutRect layoutRect;
                layoutRect.LayoutRect(
                    application_window,
                    AknLayoutScalable_Avkon::area_top_pane( topVariety ).LayoutLine() );
                TRect topLayoutRect( layoutRect.Rect() );

                layoutRect.LayoutRect(
                    topLayoutRect,
                    AknLayoutScalable_Avkon::status_pane( spVariety ).LayoutLine() );
                TRect spRect( layoutRect.Rect() );

                layoutRect.LayoutRect(
                    spRect,
                    AknLayoutScalable_Avkon::bg_status_flat_pane( bgVariety ).LayoutLine() );
                TRect bgRect( layoutRect.Rect() );


                if ( aLayoutId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT )
                    {
                    TAknLayoutRect extension;
                        extension.LayoutRect(
                        application_window,
                        AKN_LAYOUT_WINDOW_main_pane( application_window, 0, 1, 1 ) );

                    // Wallpaper
                    aBgContext->SetLayerImage( ELayerFlatWallpaper,
                                               KAknsIIDWallpaper );
                    aBgContext->SetLayerRect(  ELayerFlatWallpaper, screen );

                    // Main pane
                    aBgContext->SetLayerImage( ELayerFlatMain,
                                               KAknsIIDQsnBgAreaMainIdle );
                    aBgContext->SetLayerRect( ELayerFlatMain, extension.Rect() );

                    // Skin background, transparency support
                    aBgContext->SetLayerImage( ELayerFlatBackground,
                                               KAknsIIDQsnBgScreenIdle );
                    aBgContext->SetLayerRect(  ELayerFlatBackground,
                                               topLayoutRect );

                    // CBA area
                    aBgContext->SetLayerImage( ELayerFlatCba,
                                               KAknsIIDQsnBgAreaControlIdle );
                    aBgContext->SetLayerRect( ELayerFlatCba, cbaRect );
                    }
                 else
                    { // Not Idle.
                    // Main pane
                    aBgContext->SetLayerImage( ELayerFlatMain, KAknsIIDNone );

                    // Wallpaper
                    aBgContext->SetLayerImage( ELayerFlatWallpaper, KAknsIIDNone );

                    // Skin background, transparency support
                    aBgContext->SetLayerImage( ELayerFlatBackground,
                                               KAknsIIDQsnBgScreen );
                    aBgContext->SetLayerRect( ELayerFlatBackground, screen );

                    // CBA area
                    aBgContext->SetLayerImage( ELayerFlatCba, aCbaBgID );
                    aBgContext->SetLayerRect( ELayerFlatCba, cbaRect );
                    }

                MAknsSkinInstance* si = AknsUtils::SkinInstance();
                CAknsItemData* idata  = NULL;
                if ( si )
                    {
                    TRAP_IGNORE(
                        idata = si->CreateUncachedItemDataL(
                            KAknsIIDQsnFrStatusFlat, EAknsITImageTable ) );
                    }

                if ( idata ) // 9 piece frame used
                    {
                    TAknWindowLineLayout layout( AknLayoutScalable_Avkon::bg_status_flat_pane_g2().LayoutLine() );
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatTl, KAknsIIDQsnFrStatusFlatCornerTl );
                    aBgContext->SetLayerRect( ELayerFlatTl, layoutRect.Rect() );

                    layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g3().LayoutLine();
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatTr, KAknsIIDQsnFrStatusFlatCornerTr );
                    aBgContext->SetLayerRect( ELayerFlatTr, layoutRect.Rect());

                    layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g4().LayoutLine();
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatBl, KAknsIIDQsnFrStatusFlatCornerBl );
                    aBgContext->SetLayerRect( ELayerFlatBl, layoutRect.Rect() );

                    layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g5().LayoutLine();
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatBr, KAknsIIDQsnFrStatusFlatCornerBr );
                    aBgContext->SetLayerRect( ELayerFlatBr, layoutRect.Rect() );

                    layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g6().LayoutLine();
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatT,  KAknsIIDQsnFrStatusFlatSideT);
                    aBgContext->SetLayerRect( ELayerFlatT, layoutRect.Rect() );

                    layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g7().LayoutLine();
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatB, KAknsIIDQsnFrStatusFlatSideB );
                    aBgContext->SetLayerRect( ELayerFlatB, layoutRect.Rect() );

                    layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g9().LayoutLine();
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatR, KAknsIIDQsnFrStatusFlatSideR );
                    aBgContext->SetLayerRect( ELayerFlatR, layoutRect.Rect() );

                    layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g8().LayoutLine();
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatL, KAknsIIDQsnFrStatusFlatSideL );
                    aBgContext->SetLayerRect( ELayerFlatL, layoutRect.Rect() );

                    layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g1().LayoutLine();
                    layoutRect.LayoutRect( bgRect, layout );
                    aBgContext->SetLayerImage( ELayerFlatCenter, KAknsIIDQsnFrStatusFlatCenter );
                    aBgContext->SetLayerRect( ELayerFlatCenter, layoutRect.Rect() );

                    if ( aLayoutId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT )
                        {
                        if ( isLandscape )
                            {
                            maskIID = KAknsIIDQgnGrafBgLscTopMaskIcon;
                            }
                        else
                            {
                            maskIID = KAknsIIDQgnGrafBgPrtTopMaskIcon;
                            }
                        maskRect = spRect;
                        }
                    }
                else // handle one piece version here
                    {
                    if ( aLayoutId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT )
                        {
                        // Wallpaper
                        aBgContext->SetLayerImage( ELayerFlatWallpaper,
                                                   KAknsIIDWallpaper );
                        aBgContext->SetLayerRect( ELayerFlatWallpaper,
                                                  staconTop );

                        // Skin background
                        aBgContext->SetLayerImage( ELayerFlatBackground,
                                                   KAknsIIDQsnFrStatusFlat );
                        aBgContext->SetLayerRect( ELayerFlatBackground, bgRect );

                        // Set all other frame parts empty as they
                        // might already be filled with something
                        for ( TInt n = ELayerFlatBackground + 1; n <= ELayerFlatCenter; n++ )
                           {
                           aBgContext->SetLayerImage( n, KAknsIIDNone );
                           }
                        if ( isLandscape )
                            {
                            maskIID = KAknsIIDQgnGrafBgLscTopMaskIcon;
                            }
                        else
                            {
                            maskIID = KAknsIIDQgnGrafBgPrtTopMaskIcon;
                            }
                        maskRect = spRect;
                        }
                    else
                        {
                        aBgContext->SetLayerImage( 0, KAknsIIDQsnFrStatusFlat );
                        aBgContext->SetLayerRect( 0, bgRect );
                        // Set all other frame parts empty as they
                        // might already be filled with something
                        for ( TInt n = 1; n <= ELayerFlatCenter; n++ )
                            {
                            aBgContext->SetLayerImage( n, KAknsIIDNone );
                            }
                        }
                    }

                delete idata;
                }
            else // context == 1 - this is the area removed from cba for clock
                 // and indicator updates.
                {
                if ( aLayoutId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT )
                    {
                    aBgContext->SetLayerImage( ELayerFlatCbaWp,
                                               KAknsIIDWallpaper );
                    aBgContext->SetLayerRect( ELayerFlatCbaWp, screen );

                    if ( Layout_Meta_Data::IsLandscapeOrientation() )
                        {
                        maskIID = KAknsIIDQgnGrafBgLscBottomMaskIcon;
                        }
                    else
                        {
                        maskIID = KAknsIIDQgnGrafBgPrtBottomMaskIcon;
                        }
                    maskRect = cbaRect;
                    }
                else
                    {
                    aBgContext->SetLayerImage( ELayerFlatCbaWp, KAknsIIDNone );
                    }

                aBgContext->SetLayerImage( ELaterFlatCbaSkin,
                                           KAknsIIDQsnBgAreaControlIdle );
                aBgContext->SetLayerRect( ELaterFlatCbaSkin, cbaRect );
                }

            break;
            }

       case R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT:
            {
            // For now we use classic statuspane
            TAknLayoutRect layoutRect;

            // Statuspane background
            aBgContext->SetLayerImage( ELayerBackground,
                                       KAknsIIDQsnBgAreaStatus );
            layoutRect.LayoutRect(
                statusPaneUsual,
                AknLayoutScalable_Avkon::status_pane_g2( 3 ).LayoutLine() );
            aBgContext->SetLayerRect( ELayerBackground, layoutRect.Rect() );

            // Navipane background graphics
            aBgContext->SetLayerImage( ELayerStripe,
                                       KAknsIIDQsnBgNavipaneSolid );
            layoutRect.LayoutRect(
                statusPaneUsual,
                AknLayoutScalable_Avkon::status_pane_g1( 4 ).LayoutLine() );
            aBgContext->SetLayerRect( ELayerStripe, layoutRect.Rect() );

            break;
            }

       case R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT:
            {
            // For now we use classic statuspane
            TAknLayoutRect layoutRect;

            // Statuspane background
            aBgContext->SetLayerImage( ELayerWallpaper, KAknsIIDWallpaper );
            layoutRect.LayoutRect(
                statusPaneUsual,
                AknLayoutScalable_Avkon::status_pane_g1( 0 ).LayoutLine() );
            aBgContext->SetLayerRect( ELayerWallpaper, screen );

            aBgContext->SetLayerImage( ELayerBackground,
                                       KAknsIIDQsnBgAreaStatusIdle );
            layoutRect.LayoutRect(
                statusPaneUsual,
                AknLayoutScalable_Avkon::status_pane_g2( 0 ).LayoutLine() );
            aBgContext->SetLayerRect( ELayerBackground, layoutRect.Rect() );

            TRect statusPaneRect( layoutRect.Rect() );

            // Navipane background graphics
            aBgContext->SetLayerImage( ELayerStripe,
                                       KAknsIIDQsnBgNavipaneSolidIdle );
            layoutRect.LayoutRect(
                statusPaneUsual,
                AknLayoutScalable_Avkon::status_pane_g1( 0 ).LayoutLine() );
            aBgContext->SetLayerRect( ELayerStripe, layoutRect.Rect() );

            aBgContext->SetLayerImage( ELayerN, KAknsIIDNone );

            maskIID  = KAknsIIDQgnGrafBgPrtTopMaskIcon;
            maskRect = statusPaneRect;

            break;
            }

        case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL:
        case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE: // fallthrough
            {
            TAknLayoutRect wideStatusPane;
            wideStatusPane.LayoutRect(
                application_window, DoCompose(
                    AknLayoutScalable_Avkon::area_top_pane( 8 ),
                    AknLayoutScalable_Avkon::status_pane( 1 ) ).LayoutLine() );
            TRect wideSPRect( wideStatusPane.Rect() );

            if ( aLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE )
                {
                aBgContext->SetLayerImage( ELayerFlatWallpaper,
                                           KAknsIIDWallpaper );
                aBgContext->SetLayerRect( ELayerFlatWallpaper, screen );

                maskIID  = KAknsIIDQgnGrafBgLscTopMaskIcon;
                maskRect = wideSPRect;
                }

            aBgContext->SetLayerImage( ELayerFlatMain, KAknsIIDNone );

            aBgContext->SetLayerImage( ELayerFlatCba, KAknsIIDNone );

            MAknsSkinInstance* si = AknsUtils::SkinInstance();
            CAknsItemData* idata  = NULL;
            if ( si )
                {
                TRAP_IGNORE( idata = si->CreateUncachedItemDataL(
                    KAknsIIDQsnFrStatusFlat, EAknsITImageTable ) );
                }

            if ( idata ) // 9 piece frame used
                {
                if ( aLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE )
                    {
                    aBgContext->SetLayerImage( ELayerFlatBackground,
                                               KAknsIIDQsnBgScreenIdle );
                    }
                else if ( aCbaBgID == KAknsIIDQsnBgAreaControlMp )
                    {
                    aBgContext->SetLayerImage( ELayerFlatBackground,
                                               KAknsIIDQsnBgScreenMp );
                    }
                else
                    {
                    aBgContext->SetLayerImage( ELayerFlatBackground,
                                               KAknsIIDQsnBgScreen );
                    }
                aBgContext->SetLayerRect( ELayerFlatBackground, screen );

                TAknWindowLineLayout layout( AknLayoutScalable_Avkon::bg_status_flat_pane_g2().LayoutLine() );
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatTl, KAknsIIDQsnFrStatusFlatCornerTl );
                aBgContext->SetLayerRect( ELayerFlatTl, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g3().LayoutLine();
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatTr, KAknsIIDQsnFrStatusFlatCornerTr );
                aBgContext->SetLayerRect( ELayerFlatTr, layoutRect.Rect());

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g4().LayoutLine();
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatBl, KAknsIIDQsnFrStatusFlatCornerBl );
                aBgContext->SetLayerRect( ELayerFlatBl, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g5().LayoutLine();
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatBr, KAknsIIDQsnFrStatusFlatCornerBr );
                aBgContext->SetLayerRect( ELayerFlatBr, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g6().LayoutLine();
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatT,  KAknsIIDQsnFrStatusFlatSideT);
                aBgContext->SetLayerRect( ELayerFlatT, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g7().LayoutLine();
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatB, KAknsIIDQsnFrStatusFlatSideB );
                aBgContext->SetLayerRect( ELayerFlatB, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g9().LayoutLine();
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatR, KAknsIIDQsnFrStatusFlatSideR );
                aBgContext->SetLayerRect( ELayerFlatR, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g8().LayoutLine();
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatL, KAknsIIDQsnFrStatusFlatSideL );
                aBgContext->SetLayerRect( ELayerFlatL, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g1().LayoutLine();
                layoutRect.LayoutRect( wideSPRect, layout );
                aBgContext->SetLayerImage( ELayerFlatCenter, KAknsIIDQsnFrStatusFlatCenter );
                aBgContext->SetLayerRect( ELayerFlatCenter, layoutRect.Rect() );

                delete idata;
                }
            else
                {
                aBgContext->SetLayerImage( ELayerFlatBackground,
                                           KAknsIIDQsnFrStatusFlat );
                aBgContext->SetLayerRect( ELayerFlatBackground,
                                          wideSPRect );
                }

            break;
            }

        case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT:
        case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT: // fallthrough
            {
            TBool idleLayout =
                aLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT;

            TAknLayoutRect flatWideStatusPane;
            flatWideStatusPane.LayoutRect(
                application_window,
                DoCompose( AknLayoutScalable_Avkon::area_top_pane( 19 ),
                           AknLayoutScalable_Avkon::status_pane( 4 ) ).LayoutLine() );
            TRect spRect( flatWideStatusPane.Rect() );

            if ( idleLayout )
                {
                aBgContext->SetLayerImage( ELayerFlatWallpaper, KAknsIIDWallpaper );
                aBgContext->SetLayerRect( ELayerFlatWallpaper, screen );
                maskIID  = KAknsIIDQgnGrafBgLscTopMaskIcon;
                maskRect = spRect;
                }

            aBgContext->SetLayerImage( ELayerFlatMain, KAknsIIDNone );

            aBgContext->SetLayerImage( ELayerFlatCba, KAknsIIDNone );

            MAknsSkinInstance* si = AknsUtils::SkinInstance();
            CAknsItemData* idata = NULL;
            if ( si )
                {
                TRAP_IGNORE(
                    idata = si->CreateUncachedItemDataL( KAknsIIDQsnFrStatusFlat,
                                                         EAknsITImageTable ) );
                }

            if ( idata ) // 9 piece frame used
                {
                if ( aCbaBgID == KAknsIIDQsnBgAreaControlMp )
                    {
                    aBgContext->SetLayerImage( ELayerFlatBackground,
                                               KAknsIIDQsnBgScreenMp );
                    }
                else
                    {
                    aBgContext->SetLayerImage(
                        ELayerFlatBackground,
                        idleLayout ? KAknsIIDQsnBgScreenIdle :
                                     KAknsIIDQsnBgScreen );
                    }
                aBgContext->SetLayerRect( ELayerFlatBackground, screen );

                TAknWindowLineLayout layout( AknLayoutScalable_Avkon::bg_status_flat_pane_g2().LayoutLine() );
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatTl, KAknsIIDQsnFrStatusFlatCornerTl );
                aBgContext->SetLayerRect( ELayerFlatTl, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g3().LayoutLine();
                layoutRect.LayoutRect( spRect, AknLayoutScalable_Avkon::bg_status_flat_pane_g3() );
                aBgContext->SetLayerImage( ELayerFlatTr, KAknsIIDQsnFrStatusFlatCornerTr );
                aBgContext->SetLayerRect( ELayerFlatTr, layoutRect.Rect());

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g4().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatBl, KAknsIIDQsnFrStatusFlatCornerBl );
                aBgContext->SetLayerRect( ELayerFlatBl, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g5().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatBr, KAknsIIDQsnFrStatusFlatCornerBr );
                aBgContext->SetLayerRect( ELayerFlatBr, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g6().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatT,  KAknsIIDQsnFrStatusFlatSideT);
                aBgContext->SetLayerRect( ELayerFlatT, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g7().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatB, KAknsIIDQsnFrStatusFlatSideB );
                aBgContext->SetLayerRect( ELayerFlatB, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g9().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatR, KAknsIIDQsnFrStatusFlatSideR );
                aBgContext->SetLayerRect( ELayerFlatR, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g8().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatL, KAknsIIDQsnFrStatusFlatSideL );
                aBgContext->SetLayerRect( ELayerFlatL, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g1().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatCenter, KAknsIIDQsnFrStatusFlatCenter );
                aBgContext->SetLayerRect( ELayerFlatCenter, layoutRect.Rect() );

                delete idata;
                }
            else
                {
                aBgContext->SetLayerImage( ELayerFlatBackground,
                                           KAknsIIDQsnFrStatusFlat );
                aBgContext->SetLayerRect( ELayerFlatBackground, spRect );
                }

            break;
            }

        case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS:
        case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS: // fallthrough
            {
            TBool idleLayout =
                aLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS;

            TAknLayoutRect flatWideStatusPane;
            flatWideStatusPane.LayoutRect(
                application_window,
                DoCompose( AknLayoutScalable_Avkon::area_top_pane( 20 ),
                           AknLayoutScalable_Avkon::status_pane( 5 ) ).LayoutLine() );
            TRect spRect( flatWideStatusPane.Rect() );

            if ( idleLayout )
                {
                aBgContext->SetLayerImage( ELayerFlatWallpaper, KAknsIIDWallpaper );
                aBgContext->SetLayerRect( ELayerFlatWallpaper, screen );
                maskIID  = KAknsIIDQgnGrafBgLscTopMaskIcon;
                maskRect = spRect;
                }

            aBgContext->SetLayerImage( ELayerFlatMain, KAknsIIDNone );

            aBgContext->SetLayerImage( ELayerFlatCba, KAknsIIDNone );

            MAknsSkinInstance* si = AknsUtils::SkinInstance();
            CAknsItemData* idata  = NULL;
            if ( si )
                {
                TRAP_IGNORE(
                    idata = si->CreateUncachedItemDataL( KAknsIIDQsnFrStatusFlat,
                                                         EAknsITImageTable ) );
                }

            if ( idata ) // 9 piece frame used
                {
                aBgContext->SetLayerImage(
                    ELayerFlatBackground,
                    idleLayout ? KAknsIIDQsnBgScreenIdle :
                                 KAknsIIDQsnBgScreen );
                aBgContext->SetLayerRect( ELayerFlatBackground, screen );

                TAknWindowLineLayout layout( AknLayoutScalable_Avkon::bg_status_flat_pane_g2().LayoutLine() );
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatTl, KAknsIIDQsnFrStatusFlatCornerTl );
                aBgContext->SetLayerRect( ELayerFlatTl, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g3().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatTr, KAknsIIDQsnFrStatusFlatCornerTr );
                aBgContext->SetLayerRect( ELayerFlatTr, layoutRect.Rect());

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g4().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatBl, KAknsIIDQsnFrStatusFlatCornerBl );
                aBgContext->SetLayerRect( ELayerFlatBl, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g5().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatBr, KAknsIIDQsnFrStatusFlatCornerBr );
                aBgContext->SetLayerRect( ELayerFlatBr, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g6().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatT,  KAknsIIDQsnFrStatusFlatSideT);
                aBgContext->SetLayerRect( ELayerFlatT, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g7().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatB, KAknsIIDQsnFrStatusFlatSideB );
                aBgContext->SetLayerRect( ELayerFlatB, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g9().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatR, KAknsIIDQsnFrStatusFlatSideR );
                aBgContext->SetLayerRect( ELayerFlatR, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g8().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatL, KAknsIIDQsnFrStatusFlatSideL );
                aBgContext->SetLayerRect( ELayerFlatL, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g1().LayoutLine();
                layoutRect.LayoutRect( spRect, layout );
                aBgContext->SetLayerImage( ELayerFlatCenter, KAknsIIDQsnFrStatusFlatCenter );
                aBgContext->SetLayerRect( ELayerFlatCenter, layoutRect.Rect() );

                delete idata;
                }
            else
                {
                aBgContext->SetLayerImage( ELayerFlatBackground,
                                           KAknsIIDQsnFrStatusFlat );
                aBgContext->SetLayerRect( ELayerFlatBackground, spRect );
                }

            break;
            }

        default:
            {
            for ( TInt n = 0; n < ELayerFlatN; n++ )
                {
                aBgContext->SetLayerImage( n, KAknsIIDNone );
                }
            }
        }

    TRAP_IGNORE( aBgContext->SetLayerMaskAndSizeL( maskIID, maskRect ) );
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::HandleResourceChange
// Handles resource change events.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneContainer::HandleResourceChange( TInt aType )
	{
	if ( aType == KEikColorResourceChange )
		{
		Window().SetBackgroundColor(
		    iEikonEnv->ControlColor( EColorStatusPaneBackground, *this ) );
        }

    if ( iControl )
        {
        iControl->HandleResourceChange( aType );
        }
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::Draw
// Draws the pane.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneContainer::Draw( const TRect& /*aRect*/ ) const
	{
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::MopSupplyObject
// Supplies a contained object to the mop-chain.
// ---------------------------------------------------------------------------
//
TTypeUid::Ptr CEikStatusPaneContainer::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == MAknsControlContext::ETypeId )
        {
        // Always return iBgContext1 to mop-chain, iBgContext2 is its parent
        // and gets redrawn automatically.
        return MAknsControlContext::SupplyMopObject( aId, iBgContext1 );
        }
    else if ( aId.iUid == CAknStatusPaneDataSubscriber::ETypeId )
        {
       	return aId.MakePtr( iDataSubscriber );
        }

    return CCoeControl::MopSupplyObject( aId );
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::WriteInternalStateL
// Writes the internal state of the control and its components to aStream.
// Does nothing in release mode.
// Designed to be overidden and base called by subclasses.
// ---------------------------------------------------------------------------
//
#ifndef _DEBUG

void CEikStatusPaneContainer::WriteInternalStateL( RWriteStream& ) const
	{
	}

#else

void CEikStatusPaneContainer::WriteInternalStateL(
    RWriteStream& aWriteStream ) const
	{
	_LIT( KEikLitStatPnCtlStart, "<CEikStatusPaneContainer>" );
	_LIT( KEikLitStatPnCtlEnd,   "<\\CEikStatusPaneContainer>" );
	_LIT( KEikLitStatPnPane,     "<iPaneId>" );
	_LIT( KEikLitStatPnPaneEnd,  "<\\iPaneId>" );

	aWriteStream << KEikLitStatPnCtlStart;
	aWriteStream << KEikLitStatPnPane;
	aWriteStream.WriteInt32L( iPaneId.iUid );
	aWriteStream << KEikLitStatPnPaneEnd;
	CCoeControl::WriteInternalStateL( aWriteStream );
	aWriteStream << KEikLitStatPnCtlEnd;
	}

#endif // _DEBUG


// ---------------------------------------------------------------------------
// CEikStatusPaneContainer::SetDimmed
// Sets the pane dimmed/undimmed.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneContainer::SetDimmed( TBool aDimmed )
	{
	CCoeControl::SetDimmed( aDimmed );
	if ( iControl )
	    {
		iControl->SetDimmed( aDimmed );
	    }
	}



// ===========================================================================
// class CEikStatusPaneTls
// ===========================================================================
//
class CEikStatusPaneTls : public CCoeStatic
	{
public:

	static void SetL( CEikStatusPaneBase& aPane );
	static void Remove( const CEikStatusPaneBase& aPane );
	static CEikStatusPaneBase* Pane();

private:

	inline CEikStatusPaneTls();
	inline static CEikStatusPaneTls* Self();

private: // Member data.

	CEikStatusPaneBase*	iPane;
	};

// Define inlines first to ensure the compiler really inlines them.

// ---------------------------------------------------------------------------
// CEikStatusPaneTls::CEikStatusPaneTls
// C++ constructor.
// ---------------------------------------------------------------------------
//
inline CEikStatusPaneTls::CEikStatusPaneTls()
	: CCoeStatic( KUidStatusPaneTls, CCoeStatic::EApp )
	{
	}

// ---------------------------------------------------------------------------
// CEikStatusPaneTls::Self
// Gets the singleton instance of CEikStatusPaneTls.
// ---------------------------------------------------------------------------
//
inline CEikStatusPaneTls* CEikStatusPaneTls::Self()
	{
	return static_cast<CEikStatusPaneTls*>(
	    CCoeEnv::Static( KUidStatusPaneTls ) );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneTls::SetL
// Sets the status pane.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneTls::SetL( CEikStatusPaneBase& aPane )
	{ // static
	CEikStatusPaneTls* self = CEikStatusPaneTls::Self();
	if ( !self )
		{
		// CCoeEnv takes ownership immediately.
		self = new (ELeave) CEikStatusPaneTls();
		}
	self->iPane = &aPane;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneTls::Remove
// Removes the current status pane.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneTls::Remove( const CEikStatusPaneBase& aPane )
	{ // static
	CEikStatusPaneTls* self = CEikStatusPaneTls::Self();
	if ( self && (TInt) ( self->iPane ) == (TInt) &aPane )
	    {
		delete self;
	    }
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneTls::Pane
// Returns the current status pane.
// ---------------------------------------------------------------------------
//
CEikStatusPaneBase* CEikStatusPaneTls::Pane()
	{ // static
	CEikStatusPaneBase* ret = NULL;
	CEikStatusPaneTls* self = CEikStatusPaneTls::Self();
	if ( self )
		{
		ret = self->iPane;
		}
	return ret;
	}


/**
 * Internal extension class
 */
class CEikStatusPaneBaseExtension : public CBase
    {
public:
    static CEikStatusPaneBaseExtension* NewL()
        {
        CEikStatusPaneBaseExtension* self =
            new (ELeave) CEikStatusPaneBaseExtension();
        CleanupStack::PushL( self );
        self->ConstructL();
        CleanupStack::Pop( self );
        return self;
        }

    void ConstructL()
        {
        iCbaBgID = KAknsIIDQsnBgAreaControl;
        };

    ~CEikStatusPaneBaseExtension()
        {
        };

public:

    /** Resource id that last has been reuqested by app using switch layout. */
	TInt iLastRequestedResourceId;

	/** Resource id that last has been used in portrait mode. */
    TInt  iLastPortraitResourceId;

    /** Resource id that last has been used in lnadscape mode. */
    TInt iLastLandscapeResourceId;

    /** Resource id that was initally defined as default id. */
    TInt iInitialResourceId;

    /** Status pane clearer is not used anymore. */
    CAknStatuspaneClearer* iBlankStatuspane;

    CAknStatusPaneDataSubscriber* iDataSubscriber;

    CAknsCombinedBackgroundControlContext* iCommonBgContext;

    /** Handles switching redraw storing on and off when required. */
    CRedrawStoreHandler* iRedrawStoreHandler;

    /** Skin background item of current CBA. */
    TAknsItemID         iCbaBgID;
    };


// ===========================================================================
// class CEikStatusPaneBase
// ===========================================================================


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::~CEikStatusPaneBase
// Destructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CEikStatusPaneBase::~CEikStatusPaneBase()
	{
	if ( iControls )
	    {
		iControls->ResetAndDestroy();
	    }
	delete iControls;
	delete iModel;
	if ( iExtension )
		{
		delete iExtension->iRedrawStoreHandler;
		delete iExtension->iBlankStatuspane;
		delete iExtension->iDataSubscriber;
		delete iExtension->iCommonBgContext;
		}
    delete iExtension;
	CEikStatusPaneTls::Remove( *this );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::Current
// Returns a pointer to the thread's currently active status pane
// without transferring ownership.  Returns NULL is no such pane exists.
// ---------------------------------------------------------------------------
//
EXPORT_C CEikStatusPaneBase* CEikStatusPaneBase::Current()
	{ // static
	return CEikStatusPaneTls::Pane();
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SwitchLayoutL
// Switch to the specified status pane layout.
// This must be one of the layouts identified in the status pane resource
// structures, otherwise the function leaves KErrNotFound.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::SwitchLayoutL( TInt aLayoutResourceId )
	{
	if ( !Clearer() && IsApp() )
		{
		// DrawNow because otherwise screenupdate looks ugly
		DoSwitchLayoutL( aLayoutResourceId, EDrawNow );
		}
    else
    	{
		// DrawDeferred can be used if the clearer does exist
    	DoSwitchLayoutL( aLayoutResourceId, EDrawDeferred );
    	}

    SetLastUsedResourceId( aLayoutResourceId );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::DoSwitchLayoutL
// Switches the status pane layout.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::DoSwitchLayoutL( TInt aLayoutResourceId,
                                          TDrawCmd aDraw )
	{
	TInt oldResId     = CurrentLayoutResId();
	TInt blankedResId = oldResId;

   	RRegion oldRegion;
   	CleanupClosePushL( oldRegion );
   	RRegion newRegion;
   	CleanupClosePushL( newRegion );
   	GetShapeL( oldRegion, ETrue, ETrue );

    TBool forcedBlank = EFalse;
    CAknStatuspaneClearer* clearer = Clearer();
    if ( clearer )
    	{
	    // We blank even if blanking has been disabled with
	    // normal disable level.
	    if ( clearer->BlankDisabled() == EBlankDisableLevelNormal )
	    	{
	    	clearer->EnableBlank();
	    	forcedBlank = ETrue;
	    	}
    	}


    // If AknLayout system is used for placing statuspane elements, then
    // we need to be less strict when new layout is applied or size change
    // is reported. This is because AknLayout data may change even when
    // statuspane layout id doesn't e.g. in dynamic variant changes etc.
    // So we check here first if either new or old one is using AknLayout.
    TBool aknLayoutUsed = iModel->AknLayoutUsed( aLayoutResourceId ) ||
                          iModel->AknLayoutUsed( CurrentLayoutResId() );

	CEikStatusPaneLayout* oldLayout = iModel->CurrentLayout();
	TRect oldRect = Rect();
    if ( IsApp() )
        {
        CEikAppStatusPaneModel* appModel =
            static_cast<CEikAppStatusPaneModel*> ( iModel );
        // This does not update serverside, we later at better time ourself call
        // CAknSgcClient::HandleChangeL()
        appModel->SetLayoutL( aLayoutResourceId, ETrue, EFalse );
        }
    else
        {
        // On server side we do this normally.
        iModel->SetLayoutL( aLayoutResourceId, OkToChangeStatusPaneNow() );
        }

	CEikStatusPaneLayout* newLayout = iModel->CurrentLayout();
	if ( newLayout != oldLayout || aknLayoutUsed )
		{
		// Need to refresh the model's layout.
	    iModel->AknLayoutRefresh();

        TBool drawNavi = ETrue;

		if ( clearer )
			{
			// Before we do the layout switch, we create a blank window to cover
    		// the non-syncronized layout transformation. This should make layout
    		// swithces look a bit smoother.
    	    //
		    if ( !clearer->BlankDisabled() )
	            {
	            TBool newBoundingRectIsLarger = ETrue;

	        	GetShapeL( newRegion, ETrue, ETrue );

                TRect newBoundingRect( newRegion.BoundingRect() );
                TRect oldBoundingRect( oldRegion.BoundingRect() );

	            newBoundingRectIsLarger =
	                ( newBoundingRect.Size().iHeight * newRegion.BoundingRect().Size().iWidth >=
	                  oldBoundingRect.Size().iHeight * oldRegion.BoundingRect().Size().iWidth );

				// If new rect is much smaller than the old, then
				// we don't want to draw navi graphics in the blanker.
	            drawNavi =
	                ( newBoundingRect.Size().iHeight >
	                  ( oldBoundingRect.Size().iHeight / 2 ) );

	    	    // First select better layout that is used for blanking.
	            if ( ( newBoundingRectIsLarger &&
	                   ( IsApp() ||
	                     forcedBlank ||
	                     oldBoundingRect.Size() == TSize(0,0) ) ) )
	                {
	                blankedResId = CurrentLayoutResId();
	    		    OptimizeClearerWindowShape( oldResId,
	    		                                CurrentLayoutResId(),
	    		                                newRegion );
	    		    clearer->SetShape( newRegion );
	                }
	            else
	                {
	                blankedResId = oldResId;
	    		    OptimizeClearerWindowShape( oldResId,
	    		                                CurrentLayoutResId(),
	    		                                oldRegion);
	    		    clearer->SetShape( oldRegion );
	                }

	            clearer->SetSkinBackgroundContext( blankedResId, drawNavi );
	            clearer->SetOrdinalPosition( 0 );

	            if ( IsApp() )
	                {
	                // timeout for serverside app
	    	        //clearer->Blank(KDefaultUnblankTimeout*3);
	    	        clearer->Blank( KDefaultUnblankTimeout );
	                }
	            else
	                {
	                // little longer timeout for serverside
	    	        //clearer->Blank(KDefaultUnblankTimeout*5);
	    	        clearer->Blank( KDefaultUnblankTimeout * 2 );
	                }
	            }
			}


        // Update serverside model (SetLayoutL)
        if ( IsApp() )
        	{
        	CAknSgcClient::HandleChangeL();
        	}

        // Trapped, so that we can always reset the blank window...
		TRAP_IGNORE( ApplyLayoutL( newLayout, aDraw ) );


		if ( oldRect != Rect() || aknLayoutUsed )
			{
			ReportSizeChange();
			}

	    // Reset blank window shape and skin context
        if ( clearer && !clearer->BlankDisabled() && !IsApp() )
        	{
   		    OptimizeClearerWindowShape( oldResId,
   		                                CurrentLayoutResId(),
   		                                newRegion );
            clearer->SetShape( newRegion );
            clearer->SetSkinBackgroundContext( CurrentLayoutResId(),
                                               drawNavi );
			clearer->DrawNow();
        	}
		}

   	CleanupStack::PopAndDestroy( 2, &oldRegion ); // close shapes

   	CAknStatusPaneDataSubscriber* subscriber = DataSubscriber();
   	if ( subscriber )
   		{
   		subscriber->RefreshDataL();
   		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::PaneRectL
// Provides the screen rectangle of a sub-pane.
// This can be used to set the size of a new control which you
// want to place in the status pane.
// This will leave with KErrNotFound if the pane ID is not valid.
// ---------------------------------------------------------------------------
//
EXPORT_C TRect CEikStatusPaneBase::PaneRectL( TPaneId aPaneId ) const
	{
	CEikStatusPaneLayoutTree* pane = iModel->CurrentLayout()->Find( aPaneId );
	if ( !pane )
		{
		User::Leave( KErrNotFound );
		}
	return pane->Rect();
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::ControlL
// Provides the control currently inside a sub-pane.
// This gives the application direct access to the contents of a pane.
// This will leave with KErrNotFound if the pane ID is not valid.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CEikStatusPaneBase::ControlL( TPaneId aPaneId ) const
	{
	CEikStatusPaneContainer* cont = Find( aPaneId );
	if ( !cont )
		{
		User::Leave( KErrNotFound );
		}
	return cont->Control();
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SwapControlL
// Swaps the control currently inside a sub-pane.
// The new control must be a fully constructed control.
// It will be placed inside the status pane, and the current content
// will be returned to the caller.
// This will leave with KErrNotFound if the pane ID is not valid.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CEikStatusPaneBase::SwapControlL(
    TPaneId aPaneId, CCoeControl* aNewControl )
	{
	CEikStatusPaneContainer* cont = Find( aPaneId );
	if ( !cont )
		{
		User::Leave( KErrNotFound );
		}

	CCoeControl* oldControl = cont->Control();
	cont->SetControl( aNewControl );

	return oldControl;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::ContainerControlL
// Provides access to the container control for a sub-pane.
// You will need access to the container control for a sub-pane if you want to
// swap in a new control. The container control should be set as the parent
// window of the new control.
// NB. It also provides a fast way to get the rectangle of the
// sub-pane (see PaneRect()).
// This will leave with KErrNotFound if the pane ID is not valid.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CEikStatusPaneBase::ContainerControlL(
    TPaneId aPaneId ) const
	{
	CEikStatusPaneContainer* cont = Find( aPaneId );
	if ( !cont )
		{
		User::Leave( KErrNotFound );
		}
	return cont;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::CEikStatusPaneBase
// C++ constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CEikStatusPaneBase::CEikStatusPaneBase( CEikonEnv& aEikEnv,
                                                 RWindowGroup* aParent )
    : iEikEnv( aEikEnv ),
      iFlags( KEikStatusPaneBaseVisibleBit ),
      iParentWindowGroup( aParent )
	{
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::BaseConstructL
// Second-phase base constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::BaseConstructL( TInt aCoreResId )
	{
	CEikStatusPaneTls::SetL( *this );

    iExtension = CEikStatusPaneBaseExtension::NewL();

	if ( IsApp() )
		{
		iExtension->iDataSubscriber = CAknStatusPaneDataSubscriber::NewL();
		}

    // Create a combined background context and two sub-contextes;
    // one for stacon top and another for stacon bottom.
    iExtension->iCommonBgContext =
        CAknsCombinedBackgroundControlContext::NewL( ETrue );

    CAknsMaskedLayerBackgroundControlContext* staconTop =
        CAknsMaskedLayerBackgroundControlContext::NewL(
            KAknsIIDWallpaper, TRect(0,0,1,1), ETrue, ELayerFlatN );
    CleanupStack::PushL( staconTop );
    iExtension->iCommonBgContext->AddControlContext( staconTop );
    CleanupStack::Pop( staconTop ); // ownership transferred

    CAknsMaskedLayerBackgroundControlContext* staconBottom =
        CAknsMaskedLayerBackgroundControlContext::NewL(
            KAknsIIDWallpaper, TRect(0,0,1,1), ETrue, ELayerFlatN );
    CleanupStack::PushL( staconBottom );
    iExtension->iCommonBgContext->AddControlContext( staconBottom );

    // Set stacon bottom as parent for stacon top.
    // this is needed as top needs to be drawn when bottom is drawn.
    staconTop->SetParentContext( staconBottom );
    CleanupStack::Pop( staconBottom ); // ownership transferred

    iExtension->iRedrawStoreHandler = new (ELeave) CRedrawStoreHandler;
    iExtension->iRedrawStoreHandler->ConstructL();

	iModel = CreateModelL( aCoreResId );
	iControls =
	    new (ELeave) CContainerControls( KEikStatusPaneControlGranularity );
	CreatePanesL();
	ApplyLayoutL( iModel->CurrentLayout(), ENoDraw );

	// Clearer is not needed anymore if all panes are drawn in app side.
	//iExtension->iBlankStatuspane = CAknStatuspaneClearer::NewL(*iParentWindowGroup, 0, !IsApp());
    //iExtension->iBlankStatuspane->SetSkinBackgroundContext(CurrentLayoutResId());

	SetInitialUsedResourceId(ReadInitialUsedResourceIdL( aCoreResId ) );
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::CreatePanesL
// Creates all the sub-panes in the current layout.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::CreatePanesL()
	{
	CEikStatusPaneSetInit* inits = iModel->PaneInits();
	const TInt count = inits->Count();
	for ( TInt ii = 0; ii < count; ++ii )
		{
		TEikStatusPaneInit& init = inits->At( ii );
		if ( COMPARE_BOOLS( init.AppOwned(), IsApp() ) )
			{
			CreatePaneL( init );
			}
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::CreatePaneL
// Creates a sub-pane.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::CreatePaneL( const TEikStatusPaneInit& aPaneInit )
    {
    CEikStatusPaneContainer* cont = CEikStatusPaneContainer::NewL(
        aPaneInit.Id(),
        aPaneInit.ControlTypeId(),
        aPaneInit.ControlResourceId(),
        iParentWindowGroup,
        static_cast<CAknsMaskedLayerBackgroundControlContext*>(
            iExtension->iCommonBgContext->GetControlContext( 0 ) ),
        static_cast<CAknsMaskedLayerBackgroundControlContext*>(
            iExtension->iCommonBgContext->GetControlContext( 1 ) ),
        iExtension->iDataSubscriber,
        *iExtension->iRedrawStoreHandler );
    CleanupStack::PushL( cont );
    iControls->AppendL( cont );
    CleanupStack::Pop( cont );
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::ApplyLayoutL
// Applies a status pane layout.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::ApplyLayoutL( CEikStatusPaneLayout* aLayout,
                                       TDrawCmd aDraw )
    {
    // We don't set all invisible, only not needed ones to avoid flicker.
    SetNotNeededInvisible();

    // Background layouts must be updated before AcceptL is called,
    // otherwise the change will not be available for controls in SizeChanged
    TInt layoutResId = CurrentLayoutResId();

    MAknsControlContext* partOfCombinedContext =
        iExtension->iCommonBgContext->GetControlContext( 0 );

    CEikStatusPaneContainer::PrepareBackgroundContext(
        static_cast<CAknsMaskedLayerBackgroundControlContext*>(partOfCombinedContext),
        layoutResId,
        ETrue,
        0,
        iExtension->iCbaBgID );

     // In stacon, make a second prepare and draw. This is due to that stacon
    // has two background contextes.
    if ( ( layoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT ||
           layoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT ||
           layoutResId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT ) )
        {
        partOfCombinedContext =
            iExtension->iCommonBgContext->GetControlContext( 1 );

        CEikStatusPaneContainer::PrepareBackgroundContext(
            static_cast<CAknsMaskedLayerBackgroundControlContext*>(partOfCombinedContext),
            layoutResId,
            ETrue,
            1,
            iExtension->iCbaBgID );
        }

	TSetRectAndVisibility vis( IsApp(), this );
	aLayout->AcceptL( &vis );

	DoDrawNow( aDraw );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SetAllInvisible
// Sets all sub-panes non-visible.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::SetAllInvisible()
	{
	const TInt count = iControls->Count();
	for ( TInt ii = 0; ii < count; ++ii )
		{
		iControls->At( ii )->MakeVisible( EFalse );
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SetNotNeededInvisible
// Sets the sub-panes that are not needed non-visible.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::SetNotNeededInvisible()
    {
	const TInt c = iControls->Count();
	TEikStatusPaneInit init;
	for ( TInt ii = 0; ii < c; ++ii )
		{
		TPaneId theid = iControls->At( ii )->Id();
		if ( iModel->CurrentLayout()->Find( theid ) == NULL )
		    {
    		iControls->At( ii )->MakeVisible( EFalse );
		    }
		}
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SetStoreHandler
// Sets the redraw storing on/off.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::SetStoreHandler( RWindow* aWindow, TBool aOn )
	{
	iExtension->iRedrawStoreHandler->SetStore( aWindow, aOn );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::DrawNow
// Draws the status pane immediately.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::DrawNow()
	{
	DoDrawNow( EDrawNow );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::DoDrawNow
// Draws the status pane with specified command.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::DoDrawNow( TDrawCmd aDraw )
	{
	if ( aDraw == ENoDraw )
		{
		return;
		}

	const TInt count = iControls->Count();
	for ( TInt ii = 0; ii < count; ++ii )
		{
		CCoeControl* control = iControls->At( ii );
		if ( aDraw == EDrawNow )
		    {
			control->DrawNow();
		    }
		else
		    {
			control->DrawDeferred();
		    }
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::OptimizeClearerWindowShape
// Optimizes the status pane blanker shape.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::OptimizeClearerWindowShape( TInt aOldResourceId,
                                                     TInt aNewResourceId,
                                                     TRegion& aRegion)
	{
	CEikStatusPaneSetInit* inits = iModel->PaneInits();
	CEikStatusPaneLayout* layout = iModel->CurrentLayout();
	const TInt count = inits->Count();
	for ( TInt ii = 0; ii < count; ++ii )
		{
		TEikStatusPaneInit& init = inits->At( ii );
		TPaneId theid            = init.Id();
        TRect oldRect( layout->AknLayoutRect( aOldResourceId, theid ) );
        TRect newRect( layout->AknLayoutRect( aNewResourceId, theid ) );
   		if ( oldRect == newRect &&
   		     newRect != TRect( 0, 0, 0, 0 ) &&
   		     oldRect != TRect( 0, 0, 0, 0 ) )
   			{
   			aRegion.SubRect( newRect );
   			}
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SetCbaAreaBackgroundID
// Sets the current CBA area skin background ID.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::SetCbaAreaBackgroundID( const TAknsItemID& aBgID,
                                                 TDrawCmd aDrawCmd )
    {
    if ( iExtension->iCbaBgID != aBgID )
        {
        TInt contextCount = 0;
        // Get first part of combination.
        MAknsControlContext* partOfCombinedContext =
            static_cast<CAknsCombinedBackgroundControlContext*>(
                iExtension->iCommonBgContext)->GetControlContext( contextCount );

        // While there are parts, fetch them and prepare each separately.
        while ( partOfCombinedContext )
            {
            CEikStatusPaneContainer::PrepareBackgroundContext(
                static_cast<CAknsMaskedLayerBackgroundControlContext*>(partOfCombinedContext),
                CurrentLayoutResId(),
                ETrue,
                contextCount,
                aBgID );

            partOfCombinedContext =
                static_cast<CAknsCombinedBackgroundControlContext*>(
                    iExtension->iCommonBgContext)->GetControlContext( ++contextCount );
            }


        iExtension->iCbaBgID = aBgID;

        DoDrawNow( aDrawCmd );
        }
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::CbaAreaBackgroundID
// Gets the current CBA area skin background ID.
// ---------------------------------------------------------------------------
//
TAknsItemID CEikStatusPaneBase::CbaAreaBackgroundID()
    {
    return iExtension->iCbaBgID;
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::Find
// Returns a sub-pane container by the specified sub-pane ID.
// ---------------------------------------------------------------------------
//
CEikStatusPaneContainer* CEikStatusPaneBase::Find( TPaneId aPaneId ) const
	{
	CEikStatusPaneContainer* ctrl = NULL;

	const TInt count = iControls->Count();
	for ( TInt ii = 0; ii < count; ++ii )
		{
		ctrl = iControls->At( ii );
		if ( ctrl->Id() == aPaneId )
			{
			break;
			}
		}

	return ctrl;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::ReduceRect
// Modifies the bounding rectangle passed in so that it lies next to the
// status pane rectangle.
// The status pane always places itself along the edge of the screen, so that
// it is consistent across applications and the server. It is assumed that the
// bounding rectangle passed in does not extend beyond the screen area.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::ReduceRect( TRect& aBoundingRect ) const
	{
	if ( !IsVisible() )
		{
		return;
		}

    // If Aknlayout is used, the shape of statuspane can be complex.
    if (iModel->AknLayoutUsed( CurrentLayoutResId() ) )
        {
        // TODO: This "algorithm" should still be improved,
        // it does not always find the right solution.
        RRegion statusPaneRegion;
        RRegion boundingRegion;
        TRect boundingRect( aBoundingRect );

        boundingRegion.AddRect( boundingRect );

        // Read statuspane shape
        TRAP_IGNORE( GetShapeL( statusPaneRegion, ETrue, ETrue ) );
        statusPaneRegion.Tidy();

        // Get largest possible rect that does not overlap with sp shape
        TRect largestBoundingRect(
            LargestBoundingRect( boundingRegion, statusPaneRegion ) );

        // Now, lets try to rotate all rects, we may find larger
        // bounding rect that way.
        RRegion rotatedBoundingRegion;

        // Rotate bounding region.
        rotatedBoundingRegion.AddRect(
            TRect( boundingRect.iTl.iY,
                   boundingRect.iTl.iX,
                   boundingRect.iBr.iY,
                   boundingRect.iBr.iX ) );

        // Construct a statuspane shape region which has rects rotated.
        RRegion rotatedStatusPaneRegion;
        TInt count = statusPaneRegion.Count();
        for ( TInt i = 0; i < count; i++ )
            {
            rotatedStatusPaneRegion.AddRect(
                TRect( statusPaneRegion[i].iTl.iY,
                       statusPaneRegion[i].iTl.iX,
                       statusPaneRegion[i].iBr.iY,
                       statusPaneRegion[i].iBr.iX ) );
            }

        // Get largest possible rect that does not overlap with sp shape.
        TRect largestBoundingRectRotated(
            LargestBoundingRect( rotatedBoundingRegion,
                                 rotatedStatusPaneRegion ) );

        rotatedStatusPaneRegion.Close();
        rotatedBoundingRegion.Close();
        statusPaneRegion.Close();
        boundingRegion.Close();

        // Now check which one was larger, if it was found by rotating
        // rects then rotate it back to real coordinates.
        if ( largestBoundingRectRotated.Height() * largestBoundingRectRotated.Width() >=
                 largestBoundingRect.Height() * largestBoundingRect.Width() )
            {
            aBoundingRect = TRect( largestBoundingRectRotated.iTl.iY,
                                   largestBoundingRectRotated.iTl.iX,
                                   largestBoundingRectRotated.iBr.iY,
                                   largestBoundingRectRotated.iBr.iX );
            }
        else
            {
            aBoundingRect = largestBoundingRect;
            }
        }
    else
        {
        TRect rect( Rect() );

	    if ( rect.iTl.iX > aBoundingRect.iTl.iX )
	        {
		    aBoundingRect.iBr.iX = rect.iTl.iX;
	        }
	    if ( rect.iBr.iX < aBoundingRect.iBr.iX )
	        {
		    aBoundingRect.iTl.iX = rect.iBr.iX;
	        }
	    if ( rect.iTl.iY > aBoundingRect.iTl.iY )
	        {
		    aBoundingRect.iBr.iY = rect.iTl.iY;
	        }
	    if ( rect.iBr.iY < aBoundingRect.iBr.iY )
	        {
		    aBoundingRect.iTl.iY = rect.iBr.iY;
	        }
        }
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::LargestBoundingRect
// Gets the largest bounding rectangle that contains the specified region.
// ---------------------------------------------------------------------------
//
TRect CEikStatusPaneBase::LargestBoundingRect( TRegion& aWholeRegion,
                                               TRegion& aRemovedRegion ) const
    {
    TInt count = aRemovedRegion.Count();
    for ( TInt i = 0; i < count; i++ )
        {
        aWholeRegion.SubRect( aRemovedRegion[i] );
        }

    aWholeRegion.Tidy();
    TInt count2 = aWholeRegion.Count();

    TRect largestBoundingRect( 0, 0, 0, 0 );
    for ( TInt j = 0; j < count2; j++ )
        {
        TRect boundingRect( aWholeRegion[j] );
        if ( boundingRect.Height() * boundingRect.Width() >=
                 largestBoundingRect.Height() * largestBoundingRect.Width() )
            {
            largestBoundingRect = boundingRect;
            }
        }

    // Return largest bounding rect.
    return largestBoundingRect;
    }


/**
 * Visitor class for collecting the sub-pane areas to a single region.
 */
NONSHARABLE_CLASS( TStatusPaneRegionCollector )
    : public MEikStatusPaneLayoutTreeVisitor
	{
public:

	TStatusPaneRegionCollector( CEikStatusPaneSetInit* aPanes,
	                            TRegion& aRegion,
	                            TBool aIncludeAppPanes,
	                            TBool aIncludeServerPanes );

	void VisitL( CEikStatusPaneLayoutTree* aNode );

private:

	CEikStatusPaneSetInit* iPanes;
	TRegion&               iRegion;
	TBool                  iIncludeAppPanes;
	TBool                  iIncludeServerPanes;
	};


// ---------------------------------------------------------------------------
// TStatusPaneRegionCollector::TStatusPaneRegionCollector
// C++ constructor.
// ---------------------------------------------------------------------------
//
TStatusPaneRegionCollector::TStatusPaneRegionCollector(
    CEikStatusPaneSetInit* aPanes,
    TRegion& aRegion,
    TBool aIncludeAppPanes,
    TBool aIncludeServerPanes )
    : iPanes( aPanes ),
      iRegion( aRegion ),
      iIncludeAppPanes( aIncludeAppPanes ),
      iIncludeServerPanes( aIncludeServerPanes )
	{
	}


// ---------------------------------------------------------------------------
// TStatusPaneRegionCollector::VisitL
// Visit method status pane region collector.
// ---------------------------------------------------------------------------
//
void TStatusPaneRegionCollector::VisitL( CEikStatusPaneLayoutTree* aNode )
	{
	TBool appOwned = iPanes->FindL( aNode->Id() ).AppOwned();
    TRect rect( aNode->Rect() );
	if ( ( appOwned && iIncludeAppPanes ) ||
	     ( !appOwned && iIncludeServerPanes ) )
		{
		iRegion.AddRect( rect );
		}
	else
		{
		iRegion.SubRect( rect );
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::GetShapeL
// Adds and removes pane rectangles from aRegion.
// App panes are added is aIncludeAppPanes is ETrue, otherwise they are
// removed. The same holds for server panes and aIncludeServerPanes.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::GetShapeL( TRegion& aRegion,
                                             TBool aIncludeAppPanes,
                                             TBool aIncludeServerPanes ) const
	{
	TStatusPaneRegionCollector collector( iModel->PaneInits(),
	                                      aRegion,
	                                      aIncludeAppPanes,
	                                      aIncludeServerPanes );
	iModel->CurrentLayout()->AcceptL( &collector );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SetFlags
// Sets all the visual flags at once (dimmed and visible).
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::SetFlags( TInt aFlags )
	{
	MakeVisible( aFlags & KEikStatusPaneBaseVisibleBit );
	SetDimmed( aFlags & KEikStatusPaneBaseDimmedBit );
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::Flags
// Returns the status pane flags.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CEikStatusPaneBase::Flags() const
	{
	return iFlags;
	}

// ---------------------------------------------------------------------------
// CEikStatusPaneBase::MakeVisible
// Sets the visiblility of the status pane and its contents.
// Same as CCoeControl::MakeVisible().
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::MakeVisible( TBool aVisible )
	{
	if ( COMPARE_BOOLS( aVisible, IsVisible() ) )
		{
		return;
		}

	if ( aVisible )
		{
		iFlags |= KEikStatusPaneBaseVisibleBit;
		TSetRectAndVisibility vis( IsApp(), this );
		// Won't leave because TSetRectAndVisibility only looks for
		// panes that it knows exist.
		TRAP_IGNORE( iModel->CurrentLayout()->AcceptL( &vis ) );
		DoDrawNow( EDrawDeferred );
		}
	else
		{
		iFlags &= ~KEikStatusPaneBaseVisibleBit;
		SetAllInvisible();
		}

	ReportSizeChange();
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SetDimmed
// Sets the dimmed state of the status pane and its contents.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::SetDimmed( TBool aDimmed )
	{
	if ( COMPARE_BOOLS( aDimmed, IsDimmed() ) )
		{
		return;
		}

	if ( aDimmed )
		{
		iFlags |= KEikStatusPaneBaseDimmedBit;
		}
	else
		{
		iFlags &= ~KEikStatusPaneBaseDimmedBit;
		}

	const TInt count = iControls->Count();
	for ( TInt ii = 0; ii < count; ++ii )
		{
		iControls->At( ii )->SetDimmed( aDimmed );
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SetFaded
// Does nothing - fading is now handled by Window Server and
// the Application Framework.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::SetFaded( TBool /*aFaded*/ )
	{
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::HandleResourceChange
// Passes the HandleResourceChange() signal to all sub parts
// of the status pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::HandleResourceChange( TInt aType )
	{
	if ( aType == KEikDynamicLayoutVariantSwitch )
		{
        TBool landscape( Layout_Meta_Data::IsLandscapeOrientation() );
        TInt  currentLayoutResId( CurrentLayoutResId() );
		TInt  resId( 0 );

        if ( IsApp() )
            {
            // Check if current layout is supported in this orientation and
            // if it has been set by the application...
            if ( currentLayoutResId == AVKONENV->StatusPaneResIdForCurrentLayout( currentLayoutResId ) &&
                    ( currentLayoutResId == iExtension->iLastLandscapeResourceId ||
                    currentLayoutResId == iExtension->iLastPortraitResourceId ) )
                {
                // ...supported, then we use it !
                resId = currentLayoutResId;
                }
            // ...if not, then check the last ID app has used when calling
            // SwitchLayout(), and if it's supported in this orientation...
            else if (iExtension->iLastRequestedResourceId != 0 &&
                    ( landscape && SupportedLandscapeResId( iExtension->iLastRequestedResourceId ) ||
                    ( !landscape && SupportedPortraitResId( iExtension->iLastRequestedResourceId ) ) ) )
                {
                resId = iExtension->iLastRequestedResourceId;
                }
            else
                {
                // ...not supported, then find most suitable one...
                // Get the last layout used in this orientation
                resId = LastUsedResourceId();

                // If suitable layout still not found for some reason
                // then default to initial one.
                if ( resId == 0 )
                    {
                    resId = InitialUsedResourceId();
                    }
                }
		    }
		else
		    {
		    resId = currentLayoutResId;
		    }

        // Reset current layout so that layout for the new
        // orientation/language is used.
		// Note, drawing is not done in this case, as it is assumed that the
		// controls will draw themselves if necessary.
		// This prevents double drawing.

	    CAknStatuspaneClearer* clearer = Clearer();
		if ( clearer )
			{
			clearer->UnBlank();
			// Disable statuspane own blanker, if screenblanker does blanking.
			clearer->DisableBlank( EBlankDisableLevelHigh );
			}

		TRAP_IGNORE( DoSwitchLayoutL( resId, ENoDraw ) );
		if ( clearer )
			{
	        clearer->SetDefaultShape();
	        clearer->SetSkinBackgroundContext( CurrentLayoutResId() );
	        clearer->SetOrdinalPosition( 0 );
			clearer->EnableBlank();
			}
		}
    else if ( aType == KAknsMessageSkinChange )
        {
        CEikStatusPaneContainer::PrepareBackgroundBaseContext(
            iExtension->iCommonBgContext,
            CurrentLayoutResId(),
            ENoDraw );

		CAknStatuspaneClearer* clearer = Clearer();
		if ( clearer )
			{
        	clearer->SetSkinBackgroundContext( CurrentLayoutResId() );
			}
        }
    // The following fixes EAKH-78RBFS
    else if ( aType == KEikMessageUnfadeWindows )
        {
        DoDrawNow( EDrawDeferred );
        }

	const TInt count = iControls->Count();
	for ( TInt ii = 0; ii < count; ++ii )
		{
		iControls->At( ii )->HandleResourceChange( aType );
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::IsVisible
// Returns the visibility of the status pane.
// Same as CCoeControl::IsVisible().
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CEikStatusPaneBase::IsVisible() const
	{
	return iFlags & KEikStatusPaneBaseVisibleBit;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::IsDimmed
// Returns the dimming state of the status pane.
// Same as CCoeControl::IsDimmed().
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CEikStatusPaneBase::IsDimmed() const
	{
	return iFlags & KEikStatusPaneBaseDimmedBit;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::IsFaded
// Returns EFalse.
// Fading is now handled by Window Server and the Application Framework.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CEikStatusPaneBase::IsFaded() const
	{
	return iAvkonAppUiBase->IsFaded();
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::PaneCapabilities
// Returns the capabilities of a sub pane.
// ---------------------------------------------------------------------------
//
EXPORT_C CEikStatusPaneBase::TPaneCapabilities CEikStatusPaneBase::PaneCapabilities(
    TPaneId aPaneId ) const
	{
	TPaneCapabilities caps;
	TEikStatusPaneInit* init = NULL;
	TRAPD( err, init = &iModel->PaneInits()->FindL( aPaneId ) );
	if ( !err )
		{
		caps.SetPresent();
		if ( init && init->AppOwned() )
			{
			caps.SetAppOwned();
			}
		if ( iModel->CurrentLayout()->Find( aPaneId ) != NULL )
			{
			caps.SetInCurrentLayout();
			}
		}
	return caps;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::ReportSizeChange
// Reports status pane size change to the observer.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::ReportSizeChange()
	{
    // If Aknlayout is used, then it is possible that statuspane
    // panes can be located almost "everywhere" in the screen area.
    // Notify here first CBA about size change so that it can adjust itself.
    if ( iModel && iModel->AknLayoutUsed( CurrentLayoutResId() ) )
        {
        CEikButtonGroupContainer* cba = iEikEnv.AppUiFactory()->Cba();
        TRect cbaBoundingRect( 0, 0, 0, 0 ); // dummy
        if ( cba )
        	{
            cba->SetBoundingRect( cbaBoundingRect );
        	}
        }


    // Now let observers adjust their sizes etc.
	if ( iObserver )
		{
		iObserver->HandleStatusPaneSizeChange();
		}

    // If this statuspane is in embedded app, then inform
    // also embedding app about the statuspane size change. This prevents
    // embedding app from clipping serverside pane drawing.
    CEikAppUi* appUi = iEikEnv.EikAppUi();
	if ( appUi && appUi->ContainerAppUi() )
		{
		appUi = appUi->ContainerAppUi();
		MEikAppUiFactory* factory = iEikEnv.AppUiFactory( *appUi );
		if ( factory )
			{
			CEikStatusPane* statusPane = factory->StatusPane();
			if ( statusPane && statusPane != this )
			    {
				statusPane->ReportSizeChange();
			    }
			}
		}

#ifdef RD_SCALABLE_UI_V2
    // Notify touch pane of size change.
    CAknTouchPane* touchPane = iAvkonAppUi->TouchPane();
    if ( touchPane )
        {
        TInt initial = InitialUsedResourceId();
        TInt last    = iExtension ? iExtension->iLastRequestedResourceId : NULL;
        touchPane->HandleStatusPaneSizeChange( initial, last );
        }
#endif // RD_SCALABLE_UI_V2
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::CurrentLayoutResId
// Returns the current status pane layout resource ID.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CEikStatusPaneBase::CurrentLayoutResId() const
	{
	if ( iModel )
	    {
	    return iModel->CurrentLayoutResId();
	    }
	else
	    {
	    return KErrNotFound;
	    }
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::OkToChangeStatusPaneNow
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CEikStatusPaneBase::OkToChangeStatusPaneNow()
	{
	return ETrue;
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::TSetRectAndVisibility::TSetRectAndVisibility
// Constructor of the visitor class for setting sub-pane rects and
// visibilities.
// ---------------------------------------------------------------------------
//
CEikStatusPaneBase::TSetRectAndVisibility::TSetRectAndVisibility(
    TBool aIsApp, CEikStatusPaneBase* aStatusPane )
    : iIsApp( aIsApp ), iStatusPane( aStatusPane )
	{
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::TSetRectAndVisibility::VisitL
// Visit method for setting the rect and visibility of sub-panes.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::TSetRectAndVisibility::VisitL(
    CEikStatusPaneLayoutTree* aNode )
	{
	TBool appOwned =
	    iStatusPane->iModel->PaneInits()->FindL( aNode->Id() ).AppOwned();

	if ( COMPARE_BOOLS( appOwned, iIsApp ) )
		{
		CEikStatusPaneContainer* cont = iStatusPane->Find( aNode->Id() );
		if (NULL != cont)
		    {
            cont->SetRect( aNode->Rect() );
            cont->MakeVisible( iStatusPane->IsVisible() );
		    }
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::TPaneCapabilities::TPaneCapabilities
// Constructor for TPaneCapabilities object.
// ---------------------------------------------------------------------------
//
CEikStatusPaneBase::TPaneCapabilities::TPaneCapabilities() : iFlags( 0 )
	{
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::SetLastUsedResourceId
// Sets the status pane layout resource ID last used.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::SetLastUsedResourceId( TInt aResourceId )
    {
    if ( !iExtension )
    	{
        return;
    	}

	iExtension->iLastRequestedResourceId = aResourceId;

    // Check if the resource ID is supported in the current orientation.
    // Without this check it may happen that iLastPortraitResourceId gets
    // status pane resource of landscape status pane. If this would happen
    // following portrait status pane layout can fallback to wrong layout.
    //
    // if (aResourceId == AVKONENV->StatusPaneResIdForCurrentLayout(aResourceId))
	//
	// NOTE: Check mentioned above has been commented out because it may
	// cause other problems if there are other layout id mappings used in
	// addition to landscape/portrait mappings.
	// It should be enough to use Layout_Meta_Data::IsLandscapeOrientation()
	// when checking the orientation instead of the screendevice,
	// so no confusions should appear.

    // Update last used resource ID in the current orientation so that
    // we can restore it when orientation changes back.
	//
	// It is important to check orientation from layout instead of
	// the screendevice because of delayed layout switch
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        iExtension->iLastLandscapeResourceId = aResourceId;
        }
    else
        {
        iExtension->iLastPortraitResourceId = aResourceId;
        }
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::LastUsedResourceId
// Returns the status pane layout resource ID last used.
// ---------------------------------------------------------------------------
//
TInt CEikStatusPaneBase::LastUsedResourceId()
    {
    if ( !iExtension )
    	{
        return 0;
    	}

	// It is important to check orientation from layout instead of the
	// screendevice because of delayed layout switch.
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        return iExtension->iLastLandscapeResourceId;
        }
    else
        {
        return iExtension->iLastPortraitResourceId;
        }
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::ReadInitialUsedResourceIdL
// Reads the initial status pane ID from resource.
// ---------------------------------------------------------------------------
//
TInt CEikStatusPaneBase::ReadInitialUsedResourceIdL( TInt aCoreResId )
    {
	TResourceReader res;
	iEikEnv.CreateResourceReaderLC( res, aCoreResId );
   	const TInt count = res.ReadInt16();

	for ( TInt ii = 0; ii < count; ++ii )
		{
		TEikStatusPaneInit init;
		init.LoadDefaults( res );
		}

    // This is the only thing in the resource that we are interested in...
    TInt defaultResource = res.ReadUint32();
	CleanupStack::PopAndDestroy();	// res

    return defaultResource;
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::InitialUsedResourceId
// Sets the initial status pane resource ID.
// ---------------------------------------------------------------------------
//
void CEikStatusPaneBase::SetInitialUsedResourceId( TInt aResourceId )
    {
    if ( !iExtension )
    	{
        return;
    	}
    iExtension->iInitialResourceId = aResourceId;
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::InitialUsedResourceId
// Returns the initially used status pane resource ID.
// ---------------------------------------------------------------------------
//
TInt CEikStatusPaneBase::InitialUsedResourceId()
    {
    if ( !iExtension )
    	{
        return 0;
    	}

    return iExtension->iInitialResourceId;
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::Clearer
// Returns pointer to the status pane blanker.
// ---------------------------------------------------------------------------
//
CAknStatuspaneClearer* CEikStatusPaneBase::Clearer()
    {
    return iExtension->iBlankStatuspane;
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::DisableClearer
// Disables or enables the status pane blanker.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::DisableClearer( TBool aDisabled )
    {
  	CAknStatuspaneClearer* clearer = Clearer();
    if ( aDisabled )
    	{
		if ( clearer )
			{
	    	clearer->DisableBlank( EBlankDisableLevelNormal );
	    	clearer->UnBlank();
			}
    	}
    else
    	{
    	if ( clearer )
    		{
    		clearer->EnableBlank();
    		}
    	}
    }


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::CommonPrepareForAppExit
// Prepares for application exit.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPaneBase::CommonPrepareForAppExit()
	{
	if ( IsApp() )
		{
    	// Blank statuspane during app exit.
    	CAknStatuspaneClearer* clearer = Clearer();
    	if ( clearer )
    		{
	    	clearer->EnableBlank();
		    clearer->SetSkinBackgroundContext( CurrentLayoutResId(), ETrue );
			clearer->SetDefaultShape();
		    clearer->SetOrdinalPosition( 0 );
			clearer->Blank();
    		}
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPaneBase::DataSubscriber
// Returns pointer to the status pane data subscriber.
// ---------------------------------------------------------------------------
//
CAknStatusPaneDataSubscriber*  CEikStatusPaneBase::DataSubscriber() const
	{
	if ( iExtension )
		{
		return iExtension->iDataSubscriber;
		}
	else
		{
		return NULL;
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::NewL
// Factory method for the application side status pane.
// ---------------------------------------------------------------------------
//
EXPORT_C CEikStatusPane* CEikStatusPane::NewL( CEikonEnv& aEikEnv,
                                               RWindowGroup* aParent,
                                               TInt aCoreStatusPaneModelResId,
                                               TInt aAppStatusPaneModelId )
	{
	CEikStatusPane* self =
	    new (ELeave) CEikStatusPane( aEikEnv, aParent, aAppStatusPaneModelId );
	CleanupStack::PushL( self );
	self->ConstructL( aCoreStatusPaneModelResId );
    CleanupStack::Pop( self );
	return self;
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::CreateModelL
// Creates the status pane model.
// ---------------------------------------------------------------------------
//
CEikStatusPaneModelBase* CEikStatusPane::CreateModelL( TInt aCoreResId ) const
	{
	return CEikAppStatusPaneModel::NewL(
	    iEikEnv, aCoreResId, iAppDeclId, ETrue );
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::IsApp
// ---------------------------------------------------------------------------
//
TBool CEikStatusPane::IsApp() const
	{
	return ETrue;
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::CEikStatusPane
// C++ constructor.
// ---------------------------------------------------------------------------
//
CEikStatusPane::CEikStatusPane( CEikonEnv& aEikEnv,
                                RWindowGroup* aParent,
                                TInt aAppStatusPaneModelId )
    : CEikStatusPaneBase( aEikEnv, aParent ),
      iAppDeclId( aAppStatusPaneModelId )
	{
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::~CEikStatusPane
// Destructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CEikStatusPane::~CEikStatusPane()
	{
	// If this is an embedded app, tell the underlying statuspane
	// to unhide itself.
	CEikAppUi* appUi = iEikEnv.EikAppUi();
	if ( appUi && appUi->ContainerAppUi() )
		{
		appUi = appUi->ContainerAppUi();
		MEikAppUiFactory* factory = iEikEnv.AppUiFactory( *appUi );
		if ( factory )
			{
			CEikStatusPane* statusPane = factory->StatusPane();
			if ( statusPane )
			    {
				statusPane->HideAppPanes( EFalse );
			    }
			}
		}

	delete iDelayedForegroundObserver;
    iEikEnv.RemoveForegroundObserver( *this );
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CEikStatusPane::ConstructL( TInt aCoreResId )
	{
	BaseConstructL( aCoreResId );

	if ( iAppDeclId != EEikStatusPaneUseDefaults )
		{
	    SetInitialUsedResourceId(
	        ReadInitialUsedResourceIdL( aCoreResId, iAppDeclId ) );
		}

    iEikEnv.AddForegroundObserverL( *this );
	CAknStatusPaneDataSubscriber* subscriber = DataSubscriber();
	// Syncronize data from server here so that we have
    // up to date state before first draw.
	if ( subscriber )
		{
		subscriber->RefreshDataL();
		}

	CAknStatuspaneClearer* clearer = Clearer();
	if ( clearer )
		{
		clearer->SetOrdinalPosition( 0 );
		RAknUiServer* client = CAknSgcClient::AknSrv();
		TInt appResInServerside = client->CurrentAppStatuspaneResource();
		TInt appResInClientside = CurrentLayoutResId();

	   	RRegion region;
	   	CleanupClosePushL( region );
	   	GetShapeL( region, ETrue, ETrue );
	    OptimizeClearerWindowShape( appResInServerside,
	                                appResInClientside,
	                                region );
		clearer->SetShape( region );
	    clearer->SetSkinBackgroundContext( CurrentLayoutResId() );
		CleanupStack::PopAndDestroy( &region );
		clearer->Blank( KDefaultUnblankTimeout );
	    clearer->DisableBlank( EBlankDisableLevelNormal );
		iDelayedForegroundObserver = CAknDelayedForegroundObserver::NewL( this );
		// This is not really needed (?). Consumes about 60ms in app startup
		//DoDrawNow(EDrawNow);
		}
	else
		{
		DoDrawNow( EDrawDeferred );
		}
    }


// ---------------------------------------------------------------------------
// CEikStatusPane::MakeVisible
// Makes status pane visible or non-visible.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPane::MakeVisible( TBool aVisible )
	{
	// This call must be made before the setting the refresh levels
	// in order for the incall status bubble to be hidden when
	// status pane is made non-visible.
	CEikStatusPaneBase::MakeVisible( aVisible );

	CAknStatusPaneDataSubscriber* subscriber = DataSubscriber();
	if ( subscriber )
		{
		if ( !aVisible )
			{
			subscriber->SetRefreshLevel(
			    CAknStatusPaneDataSubscriber::ERefreshLevelNone, EFalse );
			}
		else
			{
			subscriber->SetRefreshLevel(
			    CAknStatusPaneDataSubscriber::ERefreshLevelMedium, EFalse );
			}
		}

	ApplyCurrentFlags();
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::SetDimmed
// Sets status pane dimmed/undimmed.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPane::SetDimmed( TBool aDimmed )
	{
	CEikStatusPaneBase::SetDimmed( aDimmed );
	ApplyCurrentFlags();
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::SetFaded
// Handled by Window Server and Application Framework.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPane::SetFaded( TBool /*aFaded*/ )
	{
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::HandleResourceChange
// Passes the HandleResourceChange() signal to all sub parts
// of the status pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPane::HandleResourceChange( TInt aType )
	{
	CEikStatusPaneBase::HandleResourceChange( aType );

    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        // CEikStatusPaneBase::HandleResourceChange has set all panes visible
        // by default. If we are embedding app, then hide the panes here.
        TBool embedding = ( this != Current() );
        HideAppPanes( embedding );
        }

	if ( aType == KEikMessageEmbedLevelChange )
		{
        // Report statuspane change if this is NOT in embedded app
        CEikAppUi* appUi = iEikEnv.EikAppUi();
	    if ( appUi && !appUi->ContainerAppUi() )
		    {
            ReportSizeChange();
		    }
		const TBool appPaneVis = ( this == Current() );
		HideAppPanes( !appPaneVis );
		if ( appPaneVis )
			{
			// Function doesn't actually leave
			TRAP_IGNORE( ApplyCurrentSettingsL() );
			}
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::ApplyCurrentSettingsL
// Synchronises the server status pane layout with the
// application status pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPane::ApplyCurrentSettingsL()
	{
	static_cast<CEikAppStatusPaneModel*>( iModel )->ApplyCurrentLayoutL();
	ApplyCurrentFlags();
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::ApplyCurrentFlags
// Applies current flags to the server side.
// ---------------------------------------------------------------------------
//
void CEikStatusPane::ApplyCurrentFlags()
	{
	TRAP_IGNORE( CAknSgcClient::HandleChangeL() );
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::OkToChangeStatusPaneNow
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CEikStatusPane::OkToChangeStatusPaneNow()
	{
	return ETrue;
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::PrepareForAppExit
// Prepares for application exit.
// ---------------------------------------------------------------------------
//
EXPORT_C void CEikStatusPane::PrepareForAppExit()
	{
	CommonPrepareForAppExit();
	CAknSgcClient::PrepareForAppExit();
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::HandleGainingForeground
// Handles gaining foreground.
// ---------------------------------------------------------------------------
//
void CEikStatusPane::HandleGainingForeground()
	{
	// Make sure no delayed calls are active.
	if ( iDelayedForegroundObserver )
		{
		iDelayedForegroundObserver->StopDelayedObservation();
		}

    CAknStatuspaneClearer* clearer = Clearer();
	if ( clearer )
		{
		TInt appResInClientside = CurrentLayoutResId();
		RAknUiServer* client = CAknSgcClient::AknSrv();
		if ( client )
			{
	   		client->SetCurrentAppStatuspaneResource( appResInClientside );
			}

		// Enable window redraw storing when we are foreground.
		const TInt count = iControls->Count();
		for ( TInt ii = 0; ii < count; ++ii )
			{
			RWindow* window =
			    static_cast<RWindow*>( iControls->At(ii)->DrawableWindow() );
			SetStoreHandler( window, KEnableRedrawStoring );
			}
		}

    // Report statuspane change if we are in embedded app.
    CEikAppUi* appUi = iEikEnv.EikAppUi();
	if ( appUi && appUi->ContainerAppUi() )
		{
        ReportSizeChange();
		}
    }


// ---------------------------------------------------------------------------
// CEikStatusPane::HandleLosingForeground
// Handles losing foreground.
// ---------------------------------------------------------------------------
//
void CEikStatusPane::HandleLosingForeground()
	{
    CAknStatuspaneClearer* clearer = Clearer();
	if ( clearer )
		{
		//
		// Window redraw storing is disabled here to avoid flicker when
		// foreground next time is gained because of the status pane clearer.
		//
		RAknUiServer* client = CAknSgcClient::AknSrv();
		TInt appResInClientside = CurrentLayoutResId();
		TInt appResInServerside = client->StatusPaneResourceId();
		TBool faded = EFalse;
		client->IsSystemFaded( faded );
		// Fading is checked so that we don't disable redrawing during
		// fade because unfading looks ugly if redrawing is disabled.
		if ( appResInClientside != appResInServerside || !faded )
			{
			const TInt count = iControls->Count();
			for ( TInt ii = 0; ii < count; ++ii )
				{
				RWindow* window =
				    static_cast<RWindow*>( iControls->At( ii )->DrawableWindow() );
				SetStoreHandler( window, EFalse );
				}

			// Make sure no delayed HandleLosingForeground-calls are active.
			if ( iDelayedForegroundObserver )
				{
				iDelayedForegroundObserver->StopDelayedObservation();
				}
			}
		else if ( iDelayedForegroundObserver &&
		          !iDelayedForegroundObserver->IsDelayedCallbackActive() )
			{
			// If we could not yet turn redraw storing off, we try few times
			// with timer. If not succesful, then result may be some
			// additional flicker when becoming to foreground again.
			iDelayedForegroundObserver->StartDelayedForegroundLossObservation(
			    1000000, 15 ); // 1s interval, 15 times.
			}
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::DoHandleLosingForegroundL
// Handles losing foreground.
// ---------------------------------------------------------------------------
//
void CEikStatusPane::DoHandleLosingForegroundL()
    {
    }



// ---------------------------------------------------------------------------
// CEikStatusPane::HideAppPanes
// Hides the application owned sub-panes.
// ---------------------------------------------------------------------------
//
void CEikStatusPane::HideAppPanes( TBool aHide )
	{
	CEikStatusPaneSetInit* paneSet = iModel->PaneInits();
	const TInt count = paneSet->Count();
	for ( TInt ii = 0; ii < count; ii++ )
		{
		TEikStatusPaneInit& paneInit = (*paneSet)[ii];
		if ( paneInit.AppOwned() )
			{
			CEikStatusPaneContainer* container = Find( paneInit.Id() );
			if ( container )
				{
				if ( aHide )
					{
					if ( container->IsVisible() )
						{
						paneInit.SetHidden();
						container->MakeVisible( !aHide );
						}
					}
				else
					{
					if ( paneInit.IsHidden() )
						{
						paneInit.ClearHidden();
						container->MakeVisible( !aHide );
						}
					}
				}
			}
		}
	}


// ---------------------------------------------------------------------------
// CEikStatusPane::ReadInitialUsedResourceIdL
// Reads the inital status pane resource ID.
// ---------------------------------------------------------------------------
//
TInt CEikStatusPane::ReadInitialUsedResourceIdL( TInt aCoreResId,
                                                 TInt aAppStatusPaneModelResId )
    {
    TInt  id    = 0;
    TBool found = EFalse;
    TInt  ii    = 0;

    // First check if given aAppStatusPaneModelResId
    // is one of the legal resource IDs.
	TResourceReader res;
	iEikEnv.CreateResourceReaderLC( res, aCoreResId );
   	const TInt count = res.ReadInt16();

	for ( ii = 0; ii < count; ++ii )
		{
		TEikStatusPaneInit init;
		init.LoadDefaults( res );
		}

    TInt defaultResource = res.ReadUint32();

   	const TInt layoutCount = res.ReadInt16();
	for ( ii = 0; ii < layoutCount; ++ii )
		{
		TInt layoutRes = res.ReadInt32();
		if ( aAppStatusPaneModelResId == layoutRes )
		    {
		    id    = aAppStatusPaneModelResId;
		    found = ETrue;
		    }
		}

	CleanupStack::PopAndDestroy();	// res

    // If ID is not any of the valid resources, then read app model.
    if ( !found )
        {
    	TResourceReader res2;
    	iEikEnv.CreateResourceReaderLC( res2, aAppStatusPaneModelResId );
        // This is the only thing in the resource that we are interested in...

        TInt appId = res2.ReadUint32();

        // App may have set it to use default statuspane layout.
        if ( appId != EEikStatusPaneUseDefaults )
        	{
       	    id = appId;
        	}
        else
        	{
            id = defaultResource;
        	}

    	CleanupStack::PopAndDestroy();	// res2
        }

    return id;
    }


// ===========================================================================
// CAknStatuspaneClearer, class for drawing a blank statuspane.
// ===========================================================================

// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::NewLC
// Two-phase constructor.
// ---------------------------------------------------------------------------
//
CAknStatuspaneClearer* CAknStatuspaneClearer::NewLC( RWindowGroup& aParent,
                                                     TInt aStatuspaneLayoutId,
                                                     TBool aOwnWindowGroup )
	{
	CAknStatuspaneClearer* self = new (ELeave) CAknStatuspaneClearer;
	CleanupStack::PushL( self );
	self->ConstructL( aParent, aStatuspaneLayoutId, aOwnWindowGroup );
	AKNTASHOOK_ADDL( self, "CAknStatuspaneClearer" );
	return self;
	}


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::NewL
// Two-phase constructor.
// ---------------------------------------------------------------------------
//
CAknStatuspaneClearer* CAknStatuspaneClearer::NewL( RWindowGroup& aParent,
                                                    TInt aStatuspaneLayoutId,
                                                    TBool aOwnWindowGroup )
	{
	CAknStatuspaneClearer* self =
	    CAknStatuspaneClearer::NewLC( aParent,
	                                  aStatuspaneLayoutId,
	                                  aOwnWindowGroup );
	CleanupStack::Pop( self );
	return self;
	}


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::~CAknStatuspaneClearer
// Destructor.
// ---------------------------------------------------------------------------
//
CAknStatuspaneClearer::~CAknStatuspaneClearer()
	{
	AKNTASHOOK_REMOVE();
    delete iBgContext;

    if ( iUnblankTimer )
    	{
   	    iUnblankTimer->Cancel();
        delete iUnblankTimer;
    	}

    if ( iOwnWindowGroup )
    	{
    	iParent->Close();
    	}
	}


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::SetSkinBackgroundContext
// Sets the blanker's skin background context.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::SetSkinBackgroundContext( TInt aStatuspaneLayoutId,
                                                      TBool aDrawNavi)
    {
    CEikStatusPaneContainer::PrepareBackgroundContext( iBgContext,
                                                       aStatuspaneLayoutId,
                                                       aDrawNavi );
    iStatuspaneLayoutId = aStatuspaneLayoutId;
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::Blank
// Blanks the status pane for a specific time.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::Blank( TInt aUnblankTimeout )
    {
    if (!iBlankDisableLevel)
        {
        Blank();
        }

	InitTimer( aUnblankTimeout, aUnblankTimeout );
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::Blank
// Blanks the status pane.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::Blank()
    {
    if ( !iBlankDisableLevel )
        {
        MakeVisible( ETrue );
    	DrawNow();
        }
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::IsBlank
// Checks if status pane is currently blanked.
// ---------------------------------------------------------------------------
//
TBool CAknStatuspaneClearer::IsBlank()
    {
    return IsVisible();
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::UnBlank
// Unblanks the status pane.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::UnBlank()
    {
    MakeVisible( EFalse );
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::SetShape
// Sets the blanker shape.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::SetShape( TRegion& aRegion )
    {
	DrawableWindow()->SetShape( aRegion );
	SetRect( AknLayout::screen().Rect() );
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::SetDefaultShape
// Sets the default blanker shape.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::SetDefaultShape()
    {
	RRegion shape;
    CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();
    if ( sp )
        {
        // Add all statuspane panes to shape.
        TRAPD( err, sp->GetShapeL( shape, ETrue, ETrue ) );
        if ( err == KErrNone )
            {
            DrawableWindow()->SetShape( shape );
            SetRect( AknLayout::screen().Rect() );
            }
        }
    shape.Close();
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::ConstructL
// Second-phase constructor.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::ConstructL( RWindowGroup& aParent,
                                        TInt aLayoutId,
                                        TBool aOwnWindowGroup )
	{
	if ( aOwnWindowGroup )
		{
		RWindowGroup wg = RWindowGroup( iCoeEnv->WsSession() );
		iParent = &wg;

	    User::LeaveIfError( iParent->Construct( (TUint32) iParent ) );
	    iParent->SetOrdinalPosition( 0, ECoeWinPriorityMedium );
    	iParent->EnableReceiptOfFocus( EFalse );
		}
	else
		{
		iParent = &aParent;
		}

	iOwnWindowGroup = aOwnWindowGroup;

	CreateWindowL( iParent );

   	iUnblankTimer = CPeriodic::NewL( CActive::EPriorityStandard );

    SetDefaultShape();

	SetOrdinalPosition( 0 );

    // No blank active
	UnBlank();

	ActivateL();

    iBgContext = CAknsMaskedLayerBackgroundControlContext::NewL(
        KAknsIIDQsnBgAreaStatus, TRect(0,0,1,1), ETrue, ELayerFlatN + 1 );

    SetSkinBackgroundContext( aLayoutId );
	}


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::Draw
// Draws the blanker.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::Draw( const TRect& /*aRect*/ ) const
	{
	CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::Background( skin, iBgContext, this, gc, Rect() );
    iEikonEnv->WsSession().Flush();

    return;
	}


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::SetOrdinalPosition
// Sets the window group ordinal position.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::SetOrdinalPosition( TInt aPosition )
    {
    DrawableWindow()->SetOrdinalPosition( aPosition );
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::EnableBlank
// Enables the blanker.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::EnableBlank()
    {
    iBlankDisableLevel = 0;
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::DisableBlank
// Sets the blank disable level.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::DisableBlank( TInt aDisableLevel )
    {
    iBlankDisableLevel = aDisableLevel;
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::InitTimer
// Starts the unblank timer.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::InitTimer( TInt aDelay, TInt aInterval )
    {
    CancelTimer();
    if ( iUnblankTimer &&
         !iUnblankTimer->IsActive() )  // start timer if not already started
        {
        iUnblankTimer->Start(
            TTimeIntervalMicroSeconds32( aDelay ),
		    TTimeIntervalMicroSeconds32( aInterval ),
            TCallBack( CAknStatuspaneClearer::TimerEvent, this ) );
        }
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::CancelTimer
// Cancels the unblank timer.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::CancelTimer()
    {
   	if ( iUnblankTimer && iUnblankTimer->IsActive() )
    	{
   		iUnblankTimer->Cancel();
    	}
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::TimerEvent
// Static callback function for delayed unblanking.
// ---------------------------------------------------------------------------
//
TInt CAknStatuspaneClearer::TimerEvent( TAny* aPtr )
    {
    static_cast<CAknStatuspaneClearer*>( aPtr )->DoTimerEvent();
    return TRUE;
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::DoTimerEvent
// Callback function for delayed unblanking.
// ---------------------------------------------------------------------------
//
void CAknStatuspaneClearer::DoTimerEvent()
    {
    UnBlank();
    CancelTimer();
    }


// ---------------------------------------------------------------------------
// CAknStatuspaneClearer::BlankDisabled
// Returns the current blank disable level.
// ---------------------------------------------------------------------------
//
TInt CAknStatuspaneClearer::BlankDisabled()
    {
    return iBlankDisableLevel;
    }

// End of file
