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
*   Label control to the status pane's navigation pane.
*
*
*/


#ifndef AKNNAVILABEL_H
#define AKNNAVILABEL_H

#include <AknControl.h>

class CAknNaviLabelExtension;
class TAknLayoutText;

/**
 * Label control to the status pane's navigation pane.
 */
class CAknNaviLabel : public CAknControl
	{
public:
    enum TNaviLabelType
        {
        ENavigationLabel,
        EAdditionalInfoLabel,
        EHintText
        };

public:  // new functions

    /**
    * Constructor.
    */
    IMPORT_C CAknNaviLabel();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknNaviLabel();

    /**
     * Set type of the label.
     * @param aNaviLabelType navigation label type.
     */
    IMPORT_C void SetNaviLabelType(TNaviLabelType aNaviLabelType);

    /**
     * Returns type of the label.
     * @return navigation label type.
     */
    IMPORT_C TNaviLabelType NaviLabelType();

    /**
     * Sets navigation label text.
     * @param aText reference to the navigation text.
     */
    IMPORT_C void SetTextL(const TDesC& aText);

    /**
     * Returns the current label text.
     * @return label text. Ownership of the text is not transfered.
     */
    inline const TDesC* Text() const;

public: 

    /**
    * From CCoeControl. Handles pointer event.
    * @param aPointerEvent Pointer event to be handled.
    */
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 

protected: // from CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * From CCoeControl.  Draw a control.  
    *
    * @param aRect The region of the control to be redrawn.   
    */
    IMPORT_C void Draw(const TRect& aRect) const;
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
    /**
     * Calculates width using margins.
     * @return width.
     */
    TInt WidthInsideMargins() const;

    /**
     * Reads the text layout from Aknlayout system.
     * @return Text layout.
     */
    TAknLayoutText LayoutText() const;    

private:
	HBufC* iText;
	CAknNaviLabelExtension* iExtension;
    const CFont* iFont;
    TInt iLeftMargin;
    TInt iRightMargin;
    TInt iSpare;
    TInt iRightOffset;
    TRgb iColor; 

    TNaviLabelType iLabelType;
	};


inline const TDesC* CAknNaviLabel::Text() const
	{ return(iText); }


#endif // AKNNAVILABEL_H
