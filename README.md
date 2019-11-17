# TSAL

A Thread Safe Audio Library that uses audiolizations to assist in the understanding of concurrent and parallel processing.

## Getting Started

TSAL uses the GNU Autotools build system to build and install the library.

### Prerequisites

Install [PortAudio](http://www.portaudio.com/)

Install autotools (`autoconf`, `automake`, and `libtool`). For Windows, a build environment like MSYS2 is recommended

### Build

Once the prerequisites have been met, building TSAL should follow the Autotools workflow

```console
autoreconf -vi
./configure
make
```

This will compile all the necessary files, tests, and examples for the project

To install the library on your system run `make install` as root.

## Running the tests

Use `make check` to run the tests

## Built With

* [PortAudio](http://www.portaudio.com/) - Audio API
* [Midifile](https://github.com/craigsapp/midifile) - MIDI processing
* [TinySoundFont](https://github.com/schellingb/TinySoundFont) - SoundFont player
  
## License

This project is licensed under the GNU General Public License - see the [LICENSE](LICENSE) file for details
