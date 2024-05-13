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

Report bugs to <yagizzengin73@gmail.com>
```

#### Some notes

- Feel free to ask any questions you want.
- Packages are available in publications.
- İt is mandatory to use the `-b` | `--backup` or `-f` | `--flash` and `-p` | `--partition` argument. After all, a partition name and progress type is required to be progress.
- If the logical partition flag is not used, a classic partition is tried to be processing by default.
- [Click to see special version changes](https://github.com/YZBruh/pbt/blob/1.9.0-en/CHANGELOG.md)
- Let me know your suggestions!

### How is it built?
Android NDK is required to build. [Click for usage information](https://developer.android.com/ndk/guides/other_build_systems). [Click for NDK downloads](https://developer.android.com/ndk/downloads). 
 - NOTE 1: The current configuration is configured for compilation with NDK. The configuration was configured according to the NDK guide (I gave the link). You may need to replace it depending on the situation. You just need to set the `CC` variable in the compile command.
 - NOTE 2: The current target architecture is aarch64. You can change this in the configuration or by adding it to the compile command. Be careful. While making this current configuration, the following was considered (directory structure):

```
pmt       android-ndk       other-directories
```

 - The directory structure was thought exactly like this. Be careful.
 - Specify macOS or Linux system usage in config or build command. Default is linux.

If you want to change something, take a look at the configuration. You can change him.
it is located in the `config` folder. His name is `env.mk`. I gave the information in the file. You can ask more.

To build;
```
make
```

Special `make` commands (pmt offers :) ;
```
------- Partition Manager help -------

 Commands;
    make                   ==> Build Partition Manager
    make deb               ==> Generate deb (debian) package (compatibility => termux)
    make clean             ==> Clear builded binary.
    make install           ==> If you are using termux, it installs the compiled pmt into termux. So it allows you to use it like a normal command.
    make uninstall         ==> If you are using termux, it uninstalls the compiled pmt into termux. So it allows you to use it like a normal command.
    make help              ==> Display help message
```
