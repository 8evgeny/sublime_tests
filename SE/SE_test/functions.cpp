#include <iostream>

#include "main.h"

void printAll(nativ& n) {
  cout << n.name << endl;
  cout << "As-" << n.as.lon << "\t " << endl;
  cout << "Su-" << n.su.lon << "\t " << n.su.speed << endl;
  cout << "Ch-" << n.ch.lon << "\t " << n.ch.speed << endl;
  cout << "Ma-" << n.ma.lon << "\t " << n.ma.speed << endl;
  cout << "Bu-" << n.bu.lon << "\t " << n.bu.speed << endl;
  cout << "Gu-" << n.gu.lon << "\t " << n.gu.speed << endl;
  cout << "Sk-" << n.sk.lon << "\t " << n.sk.speed << endl;
  cout << "Sa-" << n.sa.lon << "\t " << n.sa.speed << endl;
  cout << "Ra-" << n.ra.lon << "\t " << n.ra.speed << endl;
  cout << "Ke-" << n.ke.lon << "\t " << n.ke.speed << endl;
  cout << endl;
}

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

int32 call_lunar_occultation(double t_ut, int32 ipl, char* star, int32 whicheph,
                             int32 special_mode, double* geopos, char* serr) {
  int i, ii, ecl_type = 0, eclflag, retc = OK;
  double dt, tret[30], attr[30], geopos_max[3];
  char s1[AS_MAXCH], s2[AS_MAXCH];
  AS_BOOL has_found = FALSE;
  int nloops = 0;
  /* no selective eclipse type set, set all */
  if ((search_flag & SE_ECL_ALLTYPES_SOLAR) == 0)
    search_flag |= SE_ECL_ALLTYPES_SOLAR;
  /* for local occultations: set geographic position of observer */
  if (special_mode & SP_MODE_LOCAL) {
    swe_set_topo(geopos[0], geopos[1], geopos[2]);
    if (with_header)
      printf("\ngeo. long %f, lat %f, alt %f", geopos[0], geopos[1], geopos[2]);
  }
  do_printf("\n");
  for (ii = 0; ii < nstep; ii++) {
    *sout = '\0';
    nloops++;
    if (nloops > SEARCH_RANGE_LUNAR_CYCLES) {
      sprintf(serr, "event search ended after %d lunar cycles at jd=%f\n",
              SEARCH_RANGE_LUNAR_CYCLES, t_ut);
      do_printf(serr);
      return ERR;
    }
    if (special_mode & SP_MODE_LOCAL) {
      /* * local search for occultation, test one lunar cycle only
       * (SE_ECL_ONE_TRY) */
      if (ipl != SE_SUN) {
        search_flag &= ~(SE_ECL_ANNULAR | SE_ECL_ANNULAR_TOTAL);
        if (search_flag == 0) search_flag = SE_ECL_ALLTYPES_SOLAR;
      }
      if ((eclflag = swe_lun_occult_when_loc(
               t_ut, ipl, star, whicheph, geopos, tret, attr,
               direction_flag | SE_ECL_ONE_TRY, serr)) == ERR) {
        do_printf(serr);
        return ERR;
      } else if (eclflag == 0) { /* event not found, try next conjunction */
        t_ut = tret[0] +
               direction * 10; /* try again with start date increased by 10 */
        ii--;
      } else {
        t_ut = tret[0];
        if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
          for (i = 0; i < 10; i++) {
            if (tret[i] != 0) {
              retc = ut_to_lmt_lat(tret[i], geopos, &(tret[i]), serr);
              if (retc == ERR) {
                do_printf(serr);
                return ERR;
              }
            }
          }
        }
        has_found = FALSE;
        *sout = '\0';
        if ((search_flag & SE_ECL_TOTAL) && (eclflag & SE_ECL_TOTAL)) {
          strcat(sout, "total");
          has_found = TRUE;
          ecl_type = ECL_SOL_TOTAL;
        }
        if ((search_flag & SE_ECL_ANNULAR) && (eclflag & SE_ECL_ANNULAR)) {
          strcat(sout, "annular");
          has_found = TRUE;
          ecl_type = ECL_SOL_ANNULAR;
        }
        if ((search_flag & SE_ECL_PARTIAL) && (eclflag & SE_ECL_PARTIAL)) {
          strcat(sout, "partial");
          has_found = TRUE;
          ecl_type = ECL_SOL_PARTIAL;
        }
        if (ipl != SE_SUN) {
          if ((eclflag & SE_ECL_OCC_BEG_DAYLIGHT) &&
              (eclflag & SE_ECL_OCC_END_DAYLIGHT))
            strcat(sout, "(daytime)"); /* occultation occurs during the day */
          else if (eclflag & SE_ECL_OCC_BEG_DAYLIGHT)
            strcat(sout, "(sunset) "); /* occultation occurs during the day */
          else if (eclflag & SE_ECL_OCC_END_DAYLIGHT)
            strcat(sout, "(sunrise)"); /* occultation occurs during the day */
        }
        if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
        while (strlen(sout) < 17) strcat(sout, " ");
        if (!has_found) {
          ii--;
        } else {
          swe_calc_ut(t_ut, SE_ECL_NUT, 0, x, serr);
          swe_revjul(tret[0], gregflag, &jyear, &jmon, &jday, &jut);
          dt = (tret[3] - tret[2]) * 24 * 60;
          sprintf(sout + strlen(sout), "%2d.%02d.%04d\t%s\t%f\t%.6f\n", jday,
                  jmon, jyear, hms(jut, BIT_LZEROES), attr[0], tret[0]);
          sprintf(sout + strlen(sout), "\t%d min %4.2f sec\t", (int)dt,
                  fmod(dt, 1) * 60);
          if (eclflag & SE_ECL_1ST_VISIBLE)
            sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[1]));
          else
            strcat(sout, "   -         ");
          if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
          if (eclflag & SE_ECL_2ND_VISIBLE)
            sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[2]));
          else
            strcat(sout, "   -         ");
          if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
          if (eclflag & SE_ECL_3RD_VISIBLE)
            sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[3]));
          else
            strcat(sout, "   -         ");
          if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
          if (eclflag & SE_ECL_4TH_VISIBLE)
            sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[4]));
          else
            strcat(sout, "   -         ");
          if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
