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
* Description:     Inline functions for AiwContactSelectionDataTypes.
*
*/





/////////////////////////////////////////////////////////////////////////////
//
// TAiwContactSelectionDataBase inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwContactSelectionDataBase::TAiwContactSelectionDataBase() :
        iSelectionDataType( EAiwContactSelectionDataTypeNotDefined )
    {
    }

inline TAiwContactSelectionDataType TAiwContactSelectionDataBase::
        SelectionDataTypeFromBuffer( const TDesC8& aBuffer )
    {
    TPckgBuf<TAiwContactSelectionDataBase>
        data(EAiwContactSelectionDataTypeNotDefined);
    data.Copy(aBuffer.Ptr(),
              sizeof(TAiwContactSelectionDataBase));

    return data().SelectionDataType();
    }

inline TAiwContactSelectionDataBase::TAiwContactSelectionDataBase(
        TAiwContactSelectionDataType aSelectionDataType ) :
    iSelectionDataType( aSelectionDataType )
    {
    }

inline TAiwContactSelectionDataType
        TAiwContactSelectionDataBase::SelectionDataType() const
    {
    return iSelectionDataType;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwSingleEntrySelectionDataV1 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwSingleEntrySelectionDataV1::TAiwSingleEntrySelectionDataV1() :
        TAiwContactSelectionDataBase( KSelectionDataType ),
            iFlags( 0 )
    {
    }

inline TAiwSingleEntrySelectionDataV1&
        TAiwSingleEntrySelectionDataV1::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TUint TAiwSingleEntrySelectionDataV1::Flags() const
    {
    return iFlags;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwSingleEntrySelectionDataV2 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwSingleEntrySelectionDataV2::TAiwSingleEntrySelectionDataV2() :
        TAiwContactSelectionDataBase( KSelectionDataType ),
            iFlags( 0 ), iFetchFilter( NULL )
    {
    }

inline TAiwSingleEntrySelectionDataV2&
        TAiwSingleEntrySelectionDataV2::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TAiwSingleEntrySelectionDataV2&
        TAiwSingleEntrySelectionDataV2::SetFetchFilter
            ( CVPbkFieldTypeSelector* aFilter )
    {
    iFetchFilter = aFilter;
    return *this;
    }

inline TUint TAiwSingleEntrySelectionDataV2::Flags() const
    {
    return iFlags;
    }

inline CVPbkFieldTypeSelector*
        TAiwSingleEntrySelectionDataV2::FetchFilter() const
    {
    return iFetchFilter;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwMultipleEntrySelectionDataV1 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwMultipleEntrySelectionDataV1::TAiwMultipleEntrySelectionDataV1() :
        TAiwContactSelectionDataBase( KSelectionDataType ),
            iFlags( 0 )
    {
    }

inline TAiwMultipleEntrySelectionDataV1&
        TAiwMultipleEntrySelectionDataV1::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TUint TAiwMultipleEntrySelectionDataV1::Flags() const
    {
    return iFlags;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwMultipleEntrySelectionDataV2 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwMultipleEntrySelectionDataV2::TAiwMultipleEntrySelectionDataV2() :
        TAiwContactSelectionDataBase( KSelectionDataType ),
            iFlags( 0 ), iFetchFilter( NULL )
    {
    }

inline TAiwMultipleEntrySelectionDataV2&
        TAiwMultipleEntrySelectionDataV2::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TAiwMultipleEntrySelectionDataV2&
        TAiwMultipleEntrySelectionDataV2::SetFetchFilter
            ( CVPbkFieldTypeSelector* aFilter )
    {
    iFetchFilter = aFilter;
    return *this;
    }

inline TUint TAiwMultipleEntrySelectionDataV2::Flags() const
    {
    return iFlags;
    }

inline CVPbkFieldTypeSelector*
        TAiwMultipleEntrySelectionDataV2::FetchFilter() const
    {
    return iFetchFilter;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwSingleItemSelectionDataV1 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwSingleItemSelectionDataV1::TAiwSingleItemSelectionDataV1() :
        TAiwContactSelectionDataBase( KSelectionDataType ),
            iFlags( 0 ), iAddressSelectType( EAiwAllItemsSelect ),
            iCommAddressSelectType( EAiwCommEmpty ),
            iDefaultPriorities( NULL )
    {
    }

inline TAiwSingleItemSelectionDataV1&
        TAiwSingleItemSelectionDataV1::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TAiwSingleItemSelectionDataV1&
        TAiwSingleItemSelectionDataV1::SetAddressSelectType(
            TAiwAddressSelectType aAddressSelectType )
    {
    iAddressSelectType = aAddressSelectType;
    return *this;
    }

inline TAiwSingleItemSelectionDataV1&
        TAiwSingleItemSelectionDataV1::SetCommAddressSelectType(
            TAiwCommAddressSelectType aCommAddressSelectType )
    {
    iCommAddressSelectType = aCommAddressSelectType;
    return *this;
    }

inline TAiwSingleItemSelectionDataV1&
        TAiwSingleItemSelectionDataV1::SetDefaultPriorities(
            RVPbkContactFieldDefaultPriorities& aDefaultPriorities )
    {
    iDefaultPriorities = &aDefaultPriorities;
    return *this;
    }

inline TUint TAiwSingleItemSelectionDataV1::Flags() const
    {
    return iFlags;
    }

inline TAiwAddressSelectType
        TAiwSingleItemSelectionDataV1::AddressSelectType() const
    {
    return iAddressSelectType;
    }

inline TAiwCommAddressSelectType
        TAiwSingleItemSelectionDataV1::CommAddressSelectType() const
    {
    return iCommAddressSelectType;
    }

inline RVPbkContactFieldDefaultPriorities*
        TAiwSingleItemSelectionDataV1::DefaultPriorities() const
    {
    return iDefaultPriorities;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwSingleItemSelectionDataV2 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwSingleItemSelectionDataV2::TAiwSingleItemSelectionDataV2() :
        TAiwContactSelectionDataBase( KSelectionDataType ),
            iFlags( 0 ), iAddressSelectResourceId( KErrNotFound),
            iDefaultPriorities( NULL )
    {
    }

inline TAiwSingleItemSelectionDataV2&
        TAiwSingleItemSelectionDataV2::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TAiwSingleItemSelectionDataV2&
        TAiwSingleItemSelectionDataV2::SetAddressSelectResourceId(
            TInt aAddressSelectResourceId )
    {
    iAddressSelectResourceId = aAddressSelectResourceId;
    return *this;
    }

inline TAiwSingleItemSelectionDataV2&
        TAiwSingleItemSelectionDataV2::SetDefaultPriorities(
            RVPbkContactFieldDefaultPriorities& aDefaultPriorities )
    {
    iDefaultPriorities = &aDefaultPriorities;
    return *this;
    }

inline TUint TAiwSingleItemSelectionDataV2::Flags() const
    {
    return iFlags;
    }

inline TInt TAiwSingleItemSelectionDataV2::AddressSelectResourceId() const
    {
    return iAddressSelectResourceId;
    }

inline RVPbkContactFieldDefaultPriorities*
        TAiwSingleItemSelectionDataV2::DefaultPriorities() const
    {
    return iDefaultPriorities;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwSingleItemSelectionDataV3 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwSingleItemSelectionDataV3::TAiwSingleItemSelectionDataV3() :
        TAiwContactSelectionDataBase( KSelectionDataType ),
            iFlags( 0 ), iAddressSelectType( EAiwAllItemsSelect ),
            iCommAddressSelectType( EAiwCommEmpty ),
            iDefaultPriorities( NULL ), iFetchFilter( NULL )
    {
    }

inline TAiwSingleItemSelectionDataV3&
        TAiwSingleItemSelectionDataV3::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TAiwSingleItemSelectionDataV3&
        TAiwSingleItemSelectionDataV3::SetAddressSelectType(
            TAiwAddressSelectType aAddressSelectType )
    {
    iAddressSelectType = aAddressSelectType;
    return *this;
    }

inline TAiwSingleItemSelectionDataV3&
        TAiwSingleItemSelectionDataV3::SetCommAddressSelectType(
            TAiwCommAddressSelectType aCommAddressSelectType )
    {
    iCommAddressSelectType = aCommAddressSelectType;
    return *this;
    }

inline TAiwSingleItemSelectionDataV3&
        TAiwSingleItemSelectionDataV3::SetDefaultPriorities(
            RVPbkContactFieldDefaultPriorities& aDefaultPriorities )
    {
    iDefaultPriorities = &aDefaultPriorities;
    return *this;
    }

inline TAiwSingleItemSelectionDataV3&
        TAiwSingleItemSelectionDataV3::SetFetchFilter
            ( CVPbkFieldTypeSelector* aFilter )
    {
    iFetchFilter = aFilter;
    return *this;
    }

inline TUint TAiwSingleItemSelectionDataV3::Flags() const
    {
    return iFlags;
    }

inline TAiwAddressSelectType
        TAiwSingleItemSelectionDataV3::AddressSelectType() const
    {
    return iAddressSelectType;
    }

inline TAiwCommAddressSelectType
        TAiwSingleItemSelectionDataV3::CommAddressSelectType() const
    {
    return iCommAddressSelectType;
    }

inline RVPbkContactFieldDefaultPriorities*
        TAiwSingleItemSelectionDataV3::DefaultPriorities() const
    {
    return iDefaultPriorities;
    }

inline CVPbkFieldTypeSelector*
        TAiwSingleItemSelectionDataV3::FetchFilter() const
    {
    return iFetchFilter;
    }
    
/////////////////////////////////////////////////////////////////////////////
//
// TAiwMultipleItemSelectionDataV1 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwMultipleItemSelectionDataV1::TAiwMultipleItemSelectionDataV1() :
        TAiwContactSelectionDataBase( KSelectionDataType ),
            iFlags( 0 ), iAddressSelectType( EAiwAllItemsSelect ),
            iDefaultPriorities( NULL ), iFetchFilter( NULL )
    {
    }

inline TAiwMultipleItemSelectionDataV1&
        TAiwMultipleItemSelectionDataV1::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TAiwMultipleItemSelectionDataV1&
        TAiwMultipleItemSelectionDataV1::SetAddressSelectType(
            TAiwAddressSelectType aAddressSelectType )
    {
    iAddressSelectType = aAddressSelectType;
    return *this;
    }

inline TAiwMultipleItemSelectionDataV1&
        TAiwMultipleItemSelectionDataV1::SetDefaultPriorities(
            RVPbkContactFieldDefaultPriorities& aDefaultPriorities )
    {
    iDefaultPriorities = &aDefaultPriorities;
    return *this;
    }

inline TAiwMultipleItemSelectionDataV1&
        TAiwMultipleItemSelectionDataV1::SetFetchFilter
            ( CVPbkFieldTypeSelector* aFilter )
    {
    iFetchFilter = aFilter;
    return *this;
    }

inline TUint TAiwMultipleItemSelectionDataV1::Flags() const
    {
    return iFlags;
    }

inline TAiwAddressSelectType
        TAiwMultipleItemSelectionDataV1::AddressSelectType() const
    {
    return iAddressSelectType;
    }

inline RVPbkContactFieldDefaultPriorities*
        TAiwMultipleItemSelectionDataV1::DefaultPriorities() const
    {
    return iDefaultPriorities;
    }

inline CVPbkFieldTypeSelector*
        TAiwMultipleItemSelectionDataV1::FetchFilter() const
    {
    return iFetchFilter;
    }    

// End of File
