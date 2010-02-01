/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         MEikCommandObserver's sub class.
*
*/









#ifndef T_TBCTESTSUBCOMMANDOBSERVER_H
#define T_TBCTESTSUBCOMMANDOBSERVER_H

#include <eikcmobs.h>

/**
 *  MEikCommandObserver's sub class
 */
class TBCTestSubCommandObserver: public MEikCommandObserver
    {
    
// from MEikCommandObserver    
    
    /**
     * ProcessCommandL  function  
     * @param aCommandId ID of the command to respond to.
     */
    void ProcessCommandL( TInt /*aCommandId*/ ){} 
    
    };

#endif // T_TBCTESTSUBCOMMANDOBSERVER_H
