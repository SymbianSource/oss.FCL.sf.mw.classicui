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


#include <eikconso.h>
#include <gdi.h>
#include <coecntrl.h>
#include <coemain.h>

EXPORT_C TSize CEikConsoleScreen::ScreenSize() const
    {
    return iConsoleSize;
    }

EXPORT_C TInt CEikConsoleScreen::Create(const TDesC& aTitle,TSize aSize)
    {
    TRAPD(err,ConstructL(aTitle,aSize,EUseBackedUpWindow));
    if (!err)
        DrawCursor();
    return(err);
    }

EXPORT_C void CEikConsoleScreen::Read(TRequestStatus& /*aStatus*/)
    { // not implemented - this part of base abstraction deliberately broken
    }

EXPORT_C void CEikConsoleScreen::ReadCancel()
    { // not implemented - this part of base abstraction deliberately broken
    }

EXPORT_C TKeyCode CEikConsoleScreen::KeyCode() const
    { // not implemented - this part of base abstraction deliberately broken
    return(EKeyNull);
    }

EXPORT_C TUint CEikConsoleScreen::KeyModifiers() const
    { // not implemented - this part of base abstraction deliberately broken
    return(0);
    }

EXPORT_C void CEikConsoleScreen::FlushChars() 
	{
	if (!iWriteNow && iWriteBuffer.Length())
		{
		iWriteNow=1;
		Write(iWriteBuffer);
		iWriteBuffer.SetLength(0);
		iWriteNow=0;
		}
	}
	    
////////////////////////////////////////////////////////////////////////////////////////
//
//  UTILITY FUNCTIONS
//
////////////////////////////////////////////////////////////////////////////////////////

void cutmax(TInt &x,TInt max) {if (x>max) x=max;}
void cutmin(TInt &x,TInt min) {if (x<min) x=min;}

TUint SmallerPoint(TPoint a,TPoint b)
	{ 
	return ( a.iY < b.iY || (a.iY==b.iY && a.iX<=b.iX ) ); 
	}

TRect Clip(const TRect &aRect,const TRect &anOtherRect)
// return aRect clipped to anOtherRect (i.e. true intersection) 
	{
	TRect theRect = aRect;
	theRect.Intersection(anOtherRect);
	cutmax(theRect.iTl.iX,theRect.iBr.iX);
	cutmax(theRect.iTl.iY,theRect.iBr.iY);
	return theRect;
	}

