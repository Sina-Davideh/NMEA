#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "nmea.h"

NMEA_Data_Struct_t GPS_NMEA_DataPackage;

typedef struct {
    char ID[10];
    char Message[50];
    char Checksum[3];
} NMEA_Meaage_Struct_t;



int main()
{
    // GGA_Structure_Update(&GPS_NMEA_DataPackage, GGA_Sample);
    // GLL_Structure_Update(&GPS_NMEA_DataPackage, GLL_Sample);
    GSA_Structure_Update(&GPS_NMEA_DataPackage, GSA_Sample);
    
    return 0;
}

void GGA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->GGA.Message_ID, token);

    /* Extract UTC Time */
    token = strtok(0, ",");
    nmea->GGA.UTC_Time.Time = atof(token);
    nmea->GGA.UTC_Time.hour = nmea->GGA.UTC_Time.Time / 10000;
    nmea->GGA.UTC_Time.min = (nmea->GGA.UTC_Time.Time/100) - (((int)(nmea->GGA.UTC_Time.Time/10000))*100);
    nmea->GGA.UTC_Time.sec = nmea->GGA.UTC_Time.Time - (((int)(nmea->GGA.UTC_Time.Time/100))*100);

    /* Extract Latitude */
    token = strtok(0, ",");
    nmea->GGA.Location.latitude.Position = atof(token);
    nmea->GGA.Location.latitude.Degree = nmea->GGA.Location.latitude.Position / 100;
    nmea->GGA.Location.latitude.Minutes = nmea->GGA.Location.latitude.Position - (nmea->GGA.Location.latitude.Degree * 100);

    /* Extract N/S Indicator */
    token = strtok(0, ",");
    nmea->GGA.Location.NS = *token;

    /* Extract Longitude */
    token = strtok(0, ",");
    nmea->GGA.Location.longitude.Position = atof(token);
    nmea->GGA.Location.longitude.Degree = nmea->GGA.Location.longitude.Position / 100;
    nmea->GGA.Location.longitude.Minutes = nmea->GGA.Location.longitude.Position - (nmea->GGA.Location.longitude.Degree * 100);

    /* Extract E/W Indicator */
    token = strtok(0, ",");
    nmea->GGA.Location.EW = *token;

    /* Extract Position_Fix_Indicator */
    token = strtok(0, ",");
    nmea->GGA.Position_Fix = atoi(token);

    /* Extract Satellites_Used */
    token = strtok(0, ",");
    nmea->GGA.Satellites_Used = atoi(token);

    /* Extract HDOP */
    token = strtok(0, ",");
    nmea->GGA.HDOP = atof(token);

    /* Extract MSL_Altitude */
    token = strtok(0, ",");
    nmea->GGA.MSL_Altitude = atof(token);

    /* Extract MSL_Altitude_Units */
    token = strtok(0, ",");
    nmea->GGA.MSL_Altitude_Units = *token;

    /* Extract Geoid_Separation */
    token = strtok(0, ",");
    nmea->GGA.Geoid_Separation = atof(token);

    /* Extract Geoid_Separation_Units */
    token = strtok(0, ",");
    nmea->GGA.Geoid_Separation_Units = *token;

    /* Extract Age_of_Diff_Corr */
    token = strtok(0, ",");
    nmea->GGA.Age_of_Diff_Corr = atof(token);

    /* Extract Diff_Ref_Station_ID*/
    token = strtok(0, ",");
    nmea->GGA.Diff_Ref_Station_ID = atoi(token);

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(nmea->GGA.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    printf("%s\n", nmea->GGA.Message_ID);
    printf("%f\n", nmea->GGA.UTC_Time.Time);
    printf("%d\n", nmea->GGA.UTC_Time.hour);
    printf("%d\n", nmea->GGA.UTC_Time.min);
    printf("%f\n", nmea->GGA.UTC_Time.sec);
    printf("%f\n", nmea->GGA.Location.latitude.Position);
    printf("%d\n", nmea->GGA.Location.latitude.Degree);
    printf("%f\n", nmea->GGA.Location.latitude.Minutes);
    printf("%c\n", nmea->GGA.Location.NS);
    printf("%f\n", nmea->GGA.Location.longitude.Position);
    printf("%d\n", nmea->GGA.Location.longitude.Degree);
    printf("%f\n", nmea->GGA.Location.longitude.Minutes);
    printf("%c\n", nmea->GGA.Location.EW);
    printf("%d\n", nmea->GGA.Position_Fix);
    printf("%d\n", nmea->GGA.Satellites_Used);
    printf("%.1f\n", nmea->GGA.HDOP);
    printf("%.1f\n", nmea->GGA.MSL_Altitude);
    printf("%c\n", nmea->GGA.MSL_Altitude_Units);
    printf("%.1f\n", nmea->GGA.Geoid_Separation);
    printf("%c\n", nmea->GGA.Geoid_Separation_Units);
    printf("%f\n", nmea->GGA.Age_of_Diff_Corr);
    printf("%d\n", nmea->GGA.Diff_Ref_Station_ID);
    printf("%s\n", nmea->GGA.Str_Checksum);

    char *pGGA_Message_ID = &GGA_Message_ID[0];
    char *pGGA_Checksum = &GGA_Checksum[0];

    char *pGGA_Struct_Message_ID = &nmea->GGA.Message_ID[0];
    char *pGGA_Struct_Checksum = &nmea->GGA.Str_Checksum[0];

    if(strcmp(pGGA_Message_ID, pGGA_Struct_Message_ID) == 0){
        printf("GGA Message ID validated\n");
    }

    if(strcmp(pGGA_Checksum, pGGA_Struct_Checksum) == 0){
        printf("GGA Checksum validated\n");
    }
}


