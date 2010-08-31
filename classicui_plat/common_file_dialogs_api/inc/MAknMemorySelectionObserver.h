/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer interface for memory selection.
*
*/



#ifndef M_AKNMEMORYSELECTIONOBSERVER_H
#define M_AKNMEMORYSELECTIONOBSERVER_H

#include <CAknMemorySelectionDialog.h>

/**
*  Observer class that can be set to observe if selected memory
*  e.g. has enoung free space before letting dialog exit.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
class MAknMemorySelectionObserver
    {

public:

// Constructors and destructor

    /**
     * A virtual destructor to ensure that correct destructor gets called.
     * Must have an empty implementation.
     */
    virtual ~MAknMemorySelectionObserver() { };

// New functions

    /**
     * Get's called when user selects a memory.
     * @param aMemory Currently selected memory.
     * @return Returns ETrue if it is ok to exit from dialog.
     */
    virtual TBool OkToExitL( CAknMemorySelectionDialog::TMemory aMemory ) = 0;

    };

#endif // M_AKNMEMORYSELECTIONOBSERVER_H
