#include <ros/ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>


int main(int argc, char **argv){

  //ros initialization, we must provide the node name
  ros::init(argc, argv,"ultrasonic_sim");
  
  //initialize node object
  ros::NodeHandle  nh;

  //initialize sensor_msg struct
  sensor_msgs::Range sonar_msg;

  //initialize the publisher object. It needs the topic name, and the buffer size
  ros::Publisher pub_range = nh.advertise<sensor_msgs::Range>("rangeSonar", 200);

  //initialize the dummy sensor reading to 0
  int sensoReading = 0;

  //frame name, important for rviz
  char frameid[] ="/sonar_ranger"; 

  //we define the rate of publishing data. Here it is 5 transmissions per second
  ros::Rate loop_rate(5);

  //initialize the struct parameters
  /*
  * radiation_type: to be ultrasonic
  * frame_id : to the frame id we defined here
  * field_of_view: this is specified in the ultrasonic sensor documentation
  * min/max ranges
  */
  sonar_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  sonar_msg.header.frame_id =  frameid;
  sonar_msg.field_of_view = (10.0/180.0) * 3.14;
  sonar_msg.min_range = 0.0; 
  sonar_msg.max_range = 100.0;

  //The main loop of the program
  while(ros::ok()){

    //incremen the sensor dummy reading. The modulo operator means the maximum is 50, as required from the assignment
    sensoReading = (sensoReading + 1)%50;

    //assign the range field of the message to the dummy sensor reading
    sonar_msg.range = sensoReading;
    sonar_msg.header.stamp = ros::Time::now();

    //publish the message on the topic using the publisher object defined earlier
    pub_range.publish(sonar_msg);

    //sleep to adjust to the data transmission frequency defined in the Rate object
    loop_rate.sleep();
  }
}
