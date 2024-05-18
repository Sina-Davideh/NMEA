#include "nmea.h"

void NMEA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *res;
    char *tok;
    char data[100];
    char *pNMEA_Message_ID;
    strcpy(data, buffer);

    /* Remove enytihings before message ID */
    res = strchr(data, '$');
    // printf("%s\n", res);

    /* Extract Message_ID */
    tok = strtok(res, ",");
    // printf("%s\n", tok);

    pNMEA_Message_ID = &GGA_Message_ID[0];
    if (strcmp(tok, pNMEA_Message_ID) == 0)
    {
        GGA_Structure_Update(nmea, buffer);
    }

    pNMEA_Message_ID = &GLL_Message_ID[0];
    if (strcmp(tok, pNMEA_Message_ID) == 0)
    {
        GLL_Structure_Update(nmea, buffer);
    }

    pNMEA_Message_ID = &GSA_Message_ID[0];
    if (strcmp(tok, pNMEA_Message_ID) == 0)
    {
        GSA_Structure_Update(nmea, buffer);
    }

    pNMEA_Message_ID = &GSV_Message_ID[0];
    if (strcmp(tok, pNMEA_Message_ID) == 0)
    {
        GSV_Structure_Update(nmea, buffer);
    }

    pNMEA_Message_ID = &MSS_Message_ID[0];
    if (strcmp(tok, pNMEA_Message_ID) == 0)
    {
        MSS_Structure_Update(nmea, buffer);
    }

    pNMEA_Message_ID = &RMC_Message_ID[0];
    if (strcmp(tok, pNMEA_Message_ID) == 0)
    {
        RMC_Structure_Update(nmea, buffer);
    }

    pNMEA_Message_ID = &VTG_Message_ID[0];
    if (strcmp(tok, pNMEA_Message_ID) == 0)
    {
        VTG_Structure_Update(nmea, buffer);
    }

    pNMEA_Message_ID = &ZDA_Message_ID[0];
    if (strcmp(tok, pNMEA_Message_ID) == 0)
    {
        ZDA_Structure_Update(nmea, buffer);
    }

}


