#ifndef SOLAIRE_FORMAT_HPP
#define SOLAIRE_FORMAT_HPP

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
	\file Format.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\version 1.0
	\date
	Created			: 16th January 2016
	Last Modified	: 16th January 2016
*/

#include "Solaire/Core/IStream.hpp"
#include "Solaire/Core/OStream.hpp"
#include "Solaire/Encode/GenericValue.hpp"
#include "Solaire/Encode/Encoder.hpp"

namespace Solaire {

	SOLAIRE_EXPORT_INTERFACE Format {
    public:
        SOLAIRE_EXPORT_CALL ~Format(){}
        GenericValue SOLAIRE_EXPORT_CALL readValue(IStream&) const throw();
        bool SOLAIRE_EXPORT_CALL writeValue(const GenericValue&, OStream&) const throw();

        template<class T>
        SOLAIRE_FORCE_INLINE typename Encoder<T>::DecodeType read(Allocator& aAllocator, IStream& aStream) {
            return Encoder<T>::decode(aAllocator, readValue(aStream));
        }

        template<class T>
        SOLAIRE_FORCE_INLINE bool write(Allocator& aAllocator, const T& aValue, OStream& aStream) {
            return writeValue(Encoder<T>::encode(aAllocator, aValue), aStream);
        }
	};
}

#endif
