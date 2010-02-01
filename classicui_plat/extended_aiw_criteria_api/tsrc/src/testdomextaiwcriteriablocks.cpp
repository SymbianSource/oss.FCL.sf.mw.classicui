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
* Description:    test function implement of CTestDomExtAiwCriteria
*
*/





// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testdomextaiwcriteria.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDomExtAiwCriteria::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDomExtAiwCriteria::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.

        // for TAiwContactAssignDataBase in AiwContactAssignDataTypes.h
        ENTRY( "TestTAiwCADBAssignDataTypeFromBuffer",
                CTestDomExtAiwCriteria::TestTAiwCADBAssignDataTypeFromBuffer ),
        ENTRY( "TestTAiwCADBTAiwContactAssignDataBaseL",
                CTestDomExtAiwCriteria::TestTAiwCADBTAiwContactAssignDataBaseL ),
        ENTRY( "TestTAiwCADBTAiwContactAssignDataBaseWithDataTypeL",
                CTestDomExtAiwCriteria::TestTAiwCADBTAiwContactAssignDataBaseWithDataTypeL ),

        // for TAiwSingleContactAssignDataV1 in AiwContactAssignDataTypes.h
        ENTRY( "TestTAiwSCADV1TAiwSingleContactAssignDataV1L",
                CTestDomExtAiwCriteria::TestTAiwSCADV1TAiwSingleContactAssignDataV1L ),
        ENTRY( "TestTAiwSCADV1SetFlags",
                CTestDomExtAiwCriteria::TestTAiwSCADV1SetFlags ),
        ENTRY( "TestTAiwSCADV1SetEditorHelpContext",
                CTestDomExtAiwCriteria::TestTAiwSCADV1SetEditorHelpContext ),
        ENTRY( "TestTAiwSCADV1Flags",
                CTestDomExtAiwCriteria::TestTAiwSCADV1Flags ),
        ENTRY( "TestTAiwSCADV1EditorHelpContext",
                CTestDomExtAiwCriteria::TestTAiwSCADV1EditorHelpContext ),

        // for TAiwMultipleContactAssignDataV1 in AiwContactAssignDataTypes.h
        ENTRY( "TestTAiwMCADV1TAiwMultipleContactAssignDataV1L",
                CTestDomExtAiwCriteria::TestTAiwMCADV1TAiwMultipleContactAssignDataV1L ),
        ENTRY( "TestTAiwMCADV1SetFlags",
                CTestDomExtAiwCriteria::TestTAiwMCADV1SetFlags ),
        ENTRY( "TestTAiwMCADV1Flags",
                CTestDomExtAiwCriteria::TestTAiwMCADV1Flags ),

        // for TAiwContactAttributeAssignDataV1 in AiwContactAssignDataTypes.h
        ENTRY( "TestTAiwCAADV1TAiwContactAttributeAssignDataV1L",
                CTestDomExtAiwCriteria::TestTAiwCAADV1TAiwContactAttributeAssignDataV1L ),
        ENTRY( "TestTAiwCAADV1SetFlags",
                CTestDomExtAiwCriteria::TestTAiwCAADV1SetFlags ),
        ENTRY( "TestTAiwCAADV1SetAttributeRemove",
                CTestDomExtAiwCriteria::TestTAiwCAADV1SetAttributeRemove ),
        ENTRY( "TestTAiwCAADV1Flags",
                CTestDomExtAiwCriteria::TestTAiwCAADV1Flags ),
        ENTRY( "TestTAiwCAADV1RemoveAttribute",
                CTestDomExtAiwCriteria::TestTAiwCAADV1RemoveAttribute ),

        // for TAiwContactSelectionDataBase in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwCSDBSelectionDataTypeFromBuffer",
                CTestDomExtAiwCriteria::TestTAiwCSDBSelectionDataTypeFromBuffer ),
        ENTRY( "TestTAiwCSDBTAiwContactSelectionDataBaseL",
                CTestDomExtAiwCriteria::TestTAiwCSDBTAiwContactSelectionDataBaseL ),
        ENTRY( "TestTAiwCSDBTAiwContactSelectionDataBaseWithDataTypeL",
                CTestDomExtAiwCriteria::TestTAiwCSDBTAiwContactSelectionDataBaseWithDataTypeL ),

        // for TAiwSingleEntrySelectionDataV1 in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwSESDV1TAiwSingleEntrySelectionDataV1L",
                CTestDomExtAiwCriteria::TestTAiwSESDV1TAiwSingleEntrySelectionDataV1L ),
        ENTRY( "TestTAiwSESDV1SetFlags",
                CTestDomExtAiwCriteria::TestTAiwSESDV1SetFlags ),
        ENTRY( "TestTAiwSESDV1Flags",
                CTestDomExtAiwCriteria::TestTAiwSESDV1Flags ),

        // for TAiwSingleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwSESDV2TAiwSingleEntrySelectionDataV2L",
                CTestDomExtAiwCriteria::TestTAiwSESDV2TAiwSingleEntrySelectionDataV2L ),
        ENTRY( "TestTAiwSESDV2SetFlags",
                CTestDomExtAiwCriteria::TestTAiwSESDV2SetFlags ),
        ENTRY( "TestTAiwSESDV2SetFetchFilterL",
                CTestDomExtAiwCriteria::TestTAiwSESDV2SetFetchFilterL ),
        ENTRY( "TestTAiwSESDV2Flags",
                CTestDomExtAiwCriteria::TestTAiwSESDV2Flags ),
        ENTRY( "TestTAiwSESDV2FetchFilter",
                CTestDomExtAiwCriteria::TestTAiwSESDV2FetchFilter ),

        // for TAiwMultipleEntrySelectionDataV1 in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwMESDV1TAiwMultipleEntrySelectionDataV1L",
                CTestDomExtAiwCriteria::TestTAiwMESDV1TAiwMultipleEntrySelectionDataV1L ),
        ENTRY( "TestTAiwMESDV1SetFlags",
                CTestDomExtAiwCriteria::TestTAiwMESDV1SetFlags ),
        ENTRY( "TestTAiwMESDV1Flags",
                CTestDomExtAiwCriteria::TestTAiwMESDV1Flags ),

        // for TAiwMultipleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwMESDV2TAiwMultipleEntrySelectionDataV2L",
                CTestDomExtAiwCriteria::TestTAiwMESDV2TAiwMultipleEntrySelectionDataV2L ),
        ENTRY( "TestTAiwMESDV2SetFlags",
                CTestDomExtAiwCriteria::TestTAiwMESDV2SetFlags ),
        ENTRY( "TestTAiwMESDV2SetFetchFilterL",
                CTestDomExtAiwCriteria::TestTAiwMESDV2SetFetchFilterL ),
        ENTRY( "TestTAiwMESDV2Flags",
                CTestDomExtAiwCriteria::TestTAiwMESDV2Flags ),
        ENTRY( "TestTAiwMESDV2FetchFilter",
                CTestDomExtAiwCriteria::TestTAiwMESDV2FetchFilter ),

        // for TAiwSingleItemSelectionDataV1 in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwSISDV1TAiwSingleItemSelectionDataV1L",
                CTestDomExtAiwCriteria::TestTAiwSISDV1TAiwSingleItemSelectionDataV1L ),
        ENTRY( "TestTAiwSISDV1SetFlags",
                CTestDomExtAiwCriteria::TestTAiwSISDV1SetFlags ),
        ENTRY( "TestTAiwSISDV1SetAddressSelectType",
                CTestDomExtAiwCriteria::TestTAiwSISDV1SetAddressSelectType ),
        ENTRY( "TestTAiwSISDV1SetDefaultPrioritiesL",
                CTestDomExtAiwCriteria::TestTAiwSISDV1SetDefaultPrioritiesL ),
        ENTRY( "TestTAiwSISDV1Flags",
                CTestDomExtAiwCriteria::TestTAiwSISDV1Flags ),
        ENTRY( "TestTAiwSISDV1AddressSelectType",
                CTestDomExtAiwCriteria::TestTAiwSISDV1AddressSelectType ),
        ENTRY( "TestTAiwSISDV1DefaultPriorities",
                CTestDomExtAiwCriteria::TestTAiwSISDV1DefaultPriorities ),

        // for TAiwSingleItemSelectionDataV2 in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwSISDV2TAiwSingleItemSelectionDataV2L",
                CTestDomExtAiwCriteria::TestTAiwSISDV2TAiwSingleItemSelectionDataV2L ),
        ENTRY( "TestTAiwSISDV2SetFlags",
                CTestDomExtAiwCriteria::TestTAiwSISDV2SetFlags ),
        ENTRY( "TestTAiwSISDV2SetAddressSelectResourceId",
                CTestDomExtAiwCriteria::TestTAiwSISDV2SetAddressSelectResourceId ),
        ENTRY( "TestTAiwSISDV2SetDefaultPrioritiesL",
                CTestDomExtAiwCriteria::TestTAiwSISDV2SetDefaultPrioritiesL ),
        ENTRY( "TestTAiwSISDV2Flags",
                CTestDomExtAiwCriteria::TestTAiwSISDV2Flags ),
        ENTRY( "TestTAiwSISDV2AddressSelectResourceId",
                CTestDomExtAiwCriteria::TestTAiwSISDV2AddressSelectResourceId ),
        ENTRY( "TestTAiwSISDV2DefaultPriorities",
                CTestDomExtAiwCriteria::TestTAiwSISDV2DefaultPriorities ),

        // for TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwSISDV3TAiwSingleItemSelectionDataV3L",
                CTestDomExtAiwCriteria::TestTAiwSISDV3TAiwSingleItemSelectionDataV3L ),
        ENTRY( "TestTAiwSISDV3SetFlags",
                CTestDomExtAiwCriteria::TestTAiwSISDV3SetFlags ),
        ENTRY( "TestTAiwSISDV3SetAddressSelectType",
                CTestDomExtAiwCriteria::TestTAiwSISDV3SetAddressSelectType ),
        ENTRY( "TestTAiwSISDV3SetDefaultPrioritiesL",
                CTestDomExtAiwCriteria::TestTAiwSISDV3SetDefaultPrioritiesL ),
        ENTRY( "TestTAiwSISDV3SetFetchFilterL",
                CTestDomExtAiwCriteria::TestTAiwSISDV3SetFetchFilterL ),
        ENTRY( "TestTAiwSISDV3Flags",
                CTestDomExtAiwCriteria::TestTAiwSISDV3Flags ),
        ENTRY( "TestTAiwSISDV3AddressSelectType",
                CTestDomExtAiwCriteria::TestTAiwSISDV3AddressSelectType ),
        ENTRY( "TestTAiwSISDV3DefaultPriorities",
                CTestDomExtAiwCriteria::TestTAiwSISDV3DefaultPriorities ),
        ENTRY( "TestTAiwSISDV3FetchFilter",
                CTestDomExtAiwCriteria::TestTAiwSISDV3FetchFilter ),

        // for TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h
        ENTRY( "TestTAiwMISDV1TAiwMultipleItemSelectionDataV1L",
                CTestDomExtAiwCriteria::TestTAiwMISDV1TAiwMultipleItemSelectionDataV1L ),
        ENTRY( "TestTAiwMISDV1SetFlags",
                CTestDomExtAiwCriteria::TestTAiwMISDV1SetFlags ),
        ENTRY( "TestTAiwMISDV1SetAddressSelectType",
                CTestDomExtAiwCriteria::TestTAiwMISDV1SetAddressSelectType ),
        ENTRY( "TestTAiwMISDV1SetDefaultPrioritiesL",
                CTestDomExtAiwCriteria::TestTAiwMISDV1SetDefaultPrioritiesL ),
        ENTRY( "TestTAiwMISDV1SetFetchFilterL",
                CTestDomExtAiwCriteria::TestTAiwMISDV1SetFetchFilterL ),
        ENTRY( "TestTAiwMISDV1Flags",
                CTestDomExtAiwCriteria::TestTAiwMISDV1Flags ),
        ENTRY( "TestTAiwMISDV1AddressSelectType",
                CTestDomExtAiwCriteria::TestTAiwMISDV1AddressSelectType ),
        ENTRY( "TestTAiwMISDV1DefaultPriorities",
                CTestDomExtAiwCriteria::TestTAiwMISDV1DefaultPriorities ),
        ENTRY( "TestTAiwMISDV1FetchFilter",
                CTestDomExtAiwCriteria::TestTAiwMISDV1FetchFilter ),

        // for TAiwDialDataV1 in AiwDialDataTypes.h
        ENTRY( "TestTAiwDDV1TAiwDialDataV1L",
                CTestDomExtAiwCriteria::TestTAiwDDV1TAiwDialDataV1L ),
        ENTRY( "TestTAiwDDV1Reset",
                CTestDomExtAiwCriteria::TestTAiwDDV1Reset ),
        ENTRY( "TestTAiwDDV1SetTelephoneNumber",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetTelephoneNumber ),
        ENTRY( "TestTAiwDDV1SetCallType",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetCallType ),
        ENTRY( "TestTAiwDDV1SetName",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetName ),
        ENTRY( "TestTAiwDDV1SetNumberType",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetNumberType ),
        ENTRY( "TestTAiwDDV1SetContactId",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetContactId ),
        ENTRY( "TestTAiwDDV1SetWindowGroup",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetWindowGroup ),
        ENTRY( "TestTAiwDDV1SetShowNumber",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetShowNumber ),
        ENTRY( "TestTAiwDDV1SetRedial",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetRedial ),
        ENTRY( "TestTAiwDDV1SetAllowMatch",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetAllowMatch ),
        ENTRY( "TestTAiwDDV1SetEndOtherCalls",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetEndOtherCalls ),
        ENTRY( "TestTAiwDDV1SetEmergency",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetEmergency ),
        ENTRY( "TestTAiwDDV1SetSubAddress",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetSubAddress ),
        ENTRY( "TestTAiwDDV1SetSATCall",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetSATCall ),
        ENTRY( "TestTAiwDDV1SetBearer",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetBearer ),
        ENTRY( "TestTAiwDDV1SetRemoveInvalidChars",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetRemoveInvalidChars ),
        ENTRY( "TestTAiwDDV1SetContactItemField",
                CTestDomExtAiwCriteria::TestTAiwDDV1SetContactItemField ),
        ENTRY( "TestTAiwDDV1TelephoneNumber",
                CTestDomExtAiwCriteria::TestTAiwDDV1TelephoneNumber ),
        ENTRY( "TestTAiwDDV1CallType",
                CTestDomExtAiwCriteria::TestTAiwDDV1CallType ),
        ENTRY( "TestTAiwDDV1Name",
                CTestDomExtAiwCriteria::TestTAiwDDV1Name ),
        ENTRY( "TestTAiwDDV1NumberType",
                CTestDomExtAiwCriteria::TestTAiwDDV1NumberType ),
        ENTRY( "TestTAiwDDV1ContactId",
                CTestDomExtAiwCriteria::TestTAiwDDV1ContactId ),
        ENTRY( "TestTAiwDDV1WindowGroupId",
                CTestDomExtAiwCriteria::TestTAiwDDV1WindowGroupId ),
        ENTRY( "TestTAiwDDV1Redial",
                CTestDomExtAiwCriteria::TestTAiwDDV1Redial ),
        ENTRY( "TestTAiwDDV1ShowNumber",
                CTestDomExtAiwCriteria::TestTAiwDDV1ShowNumber ),
        ENTRY( "TestTAiwDDV1AllowMatch",
                CTestDomExtAiwCriteria::TestTAiwDDV1AllowMatch ),
        ENTRY( "TestTAiwDDV1EndOtherCalls",
                CTestDomExtAiwCriteria::TestTAiwDDV1EndOtherCalls ),
        ENTRY( "TestTAiwDDV1Emergency",
                CTestDomExtAiwCriteria::TestTAiwDDV1Emergency ),
        ENTRY( "TestTAiwDDV1SubAddress",
                CTestDomExtAiwCriteria::TestTAiwDDV1SubAddress ),
        ENTRY( "TestTAiwDDV1SATCall",
                CTestDomExtAiwCriteria::TestTAiwDDV1SATCall ),
        ENTRY( "TestTAiwDDV1Bearer",
                CTestDomExtAiwCriteria::TestTAiwDDV1Bearer ),
        ENTRY( "TestTAiwDDV1RemoveInvalidChars",
                CTestDomExtAiwCriteria::TestTAiwDDV1RemoveInvalidChars ),
        ENTRY( "TestTAiwDDV1ContactItemField",
                CTestDomExtAiwCriteria::TestTAiwDDV1ContactItemField ),

        // for TAiwPocParameterData in AiwPoCParameters.h
        ENTRY( "TestTAiwPPDTAiwPocParameterDataL",
                CTestDomExtAiwCriteria::TestTAiwPPDTAiwPocParameterDataL ),
        ENTRY( "TestTAiwPPDVersion",
                CTestDomExtAiwCriteria::TestTAiwPPDVersion ),

        // [test cases entries]
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//  [End of File]
