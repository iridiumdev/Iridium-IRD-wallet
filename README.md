# iridium-wallet

![iridium logo](https://avatars1.githubusercontent.com/u/31619794?s=460&v=4)

Iridium is a cryptonight based cryptocurrency (ticker : IRD)

This is the iridium gui wallet source code and binary release for MacOs, Windows and linux

[Main website](http://ird.cash)

[BitcoinTalk main announcement thread](https://bitcointalk.org/index.php?topic=2150442.0;all)

[Iridium core (source and binaries)](https://github.com/iridiumdev/iridium)

[iridium graphicals elements](https://github.com/iridiumdev/iridium-graphics)

Compilation tips : 

Dependencies needed : boost >= 1.58, CMake >= 3.1, GCC >=4.7.3, Qt >=5.0

Currently built release is compiled with boost 1.60 and Qt 5.10

* Clone the repository :
```
$ git clone https://github.com/iridiumdev/iridium-wallet.git
```
  
* Update core submodule :
```
$ cd iridium-wallet
$ git submodule update --init
$ git submodule foreach git pull origin master
```
* Build :
```
$ mkdir build
$ cd build
$ cmake -DSTATIC=ON -DCMAKE_BUILD_TYPE=RELEASE ..
$ make
```
* Trouble :
  * Cmake complain not finding boost libs : specify your boost installation path :
  ```
    -DBOOST_ROOT="Your_boost_root_path"
  ```
  * Cmake complain not finding Qt libs : specify your Qt installation path :
  ```
    -DBOOST_ROOT="Your_Qt_root_path"
  ```
  * Your Processor is quiet old and doesn't support aes or avx :
  ```
    $ PORTABLE=1 make
  ```
