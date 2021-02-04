#include "violation_order.h"

// std libs
#include <algorithm>
#include <cmath>
#include <sstream>

namespace {

bool DoubleIsEqual(double a, double b) {
  return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

}  // namespace

namespace sadko {

bool operator==(const ViolationOrder& lhs, const ViolationOrder& rhs) {
  return lhs._guid == rhs._guid && lhs._camera == rhs._camera &&
         lhs._camera_place == rhs._camera_place &&
         lhs._direction == rhs._direction &&
         DoubleIsEqual(lhs._latitude, rhs._latitude) &&
         DoubleIsEqual(lhs._longitude, rhs._longitude) &&
         lhs._lane_number == rhs._lane_number &&
         lhs._violation_code == rhs._violation_code &&
         DoubleIsEqual(lhs.recognitionAccuracy(), rhs.recognitionAccuracy()) &&
         lhs._reg_number == rhs._reg_number && lhs._country == rhs._country &&
         lhs._speed == rhs._speed && lhs._speed_limit == rhs._speed_limit &&
         lhs._timestamp == rhs._timestamp;
}

bool operator!=(const ViolationOrder& lhs, const ViolationOrder& rhs) {
  return !(lhs == rhs);
}

void ViolationOrder::SetSpeed(int speed) { _speed = speed; }
void ViolationOrder::SetSpeedLimit(int speed_limit) {
  _speed_limit = speed_limit;
}
void ViolationOrder::SetDirection(Direction direction) {
  _direction = direction;
}
void ViolationOrder::SetRecognitionAccuracy(double recognition_accuracy) {
  _recognition_accuracy = recognition_accuracy;
}
void ViolationOrder::SetLatitude(double latitude) { _latitude = latitude; }
void ViolationOrder::SetLongitude(double longitude) { _longitude = longitude; }
void ViolationOrder::SetTimestamp(time_t timestamp) { _timestamp = timestamp; }
void ViolationOrder::SetGuid(const std::string& guid) { _guid = guid; }
void ViolationOrder::SetCamera(const std::string& camera) { _camera = camera; }
void ViolationOrder::SetCameraPlace(const std::string& camera_place) {
  _camera_place = camera_place;
}
void ViolationOrder::SetLaneNumber(int lane_number) {
  _lane_number = lane_number;
}
void ViolationOrder::SetViolationCode(int violation_code) {
  _violation_code = violation_code;
}
void ViolationOrder::SetRegistrationNumber(const std::string& reg_number) {
  _reg_number = reg_number;
}
void ViolationOrder::SetCountry(const std::string& country) {
  _country = country;
}

const std::string& ViolationOrder::guid() const { return _guid; }
const std::string& ViolationOrder::camera() const { return _camera; }
const std::string& ViolationOrder::cameraPlace() const { return _camera_place; }
int ViolationOrder::laneNumber() const { return _lane_number; }
int ViolationOrder::violationCode() const { return _violation_code; }
const std::string& ViolationOrder::registrationNumber() const {
  return _reg_number;
}
const std::string& ViolationOrder::country() const { return _country; }

const time_t& ViolationOrder::timestamp() const { return _timestamp; }

std::string ViolationOrder::latitudeStr() const {
  return std::to_string(_latitude);
}

double ViolationOrder::latitude() const { return _latitude; }
std::string ViolationOrder::longitudeStr() const {
  return std::to_string(_longitude);
}

double ViolationOrder::longitude() const { return _longitude; }

double ViolationOrder::recognitionAccuracy() const {
  return std::clamp(_recognition_accuracy, 0.0, 100.0);
}

std::string ViolationOrder::recognitionAccuracyStr() const {
  std::ostringstream stream;
  stream.precision(1);
  stream.setf(std::ios::fixed, std::ios::floatfield);
  stream << recognitionAccuracy();

  return stream.str();
}

int ViolationOrder::speed() const { return _speed; }

std::string ViolationOrder::speedStr() const { return std::to_string(_speed); }
int ViolationOrder::speedLimit() const { return _speed_limit; }

std::string ViolationOrder::speedLimitStr() const {
  return std::to_string(_speed_limit);
}

ViolationOrder::Direction ViolationOrder::directin() const {
  return _direction;
}
std::string ViolationOrder::directionStr() const {
  return std::to_string(static_cast<int>(_direction));
}

void ViolationOrder::SetMainPhoto(const ViolationOrder::Content& main_photo) {
  _main_photo = main_photo;
}

const ViolationOrder::Content& ViolationOrder::mainPhoto() const {
  return _main_photo;
}

void ViolationOrder::SetPlatePhoto(const ViolationOrder::Content& plate_photo) {
  _plate_photo = plate_photo;
}

const ViolationOrder::Content& ViolationOrder::platePhoto() const {
  return _plate_photo;
}

void ViolationOrder::AddAdditionalData(
    const ViolationOrder::AdditionalData& additional_data) {
  _additional_data.emplace_back(additional_data);
}

const std::vector<ViolationOrder::AdditionalData>&
ViolationOrder::additionalData() const {
  return _additional_data;
}

void ViolationOrder::ClearAdditionData() { _additional_data.clear(); }

bool operator==(const ViolationOrder::AdditionalData& lhs,
                const ViolationOrder::AdditionalData& rhs) {
  return lhs.type == rhs.type && lhs.timestmap == rhs.timestmap &&
         lhs.content == rhs.content;
}

bool operator!=(const ViolationOrder::AdditionalData& lhs,
                const ViolationOrder::AdditionalData& rhs) {
  return !(lhs == rhs);
}

bool operator==(const ViolationOrder::Content& lhs,
                const ViolationOrder::Content& rhs) {
  return lhs.data == rhs.data && lhs.mime == rhs.mime;
}

bool operator!=(const ViolationOrder::Content& lhs,
                const ViolationOrder::Content& rhs) {
  return !(lhs == rhs);
}

}  // namespace sadko
