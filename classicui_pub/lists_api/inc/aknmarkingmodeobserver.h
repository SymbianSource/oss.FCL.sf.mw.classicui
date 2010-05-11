/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Marking mode observer interface.
*
*/

#ifndef M_AKNMARKINGMODEOBSERVER_H
#define M_AKNMARKINGMODEOBSERVER_H

/**
 * Collection observer.
 *
 * This interface is intended for those objects that are interested
 * of collection state and need to receive collection notifications.
 *
 * @lib eikcoctl
 * @since S60 v5.2
 */
class MAknMarkingModeObserver
    {
public:

    /**
     * This method is called when marking mode is activated or deactivated.
     * 
     * @param aActivated @c ETrue if marking mode was activate, @c EFalse
     *                   if marking mode was deactivated.
     */
    virtual void MarkingModeStatusChanged( TBool aActivated ) = 0;

    /**
     * This method is called just before marking mode is closed. Client can 
     * either accept or decline closing.
     * 
     * @return @c ETrue if marking mode should be closed, otherwise @c EFalse.
     */
    virtual TBool ExitMarkingMode() const = 0;
    };

#endif // M_AKNMARKINGMODEOBSERVER_H
