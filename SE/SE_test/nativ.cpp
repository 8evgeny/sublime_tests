#include "nativ.h"

#include "main.h"

planet::planet() {}

nativ::nativ(string nam) {
  po::variables_map vm;
  readConfig("../config/config.ini", vm, nam);
  name = vm[nam + ".name"].as<string>();
  bday = vm[nam + ".date"].as<string>();
  btime = vm[nam + ".time"].as<string>();
  lon = vm[nam + ".lon"].as<string>();
  lat = vm[nam + ".lat"].as<string>();
  print_calc = vm["common.print_calc"].as<bool>();
  path = vm["common.ephPatch"].as<string>();
  city = vm[nam + ".city"].as<string>();

  chronoBighDateTime = fromStringToCrono(bday, btime);
  b_time = fromCronoToTm(chronoBighDateTime);
  calc();

  printAll(*this);
  panchang(*this);
  panchangPrint(*this);

  auto ss = findStartTithi(*this, int(tithi) + 1);
  cout << "Tithi " << tithi << "begin: " << ss.first << "\t" << ss.second
       << endl;
};

nativ::nativ() {
  po::variables_map vm;
  readConfig("../config/config.ini", vm, "");
  auto datetime = dateTimeNowInString();
  bday = datetime.first;
  btime = datetime.second;
  lon = vm["common.lon_current"].as<std::string>();
  lat = vm["common.lat_current"].as<std::string>();
  name = vm["common.name"].as<std::string>();
  print_calc = vm["common.print_calc"].as<bool>();
  path = vm["common.ephPatch"].as<string>();
  city = vm["common.city"].as<std::string>();

  chronoBighDateTime = fromStringToCrono(bday, btime);
  b_time = fromCronoToTm(chronoBighDateTime);
  calc();

  printAll(*this);
  panchang(*this);
  panchangPrint(*this);

  auto ss = findStartTithi(*this, int(tithi) + 1);
  cout << "Tithi " << tithi << "begin: " << ss.first << "\t" << ss.second
       << endl;
};

