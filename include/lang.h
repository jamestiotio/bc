﻿/*
 * *****************************************************************************
 *
 * Copyright 2018 Gavin D. Howard
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * *****************************************************************************
 *
 * Definitions for program data.
 *
 */

#ifndef BC_LANG_H
#define BC_LANG_H

#include <stdbool.h>

#include <status.h>
#include <vector.h>
#include <num.h>

typedef enum BcInst {

	BC_INST_INC_PRE,
	BC_INST_DEC_PRE,
	BC_INST_INC_POST,
	BC_INST_DEC_POST,

	BC_INST_NEG,

	BC_INST_POWER,
	BC_INST_MULTIPLY,
	BC_INST_DIVIDE,
	BC_INST_MODULUS,
	BC_INST_PLUS,
	BC_INST_MINUS,

	BC_INST_REL_EQ,
	BC_INST_REL_LE,
	BC_INST_REL_GE,
	BC_INST_REL_NE,
	BC_INST_REL_LT,
	BC_INST_REL_GT,

	BC_INST_BOOL_NOT,
	BC_INST_BOOL_OR,
	BC_INST_BOOL_AND,

	BC_INST_ASSIGN_POWER,
	BC_INST_ASSIGN_MULTIPLY,
	BC_INST_ASSIGN_DIVIDE,
	BC_INST_ASSIGN_MODULUS,
	BC_INST_ASSIGN_PLUS,
	BC_INST_ASSIGN_MINUS,
	BC_INST_ASSIGN,

	BC_INST_NUM,
	BC_INST_VAR,
	BC_INST_ARRAY_ELEM,
	BC_INST_ARRAY,

	BC_INST_CALL,

	BC_INST_SCALE_FUNC,
	BC_INST_IBASE,
	BC_INST_SCALE,
	BC_INST_LAST,
	BC_INST_LENGTH,
	BC_INST_READ,
	BC_INST_OBASE,
	BC_INST_SQRT,

	BC_INST_PRINT,
	BC_INST_PRINT_POP,
	BC_INST_STR,
	BC_INST_PRINT_STR,

	BC_INST_JUMP,
	BC_INST_JUMP_ZERO,

	BC_INST_POP,

	BC_INST_RET,
	BC_INST_RET0,

	BC_INST_HALT,

#ifdef DC_ENABLED
	BC_INST_MODEXP,
	BC_INST_DIVMOD,

	BC_INST_EXECUTE,

	BC_INST_PRINT_STACK,
	BC_INST_CLEAR_STACK,
	BC_INST_STACK_LEN,
	BC_INST_DUPLICATE,
	BC_INST_SWAP,

	BC_INST_PUSH_VAR,
	BC_INST_COPY_TO_VAR,

	BC_INST_QUIT,
	BC_INST_NQUIT,

	BC_INST_INVALID = -1,
#endif // DC_ENABLED

} BcInst;

typedef struct BcEntry {

	char *name;
	size_t idx;

} BcEntry;

typedef struct BcAuto {

	char *name;
	bool var;

} BcAuto;

typedef struct BcFunc {

	BcVec code;
	BcVec labels;
	size_t nparams;
	BcVec autos;

} BcFunc;

typedef enum BcResultType {

	BC_RESULT_TEMP,

	BC_RESULT_VAR,
	BC_RESULT_ARRAY_ELEM,
	BC_RESULT_ARRAY,

	BC_RESULT_STR,

	BC_RESULT_IBASE,
	BC_RESULT_SCALE,
	BC_RESULT_LAST,

	// These are between to calculate ibase, obase, and last from instructions.
	BC_RESULT_CONSTANT,
	BC_RESULT_ONE,

	BC_RESULT_OBASE,

} BcResultType;

typedef union BcResultData {

	BcNum n;
	BcVec array;
	BcEntry id;

} BcResultData;

typedef struct BcResult {

	BcResultType t;
	BcResultData data;

} BcResult;

typedef struct BcInstPtr {

	size_t func;
	size_t idx;
	size_t len;

} BcInstPtr;

// ** Exclude start. **
BcStatus bc_func_init(BcFunc *f);
BcStatus bc_func_insert(BcFunc *f, char *name, bool var);
void bc_func_free(void *func);

BcStatus bc_array_init(BcVec *a, bool nums);
BcStatus bc_array_copy(BcVec *d, const BcVec *s);
// ** Exclude end. **

BcStatus bc_array_expand(BcVec *a, size_t len);

// ** Exclude start. **
void bc_string_free(void *string);

int bc_entry_cmp(const void *e1, const void *e2);
void bc_entry_free(void *entry);

BcStatus bc_result_copy(BcResult *d, BcResult *s);
void bc_result_free(void *result);
// ** Exclude end. **

#ifndef NDEBUG
extern const char bc_inst_chars[];
#endif // NDEBUG

#ifdef DC_ENABLED
extern const uint8_t dc_inst_noperands[];
extern const uint8_t dc_inst_nresults[];
#endif // DC_ENABLED

extern const char bc_func_main[];
extern const char bc_func_read[];

#endif // BC_LANG_H
