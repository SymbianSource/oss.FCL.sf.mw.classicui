/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include <eikfutil.h>
#include <eikappui.h>
#include <eikapp.h>

#include <apgcli.h>
#include <apgicnfl.h>
#include <apgwgnam.h> 

#include <gulicon.h>
#include <gulutil.h>
#include <eikimage.h>

#include <AknIconUtils.h>

#include <AknsUtils.h>
#include <AknsDrawUtils.h>

#include <AknTasHook.h>
#include "AknPanic.h"
#include "AknUtils.h"
#include "aknconsts.h"
#include "akncontext.h"

#include <avkon.mbg>
#include <eikspane.h>

#include "aknnavi.h"
#include "AknBitmapMirrorUtils.h"
#include "AknNaviConstants.h"
#include "aknappui.h"
#include <AknDef.h>


NONSHARABLE_CLASS(CAknContextPaneExtension): public CBase
	{
public:
	CAknContextPaneExtension();
	~CAknContextPaneExtension();
public:
    CEikImage*  iContextImage;
    CEikImage*  iDefaultContextImage;
    TInt        iCurrentColorScheme;
    };

CAknContextPaneExtension::CAknContextPaneExtension()
	{
	}

CAknContextPaneExtension::~CAknContextPaneExtension()
	{
	}

EXPORT_C CAknContextPane::CAknContextPane()
    {
    AKNTASHOOK_ADD( this, "CAknContextPane" );
    }

EXPORT_C CAknContextPane::~CAknContextPane()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );
	if (iExtension)
		{
		AknsUtils::DeregisterControlPosition( iExtension->iContextImage );
		AknsUtils::DeregisterControlPosition( iExtension->iDefaultContextImage );
		delete iExtension->iContextImage;
		delete iExtension->iDefaultContextImage;
		delete iExtension;
		}
    }

EXPORT_C void CAknContextPane::ConstructL()
    {
    CommonConstructL();
    TRAP_IGNORE(SetPictureToDefaultL()); // Trapped because of Java midlet issues
    }


EXPORT_C void CAknContextPane::ConstructFromResourceL(TResourceReader& aReader)
    {
    CommonConstructL();
    ReadFromResourceFileL(aReader);
    }

EXPORT_C void CAknContextPane::SetPicture(const CFbsBitmap* aBitmap, const CFbsBitmap* aMaskBitmap)
    {
    TBool bitmapChanged = EFalse;
    if (iExtension->iContextImage)
        {
        bitmapChanged = ETrue;
        iExtension->iContextImage->SetPictureOwnedExternally(EFalse);
        iExtension->iContextImage->SetPicture(aBitmap, aMaskBitmap);
        }
    else
        {
        // Try to create new iContextImage object.
        TRAPD( error, InitL() );
        if ( !error )
            {
            bitmapChanged = ETrue;
            iExtension->iContextImage->SetPictureOwnedExternally(EFalse);
            iExtension->iContextImage->SetPicture(aBitmap, aMaskBitmap);
            }
        else
            {
            // Ownership taken - delete if there is not memory to create new iContextImage.
            delete aBitmap;
            delete aMaskBitmap;
            }
        }

    if ( bitmapChanged )
        {
        SizeChanged();	
        DrawNow();
        }
    }

EXPORT_C void CAknContextPane::SetPicture(CEikImage* aImage)
    {
    __ASSERT_ALWAYS(aImage && aImage->Bitmap(), Panic(EAknPanicNullPointer));

    delete iExtension->iContextImage;   
    iExtension->iContextImage = aImage;
	if (!iExtension->iContextImage->DrawableWindow())
		{
		TRAP_IGNORE(iExtension->iContextImage->SetContainerWindowL(*this));
		}
	__ASSERT_DEBUG(iExtension->iContextImage->DrawableWindow(), Panic(EAknPanicNullPointer));

    iExtension->iContextImage->SetPictureOwnedExternally(EFalse);

    SizeChanged();
    DrawNow();
    }

EXPORT_C void CAknContextPane::SetPictureFromFileL(const TDesC& aFileName, TInt aMainId, TInt aMaskId)
    {
    delete iExtension->iContextImage;
    iExtension->iContextImage = NULL;
    
    InitL();
    iExtension->iContextImage->CreatePictureFromFileL(aFileName, aMainId, aMaskId);
    
    SizeChanged();
    DrawNow();
    }


