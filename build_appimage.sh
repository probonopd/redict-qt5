#!/bin/bash

qmake CONFIG+=release PREFIX=/usr
make -j$(nproc)
mkdir -p appdir/usr/bin/ appdir/usr/share/applications/ appdir/usr/share/applications/ appdir/usr/share/icons/hicolor/scalable/apps
cp redict appdir/usr/bin/
cp redict.desktop appdir/usr/share/applications/
cp images/redict.svg appdir/usr/share/icons/hicolor/scalable/apps/redict.svg
find appdir/
wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt-continuous-x86_64.AppImage
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -appimage
