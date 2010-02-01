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
* Description:  The data caging concrete filename and pathname filter
*
*/


#include <f32file.h>
#include <data_caging_path_literals.hrh>
#include <badesca.h>

#include "CAknDataCagingFilter.h"
#include "CAknCommonDialogsBase.h" // Panic codes
#include "CommonDialogs.hrh"

const TInt KGranularity = 4;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknDataCagingFilter::CAknDataCagingFilter
//
//
// -----------------------------------------------------------------------------
//
CAknDataCagingFilter::CAknDataCagingFilter()
    {
    }

// -----------------------------------------------------------------------------
// CAknDataCagingFilter::ConstructL
//
// -----------------------------------------------------------------------------
//
void CAknDataCagingFilter::ConstructL()
    {
    iCagingList = new (ELeave) CDesCArrayFlat(KGranularity);
    TBuf<KMaxPath> folder;
    iCagingList->AppendL(ExtractRoot(KDC_PROGRAMS_DIR, folder));
    iCagingList->AppendL(ExtractRoot(KDC_RESOURCE_FILES_DIR, folder));
    iCagingList->AppendL(ExtractRoot(KDC_CA_CERTIFICATES_DIR, folder));
    }

// -----------------------------------------------------------------------------
// CAknDataCagingFilter::ExtractRoot
// Extract the highest level directory from a path.
// ex. input:  //sys/bin/folder1/.../folderN,
//     output: sys
// deal with both Windows deliminator \\ and Unix deliminator /
// -----------------------------------------------------------------------------
//
TDesC& CAknDataCagingFilter::ExtractRoot(const TDesC& aPath, TDes& aResult)
    {
    //search for \\ or /
    _LIT( KDelimiterWin, "\\");
    _LIT( KDelimiterUnix, "/");
    TInt res=0;
    TBuf<KMaxPath> path(aPath);

    while( (res=path.Find(KDelimiterWin))  != KErrNotFound ||
           (res=path.Find(KDelimiterUnix)) != KErrNotFound )
        {
        if(res>0)
            {
            path=path.Left(res);
            break;
            }
        path=path.Right(path.Length()-(res+1));
        }
    path.LowerCase();

    aResult=path;
    return aResult;
    }
// -----------------------------------------------------------------------------
// CAknDataCagingFilter::NewLC
//
// -----------------------------------------------------------------------------
//
CAknDataCagingFilter* CAknDataCagingFilter::NewLC()
    {
    CAknDataCagingFilter* self = new( ELeave ) CAknDataCagingFilter();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CAknDataCagingFilter::~CAknDataCagingFilter()
// Destructor, release the caging item list.
// -----------------------------------------------------------------------------
//
CAknDataCagingFilter::~CAknDataCagingFilter()
    {
    delete iCagingList;
    }


// -----------------------------------------------------------------------------
// CAknDataCagingFilter::Accept
// Implementation of Super class virtual function,
// All items matched in caging list is forbidden.
// -----------------------------------------------------------------------------
//
TBool CAknDataCagingFilter::Accept(
    const TDesC& /*aDriveAndPath*/, const TEntry& aEntry ) const
    {
    TBuf<KMaxPath> path(aEntry.iName);
    TInt pos;
    path.LowerCase();
    return ( iCagingList->Find(path, pos)!=0 );
    }

// End of File
