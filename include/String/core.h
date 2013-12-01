/**
**      ==START OF REFU LICENSE==
**
** Copyright (c) 2011-2013, Karapetsas Eleftherios
** All rights reserved.
** 
** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
**  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
**  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the distribution.
**  3. Neither the name of the Original Author of Refu nor the names of its contributors may be used to endorse or promote products derived from
** 
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
** INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES;LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**      ==END OF REFU LICENSE==
**
**
*/
#ifndef RF_STRING_CORE_H
#define RF_STRING_CORE_H


//for string decl
    #include <String/stringx_decl.h>
//for exact sized types
    #include <Definitions/types.h>
//for bool
    #include <Definitions/retcodes.h>
// for rf_utf8_is_continutation_byte
    #include <String/unicode.h>
//for size_t
    #include <string.h>

#ifdef __cplusplus
extern "C"
{///opening bracket for calling from C++
#endif


//! @name Creating an RFstring
//! @{

/**
 ** @memberof RFstring
 ** Statically initialize a string
 */
#define RF_STRING_STATIC_INIT(s_) {s_, sizeof(s_) - 1}

/**
 ** @memberof RFstring
 ** @brief Allocates and returns a string with the given characters
 **
 ** Given characters have to be in UTF-8. A check for valid sequence
 ** of bytes is performed. @notinherited{StringX}
 ** @lmsFunction
 ** @param s                      The sequence of bytes for the characters
 **                               in UTF-8 (the default).
 ** @param ... \rfoptional{nothing}  Depending on the string literal,
 ** the function may expect a sequence of additional arguments,
 ** each containing one value to be inserted instead of each %-tag
 ** specified in the @c slit parameter, if any. There should be
 ** the same number of these arguments as the number of %-tags that expect a value.
 ** @return Returns the initialized RF_string or null in case of failure to initialize, due to invalid utf-8 sequence
 ** @see rf_string_init()
 ** @see rf_stringx_create()
 **/
i_DECLIMEX_ RFstring* rf_string_create(const char* s);
/**
 ** @memberof RFstring
 ** @brief Allocates and returns a string with the given characters (vararg)
 **
 ** Given characters have to be in UTF-8. A check for valid sequence
 ** of bytes is performed. @notinherited{StringX}
 ** @lmsFunction
 ** @param s                      The sequence of bytes for the characters
 **                               in UTF-8 (the default).
 ** @param ...                    Depending on the string literal, the function
 **                               may expect additional arguments in a printf-like
 **                               fashion
 ** @return                       Returns the initialized RF_string or null in
 **                               case of failure
 ** @see rf_string_init()
 **/
i_DECLIMEX_ RFstring* rf_string_createv(const char* s, ...);





/**
 ** @memberof RFstring
 ** @brief Initializes a string with the given characters.
 **
 ** @notinherited{StringX}
 ** @lmsFunction
 ** @see rf_string_create()
 **
 **/
i_DECLIMEX_ bool rf_string_init(RFstring* str,const char* s);
/**
 ** @memberof RFstring
 ** @brief Initializes a string with the given characters. (varargs)
 **
 ** @notinherited{StringX}
 ** @lmsFunction
 ** @see rf_string_createv()
 **
 **/
i_DECLIMEX_ bool rf_string_initv(RFstring* str, const char* s, ...);

/**
 ** @memberof RFstring
 ** @cppnotctor
 ** @brief Allocates a String by turning a unicode code point
 ** in a String (encoded in UTF-8).
 **
 ** @notinherited{StringX}
 ** @param code The unicode code point to encode
 ** @return A String with the code point encoded in it or a null
 ** pointer in case of an illegal code point value
 ** @see rf_string_init_cp()
 ** @see rf_stringx_create_cp()
 **/
i_DECLIMEX_ RFstring* rf_string_create_cp(uint32_t code);
/**
 ** @memberof RFstring
 ** @brief Initializes a string by turning a unicode code point 
 **        in a String (encoded in UTF-8).
 **
 ** @notinherited{StringX}
 ** @see rf_string_create_cp()
 ** @see rf_stringx_init_cp()
 **/
i_DECLIMEX_ bool rf_string_init_cp(RFstring* str,uint32_t code);



/**
 ** @memberof RFstring
 ** @cppnotctor
 ** @brief Allocates and returns a string with the given characters
 **        without any checking.
 **
 ** @notinherited{StringX}
 ** @warning NO VALID-UTF8 check is performed.
 ** @param s The sequence of bytes for the characters in UTF-8
 ** (the default).Can also follow a printf-like format which will be formatted with
 ** the variables that follow it. No check for valid bytestream is performed
 ** @return Returns the initialized RF_string or null in case
 ** of failure to initialize
 ** @see rf_string_init_unsafe()
 **/
RFstring* rf_string_create_unsafe(const char* s);



/**
 ** @memberof RFstring
 ** @brief Initializes a string with the given characters with no checking
 **
 ** @notinherited{StringX}
 ** @see rf_string_create_unsafe()
 **/
i_DECLIMEX_ bool rf_string_init_unsafe(RFstring* str,const char* s);

/**
 ** @memberof RFstring
 ** @brief Initializes a string from a non-null terminated char* buffer
 ** and for the given bytelength
 ** 
 ** @notinherited{StringX}
 ** @see rf_string_init_unsafe()
 **/
i_DECLIMEX_ bool rf_string_init_unsafe_nnt(RFstring* str, const char* s,
                                          size_t length);

/**
 ** @memberof RFstring
 ** @opassign
 ** @brief Allocates and returns a string with the given integer.
 **
 ** @notinherited{StringX}
 ** @param i The integer to turn into a string
 ** @return Returns the initialized RF_string
 ** @see rf_string_init_i()
 **/
i_DECLIMEX_ RFstring* rf_string_create_i(int32_t i);
/**
 ** @memberof RFstring
 ** @brief Initializes a string with the given integer.
 **
 ** @notinherited{StringX}
 ** @see rf_string_create_i()
 **/
i_DECLIMEX_ bool rf_string_init_i(RFstring* str,int32_t i);
/**
 ** @memberof RFstring
 ** @opassign
 ** @brief Allocates and returns a string with the given float.
 **
 ** @notinherited{StringX}
 ** @param f The float to turn into a string
 ** @return Returns the initialized RF_string
 ** @see rf_string_init_f()
 **/
i_DECLIMEX_ RFstring* rf_string_create_f(float f);
/**
 ** @memberof RFstring
 ** @brief Initializes a string with the given float.
 **
 ** @notinherited{StringX}
 ** @see rf_string_create_f()
 **/
i_DECLIMEX_ bool rf_string_init_f(RFstring* str,float f);

/**
 ** @memberof RFstring
 ** @brief Allocates and returns a string with the given UTF-16 byte sequence.
 **
 ** @notinherited{StringX}
 ** @param s A buffer of 2 bytes word representing the
 **  utf-16 byte sequence.
 ** @param len The bytelength of @c s
 ** @return Returns the initialized RF_string or null in case of failure to
 ** initialize, due to invalid utf-16 sequence or illegal endianess value
 ** @see rf_string_init_utf16()
 ** @see rf_string_create_f_utf16()
 ** @see rf_string_init_utf16()
 **/
i_DECLIMEX_ RFstring* rf_string_create_utf16(const uint16_t* s,
                                             unsigned int len);
/**
 ** @memberof RFstring
 ** @brief Initializes a string with the given UTF-16 byte sequence.
 **
 ** @notinherited{StringX}
 ** @see rf_string_create_utf16()
 ** @see rf_string_create_f_utf16()
 ** @see rf_string_init_utf16()
 **/
i_DECLIMEX_ bool rf_string_init_utf16(RFstring* str, const uint16_t* s,
                                     unsigned int len);

/**
 ** @memberof RFstring
 ** @cppnotctor
 ** @brief Allocates and returns a string with the given UTF-32 byte sequence.
 **
 ** @notinherited{StringX}
 ** Given characters have to be in UTF-32 and in the endianess of the system.
 ** No endianess swapping occurs in the function
 ** @param s A buffer of 4-byte words representing the utf-32
 ** byte sequence.
 ** @param len The length of s in codepoints (unicode characters)
 ** @return Returns the initialized RF_string or null in case of
 ** failure to initialize
 ** @see rf_string_init_utf32()
 ** @see rf_string_create_f_utf32()
 ** @see rf_string_init_utf32()
 **/
i_DECLIMEX_ RFstring* rf_string_create_utf32(const uint32_t* s,
                                             unsigned int len);
/**
 ** @memberof RFstring
 ** @brief Initializes a string with the given UTF-32 byte sequence.
 **
 ** @notinherited{StringX}
 ** @see rf_string_create_utf32()
 ** @see rf_string_create_f_utf32()
 ** @see rf_string_init_utf32()
 **/
i_DECLIMEX_ bool rf_string_init_utf32(RFstring* str, const uint32_t* s,
                                     unsigned int len);

//! @}

//! @name Assigning to a String
//! @{

/**
 ** @memberof RFstring
 ** @brief Assigns the value of the source string to the destination.
 **
 ** @notinherited{StringX}
 ** @lmsFunction
 ** Both strings should already be initialized and hold a value.
 ** It is an error to give null parameters.
 ** @param dest   The destination string, which should get assigned
 ** @param source The source string, whose values to copy.
 **               @inhtype{String,StringX} @tmpSTR
 **
 ** @return       Returns @c true for success and @c false otherwise
 ** @see rf_string_assign_char()
 ** @see rf_stringx_assign()
 **/
i_DECLIMEX_ bool rf_string_assign(RFstring* dest, const void* source);


/**
 ** @memberof RFstring
 ** @brief Assigns the value of a unicode character to the string
 **
 ** @notinherited{StringX}
 ** @param thisstr The string to assign to
 ** @param character The unicode character codepoint to assign to the String
 ** @return Returns @c true for succesfull assignment and @c false
 **         if the given @c character was not a valid unicode codepoint
 ** @see rf_string_assign()
 ** @see rf_stringx_assign_char()
 **/
i_DECLIMEX_ bool rf_string_assign_char(RFstring* thisstr,uint32_t character);

/**
 ** @memberof RFstring
 ** @brief Nullifies a String
 ** @warning Use null strings at your own risk. None of the RF_Sting/X
 ** functions currently test for them
 ** A safer and easier alternative is to assigg an empty string and
 * check for it with @ref rf_string_is_empty()
 **/
#define rf_string_null(i_STRING) do{                      \
        rf_string_length_bytes(i_STRING) = 0;               \
        rf_string_data(i_STRING) = NULL;                  \
}while(0)

