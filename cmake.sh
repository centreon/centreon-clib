#!/bin/bash

show_help() {
cat << EOF
Usage: ${0##*/} -n=[yes|no] -v

This program build Centreon-clib

    -f|--force    : force rebuild
    -r|--release  : Build on release mode
    -fcr|--force-conan-rebuild : rebuild conan data
    -h|--help     : help
EOF
}
BUILD_TYPE="Debug"
CONAN_REBUILD="0"
for i in $(cat conanfile.txt) ; do
  if [[ $i =~ / ]] ; then
    if [ ! -d ~/.conan/data/$i ] ; then
      echo "The package '$i' is missing"
      CONAN_REBUILD="1"
      break
    fi
  fi
done

for i in "$@"
do
  case $i in
    -f|--force)
      force=1
      shift
      ;;
    -r|--release)
      BUILD_TYPE="Release"
      shift
      ;;
    -fcr|--force-conan-rebuild)
      CONAN_REBUILD="1"
      ;;
    -h|--help)
      show_help
      exit 2
      ;;
    *)
            # unknown option
    ;;
  esac
done

# Am I root?
my_id=$(id -u)

if [ -r /etc/centos-release ] ; then
  maj="centos$(cat /etc/centos-release | awk '{print $4}' | cut -f1 -d'.')"
  v=$(cmake --version)
  if [[ $v =~ "version 3" ]] ; then
    cmake='cmake'
  else
    if rpm -q cmake3 ; then
      rm -f /usr/bin/cmake
      ln -s /usr/bin/cmake3 /usr/bin/cmake
      cmake='cmake'
    elif [ $maj = "centos7" ] ; then
      yum -y install epel-release cmake3
      mv /usr/bin/cmake /usr/bin/cmake2
      ln -s /usr/bin/cmake3 /usr/bin/cmake
      cmake='cmake'
    else
      dnf -y install cmake
      cmake='cmake'
    fi
  fi
  if [[ ! -x /usr/bin/python3 ]] ; then
    yum -y install python3
  else
    echo "python3 already installed"
  fi
  if ! rpm -q python3-pip ; then
    yum -y install python3-pip
  else
    echo "pip3 already installed"
  fi

  good=$(gcc --version | awk '/gcc/ && ($3+0)>5.0{print 1}')

  if [ ! $good ] ; then
    echo "Your compiler is too old. Trying to used devtoolset-9."
    yum -y install centos-release-scl
    yum-config-manager --enable rhel-server-rhscl-7-rpms
    yum -y install devtoolset-9
    source /opt/rh/devtoolset-9/enable
  fi

  pkgs=(
    ninja-build
  )
  for i in "${pkgs[@]}"; do
    if ! rpm -q $i ; then
      if [ $maj = 'centos7' ] ; then
        yum install -y $i
      else
        dnf -y --enablerepo=PowerTools install $i
      fi
    fi
  done
elif [ -r /etc/issue ] ; then
  maj=$(cat /etc/issue | awk '{print $1}')
  version=$(cat /etc/issue | awk '{print $3}')
  if [ $version = "9" ] ; then
    dpkg='dpkg'
  else
    dpkg='dpkg --no-pager'
  fi
  v=$(cmake --version)
  if [[ $v =~ "version 3" ]] ; then
    cmake='cmake'
  elif [ $maj = "Debian" ] ; then
    if $dpkg -l cmake ; then
      echo "Bad version of cmake..."
      exit 1
    else
      if [ $my_id -eq 0 ] ; then
        apt install -y cmake
        cmake='cmake'
      else
        echo -e "cmake is not installed, you could enter, as root:\n\tapt install -y cmake\n\n"
        exit 1
      fi
    fi
  elif [ $maj = "Raspbian" ] ; then
    if $dpkg -l cmake ; then
      echo "Bad version of cmake..."
      exit 1
    else
      if [ $my_id -eq 0 ] ; then
        apt install -y cmake
        cmake='cmake'
      else
        echo -e "cmake is not installed, you could enter, as root:\n\tapt install -y cmake\n\n"
        exit 1
      fi
    fi
  else
    echo "Bad version of cmake..."
    exit 1
  fi
  if [ $maj = "Debian" ] ; then
    pkgs=(
      gcc
      g++
      pkg-config
      ninja-build
      python3
      python3-pip
    )
    for i in "${pkgs[@]}"; do
      if ! $dpkg -l $i | grep "^ii" ; then
        if [ $my_id -eq 0 ] ; then
          apt install -y $i
        else
          echo -e "The package \"$i\" is not installed, you can install it, as root, with the command:\n\tapt install -y $i\n\n"
          exit 1
        fi
      fi
    done
  fi
  if [ $maj = "Raspbian" ] ; then
    pkgs=(
      gcc
      g++
      pkg-config
      ninja-build
      python3
      python3-pip
    )
    for i in "${pkgs[@]}"; do
      if ! $dpkg -l $i | grep "^ii" ; then
        if [ $my_id -eq 0 ] ; then
          apt install -y $i
        else
          echo -e "The package \"$i\" is not installed, you can install it, as root, with the command:\n\tapt install -y $i\n\n"
          exit 1
        fi
      fi
    done
  fi
fi

pip3 install conan --upgrade

if [ $my_id -eq 0 ] ; then
  conan='/usr/local/bin/conan'
elif which conan ; then
  conan=$(which conan)
else
  conan="$HOME/.local/bin/conan"
fi

if [ ! -d build ] ; then
  mkdir build
else
  echo "'build' directory already there"
fi

if [ "$force" = "1" ] ; then
  rm -rf build
  mkdir build
fi
cd build

if [ $maj = "centos7" ] ; then
  rm -rf ~/.conan/profiles/default
  if [ "$CONAN_REBUILD" = "1" ] ; then
    $conan install .. -s compiler.libcxx=libstdc++11 --build="*"
  else
    $conan install .. -s compiler.libcxx=libstdc++11 --build=missing
  fi
else
    $conan install .. -s compiler.libcxx=libstdc++11 --build=missing
fi

if [ $maj = "Raspbian" ] ; then
  CXXFLAGS="-Wall -Wextra" $cmake -DWITH_PREFIX=/usr -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DWITH_PREFIX_LIB=/usr/lib -DWITH_TESTING=On -DUSE_CXX11_ABI=1 $* ..
elif [ $maj = "Debian" ] ; then
  CXXFLAGS="-Wall -Wextra" $cmake -DWITH_PREFIX=/usr -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DWITH_PREFIX_LIB=/usr/lib -DWITH_TESTING=On -DUSE_CXX11_ABI=1 $* ..
else
  CXXFLAGS="-Wall -Wextra" $cmake -DWITH_PREFIX=/usr -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DWITH_PREFIX_LIB=/usr/lib64 -DWITH_TESTING=On -DUSE_CXX11_ABI=1 $* ..
fi

#CXX=/usr/bin/clang++ CC=/usr/bin/clang CXXFLAGS="-Wall -Wextra" cmake -DWITH_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug -DWITH_PREFIX_LIB=/usr/lib64 -DWITH_TESTING=On $* ..

#CXXFLAGS="-Wall -Wextra -O1 -fsanitize=address -fno-omit-frame-pointer" cmake -DWITH_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug -DWITH_PREFIX_LIB=/usr/lib64 -DWITH_TESTING=On $* ..
