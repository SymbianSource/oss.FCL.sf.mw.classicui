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


#ifndef __LAFCMBUT_H__
#define __LAFCMBUT_H__

#include <gulbordr.h>
#include <coecntrl.h>
#include <lafmain.h>

class TDrawState;
class MLafEnv;

/**
 * @internal
 * Do not use
 */
class LafCommandButtonBase
	{
public:
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
	IMPORT_C static void GetBorder(TGulBorder& aBorder, TInt aDrawState, TInt aFlags,const CCoeControl& aButtonBase,TBool aIsDefaultButton);
	IMPORT_C static TInt ComponentOffset(TInt aDrawState, TInt aFlags);
	IMPORT_C static void PrepareContext(CWindowGc& aGc,TInt aDrawState,
									   const MLafEnv& aLafEnv,
									   const CCoeControl& aButtonBase);
	IMPORT_C static void Draw(const MLafEnv& aLafEnv, const CCoeControl& aMatchedControl,
							 CWindowGc& aGc,
							 const TGulBorder& aBorder,
							 TInt aDrawOffset,TInt aDrawState,
							 TMargins8 aGutters,
							 TBool aIsDefaultButton);
	IMPORT_C static void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList);
public:
	inline static TInt ImageMargin();
	inline static TInt LabelMargin();
	inline static TInt IntraComponentMargin();
private:
	enum TConstantType
		{
		EImageMargin,
		ELabelMargin,
		EIntraComponentMargin
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstant);
private:
	static void DrawSelection(const TGulBorder& aBorder,const TRect& aRect,CWindowGc& aGc);
	};

/**
 * Returns the margin required on all sides of the command button base image
 *
 * @since App-Framework_6.1
 */
inline TInt LafCommandButtonBase::ImageMargin()
	{//static
	return Constant(EImageMargin);	
	}

/**
 * Returns the margin required on all sides of the command button base label
 *
 * @since App-Framework_6.1
 */
inline TInt LafCommandButtonBase::LabelMargin()
	{//static
	return Constant(ELabelMargin);	
	}

/**
 * Returns the margin required between the two components of a command button base
 *
 * @since App-Framework_6.1
 */
inline TInt LafCommandButtonBase::IntraComponentMargin()
	{//static
	return Constant(EIntraComponentMargin);	
	}

/**
 * @internal
 * Do not use
 */
class LafCommandButton
	{
public:
	IMPORT_C static TMargins8 Margins();
	};

/**
 * @internal
 * Do not use
 */
class LafInverterCommandButton
	{
public:
	IMPORT_C static TMargins8 Margins();
	};

/**
 * @internal
 * Do not use
 */
class LafBitmapButton
	{
public:
	IMPORT_C static TMargins8 Margins();
	};

/**
 * @internal
 * Do not use
 */
class LafTextButton
	{
public:
	IMPORT_C static TMargins8 Margins();
	};

/**
 * @internal
 * Do not use
 */
class LafTwoPictureCommandButton
	{
public:
	IMPORT_C static void GetDefaultBorder(TGulBorder& aBorder);
	IMPORT_C static TMargins8 Margins();
	IMPORT_C static void GetBorderColors(TGulBorder::TColors& aBorderColors,const MLafEnv& aEnv,const CCoeControl& aMatchedControl);
	};

#endif
