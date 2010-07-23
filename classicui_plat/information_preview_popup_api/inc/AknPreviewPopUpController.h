/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Preview popup controller.
*
*/


#ifndef AKNPREVIEWPOPUPCONTROLLER_H
#define AKNPREVIEWPOPUPCONTROLLER_H

// INCLUDES
#include <e32base.h>
#include <e32std.h>
#include <coecntrl.h>
#include <AknPreviewPopUpObserver.h>

// FORWARD DECLARATIONS
class MAknPreviewPopUpContentProvider;
class CAknPreviewPopUp;

// CLASS DECLARATION

/**
*  Class for controlling the preview popup component.
*  Preview popup is a popup that can be used to show some extra information
*  about e.g. a highlighted list item. It cannot get keyboard focus. Popup is
*  shown after a default timeout of one second and hidden on key press or when
*  it has been visible for ten seconds. These timeouts can be changed via this
*  API.
*
*  Preview popup itself provides only timing services and an empty popup window
*  whose frames and background are drawn with the current skin. It is client
*  application's responsibility to provide the actual content. This can be any
*  object derived from CCoeControl. When the popup is shown it asks content's
*  size using CCoeControl::MinimumSize and sizes itself so that the whole
*  content fits into the popup. Content can also be created asynchronously if
*  it takes considerable amount of time.
*
*  @lib avkon.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS( CAknPreviewPopUpController ) : public CTimer
    {
    public: // Type definitions
        enum TAknPreviewStyle
            {
            ELayoutDefault = 0x0001, // default graphics are used
            ELayoutSubMenu = 0x0002, // submenu graphics are used
            EPermanentMode = 0x0004, // popup stays visible infinitely
            EFixedMode     = 0x0008, // fixed position and size are used
            EExcludeFrames = 0x0010, // frames and heading area are excluded in fixed mode
            EAutoMirror    = 0x0020, // opening direction is automatically mirrored in left-to-right layouts
            EDontClose     = 0x0040  // popup not closed when pointer up received outside popup 
    };
            
        enum TAknPreviewPopUpContentSize
            {
            ESmall,
            ELarge
            };
            
    public: // Constructors and destructor

        /**
        * Two-phased constructor. This version should be used if the content
        * is created asynchronously.
        * @param aContent Reference to the content of the preview popup.
        * @param aContentProvider Reference to the content provider of the popup.
        */
        IMPORT_C static CAknPreviewPopUpController* NewL( CCoeControl& aContent,
            MAknPreviewPopUpContentProvider& aContentProvider );

        /**
        * Two-phased constructor. This version should be used if the content is
        * created synchronously i.e. it's ready when the popup is about to be
        * shown. This is also the normal use case.
        * @param aContent Reference to the content of the preview popup.
        */
        IMPORT_C static CAknPreviewPopUpController* NewL( CCoeControl& aContent );
        
        /**
        * Two-phased constructor. This version should be used if the content
        * is created asynchronously.
        * @param aContent Reference to the content of the preview popup.
        * @param aContentProvider Reference to the content provider of the popup.
        * @param aStyle Defines the used layout and behavior flags.
        */
        IMPORT_C static CAknPreviewPopUpController* NewL( CCoeControl& aContent,
            MAknPreviewPopUpContentProvider& aContentProvider,
            const TInt aStyle );

        /**
        * Two-phased constructor. This version should be used if the content is
        * created synchronously i.e. it's ready when the popup is about to be
        * shown. This is also the normal use case.
        * @param aContent Reference to the content of the preview popup.
        * @param aStyle Defines the used layout and behavior flags.
        */
        IMPORT_C static CAknPreviewPopUpController* NewL( CCoeControl& aContent,
            const TInt aStyle );
            
  	    /**
        * Destructor.
        */
        ~CAknPreviewPopUpController();

    public: // New functions
        
        /**
        * This static function can be used to query the logical size of the
        * screen when drawing the content of the popup. When ELarge is returned
        * more detailed information (e.g. a picture) can be shown whereas ESmall
        * suggests that the available screen area is more limited and simpler
        * content should be used.
        * @return Logical size of the screen.
        */
        IMPORT_C static TAknPreviewPopUpContentSize ContentSizeInLayout();

        /**
        * Sets the delay used before showing the preview popup. The default 
        * delay is one second.
        * @param aDelay Delay in microseconds.
        */
        IMPORT_C void SetPopUpShowDelay( const TTimeIntervalMicroSeconds32& aDelay );
        
        /**
        * Sets the delay used before hiding the preview popup. The default
        * delay is three seconds.
        * @param aDelay Delay in microseconds.
        */
        IMPORT_C void SetPopUpHideDelay( const TTimeIntervalMicroSeconds32& aDelay );
        
        /**
        * Sets the preview popup visible after specified delay. If the popup
        * is already visible it is hidden immediately and shown again after the
        * showing delay. Popup is automatically hidden after its hiding delay
        * unless the delay is zero in which case the popup is shown infinitely.
        */
        IMPORT_C void ShowPopUp();
        
        /**
        * Hides the popup immediately.
        */
        IMPORT_C void HidePopUp();
        
        /**
        * If application wishes to build preview popup's content asynchronously
        * the content class should be derived from MAknPreviewPopUpContentProvider
        * in addition to CCoeControl. This function must be called by the content
        * object when it has finished its asynchronous building operation.
        */
        IMPORT_C void ContentReady();
        
        /**
        * Sets the position of preview popup. Popup's size is determined by the
        * size of its content. The popup is placed left and down from the given 
        * point. If fixed mode is used then this function has no effect.
        * @param aPoint Popup's position.
        */
        IMPORT_C void SetPosition( const TPoint& aPoint );

        /**
        * Sets the position of the preview popup so that it is aligned with the
        * given rectangle as specified in the LAF data. This is intented to be
        * used in conjunction with lists and grids if the application wishes to
        * implement a popup that follows lists/grids item highlight.
        * @param aHighlightRect Screen-relative rectangle used to calculate 
        * popup's position.
        */
        IMPORT_C void SetPositionByHighlight( const TRect& aHighlightRect );

        /**
        * Adds the observer to the list of observers. Observers in the list are
        * notified of events in preview popup.
        * @param aObserver Observer.
        */
        IMPORT_C void AddObserverL( const MAknPreviewPopUpObserver& aObserver );
        
        /**
        * Removes the given observer from the observer list.
        * @param aObserver Observer.
        */
        IMPORT_C void RemoveObserver( const MAknPreviewPopUpObserver& aObserver );
        
        /**
        * Updates popup's size to reflect a change in content's size.
        * Should be called if the size of the content is changed dynamically.
        */
        IMPORT_C void UpdateContentSize();
        
        /**
        * Returns the popup's size.
        */
        IMPORT_C TSize Size() const;
        
        /**
        * Sets optional heading text. If heading text is already set the
        * current text is replaced. When set also a closing icon is shown if 
        * the currently active layout supports stylus.
        * @param aText Heading text.
        */
        IMPORT_C void SetHeadingTextL( const TDesC& aText );
        
        /**
        * Notifies observers about the specified preview popup event.
        * @param aEvent Preview popup event.
        */
        void NotifyObservers( MAknPreviewPopUpObserver::TPreviewPopUpEvent aEvent );
      
      	/**
      	 * Resets the popup timeout.
      	 */
      	IMPORT_C void ResetTimer();
      	
    protected: // Functions from base classes
	
	    /**
	    * From CTimer. Cancels an outstanding asynchronous request.
	    */
        void DoCancel();
        
        /**
        * From CActive. Handles active object's request completion event.
        */
        void RunL();
        
        /**
        * From CActive. Handles leaves that occur while RunL is executed.
        * @param aError Leave code.
        * @return Always KErrNone.
        */
        TInt RunError( TInt aError );

    private: // Constructors

        /**
        * C++ default constructor.
        * @param aContentProvider Pointer to the content provider of the popup.
        */   
        CAknPreviewPopUpController( 
            MAknPreviewPopUpContentProvider* aContentProvider );

      	/**
      	* Symbian 2nd phase constructor.
      	* @param aContent Reference to the content of the preview popup.
      	* @param aStyle Defines the layout and style of the preview popup.
      	*/
        void ConstructL( CCoeControl& aContent, 
                         const TInt aStyle );

    private: // Data
  	
  	    enum TPreviewState
  	        {
  	        EShowing,
  	        EHiding,
  	        EBuildingContent
  	        };
  	        
        // state of preview popup controller
        TPreviewState iState;
        
  	    // interface for asynchronous content building
        MAknPreviewPopUpContentProvider* iContentProvider; // Not owned
        
        // pointer to preview popup.
        CAknPreviewPopUp* iPopUp;
        
        // delay used before showing the preview popup
        TTimeIntervalMicroSeconds32 iPopUpShowDelay;
        
        // delay used before hiding the preview popup
        TTimeIntervalMicroSeconds32 iPopUpHideDelay;
        
        // array containing pointers to registered observers
        RPointerArray<MAknPreviewPopUpObserver> iObservers;
        
        // True if timer is being resetted and the DoCancel should not hide the popup
        TBool iResetting;
    };

#endif // AKNPREVIEWPOPUPCONTROLLER_H

//  End of File  
