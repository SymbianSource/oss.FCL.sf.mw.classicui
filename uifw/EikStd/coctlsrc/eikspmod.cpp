/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  EIKON Status Pane model and layouts.
*
*/


#include <eikspmod.h>
#include <barsread.h>
#include <eikenv.h>
#include <eikcoctl.rsg>
#include <AknSgcc.h>
#include <aknenv.h>
#include <aknlayout.cdl.h>
#include <AknUtils.h>
#include <AknLayout.lag>
#include <applayout.cdl.h>

#include <aknlayoutscalable_avkon.cdl.h>
#include "layoutmetadata.cdl.h"

inline TAknWindowComponentLayout DoCompose(TAknWindowComponentLayout aLine1, TAknWindowComponentLayout aLine2) 
    { 
    return TAknWindowComponentLayout::Compose(aLine1, aLine2); 
    }

inline TAknTextComponentLayout DoComposeText(TAknWindowComponentLayout aLine1, TAknTextComponentLayout aLine2) 
    { 
    return TAknWindowComponentLayout::ComposeText(aLine1, aLine2); 
    }

const TInt KStatusPaneSetInitGranularity = 4;
const TInt KEikSpanePositionMask = 3;


inline TBool TEikStatusPaneInit::Initialized() { return iFlags & KEikStatusPaneInitInitializedBit; }
inline void TEikStatusPaneInit::SetInitialized() { iFlags |= KEikStatusPaneInitInitializedBit; }

inline CEikStatusPaneLayoutTree::TDirection CEikStatusPaneLayoutTree::Direction() { return (iFlags & KEikStatusPaneDirectionBit) ? EVertical : EHorizontal; }
inline TInt CEikStatusPaneLayoutTree::Size() { return iSize; }
inline TBool CEikStatusPaneLayoutTree::Stretchable() { return iFlags & EEikStatusPaneIsStretchable; }


TEikStatusPaneInit::TEikStatusPaneInit()
: iControlId(0), iControlResource(0), iFlags(0)
	{
	}

TEikStatusPaneInit::TEikStatusPaneInit(const TEikStatusPaneInit& aCopy)
	{
	*this = aCopy;
	}

TEikStatusPaneInit& TEikStatusPaneInit::operator=(const TEikStatusPaneInit& aCopy)
	{
	// Don't copy id or flags - these will have been set when this structure was first loaded
	if (aCopy.iControlId)
		{
		iControlId = aCopy.iControlId;
		iControlResource = aCopy.iControlResource;
		}

	return *this;
	}

void TEikStatusPaneInit::LoadDefaults(TResourceReader& aResource)
	{
	iId = TUid::Uid(aResource.ReadInt32());
	iFlags = aResource.ReadUint16();
	iControlId = aResource.ReadUint16();
	iControlResource = aResource.ReadUint32();
	}



CEikStatusPaneSetInit* CEikStatusPaneSetInit::NewL()
	{
	CEikStatusPaneSetInit* self = new(ELeave) CEikStatusPaneSetInit();
	return self;
	}

CEikStatusPaneSetInit::~CEikStatusPaneSetInit()
	{
	}

void CEikStatusPaneSetInit::LoadDefaultsL(TResourceReader& aResource)
	{
	const TBool initialized = (Count() != 0);
	const TInt count=aResource.ReadInt16();

	for (TInt ii=0;ii<count;++ii)
		{
		TEikStatusPaneInit init;
		init.LoadDefaults(aResource);
		if ( init.ControlResourceId() )
		    {
		    if (initialized)
			    {
			    FindL(init.Id()) = init;
			    }
		    else
			    {
			    AppendL(init);
			    }
		    }
		}
	}

CEikStatusPaneSetInit::CEikStatusPaneSetInit() 
: CArrayFixFlat<TEikStatusPaneInit>(KStatusPaneSetInitGranularity)
	{
	}

TEikStatusPaneInit& CEikStatusPaneSetInit::FindL(const TPaneId& aPaneId)
	{
	for (TInt i=0; i<Count(); i++)
		{
		if (At(i).Id() == aPaneId)
			return At(i);
		}

	User::Leave(KErrNotFound);
	return At(0);	// will never get here
	}

CEikStatusPaneLayoutTree::~CEikStatusPaneLayoutTree()
	{
	if (iSubPanes)
		iSubPanes->ResetAndDestroy();
	delete iSubPanes;
	}

CEikStatusPaneLayoutTree* CEikStatusPaneLayoutTree::NewL(CEikStatusPaneLayout* aLayout, TResourceReader& aResource, TDirection aDefaultDirection)
	{
	CEikStatusPaneLayoutTree* self = new(ELeave) CEikStatusPaneLayoutTree(aLayout, aDefaultDirection);
	CleanupStack::PushL(self);
	self->ConstructL(aResource);
	CleanupStack::Pop();
	return self;
	}

CEikStatusPaneLayoutTree* CEikStatusPaneLayoutTree::Find(const TPaneId& aPaneId)
	{
	if (iId == aPaneId)
		return this;
	else if (iSubPanes)
		{
		for (TInt i=0; i<iSubPanes->Count(); i++)
			{
			CEikStatusPaneLayoutTree* pane = iSubPanes->At(i)->Find(aPaneId);
			if (pane)
				return pane;
			}
		}

	return NULL;
	}

CEikStatusPaneLayoutTree::CEikStatusPaneLayoutTree(CEikStatusPaneLayout* aLayout, TDirection aDefaultDirection)
: iLayout(aLayout)
	{
	SetDirection(aDefaultDirection);
	}

void CEikStatusPaneLayoutTree::ConstructL(TResourceReader& aResource)
	{
	iId.iUid = aResource.ReadInt32();

	TDirection dir = Direction();
	iFlags = aResource.ReadUint16();
	SetDirection(dir);

	iSize = aResource.ReadUint16();

	TDirection subDir = Direction() == EVertical ? EHorizontal : EVertical;	// Change direction for sub panes

	const TInt count=aResource.ReadInt16();
	if (count > 0)
		{
		iSubPanes = new(ELeave) CSubPaneArray(count);
		for (TInt ii=0;ii<count;++ii)
			{
			CEikStatusPaneLayoutTree* pane = CEikStatusPaneLayoutTree::NewL(iLayout, aResource, subDir);
			CleanupStack::PushL(pane);
			iSubPanes->AppendL(pane);
			CleanupStack::Pop();		// pane
			}
		}
	}

void CEikStatusPaneLayoutTree::Layout()
	{
	if (!iSubPanes)
		return;

	TInt unallocedSize = Direction()==EHorizontal ? iRect.Width() : iRect.Height();
	TInt stretchSize = 0;

	TInt count = iSubPanes->Count();
	TInt i;
	for (i=0; i<count; i++)
		{
		CEikStatusPaneLayoutTree* subPane = iSubPanes->At(i);

		TInt size = subPane->Size();

		if (subPane->Stretchable())
			stretchSize += size;
		else
			unallocedSize -= size;
		}

	TPoint pos( iRect.iTl );

	for (i=0; i<count; i++)
		{
		CEikStatusPaneLayoutTree* subPane = iSubPanes->At(i);

		TInt size( subPane->Size() );

		if (size > 0 && subPane->Stretchable() && stretchSize != 0)
			{
			TInt oldSize = size;
			size = (size * unallocedSize) / stretchSize;
			unallocedSize -= size;
			stretchSize -= oldSize;
			}

		TSize subSize( iRect.Size() );
		if (Direction()==EHorizontal)
			subSize.iWidth = size;
		else
			subSize.iHeight = size;
		subPane->SetRect(TRect(pos,subSize));

		if (Direction()==EHorizontal)
			pos.iX += size;
		else
			pos.iY += size;
		}
	}

void CEikStatusPaneLayoutTree::SetDirection(TDirection aDirection)
	{
	if (aDirection == EVertical)
		iFlags |= KEikStatusPaneDirectionBit;
	else
		iFlags &= ~KEikStatusPaneDirectionBit;
	}

