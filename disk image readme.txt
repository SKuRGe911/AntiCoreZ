to create a disk image on windows 10 that can be used on this core.
open a command prompt.
type diskpart
type create vdisk file="PATH TO YOUR DISK IMAGE HERE" MAXIMUM=32
type select vdisk file="PATH TO YOUR DISK IMAGE HERE"
type select partition 1
type active
type format FS=FAT LABEL="GERANIUM"
