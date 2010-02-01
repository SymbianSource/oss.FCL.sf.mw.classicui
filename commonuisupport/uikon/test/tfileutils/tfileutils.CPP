// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// Tests EikFileUtils APIs.
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#include <eikfutil.h>
#include <ecom/ecom.h>

#include "tfileutils.h"
#include <tfileutils.rsg>


_LIT(KTFileUtilesResourceFilePath, "z:\\system\\test\\fileutils\\tfileutils.rsc");

// globals 
TBufC<128> KOriginalFileName = _L("c:\\home\\letters\\azxcvmbcdef");

//
// class CTFileUtilsAppUi
//
CTFileUtilsAppUi::CTFileUtilsAppUi(CTmsTestStep* aStep) :
	CTestAppUi(aStep, KTFileUtilesResourceFilePath)
	{
	}

void CTFileUtilsAppUi::ConstructL()
    {
    CTestAppUi::ConstructL();
	
	AutoTestManager().StartAutoTest();
    }

CTFileUtilsAppUi::~CTFileUtilsAppUi()
    {
    }

/**
   The method is an override from CTestAppUi. The method initiates tests on
   EikFileUtils APIs.
 */
void CTFileUtilsAppUi::RunTestStepL(TInt aNumStep)
 	{
	User::After(TTimeIntervalMicroSeconds32(500000));
 	switch(aNumStep)
 		{
 	case 1:
 		SetTestStepID(_L("UIF-fileutils-TestFileOperations"));
		TestFileOperations();
		RecordTestResultL();
		break;
 	case 2:
 		SetTestStepID(_L("UIF-fileutils-TestFileOperations2"));
		TestFileOperations2();
		RecordTestResultL();
		break;
	case 3:
		SetTestStepID(_L("UIF-fileutils-TestFileOperations3"));
		TestFileOperations3();
		RecordTestResultL();
		break;
	case 4:
		SetTestStepID(_L("UIF-fileutils-TestFileOperations4"));
		TestFileOperations4();
		RecordTestResultL();
		break;
	case 5:
		SetTestStepID(_L("UIF-fileutils-TestAbbreviateFileName"));
		TestAbbreviateFileName();
		RecordTestResultL();
		break;
	case 6:
		SetTestStepID(_L("UIF-fileutils-TestUidTypeMatches"));
		TestUidTypeMatches();
		RecordTestResultL();
		break;
	case 7:
		SetTestStepID(_L("UIF-fileutils-TestValidFolderName"));
		TestValidFolderName();
		RecordTestResultL();
		break;
	case 8:
		{
		SetTestStepID(_L("UIF-fileutils-TestDiskListL"));
		TRAPD(err, TestDiskListL());
		TEST(err == KErrNone);
		RecordTestResultL();
		break;
		}
	case 9:
		{
		SetTestStepID(_L("UIF-fileutils-TestSortByTableL"));
		TRAPD(err, TestSortByTableL());
		TEST(err == KErrNone);
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
		}
	case 10:
 		INFO_PRINTF1(_L("Tests completed.\n"));
 		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;	

	default:
 		break;
 		}
 	}


/**
   This method creates & sets the application's user interface object.
 */
void CFileUtilsStep::ConstructAppL(CEikonEnv* aEikEnv)
     { // runs inside a TRAP harness
	aEikEnv->ConstructL();
 	CTFileUtilsAppUi* appUi=new(ELeave) CTFileUtilsAppUi(this);

	CleanupStack::PushL(appUi);
 	aEikEnv->SetAppUi(appUi);
	appUi->ConstructL();
	CleanupStack::Pop(appUi);
	// goes out of scope when function leaves and private members are destroyed. App Architecture handles 
	// CEikAppUI destruction
     }


CFileUtilsStep::~CFileUtilsStep()
	{
	}

CFileUtilsStep::CFileUtilsStep()
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KFileUtilsStep);
	}


/**
   The method creates & sets the test step's user interface object and
   launches the test step.
 */
