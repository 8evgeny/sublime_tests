#include "main.h"

char* our_strcpy(char* to, char* from) {
  char *sp, s[AS_MAXCH];
  if (*from == '\0') {
    *to = '\0';
    return to;
  }
  if (strlen(from) < AS_MAXCH) {
    strcpy(s, from);
    strcpy(to, s);
  } else {
    sp = strdup(from);
    if (sp == NULL) {
      strcpy(to, from);
    } else {
      strcpy(to, sp);
      free(sp);
    }
  }
  return to;
}

void remove_whitespace(char* s) {
  char *sp, s1[AS_MAXCH];
  if (s == NULL) return;
  for (sp = s; *sp == ' '; sp++)
    ;
  strcpy(s1, sp);
  while (*(sp = s1 + strlen(s1) - 1) == ' ') *sp = '\0';
  strcpy(s, s1);
}

int make_ephemeris_path(char* argv0, char* path) {
  /* make_ephemeris_path().
   * ephemeris path includes
   *   current working directory
   *   + program directory
   *   + default path from swephexp.h on current drive
   *   +                              on program drive
   *   +                              on drive C:
   */

  char* sp;
  char* dirglue = DIR_GLUE;
  size_t pathlen = 0;
  /* current working directory */
  sprintf(path, ".%c", *PATH_SEPARATOR);
  /* program directory */
  sp = strrchr(argv0, *dirglue);
  if (sp != NULL) {
    pathlen = sp - argv0;
    if (strlen(path) + pathlen < AS_MAXCH - 2) {
      strncat(path, argv0, pathlen);
      sprintf(path + strlen(path), "%c", *PATH_SEPARATOR);
    }
  }

  if (strlen(path) + strlen(SE_EPHE_PATH) < AS_MAXCH - 1)
    strcat(path, SE_EPHE_PATH);

  return OK;
}

void do_printf(char* info) {
#ifdef _WINDOWS
  fprintf(fp, info);
#else
  fputs(info, stdout);
#endif
}
