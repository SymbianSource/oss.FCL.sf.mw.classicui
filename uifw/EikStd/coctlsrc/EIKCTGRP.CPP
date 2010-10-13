/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  EIKON control group implementation.
*
*/


#include <eikctgrp.h>
#include <eikpanic.h>
#include <coedef.h>
#include <coeccntx.h>
#include <layoutmetadata.cdl.h>
#include <AknUtils.h> // LayoutUtils
#include <AknStatuspaneUtils.h>
#include <avkon.rsg>

const TInt KControlArrayGranularity = 5;
const TInt KStartCornerMask         = 0x00f;
const TInt KOrientationMask         = 0x030; 

EXPORT_C CEikControlGroup::CEikControlGroup()
	: iLines(1)
	{
	__DECLARE_NAME(_S("CEikControlGroup"));
	}

EXPORT_C CEikControlGroup::~CEikControlGroup()
	{
	DeleteAllComponents();
	delete iControlArray;
	}

EXPORT_C void CEikControlGroup::ConstructL(TStartCorner aStart,TOrientation aOrientation)
	{
	iControlArray=new(ELeave) CArrayFixFlat<TEikGroupControl> (KControlArrayGranularity);
	iLayout|=aStart|aOrientation;
	}

EXPORT_C void CEikControlGroup::AddControlL(CCoeControl* aControl,TInt aId)
	{
	TEikGroupControl ctrl;
	ctrl.iControl=aControl;
	ctrl.iId=aId;
	AddControlL(ctrl);
	}

EXPORT_C void CEikControlGroup::AddControlL(TEikGroupControl& aGroupControl)
	{
	__ASSERT_DEBUG(aGroupControl.iControl,Panic(EEikPanicNullPointer));
	aGroupControl.iControl->SetContainerWindowL(*this);
	iControlArray->AppendL(aGroupControl);
	}

EXPORT_C void CEikControlGroup::InsertControlL(TEikGroupControl& aGroupControl,TInt aIndex)
	{
	__ASSERT_DEBUG(aGroupControl.iControl,Panic(EEikPanicNullPointer));
	aGroupControl.iControl->SetContainerWindowL(*this);
	iControlArray->InsertL(aIndex,aGroupControl); // takes ownership at this point
	}

EXPORT_C void CEikControlGroup::DeleteControl(TInt aIndex,TInt aCount)
	{
	for (TInt ii=aIndex+aCount-1;ii>=aIndex;ii--)
		{
		delete (*iControlArray)[ii].iControl;
		iControlArray->Delete(ii);
		}
	}

EXPORT_C void CEikControlGroup::Reset()
	{
	DeleteAllComponents();
	iControlArray->Reset();
	}

EXPORT_C void CEikControlGroup::DeleteAllComponents()
	{
	if (iControlArray)
		{
		const TInt count=iControlArray->Count();
		for (TInt ii=0;ii<count;ii++)
			delete ((*iControlArray)[ii].iControl);
		}
	}

EXPORT_C TInt CEikControlGroup::IndexById(TInt aId) const
	{
	const TInt count=iControlArray->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		if ((*iControlArray)[ii].iId==aId)
			return ii;
		}
	return KErrNotFound;
	}

EXPORT_C CCoeControl* CEikControlGroup::ControlById(TInt aId) const
	{
	const TInt index=IndexById(aId);
	if (index==KErrNotFound)
		return NULL;
	return (*iControlArray)[index].iControl;
	}

EXPORT_C TInt CEikControlGroup::ControlId(CCoeControl* aControl) const
	{
	const TInt count=iControlArray->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		TEikGroupControl ctrl=(*iControlArray)[ii];
		if (ctrl.iControl==aControl)
			return ctrl.iId;
		}
	return KErrNotFound;
	}

EXPORT_C CCoeControl* CEikControlGroup::Control(TInt aIndex) const
	{
	return (*iControlArray)[aIndex].iControl;
	}

EXPORT_C CArrayFix<TEikGroupControl>* CEikControlGroup::ControlArray() const
	{
	return iControlArray;
	}

EXPORT_C void CEikControlGroup::SetControlsAllSameSize()
	{
	iLayout|=EAllSameSize;
	}

