package dev.miniteldo.search.model.tools;
// Project : graphical-interface

/**
 * Enum Regex ...
 * Date : 03/03/2022
 * Auteur : Julian
 */
public enum Regex {
    // enum constants calling the enum constructors
    REGEX_TEXTE_KEYWORD("([+|-]?\\w)*"),
    REGEX_TEXTE_PATH("([^\\s]+(\\.(?i)(xml))$)"),
    REGEX_IMAGE_RGB("([^\\s]+(\\.(?i)(jpg))$)"),
    REGEX_IMAGE_NB("([^\\s]+(\\.(?i)(bmp))$)"),
    REGEX_AUDIO("([^\\s]+(\\.(?i)(bin|wav))$)"),
    INVALID("Invalid");

    private final String regexExp;

    // private enum constructor
    Regex(String name) {
        this.regexExp = name;
    }

    public String getRegexExp() {
        return regexExp;
    }
}
