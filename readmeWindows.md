# TSAL installation on Windows

#### Currently TSAL is only supported on Cygwin.

#### There are two methods to install and build TSAL on Windows using Cygwin
1. Using our install script
2. Running a couple of commands

#### If you want to specify the installation directory, we advise you to use method 2.

### Installing Cygwin

1. Download [Cygwin](https://www.cygwin.com/)
2. Install the setup file; Continue until you get to the "Select Packages" window
   - **NOTE**: If the window crashes, open the setup file and follow the steps again
4. Click View > Not Installed
5. In the search box type `lynx` and click the dropdown next to "Skip" and select the last one
6. Do the same for `dos2unix` and `wget`
7. Click "Next" and finish the installation

![me](https://github.com/Calvin-CS/TSAL/blob/master/wiki_media/Cygwin.gif)

### Installing TSAL

## Method 1
* clone the [TSAL repository](https://github.com/Calvin-CS/TSAL.git)
* cd into the cloned folder
* run `./install-cygwin.sh`

## Method 2

Follow these steps on your terminal:
```
autoreconf -vi
./configure
make
make install
```
##### The above command will by default install TSAL in /usr/lib.
If you want to specify your installation directory use:
```
./configure --prefix=installdirectory
``` 
instead of `./configure` **replacing** `installdirectory` with your desired path.
