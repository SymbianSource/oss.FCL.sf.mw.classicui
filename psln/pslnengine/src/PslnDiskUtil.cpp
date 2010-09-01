/*
* Copyright (c) 2003-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Disk service utility for Psln.
*
*/


// INCLUDE FILES

// General.
#include <coemain.h>
#include <DRMHelper.h>
#include <DRMRights.h>
#include <AknsSrvClient.h>
#include <pathinfo.h> 
#include <caf/manager.h>

// Psln specific.
#include "PslnDiskUtil.h"
#include "PslnFeatures.h"
#include "PslnConst.h"
#include "PslnDebug.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// PslnDiskUtil::MmcStatus
// -----------------------------------------------------------------------------
//
TInt PslnDiskUtil::MmcStatus()
    {
    PSLN_TRACE_DEBUG("PslnDiskUtil::MmcStatus");
    if( !PslnFeatures::IsMMCSupported() )
        {
        PSLN_TRACE_DEBUG("PslnDiskUtil::MmcStatus Not Supported");
        return KErrNotSupported;
        }

    RFs& fs = CCoeEnv::Static()->FsSession();

    TInt error = KErrNone;
    TDriveInfo driveInfo;
    TInt res = 0;
    fs.CharToDrive( PathInfo::MemoryCardRootPath()[0], res );
    error = fs.Drive( driveInfo, res  );
    if( error )
        {
        PSLN_TRACE_DEBUG1("PslnDiskUtil::MmcStatus Error=%d", error );
        return error;
        }

    // MMC is locked
    if( driveInfo.iMediaAtt & KMediaAttLocked )
        {
        PSLN_TRACE_DEBUG("PslnDiskUtil::MmcStatus Locked");
        return KErrLocked;
        }

    // MMC is not present or of unknown type
    if ( driveInfo.iType == EMediaNotPresent ||
         driveInfo.iType == EMediaUnknown )
        {
        PSLN_TRACE_DEBUG("PslnDiskUtil::MmcStatus Not present");
        return KErrNotFound;
        }

    if( driveInfo.iMediaAtt & KMediaAttWriteProtected )
        {
        PSLN_TRACE_DEBUG("PslnDiskUtil::MmcStatus Read Only");
        return KPslnDiskUtilReadOnly;
        }
    PSLN_TRACE_DEBUG("PslnDiskUtil::MmcStatus Ok");
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// PslnDiskUtil::QueryAndSetAutomatedL
// ---------------------------------------------------------------------------
//
TBool PslnDiskUtil::QueryAndSetAutomatedL(
    RAknsSrvSession& aSkinSrvSession, const TDesC& aFileName)
    {
    PSLN_TRACE_DEBUG("PslnDiskUtil::QueryAndSetAutomatedL");

    TBool isProtected = EFalse;
    TInt value = KErrNone;

    TInt fileserverhandle;
    TInt filehandle;
    fileserverhandle = aSkinSrvSession.OpenBitmapFile( aFileName, filehandle );
    RFile file;
    User::LeaveIfError( file.AdoptFromServer( fileserverhandle, filehandle ) );
    CleanupClosePushL( file );

    CContent* content = CContent::NewLC( file );
    User::LeaveIfError( content->GetAttribute( EIsProtected, value ) );
    if ( value )
        {
        isProtected = ETrue;
        }
    CleanupStack::PopAndDestroy( content );

    PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL prot=%d", isProtected );
    PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL value=%d", value );

    TBool set = ETrue;
    if ( isProtected )
        {
        CDRMHelper* helper = CDRMHelper::NewLC();
        CDRMHelperRightsConstraints* playconst = NULL;
        CDRMHelperRightsConstraints* dispconst = NULL;
        CDRMHelperRightsConstraints* execconst = NULL;
        CDRMHelperRightsConstraints* printconst = NULL;
        TBool expired = EFalse;
        TBool sendingallowed = EFalse;
        helper->GetRightsDetailsL( 
            file, 
            CDRMRights::EDisplay, 
            expired, 
            sendingallowed, 
            playconst, 
            dispconst, 
            execconst, 
            printconst ); 
        delete playconst;
        delete execconst;
        delete printconst;
        CleanupStack::PushL( dispconst );

        // Talkin' 'bout themes here
        helper->SetAutomatedType( CDRMHelper::EAutomatedTypeTheme );

        if ( dispconst && dispconst->FullRights() )
            {
            set = ETrue;
            // Set the Fullrights content as automated also
            // and ignore the result....            
            helper->SetAutomated( file );
            }
        else
            {
            TInt res = KErrNone;           
            res = helper->SetAutomated( file );           
            PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL res=%d", res );

            if ( res == KErrCancel )
                {
                set = EFalse;
                }
            else 
                {
                User::LeaveIfError( res );
                TInt err = helper->ConsumeFile2( file, CDRMRights::EPlay, CDRMHelper::EStart );
                PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL 1 err=%d", err );
                err = helper->ConsumeFile2( file, CDRMRights::EPlay, CDRMHelper::EFinish );
                PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL 2 err=%d", err );
                err = helper->ConsumeFile2( file, CDRMRights::EDisplay, CDRMHelper::EStart );
                PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL 3 err=%d", err );
                err = helper->ConsumeFile2( file, CDRMRights::EDisplay, CDRMHelper::EFinish );
                PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL 4 err=%d", err );
                err = helper->ConsumeFile2( file, CDRMRights::EExecute, CDRMHelper::EStart );
                PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL 5 err=%d", err );
                err = helper->ConsumeFile2( file, CDRMRights::EExecute, CDRMHelper::EFinish );
                PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL 6 err=%d", err );
                set = ETrue;
                }
            }
        CleanupStack::PopAndDestroy( 2, helper );
        }
    CleanupStack:: PopAndDestroy(); // file
    PSLN_TRACE_DEBUG1("PslnDiskUtil::QueryAndSetAutomatedL set=%d", (TInt) set );
    return set;
    }

//  End of File  
