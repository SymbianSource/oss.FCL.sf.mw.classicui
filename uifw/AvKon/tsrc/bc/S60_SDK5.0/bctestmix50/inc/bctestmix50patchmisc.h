/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  declaration of test case
*
*/


#ifndef C_BCTESTMIX50PATCHMISC_H
#define C_BCTESTMIX50PATCHMISC_H

#include <eikcmobs.h>
#include <aknchoicelist.h>
#include <aknsinglestyletreelist.h>
#include <eikimage.h>
#include <aknpopup.h>
#include <aknsfld.h>
#include <aknvolumesettingpage.h>
#include <akntextsettingpage.h>
#include <aknslidersettingpage.h>
#include <aknradiobuttonsettingpage.h>
#include <aknpasswordsettingpage.h>
#include <aknmfnesettingpage.h>
#include <akncheckboxsettingpage.h>
#include <eiklbm.h>
#include <eiklbbut.h>
#include <aknfeppensupportinterface.h>
#include <COECOBS.H>
#include <eikfnlab.h>
#include <maknfilefilter.h>
#include <AknServerApp.h>
#include <AknsItemData.h>
#include <AknNoteDialog.h>

class CEikCommandButtonBase;
class MEikCommandObserver;
class CBCTestUIFWViewCase;

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestCommandButtonBase : public CEikCommandButtonBase
    {
    friend class CBCTestMix50PatchControlCase;
public: // constructor and destructor
    /**
     * C++ constructor
     */
    static CBCTestCommandButtonBase* NewL();
    
    /**
     * C++ destructor
     */
    virtual ~CBCTestCommandButtonBase();
    
    /**
     * Draw function
     */
    void Draw( const TRect& aRect )const;
    
    /**
     *  From CCoeControl
     *  Serialize the control's state. For testing
     * @param aWriteStream  Stream to write to.
     */ 
    void WriteInternalStateL(RWriteStream& aWriteStream) const;
        
private: // constructor
    
    /**
     * default constructor
     */
	CBCTestCommandButtonBase();
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestChoiceList : public CAknChoiceList
    {
    friend class CBCTestMix50PatchControlCase;
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestImage : public CEikImage
    {
    friend class CBCTestMix50PatchControlCase;
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestFadedComponent : public CBase,
                        public MAknFadedComponent
    {
    }; 

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestSearchfieldObserver : public CBase,
                        public MAdaptiveSearchTextObserver
    {
public:
    /** 
     * Notification and handling of an adaptive search text change.
     * @param aSearchField The source search field of this message. 
     */ 
    inline void AdaptiveSearchTextChanged( CAknSearchField* )
        {
        }
    };

/**
 *  CBCTestVolumeSettingPage class
 */
class CBCTestVolumeSettingPage : public CAknVolumeSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestVolumeSettingPage(TInt aResourceID, TInt& aVolume);
    
    /** 
     * C++ destructor  
     */ 
    virtual ~CBCTestVolumeSettingPage(){};
    };

/**
 *  CBCTestIntegerSettingPage class
 */
class CBCTestIntegerSettingPage : public CAknIntegerSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestIntegerSettingPage(TInt aResourceID, TInt& aValue, 
            TInt aTextSettingPageFlags = 0 );
    
    /** 
     * Destructor  
     */ 
    virtual ~CBCTestIntegerSettingPage(){};
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestTextSettingPage : public CAknTextSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestTextSettingPage(TInt aResourceID, TDes& aText, 
            TInt aTextSettingPageFlags = 0 );
    
    /** 
     * Destructor  
     */ 
    virtual ~CBCTestTextSettingPage(){}
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestSliderSettingPage : public CAknSliderSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestSliderSettingPage(TInt aResourceID, TInt& aSliderValue);
    
    /** 
     * Destructor  
     */ 
    virtual ~CBCTestSliderSettingPage(){}
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestPatchAknSettingPage: public CAknSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
	CBCTestPatchAknSettingPage( TInt aResourceId );
	
    /** 
     * Destructor  
     */ 
    virtual ~CBCTestPatchAknSettingPage(){}
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestRadioButtonSettingPage : public CAknRadioButtonSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestRadioButtonSettingPage(
            TInt aResourceID,
            TInt& aCurrentSelectionIndex,
            const MDesCArray* aItemArray );
    
    /** 
     * Destructor  
     */ 
    virtual ~CBCTestRadioButtonSettingPage(){}
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestNumericPasswordSettingPage : 
                                   public CAknNumericPasswordSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestNumericPasswordSettingPage(
            TInt aResourceID,
            TDes& aNewPassword,
            const TDesC& aOldPassword);
    
    /** 
     * Destructor  
     */ 
    virtual ~CBCTestNumericPasswordSettingPage(){}
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestAlphaPasswordSettingPage : public CAknAlphaPasswordSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestAlphaPasswordSettingPage(
            TInt aResourceID,
            TDes& aNewPassword,
            const TDesC& aOldPassword);
    
    /** 
     * Destructor  
     */ 
    virtual ~CBCTestAlphaPasswordSettingPage(){}
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestPasswordSettingPage : public CAknPasswordSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestPasswordSettingPage(
            TInt aResourceID,
            TDes& aNewPassword,
            const TDesC& aOldPassword);
    /** 
     * Destrucotor  
     */ 
    virtual ~CBCTestPasswordSettingPage(){}
    
    /** 
     * Update the text  
     */ 
    inline void UpdateTextL(){}
    };

/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestIpFieldSettingPage : public CAknIpFieldSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestIpFieldSettingPage( TInt aResourceID, TInetAddr& aIpAddress );
    };


