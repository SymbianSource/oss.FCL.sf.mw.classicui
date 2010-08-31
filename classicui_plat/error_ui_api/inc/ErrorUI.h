/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined ERROR_UI_H
#define ERROR_UI_H

#include <coemain.h>    //  CCoeEnv
#include <textresolver.h>

/**
* Utility class to display error notes by applications.
* This is the default error display class to be used by
* applications.
* The features of the class are:
*   - maps given error to error text to be displayed
*   - displays error note using timed, global note
*   - does not display error if it is already "on"
*   - offers a reference to internal TextResolver instance
*
* Usage (typically as instance variable)
*   iErrorUI = CErrorUI::NewL(); // iCoeEnv can be given as argument, no need to that though 
*   ... some code causing an error  ...
*   if ( err != KErrNone )
*       iErrorUI->ShowGlobalErrorNoteL(err);
*
*/

class CErrorUI : public CBase
{
public:

public:
    
    /**
     * This constructor method should be used by servers, does not put the created object into CleanupStack
     */
    IMPORT_C static CErrorUI* NewL();
    
    /**
     * This constructor method should be used by servers, puts the created object into CleanupStack
     */
    IMPORT_C static CErrorUI* NewLC();

    /**
     * This constructor method should be used by applications, does not put the created object into CleanupStack
     * @param aEnv Reference to caller's control environment    
     */
    IMPORT_C static CErrorUI* NewL(CCoeEnv& aEnv);
    
    /**
     * This constructor method should be used by applications, puts the created object into CleanupStack
     * @param aEnv Reference to caller's control environment
     */
    IMPORT_C static CErrorUI* NewLC(CCoeEnv& aEnv);

    
    /** 
     * Destructor 
     */
    IMPORT_C ~CErrorUI();

    /**
     * Shows a global error note which is created by
     * resolving to a display text from the given error code.
     * The is the default method to be called by applications to
     * display error messages.     
     * @param aError    Any error code, for example ETel error or Email
     *                  error.
     * @param aContext  The context of the error, needed in special cases 
     *                  such as WAP errors, usually (and by default) ECtxAutomatic 
     * @return ETrue if error was displayed, EFalse otherwise.
     */
    IMPORT_C TBool ShowGlobalErrorNoteL(
         TInt aError,
         CTextResolver::TErrorContext aContext = CTextResolver::ECtxAutomatic
         );

    /**
     * Offers a reference to internal TextResolver instance
     * @return reference to ErrorUI's internal TextResolver instance   
     */
    inline CTextResolver& TextResolver(){ return *iTextResolver; } 

    /**
     * Shows a global error query with OK key, which is created by
     * resolving to a display text from the given error code.
     * The is the default method to be called by applications to
     * display error queries.
     * @param aError    Any error code, for example ETel error or Email
     *                  error.
     * @param aContext  The context of the error, needed in special cases 
     *                  such as WAP errors, usually (and by default) ECtxAutomatic 
     * @return ETrue if error was displayed, EFalse otherwise.
     */
    IMPORT_C TBool ShowGlobalErrorQueryL(
         TInt aError,
         CTextResolver::TErrorContext aContext = CTextResolver::ECtxAutomatic
         );

private:
    
    void ConstructL();
    static CErrorUI* ConstructLC(); 

private:

    // Text resolver used by this module
    CTextResolver*  iTextResolver;    
};

#endif      // ERROR_UI_H  
            
// End of File
