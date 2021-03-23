#pragma once

#include <sys/stat.h>

#include <boost/program_options.hpp>
#include <chrono>
#include <ctime>    // localtime
#include <iomanip>  // put_time
#include <sstream>  // stringstream
#include <string>

#include "main_info.h"
#include "sweph.h"
#include "swephexp.h" /* this includes  "sweodef.h" */
#include "swephlib.h"
#include "test.h"

#define J2000 2451545.0 /* 2000 January 1.5 */
#define square_sum(x) (x[0] * x[0] + x[1] * x[1] + x[2] * x[2])
#define SEFLG_EPHMASK (SEFLG_JPLEPH | SEFLG_SWIEPH | SEFLG_MOSEPH)

#define BIT_ROUND_SEC 1
#define BIT_ROUND_MIN 2
#define BIT_ZODIAC 4
#define BIT_LZEROES 8

#define BIT_TIME_LZEROES 8
#define BIT_TIME_LMT 16
#define BIT_TIME_LAT 32
#define BIT_ALLOW_361 64

#define PLSEL_D "0123456789mtA"
#define PLSEL_P "0123456789mtABCcgDEFGHI"
#define PLSEL_H "JKLMNOPQRSTUVWXYZw"
#define PLSEL_A "0123456789mtABCcgDEFGHIJKLMNOPQRSTUVWXYZw"

#define DIFF_DIFF 'd'
#define DIFF_GEOHEL 'h'
#define DIFF_MIDP 'D'
#define MODE_HOUSE 1
#define MODE_LABEL 2
#define MODE_AYANAMSA 4

#define SEARCH_RANGE_LUNAR_CYCLES 20000

#define LEN_SOUT 1000  // length of output string variable

using namespace std;

static char se_pname[AS_MAXCH];
static char* zod_nam[] = {"ar", "ta", "ge", "cn", "le", "vi",
                          "li", "sc", "sa", "cp", "aq", "pi"};

static char star[AS_MAXCH] = "algol", star2[AS_MAXCH];
static char sastno[AS_MAXCH] = "433";
static char shyp[AS_MAXCH] = "1";

char* dms(double x, int32 iflag);
int make_ephemeris_path(char* argv0, char* ephepath);
int letter_to_ipl(int letter);
int print_line(int mode, AS_BOOL is_first, int sid_mode);
int do_special_event(double tjd, int32 ipl, char* star, int32 special_event,
                     int32 special_mode, double* geopos, double* datm,
                     double* dobs, char* serr);
int32 orbital_elements(double tjd_et, int32 ipl, int32 iflag, char* serr);
char* hms_from_tjd(double x);
void do_printf(char* info);
char* hms(double x, int32 iflag);
void remove_whitespace(char* s);
int32 call_swe_fixstar(char* star, double te, int32 iflag, double* x,
                       char* serr);
void jd_to_time_string(double jut, char* stimeout);
char* our_strcpy(char* to, char* from);
int32 ut_to_lmt_lat(double t_ut, double* geopos, double* t_ret, char* serr);
int32 print_rise_set_line(double trise, double tset, double* geopos,
                          char* serr);
int32 call_rise_set(double t_ut, int32 ipl, char* star, int32 whicheph,
                    double* geopos, char* serr);
void insert_gap_string_for_tabs(char* sout, char* gap);
char* get_gregjul(int gregflag, int year);
int32 call_lunar_occultation(double t_ut, int32 ipl, char* star, int32 whicheph,
                             int32 special_mode, double* geopos, char* serr);
int do_special_event(double tjd, int32 ipl, char* star, int32 special_event,
                     int32 special_mode, double* geopos, double* datm,
                     double* dobs, char* serr);
int32 call_lunar_eclipse(double t_ut, int32 whicheph, int32 special_mode,
                         double* geopos, char* serr);
int32 call_solar_eclipse(double t_ut, int32 whicheph, int32 special_mode,
                         double* geopos, char* serr);
