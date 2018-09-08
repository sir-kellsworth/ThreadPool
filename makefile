GCC		= g++
MAKE		= make
OPTIMIZE	= -O2 -DSUPPORT_LH7 -DMKSTEMP
CFLAGS		= -std=c++11 -Winline -pipe -g
LDLIBS		= -lpthread

TheadPool.so : ThreadPool.cpp ThreadPool.h
	$(GCC) $(CFLAGS) -fPIC -shared ThreadPool.cpp -o libThreadPool.so.1 $(LDLIBS)
	mv libThreadPool.so.1 lib/

install :
	scp ThreadPool.h /usr/include/
	scp lib/libThreadPool.so.1 /usr/local/lib/libThreadPool.so
	chmod +x /usr/lib/libThreadPool.so
	ldconfig

uninstall :
	rm /usr/include/ThreadPool.h
	rm /usr/local/lib/libThreadPool.so

clean :
	rm libs/libThreadPool.so.1
