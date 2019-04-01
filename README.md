# iridium-wallet

![iridium logo](https://ird.cash/wp-content/uploads/2019/01/iridium.svg)

Iridium is a cryptonight based cryptocurrency (ticker : IRD)

This is the iridium gui wallet source code and binary release for MacOs, Windows and linux

[Main website](http://ird.cash)

[BitcoinTalk main announcement thread](https://bitcointalk.org/index.php?topic=2150442.0;all)

[Iridium core (source and binaries)](https://github.com/iridiumdev/iridium)

[iridium graphicals elements](https://github.com/iridiumdev/iridium-graphics)

Compilation tips : 

Dependencies needed : boost >= 1.58, CMake >= 3.1, GCC >=4.7.3, Qt >=5.0

Currently built release is compiled with boost 1.60 and Qt 5.10


**development branch is now the default behavior, with blood and tears.**

If you want to compile the latest stable release, currently in production, clone the master branch :
```
git clone -b master clone https://github.com/iridiumdev/iridium-wallet.git
```

* Clone the repository :
```
$ git clone -b master clone https://github.com/iridiumdev/iridium-wallet.git
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
