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
* Description:     Inline methods for AiwDialDataTypes.
*
*/







// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// TAiwDialDataV1::TAiwDialDataV1
// 
// 
// -----------------------------------------------------------------------------
//
TAiwDialDataV1::TAiwDialDataV1()

// iTelNumber must be valid telephony number, i.e. must be changed to valid one.
:   iTelNumber( KNullDesC ),
// Optional parameters (below) can be left as they are if not needed.
    iCallType( EAiwVoice ),
    iName( KNullDesC ),
    iNumberType( KAiwDefaultNumberType ),
    iContactId( KAiwNoContact ),
    iWindowGroup( KAiwGoToIdle ),
    iRedial( KAiwRedialDefault ),
    iShowNumber( ETrue ),
    iAllowMatch( KAiwDefaultAllowMatch ),
    iEndOtherCalls( EFalse ),
    iEmergencyCall( EFalse ),
    iSubAddress( KNullDesC ),
    iSATCall( EFalse ),
    iBearer( KNullDesC8 ),
    iRemoveInvalidChars( EFalse )
/*<branchInfo originator="janneluo" since="07-04-10" category="new_feature" error=”none”>
<MCSS_5132_OFF_CYCLE_SW_INT>
</branchInfo>*/
// BRANCH 07-04-10 :janneluo
    ,iServiceId( 0 )