void CEikStatusPaneLayoutTree::SetStretchable(TBool aStretchable)
	{
	if (aStretchable)
		iFlags |= EEikStatusPaneIsStretchable;
	else
		iFlags &= ~EEikStatusPaneIsStretchable;
	}

void CEikStatusPaneLayoutTree::SetRect(const TRect& aRect)
	{
	iRect = aRect;
	Layout();
	}

void CEikStatusPaneLayoutTree::AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor)
	{
	if (iId.iUid != 0)
		aVisitor->VisitL(this);
	
	if (iSubPanes)
		{
		for (TInt i=0; i<iSubPanes->Count(); i++)
			{
			iSubPanes->At(i)->AcceptL(aVisitor);
			}
		}
	}

void CEikStatusPaneLayoutTree::SetAknLayoutUsed(TBool aAknLayoutUsed) 
    {
    if (aAknLayoutUsed)
        {
        iFlags |= EEikStatusPaneLayoutAknLafDefined; 
        }
    else
        {
        iFlags &= ~EEikStatusPaneLayoutAknLafDefined; 
        }
    }

TBool CEikStatusPaneLayoutTree::AknLayoutUsed()
    {
    if ( iFlags & EEikStatusPaneLayoutAknLafDefined )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }


void CEikStatusPaneLayoutTree::Layout(TInt aLayoutId)
    {
    if (!AknLayoutUsed())
        {
        Layout();
        }
    else
        {
        TRect rectFromAknLayout( AknLayoutRect(aLayoutId, iId) );
        if (rectFromAknLayout.Size() != TSize(0,0))
            {
            iRect = rectFromAknLayout;
            }

	    if (!iSubPanes)
		    return;

	    TInt count = iSubPanes->Count();
	    TInt i;
	    for (i=0; i<count; i++)
		    {
		    CEikStatusPaneLayoutTree* subPane = iSubPanes->At(i);
		    subPane->SetAknLayoutUsed(ETrue);
		    subPane->Layout(aLayoutId);
		    }
        }
    }

