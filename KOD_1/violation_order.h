#ifndef VIOLATION_ORDER_H
#define VIOLATION_ORDER_H

#include <string>
#include <vector>

namespace sadko {

    class ViolationOrder {
      friend bool operator==(const ViolationOrder& lhs, const ViolationOrder& rhs);
      friend bool operator!=(const ViolationOrder& lhs, const ViolationOrder& rhs);

     public:
      enum class Direction : int {
        No = -1,
        From,
        To,
      };

      void SetSpeed(int speed);
      void SetSpeedLimit(int speed_limit);
      void SetDirection(Direction directionStr);
      void SetRecognitionAccuracy(double recognition_accuracy);

      void SetLatitude(double latitudeStr);
      void SetLongitude(double longitudeStr);

      void SetTimestamp(time_t timestamp);

      void SetGuid(const std::string& guid);

      void SetCamera(const std::string& camera);
      void SetCameraPlace(const std::string& camera_place);
      void SetLaneNumber(int lane_number);
      void SetViolationCode(int violation_code);
      void SetRegistrationNumber(const std::string& reg_number);
      void SetCountry(const std::string& country);

      const std::string& guid() const;
      const std::string& camera() const;
      const std::string& cameraPlace() const;

      int laneNumber() const;
      int violationCode() const;

      const std::string& registrationNumber() const;
      const std::string& country() const;

      const time_t& timestamp() const;

      std::string latitudeStr() const;
      double latitude() const;
      std::string longitudeStr() const;
      double longitude() const;

      double recognitionAccuracy() const;
      std::string recognitionAccuracyStr() const;  // between 0.0 and 100.0

      int speed() const;
      std::string speedStr() const;

      int speedLimit() const;
      std::string speedLimitStr() const;

      Direction directin() const;
      std::string directionStr() const;  // 0 - from, 1 - to

      struct Content {
        std::vector<uint8_t> data;
        std::string mime = "image/jpeg";
      };

      void SetMainPhoto(const Content& main_photo);
      const Content& mainPhoto() const;

      void SetPlatePhoto(const Content& plate_photo);
      const Content& platePhoto() const;

      struct AdditionalData {
        Content content;
        std::string type;
        time_t timestmap;
      };

      void AddAdditionalData(const AdditionalData& additional_data);
      const std::vector<AdditionalData>& additionalData() const;

      void ClearAdditionData();

     private:
      int _speed = 0;
      int _speed_limit = 0;
      double _recognition_accuracy = 0.0;
      Direction _direction = Direction::No;

      double _latitude;
      double _longitude;

      std::string _guid;
      std::string _camera;
      std::string _camera_place;
      std::string _reg_number;
      std::string _country;

      int _lane_number = 0;
      int _violation_code = 0;

      time_t _timestamp = 0;

      Content _main_photo;
      Content _plate_photo;

      std::vector<AdditionalData> _additional_data;
    };

// Перегрузка операторов для объектов класса, даты объекта и контента
    bool operator==(const ViolationOrder& lhs, const ViolationOrder& rhs);
    bool operator!=(const ViolationOrder& lhs, const ViolationOrder& rhs);

    bool operator==(const ViolationOrder::AdditionalData& lhs,
                    const ViolationOrder::AdditionalData& rhs);
    bool operator!=(const ViolationOrder::AdditionalData& lhs,
                    const ViolationOrder::AdditionalData& rhs);

    bool operator==(const ViolationOrder::Content& lhs,
                    const ViolationOrder::Content& rhs);
    bool operator!=(const ViolationOrder::Content& lhs,
                    const ViolationOrder::Content& rhs);

}  // namespace sadko
#endif  // VIOLATION_ORDER_H
