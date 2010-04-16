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
* Description:    test functions in extended_aiw_criteria_api
*
*/





#ifndef C_TESTDOMEXTAIWCRITERIA_H
#define C_TESTDOMEXTAIWCRITERIA_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>


// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestdomextaiwcriteriaLogPath, "\\logs\\testframework\\testdomextaiwcriteria\\" ); 
// Log file
_LIT( KtestdomextaiwcriteriaLogFile, "testdomextaiwcriteria.txt" ); 
_LIT( KtestdomextaiwcriteriaLogFileWithTitle, "testdomextaiwcriteria_[%S].txt" );

/**
*  Ctestdomextaiwcriteria test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestDomExtAiwCriteria ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestDomExtAiwCriteria* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestDomExtAiwCriteria();

public: // Functions from base classes

    /**
    * From CScriptBase Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
    * C++ default constructor.
    */
    CTestDomExtAiwCriteria( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

private: // [TestMethods]
    
    /**
    * TestTAiwCADBAssignDataTypeFromBufferL test AssignDataTypeFromBuffer
    * of TAiwContactAssignDataBase in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCADBAssignDataTypeFromBuffer( CStifItemParser& aItem );

    /**
    * TestTAiwCADBTAiwContactAssignDataBaseL test TAiwContactAssignDataBase
    * of TAiwContactAssignDataBase in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCADBTAiwContactAssignDataBaseL( CStifItemParser& aItem );

    /**
    * TestTAiwCADBTAiwContactAssignDataBaseWithDataTypeL test
    *  TAiwContactAssignDataBase(which Owns Parameter)
    * of TAiwContactAssignDataBase in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCADBTAiwContactAssignDataBaseWithDataTypeL(
            CStifItemParser& aItem );
    
    /**
    * TestTAiwSCADV1TAiwSingleContactAssignDataV1L test TAiwSingleContactAssignDataV1
    * of TAiwSingleContactAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSCADV1TAiwSingleContactAssignDataV1L(
            CStifItemParser& aItem );
    
    /**
    * TestTAiwSCADV1SetFlagsL test SetFlags
    * of TAiwSingleContactAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSCADV1SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSCADV1SetEditorHelpContextL test SetEditorHelpContext
    * of TAiwSingleContactAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSCADV1SetEditorHelpContext( CStifItemParser& aItem );
    
    /**
    * TestTAiwSCADV1FlagsL test Flags
    * of TAiwSingleContactAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSCADV1Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSCADV1EditorHelpContextL test EditorHelpContext
    * of TAiwSingleContactAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSCADV1EditorHelpContext( CStifItemParser& aItem );
    
    /**
    * TestTAiwMCADV1TAiwMultipleContactAssignDataV1L test TAiwMultipleContactAssignDataV1
    * of TAiwMultipleContactAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMCADV1TAiwMultipleContactAssignDataV1L( CStifItemParser& aItem );
    
    /**
    * TestTAiwSCADV1SetFlagsL test SetFlags
    * of TAiwMultipleContactAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMCADV1SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSCADV1FlagsL test Flags
    * of TAiwMultipleContactAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMCADV1Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwCAADV1TAiwContactAttributeAssignDataV1L test TAiwContactAttributeAssignDataV1
    * of TAiwContactAttributeAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCAADV1TAiwContactAttributeAssignDataV1L(
            CStifItemParser& aItem );
    
    /**
    * TestTAiwCAADV1SetFlagsL test SetFlags
    * of TAiwContactAttributeAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCAADV1SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwCAADV1SetAttributeRemoveL test SetAttributeRemove
    * of TAiwContactAttributeAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCAADV1SetAttributeRemove( CStifItemParser& aItem );
    
    /**
    * TestTAiwCAADV1FlagsL test Flags
    * of TAiwContactAttributeAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCAADV1Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwCAADV1RemoveAttributeL test RemoveAttribute
    * of TAiwContactAttributeAssignDataV1 in AiwContactAssignDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCAADV1RemoveAttribute( CStifItemParser& aItem );
    
    /**
    * TestTAiwCSDBSelectionDataTypeFromBufferL test SelectionDataTypeFromBuffer
    * of TAiwContactSelectionDataBase in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCSDBSelectionDataTypeFromBuffer( CStifItemParser& aItem );
    
    /**
    * TestTAiwCSDBTAiwContactSelectionDataBaseL test TAiwContactSelectionDataBase
    * of TAiwContactSelectionDataBase in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCSDBTAiwContactSelectionDataBaseL( CStifItemParser& aItem );
    
    /**
    * TestTAiwCSDBTAiwContactSelectionDataBaseWithDataTypeL test 
    * TAiwContactSelectionDataBase(which Owns Parameter)
    * of TAiwContactSelectionDataBase in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwCSDBTAiwContactSelectionDataBaseWithDataTypeL(
            CStifItemParser& aItem );
    
    /**
    * TestTAiwSESDV1TAiwSingleEntrySelectionDataV1L test TAiwSingleEntrySelectionDataV1
    * of TAiwSingleEntrySelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSESDV1TAiwSingleEntrySelectionDataV1L(
            CStifItemParser& aItem );
    
    /**
    * TestTAiwSESDV1SetFlagsL test SetFlags
    * of TAiwSingleEntrySelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSESDV1SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSESDV1FlagsL test Flags
    * of TAiwSingleEntrySelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSESDV1Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSESDV2TAiwSingleEntrySelectionDataV2L test TAiwSingleEntrySelectionDataV2
    * of TAiwSingleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSESDV2TAiwSingleEntrySelectionDataV2L( CStifItemParser& aItem );
    
    /**
    * TestTAiwSESDV2SetFlags test SetFlags
    * of TAiwSingleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSESDV2SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSESDV2SetFetchFilterL test SetFetchFilter
    * of TAiwSingleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSESDV2SetFetchFilterL( CStifItemParser& aItem );

    /**
    * TestTAiwSESDV2Flags test Flags
    * of TAiwSingleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSESDV2Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSESDV2FetchFilter test FetchFilter
    * of TAiwSingleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSESDV2FetchFilter( CStifItemParser& aItem );
    
    /**
    * TestTAiwMESDV1TAiwMultipleEntrySelectionDataV1L test TAiwMultipleEntrySelectionDataV1
    * of TAiwMultipleEntrySelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMESDV1TAiwMultipleEntrySelectionDataV1L(
            CStifItemParser& aItem );
    
    /**
    * TestTAiwMESDV1SetFlags test SetFlags
    * of TAiwMultipleEntrySelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMESDV1SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwMESDV1Flags test Flags
    * of TAiwMultipleEntrySelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMESDV1Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwMESDV2TAiwMultipleEntrySelectionDataV2L test TAiwMultipleEntrySelectionDataV2
    * of TAiwMultipleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMESDV2TAiwMultipleEntrySelectionDataV2L( CStifItemParser& aItem );
    
    /**
    * TestTAiwMESDV2SetFlags test SetFlags
    * of TAiwMultipleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMESDV2SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwMESDV2SetFetchFilterL test SetFetchFilter
    * of TAiwMultipleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMESDV2SetFetchFilterL( CStifItemParser& aItem );
    
    /**
    * TestTAiwMESDV2Flags test Flags
    * of TAiwMultipleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMESDV2Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwMESDV2FetchFilter test FetchFilter
    * of TAiwMultipleEntrySelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMESDV2FetchFilter( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV1TAiwSingleItemSelectionDataV1L test TAiwSingleItemSelectionDataV1
    * of TAiwSingleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV1TAiwSingleItemSelectionDataV1L( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV1SetFlags test SetFlags
    * of TAiwSingleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV1SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV1SetAddressSelectType test SetAddressSelectType
    * of TAiwSingleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV1SetAddressSelectType( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV1SetDefaultPrioritiesL test SetDefaultPriorities
    * of TAiwSingleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV1SetDefaultPrioritiesL( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV1Flags test Flags
    * of TAiwSingleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV1Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV1AddressSelectType test AddressSelectType
    * of TAiwSingleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV1AddressSelectType( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV1DefaultPriorities test DefaultPriorities
    * of TAiwSingleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV1DefaultPriorities( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV2TAiwSingleItemSelectionDataV2L test TAiwSingleItemSelectionDataV2
    * of TAiwSingleItemSelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV2TAiwSingleItemSelectionDataV2L( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV2SetFlags test SetFlags
    * of TAiwSingleItemSelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV2SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV2SetAddressSelectResourceId test SetAddressSelectResourceId
    * of TAiwSingleItemSelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV2SetAddressSelectResourceId( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV2SetDefaultPrioritiesL test SetDefaultPriorities
    * of TAiwSingleItemSelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV2SetDefaultPrioritiesL( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV2Flags test Flags
    * of TAiwSingleItemSelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV2Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV2AddressSelectResourceId test AddressSelectResourceId
    * of TAiwSingleItemSelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV2AddressSelectResourceId( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV2DefaultPriorities test DefaultPriorities
    * of TAiwSingleItemSelectionDataV2 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV2DefaultPriorities( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3TAiwSingleItemSelectionDataV3L test TAiwSingleItemSelectionDataV3
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3TAiwSingleItemSelectionDataV3L( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3SetFlags test SetFlags
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3SetAddressSelectType test SetAddressSelectType
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3SetAddressSelectType( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3SetDefaultPrioritiesL test SetDefaultPriorities
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3SetDefaultPrioritiesL( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3SetFetchFilterL test SetFetchFilter
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3SetFetchFilterL( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3Flags test Flags
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3AddressSelectType test AddressSelectType
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3AddressSelectType( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3DefaultPriorities test DefaultPriorities
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3DefaultPriorities( CStifItemParser& aItem );
    
    /**
    * TestTAiwSISDV3FetchFilter test FetchFilter
    * of TAiwSingleItemSelectionDataV3 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwSISDV3FetchFilter( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1TAiwMultipleItemSelectionDataV1L test TAiwMultipleItemSelectionDataV1
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1TAiwMultipleItemSelectionDataV1L( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1SetFlags test SetFlags
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1SetFlags( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1SetAddressSelectType test SetAddressSelectType
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1SetAddressSelectType( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1SetDefaultPrioritiesL test SetDefaultPriorities
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1SetDefaultPrioritiesL( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1SetFetchFilterL test SetFetchFilter
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1SetFetchFilterL( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1Flags test Flags
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1Flags( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1AddressSelectType test AddressSelectType
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1AddressSelectType( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1DefaultPriorities test DefaultPriorities
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1DefaultPriorities( CStifItemParser& aItem );
    
    /**
    * TestTAiwMISDV1FetchFilter test FetchFilter
    * of TAiwMultipleItemSelectionDataV1 in AiwContactSelectionDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwMISDV1FetchFilter( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1TAiwDialDataV1L test TAiwDialDataV1
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1TAiwDialDataV1L( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1Reset test Reset
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1Reset( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetTelephoneNumber test SetTelephoneNumber
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetTelephoneNumber( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetCallType test SetCallType
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetCallType( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetName test SetName
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetName( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetNumberType test SetNumberType
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetNumberType( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetContactId test SetContactId
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetContactId( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetWindowGroup test SetWindowGroup
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetWindowGroup( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetShowNumber test SetShowNumber
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetShowNumber( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetRedial test SetRedial
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetRedial( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetAllowMatch test SetAllowMatch
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetAllowMatch( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetEndOtherCalls test SetEndOtherCalls
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetEndOtherCalls( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetEmergency test SetEmergency
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetEmergency( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetSubAddress test SetSubAddress
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetSubAddress( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetSATCall test SetSATCall
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetSATCall( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetBearer test SetBearer
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetBearer( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetRemoveInvalidChars test SetRemoveInvalidChars
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetRemoveInvalidChars( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SetContactItemField test SetContactItemField
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SetContactItemField( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1TelephoneNumber test TelephoneNumber
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1TelephoneNumber( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1CallType test CallType
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1CallType( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1Name test Name
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1Name( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1NumberType test NumberType
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1NumberType( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1ContactId test ContactId
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1ContactId( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1WindowGroupId test WindowGroupId
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1WindowGroupId( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1Redial test Redial
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1Redial( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1ShowNumber test ShowNumber
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1ShowNumber( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1AllowMatch test AllowMatch
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1AllowMatch( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1EndOtherCalls test EndOtherCalls
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1EndOtherCalls( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1Emergency test Emergency
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1Emergency( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SubAddress test SubAddress
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SubAddress( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1SATCall test SATCall
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1SATCall( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1Bearer test Bearer
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1Bearer( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1RemoveInvalidChars test RemoveInvalidChars
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1RemoveInvalidChars( CStifItemParser& aItem );
    
    /**
    * TestTAiwDDV1ContactItemField test ContactItemField
    * of TAiwDialDataV1 in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwDDV1ContactItemField( CStifItemParser& aItem );
    
    /**
    * TestTAiwPPDTAiwPocParameterDataL test TAiwPocParameterData
    * of TAiwPocParameterData in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwPPDTAiwPocParameterDataL( CStifItemParser& aItem );
    
    /**
    * TestTAiwPPDVersion test Version
    * of TAiwPocParameterData in AiwDialDataTypes.h.
    * @since S60 5.0
    * @param aItem is not used.
    * @return Symbian OS error code.
    */
    virtual TInt TestTAiwPPDVersion( CStifItemParser& aItem );
    

    private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    
    };

#endif      // C_TESTDOMEXTAIWCRITERIA_H

// End of File