void GLL_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->GLL.Message_ID, token);

    /* Extract Latitude */
    token = strtok(0, ",");
    nmea->GLL.Location.latitude.Position = atof(token);
    nmea->GLL.Location.latitude.Degree = nmea->GLL.Location.latitude.Position / 100;
    nmea->GLL.Location.latitude.Minutes = nmea->GLL.Location.latitude.Position - (nmea->GLL.Location.latitude.Degree * 100);

    /* Extract N/S Indicator */
    token = strtok(0, ",");
    nmea->GLL.Location.NS = *token;

    /* Extract Longitude */
    token = strtok(0, ",");
    nmea->GLL.Location.longitude.Position = atof(token);
    nmea->GLL.Location.longitude.Degree = nmea->GLL.Location.longitude.Position / 100;
    nmea->GLL.Location.longitude.Minutes = nmea->GLL.Location.longitude.Position - (nmea->GLL.Location.longitude.Degree * 100);

    /* Extract E/W Indicator */
    token = strtok(0, ",");
    nmea->GLL.Location.EW = *token;

    /* Extract UTC Time */
    token = strtok(0, ",");
    nmea->GLL.UTC_Time.Time = atof(token);
    nmea->GLL.UTC_Time.hour = nmea->GLL.UTC_Time.Time / 10000;
    nmea->GLL.UTC_Time.min = (nmea->GLL.UTC_Time.Time/100) - (((int)(nmea->GLL.UTC_Time.Time/10000))*100);
    nmea->GLL.UTC_Time.sec = nmea->GLL.UTC_Time.Time - (((int)(nmea->GLL.UTC_Time.Time/100))*100);

    /* Extract Status */
    token = strtok(0, ",");
    nmea->GLL.Status = *token;

    /* Extract Mode */
    token = strtok(0, ",");
    nmea->GLL.Mode = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(nmea->GLL.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    printf("%s\n", nmea->GLL.Message_ID);
    printf("%f\n", nmea->GLL.Location.latitude.Position);
    printf("%d\n", nmea->GLL.Location.latitude.Degree);
    printf("%f\n", nmea->GLL.Location.latitude.Minutes);
    printf("%c\n", nmea->GLL.Location.NS);
    printf("%f\n", nmea->GLL.Location.longitude.Position);
    printf("%d\n", nmea->GLL.Location.longitude.Degree);
    printf("%f\n", nmea->GLL.Location.longitude.Minutes);
    printf("%c\n", nmea->GLL.Location.EW);
    printf("%f\n", nmea->GLL.UTC_Time.Time);
    printf("%d\n", nmea->GLL.UTC_Time.hour);
    printf("%d\n", nmea->GLL.UTC_Time.min);
    printf("%f\n", nmea->GLL.UTC_Time.sec);
    printf("%c\n", nmea->GLL.Status);
    printf("%c\n", nmea->GLL.Mode);
    printf("%s\n", nmea->GLL.Str_Checksum);

    char *pGLL_Message_ID = &GLL_Message_ID[0];
    char *pGLL_Checksum = &GLL_Checksum[0];

    char *pGLL_Struct_Message_ID = &nmea->GLL.Message_ID[0];
    char *pGLL_Struct_Checksum = &nmea->GLL.Str_Checksum[0];

    if(strcmp(pGLL_Message_ID, pGLL_Struct_Message_ID) == 0){
        printf("GLL Message ID validated\n");
    }

    if(strcmp(pGLL_Checksum, pGLL_Struct_Checksum) == 0){
        printf("GLL Checksum validated\n");
    }
}


