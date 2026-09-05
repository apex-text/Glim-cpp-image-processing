#include "Brightness.h"
#include <cstdint>
#include <algorithm>

namespace ip {

    void BrightnessFilter::process(ImageBuffer& image, int bright) {
        std::uint8_t* data = image.data();
        int width = image.width();
        int height = image.height();
        int totalPixels = width * height;

        // 모든 픽셀을 하나씩 돌면서 작업합니다.
        for (int i = 0; i < totalPixels; ++i) {
            // 하나의 픽셀은 3바이트(B, G, R)를 차지합니다.
            int index = i * ImageBuffer::CHANNELS;
            
            //std::uint8_t gray = (data[index] * 0.299 + data[index + 1] * 0.587 + data[index + 2] * 0.114);


            // 밝기 조절
            int newB = data[index + 0]+ bright; // B
            int newG = data[index + 1]+ bright; // G
            int newR = data[index + 2]+ bright; // R

            // 조절 후 값으로 교체
            data[index + 0] = static_cast<std::uint8_t>(std::clamp(newB, 0, 255)); // B
            data[index + 1] = static_cast<std::uint8_t>(std::clamp(newG, 0, 255)); // G
            data[index + 2] = static_cast<std::uint8_t>(std::clamp(newR, 0, 255)); // R
        }
    }
}