#include <algorithm>

#include "collage_creator/collage_creator.h"
#include "commons/exception.h"
#include "commons/logger.h"
#include "imageutils/image.h"

using namespace imageutils;

namespace domain::solver_context {
void CollageCreator::FillMainImageAndPlate(view<const uint8_t> image_buf,
                                           const domain::PlateFrame<int>& plate,
                                           Resolution &resolution) {
  Image image(image_buf, true);
  const commons::Rectangle<int> draw_area{0, 0, image.Width() - 1,
                                          image.Height() - 1};
  auto min_max_x = std::minmax_element(
      plate.cbegin(), plate.cend(),
      [](auto &first, auto &second) -> bool { return first.x < second.x; });

  auto min_max_y = std::minmax_element(
      plate.cbegin(), plate.cend(),
      [](auto &first, auto &second) -> bool { return first.y < second.y; });

  double scale = static_cast<double>(image.Width()) / 1936;

  commons::Rectangle<int> plate_area;
  plate_area.top = min_max_y.first->y;
  plate_area.bottom = min_max_y.second->y;
  plate_area.left = min_max_x.first->x;
  plate_area.right = min_max_x.second->x;
  plate_area.scale(scale, scale);

  commons::Rectangle<int> car_area;
  auto center = plate_area.center();
  car_area.top = center.y - plate_area.Height() * 15;
  car_area.bottom = center.y + plate_area.Height() * 5;
  car_area.left = center.x - plate_area.Width() * 3;
  car_area.right = center.x + plate_area.Width() * 3;

  car_area.Intersect(draw_area);
  plate_area.Intersect(draw_area);

  {
    Image grz = image.GetCrop(plate_area);
    grz.SaveJpeg(resolution.grz_photo);
  }

  scale = 500. / car_area.Width();
  int height = static_cast<int>(car_area.Height() * scale);
  Image main_image(500, height + 100, black);
  {
    Image car = image.GetCrop(car_area);
    car.Resize(500, height);
    main_image.Draw(car);
  }

  std::string raw1 =
      resolution.camera + ", " + resolution.time_check.to_string() + ", ";

  main_image.PutText(raw1.c_str(), 0, height, 18, white);
  plate_area = plate_area - car_area.TopLeft();
  plate_area.scale(scale, scale);

  main_image.DrawRect(plate_area, green);
  std::string s =
      resolution.camera_place.substr(0, resolution.camera_place.find(' ', 80));
  std::string s3 = resolution.camera_place.substr(s.size());
  main_image.PutText(s.c_str(), 0, height + 20, 18, white);
  main_image.PutText(s3.c_str(), 0, height + 40, 18, white);
  if (resolution.speed >= 1) {
    std::string raw2 = +"Максимальная скорость: " +
                       std::to_string(static_cast<int>(resolution.speed)) +
                       " км/ч";
    main_image.PutText(raw2.c_str(), 0, height + 60, 18, white);
  }
  main_image.SaveJpeg(resolution.ts_photo);
}
}  // namespace domain::solver_context
