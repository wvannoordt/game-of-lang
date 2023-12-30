# sudo apt-get install libsfml-dev

flags := 
flags += -g -O3
flags += -std=c++23

sanny := 0
ifeq (${sanny},1)
flags += -fsanitize=undefined,address -fstack-protector-all
endif

main:
	g++ ${flags} -I./src main.cc -o a.x -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f ./a.x
