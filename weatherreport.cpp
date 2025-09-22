#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SensorReadings {
    int temperatureInC;
    int precipitation;
    int humidity;
    int windSpeedKMPH;
};

// This is a stub for a weather sensor. For the sake of testing 
// we create a stub that generates weather data and allows us to
// test the other parts of this application in isolation
// without needing the actual Sensor during development

struct SensorReadings sensorStub() {
    struct SensorReadings readings;
    readings.temperatureInC = 50;
    readings.precipitation = 70;
    readings.humidity = 26;
    readings.windSpeedKMPH = 52;
    return readings;
}

// Custom sensor stub for rainy conditions testing
struct SensorReadings rainySensorStub() {
    struct SensorReadings readings;
    readings.temperatureInC = 30;
    readings.precipitation = 50; // between 20 and 60
    readings.humidity = 80;
    readings.windSpeedKMPH = 30; // below 50
    return readings;
}

// Custom sensor stub for high precipitation but low wind
struct SensorReadings highPrecipLowWindStub() {
    struct SensorReadings readings;
    readings.temperatureInC = 30;  // > 25
    readings.precipitation = 70;   // >= 60
    readings.humidity = 85;
    readings.windSpeedKMPH = 30;   // < 50
    return readings;
}

char* report(struct SensorReadings (*sensorReader)()) {
    size_t bufsize = 50;
    char* weather = (char*)malloc(bufsize);
    if (!weather) return NULL;
    struct SensorReadings readings = sensorReader();
    const char* weatherStr = "Sunny Day";
    if (readings.temperatureInC > 25) {
        if (readings.precipitation >= 20 && readings.precipitation < 60) {
            weatherStr = "Partly Cloudy";
        } else if (readings.windSpeedKMPH > 50) {
            weatherStr = "Alert, Stormy with heavy rain";
        } else if (readings.precipitation >= 60) {
            weatherStr = "Heavy rain expected";
        }
    }
    snprintf(weather, bufsize, "%s", weatherStr);
    return weather;
}

void testRainy() {
    char* weather = report(sensorStub);
    printf("Weather from default stub: %s\n", weather);
    int hasRain = (weather && strstr(weather, "rain") != NULL);
    if (!hasRain) {
        printf("ERROR: Weather report should contain 'rain' for stormy conditions\n");
    }
    free(weather);
    // Return the check result to use with the gtest framework
}

void testHighPrecipitation() {
    // This instance of stub gives high precipitation (>60) and low wind-speed (<50)
    char* weather = report(highPrecipLowWindStub);
    printf("Weather from high precip stub: %s\n", weather);
    int hasRain = (weather && strstr(weather, "rain") != NULL);
    if (!hasRain) {
        printf("ERROR: Weather report should contain 'rain' for high precipitation\n");
    }
    free(weather);
    // Return the check result to use with the gtest framework
}

int testWeatherReport() {
    printf("\nWeather report test\n");
    int passed = 1;
    
    // Test stormy weather (high wind)
    char* weather1 = report(sensorStub);
    int hasRain1 = (weather1 && strstr(weather1, "rain") != NULL);
    printf("Stormy weather test: %s\n", weather1);
    if (!hasRain1) {
        printf("ERROR: Weather report should contain 'rain' for stormy conditions\n");
        passed = 0;
    }
    free(weather1);
    
    // Test high precipitation (low wind)
    char* weather2 = report(highPrecipLowWindStub);
    int hasRain2 = (weather2 && strstr(weather2, "rain") != NULL);
    printf("High precipitation test: %s\n", weather2);
    if (!hasRain2) {
        printf("ERROR: Weather report should contain 'rain' for high precipitation\n");
        passed = 0;
    }
    free(weather2);
    
    if (passed) {
        printf("All is well (maybe!)\n");
    } else {
        printf("FAILED: Weather reporting has issues\n");
    }
    
    return passed;
}