void GGA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove anythings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

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
    // printf("%s\n", nmea->GGA.Message_ID);
    // printf("%f\n", nmea->GGA.UTC_Time.Time);
    // printf("%d\n", nmea->GGA.UTC_Time.hour);
    // printf("%d\n", nmea->GGA.UTC_Time.min);
    // printf("%f\n", nmea->GGA.UTC_Time.sec);
    // printf("%f\n", nmea->GGA.Location.latitude.Position);
    // printf("%d\n", nmea->GGA.Location.latitude.Degree);
    // printf("%f\n", nmea->GGA.Location.latitude.Minutes);
    // printf("%c\n", nmea->GGA.Location.NS);
    // printf("%f\n", nmea->GGA.Location.longitude.Position);
    // printf("%d\n", nmea->GGA.Location.longitude.Degree);
    // printf("%f\n", nmea->GGA.Location.longitude.Minutes);
    // printf("%c\n", nmea->GGA.Location.EW);
    // printf("%d\n", nmea->GGA.Position_Fix);
    // printf("%d\n", nmea->GGA.Satellites_Used);
    // printf("%.1f\n", nmea->GGA.HDOP);
    // printf("%.1f\n", nmea->GGA.MSL_Altitude);
    // printf("%c\n", nmea->GGA.MSL_Altitude_Units);
    // printf("%.1f\n", nmea->GGA.Geoid_Separation);
    // printf("%c\n", nmea->GGA.Geoid_Separation_Units);
    // printf("%f\n", nmea->GGA.Age_of_Diff_Corr);
    // printf("%d\n", nmea->GGA.Diff_Ref_Station_ID);
    // printf("%s\n", nmea->GGA.Str_Checksum);

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
    // printf("%s\n", ret);

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
    // printf("%s\n", nmea->GLL.Message_ID);
    // printf("%f\n", nmea->GLL.Location.latitude.Position);
    // printf("%d\n", nmea->GLL.Location.latitude.Degree);
    // printf("%f\n", nmea->GLL.Location.latitude.Minutes);
    // printf("%c\n", nmea->GLL.Location.NS);
    // printf("%f\n", nmea->GLL.Location.longitude.Position);
    // printf("%d\n", nmea->GLL.Location.longitude.Degree);
    // printf("%f\n", nmea->GLL.Location.longitude.Minutes);
    // printf("%c\n", nmea->GLL.Location.EW);
    // printf("%f\n", nmea->GLL.UTC_Time.Time);
    // printf("%d\n", nmea->GLL.UTC_Time.hour);
    // printf("%d\n", nmea->GLL.UTC_Time.min);
    // printf("%f\n", nmea->GLL.UTC_Time.sec);
    // printf("%c\n", nmea->GLL.Status);
    // printf("%c\n", nmea->GLL.Mode);
    // printf("%s\n", nmea->GLL.Str_Checksum);

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
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->GSA.Message_ID, token);

    /* Extract Mode 1 */
    token = strtok(0, ",");
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
    // printf("%s\n", nmea->GSA.Message_ID);
    // printf("%c\n", nmea->GSA.Mode1);
    // printf("%d\n", nmea->GSA.Mode2);
    // printf("%d\n", nmea->GSA.Satellite_Used_01);
    // printf("%d\n", nmea->GSA.Satellite_Used_02);
    // printf("%d\n", nmea->GSA.Satellite_Used_03);
    // printf("%d\n", nmea->GSA.Satellite_Used_04);
    // printf("%d\n", nmea->GSA.Satellite_Used_05);
    // printf("%d\n", nmea->GSA.Satellite_Used_06);
    // printf("%d\n", nmea->GSA.Satellite_Used_07);
    // printf("%d\n", nmea->GSA.Satellite_Used_08);
    // printf("%d\n", nmea->GSA.Satellite_Used_09);
    // printf("%d\n", nmea->GSA.Satellite_Used_10);
    // printf("%d\n", nmea->GSA.Satellite_Used_11);
    // printf("%d\n", nmea->GSA.Satellite_Used_12);
    // printf("%.1f\n", nmea->GSA.PDOP);
    // printf("%.1f\n", nmea->GSA.HDOP);
    // printf("%.1f\n", nmea->GSA.VDOP);
    // printf("%s\n", nmea->GSA.Str_Checksum);

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


