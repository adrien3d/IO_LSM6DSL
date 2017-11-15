/***************************************************************************
  This is a library for the LSM6DSL humidity, temperature & pressure sensor

  Designed to work with all kinds of LSM6DSL Breakout

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Written by Adrien Chapelet for IoThings
 ***************************************************************************/

#ifndef __LSM6DSL_H__
#define __LSM6DSL_H__

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

/************** I2C Address *****************/

#define LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW   0xD4  // SAD[0] = 0
#define LSM6DSL_ACC_GYRO_I2C_ADDRESS_HIGH  0xD6  // SAD[0] = 1

/************** Who am I  *******************/

#define LSM6DSL_ACC_GYRO_WHO_AM_I         0x6A

/************** Device Register  *******************/

#define LSM6DSL_ACC_GYRO_FUNC_CFG_ACCESS    0X01

#define LSM6DSL_ACC_GYRO_SENSOR_SYNC_TIME   0X04
#define LSM6DSL_ACC_GYRO_SENSOR_RES_RATIO   0X05

#define LSM6DSL_ACC_GYRO_FIFO_CTRL1   0X06
#define LSM6DSL_ACC_GYRO_FIFO_CTRL2   0X07
#define LSM6DSL_ACC_GYRO_FIFO_CTRL3   0X08
#define LSM6DSL_ACC_GYRO_FIFO_CTRL4   0X09
#define LSM6DSL_ACC_GYRO_FIFO_CTRL5   0X0A

#define LSM6DSL_ACC_GYRO_DRDY_PULSE_CFG_G   0X0B
#define LSM6DSL_ACC_GYRO_INT1_CTRL    0X0D
#define LSM6DSL_ACC_GYRO_INT2_CTRL    0X0E
#define LSM6DSL_ACC_GYRO_WHO_AM_I_REG   0X0F
#define LSM6DSL_ACC_GYRO_CTRL1_XL   0X10
#define LSM6DSL_ACC_GYRO_CTRL2_G    0X11
#define LSM6DSL_ACC_GYRO_CTRL3_C    0X12
#define LSM6DSL_ACC_GYRO_CTRL4_C    0X13
#define LSM6DSL_ACC_GYRO_CTRL5_C    0X14
#define LSM6DSL_ACC_GYRO_CTRL6_G    0X15
#define LSM6DSL_ACC_GYRO_CTRL7_G    0X16
#define LSM6DSL_ACC_GYRO_CTRL8_XL   0X17
#define LSM6DSL_ACC_GYRO_CTRL9_XL   0X18
#define LSM6DSL_ACC_GYRO_CTRL10_C   0X19

#define LSM6DSL_ACC_GYRO_MASTER_CONFIG    0X1A
#define LSM6DSL_ACC_GYRO_WAKE_UP_SRC    0X1B
#define LSM6DSL_ACC_GYRO_TAP_SRC    0X1C
#define LSM6DSL_ACC_GYRO_D6D_SRC    0X1D
#define LSM6DSL_ACC_GYRO_STATUS_REG   0X1E