EXPORT_C void CEikControlGroup::Draw(const TRect& /*aRect*/) const
	{
	const TRect rect(Rect());
	CWindowGc& gc=SystemGc();
	iBorder.Draw(gc,rect);
	if (iContext)
		{
		gc.SetPenStyle(CGraphicsContext::ENullPen);
		iContext->PrepareContext(gc);
		gc.DrawRect(iBorder.InnerRect(rect));
		}
	}

EXPORT_C void CEikControlGroup::SetLengthInPixels(TInt aLength)
	{
	__ASSERT_DEBUG(aLength>=1,Panic(EEikPanicCtGroupInvalidDimension));
	iLength=aLength;
	if (Orientation()==ELayHorizontally)
		iSize.iWidth=aLength;
	else
		iSize.iHeight=aLength;
	}

EXPORT_C void CEikControlGroup::SetBreadthInPixels(TInt aBreadth)
	{
	__ASSERT_DEBUG(aBreadth>=1,Panic(EEikPanicCtGroupInvalidDimension));
	iBreadth=aBreadth;
	if (Orientation()==ELayHorizontally)
		iSize.iHeight=aBreadth;
	else
		iSize.iWidth=aBreadth;
	}

EXPORT_C void CEikControlGroup::SetNumberOfLines(TInt aNumLines,TBool aDistributeEvenly)
	{
	__ASSERT_DEBUG(aNumLines>=1,Panic(EEikPanicCtGroupInvalidNumberOfLines));
	iLines=aNumLines;
	if (aDistributeEvenly)
		iLayout|=EDistributeEvenly;
	else
		iLayout&=~EDistributeEvenly;
	}

EXPORT_C TSize CEikControlGroup::MinimumSize()
	{
	const TBool horiz=(Orientation()==ELayHorizontally);
	TSize size=(horiz? TSize(iLength,iBreadth) : TSize(iBreadth,iLength));
	if ((horiz && size.iWidth==0) || (!horiz && size.iHeight==0))
		{
		if (iLines==1)
			{
			const TInt count=iControlArray->Count();
			TInt length=0;
			if (AllSameSize())
				length=count*(horiz? iLargestControl.iWidth : iLargestControl.iHeight);
			else
				{
				for (TInt ii=0;ii<count;ii++)
					{
					const TSize ctrlSize=ControlMinimumSize(ii);
					length+=(horiz? ctrlSize.iWidth : ctrlSize.iHeight);
					}
				}
			if (horiz)
				size.iWidth=length+(count-1)*iHSpacing;
			else
				size.iHeight=length+(count-1)*iVSpacing;
			}
		else if (iLines>1 && iLayout&EDistributeEvenly)
			{
			const TInt count=iControlArray->Count();
			const TInt maxLineCount=(count+iLines-1)/iLines;
			TInt length=0;
			if (AllSameSize())
				length=maxLineCount*(horiz? iLargestControl.iWidth : iLargestControl.iHeight);
			else
				{
				TInt ii=-1;
				while (++ii<count)
					{
					if ((ii+1)%iLines && ii!=count-1)
						{
						const TSize ctrlSize=ControlMinimumSize(ii);
						length+=(horiz? ctrlSize.iWidth : ctrlSize.iHeight);
						}
					else
						{
						length=Max((horiz? size.iWidth : size.iHeight),length);
						length=0;
						}
					}
				}
			if (horiz)
				{
				size.iWidth=length;
				size.iWidth+=(maxLineCount-1)*iHSpacing;
				}
			else
				{
				size.iHeight=length;
				size.iHeight+=(maxLineCount-1)*iVSpacing;
				}
			}
		else
			Panic(EEikPanicCtGroupInsufficientInitialisation);
		if (horiz)
			size.iWidth+=iBorder.SizeDelta().iWidth;
		else
			size.iHeight+=iBorder.SizeDelta().iHeight;
		}
	if ((horiz && size.iHeight==0) || (!horiz && size.iWidth==0))
		{
		TInt breadth=0;
		if (AllSameSize())
			breadth=(horiz? iLargestControl.iHeight : iLargestControl.iWidth);
		else
			{
			const TInt count=iControlArray->Count();
			for (TInt ii=0;ii<count;ii++)
				{
				const TSize ctrlSize=ControlMinimumSize(ii);
				breadth=Max(breadth,(horiz? ctrlSize.iHeight : ctrlSize.iWidth));
				}
			}
		breadth*=iLines;
		if (horiz)
			size.iHeight=breadth+(iLines-1)*iVSpacing+iBorder.SizeDelta().iHeight;
		else
			size.iWidth=breadth+(iLines-1)*iHSpacing+iBorder.SizeDelta().iWidth;
		}
	return size;
	}

