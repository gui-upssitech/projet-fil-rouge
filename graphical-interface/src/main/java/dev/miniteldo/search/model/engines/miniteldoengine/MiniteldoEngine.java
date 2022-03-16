package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.Config;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.Searcher;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.IOException;
import java.util.ArrayList;

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
    public ArrayList<SearchResult> keywordSearch(String[] positiveKeywords, String[] negativeKeywords) {
        return null;
    }

    @Override
    public ArrayList<SearchResult> textFileSearch(String filePath) {
        return null;
    }

    @Override
    public ArrayList<SearchResult> bwImageSearch(String filePath) {
        Searcher searcher = SearcherFactory.getSearcher(SearcherType.IMAGE_NB_PATH);
        return searcher.search(filePath);
    }

    @Override
    public ArrayList<SearchResult> rgbImageSearch(String filePath) {
        Searcher searcher = SearcherFactory.getSearcher(SearcherType.IMAGE_RGB_PATH);
        return searcher.search(filePath);
    }

    @Override
    public ArrayList<SearchResult> audioSearch(String filePath) {
        return null;
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
