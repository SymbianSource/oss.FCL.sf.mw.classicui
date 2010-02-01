/*
* ============================================================================
*  Name        : bctestdomakncharmap.h
*  Part of     : BCTest / bctestdomaiwakn       
*  Description : for indirectly testing APIs in akncharmap.h 
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
