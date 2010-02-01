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
* Description:  Dynamic soft notification data store
*
*/

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif
#include "AknDynamicNotificationData.h"

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::NewL
//-----------------------------------------------------------------------------
//   
CAknDynamicNotificationData* CAknDynamicNotificationData::NewL( 
    RReadStream& aStream )
    {
    CAknDynamicNotificationData* self = NewLC( aStream );
    CleanupStack::Pop( self );
    return self;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::NewLC
//-----------------------------------------------------------------------------
//   
CAknDynamicNotificationData* CAknDynamicNotificationData::NewLC( 
    RReadStream& aStream )
    {
    CAknDynamicNotificationData* self = new(ELeave) CAknDynamicNotificationData;
    CleanupStack::PushL( self );
    self->ConstructL( aStream );
    return self;
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::CAknDynamicNotificationData
//-----------------------------------------------------------------------------
//   
CAknDynamicNotificationData::CAknDynamicNotificationData()
    {
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::~CAknDynamicNotificationData
//-----------------------------------------------------------------------------
//   
CAknDynamicNotificationData::~CAknDynamicNotificationData()
    {
    delete iCustomMessage;

    // softkeys
    delete iLeftSoftkey;
    delete iRightSoftkey;
    
    // note labels
    delete iNoteSingularLabel;
    delete iNotePluralLabel;
    delete iGroupSingularLabel;
    delete iGroupPluralLabel;

    // Image data
    delete iImageData; 
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::ConstructL
//-----------------------------------------------------------------------------
//   
void CAknDynamicNotificationData::ConstructL( RReadStream& aStream )
    {
    aStream >> *this;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::SetId
//-----------------------------------------------------------------------------
//   
void CAknDynamicNotificationData::SetId( TInt aId )
    {
    iNoteId = aId;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::Id
//-----------------------------------------------------------------------------
//   
TInt CAknDynamicNotificationData::Id() const
    {
    return iNoteId;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::Priority
//-----------------------------------------------------------------------------
//   
TInt CAknDynamicNotificationData::Priority() const
    {
    return iPriority;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::ViewId
//-----------------------------------------------------------------------------
//   
CAknNoteDialog::TTone CAknDynamicNotificationData::Tone() const
    {
    return iTone;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::ViewId
//-----------------------------------------------------------------------------
//   
TVwsViewId CAknDynamicNotificationData::ViewId() const
    {
    return iViewId;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::PluralViewId
//-----------------------------------------------------------------------------
//   
TVwsViewId CAknDynamicNotificationData::PluralViewId() const
    {
    return iPluralViewId;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::CustomMsgUid
//-----------------------------------------------------------------------------
//   
TUid CAknDynamicNotificationData::CustomMsgUid() const
    {
    return iCustomMessageId;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::CustomMsg
//-----------------------------------------------------------------------------
//   
const TDesC8& CAknDynamicNotificationData::CustomMsg() const
    {
    return iCustomMessage ? *iCustomMessage : KNullDesC8();
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::LeftSoftkey
//-----------------------------------------------------------------------------
//   
const TDesC& CAknDynamicNotificationData::LeftSoftkey() const
    {
    return iLeftSoftkey ? *iLeftSoftkey : KNullDesC();
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::RightSoftkey
//-----------------------------------------------------------------------------
//   
const TDesC& CAknDynamicNotificationData::RightSoftkey() const
    {
    return iRightSoftkey ? *iRightSoftkey : KNullDesC();
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::SingularLabel
//-----------------------------------------------------------------------------
//   
const TDesC& CAknDynamicNotificationData::SingularLabel() const
    {
    return iNoteSingularLabel ? *iNoteSingularLabel : KNullDesC();
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::PluralLabel
//-----------------------------------------------------------------------------
//   
const TDesC& CAknDynamicNotificationData::PluralLabel() const
    {
    return iNotePluralLabel ? *iNotePluralLabel : KNullDesC();
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::PluralLabelGroup
//-----------------------------------------------------------------------------
//   
const TDesC& CAknDynamicNotificationData::SingularLabelGroup() const
    {
    return iGroupSingularLabel ? *iGroupSingularLabel : KNullDesC();
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::PluralLabelGroup
//-----------------------------------------------------------------------------
//   
const TDesC& CAknDynamicNotificationData::PluralLabelGroup() const
    {
    return iGroupPluralLabel ? *iGroupPluralLabel : KNullDesC();
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::ImageData
//-----------------------------------------------------------------------------
//   
const TDesC8& CAknDynamicNotificationData::ImageData() const
    {
    return iImageData ? *iImageData : KNullDesC8();
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::EnableObserver
//-----------------------------------------------------------------------------
//   
TBool CAknDynamicNotificationData::EnableObserver() const
    {
    return iEnableObserver;
    }    

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::ResetContent
//-----------------------------------------------------------------------------
//   
void CAknDynamicNotificationData::ResetContent()
    {
    iNoteId = 0;
    iPriority = 0;
    iTone = CAknNoteDialog::ENoTone;

    // view activation related parameters
    iViewId = KNullViewId;
    iPluralViewId = KNullViewId;
    iCustomMessageId = KNullUid;
    delete iCustomMessage;
    iCustomMessage = NULL;

    // softkeys
    delete iLeftSoftkey;
    iLeftSoftkey = NULL;
    delete iRightSoftkey;
    iRightSoftkey = NULL;
    
    // parameters that would normally be read from a resource file
    delete iNoteSingularLabel;
    iNoteSingularLabel = NULL;
    delete iNotePluralLabel;
    iNotePluralLabel = NULL;
    delete iGroupSingularLabel;
    iGroupSingularLabel = NULL;
    delete iGroupPluralLabel;
    iGroupPluralLabel = NULL;

    // Image data
    delete iImageData;
    iImageData = NULL;
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::InternalizeL
//-----------------------------------------------------------------------------
//   
void CAknDynamicNotificationData::InternalizeL( RReadStream& aStream )
    {
    ResetContent();
    
    // From AknDynamicSoftNotifier (Client side) 
    iNoteId   = aStream.ReadInt32L();
    
    // NOTE: These steps needs to be equal to those in 
    // TAknDynamicSoftNotificationParams::ExternalizeL, so that the 
    // data won't be corrupted
    //    
    iPriority = aStream.ReadInt32L();
    iTone = (CAknNoteDialog::TTone)aStream.ReadInt32L();
    
    iViewId.iAppUid.iUid  = aStream.ReadUint32L();
    iViewId.iViewUid.iUid = aStream.ReadUint32L();
    iPluralViewId.iAppUid.iUid  = aStream.ReadUint32L();
    iPluralViewId.iViewUid.iUid = aStream.ReadUint32L();
    
    TInt messageUid = aStream.ReadInt32L();
    if( messageUid != KErrNotFound )
        {
        iCustomMessageId.iUid = messageUid;
        iCustomMessage = InternalizeText8L( aStream );
        }

    iLeftSoftkey  = InternalizeText16L( aStream );
    iRightSoftkey = InternalizeText16L( aStream );
    
    iNoteSingularLabel = InternalizeText16L( aStream );
    iNotePluralLabel   = InternalizeText16L( aStream );
    iGroupSingularLabel = InternalizeText16L( aStream );
    iGroupPluralLabel   = InternalizeText16L( aStream );
    
    iEnableObserver = aStream.ReadUint8L();
    
    iImageData = InternalizeText8L( aStream );
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::ExternalizeL
//-----------------------------------------------------------------------------
//   
void CAknDynamicNotificationData::ExternalizeL( RWriteStream& aStream ) const
    {
    aStream.WriteInt32L( iNoteId );
    aStream.WriteInt32L( iPriority );
    aStream.WriteInt32L( iTone );
    
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

    ExternalizeTextL( aStream, iLeftSoftkey );
    ExternalizeTextL( aStream, iRightSoftkey );
    
    ExternalizeTextL( aStream, iNoteSingularLabel );
    ExternalizeTextL( aStream, iNotePluralLabel );
    ExternalizeTextL( aStream, iGroupSingularLabel );
    ExternalizeTextL( aStream, iGroupPluralLabel );
    
    aStream.WriteUint8L(iEnableObserver);
    
    ExternalizeTextL( aStream, iImageData );
    }
    
//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::InternalizeText16L
//-----------------------------------------------------------------------------
//
HBufC16* CAknDynamicNotificationData::InternalizeText16L( 
    RReadStream& aStream ) const
    {
    HBufC16* text = NULL;
    TInt length = aStream.ReadInt32L();
    if( length > 0 )
        {
        text = HBufC16::NewL( aStream, length );
        }
    return text;    
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::InternalizeText8L
//-----------------------------------------------------------------------------
//
HBufC8* CAknDynamicNotificationData::InternalizeText8L( 
    RReadStream& aStream ) const
    {
    HBufC8* text = NULL;
    TInt length = aStream.ReadInt32L();
    if( length > 0 )
        {
        text = HBufC8::NewL( aStream, length );
        }
    return text;    
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::ExternalizeTextL
//-----------------------------------------------------------------------------
//
void CAknDynamicNotificationData::ExternalizeTextL( 
    RWriteStream& aStream, 
    const TDesC16* aText ) const
    {
    TInt length = aText ? aText->Length() : 0;
    if( length > 0 )
        {
        aStream.WriteInt32L( aText->Length() );
        aStream << *aText;
        }
    else
        {
        aStream.WriteInt32L( KErrNotFound );
        }
    }

//-----------------------------------------------------------------------------
// CAknDynamicNotificationData::ExternalizeTextL
//-----------------------------------------------------------------------------
//
void CAknDynamicNotificationData::ExternalizeTextL( 
    RWriteStream& aStream, 
    const TDesC8* aText ) const
    {
    TInt length = aText ? aText->Length() : 0;
    if( length > 0 )
        {
        aStream.WriteInt32L( aText->Length() );
        aStream << *aText;
        }
    else
        {
        aStream.WriteInt32L( KErrNotFound );
        }
    }

//  End of File