EXPORT_C void CAknContextPane::SetFromResourceL(TResourceReader& aReader)
    {
    ReadFromResourceFileL(aReader);
    }


void FindRootApplication(TInt aCount, TInt& aWgId, RArray<RWsSession::TWindowGroupChainInfo>* aWgIds )
    {
    // Go through all window group IDs looking for the current one
    for (TInt i=0;i<aCount;i++)
        {
        RWsSession::TWindowGroupChainInfo wgId=(*aWgIds)[i];
        
        if ( wgId.iId == aWgId ) // found my wg
        	{
            if (wgId.iParentId <= 0) // I'm standalone application
                break;
            else
                {
                aWgId = wgId.iParentId;
                FindRootApplication(aCount, aWgId, aWgIds);
                }
        	}
        }
 
    }


EXPORT_C void CAknContextPane::SetPictureToDefaultL()
    {
    if (iExtension->iDefaultContextImage)
        {
        CFbsBitmap* bitmap = new (ELeave) CFbsBitmap();
        CleanupStack::PushL(bitmap);                
        CFbsBitmap* mask = new (ELeave) CFbsBitmap();                
        
        if ( iExtension->iDefaultContextImage->Bitmap() )
            {
            bitmap->Duplicate(iExtension->iDefaultContextImage->Bitmap()->Handle());
            }
        if ( iExtension->iDefaultContextImage->Mask() )
            {
            mask->Duplicate(iExtension->iDefaultContextImage->Mask()->Handle());
            }
        SetPicture(bitmap, mask); 
        CleanupStack::Pop(); // bitmap
        return;
        }

    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    // statuspane
    TAknLayoutRect statuspane;
    statuspane.LayoutRect(iAvkonAppUi->ApplicationRect(), AknLayout::status_pane(iAvkonAppUi->ApplicationRect(),0));
       
    // context pane
    TAknWindowLineLayout contextPaneLayout = AknLayout::context_pane(statuspane.Rect(), 0);    
    TAknLayoutRect contextPaneLayoutRect;
    contextPaneLayoutRect.LayoutRect(statuspane.Rect(), contextPaneLayout);
    TRect contextPaneRect = contextPaneLayoutRect.Rect(); 

    // context pane elements    
    TAknWindowLineLayout contextPaneElements = 
        AknLayout::Context_pane_elements_Line_1();    
    TAknLayoutRect rect;
    rect.LayoutRect(contextPaneRect, contextPaneElements);

    // -- Wg chaining support ---
    RWsSession& ws = iEikonEnv->WsSession();    

    TInt wgCount=ws.NumWindowGroups();
	TInt wgId = iEikonEnv->RootWin().Identifier();
    
    RArray<RWsSession::TWindowGroupChainInfo>* wgIds=new(ELeave) RArray<RWsSession::TWindowGroupChainInfo>(wgCount);
    CleanupStack::PushL(wgIds);
    CleanupClosePushL(*wgIds);

    User::LeaveIfError(ws.WindowGroupList(wgIds));
    
    FindRootApplication(wgCount, wgId, wgIds );
    
	CleanupStack::PopAndDestroy(2);  // wgids
	
    CApaWindowGroupName* windowName = CApaWindowGroupName::NewLC(ws, wgId);
    TUid appUid  = windowName->AppUid();
	CleanupStack::PopAndDestroy();  //windowName

    // ------

    AknsUtils::CreateAppIconLC( AknsUtils::SkinInstance(), 
        appUid, EAknsAppIconTypeContext,
        bitmap, mask );
    
    SetPictureSize( bitmap, 
        rect.Rect().Size() ) ;

    iExtension->iDefaultContextImage = new (ELeave) CEikImage;
    CFbsBitmap* defaultBitmap = new (ELeave) CFbsBitmap();
    CleanupStack::PushL(defaultBitmap);                
    CFbsBitmap* defaultMask = new (ELeave) CFbsBitmap();                
    defaultBitmap->Duplicate(bitmap->Handle());
    defaultMask->Duplicate(mask->Handle());
    iExtension->iDefaultContextImage->SetPicture(defaultBitmap, defaultMask);
    iExtension->iDefaultContextImage->SetPictureOwnedExternally(EFalse);

    // ownership of the defaultBitmap moved to iDefaultContextImage.
    CleanupStack::Pop( 3 ); // defaultBitmap,  mask, bitmap
    SetPicture( bitmap, mask );    
    }

