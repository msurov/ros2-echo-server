#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "time.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;


class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher")
    {
      publisher_ = this->create_publisher<std_msgs::msg::Int64>("echoinp", 10);
      subscription_ = this->create_subscription<std_msgs::msg::Int64>(
          "echoout", 10, 
          std::bind(&MinimalPublisher::topic_callback, this, _1)
      );
      timer_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer_callback, this)
      );
    }

  private:

    void timer_callback()
    {
      auto req = std_msgs::msg::Int64();
      req.data = get_epoch_usec();
      publisher_->publish(req);
    }

    void topic_callback(const std_msgs::msg::Int64::SharedPtr msg) const
    {
      int64_t value = msg->data;
      RCLCPP_INFO(this->get_logger(), "ellapsed %ld usec", get_epoch_usec() - value);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