/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestTimeOffsetSettingPage : public CAknTimeOffsetSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestTimeOffsetSettingPage( TInt aResourceID, 
            TTimeIntervalSeconds& aTimeOffsetValue );
    };


/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestCheckBoxSettingPage: public CAknCheckBoxSettingPage
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /** 
     * C++ Constructor  
     */ 
    CBCTestCheckBoxSettingPage(TInt aResourceID, 
            CSelectionItemList* aItemArray );
    };


/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestSnakingListBox : public CEikSnakingListBox
    {
    friend class CBCTestMix50PatchControlCase;
    };

/**
*  helper class for test CAknAppUi
*/
class CAknAppUiEx: public CAknAppUi
    {
    friend class CBCTestMix50PatchControlCase;
    friend class CBCTestMix50PatchViewCase;
public:
    
    /** 
     * C++ Constructor  
     */ 
    CAknAppUiEx();
    
    /** 
     * Destructor  
     */ 
    virtual ~CAknAppUiEx();
    
protected:
    /** 
     * Symbian second-phase constructor  
     */ 
    void Construct();
    };


/**
 *  CBCTestSingleStyleListBox class
 */
class CBCTestMAknAliasKeyCodeResolver : public CBase,
                                        public MAknAliasKeyCodeResolver
    {
    friend class CBCTestMix50PatchControlCase;
public:
    /**
    * Resolves keyboard layout dependent keycode for the given event 
    * @since S60 3.1
    * @param aCode reference to variable to contain new keycode 
    * @param aKeyEvent reference to original, complete, event
    * @param aType indicating original event type
    * @return KErrNone on success, otherwise system wide error codes
    */
    inline TInt GetAliasKeyCode(TUint& /* aCode */, 
    		const TKeyEvent& /* aKeyEvent */,TEventCode /* aType */ )
    	{ return 0; }
    };

/**
 *  CBCTestFepPen class
 */
class CBCTestFepPen: public CBase, public MAknFepPenSupportInterface
    {
public:
    /**
     * Start pen input method
     *
     * @since S60 v3.2
     * @return None
     */
    inline void ActivatePenInputL(){}
    
    /**
     * Close pen input method
     *
     * @since S60 v3.2
     * @return None
     */
    inline void DeactivatePenInputL(){}
    };

/**
 *  CBCTestEikFileNameLabel class
 */
class CBCTestEikFileNameLabel : public CEikFileNameLabel
	{
	friend class CBCTestMix50PatchControlCase;
	};

/**
 *  MonkFilter
 */
struct MonkFilter: public MAknFileFilter
    {

    /**
     * Checks if a file is accepted by the filter.
     * @param aDriveAndPath Drive and full path of the file.
     * @param aEntry A directory entry.
     * @return Returns ETrue if filter accepts the file.
     */
    TBool Accept( const TDesC& /*aDriveAndPath*/, 
            const TEntry& /*aEntry*/ ) const
        {
        return ETrue;
        }
    };

/**
*  helper class for test CAknAppServiceBase 
*/
class CBCTestAppServiceBase : public CAknAppServiceBase, 
                              public MAknServerAppExitObserver
	{
	friend class CBCTestMix50PatchViewCase;
public:
    /**
    * Handle the exit of a connected server app.
    * This implementation provides Series 60 default behavior
    * for handling of the EAknCmdExit exit code. Derived classes
    * should base-call this implementation if they override this
    * function.
    * @param aReason The reason that the server application exited.
    * This will either be an error code, 
    * or the command id that caused
    * the server app to exit.
    */
	void HandleServerAppExit(TInt aReason);
	
protected:
    /**
    * Override of CSession2::CreateL().
    * If further overridden, this function must be base-called.
    */
	void CreateL();
	
    /**
    * Override of CSession2::ServiceL().
    * If further overridden, this function must be base-called.
    * @param aMessage The client message
    */
	void ServiceL(const RMessage2& aMessage);
	
    /**
    * Override of CSession2::ServiceError().
    * If further overridden, this function must be base-called.
    * @param aMessage The client message.
    * @param aError The error code to which 
    * occured during message servicing
    */
	void ServiceError(const RMessage2& aMessage,TInt aError);
	};

/**
*  helper class for test CAknNoteDialog 
*/
class CBCTestAknNoteDialog : public CAknNoteDialog
	{
	friend class CBCTestMix50PatchControlCase;
public:
    /**
     * C++ default constructor.
     *
     * @param aSelfPtr Pointer to the address of the dialog.
     * @param aTone = @c ENoTone The tone. 
     * @param aTimeout = @c ENoTimeout The timeout (microseconds). 
     * @see @c TTone, @c TTimeout.
     */
    IMPORT_C CBCTestAknNoteDialog(CEikDialog** aSelfPtr, 
                            const TTone& aTone = ENoTone, 
                            const TTimeout& aTimeout = ENoTimeout)
    	: CAknNoteDialog( aSelfPtr, aTone, aTimeout )
    	{
    	
    	}
    
    /**
     * Deletes the note dialog.
     *
     * @see @c TTimer, @c OkToExitL(), @c ExitSleepingDialog().
     * @param aThis Pointer to the dialog.
     * @return Always returns @c EFalse.
     */
    IMPORT_C static TInt OwnStaticDeleteL(TAny* aThis)
    	{
    	return CAknNoteDialog::StaticDeleteL( aThis );
    	}
	};
#endif /*C_BCTESTMIX50PATCHMISC_H*/