#if 0
      sprintf(sout + strlen(sout), "\t%d min %4.2f sec   %s %s %s %s",
                (int) dt, fmod(dt, 1) * 60,
                strcpy(s1, hms(fmod(tret[1] + 0.5, 1) * 24, BIT_LZEROES)),
                strcpy(s3, hms(fmod(tret[2] + 0.5, 1) * 24, BIT_LZEROES)),
                strcpy(s4, hms(fmod(tret[3] + 0.5, 1) * 24, BIT_LZEROES)),
                strcpy(s2, hms(fmod(tret[4] + 0.5, 1) * 24, BIT_LZEROES)));
#endif
          sprintf(sout + strlen(sout), "dt=%.1f",
                  swe_deltat_ex(tret[0], whicheph, serr) * 86400.0);
          strcat(sout, "\n");
          if (have_gap_parameter) insert_gap_string_for_tabs(sout, gap);
          do_printf(sout);
        }
      }
    } /* endif search_local */
    if (!(special_mode & SP_MODE_LOCAL)) {
      /* * global search for occultations, test one lunar cycle only
       * (SE_ECL_ONE_TRY) */
      if ((eclflag = swe_lun_occult_when_glob(
               t_ut, ipl, star, whicheph, search_flag, tret,
               direction_flag | SE_ECL_ONE_TRY, serr)) == ERR) {
        do_printf(serr);
        return ERR;
      }
      if (eclflag == 0) { /* no occltation was found at next conjunction, try
next conjunction */
        t_ut = tret[0] + direction;
        ii--;
        continue;
      }
      if ((eclflag & SE_ECL_TOTAL)) {
        strcpy(sout, "total   ");
        ecl_type = ECL_SOL_TOTAL;
      }
      if ((eclflag & SE_ECL_ANNULAR)) {
        strcpy(sout, "annular ");
        ecl_type = ECL_SOL_ANNULAR;
      }
      if ((eclflag & SE_ECL_ANNULAR_TOTAL)) {
        strcpy(sout, "ann-tot ");
        ecl_type = ECL_SOL_ANNULAR; /* by Alois: what is this ? */
      }
      if ((eclflag & SE_ECL_PARTIAL)) {
        strcpy(sout, "partial ");
        ecl_type = ECL_SOL_PARTIAL;
      }
      if ((eclflag & SE_ECL_NONCENTRAL) && !(eclflag & SE_ECL_PARTIAL))
        strcat(sout, "non-central ");
      t_ut = tret[0];
      swe_lun_occult_where(t_ut, ipl, star, whicheph, geopos_max, attr, serr);
      /* for (i = 0; i < 8; i++) {
printf("attr[%d]=%.17f\n", i, attr[i]);
} */
      if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
        for (i = 0; i < 10; i++) {
          if (tret[i] != 0) {
            retc = ut_to_lmt_lat(tret[i], geopos, &(tret[i]), serr);
            if (retc == ERR) {
              do_printf(serr);
              return ERR;
            }
          }
        }
      }
      swe_revjul(tret[0], gregflag, &jyear, &jmon, &jday, &jut);
      sprintf(sout + strlen(sout), "%2d.%02d.%04d\t%s\t%f km\t%f\t%.6f\n", jday,
              jmon, jyear, hms(jut, BIT_LZEROES), attr[3], attr[0], tret[0]);
      sprintf(sout + strlen(sout), "\t%s ", hms_from_tjd(tret[2]));
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[4] != 0)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[4]));
      else
        strcat(sout, "   -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[5] != 0)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[5]));
      else
        strcat(sout, "   -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      sprintf(sout + strlen(sout), "%s", hms_from_tjd(tret[3]));
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      sprintf(sout + strlen(sout), "dt=%.1f",
              swe_deltat_ex(tret[0], whicheph, serr) * 86400.0);
      strcat(sout, "\n");
      sprintf(sout + strlen(sout), "\t%s\t%s",
              strcpy(s1, dms(geopos_max[0], BIT_ROUND_MIN)),
              strcpy(s2, dms(geopos_max[1], BIT_ROUND_MIN)));
      if (!(eclflag & SE_ECL_PARTIAL) && !(eclflag & SE_ECL_NONCENTRAL)) {
        if ((eclflag = swe_lun_occult_when_loc(t_ut - 10, ipl, star, whicheph,
                                               geopos_max, tret, attr, 0,
                                               serr)) == ERR) {
          do_printf(serr);
          return ERR;
        }
        if (fabs(tret[0] - t_ut) > 2)
          do_printf("when_loc returns wrong date\n");
        dt = (tret[3] - tret[2]) * 24 * 60;
        sprintf(sout + strlen(sout), "\t%d min %4.2f sec", (int)dt,
                fmod(dt, 1) * 60);
      }
      strcat(sout, "\n");
      if (have_gap_parameter) insert_gap_string_for_tabs(sout, gap);
      if (special_mode & SP_MODE_HOCAL) {
        int ihou, imin, isec, isgn;
        double dfrc;
        swe_split_deg(jut, SE_SPLIT_DEG_ROUND_MIN, &ihou, &imin, &isec, &dfrc,
                      &isgn);
        sprintf(sout, "\"%04d %02d %02d %02d.%02d %d\",\n", jyear, jmon, jday,
                ihou, imin, ecl_type);
      }
      do_printf(sout);
    }
    t_ut += direction;
  }
  return OK;
}

