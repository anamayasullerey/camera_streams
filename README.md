# camera_streams
Framework for generating RGB Image frames from MJPEG encoded streams from multiple cameras 

# Introduction
AI appliactions require RGB format image frames. The cameras available through retail channels have USB based connectivity. These cameras are able to transfer black and white images at a lower resolution in the raw format. For colored images in 2K or 4K format these cameras provide encoded video streams. YUV formats for higher resolution are either not supported or the frame rate is too low for many application. The encoded video stream help in many ways due to reduced bandwidth and bufferring requirements.

There is no currently available open source software to convert the encoded stream to RGB format. There are pieces of these software available but we have not found any well packaged software. One challenge is that many of the cameras do not come with any documentation. To tackle this challenge we want to focus on couple of specific cameras and keep the device layer functionality as a separate layer so that it can be extended ro other devices in the future. 

# High level requirements
## Operating system
Ubuntu 22.04 LTS / Ubuntu 22.10

## Package framework
The goal is to first create a solution in Python. Underlying components can be Python based to begin with. A longer term goal will be to optimize the solution which may require C++ based implementation of the key parts.

## Cameras
We will concentrate on the following two cameras:
1. [4K HD Digital camera](https://www.amazon.com/gp/product/B08F385MPL/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
2. [SVPRO 5MP camera](https://www.amazon.com/gp/product/B07CBNSXTH/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)

[Link to format/size/framerate requirements](https://github.com/anamayasullerey/camera_streams/blob/main/format_requirements.md)

# Solution requirements
# High level archtecture

Following the representation of processing for single camera stream.
```
MJPEG stream
using existing ====>> MJPEG decode to RGB ====>> RGB frame queue =====> Output
utility
```
For the first two steps use of an existing library is preferred. This solution should be from a well maintained source.

The solution must allow one or more cameras. The solution must allow individual resolution to be set independently. Each camera must have a corresponding queue of frame buffers. 


The solution must allow:
- command supporting flush of all queues
- command support a timestamp based initialization of all queues

***The solution must allow queues to be mapped to different threads of a multithreaded CPU***

# Output queue definition and its APIs
Each frame queue stores frame buffers in YUV format. Additionally the queue must also store frame timestamp form the stream, encoded frame arrival timestamp, and decoded frame queueing timestamp.

## Functional API
The following API is required for each queue:
- Specification of frame size and queue depth at initializtion
- Queue pop command that returns frame buffer, timestamps and number of frames in the queue. The top entry in the queue is deleted after the execution of this command.
- A queue read command that returns frame buffer, timestamps and number of frames in the queue
- Queue status command that returns timestamps for the first frame and number of frames in the queue
- Flush command that flushes the queue
- Flush_till command that takes timestamp argument flushes any frame before that specified timestamp
- Method to make a queue active instantaneously or after a specified clock time
- Method to make a queue inactive instantaneiouly or after a specified clock time
- Mechanism to select drop from front or drop from back in case of overflow

## Monitoring API
- A queue must be able to log the timestamps of all the frames passing through the queue
- A queue must be able to log the method in which an enqueued fram was removed from the queue
- A queue must be able to log a frame at entry and exit based on a callback function result
- A queue must be able handle turning on and turning off of logging while it is active
- A queue must support time window based logging
- A queue must support sampled logging (1 in N frames)

## Statistics
- Number of frames moved
- Number of frames moved since last activation
- Number of frames dropped
- Number of frames dropped since last activation
- Max and min latencies at the input and output of the queues
- Average queue depth
- Max queue depth
- Min queue depth

# Performance
The solution should be process to do 4K frames at 30fps using 50% of a single core performance of a newer generation I5 processor.

# Proof of concept
VLC player allows capture and display of camera streams. A codec can be selected for VLC camera. When using the YUV codec VLC desplayed4K camera video with very slow frame rate. When using MJPEC codec the frame rate was much higher. Though the latency was a bit high in this case the video appeared smooth.

# Useful links
* [Another project with similar goals](https://pyimagesearch.com/2017/02/06/faster-video-file-fps-with-cv2-videocapture-and-opencv/)
* [Github repo for the above project](https://github.com/PyImageSearch/imutils/blob/9f740a53bcc2ed7eba2558afed8b4c17fd8a1d4c/imutils/video/pivideostream.py)
* [picamera: for Raspberry Pi](https://picamera.readthedocs.io/en/release-1.13/)
* [Video for Linux API](https://www.kernel.org/doc/html/v4.8/media/uapi/v4l/pixfmt.html)

