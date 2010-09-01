/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  observer
 *
*/


#ifndef C_TESTSDKCFDMAKNMEMORYSELECTIONOBSERVER_H
#define C_TESTSDKCFDMAKNMEMORYSELECTIONOBSERVER_H

//  INCLUDES
#include <maknmemoryselectionobserver.h>

class CTestSDKCFDMAknMemorySelectionOberver : public CBase, public MAknMemorySelectionObserver
{
public:

    /**
     * Two-phased constructor.
     */
    static CTestSDKCFDMAknMemorySelectionOberver* NewL();

    /**
     * Get's called when user selects a memory.
     * @param aMemory Currently selected memory.
     * @return Returns ETrue if it is ok to exit from dialog.
     */
    TBool OkToExitL( CAknMemorySelectionDialog::TMemory aMemory );

    /**
     * Destructor.
     */
    virtual ~CTestSDKCFDMAknMemorySelectionOberver();

private:

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

    /**
     * C++ default constructor.
     */
    CTestSDKCFDMAknMemorySelectionOberver();

};

#endif /*C_TESTSDKCFDMAKNMEMORYSELECTIONOBSERVER_H*/



