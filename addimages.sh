#!/bin/bash
cp -n build/coreboot.rom build/coreboot_copy.rom #backup unmodified rom image

for filename in example_images/*; #add all files in /example_images/ to the CBFS
do 
    ./build/cbfstool build/coreboot.rom add -f ${filename} -n ${filename#*/} -t bootsplash
done

./build/cbfstool build/coreboot.rom add-int -i 1500 -n etc/boot-menu-wait #define boot menu timeout
./build/cbfstool build/coreboot.rom add-int -i $(ls example_images/ | wc -l) -n etc/n-of-img #set image number variable in CBFS

./build/cbfstool build/coreboot.rom #print CBFS content