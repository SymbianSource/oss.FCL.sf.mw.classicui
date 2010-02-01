/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
#include <Aknnumseced.h>
#include <AknPanic.h>
#include <barsread.h>
#include <eikenv.h>
#include <aknedsts.h>
#include <gulcolor.h>

#define KSecretChar '*'
#define KSecretCharAsString "*"



// ----------------------------------------------------------------------------
// CAknNumericSecretEditor::CAknNumericSecretEditor()
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNumericSecretEditor::CAknNumericSecretEditor()
    {
    }

CAknNumericSecretEditor::~CAknNumericSecretEditor()
    {
    }

EXPORT_C void CAknNumericSecretEditor::AppendCharacterL( TInt aKeyCode )
    {
    CEikSecretEditor::AppendCharacterL( aKeyCode );
    }

// ----------------------------------------------------------------------------
// CAknNumericSecretEditor::InputCapabilities() const
// Sets the TCoeInputCapabilities.
// ----------------------------------------------------------------------------
//
EXPORT_C TCoeInputCapabilities CAknNumericSecretEditor::InputCapabilities() const
    {
    TCoeInputCapabilities inputCaps( 
        TCoeInputCapabilities::EWesternNumericIntegerPositive|
        TCoeInputCapabilities::ESecretText|
        TCoeInputCapabilities::ENavigation,
        const_cast<CAknNumericSecretEditor*>( this ),
        NULL );
        
    inputCaps.SetObjectProvider( 
        CEikSecretEditor::InputCapabilities().ObjectProvider() );
    
    return inputCaps;
    }

EXPORT_C MCoeFepAwareTextEditor_Extension1::CState* CAknNumericSecretEditor::CreateFepStateL()
    {
    CAknEdwinState* editorState = new(ELeave) CAknEdwinState();
        
    editorState->SetFlags(EAknEditorFlagNoLRNavigation | EAknEditorFlagNoT9 | EAknEditorFlagLatinInputModesOnly);
    editorState->SetDefaultInputMode(EAknEditorNumericInputMode);
    editorState->SetCurrentInputMode(EAknEditorNumericInputMode);
    editorState->SetPermittedInputModes(EAknEditorNumericInputMode);
    editorState->SetDefaultCase(EAknEditorLowerCase);
    editorState->SetCurrentCase(EAknEditorLowerCase);
    editorState->SetPermittedCases(EAknEditorLowerCase|EAknEditorUpperCase);
    editorState->SetSpecialCharacterTableResourceId(0);
    editorState->SetNumericKeymap(EAknEditorPlainNumberModeKeymap);
	editorState->SetObjectProvider(this);

    return editorState;
    }

EXPORT_C void CAknNumericSecretEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikSecretEditor::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknNumericSecretEditor::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknNumericSecretEditor::Reserved_1()
    {}

// ----------------------------------------------------------------------------
// CAknNumericSecretEditor::Reserved_2()
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknNumericSecretEditor::Reserved_2()
    {}


EXPORT_C void CAknNumericSecretEditor::MCoeFepAwareTextEditor_Reserved_2()
	{
	}

EXPORT_C void CAknNumericSecretEditor::MCoeFepAwareTextEditor_Extension1_Reserved_2()
	{
	}

EXPORT_C void CAknNumericSecretEditor::MCoeFepAwareTextEditor_Extension1_Reserved_3()
	{
	}

EXPORT_C void CAknNumericSecretEditor::MCoeFepAwareTextEditor_Extension1_Reserved_4()
	{
	}

//  End of File  
