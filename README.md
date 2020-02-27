![C](res/c.png)
# cmics
The `C` based comics downloader.
## Installation
Clone the repository into somewhere disposable on your system. Run
```sh
cd ~/path/to/application/cmics/
```
and then run the makefiles.
```sh
make config # This will configure some config header files before usage
make           # This will build the program
make install   # This will create the directories and move the binary to /usr/local/bin or equivalent
```

Voila! You're done!
## usage
Simply call `cmics` from the command line. No arguments necessary.
## Inspiration
This is a `C` port of the earlier [comic-downloader](https://github.com/Barthandelous01/Comic-Downloader). All the features are ported, except for the CLI-argument based functionality. As a matter of fact, `python` is still a dependency for displaying images!