TVerdict CFileUtilsStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
	PreallocateHALBuffer();

	__UHEAP_MARK;
 
 	CEikonEnv* eikEnv=new CEikonEnv;
 	if (eikEnv==NULL)
		{
		INFO_PRINTF1(_L("Failed to create Eikon Environment due to lack of Memory"));
		SetTestStepResult(EFail);
 		return TestStepResult();
		}
 	TRAPD(err,ConstructAppL(eikEnv));
 	if (err!=KErrNone)
		{
 		SetTestStepResult(EFail);
		delete eikEnv;
		INFO_PRINTF2(_L("Failed to construct Eikon Environment, error %d"), err);
		}
 	else
 		eikEnv->ExecuteD();

	REComSession::FinalClose();	
	 
 	__UHEAP_MARKEND;
 
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
    }

/**
   @SYMTestCaseID UIF-fileutils-TestFileOperations
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test folder information,file copy, renaming & deletion APIs of
   EikFileUtils.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests the following APIs:\n
   1.EikFileUtils::IsFolder() : IsFolder() API is tested to verify whether 
   folder path exists by passing invalid & valid folder paths. It also tests the
   API by passing valid path including filename of a file.\n
   2.EikFileUtils::PathExists() : PathExists() API is tested to verify whether
   the specifed path exists by passing valid path including filename.\n
   3.EikFileUtils::FolderExists() : FolderExists() API is tested to verify
   whether folder exists by passing a valid folder path.\n
   4.EikFileUtils::CheckFolder() : CheckFolder() API is tested by passing a
   non-existent folder path.\n
   5.EikFileUtils::CheckWhetherFullNameRefersToFolder() : 
   CheckWhetherFullNameRefersToFolder() API is tested to verify whether the
   fullname passed refers to a folder. This is done by passing a fullname 
   with filename and by passing fullname without a filename.\n
   6.EikFileUtils::CopyFile() : CopyFile() API is tested to verify copying of
   an existing & non-existent file.\n
   7.EikFileUtils::RenameFile() : RenameFile() API is tested to verify renaming
   of a file.\n
   8.EikFileUtils::DeleteFile() : DeleteFile() API is tested to verify deletion
   of a valid and invalid file.\n
   
   @SYMTestExpectedResults The test validates results against expected values.
   
 */
