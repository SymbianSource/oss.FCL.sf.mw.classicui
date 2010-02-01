// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code  
*/


#include "t_addressstringtokenizer.h"

// LOCAL CONSTANTS AND MACROS
static const TInt KReadBufSize(256);
static const TInt KFullBufSize(10000);

_LIT(KTextToBeParsed, "http://www.google.com 23). 9p=71 jee elvis.presley@hotmail.com  07/00-123123? http://wap.google.com (123 45678910?) 127.0555.0555 roskaa 1.3.4.5.6.7.8.9 laatikos (127.0.0.1) a (0802345... ad (+0821898 (*02 +#098");
_LIT(KTextToBeParsedForPhNoWithMin15Nos, "tekstii... http://www.google.com jeba jee elvis.presley@hotmail.com 0700-12w312312345 habaha 123 45p1234678910 a 127.052355.052355 roskaa 1.3.4.5.6.7.8.9.1.2.3.4.5.6.7 laatikos a");
_LIT(KTextToBeParsedToCheckPositions, "tekstii... rtsp://www.abcd.com jeba jee elvis.presley@hotmail.com 0700-123123 habaha@luukku.com 123 45678910? lapalaa vielayksi@yahoo.com roskaa");

_LIT(KTextToBeParsedForEmailAndURL, "tekstii... https://www.google.com jeba jee ..elvis.presley@hotmail.com.. 127.0.0.1? roskaa ad!d#$?%&c*+-/d@g_mail-1.com");
_LIT(KTextToBeParsedForInvalidEMail, "tekstii... www.yahoo.com adsadf .@gmail.com akjdl adf@.$ya%hoo.com jeba jee 127.*.0.1 roskaa@");
_LIT(KPhoneNo1, "07/00-123123");
_LIT(KPhoneNo2, "123 45678910");
_LIT(KPhoneNo3, "127.0555.0555");
_LIT(KPhoneNo4, "1.3.4.5.6.7.8.9");
_LIT(KPhoneNo5, "0802345");
_LIT(KPhoneNo6, "+0821898");
_LIT(KPhoneNo7, "#098");

_LIT(KEMail, "elvis.presley@hotmail.com");
_LIT(KEMail1, "habaha@luukku.com");
_LIT(KEMail2, "vielayksi@yahoo.com");
_LIT(KEMail3, "ad!d#$?%&c*+-/d@g_mail-1.com");

_LIT(KURL1, "http://www.google.com");
_LIT(KURL2, "127.0.0.1");
_LIT(KURL3, "https://www.google.com");
_LIT(KURL4, "rtsp://www.abcd.com");
_LIT(KURL5, "http://wap.google.com");

/**
   Constructor
 */	
CT_AddressStringTokenizerStep::CT_AddressStringTokenizerStep()
	{
	// Call base class method to set up the human readable name for logging*/
	SetTestStepName(KT_AddressStringTokenizerStep);
	}

/**
   Destructor
 */
CT_AddressStringTokenizerStep::~CT_AddressStringTokenizerStep()
	{
	}

TVerdict CT_AddressStringTokenizerStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
	__UHEAP_MARK;
	RunTestCases();
	__UHEAP_MARKEND;
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}