void nativ::readConfig(const char* conf_file,
                       boost::program_options::variables_map& vm, string nam) {
  auto name = nam + ".name";
  auto date = nam + ".date";
  auto time = nam + ".time";
  auto lon = nam + ".lon";
  auto lat = nam + ".lat";
  auto city = nam + ".city";
  po::options_description comm("common");
  comm.add_options()("common.ephPatch", po::value<string>(), "ephPatch")(
      "common.print_calc", po::value<bool>(), "print_calc")(
      "common.lon_current", po::value<string>(), "lon")(
      "common.lat_current", po::value<string>(), "lat")(
      "common.name", po::value<string>(), "name")("common.city",
                                                  po::value<string>(), "city");
  po::options_description nativ(nam);
  nativ.add_options()(name.c_str(), po::value<string>(), "name")(
      date.c_str(), po::value<string>(), "date")(
      time.c_str(), po::value<string>(), "time")(lon.c_str(),
                                                 po::value<string>(), "lon")(
      lat.c_str(), po::value<string>(), "lat")(city.c_str(),
                                               po::value<string>(), "lon");
  po::options_description desc("Allowed options");
  desc.add(comm);
  desc.add(nativ);
  try {
    po::parsed_options parsed = po::parse_config_file<char>(
        conf_file, desc,
        true);  //флаг true разрешает незарегистрированные опции !
    po::store(parsed, vm);
  } catch (const po::reading_file& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  po::notify(vm);
  //  cout << "ephPath-" << vm["common.ephPatch"].as<string>() << endl;
  //  cout << "print_calc-" << vm["common.print_calc"].as<bool>() << endl;
}

int nativ::print_line(int mode, AS_BOOL is_first, int sid_mode) {
  /*
   * The string fmt contains a sequence of format specifiers;
   * each character in fmt creates a column, the columns are
   * sparated by the gap string.
   * Time columns tTJyY are only printed, if is_first is TRUE,
   * so that they are not repeated in list_hor (horizontal list) mode.
   * In list_hor mode, no newline is printed.
   */

  //  cout << "mode-" << mode << ", is_first-" << is_first << ", sid_mode-"
  //       << sid_mode << endl;
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
    //*****************************************************************************
    //    is_label = true;
    //    cout << " sp-" << sp;
    if ((*(sp) == 'P') && (mode == 1) && (ipl != 13)) break;  // only As
    // mode 0 - planets
    // mode 1 - houses

    if ((*(sp) == 'S') && (mode == 1)) break;

    //    cout << " mode-" << mode << " ipl-" << ipl << "\t";

    //*****************************************************************************

    // if (is_house && ipl <= nhouses && strchr("bBsSrRxXuUQnNfFj+-*/=", *sp)
    // != NULL) continue;
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
          if (print_calc) printf("year");
          break;
        }
        if (print_calc) printf("%d", jyear);
        break;

      case 'Y':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          if (print_calc) printf("year");
          break;
        }
        t2 = swe_julday(jyear, 1, 1, ju2, gregflag);
        y_frac = (t - t2) / 365.0;
        if (print_calc) printf("%.2f", jyear + y_frac);
        break;

      case 'p':
        if (is_label) {
          if (print_calc) printf("obj.nr");
          break;
        }
        if (!is_house && diff_mode == DIFF_DIFF) {
          if (print_calc) printf("%d-%d", ipl, ipldiff);
        } else if (!is_house && diff_mode == DIFF_GEOHEL) {
          if (print_calc) printf("%d-%dhel", ipl, ipldiff);
        } else if (!is_house && diff_mode == DIFF_MIDP) {
          if (print_calc) printf("%d/%d", ipl, ipldiff);
        } else {
          if (print_calc) printf("%d", ipl);
        }
        break;

      case 'P':

        if (is_label) {
          if (print_calc) printf("%-15s", "name");
          break;
        }

        if (is_house) {
          if (ipl <= nhouses) {
            if (print_calc) printf("house %2d       ", ipl);
          } else {
            if (print_calc) printf("%-15s", hs_nam[ipl - nhouses]);
          }
        } else if (is_ayana) {
          // printf("Ayanamsha       ");
          if (print_calc)
            printf("Ayanamsha %s ", swe_get_ayanamsa_name(sid_mode));
        } else if (diff_mode == DIFF_DIFF || diff_mode == DIFF_GEOHEL) {
          if (print_calc) printf("%.3s-%.3s", spnam, spnam2);
        } else if (diff_mode == DIFF_MIDP) {
          if (print_calc) printf("%.3s/%.3s", spnam, spnam2);
        } else {
          if (print_calc) printf("%-15s", spnam);
        }
        break;

      case 'J':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          if (print_calc) printf("julday");
          break;
        }
        y_frac = (t - floor(t)) * 100;
        if (floor(y_frac) != y_frac) {
          if (print_calc) printf("%.5f", t);
        } else {
          if (print_calc) printf("%.2f", t);
        }
        break;

      case 'T':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          if (print_calc) printf("date    ");
          break;
        }
        if (print_calc) printf("%02d.%02d.%d", jday, jmon, jyear);
        if (jut != 0 || step_in_minutes || step_in_seconds) {
          int h, m, s;
          s = (int)(jut * 3600 + 0.5);
          h = (int)(s / 3600.0);
          m = (int)((s % 3600) / 60.0);
          s %= 60;
          if (print_calc) printf(" %d:%02d:%02d", h, m, s);
          if (universal_time)
            if (print_calc)
              printf(" UT");
            else if (print_calc)
              printf(" TT");
        }
        break;

      case 't':
        if (list_hor && !is_first) {
          break;
        }
        if (is_label) {
          if (print_calc) printf("date");
          break;
        }
        if (print_calc) printf("%02d%02d%02d", jyear % 100, jmon, jday);
        break;

      case 'L':
        if (is_label) {
          if (print_calc) printf(slon);
          break;
        }
        if (psp != NULL &&
            (*psp == 'q' || *psp == 'y')) { /* delta t or time equation */
          if (print_calc) printf("%# 11.7f", x[0]);
          if (print_calc) printf("s");
          break;
        }

        //**********************************************************************

        if (mode == 0) {
          switch (ipl) {
            case 0:
              su.lon = x[0];
              break;
            case 1:
              ch.lon = x[0];
              break;
            case 2:
              bu.lon = x[0];
              break;
            case 3:
              sk.lon = x[0];
              break;
            case 4:
              ma.lon = x[0];
              break;
            case 5:
              gu.lon = x[0];
              break;
            case 6:
              sa.lon = x[0];
              break;
            case 10:
              ra.lon = x[0];
              ke.lon = 180 + ra.lon;
              ke.lon > 360 ? ke.lon -= 360 : ke.lon;
              break;
          }
        }
        if ((mode == 1) && (ipl == 13)) {
          as.lon = x[0];
        }
        //Значениe  при *sp == 'L'
        //        fputs(dms(x[0], round_flag), stdout);
        //**********************************************************************

        break;
      case 'l':
        if (is_label) {
          if (print_calc) printf(slon);
          break;
        }
        if (output_extra_prec)
          if (print_calc)
            printf("%# 11.11f", x[0]);
          else if (print_calc)
            printf("%# 11.7f", x[0]);
        break;

      case 'G':
        if (is_label) {
          if (print_calc) printf("housPos");
          break;
        }

        fputs(dms(hpos, round_flag), stdout);

        break;
      case 'g':
        if (is_label) {
          if (print_calc) printf("housPos");
          break;
        }
        if (print_calc) printf("%# 11.7f", hpos);
        break;
      case 'j':
        if (is_label) {
          if (print_calc) printf("houseNr");
          break;
        }
        if (print_calc) printf("%# 11.7f", hposj);
        break;
      case 'Z':
        if (is_label) {
          if (print_calc) printf(slon);
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
                  if (print_calc) printf("lon/day");
                  break;
                }

                fputs(dms(x[3], round_flag), stdout);

                break;
              case 'l': /* speed! */
                if (is_label) {
                  if (print_calc) printf("lon/day");
                  break;
                }
                if (output_extra_prec)
                  if (print_calc)
                    printf("%# 11.9f", x[3]);
                  else if (print_calc)
                    printf("%# 11.7f", x[3]);
                break;
              case 'B': /* speed! */
                if (is_label) {
                  if (print_calc) printf("lat/day");
                  break;
                }
                fputs(dms(x[4], round_flag), stdout);
                break;
              case 'b': /* speed! */
                if (is_label) {
                  if (print_calc) printf("lat/day");
                  break;
                }
                if (output_extra_prec)
                  if (print_calc)
                    printf("%# 11.9f", x[4]);
                  else if (print_calc)
                    printf("%# 11.7f", x[4]);
                break;
              case 'A': /* speed! */
                if (is_label) {
                  if (print_calc) printf("RA/day");
                  break;
                }
                fputs(dms(xequ[3] / 15, round_flag | SEFLG_EQUATORIAL), stdout);
                break;
              case 'a': /* speed! */
                if (is_label) {
                  if (print_calc) printf("RA/day");
                  break;
                }
                if (output_extra_prec)
                  if (print_calc)
                    printf("%# 11.9f", xequ[3]);
                  else if (print_calc)
                    printf("%# 11.7f", xequ[3]);
                break;
              case 'D': /* speed! */
                if (is_label) {
                  if (print_calc) printf("dcl/day");
                  break;
                }
                fputs(dms(xequ[4], round_flag), stdout);
                break;
              case 'd': /* speed! */
                if (is_label) {
                  if (print_calc) printf("dcl/day");
                  break;
                }
                if (output_extra_prec)
                  if (print_calc)
                    printf("%# 11.9f", xequ[4]);
                  else if (print_calc)
                    printf("%# 11.7f", xequ[4]);
                break;
              case 'R': /* speed! */
              case 'r': /* speed! */
                if (is_label) {
                  if (print_calc) printf("AU/day");
                  break;
                }
                if (output_extra_prec)
                  if (print_calc)
                    printf("%# 16.11f", x[5]);
                  else if (print_calc)
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
                if (print_calc) printf("%# 14.9f", xcart[3] / ar);
                fputs(gap, stdout);
                if (print_calc) printf("%# 14.9f", xcart[4] / ar);
                fputs(gap, stdout);
                if (print_calc) printf("%# 14.9f", xcart[5] / ar);
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
                if (print_calc) printf("%# 14.9f", xcartq[3] / ar);
                fputs(gap, stdout);
                if (print_calc) printf("%# 14.9f", xcartq[4] / ar);
                fputs(gap, stdout);
                if (print_calc) printf("%# 14.9f", xcartq[5] / ar);
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
            if (print_calc) printf("deg/day");
            break;
          }

          //*****************************************************************************
          //Скорость (Градусы в день)

          if (mode == 0) {
            switch (ipl) {
              case 0:

                su.speed = x[3];
                break;
              case 1:
                ch.speed = x[3];
                break;
              case 2:
                bu.speed = x[3];
                break;
              case 3:
                sk.speed = x[3];
                break;
              case 4:
                ma.speed = x[3];
                break;
              case 5:
                gu.speed = x[3];
                break;
              case 6:
                sa.speed = x[3];
                break;
              case 10:
                ra.speed = x[3];
                ke.speed = x[3];
                break;
            }
          }
          if ((mode == 1) && (ipl == 13)) {
            as.speed = x[3];
          }

          //          fputs(dms(x[3], flag), stdout);

          //*****************************************************************************

        } else {
          if (is_label) {
            if (print_calc) printf("deg/day");
            break;
          }
          if (output_extra_prec)
            if (print_calc)
              printf("%# 11.17f", x[3]);
            else if (print_calc)
              printf("%# 11.7f", x[3]);
        }
        break;

      case 'B':

        //************************************
        break;
        //************************************

        if (is_label) {
          if (print_calc) printf("lat.    ");
          break;
        }
        if (*psp == 'q') { /* delta t */
          if (print_calc) printf("%# 11.7f", x[1]);
          if (print_calc) printf("h");
          break;
        }
        fputs(dms(x[1], round_flag), stdout);
        break;
      case 'b':
        if (is_label) {
          if (print_calc) printf("lat.    ");
          break;
        }
        if (output_extra_prec)
          if (print_calc)
            printf("%# 11.11f", x[1]);
          else if (print_calc)
            printf("%# 11.7f", x[1]);
        break;

      case 'A': /* right ascension */
        if (is_label) {
          if (print_calc) printf("RA      ");
          break;
        }
        fputs(dms(xequ[0] / 15, round_flag | SEFLG_EQUATORIAL), stdout);
        break;
      case 'a': /* right ascension */
        if (is_label) {
          if (print_calc) printf("RA      ");
          break;
        }
        if (output_extra_prec)
          if (print_calc)
            printf("%# 11.11f", xequ[0]);
          else if (print_calc)
            printf("%# 11.7f", xequ[0]);
        break;
      case 'D': /* declination */
        if (is_label) {
          if (print_calc) printf("decl      ");
          break;
        }
        fputs(dms(xequ[1], round_flag), stdout);
        break;

      case 'd': /* declination */
        if (is_label) {
          if (print_calc) printf("decl      ");
          break;
        }
        if (output_extra_prec)
          if (print_calc)
            printf("%# 11.11f", xequ[1]);
          else if (print_calc)
            printf("%# 11.7f", xequ[1]);
        break;

      case 'I': /* azimuth */
        if (is_label) {
          if (print_calc) printf("azimuth");
          break;
        }
        fputs(dms(xaz[0], round_flag), stdout);
        break;

      case 'i': /* azimuth */
        if (is_label) {
          if (print_calc) printf("azimuth");
          break;
        }
        if (print_calc) printf("%# 11.7f", xaz[0]);
        break;

      case 'H': /* height */
        if (is_label) {
          if (print_calc) printf("height");
          break;
        }
        fputs(dms(xaz[1], round_flag), stdout);
        break;

      case 'h': /* height */
        if (is_label) {
          if (print_calc) printf("height");
          break;
        }
        if (print_calc) printf("%# 11.7f", xaz[1]);
        break;

      case 'K': /* height (apparent) */
        if (is_label) {
          if (print_calc) printf("hgtApp");
          break;
        }
        fputs(dms(xaz[2], round_flag), stdout);
        break;

      case 'k': /* height (apparent) */
        if (is_label) {
          if (print_calc) printf("hgtApp");
          break;
        }
        if (print_calc) printf("%# 11.7f", xaz[2]);
        break;

      case 'R':
        //************************************
        break;
        //************************************

        if (is_label) {
          if (print_calc) printf("distAU   ");
          break;
        }
        if (print_calc) printf("%# 14.9f", x[2]);
        break;
      case 'W':
        if (is_label) {
          if (print_calc) printf("distLY   ");
          break;
        }
        if (print_calc) printf("%# 14.9f", x[2] * SE_AUNIT_TO_LIGHTYEAR);
        break;
      case 'w':
        if (is_label) {
          if (print_calc) printf("distkm   ");
          break;
        }
        if (print_calc) printf("%# 14.9f", x[2] * SE_AUNIT_TO_KM);
        break;
      case 'r':
        if (is_label) {
          if (print_calc) printf("dist");
          break;
        }
        if (ipl == SE_MOON) { /* for moon print parallax */
          /* geocentric horizontal parallax: */
          if ((0)) {
            sinp = 8.794 / x[2]; /* in seconds of arc */
            ar = sinp * (1 + sinp * sinp * 3.917402e-12);
            /* the factor is 1 / (3600^2 * (180/pi)^2 * 6) */
            if (print_calc) printf("%# 13.5f\" %# 13.5f'", ar, ar / 60.0);
          }
          swe_pheno(te, ipl, iflag, dret, serr);
          if (print_calc) printf("%# 13.5f\"", dret[5] * 3600);
        } else {
          if (print_calc) printf("%# 14.9f", x[2] * SE_AUNIT_TO_LIGHTYEAR);
        }
        break;
      case 'q':
        if (is_label) {
          if (print_calc) printf("reldist");
          break;
        }
        dar = get_geocentric_relative_distance(te, ipl, iflag, serr);
        if (print_calc) printf("% 5d", dar);
        break;
      case 'U':
      case 'X':
        if (*sp == 'U')
          ar = sqrt(square_sum(xcart));
        else
          ar = 1;
        if (print_calc) printf("%# 14.9f", xcart[0] / ar);
        fputs(gap, stdout);
        if (print_calc) printf("%# 14.9f", xcart[1] / ar);
        fputs(gap, stdout);
        if (print_calc) printf("%# 14.9f", xcart[2] / ar);
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
          if (print_calc) printf("%# .17f", xcartq[0] / ar);
          fputs(gap, stdout);
          if (print_calc) printf("%# .17f", xcartq[1] / ar);
          fputs(gap, stdout);
          if (print_calc) printf("%# .17f", xcartq[2] / ar);
        } else {
          if (print_calc) printf("%# 14.9f", xcartq[0] / ar);
          fputs(gap, stdout);
          if (print_calc) printf("%# 14.9f", xcartq[1] / ar);
          fputs(gap, stdout);
          if (print_calc) printf("%# 14.9f", xcartq[2] / ar);
        }
        break;
      case 'Q':
        if (is_label) {
          if (print_calc) printf("Q");
          break;
        }
        if (print_calc) printf("%-15s", spnam);
        fputs(dms(x[0], round_flag), stdout);
        fputs(dms(x[1], round_flag), stdout);
        if (print_calc) printf("  %# 14.9f", x[2]);
        fputs(dms(x[3], round_flag), stdout);
        fputs(dms(x[4], round_flag), stdout);
        if (print_calc) printf("  %# 14.9f\n", x[5]);
        if (print_calc) printf("               %s", dms(xequ[0], round_flag));
        fputs(dms(xequ[1], round_flag), stdout);
        if (print_calc) printf("                %s", dms(xequ[3], round_flag));
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
          else if (print_calc)
            printf("%# 11.7f", xasc[0]);
          fputs(gap, stdout);
          if (use_dms)
            fputs(dms(xdsc[0], round_flag | BIT_ZODIAC), stdout);
          else if (print_calc)
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
            if (print_calc) printf("%# 11.7f", xper[0]);
            fputs(gap, stdout);
            if (print_calc) printf("%# 11.7f", xaph[0]);
          }
          imeth |= SE_NODBIT_FOPOINT;
          iflgret =
              swe_nod_aps(te, ipl, iflag, imeth, NULL, NULL, xper, xfoc, serr);
          if (iflgret >= 0 && (ipl <= SE_NEPTUNE || *sp == 'F')) {
            fputs(gap, stdout);
            if (print_calc) printf("%# 11.7f", xfoc[0]);
          }
        };
        break;
      case '+':
        if (is_house) break;
        if (is_label) {
          if (print_calc) printf("phase");
          break;
        }
        fputs(dms(attr[0], round_flag), stdout);
        break;
      case '-':
        if (is_label) {
          if (print_calc) printf("phase");
          break;
        }
        if (is_house) break;
        if (print_calc) printf("  %# 14.9f", attr[1]);
        break;
      case '*':
        if (is_label) {
          if (print_calc) printf("elong");
          break;
        }
        if (is_house) break;
        fputs(dms(attr[2], round_flag), stdout);
        break;
      case '/':
        if (is_label) {
          if (print_calc) printf("diamet");
          break;
        }
        if (is_house) break;
        fputs(dms(attr[3], round_flag), stdout);
        break;
      case '=':
        if (is_label) {
          if (print_calc) printf("magn");
          break;
        }
        if (is_house) break;
        if (print_calc) printf("  %# 6.3fm", attr[4]);
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
          if (print_calc) printf("hds");
          break;
        }
        if (is_house) break;
        xhds = swe_degnorm(x[0] - 223.25);
        ihex = (int)floor(xhds / 5.625);
        iline = ((int)(floor(xhds / 0.9375))) % 6 + 1;
        igate = hexa[ihex];
        if (print_calc) printf("%2d.%d", igate, iline);
        if (*sp == 'V')
          if (print_calc)
            printf(" %2d%%", swe_d2l(100 * fmod(xhds / 0.9375, 1)));
        break;
      }
    }  // end swith sp
  }    // end for sp = fmt
  if (!list_hor)
    if (print_calc) printf("\n");
  return OK;
}

