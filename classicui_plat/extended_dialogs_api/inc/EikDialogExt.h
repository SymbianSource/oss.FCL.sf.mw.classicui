/*
* Copyright (c) 2003 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __EIKDIALOGEXT_H__
#define __EIKDIALOGEXT_H__

#include <e32base.h>

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <akntransitionutils.h>
#endif

class CEikDialogPageSelector ;
class CEikDialog ;
class CAknsListBoxBackgroundControlContext ;
class CAknEdwinDrawingModifier ;
class CAknMediatorFacade;

/*
 * Extension structure for extra data members without breaking BC.
 * This header should not be a published interface.
 */
NONSHARABLE_CLASS(CEikDialogExtension) : public CActive
	{
	friend class CEikDialogPageSelector ;
	friend class CEikDialog ;

public: 
	/**
	* This enumeration encodes the way that CEikDialog is used in Averell.
	*/
	enum TLayoutCategory
		{
		ENotConstructed, // Returned if CEikDialog is not constructed enough to evaluate
		EUnknownLayout, // Layout is not known
		EFullScreenLayout, // returned if EEikDialogFlagFillAppClientRect has been set
		EFormLayout,      // True if the object is a CAknForm and appriopriate resource has been used
		EPopupLayout	// Popup layout; used for Notes, Queries; effectively the default
		};
	/**
	* Returns the type of Averell Layout that this instance of CEikDialog is implementing.
	* This is internal API for use inside Averell only.
	* 
	* @return	TLayoutCategory 
	*/
	IMPORT_C TLayoutCategory LayoutCategory() const;

	enum TPublicFlags
		{
        /** When set, dialog doesn't draw in the space of its child controls */
        EClipChildControlRect,
        EUseVirtualInput,
        EDelayedExit,
        EFullyConstructed
		};	
		
private :
	static CEikDialogExtension* NewL( const CEikDialog& aParent ) ;
	~CEikDialogExtension() ;
	CEikDialogExtension( const CEikDialog& aParent ) ;

    /**
    * Symbian OS 2nd stage contruction
    */
    void ConstructL();

protected: // from CActive
    void DoCancel();
    void RunL();

private:
    void StartDelayedExit();
        
private:
	enum TFlags
		{
		EEditableStateInitialised,
	    // whether dialog will show up with sliding effect or not
		ESlidingEnabled,
		ELayoutChangeWhileInvisible
		};
		
	const CEikDialog& iParent ; // NOT OWNED.  To access the dialog.  
	CAknsListBoxBackgroundControlContext* iBgContext ; // OWNED. <SKIN> might need: CAknsListBoxBackgroundControlContext
    TBitFlags iFlags;
    CAknEdwinDrawingModifier* iDrawingModifier; // OWNED - detailed control of edwin drawing
    CAknMediatorFacade* iAknDSSD;
    TInt iButtonId;
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    TUid iRegisteredContext;
    TBool iSleepDialogExitBeginCalled;
#endif

public:
    TBitFlags iPublicFlags;
    TBool iInitialMade;
  } ;


#ifdef RD_SLIDING_ANIMATION_EFFECTS
/**
* Class used for fake sliding animation.
* The control creates whole screen size window and slides dialog background in it.
*/

NONSHARABLE_CLASS(CEikDialogSlider) : public CCoeControl
	{
public:    
    ~CEikDialogSlider();
	static CEikDialogSlider* NewL(CWindowGc& aWindowGc, CFbsBitmap*& aDialogBack, CFbsBitmap*& aScreen);
    void SlideDialogL(TPoint& aStart, TPoint& aEnd, TInt aStepCount);
	
protected:
	CEikDialogSlider(CWindowGc& aWindowGc, CFbsBitmap*& aDialogBack, CFbsBitmap*& aScreen);
	void ConstructL();
	void Draw(const TRect& aRect) const;

private:
	CWindowGc& iWindowGc;
	CFbsBitmap* iDialogBack;
	CFbsBitmap* iScreen;
    TInt        iSpare;
    };
#endif //RD_SLIDING_ANIMATION_EFFECTS


#endif
