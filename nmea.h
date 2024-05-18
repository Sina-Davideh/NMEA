#ifndef _NMEA_H_
#define _NMEA_H_


const char Message_Sign = '$';
const char *Split_Sign = ",";
const char Checksum_Sign = '*';

/* Message sample to test */
char GGA_Sample[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,0,0000*5E";
char GLL_Sample[] = "$GPGLL,3723.2475,N,12158.3416,W,161229.487,A,A*41";
char GSA_Sample[] = "$GPGSA,A,3,07,02,26,27,09,04,15, , , , , ,1.8,1.0,1.5*33";
char GSV_Sample_One[] = "$GPGSV,2,1,07,07,79,048,42,02,51,062,43,26,36,256,42,27,27,138,42*71";
char GSV_Sample_Two[] = "$GPGSV,2,2,07,09,23,313,42,04,19,159,41,15,12,041,42*41";
char MSS_Sample[] = "$GPMSS,55,27,318.0,100,1,*57";
char RMC_Sample[] = "$GPRMC,161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598, ,*10";
char VTG_Sample[] = "$GPVTG,309.62,T, ,M,0.13,N,0.2,K,A*23";
char ZDA_Sample[] = "$GPZDA,181813,14,10,2003,00,00*4F";
char N150_Sample[] = "$PSRF150,1*3F";
char N151_Sample[] = "";
char N152_Sample[] = "";
char N154_Sample[] = "";

/* Message ID and Checksum definition */
char GGA_Message_ID[] = "$GPGGA";
char GGA_Checksum[] = "*5E";

char GLL_Message_ID[] = "$GPGLL";
char GLL_Checksum[] = "*41";

char GSA_Message_ID[] = "$GPGSA";
char GSA_Checksum[] = "*33";

const char GSV_Message_ID[] = "$GPGSV";
const char GSV_Checksum[] = "*71";

const char MSS_Message_ID[] = "$GPMSS";
const char MSS_Checksum[] = "*57";

const char RMC_Message_ID[] = "$GPRMC";
const char RMC_Checksum[] = "*10";

const char VTG_Message_ID[] = "$GPVTG";
const char VTG_Checksum[] = "*23";

const char ZDA_Message_ID[] = "$GPZDA";
const char ZDA_Checksum[] = "*4F";









typedef enum{
    Fix_Not_Available = 0,
    GPS_SPS_Mode_fix_valid,
    Differential_GPS_SPS_Mode_fix_valid,
    Not_Supported1,
    Not_Supported2,
    Not_Supported3,
    Dead_Reckoning_Mode_fix_valid
} Position_Fix_Indicator_e;

typedef struct {
    double Time;
	int hour;
	int min;
	float sec;
} UTC_TIME_Struct_t;

typedef struct
{
    float Position;
    int Degree;
    float Minutes;
} Position_Struct_t;

typedef struct {
	Position_Struct_t latitude;
	char NS;     /* N=north or S=south */
	Position_Struct_t longitude;
	char EW;     /* E=east or W=west */
} Location_Struct_t;



typedef struct{
    char Message_ID[6];
    UTC_TIME_Struct_t UTC_Time;
	Location_Struct_t Location;
	// Position_Fix_Indicator_e Position_Fix;
    int Position_Fix;
    int Satellites_Used;
    float HDOP;
    float MSL_Altitude;
    char MSL_Altitude_Units;
    float Geoid_Separation;
    char Geoid_Separation_Units;
    float Age_of_Diff_Corr;
    int Diff_Ref_Station_ID;
    char Str_Checksum[3];
} GGA_Struct_t;

typedef struct{
    char Message_ID[6];
    UTC_TIME_Struct_t UTC_Time;
	Location_Struct_t Location;
    char Status;                  /* A=data valid or V=data not valid */
    char Mode;                    /* A=Autonomous, D=DGPS, E=DR (Only present in NMEA v3.00) */
    char Str_Checksum[3];
} GLL_Struct_t;

typedef struct{
    char Message_ID[6];
    char Mode1;                     /* M:Manual—forced to operate in 2D or 3D mode | A:2D Automatic—allowed to automatically switch 2D/3D */
    int Mode2;                      /* 1:Fix not available | 2:2D (<4 SVs used) | 3:3D (>3 SVs used) */
    int Satellite_Used_01;          /* SV on Channel 1 */
    int Satellite_Used_02;          /* SV on Channel 2 */
    int Satellite_Used_03;          /* SV on Channel 3 */
    int Satellite_Used_04;          /* SV on Channel 4 */
    int Satellite_Used_05;          /* SV on Channel 5 */
    int Satellite_Used_06;          /* SV on Channel 6 */
    int Satellite_Used_07;          /* SV on Channel 7 */
    int Satellite_Used_08;          /* SV on Channel 8 */
    int Satellite_Used_09;          /* SV on Channel 9 */
    int Satellite_Used_10;          /* SV on Channel 10 */
    int Satellite_Used_11;          /* SV on Channel 11 */
    int Satellite_Used_12;          /* SV on Channel 12 */
    float PDOP;                     /* Position Dilution of Precision */
    float HDOP;                     /* Horizontal Dilution of Precision */
    float VDOP;                     /* Vertical Dilution of Precision */
    char Str_Checksum[3];
} GSA_Struct_t;


typedef struct
{
    GGA_Struct_t    GGA;
    GLL_Struct_t    GLL;
    GSA_Struct_t    GSA;
    // GSV_Struct_t    GSV;
    // MSS_Struct_t    MSS;
    // RMC_Struct_t    RMC;
    // VTG_Struct_t    VTG;
    // ZDA_Struct_t    ZDA;
    // N150_Struct_t   N150;
    // N151_Struct_t   N151;
    // N152_Struct_t   N152;
    // N154_Struct_t   N154;
} NMEA_Data_Struct_t;



// typedef struct {
// 	float altitude;
// 	char unit;
// }ALTITUDE;

// typedef struct {
// 	int Day;
// 	int Mon;
// 	int Yr;
// }DATE;

// typedef struct {
// 	DATE date;
// 	float speed;
// 	float course;
// 	int isValid;
// }RMCSTRUCT;

// typedef struct {
// 	GGA_STRUCT_t ggastruct;
// 	RMCSTRUCT rmcstruct;
// }GPSSTRUCT;

void GGA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer);
void GLL_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer);
void GSA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer);

#endif /* _NMEA_H_ */
