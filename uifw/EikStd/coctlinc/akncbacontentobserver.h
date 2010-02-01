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
* Description:
*
*/
#ifndef AKNCBACONTENTOBSERVER_H
#define AKNCBACONTENTOBSERVER_H

#include <e32base.h>

class CEikCba;

/**
 * This class provides means to set content observer
 * for @c CEikCba.
 * @since S60 v5.2
 */
class AknCbaContentObserver
    {
public:
    /**
     * Sets content observer.
     * @param aCba Cba to be observer.
     * @param aCallBack Call back method to invoke when 
     *        value of 'empty OR invisible' boolean expression
     *        changes.
     */
    IMPORT_C static void SetContentObserver( 
        CEikCba* aCba, 
        TCallBack aCallBack );
    };

#endif // AKNCBACONTENTOBSERVER_H
