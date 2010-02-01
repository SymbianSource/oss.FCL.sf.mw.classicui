/*
* ============================================================================
*  Name        : bctestdomaknanimdata.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : for testing APIs in aknAnimData.h
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

#ifndef C_BCTESTDOMAKNANIMATIONDATA_H
#define C_BCTESTDOMAKNANIMATIONDATA_H

#include <aknAnimData.h>
 
/**
 *  CBCTestDomAknAnimationData class
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */ 
class CBCTestDomAknAnimationData : public CAknAnimationData
    {
public:

    /**
     * Symbian static 2nd constructor
     */
    static CBCTestDomAknAnimationData* NewLC();
    
    /**
     * destructor
     */
    virtual ~CBCTestDomAknAnimationData();
    
// from base classes from CAknAnimationData.    
    /**
     * From CAknAnimationData.     
     * PreAnimateSetup
     *
     * @since S60 v5.0   
     * @param aGc   a CBitmapContext object reference
     * @param aStep a TAnimMultiStep object reference
     */	    
	IMPORT_C virtual TBool DrawUserAnimationStep( 
	    CBitmapContext& aGc, TAnimMultiStep& aStep );

    /**
     * From CAknAnimationData.     
     * PreAnimateSetup
     *
     * @since S60 v5.0  
     * @param aAnimStep  a TAnimStep object reference
     * @param aReader  a TResourceReader object reference          
     */		
	IMPORT_C virtual void ConstructUserAnimationStepL(
	    TAnimStep& aAnimStep, TResourceReader& aReader );

// from base classes from CAknAnimationData.  
    /**
     * From CAknAnimationData.      
     * symbian 2nd constructor
     *
     * @since S60 v5.0       
     */
    void ConstructL();     

private:  

    /**
     * C++ default constructor
     */
    CBCTestDomAknAnimationData();

    };

#endif // C_BCTESTDOMAKNANIMATIONDATA_H

// End of File
