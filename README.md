# camera_streams
Framework for generating RAW Image frames from encoded streams from multiple cameras 

# Introduction
AI appliactions require RAW format image frames. The cameras available through retail channels have USB based connectivity. These cameras are able to transfer black and white images at a lower resolution in the raw format. For colored images in 2K or 4K format these cameras provide encoded video streams. This reduces the data rate and allows efficient movement of data.

There is no currently available open source software to convert the encoded stream to RAW format. There are pieces of these software available but we have not found any well packaged software. One challenge is that many of the cameras do not come with any docuentation. To tackle this challenge we want to focus on couple of specific cameras and keep the device layer functionality as a separate layer so that it can be extended ro other devices in the future. 

# Context of the solution
## Camera
We will concentrate on the following two cameras:
1. [4K HD Digital camera](https://www.amazon.com/gp/product/B08F385MPL/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
2. [SVPRO 5MP camera](https://www.amazon.com/gp/product/B07CBNSXTH/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)
