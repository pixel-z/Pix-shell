#include "header.h"

ll tp=0; // exit code

void print_permissions(struct stat s)
{
    char perm[1024];
    ll i=0;

    if(S_ISDIR(s.st_mode)) perm[i++]='d';
    else perm[i++]='-';

    //user
    if ((s.st_mode & S_IRUSR) != 0) perm[i++]='r';
    else perm[i++]='-';
    if ((s.st_mode & S_IWUSR) != 0) perm[i++]='w';
    else perm[i++]='-';
    if ((s.st_mode & S_IXUSR) != 0) perm[i++]='x';
    else perm[i++]='-';

    //grp
    if ((s.st_mode & S_IRGRP) != 0) perm[i++]='r';
    else perm[i++]='-';
    if ((s.st_mode & S_IWGRP) != 0) perm[i++]='w';
    else perm[i++]='-';
    if ((s.st_mode & S_IXGRP) != 0) perm[i++]='x';
    else perm[i++]='-';
    
    //others
    if ((s.st_mode & S_IROTH) != 0) perm[i++]='r';
    else perm[i++]='-';
    if ((s.st_mode & S_IWOTH) != 0) perm[i++]='w';
    else perm[i++]='-';
    if ((s.st_mode & S_IXOTH) != 0) perm[i++]='x';
    else perm[i++]='-';
    
    perm[i]='\0';
    printf("%s\t",perm);

    return;
}

// no of directories = n
void ls_a(char **dir_address, ll n)
{
    DIR *directory;
    for (ll i = 0; i < n; i++)
    {
        directory=opendir(dir_address[i]);
        if (directory == NULL)
        {
            printf("%s: No such file or directory\n",dir_address[i]);
            tp=1;
            continue;
        }
        
        struct dirent *dir;
        // everytime goes to next content in that directory
        while ((dir=readdir(directory)) != NULL)
        {
            printf("%s   ",dir->d_name);
        }
        closedir(directory);
    }
    printf("\n");
    return;
}

void ls_l(char **dir_address, ll n)
{
    DIR *directory;
    for (ll i = 0; i < n; i++)
    {
        directory=opendir(dir_address[i]);
        if (directory == NULL)
        {
            printf("%s: No such file or directory\n",dir_address[i]);
            tp=1;
            continue;
        }
        printf("Contents:\n");
        
        struct dirent *dir;
        struct passwd *pass;
        struct group *grp;
        struct tm *time;
        // everytime goes to next content in that directory
        while ((dir=readdir(directory)) != NULL)
        {
            if(dir->d_name[0] == '.') continue;

            char *buf=(char *)malloc(1024*sizeof(char));
            struct stat s;

            sprintf(buf,"%s/%s",dir_address[i],dir->d_name);
            stat(buf,&s);

            //permissions
            print_permissions(s);

            // link count
            printf("%lu\t",s.st_nlink);

            // owner of file/direc
            printf("%s\t",getpwuid(s.st_uid)->pw_name);
            
            //usergroup of file/direc
            printf("%s\t",getgrgid(s.st_gid)->gr_name);
            
            // size
            printf("%ld\t",s.st_size);

            //date & time 
            char datetime[1024];
            strftime(datetime,50,"%b %d %H:%M",localtime(&s.st_mtime));
            printf("%s\t",datetime);

            // file name
            printf("%s\n",dir->d_name);
        }
        closedir(directory);
    }
    return;
}

void ls_l_a(char **dir_address, ll n)
{
    DIR *directory;
    for (ll i = 0; i < n; i++)
    {
        directory=opendir(dir_address[i]);
        if (directory == NULL)
        {
            printf("%s: No such file or directory\n",dir_address[i]);
            tp=1;
            continue;
        }
        printf("Contents:\n");
        
        struct dirent *dir;
        struct passwd *pass;
        struct group *grp;
        struct tm *time;
        // everytime goes to next content in that directory
        while ((dir=readdir(directory)) != NULL)
        {
            char *buf=(char *)malloc(1024*sizeof(char));
            struct stat s;

            sprintf(buf,"%s/%s",dir_address[i],dir->d_name);
            stat(buf,&s);

            //permissions
            print_permissions(s);

            // link count
            printf("%lu\t",s.st_nlink);

            // owner of file/direc
            printf("%s\t",getpwuid(s.st_uid)->pw_name);
            
            //usergroup of file/direc
            printf("%s\t",getgrgid(s.st_gid)->gr_name);
            
            // size
            printf("%ld\t",s.st_size);

            //date & time 
            char datetime[1024];
            strftime(datetime,50,"%b %d %H:%M",localtime(&s.st_mtime));
            printf("%s\t",datetime);

            // file name
            printf("%s\n",dir->d_name);
        }
        closedir(directory);
    }
    return;
}

ll LS(char **com)
{
    ll l=0,a=0,flag=0;
    char **dir_address=(char **)malloc(sizeof(char *)*1024);
    tp=0;

    ll i=1,j=0; // j = no of directories whose ls is to be performed
    while(com[i]!=NULL)
    {
        if(strcmp(com[i], "-l")==0) l=1;
        else if(strcmp(com[i], "-a")==0) a=1;
        else if(strcmp(com[i], "-la")==0 || strcmp(com[i], "-al")==0) l=1,a=1;
        else
        {
            char *path=(char *)malloc(sizeof(char)*1024);
            path = actual_path(com[i]);
            flag=1;
            dir_address[j]=path;
            dir_address[j][strlen(path)]='\0';
            j++;
        }
        i++;
    }

    // if no directory is given then cwd is directory 
    if (flag==0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        dir_address[j]=cwd;
        dir_address[j][strlen(cwd)]='\0';
        j++;
    }
    if (l==1 && a==1) ls_l_a(dir_address,j);
    else if (l==1) ls_l(dir_address,j);
    else if (a==1) ls_a(dir_address,j);
    else 
    {
        // no flags 
        DIR *directory;
        for (ll i = 0; i < j; i++)
        {
            directory=opendir(dir_address[i]);
            if (directory == NULL)
            {
                perror("dir error");
                tp=1;
                continue;
            }
            
            struct dirent *dir;
            // everytime goes to next content in that directory
            while ((dir=readdir(directory)) != NULL)
            {
                if (dir->d_name[0] == '.')
                    continue;
                
                printf("%s   ",dir->d_name);
            }
            closedir(directory);
        }
        printf("\n");
    }

    return tp;
}