
#include <ros/ros.h>

#include <ros/console.h>


#include <tf/transform_listener.h>
#include <tf/message_filter.h>

#include <message_filters/subscriber.h>
#include <std_msgs/String.h>
#include <handle_detector/HandleListMsg.h>
#include <handle_detector/CylinderMsg.h>
#include <geometry_msgs/PoseStamped.h>
class Door_handle_detection_node
{
public:
    Door_handle_detection_node(ros::NodeHandle& nh,ros::NodeHandle& pnh)
     {

        tf_listener_.reset(new tf::TransformListener());
        subHandleList_ = nh.subscribe("/localization/handle_list",10,&Door_handle_detection_node::handleCallback,this);
        doorHandlePub_ = nh.advertise<geometry_msgs::PoseStamped>("best_door_handle_pose", 1, false);
        cylinderPub_ = nh.advertise<handle_detector::CylinderMsg>("best_door_handle_cylinder", 1, false);

    }

    void handleCallback(const handle_detector::HandleListMsg& handle_list)

    {  //std::cout << "in callback"<<std::endl;
        handle_detector::CylinderMsg best_cylinder; //currently just the one most at the right from camera view
        std::cout <<"size of handle list "<< handle_list.handles.size()<<std::endl;
        if (handle_list.handles.size()>0){


            best_cylinder=handle_list.handles.at(0).cylinders.at(0);
            for(int i=0; i< handle_list.handles.size(); ++i) {
                for (int j=0; j< handle_list.handles.at(i).cylinders.size(); ++j){
                    if(best_cylinder.pose.position.x<handle_list.handles.at(i).cylinders.at(j).pose.position.x){
                        best_cylinder=handle_list.handles.at(i).cylinders.at(j);
                    }
                    //std::cout << "Pose of handel " << i <<"/ "<<j<<"  : "<<handle_list.handles.at(i).cylinders.at(j).pose.position << std::endl;
                }
            }
            std::cout <<" best cylinder pose "<< best_cylinder.pose.position<<std::endl;
            geometry_msgs::PoseStamped best_cylinder_pose;
            best_cylinder_pose.header.frame_id="camera_depth_optical_frame";
            best_cylinder_pose.pose=best_cylinder.pose;
            best_cylinder_pose.header.stamp=ros::Time::now();
            doorHandlePub_.publish(best_cylinder_pose);
            cylinderPub_.publish(best_cylinder);
        }

    }


protected:
    ros::Subscriber subHandleList_;
    boost::shared_ptr<tf::TransformListener> tf_listener_;
    ros::Publisher doorHandlePub_;
    ros::Publisher cylinderPub_;
};


int main(int argc, char **argv)
{
    ROS_INFO("Door Handle: started Node");
    ros::init(argc,argv,"hector_door_handle_detector");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    Door_handle_detection_node m_door_handle_node(nh,pnh);
    ros::spin();

    return 0;

}

