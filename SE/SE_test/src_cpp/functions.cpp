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

int letter_to_ipl(int letter) {
  if (letter >= '0' && letter <= '9') return letter - '0' + SE_SUN;
  if (letter >= 'A' && letter <= 'I') return letter - 'A' + SE_MEAN_APOG;
  if (letter >= 'J' && letter <= 'Z') return letter - 'J' + SE_CUPIDO;
  switch (letter) {
    case 'm':
      return SE_MEAN_NODE;
    case 'c':
      return SE_INTP_APOG;
    case 'g':
      return SE_INTP_PERG;
    case 'n':
    case 'o':
      return SE_ECL_NUT;
    case 't':
      return SE_TRUE_NODE;
    case 'f':
      return SE_FIXSTAR;
    case 'w':
      return SE_WALDEMATH;
    case 'e': /* swetest: a line of labels */
    case 'q': /* swetest: delta t */
    case 'y': /* swetest: time equation */
    case 'x': /* swetest: sidereal time */
    case 'b': /* swetest: ayanamsha */
    case 's': /* swetest: an asteroid, with number given in -xs[number] */
    case 'v': /* swetest: a planetary moon, with number given in -xv[number] */
    case 'z': /* swetest: a fictitious body, number given in -xz[number] */
    case 'd': /* swetest: default (main) factors 0123456789mtABC */
    case 'p': /* swetest: main factors ('d') plus main asteroids DEFGHI */
    case 'h': /* swetest: fictitious factors JKLMNOPQRSTUVWXYZw */
    case 'a': /* swetest: all factors, like 'p'+'h' */
      return -1;
  }
  return -2;
}

int32 ut_to_lmt_lat(double t_ut, double* geopos, double* t_ret, char* serr) {
  int32 iflgret = OK;
  if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
    t_ut += geopos[0] / 360.0;
    if (time_flag & BIT_TIME_LAT) {
      iflgret = swe_lmt_to_lat(t_ut, geopos[0], &t_ut, serr);
    }
  }
  *t_ret = t_ut;
  return iflgret;
}

int32 orbital_elements(double tjd_et, int32 ipl, int32 iflag, char* serr) {
  int32 retval;
  double dret[20], jut;
  int32 jyear, jmon, jday;
  char sdateperi[20];
  retval = swe_get_orbital_elements(tjd_et, ipl, iflag, dret, serr);
  if (retval == ERR) {
    printf("%s\n", serr);
    return ERR;
  } else {
    swe_revjul(dret[14], gregflag, &jyear, &jmon, &jday, &jut);
    sprintf(sdateperi, "%2d.%02d.%04d,%s", jday, jmon, jyear,
            hms(jut, BIT_LZEROES));
    printf(
        "semiaxis         \t%f\neccentricity     \t%f\ninclination      "
        "\t%f\nasc. node       \t%f\narg. pericenter  \t%f\npericenter       "
        "\t%f\n",
        dret[0], dret[1], dret[2], dret[3], dret[4], dret[5]);
    printf(
        "mean longitude   \t%f\nmean anomaly     \t%f\necc. anomaly     "
        "\t%f\ntrue anomaly     \t%f\n",
        dret[9], dret[6], dret[8], dret[7]);
    printf(
        "time pericenter  \t%f %s\ndist. pericenter \t%f\ndist. apocenter  "
        "\t%f\n",
        dret[14], sdateperi, dret[15], dret[16]);
    printf(
        "mean daily motion\t%f\nsid. period (y)  \t%f\ntrop. period (y) "
        "\t%f\nsynodic cycle (d)\t%f\n",
        dret[11], dret[10], dret[12], dret[13]);
  }
  return OK;
}