//! @}

//! @name String Copying Functions
//! @{

/**
 ** @memberof RFstring
 ** @brief Creates and returns an allocated copy of the given string
 **
 ** @isinherited{StringX}
 ** @param src The string to copy from. @inhtype{String,StringX}
 ** @return Returns a string copied from the previous one or null
 ** if the original string was null
 ** @see rf_string_copy_in()
 ** @see rf_string_copy_chars()
 **/
i_DECLIMEX_ RFstring* rf_string_copy_out(const void* src);
/**
 ** @memberof RFstring
 ** @brief Copies all the contents of a string to another
 **
 ** @isinherited{StringX}
 ** @return Returns @c true for succesfull copying @c false otherwise
 ** @see rf_string_copy_out()
 ** @see rf_string_copy_chars()
 **
 **/
i_DECLIMEX_ bool rf_string_copy_in(RFstring* dst, const void* src);
/**
 ** @memberof RFstring
 ** @brief Copies a certain number of characters from a string
 **
 ** @isinherited{StringX}
 ** Copies @c n characters from @c src String into the destination @c dst string.
 ** @param dst The string to copy in
 ** @param src The string to copy from. @inhtype{String,StringX}
 ** @param n The number of characters to copy from the @c src string
 ** If the value is bigger than the maximum number of characters 
 ** then still all characters are copied.
 ** @return Returns @c true for success and @c false otherwise
 ** @see rf_string_copy_in()
 ** @see rf_string_copy_out()
 **
 **/
