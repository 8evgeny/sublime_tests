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
};

nativ::nativ() {
  po::variables_map vm;
  string datenow, timenow;
  datetimenow(datenow, timenow);
  readConfig("../config/config.ini", vm, "");
  bday = datenow;
  btime = timenow;
  lon = vm["common.lon_current"].as<std::string>();
  lat = vm["common.lat_current"].as<std::string>();
  name = vm["common.name"].as<std::string>();
  print_calc = vm["common.print_calc"].as<bool>();
  path = vm["common.ephPatch"].as<string>();
  city = vm["common.city"].as<std::string>();
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

void nativ::datetimenow(string& datenow, string& timenow) {
  std::chrono::duration<int, std::ratio<60 * 60 * 24> > one_day(1);
  std::chrono::duration<int, std::ratio<60> > one_minut(1);
  std::chrono::system_clock::time_point today =
      std::chrono::system_clock::now();  // -
  //      one_minut * 180;  // минус 3 часа ****!!!

  std::chrono::system_clock::time_point tomorrow = today + one_day;  // !!!

  std::time_t tt, tt_tom;
  tt = std::chrono::system_clock::to_time_t(today);
  //  std::cout << "today is: " << ctime(&tt);
  tt_tom = std::chrono::system_clock::to_time_t(tomorrow);
  //  std::cout << "tomorrow will be: " << ctime(&tt_tom);
  // вывод -  today is: Mon Mar 22 22:39:57 2021
  // вывод -  tomorrow will be: Tue Mar 23 22:39:57 2021

  //  time_t now1 = time(0); // это текущее
  time_t now1 = tt;
  struct tm tstruct;
  char date[80];
  char time1[80];
  //  tstruct = *localtime(&now1);
  tstruct = *gmtime(&now1);
  //  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); //
  //  2021-03-22.23:03:44
  strftime(date, sizeof(date), "%d-%m-%Y", &tstruct);
  strftime(time1, sizeof(time1), "%X", &tstruct);
  //  cout << "date-" << date << endl;
  //  cout << "time-" << time1 << endl;
  datenow = date;
  timenow = time1;
}

void nativ::printAll() {
  cout << endl
       << this->name << ":  " << this->bday << ", " << this->btime << endl;
  cout << this->city << ", " << this->lon << ", " << this->lat << endl;
  cout << "As-" << this->as.lon << "\t " << this->as.lon << endl;
  cout << "Su-" << this->su.lon << "\t " << this->su.speed << endl;
  cout << "Ch-" << this->ch.lon << "\t " << this->ch.speed << endl;
  cout << "Ma-" << this->ma.lon << "\t " << this->ma.speed << endl;
  cout << "Bu-" << this->bu.lon << "\t " << this->bu.speed << endl;
  cout << "Gu-" << this->gu.lon << "\t " << this->gu.speed << endl;
  cout << "Sk-" << this->sk.lon << "\t " << this->sk.speed << endl;
  cout << "Sa-" << this->sa.lon << "\t " << this->sa.speed << endl;
  cout << "Ra-" << this->ra.lon << "\t " << this->ra.speed << endl;
  cout << "Ke-" << this->ke.lon << "\t " << this->ke.speed << endl;
  cout << endl;
}
