/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:    test functions for testing aiwdialdatatypes.h
*
*/






// INCLUDE FILES
#include <aiwdialdatatypes.h>

#include "testdomextaiwcriteria.h"

// CONSTANTS
const TInt KNumberType = 1;
const TInt KWindowGroupId = 1;
const TInt KRedial = 1;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1TAiwDialDataV1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1TAiwDialDataV1L( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1* dialdatav1 = new ( ELeave ) TAiwDialDataV1();
    CleanupStack::PushL( dialdatav1 );
    
    STIF_ASSERT_NOT_NULL( dialdatav1 );
    
    CleanupStack::PopAndDestroy( dialdatav1 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1Reset
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1Reset( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.Reset();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetTelephoneNumber
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetTelephoneNumber( CStifItemParser& /*aItem*/ )
    {
    TAiwTelephoneNumber phoneNum;
    
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetTelephoneNumber( phoneNum );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetCallType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetCallType( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetCallType( EAiwVoice );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetName
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetName( CStifItemParser& /*aItem*/ )
    {
    TAiwNameBuffer nameBuffer;
    
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetName( nameBuffer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetNumberType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetNumberType( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetNumberType( KNumberType );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetContactId
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetContactId( CStifItemParser& /*aItem*/ )
    {
    TAiwContactId contactId = 1;
    
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetContactId( contactId );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetWindowGroup
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetWindowGroup( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetWindowGroup( KWindowGroupId );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetShowNumber
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetShowNumber( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetShowNumber( ETrue );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetRedial
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetRedial( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetRedial( KRedial );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetAllowMatch
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetAllowMatch( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetAllowMatch( ETrue );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetEndOtherCalls
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetEndOtherCalls( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetEndOtherCalls( ETrue );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetEmergency
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetEmergency( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetEmergency( ETrue );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetSubAddress
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetSubAddress( CStifItemParser& /*aItem*/ )
    {
    TAiwSubAddress subAddress;
    
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetSubAddress( subAddress );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetSATCall
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetSATCall( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetSATCall( ETrue );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetBearer
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetBearer( CStifItemParser& /*aItem*/ )
    {
    TAiwBearerCapability bearer;
    
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetBearer( bearer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetRemoveInvalidChars
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetRemoveInvalidChars( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetRemoveInvalidChars( ETrue );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SetContactItemField
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SetContactItemField( CStifItemParser& /*aItem*/ )
    {
    TAiwContactItemField contactItemField;
    
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SetContactItemField( contactItemField );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1TelephoneNumber
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1TelephoneNumber( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.TelephoneNumber();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1CallType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1CallType( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.CallType();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1Name
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1Name( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.Name();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1NumberType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1NumberType( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.NumberType();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1ContactId
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1ContactId( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.ContactId();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1WindowGroupId
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1WindowGroupId( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.WindowGroupId();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1Redial
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1Redial( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.Redial();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1ShowNumber
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1ShowNumber( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.ShowNumber();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1AllowMatch
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1AllowMatch( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.AllowMatch();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1EndOtherCalls
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1EndOtherCalls( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.EndOtherCalls();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1Emergency
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1Emergency( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.Emergency();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SubAddress
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SubAddress( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SubAddress();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1SATCall
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1SATCall( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.SATCall();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1Bearer
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1Bearer( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.Bearer();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1RemoveInvalidChars
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1RemoveInvalidChars( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.RemoveInvalidChars();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwDDV1ContactItemField
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwDDV1ContactItemField( CStifItemParser& /*aItem*/ )
    {
    TAiwDialDataV1 dialdatav1;
    
    dialdatav1.ContactItemField();
    
    return KErrNone;
    }


// End of file

