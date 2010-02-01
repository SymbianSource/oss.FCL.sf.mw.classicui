/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Contins ECom related implementaion of
*        CHTIServiceInterfaceinterface class
*
*/


inline CTasDataModelInterface* CTasDataModelInterface::NewL()
    {
#ifdef _DEBUG
    RDebug::Print( _L( "=> CTasDataModelInterface::NewL" ) );
#endif
    
    TAny* ptr = REComSession::CreateImplementationL( 
                KTasDataModelImplementationUid,
                _FOFF( CTasDataModelInterface, iImplementation ) );

#ifdef _DEBUG
    RDebug::Print( _L( "<= CTasDataModelInterface::NewL" ) );
#endif
    return reinterpret_cast<CTasDataModelInterface*>( ptr );
    }


inline CTasDataModelInterface* CTasDataModelInterface::NewL(
    const TUid aUID)
    {
    TAny* ptr = REComSession::CreateImplementationL(
                aUID,
                _FOFF(CTasDataModelInterface,iImplementation) );

     return reinterpret_cast<CTasDataModelInterface*>( ptr );
    }

inline CTasDataModelInterface* CTasDataModelInterface::NewL(
    const TDesC8& aMatchString)
    {

    TEComResolverParams resolverParams;
    resolverParams.SetDataType(aMatchString);
    TAny* ptr = REComSession::CreateImplementationL(
                KTasDataModelInterfaceUid,
                _FOFF(CTasDataModelInterface,iImplementation),
        resolverParams);

     return reinterpret_cast<CTasDataModelInterface*>( ptr );
    }

inline CTasDataModelInterface::~CTasDataModelInterface()
    {
    REComSession::DestroyedImplementation(iImplementation);
    }

