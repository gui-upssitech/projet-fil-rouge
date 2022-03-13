package dev.miniteldo.search.view;

import javafx.fxml.FXML;
import javafx.scene.Group;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.io.InputStream;

/**
 * class: SVGImage
 * author: Guillaume Roussin
 * date: 12/03/2022
 */
public class SVGIcon extends Group {

    // TODO: Make functionnal !

    // Attributes
    @FXML public String path = "/images/icons/settings.png";

    // Constructor
    public SVGIcon() {
        super();

        Image icon = loadSVG();
        if(icon != null) {
            ImageView view = new ImageView(icon);
            getChildren().add(view);
        }
    }

    // Methods
    private Image loadSVG() {
        InputStream stream = getClass().getResourceAsStream(path);
        return (stream == null) ? null : new Image(stream);
    }

}