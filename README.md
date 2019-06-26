# TSAL

A Thread Safe Audio Library that uses audiolizations to assist in the understanding of concurrent and parallel processing.

## Getting Started

TSAL uses the GNU Autotools build system to build and install the library.

### Prerequisites

Install RtAudio (this should maybe just be included in the src dir)

Install autotools (`autoconf`, `automake`, and `libtool`) on your system. For Windows, a building environment like MSYS2 is recommended

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

* [RtAudio](https://github.com/thestk/rtaudio) - Audio API
* [Midifile](https://github.com/craigsapp/midifile) - Midi processing
  
## License

TODO license
