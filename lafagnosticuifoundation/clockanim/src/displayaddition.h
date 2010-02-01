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

#ifndef DISPLAYADDITION_H
#define DISPLAYADDITION_H
// miscellaneous typedefs
//
/** @internalComponent
WARNING: For internal use ONLY. Compatibility is not guaranteed in future releases.
*/
typedef TBuf8<1024> TConstructorBuf8; 
// implementation class

//
// miscellaneous enums
//

/** @internalComponent
WARNING: For internal use ONLY. Compatibility is not guaranteed in future releases.
*/
enum TDisplayType // implementation class
	{
	EDisplayDigital,
	EDisplayAnalog
	};

/** @internalComponent
WARNING: For internal use ONLY. Compatibility is not guaranteed in future releases.
*/
enum TAnalogDisplayHandFeatureType // implementation class
	{
	EAnalogDisplayHandFeatureLine,
	EAnalogDisplayHandFeaturePolyLine,
	EAnalogDisplayHandFeatureCircle
	};

//
// display-addition class
//

class TDisplayAddition
/** This class is used in the derivation of TAnalogDisplayHand and TDigitalDisplayTextSection. 

@internalComponent
WARNING: For internal use ONLY. Compatibility is not guaranteed in future releases.
*/
	{
public:
	const TDesC8& Buf() const;
protected:
	TConstructorBuf8 iBuf;
	};

#endif // DISPLAYADDITION_H
//

