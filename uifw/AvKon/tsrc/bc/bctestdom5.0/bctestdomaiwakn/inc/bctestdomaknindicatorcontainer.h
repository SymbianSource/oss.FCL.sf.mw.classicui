/*
* ============================================================================
*  Name        : bctestdomaknindicatorcontainer.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : for indirectly testing APIs in aknindicator.h 
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

#ifndef C_CBCTESTDOMAKNINDICATORCONTAINER_H
#define C_CBCTESTDOMAKNINDICATORCONTAINER_H
  
#include <aknindicatorcontainer.h>
 
/**
 *  for indirectly testing APIs in aknindicator.h  
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */  
class CBCTestDomAknIndicatorContainer : public CAknIndicatorContainer
    {

public:
     static CBCTestDomAknIndicatorContainer* NewL();

     static CBCTestDomAknIndicatorContainer* NewLC();

    /**
     * Destructor.
     */
     virtual ~CBCTestDomAknIndicatorContainer();

// from base class CAknIndicatorContainer  
    /**
     * from  CAknIndicatorContainer. 
     * Returns a control determined by control id.
     *
     * @since S60 v5.0 
     * @param anIndex Index of a control to be returned.
     * @return Pointer to control   
     */
     IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
      
private:
    
    CBCTestDomAknIndicatorContainer();

    void ConstructL();

    /**
     * Reserved_1
     *
     * @since S60 v5.0
     */
    virtual void Reserved_1();  
    };

#endif // C_CBCTESTDOMAKNINDICATORCONTAINER_H
