#ifndef IMAGES_MODEL_H
#define IMAGES_MODEL_H

#include <QAbstractTableModel>

class ImagesModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit ImagesModel(QObject* parent = nullptr);

  // QAbstractItemModel interface
 public:
  int rowCount(const QModelIndex& parent) const override;
  int columnCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
 public slots:
  void ResetImages();
  void RecievedImages(const QString& name, const QString& file,
                      const QString& mime, const QString& extra_type);

 private:
  struct Column {
    QString name;
    QString file;
    QString mime;
    QString extra_type;
  };

  QVector<Column> _data;
};

#endif  // IMAGES_MODEL_H
