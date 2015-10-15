# Arm
(1/14/15)
Jake Johnson


An overview of the Arm, based on the current design:

The Arm will have an onboard fuse box.  12V in, and each effectuator will be fused separately.

 
Descriptions of each Effectuator:

  Turret - 12V Power source, 5V PWM signal from Arm Master Controller.  
    
  Shoulder - 12V Power source, Mamba Micro Pro, 5V PWM Signal.  Potentiometer to give positional feedback on joint angle.  
  
  Elbow - Same as shoulder.
  
  Wrist - 2 Daisychained Dynamixel servos, 12V DC power source, driven by a PSOC programmed with the Dynamixel driver
  
  **We don't have the hand designated by the ME's yet.  Once they add that, we will have extra signals to drive the Hand and the auger.  
