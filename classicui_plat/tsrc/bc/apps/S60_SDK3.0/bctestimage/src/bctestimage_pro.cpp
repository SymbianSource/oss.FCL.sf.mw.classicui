/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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








#include <s32strm.h>
#include <s32file.h>
#include <eikenv.h>
#include <f32file.h>
#include <eikimage.h>

#include "bctestimage_pro.h"
#include "bctestassert.h"

_LIT(KStreamName, "c:\\BCTestLog\\testImage.txt");


CBCTestImage_pro::~CBCTestImage_pro()
{
	
}

CBCTestImage_pro::CBCTestImage_pro()
{
	
}

void CBCTestImage_pro::testWriteInternalL() const
{
	RFs tempServer = CEikonEnv::Static()->FsSession();

	RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer, 
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    WriteInternalStateL( fWrite );
    CleanupStack::PopAndDestroy(&fWrite );
}

