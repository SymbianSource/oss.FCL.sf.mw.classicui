/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/




#if !defined(__AKNSCBUT_H__)
#define __AKNSCBUT_H__

//  INCLUDES
#include <AknControl.h>

// FORWARD DECLARATIONS

class CAknScrollIndicator;

/**
*  Implements a scroll buttons of a scroll bar.
*
*  @since Series 60 0.9
*/
NONSHARABLE_CLASS(CAknScrollButton) : public CAknControl
	{
public:
	/**
	* Indicates a Scroll button's type
	*/
	enum TType
		{
		/** Scroll button to move the display to the left. */
		ENudgeLeft,
		/** Scroll button to move the display up.  */
		ENudgeUp, 
		/** Scroll button to move the display to the right. */
		ENudgeRight,
		/** Scroll button to move the display down. */ 
		ENudgeDown,
		/** Scroll button to move the display page to the left. */ 
		EPageLeft, 
		/** Scroll button to move the display page up. */
		EPageUp, 
		/** Scroll button to move the display page to the right.*/
		EPageRight,
		/** Scroll button to move the display page down. */ 
		EPageDown, 
		/** Scroll button to move the display to the home position. */
		EHome,
		/** Scroll button to move the display to the top. */ 
		ETop,
		 /** Scroll button to move the display to the end position. */ 
		EEnd,
		/** Scroll button to move the display to the bottom. */
		EBottom 
		};

public:
	/**
	* Indicates a scroll bar's type.
	*/
	enum TTypeOfScrollBar
		{
		/** Normal scroll bar  */
		ENormal		=0x00,
		/** Arrow headed scroll bar */ 
		EArrowHead	=0x01 
		};

public: // class specific functions

    /**
    * Two-phased constructor.
    * @param aType scroll button's type.
    * @return A fully constructed @c CAknScrollButton object.
    */
	IMPORT_C static CAknScrollButton* NewL(TType aType);
	
	/**
    * Destructor.
    */
	IMPORT_C ~CAknScrollButton();
	
	/**
    * Gets a scroll button's type.
    * @return The scroll button's type.
    */
	IMPORT_C TType Type() const;
	
	/**
    * Creates a window only for arrows. 
    * Sets the container window to be this class.
    * @param aParent The control to be the parent of this control.
    */
	IMPORT_C void CreateWindowOnlyForArrowsL(const CCoeControl* aParent);
	
	/**
    * Determines whether a scroll button is owned by normal scroll bar.
    * @return @c ETrue if a scroll button is owned by the normal scroll bar, 
    *         @c EFalse if not
    */
	IMPORT_C TBool IsNormalScrollBarUsingButton() const;
	
	/**
    * Sets the type of scroll bar which owns the button.
    * @param aTypeOfScrollBar The type of the scroll bar.
    */
	IMPORT_C void SetTypeOfScrollBarUsingButton(TTypeOfScrollBar aTypeOfScrollBar);
	
	/**
    * Sets the new focus position in the control and the span length.
    * @param aFocusPosition The new focus position.
    * @param aScrollSpan The new span length.
    */
	IMPORT_C void SetPosition(const TInt aFocusPosition, const TInt aScrollSpan);
	
	/**
    * Two-phased constructor.
    * @param aType scroll button's type.
    * @param aTypeOfScrollBar scroll bar type, this information is needed at construction
    *  time when creating button for double span scroll bar (ie. the parameter is ENormal)
    * @return A fully constructed @c CAknScrollButton object.
    */
	IMPORT_C static CAknScrollButton* NewL(TType aType, TTypeOfScrollBar aTypeOfScrollBar);
	
	void SetContainerWindowL( const CCoeControl& aControl );
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl( TInt aIndex ) const;
	
private: // class specific functions
	CAknScrollButton(TType aType);
	void ConstructL();
	void SizeChanged();
	void DrawIndicator() const;
	void ConstructL(TTypeOfScrollBar aTypeOfScrollBar);
private: // from CCoeControl
	virtual void Draw(const TRect& aRect) const;
private:
	friend class CAknScrollBar;
	TType iType;
	TInt iFlag;
	CAknScrollIndicator* iScrollIndicator;
	TRect iOldRect;
	};


#endif
