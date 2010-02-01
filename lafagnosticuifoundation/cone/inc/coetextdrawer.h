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

#ifndef __COETEXTDRAWER_H__
#define __COETEXTDRAWER_H__

#include <gulutil.h>	 
#include <gulalign.h>	 
#include <biditext.h>
#include <coemop.h>

//
// TEXT DRAWER CODE
//

// forward declarations
class CCoeTextDrawerBase;
class TCoeTextTypeAdaptor;

/**
This class serves as a smart-pointer handle to a CCoeTextDrawerBase-derived object, used for drawing
user interface text. Through the use of the CCoeControl's TextDrawer() and GetTextDrawer() methods, a
container control can control the text style and color used by its child controls. For example, a button
class can override its GetTextDrawer() method to set the text color used by its text label child control 
depending on the buttons state (e.g. unpressed, pressed, or dimmed).

The XCoeTextDrawer object manages the life of the heap allocated CCoeTextDrawerBase (deleting it or 
resetting it depending on whether the object is reusable or not).

XCoeTextDrawer objects shall be allocated on the stack in the control's Draw() method and initialized 
with a heap allocated CCoeTextDrawerBase object fetched from the control's skin, or from its parent or 
background through the CCoeControl::TextDrawer() method. 

Never create a CCoeTextDrawer-derived object inside your CCoeControl::Draw() method, as this is not 
guaranteed to work in low-memory situations. Non-reusable text drawers must only be created in your
control's GetTextDrawer() method, as this provides error handling in case the text drawer could not be 
created.

Hence, typical use from inside a CCoeControl's Draw() method:
<code>
XCoeTextDrawer textDrawer(TextDrawer());
textDrawer.SetAlignment(EHLeftVCenter);
textDrawer.SetMargins(iTextMargins);
textDrawer.DrawText(SystemGc(), *iText, iTextRect, ScreenFont(TCoeFont::NormalFont()));
</code>

@publishedAll
@released
*/
class XCoeTextDrawer
	{
public:
	IMPORT_C XCoeTextDrawer(CCoeTextDrawerBase& aTextDrawer);
	IMPORT_C ~XCoeTextDrawer();
	
	IMPORT_C void operator=(CCoeTextDrawerBase& aTextDrawer);

	IMPORT_C void DrawText(CGraphicsContext& aGc, const TBidiText& aText, const TRect& aTextRect, const CFont& aFont) const;
	IMPORT_C void DrawDisplayOrderedText(CGraphicsContext& aGc, const TDesC& aText, const TRect& aTextRect, const CFont& aFont) const;
	
	IMPORT_C void DrawTextVertical(CGraphicsContext& aGc, const TBidiText& aText, const TRect& aTextRect, const CFont& aFont, TBool aUp = ETrue) const;
	IMPORT_C void DrawDisplayOrderedTextVertical(CGraphicsContext& aGc, const TDesC& aText, const TRect& aTextRect, const CFont& aFont, TBool aUp = ETrue) const;
	
	IMPORT_C TRect ClipRect() const;
	IMPORT_C void SetClipRect(const TRect& aClipRect);

	inline TRgb TextColor() const;
	inline void SetTextColor(TRgb aColor);
	
	inline TGulAlignment Alignment() const;
	inline void SetAlignment(const TGulAlignment& aAlignment);
	
	inline TMargins8 Margins() const;
	inline void SetMargins(const TMargins8& aMargins);
	
	inline TInt LineGapInPixels() const;
	inline void SetLineGapInPixels(TInt aLineGapInPixels);	
public: 
	IMPORT_C CCoeTextDrawerBase *operator ->();		// deprecated	
private:
	XCoeTextDrawer(const XCoeTextDrawer& aTextDrawer);  
private:	
	CCoeTextDrawerBase* iTextDrawer;
	TRect iClipRect;
	};


// forward declaration
class CCoeTextDrawerBaseExt;

