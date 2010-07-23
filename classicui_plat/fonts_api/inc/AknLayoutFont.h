/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
*   Interface for Series 60 font type, incorporating principles of series 60 layout
*
*
*/

   
#ifndef AKNLAYOUTFONT_H
#define AKNLAYOUTFONT_H

#include <gdi.h>
#include <fbs.h>
#include <AknFontSpecification.h>
#include <AknTextDecorationMetrics.h>

class CBitmapDevice;

/**
* This abstract class is a CFbsFont that can update itself (re-bind a font) and has standard
* Series 60 layout API available.
* 
* Concrete classes derived from this implement constructors and Update methods that
* supply the specification required for the initially, and newly bound font, respectively. 
* Derived classes must also implement the CreateFont framework method in order to
* implement the font binding itself.
* 
*  @lib avkon.dll
*  @since 2.8
*
*  @internal
*/
NONSHARABLE_CLASS(CAknLayoutFont) : public CFbsFont
    {

public:
    /**
    * C++ Destructor.
    */
    virtual ~CAknLayoutFont();

public: // New functions
    /**  
    * Update this object's binding to a CFbsFont, using the member data of the derived class.
    * This method only needs to be called if the client owns the CAknLayoutFont
    * object, and there has been a layout switch that may affect the font. 
    * 
    * It is functionally equivalent to deleting the CAknLayoutFont object, and 
    * reconstructing it with the same parameters.
    */
    IMPORT_C void Update();

    /**
    * Return the maximum extent of any pixel in the font upwards from the baseline
    * Measured up, so therefore it is a positive value.
    * 
    * @return maximum ascent of the font
    */ 
    IMPORT_C TInt MaxAscent() const;

    /**
    * Return the maximum extent of any pixel in the font down the baseline
    * Measured down, so therefore it is usually a positive value.
    * 
    * @return maximum descent of the font
    */ 
    IMPORT_C TInt MaxDescent() const;

    /*
    * Position of the baseline measured down from the Series 60 layout text pane top
    *
    * @return distance from text pane top to baseline
    */
    IMPORT_C TInt TextPaneTopToBaseline() const;
    
    /*
    * Position of the text pane bottom measured down from the baseline
    *
    * @return distance from text pane top to baseline
    */
    IMPORT_C TInt BaselineToTextPaneBottom() const;

    /*
    * Series 60 text pane height. 
    * Always equal to TextPaneTopToBaseline() + BaselineToTextPaneBottom()
    *
    * @return text pane height
    */
    IMPORT_C TInt TextPaneHeight() const;

    /**
    * This provides the baseline relative to the top of the combined font for a specific 
    * character code. This value does not include any TopShortfall.
    **/
    TInt AscentForCharacter( TChar aCharacter ) const; 

    /**
    * Returns if a font pointer cast to this type if the actual type conforms to this type. 
    * 
    * @returns NULL if the font does not conform to CAknLayoutFont.
    */
    IMPORT_C static const CAknLayoutFont* AsCAknLayoutFontOrNull( const CFont* aFont );

    /**
    * Returns an object describing how the text with this font is to be decorated
    * 
    * @return   text decoration metrics for the font
    */
    IMPORT_C TAknTextDecorationMetrics TextDecorationMetrics() const;

    /**
    * Returns the Avkon font category (EAknFontCategoryPrimary, EAknFontCategorySecondary...)
    * that was used to generate this font.
    * 
    * @return   font category
    */
    IMPORT_C TAknFontCategory FontCategory() const;

    /**
    * This API allows the font to provide the metrics under which the font was requested.
    * 
    * @return   the font specification for which the font has been supplied
    */
    IMPORT_C TAknFontSpecification FontSpecification() const;
    
public: // Functions from CFont
     
public:// Functions from CFbsFont

    TFontSpec DoFontSpecInTwips() const;

protected:
    /**
    * C++ Constructor.
    */
    CAknLayoutFont( CBitmapDevice& aScreenDevice );
    CBitmapDevice& BitmapDevice() const;

protected: // Internal methods

    void SetExcessAscent( TInt aExcessAscent );
    void SetExcessDescent( TInt aExcessDescent );
    void SetBottomShortfall( TInt aBottomShortfall );
    void SetTextPaneHeight( TInt aTextPaneHeight );

private: // New Framework methods
    virtual CFbsFont* SupplyFont() = 0;
    virtual TInt DoAscentForCharacter( TChar aCharacter ) const;
    virtual TAknTextDecorationMetrics DoTextDecorationMetrics() const = 0;
    virtual TAknFontSpecification DoFontSpecification() const = 0;
    virtual void CAknLayoutFont_Reserved_1();

private:
    void Register();
    void Deregister();

private:

    CFbsFont* iNonDynamicFont;
    CBitmapDevice& iScreenDevice;
    TInt iExcessAscent;
    TInt iExcessDescent;
    TInt iBottomShortfall;
    TInt iTextPaneHeight;
    TInt iSpare;
    };


#endif  //AKNLAYOUTFONT_H
