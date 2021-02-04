#include "violation_order_widget.h"

// Qt
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
#include <QSpinBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QUuid>
#include <QValidator>

#include <QSettings>

// library
#include "duplo_dispatcher_exception.h"

// third party
#include <easy/profiler.h>

const QString kSettingsFile = "duplo_sending.ini";
const int kMinWidthMainlayout = 700;  // px
const QString kDateTimeFormat = "dd.MM.yyyy HH:mm:ss";

const QString kRegularRegistrationNumber = R"(^([\dа-яА-Я]+)(\w{2,3})$)";
const QString kRegularFilesFormatValid = R"((\d+)\.*(\w+)\.*(\w*)\.+(\w+)$)";

ViolationOrderWidget::ViolationOrderWidget(QWidget* parent) : QWidget(parent) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

  QSettings settings(kSettingsFile, QSettings::IniFormat);

  auto param = [&settings](const QString& key, const QVariant& default_value) {
    if (!settings.contains(key)) {
      settings.setValue(key, default_value);
    }
    return settings.value(key);
  };

  auto paramStr = [param](const QString& key, const QString& default_value) {
    return param(key, default_value).toString();
  };

  settings.beginGroup("database");
  {
    db.setHostName(paramStr("host", "localhost"));
    db.setDatabaseName(paramStr("database", "data_for_duplo_dispatcher"));
    db.setUserName(paramStr("user", "postgres"));
    db.setPassword(paramStr("password", ""));
  }
  settings.endGroup();

  db.open();

  if (db.isOpenError()) {
    qFatal("Can't opend database");
  }

  // Fake data
  auto uuid = QUuid::createUuid();
  _violation_order.SetGuid(uuid.toString(QUuid::WithoutBraces).toStdString());

  settings.beginGroup("violation-order-default");

  _violation_order.SetCamera(paramStr("camera", "SD7700216").toStdString());
  _violation_order.SetCameraPlace(
      paramStr("camera-place", "Шоссе Энтузиастов д 46/2, Москва, Россия")
          .toStdString());
  _violation_order.SetCountry(paramStr("country", "RUS").toStdString());
  _violation_order.SetTimestamp(QDateTime::currentSecsSinceEpoch());
  _violation_order.SetDirection(
      ViolationOrder::Direction(param("direction", 1).toInt()));
  _violation_order.SetLaneNumber(param("lane", 1).toInt());
  _violation_order.SetSpeed(param("speed", 0).toInt());
  _violation_order.SetSpeedLimit(param("speed-limit", 60).toInt());
  _violation_order.SetViolationCode(param("violation-code", 60).toInt());
  _violation_order.SetRecognitionAccuracy(
      param("recognition", 99.9).toDouble());
  _violation_order.SetLatitude(param("latitude", 55.759285).toDouble());
  _violation_order.SetLongitude(param("longitude", 37.756140).toDouble());

  settings.endGroup();
}

