// Not ready for productions
// minimal ls in c using termux

#include <bits/getopt.h>
#include <linux/limits.h>
#include <linux/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>


void str_mod(mode_t m, char *s){

    strcpy(s,"----------");

    if(S_ISDIR(m)) s[0]='d';
    else if(S_ISBLK(m)) s[0]='b';
    else if(S_ISLNK(m)) s[0]='l';
    else if(S_ISFIFO(m)) s[0]='p';
    else if(S_ISSOCK(m)) s[0]='s';
    else if(S_ISCHR(m)) s[0]='c';

    if(m & S_IRUSR) s[1]='r';
    if(m & S_IWUSR) s[2]='w';
    if(m & S_IXUSR) s[3]='x';

    if(m & S_IRGRP) s[4]='r';
    if(m & S_IWGRP) s[5]='w';
    if(m & S_IXGRP) s[6]='x';

    if(m & S_IROTH) s[7]='r';
    if(m & S_IWOTH) s[8]='w';
    if(m & S_IXOTH) s[9]='x';
}



void lngprnt(char *path, char *name){
    char fullpath[PATH_MAX];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, name);

    struct stat st;
    if(lstat(fullpath, &st)) return; 

    char prms[11];
    str_mod(st.st_mode, prms);

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gp = getgrgid(st.st_gid);

    char *owner = pw ? pw->pw_name : "unkn";
    char *group = gp ? gp->gr_name : "unkn";


    char tmbufff[64];
    strftime(tmbufff, sizeof(tmbufff), "%a %b %d %H:%M", localtime(&st.st_mtime));


    printf("%s %3ld %s %s %6ld %s %s\n", prms, (long)st.st_nlink, owner, group, st.st_size, tmbufff, name);
    
}

int main(int argc, char **argv){
    int opt;
    int show_all=0; 
    int show_lng=0;

    while((opt=getopt(argc, argv, "al"))!=-1){
        switch (opt){
            case 'a':
                show_all = 1;
                break;
            case 'l':
                show_lng = 1;
                break;
            default:
                fprintf(stderr, "Usage %s <-a/-l> <path>\n", argv[0]);
                return 1;
        }
    }

    char *path=(optind<argc) ? argv[optind] : ".";

    DIR *d=opendir(path);
    if(!d){
        perror(path);
        return 1;
    }
    

    for (struct dirent *e; (e=readdir(d));){
        if(show_all || e->d_name[0] != '.')
       show_lng ? lngprnt(path, e->d_name) : printf("%s  ",e->d_name);
    }

    if(!show_lng) printf("\n");
    closedir(d);
    return 0;
}
