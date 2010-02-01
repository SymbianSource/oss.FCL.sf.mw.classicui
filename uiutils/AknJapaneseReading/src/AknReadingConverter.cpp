/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


// INCLUDE FILES
#include "AknReadingConverter.h"
#include "AknJapaneseReading.h"
#include "eikedwin.h"
// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES


// ============================ MEMBER FUNCTIONS ===============================

inline CReadingConverter::CReadingConverter(CEikEdwin* aMainEditor,
                                     CEikEdwin* aReadingEditor) :
        iMainEditor(aMainEditor),
        iReadingEditor(aReadingEditor)
    {
    }

inline void CReadingConverter::ConstructL()
    {
    CCoeEnv::Static()->AddFepObserverL(*this);
    }

EXPORT_C CReadingConverter* CReadingConverter::NewL(CEikEdwin& aMainEditor,
                                                    CEikEdwin& aReadingEditor)
    {
    CReadingConverter* self =
        new (ELeave) CReadingConverter( &aMainEditor, &aReadingEditor );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

EXPORT_C CReadingConverter* CReadingConverter::NewL()
    {
    CReadingConverter* self =
        new (ELeave) CReadingConverter( NULL, NULL );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CReadingConverter::~CReadingConverter()
    {
    delete iPreviousMainText;
    CCoeEnv::Static()->RemoveFepObserver(*this);
    }

EXPORT_C void CReadingConverter::HandleCompletionOfTransactionL()
    {
    if (iMainEditor && iReadingEditor)
        {
        if (iMainEditor->IsFocused())
            {
            TPtrC ptr = CAknJapaneseReading::ReadingTextL();
            TInt newTextLength = ptr.Length();
            if (newTextLength > 0)
                {
                TBool appendReading = ETrue;
                if (iPreviousMainText)
                    {
                    HBufC* currentMainText = iMainEditor->GetTextInHBufL();
                    if (currentMainText)
                        {
                        CleanupStack::PushL(currentMainText);
                        if (currentMainText->Compare(*iPreviousMainText) == 0)
                            {
                            // If there is no differences between previous main test
                            // and current its, there is nothing to append to Reading
                            // field.
                            appendReading = EFalse;
                            }
                        CleanupStack::PopAndDestroy(currentMainText); // currentMainText
                        }
                    else
                        {
                        // No buffer on Main editor in case of T9 insert word.
                        appendReading = EFalse;
                        }
                    }

                if (appendReading)
                    {
                    TInt maxLength = iReadingEditor->MaxLength();
                    TInt oldTextLength = iReadingEditor->TextLength();
                    if ((maxLength > 0) && (maxLength < oldTextLength + newTextLength))
                        {
                        newTextLength = maxLength - oldTextLength;
                        }
                    HBufC* text = HBufC::NewLC(oldTextLength + newTextLength);
                    TPtr textPtr = text->Des();
                    iReadingEditor->GetText(textPtr);
                    textPtr.Append(ptr.Ptr(), newTextLength);
                    iReadingEditor->SetTextL(text);
                    CleanupStack::PopAndDestroy(text);
                    iReadingEditor->DrawNow();
                    // send EEventStateChanged event to observer
                    iReadingEditor->UpdateAllFieldsL();

                    // Save current main editor text
                    delete iPreviousMainText;
                    iPreviousMainText = NULL;
                    iPreviousMainText = HBufC::NewL(iMainEditor->TextLength());
                    TPtr prev = iPreviousMainText->Des();
                    iMainEditor->GetText(prev);
                    }
                }
            else
                {
                if (iMainEditor->TextLength() == 0)
                    {
                    iReadingEditor->SetTextL(&KNullDesC);
                    iReadingEditor->DrawNow();
                    // send EEventStateChanged event to observer
                    iReadingEditor->UpdateAllFieldsL();
                    delete iPreviousMainText;
                    iPreviousMainText = NULL;
                    }
                }
            }
        }
    }

EXPORT_C void CReadingConverter::SetMainEditor(CEikEdwin& aMainEditor)
    {
    iMainEditor = &aMainEditor;
    }

EXPORT_C CEikEdwin& CReadingConverter::MainEditor() const
    {
    return *iMainEditor;
    }

EXPORT_C void CReadingConverter::SetReadingEditor(CEikEdwin& aReadingEditor)
    {
    iReadingEditor = &aReadingEditor;
    }

EXPORT_C CEikEdwin& CReadingConverter::ReadingEditor() const
    {
    return *iReadingEditor;
    }

