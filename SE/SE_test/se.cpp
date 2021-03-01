#include <array>
#include <iostream>
#include <string>
using namespace std;
#include "swephexp.h" /* this includes  "sweodef.h" */

int main(int argc, char** argv) {
  char sdate[AS_MAXCH], snam[40], serr[AS_MAXCH];
  int jday = 1, jmon = 1, jyear = 2000;
  double jut = 0.0;
  double tjd, te, x2[6];
  int32 iflag, iflgret;
  int p;
  //  swe_set_ephe_path(NULL);
  swe_set_ephe_path(argv[1]);
  iflag = SEFLG_SPEED;

  //  while (TRUE) {
  //  printf("\nDate (d.m.y) ?");

  //  swe_set_sid_mode(int32 sid_mode, double t0, double ayan_t0)
  swe_set_sid_mode(SE_SIDM_LAHIRI, 0, 0);

  cout << "Введите дату:(d.m.y)" << endl;
  /*gets(sdate);*/
  //  if (!fgets(sdate, sizeof(sdate) - 1, stdin)) return OK;
  string date = "17-11-1966";
  int k = 0;
  for (auto i : date) {
    sdate[k] = date[k];
    ++k;
  }
  cout << "Введено:" << sdate << endl;
  /*
   * stop if a period . is entered
   */
  if (*sdate == '.') return OK;
  if (sscanf(sdate, "%d%*c%d%*c%d", &jday, &jmon, &jyear) < 1) exit(1);
  /*
   * we have day, month and year and convert to Julian day number
   */
  tjd = swe_julday(jyear, jmon, jday, jut, SE_GREG_CAL);
  /*
   * compute Ephemeris time from Universal time by adding delta_t
   */
  te = tjd + swe_deltat(tjd);
  printf("date: %02d.%02d.%d at 0:00 Universal time\n", jday, jmon, jyear);
  printf("planet     \tlongitude\tlatitude\tdistance\tspeed long.\n");
  /*
   * a loop over all planets
   */
  //  for (p = SE_SUN; p <= SE_CHIRON; p++) {

  //#define SE_SUN 0
  //#define SE_MOON 1
  //#define SE_MERCURY 2
  //#define SE_VENUS 3
  //#define SE_MARS 4
  //#define SE_JUPITER 5
  //#define SE_SATURN 6
  //#define SE_URANUS 7
  //#define SE_NEPTUNE 8
  //#define SE_PLUTO 9
  //#define SE_MEAN_NODE 10
  //#define SE_TRUE_NODE 11

  for (p = 0; p <= 11; p++) {
    if (p == 7) p = 10;
    //    if (p == SE_EARTH) continue;
    /*
     * do the coordinate calculation for this planet p
     */
    iflgret = swe_calc(te, p, iflag, x2, serr);
    /*
     * if there is a problem, a negative value is returned and an
     * errpr message is in serr.
     */
    if (iflgret < 0)
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
      printf("warning: iflgret != iflag. %s\n", serr);
    /*
     * get the name of the planet p
     */
    swe_get_planet_name(p, snam);
    /*
     * print the coordinates
     */
    printf("%10s\t%11.7f\t%10.7f\t%10.7f\t%10.7f\n", snam, x2[0], x2[1], x2[2],
           x2[3]);
  }
  //  }
  return OK;
}
