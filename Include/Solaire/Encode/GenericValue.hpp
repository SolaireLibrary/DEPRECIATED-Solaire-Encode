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
        GenericValue(const uint64_t aValue) throw();
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
	};

    typedef GenericValue::GenericArray GenericArray;
    typedef GenericValue::GenericObject GenericObject;
}

#endif
