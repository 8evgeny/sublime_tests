//-sid1 -ut04:50:00 -p0123456mt -house35,47,A

static char* infocmd0 =
    "\n\
  Swetest computes a complete set of geocentric planetary positions,\n\
  for a given date or a sequence of dates.\n\
  Input can either be a date or an absolute julian day number.\n\
  0:00 (midnight).\n\
  With the proper options, swetest can be used to output a printed\n\
  ephemeris and transfer the data into other programs like spreadsheets\n\
  for graphical display.\n\
  Version:                                                                                   \n\
\n";
static char* infocmd1 =
    "\n\
  Command line options:\n\
     help commands:\n\
        -?, -h  display whole info\n\
        -hcmd   display commands\n\
        -hplan  display planet numbers\n\
        -hform  display format characters\n\
        -hdate  display input date format\n\
        -hexamp  display examples\n\
        -glp  report file location of library\n\
     input time formats:\n\
        -bDATE  begin date; e.g. -b1.1.1992 if\n\
                Note: the date format is day month year (European style).\n\
        -bj...  begin date as an absolute Julian day number; e.g. -bj2415020.5\n\
        -j...   same as -bj\n\
        -tHH.MMSS  input time (as Ephemeris Time)\n\
        -ut     input date is Universal Time (UT1)\n\
    -utHH:MM:SS input time (as Universal Time)\n\
    -utHH.MMSS input time (as Universal Time)\n\
    -utcHH.MM:SS input time (as Universal Time Coordinated UTC)\n\
     output time for eclipses, occultations, risings/settings is UT by default\n\
        -lmt    output date/time is LMT (with -geopos)\n\
        -lat    output date/time is LAT (with -geopos)\n\
     object, number of steps, step with\n\
        -pSEQ   planet sequence to be computed.\n\
                See the letter coding below.\n\
        -dX     differential ephemeris: print differential ephemeris between\n\
                body X and each body in list given by -p\n\
                example: -p2 -d0 -fJl -n366 -b1.1.1992 prints the longitude\n\
                distance between SUN (planet 0) and MERCURY (planet 2)\n\
                for a full year starting at 1 Jan 1992.\n\
        -dhX    differential ephemeris: print differential ephemeris between\n\
                heliocentric body X and each body in list given by -p\n\
                example: -p8 -dh8 -ftl -n36600 -b1.1.1500 -s5 prints the longitude\n\
                distance between geocentric and heliocentric Neptune (planet 8)\n\
                for 500 year starting at 1 Jan 1500.\n\
        Using this option mostly makes sense for a single planet\n\
        to find out how much its geocentric and heliocentric positions can differ\n\
        over extended periods of time\n\
    -DX	midpoint ephemeris, works the same way as the differential\n\
        mode -d described above, but outputs the midpoint position.\n\
        -nN     output data for N consecutive timesteps; if no -n option\n\
                is given, the default is 1. If the option -n without a\n\
                number is given, the default is 20.\n\
        -sN     timestep N days, default 1. This option is only meaningful\n\
                when combined with option -n.\n\
                If an 'y' is appended, the time step is in years instead of days, \n\
                for example -s10y for a time step of 10 years.\n\
                If an 'mo' is appended, the time step is in months instead of days, \n\
                for example -s3mo for a time step of 3 months.\n\
                If an 'm' is appended, the time step is in minutes instead of days, \n\
                for example -s15m for a time step of 15 minutes.\n\
                If an 's' is appended, the time step is in seconds instead of days, \n\
                for example -s1s for a time step of 1 second.\n\
";
static char* infocmd2 =
    "\
     output format:\n\
        -fSEQ   use SEQ as format sequence for the output columns;\n\
                default is PLBRS.\n\
        -head   don\'t print the header before the planet data. This option\n\
                is useful when you want to paste the output into a\n\
                spreadsheet for displaying graphical ephemeris.\n\
        +head   header before every step (with -s..) \n\
        -gPPP   use PPP as gap between output columns; default is a single\n\
                blank.  -g followed by white space sets the\n\
                gap to the TAB character; which is useful for data entry\n\
                into spreadsheets.\n\
        -hor	list data for multiple planets 'horizontally' in same line.\n\
        all columns of -fSEQ are repeated except time colums tTJyY.\n\
     astrological house system:\n\
        -house[long,lat,hsys]	\n\
        include house cusps. The longitude, latitude (degrees with\n\
        DECIMAL fraction) and house system letter can be given, with\n\
        commas separated, + for east and north. If none are given,\n\
        Greenwich UK and Placidus is used: 0.00,51.50,p.\n\
        The output lists 12 house cusps, Asc, MC, ARMC, Vertex,\n\
        Equatorial Ascendant, co-Ascendant as defined by Walter Koch, \n\
        co-Ascendant as defined by Michael Munkasey, and Polar Ascendant. \n\
        Houses can only be computed if option -ut is given.\n\
                   A  equal\n\
                   B  Alcabitius\n\
                   C  Campanus\n\
                   D  equal / MC\n\
                   E  equal = A\n\
                   F  Carter poli-equatorial\n\
                   G  36 Gauquelin sectors\n\
                   H  horizon / azimuth\n\
                   I  Sunshine\n\
                   i  Sunshine alternative\n\
                   K  Koch\n\
                   L  Pullen S-delta\n\
                   M  Morinus\n\
                   N  Whole sign, Aries = 1st house\n\
                   O  Porphyry\n\
                   P  Placidus\n\
                   Q  Pullen S-ratio\n\
                   R  Regiomontanus\n\
                   S  Sripati\n\
                   T  Polich/Page (\"topocentric\")\n\
                   U  Krusinski-Pisa-Goelzer\n\
                   V  equal Vehlow\n\
                   W  equal, whole sign\n\
                   X  axial rotation system/ Meridian houses\n\
                   Y  APC houses\n\
         The use of lower case letters is deprecated. They will have a\n\
         different meaning in future releases of Swiss Ephemeris.\n\
        -hsy[hsys]	\n\
         house system to be used (for house positions of planets)\n\
         for long, lat, hsys, see -house\n\
         The use of lower case letters is deprecated. They will have a\n\
         different meaning in future releases of Swiss Ephemeris.\n\
";
static char* infocmd3 =
    "\
        -geopos[long,lat,elev]	\n\
        Geographic position. Can be used for azimuth and altitude\n\
                or house cups calculations.\n\
                The longitude, latitude (degrees with DECIMAL fraction)\n\
        and elevation (meters) can be given, with\n\
        commas separated, + for east and north. If none are given,\n\
        Greenwich is used: 0,51.5,0.\n\
        For topocentric planet positions please user the parameter -topo\n\
     sidereal astrology:\n\
    -ay..   ayanamsha, with number of method, e.g. ay0 for Fagan/Bradley\n\
    -sid..    sidereal, with number of method (see below)\n\
    -sidt0..  dito, but planets are projected on the ecliptic plane of the\n\
              reference date of the ayanamsha (more info in general documentation\n\
          www.astro.com/swisseph/swisseph.htm)\n\
    -sidsp..  dito, but planets are projected on the solar system plane.\n\
          (see www.astro.com/swisseph/swisseph.htm)\n\
        -sidudef[jd,ay0,...]  sidereal, with user defined ayanamsha; \n\
              jd=julian day number in TT/ET\n\
              ay0=initial value of ayanamsha, \n\
          ...=optional parameters, comma-sparated:\n\
          'jdisut': ayanamsha reference date is UT\n\
          'eclt0':  project on ecliptic of reference date (like -sidt0..)\n\
          'ssyplane':  project on solar system plane (like -sidsp..)\n\
          e.g. '-sidudef2452163.8333333,25.0,jdisut': ayanamsha is 25.0° on JD 2452163.8333333 UT\n\
           number of ayanamsha method:\n\
       0 for Fagan/Bradley\n\
       1 for Lahiri\n\
       2 for De Luce\n\
       3 for Raman\n\
       4 for Usha/Shashi\n\
       5 for Krishnamurti\n\
       6 for Djwhal Khul\n\
       7 for Yukteshwar\n\
       8 for J.N. Bhasin\n\
       9 for Babylonian/Kugler 1\n\
       10 for Babylonian/Kugler 2\n\
       11 for Babylonian/Kugler 3\n\
       12 for Babylonian/Huber\n\
       13 for Babylonian/Eta Piscium\n\
       14 for Babylonian/Aldebaran = 15 Tau\n\
       15 for Hipparchos\n\
       16 for Sassanian\n\
       17 for Galact. Center = 0 Sag\n\
       18 for J2000\n\
       19 for J1900\n\
       20 for B1950\n\
       21 for Suryasiddhanta\n\
       22 for Suryasiddhanta, mean Sun\n\
       23 for Aryabhata\n\
       24 for Aryabhata, mean Sun\n\
       25 for SS Revati\n\
       26 for SS Citra\n\
       27 for True Citra\n\
       28 for True Revati\n\
       29 for True Pushya (PVRN Rao)\n\
       30 for Galactic (Gil Brand)\n\
       31 for Galactic Equator (IAU1958)\n\
       32 for Galactic Equator\n\
       33 for Galactic Equator mid-Mula\n\
       34 for Skydram (Mardyks)\n\
       35 for True Mula (Chandra Hari)\n\
       36 Dhruva/Gal.Center/Mula (Wilhelm)\n\
       37 Aryabhata 522\n\
       38 Babylonian/Britton\n\
       39 Vedic/Sheoran\n\
       40 Cochrane (Gal.Center = 0 Cap)\n\
       41 Galactic Equator (Fiorenza)\n\
       42 Vettius Valens\n\
     ephemeris specifications:\n\
        -edirPATH change the directory of the ephemeris files \n\
        -eswe   swiss ephemeris\n\
        -ejpl   jpl ephemeris (DE431), or with ephemeris file name\n\
                -ejplde200.eph \n\
        -emos   moshier ephemeris\n\
        -true             true positions\n\
        -noaberr          no aberration\n\
        -nodefl           no gravitational light deflection\n\
    -noaberr -nodefl  astrometric positions\n\
        -j2000            no precession (i.e. J2000 positions)\n\
        -icrs             ICRS (use Internat. Celestial Reference System)\n\
        -nonut            no nutation \n\
";
static char* infocmd4 =
    "\
        -speed            calculate high precision speed \n\
        -speed3           'low' precision speed from 3 positions \n\
                          do not use this option. -speed parameter\n\
              is faster and more precise \n\
    -iXX	          force iflag to value XX\n\
        -testaa96         test example in AA 96, B37,\n\
                          i.e. venus, j2450442.5, DE200.\n\
                          attention: use precession IAU1976\n\
                          and nutation 1980 (s. swephlib.h)\n\
        -testaa95\n\
        -testaa97\n\
        -roundsec         round to seconds\n\
        -roundmin         round to minutes\n\
    -dms              use dms instead of fractions, at some places\n\
    -lim		  print ephemeris file range\n\
     observer position:\n\
        -hel    compute heliocentric positions\n\
        -bary   compute barycentric positions (bar. earth instead of node) \n\
        -topo[long,lat,elev]	\n\
        topocentric positions. The longitude, latitude (degrees with\n\
        DECIMAL fraction) and elevation (meters) can be given, with\n\
        commas separated, + for east and north. If none are given,\n\
        Greenwich is used 0.00,51.50,0\n\
     orbital elements:\n\
        -orbel  compute osculating orbital elements relative to the\n\
            mean ecliptic J2000. (Note, all values, including time of\n\
        pericenter vary considerably depending on the date for which the\n\
        osculating ellipse is calculated\n\
\n\
     special events:\n\
        -solecl solar eclipse\n\
                output 1st line:\n\
                  eclipse date,\n\
                  time of maximum (UT):\n\
            geocentric angle between centre of Sun and Moon reaches minimum.\n\
                  core shadow width (negative with total eclipses),\n\
          eclipse magnitudes:\n\
            1. NASA method (= 2. with partial ecl. and \n\
               ratio lunar/solar diameter with total and annular ecl.)\n\
            2. fraction of solar diameter covered by moon;\n\
               if the value is > 1, it means that Moon covers more than\n\
               just the solar disk\n\
            3. fraction of solar disc covered by moon (obscuration)\n\
               with total and annular eclipses it is the ratio of\n\
               the sizes of the solar disk and the lunar disk.\n\
          Saros series and eclipse number\n\
          Julian day number (6-digit fraction) of maximum\n\
                output 2nd line:\n\
                  start and end times for partial and total phases\n\
          delta t in sec\n\
                output 3rd line:\n\
                  geographical longitude and latitude of maximum eclipse,\n\
                  totality duration at that geographical position,\n\
                output with -local, see below.\n\
        -occult occultation of planet or star by the moon. Use -p to \n\
                specify planet (-pf -xfAldebaran for stars) \n\
                output format same as with -solecl, with the following differences:\n\
          Magnitude is defined like no. 2. with solar eclipses.\n\
          There are no saros series.\n\
";
static char* infocmd5 =
    "\
        -lunecl lunar eclipse\n\
                output 1st line:\n\
                  eclipse date,\n\
                  time of maximum (UT),\n\
                  eclipse magnitudes: umbral and penumbral\n\
            method as method 2 with solar eclipses\n\
          Saros series and eclipse number \n\
          Julian day number (6-digit fraction) of maximum\n\
                output 2nd line:\n\
                  6 contacts for start and end of penumbral, partial, and\n\
                  total phase\n\
          delta t in sec\n\
                output 3rd line:\n\
                  geographic position where the Moon is in zenith at maximum eclipse\n\
        -local  only with -solecl or -occult, if the next event of this\n\
                kind is wanted for a given geogr. position.\n\
                Use -geopos[long,lat,elev] to specify that position.\n\
                If -local is not set, the program \n\
                searches for the next event anywhere on earth.\n\
                output 1st line:\n\
                  eclipse date,\n\
                  time of maximum,\n\
                  eclipse magnitudes, as with global solar eclipse function \n\
            (with occultations: only diameter method, see solar eclipses, method 2)\n\
          Saros series and eclipse number (with solar eclipses only)\n\
          Julian day number (6-digit fraction) of maximum\n\
                output 2nd line:\n\
                  local eclipse duration for totality (zero with partial occultations)\n\
                  local four contacts,\n\
          delta t in sec\n\
        Occultations with the remark \"(daytime)\" cannot be observed because\n\
        they are taking place by daylight. Occultations with the remark\n\
        \"(sunrise)\" or \"(sunset)\" can be observed only partly because part\n\
        of them takes place in daylight.\n\
        -hev[type] heliacal events,\n\
        type 1 = heliacal rising\n\
        type 2 = heliacal setting\n\
        type 3 = evening first\n\
        type 4 = morning last\n\
            type 0 or missing = all four events are listed.\n\
        -rise   rising and setting of a planet or star.\n\
                Use -geopos[long,lat,elev] to specify geographical position.\n\
        -metr   southern and northern meridian transit of a planet of star\n\
                Use -geopos[long,lat,elev] to specify geographical position.\n\
     specifications for eclipses:\n\
        -total  total eclipse (only with -solecl, -lunecl)\n\
        -partial partial eclipse (only with -solecl, -lunecl)\n\
        -annular annular eclipse (only with -solecl)\n\
        -anntot annular-total (hybrid) eclipse (only with -solecl)\n\
        -penumbral penumbral lunar eclipse (only with -lunecl)\n\
        -central central eclipse (only with -solecl, nonlocal)\n\
        -noncentral non-central eclipse (only with -solecl, nonlocal)\n\
";
static char* infocmd6 =
    "\
     specifications for risings and settings:\n\
        -norefrac   neglect refraction (with option -rise)\n\
        -disccenter find rise of disc center (with option -rise)\n\
        -discbottom find rise of disc bottom (with option -rise)\n\
    -hindu      hindu version of sunrise (with option -rise)\n\
     specifications for heliacal events:\n\
        -at[press,temp,rhum,visr]:\n\
                pressure in hPa\n\
            temperature in degrees Celsius\n\
            relative humidity in %\n\
            visual range, interpreted as follows:\n\
              > 1 : meteorological range in km\n\
              1>visr>0 : total atmospheric coefficient (ktot)\n\
              = 0 : calculated from press, temp, rhum\n\
            Default values are -at1013.25,15,40,0\n\
         -obs[age,SN] age of observer and Snellen ratio\n\
                Default values are -obs36,1\n\
         -opt[age,SN,binocular,magn,diam,transm]\n\
                age and SN as with -obs\n\
            0 monocular or 1 binocular\n\
            telescope magnification\n\
            optical aperture in mm\n\
            optical transmission\n\
            Default values: -opt36,1,1,1,0,0 (naked eye)\n\
     backward search:\n\
        -bwd\n";
