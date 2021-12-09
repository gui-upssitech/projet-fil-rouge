#!/bin/bash

##### TODO : Make modular

# ARGS: 
# 1. Filename           Path
# 2. Output directory   Path
# 2. descriptor ID      Number
# 3. Debug mode         Boolean
# 4. Threshold type     String
# 5. Threshold value    Number

# RETURN VALUES
# 0 No errors
# 1 Missing args

dir=/home/uni/Documents/PFR/data/texts
filename="03-Des_chercheurs_parviennent_α_rΘgΘnΘrer"

in_path="$dir/$filename.xml"
clean_out="$dir/$filename.clean"
tok_out="$dir/$filename.tok"
list_out="$dir/$filename.list"
desc_out="$dir/$filename.desc"

stop_words="stop_words_french.txt"

### PHASE 1 : Cleaning of the input file

encoding=$(file -b --mime-encoding $in_path)

# In order of execution this block will :
# - Remove the XML tags
# - Remove blank lines
# - Separate apostrophes from words
# - Replace punctuation with spaces
# - Replace uppercase letters with lowercase letters
# - Remove the first two lines

iconv -f $encoding -t UTF-8 $in_path | sed \
    -e 's/<[^>]*>//g'       \
    -e '/^$/d'              \
    -e "s/'/' /g"           \
    -e 's/[[:punct:]]/ /g'  \
    -e 's/[A-Z]/\L&/g'      \
| tail +3 > $clean_out

### PHASE 2 : Removal of unnecessary words

# Remove \r to sanitize word list as a precaution
sed -i "s/\r$//" $stop_words

# Remove stop words
sed -e "$(sed 's|.*|s/\\b&\\b//ig|' $stop_words)" $clean_out > $tok_out

### PHASE 3 : Counting 

# Organise text to have one word per line
sed -E "s/\s+/\n/g" $tok_out | sed '/^$/d' | sort > $list_out

# Getting number of tokens for the descriptor
num_tokens=$(cat $list_out |wc -l)
num_uniq_tokens=$(uniq $list_out | wc -l)

# Counting the occurence of each word in the file
echo "" > $desc_out
for word in $(uniq $list_out)
do
    echo -e "$word $(grep "$word" $list_out | wc -l)" >> $desc_out
done

# Formatting it all properly
sort -nr $desc_out -o $desc_out
#sed -i -E -e "s|(\w+) (\w+)|\2 \1}|g" $desc_out

# Adding descriptor id and number of tokens
sed -i -e "1s/^/$1\n/" -e '/^$/d' $desc_out
echo -e "$num_uniq_tokens\n$num_tokens" >> $desc_out