void GSV_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->GSV.Message_ID, token);

    /* Extract Number of Message */
    token = strtok(0, ",");
    nmea->GSV.Number_of_Message = atoi(token);

    /* Extract Message Number */
    token = strtok(0, ",");
    nmea->GSV.Message_Number = atoi(token);

    /* Extract Satellites in View */
    token = strtok(0, ",");
    nmea->GSV.Satellites_in_View = atoi(token);

    /* Extract Satellite-1 ID | Channel 1 (Range 1 to 32) */
    token = strtok(0, ",");
    nmea->GSV.Satellite_1_ID = atoi(token);

    /* Extract Satellite-1 Elevation | Channel 1 (Maximum 90) degrees */
    token = strtok(0, ",");
    nmea->GSV.Satellite_1_Elevation = atoi(token);

    /* Extract Satellite-1 Azimuth | Channel 1 (True, Range 0 to 359) degrees */
    token = strtok(0, ",");
    nmea->GSV.Satellite_1_Azimuth = atoi(token);

    /* Extract Satellite-1 SNR | Range 0 to 99, null when not tracking dBHZ*/
    token = strtok(0, ",");
    nmea->GSV.Satellite_1_SNR = atoi(token);

    /* Extract Satellite-2 ID | Channel 2 (Range 1 to 32) */
    token = strtok(0, ",");
    nmea->GSV.Satellite_2_ID = atoi(token);

    /* Extract Satellite-2 Elevation | Channel 2 (Maximum 90) degrees */
    token = strtok(0, ",");
    nmea->GSV.Satellite_2_Elevation = atoi(token);

    /* Extract Satellite-2 Azimuth | Channel 2 (True, Range 0 to 359) degrees */
    token = strtok(0, ",");
    nmea->GSV.Satellite_2_Azimuth = atoi(token);

    /* Extract Satellite-2 SNR | Range 0 to 99, null when not tracking dBHZ*/
    token = strtok(0, ",");
    nmea->GSV.Satellite_2_SNR = atoi(token);

    /* Extract Satellite-3 ID | Channel 3 (Range 1 to 32) */
    token = strtok(0, ",");
    nmea->GSV.Satellite_3_ID = atoi(token);

    /* Extract Satellite-3 Elevation | Channel 3 (Maximum 90) degrees */
    token = strtok(0, ",");
    nmea->GSV.Satellite_3_Elevation = atoi(token);

    /* Extract Satellite-3 Azimuth | Channel 3 (True, Range 0 to 359) degrees */
    token = strtok(0, ",");
    nmea->GSV.Satellite_3_Azimuth = atoi(token);

    /* Extract Satellite-3 SNR | Range 0 to 99, null when not tracking dBHZ*/
    token = strtok(0, ",");
    nmea->GSV.Satellite_3_SNR = atoi(token);

    /* Extract Satellite-4 ID | Channel 4 (Range 1 to 32) */
    token = strtok(0, ",");
    nmea->GSV.Satellite_4_ID = atoi(token);

    /* Extract Satellite-4 Elevation | Channel 4 (Maximum 90) degrees */
    token = strtok(0, ",");
    nmea->GSV.Satellite_4_Elevation = atoi(token);

    /* Extract Satellite-4 Azimuth | Channel 4 (True, Range 0 to 359) degrees */
    token = strtok(0, ",");
    nmea->GSV.Satellite_4_Azimuth = atoi(token);

    /* Extract Satellite-4 SNR | Range 0 to 99, null when not tracking dBHZ*/
    token = strtok(0, ",");
    nmea->GSV.Satellite_4_SNR = atoi(token);

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(nmea->GSV.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", nmea->GSV.Message_ID);
    // printf("%d\n", nmea->GSV.Number_of_Message);
    // printf("%d\n", nmea->GSV.Message_Number);
    // printf("%d\n", nmea->GSV.Satellites_in_View);
    // printf("%d\n", nmea->GSV.Satellite_1_ID);
    // printf("%d\n", nmea->GSV.Satellite_1_Elevation);
    // printf("%d\n", nmea->GSV.Satellite_1_Azimuth);
    // printf("%d\n", nmea->GSV.Satellite_1_SNR);
    // printf("%d\n", nmea->GSV.Satellite_2_ID);
    // printf("%d\n", nmea->GSV.Satellite_2_Elevation);
    // printf("%d\n", nmea->GSV.Satellite_2_Azimuth);
    // printf("%d\n", nmea->GSV.Satellite_2_SNR);
    // printf("%d\n", nmea->GSV.Satellite_3_ID);
    // printf("%d\n", nmea->GSV.Satellite_3_Elevation);
    // printf("%d\n", nmea->GSV.Satellite_3_Azimuth);
    // printf("%d\n", nmea->GSV.Satellite_3_SNR);
    // printf("%d\n", nmea->GSV.Satellite_4_ID);
    // printf("%d\n", nmea->GSV.Satellite_4_Elevation);
    // printf("%d\n", nmea->GSV.Satellite_4_Azimuth);
    // printf("%d\n", nmea->GSV.Satellite_4_SNR);
    // printf("%s\n", nmea->GSV.Str_Checksum);

    char *pGSV_Message_ID = &GSV_Message_ID[0];
    char *pGSV_Checksum = &GSV_Checksum[0];

    char *pGSV_Struct_Message_ID = &nmea->GSV.Message_ID[0];
    char *pGSV_Struct_Checksum = &nmea->GSV.Str_Checksum[0];

    if(strcmp(pGSV_Message_ID, pGSV_Struct_Message_ID) == 0){
        printf("GSV Message ID validated\n");
    }

    if(strcmp(pGSV_Checksum, pGSV_Struct_Checksum) == 0){
        printf("GSV Checksum validated\n");
    }
}


