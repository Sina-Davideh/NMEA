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

    GGA_Struct_t gga_temp_struct;

    /* Remove anythings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(gga_temp_struct.Message_ID, token);

    /* Extract UTC Time */
    token = strtok(0, ",");

    gga_temp_struct.UTC_Time.Time = atof(token);
    gga_temp_struct.UTC_Time.hour = gga_temp_struct.UTC_Time.Time / 10000;
    gga_temp_struct.UTC_Time.min = (gga_temp_struct.UTC_Time.Time/100) - (((int)(gga_temp_struct.UTC_Time.Time/10000))*100);
    gga_temp_struct.UTC_Time.sec = gga_temp_struct.UTC_Time.Time - (((int)(gga_temp_struct.UTC_Time.Time/100))*100);

    /* Extract Latitude */
    token = strtok(0, ",");
    gga_temp_struct.Location.latitude.Position = atof(token);
    gga_temp_struct.Location.latitude.Degree = gga_temp_struct.Location.latitude.Position / 100;
    gga_temp_struct.Location.latitude.Minutes = gga_temp_struct.Location.latitude.Position - (gga_temp_struct.Location.latitude.Degree * 100);

    /* Extract N/S Indicator */
    token = strtok(0, ",");
    gga_temp_struct.Location.NS = *token;

    /* Extract Longitude */
    token = strtok(0, ",");
    gga_temp_struct.Location.longitude.Position = atof(token);
    gga_temp_struct.Location.longitude.Degree = gga_temp_struct.Location.longitude.Position / 100;
    gga_temp_struct.Location.longitude.Minutes = gga_temp_struct.Location.longitude.Position - (gga_temp_struct.Location.longitude.Degree * 100);

    /* Extract E/W Indicator */
    token = strtok(0, ",");
    gga_temp_struct.Location.EW = *token;

    /* Extract Position_Fix_Indicator */
    token = strtok(0, ",");
    gga_temp_struct.Position_Fix = atoi(token);

    /* Extract Satellites_Used */
    token = strtok(0, ",");
    gga_temp_struct.Satellites_Used = atoi(token);

    /* Extract HDOP */
    token = strtok(0, ",");
    gga_temp_struct.HDOP = atof(token);

    /* Extract MSL_Altitude */
    token = strtok(0, ",");
    gga_temp_struct.MSL_Altitude = atof(token);

    /* Extract MSL_Altitude_Units */
    token = strtok(0, ",");
    gga_temp_struct.MSL_Altitude_Units = *token;

    /* Extract Geoid_Separation */
    token = strtok(0, ",");
    gga_temp_struct.Geoid_Separation = atof(token);

    /* Extract Geoid_Separation_Units */
    token = strtok(0, ",");
    gga_temp_struct.Geoid_Separation_Units = *token;

    /* Extract Age_of_Diff_Corr */
    token = strtok(0, ",");
    gga_temp_struct.Age_of_Diff_Corr = atof(token);

    /* Extract Diff_Ref_Station_ID*/
    token = strtok(0, ",");
    gga_temp_struct.Diff_Ref_Station_ID = atoi(token);

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(gga_temp_struct.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", gga_temp_struct.Message_ID);
    // printf("%f\n", gga_temp_struct.UTC_Time.Time);
    // printf("%d\n", gga_temp_struct.UTC_Time.hour);
    // printf("%d\n", gga_temp_struct.UTC_Time.min);
    // printf("%f\n", gga_temp_struct.UTC_Time.sec);
    // printf("%f\n", gga_temp_struct.Location.latitude.Position);
    // printf("%d\n", gga_temp_struct.Location.latitude.Degree);
    // printf("%f\n", gga_temp_struct.Location.latitude.Minutes);
    // printf("%c\n", gga_temp_struct.Location.NS);
    // printf("%f\n", gga_temp_struct.Location.longitude.Position);
    // printf("%d\n", gga_temp_struct.Location.longitude.Degree);
    // printf("%f\n", gga_temp_struct.Location.longitude.Minutes);
    // printf("%c\n", gga_temp_struct.Location.EW);
    // printf("%d\n", gga_temp_struct.Position_Fix);
    // printf("%d\n", gga_temp_struct.Satellites_Used);
    // printf("%.1f\n", gga_temp_struct.HDOP);
    // printf("%.1f\n", gga_temp_struct.MSL_Altitude);
    // printf("%c\n", gga_temp_struct.MSL_Altitude_Units);
    // printf("%.1f\n", gga_temp_struct.Geoid_Separation);
    // printf("%c\n", gga_temp_struct.Geoid_Separation_Units);
    // printf("%f\n", gga_temp_struct.Age_of_Diff_Corr);
    // printf("%d\n", gga_temp_struct.Diff_Ref_Station_ID);
    // printf("%s\n", gga_temp_struct.Str_Checksum);

    char *pGGA_Message_ID = &GGA_Message_ID[0];
    char *pGGA_Checksum = &GGA_Checksum[0];

    char *pGGA_Struct_Message_ID = &gga_temp_struct.Message_ID[0];
    char *pGGA_Struct_Checksum = &gga_temp_struct.Str_Checksum[0];

    if(strcmp(pGGA_Message_ID, pGGA_Struct_Message_ID) == 0){
        printf("GGA Message ID validated\n");

        if(strcmp(pGGA_Checksum, pGGA_Struct_Checksum) == 0){
            printf("GGA Checksum validated\n");
            nmea->GGA = gga_temp_struct;
        }
    }

}


