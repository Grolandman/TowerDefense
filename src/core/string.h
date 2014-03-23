/* File name : string.h
 * File type : Header
 * Author : Alexandre DUBUJET
 * Creation : 2013
 * Desc. : C String implementation
 * Dependencies : -
 * Last modifications : 17/03/2014
 */

#ifndef H_STRING_INCLUDED
#define H_STRING_INCLUDED

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned long u32_t;
typedef char s8_t;
typedef short s16_t;
typedef long s32_t;

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum {
    STRING_SMALLER = -1,
    STRING_EQUAL,
    STRING_GREATER
} strcmpvalue_t;

typedef enum {
    STRING_ALLOCERROR = -1,
    STRING_NOSTRING,
    STRING_NOALLOC,
    STRING_ALLOCOK,
    STRING_UNMODIFIED
} strresult_t;

typedef struct string_t string_t;

string_t * NewString(void);

string_t * NewStringStr(char const * ap_str);

string_t * DelString(string_t * ap_this);

strresult_t SetStringStr(string_t * ap_this, char const * ap_str);

strresult_t SetStringChar(string_t * ap_this, char a_c);

strresult_t SetString(string_t * ap_this, string_t * ap_str);

strcmpvalue_t StringSizeCmp(string_t * ap_str1, string_t * ap_str2);

strresult_t StringStrAppend(string_t * ap_this, char const * ap_str);

strresult_t StringCharAppend(string_t * ap_this, char a_c);

string_t * StringStrAppendResult(char const * ap_str1, char const * ap_str2);

strresult_t StringStrInsert(string_t * ap_this, u32_t a_at, char const * ap_str);

strresult_t StringCharInsert(string_t * ap_this, u32_t a_at, char a_c);

strresult_t StringCut(string_t * ap_this, u32_t a_at);

string_t * StringSubStr(string_t * ap_str, u32_t a_begin, u32_t a_end);

string_t * StringNSubStr(string_t * ap_str, u32_t a_at, u32_t a_size);

strresult_t StringRemove(string_t * ap_this, u32_t a_begin, u32_t a_end);

strresult_t StringNRemove(string_t * ap_this, u32_t a_at, u32_t a_size);

u32_t StringSize(string_t * ap_this);

u32_t StringCapacity(string_t * ap_this);

char * const StringCStr(string_t * ap_this);

#ifdef __cplusplus
}
#endif

#endif /* H_STRING_INCLUDED */
