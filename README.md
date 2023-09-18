# Kexxu Eye Tracking Glasses and the ESP32

## Prerequisites
 - Kexxu Eye Tracking Glasses
 - ESP32 or compatible embedded device
 - Arduino IDE

## Setup
Please follow these steps in order to make events emitted by your Kexxu Eye Tracking Glasses available to your embedded device:

1. Power on your Kexxu Eye Tracking Glasses
2. Open the Arduino example project in the Arduino IDE
3. Fill in your wifi configuration in the Arduino IDE
4. Enter your Kexxu Eye Tracking Glasses' IP as the `mqtt_server` string. (The address can be found in the Kexxu Devices app)
5. Compile and upload the Arduino project to your embedded device
6. Open the Serial Monitor with a baud-rate of 115200
7.  Follow the embedded devices' output. It should look something like  
    this:
    ```
    09:00:00.394 -> Waiting for WiFi... 
    09:00:07.321 -> WiFi connected
    09:00:07.321 -> IP address: 
    09:00:07.321 -> 192.168.1.198
    09:00:08.406 -> 200
    09:00:08.406 -> {"Id":xyzxyzxyz}
    09:00:08.406 -> Attempting MQTT connection...connected
    ```
8.  After this output, the serial monitor should quickly fill with
    with eye tracking information similar to this:
    ```
    Message arrived on topic: devices/<DEVICE_ID>/eyetracking. Message: 
    ```
    ```json
    {"eye_left_pos_x":0.0,"eye_left_pos_y":0.0,"eye_right_pos_x":0.0,"eye_right_pos_y":0.0,"eye_top_pos_x":0.0,"eye_top_pos_y":0.0,"pupil_pos_x":-0.30000001192092896,"pupil_pos_y":0.35555556416511536,"pupil_rel_pos_x":-1.2332611083984375,"pupil_rel_pos_y":2.533367395401001,"timestamp_ms":"1695027209126"}
    ```

Great, you are ready to extend the example project from this point on!

We hope you were able to follow the steps without any problems and we thank you for choosing the Kexxu Eye Tracking Glasses!

Best wishes for you and your project from Amsterdam!

Kexxu