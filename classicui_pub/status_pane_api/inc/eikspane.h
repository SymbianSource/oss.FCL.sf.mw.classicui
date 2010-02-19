/*
* Copyright (c) 2002-2010 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  EIKON Status Pane control.
*
*/


#ifndef __EIKSPANE_H__
#define __EIKSPANE_H__

#include <eikspmod.h>
#include <coecntrl.h>
#include <coecobs.h>

class CCoeBrushAndPenContext;
class CEikStatusPaneContainer;
class CEikStatusPaneBaseExtension;
class CAknStatuspaneClearer;
class CAknDelayedForegroundObserver;
class CAknStatusPaneDataSubscriber;
class TAknsItemID;

/**
* Status pane flag indicating that a sub-pane exists
* in the status pane.
*/
const TInt KStatusPaneCapsPresentBit         = 1;

/**
* Status pane flag indicating that a sub-pane is owned
* by the application side status pane.
*/
const TInt KStatusPaneCapsAppOwnedBit        = 2;

/**
* Status pane flag indicating that a sub-pane is part of
* a specific status pane layout.
*/
const TInt KStatusPaneCapsInCurrentLayoutBit = 4;

/**
 * The @c MEikStatusPaneObserver interface allows a status pane observer to
 * pick up changes in the size or position of the status pane. Such events
 * will be as a result of layout changes which cause an actual change in the
 * status pane rectangle.
 */
class MEikStatusPaneObserver
	{
public:
	virtual void HandleStatusPaneSizeChange() = 0;
	};

/**
 * The base class for status panes.
 */
