#include "Contrast.h"
#include <cstdint> // std::uint8_t 타입을 사용하기 위해 필요
#include <algorithm> // clamp 함수를 사용하기 위해 필요

namespace ip {

    void ContrastFilter::process(ImageBuffer& image) {
        std::uint8_t* data = image.data();
        int width = image.width();
        int height = image.height();
        int totalPixels = width * height;

        // 모든 픽셀을 하나씩 돌면서 작업합니다.
        for (int i = 0; i < totalPixels; ++i) {
            // 하나의 픽셀은 3바이트(B, G, R)를 차지합니다.
            int index = i * ImageBuffer::CHANNELS;

            // 대비 조절
            double newB = (data[index + 0] - 128) * 1.0 * m_contrast + 128; // B
            double newG = (data[index + 1] - 128) * 1.0 * m_contrast + 128; // G
            double newR = (data[index + 2] - 128) * 1.0 * m_contrast + 128; // R

            // 조절 후 값으로 교체
            data[index + 0] = static_cast<std::uint8_t>(std::clamp(newB, 0.0, 255.0)); // B
            data[index + 1] = static_cast<std::uint8_t>(std::clamp(newG, 0.0, 255.0)); // G
            data[index + 2] = static_cast<std::uint8_t>(std::clamp(newR, 0.0, 255.0)); // R
        }
    }
}