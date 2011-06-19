# TODO
- signal handling
- turn either 1 or 3 cards to the waste pile (configurable)
- {cursor,label,hacker} mode (configurable)
- undo

## For 1.0
- [ ] explicit non-support for non-colored terminals (autoconf, ncurses)
- [ ] make it somewhat portable
- [x] handle screen resizing
- [x] number of passes through the stock (configurable)

## Ideas
- pure ascii interface for old terminal emulators
- automatic moving of cards (think windows solitaire)
- move without cursor (a digit for each stack)
- move like a hacker (e.g 'm03m2' == move 3 cards from maneuvre 0 to maneuvre 2)