void CT_AddressStringTokenizerStep::RunTestCases()
	{
	TInt err;
	SetTestStepID(_L("UIF-ETUL-0001"));
	INFO_PRINTF1(_L("Test to search URLs"));
	TRAP(err, SearchURLsL());
	TEST(err == KErrNone);
	RecordTestResultL();

	SetTestStepID(_L("UIF-ETUL-0002"));
	INFO_PRINTF1(_L("Test to search EMailAddresses"));
	TRAP(err, SearchEMailAddressesL());
	TEST(err == KErrNone);
	RecordTestResultL();
	
	SetTestStepID(_L("UIF-ETUL-0003"));
	INFO_PRINTF1(_L("Test to search PhoneNumbers"));
	TRAP(err, SearchPhoneNumbersL());
	TEST(err == KErrNone);
	RecordTestResultL();

	SetTestStepID(_L("UIF-ETUL-0004"));
	INFO_PRINTF1(_L("Tests for PhoneNos with Min. 3 nos. in a string \n\t\t\t\t\t\t\t when the string is considered as a phone no.\n"));
	TRAP(err, SearchPhoneNumbersWithMin3NosL());
	TEST(err == KErrNone);
	RecordTestResultL();
	
	SetTestStepID(_L("UIF-ETUL-0005"));
	INFO_PRINTF1(_L("Tests for PhoneNos with Min. 8 nos. in a string \n\t\t\t\t\t\t\t when the string is considered as a phone no.\n"));
	TRAP(err, SearchPhoneNumbersWithMin8NosL());
	TEST(err == KErrNone);
	RecordTestResultL();
	
	SetTestStepID(_L("UIF-ETUL-0006"));
	INFO_PRINTF1(_L("Tests for PhoneNos with Min. 15 nos. in a string \n\t\t\t\t\t\t\t when the string is considered as a phone no.\n"));
	TRAP(err, SearchPhoneNumbersWithMin15NosL());
	TEST(err == KErrNone);
	RecordTestResultL();
	
	SetTestStepID(_L("UIF-ETUL-0007"));
	INFO_PRINTF1(_L("Test to search URL's, EMailAddresses, PhoneNumbers"));
	TRAP(err, SearchAllL());
	TEST(err == KErrNone);
	RecordTestResultL();
	
	SetTestStepID(_L("UIF-ETUL-0008"));
	INFO_PRINTF1(_L("Test to check the positions"));
	TRAP(err, CheckPositionsL());
	TEST(err == KErrNone);
	RecordTestResultL();
	
	SetTestStepID(_L("UIF-ETUL-0009"));
 	INFO_PRINTF1(_L("Test to Parse URI file"));
	TRAP(err, ParseURIFileL());
	TEST(err == KErrNone);
	RecordTestResultL();
		
	TestOOMForAddressStringTokenizer();
	
	SetTestStepID(_L("UIF-ETUL-0024"));
	INFO_PRINTF1(_L("Test Phone Search Separators"));
	TRAP(err, TestPhoneSearchSeparatorsL());
	TEST(err == KErrNone);
	RecordTestResultL();
	CloseTMSGraphicsStep();
	}

/**
   @SYMTestCaseID UIF-ETUL-0001

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to search for 2 URLs present in the string.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs the CTulAddressStringTokenizer object with CTulAddressStringTokenizer::EFindItemSearchURLBin\n
   which parses the given string and creates an item array consisting of all the URL's found in the string.\n
   API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases);\n
   CTulAddressStringTokenizer::Item(SFoundItem& aItem); \n
   CTulAddressStringTokenizer::NextItem(SFoundItem& aItem); \n   
  
   @SYMTestExpectedResults The test checks whether 
   1. 2 URL's found by CTulAddressStringTokenizer are the correct ones.
   2. Returns zero URLs when text with Invalid URL's is used for parsing.
   3. CTulAddressStringTokenizer::addressString->ItemCount() returns two when the text with 2 valid URL's is parsed 
   		and returns zero when text with Invalid URL's is parsed.
   4. CTulAddressStringTokenizer::Item() returns EFalse when there are no found items in the addressString.
 */
void CT_AddressStringTokenizerStep::SearchURLsL()
    {
	TBufC<512> str(KTextToBeParsedForEmailAndURL);
	
	CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedForEmailAndURL, CTulAddressStringTokenizer::EFindItemSearchURLBin);
			
	// Get count of found URL's
	TInt count(addressString->ItemCount());
	
	TEST(count == 2);

	// Get currently selected URL
	CTulAddressStringTokenizer::SFoundItem item;
	addressString->Item(item);
	TPtrC16 url(str.Mid(item.iStartPos, item.iLength));
	TEST(url.Compare(KURL3) == 0);
	
	// Get next found URL
	addressString->NextItem(item);
	url.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(url.Compare(KURL2) == 0);
	
	delete addressString;
	
	INFO_PRINTF1(_L("Test to search the text with Invalid URLs"));

	_LIT(KTextToBeParsedForInvalidURL, "tekstii... htsp:\\yahoo.com adsadf wws.google.com akjdl httls://sww.google.com jeba jee 127.*.0.1 roskaa");
	addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedForInvalidURL, CTulAddressStringTokenizer::EFindItemSearchURLBin);
		
	// Get count of found URL's
	count = addressString->ItemCount();
	TEST(count == 0);
	TEST(!addressString->Item(item));

	delete addressString;
    }

