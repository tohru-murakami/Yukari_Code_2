# This script let the team assignment program make 50 optimized results.

# grouping_ils : team assignment optimization program.
# data.txt : student data of properties and peer compatibility.
# results.txt : optimized team assignments.

# README for details.

echo `date '+%y/%m/%d %H:%M:%S'` > results.txt
for i in {0..49}
do 
	./grouping_ils data.txt >> results.txt
	echo `date '+%y/%m/%d %H:%M:%S'` >> results.txt
	echo "-----" >> results.txt
done
