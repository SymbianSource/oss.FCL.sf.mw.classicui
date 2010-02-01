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

#include <coeccntx.h>


//
// Class MCoeControlContext
//
EXPORT_C MCoeControlContext::MCoeControlContext()
	{
	}

/** Activates a graphics context for the specified window.

This function is called whenever a control is about to be drawn. Its default 
implementation activates the graphics context given by aGc for the window 
given by aWindow, and calls PrepareContext(). 

This function may be overridden by derived classes.

@param aGc The graphics context to activate. When called from CCoeControl::ActivateGc(), 
this is the system graphics context.
@param aWindow The window for which the graphics context is to be activated. */
EXPORT_C void MCoeControlContext::ActivateContext(CWindowGc& aGc,RDrawableWindow& aWindow) const
	{
	aGc.Activate(aWindow);
	PrepareContext(aGc);
	}

/** Resets the control context. 

The default implementation first resets the graphics context given by aGc, 
and then calls PrepareContext(). The function may be overridden by derived 
classes.

@param aGc The graphics context to be reset. */
EXPORT_C void MCoeControlContext::ResetContext(CWindowGc& aGc) const
	{
	aGc.Reset();
	PrepareContext(aGc);
	}

/** Initialises graphics context settings.

This function should be implemented by derived classes to initialise the graphics 
context, given by aGc, with the required settings. The default implementation 
is empty.

@param aGc The graphics context to be initialised. */
EXPORT_C void MCoeControlContext::PrepareContext(CWindowGc& /*aGc*/) const
	{
	}

EXPORT_C void MCoeControlContext::MCoeControlContext_Reserved1()
	{
	}

EXPORT_C void MCoeControlContext::MCoeControlContext_Reserved2()
	{
	}
//
// Class CCoeBrushAndPenContext
//

CCoeBrushAndPenContext::CCoeBrushAndPenContext()
	{}

/** Allocates and constructs a new brush and pen graphics context object.

@return A pointer to the newly created object */
EXPORT_C CCoeBrushAndPenContext* CCoeBrushAndPenContext::NewL()
	{
	CCoeBrushAndPenContext* self=new(ELeave) CCoeBrushAndPenContext;
	return self;
	} 

/** Prepares the graphics context for drawing the control in its normal state. 

The function uses the brush and pen properties which have been set, or uses 
a black pen and a black solid brush by default. When a bitmap has been set 
a patterned style brush is selected 

@param aGc The window graphics context. */
EXPORT_C void CCoeBrushAndPenContext::PrepareContext(CWindowGc& aGc) const
	{
	if (iBitmap)
		{
		aGc.UseBrushPattern(iBitmap);
		aGc.SetBrushStyle(CGraphicsContext::EPatternedBrush);
		return;
		}
	aGc.SetBrushStyle(iBrushStyle);
	aGc.SetBrushColor(iBrushColor);
	aGc.SetPenColor(iPenColor);
	}

/** Sets the brush style.

@param aBrushStyle The brush style to be used for drawing. */
EXPORT_C void CCoeBrushAndPenContext::SetBrushStyle(CWindowGc::TBrushStyle aBrushStyle)
	{
	iBrushStyle=aBrushStyle;
	}

/** Sets the brush colour.

@param aColor The brush colour. */
EXPORT_C void CCoeBrushAndPenContext::SetBrushColor(TRgb aColor)
	{
	iBrushColor=aColor;
	}

/** Sets the drawing brush pattern bitmap. 

When a bitmap has been set, a patterned style brush is selected automatically. 

@param aBitmap The pattern bitmap. */
EXPORT_C void CCoeBrushAndPenContext::SetBrushBitmap(const CFbsBitmap& aBitmap)
	{
	iBitmap=&aBitmap;
	}

/** Sets the pen colour. 

@param aColor The pen colour. */
EXPORT_C void CCoeBrushAndPenContext::SetPenColor(TRgb aColor)
	{
	iPenColor=aColor;
	}

/** Gets the brush style. 

@return The current brush style. */
EXPORT_C CWindowGc::TBrushStyle CCoeBrushAndPenContext::BrushStyle() const
	{
	return iBrushStyle;
	}

/** Gets the brush colour. 

@return The current brush colour. */
EXPORT_C TRgb CCoeBrushAndPenContext::BrushColor() const
	{
	return iBrushColor;
	}

/** Gets a reference to the bitmap used to pattern the drawing brush.

@return The pattern bitmap. */
EXPORT_C const CFbsBitmap& CCoeBrushAndPenContext::BrushBitmap() const
	{
	return *iBitmap;
	}

/** Gets the pen colour. 

@return The current pen colour. */
EXPORT_C TRgb CCoeBrushAndPenContext::PenColor() const
	{
	return iPenColor;
	}


//
// Class MCoeControlBrushContext deprecated as of Release 005u
//

EXPORT_C MCoeControlBrushContext::MCoeControlBrushContext()
	{
	}

/** Sets the brush settings for the specified graphics context. 

If iBitmap is set, it sets this as the brush pattern and sets the brush style 
to EPatternedBrush. Otherwise, it sets the brush style and brush colour using 
the values of iBrushStyle and iBrushColor.

@param aGc The graphics context to set. */
EXPORT_C void MCoeControlBrushContext::PrepareContext(CWindowGc& aGc) const
	{
	if (iBitmap)
		{
		aGc.UseBrushPattern(iBitmap);
		aGc.SetBrushStyle(CGraphicsContext::EPatternedBrush);
		return;
		}
	aGc.SetBrushStyle(iBrushStyle);
	aGc.SetBrushColor(iBrushColor);
	}