void ViolationOrderWidget::Init() {
  auto main_layout = new QVBoxLayout;
  setMinimumWidth(kMinWidthMainlayout);
  setLayout(main_layout);

  // chose file
  {
    auto select_path = new QPushButton("Выбрать путь к изображениям");
    connect(select_path, &QPushButton::clicked, this,
            &ViolationOrderWidget::SelectFilePath);
    auto edit = new QLineEdit;
    edit->setText(_path_to_files);

    connect(edit, &QLineEdit::textChanged,
            [this](const QString& path_to_files) {
              _path_to_files = path_to_files;
            });

    connect(this, &ViolationOrderWidget::ChangedPath,
            [edit, this](const QString& path) {
              edit->setText(path);
              DirSelected(path);
            });

    auto horizontal = new QHBoxLayout;
    horizontal->addWidget(select_path);
    horizontal->addWidget(edit, 2);

    main_layout->addLayout(horizontal);
  }

  auto param_layout = new QFormLayout;

  main_layout->addLayout(param_layout);

  {  // guid
    auto edit = new QLineEdit;
    edit->setText(QString::fromStdString(_violation_order.guid()));

    connect(this, &ViolationOrderWidget::ChangedGuid,
            [edit](const QString& guid) { edit->setText(guid); });

    connect(edit, &QLineEdit::textChanged, [this](const QString& text) {
      _violation_order.SetGuid(text.toStdString());
    });

    param_layout->addRow("GUID", edit);
  }

  {  // registration number
    auto edit = new QLineEdit;
    auto validator =
        new QRegExpValidator(QRegExp(kRegularRegistrationNumber), edit);
    edit->setValidator(validator);

    edit->setText(
        QString::fromStdString(_violation_order.registrationNumber()));

    connect(this, &ViolationOrderWidget::ChangedRegNumber,
            [edit](const QString& reg_number) { edit->setText(reg_number); });

    connect(edit, &QLineEdit::textChanged, [this](const QString& text) {
      _violation_order.SetRegistrationNumber(text.toStdString());
    });

    param_layout->addRow("Гос. номер", edit);
  }

  {  // country
    auto edit = new QLineEdit;
    edit->setText(QString::fromStdString(_violation_order.country()));

    connect(edit, &QLineEdit::textChanged, [this](const QString& text) {
      _violation_order.SetCountry(text.toStdString());
    });

    param_layout->addRow("Страна номерного знака", edit);
  }

  {
    auto SetDate = [this](QDateTimeEdit* edit) {
      auto date = QDateTime::fromSecsSinceEpoch(_violation_order.timestamp());
      edit->setDateTime(date);
    };

    auto edit = new QDateTimeEdit;
    edit->setDisplayFormat(kDateTimeFormat);
    SetDate(edit);

    connect(this, &ViolationOrderWidget::ChangedTimestamp,
            [edit](const QDateTime& datetime) { edit->setDateTime(datetime); });

    connect(edit, &QDateTimeEdit::dateTimeChanged,
            [this](const QDateTime& datetime) {
              _violation_order.SetTimestamp(datetime.toSecsSinceEpoch());
            });

    param_layout->addRow("Время нарушения", edit);
  }

  {  // violation code
    auto spin_box = new QSpinBox;
    spin_box->setRange(0, 99999);
    spin_box->setSingleStep(1);
    spin_box->setValue(_violation_order.violationCode());

    connect(spin_box, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int value) { _violation_order.SetViolationCode(value); });

    param_layout->addRow("Номер нарушения", spin_box);
  }

  {  // speed
    auto spin_box = new QSpinBox;
    spin_box->setRange(0, 320);
    spin_box->setSingleStep(1);
    spin_box->setValue(_violation_order.speed());

    connect(spin_box, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int value) { _violation_order.SetSpeed(value); });

    param_layout->addRow("Скорость", spin_box);
  }

  {  // speed limit
    auto spin_box = new QSpinBox;
    spin_box->setRange(0, 320);
    spin_box->setSingleStep(1);
    spin_box->setValue(_violation_order.speedLimit());

    connect(spin_box, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int value) { _violation_order.SetSpeedLimit(value); });

    param_layout->addRow("Лимит скорости", spin_box);
  }

  {  // lane
    auto spin_box = new QSpinBox;
    spin_box->setRange(0, 320);
    spin_box->setSingleStep(1);
    spin_box->setValue(_violation_order.laneNumber());

    connect(spin_box, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int value) { _violation_order.SetLaneNumber(value); });

    param_layout->addRow("Номер полосы", spin_box);
  }

  {  // recognition accuracy
    auto spin_box = new QDoubleSpinBox;
    spin_box->setDecimals(1);
    spin_box->setRange(0, 100);
    spin_box->setSingleStep(1);
    spin_box->setValue(_violation_order.recognitionAccuracy());

    connect(spin_box, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double value) {
              _violation_order.SetRecognitionAccuracy(value);
            });

    param_layout->addRow("Процент распознования", spin_box);
  }

  {  // camera
    auto edit = new QLineEdit;
    edit->setText(QString::fromStdString(_violation_order.camera()));

    connect(edit, &QLineEdit::textChanged, [this](const QString& text) {
      _violation_order.SetCamera(text.toStdString());
    });

    param_layout->addRow("Камера", edit);
  }

  {  // camera place
    auto edit = new QLineEdit;
    edit->setText(QString::fromStdString(_violation_order.cameraPlace()));

    connect(edit, &QLineEdit::textChanged, [this](const QString& text) {
      _violation_order.SetCameraPlace(text.toStdString());
    });

    param_layout->addRow("Расположение камеры", edit);
  }

  {
    auto combo = new QComboBox;
    combo->addItem("От камеры");
    combo->addItem("на камеру");
    combo->setCurrentIndex(static_cast<int>(_violation_order.directin()));

    connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index) {
              _violation_order.SetDirection(ViolationOrder::Direction(index));
            });

    param_layout->addRow("Направление движения", combo);
  }

  {  // latitude
    auto spin_box = new QDoubleSpinBox;
    spin_box->setDecimals(5);
    spin_box->setRange(-90, 90);
    spin_box->setSingleStep(0.1);
    spin_box->setValue(_violation_order.latitude());

    connect(spin_box, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double value) { _violation_order.SetLatitude(value); });

    param_layout->addRow("Широта", spin_box);
  }

  {  // longitude
    auto spin_box = new QDoubleSpinBox;
    spin_box->setDecimals(5);
    spin_box->setRange(-180, 180);
    spin_box->setSingleStep(0.1);
    spin_box->setValue(_violation_order.longitude());

    connect(spin_box, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double value) { _violation_order.SetLongitude(value); });

    param_layout->addRow("Долгота", spin_box);
  }

  auto send_button = new QPushButton("Отправить");
  connect(send_button, &QPushButton::clicked, this,
          &ViolationOrderWidget::Send);

  main_layout->addWidget(send_button);
}

