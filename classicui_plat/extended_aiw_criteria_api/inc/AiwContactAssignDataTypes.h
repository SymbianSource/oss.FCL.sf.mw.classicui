/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Defines types used in AIW contact assign services.
*
*/





#ifndef __AIWCONTACTASSIGNDATATYPES_H__
#define __AIWCONTACTASSIGNDATATYPES_H__

#include <AiwGenericParam.hrh>
#include <coehelp.h>

namespace AiwContactAssign {

/**
 * Type of the contact assign.
 */
enum TAiwContactAssignDataType
    {
    EAiwContactAssignDataTypeNotDefined,
    EAiwSingleContactAssignV1,
    EAiwMultipleContactAssignV1,
    EAiwContactAttributeAssignV1
    };

/**
 * Parameter flags for contact assign service.
 */
enum TAssignFlags
    {
    /**
     * By default assign, if used as a menu service, shows a
     * menu item which haves subitems Update Existing and Add new.
     * If this flag is set, a plain main level Assign menu item is shown.
     *
     * The flag is valid only in single contact assign,
     * since multiple contact assign always uses the simple menu.
     * Also contact attribute assign uses just the simple menu.
     */
    EUseSimpleMenu                  = 0x0001,

    /**
     * This flag only has meaning if EUseSimple menu is used,
     * or if this service is used as a base service (no menus at all).
     * Then, by default, the assign updates an existing contact,
     * but by raising this flag a new contact is created instead.
     *
     * The flag is valid only in single contact assign,
     * since multiple contact assign can not create new contacts.
     * Contact attribute assign also can note create new contacts.
     */
    ECreateNewContact               = 0x0002,

    /**
     * If EDoNotOpenEditor flag is up, the selected contact is not opened
     * to an editor but the data/attribute is directly assigned to
     * the contact and the user is informed about it with a note.
     * The flag is ignored when creating a new contact instead
     * of updating an existing one - in that case editor is always
     * opened.
     *
     * The flag is valid only in single contact assign,
     * since multiple contact assign and contact attribute assign
     * never open editor.
     */
    EDoNotOpenEditor                = 0x0004,

    /**
     * If set, the editor is missing an Exit option.
     *
     * The flag is valid only in single contact assign.
     */
    EHideEditorExit                 = 0x0008,

    /**
     * If set the fetch dialog will use default provider title
     * ("Contacts", for example), otherwise client's current title is used.
     */
    EUseProviderTitle               = 0x0010,
/*<branchInfo originator="gronoff" since="03-10-2008" category="new_feature" error=”none”>
<PF5250_OFF_CYCLE_SW_INT>
</branchInfo>*/
// BRANCH 03-10-2008 :gronoff
    /**
     * If set, infonotes are not shown when user exits from
     * contact assign service. When set infonotes like "Contact
     * details updated" etc are not shown.
     */
    EskipInfoNotes                  = 0x0020,
// BRANCH_END 03-10-2008 :gronoff

    /**
     * If set the fetch view will use custom filtering. When building the
     * view the client is asked with KAiwEventInParamCheck, for every contact,
     * does the contact belong to the view. This is rather slow.
     */
    EUseClientSideFiltering = 0x0040
    };

/**
 * Base class for different versions of the contact assign data.
 */
class TAiwContactAssignDataBase
    {
    public: // Type checking
        /**
         * Function for checking the type of the contact assign
         * data in a data buffer.
         *
         * @param aBuffer A buffer containing an instance of a contact
         *                assign data class derived from this class.
         * @return  Type of the data class that is in the buffer.
         */
        inline static TAiwContactAssignDataType AssignDataTypeFromBuffer(
                    const TDesC8& aBuffer );

        /**
         * Public constructor.
         */
        explicit inline TAiwContactAssignDataBase();

    protected: // Constructor
        /**
         * Constructor that sets the type of the data class.
         *
         * @param aAssignDataType Type of the contact assign data.
         */
        inline TAiwContactAssignDataBase(
                TAiwContactAssignDataType aAssignDataType );

    private: // Implementation
        /**
         * Returns the type of the contact assign data class.
         *
         * @return  The type of the contact assign data class.
         */
        inline TAiwContactAssignDataType AssignDataType() const;

