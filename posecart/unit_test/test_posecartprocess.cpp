#include <gtest/gtest.h>
#include "../PoseCartProcess/PoseCartProcess.h"
TEST(AllTracks,Initialization)
{
    PoseCartProcess process;
    printf("%d %d\n",process.compute_tracklength(TRACK_365007),process.get_definedtrack(TRACK_365007).track_length_mil);
    ASSERT_EQ(process.compute_tracklength(TRACK_365007),process.get_definedtrack(TRACK_365007).track_length_mil);
}
TEST(Pose,IndividualTracks)
{
	{//Track: 365007
		PoseCartProcess process;
		process.init();
		ASSERT_TRUE(process.new_track(TRACK_365007));
		process.trackbuild_complete();
		process.reset_pose();
		double dt = .01; //inches
		double time = 0.0;
		bool sensor_direction = true;
		int sensor_value = SENSOR_HIGH-10;
		while(time < 5.0)
		{
			time += dt;
			process.new_sensorvalue(sensor_value,0);
			if(sensor_direction == true){	sensor_value += 5; 	}
			else { sensor_value -= 5; }
			if(sensor_value > (SENSOR_HIGH + 10)){ sensor_direction = false; }
			if(sensor_value < (SENSOR_LOW - 10)) { sensor_direction = true; }
			//printf("v: %d distance: %ld\n",sensor_value,process.get_traverseddistance());
		}
	}
}
TEST(Pose,TrackCollections)
{
	{//Track: 365007 x3
		PoseCartProcess process;
		process.init();
		int required_traversal_distance = 0;
		for(int i = 0; i < 3; i++)
		{
			ASSERT_TRUE(process.new_track(TRACK_365007));
			required_traversal_distance += process.get_definedtrack(TRACK_365007).track_length_mil;
			required_traversal_distance += process.get_definedtrack(TRACK_365007).last_gap;
			ASSERT_TRUE(process.new_track(TRACK_365007));
			required_traversal_distance += process.get_definedtrack(TRACK_365007).track_length_mil;
			required_traversal_distance += process.get_definedtrack(TRACK_365007).last_gap;
			ASSERT_TRUE(process.new_track(TRACK_365007));
			required_traversal_distance += process.get_definedtrack(TRACK_365007).track_length_mil;
			required_traversal_distance += process.get_definedtrack(TRACK_365007).last_gap;
		}
		process.trackbuild_complete();
		process.reset_pose();
		double dt = .01; //inches
		double time = 0.0;
		bool sensor_direction = true;
		int sensor_value = SENSOR_HIGH-10;
		int last_rail_index = 0;
		while(time < 3000.0)
		{
			if(process.get_trackcomplete() == true) { break; }
			time += dt;
			process.new_sensorvalue(sensor_value,0);
			if(sensor_direction == true){	sensor_value += 5; 	}
			else { sensor_value -= 5; }
			if(sensor_value > (SENSOR_HIGH + 10)){ sensor_direction = false; }
			if(sensor_value < (SENSOR_LOW - 10)) { sensor_direction = true; }
			if(last_rail_index != process.get_railindex())
			{
/*
				printf("v: %d distance: %ld rail: %d track: %d\n",
						sensor_value,
						process.get_traverseddistance(),
						process.get_railindex(),
						process.get_trackindex());
				last_rail_index = process.get_railindex();
*/
			}

		}
		ASSERT_TRUE(process.get_trackcomplete());
		ASSERT_TRUE(required_traversal_distance==process.get_traverseddistance());
		//printf("%d %d\n",required_traversal_distance,process.get_traverseddistance());
	}
}
int main(int argc,char ** argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
