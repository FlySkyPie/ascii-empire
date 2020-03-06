#!/bin/bash
#PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
echo "Starting compile your soure code...... \n"
g++ -c main.cpp -o main.o -Wall -lncurses -std=gnu++11 -pthread
g++ -c Objects.cpp -o Objects.o -Wall -lncurses -std=gnu++11 -pthread
g++ -c Empire_B.cpp -o Empire_B.o -Wall -lncurses -std=gnu++11 -pthread
g++ -c Empire_D.cpp -o Empire_D.o -Wall -lncurses -std=gnu++11 -pthread
g++ -c Empire_G.cpp -o Empire_G.o -Wall -lncurses -std=gnu++11 -pthread
g++ -c Empire_R.cpp -o Empire_R.o -Wall -lncurses -std=gnu++11 -pthread
g++ -c Empire_W.cpp -o Empire_W.o -Wall -lncurses -std=gnu++11 -pthread
g++ main.o Objects.o Empire_B.o Empire_D.o Empire_G.o Empire_R.o Empire_W.o -o Empire.o -Wall -lncurses -std=gnu++11 -pthread
echo "Compile finish \n"
read -n1 -r -p "Press any key to continue..." key
./Empire.o
exit 0
