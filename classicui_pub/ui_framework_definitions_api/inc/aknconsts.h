/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
*     The file contains some avkon constants (mainly for internal use).
*
*
*/


#ifndef AKNCONSTS_H
#define AKNCONSTS_H

#include <avkon.hrh>

// Status pane constants

/**
 * @deprecated
 */
const TInt KStatusPaneBackgroundGraphicsColorIdle = 215;

/**
 * @deprecated
 */
const TInt KStatusPaneBackgroundGraphicsColorUsual = 237;

/**
 * @deprecated
 */
const TInt KStatusPaneBackgroundColor = 0;

/**
 * @deprecated
 */
const TInt Kqpn_height_status_pane_idle = 56;

/**
 * @deprecated
 */
const TInt Kqpn_height_status_pane_usual = 44;

/**
 * @deprecated
 */
struct SLafIconLayout
    {
    TInt left;
    TInt top;
    TInt right;
    TInt bottom;
    TInt width;
    TInt height;
    };

/**
 * @deprecated
 */
struct SLafTextCharasteristics
    {
    TInt color;
    TInt left;
    TInt right;
    TInt baseline;
    TInt width;
    TInt justification;
    };

/** Navi pane constants */
/**
 * @deprecated
 */
const TInt KNoValue = -1000;

/**
 * @deprecated
 */
const TInt KUseOtherValue = -1001;

/**
 * @deprecated
 */
const TInt KUseBaseValue = 0;


/**
 * @deprecated
 */
const struct SLafIconLayout KStatusPaneBackgroundGraphics =
    {1,29,KNoValue,KNoValue,174,15};

/**
 * @deprecated
 */
const struct SLafIconLayout KStatusPaneNaviPaneWipeGraphics =
    {0, 1, KNoValue, KNoValue, 174, 15};

/**
 * @deprecated
 */
const struct SLafIconLayout KStatusPaneNaviPaneWipeBitmapOffset =
    {55, 0, KNoValue, KNoValue, 174, 15};

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviArrowLeft =
    {0,0,KNoValue,KNoValue,4,16};

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviArrowRight[2] =
    {
        {KNoValue,0,5,KNoValue,4,16},
        {KNoValue,0,1,KNoValue,4,16}
    };


/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviTabBitmap =
    {4,0,KNoValue,KNoValue,107,16};

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviTabIcon2[2] =
    {
        {17,3,KNoValue,KNoValue,35,11},
        {63,3,KNoValue,KNoValue,35,11}
    };

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviTabIconLong2[2] =
    {
        {17,3,KNoValue,KNoValue,74,11},
        {24,3,KNoValue,KNoValue,74,11}
    };

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviTabIcon3[3] =
    {
        {16,3,KNoValue,KNoValue,22,11},
        {47,3,KNoValue,KNoValue,22,11},
        {78,3,KNoValue,KNoValue,22,11}
    };


/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviTabIcon4[4] =
    {
        {14,3,KNoValue,KNoValue,18,11},
        {37,3,KNoValue,KNoValue,18,11},
        {60,3,KNoValue,KNoValue,18,11},
        {83,3,KNoValue,KNoValue,18,11}
    };

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviTabIconLong3[3] =
    {
        {17,3,KNoValue,KNoValue,67,11},
        {24,3,KNoValue,KNoValue,67,11},
        {31,3,KNoValue,KNoValue,67,11}
    };

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnNaviTabText2[2] =
    {
        {215,17,66,12,36,ECenter},
        {215,63,20,12,36,ECenter}
    };

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnNaviTabTextLong2[2] =
    {
        {215,17,29,12,74,ECenter},
        {215,24,22,12,74,ECenter}
    };

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnNaviTabText3[3] =
    {
        {215,17,81,12,21,ECenter},
        {215,48,50,12,21,ECenter},
        {215,79,19,12,21,ECenter}
    };

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnNaviTabText4[4] =
    {
        {215,17,89,12,13,ECenter},
        {215,40,66,12,13,ECenter},
        {215,63,43,12,13,ECenter},
        {215,86,20,12,13,ECenter}
    };