void CTFileUtilsAppUi::TestFileOperations()
	{
	_LIT(KSourceFileName, "z:\\uiktest\\uiktest_t_fileutils.script");
	_LIT(KSourceFileNameNotExist, "z:\\system\\test\\uiktest\\notexist.txt");
	_LIT(KDestDir, "c:\\uiktest\\");

	RFs	fs;
	TInt theRes = fs.Connect();
	TEST(theRes == KErrNone);
	if(theRes != KErrNone)
		{
		return;
		}

	fs.RmDir(KDestDir);

	INFO_PRINTF2(_L("Tests whether \"%S\" is a folder"), &KDestDir);
	TBool theBoolRetVal = EFalse;
	theRes = EikFileUtils::IsFolder(KDestDir, theBoolRetVal);
	TEST(theRes == KErrNotFound && (!theBoolRetVal));
	
	fs.MkDirAll(KDestDir);
	theRes = EikFileUtils::IsFolder(KDestDir, theBoolRetVal);
	//
	TEST(theRes == KErrNone);
	TEST(theBoolRetVal);

	//should be fail as consists filename
	INFO_PRINTF2(_L("Test whether path \"%S\" exist"), &KSourceFileName);
	theBoolRetVal = EikFileUtils::PathExists(KSourceFileName);
	TEST(!theBoolRetVal);
	
	theRes = EikFileUtils::IsFolder(KSourceFileName, theBoolRetVal);
	TEST(theRes == KErrNone);
	TEST(!theBoolRetVal);

	//Tests whether a specified folder exists.
	INFO_PRINTF2(_L("Tests whether a specified folder \"%S\" exist"), &KDestDir);
	theBoolRetVal = EikFileUtils::FolderExists(KDestDir);
	TEST(theBoolRetVal);
	
	//exercising CheckFolder
	//non-existant path
	theRes = EikFileUtils::CheckFolder(_L("c:\\kkkk\\"));
	TEST(theRes);

	theRes = EikFileUtils::CheckFolder(KDestDir);
	TEST(theRes == KErrNone);
		
	INFO_PRINTF2(_L("Passing full path, including filename \"%S\" and check whether full name refers to folder"), &KSourceFileName);
	theRes = EikFileUtils::CheckWhetherFullNameRefersToFolder(KSourceFileName, theBoolRetVal);
	TEST(theRes == (TInt)KErrNone);
	TEST(!theBoolRetVal);
	
	INFO_PRINTF2(_L("Passing full path, excluding filename \"%S\" and check whether full name refers to folder"), &KDestDir);
	theRes = EikFileUtils::CheckWhetherFullNameRefersToFolder(KDestDir, theBoolRetVal);
	TEST(theRes == (TInt)KErrNone);
	TEST(theBoolRetVal);

	_LIT(KDestFileName, "fileutils.txt");
	_LIT(KDestNewFileName, "fileutilsnew.txt");
	
	TFileName	destFileName(KDestDir);
	destFileName += KDestFileName;
	TFileName	destFileNameNew(KDestDir);
	destFileNameNew += KDestNewFileName; 
	
	// When trying to copy an Non-Existant File , the expected Return code is KErrNotFound
	INFO_PRINTF1(_L("Try to copy non-existent file"));
	theRes = EikFileUtils::CopyFile(KSourceFileNameNotExist, KDestFileName, CFileMan::EOverWrite);
	TEST(theRes == KErrNotFound);

	INFO_PRINTF3(_L("Try to copy a file from %S to %S "), &KSourceFileName, &destFileName);
	theRes = EikFileUtils::CopyFile(KSourceFileName, destFileName, CFileMan::EOverWrite);
	TEST(theRes == KErrNone);	

	// When the Source and Destination Filenames are the same
	INFO_PRINTF2(_L("Try to copy with src and dest filenames being same (\"%S\") with aSwitch = EOverWrite"), &destFileName);
	theRes = EikFileUtils::CopyFile(destFileName, destFileName, CFileMan::EOverWrite);
	TEST(theRes == KErrNone);
	INFO_PRINTF3(_L("Expected Return Code is KErrNone %d obtained return code is %d"),KErrNone,theRes);

	INFO_PRINTF2(_L("Try to copy with src and dest filenames being same (\"%S\") with aSwitch = 0"), &destFileName);
	theRes = EikFileUtils::CopyFile(destFileName, destFileName, 0);
	TEST(theRes == KErrAlreadyExists);
	INFO_PRINTF3(_L("Expected Return Code is KErrAlreadyExists %d obtained return code is %d"),KErrAlreadyExists,theRes);

	INFO_PRINTF3(_L("Rename the file from %S to %S"), &destFileName, &destFileNameNew);
	theRes = EikFileUtils::RenameFile(destFileName, destFileNameNew, CFileMan::EOverWrite);
	TEST(theRes == KErrNone);	

	// Copy usually keeps the same attributes on target, so we need to fix them
	fs.SetAtt(destFileNameNew,0,KEntryAttReadOnly);	
	
	INFO_PRINTF2(_L("Delete the file : \"%S\""), &destFileNameNew);
	theRes = EikFileUtils::DeleteFile(destFileNameNew);
	TEST(theRes == KErrNone);	
	if(theRes != KErrNone)
		{
		INFO_PRINTF2(_L("Error during deleting the file %d"), theRes);
		}
	
	//try to delete twice
	INFO_PRINTF1(_L("Delete the file twice"));
	theRes = EikFileUtils::DeleteFile(destFileNameNew);
	TEST(theRes == KErrNotFound);	

	INFO_PRINTF2(_L("Tests whether a specified folder %S exists"), &KDestDir);
	theBoolRetVal = EikFileUtils::FolderExists(KDestDir);
	TEST(theBoolRetVal);

	fs.RmDir(KDestDir);

	//test has to return false as we have deleted the directory
	theBoolRetVal = EikFileUtils::FolderExists(KDestDir);
	TEST(!theBoolRetVal);
	
	fs.Close();
	}


/**
   @SYMTestCaseID UIF-fileutils-TestAbbreviateFileName
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests EikFileUtils::AbbreviatePath() 
   & EikFileUtils::AbbreviateFileName() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The tests performs the following:\n
   1.EikFileUtils::AbbreviateFileName() : AbbreviateFileName() API is tested to
   display the filename when the space to display the entire filename is
   sufficient and in-sufficient.
   2.EikFileUtils::AbbreviatePath() : AbbreviatePath() API is tested to display
   path when the space to display the entire path is sufficient and
   in-sufficient.
   
   @SYMTestExpectedResults The test validates results against expected values.
   
 */
