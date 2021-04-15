# DHT21_MQTT
https://www.rhydolabz.com/wiki/?p=10450

https://raspberrypi.vn/thu-thuat-raspberry-pi/streaming-video-tren-vlc-2824.pi

https://raspberrypi.stackexchange.com/questions/23182/how-to-stream-video-from-raspberry-pi-camera-and-watch-it-live

https://github.com/bblanchon/ArduinoJson

https://github.com/adafruit/DHT-sensor-library

https://github.com/adafruit/Adafruit_Sensor

https://pypi.org/project/paho-mqtt/

https://www.communistech.com/knowledge/streaming-video-from-raspberry-pi-to-linux-pc/

https://gist.github.com/neilyoung/8216c6cf0c7b69e25a152fde1c022a5d

https://forum.arduino.cc/index.php?topic=499306.0

Gstreamer:

Pi : raspivid -fps 30 -h 480 -w 640 -vf -n -t 0 -b 200000 -o - | gst-launch-1.0 -v fdsrc ! h264parse ! rtph264pay config-interval=1 pt=96 ! gdppay ! tcpserversink host=10.10.0.131 port=5000

PC : gst-launch-1.0 -v tcpclientsrc host=10.10.0.131 port=5000 ! gdpdepay ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink sync=false

Gstreamer Webcam:

Server: gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480,framerate=\(fraction\)30/1 ! videoconvert ! jpegenc ! tcpserversink host=192.168.2.116 port=5000

Client: gst-launch-1.0 -v tcpclientsrc host=192.168.2.116 port=5000 ! jpegdec ! videoconvert ! autovideosink sync=false


