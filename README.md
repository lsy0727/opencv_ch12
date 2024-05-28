# opencv_ch12 (레이블링, 외곽선 검출)

opencv_ch12-1

1 - 영상파일에서 면적이 최대인 객체와 최소인 객체를 찾고, 무게중심을 구함
  1) 영상 레이블링 수행 (컬러->그레이->이진화(반전))
  2) 면적이 최대인 객체와 최소인 객체를 찾고, 레이블과 무게중심 저장
  3) 객체가 내접하는 바운딩 박스를 그림 (작은 객체 : 파란색, 큰 객체 : 빨간색)

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/a15f4c17-00ea-4349-860e-ebdc42fdc02f)

2 - 영상파일에서 레이블 수, 바운딩 박스 정보, BGR값 출력 후 영상에 바운딩 박스와 레이블 값 그리기
  1) 영상 레이블링 수행
  2) 노란색 바운딩 박스
  3) 객체의 무게중심 위치에 노란색 레이블 값 삽입

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/abffa367-a5ca-4eed-bb53-4cca0b6fb664)

3 - 영상파일에서 객체의 무게중심 출력 (계산 값과 레이블링 함수를 이용한 값 비교)
무게중심 = (객체영역에 포함된 모든 x(or y)좌표의 합) / (객체영역의 총 픽셀 수)
  1) 영상 레이블링 수행
  2) 무게중심 계산 후 출력
  3) 출력 값 비교 -> 비슷함

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/822b9d55-d002-49db-8d79-93dbd3dbf2dd)

4 - 자동차 영상에서 번호판 영역을 검출하고, 바운딩 박스 그리기
  1) 영상 레이블링 수행(배경도 외곽선으로 검출되는 것을 막기위해 영상반전)
  2) 번호판 영역이 가장 잘 검출되는 임계값 설정
  3) 면적이 최대인 객체를 찾음 (번호판 영역)
  4) 찾은 객체에 빨간색 바운딩 박스를 그림

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/b419e677-7b99-4022-b111-15a3263c3bb0)

========================================================================================================================================================================================

opencv_ch12-2

1 - 영상파일에서 객체의 외곽선 그려주는 프로그램
  1) 영상 레이블링 수행
  2) findContours()함수로 외곽선 검출
  3) drqwContours()함수로 와곽선 그리기

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/ad9ac57b-fea9-41e9-9e1d-d570c7984487)

2 - Mat 객체에 저장된 영상의 모든 외곽선을 찾아 각 외곽선을 구성하는 점들 출력
  1) unsigned char 형식의 8x8 배열 생성, 이진 이미지(0:검정색, 1:흰색)
  2) data배열을 이용해 8비트 1채널 형식의 행렬 생성, 그레이스케일(0->1, 1->255)
  3) 검출된 외곽선들의 개수, n번째 외곽선의 점들의 좌표 출력

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/88af077b-1789-40f5-80bf-12c29f9ef03f)

3 - 검출된 객체의 외곽선을 그려주는 함수인 drqwContours()함수 구현
  1) 영상 레이블링 수행
  2) findContours()함수로 외곽선 검출
  3) 그레이영상을 BGR컬러영상으로 변환(외곽선 색을 구분하기 위함)
  4) line()함수로 외곽선 그리기

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/501a3b24-c7dd-43df-bd78-d5acacd1025e)

4 - 영상파일에서 검출된 외곽선들의 길이를 출력하고, 길이가 최대인 외곽선을 찾아 외곽선 그리기
  1) 영상 레이블링 수행
  2) findContours()함수로 외곽선 검출
  3) 외곽선 길이 비교(외곽선의 길이는 외곽선의 점의 개수와 같기 때문에 점의 개수를 구함)
  4) 길이가 가장 긴 외곽선 그리기
  5) 가장 긴 외곽선 정보 출력

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/2e28c2af-e7f7-4e1b-a2da-30f4995644ff)

5 - 영상파일에서 객체가 열려있는 방향을 구하고, 왼쪽이면 파란색, 오른쪽이면 빨간색 외곽선 그리기
  1) 영상 레이블링 수행
  2) findContours()함수로 외곽선 검출
  3) 무게중심을 구하기위해 connectedComponentsWithStats()함수를 사용(stats : 통계 정보를 담은 행렬, centroids : 무게 중심 좌표를 담은 행렬)
  4) 객체가 열려있는 방향을 구하기 위해 무게중심을 구함(pt_x에 x 좌표 저장 - 좌우방향만 구하기 때문에 x좌표만 저장함)
  5) 무게중심이 객체의 중앙을 기준으로 왼쪽에 있는지 오른쪽에 있는지 구분, 외곽선 그리기

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/dd83be45-3e22-49c3-a21c-5bcf9b7f8beb)

========================================================================================================================================================================================

opencv_chap12-3

1 - 바운딩박스:빨간색, 최소면적사각형:파란색, 최소면적원:노란색으로 그리기
  1) 영상 레이블링 수행
  2) 바깥쪽 외곽선을 검출하기위해 findContours()함수의 2번째 인자에 RETR_EXTERNAL
  3) boundingRect()함수로 바운딩 박스 그림
      boundingRect() : 바운딩 박스를 그림
  5) 0번 객체에 대한 사각형 정보를 구함
      minAreaRect() : 특정 외곽선을 감싸는 가장 작은 면적의 사각형 정보 반환
  6) 각 점들을 잇는 선 그리기
  7) 0번 객체에 대한 원의 정보를 구하고 원을 그림
      minEnclosingCircle() : 객체, 센터, 반지름을 요소로 가짐

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/e6a01b29-906f-450d-9711-99de6ba4d9d3)

2 - 영상에서 문자의 기울어진 각도를 찾고, 똑바로 보이도록 수정하여 출력
  1) 영상 레이블링 수행
  2) 외곽선 검출
  3) 각도를 구함
      RotatedRect 클래스에는 중심점, 각도, 사이즈 정보가 저장되어있음
  4) 기울어진 각도만큼 영상을 회전변환하고, 회전으로 인해 생긴 빈 공간들을 영상의 가장자리 요소로 채움
      BORDER_REPLICATE : 나머지 공간을 영상의 가장자리 요소로 채움

![image](https://github.com/lsy0727/opencv_ch12/assets/92630416/dd572973-82d3-4c5f-bc21-b898460ed893)

3 - 영상 파일에서 삼각형, 사각형, 오각형, 육각형, 원의 개수를 각각 구하여 출력, 모든 도형의 외곽선을 그림
  1) 
