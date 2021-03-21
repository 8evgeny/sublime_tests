#include "main.h"

int main(int argc, char* argv[]) {
  char sdate_save[AS_MAXCH];
  char s1[AS_MAXCH], s2[AS_MAXCH];
  char *sp, *sp2;
  char* spno;
  char* plsel = PLSEL_D;
#if HPUNIX
  char hostname[80];
#endif
  int i, j, n, iflag_f = -1, iflgt;
  int line_count, line_limit = 36525;  // days in a century
  double daya;
  double top_long = 0.0; /* Greenwich UK */
  double top_lat = 51.5;
  double top_elev = 0;
  AS_BOOL have_geopos = FALSE;
  int ihsy = 'P';
  AS_BOOL do_houses = FALSE;
  char ephepath[AS_MAXCH];
  char fname[AS_MAXCH];
  char sdate[AS_MAXCH];
  char* begindate = NULL;
  char stimein[AS_MAXCH];
  char stimeout[AS_MAXCH];
  int32 iflgret;
  AS_BOOL is_first = TRUE;
  AS_BOOL with_glp = FALSE;
  AS_BOOL with_header_always = FALSE;
  AS_BOOL do_ayanamsa = FALSE;
  AS_BOOL do_planeto_centric = FALSE;
  double aya_t0 = 0, aya_val0 = 0;
  AS_BOOL no_speed = FALSE;
  int32 sid_mode = SE_SIDM_FAGAN_BRADLEY;
  double t2, tstep = 1, thour = 0;
  double delt;
  double tid_acc = 0;
  datm[0] = 1013.25;
  datm[1] = 15;
  datm[2] = 40;
  datm[3] = 0;
  dobs[0] = 0;
  dobs[1] = 0;
  dobs[2] = 0;
  dobs[3] = 0;
  dobs[4] = 0;
  dobs[5] = 0;
  serr[0] = serr_save[0] = serr_warn[0] = sdate_save[0] = '\0';

  *stimein = '\0';
  strcpy(ephepath, "");
  strcpy(fname, SE_FNAME_DFT);

  for (i = 1; i < argc; i++) {
    if (strncmp(argv[i], "-utc", 4) == 0) {
      universal_time = TRUE;
      universal_time_utc = TRUE;
      if (strlen(argv[i]) > 4) {
        strncpy(stimein, argv[i] + 4, 30);
        stimein[30] = '\0';
      }
    } else if (strncmp(argv[i], "-ut", 3) == 0) {
      universal_time = TRUE;
      if (strlen(argv[i]) > 3) {
        strncpy(stimein, argv[i] + 3, 30);
        stimein[30] = '\0';
      }
    } else if (strncmp(argv[i], "-glp", 4) == 0) {
      with_glp = TRUE;
    } else if (strncmp(argv[i], "-hor", 4) == 0) {
      list_hor = TRUE;
    } else if (strncmp(argv[i], "-head", 5) == 0) {
      with_header = FALSE;
    } else if (strncmp(argv[i], "+head", 5) == 0) {
      with_header_always = TRUE;
    } else if (strcmp(argv[i], "-j2000") == 0) {
      iflag |= SEFLG_J2000;
    } else if (strcmp(argv[i], "-icrs") == 0) {
      iflag |= SEFLG_ICRS;
    } else if (strcmp(argv[i], "-cob") == 0) {
      iflag |= SEFLG_CENTER_BODY;
    } else if (strncmp(argv[i], "-ay", 3) == 0) {
      do_ayanamsa = TRUE;
      sid_mode = atol(argv[i] + 3);
      /*swe_set_sid_mode(sid_mode, 0, 0);*/
    } else if (strncmp(argv[i], "-sidt0", 6) == 0) {
      iflag |= SEFLG_SIDEREAL;
      sid_mode = atol(argv[i] + 6);
      if (sid_mode == 0) sid_mode = SE_SIDM_FAGAN_BRADLEY;
      sid_mode |= SE_SIDBIT_ECL_T0;
      /*swe_set_sid_mode(sid_mode, 0, 0);*/
    } else if (strncmp(argv[i], "-sidsp", 6) == 0) {
      iflag |= SEFLG_SIDEREAL;
      sid_mode = atol(argv[i] + 6);
      if (sid_mode == 0) sid_mode = SE_SIDM_FAGAN_BRADLEY;
      sid_mode |= SE_SIDBIT_SSY_PLANE;
    } else if (strncmp(argv[i], "-sidudef", 8) == 0) {
      iflag |= SEFLG_SIDEREAL;
      sid_mode = SE_SIDM_USER;
      strcpy(s1, argv[i] + 8);
      aya_t0 = atof(s1);
      if ((sp = strchr(s1, ',')) != NULL) {
        aya_val0 = atof(sp + 1);
      }
      if (strstr(sp, "jdisut") != NULL) {
        sid_mode |= SE_SIDBIT_USER_UT;
      }
      /*swe_set_sid_mode(sid_mode, 0, 0);*/
    } else if (strncmp(argv[i], "-sidbit", 7) == 0) {
      sid_mode |= atoi(argv[i] + 7);
    } else if (strncmp(argv[i], "-sid", 4) == 0) {
      iflag |= SEFLG_SIDEREAL;
      sid_mode = atol(argv[i] + 4);
      /*if (sid_mode > 0)
        swe_set_sid_mode(sid_mode, 0, 0);*/
    } else if (strcmp(argv[i], "-jplhora") == 0) {
      iflag |= SEFLG_JPLHOR_APPROX;
    } else if (strcmp(argv[i], "-tpm") == 0) {
      iflag |= SEFLG_TEST_PLMOON;
    } else if (strcmp(argv[i], "-jplhor") == 0) {
      iflag |= SEFLG_JPLHOR;
    } else if (strncmp(argv[i], "-j", 2) == 0) {
      begindate = argv[i] + 1;
    } else if (strncmp(argv[i], "-ejpl", 5) == 0) {
      whicheph = SEFLG_JPLEPH;
      if (*(argv[i] + 5) != '\0') {
        strncpy(fname, argv[i] + 5, AS_MAXCH - 1);
        fname[AS_MAXCH - 1] = '\0';
      }
    } else if (strncmp(argv[i], "-edir", 5) == 0) {
      if (*(argv[i] + 5) != '\0') {
        strncpy(ephepath, argv[i] + 5, AS_MAXCH - 1);
        ephepath[AS_MAXCH - 1] = '\0';
      }
    } else if (strcmp(argv[i], "-eswe") == 0) {
      whicheph = SEFLG_SWIEPH;
    } else if (strcmp(argv[i], "-emos") == 0) {
      whicheph = SEFLG_MOSEPH;
    } else if (strncmp(argv[i], "-helflag", 8) == 0) {
      helflag = atoi(argv[i] + 8);
      if (helflag >= SE_HELFLAG_AV) hel_using_AV = TRUE;
    } else if (strcmp(argv[i], "-hel") == 0) {
      iflag |= SEFLG_HELCTR;
    } else if (strcmp(argv[i], "-bary") == 0) {
      iflag |= SEFLG_BARYCTR;
    } else if (strncmp(argv[i], "-house", 6) == 0) {
      sout[0] = '\0';
      sout[1] = '\0';
      sp = argv[i] + 6;
      if (*sp == '[') sp++;
      sscanf(sp, "%lf,%lf,%c", &top_long, &top_lat, sout);
      top_elev = 0;
      if (*sout) ihsy = sout[0];
      do_houses = TRUE;
      have_geopos = TRUE;
    } else if (strncmp(argv[i], "-hsy", 4) == 0) {
      ihsy = *(argv[i] + 4);
      if (ihsy == '\0') ihsy = 'P';
      if (strlen(argv[i]) > 5) hpos_meth = atoi(argv[i] + 5);
      have_geopos = TRUE;
    } else if (strncmp(argv[i], "-topo", 5) == 0) {
      iflag |= SEFLG_TOPOCTR;
      sp = argv[i] + 5;
      if (*sp == '[') sp++;
      sscanf(sp, "%lf,%lf,%lf", &top_long, &top_lat, &top_elev);
      have_geopos = TRUE;
    } else if (strncmp(argv[i], "-geopos", 7) == 0) {
      sp = argv[i] + 7;
      if (*sp == '[') sp++;
      sscanf(sp, "%lf,%lf,%lf", &top_long, &top_lat, &top_elev);
      have_geopos = TRUE;
    } else if (strcmp(argv[i], "-true") == 0) {
      iflag |= SEFLG_TRUEPOS;
    } else if (strcmp(argv[i], "-noaberr") == 0) {
      iflag |= SEFLG_NOABERR;
    } else if (strcmp(argv[i], "-nodefl") == 0) {
      iflag |= SEFLG_NOGDEFL;
    } else if (strcmp(argv[i], "-nonut") == 0) {
      iflag |= SEFLG_NONUT;
    } else if (strcmp(argv[i], "-speed3") == 0) {
      iflag |= SEFLG_SPEED3;
    } else if (strcmp(argv[i], "-speed") == 0) {
      iflag |= SEFLG_SPEED;
    } else if (strcmp(argv[i], "-nospeed") == 0) {
      no_speed = TRUE;
    } else if (strncmp(argv[i], "-testaa", 7) == 0) {
      whicheph = SEFLG_JPLEPH;
      strcpy(fname, SE_FNAME_DE200);
      if (strcmp(argv[i] + 7, "95") == 0) begindate = "j2449975.5";
      if (strcmp(argv[i] + 7, "96") == 0) begindate = "j2450442.5";
      if (strcmp(argv[i] + 7, "97") == 0) begindate = "j2450482.5";
      fmt = "PADRu";
      universal_time = FALSE;
      plsel = "3";
    } else if (strncmp(argv[i], "-lmt", 4) == 0) {
      universal_time = TRUE;
      time_flag |= BIT_TIME_LMT;
      if (strlen(argv[i]) > 4) {
        strncpy(stimein, argv[i] + 4, 30);
        stimein[30] = '\0';
      }
    } else if (strcmp(argv[i], "-lat") == 0) {
      universal_time = TRUE;
      time_flag |= BIT_TIME_LAT;
    } else if (strcmp(argv[i], "-lim") == 0) {
      show_file_limit = TRUE;
    } else if (strcmp(argv[i], "-clink") == 0) {
      with_chart_link = TRUE;
    } else if (strcmp(argv[i], "-lunecl") == 0) {
      special_event = SP_LUNAR_ECLIPSE;
    } else if (strcmp(argv[i], "-solecl") == 0) {
      special_event = SP_SOLAR_ECLIPSE;
      have_geopos = TRUE;
    } else if (strcmp(argv[i], "-short") == 0) {
      short_output = TRUE;
    } else if (strcmp(argv[i], "-occult") == 0) {
      special_event = SP_OCCULTATION;
      have_geopos = TRUE;
    } else if (strcmp(argv[i], "-ep") == 0) {
      output_extra_prec = TRUE;
    } else if (strcmp(argv[i], "-hocal") == 0) {
      /* used to create a listing for inclusion in hocal.c source code */
      special_mode |= SP_MODE_HOCAL;
    } else if (strcmp(argv[i], "-how") == 0) {
      special_mode |= SP_MODE_HOW;
    } else if (strcmp(argv[i], "-total") == 0) {
      search_flag |= SE_ECL_TOTAL;
    } else if (strcmp(argv[i], "-annular") == 0) {
      search_flag |= SE_ECL_ANNULAR;
    } else if (strcmp(argv[i], "-anntot") == 0) {
      search_flag |= SE_ECL_ANNULAR_TOTAL;
    } else if (strcmp(argv[i], "-partial") == 0) {
      search_flag |= SE_ECL_PARTIAL;
    } else if (strcmp(argv[i], "-penumbral") == 0) {
      search_flag |= SE_ECL_PENUMBRAL;
    } else if (strcmp(argv[i], "-noncentral") == 0) {
      search_flag &= ~SE_ECL_CENTRAL;
      search_flag |= SE_ECL_NONCENTRAL;
    } else if (strcmp(argv[i], "-central") == 0) {
      search_flag &= ~SE_ECL_NONCENTRAL;
      search_flag |= SE_ECL_CENTRAL;
    } else if (strcmp(argv[i], "-local") == 0) {
      special_mode |= SP_MODE_LOCAL;
    } else if (strcmp(argv[i], "-rise") == 0) {
      special_event = SP_RISE_SET;
      have_geopos = TRUE;
    } else if (strcmp(argv[i], "-norefrac") == 0) {
      norefrac = 1;
    } else if (strcmp(argv[i], "-disccenter") == 0) {
      disccenter = 1;
    } else if (strcmp(argv[i], "-hindu") == 0) {
      hindu = 1;
      norefrac = 1;
      disccenter = 1;
    } else if (strcmp(argv[i], "-discbottom") == 0) {
      discbottom = 1;
    } else if (strcmp(argv[i], "-metr") == 0) {
      special_event = SP_MERIDIAN_TRANSIT;
      have_geopos = TRUE;
      /* undocumented test feature */
    } else if (strncmp(argv[i], "-amod", 5) == 0) {
      astro_models = argv[i] + 5;
      do_set_astro_models = TRUE;
      /* undocumented test feature */
    } else if (strncmp(argv[i], "-tidacc", 7) == 0) {
      tid_acc = atof(argv[i] + 7);
    } else if (strncmp(argv[i], "-hev", 4) == 0) {
      special_event = SP_HELIACAL;
      search_flag = 0;
      sp = argv[i] + 4;
      if (*sp == '[') sp++;
      if (strlen(sp) > 0) search_flag = atoi(sp);
      have_geopos = TRUE;
      if (strstr(argv[i], "AV")) hel_using_AV = TRUE;
    } else if (strncmp(argv[i], "-at", 3) == 0) {
      sp = argv[i] + 3;
      if (*sp == '[') sp++;
      j = 0;
      while (j < 4 && sp != NULL) {
        datm[j] = atof(sp);
        sp = strchr(sp, ',');
        if (sp != NULL) sp += 1;
        j++;
      }
    } else if (strncmp(argv[i], "-obs", 4) == 0) {
      sp = argv[i] + 4;
      if (*sp == '[') sp++;
      sscanf(sp, "%lf,%lf", &(dobs[0]), &(dobs[1]));
    } else if (strncmp(argv[i], "-opt", 4) == 0) {
      sp = argv[i] + 4;
      if (*sp == '[') sp++;
      sscanf(sp, "%lf,%lf,%lf,%lf,%lf,%lf", &(dobs[0]), &(dobs[1]), &(dobs[2]),
             &(dobs[3]), &(dobs[4]), &(dobs[5]));
    } else if (strcmp(argv[i], "-orbel") == 0) {
      do_orbital_elements = TRUE;
    } else if (strcmp(argv[i], "-bwd") == 0) {
      direction = -1;
      direction_flag = TRUE;
    } else if (strncmp(argv[i], "-pc", 3) == 0) {
      iplctr = atoi(argv[i] + 3);
      do_planeto_centric = TRUE;
    } else if (strncmp(argv[i], "-p", 2) == 0) {
      spno = argv[i] + 2;
      switch (*spno) {
        case 'd':
          /*
          case '\0':
          case ' ':
          */
          plsel = PLSEL_D;
          break;
        case 'p':
          plsel = PLSEL_P;
          break;
        case 'h':
          plsel = PLSEL_H;
          break;
        case 'a':
          plsel = PLSEL_A;
          break;
        default:
          plsel = spno;
      }
    } else if (strncmp(argv[i], "-xs", 3) == 0) {
      /* number of asteroid */
      strncpy(sastno, argv[i] + 3, AS_MAXCH - 1);
      sastno[AS_MAXCH - 1] = '\0';
    } else if (strncmp(argv[i], "-xv", 3) == 0) {
      /* number of planetary moon */
      strncpy(sastno, argv[i] + 3, AS_MAXCH - 1);
      sastno[AS_MAXCH - 1] = '\0';
    } else if (strncmp(argv[i], "-xf", 3) == 0) {
      /* name or number of fixed star */
      strncpy(star, argv[i] + 3, AS_MAXCH - 1);
      star[AS_MAXCH - 1] = '\0';
    } else if (strncmp(argv[i], "-xz", 3) == 0) {
      /* number of hypothetical body */
      strncpy(shyp, argv[i] + 3, AS_MAXCH - 1);
      shyp[AS_MAXCH - 1] = '\0';
    } else if (strncmp(argv[i], "-x", 2) == 0) {
      /* name or number of fixed star */
      strncpy(star, argv[i] + 2, AS_MAXCH - 1);
      star[AS_MAXCH - 1] = '\0';
    } else if (strcmp(argv[i], "-nut") == 0) {
      inut = TRUE;
    } else if (strncmp(argv[i], "-n", 2) == 0) {
      nstep = atoi(argv[i] + 2);
      if (nstep == 0) nstep = 20;
    } else if (strncmp(argv[i], "-i", 2) == 0) {
      iflag_f = atoi(argv[i] + 2);
      if (iflag_f & SEFLG_XYZ) fmt = "PX";
    } else if (strcmp(argv[i], "-swefixstar2") == 0) {
      use_swe_fixstar2 = TRUE;
    } else if (strncmp(argv[i], "-s", 2) == 0) {
      tstep = atof(argv[i] + 2);
      if (*(argv[i] + strlen(argv[i]) - 1) == 'm') step_in_minutes = TRUE;
      if (*(argv[i] + strlen(argv[i]) - 1) == 's') step_in_seconds = TRUE;
      if (*(argv[i] + strlen(argv[i]) - 1) == 'y') step_in_years = TRUE;
      if (*(argv[i] + strlen(argv[i]) - 1) == 'o') {
        step_in_minutes = FALSE;
        step_in_months = TRUE;
      }
    } else if (strncmp(argv[i], "-b", 2) == 0) {
      begindate = argv[i] + 2;
    } else if (strncmp(argv[i], "-f", 2) == 0) {
      fmt = argv[i] + 2;
    } else if (strncmp(argv[i], "-g", 2) == 0) {
      gap = argv[i] + 2;
      have_gap_parameter = TRUE;
      if (*gap == '\0') gap = "\t";
    } else if (strcmp(argv[i], "-dms") == 0) {
      use_dms = TRUE;
    } else if (strncmp(argv[i], "-d", 2) == 0 ||
               strncmp(argv[i], "-D", 2) == 0) {
      diff_mode = *(argv[i] + 1); /* 'd' or 'D' */
      sp = argv[i] + 2;
      if (*(argv[i] + 2) == 'h') {
        sp++;
        diff_mode = 'h';  // diff helio to geo
      }
      ipldiff = letter_to_ipl((int)*sp);
      if (ipldiff < 0) ipldiff = SE_SUN;
      swe_get_planet_name(ipldiff, spnam2);
    } else if (strcmp(argv[i], "-roundsec") == 0) {
      round_flag |= BIT_ROUND_SEC;
    } else if (strcmp(argv[i], "-roundmin") == 0) {
      round_flag |= BIT_ROUND_MIN;
      /*} else if (strncmp(argv[i], "-timeout", 8) == 0) {
        swe_set_timeout(atoi(argv[i]) + 8);*/
    } else if (strncmp(argv[i], "-t", 2) == 0) {
      if (strlen(argv[i]) > 2) {
        strncat(stimein, argv[i] + 2, 30);
        stimein[30] = '\0';
      }
    } else if (strncmp(argv[i], "-h", 2) == 0 ||
               strncmp(argv[i], "-?", 2) == 0) {
      sp = argv[i] + 2;
      if (*sp == 'c' || *sp == '\0') {
        // char si0[strlen(infocmd0)+1]; // Microsoft Visual Studio does not
        // like this
        char si0[2000];
        swe_version(sout);
        strcpy(si0, infocmd0);
        sp2 = strstr(si0, "Version:");
        if (sp2 != NULL && strlen(sp2) > 10 + strlen(sout))
          strcpy(sp2 + 9, sout);
        fputs(si0, stdout);
        fputs(infocmd1, stdout);
        fputs(infocmd2, stdout);
        fputs(infocmd3, stdout);
        fputs(infocmd4, stdout);
        fputs(infocmd5, stdout);
        fputs(infocmd6, stdout);
      }
      if (*sp == 'p' || *sp == '\0') fputs(infoplan, stdout);
      if (*sp == 'f' || *sp == '\0') {
        fputs(infoform, stdout);
        fputs(infoform2, stdout);
      }
      if (*sp == 'd' || *sp == '\0') fputs(infodate, stdout);
      if (*sp == 'e' || *sp == '\0') fputs(infoexamp, stdout);
      goto end_main;
    } else {
      strcpy(sout, "illegal option ");
      strncat(sout, argv[i], 100);
      sout[100] = '\0';
      strcat(sout, "\n");
      fputs(sout, stdout);
      exit(1);
    }
  }

  if (special_event == SP_OCCULTATION || special_event == SP_RISE_SET ||
      special_event == SP_MERIDIAN_TRANSIT || special_event == SP_HELIACAL) {
    ipl = letter_to_ipl(*plsel);
    if (*plsel == 'f') {
      ipl = SE_FIXSTAR;
    } else {
      if (*plsel == 's') ipl = atoi(sastno) + SE_AST_OFFSET;
      *star = '\0';
    }
    if (special_event == SP_OCCULTATION && ipl == 1)
      ipl = 2; /* no occultation of moon by moon */
  }
  if (*stimein != '\0') {
    t = 0;
    if ((sp = strchr(stimein, ':')) != NULL) {
      if ((sp2 = strchr(sp + 1, ':')) != NULL) {
        t += atof(sp2 + 1) / 60.0;
      }
      t += atoi(sp + 1);
      t /= 60.0;
    }
    if (atoi(stimein) < 0) t = -t;
    t += atoi(stimein);
    // t += 0.0000000001;
    thour = t;
  }
#if HPUNIX
  gethostname(hostname, 80);
  if (strstr(hostname, "as10") != NULL) line_limit = 1000;
#endif

  if (with_header) {
    for (i = 0; i < argc; i++) {
      fputs(argv[i], stdout);
      printf(" ");
    }
  }
  iflag = (iflag & ~SEFLG_EPHMASK) | whicheph;
  if (strpbrk(fmt, "SsQ") != NULL && !(iflag & SEFLG_SPEED3) && !no_speed)
    iflag |= SEFLG_SPEED;
  if (*ephepath == '\0') {
    if (make_ephemeris_path(argv[0], ephepath) == ERR) {
      iflag = (iflag & ~SEFLG_EPHMASK) | SEFLG_MOSEPH;
      whicheph = SEFLG_MOSEPH;
    }
  }
  if (whicheph != SEFLG_MOSEPH) swe_set_ephe_path(ephepath);
  if (whicheph & SEFLG_JPLEPH) swe_set_jpl_file(fname);
  /* the following is only a test feature */
  if (do_set_astro_models) {
    swe_set_astro_models(astro_models,
                         iflag); /* secret test feature for dieter */
    swe_get_astro_models(astro_models, smod, iflag);
  }
#if 1
  if (inut) /* Astrodienst internal feature */
    swe_set_interpolate_nut(TRUE);
#endif
  if ((iflag & SEFLG_SIDEREAL) || do_ayanamsa) {
    if (sid_mode & SE_SIDM_USER)
      swe_set_sid_mode(sid_mode, aya_t0, aya_val0);
    else
      swe_set_sid_mode(sid_mode, 0, 0);
  }
  geopos[0] = top_long;
  geopos[1] = top_lat;
  geopos[2] = top_elev;
  swe_set_topo(top_long, top_lat, top_elev);
  if (tid_acc != 0) swe_set_tid_acc(tid_acc);
  serr[0] = serr_save[0] = serr_warn[0] = '\0';

  begindate = "17-11-1966";

  //******************************************************************
  while (TRUE) {
    if (begindate == NULL) {
      printf("\nDate ?");
      sdate[0] = '\0';
      if (!fgets(sdate, AS_MAXCH, stdin)) goto end_main;
    } else {
      strncpy(sdate, begindate, AS_MAXCH - 1);
      sdate[AS_MAXCH - 1] = '\0';
      begindate = "."; /* to exit afterwards */
    }
    if (strcmp(sdate, "-bary") == 0) {
      iflag = iflag & ~SEFLG_HELCTR;
      iflag |= SEFLG_BARYCTR;
      *sdate = '\0';
    } else if (strcmp(sdate, "-hel") == 0) {
      iflag = iflag & ~SEFLG_BARYCTR;
      iflag |= SEFLG_HELCTR;
      *sdate = '\0';
    } else if (strcmp(sdate, "-geo") == 0) {
      iflag = iflag & ~SEFLG_BARYCTR;
      iflag = iflag & ~SEFLG_HELCTR;
      *sdate = '\0';
    } else if (strcmp(sdate, "-ejpl") == 0) {
      iflag &= ~SEFLG_EPHMASK;
      iflag |= SEFLG_JPLEPH;
      *sdate = '\0';
    } else if (strcmp(sdate, "-eswe") == 0) {
      iflag &= ~SEFLG_EPHMASK;
      iflag |= SEFLG_SWIEPH;
      *sdate = '\0';
    } else if (strcmp(sdate, "-emos") == 0) {
      iflag &= ~SEFLG_EPHMASK;
      iflag |= SEFLG_MOSEPH;
      *sdate = '\0';
    } else if (strncmp(sdate, "-xs", 3) == 0) {
      /* number of asteroid */
      strcpy(sastno, sdate + 3);
      *sdate = '\0';
    }
    sp = sdate;
    if (*sp == '.') {
      goto end_main;
    } else if (*sp == '\0' || *sp == '\n' || *sp == '\r') {
      strcpy(sdate, sdate_save);
    } else {
      strcpy(sdate_save, sdate);
    }
    if (*sdate == '\0') {
      sprintf(sdate, "j%f", tjd);
    }
    if (*sp == 'j') { /* it's a day number */
      if ((sp2 = strchr(sp, ',')) != NULL) *sp2 = '.';
      sscanf(sp + 1, "%lf", &tjd);
      if (tjd < 2299160.5)
        gregflag = SE_JUL_CAL;
      else
        gregflag = SE_GREG_CAL;
      if (strstr(sp, "jul") != NULL)
        gregflag = SE_JUL_CAL;
      else if (strstr(sp, "greg") != NULL)
        gregflag = SE_GREG_CAL;
      swe_revjul(tjd, gregflag, &jyear, &jmon, &jday, &jut);
    } else if (*sp == '+') {
      n = atoi(sp);
      if (n == 0) n = 1;
      tjd += n;
      swe_revjul(tjd, gregflag, &jyear, &jmon, &jday, &jut);
    } else if (*sp == '-') {
      n = atoi(sp);
      if (n == 0) n = -1;
      tjd += n;
      swe_revjul(tjd, gregflag, &jyear, &jmon, &jday, &jut);
    } else {
      if (sscanf(sp, "%d%*c%d%*c%d", &jday, &jmon, &jyear) < 1) exit(1);
      if ((int32)jyear * 10000L + (int32)jmon * 100L + (int32)jday < 15821015L)
        gregflag = SE_JUL_CAL;
      else
        gregflag = SE_GREG_CAL;
      if (strstr(sp, "jul") != NULL)
        gregflag = SE_JUL_CAL;
      else if (strstr(sp, "greg") != NULL)
        gregflag = SE_GREG_CAL;
      jut = 0;
      if (universal_time_utc) {
        int ih = 0, im = 0;
        double ds = 0.0;
        if (*stimein != '\0') {
          sscanf(stimein, "%d:%d:%lf", &ih, &im, &ds);
        }
        if (swe_utc_to_jd(jyear, jmon, jday, ih, im, ds, gregflag, tret,
                          serr) == ERR) {
          printf(" error in swe_utc_to_jd(): %s\n", serr);
          exit(-1);
        }
        tjd = tret[1];
      } else {
        tjd = swe_julday(jyear, jmon, jday, jut, gregflag);
        tjd += thour / 24.0;
      }
    }
    if (special_event > 0) {
      do_special_event(tjd, ipl, star, special_event, special_mode, geopos,
                       datm, dobs, serr);
      swe_close();
      return OK;
    }
    line_count = 0;
    for (t = tjd, istep = 1; istep <= nstep; t += tstep, istep++) {
      if (step_in_minutes) t = tjd + (istep - 1) * tstep / 1440;
      if (step_in_seconds) t = tjd + (istep - 1) * tstep / 86400;
      if (step_in_years) {
        swe_revjul(tjd, gregflag, &jyear, &jmon, &jday, &jut);
        t = swe_julday(jyear + (istep - 1) * (int)tstep, jmon, jday, jut,
                       gregflag);
      }
      if (step_in_months) {
        swe_revjul(tjd, gregflag, &jyear, &jmon, &jday, &jut);
        jmon += (istep - 1) * (int)tstep;
        jyear += (int)((jmon - 1) / 12);
        jmon = ((jmon - 1) % 12) + 1;
        t = swe_julday(jyear, jmon, jday, jut, gregflag);
      }
      if (t < 2299160.5)
        gregflag = SE_JUL_CAL;
      else
        gregflag = SE_GREG_CAL;
      if (strstr(sdate, "jul") != NULL)
        gregflag = SE_JUL_CAL;
      else if (strstr(sdate, "greg") != NULL)
        gregflag = SE_GREG_CAL;
      delt = swe_deltat_ex(t, iflag, serr);
      if (!universal_time) {
        delt = swe_deltat_ex(t - delt, iflag, serr);
      }
      t2 = t;
      // output line:
      // "date (dmy) 4.6.2017 greg.   2:07:00 TT		version 2.07.02"
      swe_revjul(t2, gregflag, &jyear, &jmon, &jday, &jut);
      if (with_header) {
#ifndef NO_SWE_GLP  // -DNO_SWE_GLP to suppress this function
        if (with_glp) {
          swe_get_library_path(sout);
          printf("\npath: %s", sout);
        }
#endif
        printf("\ndate (dmy) %d.%d.%d", jday, jmon, jyear);
        if (gregflag)
          printf(" greg.");
        else
          printf(" jul.");
        jd_to_time_string(jut, stimeout);
        printf(stimeout);
        if (universal_time) {
          if (time_flag & BIT_TIME_LMT)
            printf(" LMT");
          else
            printf(" UT");
        } else {
          printf(" TT");
        }
        printf("\t\tversion %s", swe_version(sout));
      }
      if (universal_time) {
        // "LMT: 2457908.588194444"
        if (time_flag & BIT_TIME_LMT) {
          if (with_header) {
            printf("\nLMT: %.9f", t);
            t -= geopos[0] / 15.0 / 24.0;
          }
        }
        // "UT:  2457908.565972222     delta t: 68.761612 sec"
        if (with_header) {
          printf("\nUT:  %.9f", t);
          printf("     delta t: %f sec", delt * 86400.0);
        }
        te = t + delt;
        tut = t;
      } else {
        te = t;
        tut = t - delt;
        // "UT:  2457908.565972222     delta t: 68.761612 sec"
        if (with_header) {
          printf("\nUT:  %.9f", tut);
          printf("     delta t: %f sec", delt * 86400.0);
        }
      }
      iflgret = swe_calc(te, SE_ECL_NUT, iflag, xobl, serr);
      if (with_header) {
        // "TT:  2457908.566768074
        printf("\nTT:  %.9f", te);
        // "ayanamsa =   24° 5'51.6509 (Lahiri)"
        if (iflag & SEFLG_SIDEREAL) {
          if (swe_get_ayanamsa_ex(te, iflag, &daya, serr) == ERR) {
            printf("   error in swe_get_ayanamsa_ex(): %s\n", serr);
            exit(1);
          }
          printf("   ayanamsa = %s (%s)", dms(daya, round_flag),
                 swe_get_ayanamsa_name(sid_mode));
        }
        // "geo. long 8.000000, lat 47.000000, alt 0.000000"
        if (have_geopos) {
          printf("\ngeo. long %f, lat %f, alt %f", geopos[0], geopos[1],
                 geopos[2]);
        }
        if (iflag_f >= 0) iflag = iflag_f;
        if (strchr(plsel, 'o') == NULL) {
          if (iflag & (SEFLG_NONUT | SEFLG_SIDEREAL)) {
            printf("\n%-15s %s", "Epsilon (m)", dms(xobl[0], round_flag));
          } else {
            printf("\n%-15s %s%s", "Epsilon (t/m)", dms(xobl[0], round_flag),
                   gap);
            printf("%s", dms(xobl[1], round_flag));
          }
        }
        if (strchr(plsel, 'n') == NULL &&
            !(iflag & (SEFLG_NONUT | SEFLG_SIDEREAL))) {
          fputs("\nNutation        ", stdout);
          fputs(dms(xobl[2], round_flag), stdout);
          fputs(gap, stdout);
          fputs(dms(xobl[3], round_flag), stdout);
        }
        printf("\n");
        if (do_houses) {
          char* shsy = swe_house_name(ihsy);
          if (!universal_time) {
            do_houses = FALSE;
            printf("option -house requires option -ut for Universal Time\n");
          } else {
            strcpy(s1, dms(top_long, round_flag));
            strcpy(s2, dms(top_lat, round_flag));
            printf("Houses system %c (%s) for long=%s, lat=%s\n", ihsy, shsy,
                   s1, s2);
          }
        }
      }
      if (with_header && !with_header_always) with_header = FALSE;
      if (do_ayanamsa) {
        if (swe_get_ayanamsa_ex(te, iflag, &daya, serr) == ERR) {
          printf("   error in swe_get_ayanamsa_ex(): %s\n", serr);
          exit(1);
        }
        x[0] = daya;
        print_line(MODE_AYANAMSA, TRUE, sid_mode);
        continue;
      }
      if (t == tjd && strchr(plsel, 'e')) {
        if (list_hor) {
          is_first = TRUE;
          for (psp = plsel; *psp != '\0'; psp++) {
            if (*psp == 'e') continue;
            ipl = letter_to_ipl((int)*psp);
            *spnam = '\0';
            if (ipl >= SE_SUN && ipl <= SE_VESTA)
              swe_get_planet_name(ipl, spnam);
            print_line(MODE_LABEL, is_first, 0);
            is_first = FALSE;
          }
          printf("\n");
        } else {
          print_line(MODE_LABEL, TRUE, 0);
        }
      }
      is_first = TRUE;
      for (psp = plsel; *psp != '\0'; psp++) {
        if (*psp == 'e') continue;
        ipl = letter_to_ipl((int)*psp);
        if (ipl == -2) {
          printf("illegal parameter -p%s\n", plsel);
          exit(1);
        }
        if (*psp == 'f')  // fixed star
          ipl = SE_FIXSTAR;
        else if (*psp == 's')  // asteroid
          ipl = atoi(sastno) + 10000;
        else if (*psp == 'v')  // planetary moon
          ipl = atoi(sastno);
        else if (*psp == 'z')  // fictitious object
          ipl = atoi(shyp) + SE_FICT_OFFSET_1;
        if (iflag & SEFLG_HELCTR) {
          if (ipl == SE_SUN || ipl == SE_MEAN_NODE || ipl == SE_TRUE_NODE ||
              ipl == SE_MEAN_APOG || ipl == SE_OSCU_APOG)
            continue;
        } else if (iflag & SEFLG_BARYCTR) {
          if (ipl == SE_MEAN_NODE || ipl == SE_TRUE_NODE ||
              ipl == SE_MEAN_APOG || ipl == SE_OSCU_APOG)
            continue;
        } else { /* geocentric */
          if (ipl == SE_EARTH && !do_orbital_elements) continue;
        }
        /* ecliptic position */
        if (iflag_f >= 0) iflag = iflag_f;
        if (ipl == SE_FIXSTAR) {
          iflgret = call_swe_fixstar(star, te, iflag, x, serr);
          /* magnitude, etc. */
          if (iflgret != ERR && strpbrk(fmt, "=") != NULL) {
            double mag;
            iflgret = swe_fixstar_mag(star, &mag, serr);
            attr[4] = mag;
          }
          strcpy(se_pname, star);
        } else if (do_planeto_centric) {
          iflgret = swe_calc_pctr(te, ipl, iplctr, iflag, x, serr);
          swe_get_planet_name(ipl, se_pname);
        } else {
          iflgret = swe_calc(te, ipl, iflag, x, serr);
          /* phase, magnitude, etc. */
          if (iflgret != ERR && strpbrk(fmt, "+-*/=") != NULL)
            iflgret = swe_pheno(te, ipl, iflag, attr, serr);
          swe_get_planet_name(ipl, se_pname);
          if (show_file_limit && ipl > SE_AST_OFFSET) {
            const char* fnam;
            char sbeg[40], send[40];
            double tfstart, tfend;
            int denum;
            fnam = swe_get_current_file_data(3, &tfstart, &tfend, &denum);
            if (fnam != NULL) {
              swe_revjul(tfstart, gregflag, &jyear, &jmon, &jday, &jut);
              sprintf(sbeg, "%d.%02d.%04d", jday, jmon, jyear);
              swe_revjul(tfend, gregflag, &jyear, &jmon, &jday, &jut);
              sprintf(send, "%d.%02d.%04d", jday, jmon, jyear);
              printf("range %s: %.1lf = %s to %.1lf = %s de=%d\n", fnam,
                     tfstart, sbeg, tfend, send, denum);
              show_file_limit = FALSE;
            }
          }
        }
        if (*psp == 'q') { /* delta t */
          x[0] = swe_deltat_ex(tut, iflag, serr) * 86400;
          x[1] = x[2] = x[3] = 0;
          x[1] = x[0] / 3600.0;  // to hours
          strcpy(se_pname, "Delta T");
        }
        if (*psp == 'x') { /* sidereal time */
          x[0] = swe_degnorm(swe_sidtime(tut) * 15 + geopos[0]);
          x[1] = x[2] = x[3] = 0;
          strcpy(se_pname, "Sidereal Time");
        }
        if (*psp == 'o') { /* ecliptic is wanted, remove nutation */
          x[2] = x[3] = 0;
          strcpy(se_pname, "Ecl. Obl.");
        }
        if (*psp == 'n') { /* nutation is wanted, remove ecliptic */
          x[0] = x[2];
          x[1] = x[3];
          x[2] = x[3] = 0;
          strcpy(se_pname, "Nutation");
        }
        if (*psp == 'y') { /* time equation */
          iflgret = swe_time_equ(tut, &(x[0]), serr);
          x[0] *= 86400; /* in seconds */
          ;
          x[1] = x[2] = x[3] = 0;
          strcpy(se_pname, "Time Equ.");
        }
        if (*psp == 'b') { /* ayanamsha */
          if (swe_get_ayanamsa_ex(te, iflag, &(x[0]), serr) == ERR) {
            printf("   error in swe_get_ayanamsa_ex(): %s\n", serr);
            iflgret = -1;
          }
          x[1] = 0;
          strcpy(se_pname, "Ayanamsha");
        }
        if (iflgret < 0) {
          if (strcmp(serr, serr_save) != 0 &&
              (ipl == SE_SUN || ipl == SE_MOON || ipl <= SE_PLUTO ||
               ipl == SE_MEAN_NODE || ipl == SE_TRUE_NODE || ipl == SE_CERES ||
               ipl == SE_PALLAS || ipl == SE_JUNO || ipl == SE_VESTA ||
               ipl == SE_CHIRON || ipl == SE_PHOLUS || ipl == SE_CUPIDO ||
               ipl >= SE_PLMOON_OFFSET || ipl >= SE_AST_OFFSET ||
               ipl == SE_FIXSTAR || *psp == 'y')) {
            fputs("error: ", stdout);
            fputs(serr, stdout);
            fputs("\n", stdout);
          }
          strcpy(serr_save, serr);
        } else if (*serr != '\0' && *serr_warn == '\0') {
          if (strstr(serr, "'seorbel.txt' not found") == NULL)
            strcpy(serr_warn, serr);
        }
        if (diff_mode) {
          iflgret = swe_calc(te, ipldiff, iflag, x2, serr);
          if (diff_mode == DIFF_GEOHEL)
            iflgret = swe_calc(te, ipldiff, iflag | SEFLG_HELCTR, x2, serr);
          if (iflgret < 0) {
            fputs("error: ", stdout);
            fputs(serr, stdout);
            fputs("\n", stdout);
          }
          if (diff_mode == DIFF_DIFF || diff_mode == DIFF_GEOHEL) {
            for (i = 1; i < 6; i++) x[i] -= x2[i];
            if ((iflag & SEFLG_RADIANS) == 0)
              x[0] = swe_difdeg2n(x[0], x2[0]);
            else
              x[0] = swe_difrad2n(x[0], x2[0]);
          } else { /* DIFF_MIDP */
            for (i = 1; i < 6; i++) x[i] = (x[i] + x2[i]) / 2;
            if ((iflag & SEFLG_RADIANS) == 0)
              x[0] = swe_deg_midp(x[0], x2[0]);
            else
              x[0] = swe_rad_midp(x[0], x2[0]);
          }
        }
        /* equator position */
        if (strpbrk(fmt, "aADdQ") != NULL) {
          iflag2 = iflag | SEFLG_EQUATORIAL;
          if (ipl == SE_FIXSTAR) {
            iflgret = call_swe_fixstar(star, te, iflag2, xequ, serr);
          } else if (do_planeto_centric) {
            iflgret = swe_calc_pctr(te, ipl, iplctr, iflag2, xequ, serr);
          } else {
            iflgret = swe_calc(te, ipl, iflag2, xequ, serr);
          }
          if (diff_mode) {
            iflgret = swe_calc(te, ipldiff, iflag2, x2, serr);
            if (diff_mode == DIFF_DIFF || diff_mode == DIFF_GEOHEL) {
              if (diff_mode == DIFF_GEOHEL)
                iflgret =
                    swe_calc(te, ipldiff, iflag2 | SEFLG_HELCTR, x2, serr);
              for (i = 1; i < 6; i++) xequ[i] -= x2[i];
              if ((iflag & SEFLG_RADIANS) == 0)
                xequ[0] = swe_difdeg2n(xequ[0], x2[0]);
              else
                xequ[0] = swe_difrad2n(xequ[0], x2[0]);
            } else { /* DIFF_MIDP */
              for (i = 1; i < 6; i++) xequ[i] = (xequ[i] + x2[i]) / 2;
              if ((iflag & SEFLG_RADIANS) == 0)
                xequ[0] = swe_deg_midp(xequ[0], x2[0]);
              else
                xequ[0] = swe_rad_midp(xequ[0], x2[0]);
            }
          }
        }
        /* azimuth and height */
        if (strpbrk(fmt, "IiHhKk") != NULL) {
          /* first, get topocentric equatorial positions */
          iflgt = whicheph | SEFLG_EQUATORIAL | SEFLG_TOPOCTR;
          if (ipl == SE_FIXSTAR)
            iflgret = call_swe_fixstar(star, te, iflgt, xt, serr);
          else
            iflgret = swe_calc(te, ipl, iflgt, xt, serr);
          /* to azimuth/height */
          /* atmospheric pressure "0" has the effect that a value
           * of 1013.25 mbar is assumed at 0 m above sea level.
           * If the altitude of the observer is given (in geopos[2])
           * pressure is estimated according to that */
          swe_azalt(tut, SE_EQU2HOR, geopos, datm[0], datm[1], xt, xaz);
          if (diff_mode) {
            iflgret = swe_calc(te, ipldiff, iflgt, xt, serr);
            swe_azalt(tut, SE_EQU2HOR, geopos, datm[0], datm[1], xt, x2);
            if (diff_mode == DIFF_DIFF || diff_mode == DIFF_GEOHEL) {
              if (diff_mode ==
                  DIFF_GEOHEL) {  // makes little sense for a heliocentric
                iflgret = swe_calc(te, ipldiff, iflgt | SEFLG_HELCTR, xt, serr);
                swe_azalt(tut, SE_EQU2HOR, geopos, datm[0], datm[1], xt, x2);
              }
              for (i = 1; i < 3; i++) xaz[i] -= x2[i];
              if ((iflag & SEFLG_RADIANS) == 0)
                xaz[0] = swe_difdeg2n(xaz[0], x2[0]);
              else
                xaz[0] = swe_difrad2n(xaz[0], x2[0]);
            } else { /* DIFF_MIDP */
              for (i = 1; i < 3; i++) xaz[i] = (xaz[i] + x2[i]) / 2;
              if ((iflag & SEFLG_RADIANS) == 0)
                xaz[0] = swe_deg_midp(xaz[0], x2[0]);
              else
                xaz[0] = swe_rad_midp(xaz[0], x2[0]);
            }
          }
        }
        /* ecliptic cartesian position */
        if (strpbrk(fmt, "XU") != NULL) {
          iflag2 = iflag | SEFLG_XYZ;
          if (ipl == SE_FIXSTAR)
            iflgret = call_swe_fixstar(star, te, iflag2, xcart, serr);
          else
            iflgret = swe_calc(te, ipl, iflag2, xcart, serr);
          if (diff_mode) {
            iflgret = swe_calc(te, ipldiff, iflag2, x2, serr);
            if (diff_mode == DIFF_DIFF || diff_mode == DIFF_GEOHEL) {
              if (diff_mode == DIFF_GEOHEL)
                iflgret =
                    swe_calc(te, ipldiff, iflag2 | SEFLG_HELCTR, x2, serr);
              for (i = 0; i < 6; i++) xcart[i] -= x2[i];
            } else {
              xcart[i] = (xcart[i] + x2[i]) / 2;
            }
          }
        }
        /* equator cartesian position */
        if (strpbrk(fmt, "xu") != NULL) {
          iflag2 = iflag | SEFLG_XYZ | SEFLG_EQUATORIAL;
          if (ipl == SE_FIXSTAR)
            iflgret = call_swe_fixstar(star, te, iflag2, xcartq, serr);
          else
            iflgret = swe_calc(te, ipl, iflag2, xcartq, serr);
          if (diff_mode) {
            iflgret = swe_calc(te, ipldiff, iflag2, x2, serr);
            if (diff_mode == DIFF_DIFF || diff_mode == DIFF_GEOHEL) {
              if (diff_mode == DIFF_GEOHEL)
                iflgret =
                    swe_calc(te, ipldiff, iflag2 | SEFLG_HELCTR, x2, serr);
              for (i = 0; i < 6; i++) xcartq[i] -= x2[i];
            } else {
              xcartq[i] = (xcart[i] + x2[i]) / 2;
            }
          }
        }
        /* house position */
        if (strpbrk(fmt, "gGj") != NULL) {
          armc = swe_degnorm(swe_sidtime(tut) * 15 + geopos[0]);
          for (i = 0; i < 6; i++) xsv[i] = x[i];
          if (hpos_meth == 1) xsv[1] = 0;
          if (ipl == SE_FIXSTAR)
            strcpy(star2, star);
          else
            *star2 = '\0';
          if (hpos_meth >= 2 && toupper(ihsy) == 'G') {
            swe_gauquelin_sector(tut, ipl, star2, iflag, hpos_meth, geopos, 0,
                                 0, &hposj, serr);
          } else {
            double cusp[100];
            if (ihsy == 'i' || ihsy == 'I') {
              iflgret = swe_houses_ex(t, iflag, top_lat, top_long, ihsy, cusp,
                                      cusp + 13);
            }
            hposj = swe_house_pos(armc, geopos[1], xobl[0], ihsy, xsv, serr);
          }
          if (toupper(ihsy) == 'G')
            hpos = (hposj - 1) * 10;
          else
            hpos = (hposj - 1) * 30;
          if (diff_mode) {
            for (i = 0; i < 6; i++) xsv[i] = x2[i];
            if (hpos_meth == 1) xsv[1] = 0;
            hpos2 = swe_house_pos(armc, geopos[1], xobl[0], ihsy, xsv, serr);
            if (toupper(ihsy) == 'G')
              hpos2 = (hpos2 - 1) * 10;
            else
              hpos2 = (hpos2 - 1) * 30;
            if (diff_mode == DIFF_DIFF || diff_mode == DIFF_GEOHEL) {
              if ((iflag & SEFLG_RADIANS) == 0)
                hpos = swe_difdeg2n(hpos, hpos2);
              else
                hpos = swe_difrad2n(hpos, hpos2);
            } else { /* DIFF_MIDP */
              if ((iflag & SEFLG_RADIANS) == 0)
                hpos = swe_deg_midp(hpos, hpos2);
              else
                hpos = swe_rad_midp(hpos, hpos2);
            }
          }
        }
        strcpy(spnam, se_pname);
        print_line(0, is_first, 0);
        is_first = FALSE;
        if (!list_hor) line_count++;
        if (do_orbital_elements) {
          orbital_elements(te, ipl, iflag, serr);
          continue;
        }
        if (line_count >= line_limit) {
          printf("****** line count %d was exceeded\n", line_limit);
          break;
        }
      } /* for psp */
      if (list_hor) {
        printf("\n");
        line_count++;
      }
      if (do_houses) {
        double cusp[37];
        double cusp_speed[37];
        double ascmc[10];
        double ascmc_speed[10];
        int iofs;
        if (toupper(ihsy) == 'G')  // Gauquelin has 36 cusps
          nhouses = 36;
        iofs = nhouses + 1;
        iflgret = swe_houses_ex2(t, iflag, top_lat, top_long, ihsy, cusp, ascmc,
                                 cusp_speed, ascmc_speed, serr);
        // when swe_houses_ex() fails (e.g. with Placidus, Gauquelin,
        // Makranski), it always returns Porphyry cusps instead
        if (iflgret < 0) {
          char* shsy = swe_house_name(ihsy);
          sprintf(serr, "House method %s failed, Porphyry calculated instead",
                  shsy);
          if (strcmp(serr, serr_save) != 0) {
            fputs("error: ", stdout);
            fputs(serr, stdout);
            fputs("\n", stdout);
          }
          strcpy(serr_save, serr);
          ihsy = 'O';
          nhouses = 12;  // instead of 36 with 'G'
          iofs = nhouses + 1;
        }
        is_first = TRUE;
        for (ipl = 1; ipl < iofs + 8; ipl++) {
          x[0] = cusp[ipl];
          if (ipl >= iofs) {
            x[0] = ascmc[ipl - iofs];
            x[3] = ascmc_speed[ipl - iofs];
          } else {
            x[3] = cusp_speed[ipl];
          }
          x[1] = 0;              /* latitude */
          x[2] = 1.0;            /* pseudo radius vector */
          if (ipl == iofs + 2) { /* armc is already equatorial! */
            xequ[0] = x[0];
            xequ[1] = x[1];
            xequ[2] = x[2];
          } else if (strpbrk(fmt, "aADdQ") != NULL) {
            swe_cotrans(x, xequ, -xobl[0]);
          }
          if (strpbrk(fmt, "IiHhKk") != NULL) {
            double gpos[3];
            gpos[0] = top_long;
            gpos[1] = top_lat;
            gpos[2] = 0;
            swe_azalt(t, SE_ECL2HOR, gpos, datm[0], datm[1], x, xaz);
          }
          if (strpbrk(fmt, "gGj") != NULL) {
            hposj = swe_house_pos(armc, geopos[1], xobl[0], ihsy, x, serr);
            if (toupper(ihsy) == 'G')
              hpos = (hposj - 1) * 10;
            else
              hpos = (hposj - 1) * 30;
          }
          print_line(MODE_HOUSE, is_first, 0);
          is_first = FALSE;
          if (!list_hor) line_count++;
        }
        if (list_hor) {
          printf("\n");
          line_count++;
        }
      }
      if (line_count >= line_limit) break;
    } /* for tjd */
    if (*serr_warn != '\0') {
      printf("\nwarning: ");
      fputs(serr_warn, stdout);
      printf("\n");
    }
  } /* while 1 */
/* close open files and free allocated space */
end_main:
  if (do_set_astro_models) {
    printf(smod);
  }
  swe_close();
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

int print_line(int mode, AS_BOOL is_first, int sid_mode) {
  /*
   * The string fmt contains a sequence of format specifiers;
   * each character in fmt creates a column, the columns are
   * sparated by the gap string.
   * Time columns tTJyY are only printed, if is_first is TRUE,
   * so that they are not repeated in list_hor (horizontal list) mode.
   * In list_hor mode, no newline is printed.
   */
  char *sp, *sp2;
  double t2, ju2 = 0;
  double y_frac;
  double ar, sinp;
  double dret[20];
  char slon[20];
  char pnam[30];
  AS_BOOL is_house = ((mode & MODE_HOUSE) != 0);
  AS_BOOL is_label = ((mode & MODE_LABEL) != 0);
  AS_BOOL is_ayana = ((mode & MODE_AYANAMSA) != 0);
  int32 iflgret, dar;
  // build planet name column, just in case
  if (is_house) {
    if (ipl <= nhouses) {
      sprintf(pnam, "house %2d       ", ipl);
    } else {
      sprintf(pnam, "%-15s", hs_nam[ipl - nhouses]);
    }
  } else if (diff_mode == DIFF_DIFF) {
    sprintf(pnam, "%.3s-%.3s", spnam, spnam2);
  } else if (diff_mode == DIFF_GEOHEL) {
    sprintf(pnam, "%.3s-%.3sHel", spnam, spnam2);
  } else if (diff_mode == DIFF_MIDP) {
    sprintf(pnam, "%.3s/%.3s", spnam, spnam2);
  } else {
    sprintf(pnam, "%-15s", spnam);
  }
  if (list_hor && strchr(fmt, 'P') == NULL) {
    sprintf(slon, "%.8s %s", pnam, "long.");
  } else {
    sprintf(slon, "%-14s", "long.");
  }
  for (sp = fmt; *sp != '\0'; sp++) {
    // if (is_house && ipl <= nhouses && strchr("bBsSrRxXuUQnNfFj+-*/=", *sp) !=
    // NULL) continue;
    if (is_house && strchr("bBrRxXuUQnNfFj+-*/=", *sp) != NULL) continue;
    if (is_ayana && strchr("bBsSrRxXuUQnNfFj+-*/=", *sp) != NULL) continue;
    if (sp != fmt) fputs(gap, stdout);
    if (sp == fmt && list_hor && !is_first && strchr("yYJtT", *sp) == NULL)
      fputs(gap, stdout);
    switch (*sp) {
      case 'y':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          printf("year");
          break;
        }
        printf("%d", jyear);
        break;
      case 'Y':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          printf("year");
          break;
        }
        t2 = swe_julday(jyear, 1, 1, ju2, gregflag);
        y_frac = (t - t2) / 365.0;
        printf("%.2f", jyear + y_frac);
        break;
      case 'p':
        if (is_label) {
          printf("obj.nr");
          break;
        }
        if (!is_house && diff_mode == DIFF_DIFF) {
          printf("%d-%d", ipl, ipldiff);
        } else if (!is_house && diff_mode == DIFF_GEOHEL) {
          printf("%d-%dhel", ipl, ipldiff);
        } else if (!is_house && diff_mode == DIFF_MIDP) {
          printf("%d/%d", ipl, ipldiff);
        } else {
          printf("%d", ipl);
        }
        break;
      case 'P':
        if (is_label) {
          printf("%-15s", "name");
          break;
        }
        if (is_house) {
          if (ipl <= nhouses) {
            printf("house %2d       ", ipl);
          } else {
            printf("%-15s", hs_nam[ipl - nhouses]);
          }
        } else if (is_ayana) {
          // printf("Ayanamsha       ");
          printf("Ayanamsha %s ", swe_get_ayanamsa_name(sid_mode));
        } else if (diff_mode == DIFF_DIFF || diff_mode == DIFF_GEOHEL) {
          printf("%.3s-%.3s", spnam, spnam2);
        } else if (diff_mode == DIFF_MIDP) {
          printf("%.3s/%.3s", spnam, spnam2);
        } else {
          printf("%-15s", spnam);
        }
        break;
      case 'J':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          printf("julday");
          break;
        }
        y_frac = (t - floor(t)) * 100;
        if (floor(y_frac) != y_frac) {
          printf("%.5f", t);
        } else {
          printf("%.2f", t);
        }
        break;
      case 'T':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          printf("date    ");
          break;
        }
        printf("%02d.%02d.%d", jday, jmon, jyear);
        if (jut != 0 || step_in_minutes || step_in_seconds) {
          int h, m, s;
          s = (int)(jut * 3600 + 0.5);
          h = (int)(s / 3600.0);
          m = (int)((s % 3600) / 60.0);
          s %= 60;
          printf(" %d:%02d:%02d", h, m, s);
          if (universal_time)
            printf(" UT");
          else
            printf(" TT");
        }
        break;
      case 't':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          printf("date");
          break;
        }
        printf("%02d%02d%02d", jyear % 100, jmon, jday);
        break;
      case 'L':
        if (is_label) {
          printf(slon);
          break;
        }
        if (psp != NULL &&
            (*psp == 'q' || *psp == 'y')) { /* delta t or time equation */
          printf("%# 11.7f", x[0]);
          printf("s");
          break;
        }
        fputs(dms(x[0], round_flag), stdout);
        break;
      case 'l':
        if (is_label) {
          printf(slon);
          break;
        }
        if (output_extra_prec)
          printf("%# 11.11f", x[0]);
        else
          printf("%# 11.7f", x[0]);
        break;
      case 'G':
        if (is_label) {
          printf("housPos");
          break;
        }
        fputs(dms(hpos, round_flag), stdout);
        break;
      case 'g':
        if (is_label) {
          printf("housPos");
          break;
        }
        printf("%# 11.7f", hpos);
        break;
      case 'j':
        if (is_label) {
          printf("houseNr");
          break;
        }
        printf("%# 11.7f", hposj);
        break;
      case 'Z':
        if (is_label) {
          printf(slon);
          break;
        }
        fputs(dms(x[0], round_flag | BIT_ZODIAC), stdout);
        break;
      case 'S':
      case 's':
        if (*(sp + 1) == 'S' || *(sp + 1) == 's' ||
            strpbrk(fmt, "XUxu") != NULL) {
          for (sp2 = fmt; *sp2 != '\0'; sp2++) {
            if (sp2 != fmt) fputs(gap, stdout);
            switch (*sp2) {
              case 'L': /* speed! */
              case 'Z': /* speed! */
                if (is_label) {
                  printf("lon/day");
                  break;
                }
                fputs(dms(x[3], round_flag), stdout);
                break;
              case 'l': /* speed! */
                if (is_label) {
                  printf("lon/day");
                  break;
                }
                if (output_extra_prec)
                  printf("%# 11.9f", x[3]);
                else
                  printf("%# 11.7f", x[3]);
                break;
              case 'B': /* speed! */
                if (is_label) {
                  printf("lat/day");
                  break;
                }
                fputs(dms(x[4], round_flag), stdout);
                break;
              case 'b': /* speed! */
                if (is_label) {
                  printf("lat/day");
                  break;
                }
                if (output_extra_prec)
                  printf("%# 11.9f", x[4]);
                else
                  printf("%# 11.7f", x[4]);
                break;
              case 'A': /* speed! */
                if (is_label) {
                  printf("RA/day");
                  break;
                }
                fputs(dms(xequ[3] / 15, round_flag | SEFLG_EQUATORIAL), stdout);
                break;
              case 'a': /* speed! */
                if (is_label) {
                  printf("RA/day");
                  break;
                }
                if (output_extra_prec)
                  printf("%# 11.9f", xequ[3]);
                else
                  printf("%# 11.7f", xequ[3]);
                break;
              case 'D': /* speed! */
                if (is_label) {
                  printf("dcl/day");
                  break;
                }
                fputs(dms(xequ[4], round_flag), stdout);
                break;
              case 'd': /* speed! */
                if (is_label) {
                  printf("dcl/day");
                  break;
                }
                if (output_extra_prec)
                  printf("%# 11.9f", xequ[4]);
                else
                  printf("%# 11.7f", xequ[4]);
                break;
              case 'R': /* speed! */
              case 'r': /* speed! */
                if (is_label) {
                  printf("AU/day");
                  break;
                }
                if (output_extra_prec)
                  printf("%# 16.11f", x[5]);
                else
                  printf("%# 14.9f", x[5]);
                break;
              case 'U': /* speed! */
              case 'X': /* speed! */
                if (is_label) {
                  fputs("speed_0", stdout);
                  fputs(gap, stdout);
                  fputs("speed_1", stdout);
                  fputs(gap, stdout);
                  fputs("speed_2", stdout);
                  break;
                }
                if (*sp == 'U')
                  ar = sqrt(square_sum(xcart));
                else
                  ar = 1;
                printf("%# 14.9f", xcart[3] / ar);
                fputs(gap, stdout);
                printf("%# 14.9f", xcart[4] / ar);
                fputs(gap, stdout);
                printf("%# 14.9f", xcart[5] / ar);
                break;
              case 'u': /* speed! */
              case 'x': /* speed! */
                if (is_label) {
                  fputs("speed_0", stdout);
                  fputs(gap, stdout);
                  fputs("speed_1", stdout);
                  fputs(gap, stdout);
                  fputs("speed_2", stdout);
                  break;
                }
                if (*sp == 'u')
                  ar = sqrt(square_sum(xcartq));
                else
                  ar = 1;
                printf("%# 14.9f", xcartq[3] / ar);
                fputs(gap, stdout);
                printf("%# 14.9f", xcartq[4] / ar);
                fputs(gap, stdout);
                printf("%# 14.9f", xcartq[5] / ar);
                break;
              default:
                break;
            }
          }
          if (*(sp + 1) == 'S' || *(sp + 1) == 's') sp++;
        } else if (*sp == 'S') {
          int flag = round_flag;
          if (is_house) flag |= BIT_ALLOW_361;  // speed of houses can be > 360
          if (is_label) {
            printf("deg/day");
            break;
          }
          fputs(dms(x[3], flag), stdout);
        } else {
          if (is_label) {
            printf("deg/day");
            break;
          }
          if (output_extra_prec)
            printf("%# 11.17f", x[3]);
          else
            printf("%# 11.7f", x[3]);
        }
        break;
      case 'B':
        if (is_label) {
          printf("lat.    ");
          break;
        }
        if (*psp == 'q') { /* delta t */
          printf("%# 11.7f", x[1]);
          printf("h");
          break;
        }
        fputs(dms(x[1], round_flag), stdout);
        break;
      case 'b':
        if (is_label) {
          printf("lat.    ");
          break;
        }
        if (output_extra_prec)
          printf("%# 11.11f", x[1]);
        else
          printf("%# 11.7f", x[1]);
        break;
      case 'A': /* right ascension */
        if (is_label) {
          printf("RA      ");
          break;
        }
        fputs(dms(xequ[0] / 15, round_flag | SEFLG_EQUATORIAL), stdout);
        break;
      case 'a': /* right ascension */
        if (is_label) {
          printf("RA      ");
          break;
        }
        if (output_extra_prec)
          printf("%# 11.11f", xequ[0]);
        else
          printf("%# 11.7f", xequ[0]);
        break;
      case 'D': /* declination */
        if (is_label) {
          printf("decl      ");
          break;
        }
        fputs(dms(xequ[1], round_flag), stdout);
        break;
      case 'd': /* declination */
        if (is_label) {
          printf("decl      ");
          break;
        }
        if (output_extra_prec)
          printf("%# 11.11f", xequ[1]);
        else
          printf("%# 11.7f", xequ[1]);
        break;
      case 'I': /* azimuth */
        if (is_label) {
          printf("azimuth");
          break;
        }
        fputs(dms(xaz[0], round_flag), stdout);
        break;
      case 'i': /* azimuth */
        if (is_label) {
          printf("azimuth");
          break;
        }
        printf("%# 11.7f", xaz[0]);
        break;
      case 'H': /* height */
        if (is_label) {
          printf("height");
          break;
        }
        fputs(dms(xaz[1], round_flag), stdout);
        break;
      case 'h': /* height */
        if (is_label) {
          printf("height");
          break;
        }
        printf("%# 11.7f", xaz[1]);
        break;
      case 'K': /* height (apparent) */
        if (is_label) {
          printf("hgtApp");
          break;
        }
        fputs(dms(xaz[2], round_flag), stdout);
        break;
      case 'k': /* height (apparent) */
        if (is_label) {
          printf("hgtApp");
          break;
        }
        printf("%# 11.7f", xaz[2]);
        break;
      case 'R':
        if (is_label) {
          printf("distAU   ");
          break;
        }
        printf("%# 14.9f", x[2]);
        break;
      case 'W':
        if (is_label) {
          printf("distLY   ");
          break;
        }
        printf("%# 14.9f", x[2] * SE_AUNIT_TO_LIGHTYEAR);
        break;
      case 'w':
        if (is_label) {
          printf("distkm   ");
          break;
        }
        printf("%# 14.9f", x[2] * SE_AUNIT_TO_KM);
        break;
      case 'r':
        if (is_label) {
          printf("dist");
          break;
        }
        if (ipl == SE_MOON) { /* for moon print parallax */
          /* geocentric horizontal parallax: */
          if ((0)) {
            sinp = 8.794 / x[2]; /* in seconds of arc */
            ar = sinp * (1 + sinp * sinp * 3.917402e-12);
            /* the factor is 1 / (3600^2 * (180/pi)^2 * 6) */
            printf("%# 13.5f\" %# 13.5f'", ar, ar / 60.0);
          }
          swe_pheno(te, ipl, iflag, dret, serr);
          printf("%# 13.5f\"", dret[5] * 3600);
        } else {
          printf("%# 14.9f", x[2] * SE_AUNIT_TO_LIGHTYEAR);
        }
        break;
      case 'q':
        if (is_label) {
          printf("reldist");
          break;
        }
        dar = get_geocentric_relative_distance(te, ipl, iflag, serr);
        printf("% 5d", dar);
        break;
      case 'U':
      case 'X':
        if (*sp == 'U')
          ar = sqrt(square_sum(xcart));
        else
          ar = 1;
        printf("%# 14.9f", xcart[0] / ar);
        fputs(gap, stdout);
        printf("%# 14.9f", xcart[1] / ar);
        fputs(gap, stdout);
        printf("%# 14.9f", xcart[2] / ar);
        break;
      case 'u':
      case 'x':
        if (is_label) {
          fputs("x0", stdout);
          fputs(gap, stdout);
          fputs("x1", stdout);
          fputs(gap, stdout);
          fputs("x2", stdout);
          break;
        }
        if (*sp == 'u')
          ar = sqrt(square_sum(xcartq));
        else
          ar = 1;
        if (output_extra_prec) {
          printf("%# .17f", xcartq[0] / ar);
          fputs(gap, stdout);
          printf("%# .17f", xcartq[1] / ar);
          fputs(gap, stdout);
          printf("%# .17f", xcartq[2] / ar);
        } else {
          printf("%# 14.9f", xcartq[0] / ar);
          fputs(gap, stdout);
          printf("%# 14.9f", xcartq[1] / ar);
          fputs(gap, stdout);
          printf("%# 14.9f", xcartq[2] / ar);
        }
        break;
      case 'Q':
        if (is_label) {
          printf("Q");
          break;
        }
        printf("%-15s", spnam);
        fputs(dms(x[0], round_flag), stdout);
        fputs(dms(x[1], round_flag), stdout);
        printf("  %# 14.9f", x[2]);
        fputs(dms(x[3], round_flag), stdout);
        fputs(dms(x[4], round_flag), stdout);
        printf("  %# 14.9f\n", x[5]);
        printf("               %s", dms(xequ[0], round_flag));
        fputs(dms(xequ[1], round_flag), stdout);
        printf("                %s", dms(xequ[3], round_flag));
        fputs(dms(xequ[4], round_flag), stdout);
        break;
      case 'N':
      case 'n': {
        double xasc[6], xdsc[6];
        int imeth = (*sp == tolower(*sp)) ? SE_NODBIT_MEAN : SE_NODBIT_OSCU;
        iflgret =
            swe_nod_aps(te, ipl, iflag, imeth, xasc, xdsc, NULL, NULL, serr);
        if (iflgret >= 0 && (ipl <= SE_NEPTUNE || *sp == 'N')) {
          if (is_label) {
            fputs("nodAsc", stdout);
            fputs(gap, stdout);
            fputs("nodDesc", stdout);
            break;
          }
          if (use_dms)
            fputs(dms(xasc[0], round_flag | BIT_ZODIAC), stdout);
          else
            printf("%# 11.7f", xasc[0]);
          fputs(gap, stdout);
          if (use_dms)
            fputs(dms(xdsc[0], round_flag | BIT_ZODIAC), stdout);
          else
            printf("%# 11.7f", xdsc[0]);
        }
      }; break;
      case 'F':
      case 'f':
        if (!is_house) {
          double xfoc[6], xaph[6], xper[6];
          int imeth = (*sp == tolower(*sp)) ? SE_NODBIT_MEAN : SE_NODBIT_OSCU;
          //	fprintf(stderr, "c=%c\n", *sp);
          iflgret =
              swe_nod_aps(te, ipl, iflag, imeth, NULL, NULL, xper, xaph, serr);
          if (iflgret >= 0 && (ipl <= SE_NEPTUNE || *sp == 'F')) {
            if (is_label) {
              fputs("peri", stdout);
              fputs(gap, stdout);
              fputs("apo", stdout);
              fputs(gap, stdout);
              fputs("focus", stdout);
              break;
            }
            printf("%# 11.7f", xper[0]);
            fputs(gap, stdout);
            printf("%# 11.7f", xaph[0]);
          }
          imeth |= SE_NODBIT_FOPOINT;
          iflgret =
              swe_nod_aps(te, ipl, iflag, imeth, NULL, NULL, xper, xfoc, serr);
          if (iflgret >= 0 && (ipl <= SE_NEPTUNE || *sp == 'F')) {
            fputs(gap, stdout);
            printf("%# 11.7f", xfoc[0]);
          }
        };
        break;
      case '+':
        if (is_house) break;
        if (is_label) {
          printf("phase");
          break;
        }
        fputs(dms(attr[0], round_flag), stdout);
        break;
      case '-':
        if (is_label) {
          printf("phase");
          break;
        }
        if (is_house) break;
        printf("  %# 14.9f", attr[1]);
        break;
      case '*':
        if (is_label) {
          printf("elong");
          break;
        }
        if (is_house) break;
        fputs(dms(attr[2], round_flag), stdout);
        break;
      case '/':
        if (is_label) {
          printf("diamet");
          break;
        }
        if (is_house) break;
        fputs(dms(attr[3], round_flag), stdout);
        break;
      case '=':
        if (is_label) {
          printf("magn");
          break;
        }
        if (is_house) break;
        printf("  %# 6.3fm", attr[4]);
        break;
      case 'V': /* human design gates */
      case 'v': {
        double xhds;
        int igate, iline, ihex;
        static int hexa[64] = {
            1,  43, 14, 34, 9,  5,  26, 11, 10, 58, 38, 54, 61, 60, 41, 19,
            13, 49, 30, 55, 37, 63, 22, 36, 25, 17, 21, 51, 42, 3,  27, 24,
            2,  23, 8,  20, 16, 35, 45, 12, 15, 52, 39, 53, 62, 56, 31, 33,
            7,  4,  29, 59, 40, 64, 47, 6,  46, 18, 48, 57, 32, 50, 28, 44};
        if (is_label) {
          printf("hds");
          break;
        }
        if (is_house) break;
        xhds = swe_degnorm(x[0] - 223.25);
        ihex = (int)floor(xhds / 5.625);
        iline = ((int)(floor(xhds / 0.9375))) % 6 + 1;
        igate = hexa[ihex];
        printf("%2d.%d", igate, iline);
        if (*sp == 'V') printf(" %2d%%", swe_d2l(100 * fmod(xhds / 0.9375, 1)));
        break;
      }
    } /* switch */
  }   /* for sp */
  if (!list_hor) printf("\n");
  return OK;
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

char* get_gregjul(int gregflag, int year) {
  if (gregflag == SE_JUL_CAL) return "jul";
  if (year < 1700) return "greg";
  return "";
}

// print lon and lat string in minute precision
void format_lon_lat(char* slon, char* slat, double lon, double lat) {
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
