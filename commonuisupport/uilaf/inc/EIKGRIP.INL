// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

enum {EOrientationMask=TEikGrip::EVertical};
enum {ELineWidth=2,ESpaceBetweenLines=3};

inline TEikGrip::TEikGrip(TOrientation aOrientation)
	: iData(aOrientation)
	{}

inline void TEikGrip::SetOrientation(TOrientation aOrientation)
	{
	iData=(iData&(~EOrientationMask))|aOrientation;
	}

inline TEikGrip::TOrientation TEikGrip::Orientation() const
	{
	return (TOrientation)(iData&EOrientationMask);
	}
