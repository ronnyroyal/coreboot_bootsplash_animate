#!/bin/bash
cp -n build/coreboot.rom build/coreboot_copy.rom #backup unmodified rom image

for filename in example_images/*; 
do 
    #echo " ${filename}"; 
    #echo ${filename#*/}
    ./build/cbfstool build/coreboot.rom add -f ${filename} -n ${filename#*/} -t bootsplash
done

./build/cbfstool build/coreboot.rom add-int -i 1500 -n etc/boot-menu-wait
./build/cbfstool build/coreboot.rom add-int -i 80 -n etc/n-of-img