int do_special_event(double tjd, int32 ipl, char* star, int32 special_event,
                     int32 special_mode, double* geopos, double* datm,
                     double* dobs, char* serr) {
  int retc = 0;
  /* risings, settings, meridian transits */
  if (special_event == SP_RISE_SET || special_event == SP_MERIDIAN_TRANSIT)
    retc = call_rise_set(tjd, ipl, star, whicheph, geopos, serr);
  /* lunar eclipses */
  if (special_event == SP_LUNAR_ECLIPSE)
    retc = call_lunar_eclipse(tjd, whicheph, special_mode, geopos, serr);
  /* solar eclipses */
  if (special_event == SP_SOLAR_ECLIPSE)
    retc = call_solar_eclipse(tjd, whicheph, special_mode, geopos, serr);
  /* occultations by the moon */
  if (special_event == SP_OCCULTATION)
    retc = call_lunar_occultation(tjd, ipl, star, whicheph, special_mode,
                                  geopos, serr);
  /* heliacal event */
  if (special_event == SP_HELIACAL)
    retc =
        call_heliacal_event(tjd, ipl, star, whicheph, geopos, datm, dobs, serr);
  return retc;
}

int32 call_heliacal_event(double t_ut, int32 ipl, char* star, int32 whicheph,
                          double* geopos, double* datm, double* dobs,
                          char* serr) {
  int ii, retc = OK, event_type = 0, retflag;
  double dret[40], tsave1, tsave2 = 0;
  char obj_name[AS_MAXCH];
  helflag |= whicheph;
  /* if invalid heliacal event type was required, set 0 for any type */
  if (search_flag < 0 || search_flag > 6) search_flag = 0;
  /* optical instruments used: */
  if (dobs[3] > 0) helflag |= SE_HELFLAG_OPTICAL_PARAMS;
  if (hel_using_AV) helflag |= SE_HELFLAG_AV;
  if (ipl == SE_FIXSTAR)
    strcpy(obj_name, star);
  else
    swe_get_planet_name(ipl, obj_name);
  if (with_header) {
    printf("\ngeo. long %f, lat %f, alt %f", geopos[0], geopos[1], geopos[2]);
    do_printf("\n");
  }
  for (ii = 0; ii < nstep; ii++, t_ut = dret[0] + 1) {
    *sout = '\0';
    if (search_flag > 0)
      event_type = search_flag;
    else if (ipl == SE_MOON)
      event_type = SE_EVENING_FIRST;
    else
      event_type = SE_HELIACAL_RISING;
    retflag = swe_heliacal_ut(t_ut, geopos, datm, dobs, obj_name, event_type,
                              helflag, dret, serr);
    if (retflag == ERR) {
      do_printf(serr);
      return ERR;
    }
    if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
      retc = ut_to_lmt_lat(dret[0], geopos, &(dret[0]), serr);
      if (retc != ERR) retc = ut_to_lmt_lat(dret[1], geopos, &(dret[1]), serr);
      if (retc != ERR) retc = ut_to_lmt_lat(dret[2], geopos, &(dret[2]), serr);
      if (retc == ERR) {
        do_printf(serr);
        return ERR;
      }
    }
    do_print_heliacal(dret, event_type, obj_name);
    /* list all events within synodic cycle */
    if (search_flag == 0) {
      if (ipl == SE_VENUS || ipl == SE_MERCURY) {
        /* we have heliacal rising (morning first), now find morning last */
        event_type = SE_MORNING_LAST;
        retflag = swe_heliacal_ut(dret[0], geopos, datm, dobs, obj_name,
                                  event_type, helflag, dret, serr);
        if (retflag == ERR) {
          do_printf(serr);
          return ERR;
        }
        if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
          retc = ut_to_lmt_lat(dret[0], geopos, &(dret[0]), serr);
          if (retc != ERR)
            retc = ut_to_lmt_lat(dret[1], geopos, &(dret[1]), serr);
          if (retc != ERR)
            retc = ut_to_lmt_lat(dret[2], geopos, &(dret[2]), serr);
          if (retc == ERR) {
            do_printf(serr);
            return ERR;
          }
        }
        do_print_heliacal(dret, event_type, obj_name);
        tsave1 = dret[0];
        /* mercury can have several evening appearances without any morning
         * appearances in betweeen. We have to find out when the next
         * morning appearance is and then find all evening appearances
         * that take place before that */
        if (ipl == SE_MERCURY) {
          event_type = SE_HELIACAL_RISING;
          retflag = swe_heliacal_ut(dret[0], geopos, datm, dobs, obj_name,
                                    event_type, helflag, dret, serr);
          if (retflag == ERR) {
            do_printf(serr);
            return ERR;
          }
          tsave2 = dret[0];
        }
      repeat_mercury:
        /* evening first */
        event_type = SE_EVENING_FIRST;
        retflag = swe_heliacal_ut(tsave1, geopos, datm, dobs, obj_name,
                                  event_type, helflag, dret, serr);
        if (retflag == ERR) {
          do_printf(serr);
          return ERR;
        }
        if (ipl == SE_MERCURY && dret[0] > tsave2) continue;
        if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
          retc = ut_to_lmt_lat(dret[0], geopos, &(dret[0]), serr);
          if (retc != ERR)
            retc = ut_to_lmt_lat(dret[1], geopos, &(dret[1]), serr);
          if (retc != ERR)
            retc = ut_to_lmt_lat(dret[2], geopos, &(dret[2]), serr);
          if (retc == ERR) {
            do_printf(serr);
            return ERR;
          }
        }
        do_print_heliacal(dret, event_type, obj_name);
      }
      if (ipl == SE_MOON) {
        /* morning last */
        event_type = SE_MORNING_LAST;
        retflag = swe_heliacal_ut(dret[0], geopos, datm, dobs, obj_name,
                                  event_type, helflag, dret, serr);
        if (retflag == ERR) {
          do_printf(serr);
          return ERR;
        }
        if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
          retc = ut_to_lmt_lat(dret[0], geopos, &(dret[0]), serr);
          if (retc != ERR)
            retc = ut_to_lmt_lat(dret[1], geopos, &(dret[1]), serr);
          if (retc != ERR)
            retc = ut_to_lmt_lat(dret[2], geopos, &(dret[2]), serr);
          if (retc == ERR) {
            do_printf(serr);
            return ERR;
          }
        }
        do_print_heliacal(dret, event_type, obj_name);
      } else {
        /* heliacal setting (evening last) */
        event_type = SE_HELIACAL_SETTING;
        retflag = swe_heliacal_ut(dret[0], geopos, datm, dobs, obj_name,
                                  event_type, helflag, dret, serr);
        if (retflag == ERR) {
          do_printf(serr);
          return ERR;
        }
        if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
          retc = ut_to_lmt_lat(dret[0], geopos, &(dret[0]), serr);
          if (retc != ERR)
            retc = ut_to_lmt_lat(dret[1], geopos, &(dret[1]), serr);
          if (retc != ERR)
            retc = ut_to_lmt_lat(dret[2], geopos, &(dret[2]), serr);
          if (retc == ERR) {
            do_printf(serr);
            return ERR;
          }
        }
        do_print_heliacal(dret, event_type, obj_name);
        if ((0) && ipl == SE_MERCURY) {
          tsave1 = dret[0];
          goto repeat_mercury;
        }
      }
    }
  }
  return OK;
}

