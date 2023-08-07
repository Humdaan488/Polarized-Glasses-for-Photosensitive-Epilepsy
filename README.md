# Polarized-Glasses-for-Photosensitive-Epilepsy
Designed polarized glasses using servo controller, polarizing filters, Arduino, gears, and phototransistor to detect and block flashing lights between a certain frequency range to protect against detrimental health effects experienced by users with photosensitive epilepsy when exposed to flickering lights.


---------------------------------- DESCRIPTION of the DESIGN ---------------------------------------

  Photosensitive epilepsy is a neurological condition which affects millions of people globally with one of the main symptoms being sensitivity to flashing lights. The frequency or speed of the flashing lights can provoke various health conditions such as seizures, flickering vertigo,vestibular migraines, meniere’s disease, and much more.

  The design solution created are glasses that contain two layers of polarizing filters. In the initial state both filters will be parallel to one another. If the light sensor encounters a flashing light between 3 Hz - 50 Hz, the secondary layer of the polarizing filter will rotate to block light. The amount of light that is blocked is dependent on what range of that 3-50 Hz spectrum the frequency of incoming flashing light falls on. The angle at which the second layer will travel will be between 0° to 90° degrees, where 90° will block out all incoming light.  

  The main aspects of the design include the polarizing filters in the glasses, servo controller and light sensor. Polarizing filters are made with chemical compounds that naturally align in parallel to each other, this will create a filter that absorbs any light that doesn’t match the orientation of the filter, and only vertical light will pass through. When two filters are put on top of one another in a perpendicular direction no light will be able to pass. The secondary filter layer will be able to rotate allowing varying amounts of light to pass through based on the angle it is rotated to. This feature is important as it will appropriately rotate to an angle that diminishes the effects of flashing lights for those who 	are photosensitive, decreasing any negative effects that may occur when they are exposed to bright lights. 

  A second key component of the design solution is the servo motor controller acting as a gear to rotate the secondary polarizing filter to the desired angle between 0° to 90° degrees based on how much light is to be blocked. Once the servo controller receives an input command signal from the sensor, it applies a torque to the motor which in turn controls the rotation of the polarizing filter. The standard servo utilized in this design moves on a specific rotation arc (0° to 90°) meaning that it provides positional feedback to the controller.  The motor controller is found on the bridge part (central area) of the glasses. 
   
   In order for the servo motor controller or polarizing filters to have the desired functional impact in this design solution, light sensors are a necessary component. Once the light sensor detects flashing light of specific intensity that could cause harm to the user, it converts light energy into an electrical signal that can be perceived by other devices. This electrical signal triggers the solution’s response by causing the servo motor controller to rotate the polarizing filter and block the flashing lights. Without the light sensor, there would be no way to detect flashing flights or trigger a response to help users.

---------------------------------- DEMO VIDEO ---------------------------------------

A demo video can be found in the project files. The video demonstrates the polarizing filters on the glasses in action based on varying frequencies of flashing light being detected.



https://github.com/Humdaan488/Polarized-Glasses-for-Photosensitive-Epilepsy/assets/77771083/05a19026-2a5c-4d5b-8232-09a47cd66d5b

