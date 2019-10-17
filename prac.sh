 #! /bin/sh


#comments
while(true) #carry on till user exits
do
    echo "Menu\n\t1.CREATE DATABASE\n\t2.INSERT DATA\n\t3.Display\n\t4.delete\n\t5.modify\n\t6.exit\n"
    echo "enter ur choice"

    read choice

    # switch case 
    case "$choice" in
    1)
    echo "enter the name of document to be created"
    read document
    touch $document    #create a document
    ;;#for break
    2)
    echo "enter name of student"
    read name
    echo "enter age of student"
    read age
    data="$name\t\t$age"
    echo $data>>$document       ##append it in the file
    ;;
    3)
    cat $document
    ;;
    4)
    echo "enter the name of person whose data is to be deleted"
    read n
    grep -w ^$n $document
    if [ $? -ne 0 ]; then
        echo "record doesnt exists"
    else
        sed -i "/^$n/d" $document
        echo "deletion complete"
    fi
    ;;
    5)
    echo "enter the name to be modify"
    read n
    grep -w ^$n $document 
    if [ $? -ne 0 ]; then
        echo "record not found"
    else
        echo -n "enter new age :"
        read age
        sed -i "s/^$n.*/$n\t\t$age/g" $document
    fi
    ;;

    6)
    exit 0
    ;;
    esac
    #end of switch case
done    #end of program



#               #! /bin/sh
#               while()
#               do
#               done
#for switch case
#               case "$choice" in 
#                   1) ;;
#                   2)exit 0;;
#                   *)  default ;;
#               esac
#if statement 
#               if []; then
#               else
#               fi
#
#grep commands
#               grep -w variable file     for searching whole word
#               grep -v variable file     print all from file except line containing variable
#               grep -n variable file     displays the matched lines and their line numbers\
#               grep -o variable file     prints only matched parts of line

#sort 
#               sort -o  filename1 filename2    to store the sorted output of filename1 in filename2  -o is used
#               sort -n  filename1 filename2    To sort a file numerically used –n option.
#                sort -r inputfile.txt          reverse order sorting
#               sort -u  inputfile.txt          to sort or remove the duplicates
#
#
#           sed commands                http://gdevtest.geeksforgeeks.org/sed-command-in-linux-unix-with-examples/
