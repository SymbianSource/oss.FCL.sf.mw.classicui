/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utility class that verifies content's that it is in accordance 
*                with DRM.
*
*/


// INCLUDE FILES
#include <DRMHelper.h>
#include <aknnotewrappers.h>
#include <StringLoader.h>
#include <psln.rsg>

#include "PslnDRMImplementation.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnDRMImplementation::CPslnDRMImplementation()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnDRMImplementation::ConstructL()
    {
    iDRMHelper = CDRMHelper::NewL(*CCoeEnv::Static());
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnDRMImplementation* CPslnDRMImplementation::NewL()
    {
    CPslnDRMImplementation* self = new(ELeave) CPslnDRMImplementation();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CPslnDRMImplementation::~CPslnDRMImplementation()
    {
    delete iDRMHelper;
    }

// -----------------------------------------------------------------------------
// CPslnDRMImplementation::VerifySelectionL
// -----------------------------------------------------------------------------
//
TBool CPslnDRMImplementation::VerifySelectionL(const MDesCArray* aSelectedFiles)
    {
    if(!aSelectedFiles)
    	{
    	User::Leave(KErrArgument);    	
    	}
    
    if(aSelectedFiles->MdcaCount() == 0)
        {
        return ETrue;
        }

    User::LeaveIfError(iDRMHelper->SetAutomatedType(CDRMHelper::EAutomatedTypeWallpaper));

    TBool canBeAutomated = EFalse;
    TInt error = iDRMHelper->CanSetAutomated(aSelectedFiles->MdcaPoint(0), canBeAutomated);
    
    if(error == KErrNone)
    	{
    	if(!canBeAutomated)
    		{
		    ShowErrorNoteL( R_PSLN_QTN_DRM_PREV_RIGHTS_SET );
    		}
    		
    	return canBeAutomated;
    	}
    else if( error == KErrUnderflow )
        {
        ShowErrorNoteL( R_PSLN_IMAGE_CORRUPTED );
        }
    else if ( ( error != KErrNone ) || !canBeAutomated )
        {
        if ( iDRMHelper )
            {
            iDRMHelper->HandleErrorL(
                        error, 
                        aSelectedFiles->MdcaPoint( 0 ) );
            }
        }

    return EFalse;
    }
    
// -----------------------------------------------------------------------------
// CPslnDRMImplementation::ShowErrorNoteL
// -----------------------------------------------------------------------------
//
void CPslnDRMImplementation::ShowErrorNoteL( TInt  aResourceId  ) 
    {
    HBufC* errorText = StringLoader::LoadLC(aResourceId);
    CAknInformationNote* note = new(ELeave) CAknInformationNote(EFalse);
    note->ExecuteLD(*errorText);
    CleanupStack::PopAndDestroy(errorText);
    }
// End of File