/* characters still available:
  ijklruv
 */
static char* infoplan =
    "\n\
  Planet selection letters:\n\
     planetary lists:\n\
        d (default) main factors 0123456789mtABCcg\n\
        p main factors as above, plus main asteroids DEFGHI\n\
        h ficticious factors J..X\n\
        a all factors\n\
        (the letters above can only appear as a single letter)\n\n\
     single body numbers/letters:\n\
        0 Sun (character zero)\n\
        1 Moon (character 1)\n\
        2 Mercury\n\
        3 Venus\n\
        4 Mars\n\
        5 Jupiter\n\
        6 Saturn\n\
        7 Uranus\n\
        8 Neptune\n\
        9 Pluto\n\
        m mean lunar node\n\
        t true lunar node\n\
        n nutation\n\
        o obliquity of ecliptic\n\
    q delta t\n\
    y time equation\n\
    b ayanamsha\n\
        A mean lunar apogee (Lilith, Black Moon) \n\
        B osculating lunar apogee \n\
        c intp. lunar apogee \n\
        g intp. lunar perigee \n\
        C Earth (in heliocentric or barycentric calculation)\n\
     dwarf planets, plutoids\n\
        F Ceres\n\
    9 Pluto\n\
    s -xs136199   Eris\n\
    s -xs136472   Makemake\n\
    s -xs136108   Haumea\n\
     some minor planets:\n\
        D Chiron\n\
        E Pholus\n\
        G Pallas \n\
        H Juno \n\
        I Vesta \n\
        s minor planet, with MPC number given in -xs\n\
     fixed stars:\n\
        f fixed star, with name or number given in -xf option\n\
    f -xfSirius   Sirius\n\
     fictitious objects:\n\
        J Cupido \n\
        K Hades \n\
        L Zeus \n\
        M Kronos \n\
        N Apollon \n\
        O Admetos \n\
        P Vulkanus \n\
        Q Poseidon \n\
        R Isis (Sevin) \n\
        S Nibiru (Sitchin) \n\
        T Harrington \n\
        U Leverrier's Neptune\n\
        V Adams' Neptune\n\
        W Lowell's Pluto\n\
        X Pickering's Pluto\n\
        Y Vulcan\n\
        Z White Moon\n\
    w Waldemath's dark Moon\n\
        z hypothetical body, with number given in -xz\n\
     sidereal time:\n\
        x sidereal time\n\
        e print a line of labels\n\
          \n";
