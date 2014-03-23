/* File name : list.c
 * File type : Source
 * Author : Alexandre DUBUJET
 * Creation : 2013
 * Desc. : C Linked list implementation
 * Dependencies : list.h, stdlib.h
 * Last modifications : 22/03/2014
 */

#include "list.h"

#include <stdlib.h>

static node_t * NewNode(void)
{
    node_t * lp_out = malloc(sizeof(node_t));

    if (lp_out) {
        lp_out->data = NULL;
        lp_out->next = NULL;
    }

    return lp_out;
}

static node_t * NodeAt(list_t * ap_list, u16_t a_n)
{
    node_t * lp_out = NULL;

    if (ap_list) {
        if (a_n < ListSize(ap_list)) {
            u16_t l_i=0;
            lp_out = ap_list->first;

            while (lp_out && l_i != a_n) {
                lp_out = lp_out->next;
                l_i++;
            }
        }
    }

    return lp_out;
}

list_t * NewList(void)
{
    list_t * lp_out = malloc(sizeof(list_t));

    if (lp_out) {
        lp_out->first = NULL;
    }
    return lp_out;
}

list_t * DelList(list_t * ap_list)
{
    if (ap_list) {
        while (ap_list->first) {
            PopFrontList(ap_list);
        }
        free(ap_list);
        ap_list = NULL;
    }
    return ap_list;
}

bool_t PushFrontList(list_t * ap_list)
{
    bool_t l_code = false;

    if (ap_list) {
        node_t * lp_nf = NewNode();
        if (lp_nf) {
            if (ap_list->first) {
                lp_nf->next = ap_list->first;
            }

            ap_list->first = lp_nf;

            l_code = true;
        }
    }
    return l_code;
}

void PopFrontList(list_t * ap_list)
{
    if (ap_list) {
        if (ap_list->first) {
            node_t * lp_nf = ap_list->first;
            ap_list->first = lp_nf->next;
            free(lp_nf);
            lp_nf = NULL;
        }
    }
}

void * ListAt(list_t * ap_list, u16_t a_n)
{
    void * lp_out = NULL;
    node_t * lp_nd = NodeAt(ap_list,a_n);

    if (lp_nd) {
        lp_out = lp_nd->data;
    }
    return lp_out;
}

u16_t ListSize(list_t * ap_list)
{
    node_t * lp_tmp = NULL;
    u16_t l_i = 0;

    if (ap_list) {
        lp_tmp = ap_list->first;

        while (lp_tmp) {
            lp_tmp = lp_tmp->next;
            l_i++;
        }
    }
    return l_i;
}

bool_t PushBackList(list_t * ap_list)
{
    bool_t l_code = false;

    if (ap_list) {
        u16_t l_size = ListSize(ap_list);

        if (l_size) {
            node_t * l_n = NodeAt(ap_list,l_size-1);

            if (l_n) {
                l_n->next = NewNode();
                l_code = true;
            }
        } else {
            l_code = PushFrontList(ap_list);
        }
    }
    return l_code;
}

void PopBackList(list_t * ap_list)
{
    u16_t l_size = ListSize(ap_list);

    if (l_size) {
        node_t * l_n = NodeAt(ap_list,l_size-1);
        if (l_n) {
            free(l_n);
            l_n = NULL;
        }
    }
}

void * FirstOfList(list_t * ap_list)
{
    return ListAt(ap_list,0);
}

void * LastOfList(list_t * ap_list)
{
    void * lp_out = NULL;
    u16_t l_size = ListSize(ap_list);

    if (l_size) {
        lp_out = ListAt(ap_list,l_size-1);
    }
    return lp_out;
}

bool_t SetListDataAt(list_t * ap_list, u16_t a_n, void * ap_data)
{
    node_t * lp_tmp = NodeAt(ap_list,a_n);
    bool_t code = false;

    if (lp_tmp) {
        lp_tmp->data = ap_data;
        code = true;
    }
    return code;
}

s32_t GetListDataPosition(list_t * ap_list, void * ap_data)
{
    s32_t l_out = -1;

    if (ap_list && ap_data) {
        int l_i;
        int l_size = ListSize(ap_list);

        for (l_i=0 ; l_i<l_size ; l_i++) {
            if (ListAt(ap_list,l_i)==ap_data) {
                l_out = l_i;
                break;
            }
        }
    }

    return l_out;
}

void PopListAt(list_t * ap_list, u16_t a_n)
{
    u16_t l_n = ListSize(ap_list);

    if (ap_list && a_n<l_n) {
        if (a_n == 0) {
            PopBackList(ap_list);
        } else if (a_n == l_n-1) {
            PopBackList(ap_list);
        } else {
            node_t * lp_ptr = NodeAt(ap_list,a_n-1);

            if (lp_ptr) {
                node_t * lp_tmp = lp_ptr->next;
                lp_ptr->next = lp_tmp->next;
                free(lp_tmp);
            }
        }
    }
}

bool_t PushListAt(list_t * ap_list, u16_t a_n)
{
    bool_t l_code = false;

    if (ap_list) {
        u16_t l_size = ListSize(ap_list);
        if (a_n == 0 || l_size == 0) {
            l_code = PushFrontList(ap_list);
        } else if (a_n >= l_size) {
            l_code = PushBackList(ap_list);
        } else {
            node_t * lp_tmp = NodeAt(ap_list,a_n-1);
            node_t * lp_new = NewNode();

            if (lp_new) {
                lp_new->next = lp_tmp->next->next;
                lp_tmp->next = lp_new;
                l_code = true;
            }
        }
    }

    return l_code;
}

bool_t PushBackListData(list_t * ap_list, void * ap_data)
{
    bool_t l_code = false;

    if (ap_list) {
        if (PushBackList(ap_list)) {
            SetListDataAt(ap_list,ListSize(ap_list)-1,ap_data);
            l_code = true;
        }
    }

    return l_code;
}