void ViolationOrderWidget::SetDispatcher(Dispatcher* dispatcher) {
  _dispatcher = dispatcher;
}

void ViolationOrderWidget::Send() {
  Q_ASSERT(_dispatcher != nullptr);

  if (_violation_order.registrationNumber().empty()) {
    QMessageBox::critical(
        this, "Неполные данные",
        "Отсутствует регистрационный номер ТС. Отправка невозможна.");
    return;
  }

  auto buttons = QMessageBox::question(this, "Отправка данных", "Вы уверенны?");

  if (buttons != QMessageBox::Yes) return;

  qDebug() << "Message sending";

  QString status_code = "0";
  try {
    _dispatcher->SendMessage(_violation_order);

    // todo: implement a normal error handler
  } catch (SOAPDuploFault& e) {
    status_code = QString::number(e.get_err_code());
    qWarning() << "Duplo(fault_code): "
               << QString::fromStdString(e.get_fault_code());
  } catch (SOAPConnectionException& e) {
    status_code = QString::number(e.get_err_code());
    qWarning() << "Duplo(connection_error): "
               << QString::number(e.get_err_code());

  } catch (DuploDispatcherException& e) {
    status_code = QString::number(e.get_err_code());

    qWarning() << "Duplo(status_code): " << e.get_err_code();
  }

  SaveInDataBase(status_code, _violation_order, _images);
}

void ViolationOrderWidget::SelectFilePath() {
  auto path_dialog = new QFileDialog;
  path_dialog->setFileMode(QFileDialog::Directory);

  connect(path_dialog, &QDialog::accepted, [this, path_dialog]() {
    emit ChangedPath(path_dialog->directory().path());
  });

  path_dialog->open();
}

