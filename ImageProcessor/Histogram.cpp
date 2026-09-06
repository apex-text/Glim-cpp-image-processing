#include "Histogram.h"
#include <cstdint> // uint8_t 변수사용
#include <iostream> // std::cout 사용
#include <iomanip> // cout setw 줄맞춤시 사용
namespace ip {
    void HistogramPrint(const std::string& label, int count, int totalPixels) { // 히스토그램 print 함수
        double percent = (count * 100.0) / totalPixels;
        std::cout << std::left << std::setw(25) << label << ": ";
        std::cout << std::right << std::setw(8) << count << " (" << std::setw(5) << percent << "%) |";
        for (int p = 0; p < (percent/2); ++p) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
	void Histogram::process(ImageBuffer& image) {
        std::uint8_t* data = image.data();
        int width = image.width();
        int height = image.height();
        int totalPixels = width * height;

        int clipBlack = 0;
        int black = 0;
        int shadows = 0;
        int exposure = 0;
        int highlights = 0;
        int whites = 0;
        int clipWhites = 0;

        // 모든 픽셀을 하나씩 돌면서 작업합니다.
        for (int i = 0; i < totalPixels; ++i) {

            // 하나의 픽셀은 3바이트(B, G, R)를 차지합니다.
            int index = i * ImageBuffer::CHANNELS;

            // 밝기 계산 (NTSC 가중치)
            int y = static_cast<int>(data[index] * 0.299 + data[index + 1] * 0.587 + data[index + 2] * 0.114);
            
            // 분포 저장
            if (y == 0) {
                ++clipBlack;
            }
            else if (y >= 1 && y <= 25) {
                ++black;
            }
            else if (y >= 26 && y <= 76) {
                ++shadows;
            }
            else if (y >= 77 && y <= 178) {
                ++exposure;
            }
            else if (y >= 179 && y <= 229) {
                ++highlights;
            }
            else if (y >= 230 && y <= 254) {
                ++whites;
            }
            else if (y == 255) {
                ++clipWhites;
            }

        }


        std::cout << "\n=============== Brightness Histogram ===============\n";
        std::cout << "Total Pixels: " << totalPixels << "\n";
        HistogramPrint("[0] Black Clipping", clipBlack, totalPixels);
        HistogramPrint("[1~25] Black", black, totalPixels);
        HistogramPrint("[26~76] Shadows", shadows, totalPixels);
        HistogramPrint("[77~178] Exposure", exposure, totalPixels);
        HistogramPrint("[179~229] Highlights", highlights, totalPixels);
        HistogramPrint("[230~254] Whites", whites, totalPixels);
        HistogramPrint("[255] White Clipping", clipWhites, totalPixels);
        std::cout << "======================================================\n\n";
	}
}