void GLL_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    GLL_Struct_t gll_temp_struct;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(gll_temp_struct.Message_ID, token);

    /* Extract Latitude */
    token = strtok(0, ",");
    gll_temp_struct.Location.latitude.Position = atof(token);
    gll_temp_struct.Location.latitude.Degree = gll_temp_struct.Location.latitude.Position / 100;
    gll_temp_struct.Location.latitude.Minutes = gll_temp_struct.Location.latitude.Position - (gll_temp_struct.Location.latitude.Degree * 100);

    /* Extract N/S Indicator */
    token = strtok(0, ",");
    gll_temp_struct.Location.NS = *token;

    /* Extract Longitude */
    token = strtok(0, ",");
    gll_temp_struct.Location.longitude.Position = atof(token);
    gll_temp_struct.Location.longitude.Degree = gll_temp_struct.Location.longitude.Position / 100;
    gll_temp_struct.Location.longitude.Minutes = gll_temp_struct.Location.longitude.Position - (gll_temp_struct.Location.longitude.Degree * 100);

    /* Extract E/W Indicator */
    token = strtok(0, ",");
    gll_temp_struct.Location.EW = *token;

    /* Extract UTC Time */
    token = strtok(0, ",");
    gll_temp_struct.UTC_Time.Time = atof(token);
    gll_temp_struct.UTC_Time.hour = gll_temp_struct.UTC_Time.Time / 10000;
    gll_temp_struct.UTC_Time.min = (gll_temp_struct.UTC_Time.Time/100) - (((int)(gll_temp_struct.UTC_Time.Time/10000))*100);
    gll_temp_struct.UTC_Time.sec = gll_temp_struct.UTC_Time.Time - (((int)(gll_temp_struct.UTC_Time.Time/100))*100);

    /* Extract Status */
    token = strtok(0, ",");
    gll_temp_struct.Status = *token;

    /* Extract Mode */
    token = strtok(0, ",");
    gll_temp_struct.Mode = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(gll_temp_struct.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", gll_temp_struct.Message_ID);
    // printf("%f\n", gll_temp_struct.Location.latitude.Position);
    // printf("%d\n", gll_temp_struct.Location.latitude.Degree);
    // printf("%f\n", gll_temp_struct.Location.latitude.Minutes);
    // printf("%c\n", gll_temp_struct.Location.NS);
    // printf("%f\n", gll_temp_struct.Location.longitude.Position);
    // printf("%d\n", gll_temp_struct.Location.longitude.Degree);
    // printf("%f\n", gll_temp_struct.Location.longitude.Minutes);
    // printf("%c\n", gll_temp_struct.Location.EW);
    // printf("%f\n", gll_temp_struct.UTC_Time.Time);
    // printf("%d\n", gll_temp_struct.UTC_Time.hour);
    // printf("%d\n", gll_temp_struct.UTC_Time.min);
    // printf("%f\n", gll_temp_struct.UTC_Time.sec);
    // printf("%c\n", gll_temp_struct.Status);
    // printf("%c\n", gll_temp_struct.Mode);
    // printf("%s\n", gll_temp_struct.Str_Checksum);

    char *pGLL_Message_ID = &GLL_Message_ID[0];
    char *pGLL_Checksum = &GLL_Checksum[0];

    char *pGLL_Struct_Message_ID = &gll_temp_struct.Message_ID[0];
    char *pGLL_Struct_Checksum = &gll_temp_struct.Str_Checksum[0];

    if(strcmp(pGLL_Message_ID, pGLL_Struct_Message_ID) == 0){
        printf("GLL Message ID validated\n");

        if(strcmp(pGLL_Checksum, pGLL_Struct_Checksum) == 0){
            printf("GLL Checksum validated\n");
            nmea->GLL = gll_temp_struct;
        }
    }

}


