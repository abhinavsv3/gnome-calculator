
/*  $Header$
 *
 *  Copyright (C) 2004-2008 Sami Pietila
 *  Copyright (c) 2008-2009 Robert Ancell
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 */

#ifndef MP_EQUATION_H
#define MP_EQUATION_H

#include "mp.h"

#define PARSER_ERR_INVALID          1
#define PARSER_ERR_TOO_LONG_NUMBER  2
#define PARSER_ERR_BITWISEOP        3
#define PARSER_ERR_MODULUSOP        4
#define PARSER_ERR_OVERFLOW         5
#define PARSER_ERR_UNKNOWN_VARIABLE 6
#define PARSER_ERR_UNKNOWN_FUNCTION 7
#define PARSER_ERR_INVALID_BASE     8

typedef struct MPEquationParserState MPEquationParserState;

/* State for parser */
struct MPEquationParserState {
    /* The numeric base (e.g 2, 8, 10, 16) */
    int base;

    /* The wordlength for binary operations in bits (e.g. 8, 16, 32) */
    int wordlen;
    
    /* Units for angles (e.g. radians, degrees) */
    MPAngleUnit angle_units;
    
    /* Function to get variable values */
    int (*get_variable)(MPEquationParserState *state, const char *name, MPNumber *z);
    
    /* Function to set variable values */
    void (*set_variable)(MPEquationParserState *state, const char *name, MPNumber *x);    

    /* Function to solve functions */
    int (*get_function)(MPEquationParserState *state, const char *name, const MPNumber *x, MPNumber *z);
    
    // FIXME: get_operator??

    /* Error returned from parser */
    int error;

    /* Value returned from parser */
    MPNumber ret;
};

int mp_equation_parse(const char *expression, MPNumber *result);
int _mp_equation_error(void *yylloc, MPEquationParserState *state, char *text);

#endif