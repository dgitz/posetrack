#include "PoseCartProcess.h"
//#include <stdio.h>

bool PoseCartProcess::init()
{

}
bool PoseCartProcess::init_posetrack()
{

}
PoseCartProcess::PoseCartProcess()
{
	track_index = 0;
	track_rail_index = 0;
	pose.x_mil = 0;
	pose.y_mil = 0;
	pose.yaw_mdeg = 0;
	track_count = 0;
	gaporrail = GAP; //Initial condition is before the first rail, sensor on the gap
	last_sensorvalue = SENSOR_HIGH;
	traversed_distance_mil = 0;
	//Initialize all known Tracks

	Track_365007.PN = 365007;
	Track_365007.track_length_mil = 8895;
	Track_365007.curvature_mil = 0;
	int pattern_index = 0;
	{
		TrackPattern pattern;
		pattern.rail_index = 0;
		pattern.rail_width_mil = 100;
		pattern.gap_width_mil = 145;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 1;
		pattern.rail_width_mil = 100;
		pattern.gap_width_mil = 140;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 2;
		pattern.rail_width_mil = 95;
		pattern.gap_width_mil = 150;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
			TrackPattern pattern;
			pattern.rail_index = 32;
			pattern.rail_width_mil = 95;
			pattern.gap_width_mil = 150;
			Track_365007.patterns[pattern_index++] = pattern;
		}
	{
		TrackPattern pattern;
		pattern.rail_index = 33;
		pattern.rail_width_mil = 95;
		pattern.gap_width_mil = 140;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 34;
		pattern.rail_width_mil = 95;
		pattern.gap_width_mil = 140;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 35;
		pattern.rail_width_mil = 100;
		pattern.gap_width_mil = 145;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 36;
		pattern.rail_width_mil = 100;
		pattern.gap_width_mil = 0; //Last rail doesn't have a gap
		Track_365007.patterns[pattern_index++] = pattern;
	}
	Track_365007.pattern_count = pattern_index;

}
long PoseCartProcess::compute_tracklength(Track t)
{
	long length = 0;
	for(int i = 0; i < (t.pattern_count-1);i++)
	{
		int rail_count = t.patterns[i+1].rail_index - t.patterns[i].rail_index;
		length += rail_count * (t.patterns[i].rail_width_mil + t.patterns[i].gap_width_mil);
	}
	length += (t.patterns[t.pattern_count-1].rail_width_mil + t.patterns[t.pattern_count-1].gap_width_mil);
	return length;
}
long PoseCartProcess::compute_alltracklength()
{
	long length = 0;
	for(int i = 0; i < track_count; i++)
	{
		length += compute_tracklength(tracks[i]);
	}
	return length;
}
Track PoseCartProcess::get_definedtrack(int track_id)
{
	if(track_id == TRACK_365007)
	{
		return Track_365007;
	}
	else
	{
		Track empty;
		empty.PN = 0;
		empty.pattern_count = 0;
		empty.rail_count = 0;
		return empty;
	}
}
void PoseCartProcess::new_sensorvalue(int v)
{
	bool rail_triggered = false;
	bool gap_triggered = false;
	if((last_sensorvalue < SENSOR_HIGH) and (v >= SENSOR_HIGH)) //Triggered for RAIL
	{
		rail_triggered = true;
	}
	else if((last_sensorvalue > SENSOR_LOW) and (v <= SENSOR_LOW)) //Triggered for GAP
	{
		gap_triggered = true;
	}
	else //No trigger
	{

	}
	if(rail_triggered) //Could be start of next rail or next track
	{

		TrackPattern pattern = get_trackpatterninfo(track_index,track_rail_index);
		traversed_distance_mil += pattern.rail_width_mil;
		//printf("Rail Triggered: %d %d\n",track_rail_index,traversed_distance_mil);


	}
	if(gap_triggered)
	{

		TrackPattern pattern = get_trackpatterninfo(track_index,track_rail_index);
		traversed_distance_mil += pattern.gap_width_mil;
		//printf("Gap Triggered: %d %d\n",track_rail_index,traversed_distance_mil);
		track_rail_index++;

		if(track_rail_index > (tracks[track_index].rail_count-1)) //Next track
		{
			track_rail_index = 0;
			track_index++;
			if(track_index > (track_count-1)) //End of all tracks.  Set back to 0
			{
				track_index = 0;
			}
		}
	}
	last_sensorvalue = v;
}
TrackPattern PoseCartProcess::get_trackpatterninfo(int trackindex,int railindex)
{
	Track track = tracks[trackindex];
	if(railindex <= track.patterns[0].rail_index)
	{
		return track.patterns[0];
	}
	int rail = track.patterns[0].rail_index;
	for(int i = 1; i < track.pattern_count;i++)
	{
		rail += track.patterns[i].rail_index;
		if((railindex > track.patterns[i-1].rail_index) and (railindex <= rail))
		{
			return track.patterns[i];
		}
	}
	TrackPattern pattern;
	pattern.gap_width_mil = 0;
	pattern.rail_width_mil = 0;
	pattern.rail_index = 0;
	return pattern;
}

