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
* Description:     Defines types used in AIW contact selection.
*
*/





#ifndef __AIWCONTACTSELECTIONDATATYPES_H__
#define __AIWCONTACTSELECTIONDATATYPES_H__

#include <aiwgenericparam.hrh>

class RVPbkContactFieldDefaultPriorities;
class CVPbkFieldTypeSelector;

/**
 * Type of the contact selection.
 */
enum TAiwContactSelectionDataType
    {
    EAiwContactSelectionDataTypeNotDefined,
    EAiwSingleEntrySelectionV1,
    EAiwMultipleEntrySelectionV1,
    EAiwSingleItemSelectionV1,
    EAiwSingleItemSelectionV2,
    EAiwSingleEntrySelectionV2,
    EAiwMultipleEntrySelectionV2,
    EAiwSingleItemSelectionV3,
    EAiwMultipleItemSelectionV1
    };

/**
 * Type of the address select.
 */
enum TAiwAddressSelectType
    {
    EAiwAllItemsSelect,
    EAiwPhoneNumberSelect,
    EAiwVideoNumberSelect,
    EAiwPOCNumberSelect,
    EAiwEMailSelect,
    EAiwMMSSelect,
    EAiwSMSEMailSelect,
    EAiwVOIPSelect,
    EAiwSIPSelect,
    EAiwSIPMSISDNSelect,
    EAiwThumbnailSelect,
    EAiwDTMFPhoneNumberSelect,  // includes DTMF and phone number field types
    EAiwCallItemSelect,         // like phone number select but uses 'Call' as LSK
    EAiwVoIPItemSelect          // like voip address select but uses 'Call' as LSK
    };

/**
 * Type of the communication address select.
 */
enum TAiwCommAddressSelectType
    {
    EAiwCommEmpty,
    EAiwCommVoiceCall,
    EAiwCommUniEditor,
    EAiwCommEmailEditor,
    EAiwCommInstantMessaging,
    EAiwCommVOIPCall,
    EAiwCommURL,
    EAiwCommVideoCall
    };

/**
 * Parameter flags for selection service.
 */
enum TSelectionFlags
    { 
    /**
     * Excludes group view from the fetch dialog, has no meaning elsewhere
     * than in multiple entry fetch context.
     */
    EExcludeGroupsView  = 0x0001,
    /**
     * If set the fetch dialog will use default provider title
     * ("Contacts", for example), otherwise client's current title is used.
     */
    EUseProviderTitle   = 0x0002,
    
    /**
     * If set the fetch dialog will NOT use default field even if it exists
     * for communication method, i.e. fetch dialog will be always shown if
     * there are 2 or more items to show.
     */
    EDoNotUseDefaultField   = 0x0004,

    /**
     * If set the fetch view will use custom filtering. When building the
     * view the client is asked with KAiwEventInParamCheck, for every contact,
     * does the contact belong to the view. This is rather slow.
     */
    EUseClientSideFiltering = 0x0008
    };

/**
 * Base class for different versions of the contact selection data.
 */
class TAiwContactSelectionDataBase
    {
    public: // Type checking
        /**
         * Function for checking the type of the contact selection
         * data in a data buffer.
         *
         * @param aBuffer A buffer containing an instance of a contact 
         *                selection data class derived from this class.
         * @return  Type of the data class that is in the buffer.
         */
        inline static TAiwContactSelectionDataType SelectionDataTypeFromBuffer(
                    const TDesC8& aBuffer );
                
        /**
         * Public constructor.
         */
        explicit inline TAiwContactSelectionDataBase();

    protected: // Constructor
        /**
         * Constructor that sets the type of the data class.
         *
         * @param aSelectionDataType    Type of the contact selection data.
         */
        inline TAiwContactSelectionDataBase(
                TAiwContactSelectionDataType aSelectionDataType );
        
    private: // Implementation 
        /**
         * Returns the type of the contact selection data class.
         *
         * @return  The type of the contact selection data class.
         */
        inline TAiwContactSelectionDataType SelectionDataType() const;
        
    private: // Data
        /// Own: Type of the contact selection data class.
        TAiwContactSelectionDataType iSelectionDataType;
    };

