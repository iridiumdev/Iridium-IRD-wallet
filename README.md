# iridium-wallet

![iridium logo](https://avatars1.githubusercontent.com/u/31619794?s=460&v=4)

Iridium is a cryptonight based cryptocurrency (ticker : IRD)

This is the iridium gui wallet source code and binary release for MacOs, Windows and linux

[Main website](http://ird.cash)

[BitcoinTalk main announcement thread](https://bitcointalk.org/index.php?topic=2150442.0;all)

[Iridium core (source and binaries)](https://github.com/iridiumdev/iridium)

[iridium graphicals elements](https://github.com/iridiumdev/iridium-graphics)

Compilation tips : 

```
$ git clone https://github.com/iridiumdev/iridium-wallet.git
$ cd iridium-wallet
$ git submodule update --init
$ git submodule foreach git pull origin master // update the core code to latest commit 
$ mkdir build
$ cd build
$ cmake -D STATIC=ON -D CMAKE_BUILD_TYPE=RELEASE ..
$ PORTABLE=1 make
```
