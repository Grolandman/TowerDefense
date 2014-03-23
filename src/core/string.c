/* File name : string.c
 * File type : Source
 * Author : Alexandre DUBUJET
 * Creation : 2013
 * Desc. : C string_t implementation
 * Dependencies : stdlib.h, string.h, stdio.h, string.h
 * Last modifications : 17/03/2014
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "string.h"

#define STRING_UNIT 32

struct string_t {
    char * str;
    u32_t size;
    u32_t capacity;
};

string_t * NewString(void)
{
    string_t * lp_out = malloc(sizeof(string_t));

    if (lp_out) {
        lp_out->str = calloc(STRING_UNIT,sizeof(char));

        if (lp_out->str) {
            lp_out->size = 0;
            lp_out->capacity = STRING_UNIT;
        } else {
            free(lp_out);
            lp_out = NULL;
        }
    }
    return lp_out;
}

string_t * NewStringStr(char const * ap_str)
{
    string_t * lp_out = NewString();

    if (lp_out) {
        if (ap_str) {
            SetStringStr(lp_out,ap_str);
        }
    }

    return lp_out;
}

string_t * DelString(string_t * ap_this)
{
    if (ap_this) {
        free(ap_this->str);
        free(ap_this);
        ap_this = NULL;
    }
    return ap_this;
}

strresult_t SetStringStr(string_t * ap_this, char const * ap_str)
{
    strresult_t l_code = 0;

    if (ap_this) {
        if (ap_str && ap_str[0] != '\0') {
            u32_t l_size = strlen(ap_str);

            if (l_size + 1 > ap_this->capacity) {
                u32_t l_cap = ap_this->capacity + STRING_UNIT;
                char * lp_tmp;

                while (l_size + 1 > l_cap) {
                    l_cap += STRING_UNIT;
                }

                lp_tmp = calloc(l_cap,sizeof(char));

                if (lp_tmp) {
                    strcpy(lp_tmp,ap_str);
                    free(ap_this->str);
                    ap_this->str = lp_tmp;
                    ap_this->size = l_size;
                    ap_this->capacity = l_cap;
                    l_code = STRING_ALLOCOK;
                } else {
                    l_code = STRING_ALLOCERROR;
                }
            } else {
                ap_this->size = l_size;
                memcpy(ap_this->str,ap_str,ap_this->capacity);
                l_code = STRING_NOALLOC;
            }
        } else {
            memset(ap_this->str,0,ap_this->capacity);
            ap_this->size = 0;
            l_code = STRING_UNMODIFIED;
        }
    }

    return l_code;
}

strresult_t SetStringChar(string_t * ap_str, char a_c)
{
    char lp_tmp[2];

    sprintf(lp_tmp,"%c",a_c);

    return SetStringStr(ap_str,lp_tmp);
}

strresult_t SetString(string_t * ap_this, string_t * ap_str)
{
    return SetStringStr(ap_this,(ap_str) ? ap_str->str : NULL);
}

strcmpvalue_t StringSizeCmp(string_t * ap_str1, string_t * ap_str2)
{
    strcmpvalue_t l_code;

    if (ap_str1->size > ap_str2->size) {
        l_code = STRING_GREATER;
    } else if (ap_str1 < ap_str2) {
        l_code = STRING_SMALLER;
    } else {
        l_code = STRING_EQUAL;
    }

    return l_code;
}

strresult_t StringStrAppend(string_t * ap_this, char const * ap_str)
{
    strresult_t l_code = STRING_NOSTRING;

    if (ap_this) {
        if (ap_str && ap_str[0] != '\0') {
            if (ap_this->size) {
                u32_t l_size = strlen(ap_str) + ap_this->size + 1;
                char * lp_tmp = calloc(l_size,sizeof(char));

                if (lp_tmp) {
                    sprintf(lp_tmp,ap_this->str);
                    strcat(lp_tmp,ap_str);
                    SetStringStr(ap_this,lp_tmp);
                    l_code = STRING_ALLOCOK;
                    free(lp_tmp);
                } else {
                    l_code = STRING_ALLOCERROR;
                }
            } else {
                l_code = SetStringStr(ap_this,ap_str);
            }
        } else {
            l_code = STRING_UNMODIFIED;
        }
    }
    return l_code;
}

strresult_t StringCharAppend(string_t * ap_this, char a_c)
{
    char lp_tmp[2];

    sprintf(lp_tmp,"%c",a_c);

    return StringStrAppend(ap_this,lp_tmp);

}

string_t * StringStrAppendResult(char const * ap_str1, char const * ap_str2)
{
    string_t * lp_out = NewStringStr(ap_str1);

    if (lp_out) {
        StringStrAppend(lp_out,ap_str2);
    }
    return lp_out;
}

strresult_t StringStrInsert(string_t * ap_this, u32_t a_at, char const * ap_str)
{
    strresult_t l_code = STRING_NOSTRING;

    if (ap_this) {
        if (ap_str && ap_str[0] != '\0') {
            if (a_at >= ap_this->size) {
                l_code = StringStrAppend(ap_this,ap_str);
            } else {
                string_t * lp_tmp = StringSubStr(ap_this,a_at,ap_this->size);

                if (lp_tmp) {
                    l_code = StringCut(ap_this,a_at);

                    if (l_code > 0) {
                        l_code = StringStrAppend(ap_this,ap_str);

                        if (l_code > 0) {
                            l_code = StringStrAppend(ap_this,lp_tmp->str);
                        }
                    }
                    DelString(lp_tmp);
                }
            }
        } else {
            l_code = STRING_UNMODIFIED;
        }
    }
    return l_code;
}

strresult_t StringCharInsert(string_t * ap_this, u32_t a_at, char a_c)
{
    char lp_tmp[2];

    sprintf(lp_tmp,"%c",a_c);

    return StringStrInsert(ap_this,a_at,lp_tmp);
}

strresult_t StringCut(string_t * ap_this, u32_t a_at)
{
    strresult_t l_code = STRING_NOSTRING;

    if (ap_this) {
        if (a_at == 0) {
            l_code = SetStringStr(ap_this,NULL);
        } else if (a_at >= ap_this->size) {
            l_code = STRING_UNMODIFIED;
        } else {
            u32_t l_i;

            if (a_at > ap_this->size) {
                a_at = ap_this->size;
            }
            for (l_i=0 ; l_i<ap_this->size-a_at ; l_i++) {
                ap_this->str[a_at+l_i] = '\0';
            }
            ap_this->size -= (ap_this->size - a_at);
            l_code = STRING_NOALLOC;
        }
    }
    return l_code;
}

string_t * StringSubStr(string_t * ap_str, u32_t a_begin, u32_t a_end)
{
    string_t * lp_out = NewString();

    if (lp_out) {
        if ((ap_str)) {
            if (a_begin < ap_str->size && a_begin <= a_end) {
                char * lp_tmp = NULL;
                u32_t l_size = 0;

                if (a_end > ap_str->size) {
                    a_end = ap_str->size;
                }
                l_size = a_end - a_begin + 2;
                lp_tmp = calloc(l_size,sizeof(char));

                if (lp_tmp) {
                    memcpy(lp_tmp,ap_str->str + a_begin,l_size);
                    lp_tmp[l_size-1] = '\0';
                    SetStringStr(lp_out,lp_tmp);
                    free(lp_tmp);
                }
            }
        }
    }
    return lp_out;
}

string_t * StringNSubStr(string_t * ap_str, u32_t a_at, u32_t a_size)
{
    return StringSubStr(ap_str,a_at,a_at+a_size);
}

strresult_t StringRemove(string_t * ap_this, u32_t a_begin, u32_t a_end)
{
    strresult_t l_code = STRING_NOSTRING;

    if (ap_this) {
        if (a_begin >= ap_this->size && a_begin > a_end) {
            l_code = STRING_UNMODIFIED;
        } else {
            if (a_end >= ap_this->size) {
                l_code = StringCut(ap_this,a_begin);
            } else {
                string_t * lp_tmp = StringSubStr(ap_this,a_end+1,ap_this->size);

                if (lp_tmp) {
                    l_code = StringCut(ap_this,a_begin);

                    if (l_code) {
                        l_code = StringStrAppend(ap_this,lp_tmp->str);
                    }
                    DelString(lp_tmp);
                } else {
                    l_code = STRING_ALLOCERROR;
                }
            }
        }
    }
    return l_code;
}

strresult_t StringNRemove(string_t * ap_this, u32_t a_at, u32_t a_size)
{
    return StringRemove(ap_this,a_at,a_at+a_size-1);
}

u32_t StringSize(string_t * ap_this)
{
    return ap_this->size;
}

u32_t StringCapacity(string_t * ap_this)
{
    return ap_this->capacity;
}

char * const StringCStr(string_t * ap_this)
{
    return ap_this->str;
}

