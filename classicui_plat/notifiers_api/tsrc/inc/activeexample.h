/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test notifiers_api
*
*/


/*
 *INCLUDES
 */
#ifndef C_CACTIVEEXAMPLE_H
#define C_CACTIVEEXAMPLE_H

#include <e32base.h>    // For CActive, link against: euser.lib
#include <e32std.h>     // For RTimer, link against: euser.lib
#include <fbs.h>
#include<bamdesca.h>

/*
 * class declare
 */
class CAknGlobalConfirmationQuery;
class CAknGlobalListQuery;
class CAknGlobalMsgQuery;
class CAknGlobalNote;
class CAknGlobalProgressDialog;
class CAknGlobalListMsgQuery;

/*
 * This class inherit from CActive, it is used to test the asynchronous function
 */
class CActiveExample : public CActive
    {
public:
    /*
     * This function is used to test the showconfirmationqueryL function
     */
    static void ShowAndCancelConfirmationQueryLL( const TDesC& aPrompt );
    /*
     * This function is used to test the showconfirmationqueryL function
     */
    void ShowAndCancelConfirmationQueryL( const TDesC& aPrompt );
    /*
     * This function is used to test the showlistqueryL function
     */
    static void ShowAndCancelListQueryLL( const MDesCArray* aItems );
    /*
     * This function is used to test the showlistqueryL function
     */
    void ShowAndCancelListQueryL( const MDesCArray* aItems );
    /*
     * This function is used to test the showmsgqueryL function
     */
    static void ShowMsgQueryLL( const TDesC& aMsgText,
            TInt aSoftkeys,
            const TDesC& aHeaderText,
            const TDesC& aHeaderImageFile,
            TInt aImageId,
            TInt aImageMaskId );
    /*
     * This function is used to test the showmsgqueryL function
     */
    void ShowMsgQueryL( const TDesC& aMsgText,
            TInt aSoftkeys,
            const TDesC& aHeaderText,
            const TDesC& aHeaderImageFile,
            TInt aImageId,
            TInt aImageMaskId );
    /*
     * This function is used to test the shownotel function 
     */
    static void ShowNoteLL( TAknGlobalNoteType aType, const TDesC& aNoteText );
    /*
     * This function is used to test the shownotel function 
     */
    void ShowNoteL( TAknGlobalNoteType aType, const TDesC& aNoteText );
    /*
     * This function is used to test the showprogressdialogl function and 
     * refer to the cancel function
     */
    static void ShowAndCancelProgressDialogLL( const TDesC& aPrompt );
    /*
     * This function is used to test the showprogressdialogl function and 
     * refer to the cancel function
     */
    void ShwoAndCancelProgressDialogL( const TDesC& aPrompt );
    /*
     * NewL fuction
     */
    static CActiveExample* NewL();
    /*
     * NewLC function
     */
    static CActiveExample* NewLC();
    /*
     * Destructor
     */
    ~CActiveExample();
    /*
     * DoCancel function
     */
    void DoCancel();
    /*
     * This function is used to test the ShowListMsgQueryL function 
     */
    void ShowTheListMsgQueryL();
    
protected:
    /*
     * RunL function
     */
    void RunL();

private:
    /*
     * Constructor
     */
    CActiveExample();
    /*
     * Constructl function
     */
    void ConstructL();
    
private:
    CAknGlobalConfirmationQuery* iConfirmationquery;
    CAknGlobalListQuery* iListQuery;
    CAknGlobalMsgQuery* iMsgQuery;
    CAknGlobalNote* iNote;
    CAknGlobalProgressDialog* iProgressDialog;
    CAknGlobalListMsgQuery* iGlobalListMsgQuery;
    };

#endif

// End of File
