/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include "BCTestTextSettingPage.h"
#include "AknSettingPage.h"


// Number of lines in Text Setting Page; Same in APAC and ELAF:
//const TInt KTextSettingPageLines = 6;

class CAknTextSettingPageExtension : public CBase
    {
    public:
    static CAknTextSettingPageExtension* NewL()
        {
        CAknTextSettingPageExtension* extension =
            new (ELeave) CAknTextSettingPageExtension();
        CleanupStack::PushL(extension);
        extension->ConstructL();
        CleanupStack::Pop(extension);
        return extension;
        }

    ~CAknTextSettingPageExtension()
        {
        }

    private:
    void ConstructL()
        {
        }
    CAknTextSettingPageExtension()
        {
        }
    };

/**
 * Exported in case others want to derive from this class
 *
 */
EXPORT_C CBCTestEdwinSettingPage::CBCTestEdwinSettingPage( TInt aResourceId )
    : CAknEdwinSettingPage(aResourceId)
    {
    }


EXPORT_C CBCTestEdwinSettingPage::CBCTestEdwinSettingPage(
                                const TDesC* aSettingText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId )
                                :   CAknEdwinSettingPage(
                                    aSettingText,
                                    aSettingNumber,
                                    aControlType,
                                    aEditorResourceId,
                                    aSettingPageResourceId )
    {
    }

/**
 * All setting pages containing edwins will have the same draw code
 *
 */
EXPORT_C void CBCTestEdwinSettingPage::Draw(const TRect& aRect) const
    {
    CAknEdwinSettingPage::Draw( aRect );
    }


void CBCTestEdwinSettingPage::SizeChanged()
    {
    }
    
void CBCTestEdwinSettingPage::ConstructL()
    {
    BaseConstructL();
    }


///////////////////////////////////////////////////////////////////////
//
// CAknTextSettingPage
//
///////////////////////////////////////////////////////////////////////

/**
 *
 * Constructor from setting page resource id + referenced text + flags
 *
 */
EXPORT_C CBCTestTextSettingPage::CBCTestTextSettingPage( TInt aResourceId, TDes& aText, TInt aFlags ):
     CAknTextSettingPage( aResourceId, aText, aFlags )
    {
    }

EXPORT_C CBCTestTextSettingPage::CBCTestTextSettingPage(
                                const TDesC* aSettingText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TDes& aText,
                                TInt aTextSettingPageFlags)
                                :   CAknTextSettingPage(
                                    aSettingText,
                                    aSettingNumber,
                                    aControlType,
                                    aEditorResourceId,
                                    aSettingPageResourceId,
                                    aText,
                                    aTextSettingPageFlags )
    {
    }

/**
 * Destructor
 *
 */
EXPORT_C CBCTestTextSettingPage::~CBCTestTextSettingPage()
    {
    }

/**
 *
 * This routine is called before the editor when the editor is first displayed.  This routine
 * puts in altered softkey bindings if there is zero-length text.
 *
 */
EXPORT_C void CBCTestTextSettingPage::DynamicInitL()
    {
    CAknTextSettingPage::DynamicInitL();
    }
/**
 *
 * This routine is called when the a change is detected in the editor.
 * The text is copied out to the referenced descriptor using a utility routine.
 *
 */
EXPORT_C void CBCTestTextSettingPage::UpdateSettingL()
    {
    CAknTextSettingPage::UpdateSettingL();
    }
/**
 * Soak up function to do the safe copying of the editor to the referenced value
 *
 */
EXPORT_C void CBCTestTextSettingPage::UpdateTextL()
    {
    CAknTextSettingPage::UpdateTextL();
    }
/**
 *
 * The value is copied out and the call back called if there is an observer
 *
 */
EXPORT_C void CBCTestTextSettingPage::AcceptSettingL()
    {
    CAknTextSettingPage::AcceptSettingL();
    }

/**
 *
 * If the setting page is cancelled, this is called to restore the backed up copy of the
 * input text
 *
 */
EXPORT_C void CBCTestTextSettingPage::RestoreOriginalSettingL()
    {
    CAknTextSettingPage::RestoreOriginalSettingL();
    }

