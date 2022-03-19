package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurator;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Logger;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.Indexer;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.Searcher;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.io.IOException;
import java.util.ArrayList;

public class MiniteldoEngine implements SearchEngine {

    @Override
    public boolean indexText() {
        boolean result = false;

        try {
            result = Indexer.indexText();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public boolean indexImage() {
        boolean result = false;

        try {
            result = Indexer.indexImage();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public boolean indexAudio() {
        boolean result = false;

        try {
            result = Indexer.indexAudio();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public boolean indexAll() {
        boolean result = false;

        try {
            result = Indexer.indexAll();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public ArrayList<SearchResult> keywordSearch(ArrayList<String> positiveKeywords, ArrayList<String> negativeKeywords) {
        ArrayList returnArray = new ArrayList();

        for (String s : positiveKeywords) {
            ArrayList<SearchResult> buffer;
            Searcher searcher = SearcherFactory.getSearcher(SearcherType.TEXT_KEYWORD);
            buffer = searcher.search(s);
            for (SearchResult result : buffer) {
                if (!returnArray.contains(result)) {
                    returnArray.add(result);
                }
            }
        }

        for (String s : negativeKeywords) {
            ArrayList<SearchResult> buffer;
            Searcher searcher = SearcherFactory.getSearcher(SearcherType.TEXT_KEYWORD);
            buffer = searcher.search(s);
            for (SearchResult result : buffer) {
                if (returnArray.contains(result)) {
                    returnArray.remove(result);
                }
            }
        }

        return returnArray;
    }

    @Override
    public ArrayList<SearchResult> textFileSearch(String filePath) {
        Searcher searcher = SearcherFactory.getSearcher(SearcherType.TEXT_PATH);
        return searcher.search(filePath);
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
        Searcher searcher = SearcherFactory.getSearcher(SearcherType.AUDIO_PATH);
        return searcher.search(filePath);
    }

    @Override
    public boolean login(String password) {
        boolean result = false;

        try {
            result = Logger.login(password);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    @Override
    public boolean logout() {
        return true;
    }

    @Override
    public boolean changePassword(String newPassword) {
        boolean result = false;

        try {
            result = Logger.resetPassword(newPassword);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public boolean setConfig(Configurations configName, int value) {
        boolean result = false;
        try {
            result =  Configurator.configure(configName, String.valueOf(value));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }
}
