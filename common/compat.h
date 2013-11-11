/*
 * compat.h
 *
 *  Created on: 9-nov.-2013
 *      Author: vincent
 */

#ifndef COMPAT_H_
#define COMPAT_H_

#include "config.h"

#ifdef HAVE_SYS_TYPES_H
#   include <sys/types.h>
#else
	//no sys/types.h
	//define them ourselves or throw a compilation error (ok for now)
#   error "Can't compile; sys/types.h is not available"
#endif

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#else
	typedef unsigned char u_char_t;
	typedef unsigned char u_int8_t;
	typedef unsigned short u_int16_t;
	typedef unsigned int u_int32_t;

#endif

#endif /* COMPAT_H_ */
