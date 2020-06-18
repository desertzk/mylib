INCLUDE=
CPPFLAGS=
CFLAGS=  -g -Wall
LDFLAGS= 
CC=g++
#CC=arm-linux-gcc
#MODULE_DIR=$(shell pwd)                                                                                                                                                                                                                 
#MODULE=$(notdir $(MODULE_DIR))
src = $(wildcard *.cpp)
obj = $(patsubst %.cpp,%.o,$(src))
target = netsetup
multi:          
	make  $(target)
$(target):$(obj)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.cpp
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

.PHONY:clean

#彻底清除生生过程文件
clean:
	-rm -f *.o
	-rm -f $(target)

#彻底清除生生过程文件和生成配置文件
distclean:
	rm /usr/bin/app
install:
	cp app  /usr/bin


test:
	@echo $(src)
	@echo $(obj)
	@echo $(target)