void GSA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    GSA_Struct_t gsa_temp_struct;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(gsa_temp_struct.Message_ID, token);

    /* Extract Mode 1 */
    token = strtok(0, ",");
    gsa_temp_struct.Mode1 = *token;

    /* Extract Mode 2 */
    token = strtok(0, ",");
    gsa_temp_struct.Mode2 = atoi(token);

    /* Extract Satellite Used 01 | SV on Channel 1 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_01 = atoi(token);

    /* Extract Satellite Used 02 | SV on Channel 2 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_02 = atoi(token);

    /* Extract Satellite Used 03 | SV on Channel 3 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_03 = atoi(token);

    /* Extract Satellite Used 04 | SV on Channel 4 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_04 = atoi(token);

    /* Extract Satellite Used 05 | SV on Channel 5 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_05 = atoi(token);

    /* Extract Satellite Used 06 | SV on Channel 6 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_06 = atoi(token);

    /* Extract Satellite Used 07 | SV on Channel 7 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_07 = atoi(token);

    /* Extract Satellite Used 08 | SV on Channel 8 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_08 = atoi(token);

    /* Extract Satellite Used 09 | SV on Channel 9 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_09 = atoi(token);

    /* Extract Satellite Used 10 | SV on Channel 10 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_10 = atoi(token);

    /* Extract Satellite Used 11 | SV on Channel 11 */
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_11 = atoi(token);
    /* Extract Satellite Used 12 | SV on Channel 12*/
    token = strtok(0, ",");
    gsa_temp_struct.Satellite_Used_12 = atoi(token);

    /* Extract PDOP (Position Dilution of Precision) */
    token = strtok(0, ",");
    gsa_temp_struct.PDOP = atof(token);

    /* Extract HDOP (Horizontal Dilution of Precision) */
    token = strtok(0, ",");
    gsa_temp_struct.HDOP = atof(token);
    
    /* Extract VDOP (Vertical Dilution of Precision) */
    token = strtok(0, ",");
    gsa_temp_struct.VDOP = atof(token);

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(gsa_temp_struct.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", gsa_temp_struct.Message_ID);
    // printf("%c\n", gsa_temp_struct.Mode1);
    // printf("%d\n", gsa_temp_struct.Mode2);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_01);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_02);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_03);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_04);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_05);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_06);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_07);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_08);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_09);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_10);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_11);
    // printf("%d\n", gsa_temp_struct.Satellite_Used_12);
    // printf("%.1f\n", gsa_temp_struct.PDOP);
    // printf("%.1f\n", gsa_temp_struct.HDOP);
    // printf("%.1f\n", gsa_temp_struct.VDOP);
    // printf("%s\n", gsa_temp_struct.Str_Checksum);

    char *pGSA_Message_ID = &GSA_Message_ID[0];
    char *pGSA_Checksum = &GSA_Checksum[0];

    char *pGSA_Struct_Message_ID = &gsa_temp_struct.Message_ID[0];
    char *pGSA_Struct_Checksum = &gsa_temp_struct.Str_Checksum[0];

    if(strcmp(pGSA_Message_ID, pGSA_Struct_Message_ID) == 0){
        printf("GSA Message ID validated\n");

        if(strcmp(pGSA_Checksum, pGSA_Struct_Checksum) == 0){
            printf("GSA Checksum validated\n");
            nmea->GSA = gsa_temp_struct;
        }
    }

}


