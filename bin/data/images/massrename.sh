i=0; 
for file in *.jpg;
do mv "$file" $(printf "%0.1d.jpg" $i); 
i=$((i+1)); done