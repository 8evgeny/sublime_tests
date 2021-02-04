#ifndef IMAGES_TABLE_H
#define IMAGES_TABLE_H

#include <QTableView>

class ImagesTable : public QTableView {
  Q_OBJECT
 public:
  explicit ImagesTable(QWidget* parent = nullptr);

 public slots:
  void ResetImages();
  void RecievedImages(const QString& name, const QString& file,
                      const QString& mime, const QString& extra_type);
};

#endif  // IMAGES_TABLE_H
