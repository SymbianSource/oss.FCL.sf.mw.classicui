// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <coetextdrawer.h>
 
 
//
// class XCoeTextDrawer
//
const TInt KDefaultLineGap = 1;	


//
// class CCoeTextDrawerBaseExt 
//

/**
This extension block is used to to avoid BC breaks in adding to the
main data structures.
@internalComponent
*/
NONSHARABLE_CLASS(CCoeTextDrawerBaseExt) : public CBase
	{
public:
	static CCoeTextDrawerBaseExt* New();
	~CCoeTextDrawerBaseExt();	
	
	void SetAppLanguage(TLanguage aAppLang);
	TBidiText::TDirectionality DirectionalityToConsider(const TCoeTextTypeAdaptor& aText) const;
private:
	CCoeTextDrawerBaseExt();
	TInt	 Construct();	
private:
	enum TScriptDirectionality
		{
		EScriptDirUndefined,
		EScriptDirLeftToRight,
		EScriptDirRightToLeft
		};	
private:	
	TScriptDirectionality iAppScriptDirectionality;
	};

/**
Create a CCoeTextDrawerBaseExt object.
*/
CCoeTextDrawerBaseExt* CCoeTextDrawerBaseExt::New()
	{
	CCoeTextDrawerBaseExt* self = new CCoeTextDrawerBaseExt();
	if(self->Construct() != KErrNone)
		{
		delete self;
		self = NULL;
		}
		
	return self;
	}

/**
Constructor.
*/
CCoeTextDrawerBaseExt::CCoeTextDrawerBaseExt()
	{}

/**
Destructor.
*/
CCoeTextDrawerBaseExt::~CCoeTextDrawerBaseExt()
	{}

/**
Second-phase object construction.
*/	
TInt CCoeTextDrawerBaseExt::Construct()
//lint --e{1762} Suppress member function could be made const
	{
	return KErrNone;
	}

/**
Set the application language directionality based on the TLanguage passed as argument.
Passing ELangNone will set the application language directionality to "undefined".
*/	
void CCoeTextDrawerBaseExt::SetAppLanguage(TLanguage aAppLang)
	{
	if(aAppLang == ELangNone)
		iAppScriptDirectionality = EScriptDirUndefined;
	else if (TBidiText::ScriptDirectionality(aAppLang) == TBidiText::ELeftToRight)
		iAppScriptDirectionality = EScriptDirLeftToRight;
	else
		iAppScriptDirectionality = EScriptDirRightToLeft;
	}

/**
Return the language directionality to consider when deciding whether to swap left and right alignment
(for non-absolute horizontal alignment, left and right shall be swapped for scrips with RightToLeft 
directionality, such as Arabic).

If the application language has been set using SetAppLanguage(), the directionality of the languange that the
application is currently running in will be used. If not, the directionality of the actual text being printed
at the moment will be used.
*/	
TBidiText::TDirectionality CCoeTextDrawerBaseExt::DirectionalityToConsider(const TCoeTextTypeAdaptor& aText) const
	{		
	TBidiText::TDirectionality textDirectionality = TBidiText::ELeftToRight;
	if(iAppScriptDirectionality == EScriptDirRightToLeft)
		textDirectionality = TBidiText::ERightToLeft;
	else if(iAppScriptDirectionality == EScriptDirUndefined)
		textDirectionality = (aText.HasRightToLeftDirectionality() ? TBidiText::ERightToLeft : TBidiText::ELeftToRight);
	
	return textDirectionality;
	}
	
	
//
// Class XCoeTextDrawer
//


/**
Use this constructor to create a XCoeTextDrawer object on the stack, inside your control's
Draw() method. The XCoeTextDrawer object will work as a smart-pointer to the CCoeTextDrawerBase
object, managing its life. Get the CCoeTextDrawerBase-derived object to use by calling 
CCoeControl::TextDrawer(). Do not create a new CCoeTextDrawerBase-derived object inside the
Draw() method. If you want to change the text drawer used by the control or any of the control's
children, override the CCoeControl::GetTextDrawer() method. Inside it you can create a new 
CCoeTextDrawerBase object or change the properties of the CCoeTextDrawerBase object passed to it.
*/
EXPORT_C XCoeTextDrawer::XCoeTextDrawer(CCoeTextDrawerBase& aTextDrawer) 
	: iTextDrawer(&aTextDrawer) 
	{
	iClipRect = TRect();	
	}

	
