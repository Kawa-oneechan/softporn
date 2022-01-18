# Softporn Adventure

_An Unauthorized Rewrite by Kawa, who has absolutely no shame nor qualms._

### Why?

There are three older versions of *Softporn Adventure* out there:

* The Apple II BASIC original by Chuck Benton, famously sold by Sierra On-Line and then used as the basis for *Leisure Suit Larry in the Land of the Lounge Lizards*.
* One DOS rewrite in black and white, written in Pascal, _possibly_ also by Chuck Benton? I'm not sure.
* Another DOS rewrite in color, written by Gary Thompson, included in *Larry's Greatest Hits and Misses* by an impressed Al Lowe.

And then Kawa got inspired to take the Pascal version and rewrite it in C, initially just for Windows but with an eye on later portability.

### Any changes?

Well, it has the same subdued visual style as the Pascal version in that it's black and white, but with an Infocom-like redesign on the status line, and most immediately obvious:

* Almost every other line of prose has been rewritten to use about 90% fewer overly-excited exclamation marks.
* Some of the cheaper deaths have been removed.
* The entire parser has been replaced by one based on what *Larry* used.

### Future plans

* Linux version, using escape sequences. Perhaps a Windows 10/11 new-style Console version with the same. Either should be a matter of replacing `wincon.cpp`.
* *Larry Mode*, where more characters than just Eve get names and puzzles are changed to more closely resemble the game's more famous successor. Much more involved.



