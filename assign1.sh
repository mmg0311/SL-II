#! /bin/sh

while (true)	#breaks when exit choice is entered
do
	echo "Menu\n\t1.Create database\n\t2.Insert data\n\t3.Delete record\n\t4.Search\n\t5.Display\n\t6.Modify\n\t7.Exit\n"
	echo "Enter you choice\t"
	read choice
	case "$choice" in
		1)		#creating a file to store records
			echo "Database named 'student' created"
			echo > student
			# or 
			# touch student
			;;	#break 
		2)		#inserting a record
			echo "Enter student name : "
			read name
			echo "Enter Roll number : "
			read roll_no
			echo  "Enter percent in last year :"
			read percent
			grep -w ^$roll_no student
			if [ $? -ne 0 ]; then
				record="$roll_no\t\t$name\t\t$percent"
				echo $record >> student
				sort -o student student					#will sort wrt first character if same then wrt second cha.. and soon
			else
				echo "Record with Roll Number \"$roll_no\" already present"
			fi
			;;
		3)
			echo " enter roll number "  
   			read rn  
   			grep -w ^$rn student  
   			if [ $? -ne 0 ]; then  
   				echo "record for roll number does not exist "  
   			else  
   				#except that roll number copy all data in other file 
   				grep -vw ^$rn student>tmp  
   				#rename file
   				cp tmp student
   				rm tmp
   				echo "deletion complete "  
   			fi  
			;;
		4)
			echo  "Enter Roll Number of student to be searched :"
			read temp1
			grep -wn ^$temp1 student   # ^ for searching starting element of line
			if [ $? -ne 0 ]; then
					echo "Record Not Found"
			fi	
			;;
		5)
			echo "Roll Number \t Student name \t Perent"
			cat student 	#cat is used to display contents of file line by line
			;;
		6)
			echo "Enter the roll number whose data is tobe modified"
			read temp1
			grep -w ^$temp1 student
			if [ $? -ne 0 ]; then
				echo "Record not found"
			else
				grep -vw ^$temp1 student>tmp
				cp	tmp student
				rm tmp
				echo "Enter Modified details "
				echo "Name :" 
				read name
				echo "Percent : "
				read percent
				record="$temp1\t\t$name\t\t$percent"
				echo $record >> student
				sort -o student student		
			fi	 
			;;
		7)			
			exit 0
			;;
		*)
			echo "Enter valid coice"
			;;
	esac
done