/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnNaviTabTextLong3[3] =
    {
        {215,17,36,12,67,ECenter},
        {215,24,29,12,67,ECenter},
        {215,31,22,12,67,ECenter}
    };

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviTabIcon1 =
    {20,3,KNoValue,KNoValue,35,11};

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnNaviTabText1 =
    {0,62,25,13,33,ECenter};


/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnNaviInformation[2] =
    {
        {0, 8, 12, 12, 100, ECenter},
        {0, 8, 8, 12, 85, ECenter}
    };

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnAdditionalInformation =
    {0, 6, 3, 12, 92, ELeft};

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnHelpHints =
    {0, 6, 4, 12, 110, ELeft};

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviIcon =
    {20, 3, KNoValue, KNoValue, 35, 11};

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KNaviQgnNaviIconText =
    {0, 62, 25, 13, 33, ECenter};

/**
 * @deprecated
 */
const struct SLafIconLayout KNaviQgnNaviEditingStatusIcon =
    {75, 4, KNoValue, KNoValue, 110, 9};

/**
 * Following constants determine the layout of tabs in the navigation pane.
 * Constants are used with CAknTabGroup::SetTabFixedWidthL(TInt aWidth) method.
 */

/** Constant for two tabs layout */
const TInt KTabWidthWithTwoTabs = EAknTabWidthWithTwoTabs;
/** Constant for two long tabs layout */
const TInt KTabWidthWithTwoLongTabs = EAknTabWidthWithTwoLongTabs;
/** Constant for three tabs layout */
const TInt KTabWidthWithThreeTabs = EAknTabWidthWithThreeTabs;
/** Constant for three long tabs layout */
const TInt KTabWidthWithThreeLongTabs = EAknTabWidthWithThreeLongTabs;
/** Constant for four tabs layout */
const TInt KTabWidthWithFourTabs = EAknTabWidthWithFourTabs;
/** Constant for one tab layout */
const TInt KTabWidthWithOneTab = EAknTabWidthWithOneTab;

/** @deprecated */
const TInt KNaviTabMargins=0;
/** @deprecated */
const TInt KNaviTabActiveTextColor = 215;
/** @deprecated */
const TInt KNaviTabInactiveTextColor = 129;
/** @deprecated */
const TInt KNaviTabOneTabTextColor = 0;


/** @internal */
const TInt KTabNumberOfTabBitmaps = 14;
/** @internal */
const TInt KTabIndexOfFirstTabBitmapInTwoTabsSet = 0;
/** @internal */
const TInt KTabIndexOfLastTabBitmapInTwoTabsSet = 1;
/** @internal */
const TInt KTabIndexOfFirstTabBitmapInTwoLongTabsSet = 2;
/** @internal */
const TInt KTabIndexOfLastTabBitmapInTwoLongTabsSet = 3;
/** @internal */
const TInt KTabIndexOfFirstTabBitmapInThreeTabsSet = 7;
/** @internal */
const TInt KTabIndexOfLastTabBitmapInThreeTabsSet = 9;
/** @internal */
const TInt KTabIndexOfFirstTabBitmapInThreeLongTabsSet = 4;
/** @internal */
const TInt KTabIndexOfLastTabBitmapInThreeLongTabsSet = 6;
/** @internal */
const TInt KTabIndexOfFirstTabBitmapInFourTabsSet = 10;
/** @internal */
const TInt KTabIndexOfLastTabBitmapInFourTabsSet = 13;


/** Title pane constants */
/**
 * @deprecated
 */
const struct SLafTextCharasteristics KTitleQgnOneLineLabel[2] =
    {
        { 215, 1, 3, 22, 104, ELeft},
        { KUseOtherValue, KUseOtherValue, KUseOtherValue, KUseOtherValue, 97, KUseOtherValue}
    };

/**
 * @deprecated
 */