/**
Destructor. The XCoeTextDrawer object work as a smart-pointer object to the CCoeTextDrawerBase
object actually performing the text drawing. The XCoeTextDrawer object shall be allocated on
the stack (i.e. not using "new") in the CCoeControl's Draw() method. Once the XCoeTextDrawer object 
goes out of scope, this destructor will be called. It will call Reset() on the CCoeTextDrawerBase
object, if it was been set to be resuable by its owner. If not, the CCoeTextDrawerBase object
will be deleted. Note that it is up to the creator/owner of the CCoeTextDrawerBase to decide 
whether it shall be reusable or not. A user of the XCoeTextDrawer must not change the re-use'ness
of the CCoeTextDrawerBase.
*/	
EXPORT_C XCoeTextDrawer::~XCoeTextDrawer()
	{
	if(iTextDrawer && iTextDrawer->IsReusable())
		iTextDrawer->Reset();
	else
		delete iTextDrawer;
	}
 
/**
Assignment operator for CCoeTextDrawerBase objects.

Due to compiler defect/feature, this method may not work.
I.e. if
<code> XCoeTextDrawer textDrawer = TextDrawer(); </code>
does not compile, restate as 
<code> XCoeTextDrawer textDrawer(TextDrawer()); </code>

@param aTextDrawer A text drawer.
*/
EXPORT_C void XCoeTextDrawer::operator=(CCoeTextDrawerBase& aTextDrawer)
	{
	// The currently owned CCoeTextDrawerBase object may be reusable and should just
	// be reset rather than deleted.
	if(iTextDrawer && iTextDrawer->IsReusable())
		iTextDrawer->Reset();
	else
		delete iTextDrawer;
	
	iTextDrawer = &aTextDrawer;
	} 	//lint !e1539 Suppress Member 'XCoeTextDrawer::iClipRect' not assigned by assignment operator

/**
Deprecated.
*/
EXPORT_C CCoeTextDrawerBase * XCoeTextDrawer::operator ->() 
	{	
 	return iTextDrawer;
 	}
 
/**
An XCoeTextDrawer object should not be copied as only one handle should exist to a CCoeTextDrawer.
Therefore this copy constructor is private and just contains a panic statement.
@internalComponent
*/
XCoeTextDrawer::XCoeTextDrawer(const XCoeTextDrawer& /*aTextDrawer*/)
	{  
	ASSERT(0);
	} //lint !e1744 Suppress Member 'XCoeTextDrawer::iTextDrawer' possibly not initialized by private constructor
	
/**
Call this method to draw text contained i a TBidiText object. This is the 
recommended way of drawing any widget text, as it will manage both left-to-right 
scripts like English as well as right-to-left scripts such as Arabic and Hebrew.

Before calling this method, be sure to set the text alignment, margins, clip rect, 
etc using the XCoeTextDrawer methods SetAlignment(), SetMargins(), and SetClipRect().

Note that before a TBidiText text can be drawn, it has to be line-broken using 
TBidiText::WrapText() with a wrap width that match the text rect minus margins.

@param aGc 			The graphics context.
@param aText 		TBidiText reference containing the text to be drawn.
@param aTextRect 	Rectangle text will be drawn in
@param aFont 		Font to be used.
*/
EXPORT_C void XCoeTextDrawer::DrawText(CGraphicsContext& aGc, const TBidiText& aText, const TRect& aTextRect, const CFont& aFont) const
	{
	ASSERT(iTextDrawer);
	iTextDrawer->DrawText(aGc, TCoeTextTypeAdaptor(aText), aFont, aTextRect, iClipRect);	
	}