/**
   @SYMTestCaseID UIF-ETUL-0002

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to search for Email Addresses in the string.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs the CTulAddressStringTokenizer object with CTulAddressStringTokenizer::EFindItemSearchMailAddressBin\n
   which parses the given string and creates an item array consisting of all the Email Addresses found in the string.\n
   API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases);\n
   CTulAddressStringTokenizer::Item(SFoundItem& aItem); \n
   CTulAddressStringTokenizer::NextItem(SFoundItem& aItem); \n   
  
   @SYMTestExpectedResults The test checks whether 
   1. 2 email addresses found by CTulAddressStringTokenizer are the correct ones.
   2. CTulAddressStringTokenizer::NextItem() returns EFalse when no more email addresses are found in the addressString.
   3. Returns zero email addresses when text with Invalid email addresses is used for parsing.
 */
void CT_AddressStringTokenizerStep::SearchEMailAddressesL()
    {
	CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedForEmailAndURL, CTulAddressStringTokenizer::EFindItemSearchMailAddressBin);
	
	TBufC<512> str(KTextToBeParsedForEmailAndURL);
	
	// Get count of found email addresses
	TInt count(addressString->ItemCount());
	TEST(count == 2);

	// Get currently selected email
	CTulAddressStringTokenizer::SFoundItem item;
	addressString->Item(item);
	TPtrC16 emailAddress(str.Mid(item.iStartPos, item.iLength));
	TEST(emailAddress.Compare(KEMail) == 0);

	addressString->NextItem(item);
	emailAddress.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(emailAddress.Compare(KEMail3) == 0);

	// Try to get next email address, should fail
	TEST(addressString->NextItem(item) == EFalse);

	delete addressString;
	
	INFO_PRINTF1(_L("Test to search the text with Invalid EMail addresses"));
	addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedForInvalidEMail, CTulAddressStringTokenizer::EFindItemSearchMailAddressBin);
		
	// Get count of found EMail Addresses
	count = addressString->ItemCount();
	TEST(count == 0);

	delete addressString;
	}

/**
   @SYMTestCaseID UIF-ETUL-0003

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to search for phone numbers in the string.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs the CTulAddressStringTokenizer object with CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin \n
   which parses the given string and creates an item array consisting of all the phone numbers found in the string.\n
   3 is the minimun count of numbers in a string that the string is considered as a phone number when phone numbers are 
   searched.API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases);\n
   CTulAddressStringTokenizer::ItemArray(); \n
  
   @SYMTestExpectedResults The test checks whether 
   1. 7 Phone numbers found by CTulAddressStringTokenizer are the correct ones.
   2. CTulAddressStringTokenizer::ItemArray() returns correct array of phone numbers.
   3. Returns zero phone numbers when text with Invalid phone numbers is used for parsing.
 */
void CT_AddressStringTokenizerStep::SearchPhoneNumbersL()
    {
	CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsed, CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin);
	
	TBufC<512> str(KTextToBeParsed);
	
	const CArrayFixFlat<CTulAddressStringTokenizer::SFoundItem>* itemArray = addressString->ItemArray();
	
		// Get count of found email addresses
	TInt count(addressString->ItemCount());
	TEST(count == 7);

	// Get currently selected phone number
	TPtrC16 phoneNos(str.Mid((*itemArray)[0].iStartPos, (*itemArray)[0].iLength));
	TEST(phoneNos.Compare(KPhoneNo1) == 0);

	// Get next found number
	phoneNos.Set(str.Mid((*itemArray)[1].iStartPos, (*itemArray)[1].iLength));
	TEST(phoneNos.Compare(KPhoneNo2) == 0);

	// Get next found number
	phoneNos.Set(str.Mid((*itemArray)[2].iStartPos, (*itemArray)[2].iLength));
	TEST(phoneNos.Compare(KPhoneNo3) == 0);

	// Get next found number
	phoneNos.Set(str.Mid((*itemArray)[3].iStartPos, (*itemArray)[3].iLength));
	TEST(phoneNos.Compare(KPhoneNo4) == 0);

	// Get next found number
	phoneNos.Set(str.Mid((*itemArray)[4].iStartPos, (*itemArray)[4].iLength));
	TEST(phoneNos.Compare(KPhoneNo5) == 0);

	// Get next found number
	phoneNos.Set(str.Mid((*itemArray)[5].iStartPos, (*itemArray)[5].iLength));
	TEST(phoneNos.Compare(KPhoneNo6) == 0);

	// Get next found number
	phoneNos.Set(str.Mid((*itemArray)[6].iStartPos, (*itemArray)[6].iLength));
	TEST(phoneNos.Compare(KPhoneNo7) == 0);

	// Get last found number again
	phoneNos.Set(str.Mid((*itemArray)[5].iStartPos, (*itemArray)[5].iLength));
	TEST(phoneNos.Compare(KPhoneNo6) == 0);

	delete addressString;
	
	INFO_PRINTF1(_L("Test to search the text with Invalid Phone nos."));
	_LIT(KTextToBeParsedForInvalidPhoneNos, "jeba jee 070@0-1231#23 habaha 123 456^78910? roskaa laatikos a");

	addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedForInvalidPhoneNos, CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin, 8);
	
	count= addressString->ItemCount();
	TEST(count == 0);
	
	delete addressString;
    }

