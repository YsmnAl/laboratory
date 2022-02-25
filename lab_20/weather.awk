jasmin@ubuntu:~$ cat > weather
SUN;25;18
MON;24;19
TUES;27;17;
WED;26,5;18,3;
THURS;25;20
FRI;28;19
SAT;29;19,3
jasmin@ubuntu:~$ awk -F";" '
{
for (i=2; i<3; i++)
{
y +=$i
z +=$(i+1)
print("Average temperature on", $1, ":", ($i+$(i+1))/2)}}
END{
print("Average daily temperature of the week:", y/FNR)
print("Average night temperature of the week:", z/FNR)}' weather
Average temperature on SUN : 21.5
Average temperature on MON : 21.5
Average temperature on TUES : 22
Average temperature on WED : 22
Average temperature on THURS : 22.5
Average temperature on FRI : 23.5
Average temperature on SAT : 24
Average daily temperature of the week: 26.2857
Average night temperature of the week: 18.5714