/**
 * Version 1 of the single entry selection data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      selectionData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwSingleEntrySelectionDataV1 : public TAiwContactSelectionDataBase
    {
    public: // Data type
        static const TAiwContactSelectionDataType
                KSelectionDataType = EAiwSingleEntrySelectionV1;
        
    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwSingleEntrySelectionDataV1();

    public: // Setters for the data members
        /**
         * Sets selection flags, @see TSelectionFlags.
         *
         * @param aFlags    The flags to set.
         * @return  Reference to this object.
         */
        inline TAiwSingleEntrySelectionDataV1& SetFlags(
                TUint aFlags );

    public: // Getters for the data members
        /**
         * Returns selection flags, @see TSelectionFlags.
         *
         * @return  Selection flags.
         */
        inline TUint Flags() const;

    private: // Data
        /// Own: Selection flags.
        TUint iFlags;
    };

/**
 * Version 2 of the single entry selection data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      selectionData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwSingleEntrySelectionDataV2 : public TAiwContactSelectionDataBase
    {
    public: // Data type
        static const TAiwContactSelectionDataType
                KSelectionDataType = EAiwSingleEntrySelectionV2;
        
    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwSingleEntrySelectionDataV2();

    public: // Setters for the data members
        /**
         * Sets selection flags, @see TSelectionFlags.
         *
         * @param aFlags The flags to set.
         * @return Reference to this object.
         */
        inline TAiwSingleEntrySelectionDataV2& SetFlags(
                TUint aFlags );

        /**
         * Sets field type filter for fetch. Only contacts having the
         * fields defined by the filter will be visible in the fetch view.
         * Use of NULL filter means nothing is filtered.
         * @see CVPbkFieldTypeSelector
         * @see VPbkContactViewFilterBuilder::BuildContactViewFilterL
         *
         * @param aFlags    The filter to set.
         * @return Reference to this object.
         */
        inline TAiwSingleEntrySelectionDataV2& SetFetchFilter(
                CVPbkFieldTypeSelector* aFilter );

    public: // Getters for the data members
        /**
         * Returns selection flags, @see TSelectionFlags.
         *
         * @return  Selection flags.
         */
        inline TUint Flags() const;

        /**
         * Returns field type filter used in fetch.
         *
         * @return  Field type filter.
         */
        inline CVPbkFieldTypeSelector* FetchFilter() const;

    private: // Data
        /// Own: Selection flags.
        TUint iFlags;
        /// Ref: Field type filter.
        CVPbkFieldTypeSelector* iFetchFilter;
    };
    
/**
 * Version 1 of the multiple entry selection data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      selectionData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwMultipleEntrySelectionDataV1 : public TAiwContactSelectionDataBase
    {
    public: // Data type
        static const TAiwContactSelectionDataType
                KSelectionDataType = EAiwMultipleEntrySelectionV1;
        
    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwMultipleEntrySelectionDataV1();

    public: // Setters for the data members
        /**
         * Sets selection flags, @see TSelectionFlags.
         *
         * @param aFlags The flags to set.
         * @return  Reference to this object.
         */
        inline TAiwMultipleEntrySelectionDataV1& SetFlags(
                TUint aFlags );

    public: // Getters for the data members
        /**
         * Returns selection flags, @see TSelectionFlags.
         *
         * @return Selection flags.
         */
        inline TUint Flags() const;

    private: // Data
        /// Own: Selection flags.
        TUint iFlags;
    };

