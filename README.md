## Partition Backups (pbt)

This binary static C library is for backing up partitions of android devices.
It offers a lot of options. I will place these below. But first let me talk about the operation...

```
1. The partition name is obtained (with the -p or --partition argument)
2. Other arguments (if used) are processed.
3. It is backed up using DD. If the progress is not a problem, it is not given (DD)
```

#### Presented arguments (options)

```
Usage (arguments):
   -p, --partition   name of the partition to be backed up
   -l, --logical     know that the partition that will be backed up is logical
   -o, --out         the output name of the backed-up partition (default: partition name)
   -d, --outdir      directory where the backup partition will be saved (default: /storage/emulated/0)
   -c, --context     it is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name)
   -D, --list        list partitions
   -v, --version     see version
   -h, --help        see help message
   -L, --license     see license

Example 1:
   -p boot_a -o boot_slot_a_image -d /sdcard/backup -c /dev/block/platform/bootdevice/by-name

Example 2:
   -c /dev/block/platform/bootdevice/by-name --list

Report bugs to <xda-@YZBruh>
```

For example, if we want to back up the `boot_a` section: `pbt -p boot_a' (edit the command if it has a different name).

#### Some notes

- Feel free to ask any questions you want.
- Packages are available in publications.
- it is mandatory to use the `-p` | `--partition` argument. After all, a partition name is required to be backed up.
- If the logical partition flag is not used, a classic partition is tried to be backed up by default.
- Let me know your suggestions!
