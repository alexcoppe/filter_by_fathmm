/*
 * Author: Alessandro Coppe
 * Purpose: retrive the dbNSFP FATHMM rank score from an annotated VCF
 * Language: C
 * 
 *  (c) 2019 Coppe
 *  This code is licensed under MIT license (see LICENSE.txt for details)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


float dbNSFP_FATHMM(const char *line){
    float float_score = 0;
    char *substring;
    char score[10];
    char only_number_scores[10];

    char *vcf_line = (char *) malloc(strlen(line));

    memcpy(vcf_line, line, strlen(line));


    if (vcf_line[0] != '#') {
        substring = strstr(vcf_line, "dbNSFP_FATHMM_rankscore=");
        if (substring != NULL) {
            substring += 24;
            memcpy(score, substring, 7);
            float_score = atof(score);
            if (score[0] == '.') {
                strncpy(only_number_scores, score + 2, 10);
                float_score = atof(only_number_scores);
            }
        }  else {
            float_score = 1;
        }
    }

    free(vcf_line);

    return float_score;
}
