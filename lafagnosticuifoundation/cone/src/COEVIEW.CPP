// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//


#include <coeview.h>	// class MCoeView

//
// MCoeView
//

EXPORT_C MCoeView::MCoeView()
	{
	}

/**
 * Handles a change to the screen device returning the value of the TVwsViewIdAndMessage object that describes what
 * the view arcitecture should do next. Returns the id of the active view by default.
 * @publishedAll
 * @released
 */
EXPORT_C TVwsViewIdAndMessage MCoeView::ViewScreenDeviceChangedL()
	{
	CCoeScreenDeviceChangeDefaultHandler* screenChangeHandler=CCoeScreenDeviceChangeDefaultHandler::Self();
	if (screenChangeHandler)
		{
		return screenChangeHandler->DefaultViewOnScreenDeviceChanged();
		}
	return TVwsViewIdAndMessage();
	}


/**
 * Constructs the view. The view architecture can construct registered views in the background or on first activation.
 * Empty by default.
 * @publishedAll
 * @released
 */
EXPORT_C void MCoeView::ViewConstructL()
	{}

/**
 * By default, Views are compatible with all screen modes.
 * @publishedAll
 * @released
 */
EXPORT_C TBool MCoeView::ViewScreenModeCompatible(TInt /*aScreenMode*/)
	{
	return ETrue;
	}

/**
 * Checks whether the view being activated has the preferred screen mode or not.
 * Empty by default.
 * @publishedAll
 * @released
 */
EXPORT_C void MCoeView::PrepareForViewActivation()
	{
	}
	
EXPORT_C void MCoeView::MCoeView_Reserved_2()
	{}
		
EXPORT_C void MCoeView::MCoeView_Reserved_3()
	{}


//
// MCoeViewDeactivationObserver
//
EXPORT_C MCoeViewDeactivationObserver::MCoeViewDeactivationObserver()
	{}

EXPORT_C void MCoeViewDeactivationObserver::MCoeViewDeactivationObserver_Reserved_1()
	{}

EXPORT_C void MCoeViewDeactivationObserver::MCoeViewDeactivationObserver_Reserved_2()
	{}


//
// MCoeViewActivationObserver
//
EXPORT_C MCoeViewActivationObserver::MCoeViewActivationObserver()
	{}

EXPORT_C void MCoeViewActivationObserver::MCoeViewActivationObserver_Reserved_1()
	{}

EXPORT_C void MCoeViewActivationObserver::MCoeViewActivationObserver_Reserved_2()
	{}

//
// MCoeViewObserver
//
EXPORT_C MCoeViewObserver::MCoeViewObserver()
	{}
	
EXPORT_C void MCoeViewObserver::MCoeViewObserver_Reserved1()
	{}

EXPORT_C void MCoeViewObserver::MCoeViewObserver_Reserved2()
	{}


//
// CCoeScreenDeviceChangeDefaultHandler
//

const TUid KScreenChangedHandlerUid={0x10005FC2};

/** Destructor. */
EXPORT_C CCoeScreenDeviceChangeDefaultHandler::~CCoeScreenDeviceChangeDefaultHandler()
	{
	}
	
/*
 * Return a pointer to the screen mode change handler for this thread or NULL if there is
 * not one installed.  Doesn't pass ownership
 *
 * @since 	7.0
 */
EXPORT_C CCoeScreenDeviceChangeDefaultHandler* CCoeScreenDeviceChangeDefaultHandler::Self()
	{ // static
	return static_cast<CCoeScreenDeviceChangeDefaultHandler*>(CCoeEnv::Static(KScreenChangedHandlerUid));
	}

EXPORT_C CCoeScreenDeviceChangeDefaultHandler::CCoeScreenDeviceChangeDefaultHandler()
	: CCoeStatic(KScreenChangedHandlerUid)
/** Default constructor. */
	{}

/** Constructor specifying the destruction priority of the object.

@param aDestructionPriority Priority determining the order of destruction relative to other
CCoeStatic-derived objects. The higher the destruction-priority of the object, the earlier that
object is deleted. Objects with a positive destruction-priority are destroyed before the CCoeAppUi
object is destroyed. Objects with a negative destruction-priority are destroyed after the CCoeAppUi
object is destroyed. */
EXPORT_C CCoeScreenDeviceChangeDefaultHandler::CCoeScreenDeviceChangeDefaultHandler(TInt aDestructionPriority)
	: CCoeStatic(KScreenChangedHandlerUid, aDestructionPriority)
	{}

EXPORT_C void CCoeScreenDeviceChangeDefaultHandler::CCoeStatic_Reserved1()
	{}

EXPORT_C void CCoeScreenDeviceChangeDefaultHandler::CCoeStatic_Reserved2()
	{}
	
EXPORT_C void CCoeScreenDeviceChangeDefaultHandler::CCoeScreenDeviceChangeDefaultHandler_Reserved1()
	{}
	
EXPORT_C void CCoeScreenDeviceChangeDefaultHandler::CCoeScreenDeviceChangeDefaultHandler_Reserved2()
	{}