void MSS_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->MSS.Message_ID, token);

    /* Extract SS of tracked frequency | dB */
    token = strtok(0, ",");
    nmea->MSS.Signal_Strength = atoi(token);

    /* Extract SNR of tracked frequency | dB */
    token = strtok(0, ",");
    nmea->MSS.Signal_to_Noise_Ratio = atoi(token);

    /* Extract Satellites in View */
    token = strtok(0, ",");
    nmea->MSS.Beacon_Frequency = atof(token);

    /* Extract bits per second */
    token = strtok(0, ",");
    nmea->MSS.Beacon_Bit_Rate = atoi(token);

    /* Extract The channel of the beacon being used if a multi-channel beacon receiver is used. */
    token = strtok(0, ",");
    nmea->MSS.Channel_Number = atoi(token);

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(nmea->MSS.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", nmea->MSS.Message_ID);
    // printf("%d\n", nmea->MSS.Signal_Strength);
    // printf("%d\n", nmea->MSS.Signal_to_Noise_Ratio);
    // printf("%f\n", nmea->MSS.Beacon_Frequency);
    // printf("%d\n", nmea->MSS.Beacon_Bit_Rate);
    // printf("%d\n", nmea->MSS.Channel_Number);
    // printf("%s\n", nmea->MSS.Str_Checksum);

    char *pMSS_Message_ID = &MSS_Message_ID[0];
    char *pMSS_Checksum = &MSS_Checksum[0];

    char *pMSS_Struct_Message_ID = &nmea->MSS.Message_ID[0];
    char *pMSS_Struct_Checksum = &nmea->MSS.Str_Checksum[0];

    if(strcmp(pMSS_Message_ID, pMSS_Struct_Message_ID) == 0){
        printf("MSS Message ID validated\n");
    }

    if(strcmp(pMSS_Checksum, pMSS_Struct_Checksum) == 0){
        printf("MSS Checksum validated\n");
    }
}


