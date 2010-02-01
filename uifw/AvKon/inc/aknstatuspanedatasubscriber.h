/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon internal subscriber for the system controlled and 
*                published status pane data.
*
*/


#ifndef C_AKNSTATUSPANEDATASUBSCRIBER_H
#define C_AKNSTATUSPANEDATASUBSCRIBER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <e32property.h>
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CActive;
class CAknStatusPaneSubscriberData;
class MAknStatusPaneDataObserver;

/**
 *
 * This class is subscriber for the system controlled
 * and published status pane data.
 *
 * @since S60 3.2
 *
 * @internal
 */
NONSHARABLE_CLASS( CAknStatusPaneDataSubscriber ) : public CActive
	{
public: 

    DECLARE_TYPE_ID(0x102823DA) 

	/**
     * Two-phased constructor.
     */
    IMPORT_C static CAknStatusPaneDataSubscriber* NewL();
     
    /**
     * Destructor.
     */
    ~CAknStatusPaneDataSubscriber();        

    /**
     * Sets a flag to indicate that when this subscriber is in foreground it
     * does not indicate itself as foreground subscriber, thus allowing the
     * previous foreground subscriber still to be updated normally.
     * If this flag is set, then @c iForceBackgroundRefresh should be set to
     * @c ETrue to allow this subscriber to receive updates in the background.
     * 
     * @param  aAlwaysBackground  @c ETrue if this subscriber
     *                            remains always in the background.
     */
    IMPORT_C void SetAlwaysBackground( TBool aAlwaysBackground ); 

    /**
     * Refreshes status pane data.
     */
    IMPORT_C void RefreshDataL();

	enum
		{
		ERefreshLevelNone   = 0x10,			
		ERefreshLevelMedium = 0x20,
		ERefreshLevelHigh   = 0x30
		};
		
    /**
     * Sets the refresh level.
     *
  	 * @param  aLevel   Refresh level to be set.
  	 * @param  aForced  @c ETrue to force the level to be set or
  	 *                  to override a level that has been forced.
     */
    IMPORT_C void SetRefreshLevel( TInt aLevel, TBool aForced ); 

    /**
     * Gets the refresh level.
     *
  	 * @return  Refresh level
     */
	IMPORT_C TInt RefreshLevel();

    /**
     * Gets the id of the subscriber in the foreground currently.
     *
  	 * @return  Id of the foreground status pane.
     */
    TInt ForegroundSubscriberId() const; 

    /**
     * Sets the id of the subscriber in the foreground currently.
     *
	 * @param  aId  Id of the foreground status pane sync service subscriber.
     */
    void SetForegroundSubscriberId( TInt aId ); 

    /**
     * Gets the id of this subscriber.
     *
     * @return  Id of the status pane sync service subscriber.
     */
    TInt SubscriberId() const; 

    /**
     * Returns @c ETrue if this subscriber is in the foreground. 
     *
	 * @return @c ETrue if this is in the foreground, otherwise @c EFalse.
     */
    TBool IsBackground() const; 

    /**
     * Adds observer which will be notified when status pane data has changed.
     *
     * @param  aObserver  An observer that is to be added.
     */
	void AddObserver( MAknStatusPaneDataObserver* aObserver );

    /**
     * Removes observer.
     *
     * @param  aObserver  An observer that is to be added.
     */
	void RemoveObserver( MAknStatusPaneDataObserver* aObserver );
    
    /**
     * Handles the the situation where status pane comes
     * to foreground.
     */
    IMPORT_C void HandleGainingForeground();

    /**
     * Handles the the situation where status pane loses foreground.
     */       
    IMPORT_C void HandleLosingForeground();

private: // From @c CActive
    
    /**
     * Executes when serverside publishes data update.
     */
    void RunL();

    /**
   	 * Cancels subscription to data update notifications.
     */
    void DoCancel();

    /**
	 * Handles error situation of the property subscribtions.
     */
    TInt RunError( TInt aError );

private:

	/**
     * Private 2nd phase constructor.
     */
    void ConstructL();

    /**
     * Standard constructor
     */
    CAknStatusPaneDataSubscriber();
 
    /**
     * Subscribes to the property that contains the serverside data.
     */
    void DoSubscribe();   
        
private:

	/** Property for status pane state data. */
    RProperty iProperty;
			
	/**
	 * Flag to indicate that when this subscriber is in foreground it does not
	 * indicate itself as foreground subscriber, thus allowing the previous
	 * foreground subscriber still to be updated. If this flag is set, then
	 * @c iForceBackgroundRefresh should be set to @c ETrue to allow this
	 * subscriber to receive updates in the background.
	 */
	TBool iAlwaysBackground;	

	/** Describes the level of the status pane controls are updates. */
	TInt  iRefreshLevel;

	/** A flag to tell if refresh level has been forced or not. */	
	TBool iForcedRefreshLevel;
	
	/** Unique id of this subscriber. */
	TInt iSubscriberId;
	
	/** Data structure to hold status pane state data. */
	CAknStatusPaneSubscriberData* iStatusPaneStateData;
	
	/** Array of subscriber observers. */
	RPointerArray<MAknStatusPaneDataObserver> iObservers; 
		
	class TWsEventObserver;
	friend class TWsEventObserver;
	
	/** Owned window server event observer */
	TWsEventObserver* iObserver;	
	
	/**
	 * A flag determining whether or not this subscriber is the
	 * foreground subscriber.
	 */
	TBool iIsForeground;
		
  };

#endif // C_AKNSTATUSPANEDATASUBSCRIBER_H