    private: // Data
        /// Own: Type of the contact assign data class.
        TAiwContactAssignDataType iAssignDataType;
    };

/**
 * Version 1 of the single contact assign data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      assignData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwSingleContactAssignDataV1 : public TAiwContactAssignDataBase
    {
    public: // Data type
        static const TAiwContactAssignDataType
            KAssignDataType = EAiwSingleContactAssignV1;

    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwSingleContactAssignDataV1();

    public: // Setters for the data members
        /**
         * Sets assign flags, @see TAssignFlags.
         *
         * @param aFlags The flags to set.
         * @return  Reference to this object.
         */
        inline TAiwSingleContactAssignDataV1& SetFlags(
                TUint aFlags );

        /**
         * Sets editor help context.
         * By default the editor uses Phonebook's help context.
         *
         * @param aFlags The new help context.
         * @return  Reference to this object.
         */
        inline TAiwSingleContactAssignDataV1& SetEditorHelpContext(
                TCoeHelpContext aHelpContext );


    public: // Getters for the data members
        /**
         * Returns assign flags, @see TAssignFlags.
         *
         * @return  Assign flags.
         */
        inline TUint Flags() const;

        /**
         * Returns editor help context.
         *
         * @return  Help context.
         */
        inline TCoeHelpContext EditorHelpContext() const;

    private: // Data
        /// Own: Assign flags.
        TUint iFlags;
        /// Own: Editor's help context.
        TCoeHelpContext iEditorHelpContext;
    };

/**
 * Version 1 of the multiple contact assign data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      assignData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwMultipleContactAssignDataV1 : public TAiwContactAssignDataBase
    {
    public: // Data type
        static const TAiwContactAssignDataType
            KAssignDataType = EAiwMultipleContactAssignV1;

    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwMultipleContactAssignDataV1();

    public: // Setters for the data members
        /**
         * Sets assign flags, @see TAssignFlags.
         *
         * @param aFlags The flags to set.
         * @return  Reference to this object.
         */
        inline TAiwMultipleContactAssignDataV1& SetFlags(
                TUint aFlags );

    public: // Getters for the data members
        /**
         * Returns assign flags, @see TAssignFlags.
         *
         * @return  Assign flags.
         */
        inline TUint Flags() const;

    private: // Data
        /// Own: Assign flags.
        TUint iFlags;
    };

/**
 * Version 1 of the contact attribute assign data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      assignData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwContactAttributeAssignDataV1 : public TAiwContactAssignDataBase
    {
    public: // Data type
        static const TAiwContactAssignDataType
            KAssignDataType = EAiwContactAttributeAssignV1;

    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwContactAttributeAssignDataV1();

    public: // Setters for the data members
        /**
         * Sets assign flags, @see TAssignFlags.
         *
         * @param aFlags The flags to set.
         * @return  Reference to this object.
         */
        inline TAiwContactAttributeAssignDataV1& SetFlags(
                TUint aFlags );

        /**
         * Sets attribute remove information.
         *
         * @param aRemove   ETrue indicates the attribute should be
         *                  removed from the contact. Usage of this
         *                  value requires also sending the link to
         *                  the contact to modify as
         *                  EGenericParamContactLinkArray parameter.
         *                  EFalse (default) indicates the attribute
         *                  should be assigned to the contact.
         * @return  Reference to this object.
         */
        inline TAiwContactAttributeAssignDataV1& SetAttributeRemove(
                TBool aRemove );

    public: // Getters for the data members
        /**
         * Returns assign flags, @see TAssignFlags.
         *
         * @return  Assign flags.
         */
        inline TUint Flags() const;

        /**
         * Returns remove attribute indicator.
         *
         * @return  Remove attribute indicator.
         */
        inline TBool RemoveAttribute() const;


    private: // Data
        /// Own: Assign flags.
        TUint iFlags;
        /// Own: Attribute removal indicator
        TBool iRemoveAttribute;
    };


typedef TPckgBuf<TAiwContactAssignDataBase> TAiwContactAssignDataBasePckg;
typedef TPckgBuf<TAiwSingleContactAssignDataV1> TAiwSingleContactAssignDataV1Pckg;
typedef TPckgBuf<TAiwMultipleContactAssignDataV1> TAiwMultipleContactAssignDataV1Pckg;
typedef TPckgBuf<TAiwContactAttributeAssignDataV1> TAiwContactAttributeAssignDataV1Pckg;

#include <AiwContactAssignDataTypes.inl>

} /// namespace

#endif // __AiwContactAssignDataTypes_H__

// End of File
