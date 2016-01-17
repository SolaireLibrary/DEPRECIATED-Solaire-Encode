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
	    union {
	        char mChar;
	        bool mBool;
            uint64_t mUnsigned;
            int64_t mSigned;
            double mDouble;
	        CString* mString;
	        GenericArray* mArray;
	        GenericObject* mObject;
	    };
	    Allocator* mAllocator;
	    ValueType mType;
    public:
        GenericValue() throw();
        GenericValue(const GenericValue& aOther) throw();
        GenericValue(GenericValue&& aOther) throw();
        GenericValue(const char aValue)throw();
        GenericValue(const bool aValue) throw();
        GenericValue(const uint8_t aValue) throw();
        GenericValue(const uint16_t aValue) throw();
        GenericValue(const uint32_t aValue) throw();
        GenericValue(const uint64_t aValue) throw();
        GenericValue(const int8_t aValue) throw();
        GenericValue(const int16_t aValue) throw();
        GenericValue(const int32_t aValue) throw();
        GenericValue(const int64_t aValue) throw();
        GenericValue(const double aValue) throw();

        GenericValue& operator=(const GenericValue& aOther) throw();
        GenericValue& operator=(GenericValue&& aOther) throw();

        ValueType getType() const throw();

        bool isNull() const throw();
        bool isChar() const throw();
        bool isBool() const throw();
        bool isUnsigned() const throw();
        bool isSigned() const throw();
        bool isDouble() const throw();
        bool isString() const throw();
        bool isArray() const throw();
        bool isObject() const throw();

        char getChar() const throw();
        bool getBool() const throw();
        uint64_t getUnsigned() const throw();
        int64_t getSigned() const throw();
        double getDouble() const throw();
        const String<char>& getString() const throw();
        String<char>& getString() throw();
        const GenericArray& getArray() const throw();
        GenericArray& getArray() throw();
        const GenericObject& getObject() const throw();
        GenericObject& getObject() throw();

        void setNull() throw();
        char& setChar(const char aValue) throw();
        bool& setChar(const bool aValue) throw();
        uint64_t& setUnsigned(const uint64_t aValue) throw();
        int64_t& setSigned(const int64_t aValue) throw();
        double& setDouble(const double aValue) throw();
        String<char>& setString() throw();
        GenericArray& setArray() throw();
        GenericObject& setObject() throw();

        SOLAIRE_FORCE_INLINE explicit operator char() const throw()                  {return getChar();}
        SOLAIRE_FORCE_INLINE explicit operator bool() const throw()                  {return getBool();}
        SOLAIRE_FORCE_INLINE explicit operator int8_t() const throw()                {return static_cast<int8_t>(getSigned());}
        SOLAIRE_FORCE_INLINE explicit operator int16_t() const throw()               {return static_cast<int16_t>(getSigned());}
        SOLAIRE_FORCE_INLINE explicit operator int32_t() const throw()               {return static_cast<int32_t>(getSigned());}
        SOLAIRE_FORCE_INLINE explicit operator int64_t() const throw()               {return getSigned();}
        SOLAIRE_FORCE_INLINE explicit operator uint8_t() const throw()               {return static_cast<uint8_t>(getUnsigned());}
        SOLAIRE_FORCE_INLINE explicit operator uint16_t() const throw()              {return static_cast<uint16_t>(getUnsigned());}
        SOLAIRE_FORCE_INLINE explicit operator uint32_t() const throw()              {return static_cast<uint32_t>(getUnsigned());}
        SOLAIRE_FORCE_INLINE explicit operator uint64_t() const throw()              {return getUnsigned();}
        SOLAIRE_FORCE_INLINE explicit operator float() const throw()                 {return static_cast<float>(getDouble());}
        SOLAIRE_FORCE_INLINE explicit operator double() const throw()                {return getDouble();}
        SOLAIRE_FORCE_INLINE explicit operator String<char>&() throw()               {return getString();}
        SOLAIRE_FORCE_INLINE explicit operator const String<char>&() const throw()   {return getString();}
        SOLAIRE_FORCE_INLINE explicit operator GenericArray&() throw()               {return getArray();}
        SOLAIRE_FORCE_INLINE explicit operator const GenericArray&() const throw()   {return getArray();}
        SOLAIRE_FORCE_INLINE explicit operator GenericObject&() throw()              {return getObject();}
        SOLAIRE_FORCE_INLINE explicit operator const GenericObject&() const throw()  {return getObject();}

        SOLAIRE_FORCE_INLINE GenericValue& operator[](const int32_t aIndex) throw()                           {return (*mArray)[aIndex];}
        SOLAIRE_FORCE_INLINE const GenericValue& operator[](const int32_t aIndex) const throw()               {return (*mArray)[aIndex];}
        SOLAIRE_FORCE_INLINE GenericValue& operator[](const StringConstant<char>& aName) throw()              {return (*mObject)[aName];}
        SOLAIRE_FORCE_INLINE const GenericValue& operator[](const StringConstant<char>& aName) const throw()  {return (*mObject)[aName];}
	};

    typedef GenericValue::GenericArray GenericArray;
    typedef GenericValue::GenericObject GenericObject;
}

#endif
