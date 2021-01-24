#pragma once
#include <QApplication>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLineEdit>
#include <QMessageBox>
#include <QMimeDatabase>
#include <QMimeType>
#include <QPushButton>
#include <QRegularExpression>
#include <QSettings>
#include <QSpinBox>
#include <QStringList>
#include <QTextEdit>
#include <QUuid>
#include <QValidator>
#include <QWidget>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
//#include <map>
//#include <algorithm>
//#include <execution>
#include "person.h"
const QString settingsFile = "configDB.ini";
void fill_vector(QStringList &, std::vector<std::string> &);
void print_vector(std::vector<std::string>&);
void print_vector(std::vector<std::pair<unsigned,std::string>>&);
void read_data();
void input_data();
void edit_data();
void print_nation();
void print_nation(std::vector<std::pair<unsigned,std::string>>&);
void input_death(Person &);
void save_person(Person &);
