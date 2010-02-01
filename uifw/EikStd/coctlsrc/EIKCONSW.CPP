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


#include <e32base.h>
#include <gdi.h>
#include <coecntrl.h>
#include <coemain.h>
#include <eikconso.h>	// #include's eiksbfrm.h
#include <eikenv.h>
#include <barsread.h>
#include <aknpriv.rsg>


void cutmax(TInt &x,TInt max);

///////////////////////////////////////////////////////////////////////////////////////////////////////
// UpdateScrollBarsL()
// ===================
// Updates the thumb positions etc. on the scrollbars.
// Should be called whenever the datasize, visiblesize or position on the scrollbars have changed.
// RETURNS ETrue IF ANY SCROLLBARS (DIS)APPEARED
///////////////////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C TBool CEikConsoleControl::UpdateScrollbarsL(const TSize &aDataSize,const TSize& aVisibleSize,TPoint aPos)
	{
	// complete available area in characters
	TSize viewInChars( iSize.iWidth / iCharSize.iWidth, iSize.iHeight / iCharSize.iHeight );
	
	// remember for next time
	iLastThumbPos = aPos;
	TEikScrollBarModel vModel;
	TEikScrollBarModel hModel;
	if (iVBarVisibility!=CEikScrollBarFrame::EOff) 
		{
		// Vertical
		vModel.iScrollSpan=aDataSize.iHeight;
		if ( viewInChars.iHeight > aVisibleSize.iHeight )
			vModel.iThumbSpan=aVisibleSize.iHeight;
		else
			vModel.iThumbSpan=viewInChars.iHeight;
		vModel.iThumbPosition=aPos.iY;
		}
	if (iHBarVisibility!=CEikScrollBarFrame::EOff) 
		{
		// Horizontal
		hModel.iScrollSpan=aDataSize.iWidth;
		if ( viewInChars.iWidth > aVisibleSize.iWidth )
			hModel.iThumbSpan=aVisibleSize.iWidth;
		else
			hModel.iThumbSpan=viewInChars.iWidth;
		hModel.iThumbPosition=aPos.iX;
		}
	TRect fullRect(iSize);
	TRect clientRect(iViewInPixels);
	TEikScrollBarFrameLayout layout;
	CreateScrollBarFrameLayout(layout);
	if (iSBFrame->TileL(&hModel,&vModel,clientRect,fullRect,layout))
		{
		// something happened, so redetermine the available pixels...
		iViewInPixels=clientRect.Size();
		// the visible characters...
//	zoe
		iViewInChars = TSize( iViewInPixels.iWidth / iCharSize.iWidth, iViewInPixels.iHeight / iCharSize.iHeight );
		if (iConsole)
			{
			cutmax(iViewInChars.iWidth,iConsole->ScreenSize().iWidth);
			cutmax(iViewInChars.iHeight,iConsole->ScreenSize().iHeight);
			}
		// and clear what's outside the new scope...
		TPoint br(iViewInChars.iWidth*iCharSize.iWidth, iViewInChars.iHeight*iCharSize.iHeight);
		const TRgb background=iEikonEnv->ControlColor(EColorControlBackground,*this);
		ClearPixels(TRect(br.iX,0,iViewInPixels.iWidth,br.iY),background);
		ClearPixels(TRect(0,br.iY,iViewInPixels.iWidth,iViewInPixels.iHeight),background);
		// and inform caller that the area has changed...
		return ETrue;
		}
	return EFalse;
	}

void CEikConsoleControl::CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const
	{
	// all margins default to 0
	aLayout.iTilingMode=TEikScrollBarFrameLayout::EInclusiveRectConstant;
	aLayout.iClientAreaGranularity=iCharSize;
	}


