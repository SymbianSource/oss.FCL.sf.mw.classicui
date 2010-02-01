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
* Description:  Parameter container class for dynamic soft notifications
*
*/

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif
#include "AknDynamicSoftNotificationParams.h"

/// Maximum allowed priority for dynamic soft notification
const TInt KMaxAllowedPriority  = 3000;
/// Minimum allowed priority for dynamic soft notification
const TInt KMinAllowedPriority  = 1000;

//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::TAknDynamicSoftNotificationParams
//-----------------------------------------------------------------------------
//   
EXPORT_C TAknDynamicSoftNotificationParams::TAknDynamicSoftNotificationParams( 
    TInt aPriority,
    CAknNoteDialog::TTone aTone ) : // = CAknNoteDialog::ENoTone
    iPriority( aPriority ),
    iTone( aTone ),
    // default values
    iCustomMessageId( KNullUid ),
    iEnableObserver( EFalse )
    {
    __ASSERT_ALWAYS( aPriority >= KMinAllowedPriority && 
        aPriority <= KMaxAllowedPriority, User::Invariant() );
    }
    
//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::SetViewActivationParams
//-----------------------------------------------------------------------------
//   
EXPORT_C void TAknDynamicSoftNotificationParams::SetViewActivationParams(
    TVwsViewId aViewId,
    TVwsViewId aPluralViewId,   // = KNullViewId
    TUid aCustomMsgId,          // = KNullUid
    const TDesC8& aCustomMsg )  // = KNullDesC8
    {
    iViewId = aViewId;
    iPluralViewId = aPluralViewId;
    iCustomMessageId = aCustomMsgId;
    iCustomMessage.Set( aCustomMsg );
    }

//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::SetSoftkeys
//-----------------------------------------------------------------------------
//   
EXPORT_C void TAknDynamicSoftNotificationParams::SetSoftkeys(
    const TDesC& aLeftSoftkey,
    const TDesC& aRightSoftkey )
    {
    iLeftSoftkey.Set( aLeftSoftkey );
    iRightSoftkey.Set( aRightSoftkey );
    }
    
//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::SetNoteLabels
//-----------------------------------------------------------------------------
//   
EXPORT_C void TAknDynamicSoftNotificationParams::SetNoteLabels(
    const TDesC& aSingularLabel,
    const TDesC& aPluralLabel )
    {
    iNoteSingularLabel.Set( aSingularLabel );
    iNotePluralLabel.Set( aPluralLabel );
    }

//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::SetImageData
//-----------------------------------------------------------------------------
//   
EXPORT_C void TAknDynamicSoftNotificationParams::SetGroupLabels(
    const TDesC& aSingularLabel,
    const TDesC& aPluralLabel )
    {
    iGroupSingularLabel.Set( aSingularLabel );
    iGroupPluralLabel.Set( aPluralLabel );
    }
    
//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::SetImageData
//-----------------------------------------------------------------------------
//   
EXPORT_C void TAknDynamicSoftNotificationParams::SetImageData( 
    const TDesC8& aImageData )
    {
    iImageData.Set( aImageData );
    }
    
//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::EnableObserver
//-----------------------------------------------------------------------------
// 
EXPORT_C void TAknDynamicSoftNotificationParams::EnableObserver()
    {
    iEnableObserver = ETrue;
    }

//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::ExternalizeL
//-----------------------------------------------------------------------------
//   
void TAknDynamicSoftNotificationParams::ExternalizeL( 
    RWriteStream& aStream ) const
    {
    aStream.WriteInt32L( iPriority );
    aStream.WriteInt32L( iTone );
    
    // view activation data
    aStream.WriteUint32L( iViewId.iAppUid.iUid );
    aStream.WriteUint32L( iViewId.iViewUid.iUid );
    aStream.WriteUint32L( iPluralViewId.iAppUid.iUid );
    aStream.WriteUint32L( iPluralViewId.iViewUid.iUid );
    
    if( iViewId != KNullViewId )
        {
        aStream.WriteInt32L( iCustomMessageId.iUid );
        ExternalizeTextL( aStream, iCustomMessage );
        }
    else
        {
        aStream.WriteInt32L( KErrNotFound );
        }

    // softkeys
    ExternalizeTextL( aStream, iLeftSoftkey );
    ExternalizeTextL( aStream, iRightSoftkey );
    
    // text labels
    ExternalizeTextL( aStream, iNoteSingularLabel );
    ExternalizeTextL( aStream, iNotePluralLabel );
    ExternalizeTextL( aStream, iGroupSingularLabel );
    ExternalizeTextL( aStream, iGroupPluralLabel );
    
    aStream.WriteUint8L( iEnableObserver ? ETrue : EFalse );
    
    // image
    ExternalizeTextL( aStream, iImageData );
    }

//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::ExternalizeTextL
//-----------------------------------------------------------------------------
//
void TAknDynamicSoftNotificationParams::ExternalizeTextL( 
    RWriteStream& aStream, 
    const TDesC16& aText ) const
    {
    TInt length = aText.Length();
    if( length > 0 )
        {
        aStream.WriteInt32L( aText.Length() );
        aStream << aText;
        }
    else
        {
        aStream.WriteInt32L( KErrNotFound );
        }
    }

//-----------------------------------------------------------------------------
// TAknDynamicSoftNotificationParams::ExternalizeTextL
//-----------------------------------------------------------------------------
//
void TAknDynamicSoftNotificationParams::ExternalizeTextL( 
    RWriteStream& aStream, 
    const TDesC8& aText ) const
    {
    TInt length = aText.Length();
    if( length > 0 )
        {
        aStream.WriteInt32L( aText.Length() );
        aStream << aText;
        }
    else
        {
        aStream.WriteInt32L( KErrNotFound );
        }
    }

//  End of File
