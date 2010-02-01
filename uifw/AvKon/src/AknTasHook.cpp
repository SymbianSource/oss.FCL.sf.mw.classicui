/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: Avkon testability hook class definitions.
*
*/


// INCLUDES
#include <AknTasHook.h>
#include <TasHookingInternalCRKeys.h>
#include "AknBatteryStrength.h"
#include "AknSignalStrength.h"
#include <centralrepository.h>
#include <AknTasPluginInterface.h>
#include <TasDataModelInterface.h>

// CONSTANTS
const TUid KUidTasHook =    { 0xE000DEC4 };
const TInt KTasHookingOff =   0;
const TInt KTasHookingOn =    1;

// MACROS

    /**
     * DEBUGPRINT
     * 
     * Simple wrapper macro for the RDebug::Print utility.
     *
     * Usage:
     * 
     *  DEBUGPRINT( ( _L( "CAknTasHook::ConstructL: Error %d in doing stuff" ), error ) )
     * 
     */
    #ifdef _DEBUG
    #define DEBUGPRINT( aFormatString ) { RDebug::Print aFormatString; }
    #else
    #define DEBUGPRINT( aFormatString ) {}
    #endif

// FORWARD DECLARATIONS
class CAknTasClassInfo;
class CAknTasObjectInfo;

// CLASS DEFINITIONS

CAknTasClassInfo::CAknTasClassInfo() :
    iClassName( NULL )
    {
    }

CAknTasClassInfo::~CAknTasClassInfo()
    {
    delete iClassName;
    }

void CAknTasClassInfo::ConstructL( TDesC& aClassName )
    {
    // Allocate a copy of the given descriptor and take ownership of it 
    iClassName = aClassName.AllocL();
    }
                
const TDesC& CAknTasClassInfo::GetClassName() const
    {
    return *iClassName;
    }

TInt CAknTasClassInfo::MatchName( 
    const CAknTasClassInfo& aInfo1, 
    const CAknTasClassInfo& aInfo2 )
    {
    if ( aInfo1.GetClassName() == aInfo2.GetClassName() )
        {
        return 1;
        }
    return 0;
    }
    
CAknTasObjectInfo::CAknTasObjectInfo()
    {    
    }

CAknTasObjectInfo::~CAknTasObjectInfo()
    {
    if ( iClassInfoArray )
        {        
        iClassInfoArray->ResetAndDestroy();
        delete iClassInfoArray;
        }
    }
    
void CAknTasObjectInfo::ConstructL( 
    TAny* aObjPtr, 
    TAknTasHookObjectType aObjType )
    {
    iObjPtr = aObjPtr; // not owned
    if ( aObjPtr )
        {
        iClassInfoArray = new ( ELeave ) RPointerArray<CAknTasClassInfo>; // owned
        iControlKey = TUint32( aObjPtr );
        iObjType = aObjType;
        }
    else
        {
        iControlKey = 0;
        }
    }

TInt CAknTasObjectInfo::MatchByControl(
    const CAknTasObjectInfo& aInfo1, 
    const CAknTasObjectInfo& aInfo2 )
    {
    if ( aInfo1.iControlKey == aInfo2.iControlKey )
        {
        return 1;
        }
    return 0;        
    }

void CAknTasObjectInfo::AddL( CAknTasClassInfo* aObjPtr )
    {
    iClassInfoArray->AppendL( aObjPtr );
    }
    
EXPORT_C TBool CAknTasObjectInfo::IsA( TPtrC aClassName )
    {
    CAknTasClassInfo* classInfo = NULL;
    TRAPD( err,
            classInfo = new ( ELeave ) CAknTasClassInfo();
            CleanupStack::PushL( classInfo );
            classInfo->ConstructL( aClassName );
            CleanupStack::Pop( classInfo ) );
    if ( err )
        {
        if ( classInfo )
            {
            CleanupStack::PopAndDestroy( classInfo );
            }
        return EFalse;
        }
        
    TIdentityRelation<CAknTasClassInfo> matcher( CAknTasClassInfo::MatchName );
    TInt position = iClassInfoArray->Find( classInfo, matcher );
    delete classInfo;
    if ( position != KErrNotFound )
        {        
        classInfo = ( *iClassInfoArray )[position];
        return ETrue;
        }        
    return EFalse;
    }
 
