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
* Description:  Button state for CAknButton use in CEikCba.
*
*/


#ifndef C_AKNCOMMANDBUTTONSTATE_H
#define C_AKNCOMMANDBUTTONSTATE_H

#include <aknbutton.h>

// CLASS DECLARATION

/**
 *  Extension to the button state class to support attaching
 *  commands to the states. 
 *
 *  @lib eikcoctl.lib
 *  @since 5.0
 */
NONSHARABLE_CLASS( CAknCommandButtonState ) : public CAknButtonState
    {
    friend class CAknButton;
    
public: // Constructors and destructors

    /**
    * Destructor.
    */
    ~CAknCommandButtonState();

protected: // Constructors and destructors

    /**
    * Constructor.
    *
    * @param  aFlags      The flags for the button state.
    * @param  aCommandId  The command associated with the button state.
    */
    CAknCommandButtonState( const TInt aFlags, const TInt aCommandId );

public:
    
    /**
    * Sets the command attached with this state.
    * 
    * @param  aCommandId  New command
    */ 
    void SetCommand( const TInt aCommandId );
    
    /**
    * Gets the command attached with this state.
    * 
    * @return  The command ID.
    */ 
    TInt CommandId() const;

private: // data
    
    /** Command for this state. */
    TInt iCommandId;
    };

#endif // C_AKNCOMMANDBUTTONSTATE_H
