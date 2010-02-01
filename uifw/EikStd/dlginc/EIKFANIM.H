/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/

#ifndef __EIKFANIM_H__
#define __EIKFANIM_H__

#include <AknsEffectAnim.h>
#include <coemain.h> // For MCoeForegroundObserver
#include <babitflags.h>

/**
* Interface for CEikFormAnim observer.
*
* @since 3.0
*/
NONSHARABLE_CLASS( MEikFormAnimObserver )
    {
    public:
        virtual void AnimFrameReady() =0;
        virtual TBool AnimDrawHighlightBackground( CFbsBitGc& aGc ) =0;
    };

/**
* Wrapper class for using AknSkins effect animations. Used by
* CEikCaptionedControls and stored as a singleton in CEikDialogPageContainer
* (captioned controls acquire/unacquire the animation as they are set/unset
* current).
*
* @since 3.0
*/
NONSHARABLE_CLASS( CEikFormAnim ):
    public CActive,
    public MCoeForegroundObserver,
    public MAknsEffectAnimObserver
    {
public:
    enum TFlag
        {
        /**
        * If set, animation creation is attempted. If not set, animation will
        * never be created.
        */
        EFlagUseAnimation = 0
        };

private:
    CEikFormAnim();
    void ConstructL();

public:
    static CEikFormAnim* NewL();
    ~CEikFormAnim();

    void SetObserver( MEikFormAnimObserver* aObserver );
    MEikFormAnimObserver* Observer();

    void SetHighlightSize( const TSize& aItemCellSize );
    CAknsEffectAnim* Animation() const;

    void Play();
    void Pause();

    void ChangeHighlightBackground();

    TSize Size() const;
    void ReleaseAnimation();

public: // Implementation of MCoeForegroundObserver
    void HandleGainingForeground();
    void HandleLosingForeground();

public: // Implementation of MAknsEffectAnimObserver
    void AnimFrameReady( TInt aError, TInt );

public: // CActive overloads
    void DoCancel();
    void RunL();

private: // New internal methods
    void NoAnimIfError( TInt aError );
    void UseNoAnimation();
    void PostDeleteAnimation();
    void CreateAnimationL( const TSize& aHighlightSize );
    void DoResizeL( const TSize& aHighlightSize, TBool aAboutToStart );

private:
    CAknsEffectAnim* iAnimation;
    /**
    * Stored flags are explained in enumeration TFlags.
    */
    TBitFlags32 iAnimFlags;
    MEikFormAnimObserver* iObserver;
    };

#endif