void RMC_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->RMC.Message_ID, token);

    /* Extract UTC Time */
    token = strtok(0, ",");
    nmea->RMC.UTC_Time.Time = atof(token);
    nmea->RMC.UTC_Time.hour = nmea->RMC.UTC_Time.Time / 10000;
    nmea->RMC.UTC_Time.min = (nmea->RMC.UTC_Time.Time/100) - (((int)(nmea->RMC.UTC_Time.Time/10000))*100);
    nmea->RMC.UTC_Time.sec = nmea->RMC.UTC_Time.Time - (((int)(nmea->RMC.UTC_Time.Time/100))*100);

    /* Extract Status */
    token = strtok(0, ",");
    nmea->RMC.Status = *token;

    /* Extract Latitude */
    token = strtok(0, ",");
    nmea->RMC.Location.latitude.Position = atof(token);
    nmea->RMC.Location.latitude.Degree = nmea->RMC.Location.latitude.Position / 100;
    nmea->RMC.Location.latitude.Minutes = nmea->RMC.Location.latitude.Position - (nmea->RMC.Location.latitude.Degree * 100);

    /* Extract N/S Indicator */
    token = strtok(0, ",");
    nmea->RMC.Location.NS = *token;

    /* Extract Longitude */
    token = strtok(0, ",");
    nmea->RMC.Location.longitude.Position = atof(token);
    nmea->RMC.Location.longitude.Degree = nmea->RMC.Location.longitude.Position / 100;
    nmea->RMC.Location.longitude.Minutes = nmea->RMC.Location.longitude.Position - (nmea->RMC.Location.longitude.Degree * 100);

    /* Extract E/W Indicator */
    token = strtok(0, ",");
    nmea->RMC.Location.EW = *token;

    /* Extract Speed Over Ground | Knots */
    token = strtok(0, ",");
    nmea->RMC.Speed_Over_Ground = atof(token);

    /* Extract Course Over Ground | degr */
    token = strtok(0, ",");
    nmea->RMC.Course_Over_Ground = atof(token);

    /* Extract Date */
    token = strtok(0, ",");
    nmea->RMC.UTC_Date.Date = atoi(token);
    nmea->RMC.UTC_Date.Day = nmea->RMC.UTC_Date.Date / 10000;
    nmea->RMC.UTC_Date.Mon = (nmea->RMC.UTC_Date.Date/100) - (((int)(nmea->RMC.UTC_Date.Date/10000))*100);
    nmea->RMC.UTC_Date.Yr = nmea->RMC.UTC_Date.Date - (((int)(nmea->RMC.UTC_Date.Date/100))*100);

    /* Extract Magnetic_Variation */
    token = strtok(0, ",");
    nmea->RMC.Magnetic_Variation = *token;

    /* Extract East_West_Indicator */
    token = strtok(0, ",");
    nmea->RMC.East_West_Indicator = *token;    

    /* Extract Mode */
    token = strtok(0, ",");
    nmea->RMC.Mode = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(nmea->RMC.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", nmea->RMC.Message_ID);
    // printf("%f\n", nmea->RMC.UTC_Time.Time);
    // printf("%d\n", nmea->RMC.UTC_Time.hour);
    // printf("%d\n", nmea->RMC.UTC_Time.min);
    // printf("%f\n", nmea->RMC.UTC_Time.sec);
    // printf("%c\n", nmea->RMC.Status);
    // printf("%f\n", nmea->RMC.Location.latitude.Position);
    // printf("%d\n", nmea->RMC.Location.latitude.Degree);
    // printf("%f\n", nmea->RMC.Location.latitude.Minutes);
    // printf("%c\n", nmea->RMC.Location.NS);
    // printf("%f\n", nmea->RMC.Location.longitude.Position);
    // printf("%d\n", nmea->RMC.Location.longitude.Degree);
    // printf("%f\n", nmea->RMC.Location.longitude.Minutes);
    // printf("%c\n", nmea->RMC.Location.EW);
    // printf("%f\n", nmea->RMC.Speed_Over_Ground);
    // printf("%f\n", nmea->RMC.Course_Over_Ground);
    // printf("%d\n", nmea->RMC.UTC_Date.Date);
    // printf("%d\n", nmea->RMC.UTC_Date.Day);
    // printf("%d\n", nmea->RMC.UTC_Date.Mon);
    // printf("%d\n", nmea->RMC.UTC_Date.Yr);
    // printf("%c\n", nmea->RMC.Magnetic_Variation);
    // printf("%c\n", nmea->RMC.East_West_Indicator);
    // printf("%c\n", nmea->RMC.Mode);
    // printf("%s\n", nmea->RMC.Str_Checksum);

    char *pRMC_Message_ID = &RMC_Message_ID[0];
    char *pRMC_Checksum = &RMC_Checksum[0];

    char *pRMC_Struct_Message_ID = &nmea->RMC.Message_ID[0];
    char *pRMC_Struct_Checksum = &nmea->RMC.Str_Checksum[0];

    if(strcmp(pRMC_Message_ID, pRMC_Struct_Message_ID) == 0){
        printf("RMC Message ID validated\n");
    }

    if(strcmp(pRMC_Checksum, pRMC_Struct_Checksum) == 0){
        printf("RMC Checksum validated\n");
    }
}


