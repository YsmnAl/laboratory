#!/bin/bash
awk -F";" '
{
for (i=2; i<3; i++)
{
y +=$i
z +=$(i+1)
print("Average temperature on", $1, ":", ($i+$(i+1))/2)}}
END{
print("Average daily temperature of the week:", y/FNR)
print("Average night temperature of the week:", z/FNR)}' weather
