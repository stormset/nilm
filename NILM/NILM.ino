#include <ADS1220_WE.h>
#include <WCS.h>
#include <ZMPT101B.h>
#include <SPI.h>

#define ADS1220_CS_PIN   5 // CS pin
#define ADS1220_DRDY_PIN 2 // data ready pin
#define ZMPT_PIN 32        // ZMPT101B pin (onboard DAC)
#define ZMPT_SENS 0.019    // ZMPT101B sensitivity
#define AC_FREQ   50       // AC frequency (Hz)

float readADS1220();
float readZMPT();

ADS1220_WE ads = ADS1220_WE(ADS1220_CS_PIN, ADS1220_DRDY_PIN);
WCS WCS1 = WCS(readADS1220, _WCS1800);
ZMPT101B zmpt = ZMPT101B(readZMPT, ZMPT_SENS);

void setup(){
    Serial.begin(115200);
    if(!ads.init()){
        Serial.println("ADS1220 is not connected!");
        while(1);
    }

    /* ADC settings */
    ads.setConversionMode(ADS1220_CONTINUOUS);   // do not wait for conversion request (do it as soon as previous finished)
    ads.setDataRate(ADS1220_DR_LVL_6);           // set highest data rate (2 kSPS when in TURBO mode)
    ads.setOperatingMode(ADS1220_TURBO_MODE);    // set TURBO mode
    delay(3000);
    ads.setAvddAvssAsVrefAndCalibrate();         // use external voltage source (voltage response of the CT is highly dependent on Vin)
    ads.setCompareChannels(ADS1220_MUX_0_AVSS);  // inputs: AIN1, AVSS  mode: single-ended (not differential) 

    /* Calibration */
    delay(1000);
    WCS1.Reset();
    zmpt.Reset();    
    delay(2000);
}

void loop() {
    // dump readings to serial
    Serial.println(WCS1.getCurrentAC() * zmpt.getVoltageAC(AC_FREQ, ads.getVRef_V()));
}

// reads and returns value read by ADS1220 (connected to WCS1800)
float readADS1220() {
    return ads.getVoltage_mV();
}

// reads and returns value read by internal ADC (connected to ZMPT101B)
float readZMPT() {
    return analogRead(ZMPT_PIN);
}
