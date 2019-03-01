/****************************************************************************
* Copyright (c) 2019 Simon Slater <skslater@skslater.net>
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
****************************************************************************/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUMELEMS    100000

#include "vector.h"

int main(int argc, char **argv)
{
    struct timespec ts1, ts2;
    int rc1, rc2, n;
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;

    // test new
    vec v = vector_new(sizeof(int), 4);
    assert(v != NULL);
    assert(v->capacity == 4);
    assert(v->count == 0);
    assert(v->elemsize == sizeof(int));
    
    // test push
    vector_push(v, &one);
    assert(v->count == 1);
    int *oneptr = (int *) vector_get(v, 0);
    assert(*oneptr == 1);

    // test push to capacity
    vector_push(v, &two);
    vector_push(v, &three);
    vector_push(v, &four);
    int *threeptr = (int *) vector_get(v, 2);
    assert(v->count == 4);
    assert(*threeptr == 3);
    assert(v->capacity == 4);

    // test grow
    vector_push(v, &five);
    int *twoptr = (int *) vector_get(v, 1);
    int *fiveptr = (int *) vector_get(v, 4);
    assert(v->count == 5);
    assert(v->capacity == 8);
    assert(*fiveptr == 5);
    
    // test delete
    vector_delete(v, 3);
    assert(v->count == 4);
    int *fourptr = (int *) vector_get(v, 3);
    assert(*fourptr == 5);
    
    // test shrink
    vector_delete(v, 0);
    assert(v->count == 3);
    assert(v->capacity == 8);
    vector_shrink(v);
    assert(v->count == 3);
    assert(v->capacity == 3);

    // test clear
    vector_clear(v);
    assert(v->count == 0);
    assert(v->capacity == VECTOR_MINCAPACITY);
 
    // free
    vector_free(v);

    // test new no capacity
    v = vector_new(sizeof(int), 0);
    assert(v != NULL);
    assert(v->capacity == VECTOR_MINCAPACITY);
    assert(v->count == 0);
    assert(v->elemsize == sizeof(int));
    
    // measurement
    rc1 = clock_gettime(CLOCK_REALTIME, &ts1);
    for (n=0; n<NUMELEMS; n++)
        vector_push(v, &n);
    rc2 = clock_gettime(CLOCK_REALTIME, &ts2);
    assert(rc1 == 0);
    assert(rc2 == 0);
    
    printf("Measurements started for %d elements @ %u.%u\n", NUMELEMS, ts1.tv_sec, ts1.tv_nsec);
    printf("Measurements ended   for %d elements @ %u.%u\n", NUMELEMS, ts2.tv_sec, ts2.tv_nsec);
    
    puts("All test passed");
    
    
}