/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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



#ifndef __AKNMFNECOMMANDOBSERVER
#define __AKNMFNECOMMANDOBSERVER

#include <e32base.h>

// CLASS DECLARATION

/**
*  Interface for giving commands to MFNE editors from the owning controls.
*  This interface was added to forward touch command button events to MFNE
*  editors. The interface can be extended later by adding more commands to 
*  TMfneCommand enum if needed.
*
*  @lib eikctl.lib
*  @since Series 60 3.0
*/
class MAknMfneCommandObserver
    {
    public:
        
        /**
        * List of commands that can be given to MFNE editor with 
        * HandleMfneCommand() function
        */
        enum TMfneCommand
            {
            EMfneIncrementCurrentFieldValue,
            EMfneDecrementCurrentFieldValue
            };
        
        /**
        * Interface function allowing other classes to give commands to MFNE editors.
        * The commands are defined in TMfneCommand enum.
        *
        * @since Series 60 5.0
        * @param aCommand Command defined in TMfneCommand
        */
        virtual void HandleMfneCommandL(TInt aCommand) = 0;
    };

#endif      // __AKNMFNECOMMANDOBSERVER  
            
// End of File
