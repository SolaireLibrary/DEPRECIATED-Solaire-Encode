#ifndef SOLAIRE_GENERIC_VALUE_HPP
#define SOLAIRE_GENERIC_VALUE_HPP

//Copyright 2015 Adam Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

// Contact :
// Email             : solairelibrary@mail.com
// GitHub repository : https://github.com/SolaireLibrary/SolaireCPP

/*!
	\file GenericValue.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\version 1.0
	\date
	Created			: 15th January 2016
	Last Modified	: 16th January 2016
*/

#include <cstdint>
#include "Solaire/Data/CString.hpp"
#include "Solaire/Data/ListMap.hpp"

namespace Solaire {

	class GenericValue {
    public:
        typedef List<GenericValue> GenericArray;
        typedef Map<CString, GenericValue> GenericObject;

	    enum ValueType : uint8_t {
	        NULL_T,
	        CHAR_T,
	        BOOL_T,
	        SIGNED_T,
	        UNSIGNED_T,
	        DOUBLE_T,
	        STRING_T,
	        ARRAY_T,
	        OBJECT_T
	    };
    private:
        typedef ArrayList<GenericValue> ArrayType;
        typedef ListMap<CString, GenericValue> ObjectType;
    private:
	    union {
	        char mChar;
	        bool mBool;
            uint64_t mUnsigned;
            int64_t mSigned;
            double mDouble;
	        String<char>* mString;
	        ArrayType* mArray;
	        ObjectType* mObject;
	    };
	    Allocator* mAllocator;
	    ValueType mType;
    public:
        GenericValue() throw() :
            mType(NULL_T)
        {}

        GenericValue(const GenericValue& aOther) throw() :
            mAllocator(aOther.mAllocator),
            mType(aOther.mType)
        {
            switch(mType){
            case CHAR_T:
            case BOOL_T:
                mChar = aOther.mChar;
                break;
            case UNSIGNED_T:
            case SIGNED_T:
                mUnsigned = aOther.mUnsigned;
                break;
            case DOUBLE_T:
                mDouble = aOther.mDouble;
                break;
            case STRING_T:
                mString = new(mAllocator->allocate(sizeof(CString))) CString(*aOther.mString);
                break;
            case ARRAY_T:
                mArray = new(mAllocator->allocate(sizeof(ArrayType))) ArrayType(*aOther.mArray);
                break;
            case OBJECT_T:
                mObject = new(mAllocator->allocate(sizeof(ObjectType))) ObjectType(*aOther.mObject);
                break;
            default:
                break;
            }
        }

        GenericValue(GenericValue&& aOther) throw() :
            mAllocator(aOther.mAllocator),
            mType(aOther.mType)
        {
            switch(mType){
            case CHAR_T:
            case BOOL_T:
                mChar = aOther.mChar;
                break;
            case UNSIGNED_T:
            case SIGNED_T:
                mUnsigned = aOther.mUnsigned;
                break;
            case DOUBLE_T:
                mDouble = aOther.mDouble;
                break;
            case STRING_T:
            case ARRAY_T:
            case OBJECT_T:
                mString = aOther.mString;
                break;
            default:
                break;
            }

            aOther.mType = NULL_T;
        }

        GenericValue(const char aValue)throw() :
            mChar(aValue),
            mAllocator(&DEFAULT_ALLOCATOR),
            mType(CHAR_T)
        {}

        GenericValue(const bool aValue) throw() :
            mBool(aValue),
            mAllocator(&DEFAULT_ALLOCATOR),
            mType(BOOL_T)
        {}

        GenericValue(const uint64_t aValue) throw() :
            mUnsigned(aValue),
            mAllocator(&DEFAULT_ALLOCATOR),
            mType(UNSIGNED_T)
        {}

        GenericValue(const int64_t aValue) throw() :
            mSigned(aValue),
            mAllocator(&DEFAULT_ALLOCATOR),
            mType(SIGNED_T)
        {}

        GenericValue(const double aValue) throw() :
            mDouble(aValue),
            mAllocator(&DEFAULT_ALLOCATOR),
            mType(DOUBLE_T)
        {}

        // C++ operators

        GenericValue& operator=(const GenericValue& aOther) throw() {
            setNull();
            mType = aOther.mType;
            mAllocator = aOther.mAllocator;
            switch(mType){
            case CHAR_T:
            case BOOL_T:
                mChar = aOther.mChar;
                break;
            case UNSIGNED_T:
            case SIGNED_T:
                mUnsigned = aOther.mUnsigned;
                break;
            case DOUBLE_T:
                mDouble = aOther.mDouble;
                break;
            case STRING_T:
                mString = new(mAllocator->allocate(sizeof(CString))) CString(*aOther.mString);
                break;
            case ARRAY_T:
                mArray = new(mAllocator->allocate(sizeof(ArrayType))) ArrayType(*aOther.mArray);
                break;
            case OBJECT_T:
                mObject = new(mAllocator->allocate(sizeof(ObjectType))) ObjectType(*aOther.mObject);
                break;
            default:
                break;
            }
            return *this;
        }
        GenericValue& operator=(GenericValue&& aOther) throw() {
            setNull();
            mType = aOther.mType;
            mAllocator = aOther.mAllocator;
            switch(mType){
            case CHAR_T:
            case BOOL_T:
                mChar = aOther.mChar;
                break;
            case UNSIGNED_T:
            case SIGNED_T:
                mUnsigned = aOther.mUnsigned;
                break;
            case DOUBLE_T:
                mDouble = aOther.mDouble;
                break;
            case STRING_T:
            case ARRAY_T:
            case OBJECT_T:
                mString = aOther.mString;
                break;
            default:
                break;
            }
            aOther.mType = NULL_T;
            return *this;
        }

