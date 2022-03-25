package dev.miniteldo.search.model.tools;

import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.File;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Tools {
    public static SearcherType getRequestType(String request) {
        for (Regex regex : Regex.values()) {
            Matcher m = Pattern.compile(regex.getRegexExp()).matcher(request);
            if (m.matches()) return switch (regex) {
                case REGEX_TEXTE_KEYWORD -> SearcherType.TEXT_KEYWORD;
                case REGEX_TEXTE_PATH -> SearcherType.TEXT_PATH;
                case REGEX_IMAGE_NB -> SearcherType.IMAGE_NB_PATH;
                case REGEX_IMAGE_RGB -> SearcherType.IMAGE_RGB_PATH;
                case REGEX_AUDIO -> SearcherType.AUDIO_PATH;
                default -> null;
            };
        }
        return null;
    }

    public static boolean isRequestValid(String request) {
        SearcherType searcherType = getRequestType(request);

        if (searcherType == null) {
            return false;
        }
        if (searcherType.toString().contains("PATH")) {
            File f = new File(request);
            return f.exists();
        }
        return true;
    }
}
