#include "simpleDB.h"
using namespace std;
const QString DateTimeFormat = "dd.MM.yyyy hh:mm:ss";
const QString DateTimeFormat1 = "hh_mm_ss";
qlonglong time_long_folder_;
qlonglong time_delta_;
string time_start;
string time_end;

int main(int argc, char** argv) {
    const QString settingsFile = "split_big_files.ini";

    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("split");
    QString path_to_folders = settings.value("path_to_folders").toString();
    QString path_to_new_folders =
        settings.value("path_to_new_folders").toString();
    QString time_long_folder = settings.value("time").toString();
    int number_copied_files = settings.value("number_copied_files").toInt();
    time_long_folder_ = date_to_ts(time_long_folder);  //формат ts
    QString time_delta = settings.value("time_delta").toString();
    time_delta_ = date_to_ts(time_delta);  //формат ts
    int max_number_creating_folders =
        settings.value("max_number_creating_folders").toInt();
    QString folder1_name = settings.value("folder1_name").toString();
    QString folder2_name = settings.value("folder2_name").toString();
    QString folder3_name = settings.value("folder3_name").toString();
    QString folder4_name = settings.value("folder4_name").toString();
    QString folderini_name = settings.value("folderini_name").toString();
    settings.endGroup();
    vector<string> v1, v2, v3, v4, v4jpg, vini_ts;
    vector<QString> vini;
    QDir dir1, dir2, dir3, dir4, dirini;
    dir1.setPath(path_to_folders + folder1_name);
    dir2.setPath(path_to_folders + folder2_name);
    dir3.setPath(path_to_folders + folder3_name);
    dir4.setPath(path_to_folders + folder4_name);
    dirini.setPath(path_to_folders + folderini_name);
    QString ini = path_to_folders + folderini_name + "/";
    QStringList listFiles1 = dir1.entryList(QDir::Files);
    QStringList listFiles2 = dir2.entryList(QDir::Files);
    QStringList listFiles3 = dir3.entryList(QDir::Files);
    QStringList listFiles4 = dir4.entryList(QDir::Files);
    QStringList listFilesini = dirini.entryList(QDir::Files);
    fill_vector(listFiles1, v1);
    fill_vector(listFiles2, v2);
    fill_vector(listFiles3, v3);
    fill_vector(listFiles4, v4);
    //Для 4 папки формируем еще вектор v4jpg
    for (auto& file : listFiles4) {
        v4jpg.push_back(file.toStdString());
    }
    //Для ini файлы - формируем вектор vini и vini_ts
    for (auto& file : listFilesini) {
        vini.push_back(file);
        //передаем полный путь
        vini_ts.push_back(parsing_ini_file(ini + file));  //мин ts файла
    }

    cout << " folder 1 - files: " << v1.size() << endl;
    cout << " folder 2 - files: " << v2.size() << endl;
    cout << " folder 3 - files: " << v3.size() << endl;
    cout << " folder 4 - files: " << v4.size() << endl;
    cout << " folder ini - files: " << vini.size() << endl;
    //  минимальное время
    string time_start1 = min(v1[0], v2[0]);
    string time_start2 = min(v3[0], v4[0]);
    time_start = min(time_start1, time_start2);  // t старта

    //  максимальное время
    string time_end1 = max(v1.at(v1.size() - 1), v2.at(v2.size() - 1));
    string time_end2 = max(v3.at(v3.size() - 1), v4.at(v4.size() - 1));
    time_end = max(time_end1, time_end2);  // t end

    cout << "time_start\t " << time_start << " - "
         << ts_to_date(time_start).toStdString() << endl;
    cout << "time_end\t " << time_end << " - "
         << ts_to_date(time_end).toStdString() << endl;

    int number_new_folders;  //количество создаваемых новых директорий
    number_new_folders = (ts_in_string_to_ts_longlomg(time_end) -
                          ts_in_string_to_ts_longlomg(time_start)) /
                         time_long_folder_;

    if (number_new_folders > max_number_creating_folders)
        number_new_folders = max_number_creating_folders;
    cout << "new_folders: " << number_new_folders << endl;
    //создаем папки
    QDir dir;
    for (int i = 0; i < number_new_folders; ++i) {
        //время начала и конца
        int tmp1, tmp2;
        if (i > 0)
            tmp1 = 1;
        else
            tmp1 = 0;
        if (i < 4)
            tmp2 = 1;
        else
            tmp2 = 0;
        qlonglong tstart_folder = ts_in_string_to_ts_longlomg(time_start) +
                                  i * time_long_folder_ - tmp1 * time_delta_ / 2;
        qlonglong tstop_folder = ts_in_string_to_ts_longlomg(time_start) +
                                 (i + 1) * time_long_folder_ +
                                 tmp2 * time_delta_ / 2;

        QString tstart_folder_string = QString::number(tstart_folder);
        QString tstop_folder_string = QString::number(tstop_folder);
        QString time_hh_mm_folder_start =
            ts_to_date1(tstart_folder_string.toStdString());
        QString time_hh_mm_folder_stop =
            ts_to_date1(tstop_folder_string.toStdString());
        //    cout << time_hh_mm_folder_start.toStdString() << endl;
        //    cout << time_hh_mm_folder_stop.toStdString() << endl;

        QString number_folder = QString::number(i + 1);
        QString newDir = path_to_new_folders + "folder " + number_folder + "   " +
                         time_hh_mm_folder_start + " -- " + time_hh_mm_folder_stop +
                         "/";
        dir.mkdir(path_to_new_folders);
        dir.mkdir(newDir);
        dir.setPath(newDir);
        dir.mkdir(newDir + folder1_name + "/");
        dir.mkdir(newDir + folder2_name + "/");
        dir.mkdir(newDir + folder3_name + "/");
        dir.mkdir(newDir + folder4_name + "/");
        dir.mkdir(newDir + folderini_name + "/");

        //разбираем вектор v1
        int num = 0;
        for (auto it = v1.begin(); it != v1.end(); ++it) {
            if (ts_in_string_to_ts_longlomg(*it) >= tstart_folder) {
                if (ts_in_string_to_ts_longlomg(*it) <= tstop_folder) {
                    //копируем картинку из папки folder1_name в текущую папку
                    QString name_file = str_to_qstr(*it) + ".jpg";
                    QFile file;
                    QString from = path_to_folders + folder1_name + "/" + name_file;
                    QString to = newDir + folder1_name + "/" + name_file;
                    if (num < number_copied_files) {
                        file.QFile::copy(from, to);
                        ++num;
                    }
                }
            }
        }
        //разбираем вектор v2
        num = 0;
        for (auto it = v2.begin(); it != v2.end(); ++it) {
            if (ts_in_string_to_ts_longlomg(*it) >= tstart_folder) {
                if (ts_in_string_to_ts_longlomg(*it) <= tstop_folder) {
                    //копируем картинку из папки folder2_name в текущую папку
                    QString name_file = str_to_qstr(*it) + ".jpg";
                    QFile file;
                    QString from = path_to_folders + folder2_name + "/" + name_file;
                    QString to = newDir + folder2_name + "/" + name_file;
                    if (num < number_copied_files) {
                        file.QFile::copy(from, to);
                        ++num;
                    }
                }
            }
        }
        //разбираем вектор v3
        num = 0;
        for (auto it = v3.begin(); it != v3.end(); ++it) {
            if (ts_in_string_to_ts_longlomg(*it) >= tstart_folder) {
                if (ts_in_string_to_ts_longlomg(*it) <= tstop_folder) {
                    //копируем картинку из папки folder3_name в текущую папку
                    QString name_file = str_to_qstr(*it) + ".jpg";
                    QFile file;
                    QString from = path_to_folders + folder3_name + "/" + name_file;
                    QString to = newDir + folder3_name + "/" + name_file;
                    if (num < number_copied_files) {
                        file.QFile::copy(from, to);
                        ++num;
                    }
                }
            }
        }
        //разбираем вектор v4
        num = 0;
        auto it1 = v4jpg.begin();
        for (auto it = v4.begin(); it != v4.end();) {
            if (ts_in_string_to_ts_longlomg(*it) >= tstart_folder) {
                if (ts_in_string_to_ts_longlomg(*it) <= tstop_folder) {
                    //копируем картинку из папки folder4_name в текущую папку
                    QString name_file = str_to_qstr(*it1);
                    QFile file;
                    QString from = path_to_folders + folder4_name + "/" + name_file;
                    QString to = newDir + folder4_name + "/" + name_file;
                    if (num < number_copied_files) {
                        file.QFile::copy(from, to);
                        ++num;
                    }
                }
            }
            ++it;
            ++it1;
        }
        //Разбираем вектор vini
        auto itini = vini.begin();
        for (auto it = vini_ts.begin(); it != vini_ts.end();) {
            if (ts_in_string_to_ts_longlomg(*it) >= tstart_folder) {
                if (ts_in_string_to_ts_longlomg(*it) <= tstop_folder) {
                    //копируем картинку из папки folderini в текущую папку
                    QString name_file = *itini;
                    //          cout << (*itini).toStdString() << endl;
                    QFile file;
                    QString from = path_to_folders + folderini_name + "/" + name_file;
                    QString to = newDir + folderini_name + "/" + name_file;
                    file.QFile::copy(from, to);
                }
            }
            ++itini;
            ++it;
        }
    }

    return 0;
}