int32 call_rise_set(double t_ut, int32 ipl, char* star, int32 whicheph,
                    double* geopos, char* serr) {
  int ii, rval, loop_count;
  int32 rsmi = 0;
  double dayfrac = 0.0001;
  double tret[10], trise, tset, tnext, tret1sv = 0;
  AS_BOOL do_rise, do_set;
  AS_BOOL last_was_empty = FALSE;
  int32 retc = OK;
  int rsmior = 0;
  if (norefrac) rsmior |= SE_BIT_NO_REFRACTION;
  if (disccenter) rsmior |= SE_BIT_DISC_CENTER;
  if (discbottom) rsmior |= SE_BIT_DISC_BOTTOM;
  if (hindu) rsmior |= SE_BIT_HINDU_RISING;
  if (fabs(geopos[1]) < 60 && ipl >= SE_SUN && ipl <= SE_PLUTO) dayfrac = 0.01;
  swe_set_topo(geopos[0], geopos[1], geopos[2]);
  // "geo. long 8.000000, lat 47.000000, alt 0.000000"
  if (with_header)
    printf("\ngeo. long %f, lat %f, alt %f", geopos[0], geopos[1], geopos[2]);
  do_printf("\n");
  tnext = t_ut;
  // the code is designed for looping with -nxxx over many days, during which
  // the object might become circumpolar, or never rise at all.
  while (special_event == SP_RISE_SET && tnext < t_ut + nstep) {
    // the following 'if' avoids unnecessary calculations for circumpolar
    // objects. even without it, the output would be correct, but
    // could be considerably slower.
    if (last_was_empty && (star == NULL || *star == '\0')) {
      rval = swe_calc_ut(tnext, ipl, whicheph | SEFLG_EQUATORIAL, tret, serr);
      if (rval >= 0) {
        double edist = geopos[1] + tret[1];
        double edist2 = geopos[1] - tret[1];
        if ((edist - 2 > 90 || edist + 2 < -90) ||
            (edist2 - 2 > 90 || edist2 + 2 < -90)) {
          tnext += 1;
          continue;
        }
      }
    }
    /* rising */
    rsmi = SE_CALC_RISE | rsmior;
    rval = swe_rise_trans(tnext, ipl, star, whicheph, rsmi, geopos, datm[0],
                          datm[1], &trise, serr);
    if (rval == ERR) {
      do_printf(serr);
      exit(0);
    }
    do_rise = (rval == OK);
    /* setting */
    rsmi = SE_CALC_SET | rsmior;
    do_set = FALSE;
    loop_count = 0;
    // tnext = trise; // dieter 14-feb-17
    while (!do_set && loop_count < 2) {
      rval = swe_rise_trans(tnext, ipl, star, whicheph, rsmi, geopos, datm[0],
                            datm[1], &tset, serr);
      if (rval == ERR) {
        do_printf(serr);
        exit(0);
      }
      do_set = (rval == OK);
      if (!do_set && do_rise) {
        tnext = trise;
      }
      loop_count++;
    }
    if (do_rise && do_set && trise > tset) {
      do_rise = FALSE;  // ignore rises happening before setting
      trise =
          0;  // we hope that exact time 0 never happens, is highly unlikely.
    }
    if (do_rise && do_set) {
      rval = print_rise_set_line(trise, tset, geopos, serr);
      last_was_empty = FALSE;
      tnext = tset + dayfrac;
    } else if (do_rise && !do_set) {
      rval = print_rise_set_line(trise, 0, geopos, serr);
      last_was_empty = FALSE;
      tnext = trise + dayfrac;
    } else if (do_set && !do_rise) {
      tnext = tset + dayfrac;
      rval = print_rise_set_line(0, tset, geopos, serr);
      last_was_empty = FALSE;
    } else {  // neither rise nor set
      // for sequences of days without rise or set, the line '-   -' is printed
      // only once.
      if (!last_was_empty) rval = print_rise_set_line(0, 0, geopos, serr);
      tnext += 1;
      last_was_empty = TRUE;
    }
    if (rval == ERR) {
      do_printf(serr);
      exit(0);
    }
    if (nstep == 1) break;
  }
  /* swetest -metr
   * calculate and print transits over meridian (midheaven and lower
   * midheaven */
  if (special_event == SP_MERIDIAN_TRANSIT) {
    /* loop over days */
    for (ii = 0; ii < nstep; ii++, t_ut = tret1sv + 0.001) {
      /* transit over midheaven */
      if (swe_rise_trans(t_ut, ipl, star, whicheph, SE_CALC_MTRANSIT, geopos,
                         datm[0], datm[1], &(tret[0]), serr) != OK) {
        do_printf(serr);
        return ERR;
      }
      /* transit over lower midheaven */
      if (swe_rise_trans(t_ut, ipl, star, whicheph, SE_CALC_ITRANSIT, geopos,
                         datm[0], datm[1], &(tret[1]), serr) != OK) {
        do_printf(serr);
        return ERR;
      }
      tret1sv = tret[1];
      if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
        retc = ut_to_lmt_lat(tret[0], geopos, &(tret[0]), serr);
        retc = ut_to_lmt_lat(tret[1], geopos, &(tret[1]), serr);
      }
      strcpy(sout, "mtransit ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[0] == 0 || tret[0] > tret[1])
        strcat(sout, "         -\t           -    ");
      else {
        swe_revjul(tret[0], gregflag, &jyear, &jmon, &jday, &jut);
        sprintf(sout + strlen(sout), "%2d.%02d.%04d\t%s    ", jday, jmon, jyear,
                hms(jut, BIT_LZEROES));
      }
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      strcat(sout, "itransit ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[1] == 0)
        strcat(sout, "         -\t           -    \n");
      else {
        swe_revjul(tret[1], gregflag, &jyear, &jmon, &jday, &jut);
        sprintf(sout + strlen(sout), "%2d.%02d.%04d\t%s\n", jday, jmon, jyear,
                hms(jut, BIT_LZEROES));
      }
      if (have_gap_parameter) insert_gap_string_for_tabs(sout, gap);
      do_printf(sout);
    }
  }
  return retc;
}

int32 print_rise_set_line(double trise, double tset, double* geopos,
                          char* serr) {
  double t0;
  int retc = OK;
  *sout = '\0';
  if (trise != 0) retc = ut_to_lmt_lat(trise, geopos, &(trise), serr);
  if (tset != 0) retc = ut_to_lmt_lat(tset, geopos, &(tset), serr);
  strcpy(sout, "rise     ");
  if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
  if (trise == 0) {
    strcat(sout, "         -\t           -    ");
  } else {
    swe_revjul(trise, gregflag, &jyear, &jmon, &jday, &jut);
    sprintf(sout + strlen(sout), "%2d.%02d.%04d\t%s    ", jday, jmon, jyear,
            hms(jut, BIT_LZEROES));
  }
  if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
  strcat(sout, "set      ");
  if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
  if (tset == 0) {
    strcat(sout, "         -\t           -    ");
  } else {
    swe_revjul(tset, gregflag, &jyear, &jmon, &jday, &jut);
    sprintf(sout + strlen(sout), "%2d.%02d.%04d\t%s    ", jday, jmon, jyear,
            hms(jut, BIT_LZEROES));
  }
  if (trise != 0 && tset != 0) {
    if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
    sprintf(sout + strlen(sout), "dt =");
    if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
    t0 = (tset - trise) * 24;
    sprintf(sout + strlen(sout), "%s", hms(t0, BIT_LZEROES));
  }
  strcat(sout, "\n");
  if (have_gap_parameter) insert_gap_string_for_tabs(sout, gap);
  do_printf(sout);
  return retc;
}

void insert_gap_string_for_tabs(char* sout, char* gap) {
  char* sp;
  char s[LEN_SOUT];
  if (!have_gap_parameter) return;
  if (*gap == '\t') return;
  while ((sp = strchr(sout, '\t')) != NULL &&
         strlen(sout) + strlen(gap) < LEN_SOUT) {
    strcpy(s, sp + 1);
    strcpy(sp, gap);
    strcat(sp, s);
  }
}

char* get_gregjul(int gregflag, int year) {
  if (gregflag == SE_JUL_CAL) return "jul";
  if (year < 1700) return "greg";
  return "";
}
