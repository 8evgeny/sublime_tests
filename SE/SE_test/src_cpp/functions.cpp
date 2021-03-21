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

char* hms_from_tjd(double tjd) {
  static char s[AS_MAXCH];
  double x;
  /* tjd may be negative, 0h corresponds to day number 9999999.5 */
  x = fmod(tjd, 1);     /* may be negative ! */
  x = fmod(x + 1.5, 1); /* is positive day fraction */
  sprintf(s, "%s ", hms(x * 24, BIT_LZEROES));
  return s;
}

char* hms(double x, int32 iflag) {
  static char s[AS_MAXCH], s2[AS_MAXCH], *sp;
  char* c = ODEGREE_STRING;
  x += 0.5 / 36000.0; /* round to 0.1 sec */
  strcpy(s, dms(x, iflag));
  sp = strstr(s, c);
  if (sp != NULL) {
    *sp = ':';
    strcpy(s2, sp + strlen(ODEGREE_STRING));
    strcpy(sp + 1, s2);
    *(sp + 3) = ':';
    *(sp + 8) = '\0';
  }
  return s;
}

char* dms(double xv, int32 iflg) {
  int izod;
  int32 k, kdeg, kmin, ksec;
  char* c = ODEGREE_STRING;
  char *sp, s1[50];
  static char s[50];
  int sgn;

  if (isnan(xv)) return "nan";

  if (xv >= 360 && !(iflg & BIT_ALLOW_361)) xv = 0;
  *s = '\0';
  if (iflg & SEFLG_EQUATORIAL) c = "h";
  if (xv < 0) {
    xv = -xv;
    sgn = -1;
  } else {
    sgn = 1;
  }
  if (iflg & BIT_ROUND_MIN) {
    if (!(iflg & BIT_ALLOW_361)) xv = swe_degnorm(xv + 0.5 / 60);
  } else if (iflg & BIT_ROUND_SEC) {
    if (!(iflg & BIT_ALLOW_361)) xv = swe_degnorm(xv + 0.5 / 3600);
  } else {
    /* rounding 0.9999999999 to 1 */
    if (output_extra_prec)
      xv += (xv < 0 ? -1 : 1) * 0.000000005 / 3600.0;
    else
      xv += (xv < 0 ? -1 : 1) * 0.00005 / 3600.0;
  }
  if (iflg & BIT_ZODIAC) {
    izod = (int)(xv / 30);
    if (izod == 12) izod = 0;
    xv = fmod(xv, 30);
    kdeg = (int32)xv;
    sprintf(s, "%2d %s ", kdeg, zod_nam[izod]);
  } else {
    kdeg = (int32)xv;
    sprintf(s, " %3d%s", kdeg, c);
  }
  xv -= kdeg;
  xv *= 60;
  kmin = (int32)xv;
  if ((iflg & BIT_ZODIAC) && (iflg & BIT_ROUND_MIN)) {
    sprintf(s1, "%2d", kmin);
  } else {
    sprintf(s1, "%2d'", kmin);
  }
  strcat(s, s1);
  if (iflg & BIT_ROUND_MIN) goto return_dms;
  xv -= kmin;
  xv *= 60;
  ksec = (int32)xv;
  if (iflg & BIT_ROUND_SEC) {
    sprintf(s1, "%2d\"", ksec);
  } else {
    sprintf(s1, "%2d", ksec);
  }
  strcat(s, s1);
  if (iflg & BIT_ROUND_SEC) goto return_dms;
  xv -= ksec;
  if (output_extra_prec) {
    k = (int32)(xv * 100000000);
    sprintf(s1, ".%08d", k);
  } else {
    k = (int32)(xv * 10000);
    sprintf(s1, ".%04d", k);
  }
  strcat(s, s1);
return_dms:;
  if (sgn < 0) {
    sp = strpbrk(s, "0123456789");
    *(sp - 1) = '-';
  }
  if (iflg & BIT_LZEROES) {
    while ((sp = strchr(s + 2, ' ')) != NULL) *sp = '0';
  }
  return (s);
}

void jd_to_time_string(double jut, char* stimeout) {
  double t2;
  t2 = jut + 0.5 / 3600000.0;             // rounding to millisec
  sprintf(stimeout, "  % 2d:", (int)t2);  // hour
  t2 = (t2 - (int32)t2) * 60;
  sprintf(stimeout + strlen(stimeout), "%02d:", (int)t2);  // min
  t2 = (t2 - (int32)t2) * 60;
  sprintf(stimeout + strlen(stimeout), "%02d", (int)t2);  // sec
  t2 = (t2 - (int32)t2) * 1000;
  if ((int32)t2 > 0) {
    sprintf(stimeout + strlen(stimeout), ".%03d", (int)t2);  // millisec, if > 0
  }
}

int32 call_swe_fixstar(char* star, double te, int32 iflag, double* x,
                       char* serr) {
  if (use_swe_fixstar2)
    return swe_fixstar2(star, te, iflag, x, serr);
  else
    return swe_fixstar(star, te, iflag, x, serr);
}