/**
Call this method to draw vertical text contained in a TBidiText object. This is the 
recommended way of drawing any widget text, as it will manage both left-to-right 
scripts like English as well as right-to-left scripts such as Arabic and Hebrew.

Before calling this method, be sure to set the text alignment, margins, clip rect, 
etc using the XCoeTextDrawer methods SetAlignment(), SetMargins(), and SetClipRect().

Note that before a TBidiText text can be drawn, it has to be line-broken using 
TBidiText::WrapText() with a wrap width that match the text rect minus margins.

Also note that the margines are relative to the orientation of the text.

@param aGc 	    	The graphics context.
@param aText 		TBidiText reference containing the text to be drawn.
@param aTextRect 	Rectangle text will be drawn in
@param aFont 		Font to be used.
@param aUp 			ETrue, text is rotated 90 degrees anti-clockwise; EFalse, text is rotated 90 degrees clockwise.
@see 				XCoeTextDrawer::SetClipRect
*/
EXPORT_C void XCoeTextDrawer::DrawTextVertical(CGraphicsContext& aGc, const TBidiText& aText, const TRect& aTextRect, const CFont& aFont, TBool aUp) const
	{
	ASSERT(iTextDrawer);
	iTextDrawer->DrawTextVertical(aGc, TCoeTextTypeAdaptor(aText), aFont, aTextRect, iClipRect, aUp);	
	}

/**
Low level text drawing is always performed left-to-right on the screen. This 
means that for any script with right-to-left directionality (like Arabic), 
the in-memory order of the glyphs has to be changed (reordered) from the 
logical order (start of sentence first, before end of sentence) to the 
display order (end of sentence before (i.e. left of) start of sentence). 
This operation is performed by TBidiText.

However, sometimes text is reordered through some other means than the TBidiText 
class. In these cases, this method can be used to draw the text contained in a 
descriptor object in the same order (left-to-right) as it appears in the descriptor 
memory. I.e. this method assumes that the text has already been changed into the
display order. If this is not the case, and the text is in a right-to-left script,
it will come out backwards.

@param aGc 			The graphics context.
@param aText 		TDesC reference containing the text to be drawn.
@param aTextRect 	Rectangle text will be drawn in
@param aFont 		Font to be used.
*/
EXPORT_C void XCoeTextDrawer::DrawDisplayOrderedText(CGraphicsContext& aGc, const TDesC& aText, const TRect& aTextRect, const CFont& aFont) const
	{
	ASSERT(iTextDrawer);
	iTextDrawer->DrawText(aGc, aText, aFont, aTextRect, iClipRect);	
	}

/**
Low level text drawing is always performed left-to-right on the screen. This 
means that for any script with right-to-left directionality (like Arabic), 
the in-memory order of the glyphs has to be changed (reordered) from the 
logical order (start of sentence first, before end of sentence) to the 
display order (end of sentence before (i.e. left of) start of sentence). 
This operation is performed by TBidiText.

However, sometimes text is reordered through some other means than the TBidiText 
class. In these cases, this method can be used to draw the text contained in a 
descriptor object in the same order (left-to-right) as it appears in the descriptor 
memory. I.e. this method assumes that the text has already been changed into the
display order. If this is not the case, and the text is in a right-to-left script,
it will come out backwards.

Note that the margines are relative to the orientation of the text.

@param aGc 			The graphics context.
@param aText 		TDesC reference containing the text to be drawn.
@param aTextRect 	Rectangle text will be drawn in
@param aFont 		Font to be used.
*/
EXPORT_C void XCoeTextDrawer::DrawDisplayOrderedTextVertical(CGraphicsContext& aGc, const TDesC& aText, const TRect& aTextRect, const CFont& aFont, TBool aUp) const
	{
	ASSERT(iTextDrawer);
	iTextDrawer->DrawTextVertical(aGc, aText, aFont, aTextRect, iClipRect, aUp);	
	}

/**
Return the clip rect that will be used by DrawText() and DrawDisplayOrderedText().
Any text falling outside this rectangle will not be visible. This is used to crop text.

@return The clipping rect.
*/	
EXPORT_C TRect XCoeTextDrawer::ClipRect() const
	{
	return  iClipRect;
	}

/**
Set the clip rect that will be used by DrawText() and DrawDisplayOrderedText().
Any text falling outside this rectangle will not be visible. This is used to crop text.

@param aClipRect TRect value to set iClipRect to.  
*/		
EXPORT_C void XCoeTextDrawer::SetClipRect(const TRect& aClipRect)
	{
 	iClipRect = aClipRect;
	}


//
// class CCoeTextDrawerBase
//

