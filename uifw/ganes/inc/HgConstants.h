/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef HGCONSTANTS_H_
#define HGCONSTANTS_H_

// UI Constants
const TInt KMinDragDistance(20);
const TInt KPhysLaunchKeyCount(10);
const TInt KTurboModeLimit(15);
const TInt KKeyScrollingNormalModeMove(20);
const TInt KKeyScrollingTurboModeMove(40);
const TInt KMaxSearchLenght(128);
const TInt KSearchEndTimeOut(1500000); // 0,5 sec
const TInt KFocusTextFontSize(300); // focus text font size in TWIPS
const TInt KMaxPopupTextLength(32);
const TInt KScrollAreaOffset(15);
const TInt KListHighlightInnerRectShrink(10);
const TInt KPopupTextExtraPadding(50);
const TInt KPopupWidthDiv(3);
const TInt KDefaultHighlightTimeout( 50000 ); // 50 ms
const TInt KMaxNumberOfTitleIndicators( 2 );
const TInt KKeyScrollingUpdateInterval( 50000 );
// timeout for long keypress used in markable lists
const TInt KLongPressInterval = 600000; // 0,6 seconds
const TInt KMSKControlId = 3;

// Marquee CONSTANTS
const TInt KHgMarqueeDelay     = 1000000; // start scrolling after a delay of 1 second
const TInt KHgMarqueeInterval  = 100000;  // scroll 10 times in a second
const TInt KHgMarqueeSpeed     = 7;       // scroll 3 pixels at time
const TInt KHgMarqueeLoops     = 1;
const TInt KAknSensibleLength   = 80;
// it does not make any sense to marquee texts longer than this
// since it will take hours and drain battery.
const TInt KAknMaxMarqueeLength = 512;

_LIT( KGanesMif, "\\resource\\apps\\ganes.mif" );
_LIT( KGanesDateString, "%D%M%Y%/0%1%/1%2%/2%3%/3" );
_LIT( KGanesYearString, "%Y%3" );
_LIT( KGanesMonthString, "%N%M%2" );

#endif /* HGCONSTANTS_H_ */
