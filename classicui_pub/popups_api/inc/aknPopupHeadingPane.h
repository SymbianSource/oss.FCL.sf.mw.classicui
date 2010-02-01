/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*   Heading pane
*
*/


#ifndef AKNPOPUPHEADINGPANE_H
#define AKNPOPUPHEADINGPANE_H

// INCLUDES
#include <AknControl.h>

#include <eikbtgpc.h>
#include <AknUtils.h>


#include <aknappui.h>
#include <aknPopup.h>
#include <gulicon.h>

// FORWARD DECLARATIONS
class CAknTextControl;
class CEikImage;
class CAknBitmapAnimation;
class CAknPopupHeadingAttributes;
class CAknPopupHeadingPaneExtension;
class MAknHeadingPaneTouchObserver;

// CLASS DECLARATION

/**
 * Header control for queries.
 * Defines properties of the header of the pop-up menu.
 *
 * @since Series 60 0.9
 */
class CAknPopupHeadingPane : public CAknControl
{
    public:
        /**
        * Enumeration for different layouts
        */
        enum THeadingPaneLayout
            {
            /** Query mode layout for heading pane */
            EQueryHeadingPane,
            /** List mode layout for heading pane */
            EListHeadingPane,
            /** Heading pane for colour selection list. @since 3.0 */
            EColourSelectionGridHeadingPane,
            /** Heading pane for message query. @since 3.0 */
            EMessageQueryHeadingPane
            };


    public:
         /**
         * Constructor.
         */      
		IMPORT_C CAknPopupHeadingPane();
		
         /**
         * Destructor.
         */  		
        IMPORT_C ~CAknPopupHeadingPane();
        
         /**
         * From @c CCoeControl.
         * Responds to size changes to sets the size and position of the
         * contents of the heading pane.
         */   
        IMPORT_C void SizeChanged();
        
         /**
         * From @c CCoeControl.
         * Get the minimum required size of heading pane.
         * @return The minimum required size of heading pane.
         */          
        IMPORT_C TSize MinimumSize();
        
         /** 
         * Completes the construction of the @c CAknPopupHeadingPane object.
         * Layout is set to @c EQueryHeadingPane by default.
         * @param aText Header text.
         */       
        IMPORT_C void ConstructL(TPtrC aText);
        
         /** 
         * From @c CCoeControl.
         * Constructs heading pane from a resource file.
         * Current resource reader position must point to @c AVKON_HEADING
         * resource.
         * @param aReader The resource reader with which to access the header
         * resource values.
         */        
        IMPORT_C void ConstructFromResourceL(TResourceReader &aReader);
        
         /** 
         * Get pointer to the prompt control.
         * @return A pointer to the prompt control.
         */
        IMPORT_C CEikLabel *Prompt() const;
        
         /** 
         * Get prompt text.
         * @return A prompt text.   
         */       
		IMPORT_C TPtr PromptText() const;

        /** 
         * Set header text.
         * @param aText A header text.   
         */
        IMPORT_C void SetTextL(TPtrC aText);
        
        
         /** 
         * Set header image. Gets the ownership of the image.
         * @param aImage A  header image.   
         */      
        IMPORT_C void SetHeaderImageOwnedL(CEikImage *aImage);
  
          /** 
         * Set header image.
         * @param aImage A header image.   
         */      
        IMPORT_C void SetHeaderImageL(CEikImage *aImage);
        
        /** 
         * Set header animation by reading @c BMPANIM_DATA resource.
         * @param aResourceId A resource identifier for the header animation.
         */
        IMPORT_C void SetHeaderAnimationL(TInt aResourceId);	
        
        /**
         * Set layout of the heading pane.
         * @param aLayout A layout of the heading pane.
         */        	
        IMPORT_C void SetLayout( THeadingPaneLayout aLayout );

        /**
         * Start the animation.
         */
        IMPORT_C void StartAnimationL();
        
        /**
         * Cancel the animation.
         * Calls @c RBitmapAnim::CommandReply(EBitmapAnimCommandStopAnimation).
         * @return A value defined by the animation writer. The value may, 
         * in some cases, be defined to be an error code.
         */        
        IMPORT_C TInt CancelAnimation();

    public: 
         /**
         * From @c CCoeControl. 
         * Activates popup heading. Calls @c CCoeControl::ActivateL().
         */   
        virtual void ActivateL();
    	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

		 /**
	     * Handles a change to the control's resources of type aType
	     * which are shared across the environment, e.g. colors or fonts.
	     *
	     * @since 3.1
	     */
	     IMPORT_C void HandleResourceChange(TInt aType);

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt anIndex) const;
        IMPORT_C virtual void Draw(const TRect& aRect) const;

		void DoSetPromptL();
		void LayoutQueryHeadingPane();
		void LayoutListHeadingPane();
		void LayoutColourSelectionGridHeadingPane();
		void LayoutMessageQueryHeadingPane();
	
	private:
        //TAknLayoutRect     iLayoutLine; // Not used
        CAknPopupHeadingPaneExtension*	iExtension;  // was TAknLayoutRect iLayoutLine
        TAknLayoutRect     iLayoutHeading;
        CAknTextControl*   iPrompt;
        CEikImage*         iHeaderImage;
        CAknBitmapAnimation* iAnimation;
        TInt               iHeadingLayoutRef;
		CAknPopupHeadingAttributes* iAttributes; // was THeadingPaneLayout iLayout;

	private: // new methods
		void SetAnimationBackGroundFrameL();

    public: // new methods
        void SetPageL(TInt aCurrent, TInt aMax=0);

         /** 
         * Set heading frame ids. These can be used to override default ids.
         * @param aFrameId / aFrameCenterId Ids of heading's frame..   
         */
		IMPORT_C void SetSkinFrameId(const TAknsItemID &aFrameId);
		IMPORT_C void SetSkinFrameCenterId(const TAknsItemID &aFrameCenterId);
		
		/**
		 * Set the heading pane touch observer. The observer must derive from MAknHeadingPaneTouchObserver
		 * and implement method HandleHeadingPanePointerEventL().
		 */
		void SetTouchObserver( MAknHeadingPaneTouchObserver* aTouchObserver );
        

    private:
        HBufC* PageTextL() const;
};

#endif

