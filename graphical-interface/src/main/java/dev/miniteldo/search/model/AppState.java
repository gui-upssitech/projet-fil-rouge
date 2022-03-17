package dev.miniteldo.search.model;

import dev.miniteldo.search.model.engines.EngineFactory;
import dev.miniteldo.search.model.engines.Engines;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;

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
    private boolean adminMode;

    private Engines curEngine;
    private HashMap<Engines, SearchEngine> engines;
    private ArrayList<SearchResult> currentRequest;

    // Constructor
    private AppState() {
        darkMode = false;
        adminMode = false;

        engines = new HashMap<>();
        currentRequest = new ArrayList<>();
        setEngine(Engines.MINITELDO_ENGINE); // DUMMY ENGINE will be the default engine for now
    }

    // Methods

    // Theme selection

    public void toggleDarkMode() {
        darkMode = !darkMode;
    }

    public boolean isDarkMode() {
        return darkMode;
    }

    // Admin authorisation

    public boolean adminLogin(String password) {
        adminMode = password.equals("root");
        return adminMode;
    }

    public void adminLogout() {
        adminMode = false;
    }

    public boolean isAdmin() {
        return adminMode;
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

    public void setCurrentRequest(ArrayList<SearchResult> currentRequest) {
        this.currentRequest = currentRequest;
    }

    public ArrayList<SearchResult> getCurrentRequest() {
        return currentRequest;
    }
}