package dev.miniteldo.search.model.tools;
// Project : graphical-interface

/**
 * Enum Regex ...
 * Date : 03/03/2022
 * Auteur : Julian
 */
public enum Regex {

    // enum constants calling the enum constructors
    REGEX_TEXTE_KEYWORD("[+|-]?\\w+"),
    REGEX_TEXTE_PATH("[+|-]?\\w+"),
    REGEX_IMAGE_RGB("/^(.*\\.(?!(htm|html|class|js)$))?[^.]*$/i"),
    REGEX_IMAGE_NB("/^(.*\\.(?!(htm|html|class|js)$))?[^.]*$/i"),
    REGEX_AUDIO("The size is large."),
    INVALID("Invalid");

    private final String regexExp;

    // private enum constructor
    Regex(String pizzaSize) {
        this.regexExp = pizzaSize;
    }

    public String getRegexExp() {
        return regexExp;
    }
}

