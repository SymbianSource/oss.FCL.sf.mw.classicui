/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Class for extended input capabilities
*
*/


#ifndef AKNEXTENDEDINPUTCAPABILITIES_H
#define AKNEXTENDEDINPUTCAPABILITIES_H

#include <e32base.h>
#include <coemop.h>
#include <w32std.h>

/**
 *  Class for extended input capabilities
 *
 *  This class can be used for customized input capabilities in addition to
 *  TCoeInputCapabilities and can be acquired from controls supporting
 *  this class using TCoeInputCapabilities::ObjectProvider().
 *
 *  @lib eikctl.lib
 *  @since S60 v3.1
 */
NONSHARABLE_CLASS(CAknExtendedInputCapabilities) : public CBase
    {
public:
    DECLARE_TYPE_ID(0x10282348)

    /**
     * An object provider class for extended input capabilities.
     *
     * This has been separated from CCoeControl's MObjectProvider
     * implementation to allow better binary compatibility in case
     * the CCoeControl derived control which needs the extended input
     * capabilities doesn't implement MObjectProvider's virtual functions.
     * This class is meant to be passed through the control's 
     * TCoeInputCapabilities object provider pointer.
     *
     * This class is usually to be instantiated and owned by the same
     * or relevant object which also owns the extended input capabilities,
     * although for flexibility it is not coupled with the
     * CAknExtendedInputCapabilities class itself.
     *
     * @since S60 v3.1
     */        
    NONSHARABLE_CLASS(CAknExtendedInputCapabilitiesProvider) : public CBase,
        public MObjectProvider
        {
    public:
        /**
         * C++ constructor. While the constructor is public, this class
         * is not intended for derivation.
         */
        IMPORT_C CAknExtendedInputCapabilitiesProvider();
    
        /**
         * Destructor.
         */
        IMPORT_C virtual ~CAknExtendedInputCapabilitiesProvider();
        
        /**
         * Sets a pointer to the CAknExtendedInputCapabilities that will be
         * supplied when MopGetObject() is called. This class doesn't own the
         * CAknExtendedInputCapabilities object.
         * 
         * @since S60 v3.1
         * @param aExtendedInputCapabilities A pointer to an object of type
         * CAknExtendedInputCapabilities
         */
        IMPORT_C void SetExtendedInputCapabilities(
            CAknExtendedInputCapabilities* aExtendedInputCapabilities );

        /**
         * Gets the pointer to the CAknExtendedInputCapabilities that will be
         * supplied when MopGetObject() is called.
         *
         * @since S60 v3.1
         * @return The pointer to the supplied extended input capabilities
         */
        IMPORT_C CAknExtendedInputCapabilities* ExtendedInputCapabilities() const;
        
        /**
         * Sets the parent object provider. This is usually the control which
         * owns the supplied extended input capabilities.
         *
         * @since S60 v3.1
         * @param aObjectProvider The parent object provider.
         */
        IMPORT_C void SetMopParent( MObjectProvider* aObjectProvider );
        
    protected:
        TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
        MObjectProvider* MopNext();
        
    private: // data
        /**
         * The pointer to the extended input capabilities
         * 
         * Not own.
         */
        CAknExtendedInputCapabilities* iExtendedInputCapabilities;
        
        /**
         * The pointer to a parent object provider.
         *
         * Not own.
         */
        MObjectProvider* iParent;
        };
    
    /**
     * A simple interface for sending events to observers.
     *
     * @since S60 v3.2
     */
    class MAknEventObserver
        {
    public:

        /**  Events for MAknEventObserver */
        enum TInputCapabilitiesEvent
            {
            /** Requests pen input activation (VKB or HWR), parameter not used */
            EActivatePenInputRequest,
            /** Lightweight way of telling e.g. FEP that control has received
                pointer event, parameter is a pointer to
                TPointEventReceivedParams */
            EPointerEventReceived,
            /** Signals observer that the control (editor) content has been
                changed for example non-interactively through API. Note that
                it is not always possible for the control to determine where
                the change was initiated, so this event might be sent
                even when the editor contents are changed by FEP.
                Parameter not used. */
            EControlContentUpdatedInternally,
            /** Signals observer (FEP) to open a stylus menu with ccpu
                options.
                Parameter not used. */
            EOpenStylusMenuCcpu
            };
            
        /**
         * Parameter structure for EPointerEventReceived event
         *
         * @since S60 v3.2
         */
        struct TPointerEventReceivedParams
            {
            /** Unmodified pointer event */
            TPointerEvent iPointerEvent;
            /** Document position of the pointer event */
            TInt iDocPos;
            };

        /**
         * Handle an event. Note that the possible parameters are valid only
         * while this functions is called. If client needs to use them
         * later, it needs to copy them. Due to the internal nature of
         * this interface the aParams is trusted not to get changed in
         * the observers.
         *
         * @since S60 v3.2
         * @param aEvent An event, see TInputCapabilitiesEvent
         * @param aParams Event dependent parameters
         */
        virtual void HandleInputCapabilitiesEventL( TInt aEvent, TAny* aParams ) = 0;
        };
        
    /**  Bits for simple input capabilities  */
    enum TInputCapabilities
        {
        ESupportsOnlyASCIIDigits = 0x00000001,
        EForceEditSubmenuStatusFlagOff      = 0x00000002,
        EForceHashKeySelectionStatusFlagOff = 0x00000004,
        /** Requested by Java LCDUI to disable launching of SCT while
            being able to define certain VKB keys using
            SetAknEditorSpecialCharacterTable(). */
        EDisableSCT = 0x00000008,
        // for notifing FEP the alignment of editor
        EInputEditorAlignCenter = 0x00000010,
        EInputEditorAlignLeft = 0x00000020,
        EInputEditorAlignRight = 0x00000040,
        EInputEditorAlignBidi = 0x00000080,
        EInputEditorDisableVKB = 0x00000100,
        EInputEditorRevealSecretText = 0x00000200,
        EInputEditorQwertyInputActive = 0x00000400,
        EInputEditorPartialScreen = 0x00000800
        };
    static const TInt KAknEditorAlignMask = 0x000000f0;
       
    /**  In case of editors, the editor's type, additions can be made later */
    enum TEditorType
        {
        EUndefined,
        EEdwinBased,
        EMFNEBased,
        EPhoneNumberEditor,
        EAknIntegerEdwinBased,
        EEikSecretEditorBased,
        EHybridAlphaNumericEditor
        };

    IMPORT_C static CAknExtendedInputCapabilities* NewL();

    IMPORT_C static CAknExtendedInputCapabilities* NewLC();

    IMPORT_C virtual ~CAknExtendedInputCapabilities();

    /**
     * Sets the simple input capabilities
     *
     * @since S60 v3.1
     * @param aCapabilities The simple input capabilities to be set
     */
    IMPORT_C void SetCapabilities( TUint aCapabilities );
    
    /**
     * Gets the simple input capabilities
     *
     * @since S60 v3.1
     * @return The current simple input capabilities
     */
     IMPORT_C TUint Capabilities() const;

    /**
     * Tests if the given bitmask is supported
     *
     * @since S60 v3.1
     * @param aCapabilities The simple input capabilities to be tested
     * @return ETrue, if all the given capabilities are supported
     */
     IMPORT_C TBool SupportsCapabilities( TUint aCapabilities ) const;
         
    /**
     * Sets MIDP constraints, as defined in the MIDP for
     * javax.microedition.lcdui.TextField and .TextBox. For the values, see
     * the class definition for MMIDTextField.
     * 
     * @since S60 v3.1
     * @param aConstraints The MIDP constraints to be set for the control owning
     *                     this CAknExtendedInputCapabilities
     */
    IMPORT_C void SetMIDPConstraints( TUint aConstraints );

    /**
     * Gets MIDP constraints, as defined in the MIDP for
     * javax.microedition.lcdui.TextField and .TextBox. 
     * 
     * @since S60 v3.1
     * @return The MIDP constraints for the control owning this 
     *         CAknExtendedInputCapabilities
     */
    IMPORT_C TUint MIDPConstrainst() const;
    
    /**
     * If the control is an editor, sets the type for the
     * editor.
     *
     * @since S60 v3.1
     * @param aEditorType The editor's type
     */
    IMPORT_C void SetEditorType( TInt aEditorType );
    
    /**
     * Gets the editor type.
     *
     * @since S60 v3.1
     * @return The editor's type
     */
    IMPORT_C TInt EditorType() const;
    
    /**
     * Registers an observer
     *
     * @since S60 v3.2
     * @param aObserver Observer to listen to messages
     */
    IMPORT_C void RegisterObserver( MAknEventObserver* aObserver );
    
    /**
     * Unregisters an observer
     *
     * @since S60 v3.2
     * @param aObserver Observer to be removed from observers
     */
    IMPORT_C void UnregisterObserver( MAknEventObserver* aObserver );
    
    /**
     * Sends an event to observers
     *
     * @since S60 v3.2
     * @param aEvent An event, see MAknEventObserver::TInputCapabilitiesEvent
     * @param aParams Event dependent parameters
     */
    IMPORT_C void ReportEventL( TInt aEvent, TAny* aParams );

private:
    CAknExtendedInputCapabilities();

    void ConstructL();

private: // data

    /**
     * Simple input capabilities bitflags
     */
    TUint iInputCapabilities;
    
    /**
     * MIDP constraints
     */
    TUint iMIDPConstraints;
    
    /**
     * Editor type
     */
    TInt iEditorType;
    
    /**
     * MAknMessageObserver observer pointer array
     */
    RPointerArray<MAknEventObserver> iObserverArray;
    };

#endif // AKNEXTENDEDINPUTCAPABILITIES_H
