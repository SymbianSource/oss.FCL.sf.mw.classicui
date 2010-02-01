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
* Description:
*
*/


#if !defined(__AKNHEADINGPANETOUCHOBSERVER_H__)
#define __AKNHEADINGPANETOUCHOBSERVER_H__

class CAknPopupHeadingPane;

/**
 * Interface for implementing a touch observer of CAknPopupHeadingPane.
 * This observer is notified by the heading pane whenever it receives
 * pointer events. The observer receives the original pointer event information.
 * This class should be derived from by the heading pane touch observer.
 *
 * @since Series 60 5.0
 */
class MAknHeadingPaneTouchObserver
	{
public:
    /**
     * This pure virtual function is invoked by CAknPopupHeadingPane to report a pointer event
     * to its observer. The observer may respond appropriately.
     * 
     * @param aHeadingPane  The originating heading pane. 
     * @param aPointerEvent  The pointer event being reported. 
     */
	virtual void HandleHeadingPanePointerEventL( CAknPopupHeadingPane* aHeadingPane, const TPointerEvent& aPointerEvent ) = 0;
	};

#endif
