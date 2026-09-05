#include "GrayscaleFilter.h"
#include <cstdint>

namespace ip {

    void GrayscaleFilter::process(ImageBuffer& image) {
        std::uint8_t* data = image.data();
        int width = image.width();
        int height = image.height();
        int totalPixels = width * height;

        // 모든 픽셀을 하나씩 돌면서 작업합니다.
        for (int i = 0; i < totalPixels; ++i) {
            // 하나의 픽셀은 3바이트(B, G, R)를 차지합니다.
            int index = i * ImageBuffer::CHANNELS;

            // 흑백 값 계산 (NTSC 가중치)
            std::uint8_t gray = (data[index] * 0.299 + data[index+1] * 0.587 + data[index+2] * 0.114);

            // 흑백 값으로 교체
            data[index + 0] = gray; // B
            data[index + 1] = gray; // G
            data[index + 2] = gray; // R
        }
    }
}