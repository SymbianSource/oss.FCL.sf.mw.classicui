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
* Description:  declaration of document
*
*/


#ifndef C_BCTESTDOMAVKONPSLNEXT_H
#define C_BCTESTDOMAVKONPSLNEXT_H

#include <akntransitionutils.h>
#include <akntransparentcamerasettingpage.h>
#include <genericparamconsumer.h>
#include <xnthememanagement.h>
#include <pslnfwbasecontainer.h>
#include <mpslnfwmsklabelobserver.h>
#include <pslnfwbaseview.h>
#include <itemfinder.h>
#include <mpslnfwappthemeobserver.h>

class MDesCArray;
class CAknTransparentCameraSettingPage;
class CGulIcon;
class MItemFinderObserver;
class CXnODT;
class MPslnFWAppThemeObserver;


/**
 *  CAknTransitionExt class create just for test CAknTransition
 */
class CAknTransitionExt : public CBase,
                          public MAknTransitionUtilsObserver
    { 
    
public:

    /**
     * C++ default constructor
     */ 
    CAknTransitionExt();
    
    /**
     * C++ default destructor
     */ 
    virtual ~CAknTransitionExt();
    
    /**
     * Callback function
     */ 
    virtual TInt AknTransitionCallback( TInt, TInt, 
        const TDesC8* );

    };
 
    
/**
 *  CAknTransparentCameraSettingPageExt class create just for test 
 *  CAknTransparentCameraSettingPage
 */
class CAknTransparentCameraSettingPageExt : public CAknTransparentCameraSettingPage
    {
    
    friend class CBCTestDomAknCase;
    
public:

    /**
     * C++ default constructor
     */ 
    CAknTransparentCameraSettingPageExt( TInt aResourceID, 
        TInt& aCurrentSelectionIndex, 
        const MDesCArray* aItemArray );
    /**
     * C++ default constructor
     */ 
    CAknTransparentCameraSettingPageExt( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,
        TInt& aCurrentSelectionIndex, 
        const MDesCArray* aItemArray );
    
    };
  
/**
 *  CAiwGenericParamConsumerExt class create just for test 
 *  CAiwGenericParamConsumer
 */
class CAiwGenericParamConsumerExt : public CAiwGenericParamConsumer
    {
    
    friend class CBCTestDomJPLangCase;
    
public:

    /**
     * C++ default constructor
     */ 
    CAiwGenericParamConsumerExt( CEikApplication& aApp );
    
    /**
     * CreateAppUiL()
     */ 
    CEikAppUi* CreateAppUiL();
    
    };

/**
 *  CXnThemeManagementServiceObserverExt class
 */    
class CXnThemeManagementServiceObserverExt : public CBase,
    MXnThemeManagementServiceObserver
    {
    
public:

    /**
     * HandleXnClientMessage()
     */ 
    virtual void HandleXnClientMessage( TXnServiceCompletedMessage 
        /*aMessage*/ );
                                        
    };


/**
 *  CPslnFWBaseContainerExt class create just for test 
 *  CPslnFWBaseContainer
 */    
class CPslnFWBaseContainerExt : public CPslnFWBaseContainer
    {
    
    friend class CBCTestDomPslnCase;
    
public:

    /**
     * C++ default constructor
     */ 
    CPslnFWBaseContainerExt();
    
    /**
     * Symbian 2nd static constructor
     */
    void ConstructL( const TRect& aRect );
    
    /**
     * C++ default destructor
     */ 
    ~CPslnFWBaseContainerExt();
    
    /**
     * Construct ListBox from resource id
     */ 
    void ConstructListBoxL( TInt aResLbxId );
    
    };

/**
 *  Test Class CMPslnFWMSKObserverExt
 */       
class CMPslnFWMSKObserverExt : public CBase,
    public MPslnFWMSKObserver
    {
    
    friend class CBCTestDomPslnCase;
    
public:

    /**
     * interface function implemented to test
     */ 
    void CheckMiddleSoftkeyLabelL();
    
    };

/**
 *  CPslnFWBaseViewExt class create just for test 
 *  CPslnFWBaseView
 */    
class CPslnFWBaseViewExt : public CPslnFWBaseView
    {
    
    friend class CBCTestDomPslnCase;
    
public:

    /**
     * Symbian 2nd static constructor
     */
    void ConstructL();

    /**
     * NewContainerL()
     */
    void NewContainerL();

    /**
     * HandleListBoxSelectionL()
     */
    void HandleListBoxSelectionL();
    
    /**
     * GetCaptionL()
     */
    void GetCaptionL( TDes& ) const;
    
    /**
     * GetTabTextL()
     */
    virtual void GetTabTextL( TDes& ) const;
    
    /**
     * CreateIconL()
     */
    virtual CGulIcon* CreateIconL();

    /**
     * Id()
     */
    TUid Id() const;
    
    };

/**
 *  Test Class CMPslnFWAppThemeObserverExt 
 */    
class CItemFinderObserverExt : public CBase ,
    public MItemFinderObserver
    {
    
public:

    void HandleParsingComplete();
    };

/**
 *  Test Class CMPslnFWAppThemeObserverExt 
 */    
class CMPslnFWAppThemeObserverExt : public CBase,
    public MPslnFWAppThemeObserver
    {
    
public:

    /**
     * HandleMessage()
     */
    void HandleMessage( TXnServiceCompletedMessage );
    
    /**
     * HandleMessage() Overload
     */
    void HandleMessage( 
    const TXnServiceCompletedMessage,
        CArrayPtrFlat<CXnODT>& );
    };

#endif
//end of file