void ViolationOrderWidget::DirSelected(const QString& path) {
  EASY_FUNCTION(profiler::colors::Red)

  emit ResetImages();
  emit ChangedRegNumber("");
  emit ChangedTimestamp(QDateTime());

  _violation_order.SetMainPhoto({});
  _violation_order.SetPlatePhoto({});
  _violation_order.ClearAdditionData();

  QDir dir(path);
  dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

  const auto dir_name = dir.dirName();

  {
    QRegularExpression re(kRegularRegistrationNumber);
    auto match = re.match(dir_name);
    if (!match.hasMatch()) return;

    const auto reg_no = match.captured(1);
    const auto country = match.captured(2);

    emit ChangedRegNumber(reg_no + country);
  }

  auto lists = dir.entryList();

  for (const auto& file_name : lists) {
    QRegularExpression re(kRegularFilesFormatValid);
    re.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);

    auto match = re.match(file_name);
    if (!match.hasMatch()) continue;

    auto timestamp = match.captured(1);
    auto type = match.captured(2);
    auto extra = match.captured(3);
    auto exten = match.captured(4);

    const auto path_to_file = path + "/" + file_name;

    QFile file(path_to_file);
    if (!file.open(QIODevice::ReadOnly)) continue;

    const auto binary = file.readAll();

    QMimeDatabase mimeDatabase;
    QMimeType mimeType;

    mimeType = mimeDatabase.mimeTypeForFile(QFileInfo(file));

    std::string mime_type = "";
    if (mimeType.inherits("image/jpeg")) {
      mime_type = "image/jpeg";
    } else if (mimeType.inherits("video/mp4")) {
      mime_type = "video/mp4";
    }

    emit ChangedTimestamp(QDateTime::fromMSecsSinceEpoch(timestamp.toLong()));
    emit ChangedGuid(QUuid::createUuid().toString(QUuid::WithoutBraces));

    std::vector<uint8_t> data;
    data = {binary.begin(), binary.end()};

    QString extr_type = "";
    QString name = "";

    if (!type.compare("car", Qt::CaseInsensitive)) {
      _images.main_photo = file_name;

      _violation_order.SetMainPhoto({std::move(data), mime_type});

      name = "Основное";
    } else if (!type.compare("plate", Qt::CaseInsensitive)) {
      _images.grz_photo = file_name;
      _violation_order.SetPlatePhoto({std::move(data), mime_type});
      name = "Номер";
    } else {
      _images.additional_data.append(file_name);

      ViolationOrder::Content content{std::move(data), mime_type};
      ViolationOrder::AdditionalData additional_data;
      additional_data.content = std::move(content);
      additional_data.timestmap = timestamp.toLong() / 1000;

      auto additional_type = [&type, &extra]() -> std::string {
        if (!type.compare("collage", Qt::CaseInsensitive)) {
          return "a";
        } else if (!extra.compare("video", Qt::CaseInsensitive) ||
                   !type.compare("video", Qt::CaseInsensitive)) {
          return "3";
        } else {
          return "1";
        }
      };

      additional_data.type = additional_type();

      name = "Дополнительное";
      extr_type = QString::fromStdString(additional_data.type);

      _violation_order.AddAdditionalData(additional_data);
    }

    emit SendImages(name, file_name, QString::fromStdString(mime_type),
                    extr_type);
  }
}

void ViolationOrderWidget::SaveInDataBase(
    const QString& duplo_status, ViolationOrder& viol_order,
    const ViolationOrderWidget::Images& images) {
  EASY_FUNCTION(profiler::colors::Green)

  QSqlQuery query;

  const QString sql =
      "insert into violation_order "
      "values(:guid,:camera,:camera_place,:line_number,:violation_code,:"
      "registration_number,:country,:timestamp,:latitude,:longitude,"
      ":recognition_accuracy,:speed,:speed_limit,:direction,:photo_ts,:photo_"
      "grz,:additional_data,:duplo_status)";

  query.prepare(sql);

  query.bindValue(":guid", QString::fromStdString(viol_order.guid()));
  query.bindValue(":camera", QString::fromStdString(viol_order.camera()));
  query.bindValue(":camera_place",
                  QString::fromStdString(viol_order.cameraPlace()));
  query.bindValue(":line_number", viol_order.laneNumber());
  query.bindValue(":violation_code", viol_order.violationCode());
  query.bindValue(":registration_number",
                  QString::fromStdString(viol_order.registrationNumber()));
  query.bindValue(":country", QString::fromStdString(viol_order.country()));
  query.bindValue(":timestamp", static_cast<qint64>(viol_order.timestamp()));
  query.bindValue(":latitude", viol_order.latitude());
  query.bindValue(":longitude", viol_order.longitude());
  query.bindValue(":recognition_accuracy", viol_order.recognitionAccuracy());
  query.bindValue(":speed", viol_order.speed());
  query.bindValue(":speed_limit", viol_order.speedLimit());
  query.bindValue(":direction", static_cast<int>(viol_order.directin()));

  const auto main_photo =
      images.main_photo.isEmpty() ? "images.main_photo" : images.main_photo;
  query.bindValue(":photo_ts", main_photo);

  const auto plate_photo =
      images.grz_photo.isEmpty() ? "images.grz_photo" : images.grz_photo;
  query.bindValue(":photo_grz", plate_photo);

  auto additional = images.additional_data;
  additional.replaceInStrings(QRegExp("^"), "\"");
  additional.replaceInStrings(QRegExp("$"), "\"");

  const auto additional_str = QString("{%1}").arg(additional.join(","));
  query.bindValue(":additional_data", additional_str);

  query.bindValue(":duplo_status", duplo_status);

  if (!query.exec())
    qFatal("%s", query.lastError().databaseText().toUtf8().data());
  else
    qInfo() << "Violation order added with duplo code:" << duplo_status;
}
