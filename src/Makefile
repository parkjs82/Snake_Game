CC      = g++
CFLAGS  = -std=c++17 -Wall

SRCS    := main.cpp \
           ./module/MakeField.cpp \
           ./module/Snake.cpp \
           ./module/Score.cpp \
           ./module/Shapes.cpp \
           ./module/Draw.cpp \
           ./module/Event.cpp

OBJS    := $(SRCS:.cpp=.o)

TARGET  = snake_game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lncurses

# 각 .o 파일을 대응하는 .cpp 파일로부터 생성
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
