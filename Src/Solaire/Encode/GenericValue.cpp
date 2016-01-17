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

#include "Solaire/Encode/GenericValue.hpp"

namespace Solaire {

    typedef ArrayList<GenericValue> ArrayType;
    typedef ListMap<CString, GenericValue> ObjectType;

	// GenericValue

    GenericValue::GenericValue() throw() :
        mType(NULL_T)
    {}

    GenericValue::GenericValue(const GenericValue& aOther) throw() :
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

    GenericValue::GenericValue(GenericValue&& aOther) throw() :
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

    GenericValue::GenericValue(const char aValue)throw() :
        mChar(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(CHAR_T)
    {}

    GenericValue::GenericValue(const bool aValue) throw() :
        mBool(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(BOOL_T)
    {}

    GenericValue::GenericValue(const uint8_t aValue) throw() :
        mUnsigned(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(UNSIGNED_T)
    {}

    GenericValue::GenericValue(const uint16_t aValue) throw() :
        mUnsigned(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(UNSIGNED_T)
    {}

    GenericValue::GenericValue(const uint32_t aValue) throw() :
        mUnsigned(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(UNSIGNED_T)
    {}

    GenericValue::GenericValue(const uint64_t aValue) throw() :
        mUnsigned(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(UNSIGNED_T)
    {}

    GenericValue::GenericValue(const int8_t aValue) throw() :
        mSigned(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(SIGNED_T)
    {}

    GenericValue::GenericValue(const int16_t aValue) throw() :
        mSigned(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(SIGNED_T)
    {}

    GenericValue::GenericValue(const int32_t aValue) throw() :
        mSigned(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(SIGNED_T)
    {}

    GenericValue::GenericValue(const int64_t aValue) throw() :
        mSigned(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(SIGNED_T)
    {}

    GenericValue::GenericValue(const double aValue) throw() :
        mDouble(aValue),
        mAllocator(&DEFAULT_ALLOCATOR),
        mType(DOUBLE_T)
    {}

        // C++ operators

    GenericValue& GenericValue::operator=(const GenericValue& aOther) throw() {
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

    GenericValue& GenericValue::operator=(GenericValue&& aOther) throw() {
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

    GenericValue::ValueType GenericValue::getType() const throw() {
        return mType;
    }

    bool GenericValue::isNull() const throw() {
        return mType == NULL_T;
    }

    bool GenericValue::isChar() const throw() {
        return mType == CHAR_T;
    }

    bool GenericValue::isBool() const throw() {
        return mType == BOOL_T;
    }

    bool GenericValue::isUnsigned() const throw() {
        return mType == UNSIGNED_T;
    }

    bool GenericValue::isSigned() const throw() {
        return mType == SIGNED_T;
    }

    bool GenericValue::isDouble() const throw() {
        return mType == SIGNED_T;
    }

    bool GenericValue::isString() const throw() {
        return mType == STRING_T;
    }

    bool GenericValue::isArray() const throw() {
        return mType == ARRAY_T;
    }

    bool GenericValue::isObject() const throw() {
        return mType == OBJECT_T;
    }

    char GenericValue::getChar() const throw() {
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

    bool GenericValue::getBool() const throw() {
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

    uint64_t GenericValue::getUnsigned() const throw() {
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
            return static_cast<uint64_t>(*mString);
        default:
            return 0;
        }
    }

    int64_t GenericValue::getSigned() const throw() {
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
            return static_cast<int64_t>(*mString);
        default:
            return 0;
        }
    }

    double GenericValue::getDouble() const throw() {
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
            return static_cast<int64_t>(*mString);
        default:
            return 0.0;
        }
    }

    const String<char>& GenericValue::getString() const throw() {
        return *mString;
    }

    String<char>& GenericValue::getString() throw() {
        return *mString;
    }

    const GenericArray& GenericValue::getArray() const throw() {
        return *mArray;
    }

    GenericArray& GenericValue::getArray() throw() {
        return *mArray;
    }

    const GenericObject& GenericValue::getObject() const throw() {
        return *mObject;
    }

    GenericObject& GenericValue::getObject() throw() {
        return *mObject;
    }

    void GenericValue::setNull() throw() {
        switch(mType){
        case STRING_T:
            mString->~String();
            mAllocator->deallocate(mString);
            break;
        case ARRAY_T:
            mArray->~GenericArray();
            mAllocator->deallocate(mArray);
            break;
        case OBJECT_T:
            mObject->~GenericObject();
            mAllocator->deallocate(mObject);
            break;
        }
        mType = NULL_T;
    }

    char& GenericValue::setChar(const char aValue) throw() {
        setNull();
        mType = CHAR_T;
        return mChar = aValue;
    }

    bool& GenericValue::setChar(const bool aValue) throw() {
        setNull();
        mType = BOOL_T;
        return mBool = aValue;
    }

    uint64_t& GenericValue::setUnsigned(const uint64_t aValue) throw() {
        setNull();
        mType = UNSIGNED_T;
        return mUnsigned = aValue;
    }

    int64_t& GenericValue::setSigned(const int64_t aValue) throw() {
        setNull();
        mType = UNSIGNED_T;
        return mSigned = aValue;
    }

    double& GenericValue::setDouble(const double aValue) throw() {
        setNull();
        mType = DOUBLE_T;
        return mDouble = aValue;
    }

    String<char>& GenericValue::setString() throw() {
        if(mType != STRING_T) {
            setNull();
            mString = new(mAllocator->allocate(sizeof(CString))) CString(*mAllocator);
            mType = STRING_T;
        }else {
            mString->clear();
        }
        return *mString;
    }

    GenericArray& GenericValue::setArray() throw() {
        if(mType != ARRAY_T) {
            setNull();
            mArray = new(mAllocator->allocate(sizeof(ArrayType))) ArrayType(*mAllocator);
            mType = ARRAY_T;
        }else {
            mArray->clear();
        }
        return *mArray;
    }

    GenericObject& GenericValue::setObject() throw() {
        if(mType != OBJECT_T) {
            setNull();
            mObject = new(mAllocator->allocate(sizeof(ObjectType))) ObjectType(*mAllocator);
            mType = OBJECT_T;
        }else {
            mObject->clear();
        }
        return *mObject;
    }
}
