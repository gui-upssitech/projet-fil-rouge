#!/bin/bash

##### TODO : Make modular

# RETURN VALUES
# 0 No errors
# 1 Missing args

# Alias for removing blank lines
shopt -s expand_aliases
alias RBL="sed -e '/^$/d'"

workspace_root="/home/uni/Documents/PFR"
stop_words="stop_words_french.txt"





### == STEP 0 : Parameter retrieval ===================================================================================

INPUT_PATH="${workspace_root}/data/texts/03-Des_chercheurs_parviennent_α_rΘgΘnΘrer.xml"
OUTPUT_DIR="${workspace_root}/results/debug"

DESCRIPTOR_ID=54653475643

# LIMIT: 0 | THRESHOLD: 1
FILTER_TYPE=0
FILTER_VALUE=10

# false: 0 | true: 1
DEBUG_MODE=1





### == STEP 0.5 : variable declaration ================================================================================

clean_out="$OUTPUT_DIR/$DESCRIPTOR_ID.clean"
tok_out="$OUTPUT_DIR/$DESCRIPTOR_ID.tok"
list_out="$OUTPUT_DIR/$DESCRIPTOR_ID.list"
desc_out="$OUTPUT_DIR/$DESCRIPTOR_ID.desc"

mkdir -p $OUTPUT_DIR




### == STEP 1 : Cleaning of the input file ============================================================================

# Figure out the file encoding
encoding=$(file -b --mime-encoding $INPUT_PATH)
echo $encoding

# In order of execution this block will :
# - Remove the XML tags
# - Replace punctuation with spaces
# - Replace uppercase letters with lowercase letters
# - Remove all blank lines
# - Remove the first two lines

iconv -f $encoding -t UTF-8 $INPUT_PATH | sed \
    -e 's/<[^>]*>//g'       \
    -e 's/[[:punct:]]/ /g'  \
    -e 's/[A-Z]/\L&/g'      \
| RBL | tail +3 > $clean_out

cat $clean_out




### == STEP 2 : Removal of unnecessary words ==========================================================================

# Remove \r to sanitize word list as a precaution
sed -i "s/\r$//" $stop_words

# Remove stop words
sed -e "$(sed 's|.*|s/\\b&\\b//ig|' $stop_words)" $clean_out > $tok_out





### == STEP 3 : Counting ==============================================================================================

# Organise text to have one word per line
sed -E "s/\s+/\n/g" $tok_out | RBL | sort > $list_out

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
sed -i -e "1s/^/$1\n/" $desc_out
echo -e "$num_uniq_tokens\n$num_tokens" >> $desc_out

#cat $desc_out





# == STEP 4 : Clean up ================================================================================================

if [ $DEBUG_MODE -eq 0 ] then
    rm -rf $OUTPUT_DIR
fi