#define LSM6DSL_ACC_GYRO_OUT_TEMP_L   0X20
#define LSM6DSL_ACC_GYRO_OUT_TEMP_H   0X21
#define LSM6DSL_ACC_GYRO_OUTX_L_G   0X22
#define LSM6DSL_ACC_GYRO_OUTX_H_G   0X23
#define LSM6DSL_ACC_GYRO_OUTY_L_G   0X24
#define LSM6DSL_ACC_GYRO_OUTY_H_G   0X25
#define LSM6DSL_ACC_GYRO_OUTZ_L_G   0X26
#define LSM6DSL_ACC_GYRO_OUTZ_H_G   0X27
#define LSM6DSL_ACC_GYRO_OUTX_L_XL    0X28
#define LSM6DSL_ACC_GYRO_OUTX_H_XL    0X29
#define LSM6DSL_ACC_GYRO_OUTY_L_XL    0X2A
#define LSM6DSL_ACC_GYRO_OUTY_H_XL    0X2B
#define LSM6DSL_ACC_GYRO_OUTZ_L_XL    0X2C
#define LSM6DSL_ACC_GYRO_OUTZ_H_XL    0X2D
#define LSM6DSL_ACC_GYRO_SENSORHUB1_REG   0X2E
#define LSM6DSL_ACC_GYRO_SENSORHUB2_REG   0X2F
#define LSM6DSL_ACC_GYRO_SENSORHUB3_REG   0X30
#define LSM6DSL_ACC_GYRO_SENSORHUB4_REG   0X31
#define LSM6DSL_ACC_GYRO_SENSORHUB5_REG   0X32
#define LSM6DSL_ACC_GYRO_SENSORHUB6_REG   0X33
#define LSM6DSL_ACC_GYRO_SENSORHUB7_REG   0X34
#define LSM6DSL_ACC_GYRO_SENSORHUB8_REG   0X35
#define LSM6DSL_ACC_GYRO_SENSORHUB9_REG   0X36
#define LSM6DSL_ACC_GYRO_SENSORHUB10_REG    0X37
#define LSM6DSL_ACC_GYRO_SENSORHUB11_REG    0X38
#define LSM6DSL_ACC_GYRO_SENSORHUB12_REG    0X39
#define LSM6DSL_ACC_GYRO_FIFO_STATUS1   0X3A
#define LSM6DSL_ACC_GYRO_FIFO_STATUS2   0X3B
#define LSM6DSL_ACC_GYRO_FIFO_STATUS3   0X3C
#define LSM6DSL_ACC_GYRO_FIFO_STATUS4   0X3D
#define LSM6DSL_ACC_GYRO_FIFO_DATA_OUT_L    0X3E
#define LSM6DSL_ACC_GYRO_FIFO_DATA_OUT_H    0X3F
#define LSM6DSL_ACC_GYRO_TIMESTAMP0_REG   0X40
#define LSM6DSL_ACC_GYRO_TIMESTAMP1_REG   0X41
#define LSM6DSL_ACC_GYRO_TIMESTAMP2_REG   0X42

#define LSM6DSL_ACC_GYRO_TIMESTAMP_L    0X49
#define LSM6DSL_ACC_GYRO_TIMESTAMP_H    0X4A

#define LSM6DSL_ACC_GYRO_STEP_COUNTER_L   0X4B
#define LSM6DSL_ACC_GYRO_STEP_COUNTER_H   0X4C

#define LSM6DSL_ACC_GYRO_SENSORHUB13_REG    0X4D
#define LSM6DSL_ACC_GYRO_SENSORHUB14_REG    0X4E
#define LSM6DSL_ACC_GYRO_SENSORHUB15_REG    0X4F
#define LSM6DSL_ACC_GYRO_SENSORHUB16_REG    0X50
#define LSM6DSL_ACC_GYRO_SENSORHUB17_REG    0X51
#define LSM6DSL_ACC_GYRO_SENSORHUB18_REG    0X52

#define LSM6DSL_ACC_GYRO_FUNC_SRC   0X53
#define LSM6DSL_ACC_GYRO_TAP_CFG1   0X58
#define LSM6DSL_ACC_GYRO_TAP_THS_6D   0X59
#define LSM6DSL_ACC_GYRO_INT_DUR2   0X5A
#define LSM6DSL_ACC_GYRO_WAKE_UP_THS    0X5B
#define LSM6DSL_ACC_GYRO_WAKE_UP_DUR    0X5C
#define LSM6DSL_ACC_GYRO_FREE_FALL    0X5D
#define LSM6DSL_ACC_GYRO_MD1_CFG    0X5E
#define LSM6DSL_ACC_GYRO_MD2_CFG    0X5F

#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_X_L    0X66
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_X_H    0X67
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_Y_L    0X68
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_Y_H    0X69
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_Z_L    0X6A
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_Z_H    0X6B