EXPORT_C const CEikImage& CAknContextPane::Picture() const
    {
    return *(iExtension->iContextImage);
    }

EXPORT_C CEikImage* CAknContextPane::SwapPicture(CEikImage* aNewImage)
    {
    CEikImage* previousImage = iExtension->iContextImage;
    iExtension->iContextImage = aNewImage;
    if (iExtension->iContextImage)
        {
        if (!iExtension->iContextImage->DrawableWindow())
            {
            TRAP_IGNORE( iExtension->iContextImage->SetContainerWindowL(*this) );
            }

        __ASSERT_DEBUG(iExtension->iContextImage->DrawableWindow(), Panic(EAknPanicNullPointer));

        iExtension->iContextImage->SetPictureOwnedExternally(EFalse);
        }
    SizeChanged();
    DrawNow();
    
    return previousImage;
    }


EXPORT_C void CAknContextPane::SizeChanged()
    {
    if (Rect() != TRect(0,0,0,0)) // Fix for Parent getting parent relative data. 
        {
        if (iExtension->iContextImage && iExtension->iContextImage->Bitmap()) 
            {
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect(Rect(), AknLayout::Context_pane_elements_Line_1());

            TBool sameIcons = EFalse;

            if ( iExtension->iDefaultContextImage &&
                 iExtension->iDefaultContextImage->Bitmap() &&
                 iExtension->iDefaultContextImage->Bitmap()->Handle() ==
                 iExtension->iContextImage->Bitmap()->Handle() )
                {
                sameIcons = ETrue;
                }
        
            // This potentially changes bitmap handles.
            SetPictureSize( const_cast<CFbsBitmap*>( iExtension->iContextImage->Bitmap() ),
                layoutRect.Rect().Size());

            if ( sameIcons )
                {
                // Must duplicate again after SetSize.
                CFbsBitmap* bitmap = const_cast<CFbsBitmap*>(
                    iExtension->iDefaultContextImage->Bitmap() );
                CFbsBitmap* mask = const_cast<CFbsBitmap*>(
                    iExtension->iDefaultContextImage->Mask() );

                if ( bitmap )
                    {
                    // ignore error
                    bitmap->Duplicate( iExtension->iContextImage->Bitmap()->Handle() );
                    }

                if ( mask )
                    {
                    // ignore error
                    mask->Duplicate( iExtension->iContextImage->Mask()->Handle() );
                    }
                }

            TSize bmpSize=iExtension->iContextImage->Bitmap()->SizeInPixels();
            TGulAlignment iAlignment;
            iAlignment.SetHAlignment(EHCenter);
            iAlignment.SetVAlignment(EVCenter);
            iExtension->iContextImage->SetRect(iAlignment.InnerRect(Rect(),bmpSize));
            AknsUtils::RegisterControlPosition( iExtension->iContextImage );
            }
        AknsUtils::RegisterControlPosition( this );
        }
    }


EXPORT_C void CAknContextPane::HandleResourceChange( TInt aType ) 
    {
    if ( aType == KEikColorResourceChange || aType==KEikDynamicLayoutVariantSwitch )
        {
        DrawDeferred();
        }
    else if( aType == KAknsMessageSkinChange )
        {
        if( iExtension->iDefaultContextImage && iExtension->iContextImage )
            {
            const CFbsBitmap* defBmp = iExtension->iDefaultContextImage->Bitmap();
            const CFbsBitmap* bmp = iExtension->iContextImage->Bitmap();
            if( defBmp && bmp )
                {
                // Update icon only if the default context image is used.
                // Otherwise, the application is responsible of updating the
                // image upon skin change (since it has set a non-default image).
                if( defBmp->Handle() == bmp->Handle() )
                    {
                    delete iExtension->iDefaultContextImage;
                    iExtension->iDefaultContextImage = NULL;
                    TRAP_IGNORE(SetPictureToDefaultL()); // Ignore error
                    }
                }
            }
        }
    }


EXPORT_C TInt CAknContextPane::CountComponentControls() const
    {
    if (iExtension->iContextImage)
        {
        return 1;
        }
    return 0;
    }


