## Partition Manager (pmt)

This binary C is for manage partitions of android devices.
It offers a lot of options. I will place these below. But first let me talk about the operation...

```
1. The partition name is obtained (with the -p or --partition argument)
2. Other arguments (if used) are processed.
3. The backup and flashing processes were written according to DD's code. So there is a piece of toybox code
```

#### Presented arguments (options)

```
Usage:
   -b | --backup      backup mode
   -F | --flash       flash mode
   -r | --format      format mode (only ext2/3/4 file systems)
   -p | --partition   name of the partition to be backed up
   -l | --logical     know that the partition that will be backed up is logical
   -o | --out         (only backups) the output name of the backed-up partition (default: partition name)
   -d | --outdir      (only backups) directory where the backup partition will be saved (default: /storage/emulated/0)
   -c | --context     it is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name)
   -D | --list        list partitions
   -f | --force       force mode. Output is not produced. Even if it's a mistake. But if the target is not a mode, the error is given. If you want to work stable, it is important to specify this option first.
   -v | --version     see version
        --help        see help message
   -L | --license     see license

Examples:
   -b --partition boot_a -o boot_slot_a_image -d /sdcard/backup -c /dev/block/platform/bootdevice/by-name
   --flash /sdcard/twrp/boot.img -p boot_a -c /dev/block/platform/bootdevice/by-name
   -c /dev/block/platform/bootdevice/by-name --list

Report bugs to <t.me/YZBruh>
```

#### Some notes

- Feel free to ask any questions you want.
- Packages are available in publications.
- İt is mandatory to use the `-b` | `--backup` or `-f` | `--flash` and `-p` | `--partition` argument. After all, a partition name and progress type is required to be progress.
- If the logical partition flag is not used, a classic partition is tried to be processing by default.
- [Click to see special version changes](https://github.com/YZBruh/pbt/blob/2.0.0-en/CHANGELOG.md)
- Let me know your suggestions!

### How is it built?
Android NDK is required to build.
 - [Download](https://developer.android.com/ndk/downloads) and extract the NDK package.
 - Clone this repository. And get access to it.
```
git clone https://github.com/YZBruh/pbt -b 2.0.0 ./pmt
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
                   libs/
                     |
           __________|__________
           |                   |
       arm64-v8a/         armeabi-v7a/
           |                   |
          pmt                 pmt
```
 - For the make installable debian package make-deb.sh use the script. It can be created within two architectures. Use the script flags correctly: arm64-v8a, armeabi-v7a
```
chmod 777 make-deb.sh

# for making 64-bit package
./make-deb.sh arm64-v8a

# for making 32-bit package
./make-deb.sh armeabi-v7a
```

### Notes
If you want to change something, take a look at the configuration. You can change him.
it is located in the `jni/config` folder. His name is `env.mk`. I gave the information in the file. You can ask more.
