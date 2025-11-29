# Splash Text!
This is a simple mod that adds some splash text like in Minecraft to your GD main menu!

# Creating Custom Splashes
To create custom splashes, create a file somewhere and give it
the file extension `.splash`, `.txt`, or `.text`. Making a splash
is as simple as just writing one per line. However, there are some
additional features which may help you in writing cooler splashes.

> [!WARNING]
> Only ASCII characters supported by `goldFont.fnt` are supported and
> **invalid characters will result in the file failing to be parsed.**
> If your file is failing to parse, the reason why will be outputted
> as an error in the developer console.

## Comments
You can add comments to the file which will be ignored by the mod.
To make one you simply type a hashtag `#` and all characters after it will
be ignored.

```
I'm a custom splash!
# This is a comment!

I have an inline comment! # Hello, world!
```

- The first line will be unmodified.
- The second line will be ignored.
- The third line will be ignored.
- The fourth line will be stripped of its inline comment.

## Macros
Additionally, there are some special macros you can use. These can
add some special flair to your splashes.
| Macro | Description |
| ----- | ----------- |
| \_\_LINE\_\_ | The line number in the file |
| \_\_PLAYER\_USERNAME\_\_ | The GD account username of the user |
| \_\_RANDOM\_\_ | Random number between 0 and 100 |

## Keywords (Date Range)
The most recent addition to the family! There are currently only two keywords.
These keywords denote the start and end of a *date range*. A date range is a selection
of splashes that will only appear when the system clock of the user is within the
specified range of dates where the date represents midnight of the specified day.

For example:
```
.DATERANGE 01-01 01-02
This splash can only appear on New Years!
./DATERANGE
```

Currently `.(/)DATERANGE` is the only keyword.
It is specified by using a dot (.) to indicate it is a keyword, then the keyword
itself (DATERANGE), when you want to end use of a date range, use the `DATERANGE`
keyword with a leading slash `./DATERANGE`. Additionally, you can nest date ranges
so only when the user is within *all* ranges can the splash appear.

> [!NOTE]
> For date ranges where the start of the range is *after* the end of the range,
> the end of the range is assumed to be in the following year. So, `09-01 08-28`
> is implcitily `09-01-CurrentYear 08-28-NextYear`

# Contributing
If you want to make this project better, just make a PR! :D