void CTFileUtilsAppUi::TestAbbreviateFileName()
	{
	//exercising AbbreviateFileName function
	TBuf<256>	buf;
	TBuf<1>	buf1;

	TFileName fileName(KOriginalFileName);
	TFileName fileName1(KOriginalFileName);

	EikFileUtils::AbbreviateFileName(fileName, buf);
	TEST(buf == KOriginalFileName);

	const TInt theLenghtBuffer = 8;
	TBuf<theLenghtBuffer> bufLen8;
	
	EikFileUtils::AbbreviateFileName(fileName, bufLen8);

	TChar ellipsis(0x2026);
	
	buf = KOriginalFileName.Right(theLenghtBuffer);
	buf[0] = (TUint16)ellipsis;
	TEST(buf == bufLen8);

	//exercising AbbreviatePath function
	buf1.Zero();
	buf1.Append(ellipsis);

	const CFont* theFont = CEikonEnv::Static()->LegendFont();
	fileName = KOriginalFileName;
	TInt theMaxWidthInPixels = 0;
	INFO_PRINTF1(_L("exercising AbbreviatePath function"));
	buf = EikFileUtils::AbbreviatePath(fileName, *theFont, theMaxWidthInPixels);
	TEST(buf == buf1);
	
	//--------
	buf.Zero();
	buf.Append(ellipsis);
	fileName = KOriginalFileName.Right(KOriginalFileName.Length() / 2);
	fileName.Insert(0, buf);
	theMaxWidthInPixels = theFont->TextWidthInPixels(fileName);	
	fileName1 = KOriginalFileName;
	buf = EikFileUtils::AbbreviatePath(fileName1, *theFont, theMaxWidthInPixels);
	TEST(buf == fileName);
	
	//--------
	buf = EikFileUtils::AbbreviatePath(fileName1, *theFont, theMaxWidthInPixels + 1);
	TEST(buf == fileName);	
	}


/**
   @SYMTestCaseID UIF-fileutils-TestFileOperations2
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests drive information APIs and Parse() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests the following APIs:
   1.EikFileUtils::RootFolderPath() : RootFolderPath() API is tested to verify
   whether the root folder for the specified drive is returned.\n
   2.EikFileUtils::Parse() : Parse() API is tested to verify whether a specifed
   filename can be parsed. The test is carried out for valid & invalid file
   paths.\n
   3.EikFileUtils::DiskIsReadOnly() : DiskIsReadOnly() API is tested to verify
   whether the specified disk is read only. This is done by specifying the drive
   root folder, drive letter & invalid drives.
   4.EikFileUtils::MostSignificantPartOfFullName() : MostSignificantPartOfFullName()
   API is tested to verify whether it retreives the most significant part of
   specified drive, path and file name.
   5.EikFileUtils::DriveAndPathFromFullName() : DriveAndPathFromFullName()
   API is tested to verify whether it parses the specified full path to obtain 
   the drive and path.
   
   @SYMTestExpectedResults The test validates results against expected values.
   
 */
