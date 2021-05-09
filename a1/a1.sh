# Name: Mihir Kulkarni (33132)
#Assignment 1: FILE HANDLING IN SHELL SCRIPT

#!/bin/bash

#default
choice=0
filename="file.txt"
name="anonymous"
vcompany="anonymous"
model="anonymous"
vnumber="anonymous"

create()
{
	read -p 'Enter the filename: ' filename		#read input on same line
		if [ -e $filename ]						#search for existance of file
		 	then
				echo "File already present"
			else
			 	touch $filename					#create file
			 	printf "Owner\t\tCompany\t\tModel\t\tNumber\n" >> $filename
				ls -l $filename					#checks if the file is created or not
				printf "Welcome to $filename\n"
		fi
}

write()
{
	read -p 'Enter the filename to write: ' filename
	if [ -e $filename ]
		then
			read -p 'Enter no. of records to insert: ' rec
			while [ $rec -gt 0 ]				#gt - greater than
			do
				read -p 'Enter the owner name: ' name
				read -p 'Enter the vehicle company: ' vcompany
				read -p 'Enter the model: ' model
				read -p 'Enter the vehicle number: ' vnumber
				printf "$name\t\t$vcompany\t\t$model\t\t$vnumber\n" >> $filename
				rec=$((rec-1))					#decrement rec
			done	
	else
			echo "File does not exist"
	fi
}

Display()
{
	read -p 'Enter the filename: ' filename
		if [ -e $filename ]
		 	then
				echo "The content of the file is as follows :- "
				cat $filename 
					#echo "The content sorted file is as follows :- "
					#sort $filename
			else
				echo "File does not exist"
		fi
}

Search()
{
	read -p 'Enter the filename: ' filename
	if [ -e $filename ]
	 	then
			read -p "Enter the name to be searched : " tempname
			grep -i -n "$tempname" $filename && echo "Found"		#grep-find and fetch, -i(neglect case sensitivity), -n(numerical)
			grep -i "$tempname" $filename || echo "Not Found"
		else
			echo "File does not exist"
	fi			
}

modify()
{
	read -p 'Enter the filename: ' filename
	if [ -e $filename ]
		then
			echo "Choose the attribute to modify:- "
			echo "1.Owner Name"
			echo "2.Vehice company"
			echo "3.Model"
			echo "4.Vehicle number"
			read option 

			if [ $option -le 0 ] || [ $option -gt 4 ]		#le-less than
				then
					echo "Enter valid option !"
			else
				case $option in
				1)read -p "Enter owner name you want to modify: " name
				  read -p "Enter new owner name: " newname
				  sed -i "s/$name/$newname/g" $filename			#sed-find and replace ,s/ - substitute, /g - global
				  echo "MODIFICATION SUCCESSFUL !!!"
				;;
				2)read -p "Enter vehicle company you want to modify: " vcompany
				  read -p "Enter new vehicle company: " newvcompany
				  sed -i "s/$vcompany/$newvcompany/g" $filename
				  echo "MODIFICATION SUCCESSFUL !!!"
				;; 
				3)read -p "Enter model you want to modify: " model
				  read -p "Enter new model name: " newmodel
				  sed -i "s/$model/$newmodel/g" $filename
				  echo "MODIFICATION SUCCESSFUL !!!"
				;; 
				4)read -p "Enter vehicle number you want to modify: " number
				  read -p "Enter new vehicle number: " newnumber
				  sed -i "s/$number/$newnumber/g" $filename
				  echo "MODIFICATION SUCCESSFUL !!!"
				;;

				*)echo "Wrong option"
				;;
			#method 2: removes whole line and appends modified
			#echo -e "Enter name to be edited:- \n"
			#read name
			#grep -n "$name" $filename
		
			#echo -e "Enter the line number to edit:- \n"
			#read lineno
			
			#for line in `grep -n "$name" $filename`
			#do
			#	number=`echo "$line"|cut -c1`
			#	if [ "$number" == "$lineno" ]
			#		then
			#			echo -e "ENTER THE MODIFICATION DETAILS:- \n"
			#			write
			#			sed -i -e "${lineno}s/.*/$insert/" $filename 
			#			echo -e "MODIFICATION SUCCESSFUL !!! \n"
			#	fi

			#done
			esac
		fi
	else
		echo "File does not exist"
	fi
}

Delete()
{
	read -p 'Enter the filename: ' filename
			if [ ! -s $filename ];
				then
					echo -e "File empty !!! \n"
			else
				echo -e "Enter content to delete:- \n"
				read fnem
				grep -n "$fnem" $filename		#fetch numerical 
	
				echo -e "Enter the line number to delete:- \n"
				read lineno

				for line in `grep -n "$fnem" $filename` 	
				do
	
					number=`echo $line|cut -c1`

					if [ "$number" == "$lineno" ];
						then
							sed -i -e "${lineno}d" $filename 	#Delete last line only if it contains the pattern
							echo -e "\nRECORD DELETION SUCCESSFUL!!!! \n"
					fi

				done
			fi
}

del_file()
{
	read -p "Enter the filename to be deleted : " delname
		if [ -e $delname ]
			then
				rm $delname
				echo "File deleted successfully"
			else
				echo "File doesn't exist"
		fi
}

while [ $choice -ne 7 ]
	do 
		#display the menu
		echo -e "\n***VEHICLE DATABASE***"
		echo "1 -> Create a file"
		echo "2 -> Write to the file"
		echo "3 -> Display file"
		echo "4 -> Search from the file"
		echo "5 -> Modify record"
		echo "6 -> Delete record"
		echo "7 -> Delete File"
		echo "8 -> Exit"
		
		read -p 'Enter your choice: ' choice

		case $choice in

		 1 ) create
			;;

		2 )	write
			;;

		3 ) Display
			;;
			

		4 ) Search
			;;

		5 ) modify
			;;

		6 ) Delete
			;;

		7)	del_file
			;;

		8)  printf "\nThank You!!"
			exit	
			;;
			
		*) echo "Wrong option"
		;;

		esac
	done