EXPORT_C void CBCTestTextSettingPage::UpdateCbaL()
    {
    CAknTextSettingPage::UpdateCbaL();
    }

EXPORT_C void CBCTestTextSettingPage::SizeChanged()
    {
    CAknTextSettingPage::SizeChanged();
    }

/**
* Validity is alway ETrue unless the flag asking for some non-whitespace data is set.
* If set, and if there is an edwin, then check to see that there is a valid character
* somewhere in the text
*/
EXPORT_C void CBCTestTextSettingPage::CheckAndSetDataValidity()
    {
    CAknTextSettingPage::CheckAndSetDataValidity();
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestTextSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestTextSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknTextSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif

/**
*
* This routes the keys to the editor.
* However, if the menu is showing, then events have to be forwarded manually to it.
*
*/
EXPORT_C TKeyResponse CBCTestTextSettingPage::BCOfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return CAknTextSettingPage::OfferKeyEventL(aKeyEvent, aType);
    }

/**
* Framework method to determine if it OK to exit the setting page.
* Derived classes may check for valid data before allowing the dismissal of the
* setting page.
*/
EXPORT_C TBool CBCTestTextSettingPage::OkToExitL(TBool aAccept)
    {
    return CAknTextSettingPage::OkToExitL( aAccept );
    }
    
EXPORT_C void CBCTestTextSettingPage::HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType )
    {
    CAknTextSettingPage::HandleControlEventL( aControl, aEventType );
    }


/////////////////////////////////////////////////////////////////////////
//
// Integer Edwin
//
/////////////////////////////////////////////////////////////////////////

/**
 *
 * Constructor from setting page resource id + referenced text + flags
 *
 */
EXPORT_C CBCTestIntegerSettingPage::CBCTestIntegerSettingPage( TInt aResourceId, TInt& aValue, TInt aFlags ):
     CAknIntegerSettingPage( aResourceId, aValue, aFlags )
    {
    }

EXPORT_C CBCTestIntegerSettingPage::CBCTestIntegerSettingPage(
                                const TDesC* aSettingText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TInt& aValue,
                                TInt aIntegerSettingPageFlags)
                                :   CAknIntegerSettingPage(
                                    aSettingText,
                                    aSettingNumber,
                                    aControlType,
                                    aEditorResourceId,
                                    aSettingPageResourceId,
                                    aValue,
                                    aIntegerSettingPageFlags )
    {
    }


/**
 *
 * This routine is called before the editor when the editor is first displayed.  This routine
 * puts in altered softkey bindings if there is zero-length text.
 *
 */
EXPORT_C void CBCTestIntegerSettingPage::DynamicInitL()
    {
    CAknIntegerSettingPage::DynamicInitL();
    }
/**
 *
 * This routine may be called when the a change is detected in the editor.
 * The text is copied out to the referenced descriptor using a utility routine.
 *
 */
EXPORT_C void CBCTestIntegerSettingPage::UpdateSettingL()
    {
    CAknIntegerSettingPage::UpdateSettingL();
    }

/**
 *
 * If the setting page is cancelled, this is called to restore the backed up copy of the
 * input text
 *
 */
EXPORT_C void CBCTestIntegerSettingPage::RestoreOriginalSettingL()
    {
    CAknIntegerSettingPage::RestoreOriginalSettingL();
    }


EXPORT_C void CBCTestIntegerSettingPage::UpdateCbaL()
    {
    CAknIntegerSettingPage::UpdateCbaL();
    }

EXPORT_C void CBCTestIntegerSettingPage::SizeChanged()
    {
    CAknIntegerSettingPage::SizeChanged();
    }


EXPORT_C void CBCTestIntegerSettingPage::CheckAndSetDataValidity()
    {
    CAknIntegerSettingPage::CheckAndSetDataValidity();
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestIntegerSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestIntegerSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknIntegerSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif

EXPORT_C void CBCTestIntegerSettingPage::HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType )
    {
    CAknIntegerSettingPage::HandleControlEventL( aControl, aEventType );
    }


// End of File
