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
// Header containing Logical border interface: MGulLogicalBorder, and logical boreder set and get: GulTls.
//

#ifndef GULLOGICALBORDER_H
#define GULLOGICALBORDER_H

/**
The MGulLogicalBorder class specifices an interface for logical borders.

@internalTechnology*/
class MGulLogicalBorder
	{
public:
	virtual void Draw(const TGulBorder& aBorder,CGraphicsContext& aGc, const TRect& aRect, const TGulBorder::TColors& aBorderColors) const=0;
	virtual TMargins Margins(const TGulBorder& aBorder) const=0;
private:
	IMPORT_C virtual void MGulLogicalBorderReserved();
	};

/**
The GulTls class sets and gets the thread local storage for EGul.
 
@internalTechnology*/
class GulTls
	{
public:
	IMPORT_C static void SetLogicalBorder(MGulLogicalBorder* aLogicalBorder);
	IMPORT_C static const MGulLogicalBorder* LogicalBorder();
	};


#endif /* GULLOGICALBORDER_H */