/**
Constructor.
*/
EXPORT_C CCoeTextDrawerBase::CCoeTextDrawerBase()  
	{
	Reset();	// N.B. This will always call local implementation, never derived overrides
 	} //lint !e1506 Supress Call to virtual function 'Reset(void)' within constructor

/**
This method is called from the destructor of the XCoeTextDrawer object managing the
life of the CCoeTextDrawerBase object, if the CCoeTextDrawerBase object has been set
to be reusable (by its owner calling SetReusable()). 

Any derived class must override this method to reset its drawing parameters to their 
defaults, so that the object is ready to be used again. Any overriding implementation 
must call the base implementation as well.
*/	
EXPORT_C void CCoeTextDrawerBase::Reset() 
	{ 
 	// Don't change iIsReusable! 
    iAlignment = EHLeftVTop; 
    iMargins = TMargins8(); 
    iLineGap = KDefaultLineGap; 
	} 

/**
Destructor.
*/	
EXPORT_C CCoeTextDrawerBase::~CCoeTextDrawerBase()  
	{ 
  	delete iExtension;
	}

/**
Second phase object construction.
Note that this method is non-leaving as it may be called indirectly from a Draw() 
method, which must not leave.

@return returns KErrNone if successful, otherwise KErrNoMemory.
*/	
EXPORT_C TInt CCoeTextDrawerBase::Construct()
	{
	// allocate extension block
	iExtension = CCoeTextDrawerBaseExt::New();

	if (!iExtension)
		return KErrNoMemory;
	else
		return KErrNone;
	} 
	
/**
Unless absolute horizontal aligment has been selected (see TGulAlignment), the actual 
horizontal text alignment used when drawing text depends on whether the directionality 
of the scrip is left-to-right or right-to-left. In the latter case left and right 
is swapped. By default, the directionality of the actual text being drawn will define 
whether the horizontal alignment will be swapped or not. However, if (as recommended) the 
directionality of the application's main language shall be considered instead (rather 
than the directionality of the text being printed at the moment), then call this method. 

If ELangNone is specified, the text drawer will be reset to swap horizontal alignment 
depending on the directionality of the text being printed.

@param aAppLang The application language (e.g. from CEikonEnv::ApplicationLanguage()).
*/
EXPORT_C void CCoeTextDrawerBase::SetAppLanguage(TLanguage aAppLang)
	{
	if(iExtension)
		iExtension->SetAppLanguage(aAppLang);
	}

/**
This method returns the actual (absolute) horizontal text alignment to be used 
when drawing text in any CCoeTextDrawerBase-derived DrawText() implementation. 
The actual alignment depends on the application language directionality if the 
application language has been set calling CCoeTextDrawerBase::SetAppLanguage(), 
or otherwise on the directionality of the actual text being printed. If the 
directionality is right-to-left (and the horizontal alignment has not been set 
to be absolute, using TGulAlignment::SetAbsoluteHAlignment()), left and right 
alignment (set using XCoeTextDrawer::SetAlignment()) will be swapped.
*/
EXPORT_C TGulHAlignment CCoeTextDrawerBase::ActualHorizontalAlignment(const TCoeTextTypeAdaptor& aText) const
	{
	if(iAlignment.HasAbsoluteHAlignment())
		return iAlignment.HAlignment();
	
	if(iExtension)
		{
		const TBidiText::TDirectionality directionalityToConsider = iExtension->DirectionalityToConsider(aText);
		return iAlignment.HAlignment(directionalityToConsider);
		}
	else
		return iAlignment.HAlignment();
	}
		
// Accessor/Set Methods

/**
Returns whether the CCoeTextDrawerBase-derived text drawer object has been set 
to be reusable or not. If reusable, the text drawer is assumed to have an owner 
that will delete it when appropriate. If not reusable, the XCoeTextDrawer will 
delete it in its destructor.

@return bool value of iIsReusable data member
*/			
EXPORT_C TBool CCoeTextDrawerBase::IsReusable() const
	{
	return iIsReusable;
	}

