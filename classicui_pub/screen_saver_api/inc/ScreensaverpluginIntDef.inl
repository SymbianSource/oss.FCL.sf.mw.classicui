/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Inline functions for CScreensaverPluginInterfaceDefinition class
*
*/


//  INCLUDES

#include <ecom/ecom.h>   			// For REComSession
#include <ScreensaverpluginIntDef.hrh>	// For KCScreensaverPluginInterfaceDefinitionUid

// CONSTANTS

// -----------------------------------------------------------------------------
// CScreensaverPluginInterfaceDefinition::NewL
// -----------------------------------------------------------------------------
//
inline CScreensaverPluginInterfaceDefinition* 
       CScreensaverPluginInterfaceDefinition::NewL(TUid aImplementationUid)
    {
    // Create an instance of an object of CScreensaverPluginInterfaceDefinition type
    // using aImplementationUid as identification
    TAny* ptr = REComSession::
                CreateImplementationL(aImplementationUid,
                                     _FOFF(CScreensaverPluginInterfaceDefinition,iDtor_ID_Key));
    return reinterpret_cast<CScreensaverPluginInterfaceDefinition*>(ptr);
    }

       

// -----------------------------------------------------------------------------
// CScreensaverPluginInterfaceDefinition::ListImplementationsL
// -----------------------------------------------------------------------------
//
inline void CScreensaverPluginInterfaceDefinition::
            ListImplementationsL(RImplInfoPtrArray& aImplInfoArray)
    {
    REComSession::ListImplementationsL(TUid::Uid(KCScreensaverPluginInterfaceDefinitionUid), aImplInfoArray);
    }

// -----------------------------------------------------------------------------
// CScreensaverPluginInterfaceDefinition::~CScreensaverPluginInterfaceDefinition
// -----------------------------------------------------------------------------
//
inline CScreensaverPluginInterfaceDefinition::~CScreensaverPluginInterfaceDefinition()
    {
    REComSession::DestroyedImplementation(iDtor_ID_Key);
    }

// End of file.