void CTFileUtilsAppUi::TestFileOperations2()
	{
	TBool theBoolRetVal;
	TBuf<1> buf1 = _L("d");
	_LIT(KRootFolderPath, "d:\\");

	TBuf<256> buf;

	buf = EikFileUtils::RootFolderPath(buf1);
	TEST(buf == KRootFolderPath);
	
	//exercising parse function
	buf.Copy(KOriginalFileName);
	INFO_PRINTF1(_L("Tests whether a specified file name can be parsed"));
	TInt theRes = EikFileUtils::Parse(buf);
	TEST(theRes == KErrNone);
	
	buf.Delete(0, 1);
	theRes = EikFileUtils::Parse(buf);
	TEST(theRes == KErrBadName);

	//exercising 	function TInt DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly);
	buf = _L("c:\\");
	INFO_PRINTF2(_L("Tests whether the specified drive %S is read-only"), &buf);
	theRes = EikFileUtils::DiskIsReadOnly(buf, theBoolRetVal);
	INFO_PRINTF1(_L("Tests whether the specified drive is read-only"));
	TEST(theRes == KErrNone && (!theBoolRetVal));

	buf = _L("z:");
	theRes = EikFileUtils::DiskIsReadOnly(buf, theBoolRetVal);
	TEST(theRes == KErrNone && theBoolRetVal);

	buf = _L("c~\\");
	theRes = EikFileUtils::DiskIsReadOnly(buf, theBoolRetVal);
	TEST(theRes == KErrBadName && theBoolRetVal);

	buf = _L("c");
	theRes = EikFileUtils::DiskIsReadOnly(buf, theBoolRetVal);
	TEST(theRes == KErrBadName);

	//exercising 	function MostSignificantPartOfFullName
	TFileName fileName(KOriginalFileName);

	INFO_PRINTF1(_L("Gets the folder/file name"));
	theRes = EikFileUtils::MostSignificantPartOfFullName(fileName, buf);
	TEST(theRes == KErrNone);
	TEST(buf.Compare(_L("azxcvmbcdef")) == 0);
	
	theRes = fileName.LocateReverseF('\\'); 
	fileName = fileName.Mid(theRes + 1);

	TEST(fileName == buf);
	
	//exercising 	function DriveAndPathFromFullName
	fileName = KOriginalFileName;
	INFO_PRINTF1(_L("Parses the specified full path and file name to obtain the drive and path"));
	fileName = EikFileUtils::DriveAndPathFromFullName(fileName);
	buf = KOriginalFileName;
	theRes = buf.LocateReverseF('\\'); 
	buf = buf.Left(theRes + 1);
	
	TEST(buf == fileName);
	}


/**
   @SYMTestCaseID UIF-fileutils-TestFileOperations4
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests EikFileUtils::FolderNameFromFullName() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests FolderNameFromFullName() API to verify whether
   it retreives folder name from a path and file name. The test is carried out
   against valid & invalid path & filename.
   
   @SYMTestExpectedResults The test validates results against expected values.
   
 */
void CTFileUtilsAppUi::TestFileOperations4()
	{
	TBuf<256>	buf;

	//exercising 	function  FolderNameFromFullName
	buf = KOriginalFileName;

	INFO_PRINTF1(_L("Gets a folder name from a path and file name"));
	TFileName fileName = EikFileUtils::FolderNameFromFullName(buf);
	buf=FolderNameFromFullName(buf);
	TEST(buf == fileName);
	
	buf = _L("c:");
	INFO_PRINTF1(_L("Gets a folder name from an invalid folder name"));
	fileName = EikFileUtils::FolderNameFromFullName(buf);
	buf=FolderNameFromFullName(buf);
	TEST(buf == fileName);
	}


/**
   Auxiliary function for TestCaseID tfileutils-TestFileOperations4
  
   This method splits folder name from a full path.
  
 */
TFileName CTFileUtilsAppUi::FolderNameFromFullName(const TDesC& aFullName)
	{
	//remove drive from path
	TFileName theFileName = aFullName;
	if(theFileName.Match(_L("?:*")) == 0)
		{
		theFileName = theFileName.Mid(2);
		}

	TInt theRes = theFileName.LocateReverseF('\\');
	if(theRes >= 0)//whether the char in the string
		{
		theFileName = theFileName.Left(theRes);
		theRes = theFileName.LocateReverseF('\\');
		if(theRes >= 0)
			{
			theFileName = theFileName.Right(theFileName.Length() - theRes - 1);
			}
		}
	
	if(theFileName.Length() == 0)
		{
		if(aFullName.MatchF(_L("?:\\")) == 0)
			{
			theFileName.Copy(aFullName.Ptr(), 3);
			}
		else if(aFullName.MatchF(_L("?:")) == 0)
			{
			theFileName.Copy(aFullName.Ptr(), 2);
			}
		}

	return theFileName;
	}
	
/**
   @SYMTestCaseID UIF-fileutils-TestFileOperations3
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests removal of system directory "z:\\system".
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method connects to the file server and sets the attributes
   of system directory & files. The test then calls RFs::GetDir() to populate
   the system directory & file list. EikFileUtils::RemoveSystemDirectory() is
   invoked to remove the system directory "z:\\system".
   
   @SYMTestExpectedResults The test validates results by calling CDir::Count() 
   which lists the directory count matching the attributes set.
   
 */
