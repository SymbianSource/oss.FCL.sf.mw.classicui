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


#ifndef __EIKENVEXTRA_H__
#define __EIKENVEXTRA_H__

#include <e32base.h>	// class CBase

class CEikonEnv;
class MPictureFactory;
class MEikPictureFactory;
class CEikPictureFactoryResolver;
class CEikStartUpViewActivator;
class CEikErrorResolver;
class CEikAppServer;
class CLocalizedFilenameCache;

//
// class CEikEnvExtra
//

/**
Extension class to allow CEikEnv to grow without breaking BC.
New data members may be added to CEikEnvExtra.
@internalComponent
*/
NONSHARABLE_CLASS(CEikEnvExtra) : public CBase
	{
public:
	static CEikEnvExtra* NewL(const CEikonEnv& aEikEnv);
	~CEikEnvExtra();	
		
	// Cache for localized bitmap file names
	void CacheLocalizedBitmapFilenameL(const TDesC& aGeneralFilename, const TDesC& aLocalizedFilename);
	TBool FindLocalizedBitmapFilenameInCache(TDesC& aFilename, TDes& aLocalizedFileName);
	// PictureFactory methods
	const MPictureFactory& PictureFactory() const;
	const MEikPictureFactory& PictureFactory(TInt aIndex) const;
	const TArray<MEikPictureFactory*> PictureFactories() const;
	void AppendPictureFactoryL(MEikPictureFactory* aPictureFactory);
	void DeletePictureFactory(TInt aIndex);
private:
	CEikEnvExtra();	
public:
	CEikStartUpViewActivator* iViewActivator;
	CEikErrorResolver* iErrorResolver;	// This holds a CEikErrorResolver object, but only when in EikSrv's thread!
	CEikAppServer* iAppServer;
	TInt iDefaultScreenNumber; 
	TLanguage iAppLanguage;
private:
	CArrayPtr<MEikPictureFactory>* iPictureFactoryArray;
	CLocalizedFilenameCache* iLocalizedFilenameCache;	
	CEikPictureFactoryResolver* iPictureFactoryResolver;
	};




#endif	//__EIKENVEXTRA_H__
