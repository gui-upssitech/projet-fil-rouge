package dev.miniteldo.search.model;

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

    // Constructor
    private AppState() {
        darkMode = false;
        adminMode = false;
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
}