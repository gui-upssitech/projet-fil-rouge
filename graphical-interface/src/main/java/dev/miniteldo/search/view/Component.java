package dev.miniteldo.search.view;

/**
 * class: Component
 * author: Guillaume Roussin
 * date: 20/03/2022
 */
public enum Component {
    SEARCH_RESULT("components/search-result.fxml");

    // Enum parameters

    // Attributes
    private final String path;

    // Constructor
    Component(String path) {
        this.path = path;
    }

    // Methods
    public String getPath() {
        return this.path;
    }

}