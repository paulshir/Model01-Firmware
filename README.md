# paulshir's Keyboardio Model01 firmware
[![Build Status](https://travis-ci.org/paulshir/Model01-Firmware.svg?branch=paulshir)](https://travis-ci.org/paulshir/Model01-firmware)

This is my current firmware build for Keyboardio Model01 firmware. It has come from a lot of messing around but will likely change. It also contains a few WIP plugins.

* [Layers](#layers)
  * [QWERTY](#qwerty)
  * [NUMPAD](#numpad)
  * [FUNCTION](#function)
  * [MEDIA](#media)
  * [MIRROR](#mirror)
  * [EMPTY](#empty)
* [Plugins](#plugins)
  * [Hyper](#hyper)
  * [Mirror](#mirror)
* [License](#license)

# Building
Please see the instructions at [Model01-Firmware](https://github.com/keyboardio/Model01-Firmware). I am using a forked version of [Arduino-Boards](https://github.com/paulshir/Keyboardio-Arduino-Boards) which will be required to get this sketch building. It contains only a few minor changes.

I have moved all my code out of the sketch file as Arduino doesn't update the file automatically when it has changed. I often edit the file elsewhere and then upload using Arduino IDE.

# Layers
## QWERTY
QWERTY with a few plugins, and a few modifications from stock firmware.

## NUMPAD
This is a standard numpad. Same as stock.

## FUNCTION
Pretty similar to the stock firmware. The media keys have been moved off of this. Mouse on the left hand, directions on the right, and a few keys dotted around the place.

## MEDIA
A few keys felt a bit cramped on the FUNCTION layer so I created a layer for media keys. The media keys map the layout I have used previously. This layer also indicates what layers are currently active (1 based index)

## MIRROR
This layer turns the Palm keys into mirror keys. FN can be locked on by tapping control, and control can be used by holding the key down. This is really useful when you have one hand on a mouse and need to do something from the other half of the board. The mirror functionality is implemented by a very much work in progress plugin. It kinda works and when used with the LED-Stalker plugin will light up the mirrored key instead of the pressed key.

This layer is activated by pressing shift on the Media Layer or pressing the 2 shift keys together.

## EMPTY
A layer for locking the keyboard. Nice and confusing. It is activated by pressing both FN keys together.

# Plugins
These are a few work in progress plugins, that could be extracted into proper plugins eventually.

## Hyper
This hijacks the Right Gui key to be hyper. This is great as it allows it to work with OneShot and other plugins.

## Mirror
This plugin will send the key from the opposite side of the board when the Mirror key is pressed. It isn't implemented properly as it is only working on key events. Really is should be storing what it sees and then manipulating it later. There are currently a few issues with it.

* If you have pressed a key and lift the Mirror Key the original key is sent.
* It is always a loop behind.
* It doesn't handle injected keys, or mouse keys, so you can't get the mirror key if a key is a mouse key.

# Source
This firmware was originally based on the [Model01-Firmware](https://github.com/keyboardio/Model01-Firmware). It has also received some inspiration from [algernon/Model01-sketch](https://github.com/algernon/Model01-sketch). Many thanks to the great work done by the Keyboardio team for making a great keyboard and software.

# License
The code is released under the terms of the GNU GPL, version 3 or later. See the
LICENSE file for details.
