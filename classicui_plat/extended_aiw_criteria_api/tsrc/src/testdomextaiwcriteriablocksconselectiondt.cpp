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
* Description:    test functions for testing aiwcontactselectiondatatypes.h
*
*/






// INCLUDE FILES
#include <app/mvpbkfieldtype.h>
#include <cvpbkfieldtypeselector.h>
#include <rvpbkcontactfielddefaultpriorities.h>
#include <aiwcontactselectiondatatypes.h>

#include "testdomextaiwcriteria.h"

// CONSTANTS
_LIT8( KBufferText, "Test");

const TInt KBufferLength = 64;
const TUint KGeneralFlags = 1;
const TInt KAddressSelectResourceId = 1;


// FORWARD DECLARATION
// For testing protected function of TAiwContactSelectionDataBase
class TTestContactSelectionDataBase: public TAiwContactSelectionDataBase
    {
public:
     // constructor that sets the type of the data class.
    TTestContactSelectionDataBase( TAiwContactSelectionDataType aSelectionDataType )
    : TAiwContactSelectionDataBase( aSelectionDataType )
        {
        }
    };

// CTestMVPbkFieldType for testing function of TAiwSingleEntrySelectionDataV2
class CTestMVPbkFieldType: public CBase, public MVPbkFieldType
    {
public:
    // from MVPbkFieldType
    TArray<TVPbkFieldVersitProperty> VersitProperties() const { return iArray; }
    
    // from MVPbkFieldType
    const TVPbkFieldTypeParameters& ExcludedParameters() const { return *iTypeParams; }
    
    // from MVPbkFieldType
    TVPbkNonVersitFieldType NonVersitType() const { return EVPbkNonVersitTypeNone; }
    
    // from MVPbkFieldType
    TBool IsSame( const MVPbkFieldType& /*aOtherType*/ ) const { return ETrue; }
    
    // from MVPbkFieldType
    TBool Matches( const TVPbkFieldVersitProperty& /*aMatchProperty*/, TInt /*aMatchPriority*/ ) const
    { return ETrue; }
    
    // from MVPbkFieldType
    TInt FieldTypeResId() const { return KErrNone; }
    
private:
    // TArray<TVPbkFieldVersitProperty> array
    TArray<TVPbkFieldVersitProperty> iArray;
    
    // TVPbkFieldTypeParameters
    TVPbkFieldTypeParameters* iTypeParams;
    };

