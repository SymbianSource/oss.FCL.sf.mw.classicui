/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/

#ifndef __AKNAPP_H__
#define __AKNAPP_H__

// INCLUDES

#include <eikapp.h>

// CLASS DECLARATION

/**
*  Base class for a Series 60 application.
*
*  @since Series 60 0.9
*/
class CAknApplication : public CEikApplication
	{
public:
	// from CApaApplication
	
	/**
	* From @c CApaApplication. Completes construction of this application
	* object. @c PreDocConstructL is implemented to first check that an instance
	* of the application being constructed is not already present. If it is 
	* present, then the application switches to the existing instance and then
	* exits. This check is only carried out for non-embedded applications.
    * This function calls @c CEikApplication::PreDocConstructL.
    */
	IMPORT_C virtual void PreDocConstructL();
	
	/**
    * From @c CApaApplication. Opens the .ini file associated with the
    * application. By default, ini files are not supported by SERIES60 
    * applications. If you want to use an ini file, either override this
    * function to base call @c CEikApplication::OpenIniFileLC, or call it
    * directly.
    * @param aFs File server session to use. Not used.
    * @return Pointer to the dictionary store object representing the
    * application's .ini file.
    */
	IMPORT_C CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
	
	
	/**
	* Sets new application server.
	* @since Series 60 3.0
	* @param aAppServer The server pointer to be set.
	*/
	IMPORT_C void NewAppServerL(CApaAppServer*& aAppServer);
	};

#endif

