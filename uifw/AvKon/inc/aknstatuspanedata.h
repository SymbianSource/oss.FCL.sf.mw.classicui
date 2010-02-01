/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon internal data structures for holding system controlled
*                status pane data.
*
*/


#ifndef T_AKNSTATUSPANEDATA_H
#define T_AKNSTATUSPANEDATA_H

#include <avkon.hrh>

/**
* Battery indicator state.
*
* @since S60 3.2
* @lib Avkon
*/
struct TAknBatteryState
    {
    TAknBatteryState() : iBatteryStrength( 0 ),
                         iRecharging( 0 ),
                         iIconState( EAknBatteryIndicatorNormal )
    {};
    /** Battery strength value. */
    TInt                iBatteryStrength;

    /** Charging animation on/off. */
    TBool               iRecharging;

    /** Battery icon ID. */
    TInt                iIconState;

    // Add new fields here if needed...
    };

/**
* Status indicator container state.
*
* @since S60 3.2
* @lib Avkon
*/
struct TAknIndicatorState
    {
    TAknIndicatorState() : iIncallBubbleFlags( 0 ),
                           iIncallBubbleAllowedInUsual( ETrue ),
                           iIncallBubbleAllowedInIdle( EFalse )
    {};

    /**
    * Max number of visible indicators, this may have to
    * be adjusted if ui can show more indicators.
    */
    enum { EMaxVisibleIndicators = 10 };

    /** Array of visible indicator UIDs. */
    TInt visibleIndicators[EMaxVisibleIndicators];

    /** Array of visible indicator states. */
    TInt visibleIndicatorStates[EMaxVisibleIndicators];

    /** Flags for incall bubble. */
    TInt iIncallBubbleFlags;

    /** Incall bubble shown in usual layout. */
    TBool iIncallBubbleAllowedInUsual;

    /** Incall bubble shown in idle layout. */
    TBool iIncallBubbleAllowedInIdle;
    
    /** Incall bubble is temporarily disabled by the framework. */
    TBool iIncallBubbleDisabled;

    // Add new fields here if needed...
    };

/**
* Signal indicator state.
*
* @since S60 3.2
* @lib Avkon
*/
struct TAknSignalState
    {
    TAknSignalState() : iSignalStrength( 0 ),
                        iIconState( 0 )
    {};

    /** Signal strength value. */
    TInt                iSignalStrength;

    /** Signal icon ID. */
    TInt                iIconState;
    // Add new fields here if needed...
    };

/**
* System owned status pane state.
*
* @since S60 3.2
* @lib Avkon
*/
struct TAknStatusPaneStateData
    {
    TAknStatusPaneStateData() : iForegroundSubscriberId( 0 ) {};

    /** ID for the status pane subscriber instance in the foreground. */
    TInt iForegroundSubscriberId;

    /** Battery indicator state. */
    TAknBatteryState iBatteryState;

    /** Signal indicator state. */
    TAknSignalState  iSignalState;

    /** Status indicator container state. */
    TAknIndicatorState   iIndicatorState;

    // Add new fields here if needed...

    typedef TPckg<TAknStatusPaneStateData> TAknStatusPaneStateDataPckg;
    };

#endif // T_AKNSTATUSPANEDATA_H
