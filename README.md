# tty-solitaire
  ncurses-based klondlike solitaire game.

## Dependencies
  - Terminal emulator with UTF-8 support
  - C library with multibyte locales support
  - libncurses compiled with wide-char/UTF-8 code

## Usage
    usage: ttysolitaire [-v|--version] [-h|--help] [-p|--passes=NUMBER]
      -v, --version  Show version
      -h, --help     Show this message
      -p, --passes   Number of passes through the deck

## Running the game
    $ git clone https://github.com/mpereira/tty-solitaire.git
    $ cd tty-solitaire
    $ make && ./ttysolitaire

## Screenshots
![Greeting screen picture](http://dl.dropbox.com/u/14256545/tty_solitaire_screenshot_shadowed_0.png)
![Game start picture](http://dl.dropbox.com/u/14256545/tty_solitaire_screenshot_shadowed_1.png)
![Game middle picture](http://dl.dropbox.com/u/14256545/tty_solitaire_screenshot_shadowed_2.png)

## Running the unit tests
    $ make test

## Author
   [Murilo Pereira](http://murilopereira.com)

## License
   Released under the
   [MIT license](http://github.com/mpereira/embratel/blob/master/MIT-LICENSE).