void GSA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->GSA.Message_ID, token);

    /* Extract Mode 1 */
    token = strtok(0, ",");
    printf("%s\n",token);
    nmea->GSA.Mode1 = *token;

    /* Extract Mode 2 */
    token = strtok(0, ",");
    nmea->GSA.Mode2 = atoi(token);

    /* Extract Satellite Used 01 | SV on Channel 1 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_01 = atoi(token);

    /* Extract Satellite Used 02 | SV on Channel 2 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_02 = atoi(token);

    /* Extract Satellite Used 03 | SV on Channel 3 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_03 = atoi(token);

    /* Extract Satellite Used 04 | SV on Channel 4 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_04 = atoi(token);

    /* Extract Satellite Used 05 | SV on Channel 5 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_05 = atoi(token);

    /* Extract Satellite Used 06 | SV on Channel 6 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_06 = atoi(token);

    /* Extract Satellite Used 07 | SV on Channel 7 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_07 = atoi(token);

    /* Extract Satellite Used 08 | SV on Channel 8 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_08 = atoi(token);

    /* Extract Satellite Used 09 | SV on Channel 9 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_09 = atoi(token);

    /* Extract Satellite Used 10 | SV on Channel 10 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_10 = atoi(token);

    /* Extract Satellite Used 11 | SV on Channel 11 */
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_11 = atoi(token);
    /* Extract Satellite Used 12 | SV on Channel 12*/
    token = strtok(0, ",");
    nmea->GSA.Satellite_Used_12 = atoi(token);

    /* Extract PDOP (Position Dilution of Precision) */
    token = strtok(0, ",");
    nmea->GSA.PDOP = atof(token);

    /* Extract HDOP (Horizontal Dilution of Precision) */
    token = strtok(0, ",");
    nmea->GSA.HDOP = atof(token);
    
    /* Extract VDOP (Vertical Dilution of Precision) */
    token = strtok(0, ",");
    nmea->GSA.VDOP = atof(token);

    // /* Extract Mode */
    // token = strtok(0, ",");
    // strcpy(temp, token);
    // nmea->GLL.Mode = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(nmea->GSA.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    printf("%s\n", nmea->GSA.Message_ID);
    printf("%c\n", nmea->GSA.Mode1);
    printf("%d\n", nmea->GSA.Mode2);
    printf("%d\n", nmea->GSA.Satellite_Used_01);
    printf("%d\n", nmea->GSA.Satellite_Used_02);
    printf("%d\n", nmea->GSA.Satellite_Used_03);
    printf("%d\n", nmea->GSA.Satellite_Used_04);
    printf("%d\n", nmea->GSA.Satellite_Used_05);
    printf("%d\n", nmea->GSA.Satellite_Used_06);
    printf("%d\n", nmea->GSA.Satellite_Used_07);
    printf("%d\n", nmea->GSA.Satellite_Used_08);
    printf("%d\n", nmea->GSA.Satellite_Used_09);
    printf("%d\n", nmea->GSA.Satellite_Used_10);
    printf("%d\n", nmea->GSA.Satellite_Used_11);
    printf("%d\n", nmea->GSA.Satellite_Used_12);
    printf("%.1f\n", nmea->GSA.PDOP);
    printf("%.1f\n", nmea->GSA.HDOP);
    printf("%.1f\n", nmea->GSA.VDOP);
    printf("%s\n", nmea->GSA.Str_Checksum);

    char *pGSA_Message_ID = &GSA_Message_ID[0];
    char *pGSA_Checksum = &GSA_Checksum[0];

    char *pGSA_Struct_Message_ID = &nmea->GSA.Message_ID[0];
    char *pGSA_Struct_Checksum = &nmea->GSA.Str_Checksum[0];

    if(strcmp(pGSA_Message_ID, pGSA_Struct_Message_ID) == 0){
        printf("GSA Message ID validated\n");
    }

    if(strcmp(pGSA_Checksum, pGSA_Struct_Checksum) == 0){
        printf("GSA Checksum validated\n");
    }
}
