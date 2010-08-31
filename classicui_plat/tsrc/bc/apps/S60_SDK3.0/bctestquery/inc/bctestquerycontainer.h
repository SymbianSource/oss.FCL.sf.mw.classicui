/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         container
*
*/








#ifndef C_BCTESTQUERYCONTAINER_H
#define C_BCTESTQUERYCONTAINER_H

#include <coecntrl.h>

class CBCTestQueryBaseCase;

/**
* container class
*/
class CBCTestQueryContainer: public CCoeControl
    {
public: 
    
// constructor and destructor
    
    CBCTestQueryContainer();
    
    virtual ~CBCTestQueryContainer();
    
    void ConstructL( const TRect& aRect );
    
// new functions
    
    /**
    * Set component control, and this container will own the 
    * component control.
    */
    void SetControl( CCoeControl* aControl ); 
    
    void ResetControl();
  
// from CCoeControl

    TInt CountComponentControls() const;
    
    CCoeControl* ComponentControl( TInt aIndex ) const;

private: // from CCoeControl    
    
    /**
    * From CCoeControl, Draw.
    * Fills the window's rectangle.
    * @param aRect Region of the control to be (re)drawn.
    */
    void Draw( const TRect& aRect ) const;  
    
private: // data
    
    /**
     * Responsible for delete this
     */ 
    CCoeControl* iControl; 
       
    };    

#endif // C_BCTESTQUERYCONTAINER_H
