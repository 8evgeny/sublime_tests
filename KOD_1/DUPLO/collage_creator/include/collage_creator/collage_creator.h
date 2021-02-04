#pragma once

#include <vector>

#include "commons/graphic_primitives.h"
#include "commons/view.h"
#include "domain/resolution.h"

namespace domain::solver_context {
/**
 * Class used in old solver.
 */
class CollageCreator {
 public:
  /**
   * Fills main_photo and plate_photo fields of the event.
   * @param image The source image to collage.
   * @param plate The coordinates of the plate corners.
   * @param resolution[in, out] The resolution to process.
   */
  void FillMainImageAndPlate(view<const uint8_t> image,
                             const domain::PlateFrame<int>& plate,
                             Resolution &resolution);
};
}  // namespace domain::solver_context
