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
*
*/

#if !defined(__AVKON_ENV_H__)
#define __AVKON_ENV_H__

//  INCLUDES
#include <eikenv.h>
#include <eiksbfrm.h>
#include <eikcba.h>
#include <eikmobs.h>
#include <eikmenub.h>
#include <eikappui.h>
#include <AknLayout2Id.h> // for TAknLayoutId
#include <AknDef.h> // for TAknUiZoom

// FORWARD DECLARATIONS
namespace AknLayout { class CInstance; }
namespace LayoutPack { class CInstance; }

class CCdlEngineRef;
class MAknEditingStateIndicator;
class MAknIntermediateState;
class CAknAppUi;
class CAknWaitDialog;
class CEikListBox;
class CAknSettingCache;
class CAknFontRegistry;
class CLafSystemFont;
class TAknLayoutConfigScreenMode;
class CCdlRefs;
class CTransitionManager;
class CAknCommandMediator;
// Since there is no include of aknsystemfont.h we need the typedef CLafSystemFont here as well
// Hence this requires parallel maintenance.
typedef CLafSystemFont CAknSystemFont;

// MACROS
// Color Macros
/** Color indirection macros
 *
 * This macro takes number from LAF specification and converts it to TRgb for
 * use to draw things.
 */

// Color macros 
#define AKN_LAF_COLOR_ENV(env,nn)	CAknEnv::AvkonColor(nn)
#define AKN_LAF_COLOR(nn)			CAknEnv::AvkonColor(nn)
#define AKN_LAF_COLOR_STATIC(nn)	CAknEnv::AvkonColor(nn)

	// Avkon layout
//	IMPORT_C const AknLayout::CInstance& AknLayout() const;


// CLASS DECLARATION

