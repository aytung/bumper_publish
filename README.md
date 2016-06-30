# bumper_publish

####**_Installing & Building_**  
Follow instructions on this website:
http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup


**A. Create the circuit described in the .png file**

```
In order to make sure that the circuit works properly, the LEDs should light up if and only if the corresponding bumper is pressed
```

**B. Load the program into your arduino**

``` 
Click "sketch" on the toolbar of the arduino IDE, then press Upload
(Hint: Under Tools->Board, make sure that you have the right model of arduino)
```
**C. Launch ROS and test functionality**

```
Start ROS:
roscore
Initialize the Arduino:
rosrun rosserial_python serial_node.py /dev/ttyACM0
(Note: May need to use port other than "/dev/ttyACM0"; Use "dmesg | tail" to find out where Arduino was mounted)
Figure out if topics are published as intended:
rostopic echo bumpers
0 Corresponds to no bumper pressed
1 Corresponds to left bumper only pressed
2 Corresponds to right bumper only pressed
3 Corresponds to left and right bumper pressed
```


