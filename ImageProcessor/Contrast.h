#pragma once
#include "ImageBuffer.h" // 이미지를 처리해야 하므로 ImageBuffer를 알아야 합니다.

namespace ip {

    class ContrastFilter {
    public:
        // 기본 생성자
        ContrastFilter() = default;

        // 핵심 기능: 이미지를 받아서 흑백으로 변환하는 함수
        // 참조(&)를 사용하여 원본 이미지를 직접 수정하도록 설계해 봅니다.
        void process(ImageBuffer& image, float contrast);
    };
}