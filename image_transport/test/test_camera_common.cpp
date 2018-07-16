#include <gtest/gtest.h>

#include "image_transport/camera_common.h"

TEST(CameraCommon, getCameraInfoTopic_namespaced_topic) {
  const auto topic_name = "/this/is/a/topic";
  const auto info_topic = image_transport::getCameraInfoTopic(topic_name);
  EXPECT_EQ(info_topic, "/this/is/a/camera_info");
}

TEST(CameraCommon, getCameraInfoTopic_topic) {
  const auto topic_name = "/topic";
  const auto info_topic = image_transport::getCameraInfoTopic(topic_name);
  EXPECT_EQ(info_topic, "/camera_info");
}

// Crashes in boost implementation
TEST(CameraCommon, getCameraInfoTopic2_slash) {
  //TODO: Check if this is the correct behavior
  const auto topic_name = "/";
  const auto info_topic = image_transport::getCameraInfoTopic(topic_name);
  EXPECT_EQ(info_topic, "/camera_info");
}

// Crashes in boost implementation
TEST(CameraCommon, getCameraInfoTopic2_empty) {
  //TODO: Check if this is the correct behavior
  const auto topic_name = "";
  const auto info_topic = image_transport::getCameraInfoTopic(topic_name);
  EXPECT_EQ(info_topic, "/camera_info");
}