i_DECLIMEX_ bool rf_string_copy_chars(RFstring* dst, const void* src,
                                     uint32_t n);

//! @}

//! @name Getting rid of an RFstring
//! @{

/**
 ** @memberof RFstring
 ** @cppignore
 ** @brief Deletes a string object and also frees its pointer.
 **
 ** @notinherited{StringX}
 ** Use it for strings made with _Create
 ** @param s The string for deletion
 ** @see rf_string_deinit()
 **/
i_DECLIMEX_ void rf_string_destroy(RFstring* s);
/**
 ** @memberof RFstring
 ** @cppignore
 ** @brief Deletes a string object only, not its memory.
 **
 ** @notinherited{StringX}
 ** @see rf_string_destroy()
 **
 **/
i_DECLIMEX_ void rf_string_deinit(RFstring* s);


//! @}

//! @name Equality check
//! @{

/**
 ** @memberof RFstring
 ** @opcmpeq
 ** @brief Compares two Strings and returns true
 **        if they are equal and false otherwise
 **
 ** @isinherited{StringX}
 ** @lmsFunction
 ** @param s1 The first string to compare @inhtype{String,StringX} @tmpSTR
 ** @param s2 The second string to compare @inhtype{String,StringX} @tmpSTR
 ** @return True in case the strings are equal and false otherwise
 **/
