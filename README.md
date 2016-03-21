# AbsoluteTouch

Synaptics "absolute mode" emulation in software. Ever wanted to use
your laptop touchpad to play osu!, or to draw your signature? Well,
now you can!

## Requirements

- A Synaptics touchpad
- Synaptics COM libraries (if you installed the drivers, you probably have this)

## Notes

- You must disable raw input in the target program!
- While absolute mode is active, your touchpad can only be used to move the
cursor -- clicking, scrolling, gestures, etc. will be disabled.

## Command-line arguments

| Argument         | Description                                                                    |
|------------------|--------------------------------------------------------------------------------|
| `-t x1,y1,x2,y2` | Sets the mapped touchpad region (x1 = left, y1 = top, x2 = right, y2 = bottom) |
| `-s x1,y1,x2,y2` | Sets the mapped screen region (see above)                                      |
| `-m`             | Enables your touchpad when the program starts, and disables it on exit         |
| `-d`             | Enables debug mode (reduces performance, disable if you get mouse lag)         |

## License

Distributed under the [MIT License](http://opensource.org/licenses/MIT).