void GSV_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    GSV_Struct_t gsv_temp_struct;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(gsv_temp_struct.Message_ID, token);

    /* Extract Number of Message */
    token = strtok(0, ",");
    gsv_temp_struct.Number_of_Message = atoi(token);

    /* Extract Message Number */
    token = strtok(0, ",");
    gsv_temp_struct.Message_Number = atoi(token);

    /* Extract Satellites in View */
    token = strtok(0, ",");
    gsv_temp_struct.Satellites_in_View = atoi(token);

    /* Extract Satellite-1 ID | Channel 1 (Range 1 to 32) */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_1_ID = atoi(token);

    /* Extract Satellite-1 Elevation | Channel 1 (Maximum 90) degrees */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_1_Elevation = atoi(token);

    /* Extract Satellite-1 Azimuth | Channel 1 (True, Range 0 to 359) degrees */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_1_Azimuth = atoi(token);

    /* Extract Satellite-1 SNR | Range 0 to 99, null when not tracking dBHZ*/
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_1_SNR = atoi(token);

    /* Extract Satellite-2 ID | Channel 2 (Range 1 to 32) */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_2_ID = atoi(token);

    /* Extract Satellite-2 Elevation | Channel 2 (Maximum 90) degrees */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_2_Elevation = atoi(token);

    /* Extract Satellite-2 Azimuth | Channel 2 (True, Range 0 to 359) degrees */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_2_Azimuth = atoi(token);

    /* Extract Satellite-2 SNR | Range 0 to 99, null when not tracking dBHZ*/
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_2_SNR = atoi(token);

    /* Extract Satellite-3 ID | Channel 3 (Range 1 to 32) */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_3_ID = atoi(token);

    /* Extract Satellite-3 Elevation | Channel 3 (Maximum 90) degrees */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_3_Elevation = atoi(token);

    /* Extract Satellite-3 Azimuth | Channel 3 (True, Range 0 to 359) degrees */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_3_Azimuth = atoi(token);

    /* Extract Satellite-3 SNR | Range 0 to 99, null when not tracking dBHZ*/
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_3_SNR = atoi(token);

    /* Extract Satellite-4 ID | Channel 4 (Range 1 to 32) */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_4_ID = atoi(token);

    /* Extract Satellite-4 Elevation | Channel 4 (Maximum 90) degrees */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_4_Elevation = atoi(token);

    /* Extract Satellite-4 Azimuth | Channel 4 (True, Range 0 to 359) degrees */
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_4_Azimuth = atoi(token);

    /* Extract Satellite-4 SNR | Range 0 to 99, null when not tracking dBHZ*/
    token = strtok(0, ",");
    gsv_temp_struct.Satellite_4_SNR = atoi(token);

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(gsv_temp_struct.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", gsv_temp_struct.Message_ID);
    // printf("%d\n", gsv_temp_struct.Number_of_Message);
    // printf("%d\n", gsv_temp_struct.Message_Number);
    // printf("%d\n", gsv_temp_struct.Satellites_in_View);
    // printf("%d\n", gsv_temp_struct.Satellite_1_ID);
    // printf("%d\n", gsv_temp_struct.Satellite_1_Elevation);
    // printf("%d\n", gsv_temp_struct.Satellite_1_Azimuth);
    // printf("%d\n", gsv_temp_struct.Satellite_1_SNR);
    // printf("%d\n", gsv_temp_struct.Satellite_2_ID);
    // printf("%d\n", gsv_temp_struct.Satellite_2_Elevation);
    // printf("%d\n", gsv_temp_struct.Satellite_2_Azimuth);
    // printf("%d\n", gsv_temp_struct.Satellite_2_SNR);
    // printf("%d\n", gsv_temp_struct.Satellite_3_ID);
    // printf("%d\n", gsv_temp_struct.Satellite_3_Elevation);
    // printf("%d\n", gsv_temp_struct.Satellite_3_Azimuth);
    // printf("%d\n", gsv_temp_struct.Satellite_3_SNR);
    // printf("%d\n", gsv_temp_struct.Satellite_4_ID);
    // printf("%d\n", gsv_temp_struct.Satellite_4_Elevation);
    // printf("%d\n", gsv_temp_struct.Satellite_4_Azimuth);
    // printf("%d\n", gsv_temp_struct.Satellite_4_SNR);
    // printf("%s\n", gsv_temp_struct.Str_Checksum);

    char *pGSV_Message_ID = &GSV_Message_ID[0];
    char *pGSV_Checksum = &GSV_Checksum[0];

    char *pGSV_Struct_Message_ID = &gsv_temp_struct.Message_ID[0];
    char *pGSV_Struct_Checksum = &gsv_temp_struct.Str_Checksum[0];

    if(strcmp(pGSV_Message_ID, pGSV_Struct_Message_ID) == 0){
        printf("GSV Message ID validated\n");

        if(strcmp(pGSV_Checksum, pGSV_Struct_Checksum) == 0){
            printf("GSV Checksum validated\n");
            nmea->GSV = gsv_temp_struct;
        }
    }

}


