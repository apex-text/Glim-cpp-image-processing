#include "ResizeFilter.h"
#include <cstdint> // uint8_t 자료형 변수사용


namespace ip {
	ResizeFilter::ResizeFilter(int percent) {
		m_percent = percent;
	}

	void ResizeFilter::process(ImageBuffer& image) {
		std::uint8_t* data = image.data();
		int width = image.width();
		int height = image.height();
		int totalPixels = width * height;

		int reWidth = width * m_percent / 100;
		int reHeight = height * m_percent / 100;

		ImageBuffer ResizedImage(reWidth, reHeight); // 새로운 가로세로 데이터를 가진 imageBuffer 생성

		std::uint8_t* resizedImage = ResizedImage.data(); // 픽셀 데이터 가져오기


		for (int y = 0; y < reHeight; ++y) {
			for (int x = 0; x < reWidth; ++x) {

				int resizedIndex = (y * reWidth + x) * ImageBuffer::CHANNELS; // 새로운 이미지의 좌표

				int originX = x * 100 / m_percent; // 원본 이미지의 좌표
				int originY = y * 100 / m_percent;

				int Originindex = (originY * width + originX) * ImageBuffer::CHANNELS;
				resizedImage[resizedIndex] = data[Originindex];
				resizedImage[resizedIndex + 1] = data[Originindex + 1];
				resizedImage[resizedIndex + 2] = data[Originindex + 2];
			}
		}
		image = std::move(ResizedImage);
	}
}