i_DECLIMEX_ bool rf_string_equal(const void* s1, const void* s2);

/**
 ** @memberof RFstring
 ** @brief Checks that a string is null
 **/
#define rf_string_is_null(i_STRING)                                       \
    (rf_string_length_bytes(i_STRING) == 0 && rf_string_data(i_STRING) == NULL)


/**
 ** @memberof RFstring
 ** @isinherited{StringX}
 ** @brief Checks that a string is empty. 
 **/
#define rf_string_is_empty(i_STRING)              \
    (rf_string_equal((i_STRING), RFS_("")))

//! @}


//! @name String Iteration
//! @{


/*
  The following 2 functions are exposed here only 
  because they are used in the iteration macros
*/

/**
 ** @internal
 ** @memberof RFstring
 ** @brief Retrieves the unicode code point of the parameter
 ** bytepos of the string.
 **
 ** @isinherited{StringX}
 ** This is an internal function, there is no need to use it. The reason
 ** it is exposed here is that it is utilized in the iteration macros.
 ** @warning DO NOT use this function unless you know what you are doing
 ** @param thisstr The string whose byte position code point we need.
 **                @inhtype{String,StringX}
 ** @param bytepos The byte position of the string from
 **                 where to get the code point.
 ** @warning If this is out of bounds then nothing can detect it and
 **          at best it will cause a SEG FAULT. Moreover no check to see
 **          if this is not a continutation byte is made. All the checks
 **          must have been made before calling the function.
 ** @return Returns the code point of the byte position as an uint32_t
 ** @endinternal
 **/
i_DECLIMEX_ uint32_t rf_string_byte_pos_to_code_point(const void* thisstr,
                                                 uint32_t bytepos);
