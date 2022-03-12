#!/bin/bash

##### TODO : Make modular

# RETURN VALUES
# 0 No errors
# 1 Missing args

# Alias for removing blank lines
shopt -s expand_aliases
alias RBL="sed -e '/^$/d'"



workspace_root=$(pwd) #"/home/uni/Documents/PFR"
stop_words="$workspace_root/src/indexation_text/stop_words_french.txt"




### == STEP 0 : Parameter retrieval ===================================================================================

# Check number of args
if [ "$#" -ne 6 ]; then
    echo "ERR: invalid args"
    exit 1
fi

# Script parameters (all paths should be relative to workspace_root)

# 1 - Input path of the descriptor (ex: /data/texts/03-Des_chercheurs_parviennent_α_rΘgΘnΘrer.xml)
INPUT_PATH="$workspace_root/$1"

# 2 - directory in which the files are kept (ex: /results/debug)
OUTPUT_DIR="$workspace_root/$2"

# 3 - Decriptor ID (ex: 54653475643)
DESCRIPTOR_ID=$3

# 4 - Filter type relative to file config (ex : LIMIT: 0 | THRESHOLD: 1)
FILTER_TYPE=$4

# 5 - limit value or threshold
FILTER_VALUE=$5

# 6 - Debug mode: debug files are kept if value is true (ex : false: 0 | true: 1)
DEBUG_MODE=$6





### == STEP 1 : Cleaning of the input file ============================================================================

# Figure out the file encoding
encoding=$(file -b --mime-encoding $INPUT_PATH)

# In order of execution this block will :
# - Remove the XML tags
# - Replace punctuation with spaces
# - Replace uppercase letters with lowercase letters
# - Remove all blank lines
# - Remove the first two lines

clean_out=$(iconv -f $encoding -t ASCII//TRANSLIT $INPUT_PATH | sed \
    -e 's/<[^>]*>/ /g'      \
    -e 's/[[:punct:]]/ /g'  \
    -e 's/[A-Z]/\L&/g'      \
    -e 's/[0-9]*//g'        \
| RBL | tail +3)




### == STEP 2 : Removal of unnecessary words ==========================================================================

# Remove \r to sanitize word list as a precaution
sed -i "s/\r$//" $stop_words

# Remove stop words
tok_out=$(echo -e "$clean_out" | sed -e "$(sed 's|.*|s/\\b&\\b//ig|' $stop_words)")





### == STEP 3 : Counting ==============================================================================================

# Organise text to have one word per line
list_out=$(echo -e "$tok_out" | sed -E "s/\s+/\n/g" | RBL | sort)

# Get number of occurences of each word, sort by number of occurences, then output in format "word num_occurence"
desc_out=$(echo -e "$list_out" | uniq --count | sort -nr | awk '{ print $2 " " $1 }')

# Add filter
if [ $FILTER_TYPE -eq 0 ]
then
    # Limit mode
    desc_out=$(echo -e "$desc_out" | head -n $FILTER_VALUE)
else
    # Threshold mode
    desc_out=$(echo -e "$desc_out" | awk -v threshold=$FILTER_VALUE '$2 >= threshold')
fi

# Add descriptor id to the top of the file & add the number of tokens and unique tokens in the descriptor
desc_out="$DESCRIPTOR_ID\n$desc_out\n$(echo -e "$desc_out" | wc -l)\n$(echo -e "$list_out" | wc -l)"

# Print descriptor to console
echo -e "$desc_out"





# == STEP 4 : Debug output ============================================================================================

save_var() {
    echo -e "$1" > "$OUTPUT_DIR/$DESCRIPTOR_ID/$DESCRIPTOR_ID.$2"
}

if [ $DEBUG_MODE -eq 1 ]; then
    mkdir -p "$OUTPUT_DIR/$DESCRIPTOR_ID"
    save_var "$clean_out" "clean"
    save_var "$tok_out"   "tok"
    save_var "$list_out"  "list"
    save_var "$desc_out"  "desc"
fi

exit 0