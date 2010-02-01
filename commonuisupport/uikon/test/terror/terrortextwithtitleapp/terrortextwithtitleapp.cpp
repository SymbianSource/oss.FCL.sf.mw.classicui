// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "terrortextwithtitleapp.h"
#include <textresolver.h>
#include <errorres.rsg>

const TInt KTErrorContextFailure = -1122;	// random test failure

// CErrorTextWithTitleAppUi
CErrorTextWithTitleAppUi::CErrorTextWithTitleAppUi() : CTestAppUi(NULL, KNullDesC)
  {
  }

void CErrorTextWithTitleAppUi::ConstructL()
    {
   	CTestAppUi::ConstructL();
	// auto start for the tests
	AutoTestManager().StartAutoTest();
	}

CErrorTextWithTitleAppUi::~CErrorTextWithTitleAppUi()
	{
	}

void CErrorTextWithTitleAppUi::RunTestStepL(TInt aNumStep)
	{
	RDebug::Print(_L("CErrorTextWithTitleAppUi::RunTestStepL with aNumStep=%d."), aNumStep);
	__UHEAP_MARK;
	switch(aNumStep)
		{
		case 1:
			{
			// Test simple
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv);      
            TPtrC buf(textResolver->ResolveErrorString(-64001));
			buf.Set(textResolver->ResolveErrorString(-64001));	// Call twice to look for leaks
            if(buf.Compare(_L("TestApp:\nShort error text, within normal limits")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
 			
            // Test simple without CoeEnv
            textResolver = CTextResolver::NewLC(); 
            buf.Set(textResolver->ResolveErrorString(-64001));
            buf.Set(textResolver->ResolveErrorString(-64001));	// Call twice to look for leaks
			if(buf.Compare(_L("TestApp:\nShort error text, within normal limits")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
			CleanupStack::PopAndDestroy(textResolver);
            }               
            break;
        
        case 2:
            {
 		    // Test long error
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv); 
            TPtrC buf(textResolver->ResolveErrorString(-64002));
			if(buf.Compare( _L("TestApp:\nLong error text. 400+ characters.            |<- 50 characters . . . . . . . . . . . . . . . . |<- 100 characters . . . . . . . . . . . . . . . .|<- 150 characters . . . . . . . . . . . . . . . .|<- 200 characters . . . . . . . . . . . . . . . .|<- 250 characters . . . . . . . . . . . . . . . .|<- 300 characters . . . . . . . . . . . . . . . .|<- 350 characters . . . . . . . . . . . . . . . .|<- 400 characters . . . . . . . . . . . . . . . .|<- 450 characters . . . . . . . . . . . . . . . .")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            // Test long error without CoeEnv
            textResolver = CTextResolver::NewLC();            
            buf.Set(textResolver->ResolveErrorString(-64002));
			if(buf.Compare( _L("TestApp:\nLong error text. 400+ characters.            |<- 50 characters . . . . . . . . . . . . . . . . |<- 100 characters . . . . . . . . . . . . . . . .|<- 150 characters . . . . . . . . . . . . . . . .|<- 200 characters . . . . . . . . . . . . . . . .|<- 250 characters . . . . . . . . . . . . . . . .|<- 300 characters . . . . . . . . . . . . . . . .|<- 350 characters . . . . . . . . . . . . . . . .|<- 400 characters . . . . . . . . . . . . . . . .|<- 450 characters . . . . . . . . . . . . . . . .")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
          	}
            break;
        
        case 3:
            {
            // Test very long error
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv); 
            TPtrC buf(textResolver->ResolveErrorString(-64003));
            if(buf.Compare(_L("TestApp:\nVery long error text. ~1000 characters. 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            // Test very long error without CoeEnv
            textResolver = CTextResolver::NewLC(); 
            buf.Set(textResolver->ResolveErrorString(-64003));
            if(buf.Compare(_L("TestApp:\nVery long error text. ~1000 characters. 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
        
        case 4:
            {
            // Test long appname
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv); 
            TPtrC buf(textResolver->ResolveErrorString(-65001));
            if(buf.Compare(_L("Long test application name. Very long indeed. Can't believe it's this long, really.:\nShort error text, within normal limits. Second edition.")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            // Test long appname without CoeEnv
            textResolver = CTextResolver::NewLC(); 
            buf.Set(textResolver->ResolveErrorString(-65001));
            if(buf.Compare(_L("Long test application name. Very long indeed. Can't believe it's this long, really.:\nShort error text, within normal limits. Second edition.")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
        
        case 5:
            {
             // Test CTextResolver reuse
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv);            
            TPtrC buf(textResolver->ResolveErrorString(-64001));
            if(buf.Compare(_L("TestApp:\nShort error text, within normal limits")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            buf.Set(textResolver->ResolveErrorString(-64002));
            if(buf.Compare(_L("TestApp:\nLong error text. 400+ characters.            |<- 50 characters . . . . . . . . . . . . . . . . |<- 100 characters . . . . . . . . . . . . . . . .|<- 150 characters . . . . . . . . . . . . . . . .|<- 200 characters . . . . . . . . . . . . . . . .|<- 250 characters . . . . . . . . . . . . . . . .|<- 300 characters . . . . . . . . . . . . . . . .|<- 350 characters . . . . . . . . . . . . . . . .|<- 400 characters . . . . . . . . . . . . . . . .|<- 450 characters . . . . . . . . . . . . . . . .")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            buf.Set(textResolver->ResolveErrorString(-64003));
            if(buf.Compare(_L("TestApp:\nVery long error text. ~1000 characters. 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            buf.Set(textResolver->ResolveErrorString(-65001));
            if(buf.Compare(_L("Long test application name. Very long indeed. Can't believe it's this long, really.:\nShort error text, within normal limits. Second edition.")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
		    CleanupStack::PopAndDestroy(textResolver);

            // Test reuse without CoeEnv
            textResolver = CTextResolver::NewLC(); 
            buf.Set(textResolver->ResolveErrorString(-64001));
            if(buf.Compare(_L("TestApp:\nShort error text, within normal limits")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            buf.Set(textResolver->ResolveErrorString(-64002));
            if(buf.Compare(_L("TestApp:\nLong error text. 400+ characters.            |<- 50 characters . . . . . . . . . . . . . . . . |<- 100 characters . . . . . . . . . . . . . . . .|<- 150 characters . . . . . . . . . . . . . . . .|<- 200 characters . . . . . . . . . . . . . . . .|<- 250 characters . . . . . . . . . . . . . . . .|<- 300 characters . . . . . . . . . . . . . . . .|<- 350 characters . . . . . . . . . . . . . . . .|<- 400 characters . . . . . . . . . . . . . . . .|<- 450 characters . . . . . . . . . . . . . . . .")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            buf.Set(textResolver->ResolveErrorString(-64003));
            if(buf.Compare(_L("TestApp:\nVery long error text. ~1000 characters. 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            buf.Set(textResolver->ResolveErrorString(-65001));
            if(buf.Compare(_L("Long test application name. Very long indeed. Can't believe it's this long, really.:\nShort error text, within normal limits. Second edition.")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
		    CleanupStack::PopAndDestroy(textResolver);
            }
            break;
        
        case 6:
            {
            // Test unlimited long appname
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv); 
			TPtrC buf(textResolver->ResolveErrorString(-65001));

            if(buf.Compare(_L("Long test application name. Very long indeed. Can't believe it's this long, really.:\nShort error text, within normal limits. Second edition.")))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            // Test long appname without CoeEnv
            textResolver = CTextResolver::NewLC(); 
            buf.Set(textResolver->ResolveErrorString(-65001));
            if(buf.Compare(_L("Long test application name. Very long indeed. Can't believe it's this long, really.:\nShort error text, within normal limits. Second edition.")))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
       
       case 7:
            {
            // Test no context
            CTextResolver* textResolver = CTextResolver::NewLC(); 
            TInt textId;
            TUint flags;
            TPtrC buf(textResolver->ResolveErrorString(-64001, textId, flags, CTextResolver::ECtxNoCtx));
            if(buf.Compare(_L(":\nShort error text, within normal limits")) || !(flags == 0))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
        
        case 8:
            {
            // Test empty string
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv);
            TInt textId;
            TUint flags;
            TPtrC buf(textResolver->ResolveErrorString(-64004, textId, flags, CTextResolver::ECtxNoCtx));
            if(buf.Compare(_L(":\n")) || !(flags == 0))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            // Test empty string without CoeEnv
            textResolver = CTextResolver::NewLC();
            buf.Set(textResolver->ResolveErrorString(-64004, textId, flags, CTextResolver::ECtxNoCtx));
            if(buf.Compare(_L(":\n")) || !(flags == 0))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
   		
   		case 9:
            {
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv);
            TInt textId;
            TUint flags;
          	TPtrC buf(textResolver->ResolveErrorString(-12004, textId, flags));
            if(buf.Compare(_L("")) || !(flags == 10))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            
            textResolver = CTextResolver::NewLC();
          	buf.Set(textResolver->ResolveErrorString(-12004, textId, flags));
            if(buf.Compare(_L("")) || !(flags == 10))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
       
       case 10:
            {
            // Test out of memory string
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv); 
            TInt textId;
            TUint flags;
            TPtrC buf(textResolver->ResolveErrorString(KErrNoMemory, textId, flags, CTextResolver::ECtxNoCtx));
            if(!(textId == R_ERROR_RES_NO_MEMORY) || !(flags == 0))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, textId contained '%d'."), textId);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            // Test out of memory string without CoeEnv
            textResolver = CTextResolver::NewLC(); 
            buf.Set(textResolver->ResolveErrorString(KErrNoMemory, textId, flags, CTextResolver::ECtxNoCtx));
            if(!(textId == R_ERROR_RES_NO_MEMORY) || !(flags == 0))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, textId contained '%d'."), textId);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
       
       case 11:
            {
            // Test the error In Use
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv); 
            
            TInt textId;
            TUint flags;
            TPtrC buf(textResolver->ResolveErrorString(-14, textId, flags, CTextResolver::ECtxNoCtx));

            if(buf.Compare(_L(":\nRequested object is used by another application")) || !(textId == R_ERROR_RES_IN_USE) || !(flags == 0))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            // Test the error In Use without CoeEnv
            textResolver = CTextResolver::NewLC();
            buf.Set(textResolver->ResolveErrorString(-14, textId, flags, CTextResolver::ECtxNoCtx));
            if(buf.Compare(_L(":\nRequested object is used by another application")) || !(textId == R_ERROR_RES_IN_USE) || !(flags == 0))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
       
       case 12:
            {
            // Test Unknown error
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv); 
            TInt textId;
            TUint flags;
            TPtrC buf(textResolver->ResolveErrorString(-34, textId, flags));
            if(buf.Compare(_L("System:\nSystem error.")) || !(textId == R_ERROR_RES_GENERAL) || !(flags == 6))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            // Test Unknown error without CoeEnv
            textResolver = CTextResolver::NewLC(); 
            buf.Set(textResolver->ResolveErrorString(-34, textId, flags));
            if(buf.Compare(_L("System:\nSystem error.")) || !(textId == R_ERROR_RES_GENERAL) || !(flags == 6))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
            }
            break;
       
       case 13:
            {
            CTextResolver* textResolver = CTextResolver::NewLC(*iCoeEnv);
            TInt textId;
            TUint flags;
          	TPtrC buf(textResolver->ResolveErrorString(-12008, textId, flags));
            if(buf.Compare(_L("System:\nSystem error.")) || !(flags == 6))
				{
				RDebug::Print(_L("Check (with CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);

            textResolver = CTextResolver::NewLC();
          	buf.Set(textResolver->ResolveErrorString(-12008, textId, flags));
            if(buf.Compare(_L("System:\nSystem error.")) || !(flags == 6))
				{
				RDebug::Print(_L("Check (without CoeEnv) failed, buf contained '%S'."), &buf);
				RProcess().Terminate(KTErrorContextFailure);
				}
            CleanupStack::PopAndDestroy(textResolver);
			}
			break;
 		
 		case 14:
			{
            // Test error resolving with memory allocation failure in 1 to n allocations
            TPtrC buf;
            TInt textId;
            TUint flags=0;
			TBool loop=ETrue;
			CTextResolver* textResolver = NULL;
			
            for (TInt fail = 1; loop; fail++)
            	{
  				__UHEAP_SETFAIL(RHeap::EDeterministic, fail);
                __UHEAP_MARK;          	

            	TRAPD(error, textResolver = CTextResolver::NewL(*iCoeEnv));
            	if (error != KErrNone)
            		{
	                __UHEAP_MARKEND;
	                __UHEAP_RESET;        	
            		continue;
            		}

                __UHEAP_RESET;        	
            	buf.Set(textResolver->ResolveErrorString(-64002, textId, flags));
				if (!(flags & EErrorResOOMFlag) && buf.Compare( _L("TestApp:\nLong error text. 400+ characters.            |<- 50 characters . . . . . . . . . . . . . . . . |<- 100 characters . . . . . . . . . . . . . . . .|<- 150 characters . . . . . . . . . . . . . . . .|<- 200 characters . . . . . . . . . . . . . . . .|<- 250 characters . . . . . . . . . . . . . . . .|<- 300 characters . . . . . . . . . . . . . . . .|<- 350 characters . . . . . . . . . . . . . . . .|<- 400 characters . . . . . . . . . . . . . . . .|<- 450 characters . . . . . . . . . . . . . . . .")) != 0)
					{
					RProcess().Terminate(KTErrorContextFailure);
					}
				delete textResolver;
				loop=EFalse;
            	__UHEAP_MARKEND;
                }
            }
            break;
       
       default:
        	AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	__UHEAP_MARKEND;			
	}

// CErrorTextWithTitleDocument
CErrorTextWithTitleDocument::CErrorTextWithTitleDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CErrorTextWithTitleDocument::CreateAppUiL()
	{
	return new (ELeave) CErrorTextWithTitleAppUi();
    }

// CErrorTextWithTitleApplication
TUid CErrorTextWithTitleApplication::AppDllUid() const
	{
	return KUidErrorContextApp;
	}

CApaDocument* CErrorTextWithTitleApplication::CreateDocumentL()
	{
	return new (ELeave) CErrorTextWithTitleDocument(*this);
	}

LOCAL_C CApaApplication* NewApplication()
	{
	return new CErrorTextWithTitleApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

