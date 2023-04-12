#!/bin/bash
cp build/coreboot.rom build/coreboot_copy.rom
./build/cbfstool build/coreboot.rom add -f bootsplash00.jpg -n bootsplash00.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash01.jpg -n bootsplash01.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash02.jpg -n bootsplash02.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash03.jpg -n bootsplash03.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash04.jpg -n bootsplash04.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash05.jpg -n bootsplash05.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash06.jpg -n bootsplash06.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash07.jpg -n bootsplash07.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash08.jpg -n bootsplash08.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash09.jpg -n bootsplash09.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash10.jpg -n bootsplash10.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash11.jpg -n bootsplash11.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash12.jpg -n bootsplash12.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash13.jpg -n bootsplash13.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash14.jpg -n bootsplash14.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash15.jpg -n bootsplash15.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash16.jpg -n bootsplash16.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f bootsplash17.jpg -n bootsplash17.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add-int -i 1500 -n etc/boot-menu-wait
./build/cbfstool build/coreboot.rom add-int -i 18 -n etc/n-of-img