#define LSM6DSL_ACC_GYRO_X_OFS_USR    0X73
#define LSM6DSL_ACC_GYRO_Y_OFS_USR    0X74
#define LSM6DSL_ACC_GYRO_Z_OFS_USR    0X75

/************** Embedded functions register mapping  *******************/
#define LSM6DSL_ACC_GYRO_SLV0_ADD                     0x02
#define LSM6DSL_ACC_GYRO_SLV0_SUBADD                  0x03
#define LSM6DSL_ACC_GYRO_SLAVE0_CONFIG                0x04
#define LSM6DSL_ACC_GYRO_SLV1_ADD                     0x05
#define LSM6DSL_ACC_GYRO_SLV1_SUBADD                  0x06
#define LSM6DSL_ACC_GYRO_SLAVE1_CONFIG                0x07
#define LSM6DSL_ACC_GYRO_SLV2_ADD                     0x08
#define LSM6DSL_ACC_GYRO_SLV2_SUBADD                  0x09
#define LSM6DSL_ACC_GYRO_SLAVE2_CONFIG                0x0A
#define LSM6DSL_ACC_GYRO_SLV3_ADD                     0x0B
#define LSM6DSL_ACC_GYRO_SLV3_SUBADD                  0x0C
#define LSM6DSL_ACC_GYRO_SLAVE3_CONFIG                0x0D
#define LSM6DSL_ACC_GYRO_DATAWRITE_SRC_MODE_SUB_SLV0  0x0E
#define LSM6DSL_ACC_GYRO_CONFIG_PEDO_THS_MIN          0x0F

#define LSM6DSL_ACC_GYRO_SM_STEP_THS                  0x13
#define LSM6DSL_ACC_GYRO_PEDO_DEB_REG                0x14
#define LSM6DSL_ACC_GYRO_STEP_COUNT_DELTA            0x15

#define LSM6DSL_ACC_GYRO_MAG_SI_XX                    0x24
#define LSM6DSL_ACC_GYRO_MAG_SI_XY                    0x25
#define LSM6DSL_ACC_GYRO_MAG_SI_XZ                    0x26
#define LSM6DSL_ACC_GYRO_MAG_SI_YX                    0x27
#define LSM6DSL_ACC_GYRO_MAG_SI_YY                    0x28
#define LSM6DSL_ACC_GYRO_MAG_SI_YZ                    0x29
#define LSM6DSL_ACC_GYRO_MAG_SI_ZX                    0x2A
#define LSM6DSL_ACC_GYRO_MAG_SI_ZY                    0x2B
#define LSM6DSL_ACC_GYRO_MAG_SI_ZZ                    0x2C
#define LSM6DSL_ACC_GYRO_MAG_OFFX_L                   0x2D
#define LSM6DSL_ACC_GYRO_MAG_OFFX_H                   0x2E
#define LSM6DSL_ACC_GYRO_MAG_OFFY_L                   0x2F
#define LSM6DSL_ACC_GYRO_MAG_OFFY_H                   0x30
#define LSM6DSL_ACC_GYRO_MAG_OFFZ_L                   0x31
#define LSM6DSL_ACC_GYRO_MAG_OFFZ_H                   0x32
/* End of registers -----------------------------------------------------*/

#define LSM6DSL_ACC_SENSITIVITY_FOR_FS_2G   0.061  /**< Sensitivity value for 2 g full scale [mg/LSB] */
#define LSM6DSL_ACC_SENSITIVITY_FOR_FS_4G   0.122  /**< Sensitivity value for 4 g full scale [mg/LSB] */
#define LSM6DSL_ACC_SENSITIVITY_FOR_FS_8G   0.244  /**< Sensitivity value for 8 g full scale [mg/LSB] */
#define LSM6DSL_ACC_SENSITIVITY_FOR_FS_16G  0.488  /**< Sensitivity value for 16 g full scale [mg/LSB] */