EXPORT_C TSize CEikControlGroup::ControlMinimumSize(TInt aIndex) const
	{
	TSize size;
	TEikGroupControl ctrl=(*iControlArray)[aIndex];
	if (Orientation()==ELayHorizontally)
		{
		TSize ctrlSize;
		if (ctrl.IsLengthSet())
			size.iWidth=ctrl.Length();
		else
			{
			ctrlSize=ctrl.iControl->MinimumSize();
			size.iWidth=ctrlSize.iWidth;
			}
		if (iBreadth==0)
			size.iHeight=(ctrlSize.iHeight>0? ctrlSize.iHeight : ctrl.iControl->MinimumSize().iHeight);
		else
			{
			size.iHeight=iBreadth;
			size.iHeight-=iBorder.SizeDelta().iHeight;
			size.iHeight/=iLines;
			}
		}
	else
		{
		TSize ctrlSize;
		if (ctrl.IsLengthSet())
			size.iHeight=ctrl.Length();
		else
			{
			ctrlSize=ctrl.iControl->MinimumSize();
			size.iHeight=ctrlSize.iHeight;
			}
		if (iBreadth==0)
			size.iWidth=(ctrlSize.iWidth>0? ctrlSize.iWidth : ctrl.iControl->MinimumSize().iWidth);
		else
			{
			size.iWidth=iBreadth;
			size.iWidth-=iBorder.SizeDelta().iWidth;
			size.iWidth/=iLines;
			}
		}
	return size;
	}

EXPORT_C TInt CEikControlGroup::ControlMinimumLength(TInt aIndex)
	{
	TEikGroupControl ctrl=(*iControlArray)[aIndex];
	if (AllSameSize())
		return (Orientation()==ELayHorizontally? iLargestControl.iWidth : iLargestControl.iHeight);
	if (ctrl.IsLengthSet())
		return ctrl.Length();
	if (Orientation()==ELayHorizontally)
		return ctrl.iControl->MinimumSize().iWidth;
	return ctrl.iControl->MinimumSize().iHeight;
	}

EXPORT_C TSize CEikControlGroup::LargestControlSize() const
	{
	TSize size;
	const TInt count=iControlArray->Count();
	for (TInt ii=0;ii<count;ii++)
		{
		const TSize ctrlSize=ControlMinimumSize(ii);
		size.iWidth=Max(size.iWidth,ctrlSize.iWidth);
		size.iHeight=Max(size.iHeight,ctrlSize.iHeight);
		}
	return size;
	}


EXPORT_C TInt CEikControlGroup::CountComponentControls() const
	{
    TInt count = iControlArray->Count();

	// This prevents MSK from drawing in landscape layouts.
	// Also MSK doesn't even need to be activated in landscape modes.
    if ( count == 4 )
        {   
        // Exception is made for idle flat status pane layouts,
        // in which the MSK is used also in landscape.
        TBool mskSupportedLscLayoutActive(
            AVKONENV->StatusPaneResIdForCurrentLayout(
                AknStatuspaneUtils::CurrentStatusPaneLayoutResId() ) ==
                    R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS );

        if ( iLayout & EDisableMSKDrawing ||
             ( Layout_Meta_Data::IsLandscapeOrientation() && 
               !mskSupportedLscLayoutActive ) )
            {
            count--;
            }
        }

	return count;
	}

EXPORT_C CCoeControl* CEikControlGroup::ComponentControl(TInt aIndex) const
	{
	return (*iControlArray)[aIndex].iControl;
	}

void CEikControlGroup::SetMSKVisibility(TBool aEnable)
    {
    if (!aEnable)
        {
        iLayout|=EDisableMSKDrawing;
        }
    else
        {
        iLayout&=~EDisableMSKDrawing;
        }
    }

EXPORT_C void CEikControlGroup::ControlSpacing(TInt& aHSpacing,TInt& aVSpacing) const
	{
	aHSpacing=iHSpacing;
	aVSpacing=iVSpacing;
	}

EXPORT_C void CEikControlGroup::SetControlSpacing(TInt aHSpacing,TInt aVSpacing)
	{
	iHSpacing=aHSpacing;
	iVSpacing=aVSpacing;
	}