/**
   @SYMTestCaseID UIF-ETUL-0004

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to search for phone numbers containing minimum 3 numbers, in the string.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs the CTulAddressStringTokenizer object with CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin\n
   which parses the given string and creates an item array consisting of all the phone numbers containing minimum 3 numbers, found in the string.\n
   API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases, TInt aMinNumbers);\n
   CTulAddressStringTokenizer::Item(SFoundItem& aItem); \n
   CTulAddressStringTokenizer::NextItem(SFoundItem& aItem); \n   
  
   @SYMTestExpectedResults The test checks whether 
   1. 7 Phone numbers found by CTulAddressStringTokenizer are the correct ones.
 */
void CT_AddressStringTokenizerStep::SearchPhoneNumbersWithMin3NosL()
    {
	CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsed, CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin, 3);
	
	TBufC<512> str(KTextToBeParsed);
	
	// Get count of found email addresses
	TInt count(addressString->ItemCount());
	TEST(count == 7);

	// Get currently selected phone number
	CTulAddressStringTokenizer::SFoundItem item;
	addressString->Item(item);
	TPtrC16 phoneNos(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo1) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo2) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo3) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo4) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo5) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo6) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo7) == 0);

	delete addressString;
    }

/**
   @SYMTestCaseID UIF-ETUL-0005

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to search for phone numbers containing minimum 8 numbers, in the string.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs the CTulAddressStringTokenizer object with CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin\n
   which parses the given string and creates an item array consisting of all the phone numbers containing minimum 8 numbers, found in the string.\n
   API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases, TInt aMinNumbers);\n
   CTulAddressStringTokenizer::Item(SFoundItem& aItem); \n
   CTulAddressStringTokenizer::NextItem(SFoundItem& aItem); \n   
   CTulAddressStringTokenizer::PrevItem(SFoundItem& aItem); \n   
  
   @SYMTestExpectedResults The test checks whether 
   1. 4 Phone numbers found by CTulAddressStringTokenizer are the correct ones.
   2. CTulAddressStringTokenizer::PrevItem() returns EFalse when called for the first time on addressString 
   		array(ie., when addressString is pointing to the first item in the array).
   3. CTulAddressStringTokenizer::PrevItem() returns correct phone number if it is called after accessing 
   		the last item in the addressString array.
 */
void CT_AddressStringTokenizerStep::SearchPhoneNumbersWithMin8NosL()
    {
	CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsed, CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin, 8);
	
	TBufC<512> str(KTextToBeParsed);
	
	// Get count of found email addresses
	TInt count(addressString->ItemCount());
	TEST(count == 4);

	CTulAddressStringTokenizer::SFoundItem item;
	
	// Try to get a previous item
	TEST(!addressString->PrevItem(item));

	// Get currently selected phone number
	addressString->Item(item);
	TPtrC16 phoneNos(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo1) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo2) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo3) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo4) == 0);

	// Get last found number again
	addressString->PrevItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNo3) == 0);

	delete addressString;
    }

/**
   @SYMTestCaseID UIF-ETUL-0006

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to search for phone numbers containing minimum 15 numbers, in the string.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs the CTulAddressStringTokenizer object with CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin\n
   which parses the given string and creates an item array consisting of all the phone numbers containing minimum 15 numbers, found in the string.\n
   API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases, TInt aMinNumbers);\n
   CTulAddressStringTokenizer::Item(SFoundItem& aItem); \n
   CTulAddressStringTokenizer::NextItem(SFoundItem& aItem); \n   
  
   @SYMTestExpectedResults The test checks whether 
   1. 4 Phone numbers found by CTulAddressStringTokenizer are the correct ones.
   2. CTulAddressStringTokenizer::PrevItem() returns correct phone number if it is called after accessing 
   		the last item in the addressString array.
 */
