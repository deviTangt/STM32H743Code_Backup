#ifndef _SORT_CODE_H
#define _SORT_CODE_H

#include "main.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

//
extern void show_array(uint32_t *a,uint32_t array_size);
//
extern void swap(uint32_t *a,uint32_t i,uint32_t j);
//
extern void reset_array(uint32_t *a,uint32_t array_size,uint32_t range,uint32_t offset);
//
extern void bubble_sort(uint32_t *a,uint32_t array_size);
//
extern void cocktail_sort(uint32_t *a,uint32_t array_size);
//
extern void select_sort(uint32_t *a,uint32_t array_size);
//
extern void insert_sort(uint32_t *a,uint32_t array_size);
//
extern void gnome_sort(uint32_t *a,uint32_t array_size);
//
extern void merge_subArray(uint32_t *a,uint32_t left,uint32_t middle1,uint32_t middle2,uint32_t right);
//
extern void merge_sort_subArray(uint32_t *a,uint32_t low,uint32_t high);
//
extern void merge_sort(uint32_t *a,uint32_t array_size);
//
extern void bucket_sort(uint32_t *a,uint32_t array_size);
//
extern void insert_sort_for_quickupgrade(uint32_t *a,uint32_t low,uint32_t high);
//
extern void mid_swap(uint32_t *a,uint32_t low,uint32_t high);
//
extern void quick_sort_upgrade(uint32_t *a,uint32_t low,uint32_t high);
//
#endif

