#Bowling game example.

##Build:
1. Clone repo.
2. mkdir build
3. cd build 
4. cmake ..
5. make -j

##Test:
1. cmake -V

##Debug:
1. mkdir debug
2. cd debug
3. cmake -DCMAKE_BUILD_TYPE=DEBUG ..
4. make -j
5. gdb ./BowlingGame
   gdb ./BowlingGame-ut