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
* Description:  test special_character_table_api
*
*/


#ifndef C_TESTDOMCHARMAP_H
#define C_TESTDOMCHARMAP_H

//  INCLUDES
#include <coecntrl.h>
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <akncharmap.h>

#include "testdomspecialchartab.h"

/**
 *  for indirectly testing APIs in akncharmap.h   
 *  @code
 *  @endcode
 *  @lib   
 *  @since S60 v5.0
 */
class CTestDomCharMap : public CAknCharMap
    {
public:
    /**
    * C++ default constructor.
    */

    CTestDomCharMap ();

    /**
     * Destructor.
     */
     virtual ~CTestDomCharMap ();

     // from base class CAknCharMap  
     
     /**
      * from  CAknCharMap. 
      * for testing CAknCharMap::SizeChanged() .
      *
      * @since S60 v5.0  
      */
      void DoSizeChanged();

     /**
      * from  CAknCharMap. 
      * for testing CAknCharMap::HandleResourceChange().
      *
      * @since S60 v5.0 
      * @param aType Resource type.
      * @return Pointer to control   
      */     
      void DoHandleResourceChange(TInt aType);

     /**
      * from  CAknCharMap. 
      * for testing CAknCharMap::CountComponentControls().
      *
      * @since S60 v5.0 
      * @param anIndex Index of a control to be returned.
      * @return Count of component controls.   
      */     
      TInt DoCountComponentControls() const;
     
     /**
      * from  CAknCharMap. 
      * for testing CAknCharMap::ComponentControl().
      *
      * @since S60 v5.0 
      * @param anIndex Index of a control to be returned.
      * @return Pointer to control   
      */     
      CCoeControl* DoComponentControl(TInt aIndex) const;
 
 private:
     /**
      * This function handles pointer events directed at the charmapdialog.
      *
      * @since S60 v5.0       
      * @param aScrollBar The scrollbar to be observed.
      * @param aEventType The incomming event type so that correct 
      * functionality can be done.
      */
     void HandleScrollEventL( CEikScrollBar* aScrollBar, TEikScrollEvent aEventType );
    
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

#endif // C_TESTDOMCHARMAP_H

// End of File


