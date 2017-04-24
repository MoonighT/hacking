/** @file traceback.c
 *  @brief The traceback function
 *
 *  This file contains the traceback function for the traceback library
 *
 *  @author Harry Q. Bovik (hqbovik)
 *  @bug Unimplemented
 */

#include <stdio.h>
#include "traceback_internal.h"
#include "traceback_assist.h"

#define __DEBUG__

void traceback(FILE *fp)
{
	/* the following just makes a sample access to "functions" array. 
	 * note if "functions" is not referenced somewhere outside the 
	 * file that it's declared in, symtabgen won't be able to find
	 * the symbol. So be sure to always do something with functions */
    // get ebp and return addr
    int i;
    int j;
    int frame = getebp();
    for(i=0; i< FUNCTS_MAX_NUM; ++i) {
        if(functions[i].name[0] == '\0')
            break;
        fprintf(fp, "function %d = %s addr= %#x\n", i, functions[i].name, (int)functions[i].addr);
    }
    while(1) {
        #ifdef __DEBUG__
            fprintf(fp, "frameaddr=%#x\n", frame);
        #endif
        int retaddr = *((int*)(frame + sizeof(int)));
        frame = *(int *)frame;
        #ifdef __DEBUG__
            fprintf(fp, "oldframeaddr=%#x\n", frame);
            fprintf(fp, "retaddr=%#x\n", retaddr);
        #endif

        for(i=0; i< FUNCTS_MAX_NUM; ++i) {
            if(functions[i].name[0] == '\0')
                break;
            if((int)functions[i].addr > retaddr ) {
                fprintf(fp, "found a function name = %s\n", functions[i-1].name);
                for(j=0; j<ARGS_MAX_NUM; ++j) {
                    if(functions[i-1].args[j].name[0] == '\0') {
                        break;
                    }
                    fprintf(fp, "args name = %s\n", functions[i-1].args[j].name);
                }
                break;
            }
        }
        // if no symbals 
        if(functions[i].name == '\0' || i == FUNCTS_MAX_NUM)
            fprintf(fp, "Function %#x(...), in\n", retaddr);
    }
}


