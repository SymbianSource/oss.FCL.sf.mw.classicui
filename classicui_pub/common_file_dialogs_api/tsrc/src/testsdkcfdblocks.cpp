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
* Description:  Test Common File Dialogs
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkcfd.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKCFD::Delete() 
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 

        // Test CAknMemorySelectionDialog.h
        ENTRY( "TestMSDNewL", CTestSDKCFD::TestMSDNewL ), 
        ENTRY( "TestMSDNewWithResourceL", CTestSDKCFD::TestMSDNewWithResourceL ),
        ENTRY( "TestMSDNewWithMediaL", CTestSDKCFD::TestMSDNewWithMediaL ),
        ENTRY( "TestMSDSetTitleL", CTestSDKCFD::TestMSDSetTitleL ),
        ENTRY( "TestMSDSetLeftSoftkeyL", CTestSDKCFD::TestMSDSetLeftSoftkeyL ),
        ENTRY( "TestMSDSetRightSoftkeyL", CTestSDKCFD::TestMSDSetRightSoftkeyL ),
        ENTRY( "TestMSDSetObserverL", CTestSDKCFD::TestMSDSetObserverL ),
        ENTRY( "TestMSDExecuteL", CTestSDKCFD::TestMSDExecuteL ),
        ENTRY( "TestMSDExecuteLDefaultFolderL", CTestSDKCFD::TestMSDExecuteLDefaultFolderL ),
        ENTRY( "TestMSDRunDlgLD", CTestSDKCFD::TestMSDRunDlgLD ),
        ENTRY( "TestMSDRunDlgLDTitleL", CTestSDKCFD::TestMSDRunDlgLDTitleL ),
        ENTRY( "TestMSDRunDlgLDResourceL", CTestSDKCFD::TestMSDRunDlgLDResourceL ),
        ENTRY( "TestMSDGetItemL", CTestSDKCFD::TestMSDGetItemL ), 
        ENTRY( "TestMSDGetMemoriesL", CTestSDKCFD::TestMSDGetMemoriesL ), 
        
        
        // Test AknCommonDialogs.h
        ENTRY( "TestCDRunSelectDlgLD", CTestSDKCFD::TestCDRunSelectDlgLD ),
        ENTRY( "TestCDRunSelectDlgLDFilter", CTestSDKCFD::TestCDRunSelectDlgLDFilterL ),
        ENTRY( "TestCDRunSelectDlgLDTitle", CTestSDKCFD::TestCDRunSelectDlgLDTitleL ),
        ENTRY( "TestCDRunSelectDlgLDFileId", CTestSDKCFD::TestCDRunSelectDlgLDFileIdL ),
        ENTRY( "TestCDRunMoveDlgLD", CTestSDKCFD::TestCDRunMoveDlgLD ),
        ENTRY( "TestCDRunMoveDlgLDFilter", CTestSDKCFD::TestCDRunMoveDlgLDFilterL ),
        ENTRY( "TestCDRunMoveDlgLDTitle", CTestSDKCFD::TestCDRunMoveDlgLDTitleL ),
        ENTRY( "TestCDRunMoveDlgLDFileId", CTestSDKCFD::TestCDRunMoveDlgLDFileIdL ),
        ENTRY( "TestCDRunSaveDlgLD", CTestSDKCFD::TestCDRunSaveDlgLD ),
        ENTRY( "TestCDRunSaveDlgLDFilter", CTestSDKCFD::TestCDRunSaveDlgLDFilterL ),
        ENTRY( "TestCDRunSaveDlgLDTitle", CTestSDKCFD::TestCDRunSaveDlgLDTitleL ),
        ENTRY( "TestCDRunSaveDlgLDFileId", CTestSDKCFD::TestCDRunSaveDlgLDFileIdL ),
        ENTRY( "TestCDRunSaveDlgLDIdTitle", CTestSDKCFD::TestCDRunSaveDlgLDIdTitleL ),
        ENTRY( "TestCDRunSaveDlgNoDirectorySelectionLD", CTestSDKCFD::TestCDRunSaveDlgNoDirectorySelectionLD ),
        ENTRY( "TestCDRunSaveDlgNoDirectorySelectionLDTitle", CTestSDKCFD::TestCDRunSaveDlgNoDirectorySelectionLDTitleL ),
        ENTRY( "TestCDRunCopyDlgLD", CTestSDKCFD::TestCDRunCopyDlgLD ),
        ENTRY( "TestCDRunCopyDlgLDFilter", CTestSDKCFD::TestCDRunCopyDlgLDFilterL ),
        ENTRY( "TestCDRunCopyDlgLDFileId", CTestSDKCFD::TestCDRunCopyDlgLDFileIdL ),
        ENTRY( "TestCDRunSelectDlgLDFolder", CTestSDKCFD::TestCDRunSelectDlgLDFolderL ),
        ENTRY( "TestCDRunSelectDlgLDFolderFilter", CTestSDKCFD::TestCDRunSelectDlgLDFolderFilterL ),
        ENTRY( "TestCDRunSelectDlgLDFolderTitle", CTestSDKCFD::TestCDRunSelectDlgLDFolderTitleL ),
        ENTRY( "TestCDRunSelectDlgLDFolderFileID", CTestSDKCFD::TestCDRunSelectDlgLDFolderFileIDL ),
        ENTRY( "TestCDRunSelectDlgLDFolderTitleFilter", CTestSDKCFD::TestCDRunSelectDlgLDFolderTitleFilterL ),
        ENTRY( "TestCDRunSaveDlgLDFolderTitleFilter", CTestSDKCFD::TestCDRunSaveDlgLDFolderTitleFilterL ),
        ENTRY( "TestCDRunFolderSelectDlgLD", CTestSDKCFD::TestCDRunFolderSelectDlgLD ),
        
        // Test AknCommonDialogsDynMem.h
        ENTRY( "TestCDDMRunSelectDlgLD", CTestSDKCFD::TestCDDMRunSelectDlgLD ),
        ENTRY( "TestCDDMRunSelectDlgLDFilter", CTestSDKCFD::TestCDDMRunSelectDlgLDFilterL ),
        ENTRY( "TestCDDMRunSelectDlgLDTitle", CTestSDKCFD::TestCDDMRunSelectDlgLDTitleL ),
        ENTRY( "TestCDDMRunSelectDlgLDFileId", CTestSDKCFD::TestCDDMRunSelectDlgLDFileIdL ),
        ENTRY( "TestCDDMRunMoveDlgLD", CTestSDKCFD::TestCDDMRunMoveDlgLD ),
        ENTRY( "TestCDDMRunMoveDlgLDFilter", CTestSDKCFD::TestCDDMRunMoveDlgLDFilterL ),
        ENTRY( "TestCDDMRunMoveDlgLDTitle", CTestSDKCFD::TestCDDMRunMoveDlgLDTitleL ),
        ENTRY( "TestCDDMRunMoveDlgLDFileId", CTestSDKCFD::TestCDDMRunMoveDlgLDFileIdL ),
        ENTRY( "TestCDDMRunSaveDlgLD", CTestSDKCFD::TestCDDMRunSaveDlgLD ),
        ENTRY( "TestCDDMRunSaveDlgLDFilter", CTestSDKCFD::TestCDDMRunSaveDlgLDFilterL ),
        ENTRY( "TestCDDMRunSaveDlgLDTitle", CTestSDKCFD::TestCDDMRunSaveDlgLDTitleL ),
        ENTRY( "TestCDDMRunSaveDlgLDFileId", CTestSDKCFD::TestCDDMRunSaveDlgLDFileIdL ),
        ENTRY( "TestCDDMRunSaveDlgLDIdTitle", CTestSDKCFD::TestCDDMRunSaveDlgLDIdTitleL ),
        ENTRY( "TestCDDMRunSaveDlgNoDirectorySelectionLD", CTestSDKCFD::TestCDDMRunSaveDlgNoDirectorySelectionLD ),
        ENTRY( "TestCDDMRunSaveDlgNoDirectorySelectionLDTitle", CTestSDKCFD::TestCDDMRunSaveDlgNoDirectorySelectionLDTitleL ),
        ENTRY( "TestCDDMRunCopyDlgLD", CTestSDKCFD::TestCDDMRunCopyDlgLD ),
        ENTRY( "TestCDDMRunCopyDlgLDFilter", CTestSDKCFD::TestCDDMRunCopyDlgLDFilterL ),
        ENTRY( "TestCDDMRunCopyDlgLDFileId", CTestSDKCFD::TestCDDMRunCopyDlgLDFileIdL ),
        ENTRY( "TestCDDMRunSelectDlgLDFolder", CTestSDKCFD::TestCDDMRunSelectDlgLDFolderL ),
        ENTRY( "TestCDDMRunSelectDlgLDFolderFilter", CTestSDKCFD::TestCDDMRunSelectDlgLDFolderFilterL ),
        ENTRY( "TestCDDMRunSelectDlgLDFolderTitle", CTestSDKCFD::TestCDDMRunSelectDlgLDFolderTitleL ),
        ENTRY( "TestCDDMRunSelectDlgLDFolderFileID", CTestSDKCFD::TestCDDMRunSelectDlgLDFolderFileIDL ),
        ENTRY( "TestCDDMRunSelectDlgLDFolderTitleFilter", CTestSDKCFD::TestCDDMRunSelectDlgLDFolderTitleFilterL ),
        ENTRY( "TestCDDMRunSaveDlgLDFolderTitleFilter", CTestSDKCFD::TestCDDMRunSaveDlgLDFolderTitleFilterL ),
        ENTRY( "TestCDDMRunFolderSelectDlgLD", CTestSDKCFD::TestCDDMRunFolderSelectDlgLD ),

        // Test CAknFileSelectionDialog.h
        ENTRY( "TestFSDNewL", CTestSDKCFD::TestFSDNewL ),
        ENTRY( "TestFSDNewLWithResL", CTestSDKCFD::TestFSDNewLWithResL ),
        ENTRY( "TestFSDExecuteL", CTestSDKCFD::TestFSDExecuteL ),
        ENTRY( "TestFSDRunDlgLD", CTestSDKCFD::TestFSDRunDlgLD ),
        ENTRY( "TestFSDRunDlgLDWithTitleLD", CTestSDKCFD::TestFSDRunDlgLDWithTitleLD ),
        ENTRY( "TestFSDRunDlgLDWithResLD", CTestSDKCFD::TestFSDRunDlgLDWithResLD ),
        ENTRY( "TestFSDDelete", CTestSDKCFD::TestFSDDelete ),
        ENTRY( "TestFSDSetDefaultFolderL", CTestSDKCFD::TestFSDSetDefaultFolderL ),
        ENTRY( "TestFSDSetTitleL", CTestSDKCFD::TestFSDSetTitleL ),
        ENTRY( "TestFSDSetLeftSoftkeyFileL", CTestSDKCFD::TestFSDSetLeftSoftkeyFileL ),
        ENTRY( "TestFSDSetLeftSoftkeyFolderL", CTestSDKCFD::TestFSDSetLeftSoftkeyFolderL ),
        ENTRY( "TestFSDSetRightSoftkeyRootFolderL", CTestSDKCFD::TestFSDSetRightSoftkeyRootFolderL ),
        ENTRY( "TestFSDSetRightSoftkeySubfolderL", CTestSDKCFD::TestFSDSetRightSoftkeySubfolderL ),
        ENTRY( "TestFSDSetObserverL", CTestSDKCFD::TestFSDSetObserverL ),
        ENTRY( "TestFSDAddFilterL", CTestSDKCFD::TestFSDAddFilterL ),
        
        // Test CAknFileNamePromptDialog.h
        ENTRY( "TestFNPDNewL", CTestSDKCFD::TestFNPDNewL ),
        ENTRY( "TestFNPDNewLWithResL", CTestSDKCFD::TestFNPDNewLWithResL ),
        ENTRY( "TestFNPDSetPathL", CTestSDKCFD::TestFNPDSetPathL ),
        ENTRY( "TestFNPDExecuteL", CTestSDKCFD::TestFNPDExecuteL ),
        ENTRY( "TestFNPDRunDlgLD", CTestSDKCFD::TestFNPDRunDlgLD ),
        ENTRY( "TestFNPDRunDlgLDWithTitleLD", CTestSDKCFD::TestFNPDRunDlgLDWithTitleLD ),
        ENTRY( "TestFNPDRunDlgLDWithResLD", CTestSDKCFD::TestFNPDRunDlgLDWithResLD ),
        ENTRY( "TestFNPDDeleteL", CTestSDKCFD::TestFNPDDeleteL ),
        ENTRY( "TestFNPDSetObserverL", CTestSDKCFD::TestFNPDSetObserverL ),
        ENTRY( "TestFNPDSetTitleL", CTestSDKCFD::TestFNPDSetTitleL ),
        ENTRY( "TestFNPDSetLeftSoftkeyL", CTestSDKCFD::TestFNPDSetLeftSoftkeyL ),
        ENTRY( "TestFNPDSetRightSoftkeyL", CTestSDKCFD::TestFNPDSetRightSoftkeyL ),
        ENTRY( "TestFNPDRenameL", CTestSDKCFD::TestFNPDRenameL ),
        
        // Test CAknMemorySelectionSettingPage
        ENTRY( "TestSettingPageNewLNoParaL", CTestSDKCFD::TestSettingPageNewLNoParaL ),
        ENTRY( "TestSettingPageNewL", CTestSDKCFD::TestSettingPageNewL ),
        ENTRY( "TestSettingPageExecuteLOnlyMemoryTypeL", CTestSDKCFD::TestSettingPageExecuteLOnlyMemoryTypeL ),
        ENTRY( "TestSettingPageDeconstructorL", CTestSDKCFD::TestSettingPageDeconstructorL ),
        ENTRY( "TestSettingPageRunDlgLDTwoParaL", CTestSDKCFD::TestSettingPageRunDlgLDTwoParaL ),
        ENTRY( "TestSettingPageRunDlgLDThreeParaL", CTestSDKCFD::TestSettingPageRunDlgLDThreeParaL ),
        ENTRY( "TestSettingPageRunDlgLDFiveParaL", CTestSDKCFD::TestSettingPageRunDlgLDFiveParaL ),

        ENTRY( "TestSettingItemConstructorL", CTestSDKCFD::TestSettingItemConstructorL ),
        ENTRY( "TestSettingItemDeconstructorL", CTestSDKCFD::TestSettingItemDeconstructorL ),
        ENTRY( "TestSettingItemCompleteConstructionL", CTestSDKCFD::TestSettingItemCompleteConstructionL ),
        ENTRY( "TestSettingItemEditItemL", CTestSDKCFD::TestSettingItemEditItemL ),
        ENTRY( "TestSettingItemLoadL", CTestSDKCFD::TestSettingItemLoadL ),
        ENTRY( "TestSettingItemStoreL", CTestSDKCFD::TestSettingItemStoreL ),
        ENTRY( "TestSettingItemSettingTextL", CTestSDKCFD::TestSettingItemSettingTextL ),

        // Test CAknMemorySelectionSettingItemMultiDrive
        ENTRY( "TestSettingItemMultiConstructorL", CTestSDKCFD::TestSettingItemMultiConstructorL ),
        ENTRY( "TestSettingItemMultiDeconstructorL", CTestSDKCFD::TestSettingItemMultiDeconstructorL ),
        ENTRY( "TestSettingItemMultiCompleteConstructionL", CTestSDKCFD::TestSettingItemMultiCompleteConstructionL ),
        ENTRY( "TestSettingItemMultiEditItemL", CTestSDKCFD::TestSettingItemMultiEditItemL ),
        ENTRY( "TestSettingItemMultiLoadL", CTestSDKCFD::TestSettingItemMultiLoadL ),
        ENTRY( "TestSettingItemMultiStoreL", CTestSDKCFD::TestSettingItemMultiStoreL ),
        ENTRY( "TestSettingItemMultiSettingTextL", CTestSDKCFD::TestSettingItemMultiSettingTextL ),

        // Test CAknMemorySelectionDialogMultiDrive
        ENTRY( "TestMSDMDNewL", CTestSDKCFD::TestMSDMDNewL ),
        ENTRY( "TestMSDMDNewWithResourceL", CTestSDKCFD::TestMSDMDNewWithResourceL ),
        ENTRY( "TestMSDMDNewWithMediaL", CTestSDKCFD::TestMSDMDNewWithMediaL ),
        ENTRY( "TestMSDMDSetTitleL", CTestSDKCFD::TestMSDMDSetTitleL ),
        ENTRY( "TestMSDMDSetLeftSoftkeyL", CTestSDKCFD::TestMSDMDSetLeftSoftkeyL ),
        ENTRY( "TestMSDMDSetRightSoftkeyL", CTestSDKCFD::TestMSDMDSetRightSoftkeyL ),
        ENTRY( "TestMSDMDExecuteL", CTestSDKCFD::TestMSDMDExecuteL ),
        ENTRY( "TestMSDMDExecuteLDefaultFolderL", CTestSDKCFD::TestMSDMDExecuteLDefaultFolderL ),
        ENTRY( "TestMSDMDRunDlgLD", CTestSDKCFD::TestMSDMDRunDlgLD ),
        ENTRY( "TestMSDMDRunDlgLDTitleL", CTestSDKCFD::TestMSDMDRunDlgLDTitleL ),
        ENTRY( "TestMSDMDRunDlgLDResourceL", CTestSDKCFD::TestMSDMDRunDlgLDResourceL ),
        ENTRY( "TestMSDMDGetItemL", CTestSDKCFD::TestMSDMDGetItemL ),
        ENTRY( "TestMSDMDAddDrivePathsL", CTestSDKCFD::TestMSDMDAddDrivePathsL ),
        ENTRY( "TestMSDMDFindIndexByDriveL", CTestSDKCFD::TestMSDMDFindIndexByDriveL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File]