void VTG_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->VTG.Message_ID, token);

    /* Extract Measured true heading | degree */
    token = strtok(0, ",");
    nmea->VTG.Course_T = atof(token);

    /* Extract Measured heading reference | True */
    token = strtok(0, ",");
    nmea->VTG.Reference_T = *token;

    /* Extract Measured magnetic heading | degree */
    token = strtok(0, ",");
    nmea->VTG.Course_M = atof(token);

    /* Extract Measured heading reference | Magnetic */
    token = strtok(0, ",");
    nmea->VTG.Reference_M = *token;

    /* Extract Measured horizontal speed | Knots */
    token = strtok(0, ",");
    nmea->VTG.Speed_Knots = atof(token);

    /* Extract Measured horizontal speed units | Knots */
    token = strtok(0, ",");
    nmea->VTG.Units_Knots = *token;

    /* Extract Measured horizontal speed | Km/hr */
    token = strtok(0, ",");
    nmea->VTG.Speed_Km_hr = atof(token);

    /* Extract Measured horizontal speed units | Km/hr */
    token = strtok(0, ",");
    nmea->VTG.Units_Km_hr = *token;    

    /* Extract Mode */
    token = strtok(0, ",");
    nmea->VTG.Mode = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(nmea->VTG.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", nmea->VTG.Message_ID);
    // printf("%f\n", nmea->VTG.Course_T);
    // printf("%c\n", nmea->VTG.Reference_T);
    // printf("%f\n", nmea->VTG.Course_M);
    // printf("%c\n", nmea->VTG.Reference_M);
    // printf("%f\n", nmea->VTG.Speed_Knots);
    // printf("%c\n", nmea->VTG.Units_Knots);
    // printf("%f\n", nmea->VTG.Speed_Km_hr);
    // printf("%c\n", nmea->VTG.Units_Km_hr);
    // printf("%c\n", nmea->VTG.Mode);
    // printf("%s\n", nmea->VTG.Str_Checksum);

    char *pVTG_Message_ID = &VTG_Message_ID[0];
    char *pVTG_Checksum = &VTG_Checksum[0];

    char *pVTG_Struct_Message_ID = &nmea->VTG.Message_ID[0];
    char *pVTG_Struct_Checksum = &nmea->VTG.Str_Checksum[0];

    if(strcmp(pVTG_Message_ID, pVTG_Struct_Message_ID) == 0){
        printf("VTG Message ID validated\n");
    }

    if(strcmp(pVTG_Checksum, pVTG_Struct_Checksum) == 0){
        printf("VTG Checksum validated\n");
    }
}


void ZDA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(nmea->ZDA.Message_ID, token);

    /* Extract UTC Time */
    token = strtok(0, ",");
    nmea->ZDA.UTC_Time.Time = atof(token);
    nmea->ZDA.UTC_Time.hour = nmea->ZDA.UTC_Time.Time / 10000;
    nmea->ZDA.UTC_Time.min = (nmea->ZDA.UTC_Time.Time/100) - (((int)(nmea->ZDA.UTC_Time.Time/10000))*100);
    nmea->ZDA.UTC_Time.sec = nmea->ZDA.UTC_Time.Time - (((int)(nmea->ZDA.UTC_Time.Time/100))*100);

    /* Extract Date */
    token = strtok(0, ",");
    nmea->ZDA.UTC_Date.Day = atoi(token);
    token = strtok(0, ",");
    nmea->ZDA.UTC_Date.Mon = atoi(token);
    token = strtok(0, ",");
    nmea->ZDA.UTC_Date.Yr = atoi(token);

    /* Extract Local_Zone */
    token = strtok(0, ",");
    nmea->ZDA.Local_Zone.hour = *token;
    token = strtok(0, ",");
    nmea->ZDA.Local_Zone.minutes = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(nmea->ZDA.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", nmea->ZDA.Message_ID);
    // printf("%f\n", nmea->ZDA.UTC_Time.Time);
    // printf("%d\n", nmea->ZDA.UTC_Time.hour);
    // printf("%d\n", nmea->ZDA.UTC_Time.min);
    // printf("%f\n", nmea->ZDA.UTC_Time.sec);
    // printf("%d\n", nmea->ZDA.UTC_Date.Day);
    // printf("%d\n", nmea->ZDA.UTC_Date.Mon);
    // printf("%d\n", nmea->ZDA.UTC_Date.Yr);
    // printf("%d\n", nmea->ZDA.Local_Zone.hour);
    // printf("%d\n", nmea->ZDA.Local_Zone.minutes);
    // printf("%s\n", nmea->ZDA.Str_Checksum);

    char *pZDA_Message_ID = &ZDA_Message_ID[0];
    char *pZDA_Checksum = &ZDA_Checksum[0];

    char *pZDA_Struct_Message_ID = &nmea->ZDA.Message_ID[0];
    char *pZDA_Struct_Checksum = &nmea->ZDA.Str_Checksum[0];

    if(strcmp(pZDA_Message_ID, pZDA_Struct_Message_ID) == 0){
        printf("ZDA Message ID validated\n");
    }

    if(strcmp(pZDA_Checksum, pZDA_Struct_Checksum) == 0){
        printf("ZDA Checksum validated\n");
    }
}

