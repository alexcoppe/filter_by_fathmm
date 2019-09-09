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
#include<getopt.h>
#include<ctype.h>
#include"fathmm.h"


int main(int argc, char *argv[]){
    char c;
    FILE *vcf;
    const int LONGEST_LINE = 9000;
    char line[LONGEST_LINE];
    float fathmm;
    float min_FATHMM = 0.7;
    char *sflag = NULL;
    int hflag = 0;
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    float functional_score = 0.7;

    /* Help string */
    char help[] = "Usage: filter_by_FATHMM  [OPTION]... VCF_file\n  "
        "-s\tFunctional scores for individual mutations from FATHMM-MKL to pass the filter (>= 0.7)\n  "
        "-h\tshow help options";

    while ((c = getopt (argc, argv, "hs:")) != -1)
        switch (c) {
            case 'h':
                hflag = 1;
                puts(help);
                break;
            case 's':
                sflag = optarg;
                break;
            case '?':
                if (optopt == 's')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }

    if (sflag != NULL) {
        functional_score = atof(sflag);
    } else {
        functional_score = 0.7;
    }

    if (functional_score == 0) {
        fprintf(stderr, "Not a numeric value for -s option\n");
        return -1;
    }


    if (functional_score >= 1 || functional_score <= 0) {
        fprintf(stderr, "The -s option cannot be <= 0  and >= 1\n");
        return -1;
    }

    argc -= optind;
    argv += optind;


    /* Check if there is a VCF file argument */
    if (argc < 1) {
        fprintf(stderr, "VCF file name not specified\n");
        return 1;
    }

    /*If the VCF file is not present */
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
            if (fathmm >= functional_score)
                fprintf(stdout, "%s", line);
        }
    }
 
}
