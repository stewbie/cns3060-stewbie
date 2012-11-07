#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

struct termios backup;
FILE* file;

int inputSize(FILE*);
void set(struct termios);
void cleanup();
void interrupt();

int main (char argc,char* argv[]) {
  FILE* input;
  int c = 0;
  struct termios termSettings;
  char* line;
  int i,done = 0;
  size_t len = 0;
  ssize_t reader;

  if (argc < 2) {
    input = stdin;
    printf("\033[7mbytes: %u\033[m\n",inputSize(input));
    exit(0);
  }

  if ((tcgetattr(0,&termSettings)) == -1) {
    perror("tcgetattr error\n");
    exit(1);
  }

  if(!(file = fopen(argv[1], "r"))) {
    printf("error opening file.\n");
    exit(1);
  }
  backup = termSettings;
  atexit(cleanup);
  signal(SIGINT, interrupt);

  termSettings.c_lflag &= ~(ICANON|ECHO); 
  termSettings.c_cc[VMIN] = 1;
  termSettings.c_cc[VTIME] = 0;
  set(termSettings);

  reader = getline(&line, &len, file);
  if(reader == -1)
    return 0;
  printf("%s",line);
  for(i = 0; i < 22 && line != 0;i++) {
    reader = getline(&line, &len, file);
    if (reader == -1)
      return 0;
    printf("%s",line);
  }

  while(1) {
    read (0,&c,1);
    if (c == 113)
      break;
    if (c == 10) { //enter key
      reader = getline(&line, &len, file);
      if (reader == -1)
        break;
      printf("%s\n",line);
      printf("\r\033[7m%u%%\033[m\r",12);
    }
    else if (c == 32) { //space bar
      reader = getline(&line, &len, file);
      if (reader == -1)
        break;
      printf("\r");
      printf("%s",line);
      for (i = 0; i < 22 && line != 0;i++) {
        reader = getline(&line, &len, file);
        if (reader == -1) {
          done = 1;
          break;
        }
        printf("%s", line);
      }
      if (done)
        break;
    }
  }
  if (line)
    free(line);
  return 0;
}

void interrupt() {
  cleanup();
  printf("Restored terminal settings, now terminating program.\n");
  exit(1);
}

int inputSize(FILE* input) {
  int c,retvalue = 0;
  while (EOF != (c = fgetc(input)))
    retvalue++;
  return retvalue;
}
void cleanup(void) { 
    fclose(file);
    tcsetattr(0, TCSANOW, &backup);
}

void set(struct termios termSettings) {
  if(tcsetattr(0,TCSANOW,&termSettings) == -1) {
    perror("tcsetattr error\n");
    exit(1);
  }
}