void CT_AddressStringTokenizerStep::SearchPhoneNumbersWithMin15NosL()
	{
	_LIT(KPhoneNoWithMin15no1, "0700-12w312312345");
	_LIT(KPhoneNoWithMin15no2, "123 45p1234678910");
	_LIT(KPhoneNoWithMin15no3, "127.052355.052355");
	_LIT(KPhoneNoWithMin15no4, "1.3.4.5.6.7.8.9.1.2.3.4.5.6.7");

	CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedForPhNoWithMin15Nos, CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin, 15);
	
	TBufC<512> str(KTextToBeParsedForPhNoWithMin15Nos);
	  
	  // Get count of found email addresses
	TInt count(addressString->ItemCount());
	TEST(count == 4);

	// Get currently selected phone number
	CTulAddressStringTokenizer::SFoundItem item;
	addressString->Item(item);
	TPtrC16 phoneNos(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNoWithMin15no1) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNoWithMin15no2) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNoWithMin15no3) == 0);

	// Get next found number
	addressString->NextItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNoWithMin15no4) == 0);

	// Get last found number again
	addressString->PrevItem(item);
	phoneNos.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(phoneNos.Compare(KPhoneNoWithMin15no3) == 0);

	delete addressString;
    }

/**
   @SYMTestCaseID UIF-ETUL-0007

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to search for Phone numbers, Email addresses and URL's in the string.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs three CTulAddressStringTokenizer objects with CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin\n
   CTulAddressStringTokenizer::EFindItemSearchMailAddressBin and CTulAddressStringTokenizer::EFindItemSearchURLBin,
   which parses the given string and creates an item array consisting of all the Phone numbers, Email addresses and URL's \n
   respectively found in the string.\n
   API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases);\n
   CTulAddressStringTokenizer::Item(SFoundItem& aItem); \n
   CTulAddressStringTokenizer::NextItem(SFoundItem& aItem); \n   
   CTulAddressStringTokenizer::DoNewSearchL( const TDesC& aText, TInt aSearchCases); \n
  
   @SYMTestExpectedResults The test checks whether 
   1. Phone numbers, Email addresses and URL's found by CTulAddressStringTokenizer are the correct ones.
   2. CTulAddressStringTokenizer::DoNewSearchL() returns correct addressString array.
 */
void CT_AddressStringTokenizerStep::SearchAllL()
    {
	CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsed, CTulAddressStringTokenizer::EFindItemSearchMailAddressBin);
	
	TBufC<512> str(KTextToBeParsed);
	
	// Get count of found email addresses
	TInt count(addressString->ItemCount());
	
	TEST(count == 1);

	// Get currently selected email
	CTulAddressStringTokenizer::SFoundItem item;
	addressString->Item(item);
	TPtrC16 result(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KEMail) == 0);
	
	//make a new search - search for URL
	addressString->DoNewSearchL(KTextToBeParsed, CTulAddressStringTokenizer::EFindItemSearchURLBin);
	
	count = addressString->ItemCount();
	TEST(count == 3);

	// Get currently selected URL
	addressString->Item(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KURL1) == 0);

	// Get next selected URL
	addressString->NextItem(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KURL5) == 0);
	
	// Get next selected URL
	addressString->NextItem(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KURL2) == 0);

	//make a new search - search for phone number
	addressString->DoNewSearchL(KTextToBeParsed, CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin);
	
	count = addressString->ItemCount();
	TEST(count == 7);
	
	// Get selected phone number
	addressString->Item(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KPhoneNo1) == 0);
	
	// Get next selected phone number
	addressString->NextItem(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KPhoneNo2) == 0);

	// Get next selected phone number
	addressString->NextItem(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KPhoneNo3) == 0);

	// Get next selected phone number
	addressString->NextItem(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KPhoneNo4) == 0);

	// Get next selected phone number
	addressString->NextItem(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KPhoneNo5) == 0);
	
	// Get next selected phone number
	addressString->NextItem(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KPhoneNo6) == 0);

	// Get next selected phone number
	addressString->NextItem(item);
	result.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KPhoneNo7) == 0);

	delete addressString;
	}

