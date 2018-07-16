#include <sensor_msgs/msg/image.hpp>

#include <memory>

namespace image_transport {
  using Image = sensor_msgs::msg::Image;
  using ImageConstPtr = std::shared_ptr<Image>;
  using VoidPtr = std::shared_ptr<void>;
}