EXPORT_C CCoeControl* CAknContextPane::ComponentControl(TInt /*aIndex*/) const
    {
    return (iExtension->iContextImage);
    }


EXPORT_C void CAknContextPane::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc=SystemGc();

    // screen
    TRect screenRect = iAvkonAppUi->ApplicationRect();
    
    //TAknWindowLineLayout screenLayout = AknLayout::screen();
    //TRect screenRect = screenLayout.Rect();


    // app window
    TAknWindowLineLayout applicationWindowLayout =
        AknLayout::application_window(screenRect);
    
    TAknLayoutRect applicationWindowLayoutRect;
    applicationWindowLayoutRect.LayoutRect(screenRect, applicationWindowLayout);
    TRect applicationWindowRect = applicationWindowLayoutRect.Rect(); 

    // statuspane
    TAknWindowLineLayout statusPaneLayout = 
        AknLayout::status_pane(applicationWindowRect, 0);

    TAknLayoutRect statusPaneLayoutRect;
    statusPaneLayoutRect.LayoutRect(applicationWindowRect, statusPaneLayout);
    TRect statusPaneRect = statusPaneLayoutRect.Rect(); 

    // context pane
    TAknWindowLineLayout contextPaneLayout = 
        AknLayout::context_pane(statusPaneRect, 0);
    
    TAknLayoutRect contextPaneLayoutRect;
    contextPaneLayoutRect.LayoutRect(statusPaneRect, contextPaneLayout);
    TRect contextPaneRect = contextPaneLayoutRect.Rect(); 

    TAknWindowLineLayout naviPaneGraphicsLayout = 
        AknLayout::Status_pane_elements_Line_1();

    TAknWindowLineLayout naviWipeGraphicsLayout = 
        AknLayout::Status_pane_elements_Line_2();

    TAknLayoutRect naviPaneGraphicsLayoutRect;
    naviPaneGraphicsLayoutRect.LayoutRect(statusPaneRect, naviPaneGraphicsLayout);
    TRect naviPaneGraphicsRect = naviPaneGraphicsLayoutRect.Rect(); 

    TAknLayoutRect naviWipeGraphicsLayoutRect;
    naviWipeGraphicsLayoutRect.LayoutRect(statusPaneRect, naviWipeGraphicsLayout);
    TRect naviWipeGraphicsRect = naviWipeGraphicsLayoutRect.Rect(); 

    TRect rect(Rect());

    TRect barRect = contextPaneRect;
    if (barRect.Intersects(naviPaneGraphicsRect))
        {
        barRect.Intersection(naviPaneGraphicsRect);
        
        // calculate new origo, relative to context pane.
        barRect.iTl.iX -= contextPaneRect.iTl.iX;
        barRect.iTl.iY -= contextPaneRect.iTl.iY;
        barRect.iBr.iX -= contextPaneRect.iTl.iX;
        barRect.iBr.iY -= contextPaneRect.iTl.iY;
        }
    else
        {
        barRect = TRect(0,0,0,0);
        }
    

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext(this);

        // Solid or wipe comes from background
    if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
        {
        // Default drawing if skinning is not available
        gc.Clear(rect); 
        gc.SetPenStyle(CGraphicsContext::ENullPen);
        gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        gc.SetBrushColor(AKN_LAF_COLOR(KStatusPaneBackgroundGraphicsColorUsual));
        gc.DrawRect(barRect);
        }
    }


void CAknContextPane::CommonConstructL()
    {
    InitL();
    // Wipe is never used initally anymore 
    SetNaviPaneBackgroundType( EAknNaviPaneBackgroundTypeSolid );
    }


TUid CAknContextPane::AppUid()
    {
    // Returns application's Uid. 
    // In embedded applications, root application's Uid is returned.
    CEikAppUi* root = iEikonEnv->EikAppUi();
    while (root->ContainerAppUi())
        {
        root = root->ContainerAppUi();
        }
    
    CEikApplication* app = root->Application();
    if (app)
        {
        return app->AppDllUid();
        }
    return KNullUid;
    }


