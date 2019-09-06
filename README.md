# filter_by_fathmm

#### :pill: Filter an annotated VCF based on FATHMM_rankscore from dbNSF

Filter an annotated VCF file based on FATHMM_rankscore obtained from [dbNSF](https://sites.google.com/site/jpopgen/dbNSFP). The input VCF should be annotated using [SnpSift](http://snpeff.sourceforge.net/SnpSift.html) and the dbNSFP gz file.
Sample command:

```
java -jar /usr/local/snpEff/SnpSift.jar dbnsfp -v -db dbNSFP2.9.3_lite.txt.gz -f MetaSVM_pred,MetaLR_pred,FATHMM_pred,FATHMM_rankscore
```

### Compiling the software

Download the software from [github](https://github.com/alexcoppe/filter_by_fathmm), enter the directory and compile it with:
```
gcc -o filter_by_FATHMM fathmm.c filter_by_FATHMM.c
```

### Getting help

To get the help just launch the program with the -h option:

```
./filter_by_FATHMM -h
Usage: filter_by_FATHMM  [OPTION]... VCF_file
  -s	Functional scores for individual mutations from FATHMM-MKL to pass the filter (>= 0.7)
  -h	show help options
```
