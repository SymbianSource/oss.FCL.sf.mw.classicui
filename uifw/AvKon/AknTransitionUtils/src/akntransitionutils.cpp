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
* Description:  Transition utilities.
*
*/


#include <coecntrl.h>
#include <avkondomainpskeys.h>
#include <centralrepository.h>
#include <pslninternalcrkeys.h>
#include <AknUtils.h>

#include "akntransitionutils.h"
#include "aknpsobserver.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
struct CAknTransitionUtils::TDataEntry
    {
    TDataEntry( const TInt iKey, TAny* aData );
      
    static TBool SameKey( const TDataEntry& aEntry1,
                          const TDataEntry& aEntry2 );

    const TInt iKey;
    TAny* iData;
    };
        
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
struct CAknTransitionUtils::TTransitionObserver
    {
    TTransitionObserver( const TInt iKey, TInt iEvents,
                         MAknTransitionUtilsObserver* aObserver );
 
    static TBool Equal( const TTransitionObserver& aObserver1,
                        const TTransitionObserver& aObserver2 );

    TInt iEvents;        
    TInt iKey;
    MAknTransitionUtilsObserver* iObserver;
    };

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CAknTransitionUtils::TDataEntry::TDataEntry( const TInt aKey, 
                                             TAny* aData ) :
        iKey( aKey ), iData( aData )
    {
    }
        
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CAknTransitionUtils::TDataEntry::SameKey( const TDataEntry& aEntry1, 
                                                const TDataEntry& aEntry2 )
    {
    return aEntry1.iKey == aEntry2.iKey;
    }
    

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CAknTransitionUtils::TTransitionObserver::TTransitionObserver( 
            const TInt aKey, const TInt aEvents, 
            MAknTransitionUtilsObserver* aObserver ) :
    iEvents( ( TEvents )aEvents ), iKey( aKey ), iObserver( aObserver )
    {
    }
 
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CAknTransitionUtils::TTransitionObserver::Equal( 
        const TTransitionObserver& aObserver1,
        const TTransitionObserver& aObserver2 )
    {
    return aObserver1.iObserver == aObserver2.iObserver;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CAknTransitionUtils::~CAknTransitionUtils() 
    {
    TInt count = iUserData.Count();        
    for ( TInt i = 0; i < count; i++ )
        {
        delete iUserData[i];
        }
            
    count = iObservers.Count();        
    for ( TInt i = 0; i < count; i++ )
        {
        delete iObservers[i];
        }

    iUserData.Reset();
    iObservers.Reset();
    delete iPsObserver;
    delete iRepository;
    };

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknTransitionUtils::AddObserver( 
        MAknTransitionUtilsObserver* aObserver, TInt aEvents,  
        const TDesC8* aParams )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return KErrNoMemory;
        }
    
    TInt key = reinterpret_cast<TInt>( aParams );
    TInt count = singleton->iObservers.Count();
    TInt newEvents = 0;
    TBool foundObserver = EFalse;
    for ( TInt i = 0; i < count; i++ )
        {
        TTransitionObserver* o = singleton->iObservers[i];
        if ( o->iObserver == aObserver )
            {
            foundObserver = ETrue;
            newEvents = aEvents & ~o->iEvents;
            o->iEvents |= aEvents;
            break;
            }
        }
        
    if ( !foundObserver )
        {
        TTransitionObserver* o = new TTransitionObserver( key, aEvents, 
                                                          aObserver );
        if ( !o )
            {
            return KErrNoMemory;
            }
        singleton->iObservers.Append( o );
        newEvents = aEvents;
        }

    if ( newEvents & EEventControlTransitionFinished )
        {
        GfxTransEffect::SetTransitionObserver( singleton );
        singleton->iNumControlTransitionObservers++;
        }
    
    if ( newEvents & EEventWsBufferRedirection )
        {
        if ( !singleton->iPsObserver )
            {
            singleton->iPsObserver = CAknPsObserver::New( singleton, 
                                                          KPSUidAvkonDomain, 
                                                          KAknTfxServerRedirectionStatus );
            if ( !singleton->iPsObserver )
                {
                return KErrNoMemory;
                }
             TInt value = 0;
             singleton->iPsObserver->GetCurrentValue( value ); 
             singleton->iScreenRedirected = value & ETfxScreenRedirected;
            }
        singleton->iNumPsObservers++;
        }
        
    return KErrNone;
    }
  
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknTransitionUtils::RemoveObserver( 
        MAknTransitionUtilsObserver* aObserver, TInt aEvents )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return KErrNoMemory;
        }

    TIdentityRelation<TTransitionObserver> identity( 
                                              TTransitionObserver::Equal );
    TTransitionObserver tmp( 0, aEvents, aObserver );
    TInt index = singleton->iObservers.Find( &tmp, identity );
    if ( index != KErrNotFound )
        {
        TTransitionObserver* o = singleton->iObservers[index];
        TInt removedEvents = aEvents & o->iEvents;
        o->iEvents &= ~removedEvents;

        if ( o->iEvents == 0 )
            {
            delete singleton->iObservers[index];
            singleton->iObservers.Remove( index );
            }
            
        if ( removedEvents & EEventControlTransitionFinished )
            {
            if ( --singleton->iNumControlTransitionObservers == 0 )
                {
                GfxTransEffect::SetTransitionObserver( NULL );
                }
            }
        
        if ( removedEvents & EEventWsBufferRedirection )
            {
            if ( --singleton->iNumPsObservers == 0 )
                {
                delete singleton->iPsObserver;
                singleton->iPsObserver = NULL;
                }
            }
        
        return KErrNone;
        }
        
    return KErrNotFound;
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknTransitionUtils::GetState( TInt aEvent, TInt* aState, 
                                             TDes8* /*aParams*/ )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return KErrNoMemory;
        }
        
    if ( aEvent & EEventWsBufferRedirection )
        {
        *aState = singleton->iScreenRedirected;
        }
    else
        {
        return KErrNotSupported;
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CAknTransitionUtils::TransitionFinished( const CCoeControl* aControl, 
                                              TUint /* aAction */ )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return;
        }

    TInt key = reinterpret_cast<TInt>( aControl );

    for ( TInt i = 0; i < singleton->iObservers.Count(); i++ )
        {
        if ( ( singleton->iObservers[i]->iEvents & 
               EEventControlTransitionFinished ) &&
             ( singleton->iObservers[i]->iKey == key ) )
            {
            singleton->iObservers[i]->iObserver->AknTransitionCallback(
                EEventControlTransitionFinished, 0, 
                reinterpret_cast<const TDesC8*>( aControl ) );
            }
        }
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CAknTransitionUtils::PsValueUpdated( const TUid /* aCategory */, 
                                          const TUint /* aKey */,
                                          const TInt aVal )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return;
        }

    iScreenRedirected = aVal & ETfxScreenRedirected;

    for ( TInt i = 0; i < singleton->iObservers.Count(); i++ )
        {
        if ( singleton->iObservers[i]->iEvents & EEventWsBufferRedirection )
            {
           	MAknTransitionUtilsObserver* observer = singleton->iObservers[i]->iObserver;
           	observer->AknTransitionCallback(
                EEventWsBufferRedirection, iScreenRedirected );
            if ( (i >= singleton->iObservers.Count() ) // Out of bounds
            	|| ( observer != singleton->iObservers[i]->iObserver ) ) // removed
            	{
            	// Observer removed itself during AknTransitionCallback()
            	i--;
            	}
            }
        }
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknTransitionUtils::RemoveData( const TInt aKey )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return;
        }

    TIdentityRelation<TDataEntry> identity( TDataEntry::SameKey );
    TDataEntry tmp( aKey, NULL );
    TInt index = singleton->iUserData.Find( &tmp, identity );
    if ( index != KErrNotFound )
        {
        delete singleton->iUserData[index];
        singleton->iUserData.Remove( index );
        }
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknTransitionUtils::SetData( const TInt aKey, TAny* aData )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return KErrNoMemory;
        }
        
    TIdentityRelation<TDataEntry> identity( TDataEntry::SameKey );
    TDataEntry* tmp = new TDataEntry( aKey, aData );
    if ( !tmp )
        {
        return KErrNoMemory;
        }
    TInt index = singleton->iUserData.Find( tmp, identity );
    if ( index != KErrNotFound )
        {
        delete singleton->iUserData[index];
        singleton->iUserData.Remove( index );
        }

    singleton->iUserData.Append( tmp );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C TAny* CAknTransitionUtils::GetData( const TInt aKey )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return NULL;
        }
        
    TIdentityRelation<TDataEntry> identity( TDataEntry::SameKey );
    TDataEntry tmp( aKey, NULL );
    TInt index = singleton->iUserData.Find( &tmp, identity );
    if ( index != KErrNotFound )
        {
        return singleton->iUserData[index]->iData;
        }
    else
        {
        return NULL;
        }
    }
        
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknTransitionUtils::SetAllParents( const CCoeControl* aControl )
    {
    CCoeControl* child = NULL;
    CCoeControl* parent = const_cast<CCoeControl*>( aControl );

    TInt compControlCount = parent->CountComponentControls();

    for( TInt i( 0 ); i < compControlCount; i++ )
        {
        child = parent->ComponentControl( i );
        if ( child )
            {
            child->SetParent( parent );
            SetAllParents( child );
            }
        }
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknTransitionUtils::TransitionsEnabled( TInt aEffectCategory )
    {
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        // if singleton does not exist we create a temporary CRepository
        // to check the value
        CRepository* rep( NULL ); 
        TRAPD( err, rep = CRepository::NewL( KCRUidThemes ) );
        if ( err != KErrNone )
            {
            delete rep;
            return EFalse;
            }       
        TInt val;
        err = rep->Get( KThemesTransitionEffects, val );
        if ( err != KErrNone )
            {
            delete rep;
            return EFalse;
            }
 
        if ( val & aEffectCategory )
            {
            delete rep;
            return EFalse;
            }
    
        delete rep;
        return ETrue;
        }

    if ( !singleton->iRepository )
        {
        TRAPD( err, singleton->iRepository = CRepository::NewL( KCRUidThemes ) );
        if ( err != KErrNone )
            {
            return EFalse;
            }
        }

    TInt val;
    TInt err = singleton->iRepository->Get( KThemesTransitionEffects, val );
    if ( err != KErrNone )
        {
        return EFalse;
        }

    if ( val & aEffectCategory )
        {
        return EFalse;
        }
    
    return ETrue;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TInt CAknTransitionUtils::MakeVisibleSubComponentsR( CCoeControl* aControl,
                                        TMakeVisibleSubComponentsInfo aInfo )
    {
    CCoeControl* child = NULL;
    TInt compControlCount = aControl->CountComponentControls();

    for( TInt i = 0; i < compControlCount; i++ )
        {
        child = aControl->ComponentControl( i );
        if( child )
            {
            if( child->OwnsWindow() )
                {
                TBool makeVisible;
                TBool call = ETrue;
                TBool visible = child->IsVisible();
                switch ( aInfo )
                    {
                    case EForceInvisible:
                    case EDisappearInvisible:
                        makeVisible = EFalse;
                        break;
                    case EForceVisible:
                        makeVisible = ETrue;
                        break;
                    case EAppearInvisible:
                        call = visible;
                        if ( !visible &&
                             iIgnoredChildControls.Append( child ) == KErrNone )
                            {
                            GfxTransEffect::NotifyExternalState(
                                                    EAddIgnoreWOChildComponent,
                                                    ( const TDesC8* ) child );
                            }
                        makeVisible = EFalse;
                        break;
                    case EAppearVisible:
                        {
                        TInt pos = iIgnoredChildControls.Find( child );
                        if ( pos >= 0 )
                            {
                            iIgnoredChildControls.Remove( pos );
                            GfxTransEffect::NotifyExternalState(
                                                ERemoveIgnoreWOChildComponent,
                                                ( const TDesC8* ) child );
                            call = EFalse;
                            }
                        makeVisible = ETrue;
                        }
                        break;
                    default:
                        call = ETrue;
                        makeVisible = ETrue;
                    }
                if ( call )
                    {
                    child->MakeVisible( makeVisible );
                    }
                }
            MakeVisibleSubComponentsR( child, aInfo );
            }
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknTransitionUtils::MakeVisibleSubComponents(
        CCoeControl* aControl, TMakeVisibleSubComponentsInfo aInfo )
    {
    TInt err = KErrNone;
    CAknTransitionUtils* singleton = CAknTransitionUtils::Static();
    if ( !singleton )
        {
        return KErrNoMemory;
        }

    if ( aInfo != EClearIgnored )
        {
        err = singleton->MakeVisibleSubComponentsR( aControl, aInfo );
        }

    if ( aInfo == EClearIgnored || aInfo == EAppearVisible )
        {
        for ( TInt i = 0; i < singleton->iIgnoredChildControls.Count(); i++ )
            {
            GfxTransEffect::NotifyExternalState( ERemoveIgnoreWOChildComponent,
                        ( const TDesC8* ) singleton->iIgnoredChildControls[i] );
            }
        singleton->iIgnoredChildControls.Reset();
        }

    return err;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
static void GetDemarcationOptionsMenu( TRect& aRect )
    {
    if ( AknLayoutUtils::LayoutMetricsRect( 
            AknLayoutUtils::EControlPaneBottom, aRect ) )
        {
        // Options soft button on the left or right
        return;
        }
    else
        {
        // Soft buttons at the bottom of the screen
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPane, aRect );
        }
    }
    
static void GetDemarcationPopup( TRect& aRect )
    {
    TRect controlTop;
    TRect controlBottom;
    TBool topRet = AknLayoutUtils::LayoutMetricsRect(
        AknLayoutUtils::EControlPaneTop, controlTop);
    TBool bottomRet = AknLayoutUtils::LayoutMetricsRect(
        AknLayoutUtils::EControlPaneBottom, controlBottom);
    if (bottomRet)
        {
        if (controlTop.iTl.iX == 0)
            {
            // The softkeys are on the left
            aRect.iTl.iX = aRect.iBr.iX = 0;
            aRect.iTl.iY = controlTop.iBr.iY;
            aRect.iBr.iY = controlBottom.iTl.iY;
            }
        else
            {
            // The softkeys are on the right
            aRect.iTl = controlTop.iBr;
            aRect.iBr.iX = controlBottom.iBr.iX;
            aRect.iBr.iY = controlBottom.iTl.iY;    
            }
        }
    else
        {
        // The softkeys are on the top or bottom
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EControlPane, aRect);
        }
    }
    
EXPORT_C TInt CAknTransitionUtils::GetDemarcation( 
        TGfxControlType aControlType, TRect& aRect )
    {
    if ( aControlType == EOptionsMenu )
        {
        GetDemarcationOptionsMenu( aRect );
        }
    else // EPopup
        {
        GetDemarcationPopup( aRect );
        }

    return KErrNone;
    };
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CAknTransitionUtils::CAknTransitionUtils() :
        CCoeStatic( KAknTransitionUtilsUid, -1, CCoeStatic::EThread ),
        iNumControlTransitionObservers( 0 )
    {
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CAknTransitionUtils* CAknTransitionUtils::Static()
    {
	CCoeEnv *env = CCoeEnv::Static();
	if(!env)
	{
		return NULL;
	}
    CAknTransitionUtils* singleton = 
        reinterpret_cast<CAknTransitionUtils*>(CCoeEnv::Static( 
                                                  KAknTransitionUtilsUid ) );
    if ( !singleton )
        {
        singleton = new CAknTransitionUtils();
        }
        
    return singleton;
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CAknTransitionUtils::RemoveControlTransitionObserver( const TInt aKey )
    {
    TInt count = iObservers.Count();
    for ( TInt i = 0; i < count; i++ )
        {
        TTransitionObserver* o = iObservers[i];
        if ( o->iKey == aKey )
            {
            CAknTransitionUtils::RemoveObserver( o->iObserver, 0xffffffff );
            break;
            }
        }
    }