void CAknContextPane::ReadFromResourceFileL(TResourceReader& aReader)
    {
    HBufC* bitmapFile = aReader.ReadHBufCL();	// bmp filename
    TInt bitmapId = aReader.ReadInt16();	// bmp id
    TInt maskId = aReader.ReadInt16();	// bmp mask id
    
    if ( bitmapFile ) 
        {
        CleanupStack::PushL(bitmapFile);
        if (bitmapId != -1)
            {
            SetPictureFromFileL(*bitmapFile, bitmapId, maskId);
            }
        CleanupStack::PopAndDestroy();  // bitmapFile
        }
    else
        {
        TRAP_IGNORE(SetPictureToDefaultL()); // Trapped because of Java midlet issues
        }
    }

void CAknContextPane::LoadNaviWipeBitmapL()
    {    
    // Naviwipe is no more used (since 3.0)
    }

void CAknContextPane::SetNaviPaneBackgroundType( TInt /*aType*/ ) 
    {
    // Naviwipe is no more used (since 3.0)
    }

EXPORT_C void CAknContextPane::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknContextPane::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

TTypeUid::Ptr CAknContextPane::MopSupplyObject(TTypeUid aId)
    {
    if(aId.iUid == CAknContextPane::ETypeId)
        {
        // Return self, this code makes it possible to workaround the fact
        // that statuspane controls cannot be safely casted after
        // retrieving them using CEikStatusPaneBase::ControlL().
        // 
        // So now the caller could do something like this rather safely:
        //
        // CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        // CAknContextPane* contextPane = NULL;
        //
        //if (statusPane && 
        //    statusPane->PaneCapabilities(TUid::Uid(EEikStatusPaneUidContext)).IsInCurrentLayout())
        //    {
        //    CCoeControl* control = statusPane->ControlL(TUid::Uid( EEikStatusPaneUidContext ));
        //    control->MopGetObject(contextPane);
        //    }
        //
        //if (contextPane)
        //  {
        //  // The retrieved control was type of CAknContextPane
        //  }
        //else
        //  {
        //  // The retrieved control was NOT type of CAknContextPane. 
        //  // Someone has perhaps swap the control in the statuspane.
        //  }
        return aId.MakePtr(this);
        }

    return CCoeControl::MopSupplyObject(aId);
    }

void CAknContextPane::InitL()
    {
    if (!iExtension)
        {
        iExtension = new (ELeave) CAknContextPaneExtension(); 
        }
    iExtension->iContextImage = new (ELeave) CEikImage;
    iExtension->iContextImage->SetContainerWindowL(*this);
	__ASSERT_DEBUG(iExtension->iContextImage->DrawableWindow(), Panic(EAknPanicNullPointer));
    iExtension->iContextImage->SetNonFocusing();
    iExtension->iContextImage->SetAlignment(EHCenterVCenter);
    }

void CAknContextPane::SetPictureSize(CFbsBitmap* aPicture, TSize aSize)
    {
    const TSize KLegacyScreenSize = TSize(176,208);
    const TSize KLegacyPictureMaxSize = TSize(44,44);
    
    if (!aPicture)
        return;

    TRect screenRect = iAvkonAppUi->ApplicationRect();
    TSize originalSize = aPicture->SizeInPixels();
    
    TBool isLegacyScreenSize = 
        (screenRect.Height() == KLegacyScreenSize.iHeight && 
         screenRect.Width() == KLegacyScreenSize.iWidth);

    TBool isBitmap = !AknIconUtils::IsMifIcon(aPicture);        

    TBool isBitmapValidLegacySize = 
        (originalSize.iHeight <= KLegacyPictureMaxSize.iHeight &&
         originalSize.iWidth <= KLegacyPictureMaxSize.iWidth);

    // If we are in legacy screen size and the given bitmap is bitmap (not SVG originated)
    // and its size is ok we don't set the size. This is done because
    // some legacy app have contextpane icons sizes other than
    // 44x44 and those look better if left not scaled.
    if (isLegacyScreenSize && 
        isBitmap &&
        isBitmapValidLegacySize)        
        {
        return;
        }

    // Perf optimization: We dont set the size if context pane is not in current status pane layout. When
    // status pane layout changes, this method will be called again and size is set then.
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
   	if (statusPane && statusPane->PaneCapabilities(TUid::Uid(EEikStatusPaneUidContext)).IsInCurrentLayout())
   		{
		AknIconUtils::SetSize( aPicture, aSize);
   		}
    }


//  End of File  


