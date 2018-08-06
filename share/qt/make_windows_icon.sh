#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/lunarium.png
ICON_DST=../../src/qt/res/icons/lunarium.ico
convert ${ICON_SRC} -resize 16x16 lunarium-16.png
convert ${ICON_SRC} -resize 32x32 lunarium-32.png
convert ${ICON_SRC} -resize 48x48 lunarium-48.png
convert lunarium-16.png lunarium-32.png lunarium-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/lunarium_testnet.png
ICON_DST=../../src/qt/res/icons/lunarium_testnet.ico
convert ${ICON_SRC} -resize 16x16 lunarium-16.png
convert ${ICON_SRC} -resize 32x32 lunarium-32.png
convert ${ICON_SRC} -resize 48x48 lunarium-48.png
convert lunarium-16.png lunarium-32.png lunarium-48.png ${ICON_DST}
rm lunarium-16.png lunarium-32.png lunarium-48.png
