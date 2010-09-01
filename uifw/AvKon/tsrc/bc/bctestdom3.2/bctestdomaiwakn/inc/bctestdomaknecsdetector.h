/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef C_CBCTESTDOMAKNECSDESTRUCTOR_H
#define C_CBCTESTDOMAKNECSDESTRUCTOR_H


#include <aknecs.h> //for test CAknEcsDetector
 
 
/**
 *  test CAknEcsDetector .
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */  
class CBCTestDomAknEcsDetector : public CAknEcsDetector
    {

public:

     static CBCTestDomAknEcsDetector* NewL();

     static CBCTestDomAknEcsDetector* NewLC();

    /**
     * Destructor.
     */
     virtual ~CBCTestDomAknEcsDetector();

 

// from base class CAknEcsDetector  
    /**
     * from  CAknEcsDetector.  
     * Calls the observer
     *
     * @since S60 ?S60_version 
     * @param aNewState     New state.
     */
     IMPORT_C virtual void ReportEvent( TState aNewState );

    /**
     * from  CAknEcsDetector. 
     * Internal routine to set the state
     * @since S60 ?S60_version 
     * @param aNewState     New state.     
     */
     IMPORT_C void SetState( TState newState );

    /**
     * from  CAknEcsDetector. 
     * Framework method that may be re-implemented in order to perform some 
     * check or put up UI before the phone call is made
     * Implementation must not leave;
     *
     * @since S60 ?S60_version      
     * @return     Whether or not to continue with the emergency call
     */
     IMPORT_C virtual TBool OfferEmergencyCall();

    /**
     * from  CAknEcsDetector. 
     * Framework method that may be re-implemented in order to perform some 
     * check or put up UI before the phone call is made
     * Implementation must not leave;
     *
     * @since S60 ?S60_version      
     * @return     Whether or not to continue with the emergency call
     */          
     virtual void HandlePhoneStatusL( const TInt aStatus );
private:

    CBCTestDomAknEcsDetector();

    void ConstructL();

    };

#endif // C_CBCTESTDOMAKNECSDESTRUCTOR_H
