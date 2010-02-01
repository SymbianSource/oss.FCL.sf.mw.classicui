/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef AKNINPUTBLOCK_H
#define AKNINPUTBLOCK_H

#include <coecntrl.h>
#include <eikcmobs.h>

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;
class CEikAppUi;


/**
 * MAknInputBlockCancelHandler is an interface to an object that
 * can handle the UI framework attempting to cancel a CAknInputBlock.
 * @since 3.1
 */
class MAknInputBlockCancelHandler
	{
public:
	virtual void AknInputBlockCancel() = 0;
	};


/**
 * CAknInputBlock blocks user input, key and pen, from reaching
 * existing controls, such as softkeys, dialogs or main panes.
 * It will not block controls higher on the control stack than
 * ECoeStackPriorityDialog.
 * It will not block subsequently created dialogs.
 * It will detect attempts from the UI framework to cancel the 
 * blocked state.
 * Clients should supply something to handle such cancel requests.
 * There are three ways that cancel can be signalled: through
 * an M-class interface, by cancelling an active object, by
 * deleting a CBase derived object.
 * All three cancel methods can be active. When a cancel signal
 * is detected, the handlers will be triggered in the order of
 * M-class first, then active object cancel, finally CBase delete.
 * If no cancel hander is supplied, all input is blocked, including
 * framework attempts to deactivate views and exit the application.
 *
 * This is an example of use of all cancel methods with an active object that
 * blocks with a CActiveSchedulerWait...
 * CAknInputBlock* inputBlock = CAknInputBlock::NewCancelHandlerLC(this);	// notify "this" on cancel
 * CAOWait* wait = CAOWait::NewL();			// create waiting active object
 * inputBlock->SetCancelActive(wait);		// set it as an active object to cancel
 * inputBlock->SetCancelDelete(wait);		// set it as an object to delete, takes ownership
 * wait->Start();
 * inputBlock->SetCancelHandler(NULL);		// Clear the cancel handler so that "this" is not notified by cancel on deletion
 * CleanupStack::PopAndDestroy(inputBlock);	// wait will be cancelled and deleted by inputBlock
 *
 * @since 3.1
 */
NONSHARABLE_CLASS(CAknInputBlock) : public CCoeControl, public MEikCommandObserver
	{
public:
    /**
    * Create a new input blocker with no cancel support.
    * Cancel handling can be set later with one of the
    * SetCancel... methods.
    * Note: while this object exists without cancel support,
    * view deactivations and application exit requests will not be processed.
    * @return a new instance of CAknInputBlock on the cleanup stack
    */
	IMPORT_C static CAknInputBlock* NewLC();
    /**
    * Create a new input blocker with M-class cancel support.
    * @param aHandlerToCancel, a pointer to the M-class instance
    * to call back on cancel. Does not take ownership. Can be
    * called with NULL to clear the cancel handler.
    * @return a new instance of CAknInputBlock on the cleanup stack
    */
	IMPORT_C static CAknInputBlock* NewCancelHandlerLC(MAknInputBlockCancelHandler* aHandlerToCancel);
    /**
    * Create a new input blocker with active object cancel support.
    * @param aActiveObjectToCancel, a pointer to the active object
    * to cancel. Does not take ownership. Can be called with
    * NULL to clear the cancel handler.
    * @return a new instance of CAknInputBlock on the cleanup stack
    */
	IMPORT_C static CAknInputBlock* NewCancelActiveLC(CActive* aActiveObjectToCancel);
    /**
    * Create a new input blocker with object delete cancel support.
    * @param aObjectToDelete, a pointer to the CBase-derived object
    * to delete on cancel. Take ownership. Can be called with
    * NULL to clear the cancel handler.
    * @return a new instance of CAknInputBlock on the cleanup stack
    */
	IMPORT_C static CAknInputBlock* NewCancelDeleteLC(CBase* aObjectToDelete);
	/**
	* destructor
	* This will also call Cancel()
	*/
	IMPORT_C ~CAknInputBlock();

	/**
	* Set a cancel handler.
    * @param aHandlerToCancel, a pointer to the M-class instance
    * to call back on cancel. Does not take ownership. Can be
    * called with NULL to clear the cancel handler.
	*/
	IMPORT_C void SetCancelHandler(MAknInputBlockCancelHandler* aHandlerToCancel);
	/**
	* Set a cancel handler.
    * @param aActiveObjectToCancel, a pointer to the active object
    * to cancel. Does not take ownership. Can be called with
    * NULL to clear the cancel handler.
	*/
	IMPORT_C void SetCancelActive(CActive* aActiveObjectToCancel);
	/**
	* Set a cancel handler.
    * @param aObjectToDelete, a pointer to the CBase-derived object
    * to delete on cancel. Take ownership. Can be called with
    * NULL to clear the cancel handler.
	*/
	IMPORT_C void SetCancelDelete(CBase* aObjectToDelete);

	/**
	* Called when the UI framework wants to cancel this input
	* blocking state, eg on app exit.
	* May also be called manually to force cancel.
	* After cancelling, all handers are set to NULL.
	*/
	IMPORT_C void Cancel();
	
private:
	CAknInputBlock();
	void ConstructL();
	
	bool IsCancellable() const;

private: // from CCoeControl
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void FocusChanged(TDrawNow aDrawNow);

private: // from MEikCommandObserver
	void ProcessCommandL(TInt /*aCommandId*/);

private:
	MAknInputBlockCancelHandler* iHandlerToCancel;	// not owned
	CActive* iActiveObjectToCancel;					// not owned
	CBase* iObjectToDelete;							// owned
	CEikAppUi* iAppUi;								// not owned
	CEikButtonGroupContainer* iCba;					// owned
	};




#endif
