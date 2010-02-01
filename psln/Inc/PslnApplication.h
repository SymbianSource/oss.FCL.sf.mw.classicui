/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  App class for Psln application.
*
*/


#ifndef C_PSLNAPPLICATION_H
#define C_PSLNAPPLICATION_H

#include <aknapp.h>

/**
 * Psln Application class. 
 * This class is created by the Symbian OS framework by a call to NewApplication()
 * function when the application is started. The main purpose of the 
 * application class is to create the application-specific document object 
 * (PslnDocument in this case) via a call to virtual CreateDocumentL().
 *
 * @see NewApplication
 */
class CPslnApplication : public CAknApplication 
    {
    private: // from CApaApplication
        
        /**
        * Creates the Psln document object (PslnDocument). 
        * Called by the application framework.
        * 
        * @return New Psln document object (PslnDocument).
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * Returns application UID.
        * @return KUidPsln.
        */
        TUid AppDllUid() const;
    };

#endif // C_PSLNAPPLICATION_H
            
// End of File
