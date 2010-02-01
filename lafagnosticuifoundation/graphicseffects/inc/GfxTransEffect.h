// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __GFXTRANSEFFECT_H__
#define __GFXTRANSEFFECT_H__

#include <e32def.h> // IMPORT_C
#include <e32std.h> // T types
#include <vwsdef.h> // TVwsViewId

// forwards for standard Symbian classes used
class CCoeControl;

/**
MGfxTransEffectObserver
Observer class for watching for when a transition is finished.
 
@publishedPartner
@released
*/
class MGfxTransEffectObserver
	{
public:
	/**
	 Called when a transition is finished
	
	TransitionFinished will not be called if the transition fails. Depending on engine implementation 
	TransitionFinished might be called after or during the GfxTransEffect::End() call
	*/ 
	virtual void TransitionFinished(const CCoeControl* aControl, TUint aAction) = 0;
	};

/**
GfxTransEffect
 
A generic interface used by transition-enabled controls and implemented by the transition engine vendor
@publishedPartner
@released
*/
class GfxTransEffect
	{
public:
	//@{
	/**
	  Registration and Deregistration of transition-able controls
	 
	 The transition engine needs to associate internal data and state with the transition-able controls in the client thread.
	 Each control that is transition-able needs to register with the transition engine.  An ideal place to register is during
	 control construction.
	 
	 Registration associates a logical class of transitions with the control instance.  It allows the transition effects associated
	 with listbox events to be different from those associated with dialogs closing.  Standard UIDs shall be defined as required
	 to identify logical transitionable-control classes.
	 
	 If you register a simple view or control, the control represents the foreground and an implicit background is registered too if
	 required.
	 
	 If you register an N-Layered control, the component layers shall be implicitly registered.  Change to the layers (including the
	 adding, removing and reordering of layers) shall be detected by the @c GfxTransEffect::Begin() automagically.
	 
	 Controls that are not registered with the transition engine shall be ignored.  Specifically, the @c Begin() function shall
	 do nothing and the @c End() function shall invoke a @c CCoeControl::DrawNow()
	 
	 */
	 
	/**	
	  register the type of a view
	 
	 Associates a view with a logical type; example types might include DETAILVIEW etc.
	 
	 A transitionable view is not n-layered.  The transition engine may split it into two layers -
	 a background and a foreground - to allow effects (e.g. animation) to happen between the two.  Or
	 it may consider it a single, flat layer.
	 
	 Warning: Views that are not registered shall not have transitions associated with them
	 
	 @param aKey	a view
	 @param aView	the view-id to associate view
	 @param aType	the classification of the view; standard UIDs shall be reserved for base views, detail views etc
	 */
	IMPORT_C static void Register(const CCoeControl* aKey,const TVwsViewId &aView,TUid aType);	
		
	/**
	  register the type of a control
	 
	 Associates a control with a logical type; example types might include LISTBOX, MENUPAGE etc.
	 
	 A transitionable control probably contains an implicit zero layer - it's background.  This is gathered if the @c MCoeControlBackground is set
	 If the control is @c aNLayered, then each child is considered a separate layer (in strict order they are returned, last returned being topmost).
	 Otherwise, a single foreground layer is assumed.
	 
	 Warning: Controls that are not registered will not have any transition associated with them
	 
	 @param aKey		the address of the control used to coordinate the transitions
	 @param aType		the classification of the control; standard UIDs shall be reserved for listboxes, menupanes, tab groups, building blocks etc
	 @param aNLayered	does the control consist of more than two layers?
	 */
	IMPORT_C static void Register(const CCoeControl* aKey,TUid aType,TBool aNLayered = EFalse);
	
	/**
	  tests whether a control is registered or not
	 
	 This does not test if the control is a layer within a registered N-Layered control
	 
	 @param aKey		the address of the control used to coordinate the transitions
	 @return			ETrue if the control is registered, else EFalse
	 */
	IMPORT_C static TBool IsRegistered(const CCoeControl* aKey);
	 	
	/**
	  Deregister a control or view
	 
	 Controls might often register themselves during their construction.
	 This function provides the facility to undo that for the application programmer.
	 
	 Controls that are not registered shall not have transitions associated with them.
	 
	 Deregistration of a control currently under transition (between begin and end) will abort the transition.

	 @param aKey	the address of the control to be deregistered
	 */
	IMPORT_C static void Deregister(const CCoeControl* aKey);
	//@}

	//@{
	/**
	  Transition Hints
	 
	 Often the implementation of a transition-able control (or control that represents a layer within that control) shall be
	 able to hint things to the transition effects engine that assist the transition effects engine in dealing with that control
	 efficiently.
	 
	 Hints are just that: advice to the transition engine, which the transition engine may ignore if appropriate.
	 
	 Additional hints might be added in the future, or specific to a particular class of control.
	 */
	 
	/**
	  generic flags for @c SetHints()
	 
	 Implicit background layers have default flags of @c EStatic|EOpaque
	 
	 Foreground layers have default flags of @c EDynamic|ETransparent
	 
	 N-Layered controls have default flags of @c EDynamic|ETransparent - which is used to as the default for their child layers - 
	 even if they have an implicit background layer with default background layer flags.
	 */
	enum
		{
		EDynamic =		0x00000000, //< needs constant recalculating by the client
		EStatic =		0x00000001, //< unlikely to change (unless @c Invalidate() d) and therefore a good candidate for caching the contents of; opposite to @c EDynamic
		ETransparent =	0x00000000, //< needs to be drawn to a @c CBitmapContext that supports alpha
		EOpaque =		0x00000002, //< does not need alpha; opposite to @c ETransparent
		ENone = ~0 //< used if flags are retrieved for a control that is not registered
		};

	/**
	  sets the flags for a control
	 
	 If you @c SetHints on an N-Layered control, you shall be setting those same hints upon all component layers of that control;
	 this is probably not what you intend to do.

	 @param aControl	the address of the control to associate the flags with; it is either registered, or a layer of a registered N-Layered control
	 @param aFlags		the new flags
	 */
	IMPORT_C static void SetHints(const CCoeControl* aControl,TUint aFlags);
		
	/**
	  retrieves the flags for a control
	 
	 If you @c GetHints on an N-Layered control, you shall be retrieving the default settings for that control and it's layers.
	 If individual layers have had @c SetHints called explicitly, they may not have the same flags as their parent.
	 
	 @param aControl	the address of the control that the flags are associated with; it is either registered, or a layer of a registered N-Layered control
	 @return			@c ENone if the control is not registered, otherwise the flags
	 */
	IMPORT_C static TUint GetHints(const CCoeControl* aControl);
	
	IMPORT_C static void SetHints(const CCoeControl* aControl,TUid aLayerType);

	/**
	  informs the engine that any cached graphical representation of a control that it might have made is now out of date

	 controls flagged as @c EStatic may have bitmaps cached unless resized (although repositioning probably doesn't affect their cache)
	 or an explicit call to @c Invalidate().
	 
	 If you @c Invalidate() a registered N-Layered control, only its background layer will be invalidated
	 
	 @param aControl	the address of the control to be invalidated; it is either registered, or a layer of a registered N-Layered control
	 */
	IMPORT_C static void Invalidate(const CCoeControl* aControl);
	//@}
	
	//@{
	/**
	  Transition Demarcations
	 
	 Sometimes an inter-window transition has an demarcation - e.g. a detail view 'zoom out' of the selected list box item, or a popup occur from a pointer press.  The
	 new window may not know where it is coming from, but the window losing focus might.  This hint might help make the two transitions appear synchronised
	 and connected.
	 
	 The demarcation can be set for a window losing focus/visibility and for a window gaining focus/visibility, or both at once.
	 
	 Non-TVwsViewId demarcation operations are applied to the inner-most @c Begin() block for this control; they panic if the control is not currently in transition
	 (unless the transition engine is not able to comply)
	 
	 For a window gaining focus/visibility, the demarcation represents the begin-point for the transition.
	 For a window losing focus/visibility, the demarcation infact represents the end-point for the transition.
	 */
	 
	/**
	  set the demarcation point of a transition
	 
	 Useful if the window losing focus and the window gaining focus are both in the same thread.
	 
	 @param aControl	the address of the control to set the demarcation for; it is either registered, or a layer of a registered N-Layered control
	 @param aDemarcation		the point at from which the transition ought begin or end
	 */
	IMPORT_C static void SetDemarcation(const CCoeControl* aControl,const TPoint &aDemarcation);

	/**
	  set the demarcation point of a transition using a @c TVwsViewId
	 
	 Useful if the window losing focus and the window gaining focus are not necessarily in the same thread
	 
	 @param aView		the view id of the window
	 @param aDemarcation		the point from which the transition ought begin or end
	 */
	IMPORT_C static void SetDemarcation(const TVwsViewId &aView,const TPoint &aDemarcation);
	
	/**
	  set the demarcation rectangle of a transition
	 
	 Useful if the control losing focus and the control gaining focus are both in the same thread
	 
	 @param aControl	the address of the control to set the demarcation for; it is either registered, or a layer of a registered N-Layered control
	 @param aDemarcation		the rectangle from which the transition ought begin or end
	 */
	IMPORT_C static void SetDemarcation(const CCoeControl* aControl,const TRect &aDemarcation);

	/**
	  set the demarcation rectangle of a transition using a @c TVwsViewId
	 
	 Useful if the window losing focus and the window gaining focus are not necessarily in the same thread
	 
	 @param aView		the view id of the window
	 @param aDemarcation		the rectangle from which the transition ought begin or end
	 */
	IMPORT_C static void SetDemarcation(const TVwsViewId &aView,const TRect &aDemarcation);

	/**
	  set the demarcation rectangle from the client rectangle of another control for a transition
	 
	 Useful if the control losing focus and the control gaining focus are both in the same thread
	 
	 @param aControl	the address of the control to set the demarcation for; it is either registered, or a layer of a registered N-Layered control
	 @param aSrc		the control to use as the source; this control need not be registered
	 @param aDemarcation		the client rectangle of @c aSrc from which the transition ought begin or end
	 */
	IMPORT_C static void SetDemarcation(const CCoeControl* aControl,const CCoeControl* aSrc,const TRect &aDemarcation);

	/**
	  set the demarcation rectangle from the client rectangle of a control for a transition using a @c TVwsViewId
	 
	 Useful if the window losing focus and the window gaining focus are not necessarily in the same thread
	 
	 @param aView		the view id of the window, possibly owned by another thread
	 @param aSrc		the control in the current thread to use as the source; this control need not be registered
	 @param aDemarcation		the client rectangle of @c aSrc from which the transition ought begin or end
	 */
	IMPORT_C static void SetDemarcation(const TVwsViewId &aView,const CCoeControl* aSrc,const TRect &aDemarcation);
	//@}
		
	//@{
	/**
	  Effecting Transitions
	 
	 Actions that affect the visual representation of a control and that might have a transition associated with them are wrapped between
	 @c Begin() and @c End() calls.
	 
	 @c Begin() and @c End() calls can be nested.  It is up to the engine to decide whether to have sub-stages in transition effects or to
	 flatten the transitions into a single transition.  @c Begin() and @c End() calls must be matched and cannot be overlapped.
	 */
	 
	/**
	  generic transition event identifiers
	 
	 Additional events might be added in the future, or specific to a particular class of control
	 */
	enum 
		{
		EOpen,
		EClose,		
		EVisible,	
		EInvisible,	
		EGainFocus,
		ELoseFocus,
		EForegroundChange,
		EBackgroundChange,
		EInternalStateChange	//< not an implicit @c Invalidate() !  You still have to invalidate a control or it's component layers manually
		};

	/**
	  begins a transition
	 
	 Provides an opportunity for the engine to capture the 'before' state of the control and its layers.
	 
	 Code between a @c Begin and it's matching @c End cannot leave.  In those circumstances, use @c BeginLC instead.
	 
	 @param aKey		the address of the control to begin transition
	 @param aAction		a hint as to the type of transition to perform, e.g. EGainFocus
	 */
	IMPORT_C static void Begin(const CCoeControl* aKey,TUint aAction);
	
	/**
	  begins a transition in a leave-safe way
	 
	 Provides an opportunity for the engine to capture the 'before' state of the control and its layers.
	 
	 Places a special TCleanupItem onto the cleanup-stack so that subsequent code before the next @c End can leave.
	 In the event of a leave, the transition shall be implicitly aborted and the corresponding @c End should not be called.
	 
	 This means that code within the @c BeginLC and the matching @c End cannot unbalance the cleanup stack, however.
	 
	 @c BeginLC shall only leave if it the push of the TCleanupItem fails (in which case code is typically in a bad way anyway).
	 It shall not leave if there are insufficient resources to coordinate a transition.
	 
	 @param aKey		the address of the control to begin transition
	 @param aAction		a hint as to the type of transition to perform, e.g. EGainFocus
	 */
	IMPORT_C static void BeginLC(const CCoeControl* aKey,TUint aAction);
	
	/**
	  ends a transition
	 
	 Transition effects might not occur until the engine has seen both the 'before' and 'after' state of the control.
	 
	 End() should match the inner-most Begin() or BeginLC() block. 
	 If it doesn't, the client will try find a matching begin on a higher nesting level. 
	 If found, the 'unmatched' Begin calls lower in the nesting chain will be discarded.
	 If not found, the End will be ignored.
	 	 
	 @param aKey		the address of the registered control to end transition
	 */
	IMPORT_C static void End(const CCoeControl* aKey);
	
	/**
	 notify the engine of an external state (change).
	
	Some transitions might need a notification of when an external state has been reached.
	Then this function can be used.
	The state information and the optional data is send unmodified to the engine, and has to be supported
	by the specific engine implementation.

	@param aState the state that has been reached.
	@param aArg optional argument data.
	*/
	IMPORT_C static void NotifyExternalState(TInt aState, const TDesC8* aArg = NULL);

	/**
	  terminate a specific transition
	 
	 An aborted transition must not subsequently be ended.
	 
	 The call is ignored if @c aKey does not match the inner-most @c Begin
	 
	 @param aKey		the address of the registered control to abort transition
	 */	 
	IMPORT_C static void Abort(const CCoeControl* aKey);
	
	/**
	  terminate all effects for this client
	 
	 @c Abort() shall terminate all non-complete transitions.  It may also signal the cancellation of logically-complete yet still under-animation
	 transitions.
	 
	 Subsequent calls to @c Begin() shall begin a fresh transition set.  Calls to @c End() and @c Abort() before the next @c Begin() shall
	 not panic.
	 */
	IMPORT_C static void Abort();
	
	/**
	  terminate all effects for this client
	 
	 Aborts all non-complete transitions and may signal the cancellation of underway transitions.
	 
	 Subsequent calls to @c Begin() shall not begin a fresh transition set.
	 */
	IMPORT_C static void Disable();
	
	/**
	  enable transition effects
	 */
	IMPORT_C static void Enable();
	
	/**
	  query if the transition engine is available and enabled for this client
	 
	 This is no guarentee that the transition engine has resources to render transitions.
	 */
	IMPORT_C static TBool IsEnabled();



	/**
	 Sets the demarcation rectangle for the controls end position.

	This call will override the controls actual position at End.

	@param aControl the address of the control to set the demarcation for; it is either registered, or a layer of a registered N-Layered control
	@param aDemarcation the rectangle to which the transition will end
	*/
	IMPORT_C static void SetEndDemarcation(const CCoeControl* aControl, const TRect& aDemarcation);

	/**
	 Sets the demarcation rectangle for the controls begin position.

	This call will override the controls actual position at Begin.

	@param aControl the address of the control to set the demarcation for; it is either registered, or a layer of a registered N-Layered control
	@param aDemarcation the rectangle from which the transition will begin
	*/
	IMPORT_C static void SetBeginDemarcation(const CCoeControl* aControl, const TRect& aDemarcation);

	/**
	 Begins a new transition group

	Used to group several independent transitions to be executed synchronized.
	Begin/End calls between calls to BeginGroup and EndGroup will be queued and transitioned on the call to EndGroup.
	All calls to Begin must be followed by a corresponding call to End before EndGroup is called.

	@return an integer ID that indentifies the group.
	*/
	IMPORT_C static TInt BeginGroup(); //returns an id for the group.

	/**
	 Ends a transition group.

	Ends a transition group and starts the grouped transitions.

	@param aGroupId the ID of the group.
	*/
	IMPORT_C static void EndGroup(TInt aGroupId);

	/**
	 associates arbitrary data with a transition. 

	The data is given the supplied aType id and applied to the inner-most Begin block.
	The descriptors data must be valid until End has been called.

	@param aType the type identifier of the data
	@param aData the data to supply.
	*/
	IMPORT_C static void SetTransitionData(TUint aType, const TDesC8& aData);

	//Support for non-CCoeControl transitions.

	/**
	 Used to register a Draw Item Control.

	A Draw Item Control is a flat coecontrol that has graphic parts that are transioned independently. For example a listbox with listbox items. The client is informed of the independent parts while drawing the coecontrol using BeginDrawItem and EndDrawItem.   

	@param aControl the control
	@param aType Type of item. Used by transition engine to assign proper behaviour.
	*/
	IMPORT_C static void RegisterDrawItemControl(const CCoeControl* aControl, TUid aType);          


	/**
	 Used to mark the start of an individual Draw Item in a Draw Item Control.

	BeginDrawItem and EndDrawItem should be called in the Draw Item Controls Draw() function, to identify wich drawing commands that belong to wich individual Draw Item. The draw commands supplied between BeginDrawItem and EndDrawItem will be treated as an individual participant bitmap in the transition.
	All draw commands not within Begin/EndDrawItem calls will be drawn treated as part of the coecontrol and not as an individual Draw Item.

	Note that aFromRect:s and aToRect:s provided in the Draw corrensponding to the end state of a transition has priority over the begin state

	@param aControl the control
	@param aId Unique id to match subitems between CCoeControl begin- and end states.
	@param aType Type of item. Used by transition engine to assign proper behaviour.
	@param aDrawRect This is the rect within the CCoeControl where the item is drawn.
	@param aFromRect Optional: This rectangle will be used as "begin demarcation" if used.
	@param aToRect Optional: This rectangle will be used as "end demarcation" if used.
	*/
	IMPORT_C static void BeginDrawItem(const CCoeControl* aControl, TUint aId, TUid aType,TRect &aDrawRect,const TRect* aFromRect, const TRect* aToRect);


	/**
	 Used to mark the end of an individual Draw Item in a Draw Item Control.

	@param aControl the control
	*/  
	IMPORT_C static void EndDrawItem(const CCoeControl* aControl);

	/**
	 starts a full screen transition effect.

	Begins a full screen effect. 
	Depending on the type of effect, it might start immediatly, or at the corresponding End call.

	@param aAction Effect identifier
	@param aEffectArea the part of the framebuffer to be affected
	*/
	IMPORT_C static void BeginFullScreen(TUint aAction, const TRect &aEffectArea);


	/**
	 starts a full screen transition effect.

	Begins a full screen effect. 
	Depending on the type of effect, it might start immediatly, or at the corresponding End call.
	This variant takes a type and a descriptor with extra parameters to the transition. These can typically be a position on the screen from wich the full screen effect should originate.

	@param aAction Effect identifier
	@param aEffectArea the part of the framebuffer to be affected
	@param aType the type of the parameters.
	@param aParam the parameters.
	*/
	IMPORT_C static void BeginFullScreen(TUint aAction, const TRect &aEffectArea, TUint aType, const TDesC8& aParams);

	/**
	 Marks the end point for a full screen effect.

	Tells the transition engine that the wserv framebuffer should contain the desired end state of a fullscreen effect.
	For some effects this point might be when the transition actually start.
	*/
	IMPORT_C static void EndFullScreen();

	/**
	 aborts a full screen effect.

	Aborts any ongoing full screen effect.
	*/
	IMPORT_C static void AbortFullScreen();
 
	/**
	 Sets a transition observer
	
	The observer recieves callbacks when transitions are finished. 
	@param aObserver The observer that will be notified. NULL means that no observer will be called.
	*/
	IMPORT_C static void SetTransitionObserver(MGfxTransEffectObserver* aObserver);

	//@}
	
	
	//
	};	
#endif // __GFXTRANSEFFECT_H__
