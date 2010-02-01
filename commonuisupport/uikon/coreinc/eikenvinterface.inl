// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __EIKENVINTERFACE_INL__
#define __EIKENVINTERFACE_INL__

#include <eikenv.h>

/**
@publishedPartner
@released
*/
inline TInt CEikonEnv::EditableControlStandardHeight() const
	{ return(iEditableControlStandardHeight); }

/**
@publishedPartner
@released
*/
inline void CEikonEnv::SetCDlgDialogFactory(MEikCDlgDialogFactory* aDialogFactory)
	{iCDlgDialogFactory=aDialogFactory;}

/**
@publishedPartner
@released
*/
inline void CEikonEnv::SetPrintDialogFactory(MEikPrintDialogFactory* aDialogFactory)
	{iPrintDialogFactory=aDialogFactory;}

/**
@publishedPartner
@released
*/
inline void CEikonEnv::SetFileDialogFactory(MEikFileDialogFactory* aDialogFactory)
	{iFileDialogFactory=aDialogFactory;}

/**
@publishedPartner
@released
*/
inline void CEikonEnv::SetIrFactory(MEikIrFactory* aIrFactory)
	{iIrFactory=aIrFactory;}

/**
@publishedPartner
@released
*/
inline MEikCDlgDialogFactory* CEikonEnv::CDlgDialogFactory() const
	{return iCDlgDialogFactory;}

/**
@publishedPartner
@released
*/
inline MEikPrintDialogFactory* CEikonEnv::PrintDialogFactory() const
	{return iPrintDialogFactory;}

/**
@publishedPartner
@released
*/
inline MEikFileDialogFactory* CEikonEnv::FileDialogFactory() const
	{return iFileDialogFactory;}

/**
@publishedPartner
@released
*/
inline MEikIrFactory* CEikonEnv::IrFactory() const
	{return iIrFactory;}


/**
@publishedPartner
@released
*/
inline TInt CEikonEnv::StatusPaneCoreResId() const
	{return iStatusPaneCoreResId;}

/**
@publishedPartner
@released
*/
inline void CEikonEnv::SetStatusPaneCoreResId(TInt aStatusPaneCoreResId)
	{iStatusPaneCoreResId=aStatusPaneCoreResId;}

/**
@publishedPartner
@released
*/
inline CEikAutoMenuTitleArray* CEikonEnv::AutoMenuTitleArray() const
	{return iAutoMenuTitleArray;}


#endif // __EIKENVINTERFACE_INL__
