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
