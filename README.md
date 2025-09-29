# kitty
The kitty kernel, maintained by BYUI students

## Building

Requisites:
- If on windows, Put these precompiled binaries (x86_64) into your path: https://github.com/lordmilko/i686-elf-tools/releases/tag/13.2.0
- Install make (chocolatey or mingw for windows)
- Install nasm
- Install qemu

Make sure that all of the above software is accessible through your shell (put everything in path!)

Run this in the src directory:
```make run arch=x86```
or
```make run arch=x86_64```

## Other components included in this repository

### x86/x86_64 bootloader

Located in src/x86-boot/, a boot sector written for 32/64 bit x86.

### EXT4 filesystem image

Located in src/test/fs_ext4/, this FS image contains just enough to get the operating system running by providing service files
that the kernel loads automatically.

## License

The kitty kernel utilizes a GNU General Public License.
Much of the bootloader code (under x86-boot) is CC0 license and in the public domain. 

Before contributing, read the notes on our organizations [main page](https://github.com/BYUi-OSDevelopment).