void MSS_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    MSS_Struct_t mss_temp_struct;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(mss_temp_struct.Message_ID, token);

    /* Extract SS of tracked frequency | dB */
    token = strtok(0, ",");
    mss_temp_struct.Signal_Strength = atoi(token);

    /* Extract SNR of tracked frequency | dB */
    token = strtok(0, ",");
    mss_temp_struct.Signal_to_Noise_Ratio = atoi(token);

    /* Extract Satellites in View */
    token = strtok(0, ",");
    mss_temp_struct.Beacon_Frequency = atof(token);

    /* Extract bits per second */
    token = strtok(0, ",");
    mss_temp_struct.Beacon_Bit_Rate = atoi(token);

    /* Extract The channel of the beacon being used if a multi-channel beacon receiver is used. */
    token = strtok(0, ",");
    mss_temp_struct.Channel_Number = atoi(token);

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(mss_temp_struct.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", mss_temp_struct.Message_ID);
    // printf("%d\n", mss_temp_struct.Signal_Strength);
    // printf("%d\n", mss_temp_struct.Signal_to_Noise_Ratio);
    // printf("%f\n", mss_temp_struct.Beacon_Frequency);
    // printf("%d\n", mss_temp_struct.Beacon_Bit_Rate);
    // printf("%d\n", mss_temp_struct.Channel_Number);
    // printf("%s\n", mss_temp_struct.Str_Checksum);

    char *pMSS_Message_ID = &MSS_Message_ID[0];
    char *pMSS_Checksum = &MSS_Checksum[0];

    char *pMSS_Struct_Message_ID = &mss_temp_struct.Message_ID[0];
    char *pMSS_Struct_Checksum = &mss_temp_struct.Str_Checksum[0];

    if(strcmp(pMSS_Message_ID, pMSS_Struct_Message_ID) == 0){
        printf("MSS Message ID validated\n");

        if(strcmp(pMSS_Checksum, pMSS_Struct_Checksum) == 0){
            printf("MSS Checksum validated\n");
            nmea->MSS = mss_temp_struct;
        }
    }

}


