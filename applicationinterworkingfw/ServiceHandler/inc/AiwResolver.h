/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Declares custom ECom resolver.
*
*/




#ifndef _AIW_RESOLVER_H
#define _AIW_RESOLVER_H

#include "AiwUids.hrh"
#include <ecom/resolver.h>
#include <ecom/publicregistry.h>
#include <ecom/implementationproxy.h>

// FORWARD DECLARATIONS
class TEComResolverParams;

// DynFeature resolver's UID
const TUid KAiwResolverImplUid = { KAiwResolverImplUidValue };

/**
 * Implements a non-default resolver.
 *
 * This controls the identification, (resolution), of which implementation
 * will be used to satisfy an interface implementation instantiation.
 */
class CAiwResolver : public CResolver
    {
    public:

        /**
        * Factory function
        * @param aRegistry <add description>
        */
        static CAiwResolver* NewL(MPublicRegistry& aRegistry);

        /**
        * Destructor.
        */
        virtual ~CAiwResolver();

        /**
        * Request that the resolver identify the most appropriate interface implementation.
        * 
        * @param aInterfaceUid          The interface for which implementations are requested.
        * @param aAdditionalParameters  Data to be used to refine the search further.
        * @return                       The Uid of the best fit interface implementation - 
        *                               KNullUid if no match is found.
        */
        TUid IdentifyImplementationL(TUid aInterfaceUid, 
            const TEComResolverParams& aAdditionalParameters) const;

        /**
        * List all the implementations which satisfy the specified interface.
        *
        * @param aInterfaceUid          The interface for which implementations are requested
        * @param aAdditionalParameters  Data to be used to refine the search further
        * @return                       Pointer to an array of suitable implementations. 
        *                               Ownership of this array is passed to the calling function.
        */
        RImplInfoArray* ListAllL(TUid aInterfaceUid, 
            const TEComResolverParams& aAdditionalParameters) const;

    private:

        /**
        * Constructor.
        * @param aRegistry <add description>
        */
        explicit CAiwResolver(MPublicRegistry& aRegistry);

        /**
        * Called by IdentifyImplementationL to select an appropriate implementation from a 
        * list of possibles.
        *
        * @param aImplementationsInfo   Information on the potential implementations
        * @param aAdditionalParameters  The data to match against to detemine the implementation
        * @return                       The Uid of the selected implementation - 
        *                               KNullUid if no match is found
        */
        TUid Resolve(const RImplInfoArray& aImplementationsInfo, 
            const TEComResolverParams& aAdditionalParameters) const;

        /**
        * Searches for a match of a data type on an implementation type.
        * Match returns ETrue if aMatchType is found within aImplementationType according 
        * to the following rules:
        *
        * 1) aImplementationType is treated as a series of descriptors separated by double
        * bars (||). ETrue is returned if aMatchType matches exactly any of the short
        * descriptors.  If no double bar is present then aImplementationType is treated as a
        * single descriptor.
        *
        * 2) If aUseWildcards == ETrue then a '?' in aMatchType will be matched to any single
        * character and '*' will be matched to any series of characters.
        *
        * @param aImplementationType  The implementation data type to search for a match
        * @param aMatchType           The data to search for
        * @param aUseWildcards        ETrue if wildcard matching should be allowed
        * @return                     ETrue if a match was found, EFalse otherwise
        */
        TBool Match(const TDesC8& aImplementationType, const TDesC8& aMatchType, 
            TBool aUseWildcards) const;

        TBool MatchServiceCmd(const TDesC8& aOpaqueData, const TDesC8& aServiceCmd) const;

        void ParseInput(const TDesC8& aParam, TDes8& aContent, TDes8& aOpaque) const;

    private:

        mutable RImplInfoArray* iImplementationInfoArray;
    };


#endif  // AIW_RESOLVER_H

// End of file

