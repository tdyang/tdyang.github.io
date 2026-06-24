> Before you get started coding, draw out a state machine for the navigation of the arena, keeping in mind that turning (being non-blocking) is a state. Be sure to label the transitions with events and actions.

![alt text](https://github.com/WPI-RBE-2002-D23/rbe-2002-d23-team10/blob/main/rbe2002-week04/users/state-machine-maze.jpg?raw=true)

> List out at least three methods you could use for executing turns. List the advantages and disadvantages of each.

Gyroscope:
- Gyroscope sensor is very accurate
- Differences in surface friction do not affect final position
- Very easy to implement a left hand turn after right hand turn is established
- Most difficult to implement
- Sensor has some internal bias

Line Sensor:
- Already being implemented in state machine (line following)
- Not impacted by surface friction
- Differences in lighting affect how much it turns
- Robot is not perfectly lined up after turning

Timer:
- Simple to implement
- Fails when batteries are low
- Requires trial and error to determine correct timing
- Differences in surface friction affect final position

> Describe the method you will use to execute turns. Make a *positive statement* about why you chose that method. How can you mitigate the disadvantages?

The method we chose to execute turns was the Timer Based turn. We chose this method after testing all of the methods becasue it was simple to implement and it was easy to tune. The turns were more accurate than initially theorized. To mitigate the disadvantage of the turn not being the exact same each time was by having a strong line follow meaning the romi would self correct itself quickly after turning. 

Don't forget to create a release of your team's code.

> Briefly describe each student’s contribution and participation for this lab. In addition, divide 100 points among the team members based on their individual contributions to the lab as- signment. Each team member should be allocated a percentage of the total points earned by the team. This will allow us to evaluate the effort and participation of each team member in the assignment.

Zephyr: 33.33% Chad: 33.33% Tracy: 33.33%

Each member worked in the lab and answered lab questions as well as did the CS and ECE equally