/**
Set whether the text drawer is reusable or not. A reusable text drawer will be
reset (through a call to Reset()) rather than deleted when the XCoeTextDrawer
referring to it is deleted. This decision has to be made by the creator of the 
CCoeTextDrawerBase object. I.e. this method must not be called by a mere user 
of the XCoeTextDrawer.

@param aIsReusable Boolean indicating whether the text drawer can be re-used.
*/	
EXPORT_C void CCoeTextDrawerBase::SetReusable(TBool aIsReusable)
	{
	iIsReusable = aIsReusable;
	}

/**
Returns the text alignment that will be used by DrawText() and DrawDisplayOrderedText().
Note that left and right alignment will be swapped for right-to-left scripts, unless
the alignment has been set to be absolute (see TGulAlignment).

A typical user of the text drawer mechanism will use the XCoeTextDrawer version of this API.

@return TGulAlignment value of iAlignment data member
*/	
EXPORT_C TGulAlignment CCoeTextDrawerBase::Alignment() const
	{
	return  iAlignment;
	}

/**
Set the text alignment that will be used by DrawText() and DrawDisplayOrderedText().
Note that left and right alignment will be swapped for right-to-left scripts, unless
the alignment has been set to be absolute (see TGulAlignment).

A typical user of the text drawer mechanism will use the XCoeTextDrawer version of this API.

@param aAlignment TGulAlignment value.  
*/		
EXPORT_C void CCoeTextDrawerBase::SetAlignment(const TGulAlignment& aAlignment)
	{
	iAlignment = aAlignment;
	}
	
/**
Returns the text margins that will be used by DrawText() and DrawDisplayOrderedText().

A typical user of the text drawer mechanism will use the XCoeTextDrawer version of this API.

@return The margins between the text rect and the actual text, in pixels.
*/	
EXPORT_C TMargins8 CCoeTextDrawerBase::Margins() const
	{
	return iMargins;
	}

/**
Set the text margins that will be used by DrawText() and DrawDisplayOrderedText().

A typical user of the text drawer mechanism will use the XCoeTextDrawer version of this API.

@param aMargins The margins between the text rect and the actual text, in pixels.
*/		
EXPORT_C void CCoeTextDrawerBase::SetMargins(const TMargins8& aMargins)
	{
 	iMargins = aMargins;
	}

/**
Returns the gap (in pixels) between lines of text. Default gap is 1 (one) pixel.

A typical user of the text drawer mechanism will use the XCoeTextDrawer version of this API.

@return The gap between lines of text, in pixels.
*/	
EXPORT_C TInt CCoeTextDrawerBase::LineGapInPixels() const
	{
	return iLineGap;
	}

/**
Set the gap (in pixels) between lines of text. Default gap is 1 (one) pixel.

A typical user of the text drawer mechanism will use the XCoeTextDrawer version of this API.

@param aLineGapInPixels The gap between lines of text, in pixels.
*/			
EXPORT_C void CCoeTextDrawerBase::SetLineGapInPixels(TInt aLineGapInPixels)
	{
 	iLineGap = aLineGapInPixels;
	}

/**
Any text drawer implementation must override this method, returning the "margins" 
that the text effect will add to the text extent. I.e. a one-pixel drop-shadow
to the lower right will add an effect margin of TMargins8(0,0,1,1), while a 
one-pixel all-around outline will add an effect margin of TMargins8(1,1,1,1).
*/
EXPORT_C TMargins8 CCoeTextDrawerBase::EffectMargins()
	{
	return TMargins8();
	}

