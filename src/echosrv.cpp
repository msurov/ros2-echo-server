#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class EchoServer : public rclcpp::Node
{
  public:
    EchoServer() : Node("echoserver")
    {
      subscription_ = this->create_subscription<std_msgs::msg::Int64>(
          "echoinp", 10, 
          std::bind(&EchoServer::topic_callback, this, _1)
      );
      publisher_ = this->create_publisher<std_msgs::msg::Int64>("echoout", 10);
    }

  private:
    void topic_callback(const std_msgs::msg::Int64::SharedPtr msg) const
    {
      auto value = msg->data;
      auto answer = std_msgs::msg::Int64();
      answer.data = value;
      publisher_->publish(answer);
      RCLCPP_INFO(this->get_logger(), "received: %ld", value);
    }

    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<EchoServer>());
  rclcpp::shutdown();
  return 0;
}
