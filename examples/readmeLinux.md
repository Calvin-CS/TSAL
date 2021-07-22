# TSAL installation on Linux

#### There are two methods to install and build TSAL on Linux
1. Using our install script
2. Running a couple of commands

#### Both methods install TSAL by default in /usr/lib. If you want to specify the installation directory, we advise you to use method 2.

## Method 1
* clone the [TSAL repository](https://github.com/Calvin-CS/TSAL.git)
* cd into the cloned folder
* run `./install-ubuntu.sh`

## Method 2

Follow these steps on your terminal:
```
autoreconf -vi
./configure
make
make install
```

If you want to specify your installation directory use:
```
./configure --prefix=installdirectory
``` 
instead of `./configure` **replacing** `installdirectory` with your desired path.
