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
* Description:    test functions for testing AiwContactAssignDataTypes.h
*
*/






// INCLUDE FILES
#include <aiwcontactassigndatatypes.h>

#include "testdomextaiwcriteria.h"


using namespace AiwContactAssign;

// CONSTANTS
_LIT8( KBufferText, "Test");

const TInt KBufferLength = 64;
const TUint KGeneralFlags = 1;


// FORWARD DECLARATION
// TTestContactAssignDataBase
// For testing protected function TAiwContactAssignDataBase of TAiwContactAssignDataBase
class TTestContactAssignDataBase: public TAiwContactAssignDataBase
    {
public:
    /**
     * Constructor that sets the type of the data class.
     *
     * @param aAssignDataType Type of the contact assign data.
     */
    TTestContactAssignDataBase( TAiwContactAssignDataType aAssignDataType )
    : TAiwContactAssignDataBase( aAssignDataType )
        {
        }
    };


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCADBAssignDataTypeFromBufferL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCADBAssignDataTypeFromBuffer(
        CStifItemParser& /*aItem*/)
    {
    TAiwContactAssignDataBase database;
    
    TBuf8<KBufferLength> buffer( KBufferText );
    database.AssignDataTypeFromBuffer( buffer );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCADBTAiwContactAssignDataBaseL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCADBTAiwContactAssignDataBaseL(
        CStifItemParser& /*aItem*/ )
    {
    TAiwContactAssignDataBase* database = new ( ELeave ) TAiwContactAssignDataBase();
    CleanupStack::PushL( database );
    STIF_ASSERT_NOT_NULL( database );
    CleanupStack::PopAndDestroy( database );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCADBTAiwContactAssignDataBaseWithDataTypeL
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCADBTAiwContactAssignDataBaseWithDataTypeL(
        CStifItemParser& /*aItem*/ )
    {
    TTestContactAssignDataBase* testdatabase =
        new ( ELeave ) TTestContactAssignDataBase( EAiwSingleContactAssignV1 );
    CleanupStack::PushL( testdatabase );
    STIF_ASSERT_NOT_NULL( testdatabase );
    CleanupStack::PopAndDestroy( testdatabase );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSCADV1TAiwSingleContactAssignDataV1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSCADV1TAiwSingleContactAssignDataV1L(
        CStifItemParser& /*aItem*/ )
    {
    TAiwSingleContactAssignDataV1* singledatav1 =
                new ( ELeave ) TAiwSingleContactAssignDataV1();
    CleanupStack::PushL( singledatav1 );
    STIF_ASSERT_NOT_NULL( singledatav1 );
    CleanupStack::PopAndDestroy( singledatav1 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSCADV1SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSCADV1SetFlags(
        CStifItemParser& /*aItem*/ )
    {
    TAiwSingleContactAssignDataV1 singledatav1;
    
    singledatav1.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSCADV1SetEditorHelpContext
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSCADV1SetEditorHelpContext(
        CStifItemParser& /*aItem*/ )
    {
    TAiwSingleContactAssignDataV1 singledatav1;
    
    TCoeHelpContext helpcontext;
    singledatav1.SetEditorHelpContext( helpcontext );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSCADV1Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSCADV1Flags( CStifItemParser& /*aItem*/ )
    {
    TAiwSingleContactAssignDataV1 singledatav1;
    
    singledatav1.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwSCADV1EditorHelpContext
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwSCADV1EditorHelpContext( CStifItemParser& /*aItem*/ )
    {
    TAiwSingleContactAssignDataV1 singledatav1;
    
    singledatav1.EditorHelpContext();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMCADV1TAiwMultipleContactAssignDataV1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMCADV1TAiwMultipleContactAssignDataV1L(
        CStifItemParser& /*aItem*/ )
    {
    TAiwMultipleContactAssignDataV1* multidatav1 =
                new ( ELeave ) TAiwMultipleContactAssignDataV1();
    CleanupStack::PushL( multidatav1 );
    
    STIF_ASSERT_NOT_NULL( multidatav1 );
    
    CleanupStack::PopAndDestroy( multidatav1 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMCADV1SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMCADV1SetFlags(
        CStifItemParser& /*aItem*/ )
    {
    TAiwMultipleContactAssignDataV1 multidatav1;
    
    multidatav1.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwMCADV1Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwMCADV1Flags( CStifItemParser& /*aItem*/ )
    {
    TAiwMultipleContactAssignDataV1 multidatav1;
    
    multidatav1.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCAADV1TAiwContactAttributeAssignDataV1L
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCAADV1TAiwContactAttributeAssignDataV1L(
        CStifItemParser& /*aItem*/ )
    {
    TAiwContactAttributeAssignDataV1* attdatav1 =
                new ( ELeave ) TAiwContactAttributeAssignDataV1();
    CleanupStack::PushL( attdatav1 );
    
    STIF_ASSERT_NOT_NULL( attdatav1 );
    
    CleanupStack::PopAndDestroy( attdatav1 );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCAADV1SetFlags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCAADV1SetFlags( CStifItemParser& /*aItem*/ )
    {
    TAiwContactAttributeAssignDataV1 attdatav1;
    
    attdatav1.SetFlags( KGeneralFlags );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCAADV1SetAttributeRemove
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCAADV1SetAttributeRemove( CStifItemParser& /*aItem*/ )
    {
    TAiwContactAttributeAssignDataV1 attdatav1;
    
    attdatav1.SetAttributeRemove( ETrue );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCAADV1Flags
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCAADV1Flags( CStifItemParser& /*aItem*/ )
    {
    TAiwContactAttributeAssignDataV1 attdatav1;
    
    attdatav1.Flags();
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::TestTAiwCAADV1RemoveAttribute
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::TestTAiwCAADV1RemoveAttribute( CStifItemParser& /*aItem*/ )
    {
    TAiwContactAttributeAssignDataV1 attdatav1;
    
    attdatav1.RemoveAttribute();
    
    return KErrNone;
    }


//End Of File
