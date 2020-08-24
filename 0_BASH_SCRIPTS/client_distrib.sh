`export PATH=~/scripts/:$PATH`
SADKO_BUILD=`pwd`/..

do_distrib.sh complex_configurator $1
do_distrib.sh complex_viewer $1

cp -R $SADKO_BUILD/config $1/config
cp -R $SADKO_BUILD/data $1/data