const struct SLafTextCharasteristics KTitleQgnTwoLineLabel[2] =
    {
        { 215, 1, 3, 11, 104, ELeft},
        { KUseOtherValue, KUseOtherValue, KUseOtherValue, 25, 97, KUseOtherValue}
    };

/**
 * @deprecated
 */
const struct SLafIconLayout KTitleQgnLogoImage = { 2, 2, 2, 1, 97, 25};

/**
 * Title pane default text if not any other default text is avilable
 * @internal
 */
_LIT(KTitlePaneDefaultText, " ");

#ifndef __GMXMLCONSTANTS_H__
/**
 * @deprecated
 *
 * Notice that GMXMLConstants.h contains same constant with different value. 
 */
_LIT(KNewLine, "\n");
#endif


/** Context pane constants */

/**
 * @deprecated
 */
const struct SLafIconLayout KContextQgnBitmap =
    { 0, 0, KNoValue, KNoValue, 44, 44};

/** Battery pane constants */

/** 
 * Constant for battery level minimum value
 * @deprecated
 */
const TInt KBatteryLevelMin = 0;
/** 
 * Constant for battery level maximum value
 * @deprecated
 */
const TInt KBatteryLevelMax = 7;

/**
 * @deprecated
 */
const TInt KBatteryBitmapOffsets[KBatteryLevelMax] =
    {25,21,17,13,9,5,1}; // Levels 1,2,3,4,5,6,7

/**
 * @deprecated
 */
const struct SLafIconLayout KBatteryQgnIndiBatteryStrength =
    {KNoValue,0,0,KNoValue,12,29};

/**
 * @deprecated
 */
const struct SLafIconLayout KBatteryQgnIndiBatteryIcon =
    {KNoValue,29,0,KNoValue,12,15};


/** Signal pane constants */

/** 
 * Constant for signal level minimum value
 * @deprecated
 */
const TInt KSignalLevelMin = 0;
/** 
 * Constant for signal level maximum value
 * @deprecated
 */
const TInt KSignalLevelMax = 7;

/**
 * @deprecated
 */
const TInt KSignalBitmapOffsets[KSignalLevelMax] =
    {25,21,17,13,9,5,1}; // Levels 1,2,3,4,5,6,7

/**
 * @deprecated
 */
const struct SLafIconLayout KSignalQgnIndiSignalStrength =
    {0,0,KNoValue,KNoValue,12,29};

/**
 * @deprecated
 */
const struct SLafIconLayout KSignalQgnIndiSignalIcon =
    {0,29,KNoValue,KNoValue,12,15};


// Common

/**
 * Location of the common dialogs bitmap file
 */
_LIT(KCommonDialogsBitmapFile,  "z:\\resource\\apps\\commondialogs.mbm");

/**
 * Location of the call status bitmap file
 */
_LIT(KCallStatusBitmapFile,     "z:\\resource\\apps\\callstatus.mbm");

/**
 * Location of the memory card ui bitmap file
 */
_LIT(KMemoryCardUiBitmapFile,   "z:\\resource\\apps\\aknmemorycardui.mbm");

/**
 * Location of the avkon bitmap file
 */
_LIT(KAvkonBitmapFile,          "z:\\resource\\apps\\avkon2.mbm");

/**
 * Location of the variated bitmaps bitmap file
 */
_LIT(KAvkonVariatedBitmapsFile, "z:\\resource\\apps\\variatedbitmaps.mbm");


/**
 * @deprecated
 */
const TInt KAknSoftkeyPaneHeight = 20;

/**
 * Default size of the window server buffer.
 */
const TInt KAknDefaultWsBufferSize = 7000;
/**
 * Maximum size of the window server buffer.
 * UI components and applications may request window server buffer size up to
 * this size with CAknEnv::Static()->RequestWsBuffer() method.
 */
const TInt KAknMaxWsBufferSize = 16000;


// Small status pane
/**
 * @deprecated
 */
