package dev.miniteldo.search.view;

public enum Dialog {
    ERROR("error.fxml"),
    LOGIN("login.fxml"),
    SUCCESS("success.fxml");

    // Enum parameters

    // Attributes
    private final String path;

    // Constructor
    Dialog(String path) {
        this.path = path;
    }

    // Methods
    public String getPath() {
        return this.path;
    }
}
