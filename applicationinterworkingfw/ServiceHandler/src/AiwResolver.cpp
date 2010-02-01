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
* Description:     Implementation of Custom ECom Resolver for AIW.
*
*/




#include "AiwResolver.h"

const TInt KMaxDataItemSize = 150;
_LIT8(KContentTag, "<CONTENT>");
_LIT8(KOpaqueTag, "<OPAQUE>");


CAiwResolver* CAiwResolver::NewL(MPublicRegistry& aRegistry)
    {
    return new (ELeave) CAiwResolver(aRegistry);
    }


CAiwResolver::CAiwResolver(MPublicRegistry& aRegistry) : CResolver(aRegistry)
    {
    // Nothing to do.
    }


CAiwResolver::~CAiwResolver()
    {
    if (iImplementationInfoArray)
        {
        iImplementationInfoArray->Reset();  
        delete iImplementationInfoArray;
        }
    }



TUid CAiwResolver::IdentifyImplementationL(TUid aInterfaceUid, 
    const TEComResolverParams& aAdditionalParameters) const
    {
    RImplInfoArray& implementationsInfo = iRegistry.ListImplementationsL(aInterfaceUid);
    TUid found = KNullUid;

    if(implementationsInfo.Count())
        {
        found = Resolve(implementationsInfo, aAdditionalParameters);
        }

    return found;
    }



RImplInfoArray* CAiwResolver::ListAllL(TUid aInterfaceUid, 
    const TEComResolverParams& aAdditionalParameters) const
    {
    // Use the member var to create the array so that we get proper cleanup behaviour
    delete iImplementationInfoArray;
    iImplementationInfoArray = NULL;
    iImplementationInfoArray = new (ELeave) RImplInfoArray;
    RImplInfoArray* retList = iImplementationInfoArray;

    RImplInfoArray& fullList = iRegistry.ListImplementationsL(aInterfaceUid);

    const TBool useWildcards = aAdditionalParameters.IsWildcardMatch();
    TBuf8<KMaxDataItemSize> content;
    TBuf8<KMaxDataItemSize> opaque;

    ParseInput(aAdditionalParameters.DataType(), content, opaque);
    const TInt numImps = fullList.Count();

    for (TInt index = 0; index < numImps; ++index)
        {
        if (Match(fullList[index]->DataType(), content, useWildcards) &&
            MatchServiceCmd(fullList[index]->OpaqueData(), opaque))
            {
            User::LeaveIfError(retList->Append(fullList[index]));
            }
        }

    // Reset the member variable because we are passing ownership back
    iImplementationInfoArray = NULL;

    return retList;
    }



void CAiwResolver::ParseInput(const TDesC8& aParam, TDes8& aContent, TDes8& aOpaque) const
    {
    TInt cind = aParam.Find(KContentTag);
    TInt oind = aParam.Find(KOpaqueTag);
        
    if (cind != KErrNotFound)
        {
        if (oind != KErrNotFound)
            {
            aContent.Copy(aParam.Mid(cind + (&KContentTag)->Length(), 
                                     oind - (cind + (&KContentTag)->Length())));
            }
        else
            {
            aContent.Copy(aParam.Mid(cind + (&KContentTag)->Length()));
            }
        }

    if (oind != KErrNotFound)
        {
        aOpaque.Copy(aParam.Mid(oind + (&KOpaqueTag)->Length()));
        }
    }



TUid CAiwResolver::Resolve(const RImplInfoArray& aImplementationsInfo, 
    const TEComResolverParams& aAdditionalParameters) const
    {
    // Loop through the implementations matching on type
    const TInt count = aImplementationsInfo.Count();

    for (TInt index = 0; index < count; ++index)
        {
        const CImplementationInformation& impData = *aImplementationsInfo[index];
        // As soon as we get a match on the datatype then return uid of the
        // implementation found.
        if (Match(impData.DataType(),                   // The Datatype of this implementation
            aAdditionalParameters.DataType(),           // The type we are trying to find
            aAdditionalParameters.IsWildcardMatch()))   // If wildcards should be used
            {
            return impData.ImplementationUid();
            }
        }

    return KNullUid;
    }


