# TSAL installation on macOS

#### There are two methods to install and build TSAL on MacOS
1. Using our install script
2. Running a couple of commands

#### If you want to specify the installation directory, we advise you to use method 2.

## Method 1
* clone the [TSAL repository](https://github.com/Calvin-CS/TSAL.git)
* cd into the cloned folder
* run `. install-mac.sh` --> (there is a space after the dot)

## Method 2

Follow these steps on your terminal:
```
autoreconf -vi
./configure
make
make install
```
##### The above command will by default install TSAL in /usr/local/lib.
If you want to specify your installation directory use:
```
./configure --prefix=installdirectory
``` 
instead of `./configure` **replacing** `installdirectory` with your desired path.