#define LSM6DSL_GYRO_SENSITIVITY_FOR_FS_125DPS   04.375  /**< Sensitivity value for 125 dps full scale [mdps/LSB] */
#define LSM6DSL_GYRO_SENSITIVITY_FOR_FS_245DPS   08.750  /**< Sensitivity value for 245 dps full scale [mdps/LSB] */
#define LSM6DSL_GYRO_SENSITIVITY_FOR_FS_500DPS   17.500  /**< Sensitivity value for 500 dps full scale [mdps/LSB] */
#define LSM6DSL_GYRO_SENSITIVITY_FOR_FS_1000DPS  35.000  /**< Sensitivity value for 1000 dps full scale [mdps/LSB] */
#define LSM6DSL_GYRO_SENSITIVITY_FOR_FS_2000DPS  70.000  /**< Sensitivity value for 2000 dps full scale [mdps/LSB] */

#define LSM6DSL_PEDOMETER_THRESHOLD_LOW       0x00  /**< Lowest  value of pedometer threshold */
#define LSM6DSL_PEDOMETER_THRESHOLD_MID_LOW   0x07
#define LSM6DSL_PEDOMETER_THRESHOLD_MID       0x0F
#define LSM6DSL_PEDOMETER_THRESHOLD_MID_HIGH  0x17
#define LSM6DSL_PEDOMETER_THRESHOLD_HIGH      0x1F  /**< Highest value of pedometer threshold */

#define LSM6DSL_WAKE_UP_THRESHOLD_LOW       0x01  /**< Lowest  value of wake up threshold */
#define LSM6DSL_WAKE_UP_THRESHOLD_MID_LOW   0x0F
#define LSM6DSL_WAKE_UP_THRESHOLD_MID       0x1F
#define LSM6DSL_WAKE_UP_THRESHOLD_MID_HIGH  0x2F
#define LSM6DSL_WAKE_UP_THRESHOLD_HIGH      0x3F  /**< Highest value of wake up threshold */

#define LSM6DSL_TAP_THRESHOLD_LOW       0x01  /**< Lowest  value of wake up threshold */
#define LSM6DSL_TAP_THRESHOLD_MID_LOW   0x08
#define LSM6DSL_TAP_THRESHOLD_MID       0x10
#define LSM6DSL_TAP_THRESHOLD_MID_HIGH  0x18
#define LSM6DSL_TAP_THRESHOLD_HIGH      0x1F  /**< Highest value of wake up threshold */

#define LSM6DSL_TAP_SHOCK_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define LSM6DSL_TAP_SHOCK_TIME_MID_LOW   0x01
#define LSM6DSL_TAP_SHOCK_TIME_MID_HIGH  0x02
#define LSM6DSL_TAP_SHOCK_TIME_HIGH      0x03  /**< Highest value of wake up threshold */

#define LSM6DSL_TAP_QUIET_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define LSM6DSL_TAP_QUIET_TIME_MID_LOW   0x01
#define LSM6DSL_TAP_QUIET_TIME_MID_HIGH  0x02
#define LSM6DSL_TAP_QUIET_TIME_HIGH      0x03  /**< Highest value of wake up threshold */

#define LSM6DSL_TAP_DURATION_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define LSM6DSL_TAP_DURATION_TIME_MID_LOW   0x04
#define LSM6DSL_TAP_DURATION_TIME_MID       0x08
#define LSM6DSL_TAP_DURATION_TIME_MID_HIGH  0x0C
#define LSM6DSL_TAP_DURATION_TIME_HIGH      0x0F  /**< Highest value of wake up threshold */

/* Typedefs ------------------------------------------------------------------*/
typedef enum
{
  LSM6DSL_STATUS_OK = 0,
  LSM6DSL_STATUS_ERROR,
  LSM6DSL_STATUS_TIMEOUT,
  LSM6DSL_STATUS_NOT_IMPLEMENTED
} LSM6DSLStatusTypeDef;

typedef enum
{
  LSM6DSL_INT1_PIN,
  LSM6DSL_INT2_PIN
} LSM6DSL_Interrupt_Pin_t;

