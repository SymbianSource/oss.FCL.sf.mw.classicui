/*
* ============================================================================
*  Name        : bctestdomuiserverunlockmedia.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : test the asynchronous methods of RAknUiServer.
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
