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

#if !defined(__GULDEF_H__)
#define __GULDEF_H__

/** The sides on which borders can be adjacent. 

@publishedAll
@released */
enum TGulAdjacent
	{
	/** Indicates that rectangle borders are not adjacent. */
	EGulAdjNone		=0x00,
	/** Adjacent at the top. */
	EGulAdjTop		=0x01,
	/** Adjacent at the bottom. */
	EGulAdjBottom	=0x02,
	/** Adjacent at the left. */
	EGulAdjLeft		=0x04,
	/** Adjacent at the right. */
	EGulAdjRight	=0x08
	};
	
/** Symbian light grey.

@publishedAll
@released */
#define KRgbDitheredLightGray 	TRgb(204,204,204)

/** Symbian dithered grey.

@publishedAll
@released */
#define KRgb1in4DitheredGray 	TRgb(238,238,238)

/** Symbian green.

@publishedAll
@released */
#define KRgbSymbianGreen 		TRgb(0,153,153)

/** Symbian light green.

@publishedAll
@released */
#define KRgbSymbianGreenLight	TRgb(0,183,183)

/** Symbian blue.

@publishedAll
@released */
#define KRgbSymbianBlue 		TRgb(0,102,153)

/** Symbian dark blue.

@publishedAll
@released */
#define KRgbSymbianBlueDark		TRgb(0,72,123)

/** Symbian orange.

@publishedAll
@released */
#define KRgbSymbianOrange		TRgb(255,218,155)

#endif
