/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef AKNCAPSERVERALTERNATEFSPLUGIN_H
#define AKNCAPSERVERALTERNATEFSPLUGIN_H

#include <e32base.h>
#include <ecom/ecom.h>

/**
 * Base class for ECOM plugins which provide alternate fast swap window 
 * functionality. AknCapServer will load the first of the found plugins or
 * if none found then use the built-in fast swapper.
 */
class CAknCapAppServerAlternateFs : public CBase
	{
public:
    
    /**
     * Symbian two phased constructors.
     *
     * @param aImplementationUid Implementation to create.
     * @return CAlternateFsPlugin pointer.
     */
    inline static CAknCapAppServerAlternateFs* NewL( 
        const TUid& aImplementationUid );
    
    /**
     * Destructor.
     */
    inline virtual ~CAknCapAppServerAlternateFs();
    
    /**
     * Shows the alternate fast swap.
     */
    virtual void Show() = 0;

    /**
     * Dismisses the alternate fast swap.
     */
    virtual void Dismiss() = 0;

    /**
     * Checks if alternate fast swap is currently visible.
     * 
     * @return ETrue If alternate FS is visible.
     */    
    virtual TBool IsVisible() = 0;

    /**
     * Checks if alternate fast swap is ready to be shown.
     * 
     * @return ETrue If alternate FS is ready.
     */    
    virtual TBool IsReady() = 0;

    /**
     * Returns the ecom implementation uid of this plugin.
     **/
    inline TUid ImplementationUid() const;

	/**
     * Forward long app key to the alternate fast swap
     */
    virtual void HandleLongAppKeyPress() = 0;
    
    /**
     * Forward short app key to the alternate fast swap
     */
    virtual void HandleShortAppKeyPress() = 0;

private:
    
    /** Destructor Id */
    TUid iDtorKey;
    
    /** Impl uid */
    TUid iImplUid;
    
    /** For future purposes */
    TInt iReserved0;
    TInt iReserved1;
    TInt iReserved2;
    TInt iReserved3;    
    };

// Inline functions
#include <akncapserveralternatefsplugin.inl>
    
#endif // AKNCAPSERVERALTERNATEFSPLUGIN_H
