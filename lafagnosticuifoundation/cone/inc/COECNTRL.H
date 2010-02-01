// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __COECNTRL_H__
#define __COECNTRL_H__

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <gulalign.h>
#include <coedef.h>
#include <coecobs.h>
#include <coehelp.h>
#include <coeinput.h>
#include <coemop.h>
#include <coemain.h>
#include <coefont.h>
#include <coetextdrawer.h>
#include <coecontrolarray.h>

#include <coecoloruse.h>	// class TCoeColorUse

class TResourceReader;
class CCoeEnv;
class MCoeControlContext;
class CCoeControlStorage;

class MCoeLayoutManager;
class TCoeZoomWithType; 
class CCoeFontProvider;

// forward declarations.	
class CCoeControl;
class CCoeTextDrawerBase;

/** Interface to be used if a control elects to be a background drawer.

Parent controls can elect to take responsibility for drawing the background for their child
controls. To achieve this, they should aggregate an object that implements this interface.
CCoeControl::SetBackground() accepts the object and sets it as the background drawer

@see CCoeControl::EnableWindowTransparency()
@publishedAll
@released
*/
class MCoeControlBackground
	{
public:
	/** Draw the background for a given control.
	The text drawer that shall be used to draw text on the specific background can be 
	fetched through the GetTextDrawer() method. 

	@param aGc Graphics context used for drawing
	@param aControl The control being drawn (may be a child of the drawer)
	@param aRect The area to be redrawn

	@publishedAll
	@released
	*/
	virtual void Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const = 0;
	/**
	This function retrieves the text drawer associated with the background.
	@param aTextDrawer The text drawer associated with the background. This may be null. The default implementation
	always sets this to 0.
	@param aDrawingControl The control that is requesting the text drawer.
	*/
	IMPORT_C virtual void GetTextDrawer(CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* aDrawingControl) const;
protected:
	IMPORT_C MCoeControlBackground();
private:  
  	IMPORT_C virtual void MCoeControlBackground_Reserved1();
  	IMPORT_C virtual void MCoeControlBackground_Reserved2();
  	IMPORT_C virtual void MCoeControlBackground_Reserved3();
  	IMPORT_C virtual void MCoeControlBackground_Reserved4();
  	IMPORT_C virtual void MCoeControlBackground_Reserved5();
private:
	TInt iMCoeControlBackground_Reserved1();
	};

/** Abstract interface for defining a control's hit region.

This could be implemented by a CCoeControl-derived class to 
define hit region checking. The object is installed by calling CCoeControl::SetHitTest().

The hit region is the area inside the control's rectangle in which pointer events are handled.
It can be any shape, not necessarily rectangular.

@publishedAll
@released
*/
class MCoeControlHitTest
	{
public:	
	/** Tests whether a pointer event occurred inside the control's hit region.
	This function is called by CCoeControl::HandlePointerEventL().

	@param aPoint The position of the pointer event.
	@return ETrue if the specified point lies inside the hit region, EFalse if not.

	@publishedAll
	@released
	*/
	virtual TBool HitRegionContains(const TPoint& aPoint, const CCoeControl& aControl) const = 0;
protected:
	IMPORT_C MCoeControlHitTest();
private:
	IMPORT_C virtual void MCoeControlHitTest_Reserved1();
	IMPORT_C virtual void MCoeControlHitTest_Reserved2();
private: 
    TInt iMCoeControlHitTest_Reserved1;
	};