const TInt KMinSpaceBetweenIconsInPixels = 3;

/**
 * @deprecated
 */
const struct SLafIconLayout KSmallStatusPaneIndicator =
    {0,3,KNoValue,KNoValue,171,15};
/**
 * @deprecated
 */
const struct SLafIconLayout KSmallStatusPaneTextIndicator =
    {2,2,KNoValue,KNoValue,171,11};
/**
 * @deprecated
 */
const struct SLafIconLayout KSmallStatusPaneSecureStateIndicator =
    {0,4,KNoValue,KNoValue,10,9};
/**
 * @deprecated
 */
const struct SLafIconLayout KSmallStatusPaneWmlWaitGlobeIndicator =
    {82,1,80,KNoValue,13,13};
/**
 * @deprecated
 */
const struct SLafIconLayout KSmallStatusPaneWaitBarIndicator =
    {3,3,KNoValue,KNoValue,77,9};
/**
 * @deprecated
 */
const struct SLafIconLayout KSmallStatusPaneProgressBarIndicator =
    {3,3,KNoValue,KNoValue,77,9};
/**
 * @deprecated
 */
const struct SLafIconLayout KSmallStatusPaneGprsIndicator =
    {KNoValue,KNoValue,KNoValue,KNoValue,12,15};

// Mirrored statuspane for A&H
/**
 * @deprecated
 */
const struct SLafIconLayout KMirroredStatusPaneNaviPaneWipeBitmapOffset =
    {0, 0, 55, KNoValue, 174, 15};

/**
 * @deprecated
 */
const struct SLafIconLayout KMirroredNaviQgnNaviArrowLeft[2] =
    {
        {5,0,KNoValue,KNoValue,4,16},
        {1,0,KNoValue,KNoValue,4,16}
    };

/**
 * @deprecated
 */
const struct SLafIconLayout KMirroredNaviQgnNaviArrowRight =
    {0,0,KNoValue,KNoValue,4,16};

/**
 * @deprecated
 */
const struct SLafIconLayout KMirroredNaviQgnNaviTabBitmap =
    {9,0,KNoValue,KNoValue,107,16};


// Naviwipe related constants
/**
 * @deprecated
 */
struct SNaviWipePart
    {
    TInt start;
    TInt end;
    };

// Note that values are for skin navi wipes (176x15). Not for
// default avkon LAF navi wipes (174x15).
/**
 * @deprecated
 */
const struct SNaviWipePart KNaviWipeSignalPanePart =
    {0,12};
/**
 * @deprecated
 */
const struct SNaviWipePart KNaviWipeContextPanePart =
    {12,56};
/**
 * @deprecated
 */
const struct SNaviWipePart KNaviWipeNaviPanePart =
    {56,176};

/**
 * @deprecated
 */
const struct SNaviWipePart KNaviWipeSignalPanePartMirrored =
    {164,176};
/**
 * @deprecated
 */
const struct SNaviWipePart KNaviWipeContextPanePartMirrored =
    {120,164};
/**
 * @deprecated
 */
const struct SNaviWipePart KNaviWipeNaviPanePartMirrored =
    {0,120};


// Keyboard delays and repeat periods
/**
 * Constant for the delay in microseconds before the key repeating starts
 * when the key is pressed down.
 */
const TInt KAknKeyboardRepeatInitialDelay = 600000;

/** 
 * Keyboard repeat rate in microseconds. Key events are repeated
 * at this rate when the key is pressed down. 
 *
 * Editor repeat rate is set in KAknEditorKeyboardRepeatRate constant
 */
const TInt KAknStandardKeyboardRepeatRate = (1000000/6);

/** 
 * Keyboard repeat rate in editors in microseconds. Key events are repeated
 * at this rate in editors when the key is pressed down.
 */
const TInt KAknEditorKeyboardRepeatRate = (1000000/10);



/**
 * Value for unset screen mode. 
 */
const TInt KAknScreenModeUnset = -1;

#endif // AKNCONSTS_H

