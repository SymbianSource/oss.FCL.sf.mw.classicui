/*
* ============================================================================
*  Name        : bctestdomaiwakndocument.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : declaration of document
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

#ifndef C_CBCTESTDOMAIWAKNDOCUMENT_H
#define C_CBCTESTDOMAIWAKNDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
 *  CBCTestDomAiwAknDocument class.
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib  
 *  @since S60 v5.0
 */ 

class CBCTestDomAiwAknDocument : public CEikDocument
    {
public: 
    /**
     * Symbian OS two-phased constructor.
     *
     * 
     * @return Pointer to created Document class object.
     * @param aApp Reference to Application class object.     
     */         
        static CBCTestDomAiwAknDocument* NewL( CEikApplication& aApp );

    /**
     * Destructor.
     *
     */         
    virtual ~CBCTestDomAiwAknDocument();

private:  

    /**
     * Overload constructor..
     *
     * @since S60 v5.0
     * @param aApp Reference to Application class object.
     */        
    CBCTestDomAiwAknDocument( CEikApplication& aApp );

// from base class CEikDocument

    /**
     * From CEikDocument.
     * Creates CBCTestDomAiwAknAppUi "App UI" object.
     *
     * @since S60 v5.0
     * @return Pointer to created AppUi class object.
     */
    CEikAppUi* CreateAppUiL();

    };

#endif  // C_CBCTESTDOMAIWAKNDOCUMENT_H

// End of File
