//Cpp Specific
#include <iostream>
#include <stdio.h>
#include <string.h>
//ROBOTEQ Specific
#include "RoboteqDevice.h"
#include "ErrorCodes.h"
#include "Constants.h"
//ROS Specific
#include<ros/ros.h>
#include<sensor_msgs/Joy.h>

//using namespace std;
// roboteq global description
	RoboteqDevice device;//std::
	int status,speed_pos=100,speed_neg=-100;//std::

void increment()
{
	speed_pos++;
	speed_neg--;
	cout<<speed_pos<<"  "<<speed_neg;
}

void decrement()
{
	speed_pos--;
	speed_neg++;
	cout<<speed_pos<<"  "<<speed_neg;
}

void forward()
{
	if((status = device.SetCommandId(1,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(2,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(3,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(4,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
}

void backward()
{
	if((status = device.SetCommandId(1,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(2,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(3,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(4,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
}

void right()
{
	if((status = device.SetCommandId(1,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(2,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(3,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(4,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
}


void left()
{
	if((status = device.SetCommandId(1,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(2,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(3,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(4,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
}

void clockwise()
{
	if((status = device.SetCommandId(1,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(2,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(3,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(4,_GO,1,speed_neg)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
}

void anticlockwise()
{
	if((status = device.SetCommandId(1,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(2,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(3,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(4,_GO,1,speed_pos)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
}

void stop()
{
	if((status = device.SetCommandId(1,_GO,1,0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(2,_GO,1,0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(3,_GO,1,0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	if((status = device.SetCommandId(4,_GO,1,0)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
}

void reset_velo()
{
	speed_neg=-100;
	speed_pos=100;
	cout<<speed_pos<<"  "<<speed_neg;
}
// void soft_right()
// {
// 	if((status = device.SetCommandId(1,_GO,1,speed_pos)) != RQ_SUCCESS)
// 		cout<<"failed --> "<<status<<endl;
// 	if((status = device.SetCommandId(2,_GO,1,speed_pos)) != RQ_SUCCESS)
// 		cout<<"failed --> "<<status<<endl;
// 	if((status = device.SetCommandId(3,_GO,1,speed_pos)) != RQ_SUCCESS)
// 		cout<<"failed --> "<<status<<endl;
// 	if((status = device.SetCommandId(4,_GO,1,speed_pos)) != RQ_SUCCESS)
// 		cout<<"failed --> "<<status<<endl;

// }

// void soft_left()
// {
	
// }



/*THE CALLBACK FUNCTION*/
void alareala(const sensor_msgs::Joy::ConstPtr& joy)
{
	//cout<<"dodo";
	
	//ROS_INFO_STREAM("Connection succesfully established and trying to receive messages");

	if(joy->buttons[3]==1)
	{
		cout<<"connecting"<<endl;
		status = device.Connect("/dev/ttyUSB0");
	}
	if(joy->buttons[4]==1)
	{
		cout<<"forward"<<endl;
		forward();
	}
	else if(joy->buttons[6]==1)
	{
		cout<<"backward"<<endl;
		backward();

	}
	else if(joy->buttons[5]==1)
	{
		cout<<"right"<<endl;
		right();
	}
	else if(joy->buttons[7]==1)
	{
		cout<<"left"<<endl;
		left();
	}
	else if(joy->buttons[13]==1)
	{
		cout<<"clockwise"<<endl;
		clockwise();
	}
	else if(joy->buttons[15]==1)
	{
		cout<<"anti-clockwise"<<endl;
		anticlockwise();
	}
	else if(joy->buttons[0]==1)
	{
		cout<<"disconnecting...."<<endl;
		device.Disconnect();;
	}
	else if(joy->buttons[14]==1)
	{
		cout<<"stop"<<endl;
		stop();
	}
	else if(joy->buttons[10]==1)
	{
		cout<<"decrement"<<endl;
		increment();
	}
	else if(joy->buttons[11]==1)
	{
		cout<<"increment"<<endl;
		decrement();
	}
	else if(joy->buttons[9]==1)
	{
		cout<<"reset velo"<<endl;
		reset_velo();
	}
	else 
	{	}
}





int main(int argc, char *argv[])
{



//ros
	ros::init(argc,argv,"sub");
	ros::NodeHandle nh;

	if(status != RQ_SUCCESS)
	{
		cout<<"Error connecting to device: "<<status<<"."<<endl;
		return 1;
	}
	cout<<"- SetConfig(_DINA, 1, 1)...";
	
	if((status = device.SetConfig(_DINA, 1, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	 sleepms(10);
	ROS_INFO_STREAM("Connection succesfully established and trying to receive messages");

//considering all connection issues resolved

// Create a subscriber object.
	ros::Subscriber sub=nh.subscribe( "joy",1000,&alareala );
	ros::spin();

	/*At the end of everything, use this*/
	// device.Disconnect();
	return 0;
	
}
