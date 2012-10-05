#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#define success 0
#define failure 1

#define ERROR_MESSAGE_MAX_SIZE  256

int printDirectory(const char* directory);
int printDirectoryStats(const char* directory);
int printFile(const char* target);
void printDirectoryError(const char* directory);

char* globalErrorMessage = NULL;

int main(int argc, char* argv[]) {

  const char* directory = argc > 1 ? argv[1] : ".";
  bool isfile = true; 
 
  if(printFile(directory) != success) {
    check = false;
  }  

  if(printDirectoryStats(directory) != success && !check) {
    printDirectoryError(directory);
    return failure;
  }
  
  return success;
}

void printDirectoryError(const char* directory) { 
  char buffer[ERROR_MESSAGE_MAX_SIZE];
  snprintf(buffer, sizeof(buffer)-1, "Directory: '%s' has error %s\n", directory, globalErrorMessage);
  perror(buffer);
}

int printFile(const char* target) {
  DIR* current = opendir(".");
  
  struct dirent* fileEntry;
  while((fileEntry = readdir(current)) != NULL) {
    if(!strcmp(target, fileEntry->d_name)) { 
      struct stat entryDetails;
      if(stat(fileEntry->d_name, & entryDetails) != success) {
        globalErrorMessage = "Unable to get data";
	closedir(current);
	return failure;
      }
      printf("%10lld B %20s", (long long)entryDetails.st_size, fileEntry->d_name);
    }
  }  
  return success;
}

int printDirectoryStats(const char* directory) 
{
  DIR* current = opendir(directory);

  if (current == NULL) {
    globalErrorMessage = "Unable to open the selected directory";
    return failure;
  }

  struct dirent* directoryEntry;
  while ((directoryEntry = readdir(current)) != NULL) {
    struct stat entryDetails;
    if (stat(directoryEntry->d_name, &entryDetails) != success) {
      globalErrorMessage = "Failed to obtain stats information";
      return failure;
    }

    printf("Entry: %25s - %10lld b \n", directoryEntry->d_name, (long long)entryDetails.st_size);
  }

  return success;
}