typedef struct
{
  unsigned int FreeFallStatus : 1;
  unsigned int TapStatus : 1;
  unsigned int DoubleTapStatus : 1;
  unsigned int WakeUpStatus : 1;
  unsigned int StepStatus : 1;
  unsigned int TiltStatus : 1;
  unsigned int D6DOrientationStatus : 1;
} LSM6DSL_Event_Status_t;

typedef enum {
  LSM6DSL_ACC_ACT_GYR_DWN = 0;
  LSM6DSL_ACC_DWN_GYR_ACT = 0;
  LSM6DSL_ACC_ACT_GYR_ACT = 0;
} LSM6DSL_Operating_Modes_t;

typedef enum {
  LSM6DSL_POWER_DOWN = 0;
  LSM6DSL_LOW_POWER = 1;
  LSM6DSL_NORMAL = 2;
  LSM6DSL_HGH_PERFORMANCE = 3;
} LSM6DSL_Acc_Power_Modes_t;

typedef enum {
  LSM6DSL_POWER_DOWN = 0;
  LSM6DSL_LOW_POWER = 1;
  LSM6DSL_NORMAL = 2;
  LSM6DSL_HGH_PERFORMANCE = 3;
} LSM6DSL_Gyr_Power_Modes_t;

typedef enum {
    LSM6DSL_ACC_GYRO_FS_XL_2g      =0x00,
    LSM6DSL_ACC_GYRO_FS_XL_16g     =0x04,
    LSM6DSL_ACC_GYRO_FS_XL_4g      =0x08,
    LSM6DSL_ACC_GYRO_FS_XL_8g      =0x0C,
} LSM6DSL_ACC_GYRO_FS_XL_t;

typedef enum {
    LSM6DSL_ACC_GYRO_ODR_XL_POWER_DOWN     =0x00,
    LSM6DSL_ACC_GYRO_ODR_XL_13Hz     =0x10,
    LSM6DSL_ACC_GYRO_ODR_XL_26Hz     =0x20,
    LSM6DSL_ACC_GYRO_ODR_XL_52Hz     =0x30,
    LSM6DSL_ACC_GYRO_ODR_XL_104Hz      =0x40,
    LSM6DSL_ACC_GYRO_ODR_XL_208Hz      =0x50,
    LSM6DSL_ACC_GYRO_ODR_XL_416Hz      =0x60,
    LSM6DSL_ACC_GYRO_ODR_XL_833Hz      =0x70,
    LSM6DSL_ACC_GYRO_ODR_XL_1660Hz     =0x80,
    LSM6DSL_ACC_GYRO_ODR_XL_3330Hz     =0x90,
    LSM6DSL_ACC_GYRO_ODR_XL_6660Hz     =0xA0,
} LSM6DSL_ACC_GYRO_ODR_XL_t;

typedef enum {
    LSM6DSL_ACC_GYRO_FS_G_245dps     =0x00,
    LSM6DSL_ACC_GYRO_FS_G_500dps     =0x04,
    LSM6DSL_ACC_GYRO_FS_G_1000dps      =0x08,
    LSM6DSL_ACC_GYRO_FS_G_2000dps      =0x0C,
} LSM6DSL_ACC_GYRO_FS_G_t;

typedef enum {
    LSM6DSL_ACC_GYRO_ODR_G_POWER_DOWN      =0x00,
    LSM6DSL_ACC_GYRO_ODR_G_13Hz      =0x10,
    LSM6DSL_ACC_GYRO_ODR_G_26Hz      =0x20,
    LSM6DSL_ACC_GYRO_ODR_G_52Hz      =0x30,
    LSM6DSL_ACC_GYRO_ODR_G_104Hz     =0x40,
    LSM6DSL_ACC_GYRO_ODR_G_208Hz     =0x50,
    LSM6DSL_ACC_GYRO_ODR_G_416Hz     =0x60,
    LSM6DSL_ACC_GYRO_ODR_G_833Hz     =0x70,
    LSM6DSL_ACC_GYRO_ODR_G_1660Hz      =0x80,
    LSM6DSL_ACC_GYRO_ODR_G_3330Hz      =0x90,
    LSM6DSL_ACC_GYRO_ODR_G_6660Hz      =0xA0,
} LSM6DSL_ACC_GYRO_ODR_G_t;