EXPORT_C void CEikControlGroup::SetControlLayout(TStartCorner aStart,TOrientation aOrientation)
	{
	iLayout&=~KStartCornerMask;
	iLayout&=~KOrientationMask;
	iLayout|=aStart|aOrientation;
	}

EXPORT_C void CEikControlGroup::SizeChanged()
	{
	LayoutControls();
	}

EXPORT_C void CEikControlGroup::LayoutControls()
	{
	const TBool horiz=Orientation()==ELayHorizontally;
	const TRect inner=iBorder.InnerRect(Rect());
	TInt lineBreadth=0;
	if (horiz)
		lineBreadth=(inner.Height()-(iLines-1)*iVSpacing)/iLines;
	else
		lineBreadth=(inner.Width()-(iLines-1)*iHSpacing)/iLines;
	const TInt count=iControlArray->Count();
	TInt ctrlsInLine=(DistributeEvenly()? (count+iLines-1)/iLines : 0);
	TInt index=0;
	TPoint ctrlPos=inner.iTl;
	TStartCorner startCorner=StartCorner();
	for (TInt ii=0;ii<iLines && index<count;ii++)
		{
		TInt excess=0;
		TInt length=(iLength? iLength-(horiz? iBorder.SizeDelta().iWidth : iBorder.SizeDelta().iHeight) :
							(horiz? inner.Width() : inner.Height()));
		if (DistributeEvenly())
			{
			if (ii==iLines-1)
				ctrlsInLine=count-(ctrlsInLine*ii);
			else
				ctrlsInLine=Min(ctrlsInLine,count-index);
			TInt ctrlsLength=0;
			for (TInt jj=0;jj<ctrlsInLine && index+jj<=count;jj++)
				{
				if (index+jj==count)
					{
					ctrlsInLine=jj;
					break;
					}
				ctrlsLength+=ControlMinimumLength(index+jj);
				}
			ctrlsLength+=(ctrlsInLine-1)*(horiz? iHSpacing : iVSpacing);
			excess=length-ctrlsLength;
			}
		else
			{
			ctrlsInLine=0;
			TInt jj=index;
			TInt ctrlsLength=0;
			const TInt spacing=(horiz? iHSpacing : iVSpacing);
			if (index<count)
				{
				FOREVER
					{
					const TInt ctrlLength=ControlMinimumLength(jj++)+(ctrlsInLine? spacing : 0);
					if (ctrlLength+ctrlsLength<=length)
						{
						ctrlsLength+=ctrlLength;
						++ctrlsInLine;
						if (jj==count)
							break;
						}
					else
						break;
					}
				excess=length-ctrlsLength;
				}
			}
		TInt stretchable=0;
		for (TInt jj=0;jj<ctrlsInLine;jj++)
			{
			if ((*iControlArray)[index+jj].IsStretchable())
				++stretchable;
			}
		switch (startCorner)
			{
		case EFromTopLeft:
			ctrlPos=inner.iTl;
			if (horiz)
				ctrlPos.iY+=ii*(lineBreadth+iVSpacing);
			else
				ctrlPos.iX+=ii*(lineBreadth+iHSpacing);
			break;
		case EFromTopRight:
			ctrlPos.iX=inner.iBr.iX;
			ctrlPos.iY=inner.iTl.iY;
			if (horiz)
				{
				ctrlPos.iX-=ControlMinimumLength(index);
				ctrlPos.iY+=ii*(lineBreadth+iVSpacing);
				}
			else
				ctrlPos.iX-=lineBreadth+(ii*(lineBreadth+iHSpacing));
			break;
		case EFromBottomLeft:
			ctrlPos.iX=inner.iTl.iX;
			ctrlPos.iY=inner.iBr.iY;
			if (horiz)
				ctrlPos.iY-=(lineBreadth+(ii*(lineBreadth+iVSpacing)));
			else
				{
				ctrlPos.iX+=ii*(lineBreadth+iHSpacing);
				ctrlPos.iY-=ControlMinimumLength(index);
				}
			break;
		case EFromBottomRight:
			ctrlPos=inner.iBr;
			if (horiz)
				{
				ctrlPos.iX-=ControlMinimumLength(index);
				ctrlPos.iY-=(lineBreadth+(ii*(lineBreadth+iVSpacing)));
				}
			else
				{
				ctrlPos.iX-=lineBreadth+(ii*(lineBreadth+iHSpacing));
				ctrlPos.iY-=ControlMinimumLength(index);
				}
			break;
			}
		TInt stretched=0;
		for (TInt kk=index;kk<ctrlsInLine+index;kk++)
			{
			TSize ctrlSize;
			TSize delta=TSize(0,0);
			TSize deltaPos=TSize(0,0);
			if (AllSameSize())
				ctrlSize=iLargestControl;
			else
				{
				ctrlSize=ControlMinimumSize(kk);
				if(kk<ctrlsInLine+index-1)
					delta=ControlMinimumSize(kk+1)-ctrlSize;
				}
			if (horiz)
				ctrlSize.iHeight=lineBreadth;
			else
				ctrlSize.iWidth=lineBreadth;
			if ((*iControlArray)[kk].IsStretchable())
				{
				TInt extra=excess/stretchable;
				if (excess%stretchable>stretched)
					++extra;
				++stretched;
				if (horiz)
					{
					ctrlSize.iWidth+=extra;
					if (startCorner==EFromTopRight || startCorner==EFromBottomRight)
						deltaPos.iWidth-=extra;
					}
				else
					{
					ctrlSize.iHeight+=extra;
					if (startCorner==EFromBottomLeft || startCorner==EFromBottomRight)
						deltaPos.iHeight-=extra;
					}
				}
			CCoeControl* ctrl=(*iControlArray)[kk].iControl;
			TInt adjacent=0;
			if (horiz)
				adjacent=Adjacent(ii+1,kk-index+1,kk,iLines,ctrlsInLine);
			else
				adjacent=Adjacent(kk-index+1,ii+1,kk,ctrlsInLine,iLines);
			ctrl->SetAdjacent(adjacent);
			ctrl->SetExtent(ctrlPos+deltaPos,ctrlSize);
			if (kk<ctrlsInLine+index-1)
				{
				if (horiz)
					{
					if (startCorner==EFromTopLeft || startCorner==EFromBottomLeft)
						ctrlPos.iX+=ctrlSize.iWidth+iHSpacing;
					else
						ctrlPos.iX-=((ctrlSize+delta).iWidth+iHSpacing);
					}
				else
					{
					if (startCorner==EFromTopLeft || startCorner==EFromTopRight)
						ctrlPos.iY+=ctrlSize.iHeight+iVSpacing;
					else
						ctrlPos.iY-=((ctrlSize+delta).iHeight+iVSpacing);
					}
				}
			}
		index+=ctrlsInLine;
		}
	}

