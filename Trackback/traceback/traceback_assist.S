/**
 * @file traceback_assist.S
 * @brief functions that provide some hardware-related operations
 */


/* define the getesp and getebp labels so that they can be called from
 * other files (.c or .S) */

.global getebp

getebp:
	movl %ebp, %eax
	ret
