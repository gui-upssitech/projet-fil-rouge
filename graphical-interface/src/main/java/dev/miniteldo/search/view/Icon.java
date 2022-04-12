package dev.miniteldo.search.view;

import dev.miniteldo.search.model.AppState;
import javafx.beans.property.*;
import javafx.fxml.Initializable;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.net.URL;
import java.util.ResourceBundle;

public class Icon extends ImageView {

    private static final AppState state = AppState.getInstance();

    // Attributes
    private StringProperty name;
    private IntegerProperty size;

    // Constructor
    public Icon() {
        super();
        setSize(24);
        paintComponent();

        state.addThemeListener(evt -> {
            if(evt.getPropertyName().equals("theme")) paintComponent();
        });
    }

    // Methods

    private void paintComponent() {
        String dir = state.isDarkMode() ? "dark" : "light";
        String path = "/images/icons/" + dir + "/" + getName() + ".png";

        URL url = getClass().getResource(path);
        Image image = (url == null) ? null : new Image(url.toExternalForm());

        this.setImage(image);
        this.setFitWidth(size.getValue());
        this.setFitHeight(size.getValue());

        this.setPickOnBounds(true);
        this.setPreserveRatio(true);
    }

    // Getters & setters

    public final IntegerProperty sizeProperty() {
        if (this.size == null) this.size = new SimpleIntegerProperty(this, "size", 24);
        return this.size;
    }

    public final void setSize(int newSize) {
        this.sizeProperty().setValue(newSize);
        paintComponent();
    }

    public final int getSize() {
        return this.size.getValue();
    }

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


}