/**
Draws the vertical text provided as parameter.

@param aGc The graphics context.
@param aText The TCoeTextTypeAdaptor text object to draw. 
@param aFont Font to be used for drawing the text.
@param aTextRect The rectangle to draw the text in.
@param aClipRect The clipping rectangle.
@param aUp ETrue, text is rotated 90 degrees anti-clockwise; EFalse, text is rotated 90 degrees clockwise.
*/
EXPORT_C void CCoeTextDrawerBase::DrawTextVertical(CGraphicsContext& aGc, const TCoeTextTypeAdaptor& aText, const CFont& aFont, 
			const TRect& aTextRect, const TRect& aClipRect, TBool aUp) const
	{
    const TInt lineSpacing = aFont.FontMaxHeight() +  LineGapInPixels();
	const TInt textHeightInPixels = (aText.NumberOfLines() * lineSpacing) -  LineGapInPixels(); // Center the ascent
	
	// Calculate the text's "left point", i.e. the point on the baseline where the text starts
	TPoint leftPoint =  Margins().InnerRect(aTextRect).iTl + TPoint(0,aFont.FontMaxAscent());
	const TInt deltaHeight = aTextRect.Width() - Margins().SizeDelta().iHeight - textHeightInPixels;
	if (deltaHeight > 0)
		{
		switch(Alignment().VAlignment())
			{
			case EVTop:
				break;
			case EVBottom:
				leftPoint.iY +=  deltaHeight;
				break;
			case EVCenter:
				leftPoint.iY +=  deltaHeight >> 1;
				break;
			}
		}

	// Set up the GC
	aGc.UseFont(&aFont);
	aGc.SetBrushStyle(CBitmapContext::ENullBrush);
	aGc.SetPenStyle(CBitmapContext::ESolidPen);
	aGc.SetPenColor(TextColor());
	
	// Compensate textRect for ClipRect
   	TRect textRect = aTextRect;
    if(!(aClipRect.IsEmpty()) && aClipRect != aTextRect)
    	{   	
    	textRect.Intersection(aClipRect);
    	}
   
	// Use leftMargin and baseline to position each text line correctly, 
	// taking margins, alignment, and line spacing into account
	TInt baseline = leftPoint.iY - textRect.iTl.iY;
	
	// Draw the lines
	const TInt lines = lineSpacing == 0 ? 1 : aText.NumberOfLines();
	const TGulHAlignment actualHorizontalAlignment = ActualHorizontalAlignment(aText);
	for (TInt i = 0; i < lines; ++i)
		{
		TInt width = 0;
		TPtrC textLine = aText.LineOfText(i, width, aFont);
		TInt margin = leftPoint.iX - textRect.iTl.iX;
		 if (actualHorizontalAlignment != EHLeft)
			{
			const TInt wrapWidth = aTextRect.Height() -  Margins().SizeDelta().iWidth;
			const TInt excess = wrapWidth - width;
			margin += actualHorizontalAlignment != EHCenter ? excess : excess >> 1;	
			}
		aGc.DrawTextVertical(textLine, textRect, baseline, aUp, CGraphicsContext::ELeft, margin);
		baseline += lineSpacing;
		}
	
	aGc.DiscardFont();	
	}

// For future use	
/** @internalComponent */
EXPORT_C void CCoeTextDrawerBase::CCoeTextDrawerBase_Reserved3() { }
/** @internalComponent */
EXPORT_C void CCoeTextDrawerBase::CCoeTextDrawerBase_Reserved4() { }
/** @internalComponent */
EXPORT_C void CCoeTextDrawerBase::CCoeTextDrawerBase_Reserved5() { }
/** @internalComponent */
EXPORT_C void CCoeTextDrawerBase::CCoeTextDrawerBase_Reserved6() { }
/** @internalComponent */
EXPORT_C void CCoeTextDrawerBase::CCoeTextDrawerBase_Reserved7() { }
/** @internalComponent */
EXPORT_C void CCoeTextDrawerBase::CCoeTextDrawerBase_Reserved8() { }
/** @internalComponent */
EXPORT_C void CCoeTextDrawerBase::CCoeTextDrawerBase_Reserved9() { }
/** @internalComponent */
EXPORT_C void CCoeTextDrawerBase::CCoeTextDrawerBase_Reserved10() { }
 


// 
// class CCoePlainTextDrawer
//

/**
Created a new plain text drawer on the heap. This shall typically be done in the
CCoeControl::GetTextDrawer() method, or better, in the constructor of the owner
of the text drawer.

Do not call this method from within a CCoeControl::Draw() method. If all you want
is access to a text drawer, call CCoeControl::TextDrawer().

@param aTextColor The color that will be used to draw text.
@return A new CCoePlainTextDrawer instance or null if the creation of a new instance failed.
*/
EXPORT_C CCoePlainTextDrawer* CCoePlainTextDrawer::New(TRgb aTextColor)
	{
	CCoePlainTextDrawer* self = new  CCoePlainTextDrawer(aTextColor);

 	if(self && self->Construct() == KErrNone)
 		return self;	// Successful allocation
	else 
		{
		delete self;
		return NULL;	// Error in allocation
		}
	}