void CTFileUtilsAppUi::TestFileOperations3()
	{
	RFs theFs;

	CDir* theDir = NULL;
	CDir* fileList = NULL;

	theFs.Connect();
	TInt attribs=KEntryAttDir|KEntryAttSystem|KEntryAttMatchExclusive;
	theFs.GetDir(_L("z:\\system"),attribs,ESortNone, fileList, theDir);
	
	TInt theNumber = theDir -> Count();
	TEST(theNumber == 1);
	INFO_PRINTF1(_L("Removes the System directory from a list of directory entries"));
	EikFileUtils::RemoveSystemDirectory(*theDir);
	theNumber = theDir -> Count();
	TEST(theNumber == 0);
	
	delete fileList;
	delete theDir;
	
	theFs.Close();
	}


/**
   @SYMTestCaseID UIF-fileutils-TestUidTypeMatches
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests EikFileUtils::UidTypeMatches() function which tests
   whether two UID types match.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method creates some valid UID types and NULL UID type. It
   also creates similar UID types which is used to compare.\n
   The method then performs the following tests:\n
   1. Invokes UidTypeMatches() with valid UID type & its corresponding match UID
   type.\n
   2. Invokes UidTypeMatches() with NULL UID type & its corresponding match UID
   type ie another NULL UID type.\n
   3. Invokes UidTypeMatches() with NULL UID type & a valid UID type.\n
   4. Invokes UidTypeMatches() with 2 UID types that do not match.\n
   5. Invokes UidTypeMatches() with 2 UID types that contain some NULL UID but
   are similar matches.\n
   
   @SYMTestExpectedResults The test validates results against expected boolean values
   returned by EikFileUtils::UidTypeMatches().
   
 */
void CTFileUtilsAppUi::TestUidTypeMatches()
	{
    TBool bIsMatch;
 
    // set up some uid's
    TUid uid1, uid2, uid3, uid4;
    uid1.iUid = 11111;
    uid2.iUid = 22222;
    uid3.iUid = 33333;
    uid4.iUid = 0;
 
    // set up some uid types
    TUidType theFileUid1(uid1, uid2, uid3);
    TUidType theFileUid2;
    TUidType theFileUid3(uid1, uid2, uid4);
    TUidType theMatchUid1(uid1, uid2, uid3);
    TUidType theMatchUid2;
    TUidType theMatchUid3(uid1, uid2, uid4);
 
     // good
 	INFO_PRINTF3(_L("Tests whether two valid UID types match, uid1 = %d, uid2 = %d"), 
	theFileUid1[0], theMatchUid1[0]);
    bIsMatch = EikFileUtils::UidTypeMatches(theFileUid1, theMatchUid1);
    TEST(bIsMatch);
    // both nulls
 	INFO_PRINTF3(_L("Tests whether two null UID types match, uid1 = %d, uid2 = %d"),
	theFileUid2[0], theMatchUid2[0]);
    bIsMatch = EikFileUtils::UidTypeMatches(theFileUid2, theMatchUid2);
    TEST(bIsMatch);
    // null passed
 	INFO_PRINTF3(_L("Tests whether null and valid UID types match, uid1 = %d, uid2 = %d"),
	theFileUid1[0], theMatchUid2[0]);
    bIsMatch = EikFileUtils::UidTypeMatches(theFileUid1, theMatchUid2);
    TEST(bIsMatch);
    // bad
 	INFO_PRINTF3(_L("Tests whether two invalid UID types match, uid1 = %d, uid2 = %d"),
	theFileUid2[0], theMatchUid1[0]);
    bIsMatch = EikFileUtils::UidTypeMatches(theFileUid2, theMatchUid1);
    TEST(!bIsMatch);
	 
	 //some of the Uid are null
 	INFO_PRINTF3(_L("Compearing two UId's where some of them are null, uid1 = %d, uid2 = %d"),
	theFileUid3[0], theMatchUid3[0]);
    bIsMatch = EikFileUtils::UidTypeMatches(theFileUid3, theMatchUid3);
    TEST(bIsMatch);
	 
    bIsMatch = EikFileUtils::UidTypeMatches(theFileUid3, theMatchUid1);
    TEST(!bIsMatch);
	}