/** 
Control base class from which all other controls are derived. 

@publishedAll
@released 
*/
class CCoeControl : public CBase, public MObjectProvider
	{
public:
    enum TZoomType 
        { 
        EAbsoluteZoom,        // absolute 
        ERelativeZoom         // relative to parent's zoom 
        }; 
public:    
    // Construction and destruction    
	IMPORT_C CCoeControl();
	IMPORT_C CCoeControl(CCoeEnv* aCoeEnv);
	IMPORT_C ~CCoeControl();
	IMPORT_C TBool ComponentArrayExists() const;
public: // Virtuals (see more related non-virtuals further down)
	// Key input
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	// Visual state
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	// Construction
	IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual void ActivateL();
	// Focus
	IMPORT_C virtual void PrepareForFocusLossL();
	IMPORT_C virtual void PrepareForFocusGainL();
	// Control proximity
	IMPORT_C virtual void SetAdjacent(TInt aAdjacent);
	IMPORT_C virtual void SetNeighbor(CCoeControl* aNeighbor);
	IMPORT_C virtual TBool HasBorder() const;	// deprecated from 9.2
	// Control size
	IMPORT_C virtual TSize MinimumSize();
	// Resource change handling
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	// Logical color use (for Java)
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	// User help
	IMPORT_C virtual void GetHelpContext(TCoeHelpContext& aContext) const;
	// Text input
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
public:	
	// Environment
	inline CCoeEnv* ControlEnv() const;
	// Container window
	IMPORT_C RDrawableWindow* DrawableWindow() const;
	IMPORT_C TBool OwnsWindow() const;
	IMPORT_C TBool IsBackedUp() const;
	IMPORT_C void SetContainerWindowL(RWindow& aWindow); 			// deprecated from 9.2
	IMPORT_C void SetContainerWindowL(RBackedUpWindow& aWindow);	// deprecated from 9.2
	// Control parent
	IMPORT_C CCoeControl* Parent();
	IMPORT_C const CCoeControl* Parent() const;
	IMPORT_C virtual TInt SetParent(CCoeControl* aParent);
	// Size and position
	IMPORT_C TRect Rect() const;
	IMPORT_C void SetRect(const TRect& aRect);
	IMPORT_C void SetExtent(const TPoint& aPosition,const TSize& aSize);
	IMPORT_C void SetExtentToWholeScreen();
	IMPORT_C TSize Size() const;
	IMPORT_C void SetSize(const TSize& aSize);
	IMPORT_C TPoint Position() const;
	IMPORT_C TPoint PositionRelativeToScreen() const;
	IMPORT_C void SetPosition(const TPoint& aPosition);
	IMPORT_C TInt MaximumWidth() const;
	IMPORT_C TInt SetMaximumWidth(TInt aMaxWidth);
	// Layout	
	IMPORT_C MCoeLayoutManager* LayoutManager() const;
	IMPORT_C virtual void SetLayoutManagerL(MCoeLayoutManager* aLayout);
	IMPORT_C virtual TBool RequestRelayout(const CCoeControl* aChildControl);
	// Visibility
	IMPORT_C TBool IsVisible() const;
	IMPORT_C void SetComponentsToInheritVisibility(TBool aInherit=ETrue);
	// Dimmed
	IMPORT_C TBool IsDimmed() const;
	// State observer
	IMPORT_C void SetObserver(MCoeControlObserver* aObserver);
	IMPORT_C MCoeControlObserver* Observer() const;
	// Focus
	IMPORT_C TBool IsFocused() const;
	IMPORT_C void SetFocus(TBool aFocus,TDrawNow aDrawNow=ENoDrawNow);
	IMPORT_C void SetNonFocusing();
	IMPORT_C void SetFocusing(TBool aFocusing);
	IMPORT_C TBool IsNonFocusing() const;
	// Drawing (see also Draw() below)
	IMPORT_C void DrawNow() const;
	IMPORT_C void DrawNow(const TRect &aRect) const;
	IMPORT_C void DrawDeferred() const;
	IMPORT_C CWindowGc& SystemGc() const;
	IMPORT_C TInt SetCustomGc(CWindowGc* aGraphicsContext);
	IMPORT_C CWindowGc* CustomGc() const;	
	// Control context (background color etc). Deprecated (use MCoeControlBackground)
	IMPORT_C void SetControlContext(MCoeControlContext* aContext);		// deprecated from 9.2
	IMPORT_C void CopyControlContextFrom(const CCoeControl* aControl);	// deprecated from 9.2
	IMPORT_C MCoeControlContext* ControlContext() const;				// deprecated from 9.2
	// Pointer events
	IMPORT_C void SetPointerCapture(TBool aCapture=ETrue);
	IMPORT_C void ClaimPointerGrab(TBool aSendUpEvent=ETrue);
	IMPORT_C TInt ClaimPointerGrab(TInt aPointerNumber, TBool aSendUpEvent);
	IMPORT_C void IgnoreEventsUntilNextPointerUp();
	IMPORT_C void SetGloballyCapturing(TBool aGlobal);
	// Pointer hit test
	IMPORT_C TInt SetHitTest(const MCoeControlHitTest* aHitTestControl);
	IMPORT_C const MCoeControlHitTest* HitTest() const;
	// Logical colors
	IMPORT_C void OverrideColorL(TInt aLogicalColor,TRgb aColor);
	IMPORT_C TBool GetColor(TInt aLogicalColor,TRgb& aColor) const;
	// Control background
	IMPORT_C void DrawBackground(const TRect& aRect) const;
	IMPORT_C void DrawForeground(const TRect& aRect) const;
	IMPORT_C const MCoeControlBackground* Background() const;
	IMPORT_C const MCoeControlBackground* FindBackground() const;
	IMPORT_C void SetBackground(const MCoeControlBackground* aBackground);
	// Zooming
	IMPORT_C void SetZoomFactorL(TInt aZoomFactor, TZoomType aZoomType = ERelativeZoom);
   	IMPORT_C TZoomFactor AccumulatedZoom() const;
   	IMPORT_C const TCoeZoomWithType* ZoomWithType() const;
  	// Font provider (see ScreenFont() below)
    IMPORT_C const CCoeFontProvider& FindFontProvider() const;
	IMPORT_C void SetFontProviderL(const CCoeFontProvider& aFontProvider);
	// Text baseline (virtuals)
	IMPORT_C virtual TInt TextBaselineOffset(const TSize& aSize) const;
	IMPORT_C virtual void SetTextBaselineSpacing(TInt aSpacing);
	// Input capabilities
	IMPORT_C TCoeInputCapabilities RecursivelyMergedInputCapabilities() const;
	// Interface access
	IMPORT_C void SetMopParent(MObjectProvider* aParent);
	// Instance identification
	IMPORT_C TInt UniqueHandle() const;
	IMPORT_C TInt SetUniqueHandle(TInt aUniqueHandle); 
public: // Pointer events (virtuals)
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected: // Virtuals. Override to handle these events.
	IMPORT_C virtual void HandlePointerBufferReadyL();	// See HandlePointerEventL()
	// Change of focus
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
	// Change of size and position
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void PositionChanged();
public:
	// Component control access
	IMPORT_C virtual TInt CountComponentControls() const;
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TInt Index(const CCoeControl* aControl) const;
protected:
	// Control state	
	IMPORT_C TBool IsActivated() const;
	IMPORT_C TBool IsBeingDestroyed() const;
	// Component ownership
	IMPORT_C void InitComponentArrayL();
	IMPORT_C CCoeControlArray& Components();
	IMPORT_C const CCoeControlArray& Components() const;
	// Container window
	IMPORT_C RWindow& Window() const;
	IMPORT_C RBackedUpWindow& BackedUpWindow() const;
	IMPORT_C void CloseWindow();
	IMPORT_C void CreateWindowL();
	IMPORT_C void CreateWindowL(const CCoeControl* aParent);
	IMPORT_C void CreateWindowL(RWindowTreeNode& aParent);
	IMPORT_C void CreateWindowL(RWindowGroup* aParent);
	IMPORT_C void CreateBackedUpWindowL(RWindowTreeNode& aParent);
	IMPORT_C void CreateBackedUpWindowL(RWindowTreeNode& aParent,TDisplayMode aDisplayMode);
	IMPORT_C void EnableWindowTransparency();
	// Size and position
	IMPORT_C void SetCornerAndSize(TGulAlignment aCorner,const TSize& aSize);
	IMPORT_C void SetSizeWithoutNotification(const TSize& aSize);
	// Font access
	IMPORT_C const CFont& ScreenFont(const TCoeFont& aFont) const;
	// Text drawer
	IMPORT_C CCoeTextDrawerBase& TextDrawer(TInt aKey = KErrNotFound) const; 
	// Pointer events
	IMPORT_C void EnableDragEvents();
	IMPORT_C void HandleRedrawEvent(const TRect& aRect) const;
	IMPORT_C void SetAllowStrayPointers();
	IMPORT_C CCoeControl* GrabbingComponent() const;
	IMPORT_C CCoeControl* GrabbingComponent(TInt aPointer) const;
	IMPORT_C TBool CapturesPointer() const;
	// Drawing	
	IMPORT_C TBool IsReadyToDraw() const;
	IMPORT_C TBool IsBlank() const;
	IMPORT_C void SetBlank();
	IMPORT_C void SetCanDrawOutsideRect();
	IMPORT_C void ActivateGc() const;
	IMPORT_C void DeactivateGc() const;
	IMPORT_C void ResetGc() const;
	// State events
	IMPORT_C void ReportEventL(MCoeControlObserver::TCoeEvent aEvent);
	// Resource changes	
	IMPORT_C void HandleComponentControlsResourceChange(TInt aType);
	// Copy Constructor and Assignment Operator
	inline CCoeControl(const CCoeControl& aControl);
	inline CCoeControl& operator=(const CCoeControl& aControl);
protected:	
	friend class CCoeControlArray;   
	IMPORT_C virtual void HandleControlArrayEventL(CCoeControlArray::TEvent aEvent, const CCoeControlArray* aArray, CCoeControl* aControl, TInt aControlId);
private: // reserved
	IMPORT_C virtual void Reserved_CCoeControl_10();
	IMPORT_C virtual void Reserved_CCoeControl_11();
	IMPORT_C virtual void Reserved_CCoeControl_12();
	IMPORT_C virtual void Reserved_CCoeControl_13();
private:
	IMPORT_C virtual void GetTextDrawer(CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* aDrawingControl, TInt aKey) const;
private: // reserved
	IMPORT_C virtual void Reserved_CCoeControl_8();
	IMPORT_C virtual void Reserved_CCoeControl_9();
protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private: // from MObjectProvider
	IMPORT_C MObjectProvider* MopNext();
private: 
	// Drawing (override this to draw)
	IMPORT_C virtual void Draw(const TRect& aRect) const;
protected: 
	// Debugging
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // reserved
	IMPORT_C virtual void Reserved_2();
public: // but not exported
	void ProcessPointerEventL(const TPointerEvent& aPointerEvent);
	void ProcessPointerBufferReadyL();
	void RecursivelyMergeInputCapabilities(TCoeInputCapabilities& aInputCapabilities) const;
	void WriteInternalStateNowL(RWriteStream& aWriteStream) const;
    void NotifyFontChange(const CCoeFontProvider* aFontProvider);
    void RemoveFromParent();
    void RefetchPixelMappingL();
public: // deprecated
	inline TInt SetGc(CWindowGc* aGraphicsContext) const;
	inline CWindowGc* GetGc() const;
private:
	friend class CCoeRedrawer;
	void DrawComponents(const TRect& aRect) const;	
	void DrawWindowOwningComponentsNow() const;
	void DrawWindowOwningComponentsNow(const TRect &aRect) const;	
	void SetGrabbed(TBool aGrabbed, TInt aPointerNumber);
	TBool IsGrabbed(TInt aPointerNumber = 0) const;
	void DoMakeVisible(TBool aVisible);
	void CheckPointerEventPurge() const;
	void RecursivelyMergeTextDrawers(CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* aDrawingControl, TInt aKey) const;
	CCoeControl* WindowOwningParent();
	const CCoeControl* WindowOwningParent() const { return const_cast<CCoeControl*>(this)->WindowOwningParent(); }
	const CCoeControl* SearchParent(const CCoeControl* aParentToFind) const;
	TInt SetZoomWithType(TCoeZoomWithType* aZoomWithType);
	TCoeZoomWithType* GetZoomWithType() const;
	TInt SetFontProvider(const CCoeFontProvider* aFontProvider);
	const CCoeFontProvider* GetFontProvider() const;
	TInt FindColor(TInt aLogicalColor) const;
	void ActivateGcRecursive() const;
	void DeactivateGcRecursive() const;
	void ReportControlStateChange(MCoeControlStateObserver::TCoeState aType);
	TInt ValidateAdvancedPointerNumber( const TPointerEvent& aPointerEvent ) const;
	void ControlClaimPointerGrab(TInt aPointerNumber);
public:	
	IMPORT_C void EnableReportControlStateChange(TBool aState);

protected:
	CCoeEnv* iCoeEnv;
	MCoeControlContext* iContext;	// deprecated
	TPoint iPosition;
	TSize iSize;
private:
	TInt iFlags;
	RDrawableWindow* iWin;
	CCoeControlStorage* iData;
	MObjectProvider* iMopParent;
	};


/** 
Gets the control environment object for this control.

@return The control's control environment object. 
*/
inline CCoeEnv* CCoeControl::ControlEnv() const
	{ return(iCoeEnv); }

/**
Deprecated. See CCoeControl::SetCustomGc().
@deprecated
*/
inline TInt CCoeControl::SetGc(CWindowGc* aGraphicsContext) const
	{ return const_cast<CCoeControl*>(this)->SetCustomGc(aGraphicsContext); }
	
/**
Deprecated. See CCoeControl::CustomGc().
@deprecated
*/
inline CWindowGc* CCoeControl::GetGc() const
	{ return CustomGc(); }


#endif	// __COECNTRL_H__
