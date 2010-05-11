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

#include <coecntss.h>	// class CCoeControlStaticSettings
#include <coeaui.h>		// class CCoeAppUi


const TUid KUidCoeControlStaticSettings = {0x10204232};

/** Constructor
*/
CCoeControlStaticSettings::CCoeControlStaticSettings() :
	CCoeStatic(KUidCoeControlStaticSettings),
	iFocusedByDefault(ETrue), iOrdinalForAllViews(EFalse)
	{
	}

/** 
Class Destructor */	
CCoeControlStaticSettings::~CCoeControlStaticSettings()
	{
	iLogicalToPixelSizes.Reset();
	iLogicalToPixelSizes.Close();
	}

/** Retrieve the one and only CCoeControlStaticSettings object, if it exists.
*/
CCoeControlStaticSettings* CCoeControlStaticSettings::Self(CCoeEnv* aCoeEnv)
	{
	return static_cast<CCoeControlStaticSettings*>(aCoeEnv ? 
		aCoeEnv->FindStatic(KUidCoeControlStaticSettings) : 
		CCoeEnv::Static(KUidCoeControlStaticSettings));
	}
	
/**
Creates new instance of CCoeControlStaticSettings class
 
@return pointer to the instance of CCoeControlStaticSettings class */		
CCoeControlStaticSettings* CCoeControlStaticSettings::NewL()
	{
	CCoeControlStaticSettings* staticSettings = new (ELeave) CCoeControlStaticSettings();
	CleanupStack::PushL(staticSettings);
	staticSettings->ConstructL();
	CleanupStack::Pop(staticSettings);
	return staticSettings;	
	}

/**
Second stage construction of CCoeControlStaticSettings class */		
void CCoeControlStaticSettings::ConstructL()
	{
	iFocusedByDefault = ETrue;
	_LIT(KSystemTypeFaceName, "System One");
	iTypeface.iName = KSystemTypeFaceName;
		
    User::LeaveIfError(iLogicalToPixelSizes.Append(8)); 
    User::LeaveIfError(iLogicalToPixelSizes.Append(14)); 
    User::LeaveIfError(iLogicalToPixelSizes.Append(18)); 
    User::LeaveIfError(iLogicalToPixelSizes.Append(22)); 
    User::LeaveIfError(iLogicalToPixelSizes.Append(26));   
	}
	
/** 
Does nothing.
@see CCoeControlStaticSettings::ParentByDefault()
@deprecated
*/
EXPORT_C void CCoeControlStaticSettings::SetParentByDefaultL(TBool /*aParentByDefault*/)
	{
	}

/** 
Returns value of ROM-patchable constant KCoeSetControlParentByDefault.
Patch for emulator builds by adding "patchdata_cone_dll_KCoeSetControlParentByDefault X"
to epoc.ini where X is either 0 (zero) for "off" or 1 (one) for "on".
Only valid in Symbian OS 9.3 and 9.4.
@deprecated
*/
EXPORT_C TBool CCoeControlStaticSettings::ParentByDefault()
// class defined in coecntss.h to keep it away from prying eyes.
	{
	return ETrue;
	}

/** Globally sets whether a window's ordinal is set for all views (ETrue) or only
    when the top view is not active (EFalse)

This function should be called from within a CEikLibrary plugin.
@param aOrdinalForAllViews ETrue if the window's ordinal will be set for all views,
                           EFalse if not.
*/
EXPORT_C void CCoeControlStaticSettings::SetOrdinalForAllViewsL(TBool aOrdinalForAllViews)
	{
	CCoeControlStaticSettings* self = Self();
	if (!self)
		self = CCoeControlStaticSettings::NewL();

	self->iOrdinalForAllViews = aOrdinalForAllViews;
	}

/** Retrieves the global setting that determines whether a window's ordinal is set for
    all views (ETrue) or only when the top view is not active (EFalse)

If the CCoeControlStaticSettings object does not exist, then the default
is to return EFalse.
@return ETrue if a window's ordinal should be set for all views, EFalse if not.
*/
EXPORT_C TBool CCoeControlStaticSettings::OrdinalForAllViews()
	{
	CCoeControlStaticSettings* self = Self();
	TBool retval = EFalse;
	if (self)
		retval = self->iOrdinalForAllViews;
	
	return retval;
	}	
	

