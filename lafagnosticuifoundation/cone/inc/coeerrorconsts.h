// Copyright (c) 1998-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef COEERRORCONSTS_H_
#define COEERRORCONSTS_H_

/**
@internalTechnology
*/
#define KUidConeDllValue16 0x10003a41

/**
@internalTechnology
*/
const TUid KUidConeDll16={KUidConeDllValue16};


#if defined(_UNICODE)
/**
@internalTechnology
*/
#define KUidConeDllValue KUidConeDllValue16
/**
@internalTechnology
*/
const TUid KUidConeDll={KUidConeDllValue};
#else
#define KUidConeDllValue KUidConeDllValue8
const TUid KUidConeDll={KUidConeDllValue};
#endif



#endif /* COEERRORCONSTS_H_ */
