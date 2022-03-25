package dev.miniteldo.search.model;

import dev.miniteldo.search.model.engines.EngineFactory;
import dev.miniteldo.search.model.engines.Engines;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * class: AppState
 * author: Guillaume Roussin
 * date: 13/03/2022
 */
public class AppState {

    // Singleton
    private static class AppStateHolder {
        public static final AppState instance = new AppState();
    }

    public static AppState getInstance() {
        return AppStateHolder.instance;
    }

    // Attributes
    private boolean darkMode;

    private Engines curEngine;
    private HashMap<Engines, SearchEngine> engines;
    private String currentRequest;

    // Constructor
    private AppState() {
        darkMode = false;
        currentRequest = null;

        engines = new HashMap<>();
        setEngine(Engines.MINITELDO_ENGINE); // DUMMY ENGINE will be the default engine for now NOT NOW Guillaume, NOT NOW
        getEngine().init();
    }

    // Methods

    // Theme selection

    public void toggleDarkMode() {
        darkMode = !darkMode;
    }

    public boolean isDarkMode() {
        return darkMode;
    }


    // Multiengine configuration
    public void setEngine(Engines engine) {
        if(!engines.containsKey(engine))
            engines.put(engine, EngineFactory.createEngine(engine));

        curEngine = engine;
    }

    public SearchEngine getEngine() {
        return engines.get(curEngine);
    }

    // Search request transmission

    public void setCurrentRequest(String currentRequest) {
        this.currentRequest = currentRequest;
    }

    public String getCurrentRequest() {
        return currentRequest;
    }
}