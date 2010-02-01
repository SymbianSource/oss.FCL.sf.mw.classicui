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

#ifndef __COECCNTX_H__
#define __COECCNTX_H__

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>

/** Interface to allow sharing of graphics settings between controls. 

The interface provides functions to set the graphics context of a control 
before drawing. If a control has its iContext member set, the UI Control Framework 
calls functions defined by this interface when a control is about to be drawn. 
Developers must implement PrepareContext(), which is called by the framework, 
to initialise the control's window with the required graphics settings.

To use control contexts, a control should inherit from an MCoeControlContext-derived 
class. To share the context between controls, this control should then be 
set as the context for all controls that wish to share it. This is done by 
setting the iContext member of each of the controls, using CCoeControl::SetControlContext() 
and CCoeControl::CopyControlContextFrom(). 

@publishedAll 
@released */
class MCoeControlContext
	{
public:
	IMPORT_C virtual void ActivateContext(CWindowGc& aGc,RDrawableWindow& aWindow) const;
	IMPORT_C virtual void ResetContext(CWindowGc& aGc) const;
	IMPORT_C virtual void PrepareContext(CWindowGc& aGc) const;
protected:
	IMPORT_C MCoeControlContext();
	
private:
	IMPORT_C virtual void MCoeControlContext_Reserved1();	
	IMPORT_C virtual void MCoeControlContext_Reserved2();
	
private:
	TInt iMCoeControlContext_Reserved1;
	};

/** Brush and pen graphics context. 

This class allows an MCoeControlContext to be instantiated and used to set 
brush and pen properties before drawing a control. 

@publishedAll 
@released */
class CCoeBrushAndPenContext : public CBase, public MCoeControlContext
	{
public:
	IMPORT_C static CCoeBrushAndPenContext* NewL();
	//
	IMPORT_C void SetBrushStyle(CWindowGc::TBrushStyle aBrushStyle);
	IMPORT_C void SetBrushColor(TRgb aColor);
	IMPORT_C void SetBrushBitmap(const CFbsBitmap& aBitmap);
	IMPORT_C void SetPenColor(TRgb aColor);
	//
	IMPORT_C CWindowGc::TBrushStyle BrushStyle() const;
	IMPORT_C TRgb BrushColor() const;
	IMPORT_C const CFbsBitmap& BrushBitmap() const;
	IMPORT_C TRgb PenColor() const;
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	CCoeBrushAndPenContext();
private:
	CWindowGc::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	const CFbsBitmap* iBitmap;
	TRgb iPenColor;
	};


/** Protocol for sharing brush settings used in graphics operations. 

It can be used to set brush and pen properties before drawing a control.

The mixin provides a default implementation of a control context. It implements 
PrepareContext() to initialise brush settings used in graphics operations. 
Its data members are public so that the brush style, brush colour and brush 
pattern can be set by application code.

@publishedAll
@deprecated */
class MCoeControlBrushContext : public MCoeControlContext
	{
public:
	/** Cause vtable & typeinfo to be exported */
	IMPORT_C MCoeControlBrushContext();
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
public:
	/** Brush style. (Not required if iBitmap is set.) */
	CWindowGc::TBrushStyle iBrushStyle;
	/** Brush colour. (Not required if iBitmap is set.) */
	TRgb iBrushColor;
	/** Brush pattern. */
	const CFbsBitmap* iBitmap;

private:
	TInt iMCoeControlBrushContext_Reserved1;
	};

#endif