/**
 ** @internal
 ** @memberof RFstring
 ** @brief Retrieves character position of a byte position
 **
 ** @isinherited{StringX}
 ** This is an internal function, there is no need to use it. It attempts
 ** to retrieve character position from a byte position. If the byte
 ** position is a continutation byte and does not constitute the start
 ** of a character then depending on the option the function will find
 ** either the next character or the previous character position from
 ** this byte position
 **
 ** @warning DO NOT use this function unless you know what you are doing
 ** @param thisstr The string whose byte position code point we need.
 **                @inhtype{String,StringX}
 ** @param bytepos The byte position of the string from where to get
 **                the character position
 ** @param before A boolean flag denoting the behaviour in case this byte
 **               position is a continutation byte. If @c before is true then
 **               the function will retrieve the first character position
 **               before the byte. If it is false, it will retrieve the
 **               first character position after the continuation byte.
 ** @endinternal
 **/
i_DECLIMEX_ uint32_t rf_string_byte_pos_to_char_pos(const void* thisstr,
                                               uint32_t bytepos,
                                               bool before);


// Checks if a given byte is a continuation byte
#define rf_utf8_is_continuation_byte2(b__)  ( b__ >= 0x80 && b__<= 0xBF )

/*
  Two macros to accomplish iteration of an RFstring from any given
  character going forwards. This macro should be used with its end pair.
  We take advantage of the fact that an RFstring is always guaranteed
  to contain a valid UTF-8 sequence and thus no checks are performed.
*/