EXPORT_C void CEikConsoleControl::UpdateArea()
	{
	// determine how many characters will fit and how many pixels we thus ACTUALLY need
//zoe
	iViewInChars = TSize( iViewInPixels.iWidth / iCharSize.iWidth, iViewInPixels.iHeight / iCharSize.iHeight );
	if (iConsole)
		{
		cutmax(iViewInChars.iWidth,iConsole->ScreenSize().iWidth);
		cutmax(iViewInChars.iHeight,iConsole->ScreenSize().iHeight);
		}
	// clear the area and redraw
	const TRgb background=iEikonEnv->ControlColor(EColorControlBackground,*this);
	ClearPixels(iViewInPixels,background);
	if (iConsole)
		iConsole->Redraw(PixelsToChars(TRect(iViewInPixels)));
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// HandleScrollEventL()
// ====================
// Called when someone "touches the scrollbar".
// Note that it calls back the owner (a CEikConsoleScreen) to do any real action
// (specifically, it calls MoveTopLeft(), passing it the required move as a vector)
///////////////////////////////////////////////////////////////////////////////////////////////////////
EXPORT_C void CEikConsoleControl::HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType)
	{
	TInt newThumbPos = aScrollBar->ThumbPosition();
	TInt pageSize = aScrollBar->Model()->iThumbSpan;
	const TInt horizontalNudgeFactor = 1;
	switch (aEventType & KEikScrollEventBarMask)
		{
		case KEikScrollEventFromHBar:
			switch (aEventType)
				{
				default:
					break;
				case EEikScrollLeft:
					newThumbPos -= horizontalNudgeFactor;
					break;
				case EEikScrollRight:
					newThumbPos += horizontalNudgeFactor;
					break;
				case EEikScrollPageLeft:
					newThumbPos -= pageSize;
					break;
				case EEikScrollPageRight:
					newThumbPos += pageSize;
					break;
				case EEikScrollThumbDragVert:
				case EEikScrollThumbReleaseVert:
					// in the case of drag events, the scrollbar automatically updates its thumb pos...
					break;
				}
			iConsole->MoveTopLeft(TPoint(newThumbPos - iLastThumbPos.iX,0));
			if (aEventType != EEikScrollThumbDragHoriz)
				aScrollBar->SetModelThumbPosition(newThumbPos);
			break;
		case KEikScrollEventFromVBar:
			switch (aEventType)
				{
				default:
					break;
				case EEikScrollUp:
					--newThumbPos;
					break;
				case EEikScrollDown:
					++newThumbPos;
					break;
				case EEikScrollPageUp:
					newThumbPos -= ((pageSize < 2)? 1 : pageSize - 1);
					break;
				case EEikScrollPageDown:
					newThumbPos += ((pageSize < 2)? 1 : pageSize - 1);
					break;
				case EEikScrollThumbDragVert:
				case EEikScrollThumbReleaseVert:
					// in the case of drag events, the scrollbar automatically updates its thumb pos...
					break;
				}
			iConsole->MoveTopLeft(TPoint(0,newThumbPos - iLastThumbPos.iY));
			if (aEventType != EEikScrollThumbDragVert)
				aScrollBar->SetModelThumbPosition(newThumbPos);
			break;
		}
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////
// SetScrollBarVisibility
// ======================
// Changes which scroll bars are visible. Returns EFalse if nothing changed.
///////////////////////////////////////////////////////////////////////////////////////////////////////
EXPORT_C TInt CEikConsoleControl::SetScrollBarVisibilityL(CEikScrollBarFrame::TScrollBarVisibility aHBarVisibility, CEikScrollBarFrame::TScrollBarVisibility aVBarVisibility)
	{
	if ((aHBarVisibility==iHBarVisibility)&&(aVBarVisibility==iVBarVisibility))
		return EFalse;
	iHBarVisibility=aHBarVisibility;
	iVBarVisibility=aVBarVisibility;
	iSBFrame->SetScrollBarVisibilityL(iHBarVisibility, iVBarVisibility);
	return ETrue;
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////
// SizeChanged
// ==========
///////////////////////////////////////////////////////////////////////////////////////////////////////
EXPORT_C void CEikConsoleControl::SizeChanged()
	{
	iViewInPixels=Size(); // new area
	if (iConsole && iSBFrame)
		{
		iConsole->UpdateScrollBars();
		UpdateArea();
		}
	}

EXPORT_C void CEikConsoleControl::FocusChanged(TDrawNow aDrawNow)
	{
	if (aDrawNow==ENoDrawNow)
		return;
	if (IsFocused())
		iConsole->DrawCursor();
	else
		iConsole->HideCursor();
	}

EXPORT_C TInt CEikConsoleControl::CountComponentControls() const
	{
	return (iSBFrame) ? iSBFrame->CountComponentControls() : NULL;
	}

EXPORT_C CCoeControl* CEikConsoleControl::ComponentControl(TInt aIndex) const
	{
	return iSBFrame->ComponentControl(aIndex);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// VisibleSize()
// =============
// Simply returns the visible size in characters
///////////////////////////////////////////////////////////////////////////////////////////////////////
EXPORT_C TSize CEikConsoleControl::VisibleSize() const
	{
	return iViewInChars;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// ConstructL
// ==========
// Construct and activate a CEikConsoleControl (claiming the specified part of the physical screen)
///////////////////////////////////////////////////////////////////////////////////////////////////////
EXPORT_C void CEikConsoleControl::ConstructL(TInt aFlags)
	{
	// Init screen. Use RBackedUpWindow instead of RWindow if aFlags & CEikConsoleScreen::EUseBackedUpWindow
	if (aFlags&CEikConsoleScreen::EUseBackedUpWindow)
		CreateBackedUpWindowL((RWindowTreeNode&)iCoeEnv->RootWin(), EGray4);
	else
		{
		CreateWindowL();
		Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorControlBackground,*this));
		}
	SetExtentToWholeScreen();

	// Create scrollbars
	iSBFrame=new(ELeave) CEikScrollBarFrame(this, this);
	iSBFrame->SetScrollBarVisibilityL(iHBarVisibility,iVBarVisibility);

	InitFontSpecL();
	SetFontL(iFontSpec,NULL);

	// activate
	ActivateL();
	}

EXPORT_C void CEikConsoleControl::ConstructL(TPoint aTopLeft,const TSize &aSize,TInt aFlags,TEikConsWinUnits aUnit)
	{
	// Init screen. Use RBackedUpWindow instead of RWindow if aFlags & CEikConsoleScreen::EUseBackedUpWindow
	if (aFlags&CEikConsoleScreen::EUseBackedUpWindow)
		CreateBackedUpWindowL((RWindowTreeNode&)iCoeEnv->RootWin(), EGray4);
	else
		{
		CreateWindowL();
		Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorControlBackground,*this));
		}

	// Create scrollbars
	iSBFrame=new(ELeave) CEikScrollBarFrame(this, this);
	iSBFrame->SetScrollBarVisibilityL(iHBarVisibility,iVBarVisibility);

	InitFontSpecL();
	
	if (aUnit==EEikConsWinInChars)
		{
		CFont *font;
		iEikonEnv->ScreenDevice()->GetNearestFontInTwips(font,iFontSpec);
		CFbsFont* fbsFont = (CFbsFont*)font;
		iCurrentFont=fbsFont;
		iCharSize.iWidth=fbsFont->MaxNormalCharWidthInPixels();
		iCharSize.iWidth=fbsFont->CharWidthInPixels('i');
		iCharSize.iWidth=fbsFont->CharWidthInPixels('M');
		iCharSize.iHeight=fbsFont->HeightInPixels();
		
		SetExtent(TPoint(aTopLeft.iX*iCharSize.iWidth,aTopLeft.iY*iCharSize.iHeight),
			TSize(aSize.iWidth*iCharSize.iWidth,aSize.iHeight*iCharSize.iHeight));
		SetFontL(iFontSpec,fbsFont);
		}
	else
		{
		SetExtent(aTopLeft,aSize);
		SetFontL(iFontSpec,NULL);
		}
	// activate
	ActivateL();
	}

