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


#ifndef     AKN_TEXT_CONTROL_H
#define     AKN_TEXT_CONTROL_H

#include <e32std.h>
#include <coecntrl.h>
#include <eiklabel.h>
#include <AknPictographDrawerInterface.h>

#include "akntext.h"

// FORWARD DECLARATIONS

class CAknPictographInterface;

/**
 * An avkon text control.
 *
 * Manage wrapping of text into one or more labels.
 * Support line wrapping (only wrap when a new line character is
 * found) or word wrapping (wrap when a word does not fit into a
 * specified line width).
 *
 * Text is stored in a CAknText object.
 */
NONSHARABLE_CLASS(CAknTextControl) : public CCoeControl, public MAknPictographAnimatorCallBack
	{
	public:
		enum TWrapMethod
			{
			ELine,
			EWord,
            ENoProcessing,
			ENoAllocation
			};
	public:
		static CAknTextControl* NewL(
            const CAknText::TType& aTextType = CAknText::EFormatted );
        
        ~CAknTextControl();
		CAknTextControl& operator=(CAknTextControl& aTextControl);

	public:
		void ConstructFromResourceL(TResourceReader& aRes);
		TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt anIndex) const;

	public: //Layout interface
		TInt NumberOfLines() const;
		CEikLabel* Line(TInt aIndex) const;

		TBool LineModified(TInt aIndex) const;
		void  SetLineModified(TInt aIndex, TBool aValue);
	
	public: //Text interface
		void  SetTextL(const TDesC& aText);
		//kept for backwards compatibility only
		void  SetTextL(const TDesC& aText, TInt aLineNum,const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths);
		
		TPtr Text() const;
		void ParseTextL(const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths, const TWrapMethod& aWrapMethod = EWord);

		void SetTextPluralityL(TBool aIsPlural);
		void SetTextNumberL(TInt aNumber);

    public: //Pictograph interface

        /**
        * Note control invokes this callback when a redraw is required for
        * animating pictographs. Only effective if pictograph feature is
        * supported.
        */
        void SetPictographCallBackL( TCallBack& aCallBack );

        /**
        * Access to the pictograph interface owned by the text control.
        * It is NULL if pictograph feature is not supported.
        *
        * Can be used in the pictograph callback if required. It is never
        * NULL when pictograph callback is invoked.
        */
        CAknPictographInterface* PictographInterface() const;

	private: // From MAknPictographAnimatorCallBack
        void DrawPictographArea();

    private:
		CAknTextControl();
		void ConstructL(const CAknText::TType& aTextType);
		
		CAknTextControl(const CAknTextControl&); //not allowed

		void SetWrappedTextIntoLabelsL(const CArrayFix<TPtrC>& aWrappedArray, TInt aNumLines, const CFont* aFont);

		void UpdateLabelsL(const TInt aNum,const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths);
		void CreateLabelsL(const TInt aNum,const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths);
		CEikLabel* CreateLabelLC(TInt aLen);

	private:
		class CLine : public CBase
			{
			public:
				CLine(CEikLabel* aLabel) : iModified(ETrue), iLabel(aLabel) {}
				~CLine() { delete iLabel; }
			public:
				TBool	   iModified;
				CEikLabel* iLabel;
			};
	private:
		TInt                       iNumberOfLines;
		RPointerArray<CLine>	   iLines;
		CAknText*                  iText;
		TBool                      iTextIsAlreadyInLabel;
		CArrayFixFlat<TPtrC>*      iWrappedArray;
        CAknPictographInterface*   iPictoInterface;
        TCallBack                  iPictoCallBack;
	};

#endif
