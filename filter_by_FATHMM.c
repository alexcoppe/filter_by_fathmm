/*
 * Author: Alessandro Coppe
 * Purpose: filter an annotated VCF file based on dbNSFP_FATHMM_rankscore 
 * Language: C
 * 
 *  (c) 2019 Coppe
 *  This code is licensed under MIT license (see LICENSE.txt for details)
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"fathmm.h"


int main(int argc, char *argv[]){
    char ch;
    int exit = 0;
    FILE *vcf;
    const int LONGEST_LINE = 9000;
    char line[LONGEST_LINE];
    float float_score;
    float fathmm;
    float min_FATHMM = 0.7;
    /* Help string */
    char help[] = "Usage: filter_by_FATHMM  [OPTION]... VCF_file\n  "
        "-s\tFunctional scores for individual mutations from FATHMM-MKL to pass the filter (>= 0.7)\n  "
        "-h\tshow help options";

    /* Options section */
    while ((ch = getopt(argc, argv, "sh")) != EOF) {
        switch (ch) {
            case 's':
                break;
            case 'h':
                exit = 1;
                puts(help);
                return 0;
            default:
                return -1;
        }
    }

    argc -= optind;
    argv += optind;
    /* Options end */

    /* Check if there is a VCF file argument */
    if (argc < 1) {
        fprintf(stderr, "VCF file name not specified\n");
        return 1;
    }

    /* If the VCF file is not present */
    if (!(vcf = fopen(argv[0], "r"))) {
        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
        return 1;
    }


    /* Working part */
    while (fgets(line, LONGEST_LINE, vcf) != NULL){
        if (line[0] == '#') {
            printf("%s", line);
        } else {
            fathmm = dbNSFP_FATHMM(line);
            if (fathmm >= min_FATHMM)
                fprintf(stdout, "%s", line);
        }
    }
 
}
