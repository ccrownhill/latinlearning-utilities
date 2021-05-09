# Latin learning utilities

Note that for vocabulary formats the code in this repo is specifically designed for exported Anki decks in text format with the fields being separated by tabs (That's also why in `latinlaunch.c` certain html elements are removed from the words since those usually appear in these `.txt` Anki decks).

## latinlaunch

```
latinlaunch -n/--numvoc numvoc -f/--vocfile filename.csv command
```

Latinlaunch uses `latinlearn.py` to execute any given command with also asking for a specified number of latin words before that program is opened.

To automatically install so that when executing programs like `firefox` you are always being asked latin vocabulary use

```
$ sh latinlaunch_install.sh
```

Note that you can configure `latinlaunch_install.sh` to tell it where the tab separated vocabulary file is located, how many words should be asked and which applications should be started via `latinlaunch`.

## latinlearn.py

```
latinlearn.py -n num_vocs vocfilename
```

This program will ask for a specified number of latin words (their meanings) while choosing these words randomly from a tab separated vocabulary file.
