/*
 * This is a small library to create a .gpx file on an SD Card to fastly insert it into a
 * GPX Visualizer
 *
 * You will need the TinyGPS++ Library and the SD Card Library installed because this library
 * does all the Job with writing down all the Data
 *
 * author : SL7
 * version : v0.1
 */

#include "Arduino.h"
#include "TinyGPS++.h"
#include "SD.h"

/*
enum timezones {
	TZ_GMT = "UTC+0", TZ_ADT = "UTC-3", TZ_AET = "UTC+11",
	TZ_MEZ = "UTC+1", TZ_CAT = "UTC+2", TZ_CET = "UTC+1",
	TZ_CST = "UTC-6", TZ_EAT = "UTC+3", TZ_EDT = "UTC-5",
	TZ_EET = "UTC+2", TZ_EST = "UTC-5", TZ_ET = "UTC-5",
	TZ_HKT = "UTC+8", TZ_HST = "UTC-10", TZ_JST = "UTC+9",
	TZ_MST = "UTC-7", TZ_PT = "UTC-8"
};

*/

enum data_mode
{
    MODE1 = 0,
    MODE2 = 1,
    MODE3 = 2
};

enum write_delay
{
    NO_DELAY = 0,
    DELAY_2IT = 2000,
    DELAY_3IT = 3000,
    DELAY_4IT = 4000,
    DELAY_5IT = 5000
};

struct data
{
    float lat;
    float lng;
    int alt;
    String date;
};

class GPX;

class GPX
{
public:
    File file;
    int mode;
    bool isvalidFile = false;
    bool isclosedFile = true;
    String foldername;

    String base_struct_start[5] = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n",
        "<gpx version=\"1.1\" creator=\"$USER\">\n",
        "  <metadata> <!-- Metadaten --> </metadata>\n",
        "  <trk>\n",
        "    <trkseg>\n"};

    String base_struct_end[3] = {
        "    </trkseg>\n",
        "  </trk>\n",
        "</gpx>\n"};
    //timezones zone;

    void init(String foldername, write_delay delay, data_mode mode);
    bool gotGPSLock(HardwareSerial GPSSerial, TinyGPSPlus gps);
    String setFile(File file);
    void write(TinyGPSPlus gps);
    void close(void);
};
