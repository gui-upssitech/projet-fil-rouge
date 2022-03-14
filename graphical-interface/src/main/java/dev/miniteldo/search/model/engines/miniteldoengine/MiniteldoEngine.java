package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearchResult;

public class MiniteldoEngine implements SearchEngine {
    @Override
    public boolean indexText() {
        return false;
    }

    @Override
    public boolean indexImage() {
        return false;
    }

    @Override
    public boolean indexAudio() {
        return false;
    }

    @Override
    public boolean indexAll() {
        return false;
    }

    @Override
    public SearchResult[] keywordSearch(String[] positiveKeywords, String[] negativeKeywords) {
        return new SearchResult[0];
    }

    @Override
    public SearchResult[] textFileSearch(String filePath) {
        return new SearchResult[0];
    }

    @Override
    public SearchResult[] bwImageSearch(String filePath) {
        return new SearchResult[0];
    }

    @Override
    public SearchResult[] rgbImageSearch(String filePath) {
        return new SearchResult[0];
    }

    @Override
    public SearchResult[] audioSearch(String filePath) {
        return new SearchResult[0];
    }

    @Override
    public boolean login(String password) {
        return false;
    }

    @Override
    public boolean logout() {
        return false;
    }

    @Override
    public boolean changePassword(String newPassword) {
        return false;
    }

    @Override
    public boolean setConfig(Config configName, int value) {
        return false;
    }
}
