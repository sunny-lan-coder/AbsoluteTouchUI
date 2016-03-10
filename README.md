# AbsoluteTouch

Synaptics "absolute mode" emulation in software. Ever wanted to use
your laptop touchpad to play osu!, or to draw your signature? Well,
now you can!

## Requirements

- A Synaptics touchpad
- Synaptics COM libraries (if you installed the drivers, you probably have this)

## Notes

- You must disable raw input in the target program!
- While absolute mode is active, your touchpad can only be used to
move the cursor -- clicking, scrolling, gestures, etc. will be disabled.

## Command-line arguments

| Argument      | Description                                                            |
|---------------|------------------------------------------------------------------------|
| `-w <width>`  | Sets the width of the mapped screen region (in pixels).                |
| `-h <height>` | Sets the height of the mapped screen region (in pixels).               |
| `-t`          | Enables your touchpad when the program starts, and disables it on exit |

## License

Distributed under the [MIT License](http://opensource.org/licenses/MIT).
