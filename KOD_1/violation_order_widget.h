#ifndef VIOLATION_ORDER_WIDGET_H
#define VIOLATION_ORDER_WIDGET_H

// Qt
#include <QWidget>

// library
#include "duplo_dispatcher.h"
#include "violation_order.h"

using ViolationOrder = sadko::ViolationOrder;
using Dispatcher = sadko::DuploDispatcher;

class ViolationOrderWidget : public QWidget {
  Q_OBJECT
 public:
  struct Images {
    QString main_photo;
    QString grz_photo;
    QStringList additional_data;
  };

  explicit ViolationOrderWidget(QWidget* parent = nullptr);

  void Init();

  void SetDispatcher(Dispatcher* dispatcher);

 signals:
  void ChangedPath(const QString& path);
  void ChangedGuid(const QString& guid);
  void ChangedTimestamp(const QDateTime& datetime);
  void ChangedRegNumber(const QString& reg_number);

  void ResetImages();
  void SendImages(const QString& name, const QString& file, const QString& mime,
                  const QString& extra_type);

 public slots:
  void Send();
  void SelectFilePath();
  void DirSelected(const QString& path);

 private:
  ViolationOrder _violation_order;
  Images _images;

  QString _path_to_files;

  Dispatcher* _dispatcher;

  void SaveInDataBase(const QString& duplo_status, ViolationOrder& viol_order,
                      const Images& images);
};

#endif  // VIOLATION_ORDER_WIDGET_H