//
// Heap descriptor ownership passed to caller!
//
EXPORT_C HBufC* CAknTasObjectInfo::GetClassNames()
    {
    // Sum up the class name lengths and add room for the separators
    TInt bufLength( 0 );
    for ( TInt i = 0; i < iClassInfoArray->Count(); i++ )
        {
        bufLength += ( *iClassInfoArray )[i]->GetClassName().Length() + 1;
        }
    
    // Create a buffer of needed length and make it empty
    HBufC* buf = NULL;
    TRAPD( err, 
            buf = HBufC::NewLC( bufLength );
            CleanupStack::Pop( buf ) );
    if ( err )
        {
        return NULL;
        }
    TPtr modifiableBuf = buf->Des();
    modifiableBuf.Zero();
    
    if ( iClassInfoArray->Count() <= 0 )
        {
        return buf;
        }
    
    // Append class names and separators
    for ( TInt i = 0; i < iClassInfoArray->Count(); i++ )
        {
        modifiableBuf.Append( ( *iClassInfoArray )[i]->GetClassName() );
        
        if ( i + 1 < iClassInfoArray->Count() )
            {
            modifiableBuf.Append( _L( ":" ) );
            }
        }
    
    return buf;
    }

EXPORT_C TAny* CAknTasObjectInfo::GetControl() const
    {
    return iObjPtr;
    }

EXPORT_C TAknTasHookObjectType CAknTasObjectInfo::Type() const
    {
    return iObjType;
    }
                    
CAknTasHook::CAknTasHook() :
    CCoeStatic( KUidTasHook ),
    iTasHookingEnabled( EFalse ),
    iTasHookStoringEnabled( EFalse )
    {    
    }
    
CAknTasHook* CAknTasHook::InstanceL()
    {
    CAknTasHook* instance = 
        static_cast<CAknTasHook*> ( CCoeEnv::Static( KUidTasHook ) );
    if ( !instance )
        {
        instance = new ( ELeave ) CAknTasHook();
        CleanupStack::PushL( instance );
        instance->ConstructL();
        CleanupStack::Pop( instance );
        }
    return instance;
    }

CAknTasHook* CAknTasHook::Self()
    {
    CAknTasHook* instance = 
        static_cast<CAknTasHook*> ( CCoeEnv::Static( KUidTasHook ) );
    if ( !instance )
        {
        return NULL;
        }
    return instance;
    }

CAknTasHook::~CAknTasHook()
    {
    delete iTasPlugin;
    REComSession::FinalClose();
    if ( iHookingNotifyHandler )
        {
        iHookingNotifyHandler->StopListening();
        delete iHookingNotifyHandler;
        }
    if ( iHookStoringNotifyHandler )
        {
        iHookStoringNotifyHandler->StopListening();
        delete iHookStoringNotifyHandler;
        }
    delete iTasHookingRepo;
    if ( iObjectInfoArray )
        {           
        iObjectInfoArray->ResetAndDestroy();
        delete iObjectInfoArray;
        }
    }

void CAknTasHook::ConstructL()
    {
    iObjectInfoArray = new ( ELeave ) RPointerArray<CAknTasObjectInfo>; // owned

    // Connect to TAS hooking CenRep repository
    TRAPD( error, iTasHookingRepo = CRepository::NewL( KCRUidTasHooking ) );
    if ( error != KErrNone )
        {
        DEBUGPRINT( ( _L( "   CAknTasHook::ConstructL: Error %d in connecting to key 0x%x" ), error, KCRUidTasHooking.iUid ) )
        User::Leave( error );
        }
        
    // Process the initial values and start listening 
    // for key changes in this repository
    TRAP( error, iHookingNotifyHandler = CreateNotifyHandlerL( *iTasHookingRepo, KTasHooking ) );
    if ( error != KErrNone )
        {
        DEBUGPRINT( ( _L( "   CAknTasHook::ConstructL: Error %d in creating CenRep notify handler" ), error ) )
        User::Leave( error );
        }
    TRAP( error, iHookingNotifyHandler->StartListeningL() );
    if ( error != KErrNone )
        {
        DEBUGPRINT( ( _L( "   CAknTasHook::ConstructL: Error %d in starting to listen" ), error ) )
        User::Leave( error );
        }
    TRAP( error, iHookStoringNotifyHandler = CreateNotifyHandlerL( *iTasHookingRepo, KTasHookStoring ) );
    if ( error != KErrNone )
        {
        DEBUGPRINT( ( _L( "   CAknTasHook::ConstructL: Error %d in creating CenRep notify handler" ), error ) )
        User::Leave( error );
        }
    TRAP( error, iHookStoringNotifyHandler->StartListeningL() );
    if ( error != KErrNone )
        {
        DEBUGPRINT( ( _L( "   CAknTasHook::ConstructL: Error %d in starting to listen" ), error ) )
        User::Leave( error );
        }
    }
    
