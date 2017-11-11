#include "PoseCartProcess.h"
#include <stdio.h>

bool PoseCartProcess::init()
{

}
bool PoseCartProcess::init_posetrack()
{

}
PoseCartProcess::PoseCartProcess()
{
	track_index = 0;
	track_rail_index = 1;
	pose.x_mil = 0;
	pose.y_mil = 0;
	pose.yaw_mdeg = 0;
	track_count = 0;
	loop_track = false;
	trackcollection_complete = false;
	run_update = true;
	gaporrail = GAP; //Initial condition is before the first rail, sensor on the gap
	last_sensorvalue = SENSOR_HIGH;
	traversed_distance_mil = 0;
	//Initialize all known Tracks

	Track_365007.PN = TRACK_365007;
	Track_365007.track_length_mil = 8895;
	Track_365007.curvature_mil = 0;
	int pattern_index = 0;
	{
		TrackPattern pattern;
		pattern.rail_index = 1;
		pattern.rail_width_mil = 100;
		pattern.gap_width_mil = 145;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 2;
		pattern.rail_width_mil = 100;
		pattern.gap_width_mil = 140;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 3;
		pattern.rail_width_mil = 95;
		pattern.gap_width_mil = 150;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
			TrackPattern pattern;
			pattern.rail_index = 33;
			pattern.rail_width_mil = 95;
			pattern.gap_width_mil = 150;
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
		pattern.rail_width_mil = 95;
		pattern.gap_width_mil = 140;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 36;
		pattern.rail_width_mil = 100;
		pattern.gap_width_mil = 145;
		Track_365007.patterns[pattern_index++] = pattern;
	}
	{
		TrackPattern pattern;
		pattern.rail_index = 37;
		pattern.rail_width_mil = 100;
		pattern.gap_width_mil = 80; //Last rail doesn't have a gap
		Track_365007.patterns[pattern_index++] = pattern;
	}
	Track_365007.pattern_count = pattern_index;
	Track_365007.rail_count = Track_365007.patterns[pattern_index-1].rail_index;
	Track_365007.last_gap = Track_365007.patterns[pattern_index-1].gap_width_mil;

}
long PoseCartProcess::compute_tracklength(unsigned char id)
{
	Track t = get_definedtrack(id);
	long length = 0;
	printf("count: %d\n",t.pattern_count);
	int railindex = 0;
	length += (t.patterns[0].rail_width_mil + t.patterns[0].gap_width_mil);
	printf("v: %d %d %d\n",length);
	for(int i = 1; i < (t.pattern_count-1);i++)
	{

		int rail_count = t.patterns[i+1].rail_index - t.patterns[i].rail_index;
		railindex += rail_count;
		length += rail_count * (t.patterns[i].rail_width_mil + t.patterns[i].gap_width_mil);
		printf("v: %d %d %d\n",railindex,rail_count,length);
	}
	length += (t.patterns[t.pattern_count].rail_width_mil + t.patterns[t.pattern_count].gap_width_mil);
	printf("v: %d %d\n",railindex,length);
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
Track PoseCartProcess::get_definedtrack(unsigned char track_id)
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
void PoseCartProcess::new_sensorvalue(int v,int trackdirection)
{
	long dl = 0;
	if((trackcollection_complete == true) and (loop_track == false))
	{
		run_update = false;
	}
	if(run_update == true)
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
			dl = pattern.rail_width_mil;
			//printf("Rail Triggered: %d %d\n",track_rail_index,traversed_distance_mil);


		}
		if(gap_triggered)
		{

			TrackPattern pattern = get_trackpatterninfo(track_index,track_rail_index);
			traversed_distance_mil += pattern.gap_width_mil;
			dl = pattern.gap_width_mil;
			//printf("Gap Triggered: %d %d\n",track_rail_index,traversed_distance_mil);
			track_rail_index++;

			if(track_rail_index > (get_definedtrack(tracks[track_index]).rail_count)) //Next track
			{
				track_rail_index = 1;
				track_index++;
				if(track_index > (track_count-1)) //End of all tracks.  Set back to 0
				{
					trackcollection_complete = true;
					//traversed_distance_mil -= pattern.gap_width_mil;
					track_index = 0;
				}
				else
				{
					trackcollection_complete = false;
				}
			}
		}
		Track t = get_definedtrack(tracks[track_index]);
		float dtheta = 0.0;
		if(t.curvature_mil == 0)
		{
		}
		else
		{
			dtheta = (float)(dl)/t.curvature_mil;
			if(trackdirection == -1){ dtheta *= -1.0; }
			pose.yaw_mdeg += (long)(dtheta*180000.0/PI);
		}
		float d = (float)dl;
		float yaw_rad = (float)(pose.yaw_mdeg*PI/180000.0);
//#if ENVIRONMENT == DESKTOP
		float dx = dl*cos(yaw_rad);
		float dy = dl*sin(yaw_rad);
		pose.x_mil += (long)(dx);
		pose.y_mil += (long)(dy);
//#elif ENVIRONMENT == ARDUINO
//#endif
	}
	last_sensorvalue = v;
}
TrackPattern PoseCartProcess::get_trackpatterninfo(int trackindex,int railindex)
{
	unsigned char id = tracks[trackindex];
	Track track = get_definedtrack(id);
	if(railindex <= track.patterns[0].rail_index)
	{
		return track.patterns[0];
	}
	int rail = track.patterns[0].rail_index-1;
	for(int i = 1; i < track.pattern_count;i++)
	{
		rail = track.patterns[i].rail_index;
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