/**
   @SYMTestCaseID UIF-fileutils-TestValidFolderName
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests EikFileUtils::ValidateFolderNameTypedByUserL() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests EikFileUtils::ValidateFolderNameTypedByUserL()
   API which tests the folder name provided by user is valid. \n
   The following tests are performed:\n
   1. Verifies whether alphabetical characters provided by user can form a valid
   folder name.\n
   2. Verifies whether invalid characters such as "*?/\":<>\\" provided by user
   can form a valid folder name.\n
   3. Verifies whether valid characters such as "#@%^$£()[]{}&~-_;,.+" provided
   by user can form a valid folder name.\n
   
   @SYMTestExpectedResults For alphabet charachets & vlid character specified 
   ValidateFolderNameTypedByUserL() API should return KErrNone.
   
 */
void CTFileUtilsAppUi::TestValidFolderName()
	{
	const TBufC<128> theCurrentPath = _L("c:\\");
	const TBufC<128> theFolderNameTypedByUser = _L("abc");
	TFileName	theNewFolderFullName;

	TRAPD(theRes, theNewFolderFullName = EikFileUtils::ValidateFolderNameTypedByUserL(theFolderNameTypedByUser, theCurrentPath));
	TEST(theRes == KErrNone);
	TEST(theNewFolderFullName.Compare(_L("c:\\abc\\")) == 0);

	//check invalid characters
	const TBufC<32> theInvalidCharacters = _L("*?/\":<>\\");

	for(TInt index = 0; index < theInvalidCharacters.Length(); index++)
		{
		TBuf<128>	buf;
		
		buf = theFolderNameTypedByUser;
		buf.Append(theInvalidCharacters[index]);
 		INFO_PRINTF2(_L("Check whether the folder's name %S is invalid"), &buf);
		
		TRAP(theRes, theNewFolderFullName = EikFileUtils::ValidateFolderNameTypedByUserL(buf, theCurrentPath));
		TEST(theRes != KErrNone);
		}
	
	//check valid characters
	TBuf<32> theValidCharacters = _L("#@%^$£()[]{}&~-_;,.+");
	TChar ch(0x20ac);
	theValidCharacters.Append(ch);

	for(TInt index1 = 0; index1< theValidCharacters.Length(); index1++)
		{
		TBuf<128>	buf;
		
		buf = theFolderNameTypedByUser;
		buf.Append(theValidCharacters[index1]);
 		INFO_PRINTF2(_L("Check whether the folder's name %S is valid"), &buf);
		
		TRAP(theRes, theNewFolderFullName = EikFileUtils::ValidateFolderNameTypedByUserL(buf, theCurrentPath));
		TEST(theRes == KErrNone);
		}
	}

/**
   @SYMTestCaseID UIF-fileutils-TestDiskListL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests EikFileUtils::UpdateDiskListL() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests whether UpdateDiskListL() API updates the list
   of available drives. The following tests are performed on UpdateDiskListL():\n
   1. Tests updating drive list so that ROM is not included as a drive.\n
   2. Tests updating drive list so that ROM is included as a drive.\n
   3. Tests updating drive list after mounting a file system on drive X.\n
   
   @SYMTestExpectedResults The test validates results against expected values.
   
 */
void CTFileUtilsAppUi::TestDiskListL()
	{
	CCoeEnv* coeEnv = CCoeEnv::Static();
	TBool	theIncludeRom = EFalse;

	CDesCArray* drives = new(ELeave) CDesCArrayFlat(1);
	TDriveNumber theDriveNumber1 = EDriveC;

	TBuf<2> driveLetter;
	
	CleanupStack::PushL(drives);

	EikFileUtils::UpdateDiskListL(coeEnv->FsSession(), *drives, theIncludeRom, theDriveNumber1);
	INFO_PRINTF2(_L("The number of the drive : %d"), drives->MdcaCount());
	
	TInt theCurDriveNumber = drives->MdcaCount();
	TEST(theCurDriveNumber >= 1);
	driveLetter = (*drives)[0];
	INFO_PRINTF2(_L("The drive letter should be C only : %S"), &driveLetter);
	TEST(driveLetter[0] == 'C');

	EikFileUtils::UpdateDiskListL(coeEnv->FsSession(), *drives, theIncludeRom, theDriveNumber1);
	INFO_PRINTF3(_L("The number of drives has to be the same %d: %d"), theCurDriveNumber, drives->MdcaCount());
	TEST(drives->MdcaCount() == theCurDriveNumber);

	theIncludeRom = ETrue;
	EikFileUtils::UpdateDiskListL(coeEnv->FsSession(), *drives, theIncludeRom, theDriveNumber1);
	INFO_PRINTF2(_L("The number of the drive : %d"), drives->MdcaCount());
	theCurDriveNumber++;
	TEST(drives->MdcaCount() == theCurDriveNumber);
	driveLetter = (*drives)[theCurDriveNumber-1];
	INFO_PRINTF2(_L("The drive letter should be Z : %S"), &driveLetter);
	TEST(driveLetter[0] == 'Z');

	CleanupStack::PopAndDestroy(drives); 
	}


