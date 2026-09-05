#include "Convolution.h"
#include <cstdint> // uint8_t 변수사용
#include <algorithm> // clamp 사용
#include <vector> // 동적 크기의 배열 생성시 사용

namespace ip {
	void ConvolutionFilter::setBlurKernel() {
		float blur[3][3] = { // 9픽셀 평균값을 내는 블러필터를 생성합니다
			{ 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
			{ 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
			{ 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f }
		};
		for (int x = 0;x < 3;++x) { // 커널에 블러필터를 삽입합니다
			for (int y = 0; y < 3; ++y) {
				m_kernel[x][y] = blur[x][y];
			}
		}
	}
	void ConvolutionFilter::setSharpenKernel() {
		float sharpen[3][3] = { // 주변 4픽셀 차이를 계산하는 샤픈필터를 생성합니다.
			{ 0, -1.0f, 0},
			{ -1.0f, 5.0f, -1.0f },
			{ 0, -1.0f, 0 }
		};
		for (int x = 0; x < 3; ++x) { // 커널에 샤픈필터를 삽입합니다.
			for (int y = 0;y < 3;++y) {
				m_kernel[x][y] = sharpen[x][y];
			}
		}
	}
    void ConvolutionFilter::process(ImageBuffer& image) {
        std::uint8_t* data = image.data();
        int width = image.width();
        int height = image.height();
        int totalPixels = width * height;

        // 원본 이미지를 복사한 임시버퍼 생성
        std::vector<std::uint8_t> tmpbuffer(data, data + (width * height * ImageBuffer::CHANNELS));


        // 모든 픽셀을 하나씩 돌면서 작업합니다.
        for (int y = 1; y < height - 1; ++y) { 
            for (int x = 1; x < width - 1; ++x) {
                int index = (y * width + x) * ImageBuffer::CHANNELS; // 현재 처리 픽셀의 좌표가 어딘지
                float newB = 0.0f;
                float newG = 0.0f;
                float newR = 0.0f;
                for (int iy = -1; iy < 2; ++iy) {
                    for (int ix = -1; ix < 2; ++ix) { // 현재 픽셀의 근처 3*3 범위의 픽셀값 계산 9번 반복
                        int nearIndex = ((y + iy) * width + (x + ix)) * ImageBuffer::CHANNELS; // (현재 처리 픽셀 + 근처픽셀 증감값) * 3

                        float kernelValue = m_kernel[iy + 1][ix + 1]; // m_kernel 배열은 0부터 2까지에 맞춰 iy ix 값 수정
                        
                        newB += tmpbuffer[nearIndex + 0] * kernelValue;
                        newG += tmpbuffer[nearIndex + 1] * kernelValue;
                        newR += tmpbuffer[nearIndex + 2] * kernelValue;
                    }
                }
                data[index + 0] = static_cast<std::uint8_t>(std::clamp(newB, 0.0f, 255.0f));
                data[index + 1] = static_cast<std::uint8_t>(std::clamp(newG, 0.0f, 255.0f));
                data[index + 2] = static_cast<std::uint8_t>(std::clamp(newR, 0.0f, 255.0f));
            }
        }




    }
}