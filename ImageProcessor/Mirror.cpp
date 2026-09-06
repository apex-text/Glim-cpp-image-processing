#include "Mirror.h"
#include <cstdint> // uint8_t 자료형 변수사용


namespace ip {

	void MirrorFilter::process(ImageBuffer& image) {
		std::uint8_t* data = image.data();
		int width = image.width();
		int height = image.height();
		int totalPixels = width * height;


		if (m_mode == MirrorMode::Horizontal) {
			for (int y = 0; y < height; ++y) {
				for (int x = 0; x < width / 2; ++x) {
					int index = (y * width + x) * ImageBuffer::CHANNELS;
					int mirrorX = width - 1 - x;
					int mirrorIndex = (y * width + mirrorX) * ImageBuffer::CHANNELS;
					// Swap pixels
					std::swap(data[index], data[mirrorIndex]);
					std::swap(data[index + 1], data[mirrorIndex + 1]);
					std::swap(data[index + 2], data[mirrorIndex + 2]);
				}
			}
		}

		else if (m_mode == MirrorMode::Vertical) {
			for (int y = 0; y < height / 2; ++y) {
				for (int x = 0; x < width; ++x) {
					int index = (y * width + x) * ImageBuffer::CHANNELS;
					int mirrorY = height - 1 - y;
					int mirrorIndex = (mirrorY * width + x) * ImageBuffer::CHANNELS;
					// Swap pixels
					std::swap(data[index], data[mirrorIndex]);
					std::swap(data[index + 1], data[mirrorIndex + 1]);
					std::swap(data[index + 2], data[mirrorIndex + 2]);
				}
			}
		}


		//for (int y = 0; y < height; ++y) {
		//	for (int x = 0; x < width; ++x) {
		//		int index = (y * width + x) * ImageBuffer::CHANNELS; // 현재 처리 픽셀의 좌표가 어딘지

		//		if (m_mode == MirrorMode::Horizontal) {
		//			int mirrorX = width - 1 - x;
		//			int mirrorIndex = (y * width + mirrorX) * ImageBuffer::CHANNELS;
		//			// Swap pixels
		//			std::swap(data[index], data[mirrorIndex]);
		//			std::swap(data[index + 1], data[mirrorIndex + 1]);
		//			std::swap(data[index + 2], data[mirrorIndex + 2]);
		//		}
		//		else if (m_mode == MirrorMode::Vertical) {
		//			int mirrorY = height - 1 - y;
		//			int mirrorIndex = (mirrorY * width + x) * ImageBuffer::CHANNELS;
		//			// Swap pixels
		//			std::swap(data[index], data[mirrorIndex]);
		//			std::swap(data[index + 1], data[mirrorIndex + 1]);
		//			std::swap(data[index + 2], data[mirrorIndex + 2]);
		//		}

		//	}
		//}
	}
}