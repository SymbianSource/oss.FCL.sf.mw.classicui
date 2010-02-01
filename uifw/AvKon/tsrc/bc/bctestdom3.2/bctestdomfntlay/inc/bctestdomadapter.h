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
* Description:  adapter of layout
*
*/


#ifndef C_CBCTESTDOMADAPTER_H
#define C_CBCTESTDOMADAPTER_H

#include <aknlayout2def.h>
#include <aknlayout2datadef.h>

class CBCTestDomAdapter: public CBase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomAdapter* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomAdapter();
  
    
    /**
    * Get a pointer to AdpData
    * 
    */
    TUint* GetAdpDataLookup();
        
private: // constructor
    
    /**
    * C++ default constructor
    */
    CBCTestDomAdapter();
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
        
    /**
    * a callback function
    * @return return a TAknWindowLineLayout object 
    */
    static TAknWindowLineLayout WindowLine0f();
    
    /**
    * a callback function
    * @param aIndex is index of line 
    * @return return a TAknWindowLineLayout object 
    */
    static TAknWindowLineLayout WindowLine1f( TInt aIndex );
    
    /**
    * a callback function
    * @return return a TAknTextLineLayout object 
    */
    static TAknTextLineLayout TextLine0f();
   
    /**
    * a callback function
    * @param aIndex is index of line 
    * @return return a TAknTextLineLayout object 
    */   
    static TAknTextLineLayout TextLine1f( TInt aIndex );
     
private: // data
        
    /**
     * Pointer to a TUint array 
     */
    TUint*  iAdpDataLookup;
        
    };

#endif // C_CBCTESTDOMADAPTER_H