void RMC_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    RMC_Struct_t rmc_temp_struct;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(rmc_temp_struct.Message_ID, token);

    /* Extract UTC Time */
    token = strtok(0, ",");
    rmc_temp_struct.UTC_Time.Time = atof(token);
    rmc_temp_struct.UTC_Time.hour = rmc_temp_struct.UTC_Time.Time / 10000;
    rmc_temp_struct.UTC_Time.min = (rmc_temp_struct.UTC_Time.Time/100) - (((int)(rmc_temp_struct.UTC_Time.Time/10000))*100);
    rmc_temp_struct.UTC_Time.sec = rmc_temp_struct.UTC_Time.Time - (((int)(rmc_temp_struct.UTC_Time.Time/100))*100);

    /* Extract Status */
    token = strtok(0, ",");
    rmc_temp_struct.Status = *token;

    /* Extract Latitude */
    token = strtok(0, ",");
    rmc_temp_struct.Location.latitude.Position = atof(token);
    rmc_temp_struct.Location.latitude.Degree = rmc_temp_struct.Location.latitude.Position / 100;
    rmc_temp_struct.Location.latitude.Minutes = rmc_temp_struct.Location.latitude.Position - (rmc_temp_struct.Location.latitude.Degree * 100);

    /* Extract N/S Indicator */
    token = strtok(0, ",");
    rmc_temp_struct.Location.NS = *token;

    /* Extract Longitude */
    token = strtok(0, ",");
    rmc_temp_struct.Location.longitude.Position = atof(token);
    rmc_temp_struct.Location.longitude.Degree = rmc_temp_struct.Location.longitude.Position / 100;
    rmc_temp_struct.Location.longitude.Minutes = rmc_temp_struct.Location.longitude.Position - (rmc_temp_struct.Location.longitude.Degree * 100);

    /* Extract E/W Indicator */
    token = strtok(0, ",");
    rmc_temp_struct.Location.EW = *token;

    /* Extract Speed Over Ground | Knots */
    token = strtok(0, ",");
    rmc_temp_struct.Speed_Over_Ground = atof(token);

    /* Extract Course Over Ground | degr */
    token = strtok(0, ",");
    rmc_temp_struct.Course_Over_Ground = atof(token);

    /* Extract Date */
    token = strtok(0, ",");
    rmc_temp_struct.UTC_Date.Date = atoi(token);
    rmc_temp_struct.UTC_Date.Day = rmc_temp_struct.UTC_Date.Date / 10000;
    rmc_temp_struct.UTC_Date.Mon = (rmc_temp_struct.UTC_Date.Date/100) - (((int)(rmc_temp_struct.UTC_Date.Date/10000))*100);
    rmc_temp_struct.UTC_Date.Yr = rmc_temp_struct.UTC_Date.Date - (((int)(rmc_temp_struct.UTC_Date.Date/100))*100);

    /* Extract Magnetic_Variation */
    token = strtok(0, ",");
    rmc_temp_struct.Magnetic_Variation = *token;

    /* Extract East_West_Indicator */
    token = strtok(0, ",");
    rmc_temp_struct.East_West_Indicator = *token;    

    /* Extract Mode */
    token = strtok(0, ",");
    rmc_temp_struct.Mode = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(rmc_temp_struct.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", rmc_temp_struct.Message_ID);
    // printf("%f\n", rmc_temp_struct.UTC_Time.Time);
    // printf("%d\n", rmc_temp_struct.UTC_Time.hour);
    // printf("%d\n", rmc_temp_struct.UTC_Time.min);
    // printf("%f\n", rmc_temp_struct.UTC_Time.sec);
    // printf("%c\n", rmc_temp_struct.Status);
    // printf("%f\n", rmc_temp_struct.Location.latitude.Position);
    // printf("%d\n", rmc_temp_struct.Location.latitude.Degree);
    // printf("%f\n", rmc_temp_struct.Location.latitude.Minutes);
    // printf("%c\n", rmc_temp_struct.Location.NS);
    // printf("%f\n", rmc_temp_struct.Location.longitude.Position);
    // printf("%d\n", rmc_temp_struct.Location.longitude.Degree);
    // printf("%f\n", rmc_temp_struct.Location.longitude.Minutes);
    // printf("%c\n", rmc_temp_struct.Location.EW);
    // printf("%f\n", rmc_temp_struct.Speed_Over_Ground);
    // printf("%f\n", rmc_temp_struct.Course_Over_Ground);
    // printf("%d\n", rmc_temp_struct.UTC_Date.Date);
    // printf("%d\n", rmc_temp_struct.UTC_Date.Day);
    // printf("%d\n", rmc_temp_struct.UTC_Date.Mon);
    // printf("%d\n", rmc_temp_struct.UTC_Date.Yr);
    // printf("%c\n", rmc_temp_struct.Magnetic_Variation);
    // printf("%c\n", rmc_temp_struct.East_West_Indicator);
    // printf("%c\n", rmc_temp_struct.Mode);
    // printf("%s\n", rmc_temp_struct.Str_Checksum);

    char *pRMC_Message_ID = &RMC_Message_ID[0];
    char *pRMC_Checksum = &RMC_Checksum[0];

    char *pRMC_Struct_Message_ID = &rmc_temp_struct.Message_ID[0];
    char *pRMC_Struct_Checksum = &rmc_temp_struct.Str_Checksum[0];

    if(strcmp(pRMC_Message_ID, pRMC_Struct_Message_ID) == 0){
        printf("RMC Message ID validated\n");

        if(strcmp(pRMC_Checksum, pRMC_Struct_Checksum) == 0){
            printf("RMC Checksum validated\n");
            nmea->RMC = rmc_temp_struct;
        }
    }

}