/**
 * Version 2 of the multiple entry selection data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      selectionData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwMultipleEntrySelectionDataV2 : public TAiwContactSelectionDataBase
    {
    public: // Data type
        static const TAiwContactSelectionDataType
                KSelectionDataType = EAiwMultipleEntrySelectionV2;
        
    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwMultipleEntrySelectionDataV2();

    public: // Setters for the data members
        /**
         * Sets selection flags, @see TSelectionFlags.
         *
         * @param aFlags The flags to set.
         * @return  Reference to this object.
         */
        inline TAiwMultipleEntrySelectionDataV2& SetFlags(
                TUint aFlags );

        /**
         * Sets field type filter for fetch. Only contacts having the fields
         * defined by the filter will be visible in the fetch view.
         * Use of NULL filter means nothing is filtered.
         * @see CVPbkFieldTypeSelector
         * @see VPbkContactViewFilterBuilder::BuildContactViewFilterL
         *
         * @param aFlags    The filter to set.
         * @return Reference to this object.
         */
        inline TAiwMultipleEntrySelectionDataV2& SetFetchFilter(
                CVPbkFieldTypeSelector* aFilter );

    public: // Getters for the data members
        /**
         * Returns selection flags, @see TSelectionFlags.
         *
         * @return Selection flags.
         */
        inline TUint Flags() const;

        /**
         * Returns field type filter used in fetch.
         *
         * @return  Field type filter.
         */
        inline CVPbkFieldTypeSelector* FetchFilter() const;

    private: // Data
        /// Own: Selection flags.
        TUint iFlags;
        /// Ref: Field type filter.
        CVPbkFieldTypeSelector* iFetchFilter;
    };

/**
 * Version 1 of the single item selection data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      selectionData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwSingleItemSelectionDataV1 : public TAiwContactSelectionDataBase
    {
    public: // Data type
        static const TAiwContactSelectionDataType
                KSelectionDataType = EAiwSingleItemSelectionV1;
        
    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwSingleItemSelectionDataV1();
        
    public: // Setters for the data members
        /**
         * Sets selection flags, @see TSelectionFlags.
         *
         * @param aFlags The flags to set.
         * @return Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV1& SetFlags(
                TUint aFlags );

        /**
         * Sets address select type.
         *
         * @param aAddressSelectType Address select type,
         *                           @see TAiwAddressSelectType.
         * @return  Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV1& SetAddressSelectType(
                TAiwAddressSelectType aAddressSelectType );
                
        /**
         * Sets communication address select type.
         *
         * @param aCommAddressSelectType Communication address select type,
         *                           @see TAiwCommAddressSelectType.
         * @return  Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV1& SetCommAddressSelectType(
                TAiwCommAddressSelectType aCommAddressSelectType );

        /**
         * Sets address select default priorities.
         * The defaults to use should be placed in priority order in
         * to the array, the highest priority default should come first.
         * If no default priorities are set, defaults are not used in
         * address select.
         *
         * The caller can free the passed array right after HandleServiceCmdL
         * call, since the array is there externalized to a buffer.
         *
         * @param aDefaultPriorities Prioritized array of defaults to use,
         *                           @see RVPbkContactFieldDefaultPriorities.
         * @return  Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV1& SetDefaultPriorities(
                RVPbkContactFieldDefaultPriorities& aDefaultPriorities );
            
    public: // Getters for the data members
        /**
         * Returns selection flags, @see TSelectionFlags.
         *
         * @return  Selection flags.
         */
        inline TUint Flags() const;

        /**
         * Returns the type of the address select.
         *
         * @return  Type of the address select, @see TAiwAddressSelectType.
         */
        inline TAiwAddressSelectType AddressSelectType() const;

        /**
         * Returns the type of the communication address select.
         *
         * @return  Type of the communication address select,
         *          @see TAiwCommAddressSelectType.
         */
        inline TAiwCommAddressSelectType CommAddressSelectType() const;
        
        /**
         * Returns the address select default priorities
         *
         * @return  Prioritized array of defaults to use or NULL,
         *          @see RVPbkContactFieldDefaultPriorities.
         */
        inline RVPbkContactFieldDefaultPriorities* DefaultPriorities() const;
        
    private: // Data
        /// Own: Selection flags.
        TUint iFlags;
        /// Own: Address select type.
        TAiwAddressSelectType iAddressSelectType;
        
        /// Own: Communication address select type. If specified, used
        /// instead of iAddressSelectType.
        TAiwCommAddressSelectType iCommAddressSelectType;

        /// Ref: Prioritized array of defaults to use.
        RVPbkContactFieldDefaultPriorities* iDefaultPriorities;
        
        /// For future use. 
        TInt32 iReserved[4];
    };
    
