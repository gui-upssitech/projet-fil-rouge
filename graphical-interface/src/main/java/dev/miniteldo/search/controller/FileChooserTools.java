package dev.miniteldo.search.controller;

import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.nio.file.Paths;

public class FileChooserTools {
    public static File createFileChooser(Stage stage) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("All Files", "*.*"),
                new FileChooser.ExtensionFilter("TXT", "*.txt"),
                new FileChooser.ExtensionFilter("JPG", "*.jpg"),
                new FileChooser.ExtensionFilter("PNG", "*.png"),
                new FileChooser.ExtensionFilter("BIN", "*.bin"),
                new FileChooser.ExtensionFilter("WAV", "*.wav"));


        // Set title for FileChooser
        fileChooser.setTitle("Select Some Files");

        // Set Initial Directory
        String currentPath = Paths.get("").toAbsolutePath().toString();
        fileChooser.setInitialDirectory(new File(currentPath));
        File file = fileChooser.showOpenDialog(stage);

        return file;

    }
}
