package com.miniteldo.tools;
// Project : graphical-interface

/**
 * Enum Regex ...
 * Date : 03/03/2022
 * Auteur : Julian
 */
public enum Regex {

    // enum constants calling the enum constructors
    REGEX_TEXTE("[+|-]?\\w+"),
    REGEX_IMAGE("Regex image"),
    REGEX_AUDIO("The size is large.");

    private final String regexExp;

    // private enum constructor
    Regex(String pizzaSize) {
        this.regexExp = pizzaSize;
    }

    public String getRegexExp() {
        return regexExp;
    }
}

