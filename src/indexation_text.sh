#!/bin/bash

dir=/home/uni/Documents/PFR/data/texts
filename="03-Des_chercheurs_parviennent_α_rΘgΘnΘrer"

in_path=$dir/$filename.xml
clean_out=$dir/$filename.clean

# PHASE 1 : Cleaning of the input file

encoding=$(file -b --mime-encoding $in_path)

#clear
cleaned_file=$(\
    iconv -f $encoding -t UTF-8 $in_path    \
    | sed 's/<[^>]*>//g'                    \
    | sed '/^$/d'                           \
    | sed 's/[.;,?!:-]//g'                  \
    | tail +3                               \
    | tr '[:upper:]' '[:lower:]'            \
    | sed -r "s/'/' /g"                     \
)

cat <<< $cleaned_file > $clean_out

# PHASE 2 : Removal of unnecessary words

# Source - https://unix.stackexchange.com/questions/322310/how-to-delete-all-occurrences-of-a-list-of-words-from-a-text-file

tok_file=$cleaned_file
for word in $(cat stop_words_french.txt)
do
    tok_file=$(sed "s/\b$word\b//g" <<< $tok_file)
done

echo $tok_file