EXPORT_C TInt CEikControlGroup::Adjacent(TInt aRow,TInt aColumn,TInt aCtrlIndex,TInt aTotalRows,TInt aTotalColumns) const
	{
	if (!(iLines==1 || iLayout&EAllSameSize))
		return 0;
	const TBool ctrlBordered=(*iControlArray)[aCtrlIndex].iControl->HasBorder();
	TInt adjacent=EGulAdjNone;
	if (ctrlBordered)
		{
		TStartCorner startCorner=StartCorner();
		const TInt startHoriz=((startCorner==EFromTopLeft || startCorner==EFromBottomLeft)?
								EGulAdjLeft : EGulAdjRight);
		const TInt endHoriz=((startCorner==EFromTopLeft || startCorner==EFromBottomLeft)?
								EGulAdjRight : EGulAdjLeft);
		const TInt startVert=((startCorner==EFromTopLeft || startCorner==EFromTopRight)?
								EGulAdjTop : EGulAdjBottom);
		const TInt endVert=((startCorner==EFromTopLeft || startCorner==EFromTopRight)?
								EGulAdjBottom : EGulAdjTop);
		const TInt internalHoriz=startHoriz;
		const TInt internalVert=startVert;
		const TBool bordered=HasBorder();
		if (bordered)
			{
			if (aRow==1)
				adjacent|=startVert;
			if (aRow==aTotalRows)
				adjacent|=endVert;
			if (aColumn==1)
				adjacent|=startHoriz;
			if (aColumn==aTotalColumns)
				adjacent|=endHoriz;
			}
		if (iHSpacing==0 && aColumn!=1)
			{
			const TInt index=(Orientation()==ELayHorizontally? aCtrlIndex-1 : aCtrlIndex-aTotalRows);
			if ((*iControlArray)[index].iControl->HasBorder())
				adjacent|=internalHoriz;
			}
		if (iVSpacing==0 && aRow!=1)
			{
			const TInt index=(Orientation()==ELayHorizontally? aCtrlIndex-aTotalColumns : aCtrlIndex-1);
			if ((*iControlArray)[index].iControl->HasBorder())
				adjacent|=internalVert;
			}
		}
	return adjacent;
	}

