#include "Contrast.h"
#include <cstdint>
#include <algorithm>

namespace ip {

    void ContrastFilter::process(ImageBuffer& image, float contrast) {
        std::uint8_t* data = image.data();
        int width = image.width();
        int height = image.height();
        int totalPixels = width * height;

        // 모든 픽셀을 하나씩 돌면서 작업합니다.
        for (int i = 0; i < totalPixels; ++i) {
            // 하나의 픽셀은 3바이트(B, G, R)를 차지합니다.
            int index = i * ImageBuffer::CHANNELS;

            // 대비 조절
            int newB = (data[i + 0] - 128) * contrast + 128; // B
            int newG = (data[index + 1] - 128) * contrast + 128; // G
            int newR = (data[index + 2] - 128) * contrast + 128; // R

            // 조절 후 값으로 교체
            data[i] = static_cast<std::uint8_t>(std::clamp(newB, 0, 255)); // B
            data[index + 1] = static_cast<std::uint8_t>(std::clamp(newG, 0, 255)); // G
            data[index + 2] = static_cast<std::uint8_t>(std::clamp(newR, 0, 255)); // R
        }
    }
}