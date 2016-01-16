#ifndef SOLAIRE_ENCODER_HPP
#define SOLAIRE_ENCODER_HPP

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
	\file Encoder.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\version 1.0
	\date
	Created			: 16th January 2016
	Last Modified	: 16th January 2016
*/

#include "Solaire/Data/ArrayList.hpp"
#include "Solaire/Encode/GenericValue.hpp"

namespace Solaire {

	template<class T, typename ENABLE = void>
	struct Encoder {
	    typedef T DecodeType;

	    static DecodeType decode(Allocator&, const GenericValue&) throw();
	    static GenericValue encode(Allocator&, const T&) throw();
	};

	template<class T>
	static typename Encoder<T>::DecodeType decode(Allocator& aAllocator, const GenericValue& aValue) {
	    return Encoder<T>::decode(aAllocator, aValue);
	}

	template<class T>
	static GenericValue decode(Allocator& aAllocator, const T& aValue) {
	    return Encoder<T>::encode(aAllocator, aValue);
	}

	////

    template<>
	struct Encoder<char>{
	    typedef char DecodeType;

	    static DecodeType decode(Allocator& aAllocator, const GenericValue& aValue) throw() {
            return aValue.getChar();
	    }

	    static GenericValue encode(Allocator& aAllocator, const char aValue) throw() {
            return GenericValue(aValue);
	    }
	};

    template<>
	struct Encoder<bool>{
	    typedef bool DecodeType;

	    static DecodeType decode(Allocator& aAllocator, const GenericValue& aValue) throw() {
            return aValue.getBool();
	    }

	    static GenericValue encode(Allocator& aAllocator, const bool aValue) throw() {
            return GenericValue(aValue);
	    }
	};

    template<class T>
	struct Encoder<T, typename std::enable_if<
        std::is_same<T, uint8_t>::value ||
        std::is_same<T, uint16_t>::value ||
        std::is_same<T, uint32_t>::value ||
        std::is_same<T, uint64_t>::value
    >::type>{
	    typedef T DecodeType;

	    static DecodeType decode(Allocator& aAllocator, const GenericValue& aValue) throw() {
            return static_cast<T>(aValue.getUnsigned());
	    }

	    static GenericValue encode(Allocator& aAllocator, const T aValue) throw() {
            return GenericValue(static_cast<uint64_t>(aValue));
	    }
	};

    template<class T>
	struct Encoder<T, typename std::enable_if<
        std::is_same<T, int8_t>::value ||
        std::is_same<T, int16_t>::value ||
        std::is_same<T, int32_t>::value ||
        std::is_same<T, int64_t>::value
    >::type>{
	    typedef T DecodeType;

	    static DecodeType decode(Allocator& aAllocator, const GenericValue& aValue) throw() {
            return static_cast<T>(aValue.getSigned());
	    }

	    static GenericValue encode(Allocator& aAllocator, const T aValue) throw() {
            return GenericValue(static_cast<int64_t>(aValue));
	    }
	};

    template<class T>
	struct Encoder<T, typename std::enable_if<
        std::is_same<T, float>::value ||
        std::is_same<T, double>::value
    >::type>{
	    typedef T DecodeType;

	    static DecodeType decode(Allocator& aAllocator, const GenericValue& aValue) throw() {
            return static_cast<T>(aValue.getDouble());
	    }

	    static GenericValue encode(Allocator& aAllocator, const T aValue) throw() {
            return GenericValue(static_cast<double>(aValue));
	    }
	};

    template<>
	struct Encoder<String<char>>{
	    typedef CString DecodeType;

	    static DecodeType decode(Allocator& aAllocator, const GenericValue& aValue) throw() {
            return CString(aValue.getString());
	    }

	    static GenericValue encode(Allocator& aAllocator, const StringConstant<char>& aValue) throw() {
            GenericValue value;
            //! \todo Assign string
            //value.setString() = aValue;
            return value;
	    }
	};

	////

	template<class T>
	struct Encoder<StaticContainer<T>>{
	    typedef ArrayList<T> DecodeType;

	    static DecodeType decode(Allocator& aAllocator, const GenericValue& aValue) throw() {
            ArrayList<T> container(aAllocator);
            if(aValue.isArray()){
                const GenericArray& array_ = aValue.getArray();
                const int32_t size = array_.size();
                for(int32_t i = 0; i < size; ++i) {
                    container.pushBack(Encoder<T>::decode(aAllocator, array_[i]));
                }
            }
            return container;
	    }

	    static GenericValue encode(Allocator& aAllocator, const StaticContainer<T>& aContainer) throw() {
            GenericValue value;
            const GenericArray& array_ = value.setArray();
            const int32_t size = aContainer.size();
            for(int32_t i = 0; i < size; ++i) {
                array_.pushBack(Encoder<T>::encode(aAllocator, aContainer[i]));
            }
            return value;
	    }
	};
}

#endif