/**
This is the base class for all text drawers implementing different text effects (for example 
shadow or glowing/outlined text). The object can be created and deleted each time it's used, 
or Reset() and reused if it IsReusable(). The latter is recommended.

Note that the pure virtual DrawText() method is private. This ensures that the object is used 
through the XCoeTextDrawer class (which manages its life). 

Note also that the accessor and set methods should be used via the owning XCoeTextDrawer object,
and that the MObjectProvider mechanism can be used to identify the actual text drawer implementation.

@publishedAll
@released
*/
class CCoeTextDrawerBase : public CBase, public MObjectProvider
	{
	friend class XCoeTextDrawer;   
public:
	IMPORT_C ~CCoeTextDrawerBase();
	IMPORT_C virtual void Reset();

	/**
	This method returns the main color used by the CCoeTextDrawer to draw text.
	@return The color used to draw text.
	*/
	virtual TRgb TextColor() const = 0;
	/**
	This method sets the main color to use to draw text.
	@param aColor The color to use to draw text.
	*/
	virtual void SetTextColor(TRgb aColor) = 0;
 
	IMPORT_C TGulAlignment Alignment() const;
	IMPORT_C void SetAlignment(const TGulAlignment& aAlignment);
	
	IMPORT_C TMargins8 Margins() const;
	IMPORT_C void SetMargins(const TMargins8& aMargins);
	
	IMPORT_C TInt LineGapInPixels() const;
	IMPORT_C void SetLineGapInPixels(TInt aLineGapInPixels);
public:	// public methods only for use by the owner/creator of the CCoeTextDrawerBase-derived object
 	IMPORT_C TBool IsReusable() const;
	IMPORT_C void SetReusable(TBool aIsReusable);
	
	IMPORT_C void SetAppLanguage(TLanguage aAppLang);
protected:
 	IMPORT_C CCoeTextDrawerBase();
	IMPORT_C TInt Construct();
	IMPORT_C TGulHAlignment ActualHorizontalAlignment(const TCoeTextTypeAdaptor& aText) const;
private:  
	/**
	Any actual text drawer must implement this method to draw the text passed as argument.
	The implementation must draw the text inside the text rectangle, cropped to the clipping
	rectangle, and with the given margins and alignment taken into account.
	
	Note that the actual horizontal alignment shall depend on the script directionality. 
	Calling	ActualHorizontalAlignment() will return the horizontal alignment where left and 
	right has been swapped for right-to-left scripts.
	*/
	virtual void DrawText(CGraphicsContext& aGc, const TCoeTextTypeAdaptor& aText, const CFont& aFont, 
							const TRect& aTextRect, const TRect& aClipRect) const = 0;
public:
	IMPORT_C virtual TMargins8 EffectMargins();
private:
	/**
	Draws the text vertically inside the text rectangle, cropped to the clipping
	rectangle, and with the given margins and alignment taken into account.
	If aUp is ETrue, text is rotated 90 degrees anti-clockwise; EFalse, text is rotated 90 degrees clockwise.
	
	Note that the actual horizontal alignment shall depend on the script directionality. 
	Calling	ActualHorizontalAlignment() will return the horizontal alignment where left and 
	right has been swapped for right-to-left scripts.
	Also note that the margines are relative to the orientation of the text.
	*/
	IMPORT_C virtual void DrawTextVertical(CGraphicsContext& aGc, const TCoeTextTypeAdaptor& aText, const CFont& aFont, 
							const TRect& aTextRect, const TRect& aClipRect, TBool aUp) const;
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved3();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved4();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved5();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved6();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved7();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved8();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved9();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved10();
 private:
	TBool iIsReusable;	 
	TGulAlignment iAlignment;
	TMargins8 iMargins;
	TInt iLineGap;
	CCoeTextDrawerBaseExt* iExtension;
	};


/**
This class allows the XCoeTextDrawer to draw text that is in the form of a TBidiText 
object as well as pre-reordered new-line separated plain text descriptors. (The descriptor 
text is especially useful when using the XCoeTextDrawer together with the FORM component). 

This removes the need to implement two versions of the DrawText() method.

@publishedAll
@released
*/
class TCoeTextTypeAdaptor
	{
public:
	IMPORT_C TCoeTextTypeAdaptor(const TDesC& aText);		// text lines separated with '\n'
	IMPORT_C TCoeTextTypeAdaptor(const TBidiText& aText);	// TBidiText object
	IMPORT_C TInt NumberOfLines() const;
	IMPORT_C TPtrC LineOfText(TInt aLineNumber, TInt& aWidthInPixels, const CFont& aFont) const;	
	IMPORT_C TBool HasRightToLeftDirectionality() const;
private:
	enum TTextType
		{
		ENewlineSeparated,
		EBidiText
		};
	const TAny* iText;
	TTextType iTextType;
	};


