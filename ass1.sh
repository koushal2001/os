#!/bin/bash
opt=1
while [ "$opt" -lt 6 ]
do
	echo -e  "1. Create address book. \n2. View address book. \n3. Insert a record in address book. \n4. Delete a record. \n5. Modify a record. \n6. Exit."

	read opt
	case $opt in

	1)
		echo -e  "Enter filename"
		read fileName
		if [ -e $fileName ] ; then	
			rm $fileName
		fi
		cont=1
		echo -e   "NAME\tNUMBER\t\tADDRESS\n===============================\n" | cat >> $fileName
		while [ "$cont" -gt 0 ]
		do
			echo -e  "\nEnter Name"
			read name
			echo -e  "Enter Phone Number of $name"
			read number
			echo -e  "Enter Address of $name"
			read address
			echo -e  "$name\t$number\t\t$address" | cat >> $fileName
			echo -e  "Enter 0 to Stop, 1 to Enter next"
			read cont
		done
		;;

	2)
		cat $fileName
		;;
	3)
		echo -e  "\nEnter Name"
		read name
		echo -e  "Enter Phone Number of $name"
		read number
		echo -e  "Enter Address of $name"
		read address
		echo -e  "$name\t$number\t\t$address" | cat >> $fileName
		;;
	4)
		echo -e  "Delete record\nEnter Name"
		read pattern
        sed -i "/^$pattern/d" $fileName
		;;
	5)
		echo -e  "Modify record\nEnter Name"
		read pattern
		echo -e  "Enter Name"
		read name
		echo -e  "Enter Phone Number of $name"
		read number
		echo -e  "Enter Address of $name"
		read address
        replace="$name $number $address"
        sed -i "s/^.*$pattern.*$/$replace/" $fileName
		;;
	esac
done