/**
   @SYMTestCaseID UIF-fileutils-TestSortByTableL
  
   @SYMPREQ
  
   @SYMTestCaseDesc The test exercises EikFileUtils::SortByTable() API.
  
   @SYMTestPriority High
 
   @SYMTestStatus Implemented
   
   @SYMTestActions The test exercises EikFileUtils::SortByTable function. 
   The function must sort list of files in order specified in the second 
   param - table of UIDs. The testing directory has 4 files, two of them have
   equal UID in the sort table.
   
   @SYMTestExpectedResults The test validates results against expected values.
   
 */
void CTFileUtilsAppUi::TestSortByTableL()
	{
	CDir* theFileList;
	TInt theAttribs=KEntryAttNormal|KEntryAttSystem|KEntryAttAllowUid;
	TFileName theCurrentPath = _L("Z:\\uiktest\\Documents\\test\\");

	RFs& fs=iEikonEnv->FsSession();
	const TInt ret=fs.GetDir(theCurrentPath,theAttribs,ESortByName,theFileList);
	User::LeaveIfError(ret);

	CleanupStack::PushL(theFileList);

	TResourceReader reader;
	CEikonEnv::Static()->CreateResourceReaderLC(reader,R_EIK_ARRAY_FILE_SORT_TABLE);

	CBaflFileSortTable*theTable = new (ELeave) CBaflFileSortTable();
	CleanupStack::PushL(theTable);
	theTable->ConstructFromResourceL(reader);

	INFO_PRINTF1(_L("Get the names of the files sorted by alphabetical order"));
	for(TInt theIndex1 = 0; theIndex1 < theFileList->Count(); theIndex1++)
		{
		TEntry	theEntry = (*theFileList)[theIndex1];
		TUid	theUid1		= theEntry[2];
		INFO_PRINTF4(_L("The %d file in list %S, Uid = 0x%x"), theIndex1 + 1, &theEntry.iName, theUid1.iUid);
		
		switch(theIndex1)
			{
		case 0:
			TEST(theEntry.iName == _L("tfileutils.agenda"));
			break;
		case 1:
			TEST(theEntry.iName == _L("tfileutils.dummy"));
			break;
		case 2:
			TEST(theEntry.iName == _L("tfileutils.scetch"));
			break;
		case 3:
			TEST(theEntry.iName == _L("tfileutils.word"));
			break;
		default:
			break;
			}
		}


	EikFileUtils::SortByTable(*theFileList, theTable);
	INFO_PRINTF1(_L("Get the names of the files sorted by the Uid's table"));
	for(TInt theIndex = 0; theIndex < theFileList->Count(); theIndex++)
		{
		TEntry	theEntry = (*theFileList)[theIndex];
		TUid	theUid1		= theEntry[2];
		
		INFO_PRINTF4(_L("The %d file in list %S, Uid = 0x%x"), theIndex + 1, &theEntry.iName, theUid1.iUid);
		switch(theIndex)
			{
		case 0:
			TEST(theEntry.iName == _L("tfileutils.word"));
			break;
		case 1:
			TEST(theEntry.iName == _L("tfileutils.agenda"));
			break;
		case 2:
			TEST(theEntry.iName == _L("tfileutils.scetch"));
			break;
		case 3:
			TEST(theEntry.iName == _L("tfileutils.dummy"));
			break;
		default:
			break;
			}
		}

	CleanupStack::PopAndDestroy(3); //reader theFileList theTable
	}

