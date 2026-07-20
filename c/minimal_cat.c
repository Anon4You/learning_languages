// NOT FOR PRODUCTION
// MINIMAL CAT COMMAND IN C

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv){

    FILE *fp;
    fp=stdin;
    if(argc>1) fp=fopen(argv[1], "r");
    if(!fp){
        perror(argv[1]);
        return 1;
    }

    char *line=NULL;
    size_t size=0;

    while(getline(&line, &size, fp)!=-1){
        printf("%s", line);
    }

    free(line);
    fclose(fp);
    return 0;

}