string parsing_ini_file(QString ini_file) {
    QSettings settings(ini_file, QSettings::IniFormat);
    settings.beginGroup("Snapshot");
    QStringList images = settings.value("images").toStringList();
    //  string tmp = images.begin()->toStdString();
    string tmp = images[0].left(13).toStdString();
    settings.endGroup();
    return tmp;
}

QString str_to_qstr(string str) {
    QString temp;
    for (int i = 0; i < str.size(); ++i) {
        temp.append(str.at(i));
    }
    return temp;
}

void fill_vector(QStringList& listFiles, vector<string>& v) {
    for (auto& file : listFiles) {
        v.push_back(file.toStdString().substr(0, 13));
    }
}

QString ts_to_date(string time) {
    QString time1 = str_to_qstr(time);
    qint64 time_64 = static_cast<qint64>(time1.toLongLong());
    QDateTime date;
    date = QDateTime::fromMSecsSinceEpoch(time_64);
    return date.toString(DateTimeFormat);
}

QString ts_to_date1(string time) {
    QString time1 = str_to_qstr(time);
    qint64 time_64 = static_cast<qint64>(time1.toLongLong());
    QDateTime date;
    date = QDateTime::fromMSecsSinceEpoch(time_64);
    return date.toString(DateTimeFormat1);
}

qlonglong date_to_ts(QString time) {
    qlonglong tmp = time.toLongLong();
    return tmp * 60 * 1000;
}

qlonglong ts_in_string_to_ts_longlomg(string time) {
    return str_to_qstr(time).toLongLong();
}
