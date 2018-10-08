#! /bin/bash
	function work()
	{
		for file in `ls $1`
		do
			if [ -d $1"/"$file ] 
			then
				work $1"/"$file
			else
				echo $1"/"$file
#				`dos2unix $1"/"$file`
#				sed -i -e '/^$/d' $1"/"$file
				sed -i 's/	/\t/g' $1"/"$file
			fi
		done
	}
	
work .$1