CCenRepNotifyHandler* CAknTasHook::CreateNotifyHandlerL( 
    CRepository& aRepository, 
    TUint32 aKey )
    {
    // Process the initial value, the 1st notication is only received when the
    // value changes so we need to see if the hooking has already been activated
    TInt initialValue;
    TInt error = aRepository.Get( aKey, initialValue );
    if ( error != KErrNone )
        {
        DEBUGPRINT( ( _L( "   CAknTasHook::CreateNotifyHandlerL: Error %d in getting key value" ), error ) )
        User::Leave( error );
        }
    else
        {
        HandleNotifyInt( aKey, initialValue );
        }
        
    // Create a new notify handler for the given integer key
    return CCenRepNotifyHandler::NewL( *this, aRepository, CCenRepNotifyHandler::EIntKey, aKey );
    }

TBool CAknTasHook::Initialized()
    {
    if ( iObjectInfoArray )
        {
        return ETrue;
        }
    return EFalse;
    }
        
EXPORT_C void CAknTasHook::AddL( 
    TAny* aObjPtr, 
    TPtrC aStrPtr, 
    TAknTasHookObjectType aObjType )
    {
    if ( !aObjPtr )
        {
        return;
        }
    
    CAknTasHook* mePtr = InstanceL();   
    if ( mePtr )
        {
        mePtr->AddInfoL( aObjPtr, aStrPtr, aObjType );
        }
    }
    
void CAknTasHook::AddInfoL( 
    TAny* aObjPtr, 
    TPtrC aStrPtr, 
    TAknTasHookObjectType aObjType )
    {    
    if ( iTasHookStoringEnabled )
        {
        CAknTasObjectInfo* objInfo = new ( ELeave ) CAknTasObjectInfo();
        CleanupStack::PushL( objInfo );
        objInfo->ConstructL( aObjPtr, aObjType );
        CleanupStack::Pop( objInfo );
        CAknTasClassInfo* classInfo = new ( ELeave ) CAknTasClassInfo();
        CleanupStack::PushL( classInfo );
        classInfo->ConstructL( aStrPtr );
        CleanupStack::Pop( classInfo );
        
        if ( iObjectInfoArray->Count() <= 0 )
            {
            objInfo->AddL( classInfo );
            iObjectInfoArray->AppendL( objInfo );
            return;
            }
                
        TIdentityRelation<CAknTasObjectInfo> matcher( CAknTasObjectInfo::MatchByControl );
        TInt position = iObjectInfoArray->Find( objInfo, matcher );
        if ( position != KErrNotFound )
            {
            delete objInfo;
            objInfo = ( *iObjectInfoArray )[position];
            }
        else
            {
            iObjectInfoArray->AppendL( objInfo );
            }
        objInfo->AddL( classInfo );
        }
    }
    
EXPORT_C CAknTasObjectInfo* CAknTasHook::Get( TAny* aObjPtr )
    {
    CAknTasHook* mePtr = Self();
    if ( !mePtr->iTasHookingEnabled )
        {
        return NULL;
        }
    
    if ( mePtr )
        {
        return mePtr->GetInfo( aObjPtr );
        }
        
    return NULL;
    }
    
CAknTasObjectInfo* CAknTasHook::GetInfo( TAny* aObjPtr )
    {
    CAknTasObjectInfo* objInfo = NULL;
    TRAPD( err,
            objInfo = new ( ELeave ) CAknTasObjectInfo();
            CleanupStack::PushL( objInfo );
            objInfo->ConstructL( aObjPtr ) );
            CleanupStack::Pop( objInfo );
    if ( err )
        {
        if ( objInfo )
            {
            CleanupStack::PopAndDestroy( objInfo );
            }
        return NULL;
        }
    
    TIdentityRelation<CAknTasObjectInfo> matcher( CAknTasObjectInfo::MatchByControl );
    TInt position = iObjectInfoArray->Find( objInfo, matcher );
    delete objInfo;
    if ( position != KErrNotFound )
        {
        return ( *iObjectInfoArray )[position];
        }
    else
        {
        return NULL;
        }
    }
              
