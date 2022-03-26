package dev.miniteldo.search.view;

import javafx.scene.Node;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;

import java.net.URL;

/**
 * class: ResultDisplayFactory
 * author: Guillaume Roussin
 * date: 22/03/2022
 */
public class ResultDisplayFactory {

    // Methods
    public static Node createPreview(String filePath) {
        String extension = filePath.substring(filePath.lastIndexOf(".") + 1);

        return switch(extension) {
            case "xml" -> createTextPreview(filePath);
            case "bmp", "jpg" -> createImagePreview(filePath);
            case "wav" -> createAudioPreview(filePath);
            default -> new Pane();
        };
    }

    private static ImageView createImagePreview(String filePath) {
        return new ImageView();

        // Image image = new Image(filePath);
        // return new ImageView(image);
    }

    private static Pane createAudioPreview(String filePath) {
        return new Pane();
    }

    private static Pane createTextPreview(String filePath) {
        return new Pane();
    }

}