// CTestMVPbkFieldTypeList for testing function of TAiwSingleEntrySelectionDataV2
class CTestMVPbkFieldTypeList: public CBase, public MVPbkFieldTypeList
    {
public:
    // constructor
    CTestMVPbkFieldTypeList(): iFieldType( NULL ) { }

    // from MVPbkFieldTypeList
    TInt FieldTypeCount() const { return KErrNone; }
    
    // from MVPbkFieldTypeList
    const MVPbkFieldType& FieldTypeAt( TInt /*aIndex*/ ) const { return *iFieldType; }
    
    // from MVPbkFieldTypeList
    TBool ContainsSame( const MVPbkFieldType& /*aFieldType*/ ) const { return ETrue; }
    
    // from MVPbkFieldTypeList
    TInt MaxMatchPriority() const { return KErrNone; }
    
    // from MVPbkFieldTypeList
    const MVPbkFieldType* FindMatch(
                    const TVPbkFieldVersitProperty& /*aMatchProperty*/,
                    TInt /*aMatchPriority*/ ) const
                    { return NULL; }
    
    // from MVPbkFieldTypeList
    const MVPbkFieldType* FindMatch(
                    TVPbkNonVersitFieldType /*aNonVersitType*/ ) const
                    { return NULL; }
    
private:
    // the instance of CTestMVPbkFieldType
    CTestMVPbkFieldType* iFieldType;
    };


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCSDBSelectionDataTypeFromBufferL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCSDBSelectionDataTypeFromBuffer(
        CStifItemParser& /*aItem*/)
    {
    TAiwContactSelectionDataBase seldatabase;
    
    TBuf8<KBufferLength> buffer( KBufferText );
    seldatabase.SelectionDataTypeFromBuffer( buffer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCSDBTAiwContactSelectionDataBaseL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCSDBTAiwContactSelectionDataBaseL(
        CStifItemParser& /*aItem*/)
    {
    TAiwContactSelectionDataBase* seldatabase =
                new ( ELeave ) TAiwContactSelectionDataBase();
    CleanupStack::PushL( seldatabase );
    
    STIF_ASSERT_NOT_NULL( seldatabase );
    
    CleanupStack::PopAndDestroy( seldatabase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCSDBTAiwContactSelectionDataBaseWithDataTypeL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCSDBTAiwContactSelectionDataBaseWithDataTypeL(
        CStifItemParser& /*aItem*/)
    {
    TTestContactSelectionDataBase* testseldatabase =
        new ( ELeave ) TTestContactSelectionDataBase( EAiwSingleEntrySelectionV1 );
    CleanupStack::PushL( testseldatabase );
    
    STIF_ASSERT_NOT_NULL( testseldatabase );
    
    CleanupStack::PopAndDestroy( testseldatabase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSESDV1TAiwSingleEntrySelectionDataV1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSESDV1TAiwSingleEntrySelectionDataV1L(
        CStifItemParser& /*aItem*/)
    {
    TAiwSingleEntrySelectionDataV1* singledatav1 =
            new ( ELeave ) TAiwSingleEntrySelectionDataV1();
    CleanupStack::PushL( singledatav1 );
    
    STIF_ASSERT_NOT_NULL( singledatav1 );
    
    CleanupStack::PopAndDestroy( singledatav1 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSESDV1SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSESDV1SetFlags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleEntrySelectionDataV1 singledatav1;
    
    singledatav1.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSESDV1Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSESDV1Flags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleEntrySelectionDataV1 singledatav1;
    
    singledatav1.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSESDV2TAiwSingleEntrySelectionDataV2L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSESDV2TAiwSingleEntrySelectionDataV2L(
        CStifItemParser& /*aItem*/)
    {
    TAiwSingleEntrySelectionDataV2* singledatav2 =
            new ( ELeave ) TAiwSingleEntrySelectionDataV2();
    CleanupStack::PushL( singledatav2 );
    
    STIF_ASSERT_NOT_NULL( singledatav2 );
    
    CleanupStack::PopAndDestroy( singledatav2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSESDV2SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSESDV2SetFlags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleEntrySelectionDataV2 singledatav2;
    
    singledatav2.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSESDV2SetFetchFilterL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSESDV2SetFetchFilterL( CStifItemParser& /*aItem*/)
    {
    CTestMVPbkFieldTypeList* fieldTypeList = new ( ELeave ) CTestMVPbkFieldTypeList();
    CleanupStack::PushL( fieldTypeList );
    
    CVPbkFieldTypeSelector* filter = CVPbkFieldTypeSelector::NewL( *fieldTypeList );
    CleanupStack::PushL( filter );
    
    TAiwSingleEntrySelectionDataV2 singledatav2;
    
    singledatav2.SetFetchFilter( filter );
    
    CleanupStack::PopAndDestroy( filter );
    CleanupStack::PopAndDestroy( fieldTypeList );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSESDV2Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSESDV2Flags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleEntrySelectionDataV2 singledatav2;
    
    singledatav2.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSESDV2FetchFilter
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSESDV2FetchFilter( CStifItemParser& /*aItem*/)
    {
    TAiwSingleEntrySelectionDataV2 singledatav2;
    
    singledatav2.FetchFilter();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMESDV1TAiwMultipleEntrySelectionDataV1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMESDV1TAiwMultipleEntrySelectionDataV1L(
        CStifItemParser& /*aItem*/)
    {
    TAiwMultipleEntrySelectionDataV1* multidatav1 =
            new ( ELeave ) TAiwMultipleEntrySelectionDataV1();
    CleanupStack::PushL( multidatav1 );
    
    STIF_ASSERT_NOT_NULL( multidatav1 );
    
    CleanupStack::PopAndDestroy( multidatav1 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMESDV1SetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMESDV1SetFlags( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleEntrySelectionDataV1 multidatav1;
    
    multidatav1.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMESDV1Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMESDV1Flags( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleEntrySelectionDataV1 multidatav1;
    
    multidatav1.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMESDV2TAiwMultipleEntrySelectionDataV2L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMESDV2TAiwMultipleEntrySelectionDataV2L(
        CStifItemParser& /*aItem*/)
    {
    TAiwMultipleEntrySelectionDataV2* multidatav2 =
                    new ( ELeave ) TAiwMultipleEntrySelectionDataV2();
    CleanupStack::PushL( multidatav2 );
    
    STIF_ASSERT_NOT_NULL( multidatav2 );
    
    CleanupStack::PopAndDestroy( multidatav2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMESDV2SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMESDV2SetFlags( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleEntrySelectionDataV2 multidatav2;
    
    multidatav2.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMESDV2SetFetchFilterL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMESDV2SetFetchFilterL( CStifItemParser& /*aItem*/)
    {
    CTestMVPbkFieldTypeList* fieldTypeList = new ( ELeave ) CTestMVPbkFieldTypeList();
    CleanupStack::PushL( fieldTypeList );
    
    CVPbkFieldTypeSelector* filter = CVPbkFieldTypeSelector::NewL( *fieldTypeList );
    CleanupStack::PushL( filter );
    
    TAiwMultipleEntrySelectionDataV2 multidatav2;
    
    multidatav2.SetFetchFilter( filter );
    
    CleanupStack::PopAndDestroy( filter );
    CleanupStack::PopAndDestroy( fieldTypeList );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMESDV2Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMESDV2Flags( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleEntrySelectionDataV2 multidatav2;
    
    multidatav2.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMESDV2FetchFilter
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMESDV2FetchFilter( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleEntrySelectionDataV2 multidatav2;
    
    multidatav2.FetchFilter();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV1TAiwSingleItemSelectionDataV1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV1TAiwSingleItemSelectionDataV1L( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV1* singleitemdatav1 =
                new ( ELeave ) TAiwSingleItemSelectionDataV1();
    CleanupStack::PushL( singleitemdatav1 );
    
    STIF_ASSERT_NOT_NULL( singleitemdatav1 );
    
    CleanupStack::PopAndDestroy( singleitemdatav1 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV1SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV1SetFlags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV1 singleitemdatav1;
    
    singleitemdatav1.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV1SetAddressSelectType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV1SetAddressSelectType( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV1 singleitemdatav1;
    
    singleitemdatav1.SetAddressSelectType( EAiwAllItemsSelect );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV1SetDefaultPrioritiesL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV1SetDefaultPrioritiesL( CStifItemParser& /*aItem*/)
    {
    RVPbkContactFieldDefaultPriorities defaultPriorities;
    CleanupClosePushL( defaultPriorities );
    
    TAiwSingleItemSelectionDataV1 singleitemdatav1;
    
    singleitemdatav1.SetDefaultPriorities( defaultPriorities );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV1Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV1Flags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV1 singleitemdatav1;
    
    singleitemdatav1.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV1AddressSelectType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV1AddressSelectType( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV1 singleitemdatav1;
    
    singleitemdatav1.AddressSelectType();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV1DefaultPriorities
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV1DefaultPriorities( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV1 singleitemdatav1;
    
    singleitemdatav1.DefaultPriorities();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV2TAiwSingleItemSelectionDataV2L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV2TAiwSingleItemSelectionDataV2L( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV2* singleitemdatav2 =
                    new ( ELeave ) TAiwSingleItemSelectionDataV2();
    CleanupStack::PushL( singleitemdatav2 );
    
    STIF_ASSERT_NOT_NULL( singleitemdatav2 );
    
    CleanupStack::PopAndDestroy( singleitemdatav2 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV2SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV2SetFlags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV2 singleitemdatav2;
    
    singleitemdatav2.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV2SetAddressSelectResourceId
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV2SetAddressSelectResourceId( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV2 singleitemdatav2;
    
    singleitemdatav2.SetAddressSelectResourceId( KAddressSelectResourceId );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV2SetDefaultPrioritiesL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV2SetDefaultPrioritiesL( CStifItemParser& /*aItem*/)
    {
    RVPbkContactFieldDefaultPriorities defaultPriorities;
    CleanupClosePushL( defaultPriorities );
    
    TAiwSingleItemSelectionDataV2 singleitemdatav2;
    
    singleitemdatav2.SetDefaultPriorities( defaultPriorities );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV2Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV2Flags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV2 singleitemdatav2;
    
    singleitemdatav2.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV2AddressSelectResourceId
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV2AddressSelectResourceId( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV2 singleitemdatav2;
    
    singleitemdatav2.AddressSelectResourceId();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV2DefaultPriorities
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV2DefaultPriorities( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV2 singleitemdatav2;
    
    singleitemdatav2.DefaultPriorities();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3TAiwSingleItemSelectionDataV3L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3TAiwSingleItemSelectionDataV3L( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV3* singleitemdatav3 =
                new ( ELeave ) TAiwSingleItemSelectionDataV3();
    CleanupStack::PushL( singleitemdatav3 );
    
    STIF_ASSERT_NOT_NULL( singleitemdatav3 );
    
    CleanupStack::PopAndDestroy( singleitemdatav3 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3SetFlags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV3 singleitemdatav3;
    
    singleitemdatav3.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3SetAddressSelectType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3SetAddressSelectType( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV3 singleitemdatav3;
    
    singleitemdatav3.SetAddressSelectType( EAiwAllItemsSelect );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3SetDefaultPrioritiesL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3SetDefaultPrioritiesL( CStifItemParser& /*aItem*/)
    {
    RVPbkContactFieldDefaultPriorities defaultPriorities;
    CleanupClosePushL( defaultPriorities );
    
    TAiwSingleItemSelectionDataV3 singleitemdatav3;
    
    singleitemdatav3.SetDefaultPriorities( defaultPriorities );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3SetFetchFilterL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3SetFetchFilterL( CStifItemParser& /*aItem*/)
    {
    CTestMVPbkFieldTypeList* fieldTypeList = new ( ELeave ) CTestMVPbkFieldTypeList();
    CleanupStack::PushL( fieldTypeList );
    
    CVPbkFieldTypeSelector* filter = CVPbkFieldTypeSelector::NewL( *fieldTypeList );
    CleanupStack::PushL( filter );
    
    TAiwSingleItemSelectionDataV3 singleitemdatav3;
    
    singleitemdatav3.SetFetchFilter( filter );
    
    CleanupStack::PopAndDestroy( filter );
    CleanupStack::PopAndDestroy( fieldTypeList );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3Flags( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV3 singleitemdatav3;
    
    singleitemdatav3.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3AddressSelectType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3AddressSelectType( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV3 singleitemdatav3;
    
    singleitemdatav3.AddressSelectType();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3DefaultPriorities
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3DefaultPriorities( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV3 singleitemdatav3;
    
    singleitemdatav3.DefaultPriorities();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSISDV3FetchFilter
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSISDV3FetchFilter( CStifItemParser& /*aItem*/)
    {
    TAiwSingleItemSelectionDataV3 singleitemdatav3;
    
    singleitemdatav3.FetchFilter();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1TAiwMultipleItemSelectionDataV1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1TAiwMultipleItemSelectionDataV1L( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleItemSelectionDataV1* multiitemdatav1 =
                    new ( ELeave ) TAiwMultipleItemSelectionDataV1();
    CleanupStack::PushL( multiitemdatav1 );
    
    STIF_ASSERT_NOT_NULL( multiitemdatav1 );
    
    CleanupStack::PopAndDestroy( multiitemdatav1 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1SetFlags( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleItemSelectionDataV1 multiitemdatav1;
    
    multiitemdatav1.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1SetAddressSelectType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1SetAddressSelectType( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleItemSelectionDataV1 multiitemdatav1;
    
    multiitemdatav1.SetAddressSelectType( EAiwAllItemsSelect );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1SetDefaultPrioritiesL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1SetDefaultPrioritiesL( CStifItemParser& /*aItem*/)
    {
    RVPbkContactFieldDefaultPriorities defaultPriorities;
    CleanupClosePushL( defaultPriorities );
    
    TAiwMultipleItemSelectionDataV1 multiitemdatav1;
    
    multiitemdatav1.SetDefaultPriorities( defaultPriorities );
    
    CleanupStack::PopAndDestroy();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1SetFetchFilterL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1SetFetchFilterL( CStifItemParser& /*aItem*/)
    {
    CTestMVPbkFieldTypeList* fieldTypeList = new ( ELeave ) CTestMVPbkFieldTypeList();
    CleanupStack::PushL( fieldTypeList );
    
    CVPbkFieldTypeSelector* filter = CVPbkFieldTypeSelector::NewL( *fieldTypeList );
    CleanupStack::PushL( filter );
    
    TAiwMultipleItemSelectionDataV1 multiitemdatav1;
    
    multiitemdatav1.SetFetchFilter( filter );
    
    CleanupStack::PopAndDestroy( filter );
    CleanupStack::PopAndDestroy( fieldTypeList );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1Flags( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleItemSelectionDataV1 multiitemdatav1;
    
    multiitemdatav1.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1AddressSelectType
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1AddressSelectType( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleItemSelectionDataV1 multiitemdatav1;
    
    multiitemdatav1.AddressSelectType();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1DefaultPriorities
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1DefaultPriorities( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleItemSelectionDataV1 multiitemdatav1;
    
    multiitemdatav1.DefaultPriorities();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMISDV1FetchFilter
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMISDV1FetchFilter( CStifItemParser& /*aItem*/)
    {
    TAiwMultipleItemSelectionDataV1 multiitemdatav1;
    
    multiitemdatav1.FetchFilter();
    
    return KErrNone;
    }


// End of file