void CEikConsoleControl::InitFontSpecL()
    {
    HBufC16* typeface = iCoeEnv->AllocReadResourceAsDes16LC(R_AKNPRIV_DEFAULT_CONSOLE_FONTSPEC_TYPEFACE);
    iFontSpec.iTypeface.iName= *typeface;
    CleanupStack::PopAndDestroy(typeface);

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader,R_AKNPRIV_DEFAULT_CONSOLE_FONTSPEC_HEIGHT);
    iFontSpec.iHeight=reader.ReadInt16();
    CleanupStack::PopAndDestroy(); // reader

#if defined(_UNICODE)
    iFontSpec.iTypeface.SetIsProportional(EFalse);
#endif
    iFontUnderline=EUnderlineOff;
    iFontSpec.iFontStyle.SetPosture(EPostureUpright);
    iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightNormal);
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////
// SetRedrawer
// ===========
// Define aConsoleScreen as the object responsible for redrawing
///////////////////////////////////////////////////////////////////////////////////////////////////////
EXPORT_C void CEikConsoleControl::SetRedrawer(CEikConsoleScreen *aConsoleScreen)
	{
	iConsole=aConsoleScreen;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor and Destructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
EXPORT_C CEikConsoleControl::CEikConsoleControl()
	{
	// *** init color
	iBackGray16=iEikonEnv->Color(EColorControlBackground);
	iPenGray16=iEikonEnv->Color(EColorControlText);

	// *** init scrollbar settings and font (however, 0-values are free in construction)
	// iHBarPresent=FALSE;
	// iVBarPresent=FALSE;
	// iLastThumbPos = TPoint(0,0);
	// iCurrentFont=NULL;

	// *** init cursor
	iCursorHeightPercentage=20;
	iTextCursor.iType	= TTextCursor::ETypeRectangle;
	iTextCursor.iFlags	= 0;
	iTextCursor.iColor=iEikonEnv->Color(EColorControlBackground);
	iLastAtt=iLastFontFlags=(ATT_MAXVALUE+1);
	}

EXPORT_C CEikConsoleControl::~CEikConsoleControl()
	{
	iEikonEnv->ReleaseScreenFont(CONST_CAST(CFont*,iCurrentFont));
	delete(iSBFrame);
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////
// NextFontL
// =========
// Utility function: unload current font (if any) and load new font (specified elsewhere in iFontSpec)
///////////////////////////////////////////////////////////////////////////////////////////////////////
void CEikConsoleControl::NextFontL()
	{
	CFont* font;
	User::LeaveIfError(iEikonEnv->ScreenDevice()->GetNearestFontInTwips(font, iFontSpec));
	CFbsFont* fbsFont = (CFbsFont*)font;
	iEikonEnv->ReleaseScreenFont(CONST_CAST(CFont*,iCurrentFont)); // note that this only happens if the previous line succeeds!
	iCurrentFont=fbsFont;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// SetFontL
// ========
// Change the font
///////////////////////////////////////////////////////////////////////////////////////////////////////
EXPORT_C void CEikConsoleControl::SetFontL(const TFontSpec& aFontSpec,const CFbsFont *aFont)
	{
	iFontSpec=aFontSpec;
	iFontHeight=(TUint16)iFontSpec.iHeight;
	if (aFont==NULL)
		NextFontL();

	iCharSize = TSize( iCurrentFont->CharWidthInPixels('M'),iCurrentFont->FontMaxHeight() );

	SetCursorHeight(iCursorHeightPercentage);

	// Determine font flags for new font
	iFontIsProportional=iCurrentFont->FontSpecInTwips().iTypeface.IsProportional();
	iLastFontFlags = 0;
	if (iFontUnderline!=EUnderlineOff)
		iLastFontFlags|=ATT_UNDERLINE;
	if (iFontSpec.iFontStyle.Posture()!=EPostureUpright)
		iLastFontFlags|=ATT_ITALIC;
	if (iFontSpec.iFontStyle.StrokeWeight()!=EStrokeWeightNormal)
		iLastFontFlags|=ATT_BOLD;

	UpdateArea();
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  Utility functions: convert between character coordinates to pixel coordinates
//
////////////////////////////////////////////////////////////////////////////////////////

TPoint CEikConsoleControl::CharsToPixels(TPoint aPos)
	{
	return TPoint( iCharSize.iWidth * aPos.iX, iCharSize.iHeight * aPos.iY );
	}

TRect CEikConsoleControl::CharsToPixels(const TRect &aRect)
	{
	return TRect(CharsToPixels(aRect.iTl),CharsToPixels(aRect.iBr));
	}

TRect CEikConsoleControl::PixelsToChars(const TRect &aRect) 
	{
	TRect r = aRect;
	r.Normalize();
	r.iTl.iX /= iCharSize.iWidth;
	r.iBr.iX /= iCharSize.iWidth;
	r.iBr.iX ++;
	r.iTl.iY /= iCharSize.iHeight;
	r.iBr.iY /= iCharSize.iHeight;
	r.iBr.iY ++;
	return r;
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  Cursor stuff
//
////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C void CEikConsoleControl::DrawCursor(TPoint aPosition)
// Show cursor at character position
	{
	//iEikonEnv->RootWin().SetTextCursor(*DrawableWindow(),CharsToPixels(aPosition),iTextCursor);
	iEikonEnv->DrawCursor(this, CharsToPixels(aPosition), iTextCursor.iWidth, iTextCursor.iAscent, iTextCursor.iHeight);
	}

EXPORT_C void CEikConsoleControl::HideCursor()
// Hide cursor 
	{
	//iEikonEnv->RootWin().CancelTextCursor();
	iEikonEnv->HideCursor(this);
	}


EXPORT_C void CEikConsoleControl::SetCursorHeight(TUint aPercentage)
// Set new cursor height (specified as percentage of font height)
// Should also be called whenever iCharSize changes!
// Change will not take effect until the next call to DrawCursor!
	{
	iCursorHeightPercentage = aPercentage % 101;
	iTextCursor.iHeight = ( 99 + (iCharSize.iHeight * iCursorHeightPercentage) ) / 100;
	iTextCursor.iAscent = iTextCursor.iHeight-iCharSize.iHeight;
	iTextCursor.iWidth  = iCharSize.iWidth;
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  Draw - defers the real work to the owner (a CEikConsoleScreen)
//
////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C void CEikConsoleControl::Draw(const TRect& aRect) const
	{
	if (iConsole) // if there's no owner, we do nothing
		{
		M().iRedrawing=1;
		TPoint br(iViewInChars.iWidth*iCharSize.iWidth,iViewInChars.iHeight*iCharSize.iHeight);
		const TRgb background=iEikonEnv->ControlColor(EColorControlBackground,*this);
		ClearPixels(TRect(br.iX,0,iViewInPixels.iWidth,br.iY),background);
		ClearPixels(TRect(0,br.iY,iViewInPixels.iWidth,iViewInPixels.iHeight),background);
		iConsole->Redraw(M().PixelsToChars(aRect)); // Redraw all chars in the rectangle
		M().iRedrawing=0;
		}
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  Set up GC based for given attribute
//
////////////////////////////////////////////////////////////////////////////////////////

void CEikConsoleControl::InterpretColorBits(TUint aCharacterAttributes)
// Set iPenGrey16 and iBackGrey16 based on character attribute aCharacterAttributes
	{
	if (aCharacterAttributes & ATT_COLORMASK) // is color
		{
		const TInt pen16=(aCharacterAttributes&0x0F);
		iPenGray16=TRgb::Color16(pen16);
		TInt back16=((aCharacterAttributes&0x70)>>4)*2+1;
		if (back16==1)
			back16=0;
		iBackGray16=TRgb::Color16(back16);
		}
	else if ( aCharacterAttributes & ATT_INVERSE )
		{
		iBackGray16=iEikonEnv->ControlColor(EColorControlHighlightBackground,*this);
		iPenGray16=iEikonEnv->ControlColor(EColorControlHighlightText,*this);
		}
	else
		{
		iBackGray16=iEikonEnv->ControlColor(EColorControlBackground,*this);
		iPenGray16=iEikonEnv->ControlColor(EColorControlText,*this);
		}
	}

void CEikConsoleControl::InterpretAttribute(TUint aCharacterAttributes)
	{
	if (iLastAtt!=aCharacterAttributes)
		{
		_LIT(KMonospace,"Monospaced");
		_LIT(KMonodouble,"MONODOUBLE");
		iLastAtt=aCharacterAttributes;
		InterpretColorBits(aCharacterAttributes);
		TUint fontFlags = (aCharacterAttributes & ATT_COLORMASK) ? (0) : (aCharacterAttributes & ATT_IGNORE_INVERSE & ATT_IGNORE_RIGHTLEFT);
		if (iLastFontFlags!=fontFlags)
			{
			iLastFontFlags=fontFlags;
			iFontUnderline=((fontFlags & ATT_UNDERLINE)? EUnderlineOn: EUnderlineOff);
			iFontSpec.iFontStyle.SetPosture(((fontFlags & ATT_ITALIC)? EPostureItalic: EPostureUpright));
			iFontSpec.iFontStyle.SetStrokeWeight(((fontFlags & ATT_BOLD)? EStrokeWeightBold: EStrokeWeightNormal));
			if (fontFlags & ATT_DOUBLEMASK)
				{ // double aVisiblePixels
				if ( (fontFlags & ATT_DOUBLEMASK) == ATT_DOUBLEWIDTH )
					{ // double width 
					iFontSpec.iHeight = iFontHeight;
					if (iFontSpec.iTypeface.iName.Compare(KMonospace)==0 )
						iFontSpec.iTypeface.iName=KMonodouble; 			//@@@
					}
				else
					{ // double height
					iFontSpec.iHeight = (TUint16)(iFontHeight*2);
					if ( iFontSpec.iTypeface.iName.Compare(KMonodouble)==0 )
						iFontSpec.iTypeface.iName=KMonospace; 			//@@@
					}
				}
			else 
				{ // normal aVisiblePixels
				iFontSpec.iHeight = iFontHeight;
				if ( iFontSpec.iTypeface.iName.Compare(KMonodouble)==0 )
					iFontSpec.iTypeface.iName=KMonospace; 			//@@@
				} 
			TRAP_IGNORE(NextFontL());	// ignore errors. If there is a problem, we'll use the one that was loaded
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////
//
//  Basic Graphic services
//  ======================
//	NOTE: if iRedrawing, then a redraw is going on, 
//  i.e. no need to (de)activate gc's or (in)validate rectangles
//
////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C void CEikConsoleControl::InvertChars(const TRect &anArea)
// invert a rectangle of characters
	{
	if (!iRedrawing)
		ActivateGc();
	CWindowGc& gc=SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	const TRgb highlightBackground=iEikonEnv->ControlColor(EColorControlBackground,*this);
	gc.SetBrushColor(highlightBackground);
	gc.SetDrawMode(CGraphicsContext::EDrawModeXOR);
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    if (!iRedrawing && !IsBackedUp())
        { 
        Window().Invalidate(anArea); 
        Window().BeginRedraw(anArea); 
        } 
    
    gc.DrawRect(CharsToPixels(anArea));
    if (!iRedrawing && !IsBackedUp())
        {
        Window().EndRedraw(); 
        }
    
    gc.SetDrawMode(CGraphicsContext::EDrawModePEN);
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetBrushStyle(CGraphicsContext::ENullBrush);
    if (!iRedrawing)
        DeactivateGc();
    }

EXPORT_C void CEikConsoleControl::ScrollChars(const TRect &anArea,const TPoint &aVector)
// scroll a rectangle of characters by a given vector (character coordinates)
	{
	const TRect areaInPixels=CharsToPixels(anArea);
	Window().Scroll(areaInPixels,CharsToPixels(aVector),areaInPixels);
	}

void CEikConsoleControl::ClearPixels(const TRect &anArea,TRgb aColor) const
	{
	if (!iRedrawing)
		ActivateGc();
	CWindowGc& gc=SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(aColor);
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    if (!iRedrawing && !IsBackedUp()) 
        { 
        Window().Invalidate(anArea); 
        Window().BeginRedraw(anArea); 
        } 
    
    gc.DrawRect(anArea);
    if (!iRedrawing && !IsBackedUp()) 
        {
        Window().EndRedraw();
        }
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetBrushStyle(CGraphicsContext::ENullBrush);
    if (!iRedrawing)
        DeactivateGc();
    }

EXPORT_C void CEikConsoleControl::ClearChars(const TRect &anArea,TUint aCharacterAttributes) 
// Clears a rectangle of characters to the current background color
	{
	TRect theArea=CharsToPixels(anArea);
	InterpretColorBits(aCharacterAttributes); 
	ClearPixels(theArea,iBackGray16);
	}

EXPORT_C void CEikConsoleControl::DrawChars(const TDesC &aString,const TPoint &aPosition,TUint aCharacterAttributes)
// Draw characters at given position using given attribute
	{
	InterpretAttribute(aCharacterAttributes);
	TPoint pos = CharsToPixels(aPosition);
	TInt topMargin 	= iCurrentFont->AscentInPixels();
    if ( iCurrentFont->TypeUid() == KCFbsFontUid)
        {
        const CFbsFont* fbsFont = (CFbsFont*)iCurrentFont;
        topMargin = fbsFont->FontMaxAscent();
        }

	TInt isDouble = ( !(aCharacterAttributes & ATT_COLORMASK) && (aCharacterAttributes & ATT_DOUBLEMASK) );
	TRect charArea = TRect(pos,iCharSize);

	if (!iRedrawing)
		ActivateGc();
	
	CWindowGc& gc=SystemGc();
	gc.UseFont(iCurrentFont);
	gc.SetPenColor(iPenGray16);
	gc.SetBrushColor(iBackGray16);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetUnderlineStyle(iFontUnderline);
    
    TInt currentFont_width = iCurrentFont->MaxNormalCharWidthInPixels();
    if (isDouble || iFontIsProportional || currentFont_width!=iCharSize.iWidth )
        {
        TInt leftMargin = 0;
        
        if (isDouble)
            {
            if (aCharacterAttributes & ATT_RIGHTMASK)
                leftMargin -= iCharSize.iWidth;
            if ((aCharacterAttributes & ATT_DOUBLEMASK) == ATT_DOUBLEBOTTOM)
                topMargin -= iCharSize.iHeight;
            }
        
        if (!iRedrawing && !IsBackedUp()) 
            {
            TSize stringSize(iCharSize); 		
            stringSize.iWidth *= aString.Length();	// calculate on-screen width of line
            TRect wholestring(pos,stringSize);
            Window().Invalidate(wholestring); 	
            Window().BeginRedraw(wholestring); 		// begin draw transaction for whole line
            } 
        for ( TInt i=0;i<aString.Length();i++ )
            {
            gc.DrawText(aString.Mid(i,1),charArea,topMargin,CGraphicsContext::ELeft,leftMargin);
            
            charArea.Move(iCharSize.iWidth,0);
            if (isDouble)
                leftMargin = - iCharSize.iWidth - leftMargin;
            }
        if (!iRedrawing && !IsBackedUp()) 
            {
            Window().EndRedraw();
            }
        }
    else
        {
        charArea.iBr.iX += (iCharSize.iWidth*(aString.Length()-1));
        if (!iRedrawing && !IsBackedUp()) 
            { 
            Window().Invalidate(charArea); 
            Window().BeginRedraw(charArea); 
            } 
        gc.DrawText(aString,charArea,topMargin);
        if (!iRedrawing && !IsBackedUp())
            {
            Window().EndRedraw();
            }
        }
    
    gc.DiscardFont();
    if (!iRedrawing)
        DeactivateGc();
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikConsoleControl::GetColorUseListL(CArrayFix<TCoeColorUse>& /*aColorUseList*/) const
	{
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikConsoleControl::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	if (aType==KEikMessageColorSchemeChange)
		{
		if (!IsBackedUp())
			{
			Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorControlBackground,*this));
			}
		}
	}

// Reserved from CCoeControl

EXPORT_C void CEikConsoleControl::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{
	}
	
EXPORT_C void CEikConsoleControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CEikConsoleControl::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikConsoleControl::Reserved_2()
	{
	}

