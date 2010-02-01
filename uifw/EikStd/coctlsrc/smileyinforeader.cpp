/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  smiely engine class
*
*/

#include <smiley.rsg>
#include <eikenv.h>
#include <barsread.h>
#include <eikon.hrh>
#include <f32file.h>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <coeutils.h>
#include "smileymanager.h"
#include "smileymodel.h"
#include "smileyinforeader.h"

const TText KSmileyZDrive = 'Z';
_LIT( KSmileyResourceDir, "C:\\resource\\" );
_LIT( KSmileyIconDir, "C:\\resource\\apps\\" );
_LIT( KDefaultFileName, "smiley" );
_LIT( KRscFileExtName, ".rsc" );
_LIT( KMifFileExtName, ".mif" );
const TInt KSmileyPathLength = 60;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CSmileyInfoReader::CSmileyInfoReader
// ---------------------------------------------------------------------------
//
CSmileyInfoReader::CSmileyInfoReader( CSmileyModel& aModel ) :
    iModel( &aModel )
    {    
    }
    
// ---------------------------------------------------------------------------
// CSmileyInfoReader::~CSmileyInfoReader
// ---------------------------------------------------------------------------
//
CSmileyInfoReader::~CSmileyInfoReader()
    {    
    }

// ---------------------------------------------------------------------------
// CSmileyInfoReader::ReadCenRepInfoL
// ---------------------------------------------------------------------------
//
void CSmileyInfoReader::ReadCenRepInfoL( TInt& aResourceId, 
    TDes& aResourceFile, TDes& aIconFile )
    {
    aResourceId = R_SMILEY_ICONS_INFO;
    const TInt fileNameLength( 30 );
    HBufC* fileName( HBufC::NewL( fileNameLength ) );
    CleanupStack::PushL( fileName );
    TPtr ptr( fileName->Des() );
    CRepository* repository( CRepository::NewL( KCRUidAvkon ) );
    TInt err( repository->Get( KAknEmotionResourceFileName, 
        ptr ) );
    if ( err != KErrNone )
        {
        ptr.Copy( KDefaultFileName );
        }
    delete repository;
    
    aResourceFile.Append( KSmileyResourceDir );
    aResourceFile.Append( ptr );
    aResourceFile.Append( KRscFileExtName );
    aIconFile.Append( KSmileyIconDir );
    aIconFile.Append( ptr );
    aIconFile.Append( KMifFileExtName );
    CleanupStack::PopAndDestroy( fileName );
    
    if ( ConeUtils::FileExists( aResourceFile ) && 
        ConeUtils::FileExists( aIconFile ) )
        {
        return;
        }
    aResourceFile[0] = KSmileyZDrive;
    aIconFile[0] = KSmileyZDrive;
    if ( !ConeUtils::FileExists( aResourceFile ) || 
        !ConeUtils::FileExists( aIconFile ) )
        {
        User::Leave( KErrNotFound );
        }
    }

// ---------------------------------------------------------------------------
// CSmileyInfoReader::LoadSmileysFromResource
// ---------------------------------------------------------------------------
//
void CSmileyInfoReader::ReadSmileyL( CSmileyInfo& aInfo, 
    TResourceReader& aReader )
    {
    aInfo.iImageInfo.iIsAnimation = ( aReader.ReadInt16() == 1 );
    aInfo.iImageInfo.iCode = aReader.ReadInt16();
    aInfo.iImageInfo.iBmpId = aReader.ReadInt32();
    aInfo.iImageInfo.iMaskId = aReader.ReadInt32();
    aInfo.iImageInfo.iStaticBmpId = aReader.ReadInt32();
    aInfo.iImageInfo.iStaticMaskId = aReader.ReadInt32();
    TPtrC ptrc( aReader.ReadTPtrC() );
    aInfo.SetSmileyText( ptrc );
    }

// ---------------------------------------------------------------------------
// CSmileyInfoReader::LoadSmileysFromResource
// ---------------------------------------------------------------------------
//
void CSmileyInfoReader::LoadSmileysFromResourceL()
    {
    TInt resourceId( 0 );
    TBuf<KSmileyPathLength> resourceFile;
    TBuf<KSmileyPathLength> iconFile;
    ReadCenRepInfoL( resourceId, resourceFile, iconFile );
    iModel->SetSmileyIconFileL( iconFile  );
    
    CEikonEnv* env( CEikonEnv::Static() );
    TInt offset( env->AddResourceFileL( resourceFile ) );    
    TResourceReader reader;
    env->CreateResourceReaderLC( reader, resourceId );
    TInt count( reader.ReadInt16() );
    if ( count > 0 )
        {
        CSmileyInfo* info( new( ELeave ) CSmileyInfo );
        CleanupStack::PushL( info );
        for ( TInt i( 0 ); i < count; i++ )
            {
            info->Reset();
            ReadSmileyL( *info, reader );
            iModel->AddSimleyL( *info );
            }
        CleanupStack::PopAndDestroy( info );
        }
    CleanupStack::PopAndDestroy(); // reader    
    env->DeleteResourceFile( offset );
    }