/**
** @memberof RFstring
** @cppignore
** @brief Starts an RFstring forward iteration scope.
**
** @isinherited{StringX}
** Use this macro to iterate every character inside an RFstring or RFstringx
** Must be used with its pair macro #rfString_Iterate_End.
** As an example consider this code that iterates every character
** of a string from the start to finish
** @code
** uint32_t i = 0;
** uint32_t charValue;
** RFstring foo;rf_string_init(&foo,"I am a String");
** rf_string_iterate_start(&foo,i,charValue)
**      //for every character in the string,let's print it
**      printf("Character at index %d is %c\n",i,charValue);
** rf_string_iterate_end(i)
** @endcode
** @param[in] string_ The string to iterate. Must be a pointer to string
** @param[in,out] startCharacterPos_ Here give an uint32_t which will
**                be the character position from which to start the iteration.
**                In each iteration this will hold the character index.
**                If the given position is out of bounds then the
**                iteration does not happen
** @param[in,out] characterUnicodeValue_ Here pass an uint32_t which in
**                each iteration will hold the unicode code point of the
**                character at position startCharacterPos_
** @see rf_string_iterate_end()
** @see rf_string_iterate_b_start()
**/
#define rf_string_iterate_start(string_, startCharacterPos_,             \
                               characterUnicodeValue_)                  \
    {                                                                   \
    /* b index sec is the byte index and j the character index*/        \
    uint32_t byteIndex_ = 0;uint32_t j_=0;                              \
    /*                                                                  \
      iterate until we find the character position requested and        \
      its equivalent byte position                                      \
    */                                                                  \
    while(j_ != startCharacterPos_)                                     \
    {                                                                   \
        if(!rf_utf8_is_continuation_byte(rf_string_data(string_)[byteIndex_])) \
        {                                                               \
            j_++;                                                       \
        }                                                               \
        byteIndex_++;                                                   \
    }                                                                   \
    /*now start the requested iteration*/                               \
    while(byteIndex_ < rf_string_length_bytes(string_))                    \
    {                                                                   \
    /*if it's a character*/                                             \
        if(!rf_utf8_is_continuation_byte(rf_string_data(string_)[byteIndex_])) \
        {/*Give the character value to the user*/                       \
            characterUnicodeValue_ = rf_string_byte_pos_to_code_point((string_), \
                                                                 byteIndex_);

/**
 ** @memberof RFstring
 ** @cppignore
 ** @brief Ends an RF_String/RFstringx forward iteration scope.
 **
 ** @isinherited{StringX}
 ** Look at #rf_string_iterate_start for an example usage
 ** @param[in,out] startCharacterPos_ Here give the uint32_t given to #rf_string_iterate_start
 ** @see rf_string_iterate_start()
 **
 **/
#define rf_string_iterate_end(startCharacterPos_)  startCharacterPos_++;}byteIndex_++;}}

/*
  Two macros to accomplish iteration of an RFstring from any given
  character going backwards. This macro should be used with its end pair.
  We take advantage of the fact that an RFstring is always guaranteed to contain
  a valid UTF-8 sequence and thus no checks are performed.
*/

/**
** @memberof RFstring
** @cppignore
** @brief Starts an RFstring backward iteration scope.
**
** @isinherited{StringX}
** Use this macro to iterate every character inside an RFstring or
** RFstringx going backwards
** Must be used with its pair macro #rfString_IterateB_End.
** As an example consider this code that iterates every character of a
** string from the start to finish
** @code
** uint32_t charValue;
** RFstring foo;rf_string_init(&foo,"I am a String");
** uint32_t i = rf_string_length(&foo)-1;//-1 is since String indexing starts from 0
** rf_string_iterate_b_start(&foo,i,charValue)
**      //for every character in the string,let's print it
**      printf("Character at index %d is %c\n",i,charValue);
** rf_string_iterate_b_end(i)
** @endcode
** @param[in] string_ The string to iterate. Must be a pointer to string
** @param[in,out] characterPos_ Here give an uint32_t which will be the
**                character position from which to start the iteration. 
**                In each iteration this will hold the character index.
**                If the given position is out of bounds then the iteration
**                does not happen
** @param[in,out] characterUnicodeValue_ Here pass an uint32_t which in
**                each iteration will hold the unicode code point of the
**                character at position characterPos_
** @see rf_string_iterate_b_end()
** @see rf_string_iterate_start()
**/
#define rf_string_iterate_b_start(string_,characterPos_,\
                                characterUnicodeValue_)     {           \
    /* b index is the byte index and j the character index*/            \
    uint32_t b_index_ = 0;uint32_t j_=0;                                \
    /*                                                                  \
       c index sec is another signed copy of the character index        \
       (and is int64_t so that it can cater for any situation). Reason  \
       is cause going backwards we gotta have -1 too                    \
    */                                                                  \
    int64_t c_index_ = characterPos_;                                   \
    /*                                                                  \
      iterate until we find the character position requested and        \
      its equivalent byte position                                      \
    */                                                                  \
    while(j_ != characterPos_)                                          \
    {                                                                   \
        if(!rf_utf8_is_continuation_byte(rf_string_data(string_)[b_index_])) \
        {                                                               \
            j_++;                                                       \
        }                                                               \
        b_index_++;                                                     \
    }                                                                   \
    /*                                                                  \
      now start the requested iteration - notice that the               \
      end condition is to reach the first character position            \
    */                                                                  \
    while(c_index_ != -1)                                               \
    {                                                                   \
        /*if it's a character*/                                         \
        if(!rf_utf8_is_continuation_byte(rf_string_data(string_)[b_index_])) \
        {/*Give the character value to the user*/                       \
            characterUnicodeValue_ = rf_string_byte_pos_to_code_point((string_), \
                                                                 b_index_);

/**
 ** @memberof RFstring
 ** @cppignore
 ** @brief Ends an RF_String/RFstringx backward iteration scope.
 **
 ** @isinherited{StringX}
 ** Look at #rf_string_iterate_b_start for an example usage
 ** @param[in,out] characterPos_ Here give the uint32_t given
 ** to #rf_string_iterate_b_start
 ** @see rf_string_itera_b_start()
 **
 **/
#define rf_string_iterate_b_end(characterPos_)  c_index_-- ;characterPos_--;}b_index_--;}}

//! @}


#ifdef __cplusplus
}///closing bracket for calling from C++
#endif

#endif//include guards end
