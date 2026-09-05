#include "ThresholdFilter.h"
#include <cstdint>

namespace ip {
	void ThresholdFilter::process(ImageBuffer& image, uint8_t threshold) {
		std::uint8_t* data = image.data();
		int width = image.width();
		int height = image.height();
		int totalPixels = width * height;
		for (int i = 0; i < totalPixels; ++i) {
			int index = i * ImageBuffer::CHANNELS;
			
			// 픽셀 밝기 평균값 계산
			std::uint8_t y = (data[index] * 0.299 + data[index + 1] * 0.587 + data[index + 2] * 0.114);
			
			// 픽셀 이진화
			if (y > threshold) {
				data[index + 0] = 255; // B
				data[index + 1] = 255; // G
				data[index + 2] = 255; // R
			}
			else {
				data[index + 0] = 0;
				data[index + 1] = 0;
				data[index + 2] = 0;
			}

		}
	}
}