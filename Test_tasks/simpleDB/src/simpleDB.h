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

