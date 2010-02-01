/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/


// INCLUDE FILES
#include    <aknnotewrappers.h>
#include    <documenthandlerui.rsg>    // Resource ids
#include    "DocSaver.h"
#include    "DocumentHandlerUI.hrh"
#include    "DocDefaultHandler.h"


// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES  

// CONSTANTS

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// ==================== LOCAL FUNCTIONS ====================

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CDocSaver::CDocSaver()
    {
    }

// EPOC default constructor can leave.
void CDocSaver::ConstructL()
    {
    }

// Two-phased constructor.
CDocSaver* CDocSaver::NewL()
    {
    CDocSaver* self = new (ELeave) CDocSaver;
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// Destructor
CDocSaver::~CDocSaver()
    {    
    }

// ---------------------------------------------------------
// CDocSaver::ConfNoteL
// "File saved to SomeApplication" confirmation note.
// 
// ---------------------------------------------------------
//
void CDocSaver::ConfNoteL( const TDesC& aText, TBool aWait )
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocSaver::ConfNoteL: Called"));
    #endif 
    CAknConfirmationNote* myNote = new ( ELeave ) CAknConfirmationNote( aWait );

    myNote->ExecuteLD( aText );
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocSaver::ConfNoteL: Returns"));
    #endif 
    }


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//


// CDocWaitDialog
// ----------------------------------------------------------------

CDocWaitDialog::CDocWaitDialog(
    CEikDialog** aSelfPtr,
    const TDesC& aText): 
    CAknWaitDialog(aSelfPtr, EFalse),
    iText(aText), 
    iFinished(EFalse)                               
    {
    }
// ---------------------------------------------------------
// CDocWaitDialog::ExecuteDlgLD()
// 
// 
// ---------------------------------------------------------
//
TInt CDocWaitDialog::ExecuteDlgLD()
    {
    PrepareLC(R_DOCHANDLER_WAIT_NOTE);
    SetTextL( iText );
    TInt ret = RunDlgLD(CAknNoteDialog::ENoTone);
    return ret;
    }

// ---------------------------------------------------------
// CDocWaitDialog::Finish()
// 
// 
// ---------------------------------------------------------
//
TBool CDocWaitDialog::Finish()
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocWaitDialog::Finish: Called"));
    #endif 
    TBool state = ETrue;
    if (iState == EProcessOnDisplayOff)
        {
        iProgressDialogTimer->Cancel();
        state = EFalse;
        iFinished = ETrue;
        }
    TRAP_IGNORE( ProcessFinishedL() );
    #ifdef _DEBUG 
    if (state)
        {
        RDebug::Print( _L("DocumentHandler: CDocWaitDialog::Finish: state=ETRUE"));
        }   
    else 
        {
        RDebug::Print( _L("DocumentHandler: CDocWaitDialog::Finish: state=EFALSE"));
        }
    #endif 
    return state;
    }


// CDocAsyncSaver
// ----------------------------------------------------------------
// C++ default constructor can NOT contain any code, that
// might leave.
//

CDocAsyncSaver::CDocAsyncSaver():
    CActive(EPriorityStandard), 
    iShowDialog(EFalse), 
    iSilent(EFalse)
    {
    }

// EPOC default constructor can leave.
void CDocAsyncSaver::ConstructL()
    {
    
    }

// Two-phased constructor.
CDocAsyncSaver* CDocAsyncSaver::NewL()
    {
    CDocAsyncSaver* self = NewLC();
    CleanupStack::Pop();

    return self;
    }

CDocAsyncSaver* CDocAsyncSaver::NewLC()
    {
    CDocAsyncSaver* self = new (ELeave) CDocAsyncSaver();
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CActiveScheduler::Add(self);
    
    return self;
    }

    
// Destructor
CDocAsyncSaver::~CDocAsyncSaver()
    {
    if (iDocWaitDialog)
        {
        delete iDocWaitDialog;
        iDocWaitDialog = NULL;
        }
    Cancel();
    Deque();
    }
// ---------------------------------------------------------
// CDocAsyncSaver::WriteToFileL()
// 
// 
// ---------------------------------------------------------
//
void CDocAsyncSaver::WriteToFileL(
    const TDesC8& aContent, 
    RFile& aDestFile,
    const TDesC& aText )
    {
    iDocWaitDialog = 
        new (ELeave) CDocWaitDialog(
            ( REINTERPRET_CAST(
                CEikDialog**,
                &iDocWaitDialog ) ), 
            aText );
    iDocWaitDialog->ExecuteDlgLD();
    aDestFile.Write( aContent, iStatus );
    SetActive();
    iWait.Start();  
    
    }