/* characters still available
   CcEeMmOoqWwz
*/
static char* infoform =
    "\n\
  Output format SEQ letters:\n\
  In the standard setting five columns of coordinates are printed with\n\
  the default format PLBRS. You can change the default by providing an\n\
  option like -fCCCC where CCCC is your sequence of columns.\n\
  The coding of the sequence is like this:\n\
        y year\n\
        Y year.fraction_of_year\n\
        p planet index\n\
        P planet name\n\
        J absolute juldate\n\
        T date formatted like 23.02.1992 \n\
        t date formatted like 920223 for 1992 february 23\n\
        L longitude in degree ddd mm'ss\"\n\
        l longitude decimal\n\
        Z longitude ddsignmm'ss\"\n\
        S speed in longitude in degree ddd:mm:ss per day\n\
        SS speed for all values specified in fmt\n\
        s speed longitude decimal (degrees/day)\n\
        ss speed for all values specified in fmt\n\
        B latitude degree\n\
        b latitude decimal\n\
        R distance decimal in AU\n\
        r distance decimal in AU, Moon in seconds parallax\n\
        W distance decimal in light years\n\
        w distance decimal in km\n\
        q relative distance (1000=nearest, 0=furthest)\n\
        A right ascension in hh:mm:ss\n\
        a right ascension hours decimal\n\
        D declination degree\n\
        d declination decimal\n\
        I azimuth degree\n\
        i azimuth decimal\n\
        H altitude degree\n\
        h altitude decimal\n\
        K altitude (with refraction) degree\n\
        k altitude (with refraction) decimal\n\
        G house position in degrees\n\
        g house position in degrees decimal\n\
        j house number 1.0 - 12.99999\n\
        X x-, y-, and z-coordinates ecliptical\n\
        x x-, y-, and z-coordinates equatorial\n\
        U unit vector ecliptical\n\
        u unit vector equatorial\n\
        Q l, b, r, dl, db, dr, a, d, da, dd\n\
    n nodes (mean): ascending/descending (Me - Ne); longitude decimal\n\
    N nodes (osculating): ascending/descending, longitude; decimal\n\
    f apsides (mean): perihelion, aphelion, second focal point; longitude dec.\n\
    F apsides (osc.): perihelion, aphelion, second focal point; longitude dec.\n\
    + phase angle\n\
    - phase\n\
    * elongation\n\
    / apparent diameter of disc (without refraction)\n\
    = magnitude\n";
