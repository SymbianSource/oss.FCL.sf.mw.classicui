/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  DRM Verifier for slide set image sets.
*
*/


// INCLUDE FILES
#include "pslnslidesetdrmverifier.h"
#include <pslnslidesetdialogrsc.rsg>
#include <pslnslidesetdialoginterface.h>

#include <DRMHelper.h>
#include <aknnotewrappers.h>
#include <StringLoader.h>

const TInt KPslnDrmVerifyLimit = 50;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnSlideSetDRMVerifier::CPslnSlideSetDRMVerifier(  TInt aType  ) 
    : iType ( aType )
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnSlideSetDRMVerifier::ConstructL()
    {
    iDRMHelper = CDRMHelper::NewL( *CCoeEnv::Static() );
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnSlideSetDRMVerifier* CPslnSlideSetDRMVerifier::NewL( TInt aType )
    {
    CPslnSlideSetDRMVerifier* self = 
        new( ELeave ) CPslnSlideSetDRMVerifier( aType );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// Destructor.
// -----------------------------------------------------------------------------
//
CPslnSlideSetDRMVerifier::~CPslnSlideSetDRMVerifier()
    {
    delete iDRMHelper;
    }

// -----------------------------------------------------------------------------
// Verifies user selected images. Used by MGFetch.
// -----------------------------------------------------------------------------
//
TBool CPslnSlideSetDRMVerifier::VerifySelectionL( const MDesCArray* aSelectedFiles )
    {
    if ( aSelectedFiles )
        {
        if( aSelectedFiles->MdcaCount() < 1 )
            {
            // Download item
            return ETrue;
            }
        }
    else
        {
        // no aSelectedFiles.
        return EFalse;
        }

    TInt res = KErrNone;
    TBool canBeAutomated = EFalse;
    if ( iDRMHelper )
        {
        if ( iType == EPslnWallpaperDialog )
            {            
            res = iDRMHelper->SetAutomatedType( 
                CDRMHelper::EAutomatedTypeWallpaper );
            }
        else
            {
            res = iDRMHelper->SetAutomatedType( 
                CDRMHelper::EAutomatedTypeScreenSaver );
            }
        if ( res != KErrNone )
            {
            ShowErrorNoteL( R_PSLN_SLIDE_SET_DRM_ERROR );
            }
        else
            {
            // Go through the selected files.
            TInt fileCount = aSelectedFiles->MdcaCount() - 1;
            if ( fileCount > KPslnDrmVerifyLimit )
                {
                fileCount = KPslnDrmVerifyLimit;
                }
            for ( TInt index = fileCount; index >= 0; index-- )
                {
                // First check DRM issues.
                res = iDRMHelper->CanSetAutomated(
                    aSelectedFiles->MdcaPoint( index ),
                    canBeAutomated );
                if ( !res && !canBeAutomated )
                    {
                    ShowErrorNoteL( R_PSLN_SLIDE_SET_DRM_ERROR );
                    }
                else if( res == KErrUnderflow )
                    {
                    ShowErrorNoteL( R_PSLN_SLIDE_SET_IMAGE_CORRUPTED );
                    }
                else if ( ( res != KErrNone ) || !canBeAutomated )
                    {
                    if ( iDRMHelper )
                        {
                        iDRMHelper->HandleErrorL(
                            res, 
                            aSelectedFiles->MdcaPoint( index ) );
                        }
                    }
                else
                    {
                    // Empty.
                    }
                }
            }
        }
    return canBeAutomated;
    }

// -----------------------------------------------------------------------------
// Shows error note.
// -----------------------------------------------------------------------------
//
void CPslnSlideSetDRMVerifier::ShowErrorNoteL( TInt  aResourceId  ) const
    {
    HBufC* errorText = StringLoader::LoadLC( aResourceId );
    CAknInformationNote* note = new( ELeave ) CAknInformationNote( EFalse );
    note->ExecuteLD( *errorText );
    CleanupStack::PopAndDestroy( errorText );
    }

// End of file