/**
 * Version 2 of the single item selection data. Deprecated, do not use!!
 *
 * @deprecated
 */
class TAiwSingleItemSelectionDataV2 : public TAiwContactSelectionDataBase
    {
    public: // Data type
        static const TAiwContactSelectionDataType
                KSelectionDataType = EAiwSingleItemSelectionV2;
        
    public: // Construction
        /**
         * Constructor.
         *
         * @deprecated
         */
        explicit inline TAiwSingleItemSelectionDataV2();
        
    public: // Setters for the data members
        /**
         * Sets selection flags, @see TSelectionFlags.
         *
         * @param aFlags The flags to set.
         * @return  Reference to this object.
         * @deprecated
         */
        inline TAiwSingleItemSelectionDataV2& SetFlags(
                TUint aFlags );

        /**
         * Sets resource ID for the address select dialog.
         * @see PBK2_ADDRESS_SELECT resource struct.
         * 
         *
         * @param aAddressSelectResourceId  Address select resource id.
         * @return  Reference to this object.
         * @deprecated
         */
        inline TAiwSingleItemSelectionDataV2& SetAddressSelectResourceId(
                TInt aAddressSelectResourceId );

        /**
         * Sets address select default priorities.
         * The defaults to use should be placed in priority order in
         * to the array, the highest priority default should come first.
         * If no default priorities are set, defaults are not used in
         * address select.
         *
         * The caller can free the passed array right after HandleServiceCmdL
         * call, since the array is there externalized to a buffer.
         *
         * @param aDefaultPriorities Prioritized array of defaults to use,
         *                           @see RVPbkContactFieldDefaultPriorities.
         * @return  Reference to this object.
         * @deprecated
         */
        inline TAiwSingleItemSelectionDataV2& SetDefaultPriorities(
                RVPbkContactFieldDefaultPriorities& aDefaultPriorities );
            
            
    public: // Getters for the data members
        /**
         * Returns selection flags, @see TSelectionFlags.
         *
         * @return  Selection flags.
         * @deprecated
         */
        inline TUint Flags() const;

        /**
         * Returns the address select resource id.
         *
         * @return  Address select resource id.
         * @deprecated
         */
        inline TInt AddressSelectResourceId() const;
        
        /**
         * Returns the address select default priorities
         *
         * @return  Prioritized array of defaults to use or NULL,
         *          @see RVPbkContactFieldDefaultPriorities.
         * @deprecated
         */
        inline RVPbkContactFieldDefaultPriorities* DefaultPriorities() const;
        
    private: // Data
        /// Own: Selection flags.
        TUint iFlags;
        /// Own: Address select resource id.
        TInt iAddressSelectResourceId;
        /// Ref: Prioritized array of defaults to use.
        RVPbkContactFieldDefaultPriorities* iDefaultPriorities;
    };

