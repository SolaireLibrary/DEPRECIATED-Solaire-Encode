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

    /*!
        \brief Implements a storage format for encoding and decoding C++ objects.
        \version 1.0.0
    */
	SOLAIRE_EXPORT_INTERFACE Format {
    public:
        /*!
            \brief Destroy the Format object.
        */
        SOLAIRE_EXPORT_CALL ~Format(){}

        /*!
            \brief Decode data from the storage format into GenericValue format.
            \param aStream The source of encoded data.
            \return The decoded data.
        */
        GenericValue SOLAIRE_EXPORT_CALL readValue(IStream&) const throw();

        /*!
            \brief Encode data into the storage format from GenericValue format.
            \param aValue The data to encode.
            \param aStream The place to store the encoded data.
            \return True if the data was encoded successfully.
        */
        bool SOLAIRE_EXPORT_CALL writeValue(const GenericValue&, OStream&) const throw();

        /*!
            \brief Decode a C++ object in place.
            \details Passes the output of readValue into Encoder<T>::decode.
            \tparam T The type of the object being decoded.
            \param aAllocator The allocator to allocate the object, and any parseing data from.
            \param aStream The source of encoded data.
            \see readValue
            \see Encoder::decode
        */
        template<class T>
        SOLAIRE_FORCE_INLINE typename Encoder<T>::DecodeType read(Allocator& aAllocator, IStream& aStream) {
            return Encoder<T>::decode(aAllocator, readValue(aStream));
        }

        /*!
            \brief Encode a C++ object in place.
            \details Passes the output of Encoder<T>::encode into writeValue.
            \tparam T The type of the object being encoded.
            \param aAllocator The allocator to allocate any parseing data from.
            \param aValue The object being encoded.
            \param aStream The place to store the encoded data.
            \return True if the object was encoded successfully.
            \see writeValue
            \see Encoder::encode
        */
        template<class T>
        SOLAIRE_FORCE_INLINE bool write(Allocator& aAllocator, const T& aValue, OStream& aStream) {
            return writeValue(Encoder<T>::encode(aAllocator, aValue), aStream);
        }
	};
}

#endif
