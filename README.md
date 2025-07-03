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