typedef enum {
    LSM6DSL_ACC_GYRO_EMBEDDED_ACCESS_DISABLED      =0x00,
    LSM6DSL_ACC_GYRO_EMBEDDED_ACCESS_ENABLED     =0x80,
} LSM6DSL_ACC_GYRO_EMB_ACC_t;

typedef enum {
    LSM6DSL_ACC_GYRO_FIFO_TEMP_DISABLE     =0x00,
    LSM6DSL_ACC_GYRO_FIFO_TEMP_ENABLE      =0x08,
} LSM6DSL_ACC_GYRO_FIFO_TEMP_t;

typedef enum {
    LSM6DSL_ACC_GYRO_TIM_PEDO_FIFO_DRDY_DISABLED     =0x00,
    LSM6DSL_ACC_GYRO_TIM_PEDO_FIFO_DRDY_ENABLED      =0x40,
} LSM6DSL_ACC_GYRO_TIM_PEDO_FIFO_DRDY_t;

typedef enum {
    LSM6DSL_ACC_GYRO_TIM_PEDO_FIFO_EN_DISABLED     =0x00,
    LSM6DSL_ACC_GYRO_TIM_PEDO_FIFO_EN_ENABLED      =0x80,
} LSM6DSL_ACC_GYRO_TIM_PEDO_FIFO_EN_t;

/*=========================================================================*/

class IO_LSM6DSL
{
  public:
    IO_LSM6DSL(void); //I2C
    IO_LSM6DSL(int8_t cspin);
    IO_LSM6DSL(int8_t cspin, int8_t mosipin, int8_t misopin, int8_t sckpin);

