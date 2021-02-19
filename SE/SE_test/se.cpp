
#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
  char sdate[AS_MAXCH], snam[40], serr[AS_MAXCH];  
  int jday = 1, jmon = 1, jyear = 2000;
  double jut = 0.0;
  double tjd, te, x2[6];
  int32 iflag, iflgret;
  int p;
  swe_set_ephe_path(NULL);
  iflag = SEFLG_SPEED;
  while (TRUE) {
    printf("\nDate (d.m.y) ?");
    /*gets(sdate);*/
    if( !fgets(sdate, sizeof(sdate)-1, stdin) ) return OK;
		/*
		 * stop if a period . is entered
		 */
    if (*sdate == '.') 
      return OK;
    if (sscanf (sdate, "%d%*c%d%*c%d", &jday,&jmon,&jyear) < 1) exit(1);
	    /*
	     * we have day, month and year and convert to Julian day number
	     */
    tjd = swe_julday(jyear,jmon,jday,jut,SE_GREG_CAL);        
	    /*
	     * compute Ephemeris time from Universal time by adding delta_t
	     */
    te = tjd + swe_deltat(tjd);
    printf("date: %02d.%02d.%d at 0:00 Universal time\n", jday, jmon, jyear);
    printf("planet     \tlongitude\tlatitude\tdistance\tspeed long.\n");
	    /*
	     * a loop over all planets
	     */
    for (p = SE_SUN; p <= SE_CHIRON; p++) {
      if (p == SE_EARTH) continue;
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
      printf("%10s\t%11.7f\t%10.7f\t%10.7f\t%10.7f\n",
	     snam, x2[0], x2[1], x2[2], x2[3]);
    }
  }
  return OK;
}