int nativ::calc() {
  int argc = 6;
  char* argv[6];
  string arg0 = "./test";
  string arg1 = "-sid1";
  string arg2 = "-ut" + btime;
  string arg3 = "-p0123456m";
  string arg4 = "-house" + lon + "," + lat + ",W";
  string arg5 = "-edir" + path;
  argv[0] = (char*)arg0.c_str();
  argv[1] = (char*)arg1.c_str();
  argv[2] = (char*)arg2.c_str();
  argv[3] = (char*)arg3.c_str();
  argv[4] = (char*)arg4.c_str();
  argv[5] = (char*)arg5.c_str();

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
  begindate = (char*)bday.c_str();
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
      if (print_calc) printf(" ");
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

  strncpy(sdate, begindate, AS_MAXCH - 1);
  sdate[AS_MAXCH - 1] = '\0';
  begindate = "."; /* to exit afterwards */

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
      if (swe_utc_to_jd(jyear, jmon, jday, ih, im, ds, gregflag, tret, serr) ==
          ERR) {
        if (print_calc) printf(" error in swe_utc_to_jd(): %s\n", serr);
        exit(-1);
      }
      tjd = tret[1];
    } else {
      tjd = swe_julday(jyear, jmon, jday, jut, gregflag);
      tjd += thour / 24.0;
    }
  }
  if (special_event > 0) {
    do_special_event(tjd, ipl, star, special_event, special_mode, geopos, datm,
                     dobs, serr);
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
        if (print_calc) printf("\npath: %s", sout);
      }
