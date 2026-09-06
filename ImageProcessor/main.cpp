/**
 * @file main.cpp
 * @brief ImageProcessor 진입점 — 지원자가 작성해야 할 파일입니다.
 *
 * BMP 입출력과 커맨드라인 파싱은 제공된 코드가 처리합니다.
 * 본 과제에서 작성해야 할 것은 단 하나입니다:
 *
 *     ▶ 이미지 처리 필터 2개 이상 구현 + main 의 TODO 위치에 연결
 *
 * 또한 일관된 컨벤션과 예외 처리, 메모리 안정성도 함께 평가됩니다.
 */

#include "BmpParser.h"
#include "CommandLineParser.h"
#include "ImageBuffer.h"
#include "Exceptions.h"

#include <iostream>

 // TODO: 본인이 구현한 필터 헤더를 include 하세요.
#include "FilterBase.h"
#include "GrayscaleFilter.h"
#include "ThresholdFilter.h"
#include "Brightness.h"
#include "Contrast.h"
#include "Convolution.h"
#include "Histogram.h"
#include "CropFilter.h"
#include "ResizeFilter.h"
#include "Mirror.h"
#include <vector>
#include <memory>
#include <sstream>
#include <string>


int main(int argc, char* argv[]) {
    try {
        // ── CLI 인자 파싱 (제공된 코드) ─────────────────────────
        const ip::ProgramOptions options = ip::CommandLineParser::parse(argc, argv);

        // ── BMP 로드 (제공된 코드) ──────────────────────────────
        ip::ImageBuffer image = ip::BmpParser::loadFromFile(options.inputPath);
        std::cout << "Loaded: " << image.width() << " x " << image.height() << "\n";

        // ───────────────────────────────────────────────────────
        // TODO: options.filterName 에 따라 적절한 필터를 생성하고
        //       image 에 적용하세요.
        //
        //   예시 코드 (참고용):
        //
        //     if (options.filterName == "grayscale") {
        //         GrayscaleFilter filter;
        //         filter.apply(image);
        //     }
        //     else if (options.filterName == "threshold:128") {
        //         ThresholdFilter filter(128);
        //         filter.apply(image);
        //     }
        //     else {
        //         throw ip::FilterError("Unknown filter: " + options.filterName);
        //     }
        //
        //   ※ 가산점 항목:
        //     - 추상 클래스(FilterBase) 기반 다형성 설계
        //     - 필터 파이프라인 체인 (CLI 옵션 확장 필요)
        //     - 멀티쓰레드 처리
        //     - 로그 파일 출력 (CLI 옵션 확장 필요)
        // ───────────────────────────────────────────────────────

        // ↓ 여기에 필터 적용 코드를 작성하세요.

		std::vector<std::unique_ptr<ip::FilterBase>> pipeline;
        std::string pipelineStr = options.pipeline;
		std::stringstream ss(pipelineStr);
        std::string command;

        if (!options.pipeline.empty()) {
            while (std::getline(ss, command, ',')) {
                if (command == "grayscale") {
                    pipeline.push_back(std::make_unique<ip::GrayscaleFilter>());
                }
                else if (command == "blur") {
                    pipeline.push_back(std::make_unique<ip::ConvolutionFilter>());
                    dynamic_cast<ip::ConvolutionFilter*>(pipeline.back().get())->setBlurKernel();
                }
                else if (command == "sharpen") {
                    pipeline.push_back(std::make_unique<ip::ConvolutionFilter>());
                    dynamic_cast<ip::ConvolutionFilter*>(pipeline.back().get())->setSharpenKernel();
                }
                else if (command == "histogram") {
                    pipeline.push_back(std::make_unique<ip::Histogram>());
                }
                else if (command.find("crop:") != std::string::npos) {
                    // Parse crop parameters (startX, startY, endX, endY)
                    std::stringstream ss(command.substr(5));
                    int startX, startY, endX, endY;
                    ss >> startX >> startY >> endX >> endY;
                    pipeline.push_back(std::make_unique<ip::CropFilter>(startX, startY, endX, endY));
                }
                else if (command.find("resize:") != std::string::npos) {
                    int percent = std::stoi(command.substr(7));
                    pipeline.push_back(std::make_unique<ip::ResizeFilter>(percent));
                }
                else if (command == "mirror:v") {
                    pipeline.push_back(std::make_unique<ip::MirrorFilter>(ip::MirrorMode::Vertical));
                }
				else if (command == "mirror:h") {
					pipeline.push_back(std::make_unique<ip::MirrorFilter>(ip::MirrorMode::Horizontal));
				}
                else if (command.find("threshold:") != std::string::npos) {
                    int threshold = std::stoi(command.substr(10));
                    pipeline.push_back(std::make_unique<ip::ThresholdFilter>(threshold));
                }
                else if (command.find("brightness:") != std::string::npos) {
                    int brightness = std::stoi(command.substr(11));
                    pipeline.push_back(std::make_unique<ip::BrightnessFilter>(brightness));
                }
                else if (command.find("contrast:") != std::string::npos) {
                    float contrast = std::stof(command.substr(9));
                    pipeline.push_back(std::make_unique<ip::ContrastFilter>(contrast));
                }
                else {
                    throw ip::FilterError("Unknown filter in pipeline: " + command);
                }
            }
            for (const auto& filter : pipeline) {
                filter->process(image);
            }
        }


        else {
            if (options.filterName == "grayscale") { //-----------------흑백 처리-------
                ip::GrayscaleFilter filter;
                filter.process(image);
            }
            else if (options.filterName == "threshold") { //---이진화 처리-----
                uint8_t userThreshold = options.threshold;
                ip::ThresholdFilter filter(userThreshold);
                filter.process(image);
            }
            else if (options.filterName.find("brightness:") != std::string::npos) { //---밝기 조절------
                int userBrightness = std::stoi(options.filterName.substr(11));
                ip::BrightnessFilter filter(userBrightness);
                filter.process(image);
            }
            else if (options.filterName.find("contrast:") != std::string::npos) { //-----대비 조절------
                float userContrast = std::stof(options.filterName.substr(9));
                ip::ContrastFilter filter(userContrast);
                filter.process(image);
            }
            else if (options.filterName == "blur") { // -----------------블러-----------
                ip::ConvolutionFilter filter;
                filter.setBlurKernel();
                filter.process(image);
            }
            else if (options.filterName == "sharpen") { // -----------------샤픈--------
                ip::ConvolutionFilter filter;
                filter.setSharpenKernel();
                filter.process(image);
            }
            else if (options.filterName == "histogram") { // -----------히스토그램------
                ip::Histogram filter;
                filter.process(image);
            }
            else if (options.filterName.find("crop:") != std::string::npos) { // -----------------크롭 처리------
				std::string cropParams = options.filterName.substr(5); // "crop:" 이후의 문자열
                int startX = 0, startY = 0, endX = 0, endY = 0;
                std::stringstream ss(cropParams);
                if (ss >> startX >> startY >> endX >> endY) {
                    ip::CropFilter filter(startX, startY, endX, endY);
                    filter.process(image);
				}
                else {
                    throw ip::FilterError("Invalid crop parameters: " + cropParams);
                }
            }
            else if (options.filterName.find("resize:") != std::string::npos) { // ------------리사이즈 처리------
                int percent = std::stoi(options.filterName.substr(7));
                ip::ResizeFilter filter(percent);
                filter.process(image);
            }
            else if (options.filterName.find("mirror:") != std::string::npos)   { // ---------------미러 처리------
				char mode = options.filterName.back(); // 마지막 문자를 가져옴
				if (mode == 'h') {
					ip::MirrorFilter filter(ip::MirrorMode::Horizontal);
					filter.process(image);
				}
				else if (mode == 'v') {
					ip::MirrorFilter filter(ip::MirrorMode::Vertical);
					filter.process(image);
				}
				else {
					throw ip::FilterError("Unknown mirror mode: " + std::string(1, mode));
				}
            }
            else {
                throw ip::FilterError("Unknown filter: " + options.filterName);
            }

        }


        // ── BMP 저장 (제공된 코드) ──────────────────────────────
        ip::BmpParser::saveToFile(options.outputPath, image);
        std::cout << "Saved:  " << options.outputPath << "\n";
        return 0;
    }
    catch (const ip::ArgumentError& e) {
        std::cerr << e.what() << "\n\n";
        ip::CommandLineParser::printUsage(argc > 0 ? argv[0] : "ImageProcessor");
        return 4;
    }
    catch (const ip::BmpParseError& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    catch (const ip::FilterError& e) {
        std::cerr << e.what() << std::endl;
        return 3;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}
