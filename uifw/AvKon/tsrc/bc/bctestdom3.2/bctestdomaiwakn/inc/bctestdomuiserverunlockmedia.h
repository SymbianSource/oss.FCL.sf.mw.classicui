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

#ifndef C_CBCTESTDOMUISERVERUNLOCKMEDIA_H
#define C_CBCTESTDOMUISERVERUNLOCKMEDIA_H

 
#include <akncapserverclient.h> 

 
/**
 *  test the asynchronous methods of RAknUiServer.
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */  
class CBCTestDomUiServerUnlockMedia : public CActive
    {

public:

     static CBCTestDomUiServerUnlockMedia  * NewLC();

    /**
     * Destructor.
     */
     virtual ~CBCTestDomUiServerUnlockMedia  ();

    /**
     * Unlock the default Multimedia Memory Card.
     *
     * Display a text query dialog requesting the password.
     * Unlock the MMC using the password entered by the user
     * in this dialog (unless the dialog is cancelled).
     * If the password is wrong display the dialog again with
     * a different prompt. This call is asynchronous, the
     * application should not assume that the card has been
     * unlocked when this function returns. In fact,
     * when this function returns the dialog is still
     * displaying. If the application needs to be notified
     * when the unlock operation is complete, it should implement
     * UnlockComplete. Memory for this class is automatically
     * released when the unlock operation is complete.
     * The application should therefore not delete this object.
     *
     * @since S60 v5.0     
     * @param aStore        store passwd
     *
     */
    void UnlockCardLD( TBool aStore = ETrue );

protected: 

// from base class CActive  
    /**
     * from  CActive.  
     * will delete this unless we are deleting already 
     *
     * @since S60 v5.0    
     */
     void DoCancel();  
     
    /**
     * from  CActive. 
     * Internal routine to set the state
     *
     * @since S60 v5.0
     */
     void RunL();
     
private:

     CBCTestDomUiServerUnlockMedia();

     void ConstructL();
   
    /**
     * StartL     
     * 
     *
     * @since S60 v5.0
     * @param aDrive  Drive number.
     */
     void StartL( TDriveNumber& aDrive);    

private: // Data

    /**
     * a RAknUiServer object
     */
    RAknUiServer    iAknCapServerClient;

    /**
     * whether to store passwd.
     */
    TBool         iStore;
    };

#endif // C_CBCTESTDOMUISERVERUNLOCKMEDIA_H
