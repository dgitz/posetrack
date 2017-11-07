#include <gtest/gtest.h>
#include "../PoseCartProcess/PoseCartProcess.h"
TEST(AllTracks,Initialization)
{
    PoseCartProcess process;
    ASSERT_EQ(process.compute_tracklength(process.get_definedtrack(TRACK_365007)),process.get_definedtrack(TRACK_365007).track_length_mil);
}
TEST(Pose,IndividualTracks)
{
	{//Track: 365007
		PoseCartProcess process;
		process.init();
		ASSERT_TRUE(process.new_track(process.get_definedtrack(TRACK_365007)));
		process.trackbuild_complete();
		process.reset_pose();
		double dt = .01; //inches
		double time = 0.0;
		bool sensor_direction = true;
		int sensor_value = SENSOR_HIGH-10;
		while(time < 5.0)
		{
			time += dt;
			process.new_sensorvalue(sensor_value);
			if(sensor_direction == true){	sensor_value += 5; 	}
			else { sensor_value -= 5; }
			if(sensor_value > (SENSOR_HIGH + 10)){ sensor_direction = false; }
			if(sensor_value < (SENSOR_LOW - 10)) { sensor_direction = true; }
			//printf("v: %d distance: %ld\n",sensor_value,process.get_traverseddistance());
		}


	}
}
int main(int argc,char ** argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
