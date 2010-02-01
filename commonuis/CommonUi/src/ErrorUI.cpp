/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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

#include    <AknGlobalNote.h>
#include    <AknGlobalConfirmationQuery.h>
#include    "ErrorUI.h"
#include    <avkon.rsg>

EXPORT_C CErrorUI* CErrorUI::NewL()
    {
    CErrorUI* me;
    me = ConstructLC();
    CleanupStack::Pop();
    return me;
    }

EXPORT_C CErrorUI* CErrorUI::NewLC()
    {
    return ConstructLC();
    }



CErrorUI* CErrorUI::ConstructLC()
    {
    CErrorUI* me;
    me = new (ELeave) CErrorUI();
    CleanupStack::PushL(me);
    me->ConstructL();
    return me;  
    }

EXPORT_C CErrorUI* CErrorUI::NewL(CCoeEnv& aEnv)
    {
    CErrorUI* me = CErrorUI::NewLC(aEnv);
    CleanupStack::Pop();
    return me;
    }

EXPORT_C CErrorUI* CErrorUI::NewLC(CCoeEnv& /*aEnv*/)
    {
    CErrorUI* me;
    me = new (ELeave) CErrorUI();
    CleanupStack::PushL(me);
    me->ConstructL();
    return me;
    }

EXPORT_C CErrorUI::~CErrorUI()
    { 
    delete iTextResolver;
    }

EXPORT_C TBool CErrorUI::ShowGlobalErrorNoteL
        (
        TInt aError,
        CTextResolver::TErrorContext Context
        )
    {
    
    TInt resourceID = 0;
    TUint flags = 0;
    TPtrC errorstring = iTextResolver->ResolveErrorString(aError,resourceID,flags,Context);
    if ( !(flags & ETextResolverBlankErrorFlag) )
        {
        CAknGlobalNote * note1 = CAknGlobalNote::NewL();
        CleanupStack::PushL(note1);
        if ( aError == KErrDiskFull ) 
            {
            note1->SetSoftkeys(R_AVKON_SOFTKEYS_OK_EMPTY);
            }
        note1->ShowNoteL( EAknGlobalErrorNote, (TDesC&)errorstring );

        CleanupStack::PopAndDestroy();  // note1
        return ETrue;
        }
        
    return EFalse;
    }

EXPORT_C TBool CErrorUI::ShowGlobalErrorQueryL(TInt aError, CTextResolver::TErrorContext Context)
    { 
    // Copy-Paste code, but I see no sense in creating two internal methods to save two rows code.
    TInt resourceID = 0;
    TUint flags = 0;
    TPtrC errorstring = iTextResolver->ResolveErrorString(aError,resourceID,flags,Context);
    if ( !(flags & ETextResolverBlankErrorFlag) )
        {
        CAknGlobalNote * note1 = CAknGlobalNote::NewL();
        CleanupStack::PushL(note1);
        
        note1->SetSoftkeys(R_AVKON_SOFTKEYS_OK_EMPTY);
        note1->ShowNoteL( EAknGlobalErrorNote, (TDesC&)errorstring );

        CleanupStack::PopAndDestroy();  // note1
        return ETrue;
        }
        
    return EFalse;
    }

void CErrorUI::ConstructL()
    {
    iTextResolver = CTextResolver::NewL();
    }


// End of File