/**
Second-phase construction. This method is non-leaving as it will have been called indirectly 
from a control's draw method which cannot leave.
@return KErrNone if the function executed without errors, any other standard error code if the
function failed.
*/	
TInt CCoePlainTextDrawer::Construct()
	{
	return CCoeTextDrawerBase::Construct();	
	//lint --e{1762} Suppress member function could be made const
	}

/**
See CCoeTextDrawerBase::TextColor().

@see CCoeTextDrawerBase
*/	
EXPORT_C TRgb CCoePlainTextDrawer::TextColor() const
	{
	return iTextColor;
	}

/**
See CCoeTextDrawerBase::SetTextColor().

@see CCoeTextDrawerBase
*/	
EXPORT_C void CCoePlainTextDrawer::SetTextColor(TRgb aTextColor)
	{
	iTextColor = aTextColor;
	}
	
/**
Constructor.
*/	
CCoePlainTextDrawer::CCoePlainTextDrawer(TRgb aTextColor) : 
	iTextColor(aTextColor)
	{
	}

/**
This function is defined by the MObjectProvider class. 
It allows the actual type of text drawer to be identified.

@param aId The type of the desired object.
@return A pointer to an object.
@see MObjectProvider
*/
EXPORT_C TTypeUid::Ptr CCoePlainTextDrawer::MopSupplyObject(TTypeUid aId)
	{
	if (aId.iUid == ETypeId)
		return aId.MakePtr(this);
	else
		return TTypeUid::Null();
	}

/**
See CCoeTextDrawerBase::Reset().
*/
void CCoePlainTextDrawer::Reset()
	{
	CCoeTextDrawerBase::Reset();
	iTextColor = KRgbBlack;
	}

/**
Draws the text provided as parameter.

@param aGc The graphics context.
@param aText The TCoeTextTypeAdaptor text object to draw. 
@param aFont Font to be used for drawing the text.
@param aTextRect The rectangle to draw the text in.
@param aClipRect The clipping rectangle.

@return void
@see CCoeTextDrawerBase
*/
void CCoePlainTextDrawer::DrawText(CGraphicsContext& aGc, const TCoeTextTypeAdaptor& aText, const CFont& aFont, 
			const TRect& aTextRect, const TRect& aClipRect) const
	{
	const TInt lineSpacing = aFont.FontMaxHeight() +  LineGapInPixels();
	const TInt textHeightInPixels = (aText.NumberOfLines() * lineSpacing) -  LineGapInPixels(); // Center the ascent
	
	// Calculate the text's "left point", i.e. the point on the baseline where the text starts
	TPoint leftPoint =  Margins().InnerRect(aTextRect).iTl + TPoint(0,aFont.FontMaxAscent());
	const TInt deltaHeight = Margins().InnerRect(aTextRect).Height() - textHeightInPixels;
	if (deltaHeight > 0)
		{
		switch(Alignment().VAlignment())
			{
			case EVTop:
				break;
			case EVBottom:
				leftPoint.iY += deltaHeight;
				break;
			case EVCenter:
				leftPoint.iY += (deltaHeight >> 1);	// /2
				break;
			}
		}

	// Set up the GC
	aGc.UseFont(&aFont);
	aGc.SetBrushStyle(CBitmapContext::ENullBrush);
	aGc.SetPenStyle(CBitmapContext::ESolidPen);
	aGc.SetPenColor(iTextColor);		

	// Compensate textRect for ClipRect
    TRect textRect = aTextRect;
    if(!(aClipRect.IsEmpty()))
    	textRect.Intersection(aClipRect);
    
	// Use leftMargin and baseline to position each text line correctly, 
	// taking margins, alignment, and line spacing into account
	TInt baseline = leftPoint.iY - textRect.iTl.iY;
	
	const TGulHAlignment actualHorizontalAlignment = ActualHorizontalAlignment(aText);
	
	// Draw the lines
	const TInt lines = lineSpacing == 0 ? 1 : aText.NumberOfLines();
	for (TInt i = 0; i < lines; ++i)
		{
		TInt width = 0;
		TPtrC textLine = aText.LineOfText(i, width, aFont);
		TInt leftMargin = leftPoint.iX - textRect.iTl.iX;
		if (actualHorizontalAlignment != EHLeft)
			{
			const TInt wrapWidth = aTextRect.Width() -  Margins().SizeDelta().iWidth;
			const TInt excess = wrapWidth - width;
			leftMargin += actualHorizontalAlignment != EHCenter ? excess : excess >> 1;
			}
			
		aGc.DrawText(textLine, textRect, baseline, CGraphicsContext::ELeft, leftMargin);
		baseline += lineSpacing;
		}

	aGc.DiscardFont();	
	}

