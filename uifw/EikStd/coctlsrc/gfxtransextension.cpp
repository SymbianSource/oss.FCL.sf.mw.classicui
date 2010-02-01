/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class for passing data between controls.
*
*/


#include "gfxtransextension.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CGfxTransExtension::TDataEntry::TDataEntry( const TInt aKey, 
                                            const TDesC8* aData ) :
        iKey( aKey ), iData( aData )
    {
    }
        
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CGfxTransExtension::TDataEntry::SameKey( const TDataEntry& aEntry1, 
                                               const TDataEntry& aEntry2 )
    {
    return aEntry1.iKey == aEntry2.iKey;
    }
    

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CGfxTransExtension::TTransitionObserver::TTransitionObserver( 
            const TInt aKey, const TInt aEventType, 
            MAknTransitionUtilsObserver* aObserver ) :
        iKey( aKey ), iObserver( aObserver ), iEventType( ( TEvents )aEventType )
    {
    }
 
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CGfxTransExtension::TTransitionObserver::SameKey( 
        const TTransitionObserver& aObserver1,
        const TTransitionObserver& aObserver2 )
    {
    return aObserver1.iKey == aObserver2.iKey;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CGfxTransExtension::TTransitionObserver::Equal( 
        const TTransitionObserver& aObserver1,
        const TTransitionObserver& aObserver2 )
    {
    return ( aObserver1.iObserver == aObserver2.iObserver ) &&
           ( aObserver1.iEventType == aObserver2.iEventType );
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CGfxTransExtension::~CGfxTransExtension() 
    {
    TInt count = iUserData.Count();
        
    for ( TInt i = 0; i < count; i++ )
        {
        delete iUserData[i].iData;
        }
            
    iUserData.Reset();
    iObservers.Reset();
    };

/*
    static TInt GetState(TInt aEvent, TInt* aState, TDes8* aParams = NULL);

    // FIXME: TDes8 instead of TAny
    static TInt SetData( const TInt aKey, TAny* aData );
    static TAny* GetData( const TInt aKey );
    static void RemoveData( const TInt aKey );
*/

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TInt CGfxTransExtension::AddObserver( MAknTransitionUtilsObserver* aObserver,
                                      TInt aEvent,
                                      const TDesC8* aParams )
    {
    CGfxTransExtension* singleton = 
        reinterpret_cast<CGfxTransExtension*>(CCoeEnv::Static( KGfxTransExtensionUid ) );
    if ( !singleton )
        {
        return KErrNoMemory;
        }
    
    TInt key = ( TInt )aParams;
    TInt count = singleton->iObservers.Count();
    TBool exists = EFalse;
    for ( TInt i = 0; i < count; i++ )
        {
        TTransitionObserver o = singleton->iObservers[i];
        if ( ( o.iEventType == aEvent ) && ( o.iObserver == aObserver ) )
            {
            exists = ETrue;
            break;
            }
        }
        
    if ( !exists )
        {
        TTransitionObserver observer( key, aEvent, aObserver );
        singleton->iObservers.Append( observer );
        }

    if ( aEvent == EEventControlTransitionFinished )
        {
        GfxTransEffect::SetTransitionObserver( singleton );
        singleton->iNumControlTransitionObservers++;
        }
        
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TInt CGfxTransExtension::RemoveObserver( 
        MAknTransitionUtilsObserver* aObserver, TInt aEvent )
    {
    CGfxTransExtension* singleton = CGfxTransExtension::Static();
    if ( !singleton )
        {
        return KErrNotFound;
        }

    TIdentityRelation<TTransitionObserver> identity( TTransitionObserver::Equal );
    TTransitionObserver tmp( 0, aEvent, aObserver );
    TInt index = singleton->iObservers.Find( tmp, identity );
    if ( index != KErrNotFound )
        {
        singleton->iObservers.Remove( index );
        if ( aEvent == EEventControlTransitionFinished )
            {
            singleton->iNumControlTransitionObservers--;
            }
        
        if ( singleton->iNumControlTransitionObservers == 0 )
            {
            GfxTransEffect::SetTransitionObserver( NULL );
            }
            
        return KErrNone;
        }
        
    return KErrNotFound;
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TInt CGfxTransExtension::GetState(TInt /*aEvent*/, TInt* /*aState*/, TDes8* /*aParams*/ )
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CGfxTransExtension::TransitionFinished( const CCoeControl* aControl, 
                                             TUint /* aAction */ )
    {
    CGfxTransExtension* singleton = 
        reinterpret_cast<CGfxTransExtension*>(CCoeEnv::Static( KGfxTransExtensionUid ) );
    if ( !singleton )
        {
        return;
        }

    TInt key = ( TInt )aControl;

    TInt count = singleton->iObservers.Count();
    for ( TInt i = 0; i < count; i++ )
        {
        if ( singleton->iObservers[i].iKey == key )
            {
            singleton->iObservers[i].iObserver->AknTransitionCallback(
                EEventControlTransitionFinished, 0, ( const TDesC8* )aControl );
            }
        }
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CGfxTransExtension::RemoveData( const TInt aKey )
    {
    CGfxTransExtension* singleton = CGfxTransExtension::Static();
    if ( !singleton )
        {
        return;
        }

    // Find the data
    TIdentityRelation<TDataEntry> identity( TDataEntry::SameKey );
    TDataEntry tmp( aKey, NULL );
    TInt index = singleton->iUserData.Find( tmp, identity );
    if ( index != KErrNotFound )
        {
        delete singleton->iUserData[index].iData;
        singleton->iUserData.Remove( index );
        }
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TInt CGfxTransExtension::SetData( const TInt aKey, const TDesC8* aData )
    {
    CGfxTransExtension* singleton = CGfxTransExtension::Static();
    if ( !singleton )
        {
        return KErrNoMemory;
        }
        
    TIdentityRelation<TDataEntry> identity( TDataEntry::SameKey );
    TDataEntry tmp( aKey, aData );
    TInt index = singleton->iUserData.Find( tmp, identity );
    if ( index != KErrNotFound )
        {
        delete singleton->iUserData[index].iData;
        singleton->iUserData[index].iData = aData;
        }
    else
        {
        singleton->iUserData.Append( tmp );
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
const TDesC8* CGfxTransExtension::GetData( const TInt aKey )
    {
    CGfxTransExtension* singleton = CGfxTransExtension::Static();
    if ( !singleton )
        {
        return NULL;
        }
        
    TIdentityRelation<TDataEntry> identity( TDataEntry::SameKey );
    TDataEntry tmp( aKey, NULL );
    TInt index = singleton->iUserData.Find( tmp, identity );
    if ( index != KErrNotFound )
        {
        return singleton->iUserData[index].iData;
        }
    else
        {
        return NULL;
        }
    }
        
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CGfxTransExtension::CGfxTransExtension() :
        CCoeStatic( KGfxTransExtensionUid, -1, CCoeStatic::EThread ),
        iNumControlTransitionObservers( 0 )
    {
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CGfxTransExtension* CGfxTransExtension::Static()
    {
    CGfxTransExtension* singleton = 
        reinterpret_cast<CGfxTransExtension*>(CCoeEnv::Static( KGfxTransExtensionUid ) );
    if ( !singleton )
        {
        singleton = new CGfxTransExtension();
        }
        
    return singleton;
    }
