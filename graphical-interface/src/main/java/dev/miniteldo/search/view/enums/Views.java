package dev.miniteldo.search.view.enums;

public enum Views {
    MAIN("main-menu.fxml"),
    PARAMETERS("parameters.fxml"),
    SEARCH_RESULT("result-search.fxml"),
    ADMIN_CONFIG("configuration.fxml"),
    SAVE("save.fxml"),
    ERROR("error.fxml");

    // Enum parameters

    // Attributes
    private final String path;

    // Constructor
    Views(String path) {
        this.path = path;
    }

    // Methods
    public String getPath() {
        return this.path;
    }
}