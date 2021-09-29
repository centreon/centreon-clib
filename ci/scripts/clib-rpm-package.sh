#!/bin/bash
set -e

if [ -z "$VERSION" -o -z "$RELEASE" -o -z "$DISTRIB" ] ; then
  echo "You need to specify VERSION / RELEASE variables"
  exit 1
fi

# echo "################################################## BUILDING CLIB ##################################################"

# generate rpm clib
mkdir centreon-clib-$VERSION
cp -r centreon-clib/* centreon-clib-$VERSION
tar -czf centreon-clib-$VERSION.tar.gz centreon-clib-$VERSION cmake.sh
mv centreon-clib-$VERSION.tar.gz /root/rpmbuild/SOURCES/
rm -rf centreon-clib-$VERSION
rpmbuild -ba centreon-clib/packaging/rpm/centreon-clib.spectemplate -D "VERSION $VERSION" -D "RELEASE $RELEASE"

# cleaning and according permissions to slave to delivery rpms
rm -rf *.rpm
cp -r /root/rpmbuild/RPMS/x86_64/*.rpm .
chmod 777 *.rpm