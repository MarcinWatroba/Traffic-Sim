# Traffic-Sim
Traffic Simulator final year project of my Computer Games Programming course.

<h2>How to Run</h2>
Traffic Simulator has been run in Visual Studio running v140 toolset. It can be run either in Debug or Release mode, on x86 memory format.

<h2>Description</h2>
A simple microscopic traffic simulator that populates a pre-defined road network with traffic, and then collects data on it. 
Design and implementation was completely my own. My goal was to create a simple traffic simulator that would be capable of simulating 
hundreds of vehicles at once, all interacting with one another in real time.
My traffic simulator consists of following elements: Cars (purple squares), start/goal nodes for cars (green squares), roads (blue rectangles), intersections (two roads meeting), traffic lights (green/amber/red lines on intersections).

Cars are dynamically created at spawn points and are assigned A* generated routes to their destinations. 
By default, destinations are picked at random, spawn interval for cars is initialised to predefined value, and so is the traffic light 
change interval. However, user is free to modify these, choosing custom routes, spawn intervals, and traffic light change intervals. 
All AI cars interact with eachother by comparing their positions, speeds and intentions. 
There can be up to 1500 cars on the road network at once.

<img src="https://github.com/marcin388/Traffic-Sim/blob/master/trafficSim.jpg">

