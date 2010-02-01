/*
* ============================================================================
*  Name        : bctestdomaknecsdetector.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : for testing the protected methods of CAknEcsDetector
*  Version     : %version: 1 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright © 2007.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.2
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