int32 call_heliacal_event(double t_ut, int32 ipl, char* star, int32 whicheph,
                          double* geopos, double* datm, double* dobs,
                          char* serr);
void do_print_heliacal(double* dret, int32 event_type, char* obj_name);
void format_lon_lat(char* slon, char* slat, double lon, double lat);
int32 get_geocentric_relative_distance(double tjd_et, int32 ipl, int32 iflag,
                                       char* serr);

static char* fmt = "PLBRS";
static char* gap = " ";
static double t, te, tut, jut = 0;
static int jmon, jday, jyear;
static int ipl = SE_SUN, ipldiff = SE_SUN, nhouses = 12;
static int iplctr = SE_SUN;
static char spnam[AS_MAXCH], spnam2[AS_MAXCH], serr[AS_MAXCH];
static char serr_save[AS_MAXCH], serr_warn[AS_MAXCH];
static int gregflag = SE_GREG_CAL;
static int diff_mode = 0;
static AS_BOOL use_dms = FALSE;
static AS_BOOL universal_time = FALSE;
static AS_BOOL universal_time_utc = FALSE;
static int32 round_flag = 0;
static int32 time_flag = 0;
static AS_BOOL short_output = FALSE;
static AS_BOOL list_hor = FALSE;
static int32 special_event = 0;
static int32 special_mode = 0;
static AS_BOOL do_orbital_elements = FALSE;
static AS_BOOL hel_using_AV = FALSE;
static AS_BOOL with_header = TRUE;
static AS_BOOL with_chart_link = FALSE;
static double x[6], x2[6], xequ[6], xcart[6], xcartq[6], xobl[6], xaz[6], xt[6],
    hpos, hpos2, hposj, armc, xsv[6];
static int hpos_meth = 0;
static double geopos[10];
static double attr[20], tret[20], datm[4], dobs[6];
static int32 iflag = 0, iflag2; /* external flag: helio, geo... */
static char* hs_nam[] = {"undef",          "Ascendant",       "MC",
                         "ARMC",           "Vertex",          "equat. Asc.",
                         "co-Asc. W.Koch", "co-Asc Munkasey", "Polar Asc."};
static int direction = 1;
static AS_BOOL direction_flag = FALSE;
static AS_BOOL step_in_minutes = FALSE;
static AS_BOOL step_in_seconds = FALSE;
static AS_BOOL step_in_years = FALSE;
static AS_BOOL step_in_months = FALSE;
static int32 helflag = 0;
static double tjd = 2415020.5;
static int32 nstep = 1, istep;
static int32 search_flag = 0;
static char sout[LEN_SOUT];
static int32 whicheph = SEFLG_SWIEPH;
static char* psp;
static int32 norefrac = 0;
static int32 disccenter = 0;
static int32 discbottom = 0;
static int32 hindu = 0;
/* for test of old models only */
static char* astro_models;
static int do_set_astro_models = FALSE;
static char smod[2000];
static AS_BOOL inut = FALSE; /* for Astrodienst internal feature */
static AS_BOOL have_gap_parameter = FALSE;
static AS_BOOL use_swe_fixstar2 = FALSE;
static AS_BOOL output_extra_prec = FALSE;
static AS_BOOL show_file_limit = FALSE;

#define SP_LUNAR_ECLIPSE 1
#define SP_SOLAR_ECLIPSE 2
#define SP_OCCULTATION 3
#define SP_RISE_SET 4
#define SP_MERIDIAN_TRANSIT 5
#define SP_HELIACAL 6

#define SP_MODE_HOW 2   /* an option for Lunar */
#define SP_MODE_LOCAL 8 /* an option for Solar */
#define SP_MODE_HOCAL 4096

#define ECL_LUN_PENUMBRAL 1 /* eclipse types for hocal list */
#define ECL_LUN_PARTIAL 2
#define ECL_LUN_TOTAL 3
#define ECL_SOL_PARTIAL 4
#define ECL_SOL_ANNULAR 5
#define ECL_SOL_TOTAL 6
