package dev.miniteldo.search.model;

import dev.miniteldo.search.model.engines.EngineFactory;
import dev.miniteldo.search.model.engines.Engines;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.view.enums.Dialog;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
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

    private String errorMessage = "";
    private String successMessage = "";
    private boolean popUp = false;

    private final PropertyChangeSupport support;

    // Constructor
    private AppState() {
        darkMode = true;
        currentRequest = null;
        curEngine = Engines.MINITELDO_ENGINE;

        engines = new HashMap<>();
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

    public String getImageFolder() {
        return (darkMode) ? "/images/icons-dark" : "/images/icons";
    }

    public void addThemeListener(PropertyChangeListener listener) {
        support.addPropertyChangeListener(listener);
    }


    // Multiengine configuration
    public void setEngine(Engines engine) {
        if (!engines.containsKey(engine)) engines.put(engine, EngineFactory.createEngine(engine));

        curEngine = engine;
    }

    public Engines getCurEngine() {
        return curEngine;
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


}