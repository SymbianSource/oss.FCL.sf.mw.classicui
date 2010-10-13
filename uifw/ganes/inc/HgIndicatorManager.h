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


#ifndef HGINDICATORMANAGER_H_
#define HGINDICATORMANAGER_H_

#include <e32base.h>

class CWindowGc;
class TAknLayoutRect;
class CGulIcon;
class TAknsItemID;
class TAknWindowComponentLayout;

NONSHARABLE_CLASS( CHgIndicatorManager ) : public CBase
    {
public:

    static CHgIndicatorManager* NewL();

    /**
    * Destructor.
    */
    virtual ~CHgIndicatorManager();

    void InitIndicatorsL( const TSize& aIndicatorSize );

    void DrawIndicators(
            CWindowGc& aGc,
            const TRect& aRect,
            TInt aFlags, 
            TAknWindowComponentLayout aFirstIndicatorLayout, 
            TAknWindowComponentLayout aSecondIndicatorLayout 
            ) const;
    
    TBool DrawIndicator( 
            CWindowGc& aGc,
            TAknLayoutRect& aRect,
            TInt aFlags,
            TBool& aMemIndicator 
            ) const;

    void InitIconL(
            CGulIcon*& aIcon,
            const TAknsItemID& aItemId,
            TInt aIconIndex,
            TInt aMaskIndex,
            TSize aSize);

    void InitColorIconL(
            CGulIcon*& aIcon,
            const TAknsItemID& aItemId,
            TInt aIconIndex,
            TInt aMaskIndex,
            TSize aSize);

    void InitIconL(
            CGulIcon*& aIcon,
            TInt aIconIndex,
            TInt aMaskIndex,
            TSize aSize);
    
    static TInt CountIndicators( TInt aFlags );
    
private:

    CHgIndicatorManager();

    void ConstructL();

private: // data

    // Indicator stuff
    CGulIcon* iDrmIcon; // icon for valid drm rights indicator
    CGulIcon* iDrmExpIcon; // icon for expired drm rights indicator
    CGulIcon* iVideoIcon; // icon for video indicator
    CGulIcon* iMarkIcon; // Icon for selection marking
    CGulIcon* iMmcIcon; // Mmc indicator icon
    CGulIcon* iPlaybackIndicatorIcon; // Playback indicator icon
    CGulIcon* iPauseIndicatorIcon; // Playback pause indicator icon
    CGulIcon* iBrokenPlaylistIcon; // Playback pause indicator icon
    CGulIcon* iBrokenTrackIcon; // Playback pause indicator icon
    CGulIcon* iCorruptedTrackIcon; // Playback pause indicator icon
    CGulIcon* iNewVideoIcon; // new item icon for myVideos 
    CGulIcon* iMassStorageIcon; // new mass storage icon for my videos
    CGulIcon* iPhoneStorageIcon; // phone memory icon for my videos
    CGulIcon* iNewPodcastIcon; // new podcast icon for mpx
    CGulIcon* iPlayedPodcastIcon; // played podcast icon for mpx
    CGulIcon* iCompletelyPlayedPodcastIcon; // completely played podcast icon for mpx
    CGulIcon* iMoveUpIcon; // reorder playlist icon 
    CGulIcon* iMoveDownIcon; // reorder playlist icon
    CGulIcon* iMoveUpDownIcon; // reorder playlist icon

    };


#endif // HGINDICATORMANAGER_H