/**
*  This class is a Series 60 extension to @c CEikonEnv. 
*  Every Avkon application is provided with an instance of @c CAvkEnv by the
*  framework, which can be accessed through the @c iAvkonEnv macro.
* 
*  @since Series 60 0.9
*/
class CAknEnv : public CBase
	{
public:
    /**
    * Gets the @c CAknEnv maintained by the framework for the application.
    * Compare @c CCoeEnv::Static().
	*
	* This function should never be run in a thread where such a static Avkon
	* environment does not exist. Code that may run on the server side of an
	* application server is one such case.
    * @return A static @c CAknEnv.
    */
	IMPORT_C static CAknEnv* Static();

    /**
    * Destructor.
    */
	IMPORT_C ~CAknEnv();
public:
	// this one creates an empty dialog. for list queries and popup lists with 
	// "No Data" in it.
	/**
    * Executes empty popup list.
	*
    * @param aEmptyText Text indicating empty popup list. NULL if 
    * @c R_AVKON_EMPTY_POPUP_LIST_TEXT used.
	*/

	IMPORT_C void ExecuteEmptyPopupListL(const TDesC *aEmptyText=0);

    /**
    * Executes empty popup list.
	* @c aSoftkeyId is soft key rescource used, but shown without left soft
	* key (except @c R_AVKON_SOFTKEYS_OK_EMPTY).
	*
    * @param aEmptyText Text indicating empty popup list. NULL if
    * @c R_AVKON_EMPTY_POPUP_LIST_TEXT used.
	* @param aTitle A title of the popup list.
	* @param aSoftKeyId CBA resource to be used as a base. 0 if
	* @c R_AVKON_SOFTKEYS_CANCEL is used. 
    */
	IMPORT_C void ExecuteEmptyPopupListL(const TDesC *aEmptyText, 
	                                     const TDesC *aTitle, 
	                                     TInt aSoftkeyId=0);

public:
    /**
    * Set the FEP menu observer.
	*
    * @param aObserver the FEP menu observer.
    */
	IMPORT_C void SetFepMenuObserver(MEikMenuObserver* aObserver);

    /**
    * Get the FEP menu observer.
	*
    * @return Pointer to the FEP menu observer.
    */
	IMPORT_C MEikMenuObserver* FepMenuObserver();

    /**
    * Get the editing state indicator.
	*
    * @return Pointer to the editing state indicator.
    */
	IMPORT_C MAknEditingStateIndicator* EditingStateIndicator();


    /**
    * Swap the editing state indicator.
	*
    * @param aIndicator The new editing state indicator.
	* @return The old editing state indicator.
    */
	IMPORT_C MAknEditingStateIndicator* SwapEditingStateIndicator(
	    MAknEditingStateIndicator* aIndicator);

    /**
    * Exit foreground application.
    */
	IMPORT_C static void ExitForegroundAppL();

public: // Intermediate states support
    /**
    * Register the control implementing intermediate states.
	* Call @c iAvkonEnv->RegisterIntermediateState(this) in control's
	* @c ActivateL().
	*
    * @param aState The control implementing intermediate states.
    */
	IMPORT_C void RegisterIntermediateStateL(MAknIntermediateState *aState);

    /**
    * Unregister the control implementing intermediate states.
	* Call @c iAvkonEnv->UnRegisterIntermediateState(this) in control's 
	* destructor.
	*
    * @param aState The control implementing intermediate states.
    */
	IMPORT_C void UnRegisterIntermediateState(MAknIntermediateState *aState);

    /**
    * Closes all intermediate states as a low-priority process. 
    */
	IMPORT_C void CloseAllIntermediateStates();

public:
    /**
    * Run application shutter.
    */
	IMPORT_C static void RunAppShutter();

    /**
    * Get pointer to the most embedded application UI with Dialog Shutter 
    * running.
	*
    * @return Pointer to the most embedded application UI with Dialog Shutter
    * running. @c NULL if no any Dialog Shutter running.
    */
	IMPORT_C static CAknAppUi* AppWithShutterRunning();

    /**
	* Stop the scheduler. If the waiting control can't stop the scheduler
	* immediately, then trying to show a busy note.
	* @param aWait Scheduler object to be stopped.
	*/
	IMPORT_C static void StopSchedulerWaitWithBusyMessage(
	    CActiveSchedulerWait& aWait);

public:
    /**
	* Create CBA observer. The possible existing one is removed first.
	* @param aCba A control which @c ProcessCommandL handles the command.
	* @param aListBox Stored to data member @c iListBox.
	*/
	IMPORT_C void CreateCbaObserverL(CEikButtonGroupContainer *aCba, 
	                                 CEikListBox *aListBox);

    /**
	* Remove CBA observer.
	*/
	IMPORT_C void RemoveCbaObserver();


    /**
	* Remove CBA observer if the right one.
	* @param aCba CBA to be checked.
	*/
	IMPORT_C void InformCbaDeletion(CEikButtonGroupContainer *aCba);

    /**
     * Requests mediation of MSK commmands from specified CBA to the
     * given observer. When called for the first time, this method creates
     * an observer that is added to specified CBA to observe MSK commands
     * and to mediate all received events to the given observer. The created
     * observer exists until the CAknEnv instance is destroyed. All subsequent
     * calls to this method replace the previously requested mediation.
     *
     * @param aCba CBA whose MSK is to be observed.
     * @param aCommandObserver An observer for which the commands are sent.
     */
    IMPORT_C void RequestCommandMediationL( CEikButtonGroupContainer& aCba,
        MEikCommandObserver& aCommandObserver );

    /**
     * Ends mediating MSK commands to specified command observer. If commands
     * are being mediated to the specifed observer, the command mediator is
     * removed from the CBA to end mediation.
     *
     * @param aCommandObserver An observer.
     */
    IMPORT_C void EndCommandMediation( MEikCommandObserver& aCommandObserver );

public:
    /**
	* Get current layout ID.
	* @since Series 60 2.0
	* @param aCurrentLayoutId On return, contains current layout ID.
	*/
	IMPORT_C void GetCurrentLayoutId(TAknLayoutId& aCurrentLayoutId) const;

    /**
    * Get current global zoom
    * @since 3.1
    * @param aCurrentGlobalUiZoom On return, contains current global zoom.
    */
    IMPORT_C void GetCurrentGlobalUiZoom(TAknUiZoom& aCurrentGlobalUiZoom) const;

public:
    /**
    * Tells the type of status pane layout for UI.
    * @since Series 60 2.0
    * @param aResId resource id for current layout.
    * @return Resource id equivalent type of status pane layout.
    */
	IMPORT_C TInt StatusPaneResIdForCurrentLayout(TInt aResId) const;

public:
    /**
    * Requests Window Server client buffer used by the application to
    * be of at least the given size. All code that wants to increase
    * (to avoid flicker) or decrease (to save RAM) the buffer compared
    * to the default size should call this method instead of using
    * WS interface directly. A list of all requests is maintained
    * and the highest request is always effective. Only if there are no
    * requests done, the default buffer size is used.
    *
    * @since Series 60 2.0
    *
    * @param aRequestedBufferSize requested Window Server client buffer size.
    *
    * @return Request ID. This is used when the request is canceled.
    *         In OOM situation, @c KErrNoMemory is returned. 
    *         @c CancelWsBufferRequest ignores negative values as error codes
    *         so it is OK to pass any value returned by this method to
    *         @c CancelWsBufferRequest.
    */
    IMPORT_C TInt RequestWsBuffer( TInt aRequestedBufferSize );

    /**
    * Cancels a request made by call @c RequestWsBuffer. This should be
    * called in order to save RAM when higher than normal buffer size is
    * no longer required.
    *
    * @since Series 60 2.0
    *
    * @param aRequestID The request ID returned by the
    *        @c RequestWsBuffer call which is to be canceled.
    *        Negative values are treated as error codes and ignored.
    */
    IMPORT_C void CancelWsBufferRequest( TInt aRequestID );

public:
    /**
    * @internal to Series 60
    */
	IMPORT_C CAknSettingCache& SettingCache() const;

    /**
    * Access to the registry of CAknLayoutFont pointers. Used for runtime
    * checking of CFont pointers.
    * 
    * @internal to Series 60
    * @since Series 60 2.8
    * 
    * @return   Reference to the registry
    */
    CAknFontRegistry& FontRegistry() const;

    /**
    * Access to the system font array that is owned by CEikonEnv. The member accessed by this
    * is set during CEikonEnv construction and may be null during application startup.
    * 
    * @internal to Series 60
    * @since Series 60 2.8
    * 
    * @return   Pointer to the system font array
    */
    CArrayPtr<CAknSystemFont>* SystemFontArray() const;

    void UpdateSystemFontsL();
    
    static void ShutOrHideAppL();

public: // layout
    
    /**
    * Load an appropriate Avkon layout.
    * 
    * @since  Series 60 2.6
    * @return @c EFalse if the layout is already loaded.
    */
	IMPORT_C TBool LoadAknLayoutL();
    /**
    * Load an appropriate Avkon layout for a particular screen mode.
    * 
    * @since  Series 60 3.1
    * @param  aScreenMode The screen mode which the layout is required for
    * @return @c EFalse if the layout is already loaded.
    */
	IMPORT_C TBool LoadAknLayoutL(const TAknLayoutConfigScreenMode& aScreenMode);
	
    /**
    * Re-load the current Avkon layout, in case there are new layout instances present.
    * 
    * @since  Series 60 5.1
    */
	void ReloadAknLayoutL();
	
	// Avkon layout
	/**
    * Accessor method to layout. 
    *
    * @since  Series 60 2.6
    * @return Reference to the Layout.
    */
	IMPORT_C const AknLayout::CInstance& AknLayout() const;

public: // color support
	/**
    * Gets the TRgb value of the entry at the specified index in the colour 
    * lookup table.
    *
    * @since  Series 60 0.9
    * @param  The aIndex of the colour lookup table, integer between 0 and 255.
    * @return The TRgb value of the colour lookup table at the aIndex.
    */
    IMPORT_C static TRgb AvkonColor( TInt );

public: // split view support
    /**
    * Checks if split view is active.
	* @since Series 60 5.0
    * @return ETrue if split view is active.
    */
    IMPORT_C TBool SplitViewActive() const;

    /**
    * Sets split view flag.
	* @since Series 60 5.0
    * @param aSplitViewActive Etrue if split view is active.
    */
    void SplitViewActive( const TBool aSplitViewActive );

    void TransitionEvent(TInt aEvent, const TUid& aAppUid);
    void TransitionEvent(TInt aEvent);
    TBool HasBlank() const;

public: // future language
    /*
     * Check if the feature language is same.
     * @param aFeatureLanguage feature language (e.g. KFeatureIdJapanese)
     * @return ETrue if the arg is same as iFeatureLanguage.
     * @since 3.1
     */
    TBool IsFeatureLanguage(TInt aFeatureLanguage);

private:

    void SetWsBufferSize();
    void SetWsBufferSize( TInt aRequestedBufferSize );

    // Only these can use run info array, so it cannot get messed up
    // by simultaneous use.
    friend class AknBidiTextUtils;
    friend class TAknTextWrapper;

    /**
    * Returns run info array owned by AknEnv.
    *
    * @param aLength Length of the array is returned here.
    *
    * @return Run info array owned by AknEnv.
    */
    TBidirectionalState::TRunInfo* RunInfoArray( TInt& aLength ) const;

    /**
    * Tests how big run info array the given text requires and
    * tries to increase the size of the array if required.
    *
    * @param aLogicalText Text in logical order.
    *
    * @return KErrNone or KErrNoMemory.
    */
    TInt PrepareRunInfoArray( const TDesC& aLogicalText );

    /**
    * Tries to increase the size of the run info array if
    * it is currently smaller than given length.
    *
    * @param aLength Length of the new run info array to be allocated.
    *
    * @return KErrNone or KErrNoMemory.
    */
    TInt SetRequiredRunInfoArraySize( TInt aLength );

	void SetLayoutRequirementsL();
	void AssertLayoutLoaded();
	TBool TryLoadAknLayoutL(TAknLayoutId aId, const TAknLayoutConfigScreenMode& aScreenMode, TAknUiZoom aUiZoom);
	TBool LoadAknLayoutL(TAknLayoutId aId, const TAknLayoutConfigScreenMode& aScreenMode, TAknUiZoom aUiZoom);
    TAknUiZoom ResolveCurrentUiZoom();
    
    /**
    * Use the currently loaded layout to set the values of the font size array used by CCoeFontProvider. 
    */
    void SetConeFontSizeArrayL() const;

private:
	static TInt RealCloseIntermediateStates(TAny *aEnv);
	static TInt SchedulerStoppedCallBack(TAny* aWaitNote);
	void DoSchedulerStoppedCallBack();

private:
    friend class LafEnv;

    IMPORT_C static void InstallAknEnvAsExtensionL(CEikonEnv* aEnv);
    IMPORT_C CAknEnv();
    IMPORT_C void ConstructL();
    
public:
    /**
    * Return if Transparency is Enabled .
    *
    * @since 5.0
    *
    * @return if Transparency is Enabled.
    */
    IMPORT_C TBool TransparencyEnabled() const; 

private:
	MEikMenuObserver* iFepMenuObserver;
	MAknEditingStateIndicator* iEditStateIndicator;
private:
	CArrayPtr<MAknIntermediateState> *iStateArray;
	CArrayPtr<CBase> *iDeleteArray;
	CIdle *iIdle;
	CAknWaitDialog* iBusyMsgDialog;
	TInt iBusyMsgCount;
	MEikCommandObserver *iCbaCommandObserver;
    CAknSettingCache* iSettingCache;
    TBidirectionalState::TRunInfo* iRunInfoArray;
    TInt iRunInfoArrayLength;

    struct TWsBufferRequest
        {
        TInt iRequestID;
        TInt iRequestedSize;
        };

    RArray<TWsBufferRequest> iWsBufferRequestArray;
    TInt iRequestIdCounter;
    TInt iCurrentWsBufferRequest;

	// cache for layout parameters
	TAknLayoutId iLastLayoutId;
	TInt iLastScreenMode;
	TAknUiZoom iLastZoom;

	CEikonEnv* iCoeEnv;
    CAknFontRegistry* iFontRegistry;  // Owned register of CAknLayoutFont pointers
    CCdlEngineRef* iCdlEngRef;
    const AknLayout::CInstance* iLayout;	
    CArrayPtr<CAknSystemFont>* iSystemFontArray; // Not owned. System Font array is owned by CEikonEnv
    TBool iSplitViewActive;
    CTransitionManager* iTransitionManager;
    CAknCommandMediator* iCommandMediator;
    /*
     * Set the feature language Id
     * If device uses Japanese language variant, KFeatureIdJapanese is set.
     * @since 3.1
     */
    TInt iFeatureLanguage;
    };


#define iAvkonEnv (STATIC_CAST(CAknEnv*,iEikonEnv->Extension()))
#define AVKONENV (STATIC_CAST(CAknEnv*, CEikonEnv::Static()->Extension()))

#endif
