#include <iostream>
#include <opencv2/opencv.hpp>

#include "iTime.hpp"
#include <fstream>

bool read_file(const std::string& fname,
               std::vector<char>& buffer)
{
    std::ifstream file(fname, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    std::cout << "size = " << size << std::endl;
    file.seekg(0, std::ios::beg);

    buffer.resize(size);

    if (file.read(buffer.data(), size)) {
        return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    static const char* fname = "IMG_17501.JPG";
    std::vector<char> buffer;

    //
    // Read jpg file into buffer
    //
    uint64_t t1 = itime_get_us();

    if (!read_file(fname, buffer)) {
        std::cerr << "Failed to read " << fname << " into buffer" << std::endl;
        return -1;
    }
    uint64_t t2 = itime_get_us();
    std::cout << "file read took " << (t2 - t1) << "usecs" << std::endl;

    //
    // Decode jpg buffer
    //
    //Mat image = imread("IMG_17501.JPG", IMREAD_GRAYSCALE);
    //Mat image = imread("IMG_17501.JPG", IMREAD_UNCHANGED);
    t1 = itime_get_us();
    //cv::Mat image = cv::imread("IMG_17501.JPG");
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
    t2 = itime_get_us();

    std::cout << "jpg decode took " << (t2 - t1) << "usecs" << std::endl;

    // Error Handling
    if (image.empty()) {
        std::cout << "Image File "
                  << "Not Found" << std::endl;

        // wait for any key press
        std::cin.get();
        return -1;
    }

    //
    // Display file properties
    //
    std::cout << "img rows = " << image.rows << " cols = " << image.cols << std::endl;
    std::cout << "img channels = " << image.channels() << std::endl;

    // Show Image inside a window with
    // the name provided
    cv::imshow("Window Name", image);

    // Wait for any keystroke
    cv::waitKey(0);

    //
    // Convert image to RGB
    //
    t1 = itime_get_us();
    std::vector<uint8_t> vec(image.rows * image.cols * 3);
    for (uint32_t row = 0; row < image.rows; row++) {
        for (uint32_t col = 0; col < image.cols; col++) {
#if 0
            auto v = image.at<cv::Vec3b>(row, col);
            uint32_t pos = (row * image.cols + col) * 3;
            vec[pos+0] = v[0];
            vec[pos+1] = v[1];
            vec[pos+2] = v[2];
#else
            uint32_t pos = (row * image.cols + col) * 3;
            vec[pos+0] = image.data[pos+0];
            vec[pos+1] = image.data[pos+1];
            vec[pos+2] = image.data[pos+2];
#endif
        }
    }
    t2 = itime_get_us();

    std::cout << "mat to rgb took " << (t2 - t1) << "usecs" << std::endl;

    std::cout << "data=" << (void*)image.data << " start=" << (void*)image.datastart << " end=" << (void*)image.dataend << " limit=" << (void*)image.datalimit << std::endl;

    return 0;
}

