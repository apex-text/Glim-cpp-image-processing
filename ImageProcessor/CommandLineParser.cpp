/**
 * @file CommandLineParser.cpp
 */

#include "CommandLineParser.h"
#include "Exceptions.h"

#include <iostream>
#include <string>
#include "Contrast.h"

namespace ip {

namespace {
    /// argv 의 다음 인자를 안전하게 가져온다.
    std::string nextArg(int argc, char* argv[], int& i, const std::string& flag) {
        if (i + 1 >= argc) {
            throw ArgumentError(flag + ": missing value");
        }
        return argv[++i];
    }
} // anonymous namespace

ProgramOptions CommandLineParser::parse(int argc, char* argv[]) {
    ProgramOptions options;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (arg == "--input" || arg == "-i") {
            options.inputPath = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--output" || arg == "-o") {
            options.outputPath = nextArg(argc, argv, i, arg);
        }
		else if (arg == "--pipeline" || arg == "-p") {
			options.pipeline = nextArg(argc, argv, i, arg);
		}
        else if (arg == "--filter" || arg == "-f") {
            options.filterName = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--threshold" || arg == "-t") {
            options.threshold = std::stoi(nextArg(argc, argv, i, arg));
        }
        else if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            std::exit(0);
        }
        else {
            throw ArgumentError("Unknown option: " + arg);
        }
    }

    // 필수 인자 검증
    if (options.inputPath.empty()) {
        throw ArgumentError("--input is required");
    }
    if (options.outputPath.empty()) {
        throw ArgumentError("--output is required");
    }
    if (options.pipeline.empty() && options.filterName.empty()) {
		throw ArgumentError("--pipeline or --filter are required"); // 둘 다 비어있으면 안 됨
    }

    return options;
}

void CommandLineParser::printUsage(const std::string& exeName) {
    std::cout
        << "Usage:\n"
        << "  " << exeName << " --input <path> --output <path> --filter <name> --pipeline <pipeline>\n\n"
        << "Options:\n"
        << "  -i, --input    <path>   Input BMP file (24-bit, uncompressed)\n"
        << "  -o, --output   <path>   Output BMP file\n"
        << "  -f, --filter   <name>   Filter to apply\n"
        << "  -p, --pipeline <pipeline> Pipeline of filters to apply (comma separated)\n"
        << "  -t, --threshold <val>   Threshold value (used with '-f threshold')\n"
        << "  -h, --help              Show this message\n\n"
        << "Available filters:\n"
        << "  grayscale               Convert image to grayscale\n"
        << "  threshold               Apply binary threshold (requires -t <val>)\n"
        << "  brightness:<val>        Adjust brightness (e.g. brightness:50)\n"
        << "  contrast:<val>          Adjust contrast (e.g. contrast:1.5)\n"
        << "  blur                    Apply convolution blur\n"
        << "  sharpen                 Apply convolution sharpen\n"
        << "  histogram               Equalize histogram\n"
        << "  crop:<x1> <y1> <x2> <y2> Crop image (e.g. crop:100 100 300 300)\n"
        << "  resize:<percent>        Resize image (e.g. resize:50)\n"
        << "  mirror:h / mirror:v     Horizontal or vertical flip\n\n"
        << "Examples:\n"
        << "  " << exeName << " -i input.bmp -o result.bmp -f grayscale\n"
        << "  " << exeName << " -i input.bmp -o result.bmp -f threshold --threshold 128\n"
        << "  " << exeName << " -i input.bmp -o result.bmp -f \"crop:100 100 300 300\"\n"
        << "  " << exeName << " -i input.bmp -o result.bmp -p \"grayscale,blur,threshold:128\"\n";
}

} // namespace ip
