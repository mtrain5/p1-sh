#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


// Given a message as input, print it to the screen followed by a
// newline ('\n'). If the message contains the two-byte escape sequence
// "\\n", print a newline '\n' instead. No other escape sequence is
// allowed. If the sequence contains a '$', it must be an environment
// variable or the return code variable ("$?"). Environment variable
// names must be wrapped in curly braces (e.g., ${PATH}).
//
// Returns 0 for success, 1 for errors (invalid escape sequence or no
// curly braces around environment variables).
int echo(char *message) 
{
    if (message == NULL) {
        return 1;
    }
    int i = 0;
    while (message[i] != '\0') {
        if (message[i] == '\\' && message[i + 1] == 'n') {
            printf("\n");
            i += 2;
        }
        else if (message[i] == ' ' && message[i + 1] == ' ') //check for the extra spaces
        { 
          printf(" "); //regular space
          while (message[i] == ' '){
            i++; //skip until its not spaces
          }
        }
        else {
            printf("%c", message[i]);
            i++;
        }
    }
    return 0;
}

// Given a key-value pair string (e.g., "alpha=beta"), insert the mapping
// into the global hash table (hash_insert ("alpha", "beta")).
//
// Returns 0 on success, 1 for an invalid pair string (kvpair is NULL or
// there is no '=' in the string).
int
export (char *kvpair)
{
  return 0;
}

// Prints the current working directory (see getcwd()). Returns 0.
int
pwd (void)
{
  //Might have to add some type of error checking
  char *buffer;
  buffer = (char *) calloc (100, sizeof (char));
  getcwd (buffer, 100);
  printf ("%s\n", buffer);
  free (buffer);
  return 0;
}

// Removes a key-value pair from the global hash table.
// Returns 0 on success, 1 if the key does not exist.
int
unset (char *key)
{
  return 0;
}
int
checkExecutable(const char* path){
  return access (path, X_OK) == 0;
}

// Given a string of commands, find their location(s) in the $PATH global
// variable. If the string begins with "-a", print all locations, not just
// the first one.
//
// Returns 0 if at least one location is found, 1 if no commands were
// passed or no locations found.
int
which (char *cmdline)
{
  if (cmdline == NULL || strlen (cmdline) == 0){
    return 1;
  }
  char *token = strtok(cmdline, " ");
  while (token != NULL) {
      token[strcspn(token, "\n")] = '\0';
      if (strncmp(token, "cd", 2) == 0 || strncmp(token, "echo", 4) == 0 || strncmp(token, "pwd", 3) == 0 || strncmp(token, "which", 5) == 0) {
        printf("%s: dukesh built-in command\n", token);
      }
      else if (strncmp (token, "./", 2) == 0){
        if (checkExecutable (token)){
          printf("%s\n", token);
          return 0;
        }
        // printf ("%s\n", cmdline);
        //return 0;
      }
      else
      {
        char *path = getenv ("PATH");
        if (path != NULL){
          char *pathCopy = strdup (path);
          char *dir = strtok (pathCopy, ":");
          while (dir != NULL){
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, token);
            if (checkExecutable(fullPath)){
              printf("%s\n", fullPath);
              return 0;
            }
            dir = strtok(NULL, ":");
          }
          free (pathCopy);
          
        }
        return 1;
      } 
      

      token = strtok(NULL, " ");
  }

  return 0;
  }



int
cd (char *message)
{
  size_t len = strlen (message);
  if (isspace(message[len-1]))
  {
    message[len-1] = '\0';
  }
  if (chdir(message) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
