#include <stdio.h>//printf()
#include <stdlib.h>//exit()
#include <string.h>//perror(),strlen()
#include <sys/wait.h>//waitpid()
#include <unistd.h>//fork()

#define MAX_LEN 100 /* The maximum length command */

int main(void) {
  char *args[MAX_LEN / 2 + 1]; /* command line arguments */
  int should_run = 1;  /* flag to determine when to exit program */
  int background = 0;
  char *input;

while (should_run){
exit:
	printf("my_shell> ");
	fflush(stdout);
    // 표준입출력으로부터 문자열을 입력 받은 후:
    // * (1) fork()를 통해 자식 프로세스를 생성
    // * (2) 자식 프로세스가 execvp()를 호출하도록 할 것
    // * (3) 만약 입력받은 문자에 &가 포함되어 있으면,
    // *     부모 프로세스는 wait() 호출하지 않음

	input = (char *)malloc(MAX_LEN * sizeof(char));
	fgets(input, MAX_LEN, stdin);
	args[0]=strtok(input," \n");
	int i=0;
	if(args[0]==NULL){
		goto exit;
	}
	while(args[i] != NULL){
		i++;
		args[i] = strtok(NULL, " \n");
	}

	if(strcmp(args[0],"exit")==0){
		exit(0);
	}
	if(strcmp(args[i-1],"&")==0){
		printf("background process\n");
		background=1;

	}
	pid_t pid = fork();
    	if(pid<0){
		perror("fork error");
	}
	else if(pid==0){
		printf("wating for a child, not background process\n");
		execvp(args[0],args);
	}
	else if(pid>0){
		if(background == 1){
		int *status;
		waitpid(pid,status,WNOHANG);
		background=0;
		}
		
		else{
		wait(NULL);
		printf("child complete\n");	
		}
	}


}//while(should run)

return 0;

}

