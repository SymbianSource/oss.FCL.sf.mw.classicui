/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKEDWOB_H__)
#define __EIKEDWOB_H__

class CEikEdwin;

/**
 * Interface class describing the functionality expected of an observer
 * for CEikEdwins.
 * 
 * Edwin observers are informed by the edwin whenever its content is
 * changed, or whenever the user changes the cursor position.
 * 
 * This class should be derived from by all observers of edwins.
 */
class MEikEdwinObserver
	{
public:
    /**
     * Events from a value editor.
     */
	enum TEdwinEvent
		{
		/** Sent whenever the content of the edwin changes. */
		EEventFormatChanged,
		/** Sent on receipt of a navigation command. */
		EEventNavigation,
		/**
		 * Sent whenever the text of the edwin changes. To observe
		 * actual changes in the contents of the editor this should
		 * be preferred to EEventFormatChanged.
		 */
		EEventTextUpdate,
		/** Sent on receipt of a scroll event. */
		EEventScroll,
		/** Sent if you explicitly call edwin's SetTextL() */
		EEventTextUpdateAPI,
		EEventChinesePopupOpen,
		EEventChinesePopupClose,
        EEventPartialScreenEnable,
        EEventPartialScreenDisable
		};
public:
    /**
     * This pure virtual function is invoked by CEikEdwin to report an event
     * to its observer. The observer may respond appropriately.
     * 
     * @param aEdwin  The originating edwin. 
     * @param aEventType  The event being reported. 
     */
	virtual void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType)=0;
	};

/**
 * Interface to handle changes to an edwin's size.
 */
class MEikEdwinSizeObserver
	{
public:
    /**
     * Specifies the type of event reported to the edwin observer.
     */
	enum TEdwinSizeEvent
		{
		/**
		 * Specifies a change in edwin size. When the edwin observer
		 * receives an event of this type, it handles it by making
		 * its view bigger or smaller according to the new edwin size.
		 */
		EEventSizeChanging
		};
public:
    /**
     * Handles a change in the edwin's size. If you implement this function,
     * ensure it returns ETrue if you wish to redraw the edwin.
     * 
     * @param aEdwin The edwin for which the size event is being handled.
     * @param aEventType The event type.
     * @param aDesirableEdwinSize The desired size for the edwin identified
     * by aEdwin.
     * @return The return value depends on your implementation. Return
     * ETrue if you wish to redraw the edwin. EFalse otherwise.
     */
	virtual TBool HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize)=0;
	};

#endif