TBool CAknTasHook::ExistsL( TAny* aObjPtr )
    {    
    CAknTasHook* mePtr = InstanceL();
    return mePtr->InfoExistsL( aObjPtr );
    }
    
TBool CAknTasHook::InfoExistsL( TAny* aObjPtr )
    {
    if ( iObjectInfoArray->Count() <= 0 )
        {
        return EFalse;
        }
    
    CAknTasObjectInfo* objInfo = new ( ELeave ) CAknTasObjectInfo();
    CleanupStack::PushL( objInfo );
    objInfo->ConstructL( aObjPtr );
    CleanupStack::Pop( objInfo );
    
    TIdentityRelation<CAknTasObjectInfo> matcher( CAknTasObjectInfo::MatchByControl );
    TInt position = iObjectInfoArray->Find( objInfo, matcher );
    delete objInfo;
    if ( position != KErrNotFound )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }    
    }
    
EXPORT_C void CAknTasHook::Remove( TAny* aObjPtr )
    {
    CAknTasHook* mePtr = Self();
    if ( mePtr )
        {
        TInt err( KErrNone );
        TRAP( err, mePtr->RemoveInfoL( aObjPtr ) );
        }
    }
    
void CAknTasHook::RemoveInfoL( TAny* aObjPtr )
    {
    if ( iTasHookStoringEnabled )
        {
        if ( iObjectInfoArray->Count() <= 0 )
            {
            return;
            }
        
        CAknTasObjectInfo* objInfo = new ( ELeave ) CAknTasObjectInfo();
        CleanupStack::PushL( objInfo );
        objInfo->ConstructL( aObjPtr );
        CleanupStack::Pop( objInfo );
            
        TIdentityRelation<CAknTasObjectInfo> matcher( CAknTasObjectInfo::MatchByControl );
        TInt position = iObjectInfoArray->Find( objInfo, matcher );
        delete objInfo;
        if ( position != KErrNotFound )
            {
            objInfo = ( *iObjectInfoArray )[position];
            iObjectInfoArray->Remove( position );
            delete objInfo;
            }
        }
    }

EXPORT_C RPointerArray<CAknTasObjectInfo>* CAknTasHook::GetAll()
    {
    if ( !iTasHookingEnabled )
        {
        return NULL;
        }
    return iObjectInfoArray;
    }

EXPORT_C void CAknTasHook::GetAknUiLC( MTasObject& aParentApplication )
    {
    if ( !iTasHookingEnabled )
        {
        return;
        }
    
    TInt numObjects = iObjectInfoArray->Count();
        
    for ( TInt i = 0; i < numObjects; i++ )
        {
        CAknTasObjectInfo* objInfo = ( *iObjectInfoArray )[i];
        
        if ( objInfo->IsA( _L( "CAknBatteryStrength" ) ) )
            {
            if ( !CheckSanityL( ( CCoeControl* ) objInfo->GetControl() ) )
                {
                continue;
                }
            CAknBatteryStrength* battery = 
                static_cast<CAknBatteryStrength*>( objInfo->GetControl() );
            if ( battery )
                {
                MTasObject& tasObj = aParentApplication.AddObjectL();
                //tasObj.AddAttributeL( _L( "Id" ), objInfo->iControlKey );
                tasObj.SetNameL( _L( "CAknBatteryStrength" ) );
                tasObj.SetTypeL( _L( "indicator" ) );
                tasObj.SetIdL( objInfo->iControlKey );
                tasObj.AddAttributeL( _L( "Level" ), battery->BatteryLevel() );
                tasObj.AddAttributeL( _L( "Recharging" ), battery->Recharging() );
                AddCommonCoeInfoL( ( CCoeControl* ) objInfo->GetControl(), tasObj );
                }
            }
        else if ( objInfo->IsA( _L( "CAknSignalStrength" ) ) )
            {
            if ( !CheckSanityL( ( CCoeControl* )objInfo->GetControl() ) )
                {
                continue;
                }
            CAknSignalStrength* signal = 
                static_cast<CAknSignalStrength*>( objInfo->GetControl() );
            if ( signal )
                {                
                MTasObject& tasObj = aParentApplication.AddObjectL();
                //tasObj.AddAttributeL( _L( "Id" ), objInfo->iControlKey );
                tasObj.SetNameL( _L( "CAknSignalStrength" ) );
                tasObj.SetTypeL( _L( "indicator" ) );
                tasObj.SetIdL( objInfo->iControlKey );
                tasObj.AddAttributeL( _L( "Level" ), signal->SignalLevel() );
                AddCommonCoeInfoL( ( CCoeControl* ) objInfo->GetControl(), tasObj );
                }
            }
        }
    }