class CEikStatusPaneBase : public CBase
	{
	
public:

    /**
     * Describes the capabilities of a subpane.
     */
    class TPaneCapabilities
        {

    public:
        
        /**
        * Constructor.
        */
        TPaneCapabilities();
        
        /**
        * Tests whether the subpane exists in the status pane.
        * 
        * @return @c ETrue if the subpane exists and can be used by the
        *            application, even if the subpane is not visible.
        */
        inline TBool IsPresent() const;
        
        /**
        * Tests whether the pane is owned by the application or the server.
        * Applications can only interact directly with application owned
        * subpanes.
        *
        * @return @c ETrue if the subpane is owned by the application.
        */
        inline TBool IsAppOwned() const;
        
        /**
        * Tests if this pane is part of the current status pane layout.
        *
        * @return @c ETrue if pane is part of the current status pane layout.
        */
        inline TBool IsInCurrentLayout() const;

    private:

        inline void SetPresent();
        inline void SetAppOwned();
        inline void SetInCurrentLayout();

    private:

        TInt iFlags;

    private:

        friend class CEikStatusPaneBase;
        };

public:

    /**
    * Destructor.
    */
    IMPORT_C ~CEikStatusPaneBase();

    /**
    * Gets a pointer to the thread's currently active status pane
    * without transferring ownership. 
    *
    * @return Pointer to currently active status pane.
    *         Returns @c NULL if no such pane exists.
    */
    IMPORT_C static CEikStatusPaneBase* Current();
	
    /**
    * Sets the status pane observer.
    *
    * @param  aObserver  Pointer to status pane observer.
    */
    inline void SetObserver( MEikStatusPaneObserver* aObserver );
	
    /**
    * Modifies the bounding rectangle so that it lies next to the
    * status pane rectangle.
    *
    * The status pane always places itself along the edge of the screen, so 
    * that it is consistent across applications and the server. It is 
    * assumed that the given bounding rectangle does not extend beyond 
    * the screen area.
    *
    * @param[in,out]  aBoundingRect  The bounding rectangle.
    */
    IMPORT_C void ReduceRect( TRect& aBoundingRect ) const;
	
    /**
    * Adds and removes pane rectangles from @c aRegion.
    *
    * @param  aRegion              The two-dimensional area from where
    *                              rectangles are removed from or where
    *                              rectangles are added to.
    * @param  aIncludeAppPanes     If @c ETrue, app panes are added, otherwise
    *                              removed.
    * @param  aIncludeServerPanes  If @c ETrue, server panes are added, 
    *                              otherwise removed.
    */
    IMPORT_C void GetShapeL( TRegion& aRegion, 
                             TBool aIncludeAppPanes, 
                             TBool aIncludeServerPanes ) const;

    /**
    * Switches to the specified status pane layout.
    *
    * The actual layout to which this method switches may not be the
    * same as specified in @c aLayoutResourceId parameter.
    * Eg. if landscape mode status pane layout is set with this method,
    * while in portrait mode, it's mapped to the corresponding layout
    * in the portrait mode. This should be noted when using
    * @c CEikStatusPaneBase::CurrentLayoutResId().
    *
    * From release 3.2 on the old status pane layouts are also mapped
    * to the new layouts, ie.
    *  @c R_AVKON_STATUS_PANE_LAYOUT_USUAL ->
    *      @c R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT
    *
    *  @c R_AVKON_STATUS_PANE_LAYOUT_IDLE  ->
    *      @c R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT
    *
    * @param aLayoutResourceId Layout resource ID. This must be one of the
    *                          layouts identified in the status pane
    *                          resource structures, otherwise the function
    *                          leaves @c KErrNotFound.
    *                          @see avkon.rsg
    *
    * @leave KErrNotFound      The specified layout does not exist in the
    *                          status pane resource structures.
    */
    IMPORT_C virtual void SwitchLayoutL( TInt aLayoutResourceId );
	
    /**
    * Sets the visibility of the status pane and it's contents.
    *
    * @param  aVisible  If @c ETrue the status pane and it's contents are set
    *                   visible.
    */
    IMPORT_C virtual void MakeVisible( TBool aVisible );
	
    /**
    * Sets the status pane and it's contents to dimmed state.
    *
    * @param  aDimmed  If @c ETrue the status pane and it's contents are
    *                  set to dimmed state.
    */
    IMPORT_C virtual void SetDimmed( TBool aDimmed );
	
    /**
    * Not implemented.
    *
    * @param aFaded Not used.
    */
    IMPORT_C virtual void SetFaded( TBool aFaded );
	
    /**
    * Handles changes in resources which are shared across the environment.
    * This function responds to the changes in resources by propagating them
    * to sub-parts of the status pane.
    *
    * @param  aType  A message type.
    */
    IMPORT_C virtual void HandleResourceChange( TInt aType );
	
    /**
    * Returns always @c ETrue. 
    *
    * @return @c ETrue.
    */
    IMPORT_C virtual TBool OkToChangeStatusPaneNow();

    /**
    * Sets all the visual flags at once
    * (@c KEikStatusPaneBaseVisibleBit and
    *  @c KEikStatusPaneBaseDimmedBit).
    * 
    * @param  aFlags  Flags to be set.
    */
    IMPORT_C void SetFlags( TInt aFlags );
	
    /**
    * Gets status pane settings.
    *
    * @return Flags used by status pane base class.
    */
    IMPORT_C TInt Flags() const;
	
    /**
    * Gets the visibility of the status pane.
    * 
    * @return @c ETrue if the status pane is visible.
    */
    IMPORT_C TBool IsVisible() const;
	
    /**
    * Gets the dimmed state of the status pane.
    * 
    * @return @c ETrue if the status pane is dimmed.
    */
    IMPORT_C TBool IsDimmed() const;
	
    /**
    * Gets the fade status of the status pane.
    * 
    * @return @c ETrue if status pane is faded.
    */
    IMPORT_C TBool IsFaded() const;

    /**
    * Gets the capabilities of a sub-pane in the status pane.
    * 
    * @param   aPaneId  Sub-pane ID.
    *
    * @return Capabilities of the pane.
    */
    IMPORT_C TPaneCapabilities PaneCapabilities( TPaneId aPaneId ) const;
	
    /**
    * Provides the screen rectangle of a sub-pane.
    * This can be used to set the size of a new control which you want
    * to place in the status pane.
    * 
    * @param   aPaneId  Sub-pane ID.
    *
    * @return The sub-pane rectangle.
    *
    * @leave  KErrNotFound The sub-pane ID is not valid.
    */
    IMPORT_C TRect PaneRectL( TPaneId aPaneId ) const;
	
    /**
    * Provides the control currently inside a sub-pane.
    * This gives the application direct access to the contents of a pane.
    *
    * @param   aPaneId  Sub-pane ID.
    *
    * @return Pointer to the control instance inside the sub-pane.
    *
    * @leave  KErrNotFound The sub-pane ID is not valid.
    */
    IMPORT_C CCoeControl* ControlL( TPaneId aPaneId ) const;
	
    /**
    * Swaps the control currently inside a sub-pane.
    * The new control must be a fully constructed control.
    * It will be placed inside the status pane, and the current
    * content will be returned to the caller. 
    * 
    * @param  aPaneId      ID of the sub-pane.
    * @param  aNewControl  A fully constructed control to
    *                      place at @c aPaneId.
    *
    * @return The control  which was at @c aPaneId.
    *
    * @leave  KErrNotFound This can occur before ownership of the new
    *                      control is taken, if the subpane ID is not valid.
    */
    IMPORT_C CCoeControl* SwapControlL( TPaneId aPaneId,
                                        CCoeControl* aNewControl );
	
    /**
    * Provides access to the container control of a sub-pane.
    * You will need access to the container of a sub pane if you want 
    * to swap in a new control. The container control should be set as the
    * parent window of the new control.
    * It also provides a fast way to get the rectangle of the sub-pane 
    * (@see PaneRect()).
    *
    * @param   aPaneId  ID of the sub-pane.
    *
    * @return Pointer to the new container control for the sub-pane.
    *
    * @leave  KErrNotFound The sub-pane ID is not valid.
    */
    IMPORT_C CCoeControl* ContainerControlL( TPaneId aPaneId ) const;
	
    /**
    * Provides access to a server-side window group.
    *
    * @return Pointer to the window group.
    */
    inline RWindowGroup* WindowGroup() const;
	
    /**
    * Draws the control.
    */
    IMPORT_C void DrawNow();
	
    /**
    * Gets the resource ID of the current layout.
    *
    * @return The resource ID of the current layout.
    *         @see avkon.rsg
    */
    IMPORT_C TInt CurrentLayoutResId() const;
    
    /**
    * Status pane drawing commands.
    */
    enum TDrawCmd 
        { 
        /** Do not draw. */
        ENoDraw, 

        /** Draw immediately. */
        EDrawNow, 
        
        /** Draw with low priority. */
        EDrawDeferred 
        };

    /**
    * Sets the skin background ID of sub-panes which
    * are in the CBA area.
    * @internal This method is not exported.
    *
    * @param  aBgID     The skin background ID to be set.
    * @param  aDrawCmd  Whether the status pane is drawn
    *                   when updating the background context,
    *                   (@see @c TDrawCmd).
    */
    void SetCbaAreaBackgroundID( const TAknsItemID& aBgID,
                                 CEikStatusPaneBase::TDrawCmd aDrawCmd );
    
    /**
    * Returns the current skin background ID of the sub-panes
    * which are in the CBA area.
    * @internal This method is not exported.
    *
    * @return  The skin background ID.
    */
    TAknsItemID CbaAreaBackgroundID();

protected:

    /**
    * C++ default constructor.
    *
    * @param  aEikEnv  An environment for creating controls and utility 
    *                  functions for manipulating them.
    * @param  aParent  Pointer to the parent window group.
    */
    IMPORT_C CEikStatusPaneBase( CEikonEnv& aEikEnv, RWindowGroup* aParent );
	
    /**
    * Initializes the status pane with standard values. 
    * 
    * @param  aCoreResId  ID of the status pane resource.
    */
    IMPORT_C void BaseConstructL( TInt aCoreResId );

    /**
    * Creates a new model for the status pane.
    *
    * @param  aCoreResId  ID of the status pane resource.
    *
    * @return Pointer to the new status pane model instance.
    */
    virtual CEikStatusPaneModelBase* CreateModelL( TInt aCoreResId ) const = 0;
	
    /**
    * Creates the sub-panes to the status pane.
    */
    void CreatePanesL();
	
    /**
    * Creates a sub-pane.
    *
    * @param[in]  aPaneInit  Initial values for the sub-pane.
    */
    void CreatePaneL( const TEikStatusPaneInit& aPaneInit );
	
    /**
    * Gets a container of a specified sub-pane.
    *
    * @param  aPaneId  The sub-pane ID.
    *
    * @return Pointer to the container of the sub-pane with a given ID.
    */
    CEikStatusPaneContainer* Find( TPaneId aPaneId ) const;

    /**
    * Can be used to determine whether or not the status pane is on
    * application side or server side.
    *
    * @return @c ETrue if the status pane resides in the application side,
    *         @c EFalse if it's on the server side.
    */
    virtual TBool IsApp() const = 0;
	
    /**
    * Gets the rectangle of the status pane.
    *
    * @return The rectangle used by the status pane.
    */
    inline TRect Rect() const;
	
    /**
    * Calls @c CCoeControl's @c DrawNow() or @c DrawDeferred() to draw the 
    * status pane. If @c aDraw is @c ENoDraw status pane is not drawed.
    * 
    * @param  aDraw  Status pane drawing command.
    */
    void DoDrawNow( TDrawCmd aDraw );
	
    /**
    * Gets the status pane clearer.
    *
    * @return Pointer to the status pane clearer instance.
    */
    CAknStatuspaneClearer* Clearer();
	
    /**
    * Disables the status pane clearer. 
    *
    * @param  aDisabled  Disabled if @c ETrue.
    */
    IMPORT_C void DisableClearer( TBool aDisabled );
	
    /**
    * Prepares the status pane for the application exit.
    * Clears the status pane.
    */
    IMPORT_C void CommonPrepareForAppExit();

private:

    void DoSwitchLayoutL( TInt aLayoutResourceId, TDrawCmd aDraw );
    void ApplyLayoutL( CEikStatusPaneLayout* aLayout, TDrawCmd aDraw );
    void SetAllInvisible();
    void SetNotNeededInvisible();

public:
    
    /**
    * Notifies the command button area and status pane observer about the
    * status pane size change. If the status pane is an embedded application,
    * also this application is notified.
    */
    void ReportSizeChange();

private:

    class TSetRectAndVisibility : public MEikStatusPaneLayoutTreeVisitor
        {    
    public:
    
        TSetRectAndVisibility( TBool aIsApp, CEikStatusPaneBase* aStatusPane );
        void VisitL( CEikStatusPaneLayoutTree* aNode );
    
    private:
    
        TBool iIsApp;
        CEikStatusPaneBase* iStatusPane;
        };
	
	friend class TSetRectAndVisibility;

private:

    void  SetLastUsedResourceId( TInt aResourceId );
    TInt  LastUsedResourceId();
    TInt  ReadInitialUsedResourceIdL( TInt aCoreResId );    
    TInt  InitialUsedResourceId();
    TRect LargestBoundingRect( TRegion& aWholeRegion,
                               TRegion& aRemovedRegion ) const;
    void SetCombinedPaneVisibilityL( TBool aVisible );

protected:

    /**
    * Gets the status pane data subscriber.
    *
    * @return Pointer to the status pane data subscriber.
    */
	CAknStatusPaneDataSubscriber* DataSubscriber() const;

    /**
    * Sets the initial status pane resource ID to an extension class 
    * @c CEikStatusPaneBaseExtension.
    *
    * @param  aResourceId  The initial status pane resource ID.
    */
    void SetInitialUsedResourceId( TInt aResourceId );
    
    /**
    * Optimizes the status pane region which cleared during
    * status pane layout change.
    *
    * @param         aOldResourceId  Old status pane resource ID.
    * @param         aNewResourceId  New status pane resource ID.
    * @param[in,out] aRegion         Status pane region.
    *                                On return contains only
    *                                the region that needs to be cleared.
    */
	void OptimizeClearerWindowShape( TInt aOldResourceId,
	                                 TInt aNewResourceId,
	                                 TRegion& aRegion );

	/**
	* Sets redraw storing state of the window.
	*
	* @param  aWindow  The window whose redraw storing state is to be set.
	* @param  aOn      @c ETrue to turn redraw storing on.
	*/	
	void SetStoreHandler( RWindow* aWindow, TBool aOn );

protected:

    /**
    * An environment for creating controls and utility functions for 
    * manipulating them.
    */
    CEikonEnv& iEikEnv;
	
    /**
    * Status pane model class. <br>
    * Own.
    */
    CEikStatusPaneModelBase* iModel;

    /**
    * Flags for the status pane.
    */
    TInt iFlags;

protected:

	typedef CArrayPtrFlat<CEikStatusPaneContainer> CContainerControls;
	CContainerControls* iControls;
	
private:

	MEikStatusPaneObserver* iObserver;
	RWindowGroup* iParentWindowGroup;
	CEikStatusPaneBaseExtension* iExtension;
	};

