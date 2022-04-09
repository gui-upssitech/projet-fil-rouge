package dev.miniteldo.search.model;

import dev.miniteldo.search.model.engines.Engines;
import dev.miniteldo.search.model.engines.EngineFactory;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.view.enums.Dialog;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
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

    private Engines curEngines;
    public HashMap<Engines, SearchEngine> engines;
    private ArrayList<SearchEngine> enginesSelected;
    private String currentRequest;

    private String errorMessage = "";
    private String successMessage = "";
    private boolean popUp = false;

    private final PropertyChangeSupport support;

    // Constructor
    private AppState() {
        darkMode = false;
        currentRequest = null;
        curEngines = Engines.MINITELDO_ENGINE;

        engines = new HashMap<>();
        enginesSelected = new ArrayList<>();
        setEngine(Engines.MINITELDO_ENGINE_2); // DUMMY ENGINE will be the default engine for now NOT NOW Guillaume, NOT NOW
        setEngine(Engines.MINITELDO_ENGINE); // DUMMY ENGINE will be the default engine for now NOT NOW Guillaume, NOT NOW
        getEngine().init();

        support = new PropertyChangeSupport(this);
    }

    // Methods

    // Theme selection

    public void toggleDarkMode() {
        String oldValue = (darkMode) ? "dark" : "light";
        String newValue = (!darkMode) ? "dark" : "light";

        darkMode = !darkMode;
        support.firePropertyChange("theme", oldValue, newValue);
    }

    public boolean isDarkMode() {
        return darkMode;
    }

    public void addThemeListener(PropertyChangeListener listener) {
        support.addPropertyChangeListener(listener);
    }


    // Multiengine configuration
    public void setEngine(Engines engines) {
        if (!this.engines.containsKey(engines))
            this.engines.put(engines, EngineFactory.createEngine(engines));

        curEngines = engines;
        getEngine().init();
    }

    public Engines getCurEngine() {
        return curEngines;
    }

    public SearchEngine getEngine() {
        return engines.get(curEngines);
    }

    // Search request transmission

    public void setCurrentRequest(String currentRequest) {
        this.currentRequest = currentRequest;
    }

    public String getCurrentRequest() {
        return currentRequest;
    }

    public void setDialogMessage(Dialog dialog, String message) {
        switch (dialog) {
            case ERROR -> errorMessage = message;
            case SUCCESS -> successMessage = message;
        }
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public String getSuccessMessage() {
        return successMessage;
    }

    public void setPopUp() {
        popUp = true;
    }

    public void clearPopUp() {
        popUp = false;
    }

    public boolean isPopUp() {
        return popUp;
    }

    public ArrayList<SearchEngine> getAllSearchEngine() {
        return new ArrayList<>(engines.values());
    }

    public ArrayList<Engines> getAllEngines() {
        return new ArrayList<>(engines.keySet());
    }

    public void addSelectedEngine(SearchEngine engine) {
        enginesSelected.add(engine);
    }

    public void removeSelectedEngine(int index) {
        enginesSelected.remove(index);
    }

    public void clearSelectedEngine() {
        enginesSelected.clear();
    }

    public SearchEngine getEngine(Engines engines) {
        return this.engines.get(engines);
    }

    public ArrayList<SearchEngine> getEnginesSelected() {
        return enginesSelected;
    }
}