void VTG_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    VTG_Struct_t vtg_temp_struct;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(vtg_temp_struct.Message_ID, token);

    /* Extract Measured true heading | degree */
    token = strtok(0, ",");
    vtg_temp_struct.Course_T = atof(token);

    /* Extract Measured heading reference | True */
    token = strtok(0, ",");
    vtg_temp_struct.Reference_T = *token;

    /* Extract Measured magnetic heading | degree */
    token = strtok(0, ",");
    vtg_temp_struct.Course_M = atof(token);

    /* Extract Measured heading reference | Magnetic */
    token = strtok(0, ",");
    vtg_temp_struct.Reference_M = *token;

    /* Extract Measured horizontal speed | Knots */
    token = strtok(0, ",");
    vtg_temp_struct.Speed_Knots = atof(token);

    /* Extract Measured horizontal speed units | Knots */
    token = strtok(0, ",");
    vtg_temp_struct.Units_Knots = *token;

    /* Extract Measured horizontal speed | Km/hr */
    token = strtok(0, ",");
    vtg_temp_struct.Speed_Km_hr = atof(token);

    /* Extract Measured horizontal speed units | Km/hr */
    token = strtok(0, ",");
    vtg_temp_struct.Units_Km_hr = *token;    

    /* Extract Mode */
    token = strtok(0, ",");
    vtg_temp_struct.Mode = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(vtg_temp_struct.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", vtg_temp_struct.Message_ID);
    // printf("%f\n", vtg_temp_struct.Course_T);
    // printf("%c\n", vtg_temp_struct.Reference_T);
    // printf("%f\n", vtg_temp_struct.Course_M);
    // printf("%c\n", vtg_temp_struct.Reference_M);
    // printf("%f\n", vtg_temp_struct.Speed_Knots);
    // printf("%c\n", vtg_temp_struct.Units_Knots);
    // printf("%f\n", vtg_temp_struct.Speed_Km_hr);
    // printf("%c\n", vtg_temp_struct.Units_Km_hr);
    // printf("%c\n", vtg_temp_struct.Mode);
    // printf("%s\n", vtg_temp_struct.Str_Checksum);

    char *pVTG_Message_ID = &VTG_Message_ID[0];
    char *pVTG_Checksum = &VTG_Checksum[0];

    char *pVTG_Struct_Message_ID = &vtg_temp_struct.Message_ID[0];
    char *pVTG_Struct_Checksum = &vtg_temp_struct.Str_Checksum[0];

    if(strcmp(pVTG_Message_ID, pVTG_Struct_Message_ID) == 0){
        printf("VTG Message ID validated\n");

        if(strcmp(pVTG_Checksum, pVTG_Struct_Checksum) == 0){
            printf("VTG Checksum validated\n");
            nmea->VTG = vtg_temp_struct;
        }
    }

}


