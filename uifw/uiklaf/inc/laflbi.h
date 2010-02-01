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


#ifndef __LAFLBI_H__
#define __LAFLBI_H__

#include <e32std.h>
#include <gdi.h>

class TRect;
class CWindowGc;

/**
 * @internal
 * Do not use
 */
class LafListItemDrawer
	{
public:
	class TLidColors;
public:
	IMPORT_C static void DrawFrame(CWindowGc& aGc,const TRect& aRect,TInt aFlags, const TLidColors& aColors);	
	inline static TInt DefaultMarkColumnWidth();
	inline static TInt DefaultPostMarkColumnSpace();
private:
	enum TConstantType
		{
		EDefaultMarkColumnWidth,
		EDefaultPostMarkColumnSpace
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstant);
	};

/**
 * @internal
 * Do not use
 */
class LafListItemDrawer::TLidColors
	{
public:
	IMPORT_C TLidColors(TRgb aTextColor,
						TRgb aBackColor,
						TRgb aHighlightedTextColor,
						TRgb aHighlightedBackColor,
						TRgb aDimmedTextColor,
						TRgb aDimmedBackColor,
						TRgb aMarkColor);
public:
	TRgb iTextColor;
	TRgb iBackColor;
	TRgb iHighlightedTextColor;
	TRgb iHighlightedBackColor;
	TRgb iDimmedTextColor;
	TRgb iDimmedBackColor;
	TRgb iMarkColor;
	};

/**
 * Returns the default width for the tick mark.  The tick mark usually indicates 
 * if an item is selected or not.
 *
 * @since App-Framework_6.1
 */
inline TInt LafListItemDrawer::DefaultMarkColumnWidth()
	{
	return Constant(EDefaultMarkColumnWidth);
	}

/**
 * Returns the default gap width between the tick mark column rectangle and where the 
 * item contents begin.  The tick mark usually indicates if an item is selected or not.
 *
 * @since App-Framework_6.1
 */
inline TInt LafListItemDrawer::DefaultPostMarkColumnSpace()
	{
	return Constant(EDefaultPostMarkColumnSpace);
	}


/**
 * @internal
 * Do not use
 */
class LafTextListItemDrawer
	{
public:
	IMPORT_C static void DrawNormalText(const TDesC& aDes,const CFont& aFont,CWindowGc& aGc,
			const TRect& aItemTextRect,TInt aBaseLineOffset,
			CGraphicsContext::TTextAlign aAlign);
	IMPORT_C static TInt PrepareItemAttribute(TInt aFlags,TBool aItemIsCurrent,
								TBool aItemIsSelected,TBool aViewIsEmphasized);
	};

#endif //__LAFLBI_H__