    LSM6DSLStatusTypeDef begin                        (uint8_t addr = LSM6DSL_ADDRESS);
    LSM6DSLStatusTypeDef Enable_X                     (void);
    LSM6DSLStatusTypeDef Enable_G                     (void);
    LSM6DSLStatusTypeDef Disable_X                    (void);
    LSM6DSLStatusTypeDef Disable_G                    (void);
    LSM6DSLStatusTypeDef ReadID                       (uint8_t *p_id);
    LSM6DSLStatusTypeDef Get_X_Axes                   (int32_t *pData);
    LSM6DSLStatusTypeDef Get_G_Axes                   (int32_t *pData);
    LSM6DSLStatusTypeDef Get_X_Sensitivity            (float *pfData);
    LSM6DSLStatusTypeDef Get_G_Sensitivity            (float *pfData);
    LSM6DSLStatusTypeDef Get_X_AxesRaw                (int16_t *pData);
    LSM6DSLStatusTypeDef Get_G_AxesRaw                (int16_t *pData);
    LSM6DSLStatusTypeDef Get_X_ODR                    (float *odr);
    LSM6DSLStatusTypeDef Get_G_ODR                    (float *odr);
    LSM6DSLStatusTypeDef Set_X_ODR                    (float odr);
    LSM6DSLStatusTypeDef Set_G_ODR                    (float odr);
    LSM6DSLStatusTypeDef Get_X_FS                     (float *fullScale);
    LSM6DSLStatusTypeDef Get_G_FS                     (float *fullScale);
    LSM6DSLStatusTypeDef Set_X_FS                     (float fullScale);
    LSM6DSLStatusTypeDef Set_G_FS                     (float fullScale);
    LSM6DSLStatusTypeDef Enable_Free_Fall_Detection   (void);
    LSM6DSLStatusTypeDef Enable_Free_Fall_Detection   (LSM6DSL_Interrupt_Pin_t int_pin);
    LSM6DSLStatusTypeDef Disable_Free_Fall_Detection  (void);
    LSM6DSLStatusTypeDef Set_Free_Fall_Threshold      (uint8_t thr);
    LSM6DSLStatusTypeDef Enable_Pedometer             (void);
    LSM6DSLStatusTypeDef Disable_Pedometer            (void);
    LSM6DSLStatusTypeDef Get_Step_Counter             (uint16_t *step_count);
    LSM6DSLStatusTypeDef Reset_Step_Counter           (void);
    LSM6DSLStatusTypeDef Set_Pedometer_Threshold      (uint8_t thr);
    LSM6DSLStatusTypeDef Enable_Tilt_Detection        (void);
    LSM6DSLStatusTypeDef Enable_Tilt_Detection        (LSM6DSL_Interrupt_Pin_t int_pin);
    LSM6DSLStatusTypeDef Disable_Tilt_Detection       (void);
    LSM6DSLStatusTypeDef Enable_Wake_Up_Detection     (void);
    LSM6DSLStatusTypeDef Enable_Wake_Up_Detection     (LSM6DSL_Interrupt_Pin_t int_pin);
    LSM6DSLStatusTypeDef Disable_Wake_Up_Detection    (void);
    LSM6DSLStatusTypeDef Set_Wake_Up_Threshold        (uint8_t thr);
    LSM6DSLStatusTypeDef Enable_Single_Tap_Detection  (void);
    LSM6DSLStatusTypeDef Enable_Single_Tap_Detection  (LSM6DSL_Interrupt_Pin_t int_pin);
    LSM6DSLStatusTypeDef Disable_Single_Tap_Detection (void);
    LSM6DSLStatusTypeDef Enable_Double_Tap_Detection  (void);
    LSM6DSLStatusTypeDef Enable_Double_Tap_Detection  (LSM6DSL_Interrupt_Pin_t int_pin);
    LSM6DSLStatusTypeDef Disable_Double_Tap_Detection (void);
    LSM6DSLStatusTypeDef Set_Tap_Threshold            (uint8_t thr);
    LSM6DSLStatusTypeDef Set_Tap_Shock_Time           (uint8_t time);
    LSM6DSLStatusTypeDef Set_Tap_Quiet_Time           (uint8_t time);
    LSM6DSLStatusTypeDef Set_Tap_Duration_Time        (uint8_t time);
    LSM6DSLStatusTypeDef Enable_6D_Orientation        (void);
    LSM6DSLStatusTypeDef Enable_6D_Orientation        (LSM6DSL_Interrupt_Pin_t int_pin);
    LSM6DSLStatusTypeDef Disable_6D_Orientation       (void);
    LSM6DSLStatusTypeDef Get_6D_Orientation_XL        (uint8_t *xl);
    LSM6DSLStatusTypeDef Get_6D_Orientation_XH        (uint8_t *xh);
    LSM6DSLStatusTypeDef Get_6D_Orientation_YL        (uint8_t *yl);
    LSM6DSLStatusTypeDef Get_6D_Orientation_YH        (uint8_t *yh);
    LSM6DSLStatusTypeDef Get_6D_Orientation_ZL        (uint8_t *zl);
    LSM6DSLStatusTypeDef Get_6D_Orientation_ZH        (uint8_t *zh);
    LSM6DSLStatusTypeDef Get_Event_Status             (LSM6DSL_Event_Status_t *status);
    LSM6DSLStatusTypeDef ReadReg                      (uint8_t reg, uint8_t *data);
    LSM6DSLStatusTypeDef WriteReg                     (uint8_t reg, uint8_t data);

  private:

    void readParameters(void);
    uint8_t spixfer(uint8_t x);

    void      write8(byte reg, byte value);
    uint8_t   read8(byte reg);
    uint16_t  read16(byte reg);
    uint32_t  read24(byte reg);
    int16_t   readS16(byte reg);
    uint16_t  read16_LE(byte reg); // little endian
    int16_t   readS16_LE(byte reg); // little endian

    uint8_t   _i2caddr;
    int32_t   _sensorID;
    int32_t t_fine;

    int8_t _cs, _mosi, _miso, _sck;

    LSM6DSL_calib_data _LSM6DSL_calib;

};

#endif
