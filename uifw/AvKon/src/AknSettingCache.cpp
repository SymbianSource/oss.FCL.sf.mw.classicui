/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This cache contains certain system settings that are regularly
*                needed in UI controls.
*                AknEnv owns an instance of the cache.
*                Values of the cached settings are initialized when read for the
*                first time.
*                CEikAppUi updates the cache before forwarding change events
*                to application controls, which can then read them from cache.
*
*
*/


// INCLUDE FILES
#include <e32svr.h>
#include "AknSettingCache.h"
#include "AknPanic.h"
#include <AknUtils.h>

#include <e32property.h>
#include <UikonInternalPSKeys.h>    // KUikLayoutState, KUikPreferredOrientation

#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>    // KAknLayoutId
#include <AknFepInternalCRKeys.h>   // KAknFepInputTxtLang

#include <eikdef.h> // event UIDs
#include <languages.hrh>
#include <AknDef.h>
#include "AknDebug.h"

#include <featmgr.h>
// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknSettingCache::NewL()
// -----------------------------------------------------------------------------
//
CAknSettingCache* CAknSettingCache::NewL()
    {
    return new(ELeave) CAknSettingCache;
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::~CAknSettingCache()
// -----------------------------------------------------------------------------
//
CAknSettingCache::~CAknSettingCache()
    {
    iPlugins.Reset();
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::InputLanguage()
// -----------------------------------------------------------------------------
//
EXPORT_C TLanguage CAknSettingCache::InputLanguage()
    {
    if (!(iFlags & EInputLanguage))
        {
        UpdateFromCenRep(KCRUidAknFep, KAknFepInputTxtLang, (TInt&)iInputLanguage, EInputLanguage);
        }

    return iInputLanguage;
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::LayoutId()
// -----------------------------------------------------------------------------
//
EXPORT_C TAknLayoutId CAknSettingCache::LayoutId()
    {
    if (!(iFlags & ELayoutId))
        {
        UpdateFromCenRep(KCRUidAvkon, KAknLayoutId, (TInt&)iLayoutId, ELayoutId);
        }

    return iLayoutId;
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::HardwareLayoutState()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknSettingCache::HardwareLayoutState()
    {
    if (!(iFlags & EHardwareLayout))
        {
        UpdateFromPubSub(KPSUidUikon, KUikLayoutState, (TInt&)iHardwareLayout, EHardwareLayout);
        }

    return iHardwareLayout;
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::PreferredOrientation()
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknSettingCache::PreferredOrientation()
    {
    if (!(iFlags & EPreferredOrientation))
        {
        UpdateFromPubSub(KPSUidUikon, KUikPreferredOrientation,
            (TInt&)iPreferredOrientation, EPreferredOrientation);
        }
        
    return iPreferredOrientation;
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::GlobalUiZoom()
// -----------------------------------------------------------------------------
//
EXPORT_C TAknUiZoom CAknSettingCache::GlobalUiZoom()
    {
    if (!(iFlags & EGlobalUiZoom))
        {
        UpdateFromCenRep(KCRUidAvkon, KAknGlobalUiZoom, (TInt&)iGlobalUiZoom, EGlobalUiZoom);
        }

    return iGlobalUiZoom;
    }


// -----------------------------------------------------------------------------
// CAknSettingCache::Update()
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknSettingCache::Update(TInt aEventId)
    {
    TBool changed(EFalse);

    switch (aEventId)
        {
        case KEikInputLanguageChange:
            {
            changed = UpdateFromCenRep(KCRUidAknFep, KAknFepInputTxtLang, (TInt&)iInputLanguage, EInputLanguage);
            break;
            }

        case KEikDynamicLayoutVariantSwitch:
            {
            changed = UpdateFromCenRep(KCRUidAvkon, KAknLayoutId, (TInt&)iLayoutId, ELayoutId);
            changed |= UpdateFromCenRep(KCRUidAvkon, KAknGlobalUiZoom, (TInt&)iGlobalUiZoom, EGlobalUiZoom);
            break;
            }

        case KAknHardwareLayoutSwitch:
            {
            changed = UpdateFromPubSub(KPSUidUikon, KUikLayoutState, (TInt&)iHardwareLayout, EHardwareLayout);            
            changed |= UpdateFromPubSub(KPSUidUikon, KUikPreferredOrientation, (TInt&)iPreferredOrientation, EPreferredOrientation);
            break;
            }

        default:
            {
            break;
            }
        }

    // only listen to the topmost plugin for a given event
    TBool topMost = ETrue;
    // search in reverse order, as most recent registrations take precedence
    TInt count = iPlugins.Count();
    for(TInt ii = count - 1; ii >= 0; ii--)
        {
        MAknSettingCacheUpdatePlugin* pPlugin = iPlugins[ii];
        if(pPlugin->HandlesEvent(aEventId))
            {
            // update all the plugins, as some or all of them may need to update some cached data
            TBool updated = pPlugin->Update(aEventId);
            if(topMost)
                {
                changed = updated;
                topMost = EFalse;
                }
            }
        }

    return changed;
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::RegisterPlugin
// -----------------------------------------------------------------------------
EXPORT_C void CAknSettingCache::RegisterPluginL(MAknSettingCacheUpdatePlugin* aPlugin)
    {
    iPlugins.AppendL(aPlugin);
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::DeRegisterPlugin
// -----------------------------------------------------------------------------
EXPORT_C void CAknSettingCache::DeRegisterPlugin(MAknSettingCacheUpdatePlugin* aPlugin)
    {
    TInt index = iPlugins.Find(aPlugin);
    if(index != KErrNotFound)
        {
        iPlugins.Remove(index);
        }
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::PluginValue
// -----------------------------------------------------------------------------
EXPORT_C TInt CAknSettingCache::PluginValue(TInt aEventId, TInt& aValue)
    {
    // search in reverse order, as most recent registrations take precedence
    TInt count = iPlugins.Count();
    for(TInt ii = count - 1; ii >= 0; ii--)
        {
        MAknSettingCacheUpdatePlugin* pPlugin = iPlugins[ii];
        if(pPlugin->HandlesEvent(aEventId))
            {
            // only listen to the topmost plugin for a given event
            return pPlugin->GetValue(aEventId, aValue);
            }
        }
    return KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::TransparencyEnabled()
// -----------------------------------------------------------------------------
//  
EXPORT_C TBool CAknSettingCache::TransparencyEnabled()
    {
    if ( !( iFlags & ETransparencyEnabled ) )
        {
        UpdateFromCenRep( KCRUidAvkon, KAknAvkonTransparencyEnabled, 
                          (TInt&)iTransparencyEnabled, ETransparencyEnabled );    
        }
    return iTransparencyEnabled == 1 ? ETrue : EFalse;      
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::CAknSettingCache()
// -----------------------------------------------------------------------------
//
CAknSettingCache::CAknSettingCache() :
    // default values used only in case INI-files do not exist
    iInputLanguage(ELangEnglish), iLayoutId(EAknLayoutIdELAF), iGlobalUiZoom(EAknUiZoomAutomatic)
    {
    }

// -----------------------------------------------------------------------------
// CAknSettingCache::UpdateFromSharedData()
// -----------------------------------------------------------------------------
//
TBool CAknSettingCache::UpdateFromPubSub(const TUid aUid, TUint32 aKey, TInt& aValue, TCacheFlag aFlag)
    {
    TBool changed = EFalse;
    TInt newValue = 0;
    
    TInt err = RProperty::Get(aUid, aKey, newValue);
    
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("xxxx CAknSettingCache::UpdateFromPubSub err=%d value=%d"), err, newValue);
#endif
    
    if (err == KErrNone)
        {
        // cache updated
        iFlags |= aFlag;
        
        if (aValue != newValue)
            {
            changed = ETrue;
            aValue = newValue;
            }
        }
    
    return changed;
    }

TBool CAknSettingCache::UpdateFromCenRep(const TUid aUid, TUint32 aKey, TInt& aValue, TCacheFlag aFlag)
    {
    CRepository* repository = NULL;
    TBool changed = EFalse;
    TInt newValue = 0;
    
    TRAPD(err, repository = CRepository::NewL(aUid));
    
    if (err == KErrNone)
        {
        err = repository->Get(aKey, newValue);
        }
    
    // Special case: automatic detection of the layout ID
    // based on UI language is done here.
    
    // Value -1 is used to indicate 'automatic' layout ID detection.
    
    if ((err == KErrNotFound || newValue == -1) &&
        aUid == KCRUidAvkon &&
        aKey == KAknLayoutId)
        {
        TLanguage uiLanguage = AknLangUtils::UserLanguage();
        switch(uiLanguage)
            {
            case ELangArabic:
            case ELangHebrew:
            case ELangFarsi:
            case ELangUrdu:
                {
                newValue = EAknLayoutIdABRW;
                break;
                }
            case ELangTaiwanChinese:
            case ELangHongKongChinese:
            case ELangPrcChinese:
            case ELangJapanese:
            case KLangTaiwanEnglish:
            case KLangHongKongEnglish:
            case KLangPrcEnglish:
            case KLangJapaneseEnglish:
            case KLangApacMalay:
            case KLangApacEnglish:
            case KLangApacIndonesian:
                {
                newValue = EAknLayoutIdAPAC;
                break;
                }
            default: // all others use ELAF. Thai moved to Elaf since 3.2 release.
                {
                if( FeatureManager::FeatureSupported(KFeatureIdAvkonApac) )
                    { /* If APAC layout is enabled */
                    newValue = EAknLayoutIdAPAC;
                    }
                else
                    { /* Else ELAF */
                newValue = EAknLayoutIdELAF;
                    }
                break;
                }
            }
        
        if (repository)
            {
            err = repository->Set(aKey, newValue);
            }
        }
    
    delete repository;
    
    if (err == KErrNone)
        {
        // cache updated
        iFlags |= aFlag;
        
        if (aValue != newValue)
            {
            changed = ETrue;
            aValue = newValue;
            }
        }
    
    return changed;
    }

//  End of File
