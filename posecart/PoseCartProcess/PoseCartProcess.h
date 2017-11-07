#ifndef POSECARTPROCESS_H
#define POSECARTPROCESS_H
#define MAX_PATTERNS_PER_TRACK 24
#define MAX_TRACKS 64
#define TRACK_365007 1
#define SENSOR_HIGH 100//Highest value, this should be when the Sensor is on the GAP
#define SENSOR_LOW 30 //Lowest value, this should be when Sensor is on the RAIL
#define UNDEFINED 0
#define RAIL 1
#define GAP 2
struct TrackPattern
{
	//TrackPattern is a segment of rails and gaps that each have the same width
	int rail_index;
	long rail_width_mil; //milli-inch
	long gap_width_mil; //milli-inch
};
struct Track
{
	long PN;
	int direction; //-1: left 0: straight 1: right
	int curvature_inches;
	TrackPattern patterns[MAX_PATTERNS_PER_TRACK];
	int pattern_count;
	int rail_count;
	long track_length_mil; //Spec length, far left rail to far right rail

};
struct Pose
{
	long x_mil;
	long y_mil;
	long yaw_mdeg;
};

class PoseCartProcess
{
	public:
		PoseCartProcess();
		//void update();
		bool init(); //Call this method and then create all Tracks
		void reset_pose() { pose.x_mil = 0; pose.y_mil = 0; pose.yaw_mdeg = 0; }
		Pose get_pose() { return pose; }
		Track get_definedtrack(int track_id);
		bool trackbuild_complete() { track_index = 0; }
		bool new_track(Track track_)
		{
			tracks[track_index++] = track_;
			track_count++;
			if(track_index > MAX_TRACKS) { return false; } else { return true; }
		}
		bool init_posetrack(); //Call this method and all Tracks will be created automatically.
		long compute_tracklength(Track t);
		long compute_alltracklength();
		long get_traverseddistance() { return traversed_distance_mil; }
		void new_sensorvalue(int v);
	private:
		TrackPattern get_trackpatterninfo(int trackindex,int railindex);
		Track tracks[MAX_TRACKS];
		int track_index;
		int track_rail_index;
		int track_count;
		long traversed_distance_mil;
		int gaporrail;
		int last_sensorvalue;
		Pose pose;

		Track Track_365007;


};
#endif
