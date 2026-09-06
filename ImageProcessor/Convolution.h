#pragma once
#include "ImageBuffer.h" // 이미지를 처리해야 하므로 ImageBuffer를 알아야 합니다.
#include "FilterBase.h"

namespace ip {

    class ConvolutionFilter : public FilterBase {
    private:
        float m_kernel[3][3];

    public:
        // 함수 생성

        void setBlurKernel();
        void setSharpenKernel();
        

        // ImageBuffer 의 참조로 원본 이미지 직접 수정
        void process(ImageBuffer& image) override;
    };
}