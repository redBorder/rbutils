/*
 * Copyright (c) 2009-2014 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdlib.h>
#include <string.h>
#include "rbstring.h"

#ifndef min
#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#endif

#ifndef max
#define max(X,Y) ((X) > (Y) ? (X) : (Y))
#endif

#define STRBUFFER_MIN_SIZE  2048
#define STRBUFFER_FACTOR    2
#define STRBUFFER_SIZE_MAX  ((size_t)-1)

int strbuffer_init(strbuffer_t *strbuff)
{
    strbuff->size = STRBUFFER_MIN_SIZE;
    strbuff->length = 0;

    strbuff->value = malloc(strbuff->size);
    if(!strbuff->value)
        return -1;

    /* initialize to empty */
    strbuff->value[0] = '\0';
    return 0;
}

void strbuffer_close(strbuffer_t *strbuff)
{
    if(strbuff->value)
        free(strbuff->value);

    strbuff->size = 0;
    strbuff->length = 0;
    strbuff->value = NULL;
}

int strbuffer_append_bytes(strbuffer_t *strbuff, const char *data, size_t size)
{
    if(size >= strbuff->size - strbuff->length)
    {
        size_t new_size;
        char *new_value;

        /* avoid integer overflow */
        if (strbuff->size > STRBUFFER_SIZE_MAX / STRBUFFER_FACTOR
            || size > STRBUFFER_SIZE_MAX - 1
            || strbuff->length > STRBUFFER_SIZE_MAX - 1 - size)
            return -1;

        new_size = max(strbuff->size * STRBUFFER_FACTOR,
                       strbuff->length + size + 1);

        new_value = malloc(new_size);
        if(!new_value)
            return -1;

        memcpy(new_value, strbuff->value, strbuff->length);

        free(strbuff->value);
        strbuff->value = new_value;
        strbuff->size = new_size;
    }

    memcpy(strbuff->value + strbuff->length, data, size);
    strbuff->length += size;
    strbuff->value[strbuff->length] = '\0';

    return 0;
}

char strbuffer_pop(strbuffer_t *strbuff)
{
    if(strbuff->length > 0) {
        char c = strbuff->value[--strbuff->length];
        strbuff->value[strbuff->length] = '\0';
        return c;
    }
    else
        return '\0';
}

int strbuffer_append_escaped_bytes(strbuffer_t *strbuff,const char *data, size_t size,const char *escapechars){
    int i,rc=0;
    for(i=0;rc == 0 && i<size;++i){
        if(strchr(escapechars,data[i]))
            rc = strbuffer_append(strbuff,"\\");

        if(rc == 0)
            strbuffer_append_bytes(strbuff,&data[i],1);
    }

    return rc;
}
