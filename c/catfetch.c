// NOT FOR PRODUCTION
// SIMPLE NEOFETCH LIKE TOOL I C

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *run_cmd(char *cmd){
    FILE *pp=popen(cmd, "r");
    if(!pp) return NULL;

    char *output=NULL;
    size_t size=0;

    getline(&output, &size, pp);
    pclose(pp);

    output[strcspn(output, "\n")]='\0';

    return output;
}

int main(){



    char *gulabi="\e[35m";
    char *hara="\e[32m";
    char *safed="\e[0m";


    char *os=run_cmd("uname -o");
    char *krnl=run_cmd("uname -r");
    char *mchn=run_cmd("uname -m");
    char *uptm=run_cmd("uptime -s");
    char *pkgs=run_cmd("dpkg-query -f '${Package}\n' -W | wc -l");
    char *mem=run_cmd("free -m | awk '/^Mem:/ {print $3 \"MiB / \" $2 \"MiB\"}'");
    char *shl=run_cmd("echo ${SHELL##*/}");

    char *text[]={
        "OS",
        "KERNEL",
        "MACHINE",
        "UPTIME",
        "PACKAGES",
        "MEMORY",
        "SHELL"
    };

    char *logo[]={
        "    /\\_____/\\     ",
        "   /  o   o  \\    ",
        "  ( ==  ^  == )   ",
        "   )         (    ",
        "  (           )   ",
        " ( (  )   (  ) )  ",
        "(__(__)___(__)__) "
    };

    char *tinfo[]={
        os,
        krnl,
        mchn,
        uptm,
        pkgs,
        mem,
        shl
    };


    for (int i=0; i<7; i++){
        printf("%s%s %s%s %s%s\n", gulabi,logo[i], hara,text[i], safed,tinfo[i]);
    }

    free(os); free(krnl); free(mchn);
    free(uptm); free(pkgs); free(mem);
    free(shl);
    return 0;
}