void CopyNormalisedRange(TRect &dstRange,const TRect &srcRange)
// Make dstRange a normalized RANGE version of srcRange 
	{
	dstRange=srcRange;
	if (SmallerPoint(dstRange.iBr,dstRange.iTl))
		{ dstRange.iTl=srcRange.iBr; dstRange.iBr=srcRange.iTl; }
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  HISTORY ACCESS (LOW LEVEL)
//
////////////////////////////////////////////////////////////////////////////////////////

TPtr8	CEikConsoleScreen::MemAttPtr(TPoint aScrPos,TUint aLength) // aScrPos = SCREEN coordinates
// returns TPtr8 within attribute history at given position for aLength 'characters'
	{
	return TPtr8(&iAttBuf[aScrPos.iX+((aScrPos.iY+iMaxAttExtra)*iConsoleSize.iWidth)],aLength,aLength);
	}

TPtr	CEikConsoleScreen::MemChrPtr(TPoint aScrPos,TUint aLength) // aScrPos = SCREEN coordinates
// returns TPtr within character history at given position for aLength 'characters'
	{
	return TPtr(&iChrBuf[aScrPos.iX+((aScrPos.iY+iMaxChrExtra)*iConsoleSize.iWidth)],aLength,aLength);
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  SCROLLBAR STUFF 
//
////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C TBool CEikConsoleScreen::UpdateScrollBars() 
// should be called whenever datasize and/or topleft changes
// Return ETrue if, as a result, the visible window has changed
	{
	if (iConsoleControl)
		{
		TBool updatedScrollbars = EFalse;
		TRAP_IGNORE(updatedScrollbars = iConsoleControl->UpdateScrollbarsL(iConsoleSize+TSize(0,iNoChrExtra),iConsoleSize,iTopLeft-TPoint(0,iMaxChrExtra-iNoChrExtra)));
		if (updatedScrollbars)
			return RecalculateSize(); // datasize change may have resulted in a different visible window (due to scrollbars)
		}
	return EFalse;
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  HISTORY STORAGE (HIGH LEVEL)
//
////////////////////////////////////////////////////////////////////////////////////////

// aPos = SCREEN coordinates
void CEikConsoleScreen::MemScrPut(const TDesC &aString,TPoint aPos,TUint8 anAtt)
 	{
	MemChrPtr(aPos,aString.Length()).Copy(aString);
	MemAttPtr(aPos,aString.Length()).Fill(anAtt);
	}


// aRect = SCREEN coordinates
void CEikConsoleScreen::MemScrClr(const TRect &aRect,TUint8 anAtt)
	{
	TUint8 clrAtt = anAtt;
	if ((clrAtt & ATT_COLORMASK) == 0) 
		clrAtt &= (ATT_BOLD|ATT_INVERSE); // when clearing, only BOLD and INVERSE properties are relevant
	for (TInt y=aRect.iTl.iY;y<aRect.iBr.iY;y++)
		{
		TInt width = aRect.iBr.iX - aRect.iTl.iX;
		MemChrPtr(TPoint(aRect.iTl.iX,y),width).Fill(TChar(' '));
		MemAttPtr(TPoint(aRect.iTl.iX,y),width).Fill(clrAtt);
		}
	}

// anOldPt/aNewPt = SCREEN coordinates
void CEikConsoleScreen::MemScrMove(TPoint anOldPt,TPoint aNewPt,TUint aLen)
	{
	MemChrPtr(aNewPt,aLen).Copy(MemChrPtr(anOldPt,aLen));
	MemAttPtr(aNewPt,aLen).Copy(MemAttPtr(anOldPt,aLen));
	}

// aRect = SCREEN coordinates 
void CEikConsoleScreen::MemScrScroll(const TRect &aRect,TPoint aVector)
	{
	// determine the destination rectangle
	TRect normRect = aRect;
	normRect.Normalize();
	TRect newRect = normRect;
	newRect.Move(aVector);
	newRect.Intersection(normRect); 
	newRect.Intersection(TRect(iConsoleSize));
	// now move from old rectangle to new rectangle...
	TInt width = newRect.iBr.iX - newRect.iTl.iX;
	if (width>0)
		{
		TInt height= newRect.iBr.iY - newRect.iTl.iY;
		if ( aVector.iY <= 0 )
			{
			for ( TInt y=0;y<height;y++ )
				MemScrMove(newRect.iTl-aVector+TPoint(0,y),newRect.iTl+TPoint(0,y),TUint(width));
			}
		else
			{
			for ( TInt y=height-1;y>=0;y-- )
				MemScrMove(newRect.iTl-aVector+TPoint(0,y),newRect.iTl+TPoint(0,y),TUint(width));
			}	
		}
	// now, all characters that are in normRect but not in newRect must become spaces, but WE KEEP THE ATTRIBUTES!
	for(TInt y=normRect.iTl.iY;y<normRect.iBr.iY;y++)
		for(TInt x=normRect.iTl.iX;x<normRect.iBr.iX;x++)
			if (!newRect.Contains(TPoint(x,y)))
				MemChrPtr(TPoint(x,y),1).Fill(TChar(' '));
	}

void CEikConsoleScreen::MemScrScrollUp(TUint aLines)
	{
	TInt toMove = iConsoleSize.iWidth * (iConsoleSize.iHeight + iMaxChrExtra - aLines);
	if (toMove>0)
		MemChrPtr(TPoint(0,-iMaxChrExtra),toMove).Copy(MemChrPtr(TPoint(0,aLines-iMaxChrExtra),toMove));
	toMove = iConsoleSize.iWidth * (iConsoleSize.iHeight + iMaxAttExtra - aLines);
	if (toMove>0)
		MemAttPtr(TPoint(0,-iMaxAttExtra),toMove).Copy(MemAttPtr(TPoint(0,aLines-iMaxAttExtra),toMove));
	// update nr of lines stored
	iNoChrExtra+=aLines; 
	cutmax(iNoChrExtra,iMaxChrExtra); 
	}

EXPORT_C void CEikConsoleScreen::SetHistorySizeL(TUint aMaxChrExtra,TUint aMaxAttExtra)
	{
	FlushChars();
	TText* chrBuf = (TText  *) User::AllocL(iConsoleSize.iWidth * (aMaxChrExtra + iConsoleSize.iHeight) * sizeof(TText));
	CleanupStack::PushL(chrBuf);
	TUint8* attBuf = (TUint8 *) User::AllocL(iConsoleSize.iWidth * (aMaxAttExtra + iConsoleSize.iHeight) * sizeof(TUint8));
	CleanupStack::Pop(); // chrBuf
	iMaxChrExtra=aMaxChrExtra;
	iMaxAttExtra=aMaxAttExtra;
	User::Free(iChrBuf);
	iChrBuf=chrBuf;
	User::Free(iAttBuf);
	iAttBuf=attBuf;
	// clear on-screen buffers and set top left to top of screen
	iNoChrExtra=0; 
	MemScrClr(TRect(iConsoleSize),0);
	iTopLeft.SetXY(0,iMaxChrExtra);
	// datasize + topleft have changed:
	UpdateScrollBars(); 
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  SETTINGS
//
////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C void CEikConsoleScreen::SetKeepCursorInSight(TUint aFlag)
	{
	FlushChars();
	iKeepCursorInSight=aFlag;
	}

EXPORT_C void CEikConsoleScreen::SetPureCRLF(TUint aFlag)
	{
	FlushChars();
	iPureCRLF=aFlag;
	}

EXPORT_C void CEikConsoleScreen::SetAllPrintable(TUint aFlag)
	{
	FlushChars();
	iAllPrintable=aFlag;
	}

EXPORT_C void CEikConsoleScreen::SetScrollLock(TUint aFlag)
	{
	FlushChars();
	iScrollLock=aFlag;
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  CURSOR DISPLAY
//
////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C TInt CEikConsoleScreen::HideCursor()
	{
	FlushChars();
	if (iCursorBlinking) 
		{
		if (iConsoleControl->IsFocused())
			iConsoleControl->HideCursor();
		iCursorBlinking=FALSE;
		return 1;
		}
	return 0;
	}

EXPORT_C void CEikConsoleScreen::DrawCursorInSight()
	{
	DrawInSight(iCursor);
	DrawCursor();
	}

EXPORT_C void CEikConsoleScreen::DrawCursor()
	{
	if (iConsFlags&ENoInitialCursor)
		{
		iConsFlags&=(~ENoInitialCursor);
		return;
		}
	FlushChars();
	if(iConsoleControl->IsFocused())
		{
		TPoint theCursor = ScrToVis(iCursor);
		iConsoleControl->DrawCursor(theCursor);
		iCursorBlinking=TRUE;
		}
	}

void CEikConsoleScreen::DrawCursorWhereNeeded()
	{
	// FlushChars() by one of the DrawCursor's
	if (iKeepCursorInSight) 
		DrawCursorInSight(); 
	else  
		DrawCursor();
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  MoveTopLeft() and Redraw()
//
////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C void CEikConsoleScreen::SetScrollBarVisibilityL(CEikScrollBarFrame::TScrollBarVisibility aHBarVisibility, CEikScrollBarFrame::TScrollBarVisibility aVBarVisibility)
	{
	if (iConsoleControl->SetScrollBarVisibilityL(aHBarVisibility,aVBarVisibility))
		{
		if (UpdateScrollBars())
			iConsoleControl->UpdateArea();
		}
	}

EXPORT_C void CEikConsoleScreen::MoveTopLeft(TPoint aVector)
	{
	TInt cursorHidden=HideCursor(); //FlushChars(); by hidecursor

	TPoint newTL = iTopLeft + aVector; 
	cutmax(newTL.iX, iConsoleSize.iWidth - iVisSize.iWidth);
	cutmin(newTL.iX, 0);
	cutmax(newTL.iY, iMaxChrExtra + iConsoleSize.iHeight - iVisSize.iHeight);
	cutmin(newTL.iY, iMaxChrExtra - iNoChrExtra);

	TPoint vector = iTopLeft-newTL;
	iConsoleControl->ScrollChars(iVisWin,vector);	
	iTopLeft=newTL;
	// topleft has changed:
	UpdateScrollBars(); 

	// Following lines added for smooth redrawing: (@@@ are these really needed? @@@)
	if (vector.iX==0)
		{
		if (vector.iY>0)
			Redraw(TRect(0,0,iVisSize.iWidth,vector.iY)); 
		else if (vector.iY<0)
			Redraw(TRect(0,iVisSize.iHeight+vector.iY,iVisSize.iWidth,iVisSize.iHeight)); 
		}
	else if (vector.iY==0)
		{
		if (vector.iX>0)
			Redraw(TRect(0,0,vector.iX,iVisSize.iHeight)); 
		else // if (vector.iX<0)
			Redraw(TRect(iVisSize.iWidth+vector.iX,0,iVisSize.iWidth,iVisSize.iHeight)); 
		}

	if (cursorHidden) 
		DrawCursor();
	}

// Redraw of a set of same-attribute characters (knows about double LEFT/RIGHT)
void CEikConsoleScreen::RedrawChars(TInt anX,TInt anY,TInt aLength,TUint anAtt)
	{
	TUint att=anAtt;
	if ( (anX&1) && !(anAtt & ATT_COLORMASK) && (anAtt & ATT_DOUBLEMASK) )
		att |= ATT_RIGHTMASK; // set RIGHT flag for any doublewidth non-color character in an odd column
	iConsoleControl->DrawChars(MemChrPtr(TPoint(anX,anY-iMaxChrExtra),aLength),TPoint(anX,anY)-iTopLeft,att);
	TRect sel; CopyNormalisedRange(sel,iSelection); sel.Move(0,iMaxChrExtra);
	InvertOverlap(sel.iTl,sel.iBr,TPoint(anX,anY),TPoint(anX+aLength,anY)); //}}}
	}

// aRect = VISIBLE coordinates!!!
EXPORT_C void CEikConsoleScreen::Redraw(const TRect &aRect)
	{
	TInt oldnow=iWriteNow; iWriteNow=1; 

	TRect todoRect = Clip(aRect,iVisWin);
	if (RecalculateSize())
		{
		iTopLeft = GetAnInSightPosition(iCursor);
		// topleft has changed
		if (UpdateScrollBars())
			{
			iTopLeft = GetAnInSightPosition(iCursor);
			UpdateScrollBars();
			}
		// might as well redraw the whole screen now...
		todoRect = iVisWin;
		}

	// convert visible to clipped absolute coordinates
	todoRect.Move(iTopLeft);
	cutmax(todoRect.iBr.iX,iConsoleSize.iWidth);
	cutmax(todoRect.iBr.iY,iMaxChrExtra + iConsoleSize.iHeight);
	
	// hide cursor while redarwing...
	TInt cursorHidden = HideCursor();
	
	for( TInt y=todoRect.iTl.iY; y<todoRect.iBr.iY; y++) 
		{
		TInt yAtt = y+iMaxAttExtra-iMaxChrExtra; // line within attribute buffer
		TInt x,start;
		TInt len=0;
		TUint att=ATT_MAXVALUE+1;	// impossible value
		TUint attXY=ATT_NORMAL;    	// default attribute (in case there is no attribute history)
	  	for( x=start=todoRect.iTl.iX; x<todoRect.iBr.iX; x++)
			{
			if (yAtt>=0) 
				attXY=iAttBuf[x+yAtt*iConsoleSize.iWidth]; 
			if ( att != attXY )
				{
				if (len)  
					RedrawChars(start,y,len,att);
				start=x; att=attXY; len=0;
				}
			len++;
			}
		if (len)
			RedrawChars(start,y,len,att);
		}

	if (cursorHidden) 
		DrawCursor();
	iWriteNow=oldnow;
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  Constructors/Destructors/Initializers
//
////////////////////////////////////////////////////////////////////////////////////////

EXPORT_C void CEikConsoleScreen::SetTitle(const TDesC& aTitle)
    {
    TRAP_IGNORE(SetTitleL(aTitle));
    // !! what to do if err ??
    }

EXPORT_C void CEikConsoleScreen::SetTitleL(const TDesC& aTitle)
	{
    HBufC* oldTitle=iConsoleTitle;
	iConsoleTitle=aTitle.AllocL();
    delete(oldTitle);
	}

EXPORT_C void CEikConsoleScreen::ConstructL(const TDesC &aTitle,TInt aFlags)// use full screen 
	{
	// if no CEikConsoleControl set yet, claim one 
	iConsFlags=aFlags;
	if (!iConsoleControl)
		{
		CEikConsoleControl* consWin = new(ELeave) CEikConsoleControl;
		CleanupStack::PushL(consWin);
		consWin->ConstructL(aFlags);
		SetConsWin(consWin);
		CleanupStack::Pop();	// consWin
		}
	SetTitleL(aTitle);
	iConsoleSize=TSize(iConsoleControl->Size().iWidth/iConsoleControl->CharSize().iWidth,
		iConsoleControl->Size().iHeight/iConsoleControl->CharSize().iHeight);
	iKeepCursorInSight=TRUE;
	iWriteBuffer.SetLength(0); 
	SetHistorySizeL(0,0);
	}

EXPORT_C void CEikConsoleScreen::ConstructL(const TDesC &aTitle,TPoint aTopLeft,const TSize &aSize,
				TInt aFlags,TEikConsWinUnits aUnit)
	{
	// if no CEikConsoleControl set yet, claim one 
	iConsFlags=aFlags;
	if (!iConsoleControl)
		{
		CEikConsoleControl* consWin = new(ELeave) CEikConsoleControl;
		CleanupStack::PushL(consWin);
		consWin->ConstructL(aTopLeft,aSize,aFlags,aUnit);
		SetConsWin(consWin);
		CleanupStack::Pop();	// consWin
		}
	SetTitleL(aTitle);
	if (aUnit==EEikConsWinInChars)
		iConsoleSize=aSize;
	else
		iConsoleSize=TSize(aSize.iWidth/iConsoleControl->CharSize().iWidth,
			aSize.iHeight/iConsoleControl->CharSize().iHeight);
	iKeepCursorInSight=TRUE;
	iWriteBuffer.SetLength(0); 
	SetHistorySizeL(0,0);
	}

EXPORT_C void CEikConsoleScreen::ConstructL(const TDesC &aTitle,const TSize &aSize,TInt aFlags,TEikConsWinUnits aUnit)
 // place the screen at TPoint(0,0)
	{
	ConstructL(aTitle,TPoint(0,0),aSize,aFlags,aUnit);
	}

EXPORT_C CEikConsoleScreen::CEikConsoleScreen()
    {
    }

EXPORT_C CEikConsoleScreen::~CEikConsoleScreen()
	{
    delete(iConsoleControl);
	User::Free(iChrBuf);
	User::Free(iAttBuf);
	User::Free(iConsoleTitle);
	}

TBool CEikConsoleScreen::RecalculateSize()
// returns ETrue if visible window has changed
	{
	TRect oldwin=iVisWin;
	iVisSize = iConsoleControl->VisibleSize();
	cutmax(iVisSize.iWidth ,iConsoleSize.iWidth);
	cutmax(iVisSize.iHeight ,iConsoleSize.iHeight);
	iVisWin = TRect(iVisSize);
	return oldwin!=iVisWin;
	}

EXPORT_C const TFontSpec& CEikConsoleScreen::Font() const
	{
	return iConsoleControl->Font();
	}

EXPORT_C void CEikConsoleScreen::SetFontL(const TFontSpec &aFontSpec)
	{
	FlushChars();
	iConsoleControl->SetFontL(aFontSpec,NULL);
	}

EXPORT_C void CEikConsoleScreen::SetConsWin(CEikConsoleControl *aConsWin)
	{
	FlushChars();
	TBool calledBefore=EFalse;
	TInt cursorHidden=EFalse;
	if (iConsoleControl)
		{
		calledBefore=ETrue;
		cursorHidden=HideCursor();
		delete(iConsoleControl);
		}
	iConsoleControl=aConsWin;
	iConsoleControl->SetRedrawer(this);
	if (RecalculateSize())
		iTopLeft = GetAnInSightPosition(iCursor);
	if (calledBefore) // no need to update scrollbars the very first time
		UpdateScrollBars();
	if (cursorHidden)
		DrawCursorWhereNeeded();
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  Cursor Stuff
//
////////////////////////////////////////////////////////////////////////////////////////

// clip cursor to SCREEN, allows X coordinate of LAST line to be 1 past the right marging!
void CEikConsoleScreen::ClipCursor()
	{
	cutmin(iCursor.iX,0);
	cutmin(iCursor.iY, -iNoChrExtra);
	if (iCursor.iY<iConsoleSize.iHeight-1)
		cutmax(iCursor.iX,iConsoleSize.iWidth-1);
	else
		cutmax(iCursor.iX,iConsoleSize.iWidth);
	cutmax(iCursor.iY,iConsoleSize.iHeight-1);
	}

// return SCREEN coordinates
EXPORT_C TPoint CEikConsoleScreen::CursorPos() const
	{
	((CEikConsoleScreen*)this)->FlushChars();
	return iCursor;
	}

// aPoint = SCREEN coordinates
EXPORT_C void CEikConsoleScreen::SetCursorPosAbs(const TPoint &aPoint)
	{
	FlushChars();
	iCursor = aPoint;
	ClipCursor(); 
	if (iCursorBlinking)
		DrawCursorWhereNeeded();
	else if (iKeepCursorInSight) 
		DrawInSight(iCursor);
	}

EXPORT_C void CEikConsoleScreen::SetCursorPosRel(const TPoint &aPoint)
	{
	FlushChars();
	iCursor+=aPoint;
	ClipCursor();
	if (iCursorBlinking)
		DrawCursorWhereNeeded();
	else if (iKeepCursorInSight) 
		DrawInSight(iCursor);
	}

EXPORT_C void CEikConsoleScreen::SetCursorHeight(TInt aPercentage)
// set cursor height to aPercentage, and redraw cursor (if it is blinking)
	{
	iConsoleControl->SetCursorHeight(aPercentage);
	if (iCursorBlinking)
		DrawCursorWhereNeeded();
	else if (iKeepCursorInSight) 
		DrawInSight(iCursor);
	}

TPoint CEikConsoleScreen::GetAnInSightPosition(TPoint aPosition) const
	{
	TPoint newTL = iTopLeft;
	// past right margin: move so that cursor is at 3/4th of visible line screen
	if ( aPosition.iX >= newTL.iX + iVisSize.iWidth )
		newTL.iX = aPosition.iX - (3*iVisSize.iWidth)/4;
	// past left margin: move so that cursor is at 1/4th of visible line screen
	if ( aPosition.iX < newTL.iX )
		newTL.iX = aPosition.iX - iVisSize.iWidth/4;
	// keep within visible limits
	cutmax(newTL.iX,iConsoleSize.iWidth - iVisSize.iWidth);
	cutmin(newTL.iX,0);
	cutmax(newTL.iY,iMaxChrExtra + iConsoleSize.iHeight - iVisSize.iHeight);
	cutmax(newTL.iY,aPosition.iY + iMaxChrExtra);
	cutmin(newTL.iY,iMaxChrExtra + aPosition.iY - (iVisSize.iHeight-1));
	cutmin(newTL.iY,0); 
	return newTL;
	}

EXPORT_C void CEikConsoleScreen::DrawInSight(TPoint aPosition)
	{
	FlushChars();
	TPoint vector = GetAnInSightPosition(aPosition);
	if ( vector != iTopLeft )
		MoveTopLeft(vector-iTopLeft); // FlushChars() by MoveTopLeft
	}

EXPORT_C void CEikConsoleScreen::Up(TUint aCount)
	{
	FlushChars();
	iCursor.iY-=aCount;
	ClipCursor();
	DrawCursorWhereNeeded();
	}

EXPORT_C void CEikConsoleScreen::Down(TUint aCount)
	{
	FlushChars();
	iCursor.iY+=aCount;
	ClipCursor();
	DrawCursorWhereNeeded();
	}

EXPORT_C void CEikConsoleScreen::Left(TUint aCount)
	{
	FlushChars();
	iCursor.iY-=(aCount / iConsoleSize.iWidth );
	iCursor.iX-=(aCount % iConsoleSize.iWidth );
	while (iCursor.iX<0) 
		{ iCursor.iY--; iCursor.iX+=iConsoleSize.iWidth; } 
	if (iCursor.iY<(-iNoChrExtra)) 
		iCursor.SetXY(0,-iNoChrExtra);
	ClipCursor();
	DrawCursorWhereNeeded();
	}

EXPORT_C void CEikConsoleScreen::Right(TUint aCount)
	{
	FlushChars();
	iCursor.iX += aCount;
	iCursor.iY += (iCursor.iX / iConsoleSize.iWidth);
	iCursor.iX %= iConsoleSize.iWidth;
	if (iCursor.iY>=iConsoleSize.iHeight)
		iCursor.iX=iConsoleSize.iWidth;
	ClipCursor();
	DrawCursorWhereNeeded();
	}

////////////////////////////////////////////////////////////////////////////////////////
//
//  GRAPHICS
//
////////////////////////////////////////////////////////////////////////////////////////


EXPORT_C HBufC *CEikConsoleScreen::RetrieveL(const TRect &aSelection)
	{
	FlushChars();
	TRect sel=aSelection; 
	TInt len = (sel.iBr.iX-sel.iTl.iX)+iConsoleSize.iWidth*(sel.iBr.iY-sel.iTl.iY);
	if (len==0)
		return NULL;
	if (len<0) 
		return 	MemChrPtr(sel.iBr,-len).AllocL();
	return 		MemChrPtr(sel.iTl, len).AllocL();
	}

// aRect = SCREEN coordinates
EXPORT_C void CEikConsoleScreen::ClearChars(const TRect &aRect,TUint anAtt) 
	{
	FlushChars();
	MemScrClr(aRect,TUint8(anAtt));
	iConsoleControl->ClearChars(Clip(ScrToVis(aRect),TRect(iConsoleSize)),anAtt);
	}

EXPORT_C void CEikConsoleScreen::ScrollChars(const TRect &anArea,const TPoint &aVector)
	{
	FlushChars();
	MemScrScroll(anArea,aVector);
	iConsoleControl->ScrollChars(Clip(ScrToVis(anArea),TRect(iConsoleSize)),aVector);
	}

EXPORT_C void CEikConsoleScreen::ClearScreen()
	{
	TInt cursorHidden = HideCursor(); //FlushChars(); by hidecursor
	iCursor.SetXY(0,0);
	SelectCursor();
	iTopLeft.SetXY(0,iMaxChrExtra); 
	ClearChars(TRect(iConsoleSize),iAtt);
	// datasize + topleft changed
	UpdateScrollBars();  // wont ever actually leave
	if (cursorHidden) 
		DrawCursorWhereNeeded();
	else if (iKeepCursorInSight) 
		DrawInSight(iCursor);
	}

EXPORT_C void CEikConsoleScreen::SetAtt(TUint anAtt)
	{
	// never store the LEFT/RIGHT flag
	TUint newAtt = anAtt;
	if (!(anAtt & ATT_COLORMASK))
		newAtt &= ATT_IGNORE_RIGHTLEFT;
	if (newAtt!=iAtt)
		{
		FlushChars();
		iAtt = newAtt;
		}
	}

EXPORT_C void CEikConsoleScreen::SetAtt(TUint aForegroundGrey16,TUint aBackgroundGrey16)
	{
	SetAtt( ATT_COLORMASK | (aForegroundGrey16 & 0x0F) | ((((aBackgroundGrey16/2) & 0x0F)<<4)) );
	}

EXPORT_C void CEikConsoleScreen::ClearToEndOfLine()
	{
	FlushChars(); //needed before using iCursor!
	ClearChars(TRect(iCursor.iX,iCursor.iY,iConsoleSize.iWidth,iCursor.iY+1),iAtt);
	}


EXPORT_C void CEikConsoleScreen::Cr()
	{
	// !! removed by DavidW, to match E32 console behaviour -- ClearToEndOfLine(); //FlushChars(); by clreol
	iCursor.iX=0;
	}


EXPORT_C void CEikConsoleScreen::Lf()
	{
	TInt cursorHidden=HideCursor(); //FlushChars(); by hidecursor
	iCursor.iY++;
	if (iCursor.iY >= iConsoleSize.iHeight)
		{
		iCursor.iY--;
		if (!iScrollLock)
			{
			//move selection along too!
			iSelection.iTl.iY--; cutmin(iSelection.iTl.iY,-iNoChrExtra);
			iSelection.iBr.iY--; cutmin(iSelection.iBr.iY,-iNoChrExtra);
			// scroll in memory and clear new bottom line
			MemScrScrollUp();
			UpdateScrollBars();
			MemScrClr(TRect(0,iConsoleSize.iHeight-1,iConsoleSize.iWidth,iConsoleSize.iHeight),TUint8(iAtt));
			iConsoleControl->ScrollChars(iVisWin, TPoint(0,-1));  
			Redraw(TRect(0,iVisSize.iHeight-1,iVisSize.iWidth,iVisSize.iHeight)); 
			}
		// restore cursor
		}
	if (cursorHidden) 
		DrawCursorWhereNeeded();	
	else if (iKeepCursorInSight) 
		DrawInSight(iCursor);
	}

EXPORT_C void CEikConsoleScreen::Write(const TDesC &aText)
	{

	if (aText.Length()==0)
	  return;

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// consecutive write handling: save characters until
	//  - any OTHER command is called that MUST come AFTER this write
	//  - we got more than we can buffer
	//	- we encounter a CR/LF as last character (?)
	retry:
	if (iWriteNow==0)
		{
		if (iWriteBuffer.Length() + aText.Length() < 256)
			{
			iWriteBuffer.Append(aText);
/* !! Prevents eg EShell from flushing when using Up arrow (prev command coz no trailing CR/LF
			// check for CR/LF as last character @@@ should we?
			TInt c = iWriteBuffer[ iWriteBuffer.Length()-1 ];
			if ( c==EKeyLineFeed || c==EKeyEnter )
*/ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					FlushChars();
			return;
			}
		else 
			{ 
			FlushChars(); 
			if ( aText.Length() < 256 )
				goto retry;
			// ELSE: write iWriteNow!
			}
		}

	// no cursor while we draw, and forget selection
	TInt cursorHidden=HideCursor();
	InvertRange(iSelection); 

	for ( TInt i=0; i<aText.Length(); )
		{
		// current line full?
		if (iCursor.iX>=iConsoleSize.iWidth)
			{
			iCursor.iX=0; // instead of Cr()
			Lf();
			continue;
			}
		// there are characters to be printed...
		TChar c = aText[i]; 
		if ( c<32 && iAllPrintable==FALSE )
			{
			switch (c)
				{	
				// next char is a FF?
			case  EKeyBell:	
						// BELL @@@
						break;
			case  EKeyBackspace:    
						Left(); // BS
						break;
			case  EKeyTab:	//TAB
						FlushChars();
						for(;;)
							{
							// move character forward (stop at right margin)
							if (iCursor.iX<iConsoleSize.iWidth)
								iCursor.iX++;
                            else
                                break;  
							// break at the first tab that is encountered
							if ( iCursor.iX%8==0) 
								break;
							}
						break;
			case EKeyLineFeed:	
						if (!iPureCRLF) 
							Cr();
						Lf(); // LF
						break;
			case EKeyFormFeed:	
						ClearScreen(); // FF
						break;
			case EKeyEnter:	
						if (iPureCRLF) 	
							Cr(); // CR
						break;
				}
			i++;
			}
		else
			{
			// Determine how many characters can be output at once
			TUint8 att = TUint8(iAtt);
			TInt avail = ( iConsoleSize.iWidth - iCursor.iX );
			TInt outnow=0; 
			if (iAllPrintable) outnow=1;
			while ( outnow<avail && i+outnow < aText.Length() && aText[i+outnow]>=32 ) 
				outnow++;
			MemScrPut(aText.Mid(i,outnow),iCursor,att);
		
			// now let's see how many characters need actually be drawn...
			TPoint pos=ScrToVis(iCursor);
			if (pos.iY>=0 && pos.iY<iVisSize.iHeight)
				{
				TUint start=i;
				TInt len=outnow;
				if (pos.iX<0) 
					{ 
					start-=pos.iX; len+=pos.iX; pos.iX=0; 
					} 
				cutmax(len,iVisSize.iWidth-pos.iX);
				if (len>0)
					{
					TUint drawAtt = att;
					if ( !(drawAtt & ATT_COLORMASK) && (drawAtt & ATT_DOUBLEMASK) && ((pos.iX+iTopLeft.iX) &1) )
						drawAtt |= ATT_RIGHTMASK; // set RIGHT flag for any doublewidth non-color character in an odd column					
					iConsoleControl->DrawChars(aText.Mid(start,len),pos,drawAtt);
					}
				}

			iCursor.iX += outnow;
			i+=outnow;
			}
		}

	InvertRange(iSelection);
	if (iCursor.iX==iConsoleSize.iWidth)
		if (iCursor.iY<iConsoleSize.iHeight-1)
			{ iCursor.iX=0; iCursor.iY++; }
	if (cursorHidden)
		DrawCursorWhereNeeded();
	else if (iKeepCursorInSight) 
		DrawInSight(iCursor);
	}


////////////////////////////////////////////////////////////////////////////////////////
//
//  SELECTION ROUTINES (LOW LEVEL)
//
////////////////////////////////////////////////////////////////////////////////////////
TPoint CEikConsoleScreen::ScrToVis(TPoint aPoint) // ^screen -> ^visible (unclipped)
	{
	return aPoint + TPoint(0,iMaxChrExtra) - iTopLeft; 
	}

TRect CEikConsoleScreen::ScrToVis(const TRect &aRect) // ^screen -> ^visible (clip iVisWin) 
	{
	return Clip(TRect(ScrToVis(aRect.iTl),ScrToVis(aRect.iBr)),iVisWin);
	}

void CEikConsoleScreen::InvertRange(const TRect &aRange) // ^screen
	{
	TRect aRect; CopyNormalisedRange(aRect,aRange);
	for ( TInt y=aRect.iTl.iY; y<=aRect.iBr.iY; y++ )
		{
		TInt from = (y==aRect.iTl.iY) ? aRect.iTl.iX : 0;
		TInt upto = (y==aRect.iBr.iY)   ? aRect.iBr.iX : iConsoleSize.iWidth;
		if (from<upto) 
			iConsoleControl->InvertChars(ScrToVis(TRect(from,y,upto,y+1))); 
		}
	}

void CEikConsoleScreen::InvertOverlap(TPoint aStart,TPoint aEnd,TPoint bStart,TPoint bEnd) // ^absolute
	{
	if (SmallerPoint(aEnd,aStart))
		return;
	if (SmallerPoint(bEnd,bStart)) 
		return;
	TPoint start = SmallerPoint(aStart,bStart) ? bStart : aStart;  
	TPoint end   = SmallerPoint(aEnd  ,bEnd  ) ? aEnd   : bEnd;  	
	if (SmallerPoint(end,start)) 
		return;
	TRect rect(start,end);
	rect.Move(0,-iMaxChrExtra);
	InvertRange(rect); // ^absolute -> ^screen
	}


EXPORT_C void CEikConsoleScreen::SetSelection(const TRect &aSelection) // ^screen
	{
	FlushChars();
	TRect oldRange,newRange;
	CopyNormalisedRange(oldRange,iSelection);		// normalise previous selection
	CopyNormalisedRange(newRange,aSelection);		// normalise new selection
	iSelection=aSelection;

	oldRange.iTl.iY+=iMaxChrExtra; 
	oldRange.iBr.iY+=iMaxChrExtra; 
	newRange.iTl.iY+=iMaxChrExtra; 
	newRange.iBr.iY+=iMaxChrExtra; 

	InvertOverlap(TPoint(0,0), newRange.iTl,oldRange.iTl,oldRange.iBr ); 						// devert beforenew
	InvertOverlap(newRange.iTl,newRange.iBr,TPoint(0,0),oldRange.iTl);							// invert beforeold
	InvertOverlap(newRange.iTl,newRange.iBr,oldRange.iBr,TPoint(0,iMaxChrExtra)+iConsoleSize );	// invert afterold
	InvertOverlap(newRange.iBr,TPoint(0,iMaxChrExtra)+iConsoleSize,oldRange.iTl,oldRange.iBr);	// devert afternew
	}

EXPORT_C void CEikConsoleScreen::SelectCursor()
	{
	FlushChars();
	SetSelection(TRect(iCursor,iCursor)); 
	}

EXPORT_C TRect CEikConsoleScreen::Selection() // ^screen
	{
	FlushChars();
	return iSelection;
	}


