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
*     Edwin's private custom drawer
*
*
*/


#ifndef     __AKNEDWINCUSTOMDRAWBASE_H__
#define     __AKNEDWINCUSTOMDRAWBASE_H__

// INCLUDES

class CTextView;
class CTextLayout;

#include <lafmain.h>
#include <AknPictographDrawerInterface.h>

// FORWARD DECLARATIONS

class MAknsControlContext;
class CEikEdwin;
class CAknPictographInterface;

// CLASS DECLARATION

NONSHARABLE_CLASS(CAknEdwinCustomDrawBase) :
    public CLafEdwinCustomDrawBase,
    public MAknPictographAnimatorCallBack
	{
public:
	/**
    * Two phase constructor. This can be used when TextView is not present yet
    */
    static CAknEdwinCustomDrawBase* NewL(const MLafEnv& aEnv,const CEikEdwin& aEdwin);

    /**
    * Two phase constructor. This should be used when TextView is present
    */
	static CAknEdwinCustomDrawBase* NewL(const MLafEnv& aEnv,const CEikEdwin& aEdwin, CTextView* aTextView, CWindowGc* aSystemGc);

    /**
    * Destructor
    */
    virtual ~CAknEdwinCustomDrawBase();

    void ConstructL();

protected:  // Constructors
    /**
    * Constructor to use if there is no iTextView yet.
    *
    * @param aEnv   Interface to the control's environment
    * @param aEdwin The edwin being drawn
    */
    CAknEdwinCustomDrawBase(const MLafEnv& aEnv,const CEikEdwin& aEdwin);

    /**
    * This constructor is to be used if iTextView exists. It allows an optimized draw
    * to be performed.
    *
    * @param aEnv       Interface to the control's environment
    * @param aEdwin     The edwin being drawn
    * @param aTextView  The textview object being used by the edwin
    * @param aSystemGc  The system gc being used by the editor.
    */
	CAknEdwinCustomDrawBase(const MLafEnv& aEnv,const CEikEdwin& aEdwin, CTextView* aTextView, CWindowGc* aSystemGc );

public: // from MFormCustomDraw
    /**
    * Draw a chunk of text. Documented in parent class
    */
	void DrawText( const TParam& aParam, const TLineInfo& aLineInfo, 
	    const TCharFormat& aFormat, const TDesC& aText, const TPoint& aTextOrigin, 
	    TInt aExtraPixels ) const;
	
	void DrawText( const TParam& aParam, const TLineInfo& aLineInfo, 
	    const TCharFormat& aFormat, const TDesC& aText, const TInt aStart, 
	    const TInt aEnd, const TPoint& aTextOrigin, TInt aExtraPixels ) const;
	
	/**
    * Draw a section of background according to TParam structure and background color
    * aDrawn must return the rectangle successfuly drawn.
    * Documented in parent class
    */
    void DrawBackground(const TParam& aParam,const TRgb& aBackground,TRect& aDrawn) const;

    /**
    * Draw background lines.
    * Documented in parent class
    */
	void DrawLineGraphics(const TParam& aParam,const TLineInfo& aLineInfo) const;

    // Implemented with base calls only:
    TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const;
	
private: // From MAknPictographAnimatorCallBack

    void DrawPictographArea();

public: // new virtual

    virtual void CAknEdwinCustomDrawBase_Reserved_1();

private: // methods

    /**
    * Routine to group the common skin custom drawing
    *
    * @param aGc        Graphics context to use
    * @param aRect      Rectangle to draw in, in the GC's coords
    * @param aDrawnRect output declaring which rect was successfully drawn
    *
    * @return TBool EFalse iff the drawing was not performed
    */
    TBool DrawRectWithSkin( const CGraphicsContext& aGc, const TRect& aRect, TRect& aDrawnRect ) const;

    /**
    * Check if the text needs underline and return additional drawing information
    *
    * @param aText      Text being formatted in this chunk.
    * @param aParam     Information being passed to the base
    * @param aFormat    The format of the current chunk
    * @param aUnderlinePos  Position from the top of the ascender to put the underline
    */
    TBool TextNeedsCustomUnderline( 
        const TDesC& aText, const TParam& aParam, 
        const TCharFormat& aFormat, TInt& aUnderlinePos ) const;

    /**
    * Perform the drawing of the custom underline
    */
    void DrawUnderlineL(
        const TRect& aUnderlineRect, 
        const TParam& aParam,
        const TLineInfo& aLineInfo,
        const TCharFormat& aFormat,
        const TDesC& aText,
        const TPoint& aTextOrigin,
        TInt aExtraPixels) const;
    
    /**
    * Draw the text onto a rectangle situated where the underline of that text will be.
    * The resulting bitmap has a record of where the text's descenders will cross the underline 
    * rectangle
    */    
    void DrawDescendersOntoBitmap( 
        CGraphicsContext& aContext, 
        const TDesC& aText, 
        const TParam& aParam, 
        const TLineInfo& aLineInfo, 
        const TRect& aUnderlineRect, 
        TInt aExtraPixels ) const;
        
    /**
    * Routine to draw the underline, using a passed-in bitmap, onto which some text's descenders
    * have been drawn, to avoid the descenders that overlap the underline rectangle.
    */
    void DrawLineWithGaps( 
        const TParam& aParam, 
        CFbsBitmap& aUnderlineBitmap, 
        const TRect& aUnderlineRect  ) const;

    /**
    * Method to soak up actions performed during a single line segment draw
    */
    void DrawLineAndRecord(
        CGraphicsContext& aGc, 
        const TRect& aRect, 
        const TPoint& aAnchor,  
        TInt aColumn, 
        TInt aRow,
        TInt& aAccumulatedLength, 
        TInt& aSegmentsDrawn) const;
private: //member data
    const CEikEdwin& iEdwin;
    TBool iAppSkinEnabled; 
	CTextView* iTextView;
    CWindowGc* iSysGc;
    CAknPictographInterface* iPictographDrawer; // owned
    TInt iWsBufferRequestId;
	};

#endif
