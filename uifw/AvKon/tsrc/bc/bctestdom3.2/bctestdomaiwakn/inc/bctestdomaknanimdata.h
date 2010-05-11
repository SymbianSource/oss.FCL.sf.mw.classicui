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
