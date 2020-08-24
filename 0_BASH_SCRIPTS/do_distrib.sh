
function getListOfDependencies() {
	echo `ldd -r $1  | sed 's/.*=> \(\/.*\) (.*/\1/' | grep S-637-2`
}


SADKO_BUILD=`pwd`/..

where_to_build=$2

mkdir -p  $where_to_build/bin

so_deps=`getListOfDependencies $1`
for so in $so_deps; do
	so_name=`basename $so`
	if [ ! -f $where_to_build/$so_name ];then
		cp $so $where_to_build/bin
	fi
done

cp -R $SADKO_BUILD/config $where_to_build/config
cp -R $SADKO_BUILD/data $where_to_build/data
cp $1  $where_to_build/bin