/**
   @SYMTestCaseID UIF-ETUL-0008

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to search for email addresses in the string and verifies their positions.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs CTulAddressStringTokenizer object with CTulAddressStringTokenizer::EFindItemSearchMailAddressBin|EFindItemSearchURLBin \n
   which parses the given string and creates an item array consisting of all the Email addresses and URL's\n
   API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases);\n
   CTulAddressStringTokenizer::Item(SFoundItem& aItem); \n
   CTulAddressStringTokenizer::NextItem(SFoundItem& aItem);\n
   CTulAddressStringTokenizer::ResetPosition();\n
  
   @SYMTestExpectedResults The test checks whether 
   1. Phone numbers, Email addresses and URL's found by CTulAddressStringTokenizer are the correct ones.
   2. CTulAddressStringTokenizer::ResetPosition() resets the position of the addressString array to zero.
 */
void CT_AddressStringTokenizerStep::CheckPositionsL()
    {
	CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedToCheckPositions, (CTulAddressStringTokenizer::TTokenizerSearchCase)(CTulAddressStringTokenizer::EFindItemSearchMailAddressBin | CTulAddressStringTokenizer::EFindItemSearchURLBin));
	
	TBufC<512> str(KTextToBeParsedToCheckPositions);
	
	//Get count of found email addresses
	TInt count(addressString->ItemCount());
	TEST(count == 4);
		
	// Get currently selected email
	CTulAddressStringTokenizer::SFoundItem item;
	addressString->Item(item);
	TPtrC16 result(str.Mid(item.iStartPos, item.iLength));
	TEST(result.Compare(KURL4) == 0);

	addressString->NextItem(item);
	TPtrC16 result1(str.Mid(item.iStartPos, item.iLength));
	TEST(result1.Compare(KEMail) == 0);

	//move to next item
	addressString->NextItem(item);
	TPtrC16 result2(str.Mid(item.iStartPos, item.iLength));
	TEST(result2.Compare(KEMail1) == 0);
	
	//check that position is correct
	TEST(addressString->Position() == 2);
	
	//move to next item
	addressString->NextItem(item);
	result2.Set(str.Mid(item.iStartPos, item.iLength));
	TEST(result2.Compare(KEMail2) == 0);

	//Resets the position to zero 
	addressString->ResetPosition();
	//get the first item
	addressString->Item(item);

	TPtrC16 reset_result1(str.Mid(item.iStartPos, item.iLength));
	TEST(reset_result1.Compare(KURL4) == 0);

	//verify that we are in first item
	TEST(result == reset_result1);
	
	delete addressString;
	}

/**
   @SYMTestCaseID UIF-ETUL-0009

   @SYMREQ 7736
 
   @SYMTestCaseDesc Test to Parse for URI's, Email Addresses, Phone Numbers and URL's in a file and to verify them
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions Constructs CTulAddressStringTokenizer object with CTulAddressStringTokenizer::EFindItemSearchMailAddressBin \n
   which parses the given string and creates an item array consisting of all the Email addresses\n
   API Calls:\n	
   CTulAddressStringTokenizer::NewL(const TDesC& aText, TInt aSearchCases);\n
   CTulAddressStringTokenizer::Item(SFoundItem& aItem); \n
   CTulAddressStringTokenizer::NextItem(SFoundItem& aItem); \n   
  
   @SYMTestExpectedResults The test checks whether 
   1. Phone numbers, Email addresses, URL's and URI's  parsed by CTulAddressStringTokenizer are the correct ones.
 */
