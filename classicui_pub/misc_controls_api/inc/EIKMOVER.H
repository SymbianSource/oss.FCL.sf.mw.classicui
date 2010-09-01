/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKMOVER_H__)
#define __EIKMOVER_H__

#include <AknControl.h>

//
// Forward declarations
//

class TResourceReader;

/**
 * The CEikMover class implements a draggable bar that can be used as
 * the title bar of a dialog window.
 */
class CEikMover : public CAknControl
	{
public: // class specific
	/** Destructor
	 */
	IMPORT_C ~CEikMover();
	/** Constructor
	 */
	IMPORT_C CEikMover();
    /** SetText sets the text
     * @param aText a descriptor
     */
	IMPORT_C void SetText(HBufC* aText);
    /** SetTextL sets the text
     * @param aText a descriptor
     */
	IMPORT_C void SetTextL(const TDesC& aText);
	/** SetActive() sets mover active state
	 */
	IMPORT_C void SetActive(TBool aActive);
    /** Active() returns whether mover is active
     */
	IMPORT_C TBool Active() const;
    /** SetFont sets the font for the text
     */
	IMPORT_C void SetFont(const CFont* aFont);
    /** SetTitleLeftMargin sets left margin of the title text
     */
	IMPORT_C void SetTitleLeftMargin(TInt aLeftMargin);
public: // from CCoeControl
    /** ConstructFromResourceL constructs mover from resource
     * from CCoeControl
     */
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
    /** MinimumSize()
	 * from CCoeControl
     */
	IMPORT_C virtual TSize MinimumSize(); 
	/** SetContainerWindowL()
	 * from CCoeControl
	 */
	IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);
    /** GetColorUseListL()
	 * from CCoeControl
     */
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
    /** HandleResourceChange
	 * from CCoeControl
     */
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
    /** HandlePointerEventL()
	 * from CCoeControl
     */
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected: //from CCoeControl
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C virtual void Draw(const TRect& aRect) const;
private:
	IMPORT_C virtual void Reserved_2();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	HBufC* iText;
	const CFont* iFont;
	TPoint iPointerDownPos;
	TInt iMoverFlags;
	TInt iTitleLeftMargin;
	CCoeControl* iParentControl;
    TInt iSpare;
	};

#endif
