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

#ifndef C_BCTESTDOMAKNANIMATEDVIEW_H
#define C_BCTESTDOMAKNANIMATEDVIEW_H

#include <aknanimview.h>

const TUid KBCTestAknAnimatedViewId = { 2 };
 
/**
 *  CBCTestDomAknAnimatedView class
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */  
class CBCTestDomAknAnimatedView : public CAknAnimatedView
    {
public:  
    /**
     * Symbian static 2nd constructor
     */
    static CBCTestDomAknAnimatedView* NewLC( );
    
    /**
     * destructor
     */
    virtual ~CBCTestDomAknAnimatedView();

// from base classes from CAknView

    /**
     * From CAknView.
     * Return view Id.
     *
     * @since S60 v5.0       
     * @return  view Uid value
     */
    TUid Id() const;
    
    /**
     * From CAknView.
     * HandleCommandL.
     *
     * @since S60 v5.0      
     * @param aCommand Command to be handled.
     */
    void HandleCommandL( TInt aCommand );
    
// from base classes from CAknAnimatedView.    

    /**
     * From CAknAnimatedView.     
     * AknViewActivatedL
     *
     * @since S60 v5.0       
     * @param aPrevViewId The id of the previous view
     * @param aCustomMessageId message identifier
     * @param aCustomMessage custom message provided when the view is changed
     */
	IMPORT_C virtual void AknViewActivatedL(
	    const TVwsViewId& aPrevViewId,
	    TUid aCustomMessageId,
	    const TDesC8& aCustomMessage );
	    
    /**
     * From CAknAnimatedView.     
     * PreAnimateSetup
     *
     * @since S60 v5.0       
     */	    
	IMPORT_C virtual void PreAnimateSetup();

    /**
     * From CAknAnimatedView.     
     * PreAnimateSetup
     *
     * @since S60 v5.0       
     */		
	IMPORT_C virtual void PostAnimateSetup();	
	    
protected:  

// from base classes from CAknView    

    /**
     * From CAknView.     
     * DoActivateL
     *
     * @since S60 v5.0       
     * @param aPrevViewId The id of the previous view
     * @param aCustomMessageId message identifier
     * @param aCustomMessage custom message provided when the view is changed
     */
     void DoActivateL( const TVwsViewId& aPrevViewId,
                       TUid aCustomMessageId,
                       const TDesC8& aCustomMessage );
    
    /**
     * From CAknView.
     * When view is deactivated, do something.
     *
     * @since S60 v5.0      
     */         
    void DoDeactivate();

private:  

    /**
     * C++ default constructor
     */
    CBCTestDomAknAnimatedView();

    /**
     * symbian 2nd constructor
     */
    void ConstructL(); 

    };

#endif // C_BCTESTDOMAKNANIMATEDVIEW_H

// End of File
