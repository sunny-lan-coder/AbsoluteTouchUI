# AbsoluteTouch

Synaptics "absolute mode" emulation in software. Ever wanted to use
your laptop touchpad to play osu!, or to draw your signature? Well,
now you can!

## Requirements

- A Synaptics touchpad
- Synaptics COM libraries (if you installed the drivers, you probably have this)

## Notes

- While absolute mode is active, your touchpad can only be used to move the
cursor -- clicking, scrolling, gestures, etc. will be disabled.
- If your cursor does not move in-game, you may have to disable raw input mode.

## Command-line arguments

| Argument         | Description                                                                    |
|------------------|--------------------------------------------------------------------------------|
| `-t x1,y1,x2,y2` | Sets the mapped touchpad region (x1 = left, y1 = top, x2 = right, y2 = bottom) |
| `-s x1,y1,x2,y2` | Sets the mapped screen region (see above)                                      |
| `-w weight`      | Sets the touch smoothing factor (0 to 1, 0 for no smoothing)                   |
| `-m`             | Enables your touchpad when the program starts, and disables it on exit         |
| `-d`             | Enables debug mode (reduces performance, disable if you get mouse lag)         |

## License

Distributed under the [MIT License](http://opensource.org/licenses/MIT).
