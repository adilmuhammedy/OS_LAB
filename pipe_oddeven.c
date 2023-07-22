#include<stdio.h>
#include<unistd.h>

int main(){
    int fd[2];
    int fd2[2];
    int num;
    int arr[50];
    
    if(pipe(fd)==-1 || pipe(fd2)==-1){
        printf("pipe creation failed");
    }
    else{
        printf("pipe connection successful");
    }
    
    int pid=fork();
    if(pid<0)
    printf("Error creating fork");
    if(pid==0){
        printf("Child Process\n");
        close(fd[0]);
        close(fd2[0]);
        printf("Enter number of elements you want to send from child to parent: \n");
        scanf("%d",&num);
        printf("Enter the numbers: ");
        for(int i=0; i<num; i++){
            scanf("%d", &arr[i]);
        }
        write(fd2[1],&num,sizeof(int));
        write(fd[1],&arr,num*sizeof(int));
    }
    else{
        // sleep(10);
        printf("Parent process\n");
        close(fd[1]);
        close(fd2[1]);
        read(fd2[0],&num,sizeof(int));
        read(fd[0],&arr,num*sizeof(int));
        printf("Even Numbers recieved from child process are: ");
          for(int i=0; i<num; i++){
              if(arr[i]%2==0){
                  printf("%d\t",arr[i]);
              }
        }
        printf("Odd Numbers recieved from child process are: ");
          for(int i=0; i<num; i++){
              if(arr[i]%2!=0){
                  printf("%d\t",arr[i]);
              }
        }
        
    }
}
