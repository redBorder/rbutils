/*
 * Copyright (c) 2014 Eneo Tecnologia S.L.
 * Author: Eugenio Perez <eupm90@gmail.com>
 * Based on Petri Lehtinen <petri@digip.org> jansson library strbuffer 
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#pragma once

#include <string.h>

#define RB_UNUSED __attribute__((unused))

typedef struct {
    char *value;
    size_t length;   /* bytes used */
    size_t size;     /* bytes allocated */
} strbuffer_t;

int strbuffer_init(strbuffer_t *strbuff);
void strbuffer_close(strbuffer_t *strbuff);

static void strbuffer_clear(strbuffer_t *strbuff) RB_UNUSED;
static void strbuffer_clear(strbuffer_t *strbuff){
	strbuff->length = 0;
	strbuff->value[0] = '\0';
}

#define strbuffer_value(strbuff) ((strbuff)->value)
#define strbuffer_length(strbuff) ((strbuff)->length)

/* Steal the value and close the strbuffer */
static char *strbuffer_steal_value(strbuffer_t *strbuff) RB_UNUSED;
static char *strbuffer_steal_value(strbuffer_t *strbuff){
	char *result = strbuff->value;
	strbuff->value = NULL;
	return result;
}

int strbuffer_append_bytes(strbuffer_t *strbuff, const char *data, size_t size);

#define strbuffer_append(strbuff, string) strbuffer_append_bytes(strbuff,string,strlen(string))
#define strbuffer_append_byte(strbuff, byte) strbuffer_append_bytes(strbuff,&(byte),1);

int strbuffer_append_escaped_bytes(strbuffer_t *strbuff,const char *data, size_t size, const char *escapechars);

#define strbuffer_append_escaped(strbuff,data,escapefn) \
	strbuffer_append_escaped_bytes(strbuff,data,strlen(data),escapefn)

char strbuffer_pop(strbuffer_t *strbuff);

