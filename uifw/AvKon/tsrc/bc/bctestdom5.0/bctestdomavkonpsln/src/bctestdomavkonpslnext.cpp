/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  class extended for test case
*
*/


#include <bamdesca.h>
#include <barsread.h>
#include <bctestdomavkonpsln.rsg>
#include "bctestdomavkonpslnext.h"


// ================================ MEMBER FUNCTIONS =========================

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CAknTransitionExt::CAknTransitionExt()
    {
    
    }
    
// ---------------------------------------------------------------------------
// C++ default Destructor
// ---------------------------------------------------------------------------
//
CAknTransitionExt::~CAknTransitionExt()
    {
    
    }
    
// ---------------------------------------------------------------------------
// CAknTransitionExt::AknTransitionCallback
// ---------------------------------------------------------------------------
//
TInt CAknTransitionExt::AknTransitionCallback( TInt, 
    TInt, 
    const TDesC8* )
    {
    return 0;
    }

// ================================ MEMBER FUNCTIONS =========================
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CAknTransparentCameraSettingPageExt::
    CAknTransparentCameraSettingPageExt( TInt aResourceID, 
    TInt& aCurrentSelectionIndex, 
    const MDesCArray* aItemArray ):
    CAknTransparentCameraSettingPage
    ( 
    aResourceID, 
    aCurrentSelectionIndex,
    aItemArray )
    {
                    
    }


// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CAknTransparentCameraSettingPageExt::
    CAknTransparentCameraSettingPageExt( const TDesC* aSettingTitleText, 
    TInt aSettingNumber, 
    TInt aControlType,
    TInt aEditorResourceId, 
    TInt aSettingPageResourceId,
    TInt& aCurrentSelectionIndex, 
    const MDesCArray* aItemArray ):
    CAknTransparentCameraSettingPage
    (
    aSettingTitleText,
    aSettingNumber,
    aControlType,
    aEditorResourceId,
    aSettingPageResourceId,
    aCurrentSelectionIndex,
    aItemArray
                                         )
    {
                                       
    }

// ================================ MEMBER FUNCTIONS =========================

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//        
CAiwGenericParamConsumerExt::
    CAiwGenericParamConsumerExt( CEikApplication& aApp ):
    CAiwGenericParamConsumer( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CAiwGenericParamConsumerExt::CreateAppUiL()
// ---------------------------------------------------------------------------
//       
CEikAppUi* CAiwGenericParamConsumerExt::CreateAppUiL()
    {
    return NULL;
    }

// ---------------------------------------------------------------------------
// CXnThemeManagementServiceObserverExt::HandleXnClientMessage()
// ---------------------------------------------------------------------------
//  
void CXnThemeManagementServiceObserverExt::HandleXnClientMessage( 
    TXnServiceCompletedMessage /*aMessage*/ )
    {
    }
    
// ================================ MEMBER FUNCTIONS =========================

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CPslnFWBaseContainerExt::CPslnFWBaseContainerExt()
    {
    iListBox = NULL; 
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd static constructor
// ---------------------------------------------------------------------------
//
void CPslnFWBaseContainerExt::ConstructL( const TRect& aRect )
    {
    
    iListBox = new( ELeave ) CEikTextListBox();
    BaseConstructL( aRect, 0, R_BCTESTDOMAVKONPSLN_LISTBOX );
    }
    
// ---------------------------------------------------------------------------
// CPslnFWBaseContainerExt::ConstructListBoxL()
// ---------------------------------------------------------------------------
//    
void CPslnFWBaseContainerExt::ConstructListBoxL( TInt aResLbxId )
    {
    TResourceReader rReader;
    iCoeEnv->CreateResourceReaderLC( rReader, aResLbxId );
    iListBox->ConstructFromResourceL( rReader );
    CleanupStack::PopAndDestroy(); // rReader
    }
    
// ---------------------------------------------------------------------------
// C++ default Destructor
// ---------------------------------------------------------------------------
//    
CPslnFWBaseContainerExt::~CPslnFWBaseContainerExt()
    {
    }
    
// ---------------------------------------------------------------------------
// CMPslnFWMSKObserverExt::CheckMiddleSoftkeyLabelL()
// ---------------------------------------------------------------------------
//    
void CMPslnFWMSKObserverExt::CheckMiddleSoftkeyLabelL()
    {
    }
    

// ================================ MEMBER FUNCTIONS =========================

// ---------------------------------------------------------------------------
// CPslnFWBaseViewExt::ConstructL()
// ---------------------------------------------------------------------------
//    
void CPslnFWBaseViewExt::ConstructL()
    {   
    }

// ---------------------------------------------------------------------------
// CPslnFWBaseViewExt::NewContainerL()
// ---------------------------------------------------------------------------
//    
void CPslnFWBaseViewExt::NewContainerL()
    {
    if( iContainer )
        delete iContainer;
    iContainer = NULL;
    iContainer = new ( ELeave )CPslnFWBaseContainerExt;
    }

// ---------------------------------------------------------------------------
// CPslnFWBaseViewExt::HandleListBoxSelectionL()
// ---------------------------------------------------------------------------
//   
void CPslnFWBaseViewExt::HandleListBoxSelectionL()
    { 
    }

// ---------------------------------------------------------------------------
// CPslnFWBaseViewExt::GetCaptionL()
// ---------------------------------------------------------------------------
//   
void CPslnFWBaseViewExt::GetCaptionL( TDes& /*aCaption*/ ) const
    {  
    }
    
// ---------------------------------------------------------------------------
// CPslnFWBaseViewExt::GetTabTextL()
// ---------------------------------------------------------------------------
//   
void CPslnFWBaseViewExt::GetTabTextL( TDes& /*aCaption*/ ) const
    {   
    }


// ================================ MEMBER FUNCTIONS =========================

// ---------------------------------------------------------------------------
// CGulIcon* CPslnFWBaseViewExt::CreateIconL()
// ---------------------------------------------------------------------------
//   
CGulIcon* CPslnFWBaseViewExt::CreateIconL()
    {
    return NULL;
    }

// ---------------------------------------------------------------------------
// CPslnFWBaseViewExt::Id()
// ---------------------------------------------------------------------------
//   
TUid CPslnFWBaseViewExt::Id() const
    {
    return KNullUid;
    }
    
// ---------------------------------------------------------------------------
// CItemFinderObserverExt::HandleParsingComplete()
// ---------------------------------------------------------------------------
//        
void CItemFinderObserverExt::HandleParsingComplete()
    {
    
    }
    
// ---------------------------------------------------------------------------
// CMPslnFWAppThemeObserverEx::HandleMessage()
// ---------------------------------------------------------------------------
//    
void CMPslnFWAppThemeObserverExt::HandleMessage( TXnServiceCompletedMessage 
    /*aMessage*/ )
    {
    } 

// ---------------------------------------------------------------------------
// CMPslnFWAppThemeObserverEx::HandleMessage() Overload
// ---------------------------------------------------------------------------
//    
void CMPslnFWAppThemeObserverExt::HandleMessage( 
    const TXnServiceCompletedMessage /*aMessage*/,
    CArrayPtrFlat<CXnODT>& /*aAppThemeList*/ )
    {
        
    }   
//end of file
