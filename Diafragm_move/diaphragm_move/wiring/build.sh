#/usb/bin/bash -x

### COMMON PART: JUST COPY TO NEW ONE ####
#абсолютный путь к скрипту
script_path=$(realpath $(dirname $0))
echo $script_path

check_make_ok() {
  if [ $? != 0 ]; then
    echo "Make Failed..."
    exit 1
  fi
}
### END OF COMMON PART ####

BUILD_PATH=$script_path/build
INSTALL_PATH=$script_path/install
mkdir $BUILD_PATH
mkdir $INSTALL_PATH
cd $BUILD_PATH

rm -rf $BUILD_PATH/*
echo WIRINGPI_TAG=$WIRINGPI_TAG
git clone https://github.com/orangepi-xunlong/wiringOP.git .
git checkout $WIRINGPI_TAG
check_make_ok

#форсируем окружение make
export DESTDIR=$INSTALL_PATH
export LDCONFIG=
export PREFIX=
install_dir=$DESTDIR/$PREFIX
export C_INCLUDE_PATH=$install_dir/include

rm -rf $install_dir/*
mkdir -p $install_dir/include
mkdir -p $install_dir/lib

#чистим предыдущую сборку
./build clean

#./build
#build собирает также ненужное gpio,
#а там проблемы со сборкой, поэтому вынесем что нам надо напрямую

echo "WiringPi Library"
cd wiringPi
make uninstall
make -j`nproc`
check_make_ok
make install
check_make_ok

echo
echo "WiringPi Devices Library"
cd ../devLib
$sudo make uninstall
make -j`nproc`
check_make_ok
$sudo make install
check_make_ok
mv $install_dir/include $install_dir/WiringPi
mkdir $install_dir/include
mv $install_dir/WiringPi $install_dir/include/
rm $install_dir/lib/libwiringPi.so $install_dir/lib/libwiringPiDev.so
cd $install_dir/lib
ln -s libwiringPi.so.2.60 libwiringPi.so
ln -s libwiringPiDev.so.2.60 libwiringPiDev.so
cd ..

