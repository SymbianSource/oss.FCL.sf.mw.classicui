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
* Description:  Popup adaptive search grid component
*
*/


#ifndef __AKNADAPTIVESEARCHGRID_H__
#define __AKNADAPTIVESEARCHGRID_H__

// INCLUDES
#include <AknControl.h>     // CCoeControl
#include <aknbutton.h>	    // CAknbutton
#include <eiklabel.h>
#include "AknAdaptiveSearchGridObserver.h"
#include <AknWsEventObserver.h>

// FORWARD DECLARATIONS
class CAknsBasicBackgroundControlContext;
class CAknsFrameBackgroundControlContext;
class CAknsListBoxBackgroundControlContext;
class CAknInputFrame;
class CEikEdwin;

// CLASS DECLARATION
/**
 *  The class to provide adaptive search grid for the application
 *
 *  @lib avkon.lib
 *  @since Series 60 5.0
 */

class CAknAdaptiveSearchGrid : public CAknControl, 							   
							   public MCoeControlObserver,
							   public MCoeControlBackground,
							   public MAknWsEventObserver				   
    {
    public: // Constructors and destructor

    /**
     * Two-phased constructor.
     *
     * @param aTextLimit text limit for the findpane. 
     * @param aFieldStyle The same flag as search field
     * @return Pointer to the created adaptive search grid object
     */
    static CAknAdaptiveSearchGrid* NewL( const TInt aTextLimit, 
                                         TInt aFieldStyle );

    /**
     * Two-phased constructor.
     *
     * @param aTextLimit text limit for the findpane. 
     * @param aFieldStyle The same flag as search field
     * @return Pointer to the created adaptive search grid object
     */
    static CAknAdaptiveSearchGrid* NewLC( const TInt aTextLimit, 
                                          TInt aFieldStyle );
    
        /**
         * Destructor.
         */
         ~CAknAdaptiveSearchGrid();

    public:  // From base classes
		
		/**
         * From CCoeControl.
         * Gets the number of controls contained in a compound control.
         *
         * @return The number of component controls contained by this control.
         */
         TInt CountComponentControls() const;

        /**
         * From CCoeControl.
         * Gets the specified component of a compound control.
         *
         * @param aIndex The index of the control to get
         * @return The component control with an index of aIndex.
         */
         CCoeControl* ComponentControl( TInt aIndex ) const ;

    	/**
         * From CCoeControl.
         * Handles a change to the control's resources.
         *
         * @param aType A message UID value.
         */
         void HandleResourceChange( TInt aType );
                
        /**
         * From CCoeControl.
         * Retrieves an object of the same type as that encapsulated in aId.
         *
         * @param aId An encapsulated object type ID.
         * @return Encapsulated pointer to the object provided. 
         *      Note that the encapsulated pointer may be NULL.
         */
         TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
                 
        /**
         * From MCoeControlObserver.
         * Handles an event from an observed adaptive search grid item.
         *
         * @param aControl The control which sent the event
         * @param aEventType The event type
         */
         void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

	    /**
         * From CCoeControl       
         *          
         * @param aRect the rectangle of this view that needs updating
         */
         void Draw( const TRect& aRect ) const;
        
        /**
         * From CCoeControl.
         * This function is called whenever a control gains or loses focus.
         *
         * @param aDrawNow Contains the value that was passed to it by SetFocus().
         */
         void FocusChanged( TDrawNow aDrawNow );
         
        /**
         * From MAknWsEventObserver. Handles window server events.       
         *       
         * @param The event that occurred.
         * @param The control that the event occurred in.                 
         */
         void HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination ); 
                  
        /**
         * From MCoeControlBackground.
         * Draw the background for a given control.
         * The text drawer that shall be used to draw text on the specific
         * background can be fetched through the GetTextDrawer() method.
         *
         * @param aGc Graphics context used for drawing.
         * @param aControl The control being drawn (may be a child of the drawer).
         * @param aRect The area to be redrawn.
         */
        void Draw( CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect ) const;
          
    public: // New functions     
        
        /**
         * Sets the observer for the adaptive search grid.
         *
         * @param aObserver A pointer to the observer. Ownership is not changed.
         */
         void SetAdaptiveSearchGridObserver( MAknAdaptiveSearchGridObserver* aObserver );

        /**
         * Returns a pointer to the adaptive search grid observer.
         *
         * @return Pointer to the adaptive search grid observer.
         */
         MAknAdaptiveSearchGridObserver* AdaptiveSearchGridObserver();        
        
        /**
         * Shows or hides adaptive search grid. 
         * Position of the top left corner should be set in advance. 
         * Adaptive search grid set visible with this method is by default focusing.
         * Does nothing if adaptive search grid is disabled.
         *          
         * @param aVisible ETrue to show it, EFalse to hide it.
         * @param aSelectAll ETrue to highlight all content of editor.
         */
         void SetVisibilityL( TBool aVisible, TBool aSelectAll );
        
        /**
         * Show adaptive search grid button.
         */
         void ShowL();
    
        /**
         * Returns adaptive search grid visibility at this moment
         *
         * @return ETrue, if adaptive search grid is shown.
         */
         TBool IsShown() const;
        
   		/**
         * Set chars to button array        
         * 
         * @param aGridChars are the characters for adaptive search grid.                  
         */
	 	 void SetButtonGridChars( const TDesC& aGridChars );
		
		/**
		 * Sets text into search field.
		 * 		 
		 * @param const aSearchTxt Reference to the text buffer.
         */            
	     void SetSearchTextToFindPane( const TDesC& aSearchTxt );
		
		/**
         * Initiates buttons for adaptive search grid        
         */
		 void InitGridButtons();
		
	    /**
         * Initiates position for buttons of grid        
         */
         void GridButtonsPositions();
         
       	/**
         * Main function for initiation adaptive search grid       
         */
  		 void InitGrid();  		 
  		 
  		/**
         * Show controls backspase, close, prev, next buttons and find pane      
         */
  		 void ShowControls();
                        
        /**
         * Hides adaptive search grid.
         */
         void HideL();              
         
         static const TInt EDeleteLastCharPressed = -1;
		 static const TInt ECloseGridPressed = -2;  
  
    protected: // From base class
  
  		/**
         * From CCoeControl.
         * Responds to size changes to sets the size and position of 
         * the contents of this control.
         */
         void SizeChanged();  
  
    private: // Constructors

        /**
         * C++ default constructor.
         *
         * @param aTextLimit text limit for the findpane. 
         */
         CAknAdaptiveSearchGrid( const TInt aTextLimit );               
        
        /**
         * Symbian 2nd phase constructor.
         * @param aFieldStyle The same flag as search field
         */
         void ConstructL( TInt aFieldStyle );
          

    private: // New functions         
                 
        /**
         * Update page indicator.
         */
         void UpdatePageIndicatorL();    
    
        /**
         * Sets the flag to be on or off and also calls
         * CCoeControl::MakeVisible().
         * 
         * @param aShown is True, if adaptive search grid is shown.                  
         */
         void SetShown( const TBool aShown );
        
        /**
         * Create and add button controlto adaptive search grid.
         * 
         * @param aText text for button grid                       
         */
         CAknButton* CreateButtonL();  
        
        /**
         * Show next page
         */ 
         void NextPage();
        
        /**
         * Show previous page
         */
         void PrevPage();     
     
        /**
         * Initiate controls
         * Create control buttons: close, backspase, next, previous.
         * @param aFieldStyle The same flag as search field
         */
         void InitControlsL( TInt aFieldStyle);
         
        /**
         * Initiate position for controls
         */         
    	 void ControlsPositions();         
      
	    /**
         * Gets rect from layout data
         */
         TRect RectFromLayout( const TRect& aParent,
             const TAknWindowComponentLayout& aComponentLayout ) const;
             
        /**
         * Update visibility of buttons from grid
         */
         void UpdateVisibleButtonsL();
         
        /**
         * Update layout option accoding to current amount of rows
         */
         void UpdatePageAndRowCount();    
         
         /**
         * Update icon's color accoding to current theme
         */
         CGulIcon* GetColorIconL( TInt aIndex );
         /**
          * Update layout variant
          */
         void UpdateLayoutVariant();
         
         /**
          * Update adaptive search grid skin.
          */
         void UpdateSkinL();

            
    private: // Member variables
		
        // array for adaptive search grid buttons
        RPointerArray<CAknButton> iButtonArray;

        // control buttons
        CAknButton* iCloseButton;
        CAknButton* iDeleteButton;  
        CAknButton* iPrevButton;
        CAknButton* iNextButton;       
        CAknButton* iLastFocusedButton;
      
        // page indicator if several pages       
        CEikLabel* iPageIndicator;           
                
        // find pane for AS
        CAknInputFrame* iInputFrame;
        CEikEdwin* iEditor;         
        TInt iTextLimit;     
	    
	    // skin context for find pane
   	    CAknsListBoxBackgroundControlContext* iSkinContextOfFindPane;   	
   	    CAknsFrameBackgroundControlContext* iBgContextOfFindPane; 
   	    	    	       	    
   	    // contex for control pane   
   	    CAknsBasicBackgroundControlContext* iBgContextOfControlPane;    	     
   	    
        // whether adaptive search grid is shown right now
        // IsVisible() is not safe enough because can be 
        // changed from outside with MakeVisible() 
        TBool iShown;
	    
	    // number of grid rows and cols
       	TInt iNumOfRows;
       	TInt iNumOfCols;
	    	           	
       	// number of grid pages
       	TInt iNumOfPages;
       	       	
       	// current page which shown on screen
       	TInt iCurrentPage;
     		
       	// current amount of total grid button
       	TInt iTotalGridButtons;
       	
       	// max amount of total grid button
       	TInt iMaxAmountOfButtons;
       	
       	// current button icon size
       	TSize iButtonIconSize; 
       	
       	// chars of grid
       	HBufC* iGridChars;          	
        
        // region which AS cover currently 	
        RRegion iCurrentRegion;
          	
        // current layout option
       	// 0 portrait with pages
        // 1 landscape with pages
        // 2 portrait with no pages
        // 3 landscape with no pages       	
       	TInt iLayoutOption;   
       	
       	TBool iToolbarShown;   
       	       	
       	// not owned
       	CAknAppUi* iAppUi;        
    
    	// observer to report adaptive search grid item events
   		// not owned
       	MAknAdaptiveSearchGridObserver* iAdaptiveSearchGridObserver;      	
       	
       	//Reset grids position when layout is changed.
       	TBool iLayoutChanged;
   

        // For ELJG-7VC8Q2: popup find pane overlap with Adaptive Search grid  
        TBool iPopupFindpane;
        // The length of overlap section 
        TInt iOverlapLength;

    };

#endif // __AKNADAPTIVESEARCHGRID_H__

// End of File

