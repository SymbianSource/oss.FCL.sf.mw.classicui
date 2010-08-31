/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test extended_options_menu_api
 *
*/

#ifndef T_TESTDOMMENU_H
#define T_TESTDOMMENU_H

//  INCLUDES
#include <akncollection.h>

/**
 *  CTestOptionsMenu test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
class TTestCollection : public MAknCollection
{
// Constructors and destructor
public:
    /**
    * C++ default constructor.
    */
	
    /**
     * Destructor.
    */
   
    
public:// Functions inherit from MAknCollection classes

    // From MAknCollection
    /**
     * Returns the collection state. The state is combination of
     * flags defined in MAknCollection::TStateFlag. 
     *
     * @return  Collection state.
     */
    TUint CollectionState() const
        {
        return MAknCollection::EStateCollectionVisible;
        }

    /**
     * Notifies that item action menu (CAknItemActionMenu)
     * was closed. 
     */
    void ItemActionMenuClosed()
    	{
    	}

    /** 
     * Extension function.
     *
     * @param  aExtensionId  Extension id. 
     * @param  a0            First extension method parameter.
     * @param  a1            Second extension method parameter.
     */    
    TInt CollectionExtension( TUint aExtensionId, TAny*& a0, TAny* a1 )
    	{
    	return 0;
    	}
};

#endif /*T_TESDOMMENU_H*/
// End of File