EXPORT_C CEikControlGroup::TStartCorner CEikControlGroup::StartCorner() const
	{
	return ((TStartCorner)(iLayout&KStartCornerMask));
	}

EXPORT_C CEikControlGroup::TOrientation CEikControlGroup::Orientation() const
	{
	return ((TOrientation)(iLayout&KOrientationMask));
	}

EXPORT_C TBool CEikControlGroup::DistributeEvenly() const
	{
	return iLayout&EDistributeEvenly;
	}

EXPORT_C TBool CEikControlGroup::AllSameSize()
	{
	const TBool sameSize=iLayout&EAllSameSize;
	if (sameSize && !(iLargestControl.iWidth && iLargestControl.iHeight))
		iLargestControl=LargestControlSize();
	return sameSize;
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikControlGroup::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CEikBorderedControl::GetColorUseListL(aColorUseList);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikControlGroup::HandleResourceChange(TInt aType)
	{
	CEikBorderedControl::HandleResourceChange(aType);
	}

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikControlGroup::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikControlGroup::WriteInternalStateL(RWriteStream& aWriteStream) const
	{	
	_LIT(KEikLitCtGrpCtlStart,"<CEikControlGroup>");
	_LIT(KEikLitCtGrpCtlEnd,"<\\CEikControlGroup>");
	_LIT(KEikLitCtGrpLay,"<iLayout>");
	_LIT(KEikLitCtGrpLayEnd,"<\\iLayout>");
	_LIT(KEikLitCtGrpLines,"<iLines>");
	_LIT(KEikLitCtGrpLinesEnd,"<\\iLines>");
	_LIT(KEikLitCtGrpHSp,"<iHSpacing>");
	_LIT(KEikLitCtGrpHSpEnd,"<\\iHSpacing>");
	_LIT(KEikLitCtGrpVSp,"<iVSpacing>");
	_LIT(KEikLitCtGrpVSpEnd,"<\\iVSpacing>");
	_LIT(KEikLitCtGrpBrd,"<iBreadth>");
	_LIT(KEikLitCtGrpBrdEnd,"<\\iBreadth>");
	_LIT(KEikLitCtGrpLen,"<iLength>");
	_LIT(KEikLitCtGrpLenEnd,"<\\iLength>");
	_LIT(KEikLitCtGrpLrgstCtl,"<iLargestControl>");
	_LIT(KEikLitCtGrpLrgstCtlEnd,"<\\iLargestControl>");
	
	aWriteStream << KEikLitCtGrpCtlStart;
	aWriteStream << KEikLitCtGrpLay;
	aWriteStream.WriteInt32L(iLayout);
	aWriteStream << KEikLitCtGrpLayEnd;
	aWriteStream << KEikLitCtGrpLines;
	aWriteStream.WriteInt32L(iLines);
	aWriteStream << KEikLitCtGrpLinesEnd;
	aWriteStream << KEikLitCtGrpHSp;
	aWriteStream.WriteInt32L(iHSpacing);
	aWriteStream << KEikLitCtGrpHSpEnd;
	aWriteStream << KEikLitCtGrpVSp;
	aWriteStream.WriteInt32L(iVSpacing);
	aWriteStream << KEikLitCtGrpVSpEnd;
	aWriteStream << KEikLitCtGrpBrd;
	aWriteStream.WriteInt32L(iBreadth);
	aWriteStream << KEikLitCtGrpBrdEnd;
	aWriteStream << KEikLitCtGrpLen;
	aWriteStream.WriteInt32L(iLength);
	aWriteStream << KEikLitCtGrpLenEnd;
	aWriteStream << KEikLitCtGrpLrgstCtl;
	aWriteStream << iLargestControl;
	aWriteStream << KEikLitCtGrpLrgstCtlEnd;
	CEikBorderedControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KEikLitCtGrpCtlEnd;
	}
#endif

EXPORT_C void CEikControlGroup::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikBorderedControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikControlGroup::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikControlGroup::Reserved_2()
	{}
