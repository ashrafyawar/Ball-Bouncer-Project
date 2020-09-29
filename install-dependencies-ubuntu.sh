#!/bin/bash

OPENCV_VERSION='4.2.0'
OPENCV_CONTRIB='NO'

sudo apt -y update
sudo apt -y upgrade
sudo apt -y dist-upgrade
sudo apt -y autoremove

sudo apt install -y git
sudo apt install -y build-essential cmake
sudo apt install -y qt5-default libvtk6-dev
sudo apt install -y zlib1g-dev libjpeg-dev libwebp-dev libpng-dev libtiff5-dev libjasper-dev \
                        libopenexr-dev libgdal-dev
sudo apt install -y libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev \
                        libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev yasm \
                        libopencore-amrnb-dev libopencore-amrwb-dev libv4l-dev libxine2-dev
sudo apt install -y libtbb-dev libeigen3-dev
sudo apt install -y python-dev  python-tk  pylint  python-numpy  \
                        python3-dev python3-tk pylint3 python3-numpy flake8
sudo apt install -y ant default-jdk
sudo apt install -y doxygen unzip wget
sudo apt install -y libboost-atomic-dev libboost-thread-dev libboost-system-dev \
                        libboost-date-time-dev libboost-regex-dev libboost-filesystem-dev \
                        libboost-random-dev libboost-chrono-dev libboost-serialization-dev \
                        libwebsocketpp-dev openssl libssl-dev ninja-build


git clone https://github.com/Microsoft/cpprestsdk.git Casablanca
cd Casablanca && mkdir build.release && cd build.release
cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Release
ninja
cd ../..
sudo rm -f -rf Casablanca

wget https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip
unzip ${OPENCV_VERSION}.zip && rm ${OPENCV_VERSION}.zip
mv opencv-${OPENCV_VERSION} OpenCV

if [ $OPENCV_CONTRIB = 'YES' ]; then
  wget https://github.com/opencv/opencv_contrib/archive/${OPENCV_VERSION}.zip
  unzip ${OPENCV_VERSION}.zip && rm ${OPENCV_VERSION}.zip
  mv opencv_contrib-${OPENCV_VERSION} opencv_contrib
  mv opencv_contrib OpenCV
fi

cd OpenCV && mkdir build && cd build

if [ $OPENCV_CONTRIB = 'NO' ]; then
cmake -DWITH_QT=ON -DWITH_OPENGL=ON -DFORCE_VTK=ON -DWITH_TBB=ON -DWITH_GDAL=ON \
      -DWITH_XINE=ON -DENABLE_PRECOMPILED_HEADERS=OFF ..
fi

if [ $OPENCV_CONTRIB = 'YES' ]; then
cmake -DWITH_QT=ON -DWITH_OPENGL=ON -DFORCE_VTK=ON -DWITH_TBB=ON -DWITH_GDAL=ON \
      -DWITH_XINE=ON -DENABLE_PRECOMPILED_HEADERS=OFF \
      -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules ..
fi

make -j8
sudo make install
sudo ldconfig

cd ../..
sudo rm -f -rf OpenCV