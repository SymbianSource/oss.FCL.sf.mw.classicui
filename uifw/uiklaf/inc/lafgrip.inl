/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


enum {EOrientationMask=TLafGrip::EVertical};
enum {ELineWidth=2,ESpaceBetweenLines=3};

inline TLafGrip::TLafGrip(TOrientation aOrientation)
	: iData(aOrientation)
	{}

inline void TLafGrip::SetOrientation(TOrientation aOrientation)
	{
	iData=(iData&(~EOrientationMask))|aOrientation;
	}

inline TLafGrip::TOrientation TLafGrip::Orientation() const
	{
	return (TOrientation)(iData&EOrientationMask);
	}
