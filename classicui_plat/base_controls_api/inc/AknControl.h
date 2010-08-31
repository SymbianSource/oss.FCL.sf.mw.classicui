/*
* Copyright (c) 2005,2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base class for all S60 UI framework UI controls.
*
*
*/

#ifndef AKN_CONTROL_H
#define AKN_CONTROL_H

// INCLUDES
#include <e32base.h>
#include <coecntrl.h>

// FORWARD DECLARATIONS

// CONSTANTS

// CLASS DEFINITIONS

/**
 * UI framework base class for all Avkon controls.
 *
 *  @lib avkon
 *  @since S60 3.0
 */
class CAknControl : public CCoeControl
    {
    public:
    /**
    * Constructor. 
    */
    IMPORT_C CAknControl();

    /**
     * Destructor
     */
    IMPORT_C ~CAknControl();
    
    private:
    /**
     * Virtual method provided to allow extensibility of virtual behaviour
     */
    IMPORT_C virtual void* ExtensionInterface( TUid aInterface );
    
    private:
    TInt iSpare[6];
    };

#endif // AKN_CONTROL_H
