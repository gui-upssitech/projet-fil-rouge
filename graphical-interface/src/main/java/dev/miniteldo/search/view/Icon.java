package dev.miniteldo.search.view;

import dev.miniteldo.search.model.AppState;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.fxml.Initializable;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.net.URL;
import java.util.ResourceBundle;

public class Icon extends ImageView {

    private static final AppState state = AppState.getInstance();

    // Attributes
    private StringProperty name;

    // Constructor
    public Icon() {
        super();

        paintComponent();

        state.addThemeListener(evt -> {
            if(evt.getPropertyName().equals("theme")) paintComponent();
        });
    }

    // Methods

    public final StringProperty nameProperty() {
        if (this.name == null) this.name = new SimpleStringProperty(this, "name", "");
        return this.name;
    }

    public final void setName(String newName) {
        this.nameProperty().setValue(newName);
        paintComponent();
    }

    public final String getName() {
        return this.name == null ? "" : this.name.getValue();
    }

    private void paintComponent() {
        String dir = state.isDarkMode() ? "icons-dark" : "icons";
        String path = "/images/" + dir + "/" + getName() + ".png";

        URL url = getClass().getResource(path);
        Image image = (url == null) ? null : new Image(url.toExternalForm());

        this.setImage(image);
    }
}