/**
 * Application side status pane class.
 *
 * @c CEikStatusPane is the interface through which applications use the
 * status pane. This class synchronises the status pane layout with the
 * server side status pane object. To do this, the @c ApplyCurrentSettingsL()
 * method must be called whenever the owner application switches to the
 * foreground.
 */
NONSHARABLE_CLASS( CEikStatusPane ) : public CEikStatusPaneBase,
                                      public MCoeForegroundObserver
	{
public:

    /**
    * Two-phased constructor.
    *
    * @param  aEikEnv                    An environment for creating controls
    *                                    and utility functions for
    *                                    manipulating them.
    * @param  aParent                    Pointer to the parent window group.
    * @param  aCoreStatusPaneModelResId  Status pane core resource ID.
    * @param  aAppStatusPaneModelResId   Resource ID of the application's
    *                                    status pane.
    *
    * @return Pointer to the created @c CEikStatusPane object.
    */
	IMPORT_C static CEikStatusPane* NewL(
        CEikonEnv& aEikEnv,
        RWindowGroup* aParent,
        TInt aCoreStatusPaneModelResId,
        TInt aAppStatusPaneModelResId = EEikStatusPaneUseDefaults );

    /**
    * Destructor.
    */
	IMPORT_C ~CEikStatusPane();
    
    /**
    * Synchronises the server status pane layout with the
    * application status pane.
    */
	IMPORT_C void ApplyCurrentSettingsL();
	
	/**
    * Prepares the status pane for the application exit.
    * Clears the status pane.
    */
	IMPORT_C void PrepareForAppExit();

	/**
    * Sets the visiblility of the status pane and its contents.
    * From @c CEikStatusPaneBase.
    *
    * @param aVisible If @c ETrue the status pane and its
    *                 contents are set visible.
    */
	IMPORT_C virtual void MakeVisible( TBool aVisible );
	
	/**
    * Sets the status pane and its contents to dimmed state.
    * From @c CEikStatusPaneBase.
    *
    * @param aDimmed If @c ETrue the status pane and its
    *                contents are set to dimmed state.
    */
	IMPORT_C virtual void SetDimmed( TBool aDimmed );
	
	/**
    * Not implemented.
    * From @c CEikStatusPaneBase.
    *
    * @param aFaded Not used.
    */
	IMPORT_C virtual void SetFaded( TBool aFaded );
	
	/**
    * Handles changes in resources which are shared across the environment.
    * This function responds to the changes in resources by propagating them
    * to sub-parts of the status pane.
    * From @c CEikStatusPaneBase.
    *
    * @param  aType  A message type.
    */
	IMPORT_C virtual void HandleResourceChange( TInt aType );
	
	/**
    * Returns always @c ETrue. 
    * From @c CEikStatusPaneBase.
    *
    * @return @c ETrue.
    */
	IMPORT_C virtual TBool OkToChangeStatusPaneNow();

private:

    /**
    * Default C++ constructor.
    *
    * @param  aEikEnv                    An environment for creating controls
    *                                    and utility functions for
    *                                    manipulating them.
    * @param  aParent                    Pointer to the parent window group.
    * @param  aAppStatusPaneModelResId   Resource ID of the application's
    *                                    status pane.
    */
	CEikStatusPane( CEikonEnv& aEikEnv,
	                RWindowGroup* aParent,
	                TInt aAppStatusPaneModelId );

    /**
    * Second-phase constructor.
    *
    * @param  aCoreStatusPaneModelResId  Status pane core resource ID.
    */
	void ConstructL( TInt aCoreStatusPaneModelResId );

    /**
    * Creates the application side status pane model.
    *
    * @param  aCoreResId  Status pane core resource ID.
    */
	virtual CEikStatusPaneModelBase* CreateModelL( TInt aCoreResId ) const;
	
	/**
    * Can be used to determine whether or not the status pane is on
    * application side or server side.
    *
    * @return @c ETrue
    */
	TBool IsApp() const;

    /**
    * Applies the current status pane flags.
    */
	void ApplyCurrentFlags();
	
	/**
	* Hides all the sub-panes owned by the application
	* side status pane.
	*/
	void HideAppPanes( TBool aHide );

private: // From base class @c MCoeForegroundObserver.

    /**
    * Handles foreground gain events.
    */
	void HandleGainingForeground();
	
	/**
    * Handles foreground lose events.
    */
	void HandleLosingForeground();
	
private:
	
	/**
    * Reads the initial status pane layout from the status pane resources.
    *
    * @param  aCoreResId                Status pane core resource ID.
    * @param  aAppStatusPaneModelResId  Resource ID specified by the
    *                                   application.
    */
    TInt ReadInitialUsedResourceIdL( TInt aCoreResId,
                                     TInt aAppStatusPaneModelResId );

    /**
    * Handles foreground lose events.
    */
    void DoHandleLosingForegroundL();

private:

	TInt iAppDeclId;
	
	/** Formerly TEikStatusPaneSyncDrawer* iSyncDrawer */
	TAny* iSpare;
	
	/** Formerly iServerSpWgId */
	CAknDelayedForegroundObserver* iDelayedForegroundObserver;
	};

/**
* Checks if the pane exists in this status pane.
* Note: this will return @c ETrue if the pane can be used,
* even if it is not visible.
*/
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsPresent() const
    {
    return iFlags & KStatusPaneCapsPresentBit;
    }
    
/**
* Checks if this pane is owned by application rather than the server.
* Applications can only interact directly with application owned panes.
*/
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsAppOwned() const
    {
    return iFlags & KStatusPaneCapsAppOwnedBit;
    }
    
/**
* Checks if this pane is part of the current status pane layout.
*/
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsInCurrentLayout() const
    {
    return iFlags & KStatusPaneCapsInCurrentLayoutBit;
    }

/**
* Set the status pane observer.
*/
inline void CEikStatusPaneBase::SetObserver( MEikStatusPaneObserver* aObserver )
    {
    iObserver = aObserver;
    }

/**
* Gets the status pane rectangle.
*/
inline TRect CEikStatusPaneBase::Rect() const
    {
    return iModel->CurrentLayout()->Rect();
    }

/**
* Gets the window group that this status pane belongs to.
*/
inline RWindowGroup* CEikStatusPaneBase::WindowGroup() const
    {
    return iParentWindowGroup;
    }

#endif // __EIKSPANE_H__
