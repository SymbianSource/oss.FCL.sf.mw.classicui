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
* Description: 
*
*/

#ifndef C_AKNSMALLINDICATOR_H
#define C_AKNSMALLINDICATOR_H

#include <AknNotify.h>

NONSHARABLE_CLASS(CAknSmallIndicator) : public CAknNotifyBase
    {
public:
    
    /**
     * Two-phased constructor.
     *
     * @param  aIndicatorUid  UID of the status indicator.
     * @return Pointer to a new @c CAknSmallIndicator instance.
     */
    IMPORT_C static CAknSmallIndicator* NewL( TUid aIndicatorUid );
    
    /**
     * Two-phased constructor. Leaves the created instance
     * on the cleanup stack.
     *
     * @param  aIndicatorUid  UID of the status indicator.
     * @return Pointer to a new @c CAknSmallIndicator instance.
     */
    IMPORT_C static CAknSmallIndicator* NewLC( TUid aIndicatorUid );
    
    /**
     * Destructor.
     */
    IMPORT_C ~CAknSmallIndicator();
    
    /**
     * Sets the state of the status indicator.
     *
     * @param  aState  The state to be set to the indicator.
     *                 @see MAknIndicator::TAknIndicatorState
     */
    IMPORT_C void SetIndicatorStateL( const TInt aState );
    
    /**
     * Handles stylus tap event on the indicator.
     */
    IMPORT_C void HandleIndicatorTapL();
    
private:
    CAknSmallIndicator();
    void ConstructL( TUid aIndicatorUid );
    
private:
    IMPORT_C void CAknNotifyBase_Reserved();

private:
    TUid iIndicatorUid;
    };

#endif // C_AKNSMALLINDICATOR_H
