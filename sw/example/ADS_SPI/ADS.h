/**********************************************************************//**
 * @file ADS_SPI/ADS.h
 * @brief header file for firmware to interface with an ADS1220 ADC
 **************************************************************************/

//ADS1220 SPI commands

/**
    List of Byte Commands for the ADS1220
*/
typedef enum ADS1220_COMMAND {
    RESET       = 0x06,
    START       = 0x08,
    POWERDOWN   = 0x02,
    RDATA       = 0x10,
    RREG        = 0x20, //serves as mask for format 0b0010rrnn
    WREG        = 0x40  //serves as mask for format 0b0100rrnn
}   ADS1220_COMMAND;

typedef enum ADS1220_MUX {
    ADS1220_MUX_0_1     = 0x00,   //default
    ADS1220_MUX_0_2     = 0x10,
    ADS1220_MUX_0_3     = 0x20,
    ADS1220_MUX_1_2     = 0x30,
    ADS1220_MUX_1_3     = 0x40,
    ADS1220_MUX_2_3     = 0x50,
    ADS1220_MUX_1_0     = 0x60,
    ADS1220_MUX_3_2     = 0x70,
    ADS1220_MUX_0_AVSS  = 0x80,
    ADS1220_MUX_1_AVSS  = 0x90,
    ADS1220_MUX_2_AVSS  = 0xA0,
    ADS1220_MUX_3_AVSS  = 0xB0,
    ADS1220_MUX_REFPX_REFNX_4 = 0xC0,
    ADS1220_MUX_AVDD_M_AVSS_4 = 0xD0,
    ADS1220_MUX_AVDD_P_AVSS_2 = 0xE0
} ads1220Mux;

typedef enum ADS1220_GAIN {
    ADS1220_GAIN_1   = 0x00,   //default
    ADS1220_GAIN_2   = 0x02,
    ADS1220_GAIN_4   = 0x04,
    ADS1220_GAIN_8   = 0x06,
    ADS1220_GAIN_16  = 0x08,
    ADS1220_GAIN_32  = 0x0A,
    ADS1220_GAIN_64  = 0x0C,
    ADS1220_GAIN_128 = 0x0E
} ads1220Gain;

typedef enum ADS1220_DATA_RATE {
    ADS1220_DR_LVL_0 = 0x00,   // default
    ADS1220_DR_LVL_1 = 0x20,
    ADS1220_DR_LVL_2 = 0x40,
    ADS1220_DR_LVL_3 = 0x60,
    ADS1220_DR_LVL_4 = 0x80,
    ADS1220_DR_LVL_5 = 0xA0,
    ADS1220_DR_LVL_6 = 0xC0
} ads1220DataRate;

typedef enum ADS1220_OP_MODE {      
    ADS1220_NORMAL_MODE     = 0x00,  // default
    ADS1220_DUTY_CYCLE_MODE = 0x08,
    ADS1220_TURBO_MODE      = 0x10
} ads1220OpMode;


typedef enum ADS1220_CONV_MODE {
    ADS1220_SINGLE_SHOT     = 0x00,  // default
    ADS1220_CONTINUOUS      = 0x04
} ads1220ConvMode;

typedef enum ADS1220_VREF{
    ADS1220_VREF_INT            = 0x00,  // default
    ADS1220_VREF_REFP0_REFN0    = 0x40,
    ADS1220_VREF_REFP1_REFN1    = 0x80,
    ADS1220_VREF_AVDD_AVSS      = 0xC0
} ads1220VRef;

typedef enum ADS1220_FIR{
    ADS1220_NONE        = 0x00,   // default
    ADS1220_50HZ_60HZ   = 0x10,
    ADS1220_50HZ        = 0x20,
    ADS1220_60HZ        = 0x30
} ads1220FIR;

typedef enum ADS1220_PSW {
    ADS1220_ALWAYS_OPEN = 0x00,  // default
    ADS1220_SWITCH      = 0x08
} ads1220PSW;

typedef enum ADS1220_IDAC_CURRENT {
    ADS1220_IDAC_OFF        = 0x00,  // defaulr
    ADS1220_IDAC_10_MU_A    = 0x01,
    ADS1220_IDAC_50_MU_A    = 0x02,
    ADS1220_IDAC_100_MU_A   = 0x03,
    ADS1220_IDAC_250_MU_A   = 0x04,
    ADS1220_IDAC_500_MU_A   = 0x05,
    ADS1220_IDAC_1000_MU_A  = 0x06,
    ADS1220_IDAC_1500_MU_A  = 0x07
} ads1220IdacCurrent;

typedef enum ADS1220_IDAC_ROUTING {
    ADS1220_IDAC_NONE       = 0x00,  // default
    ADS1220_IDAC_AIN0_REFP1 = 0x01,
    ADS1220_IDAC_AIN1       = 0x02,
    ADS1220_IDAC_AIN2       = 0x03,
    ADS1220_IDAC_AIN3_REFN1 = 0x04,
    ADS1220_IDAC_REFP0      = 0x05,
    ADS1220_IDAC_REFN0      = 0x06,
} ads1220IdacRouting;

typedef enum ADS1220_DRDY_MODE {
    ADS1220_DRDY      = 0x00,   // default
    ADS1220_DOUT_DRDY = 0x02
} ads1220DrdyMode;