// ---------------------------------------------------------
// CDocAsyncSaver::CopyFileL()
// 
// 
// ---------------------------------------------------------
//
void CDocAsyncSaver::CopyFileL(
    CFileMan* aFileManager, 
    const TFileName& aSourceFile,
    const TFileName& aDestFile,
    TUint aSwitch,
    const TDesC& aText )
    {
    iDocWaitDialog = 
        new (ELeave) CDocWaitDialog(
            ( REINTERPRET_CAST(
                CEikDialog**,
                &iDocWaitDialog ) ), 
            aText );
    iDocWaitDialog->ExecuteDlgLD();

    TInt error = 
        aFileManager->Copy( 
            aSourceFile, 
            aDestFile, 
            aSwitch, 
            iStatus );

    if ( error != KErrNone )
        {
        iStatus = error;
        iDocWaitDialog->Finish();
        }
    else
        {        
        SetActive();
        iWait.Start();
        }
    }

// ---------------------------------------------------------
// CDocAsyncSaver::CopyFileL()
// 
// 
// ---------------------------------------------------------
//
void CDocAsyncSaver::CopyFileL(
    CFileMan* aFileManager, 
    const RFile& aSourceFile,
    const TFileName& aDestFile,
    TUint aSwitch,
    const TDesC& aText )
    {
    iDocWaitDialog = 
        new (ELeave) CDocWaitDialog(
            ( REINTERPRET_CAST(
                CEikDialog**,
                &iDocWaitDialog ) ), 
            aText );
    iDocWaitDialog->ExecuteDlgLD();

    TInt error = 
        aFileManager->Copy(
            aSourceFile, 
            aDestFile, 
            aSwitch, 
            iStatus );

    if ( error != KErrNone )
        {
        iStatus = error;
        iDocWaitDialog->Finish();
        }
    else
        {        
        SetActive();
        iWait.Start();
        }
    }

// ---------------------------------------------------------
// CDocAsyncSaver::MoveFileL()
// 
// 
// ---------------------------------------------------------
//
void CDocAsyncSaver::MoveFileL(
    CFileMan* aFileManager, 
    const TFileName& aSourceFile,
    const TFileName& aDestFile,
    TUint aSwitch,
    const TDesC& aText,
    const TBool aSilent )
    {
    iSilent = aSilent;
    if (!iSilent)
        {
        iDocWaitDialog = 
            new (ELeave) CDocWaitDialog(
                ( REINTERPRET_CAST(
                    CEikDialog**,
                    &iDocWaitDialog ) ), 
                aText );
        iDocWaitDialog->ExecuteDlgLD();
        }

    TInt error = 
        aFileManager->Move(
            aSourceFile,
            aDestFile, 
            aSwitch, 
            iStatus );
    if ( error != KErrNone )
        {
        iStatus = error;
        if (!iSilent)
            {
            iDocWaitDialog->Finish();
            }
        }
    else
        {        
        SetActive();
        iWait.Start();
        }
    }

// ---------------------------------------------------------
// CDocAsyncSaver::Status()
// 
// 
// ---------------------------------------------------------
//
TRequestStatus CDocAsyncSaver::Status()
    {
    return iStatus;
    }

// ---------------------------------------------------------
// CDocAsyncSaver::ShowDialog()
// 
// 
// ---------------------------------------------------------
//
TBool CDocAsyncSaver::ShowDialog()
    {
    #ifdef _DEBUG        
    RDebug::Print( _L("DocumentHandler: CDocAsyncSaver::ShowDialog: Called"));
    #endif 
    iShowDialog = EFalse;
    if (iSilent)
        {
        iShowDialog = EFalse;
        }
    else if (!iDocWaitDialog->Finish())
        {
        iShowDialog = ETrue;
        #ifdef _DEBUG        
        RDebug::Print( _L("DocumentHandler: CDocAsyncSaver::ShowDialog: Returns ETRUE"));
        #endif 
        }
    return iShowDialog;
    }
// ---------------------------------------------------------
// CDocAsyncSaver::RunL()
// 
// 
// ---------------------------------------------------------
//
void CDocAsyncSaver::RunL()
    {   
    iWait.AsyncStop(); 
    }


// ---------------------------------------------------------
// CDocAsyncSaver::DoCancel()
// 
// 
// ---------------------------------------------------------
//
void CDocAsyncSaver::DoCancel()
    {
    }

//  End of File  
