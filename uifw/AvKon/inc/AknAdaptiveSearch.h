/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __AKNADAPTIVESEARCH_H__
#define __AKNADAPTIVESEARCH_H__

// INCLUDES
#include "AknAdaptiveSearchGrid.h"
#include "AknAdaptiveSearchGridObserver.h"
#include <cenrepnotifyhandler.h>    // CenRep for AS

// FORWARD DECLARATIONS
class CAknSearchField;
class MAdaptiveSearchTextObserver;
class CRepository;
//class CCenRepNotifyHandler;

// CLASS DECLARATION

/**
 *  The class to provide adaptive search for the application
 *
 *  @lib avkon.lib
 *  @since Series 60 5.0
 */

class CAknAdaptiveSearch : public CBase, 
                           public MAknAdaptiveSearchGridObserver,
                           public MCenRepNotifyHandlerCallback,
			               public MCoeControlObserver								   
    {
    public: // Constructors and destructor

    /**
     * Two-phased constructor.
     *
     * @param aTextLimit The limit length of search field
     * @param aFieldStyle The same flag as search fi1eld
     * @return Pointer to the created adaptive search grid object
     */
    static CAknAdaptiveSearch* NewL( const TInt aTextLimit, TInt aFieldStyle);
    
    /**
     * Two-phased constructor.
     *
     * @param aTextLimit The limit length of search field
     * @param aFieldStyle The same flag as search field.
     * @return Pointer to the created adaptive search grid object
     */
    static CAknAdaptiveSearch* NewLC( const TInt aTextLimit, TInt aFieldStyle );
    
        /**
         * Destructor.
         */
         ~CAknAdaptiveSearch();

    public:  // From MAknAdaptiveSearchGridObserver

        /**
         * Handles an event from an observed adaptive search grid
         *
         * @param aCommand The control which sent the event        
         */       
         void ProcessCommandL( TInt aCommand );
		 
    public:  // From MCoeControlObserver

        /**
         * From MCoeControlObserver. Handles an event from an observed control.
         * If this component has observer, then a EEventStateChanged is sent 
         * to it when a item is selected from the grid
         * 
         * @param aControl The control that sent the event.
         * @param aEventType The event type. 
         */     
	     void HandleControlEventL( CCoeControl *aControl, TCoeEvent aEventType );
	     
   public: // from MCenRepNotifyHandlerCallback     
         void HandleNotifyInt( TUint32 aId, TInt aNewValue ); 	   
		           
   public: // New functions           
               
        /**
         * Shows adaptive search grid.
         */
         void ShowAdaptiveSearchGridL();        
      
    	/**
         * Hides adaptive search grid.
         */
         void HideAdaptiveSearchGridL();           
  
  		/**
         * Invert adaptive search grid.
         * @param aSelectAll If true, select all content in adaptive search editor.
         */
         void InvertAdaptiveSearchGridVisibilityL( TBool aSelectAll = EFalse );
  		
        /**
      	 *  Set characters for buttons to adaptive search grid
      	 *        	 
      	 *  @param aGridChars The characters for adaptive search grid.      	 
         */
	     void SetButtonCharsL( const TDesC& aGridChars );
  
	    
	    /**
	     * Sets a search field for this control.
	     *	     
	     * @param aSearchField A pointer to a search field object.
	     */	
	     void SetSearchField( CAknSearchField *aSearchField );
	     
	   /** 
    	* Adds an adaptive search text observer. Duplicates are not checked 
    	* (i.e. adding the same observer multiple times is not prevented). 
   		* 
   		* @since 5.0 
    	* @param aObserver Must be non-NULL. 
    	*/ 
    	void AddAdaptiveSearchTextObserverL( MAdaptiveSearchTextObserver* aObserver );

       /** 
    	* Removes an adaptive search text observer. 
    	* 
    	* @since 5.0 
   	 	* @param aObserver The observer to be removed. 
    	* @return ETrue if removal ok, EFalse if observer was not removed (not 
    	* found from the list of observers). 
    	*/ 
    	TBool RemoveAdaptiveSearchTextObserver( MAdaptiveSearchTextObserver* aObserver );	
 
    	/**
    	 * Update adaptive search grid skin.
    	 */
    	void UpdateGridSkinL();
    	
   private: // Constructors

         /**
          * C++ default constructor.
          */
          CAknAdaptiveSearch();          
        
    /**
     * Symbian 2nd phase constructor.
     *
     * @param aTextLimit The limit length of search field
     * @param aFieldStyle The same flag as search field
     */
    void ConstructL( const TInt aTextLimit, TInt aFieldStyle );       
    
   private: // Member variables	    
       
	    // Observer to report adaptive search text changes, not owned
       	MAdaptiveSearchTextObserver* iAdaptiveSearchTextObserver; 
       	
       	CAknAdaptiveSearchGrid* iAdaptiveSearchGrid;              	       	
        	
       	CAknSearchField* iSearchField; // not owned
       	
       	// Chars of grid from filtered items
       	HBufC* iGridChars;       	
       	
       	// Limit length of search field 
       	TInt iTextLimit;  
       	
       	TBool iBlockFlag;	  

        // Handle to Central Repository.
        CRepository* iCenRep;    
        
        // For CenRep value change notifications. 
        CCenRepNotifyHandler* iCenRepNotifyHandlerChinese;  
        CCenRepNotifyHandler* iCenRepNotifyHandlerPRC;
        CCenRepNotifyHandler* iCenRepNotifyHandlerTW;
        CCenRepNotifyHandler* iCenRepNotifyHandlerHongkong;        	  
    };

#endif // __AKNADAPTIVESEARCH_H__

// End of File