/** Globally sets whether CCoeControls should take focus when they are created.

This function should be called from within a CEikLibrary plugin.
@param aFocusedByDefault True if CCoeControls should take focus when created, false if not.
*/
EXPORT_C void CCoeControlStaticSettings::SetFocusedByDefaultL(TBool aFocusedByDefault)
	{
	CCoeControlStaticSettings* self = Self();
	if (!self)
		self = CCoeControlStaticSettings::NewL();

	self->iFocusedByDefault = aFocusedByDefault;
	}

/** Retrieves the global setting that determines whether CCoeControls take 
focus when created.

If the CCoeControlStaticSettings object does not exist, then the default
is to return true, which gives unchanged behaviour from pre-v9.0 releases.
@return True if CCoeControls take focus when created, false if not.
*/
EXPORT_C TBool CCoeControlStaticSettings::FocusedByDefault()
	{
	return FocusedByDefault(NULL);
	}

/** Retrieves the global setting that determines whether CCoeControls take 
focus when created.

If the CCoeControlStaticSettings object does not exist, then the default
is to return true, which gives unchanged behaviour from pre-v9.0 releases.
@return True if CCoeControls take focus when created, false if not.
@param aCoeEnv The Control environment.
*/
EXPORT_C TBool CCoeControlStaticSettings::FocusedByDefault(CCoeEnv* aCoeEnv)
// class defined in coecntss.h to keep it away from prying eyes.
	{
	CCoeControlStaticSettings* self=Self(aCoeEnv);
	TBool retval = ETrue;
	if (self)
		retval = self->iFocusedByDefault;

	return retval;
	}

/**
 Returns the default system type face name.
 
 @return default system typeface name */		
EXPORT_C const TDesC& CCoeControlStaticSettings::SystemTypeface()
	{
	CCoeControlStaticSettings* self = Self();
	if (self)
		return self->iTypeface.iName;
	else
		{
		_LIT(KSystemTypeFaceName, "System One");
		return KSystemTypeFaceName;
		}	
	}

/**
 Sets the default system type face name.
 
 @param aTypeface is the name to set default system typeface name to */	
EXPORT_C void CCoeControlStaticSettings::SetSystemTypefaceL(const TDesC& aTypeface)
	{
	CCoeControlStaticSettings* self = Self();
	if (!self)
		self = CCoeControlStaticSettings::NewL();
   		
   	self->iTypeface.iName = aTypeface;	
	}
	
/**
 Populates the TInt array provided as a parameter with the font pixel sizes.
 
 @param aLogicalToPixelSizes TInt array to be poulated with font sizes */			
EXPORT_C void CCoeControlStaticSettings::GetLogicalToPixelFontSizesL(RArray<TInt>& aLogicalToPixelSizes)
	{
    CleanupClosePushL(aLogicalToPixelSizes);
	CCoeControlStaticSettings* self = Self();
	aLogicalToPixelSizes.Reset();
	
	if (self)
		{
		for (TInt i=0; i<self->iLogicalToPixelSizes.Count(); i++)
			User::LeaveIfError(aLogicalToPixelSizes.Append(self->iLogicalToPixelSizes[i]));
		}
	else
		{
	    User::LeaveIfError(aLogicalToPixelSizes.Append(8)); 
	    User::LeaveIfError(aLogicalToPixelSizes.Append(14)); 
	    User::LeaveIfError(aLogicalToPixelSizes.Append(18)); 
	    User::LeaveIfError(aLogicalToPixelSizes.Append(22)); 
	    User::LeaveIfError(aLogicalToPixelSizes.Append(26)); 
		}
	CleanupStack::Pop(&aLogicalToPixelSizes);
	}
	
/**
Sets the default array of font pixel sizes.
 
@param aLogicalToPixelSizes TInt array to use as default with font sizes */			
EXPORT_C void CCoeControlStaticSettings::SetLogicalToPixelFontSizesL(const RArray<TInt>& aLogicalToPixelSizes)
	{
	CCoeControlStaticSettings* self = Self();
	if (!self)
		self = CCoeControlStaticSettings::NewL();
		
	self->iLogicalToPixelSizes.Reset();
	
	for (TInt i=0; i<aLogicalToPixelSizes.Count(); i++)
		User::LeaveIfError(self->iLogicalToPixelSizes.Append(aLogicalToPixelSizes[i]));
		
	CCoeEnv* env = CCoeEnv::Static();
	if (env)
		{
		env->RefetchPixelMappingL();
		CCoeAppUi* appUi = env->AppUi(); 
    	if(appUi) 
    		appUi->RefetchPixelMappingL();
		}
	}

