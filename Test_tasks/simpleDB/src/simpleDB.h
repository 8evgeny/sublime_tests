#pragma once
#include <QString>
#include <QDate>
#include <QDir>
#include <QSettings>
#include <iostream>
#include <regex>
#include <fstream>

#include <windows.h>
#include "person.h"
const QString settingsFile = "configDB.ini";
void fill_vector(QStringList &, std::vector<std::string> &);
void print_vector(std::vector<std::string>&);
void print_vector(std::vector<std::pair<unsigned,std::string>>&);
unsigned read_data();
void input_data();
void edit_data();
void view_data();
std::string name_from_munber(int num);
void print_nation();
void print_nation(std::vector<std::pair<unsigned,std::string>> &);
void delete_file(QString &);
QDate string_toqtate(std::string);
QString read_patch_DB();
void remove_data();
