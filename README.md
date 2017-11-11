# Arduino Tank
This is a respository of files and tips for the Keyestudio Tank Robot
http://www.keyestudio.com/shop/car/keyes-mini-tank-robot.html

Tip 1: Remove the Bluetooth module before uploading a sketch. The bluetooth module has priority on comms and will prevent the upload when installed.

Tip 2: Wiring for the motors is specific: Looking from the rear of the robot, the motors should be wired with the left motor then the right motor. The wires should be red, black, black, red.

Tip 3: The servo motor supplied is probably not centered. Test it before mounting.

Tip 4: The 18650 batteries are not easy to remove or install. Charge them before assembly so you get some use before having to remove them for charging. Use a small cable tie to gather up the loose wires at the back. This will prevent the wires from being caught in the treads and will help when removing and installing the batteries.

Tip 5: The assembly instructions show a AA battery pack directly wired to the motor board. The battery pack is not included and is not necessary. The motor board can be powered directly from the Arduino board using the 18650 battery pack. The supplied pack has the correct barrel adaptor to plug into the Arduino UNO.