#endif
      if (print_calc) printf("\ndate (dmy) %d.%d.%d", jday, jmon, jyear);
      if (gregflag)
        if (print_calc)
          printf(" greg.");
        else if (print_calc)
          printf(" jul.");
      jd_to_time_string(jut, stimeout);
      if (print_calc) printf(stimeout);
      if (universal_time) {
        if (time_flag & BIT_TIME_LMT)
          if (print_calc)
            printf(" LMT");
          else if (print_calc)
            printf(" UT");
      } else {
        if (print_calc) printf(" TT");
      }
      if (print_calc) printf("\t\tversion %s", swe_version(sout));
    }
    if (universal_time) {
      // "LMT: 2457908.588194444"
      if (time_flag & BIT_TIME_LMT) {
        if (with_header) {
          if (print_calc) printf("\nLMT: %.9f", t);
          t -= geopos[0] / 15.0 / 24.0;
        }
      }
      // "UT:  2457908.565972222     delta t: 68.761612 sec"
      if (with_header) {
        if (print_calc) printf("\nUT:  %.9f", t);
        if (print_calc) printf("     delta t: %f sec", delt * 86400.0);
      }
      te = t + delt;
      tut = t;
    } else {
      te = t;
      tut = t - delt;
      // "UT:  2457908.565972222     delta t: 68.761612 sec"
      if (with_header) {
        if (print_calc) printf("\nUT:  %.9f", tut);
        if (print_calc) printf("     delta t: %f sec", delt * 86400.0);
      }
    }
    iflgret = swe_calc(te, SE_ECL_NUT, iflag, xobl, serr);
    if (with_header) {
      // "TT:  2457908.566768074
      if (print_calc) printf("\nTT:  %.9f", te);
      // "ayanamsa =   24° 5'51.6509 (Lahiri)"
      if (iflag & SEFLG_SIDEREAL) {
        if (swe_get_ayanamsa_ex(te, iflag, &daya, serr) == ERR) {
          if (print_calc)
            printf("   error in swe_get_ayanamsa_ex(): %s\n", serr);
          exit(1);
        }
        if (print_calc)
          printf("   ayanamsa = %s (%s)", dms(daya, round_flag),
                 swe_get_ayanamsa_name(sid_mode));
      }
      // "geo. long 8.000000, lat 47.000000, alt 0.000000"
      if (have_geopos) {
        if (print_calc)
          printf("\ngeo. long %f, lat %f, alt %f", geopos[0], geopos[1],
                 geopos[2]);
      }
      if (iflag_f >= 0) iflag = iflag_f;
      if (strchr(plsel, 'o') == NULL) {
        if (iflag & (SEFLG_NONUT | SEFLG_SIDEREAL)) {
          //          if(vm["common.print_calc"].as<bool>()) printf ("\n%-15s
          //          %s", "Epsilon (m)", dms(xobl[0], round_flag));
        } else {
          if (print_calc)
            printf("\n%-15s %s%s", "Epsilon (t/m)", dms(xobl[0], round_flag),
                   gap);
          if (print_calc) printf("%s", dms(xobl[1], round_flag));
        }
      }
      if (strchr(plsel, 'n') == NULL &&
          !(iflag & (SEFLG_NONUT | SEFLG_SIDEREAL))) {
        fputs("\nNutation        ", stdout);
        fputs(dms(xobl[2], round_flag), stdout);
        fputs(gap, stdout);
        fputs(dms(xobl[3], round_flag), stdout);
      }
      if (print_calc) printf("\n");
      if (do_houses) {
        char* shsy = swe_house_name(ihsy);
        if (!universal_time) {
          do_houses = FALSE;
          if (print_calc)
            printf("option -house requires option -ut for Universal Time\n");
        } else {
          strcpy(s1, dms(top_long, round_flag));
          strcpy(s2, dms(top_lat, round_flag));
          //          if(vm["common.print_calc"].as<bool>()) printf ("Houses
          //          system %c (%s) for long=%s, lat=%s\n", ihsy, shsy, s1,
          //                 s2);
        }
      }
    }
    if (with_header && !with_header_always) with_header = FALSE;
    if (do_ayanamsa) {
      if (swe_get_ayanamsa_ex(te, iflag, &daya, serr) == ERR) {
        if (print_calc) printf("   error in swe_get_ayanamsa_ex(): %s\n", serr);
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
          if (ipl >= SE_SUN && ipl <= SE_VESTA) swe_get_planet_name(ipl, spnam);
          print_line(MODE_LABEL, is_first, 0);
          is_first = FALSE;
        }
        if (print_calc) printf("\n");
      } else {
        print_line(MODE_LABEL, TRUE, 0);
      }
    }
    is_first = TRUE;
    for (psp = plsel; *psp != '\0'; psp++) {
      if (*psp == 'e') continue;
      ipl = letter_to_ipl((int)*psp);
      if (ipl == -2) {
        if (print_calc) printf("illegal parameter -p%s\n", plsel);
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
        if (ipl == SE_MEAN_NODE || ipl == SE_TRUE_NODE || ipl == SE_MEAN_APOG ||
            ipl == SE_OSCU_APOG)
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
            if (print_calc)
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
          if (print_calc)
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
              iflgret = swe_calc(te, ipldiff, iflag2 | SEFLG_HELCTR, x2, serr);
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
              iflgret = swe_calc(te, ipldiff, iflag2 | SEFLG_HELCTR, x2, serr);
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
              iflgret = swe_calc(te, ipldiff, iflag2 | SEFLG_HELCTR, x2, serr);
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
          swe_gauquelin_sector(tut, ipl, star2, iflag, hpos_meth, geopos, 0, 0,
                               &hposj, serr);
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
        if (print_calc)
          printf("****** line count %d was exceeded\n", line_limit);
        break;
      }
    } /* for psp */
    if (list_hor) {
      if (print_calc) printf("\n");
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
        if (print_calc) printf("\n");
        line_count++;
      }
    }
    if (line_count >= line_limit) break;
  } /* for tjd */
  if (*serr_warn != '\0') {
    if (print_calc) printf("\nwarning: ");
    fputs(serr_warn, stdout);
    if (print_calc) printf("\n");
  }

/* close open files and free allocated space */
end_main:
  if (do_set_astro_models) {
    if (print_calc) printf(smod);
  }
  swe_close();
  return OK;
}