/**
 * Version 3 of the single item selection data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      selectionData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwSingleItemSelectionDataV3 : public TAiwContactSelectionDataBase
    {
    public: // Data type
        static const TAiwContactSelectionDataType
                KSelectionDataType = EAiwSingleItemSelectionV3;
        
    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwSingleItemSelectionDataV3();
        
    public: // Setters for the data members
        /**
         * Sets selection flags, @see TSelectionFlags.
         *
         * @param aFlags The flags to set.
         * @return  Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV3& SetFlags(
                TUint aFlags );

        /**
         * Sets address select type.
         *
         * @param aAddressSelectType Address select type,
         *                           @see TAiwAddressSelectType.
         * @return  Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV3& SetAddressSelectType(
                TAiwAddressSelectType aAddressSelectType );

        /**
         * Sets communication address select type.
         *
         * @param aCommAddressSelectType Communication address select type,
         *                           @see TAiwCommAddressSelectType.
         * @return  Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV3& SetCommAddressSelectType(
                TAiwCommAddressSelectType aCommAddressSelectType );

        /**
         * Sets address select default priorities.
         * The defaults to use should be placed in priority order in
         * to the array, the highest priority default should come first.
         * If no default priorities are set, defaults are not used in
         * address select.
         *
         * The caller can free the passed array right after HandleServiceCmdL
         * call, since the array is there externalized to a buffer.
         *
         * @param aDefaultPriorities Prioritized array of defaults to use,
         *                           @see RVPbkContactFieldDefaultPriorities.
         * @return  Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV3& SetDefaultPriorities(
                RVPbkContactFieldDefaultPriorities& aDefaultPriorities );

        /**
         * Sets field type filter for fetch. Only contacts having the fields
         * defined by the filter will be visible in the fetch view.
         * Use of NULL filter means nothing is filtered.
         * @see CVPbkFieldTypeSelector
         * @see VPbkContactViewFilterBuilder::BuildContactViewFilterL
         *
         * @param aFlags    The filter to set.
         * @return Reference to this object.
         */
        inline TAiwSingleItemSelectionDataV3& SetFetchFilter(
                CVPbkFieldTypeSelector* aFilter );
            
    public: // Getters for the data members
        /**
         * Returns selection flags, @see TSelectionFlags.
         *
         * @return  Selection flags.
         */
        inline TUint Flags() const;

        /**
         * Returns the type of the address select.
         *
         * @return  Type of the address select, @see TAiwAddressSelectType.
         */
        inline TAiwAddressSelectType AddressSelectType() const;
        
        /**
         * Returns the type of the communication address select.
         *
         * @return  Type of the communication address select,
         *          @see TAiwCommAddressSelectType.
         */
        inline TAiwCommAddressSelectType CommAddressSelectType() const;
        
        /**
         * Returns the address select default priorities.
         *
         * @return  Prioritized array of defaults to use or NULL,
         *          @see RVPbkContactFieldDefaultPriorities.
         */
        inline RVPbkContactFieldDefaultPriorities* DefaultPriorities() const;

        /**
         * Returns field type filter used in fetch.
         *
         * @return  Field type filter.
         */
        inline CVPbkFieldTypeSelector* FetchFilter() const;
        
    private: // Data
        /// Own: Selection flags.
        TUint iFlags;
        /// Own: Address select type.
        TAiwAddressSelectType iAddressSelectType;
        /// Own: Communication address select type. If specified, used
        /// instead of iAddressSelectType.
        TAiwCommAddressSelectType iCommAddressSelectType;

        /// Ref: Prioritized array of defaults to use.
        RVPbkContactFieldDefaultPriorities* iDefaultPriorities;
        /// Ref: Field type filter.
        CVPbkFieldTypeSelector* iFetchFilter;
        
        /// For future use. 
        TInt32 iReserved[4];
    };
/**
 * Version 1 of the multiple item selection data.
 *
 * All setters return a reference to this object so that the setters
 * can be easily chained to produce more compact code, for example:
 *      selectionData.SetProperty(EAiwProperty)
 *                   .SetAnotherProperty(EAiwAnotherProperty)
 */
