/*
* Copyright (c) 2003 Nokia Corporation and/or its subsidiary(-ies).
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


#include "AknBitmapMirrorUtils.h"
#include <bitdev.h>

enum
    {
    EAknNoMirroring = 0,
    EAknVerticalMirroring,
    EAknHorizontalMirroring
    };

void AknBitmapMirrorUtils::LoadHorizontalMirroredBitmapL(CFbsBitmap* aBitmap, const TDesC& aFileName,TInt32 aId)
    {
    LoadPartialBitmapL(aBitmap, aFileName,aId, KWholeBitmapRect, ETrue);
    }

void AknBitmapMirrorUtils::LoadPartialBitmapL(CFbsBitmap* aBitmap, const TDesC& aFileName,TInt32 aId, TRect aRect, TBool aMirrorHorizontally)
    {
    CFbsBitmap* destinationBitmap = aBitmap;
    User::LeaveIfNull(destinationBitmap);

    CFbsBitmap* sourceBitmap = new (ELeave) CFbsBitmap();   
    CleanupStack::PushL(sourceBitmap);   
    User::LeaveIfError(sourceBitmap->Load(aFileName, aId, ETrue));    
    TSize sourceBitmapSize = sourceBitmap->SizeInPixels();
    
    TRect sourceRect = TRect(aRect);
    if (sourceRect == KWholeBitmapRect)
        {
        sourceRect.iTl.iX = 0;
        sourceRect.iTl.iY = 0;
        sourceRect.iBr.iX = sourceBitmapSize.iWidth;
        sourceRect.iBr.iY = sourceBitmapSize.iHeight;
        }
      
    TSize destinationBitmapSize(sourceRect.Width(), sourceRect.Height()); 
    User::LeaveIfError(destinationBitmap->Create(destinationBitmapSize, sourceBitmap->DisplayMode()));

    CFbsBitmapDevice* destinationDevice = CFbsBitmapDevice::NewL( destinationBitmap );
    CleanupStack::PushL(destinationDevice);

    CFbsBitGc* destinationGc;
    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );

    if (aMirrorHorizontally)
        {
        TRect sourceBitmapBlittingRect( sourceRect.iTl.iX,sourceRect.iTl.iY,sourceRect.iTl.iX + 1,sourceRect.iBr.iY );  
    
        for ( TInt xPos=destinationBitmapSize.iWidth-1; xPos >= 0; xPos-- )
            {
            destinationGc->BitBlt( TPoint(xPos,0), sourceBitmap, sourceBitmapBlittingRect );
            sourceBitmapBlittingRect.iTl.iX++;
            sourceBitmapBlittingRect.iBr.iX++;
            }
        }
    else
        {
        destinationGc->BitBlt( TPoint(0,0), sourceBitmap, sourceRect );
        }

    delete destinationGc;  
    CleanupStack::PopAndDestroy(2); // sourceBitmap, destinationDevice
    }

CFbsBitmap* AknBitmapMirrorUtils::HorizontallyMirrorBitmapL( CFbsBitmap* aBitmap )
    {    
    return PartialBitmapL( aBitmap, KWholeBitmapRect, ETrue );
    }

CFbsBitmap* AknBitmapMirrorUtils::PartialBitmapL( CFbsBitmap* aBitmap, TRect aRect, TBool aMirrorHorizontally )
    {
    User::LeaveIfNull(aBitmap);   
	CFbsBitmap* tmpBitmap = NULL;
    TSize sourceBitmapSize = aBitmap->SizeInPixels();

    TRect sourceRect = TRect(aRect);
    if ( sourceRect == KWholeBitmapRect )
        {
        sourceRect.iTl.iX = 0;
        sourceRect.iTl.iY = 0; 
        sourceRect.iBr.iX = sourceBitmapSize.iWidth;
        sourceRect.iBr.iY = sourceBitmapSize.iHeight;
        if (aMirrorHorizontally)
        	tmpBitmap = CreateBitmapOptimizedL(aBitmap, EAknHorizontalMirroring);
        else
        	tmpBitmap = CreateBitmapOptimizedL(aBitmap, EAknNoMirroring);        
        }
    else
    	{      
	    // Check rect sanity
	    if ( sourceRect.iBr.iX > sourceBitmapSize.iWidth || sourceRect.iBr.iX <= 0 )
	        {
	        sourceRect.iBr.iX = sourceBitmapSize.iWidth;
	        }
	    if ( sourceRect.iBr.iY > sourceBitmapSize.iHeight || sourceRect.iBr.iY <= 0  )
	        {
	        sourceRect.iBr.iY = sourceBitmapSize.iHeight;
	        }
	    if ( sourceRect.iTl.iX >= sourceBitmapSize.iWidth || sourceRect.iTl.iX < 0)
	        {
	        sourceRect.iTl.iX = 0;
	        }
	    if ( sourceRect.iTl.iY >= sourceBitmapSize.iHeight || sourceRect.iTl.iY < 0)
	        {
	        sourceRect.iTl.iY = 0;        
	        }
	    TSize destinationBitmapSize = TSize( sourceRect.Width(), sourceRect.Height() );  

	    // get a copy of wanted rect of source bitmap to tmpBitmap
	    tmpBitmap = new (ELeave) CFbsBitmap();   
	    CleanupStack::PushL( tmpBitmap );                      

	    User::LeaveIfError( tmpBitmap->Create( destinationBitmapSize, aBitmap->DisplayMode() ) );

	    CFbsBitmapDevice* destinationDevice = CFbsBitmapDevice::NewL( tmpBitmap );
	    CleanupStack::PushL( destinationDevice );
	    
	    CFbsBitGc* destinationGc;
	    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );           
	    
	    if ( aMirrorHorizontally )
	        {        
	        TRect sourceBitmapBlittingRect( sourceRect.iTl.iX, sourceRect.iTl.iY,
	            sourceRect.iTl.iX + 1, sourceRect.iBr.iY );  
	        
	        for ( TInt xPos=destinationBitmapSize.iWidth-1; xPos >= 0; xPos-- )
	            {
	            destinationGc->BitBlt( TPoint(xPos,0), aBitmap, sourceBitmapBlittingRect );
	            sourceBitmapBlittingRect.iTl.iX++;
	            sourceBitmapBlittingRect.iBr.iX++;
	            }	    
	        }
	    else
	        {        
	        destinationGc->BitBlt( TPoint(0,0), aBitmap, sourceRect );        
	        }

	    delete destinationGc;  
	    CleanupStack::PopAndDestroy(); // destinationDevice
	    CleanupStack::Pop(); // tmpBitmap    		
    	}        

    return tmpBitmap;
    }

CFbsBitmap* AknBitmapMirrorUtils::CreateMirroredBitmapL(CFbsBitmap* aSourceBitmap, TBool aVerticalMirror, TBool aHorizontalMirror)
    {
    CFbsBitmap* verticalMirroredBitmap = NULL;
    CFbsBitmap* horizontalMirroredBitmap = NULL;

    if (aVerticalMirror)
        {
        verticalMirroredBitmap = CreateBitmapOptimizedL(aSourceBitmap, EAknVerticalMirroring);
        }

    if (aHorizontalMirror)
        {
        if (verticalMirroredBitmap)
            {
            CleanupStack::PushL(verticalMirroredBitmap);            
            horizontalMirroredBitmap =  CreateBitmapOptimizedL(verticalMirroredBitmap, EAknHorizontalMirroring);
            CleanupStack::PopAndDestroy(); // verticalMirroredBitmap
            verticalMirroredBitmap = NULL;
            }
        else
            {
            horizontalMirroredBitmap =  CreateBitmapOptimizedL(aSourceBitmap, EAknHorizontalMirroring);
            }
        }
    

    if (!aHorizontalMirror && !aVerticalMirror)
        {
        verticalMirroredBitmap = CreateBitmapOptimizedL(aSourceBitmap, EAknNoMirroring);
        }

    if (verticalMirroredBitmap)
        {
        return verticalMirroredBitmap;
        }
    else
        {
        return horizontalMirroredBitmap;
        }
        

    }


CFbsBitmap* AknBitmapMirrorUtils::CreateBitmapL(CFbsBitmap* aSourceBitmap, TInt aMirrorDirection)
    {
    User::LeaveIfNull(aSourceBitmap);
    CFbsBitmap* destinationBitmap = new (ELeave) CFbsBitmap();
    CleanupStack::PushL(destinationBitmap);   

    TSize sourceBitmapSize = aSourceBitmap->SizeInPixels();            
    TRect sourceRect = TRect(TPoint(0,0), sourceBitmapSize);
    TSize destinationBitmapSize(sourceRect.Width(), sourceRect.Height()); 

    User::LeaveIfError(destinationBitmap->Create(destinationBitmapSize, aSourceBitmap->DisplayMode()));

    CFbsBitmapDevice* destinationDevice = CFbsBitmapDevice::NewL( destinationBitmap );
    CleanupStack::PushL(destinationDevice);

    CFbsBitGc* destinationGc;
    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );

    switch (aMirrorDirection)
        {
        case EAknVerticalMirroring:
            {
            TRect sourceBitmapBlittingRect( sourceRect.iTl.iX,sourceRect.iTl.iY,sourceRect.iBr.iX,sourceRect.iTl.iY + 1 );  
            for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
                {
                destinationGc->BitBlt( TPoint(0,yPos), aSourceBitmap, sourceBitmapBlittingRect );
                sourceBitmapBlittingRect.iTl.iY++;
                sourceBitmapBlittingRect.iBr.iY++;
                }
            break;
            }

        case EAknHorizontalMirroring:
            {
            TRect sourceBitmapBlittingRect( sourceRect.iTl.iX,sourceRect.iTl.iY,sourceRect.iTl.iX + 1,sourceRect.iBr.iY );      
            for ( TInt xPos=destinationBitmapSize.iWidth-1; xPos >= 0; xPos-- )
                {
                destinationGc->BitBlt( TPoint(xPos,0), aSourceBitmap, sourceBitmapBlittingRect );
                sourceBitmapBlittingRect.iTl.iX++;
                sourceBitmapBlittingRect.iBr.iX++;
                }
            break;
            }

        default:
            {
            destinationGc->BitBlt( TPoint(0,0), aSourceBitmap, sourceRect );
            break;
            }
        }

    delete destinationGc;  
    CleanupStack::Pop(2); // destinationBitmap, destinationDevice
    delete destinationDevice;

    return destinationBitmap;   
    }

CFbsBitmap* AknBitmapMirrorUtils::CreateBitmapOptimizedL(CFbsBitmap* aSourceBitmap, TInt aMirrorDirection)
    {
    // Check if displaymode is optimized, fallback to non-optimized version if not.
    TBool fallback = ETrue;
    TDisplayMode displayMode = aSourceBitmap->DisplayMode();
    switch( displayMode )
        {
        case EGray256:
        case EColor256:
        case EColor4K:
        case EColor64K:
            fallback = EFalse;
            break;
        default:
            fallback = ETrue;
        }

    // Check if mirroring mode is supported, fallback to non-optimized version if not.
	if ((aMirrorDirection != EAknVerticalMirroring) && (aMirrorDirection != EAknHorizontalMirroring))
		{
		fallback = ETrue;	
		}

    if( fallback )
		return CreateBitmapL(aSourceBitmap, aMirrorDirection);
    
	// Prepare destination bitmap
    User::LeaveIfNull(aSourceBitmap);
    CFbsBitmap* destinationBitmap = new (ELeave) CFbsBitmap();
    CleanupStack::PushL(destinationBitmap);   

    TSize sourceBitmapSize = aSourceBitmap->SizeInPixels();            
    TRect sourceRect = TRect(TPoint(0,0), sourceBitmapSize);
    TSize destinationBitmapSize(sourceRect.Width(), sourceRect.Height()); 

    User::LeaveIfError(destinationBitmap->Create(destinationBitmapSize, aSourceBitmap->DisplayMode()));

	// Check source, if rom bitmap or compressed then create uncompressed ram bitmap
    TBool srcTemporary = EFalse;
    if( aSourceBitmap->IsRomBitmap() )
        {
        srcTemporary = ETrue;
        }
        
    // Heap lock for FBServ large chunk to prevent background
    // compression of aSrcBitmap after if IsCompressedInRAM returns EFalse
    aSourceBitmap->LockHeapLC( ETrue ); // fbsheaplock
    TBool fbsHeapLock = ETrue;        
        
    if( aSourceBitmap->IsCompressedInRAM() )
        {
        srcTemporary = ETrue;
        }
    if( aSourceBitmap->ExtendedBitmapType() != KNullUid  )
        {
        srcTemporary = ETrue;
        }

    CFbsBitmap* realSource = aSourceBitmap;
    if( srcTemporary )
        {
        CleanupStack::PopAndDestroy(); // fbsheaplock
        fbsHeapLock = EFalse;
        
        realSource = new (ELeave) CFbsBitmap();
        CleanupStack::PushL( realSource );
        User::LeaveIfError( realSource->Create( sourceBitmapSize, aSourceBitmap->DisplayMode() ) );
        CFbsBitmapDevice* dev = CFbsBitmapDevice::NewL( realSource );
        CleanupStack::PushL( dev );
        CFbsBitGc* gc = NULL;
        User::LeaveIfError( dev->CreateContext( gc ) );
        CleanupStack::PushL( gc );
        gc->BitBlt( TPoint(0,0), aSourceBitmap );
        CleanupStack::PopAndDestroy(2); // dev, gc
        }

	// Heap lock for FBServ large chunk is only needed with large bitmaps.
    if (!fbsHeapLock)
    	{
	    if ( realSource->IsLargeBitmap() || destinationBitmap->IsLargeBitmap() )
	        {
	        destinationBitmap->LockHeapLC( ETrue ); // fbsheaplock
	        }
	    else
	        {
	        CleanupStack::PushL( (TAny*)NULL );
	        }
    	}

    TUint32* srcAddress = realSource->DataAddress();
    TUint32* trgAddress = destinationBitmap->DataAddress();

    if ( displayMode == EColor4K || displayMode == EColor64K )
        {
        TInt srcScanLen16 = CFbsBitmap::ScanLineLength(sourceBitmapSize.iWidth, displayMode) / 2;
        TInt trgScanLen16 = CFbsBitmap::ScanLineLength(destinationBitmapSize.iWidth, displayMode) / 2;
        TInt srcScanLen32 = CFbsBitmap::ScanLineLength(sourceBitmapSize.iWidth, displayMode) / 4;
        TInt trgScanLen32 = CFbsBitmap::ScanLineLength(destinationBitmapSize.iWidth, displayMode) / 4;

	    switch (aMirrorDirection)
	        {
	        case EAknVerticalMirroring:
	            {
		        TUint32* trgAddress32 = trgAddress;
	            TUint32* srcAddress32 = srcAddress;            	
           		TInt trgPos = 0;
            	for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
            		{
		            srcAddress32 = srcAddress + srcScanLen32*yPos;
            		trgAddress32 = trgAddress + trgScanLen32*trgPos;            			
            		memcpy(trgAddress32, srcAddress32, srcScanLen32*4);
            		trgPos++;
            		}
	            break;
	            }
	        case EAknHorizontalMirroring:
	            {
		        TUint16* trgAddress16 = reinterpret_cast<TUint16*>(trgAddress);
	            TUint16* srcAddress16 = reinterpret_cast<TUint16*>(srcAddress);            	
           		TInt xTrgPos = 0;
            	for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
            		{
	           		xTrgPos = 0;            		            		
	            	for ( TInt xPos=destinationBitmapSize.iWidth-1; xPos >= 0; xPos-- )
	            		{
						trgAddress16[xTrgPos] = srcAddress16[xPos];
						xTrgPos++;
	            		}
            		srcAddress16 += srcScanLen16;
	            	trgAddress16 += trgScanLen16;	            		
            		}
	            
	            break;
	            }
	        default:
	            {
	            break;
	            }
	        }
        }
	else if( (displayMode==EGray256) || (displayMode==EColor256) )
        {
        TInt srcScanLen8 = CFbsBitmap::ScanLineLength(sourceBitmapSize.iWidth, displayMode);
        TInt trgScanLen8 = CFbsBitmap::ScanLineLength(destinationBitmapSize.iWidth, displayMode);
        TInt srcScanLen32 = CFbsBitmap::ScanLineLength(sourceBitmapSize.iWidth, displayMode) / 4;
        TInt trgScanLen32 = CFbsBitmap::ScanLineLength(destinationBitmapSize.iWidth, displayMode) / 4;
                
	    switch (aMirrorDirection)
	        {
	        case EAknVerticalMirroring:
	            {
		        TUint32* trgAddress32 = trgAddress;
	            TUint32* srcAddress32 = srcAddress;            	
           		TInt trgPos = 0;
            	for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
            		{
		            srcAddress32 = srcAddress + srcScanLen32*yPos;
            		trgAddress32 = trgAddress + trgScanLen32*trgPos;            			
            		memcpy(trgAddress32, srcAddress32, srcScanLen32*4);
            		trgPos++;
            		}
	            break;
	            }
	        case EAknHorizontalMirroring:
	            {
		        TUint8* trgAddress8 = reinterpret_cast<TUint8*>(trgAddress);
	            TUint8* srcAddress8 = reinterpret_cast<TUint8*>(srcAddress);            	
           		TInt xTrgPos = 0;
            	for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
            		{
	           		xTrgPos = 0;            		            		
	            	for ( TInt xPos=destinationBitmapSize.iWidth-1; xPos >= 0; xPos-- )
	            		{
						trgAddress8[xTrgPos] = srcAddress8[xPos];
						xTrgPos++;
	            		}
            		srcAddress8 += srcScanLen8;
	            	trgAddress8 += trgScanLen8;	            			            
            		}
	            break;
	            }
	        default:
	            {
	            break;
	            }        	            
	        }
        }

	CleanupStack::PopAndDestroy(); // fbsheaplock

    if( srcTemporary )
        {
        CleanupStack::PopAndDestroy(); // realSource
        }

    CleanupStack::Pop(); // destinationBitmap
    return destinationBitmap;   
    }
