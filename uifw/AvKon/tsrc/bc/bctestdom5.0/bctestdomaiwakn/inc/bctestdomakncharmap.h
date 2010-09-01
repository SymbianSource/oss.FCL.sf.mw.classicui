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

#ifndef C_CBCTESTDOMCAKNCHARMAP_H
#define C_CBCTESTDOMCAKNCHARMAP_H
  
#include <akncharmap.h>// for indirectly testing APIs in akncharmap.h
 
/**
 *  for indirectly testing APIs in akncharmap.h   .
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */    
class CBCTestDomCAknCharMap : public CAknCharMap
    {

public:
    /**
     * constructor.
     */

     CBCTestDomCAknCharMap ();

    /**
     * Destructor.
     */
     virtual ~CBCTestDomCAknCharMap ();

// from base class CAknCharMap  
     
     /**
      * from  CAknCharMap. 
      * for testing CAknCharMap::SizeChanged() .
      *
      * @since S60 v5.0  
      */
     IMPORT_C void SizeChanged();

     /**
      * from  CAknCharMap. 
      * for testing CAknCharMap::HandleResourceChange().
      *
      * @since S60 v5.0 
      * @param aType Resource type.
      * @return Pointer to control   
      */     
     IMPORT_C void HandleResourceChange(TInt aType);

     /**
      * from  CAknCharMap. 
      * for testing CAknCharMap::CountComponentControls().
      *
      * @since S60 v5.0 
      * @param anIndex Index of a control to be returned.
      * @return Count of component controls.   
      */     
     IMPORT_C TInt CountComponentControls() const;
     
     /**
      * from  CAknCharMap. 
      * for testing CAknCharMap::ComponentControl().
      *
      * @since S60 v5.0 
      * @param anIndex Index of a control to be returned.
      * @return Pointer to control   
      */     
     IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
 
 private:
     /**
      * This function handles pointer events directed at the charmapdialog.
      *
      * @since S60 v5.0       
      * @param aScrollBar The scrollbar to be observed.
      * @param aEventType The incomming event type so that correct 
      * functionality can be done.
      */
     void HandleScrollEventL( CEikScrollBar* aScrollBar, 
        TEikScrollEvent aEventType );
    
// from base class CCoeContrl

     /**
      * from CCoeContrl.
      * Reserved_2.
      *
      * @since S60 v5.0       
      */     
     void Reserved_2();    
     
     /**
      * from CCoeContrl.
      * Draw.Empty function.
      *
      * @since S60 v5.0  
      * @param aRect The rect to draw on.           
      */       
     void Draw(const TRect& aRect) const;
     
// from base class MAknPictographDrawerCallBack
     /**
      * from MAknPictographDrawerCallBack.
      * DrawPictographArea.
      *
      * @since S60 v5.0       
      */  
     void DrawPictographArea();
    };

#endif // C_CBCTESTDOMCAKNCHARMAP_H
