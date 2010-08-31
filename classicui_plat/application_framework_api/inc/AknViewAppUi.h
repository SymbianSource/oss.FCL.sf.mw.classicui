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
* Description:  Base class for view architecture-based applications.
*
*/

#ifndef __AKNVIEWAPPUI_H__
#define __AKNVIEWAPPUI_H__

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CAknView;
class CAknViewShutter;
class CAknLocalScreenClearer;
class CAknViewAppUiExtension;
class CAknViewNavigator;

// MACROS
#define iAvkonViewAppUi ((CAknViewAppUi*)CEikonEnv::Static()->EikAppUi())

// CLASS DECLARATION

/**
*  Base class for view architecture-based applications.
*
*  @since Series 60 0.9
*/
class CAknViewAppUi : public CAknAppUi
    {
public:
	NONSHARABLE_CLASS(CViewActivationItem) : public CBase
		{
	public:

        /**
        * Two-phased constructor.
        * @param aNewView Application view.
        * @param aCustomMessageId Message ID.
        * @param aCustomMessage Message contents.
        * @param aPrevViewId The UID of the previously active view.
        * @return Pointer to new @c CViewActivationItem object.
        */
		static CViewActivationItem* NewLC(CAknView* aNewView, 
		                                  TUid aCustomMessageId, 
		                                  const TDesC8& aCustomMessage, 
		                                  const TVwsViewId& aPrevViewId);
		
		/**
        * Destructor.
        */
		~CViewActivationItem();
	private:
		CViewActivationItem(CAknView* aNewView, 
		                    TUid aCustomMessageId,
		                    const TVwsViewId& aPrevViewId);
		                    
		void ConstructL(const TDesC8& aCustomMessage);
	public:
		
		// Application view.
		CAknView* iNewView;
		
		// Message ID.
		TUid iCustomMessageId;
		
		// Message contents.
		HBufC8* iCustomMessage;
		
		// The UID of the previously active view.
		TVwsViewId iPrevViewId;
		};

        /**
        * Container class used to hold information about one split view.
        */
        NONSHARABLE_CLASS(TAknSplitViewContainer)
            {
            public:
                /**
                * Checks is a view is part of the split view.
                * @param aViewId UID of the view to be checked.
                * @return ETrue if the given view belongs to the split view.
                */
                TBool IsPartOf( const TUid aViewId );

            public:
                // view uids
                TUid iViewIds[2];
                // ETrue if a view's activation failed
                TBool iFailed[2];
                // drawing areas
                TRect iViewRect[2];
                // the size of the leftmost view
                TInt iLeftViewSize;
            };

    	typedef CArrayPtrFlat<CViewActivationItem> CAknViewActivationQueue;
    	typedef CArrayPtrFlat<CAknView> CAknViews;

public:

    /**
    * Initialises this app UI with standard values.
    * @param aAppUiFlags Application user interface flags.
    */
	IMPORT_C void BaseConstructL(TInt aAppUiFlags=EStandardApp);
	
	/**
    * Destructor.
    */
	IMPORT_C virtual ~CAknViewAppUi();
    
    /**
    * Activates a specified application view, without passing any message.
    * The function leaves if activation of the view fails.
    * @param aViewId Identifier of the view to activate.
    */
	IMPORT_C void ActivateLocalViewL(TUid aViewId);

    /**
    * Activates a specified application view, then passes the message text 
    * descriptor aCustomMessage for a message of type aCustomMessageId.
    * The function leaves if activation of the view fails.
    * @param aViewId Identifier of the view to activate.
    * @param aCustomMessageId Specifies the message type.
    * @param aCustomMessage The message passed to the activated view.
    */
	IMPORT_C void ActivateLocalViewL(TUid aViewId, 
	                                 TUid aCustomMessageId,
	                                 const TDesC8& aCustomMessage);
	
	/**
    * Gets a pointer to specified application view.
    * @param aView ID of the application view.
    * @return Pointer to application view object, 
    * NULL if aView doesn't exists.
    */
	IMPORT_C CAknView* View(TUid aView) const;
	
	/**
    * Registers and adds the view to the app UI. 
    * This function calls @c CCoeAppUi::RegisterViewL.
    * @param aView The view to be registered and added.
    */
	IMPORT_C void AddViewL(CAknView* aView);	// takes ownership of aView

	/**
    * Removes and deregisteres the view from the app UI. 
    * This function calls @c CCoeAppUi::DeregisterView.
    * @param aViewId The view to be deregistered and removed.
    */
	IMPORT_C void RemoveView(TUid aViewId);
    
    /**
    * Processes user commands.
    * @param aCommand A command ID.
    */
	IMPORT_C void ProcessCommandL(TInt aCommand);
	
	/**
    * Stops displaying the application’s menu bar.
    */
	IMPORT_C void StopDisplayingMenuBar();

	// Avkon view architecture system. Internal use only.
	void ViewActivatedL(CAknView* aView, 
	                    const TVwsViewId& aPrevViewId,
	                    TUid aCustomMessageId,
	                    const TDesC8& aCustomMessage);
	
	void ViewDeactivated(CAknView* aView);

    /**
    * Combines two views. If either of the views belongs to another view combination
    * then that combination is removed.
    * @since Series 60 5.0
    * @param aView1Id UID of the first (leftmost) view.
    * @param aView2Id UID of the second view.
    * @param aLeftViewSize Size of the first view (in percentages).
    */
    IMPORT_C void SetSplitViewL( const TUid aView1Id, const TUid aView2Id, const TInt aLeftViewSize );

    /**
    * Removes a view combination containing the given view UID. If the view
    * with the given UID is currently visible then the screen is switched to
    * single view and the the given view stays active.
    * @since Series 60 5.0
    * @param aViewId UID of a view combination.
    */
    IMPORT_C void RemoveSplitViewL( const TUid aViewId );
    	
    /**
    * Checks if split view is in use.
    * @since Series 60 5.0
    * @return ETrue if a split view is active.
    */
    IMPORT_C TBool SplitViewActive() const;
    	
    /**
    * Returns the currently focused view.
    * @since Series 60 5.0
    * @return UID of the currently focused view.
    */
    IMPORT_C TUid FocusedView() const;
    	
    /**
    * Checks if the given view is visible on the screen.
    * @since Series 60 5.0
    * @param aViewId View to be checked.
    * @return ETrue if the given view is visible.	
    */
    IMPORT_C TBool ViewShown( const TUid aViewId ) const;
    
    /**
    * Enables/disables local screen clearer.
    * Local screen clearer is used in the view based applications
    * to clear the application window if/when the view itself fails
    * to do this. By default, the clearer is used.
    * This function must be called before the BaseConstructL() to
    * prevent the screen clearer on application start up.
    *
    * @since 3.2 
    * @param aEnable ETrue enables local screen clearer.
    *                EFalse disables local screen clearer.
    */
    IMPORT_C void EnableLocalScreenClearer( TBool aEnable = ETrue );
    	
    /**
    * Returns view's rectangle.
    * @since Series 60 5.0
    * @param aViewId UID of the view whose rectangle should be returned.
    * @param Given view's drawing area.
    */
    TRect ViewRect( const TUid aViewId ) const;
    	
    /**
    * Handles keyboard initiated navigation between visible split views.
    * @since Series 60 5.0
    * @param aKeyEvent Keyboard event.
    * @param EKeyWasConsumed if view focus was changed.
    */
    TKeyResponse HandleViewNavigationL( const TKeyEvent& aKeyEvent );
    	
protected:
	
	/**
    * From @c MEikStatusPaneObserver. Handles a change in the position or
    * size of the screen area occupied by the status pane.
    */
	IMPORT_C void HandleStatusPaneSizeChange();

	/**
    * From @c CCoeAppUi. Handles changes in keyboard focus when
    * an application switches to foreground.
    * @param aForeground @c ETrue if the application is in the foreground,
    * otherwise @c EFalse.
    */
	IMPORT_C void HandleForegroundEventL(TBool aForeground);

    /**
    * From AknAppUi. Handles pointer-initiated view switch. Currently this
    * function does nothing but calls base class function.
    * @since Series 60 3.0
    * @param aEvent Window server event.
    * @param aDestination Pointer to the control which the event is targeted to.
    */
    IMPORT_C void HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination );
    	
private:
	static TInt ActivationCallBack(TAny* aThis);
	void ActivationTick();
	void QueueActivationTick();

    /**
    * Asserts that extension object has been created.
    * @return Extension object.
    */
    CAknViewAppUiExtension* Extension() const;

    /**
    * Activates views in split view.
    * @since Series 60 5.0
    * @param View under activation.
    */
    void ActivateSplitViewL( CViewActivationItem* aItem );
    	
    /**
    * If the given view is part of a split view then returns that split view,
    * @since Series 60 5.0
    * @param aViewId UID of a view that belongs to a split view.
    * @return Pointer to a correct split view or NULL if no corresponding split view was found.
    */
    TAknSplitViewContainer* SplitView( const TUid aViewId ) const;
    	
protected:
	
    // Application view.
    CAknView* iView;
	
    // Application views.
    CAknViews* iViews;

private:
    CAknViewShutter* iShutter;
    CAknLocalScreenClearer* iClearer;
    CAknViewActivationQueue* iActivationQueue;
    CIdle* iActivationTick;
    // extension class
    CAknViewAppUiExtension* iExtension;
    };

#endif // __AKNVIEWAPPUI_H__
