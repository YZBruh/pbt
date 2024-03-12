## Partition Manager (pmt)

This binary static C library is for manage partitions of android devices.
It offers a lot of options. I will place these below. But first let me talk about the operation...

```
1. The partition name is obtained (with the -p or --partition argument)
2. Other arguments (if used) are processed.
3. It is backed up using DD. If the progress is not a problem, it is not given (DD)
```

#### Presented arguments (options)

```
Usage (arguments):
   -b, --backup      backup mode
   -f, --flash       flash mode
   -p, --partition   name of the partition to be backed up
   -l, --logical     know that the partition that will be backed up is logical
   -o, --out         (only backups) the output name of the backed-up partition (default: partition name)
   -d, --outdir      (only backups) directory where the backup partition will be saved (default: /storage/emulated/0)
   -c, --context     it is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name)
   -D, --list        list partitions
   -v, --version     see version
   -h, --help        see help message
   -L, --license     see license

Example 1:
   -b --partition boot_a -o boot_slot_a_image -d /sdcard/backup -c /dev/block/platform/bootdevice/by-name

Example 2:
   --flash /sdcard/twrp/boot.img -p boot_a -c /dev/block/platform/bootdevice/by-name

Example 3:
   -c /dev/block/platform/bootdevice/by-name --list

Report bugs to <xda-@YZBruh>
```

#### Some notes

- Feel free to ask any questions you want.
- Packages are available in publications.
- İt is mandatory to use the `-b` | `--backup` or `-f` | `--flash` and `-p` | `--partition` argument. After all, a partition name and progress type is required to be progress.
- If the logical partition flag is not used, a classic partition is tried to be processing by default.
- [Click to see special version changes](https://github.com/YZBruh/pbt/blob/1.5.0-en/CHANGELOG.md)
- Let me know your suggestions!

### How is it built?
Even termux is enough to build the pmt. Or you can compile it with linux if you want. NOTE: Use a custom gcc according to the architecture you want to compile.

If you want to change something, take a look at the configuration. You can change him.
it is located in the `mka` folder. His name is `config.mk`. I gave the information in the file. You can ask more.

To build;
```
make
```

Special `make` commands (pbt offers :) ;
```
--------- Partition Manager help ---------

 Commands;
    make                 ==> Build Partition Backupper
    make clean           ==> Clear files (Builded binaries are not deleted)
    make clean-all       ==> Clear files (Builded binaries are deleted)
    make install-termux  ==> If you are using termux, it installs the compiled pbt into termux. So it allows you to use it like a normal command.
    make help            ==> Display help message
```

I compiled it with termux :D. Why should I bother... I compiled it with `GCC 17.0.6`. You can look at the version with the viewing option :)