TBool CAiwResolver::Match(const TDesC8& aImplementationType, const TDesC8& aMatchType, 
    TBool aUseWildcards) const
    {
    TInt matchPos = KErrNotFound;

    _LIT8(dataSeparator, "||");
    const TInt separatorLength = dataSeparator().Length();

    // Look for the section separator marker '||'
    TInt separatorPos = aImplementationType.Find(dataSeparator);

    if (separatorPos == KErrNotFound)
        {
        // Match against the whole string
        if (aUseWildcards)
            {
            matchPos = aImplementationType.Match(aMatchType);
            }
        else
            {
            if (aImplementationType.Compare(aMatchType) == 0)
                {
                matchPos = KErrNone;    
                }
            }
        }
    else
        {
        // Find the first section, up to the separator
        TPtrC8 dataSection = aImplementationType.Left(separatorPos);
        TPtrC8 remainingData = aImplementationType.Mid(separatorPos + separatorLength);

        // Match against each section in turn
        while (separatorPos != KErrNotFound)
            {
            // Search this section
            if (aUseWildcards)
                {          
                matchPos = dataSection.Match(aMatchType);
                }
            else
                {
                if (dataSection.Compare(aMatchType) == 0)
                    {
                    matchPos = KErrNone;
                    }
                }

            // If we found it then no need to continue, so return
            if (matchPos != KErrNotFound)
                {
                return ETrue;
                }

            // Move on to the next section
            separatorPos = remainingData.Find(dataSeparator);

            if (separatorPos != KErrNotFound)
                {
                dataSection.Set(remainingData.Left(separatorPos));
                remainingData.Set(remainingData.Mid(separatorPos + separatorLength));
                }
            else
                {
                dataSection.Set(remainingData);
                }   
            }

        // Check the final part
        if (aUseWildcards)
            {
            matchPos = dataSection.Match(aMatchType);
            }
        else
            {
            if (dataSection.Compare(aMatchType) == 0)
                {
                matchPos = KErrNone;
                }
            }
        }

    return matchPos != KErrNotFound;
    }




TBool CAiwResolver::MatchServiceCmd(const TDesC8& aOpaqueData, const TDesC8& aServiceCmd) const
    {
    _LIT8(dataSeparator, "||");
    const TInt separatorLength = dataSeparator().Length();

    // Look for the section separator marker '||'
    TInt separatorPos = aOpaqueData.Find(dataSeparator);

    if (separatorPos == KErrNotFound)
        {
         if (aServiceCmd.Compare(aOpaqueData) == 0)
            {
            return ETrue;   
            }
        }
    else
        {
         // Find the first section, up to the separator
        TPtrC8 dataSection = aOpaqueData.Left(separatorPos);
        TPtrC8 remainingData = aOpaqueData.Mid(separatorPos + separatorLength);

        // Match against each section in turn
        while (separatorPos != KErrNotFound)
            {
            if (dataSection.Compare(aServiceCmd) == 0)
                {
                return ETrue;
                }

            // Move on to the next section
            separatorPos = remainingData.Find(dataSeparator);

            if (separatorPos != KErrNotFound)
                {
                dataSection.Set(remainingData.Left(separatorPos));
                remainingData.Set(remainingData.Mid(separatorPos + separatorLength));
                }
            else
                {
                dataSection.Set(remainingData);
                }   
            }

        if (dataSection.Compare(aServiceCmd) == 0)
            {
            return ETrue;   
            }       
        }

    return EFalse;
    }


// Map the interface UIDs
const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY(KAiwResolverImplUidValue, CAiwResolver::NewL)
    };

// Exported proxy for instantiation method resolution
// ---------------------------------------------------------
//
//
// ---------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }

// End of file