//
// TCoeTextTypeAdaptor
//

/**
Constructor taking a plain descriptor as parameter. The directionality of the text separated with '\n'
must always be left-to-right display order.
@param aText The text wrapped by the TCoeTextTypeAdaptor.
*/
EXPORT_C TCoeTextTypeAdaptor::TCoeTextTypeAdaptor(const TDesC& aText)	// text separated with '\n'
	{
	iTextType = ENewlineSeparated;
	iText = static_cast<const void*>(&aText);
	}

/**
Constructor taking a TBidiText object as parameter.
@param aText The text wrapped by the TCoeTextTypeAdaptor.
*/	
EXPORT_C TCoeTextTypeAdaptor::TCoeTextTypeAdaptor(const TBidiText& aText)	// TBidiText object
	{
	iTextType = EBidiText;
	iText = &aText;
	}

const TText KCharacterLF = 0x0a;

const TText* FindEndOfThisLine(const TText* aStart, const TText* aEnd)
	{
	while (aStart != aEnd && *aStart != KCharacterLF)
		++aStart;

	return aStart;	
	}


/**
Calculates the number of lines in the text.
@return TInt number of lines in the object
*/	
EXPORT_C TInt TCoeTextTypeAdaptor::NumberOfLines() const
	{
	switch(iTextType)
		{
		case ENewlineSeparated:
			{
			const TText* startText = static_cast<const TDesC*>(iText)->Ptr();
			const TInt length = static_cast<const TDesC*>(iText)->Length();
			const TText* endText = startText + length; 
			
			TInt num = 0;
			while (startText < endText)
				{
				startText = FindEndOfThisLine(startText, endText);
				if (*startText == KCharacterLF && startText < endText)
					{
					++startText;
					}
				++num;
				}
			return num;
			}
		case EBidiText:
			return static_cast<const TBidiText*>(iText)->NumberOfLinesInDisplayText();
		default:
			return 0;
		}
	}

/**
Extracts a line of text. The width (in pixels) of the line is returned in aWidthInPixels.
@param  aLineNumber Zero-based line number.
@param  aWidthInPixels The width of the line of text.
@param  aFont The font that will be used to draw the text.
@return TPtrC line of text
*/	
EXPORT_C TPtrC TCoeTextTypeAdaptor::LineOfText(TInt aLineNumber, TInt& aWidthInPixels, const CFont& aFont) const
	{
	switch(iTextType)
		{
		case ENewlineSeparated:
			{
			const TText* startText = static_cast<const TDesC*>(iText)->Ptr();
			const TInt length = static_cast<const TDesC*>(iText)->Length();
			const TText* endText = startText + length; 

			for (; aLineNumber != 0; --aLineNumber)
				{
				startText = FindEndOfThisLine(startText, endText);
				if (*startText == KCharacterLF)
					++startText;
				}
			const TText* endOfLine = FindEndOfThisLine(startText, endText);
			TPtrC textInLineNumber(startText, endOfLine - startText);
			// Calculate the width of the line according to the font used.
			aWidthInPixels = aFont.TextWidthInPixels(textInLineNumber);
			return textInLineNumber;
			}
		case EBidiText:
			return static_cast<const TBidiText*>(iText)->LineOfDisplayText(aLineNumber, aWidthInPixels);
		default:
			return KNullDesC();
		}
	}

/**
This function checks the directionality of the text.
@return ETrue if the text has right-to-left directionality, EFalse if it has left-to-right directionality.
*/
EXPORT_C TBool TCoeTextTypeAdaptor::HasRightToLeftDirectionality() const
	{
	switch(iTextType)
		{
		case EBidiText:
			return (static_cast<const TBidiText*>(iText)->Directionality() == TBidiText::ERightToLeft);
		default:
			return EFalse;
		}
	}