void do_print_heliacal(double* dret, int32 event_type, char* obj_name) {
  char* sevtname[] = {
      "",
      "heliacal rising ",
      "heliacal setting",
      "evening first   ",
      "morning last    ",
      "evening rising  ",
      "morning setting ",
  };
  char* stz = "UT";
  char stim0[40], stim1[40], stim2[40];
  if (time_flag & BIT_TIME_LMT) stz = "LMT";
  if (time_flag & BIT_TIME_LAT) stz = "LAT";
  *sout = '\0';
  swe_revjul(dret[0], gregflag, &jyear, &jmon, &jday, &jut);
  if (event_type <= 4) {
    if (hel_using_AV) {
      strcpy(stim0, hms_from_tjd(dret[0]));
      remove_whitespace(stim0);
      /* The following line displays only the beginning of visibility. */
      sprintf(sout + strlen(sout), "%s %s: %d/%02d/%02d %s %s (%.5f)\n",
              obj_name, sevtname[event_type], jyear, jmon, jday, stim0, stz,
              dret[0]);
    } else {
      /* display the moment of beginning and optimum visibility */
      strcpy(stim0, hms_from_tjd(dret[0]));
      strcpy(stim1, hms_from_tjd(dret[1]));
      strcpy(stim2, hms_from_tjd(dret[2]));
      remove_whitespace(stim0);
      remove_whitespace(stim1);
      remove_whitespace(stim2);
      sprintf(
          sout + strlen(sout),
          "%s %s: %d/%02d/%02d %s %s (%.5f), opt %s, end %s, dur %.1f min\n",
          obj_name, sevtname[event_type], jyear, jmon, jday, stim0, stz,
          dret[0], stim1, stim2, (dret[2] - dret[0]) * 1440);
    }
  } else {
    strcpy(stim0, hms_from_tjd(dret[0]));
    remove_whitespace(stim0);
    sprintf(sout + strlen(sout), "%s %s: %d/%02d/%02d %s %s (%f)\n", obj_name,
            sevtname[event_type], jyear, jmon, jday, stim0, stz, dret[0]);
  }
  do_printf(sout);
}

int32 call_solar_eclipse(double t_ut, int32 whicheph, int32 special_mode,
                         double* geopos, char* serr) {
  int i, ii, retc = OK, eclflag, ecl_type = 0;
  double dt, tret[30], attr[30], geopos_max[3];
  char slon[8], slat[8], saros[20];
  char s1[AS_MAXCH], s2[AS_MAXCH], sout_short[AS_MAXCH], *styp = "none", *sgj;
  AS_BOOL has_found = FALSE;
  /* no selective eclipse type set, set all */
  if (with_chart_link) do_printf("<pre>");
  if ((search_flag & SE_ECL_ALLTYPES_SOLAR) == 0)
    search_flag |= SE_ECL_ALLTYPES_SOLAR;
  /* for local eclipses: set geographic position of observer */
  if (special_mode & SP_MODE_LOCAL) {
    swe_set_topo(geopos[0], geopos[1], geopos[2]);
    // "geo. long 8.000000, lat 47.000000, alt 0.000000"
    if (with_header)
      printf("\ngeo. long %f, lat %f, alt %f", geopos[0], geopos[1], geopos[2]);
  }
  do_printf("\n");
  for (ii = 0; ii < nstep; ii++, t_ut += direction) {
    *sout = '\0';
    /* swetest -solecl -local -geopos...
     * find next solar eclipse observable from a given geographic position */
    if (special_mode & SP_MODE_LOCAL) {
      if ((eclflag = swe_sol_eclipse_when_loc(t_ut, whicheph, geopos, tret,
                                              attr, direction_flag, serr)) ==
          ERR) {
        do_printf(serr);
        return ERR;
      } else {
        has_found = FALSE;
        t_ut = tret[0];
        if ((search_flag & SE_ECL_TOTAL) && (eclflag & SE_ECL_TOTAL)) {
          strcpy(sout, "total   ");
          has_found = TRUE;
          ecl_type = ECL_SOL_TOTAL;
        }
        if ((search_flag & SE_ECL_ANNULAR) && (eclflag & SE_ECL_ANNULAR)) {
          strcpy(sout, "annular ");
          has_found = TRUE;
          ecl_type = ECL_SOL_ANNULAR;
        }
        if ((search_flag & SE_ECL_PARTIAL) && (eclflag & SE_ECL_PARTIAL)) {
          strcpy(sout, "partial ");
          has_found = TRUE;
          ecl_type = ECL_SOL_PARTIAL;
        }
        if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
        if (!has_found) {
          ii--;
        } else {
          swe_calc(t_ut + swe_deltat_ex(t_ut, whicheph, serr), SE_ECL_NUT, 0, x,
                   serr);
          if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
            for (i = 0; i < 10; i++) {
              if (tret[i] != 0) {
                retc = ut_to_lmt_lat(tret[i], geopos, &(tret[i]), serr);
                if (retc == ERR) {
                  do_printf(serr);
                  return ERR;
                }
              }
            }
          }
          t_ut = tret[0];
          swe_revjul(t_ut, gregflag, &jyear, &jmon, &jday, &jut);
          dt = (tret[3] - tret[2]) * 24 * 60;
          sgj = get_gregjul(gregflag, jyear);
          sprintf(saros, "%d/%d", (int)attr[9], (int)attr[10]);
          sprintf(sout + strlen(sout),
                  "%2d.%02d.%04d%s\t%s\t%.4f/%.4f/%.4f\tsaros %s\t%.6f\n", jday,
                  jmon, jyear, sgj, hms(jut, BIT_LZEROES), attr[8], attr[0],
                  attr[2], saros, t_ut);
          sprintf(sout + strlen(sout), "\t%d min %4.2f sec\t", (int)dt,
                  fmod(dt, 1) * 60);
          if (eclflag & SE_ECL_1ST_VISIBLE) {
            sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[1]));
          } else {
            strcat(sout, "   -         ");
          }
          if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
          if (eclflag & SE_ECL_2ND_VISIBLE) {
            sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[2]));
          } else {
            strcat(sout, "   -         ");
          }
          if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
          if (eclflag & SE_ECL_3RD_VISIBLE) {
            sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[3]));
          } else {
            strcat(sout, "   -         ");
          }
          if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
          if (eclflag & SE_ECL_4TH_VISIBLE) {
            sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[4]));
          } else {
            strcat(sout, "   -         ");
          }
          if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
