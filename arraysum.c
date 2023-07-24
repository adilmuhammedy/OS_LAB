#include<stdio.h>
#include<unistd.h>
int main(){
    int fd1[2];
    int fd2[2];
    if(pipe(fd1)==-1||pipe(fd2)==-1){
        printf("Error pipe");
    }
    int pid=fork();
    if(pid<0){
        printf("Error pipe");
    }
    if(pid==0){
        close(fd1[1]);
        close(fd2[1]);
        printf("Child Process");
        int sizeparent;
        read(fd1[0],&sizeparent,sizeof(int));
        int arrayparent[sizeparent];
        read(fd2[0],arrayparent,sizeof(arrayparent));
        int sum=0;
        for(int i=0; i<sizeparent; i++){
            sum=sum+arrayparent[i];
        }
        printf("\nSum of array: %d", sum);
        
    }
    else{
        close(fd1[0]);
        close(fd2[0]);
        printf("Parent Process");
        printf("\nEnter size of the array: ");
        int sizechild;
        scanf("%d", &sizechild);
        int arrayc[sizechild];
        printf("Enter array elements: ");
        for(int i=0; i<sizechild; i++){
            scanf("%d", &arrayc[i]);
        }
        write(fd1[1],&sizechild,sizeof(int));
        write(fd2[1], arrayc,sizeof(arrayc));
    }
}
