#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

public:
  
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/usb_cam/image_raw", 1,
      &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);
    cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void setTagLocations(float x_det, float y_det, float z_det)
  {
	  //TODO: Update tag locations
	x_arr.push_back(x_det);
	y_arr.push_back(y_det);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
	std::cout<<cv_ptr->image.rows<<cv_ptr->image.cols;
	//TODO: Draw circles at tag locations on image. 
    for(std::vector<float>::size_type i=0; i !=x_arr.size(); i++){
	int x=639.0/2.0+639.0/2.0*x_arr[i];//240+90 + x_arr[i]*240; //this is from -1(0) to +1(480) //
	int y=477.0/2.0 +477.0/2.0*y_arr[i] ;//360-75 + y_arr[i]*360; //this is from -1(0) to +1(640) //
	
	if(cv_ptr->image.rows > 60 && cv_ptr->image.cols >60)
		cv::circle(cv_ptr->image, cv::Point(x,y), 3, CV_RGB(255,0,0));
	}

    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, cv_ptr->image);
    cv::waitKey(3);

    // TODO:Output modified video stream
	image_pub_.publish(cv_ptr->toImageMsg());// is it image_pub_ or image_pub
    // Convert the modified frames into sensor_msgs::Image message and publish it using image_pub
  }

private:
  float x_loc ,y_loc;
  std::vector<float> x_arr;
  std::vector<float> y_arr;
};