TRect CEikStatusPaneLayoutTree::AknLayoutRect(TInt aLayoutId, TPaneId aPaneId)
    {
    const TBool idleIndicatorsInLandscapeAreVertical = EFalse;

	// Note that small digital clock cannot be shown in such displays that have smaller aspect ratio than 4:3. 
#ifndef __SERIES60_31__  
    TBool smallDigitalClockInStacon = ETrue;
	TBool smallDigitalClockInLandscapeFlatSpUsual = ETrue; 
	TBool smallDigitalClockInLandscapeFlatSpIdle = ETrue;  
#else
    TBool smallDigitalClockInStacon = EFalse;
	TBool smallDigitalClockInLandscapeFlatSpUsual = EFalse;
	TBool smallDigitalClockInLandscapeFlatSpIdle = EFalse;
#endif    
    
    TRect paneRect; // initialises to (0,0,0,0);
    TRect parentRect; // initialises to (0,0,0,0);
    TAknWindowLineLayout layout;
    Mem::FillZ(&layout, sizeof(layout));

    const TRect& screenRect = iLayout->iScreenRect; 
    const TRect& mainPaneRect = iLayout->iMainPaneRect;
    const TRect& usualStatusPaneRect = iLayout->iUsualStatusPaneRect;
    const TRect& applicationWindowRect = iLayout->iApplicationWindowRect;

	const AknLayout::CInstance& aknLayout = iLayout->iAknLayout;
	const AknLayoutScalable_Avkon::CInstance& aknLayoutScalable_Avkon = iLayout->iAknLayoutScalable_Avkon;

	switch (aLayoutId)
		{
		case R_AVKON_STATUS_PANE_LAYOUT_USUAL:
		case R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED:
	        {
	        parentRect = usualStatusPaneRect;
	        switch(aPaneId.iUid)
	            {
	            case EEikStatusPaneUidNavi: 
	                {
	                layout = aknLayoutScalable_Avkon.navi_pane(0).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidSignal:
	                {
	                layout = aknLayoutScalable_Avkon.signal_pane(0).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidContext:
	                {
	                layout = aknLayoutScalable_Avkon.context_pane(0).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidTitle:
	                {
	                layout = aknLayoutScalable_Avkon.title_pane(0).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidIndic:
	                {
	                layout = aknLayoutScalable_Avkon.uni_indicator_pane(0).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidBattery:
	                {
	                layout = aknLayoutScalable_Avkon.battery_pane(0).LayoutLine();
	                break;
	                }
	            }
	        break;
	        }

		case R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT:
		case R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT:
	        {
	        // Final check for small digital clock, shown only in resolutions having aspect 
	        // ratio equal or wider than qvga because otherwise there is no space for it.
	        if (smallDigitalClockInStacon)
	        	{
	        	TReal aspectRatio = TReal(screenRect.Width()) / TReal(screenRect.Height());
	        	if (aspectRatio < 1.33)
	        		smallDigitalClockInStacon = EFalse;	        			
	        	}
	        
	        
	        TInt variety = 0;
	        TInt clockVariety = 1;
	        if (aLayoutId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT)
	            {
	            // softkeys left
	            variety = 1; 
	            clockVariety = 3;
	            }

			const TRect layout1Rect( iLayout->iStaconLayout1Rect );
			const TRect layout2Rect( iLayout->iStaconLayout2Rect );

	        switch(aPaneId.iUid)
	            {
	            case EEikStatusPaneUidNavi: 
	                {
	                // If clock is shown, then use different variety for navipane
                    if (smallDigitalClockInStacon)
                    	variety +=2;	
	                
	                parentRect = layout2Rect;
	                layout = aknLayoutScalable_Avkon.navi_pane_stacon(variety).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidSignal:
	                {
	                parentRect = layout1Rect;
	                layout = aknLayoutScalable_Avkon.signal_pane_stacon(variety).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidTitle:
	                {
	                parentRect = layout1Rect;
                    if (smallDigitalClockInStacon)
                    	{
                    	TInt titleVariety = 4;
			            if (aLayoutId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT)
			                {
							titleVariety = 5;
			                }
		                layout = aknLayoutScalable_Avkon.title_pane_stacon(titleVariety).LayoutLine();                		                    	
                    	}
                    else
                    	{
		                layout = aknLayoutScalable_Avkon.title_pane_stacon(variety).LayoutLine();                		
                    	}	
	                break;
	                }
	            case EEikStatusPaneUidIndic:
	                {
                    if (smallDigitalClockInStacon)
                    	{
                    	TInt indicatorVariety = 1;
			            if (aLayoutId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT)
			                {
							indicatorVariety = 5;
			                }
	                    parentRect = layout1Rect;
	                    layout = aknLayoutScalable_Avkon.indicator_nsta_pane_cp2(indicatorVariety).LayoutLine();                		
                    	}
                    else
                    	{	                
	                	parentRect = layout1Rect;
	                	layout = aknLayoutScalable_Avkon.uni_indicator_pane_stacon(variety).LayoutLine();
	                    }
	                break;
	                }
	            case EEikStatusPaneUidBattery:
	                {
	                parentRect = layout2Rect;
	                layout = aknLayoutScalable_Avkon.battery_pane_stacon(variety).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidDigitalClock:
	                {
	                if (smallDigitalClockInStacon)
	                	{
		                parentRect = layout2Rect;
	 	               	layout = aknLayoutScalable_Avkon.clock_nsta_pane_cp2(clockVariety).LayoutLine();                		
	                	}
	                break;
	                }	             
	            }
	        break;
	        }

		case R_AVKON_STATUS_PANE_LAYOUT_SMALL:
	        {	        
	        switch(aPaneId.iUid)
	            {
	            // In this layout navi pane gets the whole small status pane area.
	            case EEikStatusPaneUidNavi: 
	                {
	                paneRect = iLayout->iSmallStatusPaneRect;
	                break;
	                }
	            }
	        break;
	        }

		case R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE:
		case R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED:
	        {
	        parentRect = iLayout->iSmallStatusPaneRect;
	        switch(aPaneId.iUid)
	            {
	            case EEikStatusPaneUidNavi: 
	                {
	                // avkon LAF doesn't provide this directly, some calculations are needed.
	                paneRect = parentRect;
	                TAknWindowLineLayout smallStatusSignalLayout(
	                    AknLayoutScalable_Avkon::status_small_pane_g2(0).LayoutLine() );
	                TAknLayoutRect smallStatusSignalLayoutRect;
	                smallStatusSignalLayoutRect.LayoutRect(parentRect, smallStatusSignalLayout);
	                TRect smallStatusSignalRect( smallStatusSignalLayoutRect.Rect() );

	                if (AknLayoutUtils::LayoutMirrored())
	                    {
	                    paneRect.iBr.iX -= smallStatusSignalRect.Width();
	                    }
	                else
	                    {
	                    paneRect.iTl.iX += smallStatusSignalRect.Width();
	                    }

	                break;
	                }
	            case EEikStatusPaneUidSignal:
	                {
	                layout = AknLayoutScalable_Avkon::status_small_pane_g2(0).LayoutLine();
                    // Adjustment needed for BSK LSC for navi pane and signal pane to be the same height
	                layout.iH = parentRect.Height();
	                break;
	                }
	            }
	        break;
	        }

		case R_AVKON_STATUS_PANE_LAYOUT_IDLE:
		case R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED:
	        {
	        // by default "idle" statuspane values have "usual" statuspane as parent in LAF
	        parentRect = usualStatusPaneRect;
	        switch(aPaneId.iUid)
	            {
	            case EEikStatusPaneUidNavi: 
	                {
	                layout = aknLayout.navi_pane(1);                
	                break;
	                }
	            case EEikStatusPaneUidSignal:
	                {
	                layout = aknLayout.signal_pane(parentRect);
	                break;
	                }

	            case EEikStatusPaneUidBattery:
	                {
	                layout = aknLayout.battery_pane(parentRect);
	                break;
	                }
	            case EEikStatusPaneUidTitle:
	                {
	                layout = aknLayout.title_pane(1);
	                break;
	                }
	            case EEikStatusPaneUidIndic:
	                {
	                // Exceptionally mainpane as parent
	                parentRect = mainPaneRect;
	                layout = aknLayout.indicator_pane();              
	                break;
	                }
	            case EEikStatusPaneUidClock:
	                {
	                // Exceptionally idle statuspane as parent
				    TAknWindowLineLayout idleStatusPaneLayout( aknLayout.status_pane(applicationWindowRect, 1) );
				    TAknLayoutRect idleStatusPaneLayoutRect;
				    idleStatusPaneLayoutRect.LayoutRect(applicationWindowRect, idleStatusPaneLayout);
	                parentRect = idleStatusPaneLayoutRect.Rect(); 
	                layout = aknLayout.context_pane(parentRect, 1);                
	                break;
	                }
	            }
	        break;
	        }

		case R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE:
		case R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED:
	        {
	        switch(aPaneId.iUid)
	            {
	            case EEikStatusPaneUidBattery: 
	                {
	                if (Layout_Meta_Data::IsLandscapeOrientation())
	                     {
	                     TAknLayoutRect layoutRect;
	                     TAknWindowComponentLayout parentLayout = aknLayoutScalable_Avkon.area_top_pane(8);
	                     layoutRect.LayoutRect(screenRect, parentLayout.LayoutLine());
	                     parentRect = layoutRect.Rect();
	                     layout = aknLayoutScalable_Avkon.battery_pane(2).LayoutLine();
	                     }
	                 else
	                     {
	                     parentRect = usualStatusPaneRect;
	                     layout = aknLayout.battery_pane(parentRect);
	                     }
	                break;
	                }
	            }
	        break;
	        }

		case R_AVKON_STATUS_PANE_LAYOUT_VT:
		case R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED:
	        {
	        parentRect = usualStatusPaneRect;
	        switch(aPaneId.iUid)
	            {
	            case EEikStatusPaneUidNavi: 
	                {
	                layout = aknLayout.navi_pane(1);                
	                break;
	                }
	            case EEikStatusPaneUidSignal:
	                {
	                layout = aknLayout.signal_pane(parentRect);
	                break;
	                }
	            case EEikStatusPaneUidBattery: 
	                {
	                layout = aknLayout.battery_pane(parentRect);
	                break;
	                }
	            case EEikStatusPaneUidContext: 
	                {
	                // note, uses idle version of context pane but needs to 
	                // have usual statuspane as parent to provide correct height.
	                layout = aknLayout.context_pane(parentRect, 1);                
	                break;
	                }
	            case EEikStatusPaneUidTitle: 
	                {
	                // LAF does not anymore define this. We calculate.
	                RRegion titleRegion;                               
	                layout = aknLayout.title_pane(1); // Idle titlepane

	                TAknLayoutRect LayoutRect;
	                LayoutRect.LayoutRect(parentRect, layout);
	                paneRect = LayoutRect.Rect(); 
	                                 
	                layout = aknLayout.uni_indicator_pane(parentRect);                
	                LayoutRect.LayoutRect(parentRect, layout);
	                TRect indicatorRect( LayoutRect.Rect() );
	                
	                // Title and indicator overlaps, reduce indicator area.
	                titleRegion.AddRect(paneRect);
	                titleRegion.SubRect(indicatorRect);
	                
	                paneRect = titleRegion.BoundingRect();
	                titleRegion.Close();
	                break;
	                }
	            case EEikStatusPaneUidIndic:
	                {
	                layout = aknLayout.uni_indicator_pane(parentRect);                
	                break;
	                }
	            }
			break;
	        }

		case R_AVKON_STATUS_PANE_LAYOUT_USUAL_WITH_BATTERY_PANE:
	        {
	        parentRect = usualStatusPaneRect;
	        switch(aPaneId.iUid)
	            {
	            case EEikStatusPaneUidNavi: 
	                {
	                layout = aknLayout.navi_pane(0);
	                break;
	                }
	            case EEikStatusPaneUidSignal:
	                {
	                layout = aknLayout.signal_pane(parentRect);
	                break;
	                }
	            case EEikStatusPaneUidContext:
	                {
	                layout = aknLayout.context_pane(parentRect, 0);
	                break;
	                }
	            case EEikStatusPaneUidTitle:
	                {
	                layout = aknLayout.title_pane(0);
	                break;
	                }
	            case EEikStatusPaneUidIndic:
	                {
	                layout = aknLayout.uni_indicator_pane(parentRect);
	                break;
	                }
	            case EEikStatusPaneUidBattery:
	                {
	                layout = aknLayout.battery_pane(parentRect);
	                break;
	                }
	            }
	        break;
	        }

		case R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT:
		case R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT:
	        {
	        if ( Layout_Meta_Data::IsLandscapeOrientation() )
	            { 
	            
		        // Final check for small digital clock, shown only in resolutions having aspect 
		        // ratio equal or wider than qvga because otherwise there is no space for it.
		        if (smallDigitalClockInStacon)
		        	{
		        	TReal aspectRatio = TReal(screenRect.Width()) / TReal(screenRect.Height());
		        	if (aspectRatio < 1.33)
		        		smallDigitalClockInStacon = EFalse;	        			
		        	}
	               
	            TInt variety = 0;
	            TInt clockVariety = 1;
	            if (aLayoutId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT)
	                {
	                variety = 1; // softkeys left
	                clockVariety = 3;
	                }

				const TRect layout1Rect( iLayout->iStaconLayout1Rect );
				const TRect layout2Rect( iLayout->iStaconLayout2Rect );

	            switch(aPaneId.iUid)
	                {
	                case EEikStatusPaneUidNavi: 
	                    {
		                // If clock is shown, then use different variety for navipane                    
	                    if (smallDigitalClockInStacon)
	                    	variety +=2;	
	                    
	                    parentRect = layout2Rect;
	                    layout = aknLayoutScalable_Avkon.navi_pane_stacon(variety).LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidSignal:
	                    {
	                    parentRect = layout1Rect;
	                    layout = aknLayoutScalable_Avkon.signal_pane_stacon(variety).LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidTitle:
	                    {
	                    if (smallDigitalClockInStacon)
	                    	{
		                    parentRect = layout1Rect;
	                    	TInt titleVariety = 4;
				            if (aLayoutId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT)
				                {
								titleVariety = 5;
				                }
			                layout = aknLayoutScalable_Avkon.title_pane_stacon(titleVariety).LayoutLine();                		                    	
	                    	}
	                    else
	                    	{
		                    // LAF does not provide yet variety for idle titlepane so we strecth the
		                    // titlepane here to cover universal indicators too which is not used in this
		                    // layout.
		                    layout = aknLayoutScalable_Avkon.title_pane_stacon(variety).LayoutLine();
		                    TAknLayoutRect LayoutRect;
		                    LayoutRect.LayoutRect(parentRect, layout);
		                    paneRect = LayoutRect.Rect(); 
		                    
		                    TRect tmpParentRect( layout1Rect );
		                    TAknWindowLineLayout tmpLayout( aknLayoutScalable_Avkon.uni_indicator_pane_stacon(variety).LayoutLine() );
		                    TAknLayoutRect tmpLayoutRect;
		                    tmpLayoutRect.LayoutRect(tmpParentRect, tmpLayout);
		                    TRect tmpRect( tmpLayoutRect.Rect() );

		                    paneRect.BoundingRect(tmpRect);
	                    	}
	                    break;
	                    }
	                case EEikStatusPaneUidIndic:
	                    {            
	                    if (smallDigitalClockInStacon)
	                    	{
	                    	TInt indicatorVariety = 1;
				            if (aLayoutId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT)
				                {
								indicatorVariety = 5;
				                }
		                    parentRect = layout1Rect;
		                    layout = aknLayoutScalable_Avkon.indicator_nsta_pane_cp2(indicatorVariety).LayoutLine();                		
	                    	}
	                    else
	                    	{
		                    // Exceptionally mainpane as parent
		                    parentRect = mainPaneRect;
		                    if (idleIndicatorsInLandscapeAreVertical)
		                    	layout = aknLayoutScalable_Avkon.indicator_pane(3).LayoutLine(); // Vertical status indicators
		                    else
		                    	layout = aknLayoutScalable_Avkon.indicator_pane(1).LayoutLine(); // Horizontal status indicators, always in right side exept in A&H
	                    	}
	                    		
	                    break;
	                    }
	                case EEikStatusPaneUidBattery:
	                    {
	                    parentRect = layout2Rect;
	                    layout = aknLayoutScalable_Avkon.battery_pane_stacon(variety).LayoutLine();
	                    break;
	                    }	                    
		            case EEikStatusPaneUidEmpty:
		                {
		                if (smallDigitalClockInStacon)
		                	{
			                parentRect = layout2Rect;
		 	               	layout = aknLayoutScalable_Avkon.clock_nsta_pane_cp2(clockVariety).LayoutLine();                		
		                	}
		                break;
		                }		                
	                }
	            }
	        break;
	        }

		case R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT:
	        {
	        TAknWindowComponentLayout parentLayout;
			
	        TBool landscapeOrientation(
	            Layout_Meta_Data::IsLandscapeOrientation() );

	        // Is bottom softkey touch landscape layout in use.
	        TBool touchLsc( landscapeOrientation &&
	                        Layout_Meta_Data::IsPenEnabled() );

			if ( landscapeOrientation )
                {
                if ( touchLsc )
                    {
                    parentLayout = aknLayoutScalable_Avkon.area_top_pane( 2 );
                    }
                else
                    {
                    parentLayout = aknLayoutScalable_Avkon.area_top_pane( 8 );
                    }
                }
	        else
	        	{
	        	parentLayout = aknLayoutScalable_Avkon.area_top_pane(6);
	        	smallDigitalClockInLandscapeFlatSpUsual = EFalse;
	        	}
	                      
	        TAknLayoutRect layoutRect;
	        layoutRect.LayoutRect(screenRect, parentLayout.LayoutLine());
	        parentRect = layoutRect.Rect();
	        switch(aPaneId.iUid)
	            {
	            case EEikStatusPaneUidNavi: 
                    {
                    layout =
                        aknLayoutScalable_Avkon.navi_pane(
                            touchLsc ? 9 : 2 ).LayoutLine();

                    break;
                    }
	            case EEikStatusPaneUidSignal:
	                {
	                layout = aknLayoutScalable_Avkon.signal_pane( touchLsc ? 14 : 2 ).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidTitle:
	                {
                    if ( touchLsc )
                        {
                        layout = aknLayoutScalable_Avkon.title_pane( 11 ).LayoutLine();
                        }
                    else if ( landscapeOrientation &&
                              smallDigitalClockInLandscapeFlatSpUsual )
	                    {                       
		                // LAF does not provide yet variety for titlepane in this case so we strecth the
		                // titlepane here to cover universal indicators too which is not used in this
		                // layout.
	                    layout = aknLayoutScalable_Avkon.title_pane(2).LayoutLine();
	                    TAknLayoutRect LayoutRect;
	                    LayoutRect.LayoutRect(parentRect, layout);
	                    paneRect = LayoutRect.Rect(); 
	                        
	                    TAknWindowLineLayout tmpLayout( aknLayoutScalable_Avkon.uni_indicator_pane(1).LayoutLine() );
	                    TAknLayoutRect tmpLayoutRect;
	                    tmpLayoutRect.LayoutRect(parentRect, tmpLayout);
	                    TRect tmpRect( tmpLayoutRect.Rect() );

	                    paneRect.BoundingRect(tmpRect);
	                    }
					else
						{
		                layout = aknLayoutScalable_Avkon.title_pane(2).LayoutLine();                    						
						}
	                break;
	                }
	            case EEikStatusPaneUidIndic:
	                {
	                if ( landscapeOrientation &&
	                     smallDigitalClockInLandscapeFlatSpUsual )
	                    {
                    	// Indicators are located in control pane area.
				        TAknWindowComponentLayout bottomArea(
				            AknLayoutScalable_Avkon::area_bottom_pane( touchLsc ? 2 : 6 ) );
				        TAknWindowComponentLayout controlPane(
				            AknLayoutScalable_Avkon::control_pane() );
                    	TAknWindowComponentLayout nstaClockIndicPane(
                    	    AknLayoutScalable_Avkon::nsta_clock_indic_pane() );
                    	TAknWindowComponentLayout indicatorNstaPane(
                    	    AknLayoutScalable_Avkon::indicator_nsta_pane_cp() ); 
			        	indicatorNstaPane =
                            DoCompose( bottomArea,
                                       DoCompose( controlPane,
                                                  DoCompose( nstaClockIndicPane,
                                                             indicatorNstaPane ) ) );
	                    layout = indicatorNstaPane.LayoutLine();
	                    parentRect = applicationWindowRect;
	                    }
	                else
	                	{
		                layout = aknLayoutScalable_Avkon.uni_indicator_pane(1).LayoutLine();                		
	                	}    
	                break;
	                }
	            case EEikStatusPaneUidBattery:
	                {
	                layout = aknLayoutScalable_Avkon.battery_pane( touchLsc ? 14 : 2 ).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidDigitalClock:
	                {
	                if (smallDigitalClockInLandscapeFlatSpUsual)
	                	{
				        TAknWindowComponentLayout bottomArea(
                            aknLayoutScalable_Avkon.area_bottom_pane( touchLsc ? 2 : 6 ) );
                        TAknWindowComponentLayout controlPane(
                            aknLayoutScalable_Avkon.control_pane() );
                        TAknWindowComponentLayout nstaClockIndicPane(
                            aknLayoutScalable_Avkon.nsta_clock_indic_pane() );
                        TAknWindowComponentLayout clockNstaPane(
                            aknLayoutScalable_Avkon.clock_nsta_pane_cp() ); 
                        clockNstaPane = DoCompose(
                            bottomArea,
                            DoCompose(
                                controlPane,
                                DoCompose(
                                    nstaClockIndicPane, clockNstaPane ) ) );
                        layout     = clockNstaPane.LayoutLine();
                        parentRect = applicationWindowRect;
	                	}
	                else
	                	{
	                	paneRect = TRect(0,0,0,1);	
	                	}	
	                break;
	                }
	            }
	        break;
	        }

		case R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT:
	        {   
	        TBool landscapeOrientation(
                Layout_Meta_Data::IsLandscapeOrientation() );

            // Is bottom softkey touch landscape layout in use.
            TBool touchLsc( landscapeOrientation &&
                            Layout_Meta_Data::IsPenEnabled() );
	                        
	        TAknWindowComponentLayout parentLayout;

            if ( landscapeOrientation )
                {
                if ( touchLsc )
                    {
                    parentLayout = aknLayoutScalable_Avkon.area_top_pane( 2 );
                    }
                else
                    {
                    parentLayout = aknLayoutScalable_Avkon.area_top_pane( 8 );    
                    }
                }
	        else
	        	{
	        	parentLayout = aknLayoutScalable_Avkon.area_top_pane( 6 );
	        	smallDigitalClockInLandscapeFlatSpIdle = EFalse;	        	
	        	}     
	            
	        TAknLayoutRect layoutRect;
	        layoutRect.LayoutRect( screenRect, parentLayout.LayoutLine() );
	        parentRect = layoutRect.Rect();

	        switch ( aPaneId.iUid )
	            {
	            case EEikStatusPaneUidNavi: 
	                {
                    layout =
                        aknLayoutScalable_Avkon.navi_pane(
                            touchLsc ? 9 : 2 ).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidSignal:
	                {
	                layout = aknLayoutScalable_Avkon.signal_pane( touchLsc ? 14 : 2 ).LayoutLine();
	                break;
	                }
	            case EEikStatusPaneUidTitle:
	                {
	                // LAF does not provide yet variety for idle title pane so
	                // we strecth the title pane here to cover universal
	                // indicators too which is not used in this layout.
	                if ( touchLsc )
                        {
                        layout = aknLayoutScalable_Avkon.title_pane( 11 ).LayoutLine();
                        }
	                else if ( landscapeOrientation )
	                    {                       
	                    layout = aknLayoutScalable_Avkon.title_pane( 2 ).LayoutLine();
	                    TAknLayoutRect LayoutRect;
	                    LayoutRect.LayoutRect( parentRect, layout );
	                    paneRect = LayoutRect.Rect(); 
	                        
	                    TAknWindowLineLayout tmpLayout(
	                        aknLayoutScalable_Avkon.uni_indicator_pane( 1 ).LayoutLine() );
	                    TAknLayoutRect tmpLayoutRect;
	                    tmpLayoutRect.LayoutRect( parentRect, tmpLayout );
	                    TRect tmpRect( tmpLayoutRect.Rect() );

	                    paneRect.BoundingRect( tmpRect );
	                    }
                    else
                        {
                        layout = aknLayoutScalable_Avkon.title_pane( 2 ).LayoutLine();
                        }
	                break;
	                }
	            case EEikStatusPaneUidIndic:
	                {
	                // Exceptionally mainpane as parent.
	                // Note that this is main_pane for flat statuspane.
	                if ( Layout_Meta_Data::IsLandscapeOrientation() )
	                    {
	                    if ( smallDigitalClockInLandscapeFlatSpIdle )
	                    	{
	                    	// Indicators are located in control pane area.
                            TAknWindowComponentLayout bottomArea(
	                            aknLayoutScalable_Avkon.area_bottom_pane( touchLsc ? 2 : 6 ) );
					        TAknWindowComponentLayout controlPane(
					            aknLayoutScalable_Avkon.control_pane() );
	                    	TAknWindowComponentLayout nstaClockIndicPane(
	                    	    aknLayoutScalable_Avkon.nsta_clock_indic_pane() );
	                    	TAknWindowComponentLayout indicatorNstaPane(
	                    	    aknLayoutScalable_Avkon.indicator_nsta_pane_cp() );
				        	indicatorNstaPane =
				        	    DoCompose( bottomArea,
				        	               DoCompose( controlPane,
				        	                          DoCompose( nstaClockIndicPane,
				        	                                     indicatorNstaPane ) ) );
		                    layout     = indicatorNstaPane.LayoutLine();
		                    parentRect = applicationWindowRect;
	                    	}
	                    else
	                    	{	                    			                                            
		                    // Exceptionally mainpane as parent
		                    parentRect = mainPaneRect;
							if ( idleIndicatorsInLandscapeAreVertical )
							    {
							    // Vertical status indicators
		                    	layout = aknLayoutScalable_Avkon.indicator_pane( 3 ).LayoutLine();
							    }
		                    else
		                        {
		                        // Horizontal status indicators
		                    	layout = aknLayoutScalable_Avkon.indicator_pane( 1 ).LayoutLine();
		                        }
	                    	}	
	                    }
	                else
	                    {
	                    layout = aknLayoutScalable_Avkon.uni_indicator_pane( 1 ).LayoutLine();
	                    }

	                break;
	                }
	            case EEikStatusPaneUidDigitalClock:
	                {
	                if ( smallDigitalClockInLandscapeFlatSpIdle )
	                	{
				        TAknWindowComponentLayout bottomArea(
				            aknLayoutScalable_Avkon.area_bottom_pane( touchLsc ? 2 : 6 ) );
				        TAknWindowComponentLayout controlPane(
				            aknLayoutScalable_Avkon.control_pane() );
                    	TAknWindowComponentLayout nstaClockIndicPane(
                    	    aknLayoutScalable_Avkon.nsta_clock_indic_pane() );
                    	TAknWindowComponentLayout clockNstaPane(
                    	    aknLayoutScalable_Avkon.clock_nsta_pane_cp() ); 
			        	clockNstaPane = DoCompose(
			        	    bottomArea,
			        	    DoCompose(
			        	        controlPane,
			        	        DoCompose(
			        	            nstaClockIndicPane, clockNstaPane ) ) );
	                    layout     = clockNstaPane.LayoutLine();
	                    parentRect = applicationWindowRect;
	                	}
	                else
	                	{
	                	paneRect = TRect(0,0,0,1);	
	                	}	
	                	
	                break;
	                }		                
	            case EEikStatusPaneUidBattery:
	                {
	               	layout = aknLayoutScalable_Avkon.battery_pane( touchLsc ? 14 : 2 ).LayoutLine();
	                break;
	                }
	            }
	        break;
	        }
        
		case R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT:
	        {
	        // For now we use classic statuspane
	        parentRect = usualStatusPaneRect;

	        if (!Layout_Meta_Data::IsLandscapeOrientation())
	            {
	            switch(aPaneId.iUid)
	                {
	                case EEikStatusPaneUidNavi: 
	                    {
	                    layout = aknLayoutScalable_Avkon.navi_pane(7).LayoutLine(); // wide navi pane layout
	                    break;
	                    }
	                case EEikStatusPaneUidSignal:
	                    {
	                    layout = aknLayoutScalable_Avkon.signal_pane(7).LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidTitle:
	                    {
	                    layout = aknLayoutScalable_Avkon.title_pane(7).LayoutLine();                    
	                    break;
	                    }
	                case EEikStatusPaneUidIndic:
	                    {
	                    layout = aknLayoutScalable_Avkon.indicator_nsta_pane().LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidBattery:
	                    {
	                    layout = aknLayoutScalable_Avkon.battery_pane(7).LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidDigitalClock:
	                    {
	                    layout = aknLayoutScalable_Avkon.clock_nsta_pane().LayoutLine();
	                    break;
	                    }                                
	                case EEikStatusPaneUidEmpty:
	                    {
	                    layout = aknLayoutScalable_Avkon.aid_fill_nsta(2).LayoutLine(); // fill for wide navi pane
	                    TAknLayoutRect LayoutRect;
	                    LayoutRect.LayoutRect(parentRect, layout);
	                    paneRect = LayoutRect.Rect(); 
	                        
	                    TAknWindowLineLayout tmpLayout( aknLayoutScalable_Avkon.aid_fill_nsta_2(1).LayoutLine() );
	                    TAknLayoutRect tmpLayoutRect;
	                    tmpLayoutRect.LayoutRect(parentRect, tmpLayout);
	                    TRect tmpRect( tmpLayoutRect.Rect() ); 

	                    paneRect.BoundingRect(tmpRect);
	                    break;
	                    }                                
	                }
	            }
	        break;
	        }
		case R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT:
	        {
	        // For now we use classic statuspane
	        parentRect = usualStatusPaneRect;

	        if (!Layout_Meta_Data::IsLandscapeOrientation())
	            {
	            switch(aPaneId.iUid)
	                {
	                case EEikStatusPaneUidNavi: 
	                    {
	                    layout = aknLayoutScalable_Avkon.navi_pane(6).LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidSignal:
	                    {
	                    layout = aknLayoutScalable_Avkon.signal_pane(8).LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidTitle:
	                    {
	                    layout = aknLayoutScalable_Avkon.title_pane(8).LayoutLine();                    
	                    break;
	                    }
	                case EEikStatusPaneUidIndic:
	                    {
	                    layout = aknLayoutScalable_Avkon.indicator_nsta_pane(1).LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidBattery:
	                    {
	                    layout = aknLayoutScalable_Avkon.battery_pane(8).LayoutLine();
	                    break;
	                    }
	                case EEikStatusPaneUidClock:
	                    {
	                    layout = aknLayoutScalable_Avkon.popup_clock_digital_window().LayoutLine();
	                    break;
	                    }                                
	                case EEikStatusPaneUidEmpty:
	                    {
	                    layout = aknLayoutScalable_Avkon.aid_fill_nsta(1).LayoutLine();
	                    break;
	                    }                                
	                }
	            }
	        break;
	        }
	        
	    case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL:
	    case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE:
	        {
	        if ( Layout_Meta_Data::IsLandscapeOrientation() ) // only usable in landscape
	            {
                TAknLayoutRect layout1ParentRect;
                layout1ParentRect.LayoutRect(
                    iLayout->iApplicationWindowRect,
                    iLayout->iAknLayoutScalable_Avkon.area_top_pane( 8 ).LayoutLine() );
                TAknLayoutRect layout1Rect;
                layout1Rect.LayoutRect(
                    layout1ParentRect.Rect(),
                    iLayout->iAknLayoutScalable_Avkon.status_pane( 1 ).LayoutLine() );
                parentRect = layout1Rect.Rect();
                
                switch ( aPaneId.iUid )
                    {
                    case EEikStatusPaneUidNavi: 
                        {
                        layout =
                            aknLayoutScalable_Avkon.navi_pane( 8 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidSignal:
                        {
                        layout =
                            aknLayoutScalable_Avkon.signal_pane( 10 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidTitle:
                        {
                        layout =
                            aknLayoutScalable_Avkon.title_pane( 10 ).LayoutLine();                    
                        break;
                        }
                    case EEikStatusPaneUidIndic:
                        {
                        if ( TLocale().TimeFormat() == ETime12 )
                            {
                            layout =
                                aknLayoutScalable_Avkon.indicator_nsta_pane( 3 ).LayoutLine();
                            }
                        else
                            {
                            layout =
                                aknLayoutScalable_Avkon.indicator_nsta_pane_cp_24( 3 ).LayoutLine();
                            }
                        break;
                        }
                    case EEikStatusPaneUidBattery:
                        {
                        layout =
                            aknLayoutScalable_Avkon.battery_pane( 10 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidDigitalClock:
                        {
                        if ( TLocale().TimeFormat() == ETime12 )
                            {
                            layout =
                                aknLayoutScalable_Avkon.clock_nsta_pane( 2 ).LayoutLine();
                            }
                        else
                            {
                            layout =
                                aknLayoutScalable_Avkon.clock_nsta_pane_cp_24( 2 ).LayoutLine();
                            }
                        break;
                        }                                
                    case EEikStatusPaneUidEmpty:
                        {
                        TAknLayoutRect LayoutRect;
                        LayoutRect.LayoutRect(
                            parentRect,
                            aknLayoutScalable_Avkon.aid_fill_nsta( 3 ).LayoutLine() );
                        paneRect = LayoutRect.Rect(); 

                        TAknLayoutRect tmpLayoutRect;
                        tmpLayoutRect.LayoutRect(
                            parentRect,
                            aknLayoutScalable_Avkon.aid_fill_nsta_2( 2 ).LayoutLine() );
                        TRect tmpRect( tmpLayoutRect.Rect() ); 

                        paneRect.BoundingRect( tmpRect );
                        
                        
                        paneRect = parentRect;
                        break;
                        }                                
                    }
	            }
            break;
	        }
        
        case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT: // fallthrough
        case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT:
            {
            if ( Layout_Meta_Data::IsLandscapeOrientation() ) // only usable in landscape
	            {
                TAknLayoutRect layout1ParentRect;
                layout1ParentRect.LayoutRect(
                    iLayout->iApplicationWindowRect,
                    iLayout->iAknLayoutScalable_Avkon.area_top_pane( 19 ).LayoutLine() );
                TAknLayoutRect layout1Rect;
                layout1Rect.LayoutRect(
                    layout1ParentRect.Rect(),
                    iLayout->iAknLayoutScalable_Avkon.status_pane( 4 ).LayoutLine() );
                parentRect = layout1Rect.Rect();
                
                switch ( aPaneId.iUid )
                    {
                    case EEikStatusPaneUidNavi: 
                        {
                        layout =
                            aknLayoutScalable_Avkon.navi_pane( 9 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidSignal:
                        {
                        layout =
                            aknLayoutScalable_Avkon.signal_pane( 11 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidTitle:
                        {
                        layout =
                            aknLayoutScalable_Avkon.title_pane( 11 ).LayoutLine();                    
                        break;
                        }
                    case EEikStatusPaneUidIndic:
                        {
                        layout =
                            aknLayoutScalable_Avkon.uni_indicator_pane( 3 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidBattery:
                        {
                        layout =
                            aknLayoutScalable_Avkon.battery_pane( 11 ).LayoutLine();
                        break;
                        }
                    }
	            }
            break;
	        }
	    case R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS: // fallthrough
	    case R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS:
	        {
	        if ( Layout_Meta_Data::IsLandscapeOrientation() ) // only usable in landscape
	            {
                TAknLayoutRect layout1ParentRect;
                layout1ParentRect.LayoutRect(
                    iLayout->iApplicationWindowRect,
                    iLayout->iAknLayoutScalable_Avkon.area_top_pane( 20 ).LayoutLine() );
                TAknLayoutRect layout1Rect;
                layout1Rect.LayoutRect(
                    layout1ParentRect.Rect(),
                    iLayout->iAknLayoutScalable_Avkon.status_pane( 5 ).LayoutLine() );
                parentRect = layout1Rect.Rect();
                
                switch ( aPaneId.iUid )
                    {
                    case EEikStatusPaneUidNavi: 
                        {
                        layout =
                            aknLayoutScalable_Avkon.navi_pane( 11 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidSignal:
                        {
                        layout =
                            aknLayoutScalable_Avkon.signal_pane( 13 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidTitle:
                        {
                        layout =
                            aknLayoutScalable_Avkon.title_pane( 13 ).LayoutLine();                    
                        break;
                        }
                    case EEikStatusPaneUidIndic:
                        {
                        layout =
                            aknLayoutScalable_Avkon.uni_indicator_pane( 5 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidBattery:
                        {
                        layout =
                            aknLayoutScalable_Avkon.battery_pane( 13 ).LayoutLine();
                        break;
                        }
                    case EEikStatusPaneUidDigitalClock:
                        {
                        if ( TLocale().TimeFormat() == ETime12 )
                            {
                            layout =
                                aknLayoutScalable_Avkon.clock_nsta_pane( 3 ).LayoutLine();
                            }
                        else
                            {
                            layout =
                                aknLayoutScalable_Avkon.clock_nsta_pane_cp_24( 11 ).LayoutLine();
                            }
                        break;
                        }
                    }
	            }
            break;
	        }
		}	// end of switch(aLayoutId)

    if ( paneRect.IsEmpty() && layout.iW != 0 && layout.iH != 0 )
        {
        TAknLayoutRect LayoutRect;
        LayoutRect.LayoutRect( parentRect, layout );
        paneRect = LayoutRect.Rect(); 
        }

#ifdef __DEBUG
    if ( paneRect == TRect( 0, 0, 0, 0 ) )
        {
        RDebug::Print(_L("CEikStatusPaneLayoutTree::GetRectFromAknLayout, Perhaps an unknown paneID = %d",aPaneId));
        RDebug::Print(_L("CEikStatusPaneLayoutTree::GetRectFromAknLayout, LayoutId = %d",aLayoutId));
        }
#endif

    return paneRect;
    }

CEikStatusPaneLayout* CEikStatusPaneLayout::NewL(TResourceReader& aResource, const TRect& aScreenRect)
	{
	CEikStatusPaneLayout* self = new(ELeave) CEikStatusPaneLayout();
	CleanupStack::PushL(self);
	self->ConstructL(aResource, aScreenRect, 0);
	CleanupStack::Pop();
	return self;
	}

CEikStatusPaneLayout* CEikStatusPaneLayout::NewL(TResourceReader& aResource, const TRect& aScreenRect, TInt aLayoutId)
	{
	CEikStatusPaneLayout* self = new(ELeave) CEikStatusPaneLayout();
	CleanupStack::PushL(self);
	self->ConstructL(aResource, aScreenRect, aLayoutId);
	CleanupStack::Pop();
	return self;
	}

CEikStatusPaneLayout::~CEikStatusPaneLayout()
	{
	delete iRoot;
	}


CEikStatusPaneLayout::CEikStatusPaneLayout()
: iAknLayout(AknLayout::CustomisationInstance()),
  iAknLayoutScalable_Avkon(AknLayoutScalable_Avkon::CustomisationInstance())
	{
	}

void CEikStatusPaneLayout::ConstructL(TResourceReader& aResource, const TRect& aScreenRect, TInt aLayoutId)
	{
	TInt position = aResource.ReadUint16();
	
	CEikStatusPaneLayoutTree::TDirection dir = CEikStatusPaneLayoutTree::EHorizontal;
	if (position & EEikStatusPaneLayoutVertical)
		dir = CEikStatusPaneLayoutTree::EVertical;

	iRoot = CEikStatusPaneLayoutTree::NewL(this, aResource, dir);

	TRect rect( aScreenRect );
	TInt size( iRoot->Size() );
	
	TAknWindowComponentLayout applicationWindow( AknLayoutScalable_Avkon::application_window( 0 ) );
    TAknWindowComponentLayout topArea( AknLayoutScalable_Avkon::area_top_pane( 1 ) );
    TAknWindowComponentLayout statusPane( AknLayoutScalable_Avkon::status_pane( 0 ) );
    statusPane = DoCompose( applicationWindow, DoCompose( topArea, statusPane ) );
    TAknLayoutRect statusPaneLayoutRect;
            
	switch (position & KEikSpanePositionMask)
		{
		case EEikStatusPanePositionTop:
            statusPaneLayoutRect.LayoutRect( rect, statusPane.LayoutLine() );      
            rect = statusPaneLayoutRect.Rect();
			break;

		case EEikStatusPanePositionBottom:
			rect.iTl.iY = rect.iBr.iY - size;
			break;

		case EEikStatusPanePositionLeft:
			rect.iBr.iX = rect.iTl.iX + size;
			break;

		case EEikStatusPanePositionRight:
		default:
			rect.iTl.iX = rect.iBr.iX - size;
			break;
		}

// Make sure the flag is never used if scalabale ui is not available.
    if (position & EEikStatusPaneLayoutAknLafDefined)        
        {
       	iRoot->SetAknLayoutUsed(ETrue);
        AknLayoutRefresh(aLayoutId);
        }

    if (!AknLayoutUsed())
        {
        iRoot->SetRect(rect);
        }
	}

void CEikStatusPaneLayout::AknLayoutRefresh(TInt aLayoutResourceId)
    {
    // If layout has been defined by the AknLayout, 
    // then re-define the layout.
    if (AknLayoutUsed()) 
        {
        UpdateLayoutData(aLayoutResourceId);
        iRoot->Layout(aLayoutResourceId);
        }
    }

TBool CEikStatusPaneLayout::AknLayoutUsed()
    {
    if (iRoot) 
        {
        return iRoot->AknLayoutUsed();
        }
    else
        {
        return EFalse;
        }
    }

void CEikStatusPaneLayout::UpdateLayoutData(TInt aLayoutResId)
	{
    // screen
    TAknWindowLineLayout screenLayout( AknLayout::screen() );
    iScreenRect = screenLayout.Rect(); 

    // application window
    TAknWindowLineLayout applicationWindowLayout(
        iAknLayoutScalable_Avkon.application_window( 0 ).LayoutLine() );
    TAknLayoutRect applicationWindowLayoutRect;
    applicationWindowLayoutRect.LayoutRect(iScreenRect, applicationWindowLayout);
    iApplicationWindowRect = applicationWindowLayoutRect.Rect(); 

    // Main pane
    TBool landscape = Layout_Meta_Data::IsLandscapeOrientation();
    TInt mainPaneVariety = landscape ? 4 : 3;
    TAknWindowLineLayout mainPaneLayout( iAknLayoutScalable_Avkon.main_pane(mainPaneVariety).LayoutLine() );
    TAknLayoutRect mainPaneLayoutRect;
    mainPaneLayoutRect.LayoutRect(iApplicationWindowRect, mainPaneLayout);
    iMainPaneRect = mainPaneLayoutRect.Rect(); 

    // statuspane, usual       
    TAknWindowComponentLayout topArea( iAknLayoutScalable_Avkon.area_top_pane( 0 ) );
    TAknWindowComponentLayout statusPaneLayout( iAknLayoutScalable_Avkon.status_pane( 0 ) );
    TAknWindowComponentLayout statusPane( 
        DoCompose( applicationWindowLayout, DoCompose( topArea, statusPaneLayout ).LayoutLine() ) );
    
    TAknLayoutRect statusPaneLayoutRect;
    statusPaneLayoutRect.LayoutRect( iScreenRect, statusPane.LayoutLine() );
    iUsualStatusPaneRect = statusPaneLayoutRect.Rect(); 
        
    // statuspane, small
    TAknWindowLineLayout topAreaLayout;
    if ( AknLayoutUtils::CbaLocation() == AknLayoutUtils::EAknCbaLocationBottom &&
         Layout_Meta_Data::IsLandscapeOrientation() )
        {
        // Landscape with bottom softkeys is the only landscape mode
        // in which small status pane can be shown.
        topAreaLayout = AknLayoutScalable_Avkon::area_top_pane( 2 ).LayoutLine();
        }
    else
        {
        topAreaLayout = AknLayoutScalable_Avkon::area_top_pane( 1 ).LayoutLine();
        }
    TAknLayoutRect topAreaLayoutRect;
    topAreaLayoutRect.LayoutRect( iApplicationWindowRect, topAreaLayout );
    
    // The small status pane fills the whole top area.
    iSmallStatusPaneRect = topAreaLayoutRect.Rect(); 
    
	if (aLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT ||
		aLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT ||
		aLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT ||
		aLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT)
		{
	    TAknWindowComponentLayout layout1parent( iAknLayoutScalable_Avkon.area_top_pane(2) );
	    TAknWindowComponentLayout layout1( iAknLayoutScalable_Avkon.stacon_top_pane() );
	    TAknLayoutRect layout1ParentRect;
	    layout1ParentRect.LayoutRect(iScreenRect, layout1parent.LayoutLine());
	    TAknLayoutRect layout1Rect;
	    layout1Rect.LayoutRect(layout1ParentRect.Rect(), layout1.LayoutLine());
    	iStaconLayout1Rect = layout1Rect.Rect();
    
	    TAknWindowComponentLayout layout2parent( iAknLayoutScalable_Avkon.area_bottom_pane(2) );
	    TAknWindowComponentLayout layout2( iAknLayoutScalable_Avkon.stacon_bottom_pane() );
	    TAknLayoutRect layout2ParentRect;
	    layout2ParentRect.LayoutRect(iScreenRect, layout2parent.LayoutLine());
	    TAknLayoutRect layout2Rect;
	    layout2Rect.LayoutRect(layout2ParentRect.Rect(), layout2.LayoutLine());
	    iStaconLayout2Rect = layout2Rect.Rect();
		}
	}

TRect CEikStatusPaneLayout::AknLayoutRect(TInt aLayoutResourceId, TPaneId aPaneId)
	{
	return iRoot->AknLayoutRect(aLayoutResourceId, aPaneId);
	}


EXPORT_C CEikStatusPaneModelBase::~CEikStatusPaneModelBase()
	{
	delete iPanes;
	if (iLayouts)
		iLayouts->ResetAndDestroy();
	delete iLayouts;
	delete iLegalIds;
	}

EXPORT_C void CEikStatusPaneModelBase::SetLayoutL(TInt aLayoutResId, TBool /*aChangeStatusPaneNow*/)
	{
	TInt layoutResId = AVKONENV->StatusPaneResIdForCurrentLayout(aLayoutResId);
	if (!IsLegalId(layoutResId))
		User::Leave(KErrNotFound);

	CEikStatusPaneLayout* layout = Layout(layoutResId);
	if (layout == NULL)
		layout = LoadLayoutL(layoutResId);

	iCurrentResId = layoutResId;
	iCurrentLayout = layout;
	}

EXPORT_C CEikStatusPaneModelBase::CEikStatusPaneModelBase(CEikonEnv& aEikEnv) 
: iEikEnv(aEikEnv)
	{
	}

EXPORT_C void CEikStatusPaneModelBase::BaseConstructL(TInt aCoreResId)
	{
	TResourceReader res;
	iEikEnv.CreateResourceReaderLC(res, aCoreResId);

	iPanes = CEikStatusPaneSetInit::NewL();
	iPanes->LoadDefaultsL(res);

	iCurrentResId = AVKONENV->StatusPaneResIdForCurrentLayout(res.ReadUint32());

	const TInt layoutCount=res.ReadInt16();
	iLegalIds = new(ELeave) CIdSet(layoutCount);
	for (TInt ii=0; ii<layoutCount; ++ii)
		{
		const TInt layoutRes=res.ReadInt32();
		iLegalIds->AppendL(layoutRes);
		}

	CleanupStack::PopAndDestroy();	// res
	}

TBool CEikStatusPaneModelBase::IsLegalId(TInt aLayoutResId) const
	{
	for (TInt i=0; i<iLegalIds->Count(); i++)
		{
		if (iLegalIds->At(i) == aLayoutResId)
			return ETrue;
		}
	return EFalse;
	}

CEikStatusPaneLayout* CEikStatusPaneModelBase::Layout(TInt aLayoutResId)
	{
	for (TInt i=0; i<iLayouts->Count(); i++)
		{
		if (iLayouts->At(i)->iResId == aLayoutResId)
			return iLayouts->At(i)->iLayout;
		}
	return NULL;
	}

EXPORT_C CEikStatusPaneLayout* CEikStatusPaneModelBase::LoadLayoutL(TInt aLayoutResId)
	{
	TResourceReader res;
	iEikEnv.CreateResourceReaderLC(res, aLayoutResId);

	TRect rect(TPoint(0,0),TSize(AKN_LAYOUT_WINDOW_screen.iW,AKN_LAYOUT_WINDOW_screen.iH));
	CEikStatusPaneLayout* layout = CEikStatusPaneLayout::NewL(res, rect, aLayoutResId);

	CleanupStack::PushL(layout);
	CheckLayoutL(layout);

	CIdLayoutPair* pair = new(ELeave) CIdLayoutPair(aLayoutResId, layout);
	CleanupStack::Pop();	// layout
	CleanupStack::PushL(pair);

	iLayouts->AppendL(pair);
	CleanupStack::Pop();	// pair

	CleanupStack::PopAndDestroy();	// res

	return layout;
	}

void CEikStatusPaneModelBase::CheckLayoutL(CEikStatusPaneLayout* aLayout)
	{
	TLayoutChecker checker(iPanes);
	aLayout->AcceptL(&checker);
	}

EXPORT_C void CEikStatusPaneModelBase::Reserved_1()
	{
	}

EXPORT_C TInt CEikStatusPaneModelBase::CurrentLayoutResId() const
	{
	return iCurrentResId;
	}

void CEikStatusPaneModelBase::AknLayoutRefresh()
    {
	for (TInt i=0; i<iLayouts->Count(); i++)
		{
		if (iLayouts->At(i))
            {
			iLayouts->At(i)->iLayout->AknLayoutRefresh(iLayouts->At(i)->iResId);
            }
		}
    }

TBool CEikStatusPaneModelBase::AknLayoutUsed(TInt aLayoutId)
    {
	for (TInt i=0; i<iLayouts->Count(); i++)
		{
		if (iLayouts->At(i) && iLayouts->At(i)->iResId == aLayoutId)
            {
			return iLayouts->At(i)->iLayout->AknLayoutUsed();
            }
		}
    return EFalse;
    }


CEikStatusPaneModelBase::TLayoutChecker::TLayoutChecker(CEikStatusPaneSetInit* aPanes)
: iPanes(aPanes)
	{
	}

void CEikStatusPaneModelBase::TLayoutChecker::VisitL(CEikStatusPaneLayoutTree* aNode)
	{
	iPanes->FindL(aNode->Id());
	}


CEikStatusPaneModelBase::CIdLayoutPair::CIdLayoutPair(TInt aResId, CEikStatusPaneLayout* aLayout)
: iResId(aResId), iLayout(aLayout)
	{
	}

CEikStatusPaneModelBase::CIdLayoutPair::~CIdLayoutPair()
	{
	delete iLayout;
	}




CEikAppStatusPaneModel* CEikAppStatusPaneModel::NewL(CEikonEnv& aEikEnv, TInt aCoreResId, TInt aAppResId, TBool aChangeStatusPaneNow)
	{
	CEikAppStatusPaneModel* self = new(ELeave) CEikAppStatusPaneModel(aEikEnv);
	CleanupStack::PushL(self);
	self->ConstructL(aCoreResId, aAppResId, aChangeStatusPaneNow);
	CleanupStack::Pop();
	return self;
	}

CEikAppStatusPaneModel::~CEikAppStatusPaneModel()
	{
	}

void CEikAppStatusPaneModel::SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow)
	{
	CEikStatusPaneModelBase::SetLayoutL(aLayoutResId, aChangeStatusPaneNow);
	CAknSgcClient::HandleChangeL();
	}

void CEikAppStatusPaneModel::SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow, TBool aNotfiyServerSide)
    {
	CEikStatusPaneModelBase::SetLayoutL(aLayoutResId, aChangeStatusPaneNow);
	if (aNotfiyServerSide)
	    CAknSgcClient::HandleChangeL();    
    }


CEikAppStatusPaneModel::CEikAppStatusPaneModel(CEikonEnv& aEikEnv)
: CEikStatusPaneModelBase(aEikEnv)
	{
	}

void CEikAppStatusPaneModel::ConstructL(TInt aCoreResId, TInt aAppResId, TBool aChangeStatusPaneNow)
	{
	BaseConstructL(aCoreResId);

	iLayouts = new(ELeave) CLayoutIdSet(1);
	
    if (aAppResId != EEikStatusPaneUseDefaults && 
        aAppResId > EEikStatusPaneLayoutAknLafDefined)
        {
		TResourceReader res;
		iEikEnv.CreateResourceReaderLC(res, aAppResId);

		TInt defaultLayout = res.ReadUint32();
		if (defaultLayout != EEikStatusPaneUseDefaults && 
            defaultLayout > EEikStatusPaneLayoutAknLafDefined)
			{
			if (IsLegalId(defaultLayout))
				{
				iCurrentResId = defaultLayout;
				}
			else
				{
				User::Leave(KErrNotFound);
				}
			}

		PaneInits()->LoadDefaultsL(res);

		CleanupStack::PopAndDestroy();	// res
		}

	SetLayoutL(iCurrentResId,aChangeStatusPaneNow);
	}

void CEikAppStatusPaneModel::ApplyCurrentLayoutL()
	{
	}

