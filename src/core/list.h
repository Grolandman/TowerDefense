/* File name : list.h
 * File type : Header
 * Author : Alexandre DUBUJET
 * Creation : 2013
 * Desc. : C Linked list implementation
 * Dependencies : -
 * Last modifications : 13/03/2014
 */

#ifndef H_LIST_INCLUDED
#define H_LIST_INCLUDED

#include <stdlib.h>

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned long u32_t;
typedef char s8_t;
typedef short s16_t;
typedef long s32_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef char bool_t;
#define true  1
#define false 0

typedef struct node_t {
    void * data;
    struct node_t * next;
} node_t;

typedef struct {
    node_t * first;
} list_t;

list_t * NewList(void);

list_t * DelList(list_t * ap_list);

bool_t PushFrontList(list_t * ap_list);

void PopFrontList(list_t * ap_list);

u16_t ListSize(list_t * ap_list);

bool_t PushBackList(list_t * ap_list);

void PopBackList(list_t * ap_list);

void * ListAt(list_t * ap_list, u16_t a_n);

void * FirstOfList(list_t * ap_list);

void * LastOfList(list_t * ap_list);

bool_t SetListDataAt(list_t * ap_list, u16_t a_n, void * ap_data);

s32_t GetListDataPosition(list_t * ap_list, void * ap_data);

void PopListAt(list_t * ap_list, u16_t a_n);

bool_t PushListAt(list_t * ap_list, u16_t a_n);

bool_t PushBackListData(list_t * ap_list, void * ap_data);

#ifdef __cplusplus
}
#endif

#endif /* H_LIST_INCLUDED */
