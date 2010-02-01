/*
* ============================================================================
*  Name        : bctestdomaiwaknapp.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : declaration of app.
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

#ifndef C_CBCTESTDOMAIWAKNAPP_H
#define C_CBCTESTDOMAIWAKNAPP_H

#include <aknapp.h>

const TUid KUidBCTestAiwAkn = { 0xA000409E }; // UID of the application.

/**
 *  CBCTestDomAiwAknApp class.
 *  Provides factory to create concrete document object.
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib avkon.lib eikcore.lib eiksrv.lib 
 *  @since S60 v5.0
 */
class CBCTestDomAiwAknApp : public CAknApplication
    {

private:  
// from base class CApaApplication

    /**
     * From CApaApplication.
     * Creates CBCTestDomAiwAknDocument document object.
     *
     * @since S60 v5.0
     * @return A pointer to the created document object.
     */        
    CApaDocument* CreateDocumentL();


    /**
     * From CApaApplication.
     * Returns application's UID ( KUidBCTestAiwAkn ).
     *
     * @since S60 v5.0
     * @return The value of KUidBCTestAiwAkn.
     */ 
    TUid AppDllUid() const;

    };

#endif // C_CBCTESTDOMAIWAKNAPP_H

// End of File
