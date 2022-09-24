# camera_streams
Framework for generating RAW Image frames from encoded streams from multiple cameras 

# Introduction
AI appliactions require RAW format image frames. The cameras available through retail channels have USB based connectivity. These cameras are able to transfer black and white images at a lower resolution in the raw format. For colored images in 2K or 4K format these cameras provide encoded video streams. YUV formats for higher resolution are either not supported or the frame rate is too low for many application. The encoded video stream help in many ways due to reduced bandwidth and bufferring requirements. 

There is no currently available open source software to convert the encoded stream to RAW (YUV) format. There are pieces of these software available but we have not found any well packaged software. One challenge is that many of the cameras do not come with any docuentation. To tackle this challenge we want to focus on couple of specific cameras and keep the device layer functionality as a separate layer so that it can be extended ro other devices in the future. 

# Context of the solution
## Operating system
Ubuntu 22.04 LTS / Ubuntu 22.10

## Package framwork
The goal is to first create a solution in Python. Underlying components can be Python based to begin with. A longer term goal will be to optimize the solution which may require C++ based implementation of the key parts.

## Cameras
We will concentrate on the following two cameras:
1. [4K HD Digital camera](https://www.amazon.com/gp/product/B08F385MPL/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
2. [SVPRO 5MP camera](https://www.amazon.com/gp/product/B07CBNSXTH/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)

# Requirements

## Camera interface support
[Link to format/size/framerate requirements](https://github.com/anamayasullerey/camera_streams/blob/main/format_requirements.md)
