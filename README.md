![C](res/c.png)
# cmics
The `C` based comics downloader.
## Installation
Clone the repository into somewhere disposable on your system. Run
```sh
cd ~/path/to/application/cmics/src
```
... install the prereques ...
```sh
# An example Debian system
sudo apt-get upgrade
sudo apt-get install libncurses5-dev libncursesw5-dev
sudo apt-get install libcurl4-gnutls-dev

# If python isn't already isntalled, run
sudo apt-get install python3-pip

# Finally, install python dependancies
pip3 install -r requirements.txt
```
and then run the make process.
```sh
make config    # This will configure some config header files before usage
make           # This will build the program
make install   # This will create the directories and move the binary to /usr/local/bin or equivalent
               # This may also require root
               
make clear     # This removes the repository. It just runs rm -rf ../../cmics (the default directory
               # that it is installed to. You could do it by hand if you prefer.
               # make clean will just remove the executable produced.
```

Voila! You're done!
If you want to make any changes to the source code, go ahead. 
## Maintinence
This code is completely open-source and modifiable under the BSD 3-term liscense. However, for best practice, it is reccomended that all changes or submissions follow the K&R bracing style, and comply to the ``gnu99 C` standard. As a warning: **GNU AND BSD INDENT WILL NOT FORMAT THIS CODE CORRECTLY!** They make errors because of the deeply-nested switch statements that form most of the menu and backend logic of this program.
## Updates
If you ran `make clear` during the install, re-clone the repository. Then do the following in the `/cmics/src`:
```sh
# if you removed or ran make clear
make config
make

# if you didn't remove the repository
make clean
make

# Everyone:
sudo make update
```
That's the entire update progress. 
## Usage
Simply call `cmics` from the command line. No arguments necessary. Or supported, for that matter.
## Inspiration
This is a `C` port of the earlier [comic-downloader](https://github.com/Barthandelous01/Comic-Downloader). All the features are ported, except for the CLI-argument based functionality. As a matter of fact, `python` is still a dependency for displaying images!
