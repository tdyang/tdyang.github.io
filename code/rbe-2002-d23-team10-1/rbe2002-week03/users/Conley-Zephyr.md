### Introductory questions (Section 1.1)

> What IMU chip is used on the Romi?

The IMU chip used on the romi is the LSM6DSS3.

> What is the I2C address of the chip _as implemented on the Romi Control Board_?

The I2C address of the chip is 0b110101X. X is 1 when the signal is high, and 0 when the signal is low.

> What is the largest (nominal) acceleration you can measure with the IMU (in _g_)?

The absolute maximum acceleration you can measure with the IMU is 10,000g for 0.1 seconds, but the largest nominal acceleration is 16g.

### Basic functionality (Section 1.2)

> Indicate the *positive* direction for each axis of the accelerometer and each axis of the gyroscope using one of UP, DOWN, LEFT, RIGHT, FRONT, BACK, STRANGE, CHARM. The +z accelerometer is done for you. 

| Device | +x | +y | +z |
|---|:---:|:---:|:---:| 
| Accelerometer | FRONT | LEFT | UP| 
| Gyroscope | LEFT UP ROLL | FRONT DOWN PITCH | LEFT YAW | 
|
> Are the coordinate systems for the accelerometer and gyroscope coincident?

The accelerometer and the gyroscope have the same axies, so they are therefore coincident.

> Fill in the table below for your predictions for the accelerometer readings.

| Orientation | a_x | a_y | a_z |
|---|:---:|:---:|:---:| 
| Top pointing up | 200 | 100 | 16000 | 
| Front pointing up | 16000 **16000** | 100 **200** | 200 **1000** | 
| Left pointing up | 200 **300** | 16000 **16000** | 100 **800** | 
| Right pointing up | -200 **400** | -16000 **-16000** | -100 **700** | 
| Bottom pointing up | -16000 **-16000**  | -100 **700** | -200 **400** | 
| Rear pointing up |-200 **200** | -100 **100** | -16000 **-16000** |
|

### Calibration (Section 1.3)

> Record the default values for the following.

| Sensor | ODR | FS | Sensitivity (from datasheet) |
|:---:|:---:|:---:|:---:|
| Gyro | ODR13 | GYRO_FS245 | 8.75 mg/LSB|
| Acc | ODR13 | ACC_FS2 | 0.061 mg/LSB |
|

> Describe your experiment to measure the sensitivity of the accelerometer. Record your results. How do your measurements compare to the datasheet values above? Write the offset in milligravities.

To record the sensitivity of the accelerometer, I will begin by collecting ~100 pieces of data while the romi is sitting still with the top pointed up. From the x and y directions, the average value from the collected data will be equal to the offset for that direction. In the z direction, I will take the average of my recorded values then divide 1000 (the expected value for gravity) by this average. This will give me my sensitivity for the z direction. I will then repeat this experiment with the x and y axies pointed upwards to record the sensitivity for each direction. Finally, during the x sensitivity experiment I will average all the z values as well to determine the offset in the z direction.

| Axis | Sensitivity | Offset|
|:---:|:---:|:---:|
| x | 0.062 | 258.9 |
| y | 0.061 | 109.8 |
| z | 0.059 | 784.6 |

> Record the standard deviation of the accelerometer readings when sitting still.

| Axis | Std. dev. (in _mg_)
|:---:|:---:|
| x | 57.18 | 
| y | 36.72 | 
| z | 33.99 | 

> If the Romi were spinning on level ground at 1 revolution per second and the gyroscope was set to a full-scale of 500 dps, what value would the IMU return on each gyro axis? Ignore noise and bias. Use the conversion factor given in Table 3 of the datasheet.

x: 0
y: 0
z: 20571.4 -> 20571

### Gyroscope (Section 1.5)

> Describe your experiment to measure the gyroscope bias and noise and your results.

For this experiment I took ~100 datapoints while the romi was not moving on flat level ground. For each of my directions, the bias is equal to the average value in my data, and the noise is equal to the standard deviation of that data.

| Axis | Bias | Noise |
|:---:|:---:|:---:|
| x | 506.03 | 8.65 |
| y | -713.31 | 16.77 |
| z | -539.46 | 59.53 |

### The `STATUS` Register (Section 2.1)

> Explain what the following line of code is doing: `if(imu.getStatus() & 0x01)`

This line of code is an if statement that checks if the accelerometer in the IMU has new data. The line imu.getStatus() checks the STATUS_REG, which is of the form 0x1E. The last bit of this hex string represents whether or not the accelerometer has new data. It is a 1 if there is new data, and a 0 if there is not new data. The statement then compares this string to another hex string 0x01, and returns 1 (true) if the accelerometer has new data or 0 (false) if there is no new data to read.


### Basic angle calculations (Section 2.3)

> Describe the basic behavior of your angle calculator. Does is get the angle correct over a complete 360?

My angle calculator takes the in the x reading minus the x-offset and the z reading minus the z-offset and then takes the inverse tangent of these. Since the value it returns is in radians, the function then multiplies this value by 360 and divides by 2 pi to get the angle in degrees. It is correct over a complete 360, however at 180 degrees it flips from being a positive angle to a negative angle.