void CAknTasHook::AddCommonCoeInfoL( CCoeControl* aObjPtr, MTasObject& aObjectInfo )
    {
    //add positional details
    TRect absoluteRect( 0, 0, 0, 0 );
    if ( aObjPtr->OwnsWindow() )
        {
        RDrawableWindow* window = aObjPtr->DrawableWindow();
        if ( window )
            {
            TRect tempRect( window->AbsPosition(), window->Size() );
            absoluteRect = tempRect;
            }
        }
    else
        {
        TRect tempRect( aObjPtr->PositionRelativeToScreen(), aObjPtr->Size() );
        absoluteRect = tempRect;
        }
    
    aObjectInfo.AddAttributeL( _L( "X" ), absoluteRect.iTl.iX );
    aObjectInfo.AddAttributeL( _L( "Y" ), absoluteRect.iTl.iY );
    aObjectInfo.AddAttributeL( _L( "Width" ), absoluteRect.Width() );
    aObjectInfo.AddAttributeL( _L( "Height" ), absoluteRect.Height() );
    
    //some general details
    aObjectInfo.AddAttributeL( _L( "Visible" ), ( aObjPtr->IsVisible()? _L( "TRUE" ) : _L( "FALSE" ) ) );
    aObjectInfo.AddAttributeL( _L( "Focused" ), ( aObjPtr->IsFocused()? _L( "TRUE" ): _L( "FALSE" ) ) );
    aObjectInfo.AddAttributeL( _L( "Dimmed" ), ( aObjPtr->IsDimmed()? _L( "TRUE" ): _L( "FALSE" ) ) );
    aObjectInfo.AddAttributeL( _L( "HasBorder" ), ( aObjPtr->HasBorder()? _L( "TRUE" ): _L( "FALSE" ) ) );
    }

void CAknTasHook::HandleNotifyInt( TUint32 aId, TInt aNewValue )
    {
    if ( aId == KTasHooking )
        {
        if ( aNewValue == KTasHookingOn && !iTasHookingEnabled )
            {
            TRAPD( errorCreate, iTasPlugin = CAknTasPluginInterface::NewL() );
            if ( errorCreate != KErrNone )
                {
                iTasHookingEnabled = EFalse;
                return;
                }
            TRAPD( errorSet, iTasPlugin->SetHookInterfaceL( InstanceL() ) );
            if ( errorSet != KErrNone )
                {
                delete iTasPlugin;
                iTasPlugin = NULL;
                iTasHookingEnabled = EFalse;
                return;
                }
            iTasHookingEnabled = ETrue;
            }
        else if ( aNewValue == KTasHookingOff && iTasHookingEnabled )
            {
            delete iTasPlugin;
            iTasPlugin = NULL;
            iTasHookingEnabled = EFalse;
            }
        else
            {
            // Invalid value
            }
        }
    else if ( aId == KTasHookStoring )
        {
        if ( aNewValue == KTasHookingOn )
            {
            iTasHookStoringEnabled = ETrue;
            }
        else if ( aNewValue == KTasHookingOff )
            {
            iTasHookStoringEnabled = EFalse;
            }
        else
            {
            // Invalid value
            }
        }
    else
        {
        // Wrong key
        }
    }

TBool CAknTasHook::CheckSanityL( CCoeControl* aControl )
    {
    // check the sanity of the object
    if ( !aControl || 
         !aControl->DrawableWindow() || 
         !aControl->ControlEnv() ||
         !aControl->IsVisible() )
        {
        return EFalse;
        }
    
    if ( !iTasPlugin->IsControlVisible( *aControl ) )
        {
        return EFalse;
        }
    
    return ETrue;
    }

// End of File