class TAiwMultipleItemSelectionDataV1 : public TAiwContactSelectionDataBase
    {
    public: // Data type
        static const TAiwContactSelectionDataType
                KSelectionDataType = EAiwMultipleItemSelectionV1;
        
    public: // Construction
        /**
         * Constructor.
         */
        explicit inline TAiwMultipleItemSelectionDataV1();
        
    public: // Setters for the data members
        /**
         * Sets selection flags, @see TSelectionFlags.
         *
         * @param aFlags The flags to set.
         * @return  Reference to this object.
         */
        inline TAiwMultipleItemSelectionDataV1& SetFlags(
                TUint aFlags );

        /**
         * Sets address select type.
         *
         * @param aAddressSelectType Address select type,
         *                           @see TAiwAddressSelectType.
         * @return  Reference to this object.
         */
        inline TAiwMultipleItemSelectionDataV1& SetAddressSelectType(
                TAiwAddressSelectType aAddressSelectType );

        /**
         * Sets address select default priorities.
         * The defaults to use should be placed in priority order in
         * to the array, the highest priority default should come first.
         * If no default priorities are set, defaults are not used in
         * address select.
         *
         * The caller can free the passed array right after HandleServiceCmdL
         * call, since the array is there externalized to a buffer.
         *
         * @param aDefaultPriorities Prioritized array of defaults to use,
         *                           @see RVPbkContactFieldDefaultPriorities.
         * @return  Reference to this object.
         */
        inline TAiwMultipleItemSelectionDataV1& SetDefaultPriorities(
                RVPbkContactFieldDefaultPriorities& aDefaultPriorities );

        /**
         * Sets field type filter for fetch. Only contacts having the fields
         * defined by the filter will be visible in the fetch view.
         * Use of NULL filter means nothing is filtered.
         * @see CVPbkFieldTypeSelector
         * @see VPbkContactViewFilterBuilder::BuildContactViewFilterL
         *
         * @param aFlags    The filter to set.
         * @return Reference to this object.
         */
        inline TAiwMultipleItemSelectionDataV1& SetFetchFilter(
                CVPbkFieldTypeSelector* aFilter );
            
    public: // Getters for the data members
        /**
         * Returns selection flags, @see TSelectionFlags.
         *
         * @return  Selection flags.
         */
        inline TUint Flags() const;

        /**
         * Returns the type of the address select.
         *
         * @return  Type of the address select, @see TAiwAddressSelectType.
         */
        inline TAiwAddressSelectType AddressSelectType() const;
        
        /**
         * Returns the address select default priorities.
         *
         * @return  Prioritized array of defaults to use or NULL,
         *          @see RVPbkContactFieldDefaultPriorities.
         */
        inline RVPbkContactFieldDefaultPriorities* DefaultPriorities() const;

        /**
         * Returns field type filter used in fetch.
         *
         * @return  Field type filter.
         */
        inline CVPbkFieldTypeSelector* FetchFilter() const;
        
    private: // Data
        /// Own: Selection flags.
        TUint iFlags;
        /// Own: Address select type.
        TAiwAddressSelectType iAddressSelectType;
        /// Ref: Prioritized array of defaults to use.
        RVPbkContactFieldDefaultPriorities* iDefaultPriorities;
        /// Ref: Field type filter.
        CVPbkFieldTypeSelector* iFetchFilter;

    };
    
typedef TPckgBuf<TAiwContactSelectionDataBase>      TAiwContactSelectionDataBasePckg;
typedef TPckgBuf<TAiwSingleEntrySelectionDataV1>    TAiwSingleEntrySelectionDataV1Pckg;
typedef TPckgBuf<TAiwSingleEntrySelectionDataV2>    TAiwSingleEntrySelectionDataV2Pckg;
typedef TPckgBuf<TAiwMultipleEntrySelectionDataV1>  TAiwMultipleEntrySelectionDataV1Pckg;
typedef TPckgBuf<TAiwMultipleEntrySelectionDataV2>  TAiwMultipleEntrySelectionDataV2Pckg;
typedef TPckgBuf<TAiwSingleItemSelectionDataV1>     TAiwSingleItemSelectionDataV1Pckg;
typedef TPckgBuf<TAiwSingleItemSelectionDataV2>     TAiwSingleItemSelectionDataV2Pckg;
typedef TPckgBuf<TAiwSingleItemSelectionDataV3>     TAiwSingleItemSelectionDataV3Pckg;
typedef TPckgBuf<TAiwMultipleItemSelectionDataV1>   TAiwMultipleItemSelectionDataV1Pckg;
    
#include <aiwcontactselectiondatatypes.inl>

#endif // __AiwContactSelectionDataTypes_H__

// End of File
