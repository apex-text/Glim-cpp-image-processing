# ImageProcessor 과제 제출

## 구현 항목

- 흑백(Grayscale) 필터 (`grayscale`)
- 이진화(Threshold) 필터 (`threshold` 또는 `threshold:<value>`)
- 밝기 조절(Brightness) 필터 (`brightness:<value>`)
- 대비 조절(Contrast) 필터 (`contrast:<value>`)
- 블러(Blur) 필터 (`blur`)
- 샤픈(Sharpen) 필터 (`sharpen`)
- 히스토그램(Histogram) 처리 (`histogram`)
- 크롭(Crop) 필터 (`"crop:<startX> <startY> <endX> <endY>"`)
- 리사이즈(Resize) 필터 (`resize:<percent>`)
- 반전(Mirror) 필터 (`mirror:h` 또는 `mirror:v`)

### 심화 항목
 - 필터 파이프라인 체인 다중 필터 적용 (`--pipeline`)
 - 추상 클래스 기반 설계 (`FilterBase`)


## 실행 명령어 (예시)

<!-- 예시 입니다. 기존 예시를 지우고 구현한 항목에 맞게 명령어를 작성해주세요. -->

```powershell
# Grayscale 변환
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_grayscale.bmp --filter grayscale
```

```powershell
# Blur 처리 + 임계값 지정
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_blur_threshold.bmp --filter blur --threshold 128
```

```powershell
# 필터 파이프라인 체인(고급)
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\Resource\3_chelsea_cat_pipeline.bmp --pipeline "grayscale, blur, threshold:128"
```

```powershell
# 샤픈 처리
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_sharpen.bmp --filter sharpen
```

```powershell
# 밝기 조절 (예: 50 증가)
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_brightness.bmp --filter brightness:50
```

```powershell
# 크롭 처리 (예: x1:100 y1:100 x2:400 y2:400)
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\Resource\3_chelsea_cat_crop.bmp --filter "crop:100 100 400 400"
```

```powershell
# 좌우 반전 처리
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_mirror.bmp --filter mirror:h
```
