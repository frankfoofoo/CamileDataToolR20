#ifndef _CYCLECOMPUTER_H_
#define _CYCLECOMPUTER_H_

#define CYCLE_TRIPS_TABLE	"TRACK"

#define GET_YEAR(_time_)	(((_time_) >> 26) + 2000)
#define GET_MONTH(_time_)	(((_time_) >> 22) & 15)
#define GET_DAY(_time_)		(((_time_) >> 17) & 31)
#define GET_HOUR(_time_)	(((_time_) >> 12) & 31)
#define GET_MINUTE(_time_)	(((_time_) >> 6) & 63)
#define GET_SECOND(_time_)	(((_time_) >> 0) & 63)

typedef enum {
	COL_TRIP_ID = 0,
	COL_POINTS,
	COL_RIDE_DATE,
	COL_RIDE_TIME,
	COL_TOTAL_TIME,
	COL_DISTANCE,
	COL_DISTANCE_UP,
	COL_DISTANCE_DOWN,
	COL_CALORIE,
	COL_MAX_SPEED,
	COL_SPORT_AVG_SPEED,
	COL_TOTAL_AVG_SPEED,
	COL_MAX_ALTITUDE,
	COL_MIN_ALTITUDE,
	COL_AVG_ALTITUDE,
	COL_MAX_GRADE_UP,
	COL_MAX_GRADE_DOWN,
	COL_MAX_TEMPERATURE,
	COL_MIN_TEMPERATURE,
	COL_AVG_TEMPERATURE,
	COL_MAX_CADENCE,
	COL_AVG_CADENCE,
	COL_MAX_HEARTRATE,
	COL_AVG_HEARTRATE,
	COL_MAX_POWER,
	COL_AVG_POWER,
	COL_MAX_CNT
}TRIPS_TBL_COL_IDX;

typedef enum {
	IDX_TRIP_ID = 0,
	IDX_POINTS,
	IDX_RIDE_DATE,
	IDX_SPORT_TIME,
	IDX_TOTAL_TIME,
	IDX_DISTANCE,
	IDX_DISTANCE_UP,
	IDX_DISTANCE_DOWN,
	IDX_CALORIE,
	IDX_MAX_SPEED,
	IDX_SPORT_AVG_SPEED,
	IDX_TOTAL_AVG_SPEED,
	IDX_MAX_ALTITUDE,
	IDX_MIN_ALTITUDE,
	IDX_AVG_ALTITUDE,
	IDX_ALTITUDE_UP,
	IDX_ALTITUDE_DOWN,
	IDX_MAX_GRADE_UP,
	IDX_MAX_GRADE_DOWN,
	IDX_MAX_TEMPERATURE,
	IDX_MIN_TEMPERATURE,
	IDX_AVG_TEMPERATURE,
	IDX_MAX_CADENCE,
	IDX_AVG_CADENCE,
	IDX_MAX_HEARTRATE,
	IDX_AVG_HEARTRATE,
	IDX_MAX_POWER,
	IDX_AVG_POWER,
	IDX_MAX_CNT
}LIST_BOX_COL_IDX;

typedef enum {
	LAP_ID = 0,
	LAP_SPORT_TIME,
	LAP_SPORT_DISTANCE,
	LAP_SPORT_AVG_SPEED,
	LAP_MAX_SPEED,
	LAP_MAX_TEMPERATURE,
	LAP_MIN_TEMPERATURE,
	LAP_AVG_TEMPERATURE,
	LAP_MAX_ALTITUDE,
	LAP_MIN_ALTITUDE,
	LAP_AVG_ALTITUDE,
	LAP_ALTITUDE_UP,
	LAP_ALTITUDE_DOWN,
	LAP_MAX_GRADE_UP,
	LAP_MAX_GRADE_DOWN,
	LAP_CALORIE,
	LAP_MAX_CADENCE,
	LAP_AVG_CADENCE,
	LAP_MAX_HEARTRATE,
	LAP_AVG_HEARTRATE,
	LAP_MAX_POWER,
	LAP_AVG_POWER,
	LAP_MAX_CNT
}LIST_BOX_LAP_INFO_IDX;

typedef struct
{
	int time_stamp;
	double longitude;
	int longitude_EW;
	double latitude;
	int latitude_NS;
	double speed;
	double trip;
	int altitude;
	int temperature;
}st_track_line_info;

typedef struct
{
	char trip_id[40];
	int point_count;
	int ride_date;
	int sport_time;
	int total_time;
	double distance;
	double distance_up;
	double distance_down;
	int calorie;
	double max_speed;
	double sport_avg_speed;
	double total_avg_speed;
	int max_altitude;
	int min_altitude;
	int avg_altitude;
	int altitude_up;
	int altitude_down;
	int max_grade_up;
	int max_grade_down;
	int max_temperature;
	int min_temperature;
	int avg_temperature;
	int max_cadence;
	int avg_cadence;
	int max_heartrate;
	int avg_heartrate;
	int max_power;
	int avg_power;
}st_track_statistics_info;


#endif  // _CYCLECOMPUTER_H_