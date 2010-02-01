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


#include <AknsDrawUtils.h>

#include "EIKFANIM.H"

/**
* High priority is well argumented because running the active object will
* result in animation deletion -> resources released.
*/
CEikFormAnim::CEikFormAnim(): CActive( EPriorityHigh )
    {
    // Derived from CActive (derives from CBase) -> members zeroed
    }

void CEikFormAnim::ConstructL()
    {
    iAnimFlags.Set( EFlagUseAnimation ); // Animations are created by default
    CActiveScheduler::Add( this );
    }

CEikFormAnim* CEikFormAnim::NewL()
    {
    CEikFormAnim* self = new(ELeave) CEikFormAnim();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

CEikFormAnim::~CEikFormAnim()
    {
    Cancel();

    // Stop receiving foreground events
    CCoeEnv* env = CCoeEnv::Static();
    env->RemoveForegroundObserver( *this );

    delete iAnimation;
    }

void CEikFormAnim::SetObserver( MEikFormAnimObserver* aObserver )
    {
    iObserver = aObserver;
    }

MEikFormAnimObserver* CEikFormAnim::Observer()
    {
    return iObserver;
    }

void CEikFormAnim::NoAnimIfError( TInt aError )
    {
    if( KErrNone != aError )
        UseNoAnimation();
    }

/**
* Reconfigures the animation size. Animation construction is attempted when
* this method is called for the first time.
*
* @param aItemCellSize  The size of the list cell highlight
*/
void CEikFormAnim::SetHighlightSize( const TSize& aItemCellSize )
    {
    if( iAnimation ) // Animation exists -> try to resize
        {
        if( iAnimation->Size() == aItemCellSize )
            {
            return;
            }

        // Resize animation
        TBool aboutToStart = ETrue;
        if( iAnimation->State() == EAknsAnimStateStopped )
            aboutToStart = EFalse;

        TRAPD( err, DoResizeL( aItemCellSize, aboutToStart ) );
        if( KErrNone != err )
            {
            // Repaint is not allowed inside resize
            UseNoAnimation();
            }
        }
    else if( iAnimFlags.IsSet( EFlagUseAnimation ) )
        {
        // This must be the first call because animation does not exist.
        TRAPD( err, CreateAnimationL( aItemCellSize ) );
        if( KErrNone != err )
            {
            // Repaint is not allowed inside resize
            UseNoAnimation();
            }
        }
    }

CAknsEffectAnim* CEikFormAnim::Animation() const
    {
    return iAnimation;
    }

/**
* Falls back to normal rendering.
*/
void CEikFormAnim::UseNoAnimation()
    {
    delete iAnimation;
    iAnimation = NULL;

    // Do not attempt to create animations in the future
    iAnimFlags.Clear( EFlagUseAnimation );

    // Stop receiving foreground events
    CCoeEnv* env = CCoeEnv::Static();
    env->RemoveForegroundObserver( *this );
    }

void CEikFormAnim::Play()
    {
    if( iAnimation )
        {
        if( EAknsAnimStatePaused == iAnimation->State() )
            {
            NoAnimIfError( iAnimation->Continue() );
            }
        else if( EAknsAnimStateStopped == iAnimation->State() )
            {
            TRAPD( err, DoResizeL( iAnimation->Size(), ETrue ) );
            NoAnimIfError( err );

            if( KErrNone != err )
                return;

            NoAnimIfError( iAnimation->Start() );
            }
        }
    }

void CEikFormAnim::Pause()
    {
    if( iAnimation )
        {
        NoAnimIfError( iAnimation->Pause() );
        }
    }

void CEikFormAnim::ChangeHighlightBackground()
    {
    // Every time the current list item is changed we need to change the
    // animation input layer (animated element is the highlight bacground that
    // can differ between highlight positions).
    if( iAnimation && iObserver )
        {
        if( iAnimation->State() == EAknsAnimStateStopped )
            {
            // Input layers don't exist when stopped or finished. We need to
            // resize to create the input layers and to update the output
            // layer.
            TRAPD( err, DoResizeL( iAnimation->Size(), EFalse ) );
            NoAnimIfError( err );
            }
        else // Either paused, running or finished
            {
            // Update the highlight background
            if( iAnimation->InputRgbGc() )
                iObserver->AnimDrawHighlightBackground( *iAnimation->InputRgbGc() );

            // We need to update the output frame (otherwise the highlight
            // would drawn with the old output before the next new animation
            // frame).
            NoAnimIfError( iAnimation->UpdateOutput() );
            }
        }
    }

TSize CEikFormAnim::Size() const
    {
    if( iAnimation )
        return iAnimation->Size();
    return TSize( 0, 0 );
    }

void CEikFormAnim::ReleaseAnimation()
    {
    delete iAnimation;
    iAnimation = NULL;

    iObserver = NULL;

    CCoeEnv* env = CCoeEnv::Static();
    env->RemoveForegroundObserver( *this );

    iAnimFlags.Set( EFlagUseAnimation );
    }

/**
* The application has gained foreground -> animation should be continued.
*/
void CEikFormAnim::HandleGainingForeground()
    {
    // Animation on focused captioned control will receive FocusGained after
    // gaining foreground -> starting animation is postponed there.
    }

/**
* The application lost foreground -> no running animation (even if the
* application is partially visible).
*/
void CEikFormAnim::HandleLosingForeground()
    {
    if( iAnimation )
        {
        NoAnimIfError( iAnimation->Stop() );
        }
    }

void CEikFormAnim::AnimFrameReady( TInt aError, TInt )
    {
    if( KErrNone != aError )
        {
        // Animation has failed to run -> schedule the animation for
        // deletion to fall back to normal rendering.
        PostDeleteAnimation();
        }
    else if( iObserver && iAnimation ) // Frame ok
        {
        iObserver->AnimFrameReady();
        }
    }

void CEikFormAnim::DoCancel()
    {
    // Required method, but not needed
    }

/**
* Postponed animation deletion is done here.
*/
void CEikFormAnim::RunL()
    {
    UseNoAnimation();
    }

/**
* Schedules the animation for deletion by activating the extension itself.
* Deletion is postponed because in many error/failure occasions the caller has
* been animation and direct deletion is possibly not safe (because function
* stack would return through the deleted object).
*/
void CEikFormAnim::PostDeleteAnimation()
    {
    TRequestStatus* status = &iStatus;
    User::RequestComplete( status, KErrNone );
    SetActive();
    }

/**
* @param aHilightSize  The size of the list cell highlight
*/
void CEikFormAnim::CreateAnimationL( const TSize& aHighlightSize )
    {
    // Create animation
    CCoeEnv* env = CCoeEnv::Static();
    env->AddForegroundObserverL( *this );

    delete iAnimation;
    iAnimation = NULL;

    iAnimation = CAknsEffectAnim::NewL( this );
    TBool ok = iAnimation->ConstructFromSkinL( KAknsIIDQsnAnimList );

    if( !ok ) // Animation for the ID was not found from the skin
        {
        User::Leave( KErrNotFound );
        }

    DoResizeL( aHighlightSize, ETrue ); // Apply size & layers
    }

/**
* @param aHilightSize  The size of the list cell highlight
*/
void CEikFormAnim::DoResizeL(
    const TSize& aHighlightSize, TBool aAboutToStart )
    {
    if( !iObserver )
        return;

    iAnimation->BeginConfigInputLayersL( aHighlightSize, aAboutToStart );

    if( iAnimation->InputRgbGc() )
        iObserver->AnimDrawHighlightBackground( *iAnimation->InputRgbGc() );

    iAnimation->EndConfigInputLayersL();
    }
