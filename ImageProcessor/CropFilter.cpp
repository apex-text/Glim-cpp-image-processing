#include "CropFilter.h"
#include <cstdint> // uint8_t 자료형 변수사용


namespace ip {

	CropFilter::CropFilter(int startX, int startY, int endX, int endY) {
		m_startX = startX;
		m_startY = startY;
		m_endX = endX;
		m_endY = endY;
	
	}
    void CropFilter::process(ImageBuffer& image) {
        std::uint8_t* data = image.data();
        int width = image.width();
        int height = image.height();
        int totalPixels = width * height;

		int cropWidth = m_endX - m_startX;
		int cropHeight = m_endY - m_startY;

		ImageBuffer CroppedImage(cropWidth, cropHeight); // 새로운 가로세로 데이터를 가진 imageBuffer 생성

		std::uint8_t* croppedImage = CroppedImage.data(); // 픽셀 데이터 가져오기
		

		for (int y = 0; y < cropHeight; ++y) {
			for (int x = 0; x < cropWidth; ++x) {
				int cropedIndex = (y * cropWidth + x) * ImageBuffer::CHANNELS;
				int Originindex = ((m_startY + y) * width + (m_startX + x)) * ImageBuffer::CHANNELS;
				croppedImage[cropedIndex] = data[Originindex];
				croppedImage[cropedIndex + 1] = data[Originindex + 1];
				croppedImage[cropedIndex + 2] = data[Originindex + 2];
			}
		}
		image = std::move(CroppedImage);
    }
}