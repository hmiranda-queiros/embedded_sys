/*
 * memory_access.h
 *
 *  Created on: 31 d�c. 2021
 *      Author: hugom
 */

#ifndef MEMORY_ACCESS_H_
#define MEMORY_ACCESS_H_

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "system.h"

#define HPS_0_BRIDGES_BASE (0x00000000)				/* address_span_expander base address from system.h (ADAPT TO YOUR DESIGN) */
#define HPS_0_BRIDGES_SPAN (2 * 1024 * 1024) 		/* address_span_expander span from system.h (ADAPT TO YOUR DESIGN) */

#define ONE_MB (1024 * 1024)

int read_memory(void);


#endif /* MEMORY_ACCESS_H_ */