void CT_AddressStringTokenizerStep::ParseURIFileL()
    {
	INFO_PRINTF1(_L("Test begins"));
    __UHEAP_MARK;

    //load test case text to string
    RFs rfs;
    User::LeaveIfError(rfs.Connect());
    CleanupClosePushL(rfs);
 	_LIT(KParesTextFile, "z:\\system\\data\\addressstringtokenizertestappdata.txt");
	_LIT(KParesTextFileRef, "z:\\system\\data\\addressstringtokenizertestappdataref.txt");

    RFile file;
    HBufC* fullBuf = HBufC::NewMaxLC(KFullBufSize);
    TPtr fullBufPtr = fullBuf->Des();                  
    fullBufPtr = KNullDesC;

	TFileText reader;
    TBuf<KReadBufSize> fileBuffer;

	if ((file.Open(rfs, KParesTextFile, EFileStreamText|EFileRead|EFileShareAny)) == KErrNone)
		{
		CleanupClosePushL(file);
        // use TFileText for reading file. There is probably better ways to do this tho.
        reader.Set(file);
        if (reader.Seek(ESeekStart))
			{
			INFO_PRINTF1(_L("File corrupted"));
            User::Leave(KErrGeneral); // not cleaning up properly
            }

        while (!reader.Read(fileBuffer))
		    {
		    fullBufPtr.Append(fileBuffer);
		    fullBufPtr.Append('\n');   
		    }
		CleanupStack::Pop(&file);    
        file.Close();
        }
    else
        {
		INFO_PRINTF1(_L("z:\\system\\data\\addressstringtokenizertestappdata.txt not found"));
		User::Leave(KErrNotFound);
  	   }

	if (file.Open(rfs, KParesTextFileRef, EFileStreamText|EFileRead|EFileShareAny) == KErrNone)
		{
		CleanupClosePushL(file);
        // use TFileText for reading file. There is probably better way to do this tho.
        reader.Set(file);
        if (reader.Seek(ESeekStart))
			{
			INFO_PRINTF1(_L("File corrupted"));
            User::Leave(KErrGeneral); // not cleaning up properly
            }
		}
    else
        {
		INFO_PRINTF1(_L("z:\\system\\data\\addressstringtokenizertestappdataref.txt not found"));
		User::Leave(KErrNotFound);
        }

    INFO_PRINTF1(_L("Start searching..."));
                
    // Create an instance of Address String Tokenizer and search for URL's.
    CTulAddressStringTokenizer* addressString = CTulAddressStringTokenizer::NewL(fullBufPtr, CTulAddressStringTokenizer::EFindItemSearchURLBin);
    TestAddressStringTokenizers(addressString, reader, fullBufPtr);
    delete addressString;

    // find phone numbers from same text
    addressString = CTulAddressStringTokenizer::NewL(fullBufPtr, CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin);
    TestAddressStringTokenizers(addressString, reader, fullBufPtr);
	
    // test do new search with same instance
    TInt count = addressString->DoNewSearchL(fullBufPtr, CTulAddressStringTokenizer::EFindItemSearchMailAddressBin);
  	TEST(count > 0);
  	TestAddressStringTokenizers(addressString, reader, fullBufPtr);
    delete addressString;
                
    // find schemed URIs from same text
    addressString = CTulAddressStringTokenizer::NewL(fullBufPtr, CTulAddressStringTokenizer::EFindItemSearchScheme);
	TestAddressStringTokenizers(addressString, reader, fullBufPtr);
    delete addressString;

    // find everything from same text
    addressString = CTulAddressStringTokenizer::NewL(fullBufPtr, (CTulAddressStringTokenizer::TTokenizerSearchCase)(CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin | CTulAddressStringTokenizer::EFindItemSearchURLBin | CTulAddressStringTokenizer::EFindItemSearchMailAddressBin | CTulAddressStringTokenizer::EFindItemSearchScheme));
	TestAddressStringTokenizers(addressString, reader, fullBufPtr);	
    delete addressString;

    CleanupStack::PopAndDestroy(3, &rfs);
    __UHEAP_MARKEND;
	}

/**
   @SYMTestCaseID UIF-ETUL-0010

   @SYMREQ 7736
 
   @SYMTestCaseDesc OOM test for CTulAddressStringTokenizer's NewL() and DoNewSearchL() methods.
  
   @SYMTestPriority High 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions  Calls CTulAddressStringTokenizer's NewL() and DoNewSearchL() methods.

   @SYMTestExpectedResults Tests should complete without any memory leaks.
 */
void CT_AddressStringTokenizerStep::TestOOMForAddressStringTokenizer()
	{
	INFO_PRINTF1(_L("Start OOM test for Address String Tokenizer"));
	CTulAddressStringTokenizer* addressString = NULL;
	TInt count;
	TInt fail;

	//OOM test for CTulAddressStringTokenizer::NewL() method.
	for (fail = 1;; fail++)
		{
		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
		__UHEAP_MARK;
		TRAPD(err, addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedForEmailAndURL, CTulAddressStringTokenizer::EFindItemSearchURLBin));
		TEST((err == KErrNone) || (err == KErrNoMemory));
		if (err == KErrNone)
			{
			// Get count of found URL's
			count = addressString->ItemCount();
			TEST(count == 2);
			delete addressString;
			addressString = NULL;
			__UHEAP_MARKEND;
			break;
			}
		__UHEAP_MARKEND;
		}

	//OOM test for CTulAddressStringTokenizer::DoNewSearchL() method.
	for (fail = 1; ; fail++)
		{
		__UHEAP_RESET;
		TRAPD(err, addressString = CTulAddressStringTokenizer::NewL(KTextToBeParsedForEmailAndURL, CTulAddressStringTokenizer::EFindItemSearchURLBin));
		TEST(err == KErrNone);

		__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
		__UHEAP_MARK;
		TRAP(err, count = addressString->CTulAddressStringTokenizer::DoNewSearchL(KTextToBeParsed, CTulAddressStringTokenizer::EFindItemSearchMailAddressBin));
		TEST((err == KErrNone) || (err == KErrNoMemory));
		if (err == KErrNone)
			{
			// Get count of found URL's
			count = addressString->ItemCount();
			TEST(count == 1);
			delete addressString;
			__UHEAP_MARKEND;
			break;
			}
		else
			{
			delete addressString;
			__UHEAP_MARKEND;
			}
		}
	__UHEAP_RESET;
	INFO_PRINTF1(_L("OOM test for Address String Tokenizer Completed"));
	}

