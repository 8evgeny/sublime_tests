#include "images_model.h"

ImagesModel::ImagesModel(QObject* parent) : QAbstractTableModel(parent) {}

int ImagesModel::rowCount(const QModelIndex& /*parent*/) const {
//Количество строк _data.size()
  return _data.size();
}
//Количество столбцов 4
int ImagesModel::columnCount(const QModelIndex& /*parent*/) const { return 4; }

QVariant ImagesModel::data(const QModelIndex& index, int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  QString display = "";

  const auto row = _data.at(index.row());
  switch (index.column()) {
    case 0:
      display = row.name;
      break;
    case 1:
      display = row.file;
      break;
    case 2:
      display = row.mime;
      break;
    case 3:
      display = row.extra_type;
      break;
  }

  return display;
}

QVariant ImagesModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
    return QVariant();

  QString header = "";
  switch (section) {
    case 0:
      header = "Тип";
      break;
    case 1:
      header = "Файл";
      break;
    case 2:
      header = "MIME";
      break;
    case 3:
      header = "Дополнительный тип";
      break;
  }

  return header;
}

void ImagesModel::ResetImages() {
  beginResetModel();
  _data.clear();
  endResetModel();
}

void ImagesModel::RecievedImages(const QString& name, const QString& file,
                                 const QString& mime,
                                 const QString& extra_type) {
  beginResetModel();
  _data.push_back({name, file, mime, extra_type});
  endResetModel();
}