        // is

        bool isChar() const throw() {
            return mType == CHAR_T;
        }

        bool isBool() const throw() {
            return mType == BOOL_T;
        }

        bool isUnsigned() const throw() {
            return mType == UNSIGNED_T;
        }

        bool isSigned() const throw() {
            return mType == SIGNED_T;
        }

        bool isString() const throw() {
            return mType == STRING_T;
        }

        bool isArray() const throw() {
            return mType == ARRAY_T;
        }

        bool isObject() const throw() {
            return mType == OBJECT_T;
        }

        // get

        char getChar() const throw() {
            switch(mType){
            case CHAR_T:
                return mChar;
            case BOOL_T:
                return static_cast<char>(mBool);
            case UNSIGNED_T:
                return static_cast<char>(mUnsigned);
            case SIGNED_T:
                return static_cast<char>(mSigned);
            case DOUBLE_T:
                return static_cast<char>(mDouble);
            case STRING_T:
                return (*mString)[0];
            default:
                return 0;
            }
        }

        bool getBool() const throw() {
            switch(mType){
            case CHAR_T:
                return static_cast<bool>(mChar);
            case BOOL_T:
                return mBool;
            case UNSIGNED_T:
                return static_cast<bool>(mUnsigned);
            case SIGNED_T:
                return static_cast<bool>(mSigned);
            case DOUBLE_T:
                return static_cast<bool>(mDouble);
            case STRING_T:
                //! \todo Cast from string
            default:
                return false;
            }
        }

        uint64_t getUnsigned() const throw() {
            switch(mType){
            case CHAR_T:
                return static_cast<uint64_t>(mChar);
            case BOOL_T:
                return static_cast<uint64_t>(mBool);
            case UNSIGNED_T:
                return mUnsigned;
            case SIGNED_T:
                return static_cast<uint64_t>(mSigned);
            case DOUBLE_T:
                return static_cast<uint64_t>(mDouble);
            case STRING_T:
                //! \todo Cast from string
                return 0;
            default:
                return 0;
            }
        }

        int64_t getSigned() const throw() {
            switch(mType){
            case CHAR_T:
                return static_cast<int64_t>(mChar);
            case BOOL_T:
                return static_cast<int64_t>(mBool);
            case UNSIGNED_T:
                return static_cast<int64_t>(mUnsigned);
            case SIGNED_T:
                return mSigned;
            case DOUBLE_T:
                return static_cast<int64_t>(mDouble);
            case STRING_T:
                //! \todo Cast from string
                return 0;
            default:
                return 0;
            }
        }

        double getDouble() const throw() {
            switch(mType){
            case CHAR_T:
                return static_cast<double>(mChar);
            case BOOL_T:
                return static_cast<double>(mBool);
            case UNSIGNED_T:
                return static_cast<double>(mUnsigned);
            case SIGNED_T:
                return static_cast<double>(mSigned);
            case DOUBLE_T:
                return mDouble;
            case STRING_T:
                //! \todo Cast from string
                return 0.0;
            default:
                return 0.0;
            }
        }

        const String<char>& getString() const throw() {
            return *mString;
        }

        String<char>& getString() throw() {
            return *mString;
        }

        const GenericArray& getArray() const throw() {
            return *mArray;
        }

        GenericArray& getArray() throw() {
            return *mArray;
        }

        const GenericObject& getObject() const throw() {
            return *mObject;
        }

        GenericObject& getObject() throw() {
            return *mObject;
        }

        // set

        void setNull() throw() {
            switch(mType){
            case STRING_T:
                mString->~String();
                mAllocator->deallocate(mString);
                break;
            case ARRAY_T:
                mArray->~ArrayType();
                mAllocator->deallocate(mArray);
                break;
            case OBJECT_T:
                mObject->~ObjectType();
                mAllocator->deallocate(mObject);
                break;
            }
            mType = NULL_T;
        }

        char& setChar(const char aValue) throw() {
            setNull();
            mType = CHAR_T;
            return mChar = aValue;
        }

        bool& setChar(const bool aValue) throw() {
            setNull();
            mType = BOOL_T;
            return mBool = aValue;
        }

        uint64_t& setUnsigned(const uint64_t aValue) throw() {
            setNull();
            mType = UNSIGNED_T;
            return mUnsigned = aValue;
        }

        int64_t& setSigned(const int64_t aValue) throw() {
            setNull();
            mType = UNSIGNED_T;
            return mSigned = aValue;
        }

        double& setDouble(const double aValue) throw() {
            setNull();
            mType = DOUBLE_T;
            return mDouble = aValue;
        }

        String<char>& setString() throw() {
            if(mType != STRING_T) {
                setNull();
                mString = new(mAllocator->allocate(sizeof(CString))) CString(*mAllocator);
                mType = STRING_T;
            }else {
                mString->clear();
            }
            return *mString;
        }

        GenericArray& setArray() throw() {
            if(mType != ARRAY_T) {
                setNull();
                mArray = new(mAllocator->allocate(sizeof(ArrayType))) ArrayType(*mAllocator);
                mType = ARRAY_T;
            }else {
                mArray->clear();
            }
            return *mArray;
        }

        GenericObject& setObject() throw() {
            if(mType != OBJECT_T) {
                setNull();
                mObject = new(mAllocator->allocate(sizeof(ObjectType))) ObjectType(*mAllocator);
                mType = OBJECT_T;
            }else {
                mObject->clear();
            }
            return *mObject;
        }
	};


    typedef GenericValue::GenericArray GenericArray;
    typedef GenericValue::GenericObject GenericObject;
}

#endif
