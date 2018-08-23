#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

void doWrite( int fd, const char *buff, int len)
{
   size_t idx = 0;
   do{
       size_t wcnt = write(fd, buff + idx, len - idx);
       if(wcnt == -1){
            perror("write");
            return;
       }
       idx += wcnt;
   }while(idx<len);
}


void write_file(int fd,  const char *infile)
{

   int oflags, mode;
   oflags =O_RDONLY;
   mode = S_IRUSR | S_IWUSR;
   
   int read_file = open(infile, oflags, mode);
   if (read_file == -1){
      printf("%s: No such file or directory \n",
infile);
      exit(1);
   }

   //we need a buffer to hold the file
   char buff[1024];

   size_t rcnt;
   while ((rcnt = read(read_file,buff,
sizeof(buff)-1)) != 0){
        if (rcnt == -1){
                perror("read");
                return ; ?
        }
        doWrite(fd,buff,rcnt);
   }

   close(read_file);
}

int main(int argc, char **argv)
{
   if(argc < 3){
        printf("Usage: ./fconc infile1  infile 
[outfile (default:fconc.out)]\n ");
        exit(1);
   }

   int fd, oflags, mode;
   oflags = O_CREAT | O_WRONLY;
 // We didn't use O_TRUNC flag, since it produced 
 //a wrong output on input A B A
        
   mode =  S_IWUSR | S_IRUSR;

   if(argv[3] != NULL){
       fd = open(argv[3], oflags, mode);
   }
   else {
       fd = open("fconc.out", oflags, mode);
   }

   write_file(fd, argv[1]);
   write_file(fd, argv[2]);

   close(fd);
   return 0;
}
