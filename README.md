# camera_streams
Framework for generating RAW Image frames from encoded streams from multiple cameras 

# Introduction
AI appliactions require RAW format image frames. The cameras available through retail channels have USB based connectivity. These cameras are able to transfer black and white images at a lower resolution in the raw format. For colored images in 2K or 4K format these cameras provide encoded video streams. YUV formats for higher resolution are either not supported or the frame rate is too low for many application. The encoded video stream help in many ways due to reduced bandwidth and bufferring requirements.

There is no currently available open source software to convert the encoded stream to RAW (YUV) format. There are pieces of these software available but we have not found any well packaged software. One challenge is that many of the cameras do not come with any docuentation. To tackle this challenge we want to focus on couple of specific cameras and keep the device layer functionality as a separate layer so that it can be extended ro other devices in the future. 

# High level requirements
## Operating system
Ubuntu 22.04 LTS / Ubuntu 22.10

## Package framwork
The goal is to first create a solution in Python. Underlying components can be Python based to begin with. A longer term goal will be to optimize the solution which may require C++ based implementation of the key parts.

## Cameras
We will concentrate on the following two cameras:
1. [4K HD Digital camera](https://www.amazon.com/gp/product/B08F385MPL/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
2. [SVPRO 5MP camera](https://www.amazon.com/gp/product/B07CBNSXTH/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)

[Link to format/size/framerate requirements](https://github.com/anamayasullerey/camera_streams/blob/main/format_requirements.md)

# Solution requirements
# High level archtecture
The solution must allow one or more cameras. The solution must allow individual resolution to be set independently. Each camera must have a corresponding queue of frame buffers. 

The solution must allow:
- command supporting flush of all queues
- command support a timestamp based initialization of all queues

***The solution must allow queues to be mapped to different threads of a multithreaded CPU***

# Output queue and its API
Each frame queue stores frame buffers in YUV format. Additionally the queue must also store frame timestamp form the stream, encoded frame arrival timestamp, and decoded frame queueing timestamp.

The following API is required for each queue:
- Specification of frame size and queue depth at initializtion
- Queue pop command that returns frame buffer, timestamps and number of frames in the queue. The top entry in the queue is deleted after the execution of this command.
- A queue read command that returns frame buffer, timestamps and number of frames in the queue
- Queue status command that returns timestamps for the first frame and number of frames in the queue
- Flush command that flushes the queue
- Flush_till command that takes timestamp argument flushes any frame before that specified timestamp
- Method to make a queue active instantaneously or after a specified clock time
- Metod to make a queue inactive instantaneiouly or after a specified clock time

# Queue monitoring API
- A queue must be able to log the timestamps of all the frames passing through the queue
- A queue must be able to log the method in which an enqueued fram was removed from the queue
- A queue must be able to log a frame at entry and exit based on a callback function result
- A queue must be able handle turning on and turning off of logging while it is active
- A queue must support time window based logging
- A queue must support sampled logging (1 in N frames)




