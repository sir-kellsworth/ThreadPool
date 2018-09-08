Just a simple thread pool library. Make sure to use c++11 or greater to use this library.
To compile this project follow these steps:

make
sudo make install

then include it in your project using this flag:
-lThreadPool

Should be awesome, only tested this on ubuntu 16.04 and 18.04, so thats all I think it
would work on. However, it would probably work on any linux distro.
No, I seriously doubt it would work on windows.

Right now, it will only allow a max of 16 active threads. If you want more or less, change
the MAX_THREADS variable in ThreadPool.h