static char* infoform2 =
    "\
        v (reserved)\n\
        V (reserved)\n\
    ";
static char* infodate =
    "\n\
  Date entry:\n\
  In the interactive mode, when you are asked for a start date,\n\
  you can enter data in one of the following formats:\n\
\n\
        1.2.1991        three integers separated by a nondigit character for\n\
                        day month year. Dates are interpreted as Gregorian\n\
                        after 4.10.1582 and as Julian Calendar before.\n\
                        Time is always set to midnight (0 h).\n\
                        If the three letters jul are appended to the date,\n\
                        the Julian calendar is used even after 1582.\n\
                        If the four letters greg are appended to the date,\n\
                        the Gregorian calendar is used even before 1582.\n\
\n\
        j2400123.67     the letter j followed by a real number, for\n\
                        the absolute Julian daynumber of the start date.\n\
                        Fraction .5 indicates midnight, fraction .0\n\
                        indicates noon, other times of the day can be\n\
                        chosen accordingly.\n\
\n\
        <RETURN>        repeat the last entry\n\
        \n\
        .               stop the program\n\
\n\
        +20             advance the date by 20 days\n\
\n\
        -10             go back in time 10 days\n";
static char* infoexamp =
    "\n\
\n\
  Examples:\n\
\n\
    swetest -p2 -b1.12.1900 -n15 -s2\n\
    ephemeris of Mercury (-p2) starting on 1 Dec 1900,\n\
    15 positions (-n15) in two-day steps (-s2)\n\
\n\
    swetest -p2 -b1.12.1900 -n15 -s2 -fTZ -roundsec -g, -head\n\
    same, but output format =  date and zodiacal position (-fTZ),\n\
    separated by comma (-g,) and rounded to seconds (-roundsec),\n\
    without header (-head).\n\
\n\
    swetest -ps -xs433 -b1.12.1900\n\
    position of asteroid 433 Eros (-ps -xs433)\n\
\n\
    swetest -pf -xfAldebaran -b1.1.2000\n\
    position of fixed star Aldebaran \n\
\n\
    swetest -p1 -d0 -b1.12.1900 -n10 -fPTl -head\n\
    angular distance of moon (-p1) from sun (-d0) for 10\n\
    consecutive days (-n10).\n\
\n\
    swetest -p6 -DD -b1.12.1900 -n100 -s5 -fPTZ -head -roundmin\n\
      Midpoints between Saturn (-p6) and Chiron (-DD) for 100\n\
      consecutive steps (-n100) with 5-day steps (-s5) with\n\
      longitude in degree-sign format (-f..Z) rounded to minutes (-roundmin)\n\
\n\
    swetest -b5.1.2002 -p -house12.05,49.50,K -ut12:30\n\
    Koch houses for a location in Germany at a given date and time\n\
\n\
    swetest -b1.1.2016  -g -fTlbR -p0123456789Dmte -hor -n366 -roundsec\n\
    tabular ephemeris (all planets Sun - Pluto, Chiron, mean node, true node)\n\
    in one horizontal row, tab-separated, for 366 days. For each planet\n\
    list longitude, latitude and geocentric distance.\n";
/**************************************************************/
