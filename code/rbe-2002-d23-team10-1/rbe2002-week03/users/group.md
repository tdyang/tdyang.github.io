
### Timing (Section 3.1)

> How many bytes of data must be transferred to read all three accelerometer axes? 

24 bytes of data must be transferred to read all 3 accelerometer axes. This is because each axis requires 8 bytes to transfer its data.

> From your oscilloscope readings, roughly how long does one I2C transaction take when only the accelerometer is enabled?

It takes roughly 76.8 millisecionds for one I2C transaction to occur when only the accelerometer is enabled.

> What is the maximum rate at which you can read the accelerometer? What limits the speed?

The maximum rate of data transfer is one transfer every 2.4 ms (416 hz). The speed is limited because the data is a physical thing that must transverse through wires and is therefore subject to forces such as friction, etc. Even though the ODR can be set to a higher value than 416, the data transfer still occurs every 2.4 ms, showing that it cannot just occur faster and faster.


### Filtering (Section 3.2)

> What were your final selections for data rates and sensitivities? How did you decide on those values?

We decided to set our ODR rate to 416 for both the gyroscope and accelerometer because that is the maximum value it would get. Anything greater than that passed data at the same rate that it did when it was set to 416. Therefore, 416 is the fastest and most reliable rate for us to transfer data. For the sensitivites we chose 0.061 for the accerometer and 8.75 for the gyroscope because those are the values we found in the datasheet.

> What happens when you set kappa = 1 in your filter?

When you set kappa to 1, the filter angle is the same as the accelerometer angle and it does not use the gyroscope data at all.

> What happens when you set kappa = 0 in your filter?

When you set kappa to 0, the filter angle is equal to the predicted angle calculate from the gyroscope data. It does not use the accelerometer data at all. The filter angle ossilates between a range of about -1 -- 1 degrees when the romi was on the ground.

> What was your final choice for kappa? Why did you select that value?

We chose 0.2 for Kappa because it is important to heavily weigh the gyroscope input because if it is not considered enough, the projected angle will increment too slowly and will not match the actual angle.

### Challenge (Section 4)

> Draw out the relevant parts of the state machine for the ramp detection.

![alt text](https://github.com/WPI-RBE-2002-D23/rbe-2002-d23-team10/blob/main/rbe2002-week03/users/state-machine.jpg?raw=true)

### Contributions

> Briefly describe each student’s contribution and participation for this lab. In addition, divide 100 points among the team members based on their individual contributions to the lab assignment. Each team member should be allocated a percentage of the total points earned by the team. This will allow us to evaluate the effort and participation of each team member in the assignment.

Zephyr: 33.33%
Chad: 33.33%
Tracy: 33.33%

Each member worked in the lab and answered lab questions as well as did the CS and ECE equally

