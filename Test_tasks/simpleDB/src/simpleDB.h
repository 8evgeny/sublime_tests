#pragma once
#include <QApplication>
#include <QComboBox>
#include <QDateTimeEdit>
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

using namespace std;

void fill_vector(QStringList &, vector<string> &);
void copy_files(vector<QString> &, QString);
QString ts_to_date(string);
QString ts_to_date1(string);
qlonglong date_to_ts(QString);
QString str_to_qstr(string);
QString str_to_qstr1(string);
qlonglong ts_in_string_to_ts_longlomg(string);
string parsing_ini_file(QString);  //возвращает мин ts