/**	
This is a basic text drawer without any text effects. The default text drawer that can be 
used if no other (device specific) text drawers has been added to the system. 

@publishedAll
@released
*/
class CCoePlainTextDrawer : public CCoeTextDrawerBase
	{
public:
	DECLARE_TYPE_ID(0x1020831A)
public:
	IMPORT_C static CCoePlainTextDrawer* New(TRgb aTextColor);
	
	IMPORT_C TRgb TextColor() const;
	IMPORT_C void SetTextColor(TRgb aTextColor);
protected: // from MObjectProvider
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:  
	void DrawText(CGraphicsContext& aGc, const TCoeTextTypeAdaptor& aText, const CFont& aFont, 
					const TRect& aTextRect, const TRect& aClipRect) const;
	void Reset();	
	CCoePlainTextDrawer(TRgb aTextColor);
	TInt Construct();	//lint !e1511 Suppress member hides non-virtual member
private:	
	TRgb iTextColor;
	};
	


// Inlines		

/**
This method returns the main color used by by DrawText() and DrawDisplayOrderedText().
@return The color used to draw text.
*/
TRgb XCoeTextDrawer::TextColor() const
	{ return iTextDrawer->TextColor(); }
	
/**
This method sets the main color to use by DrawText() and DrawDisplayOrderedText() to draw text.
@param aColor The color to use to draw text.
*/
void XCoeTextDrawer::SetTextColor(TRgb aColor)
	{ iTextDrawer->SetTextColor(aColor); }

/**
Returns the text alignment that will be used by DrawText() and DrawDisplayOrderedText().
Note that left and right alignment will be swapped for right-to-left scripts, unless
the alignment has been set to be absolute (see TGulAlignment).

@return TGulAlignment value of iAlignment data member
*/
TGulAlignment XCoeTextDrawer::Alignment() const
	{ return iTextDrawer->Alignment(); }

/**
Set the text alignment that will be used by DrawText() and DrawDisplayOrderedText().
Note that left and right alignment will be swapped for right-to-left scripts, unless
the alignment has been set to be absolute (see TGulAlignment).

@param aAlignment TGulAlignment value.  
*/		
void XCoeTextDrawer::SetAlignment(const TGulAlignment& aAlignment)
	{ iTextDrawer->SetAlignment(aAlignment); }

/**
Returns the text margins that will be used by DrawText() and DrawDisplayOrderedText().
Note that text effects may intrude on the margin.

@return The margins between the text rect and the actual text, in pixels.
*/	
TMargins8 XCoeTextDrawer::Margins() const
	{ return iTextDrawer->Margins(); }

/**
Set the text margins that will be used by DrawText() and DrawDisplayOrderedText().
Note that text effects may intrude on the margin, and that margins are always relative to the text orientation. 

@param aMargins The margins between the text rect and the actual text, in pixels.
*/		
void XCoeTextDrawer::SetMargins(const TMargins8& aMargins)
	{ iTextDrawer->SetMargins(aMargins); }
	
/**
Returns the gap (in pixels) between lines of text. Default gap is 1 (one) pixel.
@return The gap between lines of text, in pixels.
*/	
TInt XCoeTextDrawer::LineGapInPixels() const
	{ return iTextDrawer->LineGapInPixels(); }
	
/**
Set the gap (in pixels) between lines of text. Default gap is 1 (one) pixel.
@param aLineGapInPixels The gap between lines of text, in pixels.
*/			
void XCoeTextDrawer::SetLineGapInPixels(TInt aLineGapInPixels)
	{ iTextDrawer->SetLineGapInPixels(aLineGapInPixels); }

		
#endif	// __COETEXTDRAWER_H__
