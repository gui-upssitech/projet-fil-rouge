package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurator;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Logger;
import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.Descriptor;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.DescriptorFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.DescriptorType;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.Indexer;
import dev.miniteldo.search.model.engines.miniteldoengine.indexer.IndexerMode;
import dev.miniteldo.search.model.engines.miniteldoengine.openedclosedmode.OpenedClosedMode;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.Searcher;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.tools.Tools;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import static dev.miniteldo.search.model.tools.Tools.getDescriptorType;

public class MiniteldoEngine implements SearchEngine {

    protected final String miniteldoEnginePath;

    public MiniteldoEngine(String miniteldoEnginePath) {
        this.miniteldoEnginePath = miniteldoEnginePath;
    }

    @Override
    public void init() {
        Command command = new Command(miniteldoEnginePath, "init.sh");
        try {
            command.getResult();
            OpenedClosedMode.init(miniteldoEnginePath);
        } catch (IOException e) {
            e.printStackTrace();
        }

        HashMap<Configurations, Integer> configs = loadConfigs();
        if(configs.get(Configurations.INDEXING_MODE) == 1) {
            OpenedClosedMode.start();
        }
    }

    @Override
    public boolean indexText(IndexerMode mode) {
        boolean result = false;

        try {
            result = Indexer.indexText(miniteldoEnginePath, mode);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public boolean indexImage(IndexerMode mode) {
        boolean result = false;

        try {
            result = Indexer.indexImage(miniteldoEnginePath, mode);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public boolean indexAudio(IndexerMode mode) {
        boolean result = false;

        try {
            result = Indexer.indexAudio(miniteldoEnginePath, mode);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public boolean indexAll(IndexerMode mode) {
        boolean result = false;

        try {
            result = Indexer.indexAll(miniteldoEnginePath, mode);
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
            Searcher searcher = SearcherFactory.getSearcher(miniteldoEnginePath, SearcherType.TEXT_KEYWORD);
            buffer = searcher.search(s);
            for (SearchResult result : buffer) {
                if (!returnArray.contains(result)) {
                    returnArray.add(result);
                }
            }
        }

        for (String s : negativeKeywords) {
            ArrayList<SearchResult> buffer;
            Searcher searcher = SearcherFactory.getSearcher(miniteldoEnginePath, SearcherType.TEXT_KEYWORD);
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
        Searcher searcher = SearcherFactory.getSearcher(miniteldoEnginePath, SearcherType.TEXT_PATH);
        return searcher.search(filePath);
    }

    @Override
    public ArrayList<SearchResult> bwImageSearch(String filePath) {
        Searcher searcher = SearcherFactory.getSearcher(miniteldoEnginePath, SearcherType.IMAGE_NB_PATH);
        return searcher.search(filePath);
    }

    @Override
    public ArrayList<SearchResult> rgbImageSearch(String filePath) {
        Searcher searcher = SearcherFactory.getSearcher(miniteldoEnginePath, SearcherType.IMAGE_RGB_PATH);
        return searcher.search(filePath);
    }

    @Override
    public ArrayList<SearchResult> audioSearch(String filePath) {
        Searcher searcher = SearcherFactory.getSearcher(miniteldoEnginePath, SearcherType.AUDIO_PATH);
        return searcher.search(filePath);
    }

    @Override
    public boolean login(String password) {
        boolean result = false;

        try {
            result = Logger.login(miniteldoEnginePath, password);
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
            result = Logger.resetPassword(miniteldoEnginePath, newPassword);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public boolean setConfig(Configurations configName, int value) {
        boolean result = false;
        try {
            result =  Configurator.configure(miniteldoEnginePath, configName, String.valueOf(value));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    @Override
    public HashMap<Configurations, Integer> loadConfigs() {
        return Configurator.loadConfigs(miniteldoEnginePath);
    }

    @Override
    public Descriptor viewDescriptor(String filePath) {
        Descriptor descriptor = null;
        DescriptorType descriptorType = Tools.getDescriptorType(filePath);
        if(descriptorType != null) {
            String splits[] = filePath.split("/");
            switch (descriptorType) {
                case TEXT:
                    descriptor = DescriptorFactory.getDescriptor(miniteldoEnginePath, DescriptorType.TEXT, splits[splits.length - 1]);
                    break;

                case IMAGE:
                    descriptor = DescriptorFactory.getDescriptor(miniteldoEnginePath, DescriptorType.IMAGE, splits[splits.length - 1]);
                    break;

                case AUDIO:
                    break;
            }
        }
        return descriptor;
    }
}