void ZDA_Structure_Update(NMEA_Data_Struct_t *nmea, char *buffer){

    char *ret;
    char *token;

    ZDA_Struct_t zda_temp_struct;

    /* Remove enytihings before message ID */
    ret = strchr(buffer, '$');
    // printf("%s\n", ret);

    /* Extract Message_ID */
    token = strtok(ret, ",");
    strcpy(zda_temp_struct.Message_ID, token);

    /* Extract UTC Time */
    token = strtok(0, ",");
    zda_temp_struct.UTC_Time.Time = atof(token);
    zda_temp_struct.UTC_Time.hour = zda_temp_struct.UTC_Time.Time / 10000;
    zda_temp_struct.UTC_Time.min = (zda_temp_struct.UTC_Time.Time/100) - (((int)(zda_temp_struct.UTC_Time.Time/10000))*100);
    zda_temp_struct.UTC_Time.sec = zda_temp_struct.UTC_Time.Time - (((int)(zda_temp_struct.UTC_Time.Time/100))*100);

    /* Extract Date */
    token = strtok(0, ",");
    zda_temp_struct.UTC_Date.Day = atoi(token);
    token = strtok(0, ",");
    zda_temp_struct.UTC_Date.Mon = atoi(token);
    token = strtok(0, ",");
    zda_temp_struct.UTC_Date.Yr = atoi(token);

    /* Extract Local_Zone */
    token = strtok(0, ",");
    zda_temp_struct.Local_Zone.hour = *token;
    token = strtok(0, ",");
    zda_temp_struct.Local_Zone.minutes = *token;

    /* Extract Checksum */
    ret = strchr(token, '*');
    strcpy(zda_temp_struct.Str_Checksum, ret);

    /*  Print GGA Structure information
        If you need to check Structure value in "C" language so you can uncomment below lines.
    */
    // printf("%s\n", zda_temp_struct.Message_ID);
    // printf("%f\n", zda_temp_struct.UTC_Time.Time);
    // printf("%d\n", zda_temp_struct.UTC_Time.hour);
    // printf("%d\n", zda_temp_struct.UTC_Time.min);
    // printf("%f\n", zda_temp_struct.UTC_Time.sec);
    // printf("%d\n", zda_temp_struct.UTC_Date.Day);
    // printf("%d\n", zda_temp_struct.UTC_Date.Mon);
    // printf("%d\n", zda_temp_struct.UTC_Date.Yr);
    // printf("%d\n", zda_temp_struct.Local_Zone.hour);
    // printf("%d\n", zda_temp_struct.Local_Zone.minutes);
    // printf("%s\n", zda_temp_struct.Str_Checksum);

    char *pZDA_Message_ID = &ZDA_Message_ID[0];
    char *pZDA_Checksum = &ZDA_Checksum[0];

    char *pZDA_Struct_Message_ID = &zda_temp_struct.Message_ID[0];
    char *pZDA_Struct_Checksum = &zda_temp_struct.Str_Checksum[0];

    if(strcmp(pZDA_Message_ID, pZDA_Struct_Message_ID) == 0){
        printf("ZDA Message ID validated\n");

        if(strcmp(pZDA_Checksum, pZDA_Struct_Checksum) == 0){
            printf("ZDA Checksum validated\n");
            nmea->ZDA = zda_temp_struct;
        }
    }

}

