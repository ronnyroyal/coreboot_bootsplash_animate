#!/bin/bash
cp build/coreboot.rom build/coreboot_copy.rom
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash00.jpg -n bootsplash00.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash01.jpg -n bootsplash01.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash02.jpg -n bootsplash02.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash03.jpg -n bootsplash03.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash04.jpg -n bootsplash04.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash05.jpg -n bootsplash05.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash06.jpg -n bootsplash06.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash07.jpg -n bootsplash07.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash08.jpg -n bootsplash08.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash09.jpg -n bootsplash09.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash10.jpg -n bootsplash10.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash11.jpg -n bootsplash11.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash12.jpg -n bootsplash12.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash13.jpg -n bootsplash13.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash14.jpg -n bootsplash14.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash15.jpg -n bootsplash15.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash16.jpg -n bootsplash16.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add -f example_images/bootsplash17.jpg -n bootsplash17.jpg -t bootsplash
./build/cbfstool build/coreboot.rom add-int -i 1500 -n etc/boot-menu-wait
./build/cbfstool build/coreboot.rom add-int -i 18 -n etc/n-of-img