// BRANCH_END 07-04-10 :janneluo
    {
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::Reset
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::Reset()
    {
    iTelNumber = KNullDesC;

    SetCallType( EAiwVoice );
    iName = KNullDesC;
    SetNumberType( KAiwDefaultNumberType );
    SetContactId( KAiwNoContact );
    SetWindowGroup( KAiwGoToIdle );
    SetRedial( KAiwRedialDefault );
    SetShowNumber( ETrue );
    SetAllowMatch( KAiwDefaultAllowMatch );
    SetEndOtherCalls( EFalse );
    SetEmergency( EFalse );
    iSubAddress = KNullDesC;
    SetSATCall( EFalse );
    iBearer = KNullDesC8;
    SetRemoveInvalidChars( EFalse );
    iContactItemField = NULL;
/*<branchInfo originator="janneluo" since="07-04-10" category="new_feature" error=”none”>
<MCSS_5132_OFF_CYCLE_SW_INT>
</branchInfo>*/
// BRANCH 07-04-10 :janneluo
    iServiceId = 0;
// BRANCH_END 07-04-10 :janneluo
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetTelephoneNumber
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetTelephoneNumber( 
    const TAiwTelephoneNumber& aNumber )
    {
    iTelNumber = aNumber;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetCallType
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetCallType( TAiwCallType aCallType )
    {
    iCallType = aCallType;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetName
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetName( const TAiwNameBuffer& aName )
    {
    iName = aName;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetNumberType
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetNumberType( TInt aNumberType )
    {
    iNumberType = aNumberType;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetContactId
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetContactId( 
    TAiwContactId aContactId )
    {
    iContactId = aContactId;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetWindowGroup
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetWindowGroup( TInt aWindowGroupId )
    {
    iWindowGroup = aWindowGroupId;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetRedial
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetRedial( TInt aRedial )
    {
    iRedial = aRedial;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetShowNumber
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetShowNumber( TBool aShowNumber )
    {
    iShowNumber = aShowNumber;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetAllowMatch
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetAllowMatch( TBool aAllowMatch )
    {
    iAllowMatch = aAllowMatch;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetEndOtherCalls
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetEndOtherCalls( TBool aEndCalls )
    {
    iEndOtherCalls = aEndCalls;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetEmergency
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetEmergency( TBool aEmergency )
    {
    iEmergencyCall = aEmergency;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetSubAddress
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetSubAddress( 
    const TAiwSubAddress& aSubAddress )
    {
    iSubAddress = aSubAddress;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetSATCall
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetSATCall( TBool aSATCall )
    {
    iSATCall = aSATCall;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetBearer
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetBearer( 
    const TAiwBearerCapability& aBearer )
    {
    iBearer = aBearer;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetRemoveInvalidChars
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetRemoveInvalidChars( TBool aRemoveInvalidChars )
    {
    iRemoveInvalidChars = aRemoveInvalidChars;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetContactItemField
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetContactItemField( const TAiwContactItemField& aContactItemField )
    {
    iContactItemField = &aContactItemField;
    }

/*<branchInfo originator="janneluo" since="07-04-10" category="new_feature" error=”none”>
<MCSS_5132_OFF_CYCLE_SW_INT>
</branchInfo>*/
// BRANCH 07-04-10 :janneluo
// -----------------------------------------------------------------------------
// TAiwDialDataV1::SetServiceId
// 
// 
// -----------------------------------------------------------------------------
//
void TAiwDialDataV1::SetServiceId( TUint aServiceId )
    {
    iServiceId = aServiceId;
    }
// BRANCH_END 07-04-10 :janneluo

// -----------------------------------------------------------------------------
// TAiwDialDataV1::TelephoneNumber
// 
// 
// -----------------------------------------------------------------------------
//
const TAiwTelephoneNumber& 
    TAiwDialDataV1::TelephoneNumber() const
    {
    return iTelNumber;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::CallType
// 
// 
// -----------------------------------------------------------------------------
//
TAiwCallType TAiwDialDataV1::CallType() const
    {
    return iCallType;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::Name
// 
// 
// -----------------------------------------------------------------------------
//
const TAiwNameBuffer& TAiwDialDataV1::Name() const
    {
    return iName;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::NumberType
// 
// 
// -----------------------------------------------------------------------------
//
TInt TAiwDialDataV1::NumberType() const
    {
    return iNumberType;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::ContactId
// 
// 
// -----------------------------------------------------------------------------
//
TAiwContactId TAiwDialDataV1::ContactId() const
    {
    return iContactId;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::WindowGroupId
// 
// 
// -----------------------------------------------------------------------------
//
TInt TAiwDialDataV1::WindowGroupId() const
    {
    return iWindowGroup;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::Redial
// 
// 
// -----------------------------------------------------------------------------
//
TInt TAiwDialDataV1::Redial() const
    {
    return iRedial;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::ShowNumber
// 
// 
// -----------------------------------------------------------------------------
//
TBool TAiwDialDataV1::ShowNumber() const
    {
    return iShowNumber;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::AllowMatch
// 
// 
// -----------------------------------------------------------------------------
//
TBool TAiwDialDataV1::AllowMatch() const
    {
    return iAllowMatch;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::EndOtherCalls
// 
// 
// -----------------------------------------------------------------------------
//
TBool TAiwDialDataV1::EndOtherCalls() const
    {
    return iEndOtherCalls;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::Emergency
// 
// 
// -----------------------------------------------------------------------------
//
TBool TAiwDialDataV1::Emergency() const
    {
    return iEmergencyCall;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SubAddress
// 
// 
// -----------------------------------------------------------------------------
//
const TAiwSubAddress& TAiwDialDataV1::SubAddress() const
    {
    return iSubAddress;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::SATCall
// 
// 
// -----------------------------------------------------------------------------
//
TBool TAiwDialDataV1::SATCall() const
    {
    return iSATCall;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::Bearer
// 
// 
// -----------------------------------------------------------------------------
//
const TAiwBearerCapability& TAiwDialDataV1::Bearer() const
    {
    return iBearer;
    }


// -----------------------------------------------------------------------------
// TAiwDialDataV1::RemoveInvalidChars
// 
// 
// -----------------------------------------------------------------------------
//
TBool TAiwDialDataV1::RemoveInvalidChars() const
    {
    return iRemoveInvalidChars;
    }

// -----------------------------------------------------------------------------
// TAiwDialDataV1::ContactItemField
// 
// 
// -----------------------------------------------------------------------------
//
const TAiwContactItemField* TAiwDialDataV1::ContactItemField() const
    {
    return iContactItemField;
    }

/*<branchInfo originator="janneluo" since="07-04-10" category="new_feature" error=”none”>
<MCSS_5132_OFF_CYCLE_SW_INT>
</branchInfo>*/
// BRANCH 07-04-10 :janneluo
// -----------------------------------------------------------------------------
// TAiwDialDataV1::ServiceId
// 
// 
// -----------------------------------------------------------------------------
//
TUint TAiwDialDataV1::ServiceId() const
    {
    return iServiceId;
    }
// BRANCH_END 07-04-10 :janneluo
//  End of File  
