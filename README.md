# Snake_Game
## 2022년 C++프로그래밍  프로젝트
* 팀 멤버:

| 이름   | 학번     |
|--------|----------|
| 김태경 | 20191576 |
| 박준서 | 20191599 |
| 엄석현 | 20191623 |


## ⚡ 빠른 시작

### 1. 의존성 설치
```bash
# Ubuntu/Debian
sudo apt-get install build-essential libncurses5-dev

# CentOS/RHEL  
sudo yum install gcc-c++ ncurses-devel

# macOS
brew install ncurses
```

### 2. 빌드 및 실행
```bash
cd snake_game_improved

# 의존성 확인
make deps

# 빌드
make all

# 실행
make run
```

### 3. 추가 옵션
```bash
make           # 빌드
make clean     # 정리
```

## 🎮 게임 특징

### 조작법
- **이동**: WASD 또는 화살표 키
- **일시정지**: P 또는 스페이스바  
- **종료**: Q 또는 ESC

### 게임 요소
- **4개 레벨**: Plain → Cross → Circle → Final
- **미션 시스템**: 각 레벨별 달성 목표
- **아이템**: 성장(+), 독(-), 게이트(G)
- **실시간 스코어**: 시간 + 아이템 점수

## 📁 프로젝트 구조

```
snake_game_improved/
├── src/
│   ├── main.cpp                 # 100줄 미만의 깔끔한 메인
│   ├── core/Game.{h,cpp}        # 게임 로직 관리 (Singleton)
│   ├── components/              # 게임 컴포넌트들
│   ├── interfaces/              # 추상 인터페이스들
│   ├── rendering/               # 렌더링 구현체
│   ├── input/                   # 입력 처리 구현체
│   └── utils/                   # 상수 및 설정
├── maps/                        # 게임 맵 파일들
├── Makefile                     # 현대적 빌드 시스템
└── README.md                    # 상세한 프로젝트 문서
```
