## Partition Manager (pmt)

This binary C is for manage partitions of android devices.
It offers a lot of options. I will place these below. But first let me talk about the operation...

#### Presented arguments (options)

```
Usage:
   pmt backup PARTITION [OUTPUT] [OPTIONS]...
   pmt flash FILE PARTITION [OPTIONS]...
   pmt format FILE_SYSTEM[ext/2/3/4] PARTITION [OPTIONS]...

Options:
   -l | --logical     it is meant to determine whether the target partition is logical
   -c | --context     it is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name)
   -p | --list        list partitions
   -s | --silent      information and warning messages are silenced in normal work.
   -f | --force       force mode. Error messages are silenced and some things are ignored.
   -v | --version     see version
        --help        see help message
   -L | --license     see license

Examples:
   pmt backup boot_a -c /dev/block/platform/bootdevice/by-name
   pmt flash /sdcard/twrp/boot.img boot_a -c /dev/block/platform/bootdevice/by-name
   pmt format ext4 system_a --logical
   pmt -c /dev/block/platform/bootdevice/by-name --list

Report bugs to <t.me/YZBruh>
```

#### Some notes

- Feel free to ask any questions you want.
- Packages are available in publications.
- If the logical partition flag is not used, a classic partition is tried to be processing by default.
- [Click to see special version changes](https://github.com/YZBruh/pbt/blob/2.1.0-en/CHANGELOG.md)
- Let me know your suggestions!

### How is it built?
Android NDK is required to build.
 - [Download](https://developer.android.com/ndk/downloads) and extract the NDK package.
 - Clone this repository. And get access to it.
```
git clone https://github.com/YZBruh/pbt -b 2.1.0 ./pmt
cd pmt
```
 - Set the NDK working directory variable.
```
export NDK_PROJECT_PATH=$(pwd)
```
 - Go to the NDK directory and start the construction
```
./ndk-build
```
 - The output files will be inside the `pmt` folder. Binaries are available in two architectures within the `libs` folder. `arm64-v8a` (64-bit) and `armeabi-v7a` (32-bit).
```
                    pmt/
                     |
     ________________|________________
     |         |            |        |
   jni/    debutils/      objs/    libs/            
                                     |
                           __________|__________
                           |                   |
                       arm64-v8a/         armeabi-v7a/
                           |                   |
                          pmt                 pmt
```
 - For the make installable debian package make-deb.sh use the script. It can be created within two architectures. Use the script flags correctly: arm64-v8a, armeabi-v7a. If you want to process with root, add sudo as the second argument. If you don't want, use no-sudo or leave it blank

```
--Usage--

./make-deb.sh [arm64-v8a, armeabi-v7a] [sudo, no-sudo, <blank>]
```
 
```
chmod 777 make-deb.sh

# for making 64-bit package
./make-deb.sh arm64-v8a 

# for making 32-bit package
./make-deb.sh armeabi-v7a
```

### Easy install on termux
 - Just execute this command in termux:
```shell
curl -LSs "https://raw.githubusercontent.com/YZBruh/pbt/2.1.0/install-termux.sh" | bash -
```

### Notes
If you want to change something, take a look at the configuration. You can change him.
it is located in the `jni/config` folder. His name is `env.mk`. I gave the information in the file. You can ask more.