#if 0
      sprintf(sout + strlen(sout), "\t%d min %4.2f sec   %s %s %s %s",
                (int) dt, fmod(dt, 1) * 60,
                strcpy(s1, hms(fmod(tret[1] + 0.5, 1) * 24, BIT_LZEROES)),
                strcpy(s3, hms(fmod(tret[2] + 0.5, 1) * 24, BIT_LZEROES)),
                strcpy(s4, hms(fmod(tret[3] + 0.5, 1) * 24, BIT_LZEROES)),
                strcpy(s2, hms(fmod(tret[4] + 0.5, 1) * 24, BIT_LZEROES)));
#endif
          sprintf(sout + strlen(sout), "dt=%.1f",
                  swe_deltat_ex(tret[0], whicheph, serr) * 86400.0);
          strcat(sout, "\n");
          if (have_gap_parameter) insert_gap_string_for_tabs(sout, gap);
          do_printf(sout);
        }
      }
    } /* endif search_local */
    /* swetest -solecl
     * find next solar eclipse observable from anywhere on earth */
    if (!(special_mode & SP_MODE_LOCAL)) {
      if ((eclflag = swe_sol_eclipse_when_glob(t_ut, whicheph, search_flag,
                                               tret, direction_flag, serr)) ==
          ERR) {
        do_printf(serr);
        return ERR;
      }
      t_ut = tret[0];
      if ((eclflag & SE_ECL_TOTAL)) {
        styp = "Total";
        strcpy(sout, "total");
        ecl_type = ECL_SOL_TOTAL;
      }
      if ((eclflag & SE_ECL_ANNULAR)) {
        styp = "Annular";
        strcpy(sout, "annular");
        ecl_type = ECL_SOL_ANNULAR;
      }
      if ((eclflag & SE_ECL_ANNULAR_TOTAL)) {
        styp = "Annular-Total";
        strcpy(sout, "ann-tot");
        ecl_type = ECL_SOL_ANNULAR; /* by Alois: what is this ? */
      }
      if ((eclflag & SE_ECL_PARTIAL)) {
        styp = "Partial";
        strcpy(sout, "partial");
        ecl_type = ECL_SOL_PARTIAL;
      }
      if ((eclflag & SE_ECL_NONCENTRAL) && !(eclflag & SE_ECL_PARTIAL))
        strcat(sout, " non-central");
      sprintf(sout + strlen(sout), " solar\t");
      swe_sol_eclipse_where(t_ut, whicheph, geopos_max, attr, serr);
      if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
        for (i = 0; i < 10; i++) {
          if (tret[i] != 0) {
            retc = ut_to_lmt_lat(tret[i], geopos, &(tret[i]), serr);
            if (retc == ERR) {
              do_printf(serr);
              return ERR;
            }
          }
        }
      }
      swe_revjul(tret[0], gregflag, &jyear, &jmon, &jday, &jut);
      sgj = get_gregjul(gregflag, jyear);
      sprintf(saros, "%d/%d", (int)attr[9], (int)attr[10]);
      sprintf(sout_short, "%s\t%2d.%2d.%4d%s\t%s\t%.3f", sout, jday, jmon,
              jyear, sgj, hms(jut, 0), attr[8]);
      sprintf(sout + strlen(sout),
              "%2d.%02d.%04d%s\t%s\t%f km\t%.4f/%.4f/%.4f\tsaros %s\t%.6f\n",
              jday, jmon, jyear, sgj, hms(jut, 0), attr[3], attr[8], attr[0],
              attr[2], saros, tret[0]);
      sprintf(sout + strlen(sout), "\t%s ", hms_from_tjd(tret[2]));
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[4] != 0) {
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[4]));
      } else {
        strcat(sout, "   -         ");
      }
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[5] != 0) {
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[5]));
      } else {
        strcat(sout, "   -         ");
      }
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      sprintf(sout + strlen(sout), "%s", hms_from_tjd(tret[3]));
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      sprintf(sout + strlen(sout), "dt=%.1f",
              swe_deltat_ex(tret[0], whicheph, serr) * 86400.0);
      strcat(sout, "\n");
      sprintf(sout + strlen(sout), "\t%s\t%s",
              strcpy(s1, dms(geopos_max[0], BIT_ROUND_SEC)),
              strcpy(s2, dms(geopos_max[1], BIT_ROUND_SEC)));
      strcat(sout, "\t");
      strcat(sout_short, "\t");
      if (!(eclflag & SE_ECL_PARTIAL) && !(eclflag & SE_ECL_NONCENTRAL)) {
        if ((eclflag = swe_sol_eclipse_when_loc(t_ut - 10, whicheph, geopos_max,
                                                tret, attr, 0, serr)) == ERR) {
          do_printf(serr);
          return ERR;
        }
        if (fabs(tret[0] - t_ut) > 2) {
          do_printf("when_loc returns wrong date\n");
        }
        dt = (tret[3] - tret[2]) * 24 * 60;
        sprintf(s1, "%d min %4.2f sec", (int)dt, fmod(dt, 1) * 60);
        strcat(sout, s1);
        strcat(sout_short, s1);
      }
      sprintf(sout_short + strlen(sout_short), "\t%d\t%d", (int)attr[9],
              (int)attr[10]);
      strcat(sout, "\n");
      strcat(sout_short, "\n");
      if (special_mode & SP_MODE_HOCAL) {
        int ihou, imin, isec, isgn;
        double dfrc;
        swe_split_deg(jut, SE_SPLIT_DEG_ROUND_MIN, &ihou, &imin, &isec, &dfrc,
                      &isgn);
        sprintf(sout, "\"%04d%s %02d %02d %02d.%02d %d\",\n", jyear, sgj, jmon,
                jday, ihou, imin, ecl_type);
      }
      /*printf("len=%ld\n", strlen(sout));*/
      if (short_output) {
        do_printf(sout_short);
      } else {
        if (have_gap_parameter) insert_gap_string_for_tabs(sout, gap);
        do_printf(sout);
      }
      if (with_chart_link) {
        char snat[AS_MAXCH];
        char stim[AS_MAXCH];
        int iflg = 0;  // NAT_IFLG_UNKNOWN_TIME;
        char cal = gregflag ? 'g' : 'j';
        format_lon_lat(slon, slat, geopos_max[0], geopos_max[1]);
        strcpy(stim, hms(jut, BIT_LZEROES));
        while (*stim == ' ') our_strcpy(stim, stim + 1);
        if (*stim == '0') our_strcpy(stim, stim + 1);
        sprintf(snat,
                "Solar Eclipse %s,%s,e,%d,%d,%d,%s,h0e,%cnu,%d,Location of "
                "Maximum,,%s,%s,u,0,0,0",
                saros, styp, jday, jmon, jyear, stim, cal, iflg, slon, slat);
        sprintf(sout,
                "<a "
                "href='https://www.astro.com/cgi/"
                "chart.cgi?muasp=1;nhor=1;act=chmnat;nd1=%s;rs=1;iseclipse=1;"
                "topo=1' target='eclipse'>chart link</a>\n\n",
                snat);
        do_printf(sout);
      }
    }
  }
  if (with_chart_link) do_printf("</pre>\n");
  return OK;
}

