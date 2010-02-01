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


#if !defined(__EIKLABEL_H__)
#define __EIKLABEL_H__


#if !defined(__EIKALIGN_H__)
#include <eikalign.h>
#endif

#if !defined(__COECCNTX_H__)
#include <coeccntx.h>
#endif

#include <bidi.h>

class CEikLabelExtension;
class CAknPictographInterface;

/**
 * Enables one or more lines of text to be displayed.
 */
class CEikLabel : public CEikAlignedControl, public MCoeControlContext
	{
public:  // new functions
    /**
     * Destructor.
     */
    IMPORT_C ~CEikLabel();
    /** 
     * C++ default constructor.
     */
    IMPORT_C CEikLabel();
    /**
     * Sets the labels alignment. Overwrites alignment set
     * via @c CEikAlignedControl.
     * 
     * @param aAlignment Should be one of { @c ELayoutAlignNone, 
     *        @c ELayoutAlignCenter, @c ELayoutAlignLeft, @c ELayoutAlignRight,
     *        @c ELayoutAlignBidi } defined in @c Avkon.hrh.
     */
    IMPORT_C void SetLabelAlignment(TInt aAlignment);

    /**
     * Sets the brush style to be used from @c aBrushStyle, 
     * this overwrites the brush style set via the Control Context.
     * 
     * @param aBrushStyle A brush style.
     */
    IMPORT_C void SetBrushStyle(CWindowGc::TBrushStyle aBrushStyle);

    /**
     * Sets the brush style to be used from the Control Context, 
     * this overwrites the brush style set via the @c CEikLabel::SetBrushStyle().
     */
    IMPORT_C void SetBrushStyleFromContext();


public:  // from CCoeControl
    /** 
     * From @c CCoeControl.
     *
     * Sets the control's minimum required size.
     *
     * @return Minimum size required by the control.
     */
    IMPORT_C TSize MinimumSize();
    /**
     * From @c CCoeControl.
     * 
     * Constructs the control from a resource file.
     *
     * @param aReader Interprets resource data read from a resource file.
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
     * From @c CCoeControl.
     *
     * Gets the list of logical colours used to draw the control.
     *
     * @param aColorUseList The colour list.
     */
    IMPORT_C void GetColorUseListL(
                        CArrayFix<TCoeColorUse>& aColorUseList) const;
    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources.
     *
     * @param aType A message UID value.
     */
    IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
    /**
     * From @c CCoeControl.
     *
     * Draw a control - called by window server. All controls, except blank 
     * controls, should implement this function. The default implementation 
     * draws a blank control.
     *
     * This function is used for window server-initiated redrawing of controls,
     * and for some application-initiated drawing. It should be implemented by 
     * each control, but is only called from within @c CCoeControl's member 
     * functions, and not from the derived class. For this reason it is a 
     * private member function of @c CCoeControl.
     *
     * @param aRect The region of the control to be redrawn. Co-ordinates are 
     *        relative to the control's origin (top left corner).
     * @panic EEikPanicLabelNullText Panics if label text has not been defined.
     */
    IMPORT_C void Draw(const TRect& aRect) const;

public:  
    /**
     * Determines text emphasis.
     */
    enum TTextEmphasis
        {
        /** No emphasis. */
        ENoEmphasis         =0x00,
        
        /** Partial emphasis. */
        EPartialEmphasis    =0x10,
        
        /** Full emphasis. */
        EFullEmphasis	 =0x20
        };
public:  // new functions
    
    /**
     * Sets the label’s text.
     *
     * @param aText The label’s text.
     * @panic EEikPanicLabelNullText Panics if label text has not been defined.
     */
    IMPORT_C void SetTextL(const TDesC& aText);
    
    /**
     * Gets the label’s text.
     *
     * @return The label’s text.
     */
    inline const TDesC* Text() const;
    
    /**
     * Sets a flag to indicate that the text needs to be truncated
     * with 3 dots.
     */
    IMPORT_C void CropText();
    
    /**
     * Sets the buffer reserve length.
     *
     * @param aLength The buffer reserve length.
     */
    IMPORT_C void SetBufferReserveLengthL(TInt aLength);
    
    /**
     * Sets the label’s font.
     *
     * @param aFont The label's font.
     */
    IMPORT_C void SetFont(const CFont* aFont);
    
    /**
     * Gets the label’s font.
     *
     * @return The label’s font.
     */
    inline const CFont* Font() const;
    
    /**
     * Sets the label's text emphasis.
     *
     * @param aEmphasis The label's text emphasis.
     */
    IMPORT_C void SetEmphasis(TTextEmphasis aEmphasis);
    
    /**
     * Sets the gap between lines. Gap has a particular definition here.
     * It is defined to be: "baselines separation" - @c CFont::HeightInPixels()
     * 
     * @param aGap Pixels gap to set between lines.
     */
    IMPORT_C void SetPixelGapBetweenLines(TInt aGap);
    
    /**
     * Gets the number of pixels between two lines of text.
     *
     * @return The number of pixels between two lines of text.
     */
    IMPORT_C TInt PixelGapBetweenLines() const;

    /**
     * Tests whether the label is underlined.
     *
     * @return @c ETrue if the label is set as underlined.
     * @return @c EFalse if the label is not set as underlined.
     */
    inline TBool IsUnderlined() const;
    
    /**
     * Sets the label underlining.
     *
     * @param aUnderLining @c ETrue to set the label as underlined. 
     *        @c EFalse to set the label as not underlined.
     */
    IMPORT_C void SetUnderlining(TBool aUnderLining);
    
    /**
     * Tests label strike-through.
     *
     * @return @c ETrue if the label is set to be drawn with a line through it.
     * @return @c EFalse if the label is not set to be drawn with a line 
     *            through it.
     */
    inline TBool IsStrikethrough() const;
    
    /**
     * Sets the label strike-through.
     *
     * @param aStrikethrough @c ETrue to set the label to be drawn with a line 
     *        through it. @c EFalse to set the label to not be drawn with a 
     *        line through it.
     */
    IMPORT_C void SetStrikethrough(TBool aStrikethrough);
    
    /**
     * Gets the minimum size required to draw the specified text.
     *
     * @param aText The text to be drawn.
     * @return The minimum size required to draw the text.
     */
    IMPORT_C TSize CalcMinimumSize(TPtrC& aText) const;
    
    /**
     * Gets the number of lines of text in the label.
     *
     * @return The number of lines of text.
     */
    inline TUint8 NumberOfLines();
    
    /**
     * Gets the buffer reserve length.
     *
     * @return The buffer reserve length.
     */
    IMPORT_C TInt BufferReserveLength() const;

    /**
     * Enables or disables logical to visual conversion when label text
     * is drawn. By default, it is enabled.
     * If you perform the conversion yourself and give visual text
     * (in scrictly left-to-right order) to label, you
     * should disable the conversion in label. Note that label does not perform
     * cropping if logical to visual conversion is disabled.
     *
     * @param aUseConversion Whether label should perform logical to visual
     *        conversion or not.
     */
    IMPORT_C void UseLogicalToVisualConversion( TBool aUseConversion );

    /**
     * Gets information whether label is performing logical to visual
     * conversion or not.
     *
     * @return @c ETrue if label does logical to visual conversion.
     * @return @c EFalse if not.
     */
    IMPORT_C TBool LogicalToVisualConversionUsed() const;

    /**
     * Enables pictograph drawing in the label text.
     * Only effective in Japanese variant.
     * By default, it is disabled.
     *
     * @since S60 2.6
     * @param aInterface Used pictograph interface owned by the caller.
     */
    IMPORT_C void EnablePictographsL( CAknPictographInterface& aInterface );

    /**
     * Disables pictograph drawing in the label text.
     * Only effective in Japanese variant.
     * By default, it is disabled.
     *
     * @since S60 2.6
     */
    IMPORT_C void DisablePictographs();
public: // From CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Handles pointer events. This function gets called whenever a pointer 
     * event occurs in the control, i.e. when the pointer is within the 
     * control's extent, or when the control has grabbed the pointer. 
     * The control should implement this function to handle pointer events.
     * 
     * Note: events of type @c EButton1Down are processed before 
     * @c HandlePointerEventL() is called, in order to transfer keyboard focus 
     * to the control in which the @c EButton1Down event occurred.
     *
     * If overriding @c HandlePointerEventL(), the implementation must include 
     * a base call to @c CCoeControl's @c HandlePointerEventL().
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected: // from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Writes the internal state of the control and its components to a stream.
     * Does nothing in release mode.
     * Designed to be overidden and base called by subclasses.
     *
     * @param aWriteStream The write stream.
     */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
    IMPORT_C void Reserved_2();
private:
    /**
     * From @c CAknControl.
     */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: // new functions
    TInt HeightInPixels() const;
    TInt WidthInPixels(TPtrC& aText) const;
    TInt HeightInPixels(const TDesC& aText) const;
    void SetupGcForEmphasis(CGraphicsContext& aGc) const;
    TBool CheckAndCreateExtension();
    void ConvertColorsForOutlineEffect(TRgb& aFillColor, TRgb& aOutlineColor) const;

public:
    /**
     * @internal
     */
    void DrawToContext( CBitmapContext& aContext, 
        const TRgb* aOverrideColor ) const;

protected:
    
    /**
     * Determines whether text is drawn with underlining or strike-through.
     */
    enum TLabelFlags
        {
        /** Text is drawn with underlining. */
        EUnderlining                  = 0x02,
        
        /** Text is drawn with strike-through. */
        EStrikethrough                = 0x04,

        /** 
         * Determines that bi-directional algorithm still needs to be run
         * against the set text string. This flag allows app to do
         * logical-to-visual conversion in the application side -- since the
         * bi-directional algorithm can only be run once for every text string,
         * we need flagging like this to control whether the algorithm is run
         * inside label or whether the application has already run it and we
         * should not return the algorithm.
         */
        EUseLogicalToVisualConversion = 0x08
        // flags 0x10, 0x20, 0x40 are already used for text emphasis!
        };
    
    /** The label’s text. */
    HBufC* iText;
    
    /** The label’s font. */
    const CFont* iFont;
    
    /** The label’s number of lines of text. */
    TUint8 iNumberOfLines;
    
    /**
     * The label’s flags. These are used to set text emphasis and 
     * characteristics, such as underlining, and strikethrough.
     */
    TUint8 iLabFlags;

    /** The number of pixels between lines of text. */
    TInt iGapBetweenLines;

private:
    TInt iReserveLength;
    CEikLabelExtension* iExtension;
    TInt iSpare[2];
    };


inline const TDesC* CEikLabel::Text() const
	{ return(iText); }
inline const CFont* CEikLabel::Font() const
	{ return(iFont); }
inline TBool CEikLabel::IsUnderlined() const
    {return iLabFlags&EUnderlining;}
inline TBool CEikLabel::IsStrikethrough() const
    {return iLabFlags&EStrikethrough;}
inline TUint8 CEikLabel::NumberOfLines()
	{return iNumberOfLines;}	

#endif // __EIKLABEL_H__
