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
* Description:     Inline functions for AiwContactAssignDataTypes
*
*/





/////////////////////////////////////////////////////////////////////////////
//
// TAiwContactAssignDataBase inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwContactAssignDataBase::TAiwContactAssignDataBase() :
        iAssignDataType(EAiwContactAssignDataTypeNotDefined)
    {
    }

inline TAiwContactAssignDataType TAiwContactAssignDataBase::
        AssignDataTypeFromBuffer( const TDesC8& aBuffer )
    {
    TPckgBuf<TAiwContactAssignDataBase>
        data( EAiwContactAssignDataTypeNotDefined );
    data.Copy( aBuffer.Ptr(), sizeof( TAiwContactAssignDataBase ) );

    return data().AssignDataType();
    }

inline TAiwContactAssignDataBase::TAiwContactAssignDataBase
        ( TAiwContactAssignDataType aAssignDataType ) :
            iAssignDataType( aAssignDataType )
    {
    }

inline TAiwContactAssignDataType
        TAiwContactAssignDataBase::AssignDataType() const
    {
    return iAssignDataType;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwSingleContactAssignDataV1 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwSingleContactAssignDataV1::TAiwSingleContactAssignDataV1() :
        TAiwContactAssignDataBase( KAssignDataType ),
            iFlags( 0 )
    {
    }

inline TAiwSingleContactAssignDataV1&
        TAiwSingleContactAssignDataV1::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TAiwSingleContactAssignDataV1&
        TAiwSingleContactAssignDataV1::SetEditorHelpContext
            ( TCoeHelpContext aHelpContext )
    {
    iEditorHelpContext = aHelpContext;
    return *this;
    }


inline TUint TAiwSingleContactAssignDataV1::Flags() const
    {
    return iFlags;
    }

inline TCoeHelpContext TAiwSingleContactAssignDataV1::EditorHelpContext()
        const
    {
    return iEditorHelpContext;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwMultipleContactAssignDataV1 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwMultipleContactAssignDataV1::TAiwMultipleContactAssignDataV1() :
        TAiwContactAssignDataBase( KAssignDataType ),
            iFlags( 0 )
    {
    }

inline TAiwMultipleContactAssignDataV1&
        TAiwMultipleContactAssignDataV1::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TUint TAiwMultipleContactAssignDataV1::Flags() const
    {
    return iFlags;
    }

/////////////////////////////////////////////////////////////////////////////
//
// TAiwContactAttributeAssignDataV1 inline methods
//
/////////////////////////////////////////////////////////////////////////////
inline TAiwContactAttributeAssignDataV1::TAiwContactAttributeAssignDataV1() :
        TAiwContactAssignDataBase( KAssignDataType ),
            iFlags( 0 ), iRemoveAttribute( EFalse )
    {
    }

inline TAiwContactAttributeAssignDataV1&
        TAiwContactAttributeAssignDataV1::SetFlags( TUint aFlags )
    {
    iFlags = aFlags;
    return *this;
    }

inline TAiwContactAttributeAssignDataV1&
        TAiwContactAttributeAssignDataV1::SetAttributeRemove
            ( TBool aRemove )
    {
    iRemoveAttribute = aRemove;
    return *this;
    }

inline TUint TAiwContactAttributeAssignDataV1::Flags() const
    {
    return iFlags;
    }

inline TBool TAiwContactAttributeAssignDataV1::RemoveAttribute() const
    {
    return iRemoveAttribute;
    }

// End of File
