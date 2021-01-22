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

void fill_vector(QStringList &, std::vector<std::string> &);
void print_vector(std::vector<std::string>&);
void readDB();
void input_new_data();