void CT_AddressStringTokenizerStep::TestAddressStringTokenizers(CTulAddressStringTokenizer* aAddressStringTokenizer, TFileText& aReader, TDes& aText)
	{
    TBuf<KReadBufSize> fileBuffer;

    // Get count of found items.
    TInt count(aAddressStringTokenizer->ItemCount());
	TEST(count > 0);
	TPtrC result;

    // SFoundItem instance
    CTulAddressStringTokenizer::SFoundItem item;

    TBool found = aAddressStringTokenizer->Item(item);
    TEST(found);
    for(TInt i = 0; i < count; i++)
		{
        result.Set(aText.Mid(item.iStartPos, item.iLength));
		aReader.Read(fileBuffer);

		//Comparing parsed result to what read buffer reads from the file.
		TEST(!fileBuffer.Compare(result) );
		if (fileBuffer.Compare(result))
			{
			INFO_PRINTF2(_L("Buffer : %S"), &fileBuffer);
			INFO_PRINTF2(_L("Result : %S"), &result);
			}
        aAddressStringTokenizer->NextItem(item);
        }
	}

/**
   @SYMTestCaseID UIF-ETUL-0024

   @SYMREQ DEF114388
 
   @SYMTestCaseDesc Test of CTulAddressStringTokenizer::SearchPhoneNumberL( const TDesC& aText )
                    with all the phone number separators.
  
   @SYMTestPriority Normal 
 
   @SYMTestStatus Implemented
  
   @SYMTestActions There should be 5 phone numbers separators:
                      - KCharLinefeed = 0x000A 
                      - KCharFormfeed = 0x000C
                      - KCharCarriageReturn = 0x000D
                      - KCharLineSeparator = 0x2028
                      - KCharParagraphSeparator = 0x2029
                   With a simple string _LIT16(KTestPhoneSeparator, "11111%c22222")
                   and with all the separators above, we apply the tested function:
                   CTulAddressStringTokenizer::SearchPhoneNumberL( const TDesC& aText )
                      
  
   @SYMTestExpectedResults On the 5 cases, the function should find 2 phone numbers
                           i.e: multiSearch->ItemCount() should be equal to 2
                           otherwise the test fail.
 */
void CT_AddressStringTokenizerStep::TestPhoneSearchSeparatorsL()
	{
	TInt KCharLinefeed = 0x000A;
	TInt KCharFormfeed = 0x000C;
	TInt KCharCarriageReturn = 0x000D;
	TInt KCharLineSeparator = 0x2028;
	TInt KCharParagraphSeparator = 0x2029;
	TInt KSeparators[5]={KCharLinefeed,KCharFormfeed,KCharCarriageReturn,KCharLineSeparator,KCharParagraphSeparator};
	_LIT16(KTestPhoneSeparator, "11111%c22222");
	TBool succeed=ETrue;
	TBuf16<16> str;
	for (TInt k=0;k<5;k++)
		{
		str.Format(KTestPhoneSeparator,KSeparators[k]);
		CTulAddressStringTokenizer* multiSearch = CTulAddressStringTokenizer::NewL(str,
				CTulAddressStringTokenizer::EFindItemSearchPhoneNumberBin);

		 if (multiSearch->ItemCount()!=2)
			 {
			 succeed=EFalse;
			 }
		 delete multiSearch;
		 if (succeed==EFalse)
			 {
			 break;
			 }
		}
	TEST(succeed);	
	}