void format_lon_lat(char* slon, char* slat, double lon, double lat) {
  // print lon and lat string in minute precision
  int roundflag, ideg, imin, isec, isgn;
  double dsecfr;
  char c;
  roundflag = SE_SPLIT_DEG_ROUND_SEC;
  swe_split_deg(lon, roundflag, &ideg, &imin, &isec, &dsecfr, &isgn);
  c = (lon < 0) ? 'w' : 'e';
  sprintf(slon, "%d%c%02d%02d", abs(ideg), c, imin, isec);
  swe_split_deg(lat, roundflag, &ideg, &imin, &isec, &dsecfr, &isgn);
  c = (lat < 0) ? 's' : 'n';
  sprintf(slat, "%d%c%02d%02d", abs(ideg), c, imin, isec);
}

int32 call_lunar_eclipse(double t_ut, int32 whicheph, int32 special_mode,
                         double* geopos, char* serr) {
  int i, ii, retc = OK, eclflag, ecl_type = 0;
  int rval, ihou, imin, isec, isgn;
  double dfrc, attr[30], dt, xx[6], geopos_max[3];
  char s1[AS_MAXCH], s2[AS_MAXCH], sout_short[AS_MAXCH], sfmt[AS_MAXCH],
      *styp = "none", *sgj;
  char slon[8], slat[8], saros[20];
  geopos_max[0] = 0;
  geopos_max[1] = 0;
  /* no selective eclipse type set, set all */
  if (with_chart_link) do_printf("<pre>");
  if ((search_flag & SE_ECL_ALLTYPES_LUNAR) == 0)
    search_flag |= SE_ECL_ALLTYPES_LUNAR;
  // "geo. long 8.000000, lat 47.000000, alt 0.000000"
  if (special_mode & SP_MODE_LOCAL) {
    if (with_header)
      printf("\ngeo. long %f, lat %f, alt %f", geopos[0], geopos[1], geopos[2]);
  }
  do_printf("\n");
  for (ii = 0; ii < nstep; ii++, t_ut += direction) {
    *sout = '\0';
    /* swetest -lunecl -how
     * type of lunar eclipse and percentage for a given time: */
    if (special_mode & SP_MODE_HOW) {
      if ((eclflag = swe_lun_eclipse_how(t_ut, whicheph, geopos, attr, serr)) ==
          ERR) {
        do_printf(serr);
        return ERR;
      } else {
        if (eclflag & SE_ECL_TOTAL) {
          ecl_type = ECL_LUN_TOTAL;
          strcpy(sfmt, "total lunar eclipse: %f o/o \n");
        } else if (eclflag & SE_ECL_PARTIAL) {
          ecl_type = ECL_LUN_PARTIAL;
          strcpy(sfmt, "partial lunar eclipse: %f o/o \n");
        } else if (eclflag & SE_ECL_PENUMBRAL) {
          ecl_type = ECL_LUN_PENUMBRAL;
          strcpy(sfmt, "penumbral lunar eclipse: %f o/o \n");
        } else {
          strcpy(sfmt, "no lunar eclipse \n");
        }
        strcpy(sout, sfmt);
        if (strchr(sfmt, '%') != NULL) {
          sprintf(sout, sfmt, attr[0]);
        }
        do_printf(sout);
      }
      continue;
    }
    /* swetest -lunecl
     * find next lunar eclipse: */
    /* locally visible lunar eclipse */
    if (special_mode & SP_MODE_LOCAL) {
      if ((eclflag = swe_lun_eclipse_when_loc(t_ut, whicheph, geopos, tret,
                                              attr, direction_flag, serr)) ==
          ERR) {
        do_printf(serr);
        return ERR;
      }
      if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
        for (i = 0; i < 10; i++) {
          if (tret[i] != 0) {
            retc = ut_to_lmt_lat(tret[i], geopos, &(tret[i]), serr);
            if (retc == ERR) {
              do_printf(serr);
              return ERR;
            }
          }
        }
      }
      t_ut = tret[0];
      if ((eclflag & SE_ECL_TOTAL)) {
        strcpy(sout, "total   ");
        ecl_type = ECL_LUN_TOTAL;
      }
      if ((eclflag & SE_ECL_PENUMBRAL)) {
        strcpy(sout, "penumb. ");
        ecl_type = ECL_LUN_PENUMBRAL;
      }
      if ((eclflag & SE_ECL_PARTIAL)) {
        strcpy(sout, "partial ");
        ecl_type = ECL_LUN_PARTIAL;
      }
      strcat(sout, "lunar eclipse\t");
      swe_revjul(t_ut, gregflag, &jyear, &jmon, &jday, &jut);
      sgj = get_gregjul(gregflag, jyear);
      /*if ((eclflag = swe_lun_eclipse_how(t_ut, whicheph, geopos, attr, serr))
== ERR) { do_printf(serr); return ERR;
}*/
      dt = (tret[3] - tret[2]) * 24 * 60;
      sprintf(s1, "%d min %4.2f sec", (int)dt, fmod(dt, 1) * 60);
      /* short output:
       * date, time of day, umbral magnitude, umbral duration, saros series,
       * member number */
      sprintf(saros, "%d/%d", (int)attr[9], (int)attr[10]);
      sprintf(sout_short, "%s\t%2d.%2d.%4d%s\t%s\t%.3f\t%s\t%s\n", sout, jday,
              jmon, jyear, sgj, hms(jut, 0), attr[8], s1, saros);
      sprintf(sout + strlen(sout),
              "%2d.%02d.%04d%s\t%s\t%.4f/%.4f\tsaros %s\t%.6f\n", jday, jmon,
              jyear, sgj, hms(jut, BIT_LZEROES), attr[0], attr[1], saros, t_ut);
      /* second line:
       * eclipse times, penumbral, partial, total begin and end */
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (eclflag & SE_ECL_PENUMBBEG_VISIBLE)
        sprintf(sout + strlen(sout), "  %s ", hms_from_tjd(tret[6]));
      else
        strcat(sout, "      -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (eclflag & SE_ECL_PARTBEG_VISIBLE)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[2]));
      else
        strcat(sout, "    -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (eclflag & SE_ECL_TOTBEG_VISIBLE)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[4]));
      else
        strcat(sout, "    -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (eclflag & SE_ECL_TOTEND_VISIBLE)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[5]));
      else
        strcat(sout, "    -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (eclflag & SE_ECL_PARTEND_VISIBLE)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[3]));
      else
        strcat(sout, "    -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (eclflag & SE_ECL_PENUMBEND_VISIBLE)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[7]));
      else
        strcat(sout, "    -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      sprintf(sout + strlen(sout), "dt=%.1f",
              swe_deltat_ex(tret[0], whicheph, serr) * 86400.0);
      strcat(sout, "\n");
      /* global lunar eclipse */
    } else {
      if ((eclflag = swe_lun_eclipse_when(t_ut, whicheph, search_flag, tret,
                                          direction_flag, serr)) == ERR) {
        do_printf(serr);
        return ERR;
      }
      t_ut = tret[0];
      if ((eclflag & SE_ECL_TOTAL)) {
        styp = "Total";
        strcpy(sout, "total ");
        ecl_type = ECL_LUN_TOTAL;
      }
      if ((eclflag & SE_ECL_PENUMBRAL)) {
        styp = "Penumbral";
        strcpy(sout, "penumb. ");
        ecl_type = ECL_LUN_PENUMBRAL;
      }
      if ((eclflag & SE_ECL_PARTIAL)) {
        styp = "Partial";
        strcpy(sout, "partial ");
        ecl_type = ECL_LUN_PARTIAL;
      }
      strcat(sout, "lunar eclipse\t");
      if ((eclflag = swe_lun_eclipse_how(t_ut, whicheph, geopos, attr, serr)) ==
          ERR) {
        do_printf(serr);
        return ERR;
      }
      if (time_flag & (BIT_TIME_LMT | BIT_TIME_LAT)) {
        for (i = 0; i < 10; i++) {
          if (tret[i] != 0) {
            retc = ut_to_lmt_lat(tret[i], geopos, &(tret[i]), serr);
            if (retc == ERR) {
              do_printf(serr);
              return ERR;
            }
          }
        }
      }
      t_ut = tret[0];
      rval = swe_calc_ut(t_ut, SE_MOON, whicheph | SEFLG_EQUATORIAL, xx, s1);
      if (rval < 0) strcat(s1, "\n");
      do_printf(s1);
      swe_revjul(t_ut, gregflag, &jyear, &jmon, &jday, &jut);
      geopos_max[0] = swe_degnorm(xx[0] - swe_sidtime(t_ut) * 15);
      if (geopos_max[0] > 180) geopos_max[0] -= 360;
      geopos_max[1] = xx[1];
      sgj = get_gregjul(gregflag, jyear);
      dt = (tret[3] - tret[2]) * 24 * 60;
      sprintf(s1, "%d min %4.2f sec", (int)dt, fmod(dt, 1) * 60);
      /* short output:
       * date, time of day, umbral magnitude, umbral duration, saros series,
       * member number */
      sprintf(saros, "%d/%d", (int)attr[9], (int)attr[10]);
      sprintf(sout_short, "%s\t%2d.%2d.%4d%s\t%s\t%.3f\t%s\t%s\n", sout, jday,
              jmon, jyear, sgj, hms(jut, 0), attr[8], s1, saros);
      // sprintf(sout + strlen(sout), "%2d.%02d.%04d%s\t%s\t%.4f/%.4f\tsaros
      // %s\t%.6f\tdt=%.2f\n", jday, jmon, jyear, sgj, hms(jut,BIT_LZEROES),
      // attr[0],attr[1], saros, t_ut, swe_deltat_ex(t_ut, whicheph, serr) *
      // 86400);
      sprintf(sout + strlen(sout),
              "%2d.%02d.%04d%s\t%s\t%.4f/%.4f\tsaros %s\t%.6f\n", jday, jmon,
              jyear, sgj, hms(jut, BIT_LZEROES), attr[0], attr[1], saros, t_ut);
      /* second line:
       * eclipse times, penumbral, partial, total begin and end */
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      sprintf(sout + strlen(sout), "  %s ", hms_from_tjd(tret[6]));
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[2] != 0)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[2]));
      else
        strcat(sout, "   -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[4] != 0)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[4]));
      else
        strcat(sout, "   -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[5] != 0)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[5]));
      else
        strcat(sout, "   -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      if (tret[3] != 0)
        sprintf(sout + strlen(sout), "%s ", hms_from_tjd(tret[3]));
      else
        strcat(sout, "   -         ");
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      sprintf(sout + strlen(sout), "%s", hms_from_tjd(tret[7]));
      if (have_gap_parameter) sprintf(sout + strlen(sout), "\t");
      sprintf(sout + strlen(sout), "dt=%.1f",
              swe_deltat_ex(tret[0], whicheph, serr) * 86400.0);
      strcat(sout, "\n");
      if (special_mode & SP_MODE_HOCAL) {
        swe_split_deg(jut, SE_SPLIT_DEG_ROUND_MIN, &ihou, &imin, &isec, &dfrc,
                      &isgn);
        sprintf(sout, "\"%04d%s %02d %02d %02d.%02d %d\",\n", jyear, sgj, jmon,
                jday, ihou, imin, ecl_type);
      }
      sprintf(sout + strlen(sout), "\t%s\t%s\n",
              strcpy(s1, dms(geopos_max[0], BIT_ROUND_SEC)),
              strcpy(s2, dms(geopos_max[1], BIT_ROUND_SEC)));
    }
    // dt = (tret[7] - tret[6]) * 24 * 60;
    // sprintf(sout + strlen(sout), "\t%d min %4.2f sec\n", (int) dt, fmod(dt,
    // 1) * 60);
    if (have_gap_parameter) insert_gap_string_for_tabs(sout, gap);
    if (short_output) {
      do_printf(sout_short);
    } else {
      do_printf(sout);
    }
    if (with_chart_link) {
      char snat[AS_MAXCH];
      char stim[AS_MAXCH];
      int iflg = 0;
      char cal = gregflag ? 'g' : 'j';
      strcpy(stim, hms(jut, BIT_LZEROES));
      format_lon_lat(slon, slat, geopos_max[0], geopos_max[1]);
      while (*stim == ' ') our_strcpy(stim, stim + 1);
      if (*stim == '0') our_strcpy(stim, stim + 1);
      sprintf(snat,
              "Lunar Eclipse %s,%s,e,%d,%d,%d,%s,h0e,%cnu,%d,Moon Zenith "
              "location,,%s,%s,u,0,0,0",
              saros, styp, jday, jmon, jyear, stim, cal, iflg, slon, slat);
      sprintf(sout,
              "<a "
              "href='https://www.astro.com/cgi/"
              "chart.cgi?muasp=1;nhor=1;act=chmnat;nd1=%s;rs=1;iseclipse=1' "
              "target='eclipse'>chart link</a>\n\n",
              snat);
      do_printf(sout);
    }
  }
  if (with_chart_link) do_printf("</pre>\n");
  return OK;
}

int32 get_geocentric_relative_distance(double tjd_et, int32 ipl, int32 iflag,
                                       char* serr) {
  /* This function calculates the geocentric relative distance of a planet,
   * where the closest position has value 1000, and remotest position has
   * value 0.
   * The value is returned as an integer. The algorithm does not allow
   * much higher accuracy.
   *
   * With the Moon we measure the distance relative to the maximum and minimum
   * found between 12000 BCE and 16000 CE.
   * If the distance value were given relative to the momentary osculating
   * ellipse, then the apogee would always have the value 1000 and the perigee
   * the value 0. It is certainly more interesting to know how much it is
   * relative to a greater time range.
   */

  int32 iflagi = (iflag & (SEFLG_EPHMASK | SEFLG_HELCTR | SEFLG_BARYCTR));
  int32 retval;
  double ar = 0;
  double xx[6];
  double dmax, dmin, dtrue;
  if ((0) && ipl == SE_MOON) {
    dmax = 0.002718774;  // jd = 283030.8
    dmin = 0.002381834;  // jd = -1006731.3
    if ((retval = swe_calc(tjd_et, SE_MOON,
                           iflagi | SEFLG_J2000 | SEFLG_TRUEPOS, xx, serr)) ==
        ERR)
      return 0;
    dtrue = xx[2];
  } else {
    if (swe_orbit_max_min_true_distance(tjd_et, ipl, iflagi, &dmax, &dmin,
                                        &dtrue, serr) == ERR)
      return 0;
  }
  if (dmax - dmin == 0) {
    ar = 0;
  } else {
    ar = (1 - (dtrue - dmin) / (dmax - dmin)) * 1000.0;
    ar += 0.5;  // rounding
  }
  return (int32)ar;
}
